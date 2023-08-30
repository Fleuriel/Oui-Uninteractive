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


		if (keyStatesAlphabet[KEY_Z])
		{
			render_square(glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 0.0f));

		}
		if (keyStatesAlphabet[KEY_X])
		{
			en = false;
		}
		
		


		if (en == false)
		{

		}


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
	ShaderProgram.DeleteShaderProgram();



	glfwTerminate();
}


void OpenGLApplication::render_square(glm::vec2 scaling, glm::vec2 position)
{
	glm::mat4 modelMatrix = glm::mat4(1.0f);


	modelMatrix = glm::translate(modelMatrix, glm::vec3(position.x, position.y, 0.0f)); // Corrected translation
	modelMatrix = glm::scale(modelMatrix, glm::vec3(scaling.x, scaling.y, 1.0f)); // Corrected scaling


	ShaderProgram.Use();
	//ShaderProgram.SetUniform("uModel", modelMatrix);
	ShaderProgram.SetUniform("vColor", glm::vec3(0.0f, 1.0f, 0.47f)); // Using (255, 255, 120) as RGB values


	glBindVertexArray(Object_Storage["Square"].vaoID); // Replace with the actual VAO name for the square


	glDrawArrays(GL_TRIANGLES, 0, 4);

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
