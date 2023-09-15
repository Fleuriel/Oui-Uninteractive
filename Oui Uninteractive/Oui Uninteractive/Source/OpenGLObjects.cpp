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

std::vector<glm::vec2> OpenGLObject::square;
std::vector<glm::vec2> OpenGLObject::triangle;
std::vector<std::string> OpenGLObject::mesh_Directory;


std::map<std::string, OpenGLShader> OpenGLObject::shdrpgms;
std::vector<OpenGLShader> OpenGLObject::shader{};
GLuint OpenGLObject::ShaderProgram{};

std::map<std::string, OpenGLObject::OpenGLModel> OpenGLObject::Model_Storage;
std::map<std::string, OpenGLObject> OpenGLObject::Object_Storage;

GLuint OpenGLObject::VAO = 0;
GLuint OpenGLObject::VBO = 0;



GLuint OpenGLObject::textureID;								// id for texture object

// set up initial state
void OpenGLObject::Init()
{
#ifdef _DEBUG
	std::cout << "OpenGLObject::Init()\n\n";

#endif // _DEBUG

	init_scenes("../scenes/tutorial-4.scn");

	Load_Files();
//	Load_Meshes();
	



//Objects.color = { 0.5,0.2,0.1f };
//
////	OpenGLShadersInitialization();
//
//// Testing from Here
//
//GLfloat vertices[] =
//{
//	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,  // Position for vertex 0
//	1.0f, 0.0f, 0.0f,  
//
//	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,  // Position for vertex 1
//	0.0f, 1.0f, 0.0f, 
//
//	0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,  // Position for vertex 2
//	0.0f, 0.0f, 1.0f  
//};
//
//
//glm::mat4 model = glm::mat4(1.0f);
//glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f);
//translation.x += 0.001f;
//
//
//
//
//GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//glCompileShader(vertexShader);
//
//GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//glCompileShader(fragmentShader);
//
//
//ShaderProgram = glCreateProgram();
//
//glAttachShader(ShaderProgram, vertexShader);
//glAttachShader(ShaderProgram, fragmentShader);
//
////glDeleteShader(vertexShader);
////glDeleteShader(fragmentShader);
//
//
//glGenVertexArrays(1, &VAO);
//glGenBuffers(1, &VBO);
//
//glBindVertexArray(VAO);
//
//glBindBuffer(GL_ARRAY_BUFFER, VBO);
//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//glEnableVertexAttribArray(0);
//
//glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//glEnableVertexAttribArray(1);
//
//glBindBuffer(GL_ARRAY_BUFFER, 0);
//glBindVertexArray(0);
//
//
//std::cout << "Asd" << '\n';

	// End Testing
	

#ifdef _DEBUG
	std::cout << "Mesh Directories for : '\t" << mesh_Directory[0] << '\n';
	std::cout << "Mesh Directories for : '\t" << mesh_Directory[1] << '\n';
	std::cout << "Mesh Directories for : '\t" << mesh_Directory[2] << '\n';
	std::cout << '\n';
#endif

	//Setup_Quad_VAO();



}


void OpenGLObject::Update(GLdouble delta_time)
{
	std::cout << "Object Update\n";

	using glm::radians;

	if (mdl_ref->first != "triangle")
		orientation.x += (orientation.y * static_cast<float>(delta_time));

	if (orientation.x >= 360 || orientation.x <= -360)
		orientation.x = 0;


	// Compute the scale matrix
	glm::mat3 Scale = glm::mat3(
		scaling.x, 0.0f, 0.0f,
		0.0f, scaling.y, 0.0f,
		0.0f, 0.0f, 1.0f
	);

	// Compute the rotation matrix
	glm::mat3 Rotation = glm::mat3(
		cosf(radians(orientation.x)), sinf(radians(orientation.x)), 0.0f,
		-sinf(radians(orientation.x)), cosf(radians(orientation.x)), 0.0f,
		0.0f, 0.0f, 1.0f
	);

	// Compute the translation matrix
	glm::mat3 Translation = glm::mat3(
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		position.x, position.y, 1.0f
	);

	// Compute the model-to-world-to-NDC transformation matrix
	//mdl_to_ndc_xform = camera2d.world_to_ndc_xform * (Translation * Rotation * Scale);
	model_To_NDC_xform = (Translation * Rotation * Scale);
}


