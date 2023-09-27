/**************************************************************************
 * @file OpenGLApplication.cpp
 * @author 
 * @par DP email: 
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 09-05-2023
 * @brief 
 *************************************************************************/

#include <iostream>
#include <OpenGLApplication.h>
#include <Input.h>
#include <RandomUtilities.h>
#include <glm/gtc/matrix_transform.hpp>
#include <GameStateManager.h>
#include <Editor.h>	
#include <Mapping.h>
#include <ObjectFactory.h>
#include <Physics.h>
#include <JsonSerializer.h>
#include <Global.h>
#include <Sound.h>
#include <ParticleSystem.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>



std::string title = "Hello";

 // Pointer to the window
GLFWwindow* window;

// To store the window dimensions for duration of program
std::pair<unsigned short, unsigned short> windowSize;

// ImGui and Editor instance
UsingImGui myImGui;
Editor myEditor;

// Serializer instance
JsonSerializer serializer;

GLfloat squareX = 0.0f, squareY = 0.0f;

OpenGLObject Objects;
std::list<OpenGLObject> objects;					// singleton

Particle background;
ParticleSystem particleSystem;

OpenGLObject::OpenGLModel mdl;
int positionX = 0, angle;

bool toggleMode = false;
// For Input
extern float mouse_scroll_total_Y_offset;
extern int lastkeyedcommand;

static bool glewInitialized = false;
static bool imguiInitialized = false;

void OpenGLApplication::OpenGLWindowInit()
{
	// Read window size from JSON
	std::string filePath = "../window-data/window-data.JSON";
	rapidjson::Document windowDoc;
	// Initialize window dimensions from JSON
	if (serializer.ReadJSONFile(filePath, windowDoc)) {
		windowSize.first = windowDoc["windowX"].GetInt();
		windowSize.second = windowDoc["windowY"].GetInt();
	}

	std::cout << windowSize.first << windowSize.second;

	// Create window application based on the windowSize.
	window = glfwCreateWindow(windowSize.first, windowSize.second, "hello", NULL, NULL);
	if (!window)
	{
		glfwTerminate();

		std::cout << "Problem\n";
		return;
	}

	// Tell GLFW we are using OpenGL 4.5
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);


	// Tell GLFW that we are using the CORE Profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create viewport of width and height.
	glViewport(0, 0, windowSize.first, windowSize.second);

	glfwSwapInterval(1);

	// Receives Key input/output [Checks for Key Presses]
	glfwSetKeyCallback(window, keyCallBack);

	// Receives Mouse input/output [Checks for Mouse Clicks]
	glfwSetMouseButtonCallback(window, mouseCallBack);

	glfwSetScrollCallback(window, scrollCallBack);

	// Make the current window the current context
	glfwMakeContextCurrent(window);

	// Set input mode for the window with the cursor (Enables Cursor Input)
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	// Set glfw window resize callback function
	glfwSetWindowSizeCallback(window, OpenGLWindowResizeCallback);


}



void OpenGLApplication::OpenGLWindowCleanup()
{
	// Save window size
	std::string filePath = "../window-data/window-data.JSON";
	rapidjson::Document windowDoc;
	if (serializer.ReadJSONFile(filePath, windowDoc)) {
		windowDoc["windowX"] = windowSize.first;
		windowDoc["windowY"] = windowSize.second;
		serializer.WriteJSONFile(filePath, windowDoc);
	};


	myImGui.Exit();
	glfwTerminate();
}



