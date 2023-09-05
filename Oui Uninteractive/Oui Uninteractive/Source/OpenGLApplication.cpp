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
#include <InitializeEngine.h>



GLFWwindow* window;
std::map<std::string, OpenGLObject> OpenGLApplication::Object_Storage;


GLfloat squareX = 0.0f, squareY = 0.0f;

OpenGLObject Objects;

bool en = true;

// For Input
extern float mouse_scroll_total_Y_offset;
extern int lastkeyedcommand;


void OpenGLApplication::OpenGLInit(short width, short height)
{
	// Enable Object Creation


	if (!glfwInit())
	{
		return;
	}

	// Print to check if it pass through this line ...
	std::cout << "Initialization Graphics Pipeline\n";

	// Create Windows
	window = glfwCreateWindow(width, height, "Temporary Test", NULL, NULL);

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


	glewInit();

	Objects.Init();

	// Create Vertex Buffers for the primitives (Shapes).
	//unsigned int vertexBuffer;
	//glGenBuffers(1, &vertexBuffer);
	//
	//glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	//glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), Objects.Triangle.data(), GL_STATIC_DRAW);
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

	


	if (!window)
	{
		glfwTerminate();

		return;
	}


	// Set up the projection matrix for world coordinates
	//float worldWidth = 20.0f;
	//float worldHeight = 20.0f * (height / (float)width);
	//glm::mat4 projection = glm::ortho(-worldWidth / 2, worldWidth / 2, -worldHeight / 2, worldHeight / 2, -1.0f, 1.0f);

}

void OpenGLApplication::OpenGLUpdate()
{

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
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


		glClearColor(0.2f, 0.3f, 0.4f, 1.0f);


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
			}

			if (InputStates[INPUT_D]) {
				std::cout << "WALK RIGHT\n";
			}

			if (InputStates[INPUT_S]) {
				std::cout << "WALK DOWN\n";
			}

			if (InputStates[INPUT_W]) {
				std::cout << "WALK UP\n";
			}

		}

		/*-----------------------------------
		|             NUMBERS               |
		-----------------------------------*/
		if (InputStates[INPUT_0])
			std::cout << "0\n";
		if (InputStates[INPUT_1])
		{
			std::cout << Object_Storage.size() << '\n';
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

		/*---------------------------------------------------------------------------*/


		// swap the front and back buffers ....
		glfwSwapBuffers(window);
		glfwPollEvents();

	}


}


void OpenGLApplication::OpenGLCleanup()
{



	glfwTerminate();
}





void OpenGLApplication::Draw() {


	for (auto& x : Object_Storage)
	{
		std::cout << x.first << '\n';
		x.second.Draw();
	}


}



void OpenGLApplication::OpenGLObjectsInitialization()
{

}

