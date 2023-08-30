
#include <GL/glew.h> // for access to OpenGL API declarations  (PUT THIS ON TOP OR ELSE HAVE ERROR)
#include <GLFW/glfw3.h>
#include <OpenGLObjects.h>
#include <glm/glm.hpp>
#include <OpenGLApplication.h>
#include <iostream>
#include <array>
#include <sstream>
#include <fstream>
#include <filesystem>

std::vector<glm::vec2> OpenGLObject::Square;
std::vector<glm::vec2> OpenGLObject::Triangle;
std::vector<std::string> OpenGLObject::Mesh_Directory;

std::map<std::string, OpenGLObject::OpenGLModel> OpenGLObject::Model_Storage;

GLuint OpenGLObject::vaoID;									// how many indices in element buffer
GLuint OpenGLObject::pboID;									// id for PBO
GLuint OpenGLObject::textureID;								// id for texture object

// set up initial state
void OpenGLObject::Init()
{


	Load_Files();
	Load_Meshes();

	std::cout << "Hello'\t" << Mesh_Directory[0] << '\n';
	std::cout << "Hello'\t" << Mesh_Directory[1] << '\n';
	std::cout << "Hello'\t" << Mesh_Directory[2] << '\n';

	Setup_Quad_VAO();
}

void OpenGLObject::Setup_Quad_VAO()
{
	//Define vertex position and color attributes
	std::vector<VAO_Object> vao_value;
	vao_value.reserve(4);

	VAO_Object setup_var;

	//top left
	setup_var.SetValue(-1.0f, 1.0f);
	setup_var.SetTexture(0.f, 1.f);
	vao_value.emplace_back(setup_var);

	//bottom left
	setup_var.SetValue(-1.0f, -1.0f);
	setup_var.SetTexture(0.f, 0.f);
	vao_value.emplace_back(setup_var);

	//bottom right
	setup_var.SetValue(1.0f, 1.0f);
	setup_var.SetTexture(1.f, 1.f);
	vao_value.emplace_back(setup_var);

	//top right
	setup_var.SetValue(1.0f, -1.0f);
	setup_var.SetTexture(1.f, 0.f);
	vao_value.emplace_back(setup_var);

	// transfer vertex position and color attributes to VBO
	GLuint VBO_Handler;
	glCreateBuffers(1, &VBO_Handler);

	glNamedBufferStorage(VBO_Handler, sizeof(VAO_Object) * vao_value.size(), vao_value.data(), GL_DYNAMIC_STORAGE_BIT);

	//encapsulate information about contents of VBO and VBO handle
	// to another object called VAO
	glCreateVertexArrays(1, &vaoID);

	//enable use of vertex position
	glEnableVertexArrayAttrib(vaoID, 0);

	//vertex buffer binding point 3
	glVertexArrayVertexBuffer(vaoID, 3, VBO_Handler, 0, sizeof(VAO_Object)/*number of spaces each iteration*/);

	//position
	//for vertex position array, we use vertex attribute index 0
	//and vertex buffer binding point 3
	//offsetof (offset based on on data type, and member variable, offset will be automatically calculated)
	glVertexArrayAttribFormat(vaoID, 0, 2/*size of data*/, GL_FLOAT, GL_FALSE, offsetof(VAO_Object/*structure type*/, VAO_Object::Position/*value name*/));
	glVertexArrayAttribBinding(vaoID, 0, 3);

	//enable use of texture vertex
	glEnableVertexArrayAttrib(vaoID, 2);

	// for vertex color array, we use vertex attribute index 1
	// and vertex buffer binding point 3
	glVertexArrayAttribFormat(vaoID, 2, 2/*size of data*/, GL_FLOAT, GL_FALSE, offsetof(VAO_Object/*structure type*/, VAO_Object::Texture/*value name*/));
	glVertexArrayAttribBinding(vaoID, 2, 3);

	std::array<GLushort, 4> Indices_Vertex
	{
		0, 1, 2, 3
	};

	GLuint EBO_Handler;
	glCreateBuffers(1, &EBO_Handler);
	glNamedBufferStorage(EBO_Handler, sizeof(GLushort) * Indices_Vertex.size(), reinterpret_cast<GLvoid*>(Indices_Vertex.data()), GL_DYNAMIC_STORAGE_BIT);
	glVertexArrayElementBuffer(vaoID, EBO_Handler);
	glBindVertexArray(0);



}
void OpenGLObject::Load_Files()
{
	std::string directoryPath = "../meshes";

	for(auto const& entry : std::filesystem::directory_iterator(directoryPath))
	{
		if (entry.is_regular_file())
		{
			std::string meshFileName = entry.path().filename().string();
			if (meshFileName.ends_with(".msh"))
			{
				std::ifstream inputFileStream(entry.path(), std::ios::in);
				if (inputFileStream.is_open())
				{
					std::cout << "Reading " << meshFileName << "\n";


					inputFileStream.close();

					
					Mesh_Directory.push_back(entry.path().string());
				}
				else
				{
					std::cerr << "Error Opening File: " << meshFileName << '\n';
				}
			}
		}
	}
}

