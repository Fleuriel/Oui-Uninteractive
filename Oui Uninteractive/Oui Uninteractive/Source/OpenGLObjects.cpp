/**************************************************************************
 * @file OpenGLObjects.cpp
 * @author 
 * @par DP email: 
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 09-05-2023
 * @brief 
 *************************************************************************/

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


std::map<std::string, OpenGLShader> OpenGLObject::shdrpgms;
std::vector<OpenGLShader> OpenGLObject::Shader{};
GLuint OpenGLObject::ShaderProgram{};

std::map<std::string, OpenGLObject::OpenGLModel> OpenGLObject::Model_Storage;
GLuint OpenGLObject::VAO = 0;
GLuint OpenGLObject::VBO = 0;



GLuint OpenGLObject::vaoID;									// how many indices in element buffer
GLuint OpenGLObject::pboID;									// id for PBO
GLuint OpenGLObject::textureID;								// id for texture object

// set up initial state
void OpenGLObject::Init()
{
#ifdef _DEBUG
	std::cout << "OpenGLObject::Init()\n\n";

#endif // _DEBUG

	Load_Files();
	Load_Meshes();


	Objects.Color = { 0.5,0.2,0.1f };


	const char* vertexShaderSource =
		"#version 450 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec3 aColor;\n"
		"out vec3 FragColor;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"	FragColor = aColor;"
		"}\0";

	const char* fragmentShaderSource = 
		"#version 450 core\n"
		"in vec3 FragColor;\n"
		"out vec4 FragColorOutput;\n"
		"void main()\n"
		"{\n"
		"	FragColorOutput = vec4(FragColor, 1.0);\n"
		"}\n\0";

//	OpenGLShadersInitialization();

	// Testing from Here

	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,  // Position for vertex 0
		1.0f, 0.0f, 0.0f,  

		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,  // Position for vertex 1
		0.0f, 1.0f, 0.0f, 

		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,  // Position for vertex 2
		0.0f, 0.0f, 1.0f  
	};


	glm::mat4 model = glm::mat4(1.0f);
	glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f);
	translation.x += 0.001f;




	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);


	ShaderProgram = glCreateProgram();

	glAttachShader(ShaderProgram, vertexShader);
	glAttachShader(ShaderProgram, fragmentShader);

	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);

	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	std::cout << "Asd" << '\n';













	// End Testing
	





#ifdef _DEBUG
	std::cout << "Mesh Directories for : '\t" << Mesh_Directory[0] << '\n';
	std::cout << "Mesh Directories for : '\t" << Mesh_Directory[1] << '\n';
	std::cout << "Mesh Directories for : '\t" << Mesh_Directory[2] << '\n';
	std::cout << '\n';
#endif

	//Setup_Quad_VAO();



}

