#include <GLFW/glfw3.h>
#include <OpenGLObjects.h>
#include <GL/GL.h>
#include <GL/glew.h> // for access to OpenGL API declarations 
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

void OpenGLObject::CreateObject()
{
	CreateVertices();
	CreateIndices();

}

void OpenGLObject::CreateVertices()
{

}

void OpenGLObject::CreateIndices()
{

}


void OpenGLObject::SetupVertexBufferArrays()
{
	float vertices[] = {
	   -0.1f,  0.1f,  // Top left
	   -0.1f, -0.1f,  // Bottom left
		0.1f, -0.1f,  // Bottom right
		0.1f,  0.1f   // Top right
	};
	unsigned int indices[] = {
		0, 1, 2,   // First triangle
		0, 2, 3    // Second triangle
	};

	unsigned int VBO, EBO;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);



}
void OpenGLObject::SetupShader()
{
	//const char* VertexShader =
	//	"#version 330 core\n"
	//	"layout (location = 0) in vec2 aPos;\n"
	//	"void main()\n"
	//	"{\n"
	//	"	gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
	//	"}\n";

	//const char* FragmentShader = 
	//	"#version 330 core\n"
	//	"out vec4 FragColor;\n"
	//	"void main()\n"
	//	"{\n"
	//	"   FragColor = vec4(1.0, 0.5, 0.2, 1.0);\n"
	//	"}\0";

	//glUseProgram(shaderProgram);
	//glBindVertexArray(VAO);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//glBindVertexArray(0);

}