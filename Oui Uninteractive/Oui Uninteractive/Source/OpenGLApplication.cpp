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
std::list<OpenGLObject> objects; // singleton

OpenGLObject::OpenGLModel mdl;

bool toggleMode = false;

// For Input
extern float mouse_scroll_total_Y_offset;
extern int lastkeyedcommand;

std::string title = "Hello";
int angle;
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

	// Create Vertex Buffers for the primitives (Shapes).
	//unsigned int vertexBuffer;
	//glGenBuffers(1, &vertexBuffer);
	//
	//glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	//glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), Objects.Triangle.data(), GL_STATIC_DRAW);
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);





	// Set up the projection matrix for world coordinates
	//float worldWidth = 20.0f;
	//float worldHeight = 20.0f * (height / (float)width);
	//glm::mat4 projection = glm::ortho(-worldWidth / 2, worldWidth / 2, -worldHeight / 2, worldHeight / 2, -1.0f, 1.0f);

	//init a game object in run time
	/*
	objectFactory->BuildObjectRunTime("ObjectRunTime1");
	objectFactory->AddComponent(ComponentType::PHYSICS_BODY, objectFactory->GetGameObjectByID(0));
	objectFactory->AddComponent(ComponentType::TRANSFORM, objectFactory->GetGameObjectByID(0));
	objectFactory->GetGameObjectByID(0)->Initialize();
	*/
	
	//initialize 2500 objects
	/*for (size_t i{}; i < 2500; ++i) {
		std::string goName{ "ObjectRunTime" + std::to_string(i + 1) };
		objectFactory->BuildObjectRunTime(goName);
		objectFactory->AddComponent(ComponentType::PHYSICS_BODY, objectFactory->GetGameObjectByID(i));
		objectFactory->AddComponent(ComponentType::TRANSFORM, objectFactory->GetGameObjectByID(i));
		objectFactory->GetGameObjectByID(i)->Initialize();

		GET_COMPONENT(objectFactory->GetGameObjectByID(i), Transform, ComponentType::TRANSFORM)->position.x = rand() % 800;
		GET_COMPONENT(objectFactory->GetGameObjectByID(i), Transform, ComponentType::TRANSFORM)->position.y = rand() % 600;
	}*/

	// De-serializing objects from JSON file
	std::cout << "\nDe-serializing objects from JSON file..." << std::endl;
	objectFactory->BuildObjectFromFile("../scenes/testscene.JSON");
	std::cout << "De-serializing objects from JSON file... completed." << std::endl;

	objectFactory->CloneObject(0);
	GET_COMPONENT(objectFactory->GetGameObjectByID(3), Transform, ComponentType::TRANSFORM)->position.x = 450;
	GET_COMPONENT(objectFactory->GetGameObjectByID(3), Transform, ComponentType::TRANSFORM)->position.y = 50;


	// Modifying value of Object2
	/*std::cout << "\nUpdating Object2..." << std::endl;
	GET_COMPONENT(objectFactory->GetGameObjectByName("Object2"), PhysicsBody, ComponentType::PHYSICS_BODY)->velocity.y = 20.5f;
	objectFactory->SaveObjectsToFile("../scenes/testscene.JSON");
	std::cout << "Updating Object2... completed." << std::endl;*/
}

int positionX = 0;
void OpenGLApplication::OpenGLUpdate()
{
		OpenGLSetBackgroundColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		double xpos, ypos{};
		glfwGetCursorPos(window, &xpos, &ypos);
		//glUseProgram(Objects.ShaderProgram);
		//glBindVertexArray(Objects.VAO);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
				
		angle++;
		// All these should be OBJECTS. THAT UPDATE.
		// Objects.Update(0.1);


		//// create transformations
		// glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		// transform = glm::translate(transform, glm::vec3(Objects.position.x, Objects.position.y, 1.0f));
		// //transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, -0.1f));
		// 
		// glm::ortho(0.0f, 900.0f, 0.0f, 600.0f, 0.1f, 100.0f);
		// 
		// unsigned int transformLoc = glGetUniformLocation(OpenGLObject::ShaderProgram, "transform");
		// glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

		//mdl.draw();
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
			
//			OpenGLObject::OpenGLModel a;
			
			


			

			OpenGLObject newObject(0);
			//newObject.VAO = 222;
			newObject.InitObjects(0,0, 150,180,0,45);
			std::cout << newObject.position.x << newObject.position.y << '\n';
			
			
			
			
			objects.emplace_back(newObject);
			//OpenGLObject* object = GET_COMPONENT(objectFactory->GetGameObjectByID(0), Transform, ComponentType::TRANSFORM)->graphics;
			/*if (object != nullptr) {
				objects.emplace_back(*object);
			}

			*/	
			
		}

		if (keyStates[GLFW_KEY_A] ==2)
		{
			positionX--;
			std::cout << positionX<< '\n';
		}

		if (keyStates[GLFW_KEY_RIGHT_SHIFT] == 1)
		{
			std::cout << "Shift\n";
			OpenGLObject newObject(1);
			
			
			newObject.InitObjects(positionX, 100, 150, 180, 45, 45);
			objects.emplace_back(newObject);

			std::cout << objects.size() << '\n';
			
		}


		if (keyStates[GLFW_KEY_M] == 1)
		{
			Particle newparticle;


			newparticle.object.InitObjects(300, 300, 180, 180,45,45);
			//std::cout << "R : " << newparticle.object.color.r << "\nG : " << newparticle.object.color.g << "\nB : " << newparticle.object.color.b << "\n";
			objects.emplace_back(newparticle.object);
		}





