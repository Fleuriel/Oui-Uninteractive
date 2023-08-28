#include <iostream>
#include <GLFW/glfw3.h>

int main()
{


	std::cout << "Hello world\n";


	glfwInit();


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);


	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Program", NULL, NULL);
	if (window == NULL)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);


	float vertices[] = {
		-0.5f,  -0.5f, 0.0f,
		 0.0f,   0.5f, 0.0f,
		 0.5f, -0.05f, 0.0f
	};




	while (!glfwWindowShouldClose(window))
	{

		glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();





	}


	//Terminate
	glfwTerminate();

	return 0;
}