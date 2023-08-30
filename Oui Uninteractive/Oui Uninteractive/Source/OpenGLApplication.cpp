#include <iostream>
#include <OpenGLApplication.h>
#include <InputKeys.h>
#include <keyDefinition.h>
#include <RandomUtilities.h>
#include <OpenGLObjects.h>
#include <glm/gtc/matrix_transform.hpp>



GLFWwindow* window;

GLfloat squareX = 0.0f, squareY = 0.0f;

//OpenGLObject Objects;

void OpenGLApplication::OpenGLInit(short width, short height)
{
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



	// Create Vertex Buffers for the primitives (Shapes).
	//unsigned int vertexBuffer;
	//glGenBuffers(1, &vertexBuffer);
	//glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	//glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), Objects.Triangle.data(), GL_STATIC_DRAW);


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
		glVertex2f(squareX - 0.1f, squareY + 0.1f);
		glVertex2f(squareX - 0.1f, squareY - 0.1f);
		glVertex2f(squareX + 0.1f, squareY - 0.1f);
		glVertex2f(squareX + 0.1f, squareY + 0.1f);



		//glVertex2f(-5.0f, 5.0f);
		//glVertex2f(-5.0f, -5.0f);
		//glVertex2f(5.0f, -5.0f);
		//glVertex2f(5.0f, 5.0f);

		glEnd();


		glClearColor(0.2f, 0.3f, 0.4f, 1.0f);



		if (keyStatesAlphabet[KEY_A])
		{
			squareX -= 0.0025;
		}

		if (keyStatesAlphabet[KEY_D])
		{
			squareX += 0.0025;
		}

		if (keyStatesAlphabet[KEY_W])
		{
			squareY += 0.01;
		}
		if (keyStatesAlphabet[KEY_S])
		{
			squareY -= 0.01;
		}



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