//void OpenGLObject::Setup_Quad_VAO()
//{
//	//Define vertex position and color attributes
//	std::vector<VAO_Object> vao_value;
//	vao_value.reserve(4);
//
//	VAO_Object setup_var;
//
//	//top left
//	setup_var.SetValue(-1.0f, 1.0f);
//	setup_var.SetTexture(0.f, 1.f);
//	vao_value.emplace_back(setup_var);
//
//	//bottom left
//	setup_var.SetValue(-1.0f, -1.0f);
//	setup_var.SetTexture(0.f, 0.f);
//	vao_value.emplace_back(setup_var);
//
//	//bottom right
//	setup_var.SetValue(1.0f, 1.0f);
//	setup_var.SetTexture(1.f, 1.f);
//	vao_value.emplace_back(setup_var);
//
//	//top right
//	setup_var.SetValue(1.0f, -1.0f);
//	setup_var.SetTexture(1.f, 0.f);
//	vao_value.emplace_back(setup_var);
//
//	// transfer vertex position and color attributes to VBO
//	GLuint VBO_Handler;
//	glCreateBuffers(1, &VBO_Handler);
//
//	glNamedBufferStorage(VBO_Handler, sizeof(VAO_Object) * vao_value.size(), vao_value.data(), GL_DYNAMIC_STORAGE_BIT);
//
//	//encapsulate information about contents of VBO and VBO handle
//	// to another object called VAO
//	glCreateVertexArrays(1, &vaoID);
//
//	//enable use of vertex position
//	glEnableVertexArrayAttrib(vaoID, 0);
//
//	//vertex buffer binding point 3
//	glVertexArrayVertexBuffer(vaoID, 3, VBO_Handler, 0, sizeof(VAO_Object)/*number of spaces each iteration*/);
//
//	//position
//	//for vertex position array, we use vertex attribute index 0
//	//and vertex buffer binding point 3
//	//offsetof (offset based on on data type, and member variable, offset will be automatically calculated)
//	glVertexArrayAttribFormat(vaoID, 0, 2/*size of data*/, GL_FLOAT, GL_FALSE, offsetof(VAO_Object/*structure type*/, VAO_Object::Position/*value name*/));
//	glVertexArrayAttribBinding(vaoID, 0, 3);
//
//	//enable use of texture vertex
//	glEnableVertexArrayAttrib(vaoID, 2);
//
//	// for vertex color array, we use vertex attribute index 1
//	// and vertex buffer binding point 3
//	glVertexArrayAttribFormat(vaoID, 2, 2/*size of data*/, GL_FLOAT, GL_FALSE, offsetof(VAO_Object/*structure type*/, VAO_Object::Texture/*value name*/));
//	glVertexArrayAttribBinding(vaoID, 2, 3);
//
//	std::array<GLushort, 4> Indices_Vertex
//	{
//		0, 1, 2, 3
//	};
//
//	GLuint EBO_Handler;
//	glCreateBuffers(1, &EBO_Handler);
//	glNamedBufferStorage(EBO_Handler, sizeof(GLushort) * Indices_Vertex.size(), reinterpret_cast<GLvoid*>(Indices_Vertex.data()), GL_DYNAMIC_STORAGE_BIT);
//	glVertexArrayElementBuffer(vaoID, EBO_Handler);
//	glBindVertexArray(0);
//
//
//
//}

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
#ifdef _DEBUG
					std::cout << "Reading " << meshFileName << "\n";
#endif

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




	
	for (int i = 0; i < Mesh_Directory.size(); i++)
	{
		std::vector <GLushort> Indices_Vertex{};
		OpenGLObject::OpenGLModel Model;
		std::string Mesh_Name{};
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

				Model.Position_Vertex.push_back(vert_Position);						// Emplace back the vertex position into the position_vertex container
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
		glNamedBufferStorage(VBO_Handler, sizeof(glm::vec2) * Model.Position_Vertex.size(), Model.Position_Vertex.data(), GL_DYNAMIC_STORAGE_BIT);

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
		Model.draw_cnt = Indices_Vertex.size();
	//	Model.primitive_cnt = 2;

		Model_Storage[Mesh_Name] = Model;
		//std::cout << "Vaoid: " << Model_Storage[Mesh_Name].vaoid << '\n';
		//std::cout << Model_Storage[Mesh_Name].primitive_type << '\n';
		//std::cout << Model_Storage[Mesh_Name].draw_cnt << '\n';


		//std::cout << "Mesh Name: " << Mesh_Name << '\n';

		//std::cout << Model_Storage["triangle"].Position_Vertex << '\n';

	
	}

	for (auto const& x : Model_Storage[TRIANGLE].Position_Vertex)
	{
		std::cout << x.x << "," << x.y << '\n';

	}

}



void OpenGLObject::Draw() const
{
	shd_ref->second.Use();

	// Part 2: Bind object's VAO handle
	glBindVertexArray(mdl_ref->second.vaoid); // Bind object's VAO handle

	// Part 3: Copy object's 3x3 model-to-NDC matrix to vertex shader
	shd_ref->second.SetUniform("uColor", Color);
	shd_ref->second.SetUniform("uModel_to_NDC", Model_to_NDC_xform);


	// Part 4: Render using glDrawElements or glDrawArrays
	glDrawElements(
		mdl_ref->second.primitive_type,
		mdl_ref->second.draw_cnt,
		GL_UNSIGNED_SHORT, NULL);


	// Part 5: Clean up
	glBindVertexArray(0); // Unbind the VAO

	shd_ref->second.UnUse();

}
void OpenGLObject::Update(GLdouble delta_time)
{
	std::cout << "Object Update\n";
	//// Update object rotations
	//this->Rotation[0] += (this->Rotation[1] * static_cast<float>(delta_time));
	//// Compute model-to-world matrix
	//glm::mat3 scaleMatrix = { Scaling.x,   0.0f    , 0.0f,
	//							 0.0f  , Scaling.y , 0.0f,
	//							 0.0f  ,   0.0f    , 1.0f };

	//glm::mat3 rotMatrix = { cos(Rotation[0]) , sin(Rotation[0]), 0.0f,
	//						-sin(Rotation[0]), cos(Rotation[0]), 0.0f,
	//							  0.0f      ,       0.0f     , 1.0f };

	//glm::mat3 transMatrix = {     1.0f    ,     0.0f   , 0.0f,
	//							  0.0f    ,     1.f    , 0.0f,
	//						  Position[0] , Position[1], 1.0f };
	//// Compute final transformation matrix  
	//// Assign the final transformation matrix to the member variable
	//this->Model_to_NDC_xform = camera2d.world_to_ndc_xform * transMatrix * rotMatrix * scaleMatrix;
}


