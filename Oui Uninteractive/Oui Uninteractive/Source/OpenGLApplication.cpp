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
#include <InputKeys.h>
#include <keyDefinition.h>
#include <RandomUtilities.h>
#include <OpenGLObjects.h>
#include <glm/gtc/matrix_transform.hpp>
#include <GameStateManager.h>
#include <Editor.h>
#include <string>
#include <Mapping.h>

GLFWwindow* window;

UsingImGui myImGui; // Creating imGui object
Editor myEditor; // Creating editor object

GLfloat squareX = 0.0f, squareY = 0.0f;

OpenGLObject Objects;

bool en = true;

// For Input
extern float mouse_scroll_total_Y_offset;
extern int lastkeyedcommand;

std::string title = "Hello";


static bool glewInitialized = false;
static bool imguiInitialized = false;

void OpenGLApplication::OpenGLWindowInit(unsigned short width, unsigned short height)
{
	std::cout << "First\n";
	window = glfwCreateWindow(width, height, "hello", NULL, NULL);
	if (!window)
	{
		glfwTerminate();

		std::cout << "Problem\n";
		return;
	}
	std::cout << "second\n";

	// Tell GLFW we are using OpenGL 4.5
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);


	// Tell GLFW that we are using the CORE Profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	glViewport(0, 0, width, height);

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

}


void OpenGLApplication::OpenGLUpdate()
{


		OpenGLSetBackgroundColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(Objects.ShaderProgram);
		glBindVertexArray(Objects.VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

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

		if (InputStates[INPUT_CTRL]) {
			if (InputStates[INPUT_A]) {
				std::cout << "CROUCH LEFT";
			}

			if (InputStates[INPUT_D]) {
				std::cout << "CROUCH RIGHT";
			}

			if (InputStates[INPUT_S]) {
				std::cout << "CROUCH DOWN";
			}

			if (InputStates[INPUT_W]) {
				std::cout << "CROUCH UP";
			}
		}
		else

		// IF BIG LETTERS
		if ((InputStates[INPUT_SHIFT] && !InputStates[INPUT_CAPS]) + (!InputStates[INPUT_SHIFT] && InputStates[INPUT_CAPS])) {

			if (InputStates[INPUT_A]) {
				std::cout << "RUN LEFT\n";
			}

			if (InputStates[INPUT_D]) {
				std::cout << "RUN RIGHT\n";
			}

			if (InputStates[INPUT_S]) {
				std::cout << "RUN DOWN\n";
			}

			if (InputStates[INPUT_W]) {
				std::cout << "RUN UP\n";
			}


		}

		// IF SMALL LETTERS
		else {

			if (InputStates[INPUT_A]) {
				std::cout << "WALK LEFT\n";
				CurrentGameState = STATE_LEVEL_TEST;
			}

			if (InputStates[INPUT_D]) {
				std::cout << "WALK RIGHT\n";
				CurrentGameState = STATE_GRAPHICS_TEST;
			}

			if (InputStates[INPUT_S]) {
				std::cout << "WALK DOWN\n";
			}

			if (InputStates[INPUT_W]) {
				std::cout << "WALK UP\n";
			}

			if (InputStates[INPUT_M]) {
				Mapping map;
				map.rows = 4;
				map.columns = 5;
				map.entitymap = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20 };
				map.filename = "hi";
				Mapping::MapBuilder(map);
			}

			if (InputStates[INPUT_R]) {
				Mapping map;
				map.filename = "hi";
				Mapping::MapReader(map);
			}

		}

		/*-----------------------------------
		|             NUMBERS               |
		-----------------------------------*/
		if (InputStates[INPUT_0])
			std::cout << "0\n";
		if (InputStates[INPUT_1])
		{
			std::cout << OpenGLObject::Object_Storage.size() << '\n';
			//std::cout << "1\n";
		}
		if (InputStates[INPUT_2])
			std::cout << "2\n";
		if (InputStates[INPUT_3])
			std::cout << "3\n";
		if (InputStates[INPUT_4])
			std::cout << "4\n";
		if (InputStates[INPUT_5])
			std::cout << "5\n";
		if (InputStates[INPUT_6])
			std::cout << "6\n";
		if (InputStates[INPUT_7])
			std::cout << "7\n";
		if (InputStates[INPUT_8])
			std::cout << "8\n";
		if (InputStates[INPUT_9])
			std::cout << "9\n";

		/*-----------------------------------
		|              OTHERS               |
		-----------------------------------*/
		if (InputStates[INPUT_SPACE])
			std::cout << "SPACE\n";
		if (InputStates[INPUT_ALT])
			std::cout << "ALT\n";
		if (InputStates[INPUT_CTRL])
			std::cout << "CTRL\n";
		if (InputStates[INPUT_SHIFT])
			std::cout << "SHIFT\n";
		if (InputStates[INPUT_CAPS])
			std::cout << "CAPS\n";
		if (InputStates[INPUT_TAB])
			std::cout << "TAB\n";
		if (InputStates[INPUT_ESC])
			std::cout << "ESC\n";
		if (InputStates[INPUT_ENTER])
			std::cout << "ENTER\n";

		/*-----------------------------------
		|             COMMANDS              |
		-----------------------------------*/

		if (InputStates[INPUT_COPY])
			std::cout << "COPY\n";

		//requires timer
		if (InputStates[INPUT_PASTE] && lastkeyedcommand == INPUT_PASTE)
			std::cout << "PASTE\n";
		if (InputStates[INPUT_CUT] && lastkeyedcommand == INPUT_CUT)
			std::cout << "CUT\n";
		if (InputStates[INPUT_UNDO] && lastkeyedcommand == INPUT_UNDO)
			std::cout << "UNDO\n";

		/*-----------------------------------
		|              Mouse                |
		-----------------------------------*/

		if (InputStates[INPUT_LCLICK])
			std::cout << "LCLICK\n";
		if (InputStates[INPUT_RCLICK])
			std::cout << "RCLICK\n";

		/*-----------------------------------
		|              Scroll               |
		-----------------------------------*/

		if (InputStates[INPUT_SCROLLUP]) {
			std::cout << "SCROLL UP\n";
			std::cout << "Total Scroll Y Offset:" << mouse_scroll_total_Y_offset << "\n";
		}
		if (InputStates[INPUT_SCROLLDOWN]) {
			std::cout << "SCROLL DOWN\n";
			std::cout << "Total Scroll Y Offset:" << mouse_scroll_total_Y_offset << "\n";
		}


		InputStates[INPUT_SCROLLUP] = false;		// DO NOT TOUCH
		InputStates[INPUT_SCROLLDOWN] = false;		// DO NOT TOUCH

		
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

	std::cout << OpenGLObject::Object_Storage.size();

	// update object transforms
	for (auto& x : OpenGLObject::Object_Storage)
	{
		if (x.first == "Camera")
			continue;

		std::cout << x.first << '\n';
		std::cout << "YES\n";
		x.second.Draw();
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



void OpenGLApplication::OpenGLObjectsInitialization()
{

}





void OpenGLApplication::OpenGLTestChangingStates()
{
	OpenGLSetBackgroundColor(1.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(Objects.ShaderProgram);
	glBindVertexArray(Objects.VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);


	if (InputStates[INPUT_D]) {
		std::cout << "WALK RIGHT\n";
		CurrentGameState = STATE_GRAPHICS_TEST;
	}



	if (IsTimeElapsed(1))
	{
		Draw();
	}
}