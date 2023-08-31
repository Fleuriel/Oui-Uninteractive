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

	//glfwSetMouseButtonCallback(window, mouseCallBack);

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
	float tmpspeed{ 0.04 };
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glUseProgram(Objects.ShaderProgram);
		glBindVertexArray(Objects.VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);


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

		if (keyStates[KEY_CTRL]) {
			if (keyStates[KEY_A]) {
				squareX -= tmpspeed / 4;
			}

			if (keyStates[KEY_D]) {
				squareX += tmpspeed / 4;
			}

			if (keyStates[KEY_S]) {
				squareY -= tmpspeed / 4;
			}

			if (keyStates[KEY_W]) {
				squareY += tmpspeed / 4;
			}
		}
		else
		// IF BIG LETTERS
		if ((keyStates[KEY_SHIFT] && !keyStates[KEY_CAPS]) + (!keyStates[KEY_SHIFT] && keyStates[KEY_CAPS])) {

			if (keyStates[KEY_A]) {
				squareX -= tmpspeed/2;
			}

			if (keyStates[KEY_D]) {
				squareX += tmpspeed/2;
			}

			if (keyStates[KEY_S]) {
				squareY -= tmpspeed/2;
			}

			if (keyStates[KEY_W]) {
				squareY += tmpspeed/2;
			}

		}

		// IF SMALL LETTERS
		else {

			if (keyStates[KEY_A]) {
				std::cout << "a\n";
				squareX -= tmpspeed;
			}

			if (keyStates[KEY_D]) {
				std::cout << "d\n";
				squareX += tmpspeed;
			}

			if (keyStates[KEY_S]) {
				std::cout << "s\n";
				squareY -= tmpspeed;
			}

			if (keyStates[KEY_W]) {
				std::cout << "w\n";
				squareY += tmpspeed;
			}

		}

		/*-----------------------------------
		|             NUMBERS               |
		-----------------------------------*/
		if (keyStates[KEY_0])
			std::cout << "0\n";
		if (keyStates[KEY_1])
		{
			std::cout << Object_Storage.size() << '\n';
			//std::cout << "1\n";
		}
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
		{

			std::cout << "9\n";
		}

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

		/*-----------------------------------
		|             COMMANDS              |
		-----------------------------------*/

		if (keyStates[KEY_COPY])
			std::cout << "COPY\n";

		if (keyStates[KEY_PASTE])
			std::cout << "PASTE\n";

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

