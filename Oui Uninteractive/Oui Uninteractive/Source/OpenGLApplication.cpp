/**************************************************************************
 * @file OpenGLApplication.cpp
 * @author 	TAN Angus Yit Hoe
 * @co-author CHEAH Tristan Tze Hong, HWANG Jing Rui, Austin, LOW Wang Chun, Mark, CHAN Aaron Jun Xiang, QUEK Cheng Kwang Emery
 * @par DP email: tan.a@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 29-09-2023
 * @brief
 *
 * This file allows the creation and initialization of a OpenGL Application
 * Window which then allows user to draw functions and/or change states
 * depending on the game state manager.
 *
 *
 *************************************************************************/

#include <iostream>
#include "LogicComponent.h"
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
#include <iterator>
#include <Background.h>
#include "TestScript.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>



std::string title = "Oui Uninteractive Game Engine Editor";

// Pointer to the window
GLFWwindow* windowNew;

// To store the window dimensions for duration of program
std::pair<int, int> windowSize;

// ImGui and Editor instance
UsingImGui myImGui;
Editor myEditor;

// Serializer instance
JsonSerializer serializer;


OpenGLObject Objects;								// First Instance of Object to Update.
std::list<OpenGLObject> objects;					// singleton

// Initialize Background
Background background;

ParticleSystem particleSystem;


OpenGLObject::OpenGLModel mdl;
float positionX = 0;
float angle;

bool togglePolygonMode = false;
// For Input
extern float mouse_scroll_total_Y_offset;
extern int lastkeyedcommand;

static bool glewInitialized = false;
static bool imguiInitialized = false;



/**************************************************************************
* @brief		Set the parameters for the window, and then Initialize the
*				Window.
*				Then, Set parameters for OpenGL Context.
*				> Drawing the Window.
* @param  none
* @return void
*************************************************************************/
void OpenGLApplication::OpenGLWindowInit() {
	// Read window size from JSON
	std::string filePath = "../window-data/window-data.JSON";
	rapidjson::Document windowDoc;
	// Initialize window dimensions from JSON
	if (serializer.ReadJSONFile(filePath, windowDoc)) {
		windowSize.first = windowDoc["windowX"].GetInt();
		windowSize.second = windowDoc["windowY"].GetInt();
	}
#ifdef _DEBUG
	std::cout << "Win Size\n";
	std::cout << windowSize.first << windowSize.second;
#endif
	// Create window application based on the windowSize.
	windowNew = glfwCreateWindow(windowSize.first, windowSize.second, "hello", NULL, NULL);
	if (!windowNew) {
		glfwTerminate();

		std::cout << "Window parameters are wrong.\n";
		std::cout << "Parameter: WinSize Width: " << windowSize.first << " (If it is 0, Error)" << '\n';
		std::cout << "Parameter: WinSize Height: " << windowSize.second << " (If it is 0, Error)" << '\n';
		return;
	}

	// Tell GLFW we are using OpenGL 4.5
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);


	// Tell GLFW that we are using the CORE Profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create viewport of width and height.
	glViewport(0, 0, windowSize.first, windowSize.second);

	glfwSwapInterval(0);

	// Receives Key input/output [Checks for Key Presses]
	glfwSetKeyCallback(windowNew, KeyCallBack);

	// Receives Mouse input/output [Checks for Mouse Clicks]
	glfwSetMouseButtonCallback(windowNew, MouseCallBack);

	glfwSetScrollCallback(windowNew, ScrollCallBack);

	// Make the current window the current context
	glfwMakeContextCurrent(windowNew);

	// Set input mode for the window with the cursor (Enables Cursor Input)
	glfwSetInputMode(windowNew, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	// Set glfw window resize callback function
	glfwSetWindowSizeCallback(windowNew, OpenGLWindowResizeCallback);


}


