#include <iostream>
#include <OpenGLApplication.h>
#include <InputKeys.h>
#include <keyDefinition.h>
#include <RandomUtilities.h>
#include <OpenGLObjects.h>
#include <glm/gtc/matrix_transform.hpp>
#include <InitializeEngine.h>



GLFWwindow* window;
std::vector<OpenGLShader> OpenGLApplication::Shader{};
OpenGLShader OpenGLApplication::ShaderProgram{};
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

	glViewport(0, 0, width, height);

	// Receives Key input/output [Checks for Key Presses]
	glfwSetKeyCallback(window, keyCallBack);

	// Make the current window the current context
	glfwMakeContextCurrent(window);

	// Set input mode for the window with the cursor (Enables Cursor Input)
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);


	glewInit();

	Objects.Init();
	OpenGLShadersInitialization();

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
		glVertex2f(squareX - 0.1f, squareY + 0.1f);
		glVertex2f(squareX - 0.1f, squareY - 0.1f);
		glVertex2f(squareX + 0.1f, squareY - 0.1f);
		glVertex2f(squareX + 0.1f, squareY + 0.1f);

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
		// IF BIG LETTERS
		if ((keyStates[KEY_SHIFT] && !keyStates[KEY_CAPS]) + (!keyStates[KEY_SHIFT] && keyStates[KEY_CAPS])) {

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

			if (keyStates[KEY_X]) {
				std::cout << "X\n";
				en = false;
			}

			if (keyStates[KEY_Y])
				std::cout << "Y\n";

			if (keyStates[KEY_Z]) {
				std::cout << "Z\n";
				render_square(glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 0.0f));
			}
		}

		// IF SMALL LETTERS
		else {

			if (keyStates[KEY_A]) {
				std::cout << "a\n";
				squareX -= 0.0025;
			}

			if (keyStates[KEY_B])
				std::cout << "b\n";

			if (keyStates[KEY_C])
				std::cout << "c\n";

			if (keyStates[KEY_D]) {
				std::cout << "d\n";
				squareX += 0.0025;
			}

			if (keyStates[KEY_E])
				std::cout << "e\n";

			if (keyStates[KEY_F])
				std::cout << "f\n";

			if (keyStates[KEY_G])
				std::cout << "g\n";

			if (keyStates[KEY_H])
				std::cout << "h\n";

			if (keyStates[KEY_I])
				std::cout << "i\n";

			if (keyStates[KEY_J])
				std::cout << "j\n";

			if (keyStates[KEY_K])
				std::cout << "k\n";

			if (keyStates[KEY_L])
				std::cout << "l\n";

			if (keyStates[KEY_M])
				std::cout << "m\n";

			if (keyStates[KEY_N])
				std::cout << "n\n";

			if (keyStates[KEY_O])
				std::cout << "o\n";

			if (keyStates[KEY_P])
				std::cout << "p\n";

			if (keyStates[KEY_Q])
				std::cout << "q\n";

			if (keyStates[KEY_R])
				std::cout << "r\n";

			if (keyStates[KEY_S]) {
				std::cout << "s\n";
				squareY -= 0.01;
			}

			if (keyStates[KEY_T])
				std::cout << "t\n";

			if (keyStates[KEY_U])
				std::cout << "u\n";

			if (keyStates[KEY_V])
				std::cout << "v\n";

			if (keyStates[KEY_W]) {
				std::cout << "w\n";
				squareY += 0.01;
			}

			if (keyStates[KEY_X]) {
				std::cout << "x\n";
				en = false;
			}

			if (keyStates[KEY_Y])
				std::cout << "y\n";

			if (keyStates[KEY_Z]) {
				std::cout << "z\n";
				render_square(glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 0.0f));
			}
		}

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
	ShaderProgram.DeleteShaderProgram();



	glfwTerminate();
}


void OpenGLApplication::render_square(glm::vec2 scaling, glm::vec2 position)
{
	glm::mat4 Model_to_NDC_Transform = glm::mat4(1.0f);


	Model_to_NDC_Transform = glm::translate(Model_to_NDC_Transform, glm::vec3(position.x, position.y, 0.0f)); // Corrected translation
	Model_to_NDC_Transform = glm::scale(Model_to_NDC_Transform, glm::vec3(scaling.x, scaling.y, 1.0f)); // Corrected scaling


	ShaderProgram.Use();
	ShaderProgram.SetUniform("vColor", Objects.Color); // Using (255, 255, 120) as RGB values
	ShaderProgram.SetUniform("uModel", Model_to_NDC_Transform);


	glBindVertexArray(Object_Storage["Square"].vaoID); // Replace with the actual VAO name for the square
	std::cout << Object_Storage["Triangle"].vaoID << "VAOID\n";
	


	glDrawArrays(GL_TRIANGLES, 0, 4);



	// Unbind the Vertex Array
	glBindVertexArray(0);



}



void OpenGLApplication::Draw() {

	glBindVertexArray(Objects.vaoID);

	ShaderProgram.Use();

	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, nullptr);

	glBindVertexArray(0);

}



void OpenGLApplication::OpenGLObjectsInitialization()
{

}


void OpenGLApplication::OpenGLShadersInitialization()
{

	std::cout << "Shaders Initialized\n";
	OpenGLApplication::VectorPairStrStr ShaderCodex;

	std::vector<std::pair<GLenum, std::string>> ShaderFiles;

	std::string vert{}, frag{};

	vert =

		R"(
		#version 450 core

		layout(location = 0) in vec2 aVertexPosition;
		layout(location = 1) in vec3 aVertexColor;

		out vec3 vColor;

		uniform mat4 uModel;

		void main()
		{
			gl_Position = uModel * vec4(aVertexPosition, 0.0, 1.0);
			vColor = aVertexColor;
		}
	)";

	frag =

		R"(
		#version 450 core

		in vec3 vColor;
		
		out vec4 fFragColor;
		
		uniform vec3 uBaseColor; // Uniform variable for the base color
		
		void main()
		{
		    fFragColor = vec4(uBaseColor * vColor, 1.0);
		}
	)";

	// Adding vertex shader ...
	ShaderFiles.emplace_back(std::make_pair(GL_VERTEX_SHADER, vert));

	// Adding fragment shader ...
	ShaderFiles.emplace_back(std::make_pair(GL_FRAGMENT_SHADER, frag));

	ShaderProgram.CompileLinkValidate(ShaderFiles);



	std::cout << ShaderFiles[0].second << '\n';
	std::cout << ShaderFiles[1].second << '\n';



	for (std::pair<GLenum, std::string> x : ShaderFiles)
	{
		if (!ShaderProgram.CompileShaderFromString(x.first, x.second))
		{
			std::cout << "Unable to compile shader programs from string" << "\n";
			std::cout << ShaderProgram.GetLog() << std::endl;
			std::exit(EXIT_FAILURE);
		}
	}
	if (!ShaderProgram.Link())
	{
		std::cout << "Unable to link shader programs" << "\n";
		std::cout << ShaderProgram.GetLog() << std::endl;
		std::exit(EXIT_FAILURE);
	}

	if (!ShaderProgram.Validate())
	{
		std::cout << "Unable to validate shader programs" << "\n";
		std::cout << ShaderProgram.GetLog() << std::endl;
		std::exit(EXIT_FAILURE);
	}

	//shdr_pgm.Link(shdr_files);
	if (GL_FALSE == ShaderProgram.IsLinked())
	{
		std::cout << "Unable to compile/link/validate shader programs" << "\n";
		std::cout << ShaderProgram.GetLog() << std::endl;
		std::exit(EXIT_FAILURE);
	}



}