void OpenGLObject::Draw() const
{
	shd_ref->second.Use();
	// Part 2: Bind object's VAO handle
	glBindVertexArray(mdl_ref->second.vaoid); // Bind object's VAO handle

	// Part 3: Copy object's 3x3 model-to-NDC matrix to vertex shader
	shd_ref->second.SetUniform("uColor", color);
	shd_ref->second.SetUniform("uModel_to_NDC", model_To_NDC_xform);


	// Part 4: Render using glDrawElements or glDrawArrays
	glDrawElements(
		mdl_ref->second.primitive_type,
		mdl_ref->second.draw_cnt,
		GL_UNSIGNED_SHORT, NULL);


	// Part 5: Clean up
	glBindVertexArray(0); // Unbind the VAO

	shd_ref->second.UnUse();

}

void OpenGLObject::Cleanup()
{

	glDeleteTextures(1, &textureID);


	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(ShaderProgram);
}

void OpenGLObject::OpenGLModel::init(std::string model_name)
{
	std::string file_path = "../meshes/";
	file_path.append(model_name);

	file_path.append(".msh");

	Load_Meshes(file_path);


}


void OpenGLObject::init_scenes(std::string scene_filename)
{
	/*
	Scene File contains:
	=============================================================================
	|1|[No_of_Obj]		number of Objects
	=============================================================================
	|2|[Mdl_Name]		model name												|
	|3|[GameObject]		name of gameObject										|
	|4|[Shd_pgm]			names of shader program: vert and frag files		|
	|5|[Colors]			r,g,b	(rgb colors) 									|
	|6|[Scale]			x,y		(Scale x and y)									|
	|7|[Rotation]		x,y		(Initial rotation/orientation)					|
	|8|[Position]		x,y		(Position of the object in the world)			|
	=============================================================================

	* Repeats 2 to 8 for the remaining of the file for number of times declared
	* by |1|. i.e. |1| = 10, |2| - |8| repeats 10 times below

	=============================================================================

	* The code before the while loop takes |1| out of the picture so that it can
	* keep reiterate the |2| to |7| for each objects ...

	=============================================================================
*/
// Open file...
	std::ifstream ifs{ scene_filename, std::ios::in };

	// Check if file exist or not
	if (!ifs)
	{
		std::cout << "ERROR: unable to open scene file: " << scene_filename << "\n";
		exit(EXIT_FAILURE);
	}


	ifs.seekg(0, std::ios::beg);										// Seek to the top of the file ...

	std::string line;
	getline(ifs, line);													// |1|
	std::istringstream line_sStream{ line };							// Parse |1| from |2| to |8|
	GLuint obj_Count{};													// Create container for |1|
	line_sStream >> obj_Count;											// Assign values into obj_cnt


	// |1| is taken out ... and begins |2| to |8|
	while (obj_Count--)	// loop until no more object remaining
	{
		getline(ifs, line);												// |2|
		std::istringstream line_ModelName{ line };						// Parse |2| from |3| to |8|
		std::string model_name;											// Create container for |2| 
		line_ModelName >> model_name;									// Add |2| into the model_name
		if (Model_Storage.find(model_name) == Model_Storage.end())
		{
			Model_Storage[model_name].init(model_name);
		}


		getline(ifs, line);												// |3|
		std::istringstream line_ObjectName{ line };						// Parse |3| from |4| to |8|
		std::string object_name;										// Create container for |3| 
		line_ObjectName >> object_name;									// Add |3| into the object_name

		getline(ifs, line);												// |4|
		std::istringstream line_ShaderName{ line };						// Parse |4| from |5| to |8|
		std::string shader_name;										// Create container for |4| 
		line_ShaderName >> shader_name;									// Add |4| into the object_name

		if (OpenGLObject::shdrpgms.find(shader_name) == OpenGLObject::shdrpgms.end())				// If shader is not in the shdr_pgms list ...
		{
			std::string vert, frag;										// After separating |4| into model_name,
			// the program will search for a model_name
			line_ShaderName >> vert;									// from the ../shaders/ directory, and find
			line_ShaderName >> frag;									// the shader file to insert into  
			Insert_Shader_Program(shader_name, vert, frag);					// insert_shdrpgm ...
		}

		getline(ifs, line);												// |5|
		std::istringstream line_Color{ line };							// Parse |5| from |6| to |8|
		glm::vec3 Color{};												// Create Container for |5|
		line_Color >> Color.r;											// Assign Container variables r
		line_Color >> Color.g;											// Assign Container variables g
		line_Color >> Color.b;											// Assign Container variables b

		getline(ifs, line);												// |6|
		std::istringstream line_Scale{ line };							// Parse |6| from |7| and |8|
		glm::vec2 Scale{};												// Create Container for |6|
		line_Scale >> Scale.x;											// Assign Container for scaling vector x
		line_Scale >> Scale.y;											// Assign Container for scaling vector y

		getline(ifs, line);												// |7|
		std::istringstream line_Orientation{ line };					// Parse |7| from |8|
		glm::vec2 Orientation{};										// Create Container for |7|
		line_Orientation >> Orientation.x;								// Input the Orientation.x (Angle Displacement)
		line_Orientation >> Orientation.y;								// Input the Orientation.y (Rotation Speed) into the container

		getline(ifs, line);												// |8|
		std::istringstream line_Position{ line };						// Parse |8| from the entire fragment of the code
		glm::vec2 Position{};											// Create Container for |8|
		line_Position >> Position.x;									// Assign Container for Initial Position of the model x
		line_Position >> Position.y;									// Assign Container for Initial Position of the model y

		// Assign the objects with its parameters ...
		OpenGLObject obj;													// GLObject Object ...
		obj.mdl_ref = Model_Storage.find(model_name);							// Assigning object with model_reference
		obj.shd_ref = shdrpgms.find(shader_name);						// Assigning object with shader_reference
		obj.color = Color;												// Assigning object with Color Parameters
		obj.scaling = Scale;											// Assigning object with Scale Parameters
		obj.orientation = Orientation;									// Assigning object with Orientation Parameters
		obj.position = Position;										// Assigning object with Position Parameters

		Object_Storage[object_name] = obj;										// for each |2|, assign each object(finished) into
		Object_Storage[object_name].InitObjects();									// objects container, AND initialize them ...


	}
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
#ifdef _DEBUG
					std::cout << "Reading " << meshFileName << "\n";
#endif

					inputFileStream.close();

					
					mesh_Directory.push_back(entry.path().string());
				}
				else
				{
					std::cerr << "Error Opening File: " << meshFileName << '\n';
				}
			}
		}
	}
}

