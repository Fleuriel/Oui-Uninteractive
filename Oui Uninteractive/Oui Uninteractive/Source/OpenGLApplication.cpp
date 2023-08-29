#include <iostream>
#include <OpenGLApplication.h>
#include <InputKeys.h>
#include <keyDefinition.h>
#include <RandomUtilities.h>
#include <OpenGLObjects.h>



GLFWwindow* window;

GLfloat squareX = 0.0f, squareY = 0.0f;


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


	// Receives Key input/output [Checks for Key Presses]
	glfwSetKeyCallback(window, keyCallBack);

	// Make the current window the current context
	glfwMakeContextCurrent(window);

	// Set input mode for the window with the cursor (Enables Cursor Input)
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);



	if (!window)
	{
		glfwTerminate();
		return;
	}
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