/**************************************************************************
* @brief		Cleanup the Window at the end of the loop.
*
* @param  none
* @return void
*************************************************************************/
void OpenGLApplication::OpenGLWindowCleanup() {
	// Save window size
	std::string filePath = "../window-data/window-data.JSON";
	rapidjson::Document windowDoc;
	if (serializer.ReadJSONFile(filePath, windowDoc) && windowSize.first != 0 && windowSize.second != 0) {
		windowDoc["windowX"] = windowSize.first;
		windowDoc["windowY"] = windowSize.second;
		serializer.WriteJSONFile(filePath, windowDoc);
	};


	myImGui.Exit();
	glfwTerminate();
}


/**************************************************************************
* @brief		Initialize the Graphics Pipeline to enable usage of OpenGL
*
*				Drawing the Window.
*
* @param  none
* @return void
*************************************************************************/
void OpenGLApplication::OpenGLInit() {

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
	std::cout << "Initialization Graphics Pipeline | < OpenGLInit() > \n";

	const char* glsl_vers = "#version 130";

	// Creates an Object to Initialize it.
	Objects.Init();


	// Initializing ImGui
	if (!imguiInitialized) {
		myImGui.Init(windowNew, glsl_vers);
		imguiInitialized = true;
	}
	// Initializing Editor
	myEditor.Init();

	// Prefabs
#ifdef _DEBUG 
	std::cout << "\nLoading prefabs from JSON file..." << std::endl;
#endif
	objectFactory->LoadPrefab("../prefab/Prefab.JSON");

#ifdef _DEBUG
	std::cout << "Loading prefabs from JSON file... completed." << std::endl;
#endif

	// De-serializing objects from JSON file

#ifdef _DEBUG
	std::cout << "\nDe-serializing objects from JSON file..." << std::endl;
#endif
	//PLAYER OBJECT
	objectFactory->BuildObjectFromFile("../scenes/TestsceneReading.JSON");
	//objectFactory->GetGameObjectByID(0)->AddComponent(new LogicComponent(), ComponentType::LOGIC_COMPONENT);
	objectFactory->GetGameObjectByID(0)->Initialize();
	//LogicComponent* playerLogic = GET_COMPONENT(objectFactory->GetGameObjectByID(0), LogicComponent, ComponentType::LOGIC_COMPONENT);
	PhysicsBody* playerBody = GET_COMPONENT(objectFactory->GetGameObjectByID(0), PhysicsBody, ComponentType::PHYSICS_BODY);
	//apply movement script to player
	//playerLogic->scriptIndexSet.insert(LOGIC_ENUM::PLAYER_MOVEMENT);

#ifdef _DEBUG
	std::cout << "De-serializing objects from JSON file... completed." << std::endl;
#endif

#ifdef _DEBUG
	std::cout << "\nBuilding an object from player prefab..." << std::endl;
#endif
	objectFactory->BuildObjectFromPrefab("PlayerObjFromPrefab", "Player");

#ifdef _DEBUG	
	std::cout << "Building an object from player prefab... completed." << std::endl;
#endif

#ifdef _DEBUG	
	std::cout << "\nCloning object with ID 0..." << std::endl;
#endif
	//AI OBJECT
	
	objectFactory->CloneObject(1);
	//objectFactory->GetGameObjectByID(4)->AddComponent(new LogicComponent(), ComponentType::LOGIC_COMPONENT);
	objectFactory->GetGameObjectByID(4)->Initialize();
	//LogicComponent* logicTest = GET_COMPONENT(objectFactory->GetGameObjectByID(4), LogicComponent, ComponentType::LOGIC_COMPONENT);
	//logicTest->scriptIndexSet.insert(LOGIC_ENUM::TEST_SCRIPT1);
	GET_COMPONENT(objectFactory->GetGameObjectByID(4), Transform, ComponentType::TRANSFORM)->position.x = 450;
	GET_COMPONENT(objectFactory->GetGameObjectByID(4), Transform, ComponentType::TRANSFORM)->position.y = 50;

#ifdef _DEBUG	
	std::cout << "Cloning object with ID 0... completed." << std::endl;
#endif

	// Modifying value of JSONEnemy2

#ifdef _DEBUG	
	std::cout << "\nUpdating JSONEnemy2 during initialization..." << std::endl;
#endif
	objectFactory->SaveObjectsToFile("../scenes/TestsceneWriting.JSON");

#ifdef _DEBUG	
	std::cout << "Updating JSONEnemy2 during initialization... completed." << std::endl;
#endif

	//SCRIPTS

	TestScript* testScript = new TestScript();
	testScript->Initialize();
	

	TestScript2* testScript2 = new TestScript2();
	testScript2->Initialize();

	
	background.Init();
}