void OpenGLObject::Load_Meshes(std::string mesh_file) {


	//Position vertexes
	std::vector<glm::vec2> pos_vtx{};

	//Index
	std::vector<GLushort> idx_vtx;

	//GLModel
	OpenGLObject::OpenGLModel mdl;

	//Model name
	std::string mesh_name{};

	//Reading file
	std::ifstream ifs{ mesh_file, std::ios::in };

	if (ifs.fail())
	{
		std::cout << "Loading " << mesh_file << "failed. \n";
		return;
	}

	//get to the top of the file
	ifs.seekg(0, std::ios::beg);

	std::string line;
	//getting the first line

	while (!ifs.eof())
	{
		getline(ifs, line);

		std::istringstream line_sstm{ line };

		char prefix;

		line_sstm >> prefix;

		switch (prefix)
		{
			//getting model/mesh name
		case 'n':
		{
			//std::cout << "is a N \n";
			line_sstm >> mesh_name;
		}
		break;

		//getting vertex position
		case 'v':
		{
			//std::cout << "is a V \n";
			glm::vec2 vpos;

			line_sstm >> vpos.x;
			line_sstm >> vpos.y;

			pos_vtx.emplace_back(vpos);
		}
		break;

		case 't':
		{
			mdl.primitive_type = GL_TRIANGLES;

			while (line_sstm)
			{
				GLushort index;

				line_sstm >> index;

				//checking if line_sstm failed to put value into index
				if (!line_sstm.fail())
				{
					//std::cout << index << ", ";
					idx_vtx.push_back(index);
				}
			}
		}
		break;

		case 'f':
		{
			mdl.primitive_type = GL_TRIANGLE_FAN;

			while (line_sstm)
			{
				GLushort index;

				line_sstm >> index;

				//checking if line_sstm failed to put value into index
				if (!line_sstm.fail())
				{
					//std::cout << index << ", ";
					idx_vtx.push_back(index);
				}
			}
		}
		break;

		//for case 't' and 'f' [GL_TRIANGLE] || [GL_TRIANGLE_FAN]
		//also getting indexing
		default:
			break;
		}
	}

	ifs.close();
	
//for (int i = 0; i < mesh_Directory.size(); i++)
//{
//	std::vector <GLushort> Indices_Vertex{};
//	OpenGLObject::OpenGLModel Model;
//	std::string Mesh_Name{};
//	std::ifstream inputFileStream{ mesh_Directory[i], std::ios::in };			// Input file...
//
//	if (inputFileStream.fail())											// Check if file exist ...
//	{
//		std::cout << "Loading " << Mesh_Name << "failed. \n";
//		return;
//	}
//
//	inputFileStream.seekg(0, std::ios::beg);							// Initialize the file to the start ...
//
//	std::string line;													// Create container for line ...
//
//	while (!inputFileStream.eof())
//	{
//		getline(inputFileStream, line);									// Read the line it is on ...
//
//		std::istringstream line_sStream{ line };						// String Stream
//
//		char prefix;													// Create container for prefix [1]
//
//		line_sStream >> prefix;											// [1]
//
//		switch (prefix)
//		{
//		case 'n':														// [1] 
//		{
//			line_sStream >> Mesh_Name;									// Mesh name separated from prefix
//			break;
//		}
//		case 'v':														// [2] v
//		{
//			glm::vec2 vert_Position{};									// [2] Vertex Position Contianer
//
//			line_sStream >> vert_Position.x;							// Assign values of Vertex Position into Container x
//			line_sStream >> vert_Position.y;							// Assign values of Vertex Position into Container y
//
//			Model.Position_Vertex.push_back(vert_Position);				// Emplace back the vertex position into the position_vertex container
//			break;
//		}
//		case 't':														// [2] t
//		{
//			Model.primitive_type = GL_TRIANGLES;							// [t] = GL_TRIANGLE_FAN ...							
//
//			while (line_sStream)										// while line_sStream is not 0 ...
//			{
//				GLushort index;											// Create container for index ...
//
//				line_sStream >> index;									// Assign index into line_sStream
//
//				if (!line_sStream.fail())								// if line_sStream fails, then do nothing
//				{														// else
//					Indices_Vertex.push_back(index);							// pushback the index
//				}
//			}
//			break;
//		}
//		case 'f':														// [2] f
//		{
//			Model.primitive_type = GL_TRIANGLE_FAN;						// [f] = GL_TRIANGLE_FAN ...
//
//			while (line_sStream)										// while line_sStream is not 0 ...								
//			{
//				GLushort index;											// Create container for index ...
//
//				line_sStream >> index;									// Assign index into line_sStream
//
//
//				if (!line_sStream.fail())							    // if line_sStream fails, then do nothing
//				{													    // else
//					Indices_Vertex.push_back(index);						    // pushback the index
//				}
//			}
//			break;
//		}
//		default:
//			break;
//		}
//	}

	ifs.close();														// Close the file stream


		//GLuint VBO_Handler{};
		//glCreateBuffers(1, &VBO_Handler);
		//glNamedBufferStorage(VBO_Handler, sizeof(glm::vec2) * mdl.Position_Vertex.size(), mdl.Position_Vertex.data(), GL_DYNAMIC_STORAGE_BIT);
		//
		//GLuint vaoid;
		//glCreateVertexArrays(1, &vaoid);
		//
		////Vertex
		//glEnableVertexArrayAttrib(vaoid, 0); //Assigning Vertex array object with index 0 (for position)
		//glVertexArrayVertexBuffer(vaoid, 2, VBO_Handler, 0, sizeof(glm::vec2)); //bind the named buffer to vertex buffer binding point 2
		//glVertexArrayAttribFormat(vaoid, 0, 2, GL_FLOAT, GL_FALSE, 0); //format vao attribute
		//glVertexArrayAttribBinding(vaoid, 0, 2); //binding vao attribute to binding point 2
		//
		//GLuint EBO_Handler;
		//glCreateBuffers(1, &EBO_Handler); //Creating ebo buffer
		//glNamedBufferStorage(EBO_Handler, sizeof(GLushort) * idx_vtx.size(), reinterpret_cast<GLvoid*>(idx_vtx.data()), GL_DYNAMIC_STORAGE_BIT); //setting memory location for ebo buffer
		//glVertexArrayElementBuffer(vaoid, EBO_Handler); //binding ebo to vaoid


	ifs.close();

	GLuint vbo_hdl;
	glCreateBuffers(1, &vbo_hdl);
	glNamedBufferStorage(vbo_hdl, sizeof(glm::vec2)* pos_vtx.size(), pos_vtx.data(), GL_DYNAMIC_STORAGE_BIT);

	GLuint vaoid;
	glCreateVertexArrays(1, &vaoid); //Creating Vertex array object

	//Vertex
	glEnableVertexArrayAttrib(vaoid, 0); //Assigning Vertex array object with index 0 (for position)
	glVertexArrayVertexBuffer(vaoid, 2, vbo_hdl, 0, sizeof(glm::vec2)); //bind the named buffer to vertex buffer binding point 2
	glVertexArrayAttribFormat(vaoid, 0, 2, GL_FLOAT, GL_FALSE, 0); //format vao attribute
	glVertexArrayAttribBinding(vaoid, 0, 2); //binding vao attribute to binding point 2

	GLuint ebo_hdl;
	glCreateBuffers(1, &ebo_hdl); //Creating ebo buffer
	glNamedBufferStorage(ebo_hdl, sizeof(GLushort)* idx_vtx.size(), reinterpret_cast<GLvoid*>(idx_vtx.data()), GL_DYNAMIC_STORAGE_BIT); //setting memory location for ebo buffer
	glVertexArrayElementBuffer(vaoid, ebo_hdl); //binding ebo to vaoid

	glBindVertexArray(0);

	mdl.vaoid = vaoid;
	mdl.draw_cnt = idx_vtx.size();
	mdl.primitive_cnt = 2;

//		glBindVertexArray(0);

		mdl.vaoid = vaoid;
		mdl.draw_cnt = idx_vtx.size();
		//mdl.primitive_cnt = Model.Position_Vertex.size();

		Model_Storage[mesh_name] = mdl;
		//std::cout << "Vaoid: " << Model_Storage[Mesh_Name].vaoid << '\n';
		//std::cout << Model_Storage[Mesh_Name].primitive_type << '\n';
		//std::cout << Model_Storage[Mesh_Name].draw_cnt << '\n';


		//std::cout << "Mesh Name: " << Mesh_Name << '\n';

		//std::cout << Model_Storage["triangle"].Position_Vertex << '\n';

	
	}