//		std::cout << "xpos : " << xpos << "\nypos : " << ypos << std::endl;
		int windowWidth, windowHeight{};
		glfwGetWindowSize(window, &windowWidth, &windowHeight);

		if (mouseButtonStates[GLFW_MOUSE_BUTTON_LEFT] == 1)
		{
			//OpenGLObject newObject;
			//
			//newObject.InitObjects(2*(static_cast<int>(xpos) - windowWidth / 2), -2*((static_cast<int>(ypos) - windowHeight / 2)), 180, 180, 45,45);
			//objects.emplace_back(newObject);

		}

//		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);


		//glBegin(GL_QUADS);
		//
		//// This is using NDC coordinates ... Take Note
		//glVertex2f(squareX - 0.1f, squareY + 0.1f);
		//glVertex2f(squareX - 0.1f, squareY - 0.1f);
		//glVertex2f(squareX + 0.1f, squareY - 0.1f);
		//glVertex2f(squareX + 0.1f, squareY + 0.1f);
		//
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		//
		//
		//
		////glVertex2f(-5.0f, 5.0f);
		////glVertex2f(-5.0f, -5.0f);
		////glVertex2f(5.0f, -5.0f);
		////glVertex2f(5.0f, 5.0f);
		//
		//glEnd();

		

		/*-----------------------------------------------------------------------------
		|                               INPUT UPDATES                                 |
		-----------------------------------------------------------------------------*/
		// This is where you change what each key does when pressed.


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
				physicsSys->SetCurrentRotationSpeed(20, 0);
				Objects.position.x -= 0.001;
//				CurrentGameState = STATE_LEVEL_TEST;

			}

			else if (keyStates[GLFW_KEY_D]) {
				//std::cout << "WALK RIGHT\n";
				physicsSys->SetCurrentRotationSpeed(-20, 0);
				Objects.position.x += 0.001;
//				CurrentGameState = STATE_GRAPHICS_TEST;
			}
			else{
				physicsSys->SetCurrentRotationSpeed(0, 0);
			}

			if (keyStates[GLFW_KEY_S]) {
				Objects.position.y -= 0.001;
				physicsSys->MoveBackwards(0);
				//physicsSys->setVelocity(Vec2(50.f, 0.0));
				//std::cout << "WALK DOWN\n";
			}

			else if (keyStates[GLFW_KEY_W]) {
				Objects.position.y += 0.001;
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

		if (mouseButtonStates[GLFW_MOUSE_BUTTON_LEFT])
			std::cout << "LCLICK\n";
		if (mouseButtonStates[GLFW_MOUSE_BUTTON_RIGHT])
			std::cout << "RCLICK\n";

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
				obj.Update(positionX, 300, 100, angle, true);
			
			if (obj.TagID == 0)
				obj.Update(10, 10, 100, 0);

		
		}
		for (std::pair<size_t, GameObject*> gObj : objectFactory->GetGameObjectIDMap()) {
			GET_COMPONENT(gObj.second, Transform, ComponentType::TRANSFORM)->shape->Draw();
		
		}
		

		for (auto const& x : objects)
		{
			x.Draw();
		}



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
	// update object transforms
	for (auto const& obj : OpenGLObject::Object_Storage)
	{
		if (obj.first == "Camera")
			continue;
#ifdef _DEBUG
		//std::cout << x.first << '\n';
		//std::cout << "YES\n";
#endif
		obj.second.Draw();

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