/**************************************************************************
* @brief		Updates anything that is required to be on the window.
*				> Update Game Object
*				> Update Background
*				> Update Color
*				> Draw
* @param  none
* @return void
*************************************************************************/
void OpenGLApplication::OpenGLUpdate() {

	// End the Game.
	if (keyStates[GLFW_KEY_ESCAPE]) {
		// set the window to CLOSE.
		glfwSetWindowShouldClose(windowNew, GLFW_TRUE);
		// Set game state to quit to exit the while loop
		CurrentGameState = STATE_QUIT;
	}
	myImGui.CreateFrame();
	myEditor.Update();
	myImGui.Update();
	particleSystem.Update();
	// Create x and y pos variables to collect data from the mouse position.
	double xpos, ypos{};
	glfwGetCursorPos(windowNew, &xpos, &ypos);

#ifdef _DEBUG
	// For Debugging Purposes on angles.
	angle += 0.05f;
#endif

	//set WireFrame Mode to TRUE/FALSE:
	if (keyStates[GLFW_KEY_P] == 1) {
		togglePolygonMode = !togglePolygonMode;
	}
	// If True, set to line else FILL it with color.
	if (togglePolygonMode == true) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	if (togglePolygonMode == false) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}


	// Create Object using SPACE. with tag ID of 2.
	if (keyStates[GLFW_KEY_SPACE] == 1) {
		// Create Object Tag ID , 2
		OpenGLObject newObject(2);

#ifdef _DEBUG
		std::cout << "Tag ID: " << newObject.TagID << '\n';
#endif
		// Init Objects
		newObject.InitObjects();

		// Emplace back into the container.
		objects.emplace_back(newObject);

	}
	// Create Object using R-SHIFT, with tag ID of 1.
	if (keyStates[GLFW_KEY_RIGHT_SHIFT] == 1) {
		OpenGLObject newObject1(1);
#ifdef _DEBUG
		std::cout << "Tag ID: " << newObject1.TagID << '\n';
#endif

		newObject1.InitObjects();

		// Emplace back into the container.
		objects.emplace_back(newObject1);
	}

	// Moves Object left. can add positionY to change as well.
	if (keyStates[GLFW_KEY_A] == 2) {
		positionX--;
	}


	// Create new Particle of Size 15000,15000 to test if it spawns.
	if (keyStates[GLFW_KEY_H] == 1) {
		Particle newparticle;

		newparticle.Init(0, 0, 15000, 15000, 0, 0);
		particleSystem.particles.emplace_back(newparticle);
		//std::cout << "R : " << newparticle.object.color.r << "\nG : " << newparticle.object.color.g << "\nB : " << newparticle.object.color.b << "\n";

	}

	// This allows changing of game states.
#ifdef _DEBUG
	if (keyStates[GLFW_KEY_1] == 1)
		CurrentGameState = STATE_LEVEL_TEST;
