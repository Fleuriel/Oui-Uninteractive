#include <iostream>
#include <OpenGLApplication.h>
#include <InputKeys.h>
#include <keyDefinition.h>
#include <RandomUtilities.h>
#include <OpenGLObjects.h>
#include <glm/gtc/matrix_transform.hpp>
#include <InitializeEngine.h>



GLFWwindow* window;

GLfloat squareX = 0.0f, squareY = 0.0f;

OpenGLObject Objects;

void OpenGLApplication::OpenGLInit(short width, short height)
{
	// Enable Object Creation
	Objects.Init();


	OpenGLWindowInitialization(window);
	if (!glfwInit())
	{
		return;
	}

	// Print to check if it pass through this line ...
	std::cout << "Initialization Graphics Pipeline\n";

	// Create Windows
	window = glfwCreateWindow(width, height, "Temporary Test", NULL, NULL);

	glViewport(0, 0, width, height);

	// Receives Key input/output [Checks for Key Presses]
	glfwSetKeyCallback(window, keyCallBack);

	// Make the current window the current context
	glfwMakeContextCurrent(window);

	// Set input mode for the window with the cursor (Enables Cursor Input)
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);


	glewInit();

	// Create Vertex Buffers for the primitives (Shapes).
	unsigned int vertexBuffer;
	glGenBuffers(1, &vertexBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), Objects.Triangle.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

	


	if (!window)
	{
		glfwTerminate();

		return;
	}


	// Set up the projection matrix for world coordinates
	float worldWidth = 20.0f;
	float worldHeight = 20.0f * (height / (float)width);
	glm::mat4 projection = glm::ortho(-worldWidth / 2, worldWidth / 2, -worldHeight / 2, worldHeight / 2, -1.0f, 1.0f);

}

void OpenGLApplication::OpenGLUpdate()
{
	while (!glfwWindowShouldClose(window))
	{



		glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_QUADS);

		// This is using NDC coordinates ... Take Note
		//glVertex2f(squareX - 0.1f, squareY + 0.1f);
		//glVertex2f(squareX - 0.1f, squareY - 0.1f);
		//glVertex2f(squareX + 0.1f, squareY - 0.1f);
		//glVertex2f(squareX + 0.1f, squareY + 0.1f);

		glDrawArrays(GL_TRIANGLES, 0, 3);


		//glVertex2f(-5.0f, 5.0f);
		//glVertex2f(-5.0f, -5.0f);
		//glVertex2f(5.0f, -5.0f);
		//glVertex2f(5.0f, 5.0f);

		glEnd();


		glClearColor(0.2f, 0.3f, 0.4f, 1.0f);


		/*-----------------------------------------------------------------------------
		|                               INPUT UPDATES                                 |
		-----------------------------------------------------------------------------*/
		// This is where you change what each key does when pressed.

		/*-----------------------------------
		|            ALPHABETS              |
		-----------------------------------*/
		if (keyStates[KEY_A]) {
			std::cout << "A\n";
			squareX -= 0.0025;
		}

		if (keyStates[KEY_B])
			std::cout << "B\n";

		if (keyStates[KEY_C])
			std::cout << "C\n";

		if (keyStates[KEY_D]) {
			std::cout << "D\n";
			squareX += 0.0025;
		}

		if (keyStates[KEY_E])
			std::cout << "E\n";

		if (keyStates[KEY_F])
			std::cout << "F\n";

		if (keyStates[KEY_G])
			std::cout << "G\n";

		if (keyStates[KEY_H])
			std::cout << "H\n";

		if (keyStates[KEY_I])
			std::cout << "I\n";

		if (keyStates[KEY_J])
			std::cout << "J\n";

		if (keyStates[KEY_K])
			std::cout << "K\n";

		if (keyStates[KEY_L])
			std::cout << "L\n";

		if (keyStates[KEY_M])
			std::cout << "M\n";

		if (keyStates[KEY_N])
			std::cout << "N\n";

		if (keyStates[KEY_O])
			std::cout << "O\n";

		if (keyStates[KEY_P])
			std::cout << "P\n";

		if (keyStates[KEY_Q])
			std::cout << "Q\n";

		if (keyStates[KEY_R])
			std::cout << "R\n";

		if (keyStates[KEY_S]) {
			std::cout << "S\n";
			squareY -= 0.01;
		}

		if (keyStates[KEY_T])
			std::cout << "T\n";

		if (keyStates[KEY_U])
			std::cout << "U\n";

		if (keyStates[KEY_V])
			std::cout << "V\n";

		if (keyStates[KEY_W]) {
			std::cout << "W\n";
			squareY += 0.01;
		}

		if (keyStates[KEY_X])
			std::cout << "X\n";

		if (keyStates[KEY_Y])
			std::cout << "Y\n";

		if (keyStates[KEY_Z])
			std::cout << "Z\n";


		/*-----------------------------------
		|             NUMBERS               |
		-----------------------------------*/
		if (keyStates[KEY_0])
			std::cout << "0\n";
		if (keyStates[KEY_1])
			std::cout << "1\n";
		if (keyStates[KEY_2])
			std::cout << "2\n";
		if (keyStates[KEY_3])
			std::cout << "3\n";
		if (keyStates[KEY_4])
			std::cout << "4\n";
		if (keyStates[KEY_5])
			std::cout << "5\n";
		if (keyStates[KEY_6])
			std::cout << "6\n";
		if (keyStates[KEY_7])
			std::cout << "7\n";
		if (keyStates[KEY_8])
			std::cout << "8\n";
		if (keyStates[KEY_9])
			std::cout << "9\n";


		/*-----------------------------------
		|              OTHERS               |
		-----------------------------------*/
		if (keyStates[KEY_SPACE])
			std::cout << "SPACE\n";
		if (keyStates[KEY_ALT])
			std::cout << "ALT\n";
		if (keyStates[KEY_CTRL])
			std::cout << "CTRL\n";
		if (keyStates[KEY_SHIFT])
			std::cout << "SHIFT\n";
		if (keyStates[KEY_CAPS])
			std::cout << "CAPS\n";
		if (keyStates[KEY_TAB])
			std::cout << "TAB\n";
		if (keyStates[KEY_ESC])
			std::cout << "ESC\n";
		if (keyStates[KEY_ENTER])
			std::cout << "ENTER\n";

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


// Anything that requires Windows
void OpenGLApplication::OpenGLWindowInitialization(GLFWwindow* window)
{

}



void OpenGLApplication::OpenGLObjectsInitialization()
{

}


//void OpenGLApplication::OpenGLShadersInitialization()
//{
//	const char* VertexShader =
//		"#version 330 core\n"
//		"layout (location = 0) in vec2 aPos;\n"
//		"void main()\n"
//		"{\n"
//		"	gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
//		"}\n";
//
//	const char* FragmentShader =
//		"#version 330 core\n"
//		"out vec4 FragColor;\n"
//		"void main()\n"
//		"{\n"
//		"   FragColor = vec4(1.0, 0.5, 0.2, 1.0);\n"
//		"}\0";
//
//
//}