void OpenGLObject::Cleanup()
{

	//ShaderProgram.DeleteShaderProgram();
	glDeleteVertexArrays(1, &vaoID);
	glDeleteBuffers(1, &pboID);
	glDeleteTextures(1, &textureID);


	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(ShaderProgram);
}



//void OpenGLObject::VAO_Object::SetValue(float x, float y)
//{
//	Position.x = x;
//	Position.y = y;
//}
//
//void OpenGLObject::VAO_Object::SetTexture(float s, float t)
//{
//	Texture.s = s;
//	Texture.t = t;
//}




//void OpenGLObject::OpenGLShadersInitialization()
//{
//
//	std::cout << "Shaders Initialized\n";
//	OpenGLObject::VectorPairStrStr ShaderCodex;
//
//	std::vector<std::pair<GLenum, std::string>> ShaderFiles;
//
//	std::string vert{}, frag{};
//
//	vert =
//
//		R"(
//		#version 450 core
//
//		layout(location = 0) in vec2 aVertexPosition;
//		layout(location = 1) in vec3 aVertexColor;
//
//		out vec3 vColor;
//
//		uniform mat4 uModel_to_NDC;
//
//		void main()
//		{
//			gl_Position = uModel_to_NDC * vec4(aVertexPosition, 0.0, 1.0);
//			vColor = aVertexColor;
//		}
//	)";
//
//	frag =
//
//		R"(
//		#version 450 core
//
//		in vec3 vColor;
//		
//		out vec4 fFragColor;
//		
//		uniform vec3 uBaseColor; // Uniform variable for the base color
//		
//		void main()
//		{
//		    fFragColor = vec4(uBaseColor * vColor, 1.0);
//		}
//	)";
//
//	// Adding vertex shader ...
//	ShaderFiles.emplace_back(std::make_pair(GL_VERTEX_SHADER, vert));
//
//	// Adding fragment shader ...
//	ShaderFiles.emplace_back(std::make_pair(GL_FRAGMENT_SHADER, frag));
//
//	ShaderProgram.CompileLinkValidate(ShaderFiles);
//
//
//
//
//	shdrpgms["Oui_Uninteractive"] = ShaderProgram;
//
//
//	for (std::pair<GLenum, std::string> x : ShaderFiles)
//	{
//		if (!ShaderProgram.CompileShaderFromString(x.first, x.second))
//		{
//			std::cout << "Unable to compile shader programs from string" << "\n";
//			std::cout << ShaderProgram.GetLog() << std::endl;
//			std::exit(EXIT_FAILURE);
//		}
//	}
//	if (!ShaderProgram.Link())
//	{
//		std::cout << "Unable to link shader programs" << "\n";
//		std::cout << ShaderProgram.GetLog() << std::endl;
//		std::exit(EXIT_FAILURE);
//	}
//
//	if (!ShaderProgram.Validate())
//	{
//		std::cout << "Unable to validate shader programs" << "\n";
//		std::cout << ShaderProgram.GetLog() << std::endl;
//		std::exit(EXIT_FAILURE);
//	}
//
//	//shdr_pgm.Link(shdr_files);
//	if (GL_FALSE == ShaderProgram.IsLinked())
//	{
//		std::cout << "Unable to compile/link/validate shader programs" << "\n";
//		std::cout << ShaderProgram.GetLog() << std::endl;
//		std::exit(EXIT_FAILURE);
//	}
//
//
//
//}