void OpenGLApplication::OpenGLInit()
{

	if (!glewInitialized) {
		GLenum err = glewInit();
		if (err != GLEW_OK) {
			// Handle initialization error
			// You can print an error message or take appropriate action here.
			return;
		}
		glewInitialized = true;
	}

	
	// Print to check if it pass through this line ...
	std::cout << "Initialization Graphics Pipeline\n";

	const char* glsl_vers = "#version 130";

	Objects.Init();
//	Objects.InitObjects();


	// Initializing ImGui
	if (!imguiInitialized) {
		myImGui.Init(window, glsl_vers);
		imguiInitialized = true;
	}
	// Initializing Editor
	myEditor.Init();





	//init a game object in run time
	/*
	objectFactory->BuildObjectRunTime("ObjectRunTime1");
	objectFactory->AddComponent(ComponentType::PHYSICS_BODY, objectFactory->GetGameObjectByID(0));
	objectFactory->AddComponent(ComponentType::TRANSFORM, objectFactory->GetGameObjectByID(0));
	objectFactory->GetGameObjectByID(0)->Initialize();
	*/
	
	//initialize 2500 objects
	//for (size_t i{}; i < 2500; ++i) {
	//	std::string goName{ "ObjectRunTime" + std::to_string(i + 1) };
	//	objectFactory->BuildObjectRunTime(goName, "Enemy");
	//	objectFactory->AddComponent(ComponentType::PHYSICS_BODY, objectFactory->GetGameObjectByID(i));
	//	objectFactory->AddComponent(ComponentType::TRANSFORM, objectFactory->GetGameObjectByID(i));
	//	objectFactory->GetGameObjectByID(i)->Initialize();

	//	GET_COMPONENT(objectFactory->GetGameObjectByID(i), Transform, ComponentType::TRANSFORM)->position.x = rand() % 800;
	//	GET_COMPONENT(objectFactory->GetGameObjectByID(i), Transform, ComponentType::TRANSFORM)->position.y = rand() % 600;
	//}

	// Prefabs
	std::cout << "\nLoading prefabs from JSON file..." << std::endl;
	objectFactory->LoadPrefab("../prefab/Prefab.JSON");
	std::cout << "Loading prefabs from JSON file... completed." << std::endl;

	// De-serializing objects from JSON file
	std::cout << "\nDe-serializing objects from JSON file..." << std::endl;
	objectFactory->BuildObjectFromFile("../scenes/TestsceneReading.JSON");
	std::cout << "De-serializing objects from JSON file... completed." << std::endl;

	std::cout << "\nBuilding an object from player prefab..." << std::endl;
	objectFactory->BuildObjectFromPrefab("PlayerObjFromPrefab", "Player");
	std::cout << "Building an object from player prefab... completed." << std::endl;

	std::cout << "\nCloning object with ID 0..." << std::endl;
	objectFactory->CloneObject(0);
	GET_COMPONENT(objectFactory->GetGameObjectByID(4), Transform, ComponentType::TRANSFORM)->position.x = 450;
	GET_COMPONENT(objectFactory->GetGameObjectByID(4), Transform, ComponentType::TRANSFORM)->position.y = 50;
	std::cout << "Cloning object with ID 0... completed." << std::endl;

	// Modifying value of Object2
	std::cout << "\nUpdating JSONEnemy2..." << std::endl;
	GET_COMPONENT(objectFactory->GetGameObjectByName("JSONEnemy2"), PhysicsBody, ComponentType::PHYSICS_BODY)->velocity.y = 20.5f;
	objectFactory->SaveObjectsToFile("../scenes/TestsceneWriting.JSON");
	std::cout << "Updating Object2... completed." << std::endl;

	
	//background.init(0, 0, windowSize.first, windowSize.second, 0, 0);
}

