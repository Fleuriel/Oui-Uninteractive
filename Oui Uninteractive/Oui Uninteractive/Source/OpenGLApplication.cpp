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
#include <OpenGLObjects.h>
#include <glm/gtc/matrix_transform.hpp>
#include <GameStateManager.h>
#include <Editor.h>
#include <Mapping.h>
#include "ObjectFactory.h"
#include "Physics.h"
#include <Global.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
GLFWwindow* window;

UsingImGui myImGui; // Creating imGui object
Editor myEditor; // Creating editor object

GLfloat squareX = 0.0f, squareY = 0.0f;

OpenGLObject Objects;

bool en = true;
bool toggleMode = true;

// For Input
extern float mouse_scroll_total_Y_offset;
extern int lastkeyedcommand;

std::string title = "Hello";


static bool glewInitialized = false;
static bool imguiInitialized = false;

void OpenGLApplication::OpenGLWindowInit()
{
	// Read window size from JSON
	std::string filePath = "../window-data/window-data.JSON";
	rapidjson::Document windowDoc;
	// Initialize window dimensions from JSON
	unsigned short width, height;
	if (Editor::ReadJSONFile(filePath, windowDoc)) {
		width = windowDoc["windowX"].GetInt();
		height = windowDoc["windowY"].GetInt();
	}
	window = glfwCreateWindow(width, height, "hello", NULL, NULL);
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


	glViewport(0, 0, width, height);

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

	

}



void OpenGLApplication::OpenGLWindowCleanup()
{
	// Get window dimensions
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	// Save window size
	std::string filePath = "../window-data/window-data.JSON";
	rapidjson::Document windowDoc;
	if (Editor::ReadJSONFile(filePath, windowDoc)) {
		windowDoc["windowX"] = width;
		windowDoc["windowY"] = height;
		Editor::WriteJSONFile(filePath, windowDoc);
	}

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
	objectFactory->BuildObjectRunTime();
	objectFactory->AddComponent(ComponentType::PhysicsBody, objectFactory->GetGameObjectByID(0));
	objectFactory->AddComponent(ComponentType::Transform, objectFactory->GetGameObjectByID(0));
	objectFactory->GetGameObjectByID(0)->Initialize();

	objectFactory->CloneObject(0);
	//init object from file
	//objectFactory->BuildObjectFromFile("test.json");

}


void OpenGLApplication::OpenGLUpdate()
{


		OpenGLSetBackgroundColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glUseProgram(Objects.ShaderProgram);
		glBindVertexArray(Objects.VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
				

		// create transformations
		glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		//transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
		transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));



		unsigned int transformLoc = glGetUniformLocation(OpenGLObject::ShaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));


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
				std::cout << "WALK LEFT\n";
				CurrentGameState = STATE_LEVEL_TEST;
			}

			if (keyStates[GLFW_KEY_D]) {
				std::cout << "WALK RIGHT\n";
				CurrentGameState = STATE_GRAPHICS_TEST;
			}

			if (keyStates[GLFW_KEY_S]) {
				std::cout << "WALK DOWN\n";
			}

			if (keyStates[GLFW_KEY_W]) {
				physicsSys->setVelocity(Vec2(0.0f, 10.f), 0);
				std::cout << "WALK UP\n";
			}
			else {
				physicsSys->setVelocity(Vec2(0.0f, 0.0f), 0);
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
		|       ImGui Stuff Testing         |
		-----------------------------------*/
		myImGui.CreateFrame();
		myImGui.Update();
		myImGui.Draw();

		// Swap the front and back buffers
	


}


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