void OpenGLObject::Load_Meshes() {


	std::vector<glm::vec2> Position_Vertex{};
	std::vector <GLushort> Indices_Vertex{};
	OpenGLObject::OpenGLModel Model;
	std::string Mesh_Name{};

	
	for (int i = 0; i < Mesh_Directory.size(); i++)
	{
		std::ifstream inputFileStream{ Mesh_Directory[i], std::ios::in };			// Input file...

		if (inputFileStream.fail())											// Check if file exist ...
		{
			std::cout << "Loading " << Mesh_Name << "failed. \n";
			return;
		}

		inputFileStream.seekg(0, std::ios::beg);							// Initialize the file to the start ...

		std::string line;													// Create container for line ...

		while (!inputFileStream.eof())
		{
			getline(inputFileStream, line);									// Read the line it is on ...

			std::istringstream line_sStream{ line };						// String Stream

			char prefix;													// Create container for prefix [1]

			line_sStream >> prefix;											// [1]

			switch (prefix)
			{
			case 'n':														// [1] 
			{
				line_sStream >> Mesh_Name;									// Mesh name separated from prefix
				break;
			}
			case 'v':														// [2] v
			{
				glm::vec2 vert_Position{};									// [2] Vertex Position Contianer

				line_sStream >> vert_Position.x;							// Assign values of Vertex Position into Container x
				line_sStream >> vert_Position.y;							// Assign values of Vertex Position into Container y

				Position_Vertex.emplace_back(vert_Position);						// Emplace back the vertex position into the position_vertex container
				break;
			}
			case 't':														// [2] t
			{
				Model.primitive_type = GL_TRIANGLES;							// [t] = GL_TRIANGLE_FAN ...							

				while (line_sStream)										// while line_sStream is not 0 ...
				{
					GLushort index;											// Create container for index ...

					line_sStream >> index;									// Assign index into line_sStream

					if (!line_sStream.fail())								// if line_sStream fails, then do nothing
					{														// else
						Indices_Vertex.push_back(index);							// pushback the index
					}
				}
				break;
			}
			case 'f':														// [2] f
			{
				Model.primitive_type = GL_TRIANGLE_FAN;						// [f] = GL_TRIANGLE_FAN ...

				while (line_sStream)										// while line_sStream is not 0 ...								
				{
					GLushort index;											// Create container for index ...

					line_sStream >> index;									// Assign index into line_sStream


					if (!line_sStream.fail())							    // if line_sStream fails, then do nothing
					{													    // else
						Indices_Vertex.push_back(index);						    // pushback the index
					}
				}
				break;
			}
			default:
				break;
			}
		}

		inputFileStream.close();														// Close the file stream


		GLuint VBO_Handler{};
		glCreateBuffers(1, &VBO_Handler);
		glNamedBufferStorage(VBO_Handler, sizeof(glm::vec2) * Position_Vertex.size(), Position_Vertex.data(), GL_DYNAMIC_STORAGE_BIT);

		glCreateVertexArrays(1, &vaoID);

		//Vertex
		glEnableVertexArrayAttrib(vaoID, 0); //Assigning Vertex array object with index 0 (for position)
		glVertexArrayVertexBuffer(vaoID, 2, VBO_Handler, 0, sizeof(glm::vec2)); //bind the named buffer to vertex buffer binding point 2
		glVertexArrayAttribFormat(vaoID, 0, 2, GL_FLOAT, GL_FALSE, 0); //format vao attribute
		glVertexArrayAttribBinding(vaoID, 0, 2); //binding vao attribute to binding point 2

		GLuint EBO_Handler;
		glCreateBuffers(1, &EBO_Handler); //Creating ebo buffer
		glNamedBufferStorage(EBO_Handler, sizeof(GLushort) * Indices_Vertex.size(), reinterpret_cast<GLvoid*>(Indices_Vertex.data()), GL_DYNAMIC_STORAGE_BIT); //setting memory location for ebo buffer
		glVertexArrayElementBuffer(vaoID, EBO_Handler); //binding ebo to vaoid


		glBindVertexArray(0);

		Model.vaoid = vaoID;


		Model_Storage[Mesh_Name] = Model;
	}
	
}



void OpenGLObject::Draw()
{



}
void OpenGLObject::Update(GLdouble delta_time)
{
	std::cout << "Object Update\n";
}


void OpenGLObject::Cleanup()
{
	glDeleteVertexArrays(1, &vaoID);
	glDeleteBuffers(1, &pboID);
	glDeleteTextures(1, &textureID);
}



void OpenGLObject::VAO_Object::SetValue(float x, float y)
{
	Position.x = x;
	Position.y = y;
}

void OpenGLObject::VAO_Object::SetTexture(float s, float t)
{
	Texture.s = s;
	Texture.t = t;
}