void OpenGLApplication::OpenGLUpdate()
{
		OpenGLSetBackgroundColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//background.draw();

		double xpos, ypos{};
		glfwGetCursorPos(window, &xpos, &ypos);

		angle++;

		//WireFrame Mode:
		if (keyStates[GLFW_KEY_P] == 1)
		{
			toggleMode =  !toggleMode;
			
		}

		if (toggleMode == true)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		if (toggleMode == false)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		if (keyStates[GLFW_KEY_SPACE] == 1)
		{
			OpenGLObject newObject(2);

			newObject.models[0].ModelID = 0;


			//OpenGLObject newObject(0);
//			newObject.models[0].ModelID = 0;
			//newObject.models[0].texture = secondTexture;
			std::cout << "Tag ID: " << newObject.TagID << '\n';
			newObject.InitObjects(0,0, 150,180,0,45);

			std::cout << "Model ID: " << newObject.models[0].ModelID << "\n\n";
	
			objects.emplace_back(newObject);

		}
		if (keyStates[GLFW_KEY_RIGHT_SHIFT] == 1)
		{
			std::cout << "Shift\n";
			OpenGLObject newObject1(1);
			std::cout << "Tag ID: " << newObject1.TagID << '\n';
			newObject1.models[0].ModelID =0; // Change the ModelID to 2


			newObject1.InitObjects(positionX, 100, 150, 180, 45, 45);


			std::cout << "Model ID: " << newObject1.models[0].ModelID << '\n';
			objects.emplace_back(newObject1);
		}
		if (keyStates[GLFW_KEY_A] ==2)
		{
			positionX--;
			std::cout << positionX<< '\n';
		}
		if (keyStates[GLFW_KEY_H] == 1)
		{
			std::cout << objects.size();
		}

		if (keyStates[GLFW_KEY_M] == 1)
		{
			Particle newparticle;

			newparticle.init(0, 0, 15000, 15000, 0, 0);
			
		}




		int windowWidth, windowHeight{};
		glfwGetWindowSize(window, &windowWidth, &windowHeight);

		if (mouseButtonStates[GLFW_MOUSE_BUTTON_LEFT] == 1)
		{
		}


		/*-----------------------------------------------------------------------------
		|                               INPUT UPDATES                                 |
		-----------------------------------------------------------------------------*/
		/*-----------------------------------
		|            ALPHABETS              |
		-----------------------------------*/

		if (keyStates[GLFW_KEY_RIGHT_CONTROL] || keyStates[GLFW_KEY_LEFT_CONTROL]) {
			if (keyStates[GLFW_KEY_A]) {
				std::cout << "CROUCH LEFT";
			}

			if (keyStates[GLFW_KEY_D]) {
				std::cout << "CROUCH RIGHT";
			}

			if (keyStates[GLFW_KEY_S]) {
				std::cout << "CROUCH DOWN";
			}

			if (keyStates[GLFW_KEY_W]) {
				std::cout << "CROUCH UP";
				
			}
		}
		else

		// IF BIG LETTERS
		if (((keyStates[GLFW_KEY_RIGHT_SHIFT] || keyStates[GLFW_KEY_LEFT_SHIFT]) && !keyStates[GLFW_KEY_CAPS_LOCK]) + (!(keyStates[GLFW_KEY_RIGHT_SHIFT] || keyStates[GLFW_KEY_LEFT_SHIFT]) && keyStates[GLFW_KEY_CAPS_LOCK])) {

			if (keyStates[GLFW_KEY_A]) {
				std::cout << "RUN LEFT\n";
			}

			if (keyStates[GLFW_KEY_D]) {
				std::cout << "RUN RIGHT\n";
			}

			if (keyStates[GLFW_KEY_S]) {
				std::cout << "RUN DOWN\n";
			}

			if (keyStates[GLFW_KEY_W]) {
				std::cout << "RUN UP\n";
				
			}


		}

		// IF SMALL LETTERS
		else {

			if (keyStates[GLFW_KEY_A]) {
				//std::cout << "WALK LEFT\n";
				physicsSys->SetCurrentRotationSpeed(GET_COMPONENT(objectFactory->GetGameObjectByID(0), PhysicsBody, ComponentType::PHYSICS_BODY)->rotationSpeed, 0);
				//Objects.position.x -= 0.001;
//				CurrentGameState = STATE_LEVEL_TEST;

			}

			else if (keyStates[GLFW_KEY_D]) {
				//std::cout << "WALK RIGHT\n";
				physicsSys->SetCurrentRotationSpeed(-(GET_COMPONENT(objectFactory->GetGameObjectByID(0), PhysicsBody, ComponentType::PHYSICS_BODY)->rotationSpeed), 0);
				//Objects.position.x += 0.001;
//				CurrentGameState = STATE_GRAPHICS_TEST;
			}
			else{
				physicsSys->SetCurrentRotationSpeed(0, 0);
			}

			if (keyStates[GLFW_KEY_S]) {
				//Objects.position.y -= 0.001;
				physicsSys->MoveBackwards(0);
				//physicsSys->setVelocity(Vec2(50.f, 0.0));
				//std::cout << "WALK DOWN\n";
			}

			else if (keyStates[GLFW_KEY_W]) {
				//Objects.position.y += 0.001;
				physicsSys->MoveForward(0);
				//std::cout << "WALK UP\n";
			}
			else {
				physicsSys->SetVelocity(Vec2(0.0f, 0.0f));
			}

			if (keyStates[GLFW_KEY_M]) {
				Mapping map;
				map.rows = 4;
				map.columns = 5;
				map.entitymap = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20 };
				map.filename = "hi";
				Mapping::MapBuilder(map);
			}

			if (keyStates[GLFW_KEY_R]) {
				Mapping map;
				map.filename = "hi";
				Mapping::MapReader(map);
			}

		}

		/*-----------------------------------
		|             NUMBERS               |
		-----------------------------------*/


		/*-----------------------------------
		|              OTHERS               |
		-----------------------------------*/
		if (keyStates[GLFW_KEY_ESCAPE]) {
			glfwSetWindowShouldClose(window, GLFW_TRUE);
			//glfwWindowShouldClose(window);
			CurrentGameState = STATE_QUIT;
		}

		/*-----------------------------------
		|              Mouse                |
		-----------------------------------*/

	/*	if (mouseButtonStates[GLFW_MOUSE_BUTTON_LEFT])
			std::cout << "LCLICK\n";
		if (mouseButtonStates[GLFW_MOUSE_BUTTON_RIGHT])
			std::cout << "RCLICK\n";*/

		/*-----------------------------------
		|              Scroll               |
		-----------------------------------*/

		if (mouseScrollState == 1) {
			std::cout << "SCROLL UP\n";
			std::cout << "Total Scroll Y Offset:" << mouse_scroll_total_Y_offset << "\n";
		}
		if (mouseScrollState==-1) {
			std::cout << "SCROLL DOWN\n";
			std::cout << "Total Scroll Y Offset:" << mouse_scroll_total_Y_offset << "\n";
		}

		updateStatesForNextFrame();

		//particleSystem.update();
		
		//std::cout << GetFPS() << '\n';
		
		// Draws every second...
		
		Draw();
	
		

		/*---------------------------------------------------------------------------*/
		/*-----------------------------------
		|       Sound Stuff Testing         |
		-----------------------------------*/
		

		/*-----------------------------------
		|       ImGui Stuff Testing         |
		-----------------------------------*/
		myImGui.CreateFrame();
		myImGui.Update();
		myImGui.Draw();

		if (angle > 360)
			angle = 0;

		// Swap the front and back buffers
		/*
		*/
		for (OpenGLObject& obj : objects)
		{
			if (obj.TagID == 1)
				obj.Update(positionX, 300, 100,100 ,angle, true);
			

			if (obj.TagID == 0)
				obj.Update(10, 10, 100, 0);

			if (obj.TagID == 3)
			{
				obj.Update(100, 100, 50, 50);
			}
			if (obj.TagID == 2)
			{
				obj.Update(300, 400, 50, 50);
			}

		}
		for (std::pair<size_t, GameObject*> gObj : objectFactory->GetGameObjectIDMap()) {
			if (gObj.second->Has(ComponentType::TRANSFORM) != -1) {
				GET_COMPONENT(gObj.second, Transform, ComponentType::TRANSFORM)->shape->Draw();
			}	
		}





		//particleSystem.draw();

}