#endif

	/*-----------------------------------------------------------------------------
	|                               INPUT UPDATES                                 |
	-----------------------------------------------------------------------------*/
	/*-----------------------------------
	|            ALPHABETS              |
	-----------------------------------*/
	bool controlactivate = ((keyStates[GLFW_KEY_RIGHT_CONTROL] > 0) || (keyStates[GLFW_KEY_LEFT_CONTROL] > 0));
	bool shiftactivate = ((keyStates[GLFW_KEY_RIGHT_SHIFT] > 0) || (keyStates[GLFW_KEY_LEFT_SHIFT] > 0));

	if (controlactivate) {
		if (keyStates[GLFW_KEY_A]) {
#ifdef _DEBUG
			std::cout << "CROUCH LEFT";
#endif
		}

		if (keyStates[GLFW_KEY_D]) {
#ifdef _DEBUG
			std::cout << "CROUCH RIGHT";
#endif
		}

		if (keyStates[GLFW_KEY_S]) {
#ifdef _DEBUG
			std::cout << "CROUCH DOWN";
#endif
		}

		if (keyStates[GLFW_KEY_W]) {
#ifdef _DEBUG
			std::cout << "CROUCH UP";
#endif

		}
	}

	// IF BIG LETTERS

	else if (shiftactivate) {

		if (keyStates[GLFW_KEY_A]) {

#ifdef _DEBUG
			std::cout << "RUN LEFT\n";
#endif
		}

		if (keyStates[GLFW_KEY_D]) {
#ifdef _DEBUG
			std::cout << "RUN RIGHT\n";
#endif
		}

		if (keyStates[GLFW_KEY_S]) {
#ifdef _DEBUG
			std::cout << "RUN DOWN\n";
#endif
		}

		if (keyStates[GLFW_KEY_W]) {
#ifdef _DEBUG
			std::cout << "RUN UP\n";
#endif

		}
	}
	// IF SMALL LETTERS
	else {

		if (keyStates[GLFW_KEY_A]) {
			physicsSys->SetCurrentRotationSpeed(GET_COMPONENT(objectFactory->GetGameObjectByID(0), PhysicsBody, ComponentType::PHYSICS_BODY)->rotationSpeed, 0);
		}

		else if (keyStates[GLFW_KEY_D]) {
			physicsSys->SetCurrentRotationSpeed(-(GET_COMPONENT(objectFactory->GetGameObjectByID(0), PhysicsBody, ComponentType::PHYSICS_BODY)->rotationSpeed), 0);

		}
		else {
			physicsSys->SetCurrentRotationSpeed(0, 0);
		}
		
		if (keyStates[GLFW_KEY_S]) {
			/*PhysicsBody* playerBody = GET_COMPONENT(objectFactory->GetGameObjectByID(0), PhysicsBody, ComponentType::PHYSICS_BODY);
			playerBody->forceManager.SetActive(true, 0);
			playerBody->forceManager.SetDirection(-playerBody->direction, 0);
			//physicsSys->MoveBackwards(0);*/
		}

		else if (keyStates[GLFW_KEY_W]) {
			/*
			PhysicsBody* playerBody = GET_COMPONENT(objectFactory->GetGameObjectByID(0), PhysicsBody, ComponentType::PHYSICS_BODY);
			playerBody->forceManager.SetActive(true, 0);
			playerBody->forceManager.SetDirection(playerBody->direction, 0);
			//physicsSys->MoveForward(0);*/
		}
		else {
			/*
			PhysicsBody* playerBody = GET_COMPONENT(objectFactory->GetGameObjectByID(0), PhysicsBody, ComponentType::PHYSICS_BODY);
			playerBody->forceManager.DeactivateForce(0);*/
		}

		if (keyStates[GLFW_KEY_M]) {

		}

		if (keyStates[GLFW_KEY_R]) {

		}

	}


	/*-----------------------------------
	|             NUMBERS               |
	-----------------------------------*/


	/*-----------------------------------
	|              OTHERS               |
	-----------------------------------*/





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
#ifdef _DEBUG
		std::cout << "SCROLL UP\n";
		std::cout << "Total Scroll Y Offset:" << mouse_scroll_total_Y_offset << "\n";