void OpenGLObject::Insert_Shader_Program(std::string shdr_pgm_name, std::string vtx_shdr_name, std::string frg_shdr_name)
{
	std::vector<std::pair<GLenum, std::string>> shdr_files{
	std::make_pair(GL_VERTEX_SHADER, vtx_shdr_name),
	std::make_pair(GL_FRAGMENT_SHADER, frg_shdr_name)
	};
	OpenGLShader shdr_pgm;
	shdr_pgm.CompileLinkValidate(shdr_files);
	if (GL_FALSE == shdr_pgm.IsLinked()) {
		std::cout << "Unable to compile/link/validate shader programs\n";
		std::cout << shdr_pgm.GetLog() << "\n";
		std::exit(EXIT_FAILURE);
	}
	// add compiled, linked, and validated shader program to
	// std::map container GLApp::shdrpgms
	shdrpgms[shdr_pgm_name] = shdr_pgm;


}


void OpenGLObject::InitObjects()
{
	using glm::radians;

	glm::mat3 Translate = glm::mat3
	{
		1, 0, 0,
		0, 1, 0,
		 position.x,  position.y, 1
	};

	glm::mat3 Rotation = glm::mat3
	{
		cosf(radians(orientation.x)), sinf(radians(orientation.x)) , 0,
		-sinf(radians(orientation.x)),  cosf(radians(orientation.x)) , 0,
		0, 0, 1
	};

	glm::mat3 Scale = glm::mat3
	{
		scaling.x, 0, 0,
		0, scaling.y, 0,
		0, 0, 1
	};

	// Instead of doing transpose, you can do what OpenGL matrix does:
	// Row-Major Order:				Column Major Order;
	//	   x0 y0 z0						 x0 x1 x2
	//	   x1 y1 z1						 y0 y1 y2
	//	   x2 y2 z2						 z0 z1 z2
	model_To_NDC_xform = Translate * Rotation * Scale;

}







/*=======================================================================================================================*/
/*=======================================================================================================================*/
/*===================================================OPENGL CAMERA=======================================================*/
/*=======================================================================================================================*/
/*=======================================================================================================================*/
/*=======================================================================================================================*/