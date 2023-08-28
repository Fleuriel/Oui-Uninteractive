#include <iostream>
#include <MainSetup.h>
#include <InputKeys.h>
#include <keyDefinition.h>




GLFWwindow* window;

GLfloat squareX = 0.0f, squareY = 0.0f;


void OpenGLInit()
{
	if (!glfwInit())
	{
		return;
	}


	std::cout << "Initialization Graphics Pipeline\n";

	window = glfwCreateWindow(1366, 768, "Temporary Test", NULL, NULL);


	glfwSetKeyCallback(window, keyCallBack);


	glfwMakeContextCurrent(window);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);




	if (!window)
	{
		glfwTerminate();
		return;
	}



}

void OpenGLUpdate()
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


void OpenGLCleanup()
{
	glfwTerminate();
}