/**************************************************************************
* @brief Cleanup the applcation process.
* @param none
* @return void
*************************************************************************/
void OpenGLApplication::OpenGLCleanup()
{
	Objects.Cleanup();
	OpenGLSetBackgroundColor(0.0f, 0.0f, 0.0f,0.0f);


}





void OpenGLApplication::Draw() {

#ifdef _DEBUG
//	std::cout << "Object Storage Size:" << OpenGLObject::Object_Storage.size() << '\n';


#endif
//	// update object transforms
//	for (auto const& obj : OpenGLObject::Object_Storage)
//	{
//		if (obj.first == "Camera")
//			continue;
//#ifdef _DEBUG
//		//std::cout << x.first << '\n';
//		//std::cout << "YES\n";
//#endif
//		obj.second.Draw();
//
//	}

	for (auto const& obj : objects)
	{	
		obj.Draw();

	}

	
	// to prevent spamming
	if (IsTimeElapsed(1))
	{	
		// setting up the text to be displayed as the window title
		std::stringstream sStr;
		sStr << title.c_str() << " | "
			<< std::fixed << std::setprecision(2)
			<< "FPS:  | " << GetFrames();

		// setting the text as the window title
		glfwSetWindowTitle(window, sStr.str().c_str());
	}

}

void OpenGLApplication::OpenGLSetBackgroundColor(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
}



void OpenGLApplication::OpenGLTestChangingStates()
{
	OpenGLSetBackgroundColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(Objects.ShaderProgram);
	glBindVertexArray(Objects.VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);


	if (keyStates[GLFW_KEY_D]) {
		std::cout << "WALK RIGHT\n";
		CurrentGameState = STATE_GRAPHICS_TEST;
	}



	if (IsTimeElapsed(1))
	{
		Draw();
	}
}

void OpenGLApplication::OpenGLWindowResizeCallback(GLFWwindow* window, int width, int height) {
	// Update the window dimensions once changed
	// set callback for the window size
	glViewport(0, 0, width, height);
	windowSize.first = width;
	windowSize.second = height;
}