#endif
	}
	if (mouseScrollState == -1) {
#ifdef _DEBUG
		std::cout << "SCROLL DOWN\n";
		std::cout << "Total Scroll Y Offset:" << mouse_scroll_total_Y_offset << "\n";
#endif
	}

	UpdateStatesForNextFrame();



	//std::cout << GetFPS() << '\n';

	// Draws every second...





	/*---------------------------------------------------------------------------*/
	/*-----------------------------------
	|       Sound Stuff Testing         |
	-----------------------------------*/


	/*-----------------------------------
	|       ImGui Stuff Testing         |
	-----------------------------------*/
	myEditor.Update();

	particleSystem.Update();
	if (angle > 360)
		angle = 0;
	// Set the Background Color.
	OpenGLSetBackgroundColor(0.5f, 0.5f, 0.5f, 1.0f);
	// Clear the Color Buffer Bit to enable 'reloading'
	glClear(GL_COLOR_BUFFER_BIT);
	// Draws the Background
	background.Draw();

	for (OpenGLObject& obj : objects) {
		if (obj.TagID == 1)
			obj.Update(positionX, 300, 100, 100, angle, true);

		// Tag ID 2
		if (obj.TagID == 2) {
			obj.Update(300, 400, 50, 50);
		}
	}

	// Updates the Game Object
	for (std::pair<size_t, GameObject*> gObj : objectFactory->GetGameObjectIDMap()) {
		if (gObj.second->Has(ComponentType::TRANSFORM) != -1) {
			GET_COMPONENT(gObj.second, Transform, ComponentType::TRANSFORM)->shape->Draw();
		}

	}

	myImGui.Draw();
	Draw();
	particleSystem.Draw();

}


/**************************************************************************
* @brief Cleanup the applcation process.
* @param none
* @return void
*************************************************************************/
void OpenGLApplication::OpenGLCleanup() {
	Objects.Cleanup();
	OpenGLSetBackgroundColor(0.0f, 0.0f, 0.0f, 0.0f);

}




/**************************************************************************
* @brief		Draws any thing that the window is required.
*
* @param none
* @return void
*************************************************************************/
void OpenGLApplication::Draw() {

#ifdef _DEBUG
	//	std::cout << "Object Storage Size:" << OpenGLObject::Object_Storage.size() << '\n';


#endif
	// Iterate through all the objects and draw the textures assosiated with Tag ID
	for (auto const& obj : objects) {
		// Draw the Object with Texture.
		obj.Draw();
	}

	// Update the Title and Others EVERY SECOND.
	if (IsTimeElapsed(1)) {
		// setting up the text to be displayed as the window title
		std::stringstream sStr;
		sStr << title.c_str() << " | "
			<< std::fixed << std::setprecision(2)
			<< "FPS:  | " << GetFrames();

		// setting the text as the window title
		glfwSetWindowTitle(windowNew, sStr.str().c_str());
	}

}

/**************************************************************************
* @brief		Sets Background Color, Easier for people to see what it is
*				for compared to glClearColor.
* @param none
* @return void
*************************************************************************/
void OpenGLApplication::OpenGLSetBackgroundColor(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
}

#ifdef _DEBUG

/**************************************************************************
* @brief			Test Changing of States in the Game Engine..
* @warning			OpenGLObjects init lines must be drawn for it to work.
*
* @param none
* @return void
*************************************************************************/
void OpenGLApplication::OpenGLTestChangingStates() {
	// Set Background Color
	OpenGLSetBackgroundColor(0.1f, 0.1f, 0.1f, 1.0f);
	// Clear Color buffer Bit
	glClear(GL_COLOR_BUFFER_BIT);

	// 
	glUseProgram(Objects.ShaderProgram);
	glBindVertexArray(Objects.VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);


	if (keyStates[GLFW_KEY_D]) {
		std::cout << "Changing of Game States back to Original" << '\n';
		std::cout << "Test Over \n";
		CurrentGameState = STATE_GRAPHICS_TEST;
	}



	if (IsTimeElapsed(1))
	{
		Draw();
	}
}

#endif


/**************************************************************************
* @brief			Resize Window Callback
* @param none
* @return void
*************************************************************************/
void OpenGLApplication::OpenGLWindowResizeCallback(GLFWwindow* window2, int width, int height) {
	(void)window2;

	// Update the window dimensions once changed
	// set callback for the window size
	glViewport(0, 0, width, height);
	windowSize.first = width;
	windowSize.second = height;
}