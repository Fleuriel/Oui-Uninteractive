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
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <RandomUtilities.h>
#include <GameStateManager.h>
#include <stb_image.h>


std::vector<glm::vec2> OpenGLObject::square;
std::vector<glm::vec2> OpenGLObject::triangle;
std::vector<std::string> OpenGLObject::mesh_Directory;

unsigned int OpenGLObject::mdl_ref = 0; // Define and initialize mdl_ref
unsigned int OpenGLObject::shd_ref = 0; // Define and initialize shd_ref

OpenGLObject::OpenGLModel modl;

std::vector<OpenGLShader> OpenGLObject::shdrpgms;
std::vector<OpenGLObject::OpenGLModel> OpenGLObject::models;
//std::map<std::string, OpenGLShader> OpenGLObject::shdrpgms;
GLuint OpenGLObject::ShaderProgram{};

std::vector<GLuint> OpenGLObject::textures;

std::map<std::string, OpenGLObject::OpenGLModel> OpenGLObject::Model_Storage;
std::map<std::string, OpenGLObject> OpenGLObject::Object_Storage;

GLuint OpenGLObject::VAO = 0;
GLuint OpenGLObject::VBO = 0;

int bgTexture, firstTexture, secondTexture;


GLuint Suffering; 


/**************************************************************************
* @brief		Loads Meshes for models and/or other shader files to
*				enable creation of GameObjects.
* @param  none
* @return void
*************************************************************************/
void OpenGLObject::Init()
{
#ifdef _DEBUG
	std::cout << "OpenGLObject::Init()\n\n";

#endif // _DEBUG


//	Load_Meshes();
	

	//modl.setup_TextureVAO();

	VectorPairStrStr fileName{
		std::make_pair<std::string, std::string>
		("../shaders/Oui_Uninteractive.vert", "../shaders/Oui_Uninteractive.frag")
	};

	init_shdrpgms_cont(fileName);
	
	
	//modl.setup_TextureVAO();
	

	//Suffering = OpenGLObject::Setup_TextureObject("../texture/pantheon.jpg");
	firstTexture = OpenGLObject::Setup_TextureObject("../texture/pepethefrog.png");
	secondTexture = OpenGLObject::Setup_TextureObject("../texture/pepe.jpg");
	bgTexture = OpenGLObject::Setup_TextureObject("../texture/background.jpg");


	textures.emplace_back(firstTexture);
	textures.emplace_back(secondTexture);
	textures.emplace_back(bgTexture);


	models.emplace_back(OpenGLObject::Box_Model(0, color, firstTexture));
	models.emplace_back(OpenGLObject::Box_Model(1 ,color, secondTexture));
	models.emplace_back(OpenGLObject::Box_Model(2, color, bgTexture));

	



//	const char* vertexShaderSource =
//	R"(#version 450 core
//		layout(location = 0) in vec3 aPos;
//		layout(location = 1) in vec3 aColor;
//		
//		out vec3 vertexColor;
//		
//		uniform mat4 transform;
//
//		void main()
//		{
//			gl_Position = transform * vec4(aPos, 1.0);
//			vertexColor = aColor;
//		}
//
//
//)";
//
//	const char* fragmentShaderSource =
//		R"(#version 450 core
//			out vec4 FragColor;
//			in vec3 vertexColor;			
//
//
//			void main()
//			{
//			    FragColor = vec4(vertexColor, 1.0f);
//			}
// )";
	//texture = OpenGLObject::Setup_TextureObject("../textures/pepethefrog.png");
	//
	//
	//
	//
	//float vertices[] = {
	//	 0.5f,  0.5f, 0.0f,		0.4f, 0.3f, 0.9f, // top right
	//	 0.5f, -0.5f, 0.0f,		0.7f, 0.2f, 0.9f, // bottom right
	//	-0.5f, -0.5f, 0.0f,		0.2f, 0.6f, 0.15f, // bottom left
	//	-0.5f,  0.5f, 0.0f,		1.0f, 0.4f, 0.15f // top left 
	//};
	//unsigned int indices[] = {  // note that we start from 0!
	//	0, 1, 3,   // first triangle
	//	1, 2, 3    // second triangle
	//};
	//
	//// Create EBO for indices (Two Triangles for one rectangle)
	//unsigned int EBO;
	//glGenBuffers(1, &EBO);
	//
	//// Create Vertex Shader to input and compile the vertexShader
	//GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//glCompileShader(vertexShader);
	//
	//
	//// Create Fragment Shader to input and compile the fragmentShader
	//GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//glCompileShader(fragmentShader);
	//
	//
	//// Attach ShaderProgram to CreateProgram.
	//ShaderProgram = glCreateProgram();
	//
	////Attach Shader Program with both vertex and fragment shaders
	//glAttachShader(ShaderProgram, vertexShader);
	//glAttachShader(ShaderProgram, fragmentShader);
	////Link the shaders
	//glLinkProgram(ShaderProgram);
	//
	//
	//// generate the vertex arrays to VAO. 
	//glGenVertexArrays(1, &VAO);
	//// generate the buffer of VBO.
	//glGenBuffers(1, &VBO);
	//
	//// bind the vertex array to VAO.
	//glBindVertexArray(VAO);
	//
	////bind buffer to VAO.
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//
	//
	//
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);
	//
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);
	//
	//
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBindVertexArray(0);
	//
	//
	//
	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);




#ifdef _DEBUG

	std::cout << '\n';
#endif

	//Setup_Quad_VAO();



}

//void OpenGLObject::OpenGLModel::draw() const
//{
//	//texture object is to use texture image unit 6
//	glBindTextureUnit(6, importTexture);
//
//
//
//	glTextureParameteri(importTexture, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);//Repeat wrap
//	glTextureParameteri(importTexture, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);//Repeat wrap
//
//	shdrpgms[shd_ref].Use(); // Install the shader program
//	// Part 2: Bind object's VAO handle
//
//	shdrpgms[shd_ref].SetUniform("uTex2d", 6);
//
//	glBindVertexArray(models[mdl_ref].vaoid); // Bind object's VAO handle
//
//
//	glDrawElements(
//		models[mdl_ref].primitive_type,
//		models[mdl_ref].draw_cnt,
//		GL_UNSIGNED_SHORT, NULL);
//
//
//
//
//	// Part 5: Clean up
//	glBindVertexArray(0); // Unbind the VAO
//	shdrpgms[shd_ref].UnUse(); // Uninstall the shader program
//}


/**************************************************************************************
* @brief				Creates an OpenGLObject based on parameters set on this Box_Model
*
* @param color			Color <R,G,B>
* @return OpenGLObject  
***************************************************************************************/
OpenGLObject::OpenGLModel OpenGLObject::Box_Model(int ID, glm::vec3 color, int textureInput)
{
	struct Vertex {
		glm::vec2 position;        // Vertex position
		glm::vec3 color;           // Vertex color
		glm::vec2 textureCoord;    // Texture coordinates
	};

	// Define the vertices of a textured square
	std::vector<Vertex> vertices
	{
		 { glm::vec2(0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f) }, // Bottom-right
		 { glm::vec2(0.5f, 0.5f),  glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f) }, // Top-right
		 { glm::vec2(-0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) }, // Top-left
		 { glm::vec2(-0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f) }  // Bottom-left
	};

	OpenGLModel mdl;


	// Create and bind a buffer for vertex data
	GLuint vbo_hdl;
	glCreateBuffers(1, &vbo_hdl);

	// Allocate and fill data store for vertices
	glNamedBufferStorage(vbo_hdl, sizeof(Vertex) * vertices.size(), vertices.data(), GL_DYNAMIC_STORAGE_BIT);

	// Create and bind a vertex array object (VAO)
	GLuint vaoid;
	glCreateVertexArrays(1, &vaoid);

	// Vertex position attribute
	glEnableVertexArrayAttrib(vaoid, 0);
	glVertexArrayVertexBuffer(vaoid, 0, vbo_hdl, offsetof(Vertex, position), sizeof(Vertex));
	glVertexArrayAttribFormat(vaoid, 0, 2, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(vaoid, 0, 0);

	// Vertex color attribute
	glEnableVertexArrayAttrib(vaoid, 1);
	glVertexArrayVertexBuffer(vaoid, 1, vbo_hdl, offsetof(Vertex, color), sizeof(Vertex));
	glVertexArrayAttribFormat(vaoid, 1, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(vaoid, 1, 1);

	// Texture coordinates attribute
	glEnableVertexArrayAttrib(vaoid, 2);
	glVertexArrayVertexBuffer(vaoid, 2, vbo_hdl, offsetof(Vertex, textureCoord), sizeof(Vertex));
	glVertexArrayAttribFormat(vaoid, 2, 2, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(vaoid, 2, 2);

	// Bind the texture before rendering
	//glBindTexture(GL_TEXTURE_2D, textureInput);

	// Set up index buffer for rendering
	std::array<GLushort, 4> idx_vtx = { 0, 1, 2, 3 };
	GLuint ebo_hdl;
	glCreateBuffers(1, &ebo_hdl);
	glNamedBufferStorage(ebo_hdl, sizeof(GLushort) * idx_vtx.size(), idx_vtx.data(), GL_DYNAMIC_STORAGE_BIT);
	glVertexArrayElementBuffer(vaoid, ebo_hdl);

	// Store information in the model structure
	mdl.vaoid = vaoid;
	mdl.primitive_type = GL_TRIANGLE_FAN; // Use GL_TRIANGLE_FAN for a square
	mdl.draw_cnt = idx_vtx.size();
	mdl.primitive_cnt = vertices.size();
	mdl.ModelID = ID;
	mdl.texture = textureInput;


	return mdl;
}


/**************************************************************************
* @brief		Updates each OpenGLObject with Movement, Scale rotation.
*				Option for rotation has been added.
* 
* @param float  Acceleration of x-Axis
* @param float  Acceleration of y-Axis
* @param float  Scale on both X and Y axes. (Might need to change)
* @param float  Angle Rotation Speed
* @param bool   Boolean for Rotation Enable or Disable
* @return void
*************************************************************************/
void OpenGLObject::Update(float newX, float newY, float scaleX, float scaleY, float newAngle , bool enRot )
{
	//std::cout << "Object Update\n";
	// Compute the angular displacement in radians

//	angleDisplacment = aDisp;
	
	
	//Scale the model based on float variable.
	scaleModel = glm::vec2(scaleX, scaleY);


	// Increase the position based on the xSpeed of the user.
	// i.e if the user acceleration is 0, then speed increase
	// of xAccel is 0, and position would not change.
	position = glm::vec2(newX, newY);


	if (enRot == true)
	{
		angleDisplacment = newAngle;
	}
	
	if (angleDisplacment >= 360.0f || angleDisplacment <= -360.0f)
		angleDisplacment = 0.0f;

	

// Compute the scale matrix
	glm::mat3 Scale = glm::mat3(
		scaleModel.x, 0.0f, 0.0f,
		0.0f, scaleModel.y, 0.0f,
		0.0f, 0.0f, 1.0f
	);

	// Compute the rotation matrix
	glm::mat3 Rotation = glm::mat3(
		cosf(glm::radians(angleDisplacment)), -sinf(glm::radians(angleDisplacment)), 0.0f,
		sinf(glm::radians(angleDisplacment)), cosf(glm::radians(angleDisplacment)), 0.0f,
		0.0f, 0.0f, 1.0f
	);

	// Compute the translation matrix
	glm::mat3 Translation = glm::mat3(
		1.0f, 0.0f, position.x,
		0.0f, 1.0f, position.y,
		0.0f, 0.0f, 1.0f
	);


	// Compute the scaling matrix to map from world coordinates to NDC coordinates
	glm::mat3 ScaleToWorldToNDC = glm::mat3(
		1.0f / (1920 / 2), 0.0f, 0.0f,
		0.0f, 1.0f / (1080 / 2), 0.0f,
		0.0f, 0.0f, 1.0f
	);


	// Compute the model-to-world-to-NDC transformation matrix
	model_To_NDC_xform = ScaleToWorldToNDC * glm::transpose(Translation) * glm::transpose(Rotation)  * glm::transpose(Scale);

}


/**************************************************************************
* @brief		Draws the OpenGLObject.
*				
* @param  none
* @return void
*************************************************************************/
void OpenGLObject::Draw() const
{
	//texture object is to use texture image unit 6


	int tex{};
	switch (TagID)
	{
	case 0:
		tex = bgTexture;
		break;
	case 1:
		tex = firstTexture;
		break;
	case 2:
		tex = secondTexture;
		break;
	default:
		break;
	}

	glBindTextureUnit(6, tex);

	shdrpgms[shd_ref].Use(); // Install the shader program




	shdrpgms[shd_ref].SetUniform("uTex2d", 6);
	// Part 2: Bind object's VAO handle
	glBindVertexArray(models[mdl_ref].vaoid); // Bind object's VAO handle

	// Part 3: Copy object's 3x3 model-to-NDC matrix to vertex shader
	GLint uniform_var_loc1 = glGetUniformLocation(shdrpgms[shd_ref].GetHandle(), "uModel_to_NDC");
	if (uniform_var_loc1 >= 0) {
		glUniformMatrix3fv(uniform_var_loc1, 1, GL_FALSE, glm::value_ptr(OpenGLObject::model_To_NDC_xform));
	}
	else {
		std::cout << "Uniform variable doesn't exist!!!" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	// Part 4: Render using glDrawElements or glDrawArrays



	glDrawElements(
		models[mdl_ref].primitive_type,
		models[mdl_ref].draw_cnt,
		GL_UNSIGNED_SHORT, NULL);




	// Part 5: Clean up
	glBindVertexArray(0); // Unbind the VAO
	shdrpgms[shd_ref].UnUse(); // Uninstall the shader program
}

void OpenGLObject::Cleanup()
{



	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(ShaderProgram);
}




void OpenGLObject::OpenGLModel::setup_TextureVAO()
{
	std::vector<VAO_Object> vao_value;
	vao_value.reserve(4);

	VAO_Object setup_var;

	//top left
	setup_var.setTextureValue(-1.0f, 1.0f, 1.f, 0.f, 1.f);
	setup_var.setTexture(0.f, 1.f);
	vao_value.emplace_back(setup_var);

	//bottom left
	setup_var.setTextureValue(-1.0f, -1.0f, 1.f, 0.f, 0.f);
	setup_var.setTexture(0.f, 0.f);
	vao_value.emplace_back(setup_var);

	//top right
	setup_var.setTextureValue(1.0f, -1.0f, 1.f, 1.f, 0.f);
	setup_var.setTexture(1.f, 0.f);
	vao_value.emplace_back(setup_var);


	//bottom right
	setup_var.setTextureValue(1.0f, 1.0f, 0.f, 0.f, 1.f);
	setup_var.setTexture(1.f, 1.f);
	vao_value.emplace_back(setup_var);





	// transfer vertex position and color attributes to VBO
	GLuint vbo_hdl;
	glCreateBuffers(1, &vbo_hdl);

	glNamedBufferStorage(vbo_hdl, sizeof(OpenGLModel::VAO_Object) * vao_value.size(), vao_value.data(), GL_DYNAMIC_STORAGE_BIT);

	GLint max_vtx_attribs;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &max_vtx_attribs);
	std::cout << "Maximum vertex attributes: " << max_vtx_attribs << '\n';

	GLint max_vtx_binding_buffer;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIB_BINDINGS, &max_vtx_binding_buffer);
	std::cout << "Maximum vertex buffer bindings: " << max_vtx_binding_buffer << '\n';

	//encapsulate information about contents of VBO and VBO handle
	// to another object called VAO
	glCreateVertexArrays(1, &vaoid);


	//enable use of vertex position
	glEnableVertexArrayAttrib(vaoid, 0);

	//vertex buffer binding point 3
	glVertexArrayVertexBuffer(vaoid, 3, vbo_hdl, 0, sizeof(OpenGLModel::VAO_Object)/*number of spaces each iteration*/);

	//position
	// vao position, we use vertex attribute index 0
	//and vertex buffer binding point 3
	//offsetof (offset based on on data type, and member variable, offset will be automatically calculated)
	glVertexArrayAttribFormat(vaoid, 0, 2/*size of data*/, GL_FLOAT, GL_FALSE, offsetof(OpenGLModel::VAO_Object/*structure type*/, OpenGLModel::VAO_Object::position/*value name*/));
	glVertexArrayAttribBinding(vaoid, 0, 3);


	//enable use of color value
	glEnableVertexArrayAttrib(vaoid, 1);

	// vao color, we use vertex attribute index 1
	// and vertex buffer binding point 3
	glVertexArrayAttribFormat(vaoid, 1, 3/*size of data*/, GL_FLOAT, GL_FALSE, offsetof(OpenGLModel::VAO_Object/*structure type*/, OpenGLModel::VAO_Object::color/*value name*/));
	glVertexArrayAttribBinding(vaoid, 1, 3);

	//enable use of texture vertex
	glEnableVertexArrayAttrib(vaoid, 2);

	// vao color, we use vertex attribute index 1
	// and vertex buffer binding point 3
	glVertexArrayAttribFormat(vaoid, 2, 2/*size of data*/, GL_FLOAT, GL_FALSE, offsetof(OpenGLModel::VAO_Object/*structure type*/, OpenGLModel::VAO_Object::texture/*value name*/));
	glVertexArrayAttribBinding(vaoid, 2, 3);

	// Set the primitive Type of the primitive to Triangle Strip
	primitive_type = GL_TRIANGLE_STRIP;

	// Define two triangles primitives which make up a square
	std::array<GLushort, 4> idx_vtx
	{
		0, 1, 2, 3
	};

	// Set the index element count to the vertex size
	idx_elem_cnt = idx_vtx.size();

	// Ebo handlers
	GLuint ebo_hdl;
	glCreateBuffers(1, &ebo_hdl);
	glNamedBufferStorage(ebo_hdl, sizeof(GLushort) * idx_elem_cnt, reinterpret_cast<GLvoid*>(idx_vtx.data()), GL_DYNAMIC_STORAGE_BIT);
	glVertexArrayElementBuffer(vaoid, ebo_hdl);
	glBindVertexArray(0);


}









void OpenGLObject::init_shdrpgms_cont(VectorPairStrStr const& vpss) {
	for (auto const& x : vpss) {
		std::vector<std::pair<GLenum, std::string>> shdr_files;
		shdr_files.emplace_back(std::make_pair(GL_VERTEX_SHADER, x.first));
		shdr_files.emplace_back(std::make_pair(GL_FRAGMENT_SHADER, x.second));
		OpenGLShader shdr_pgm;
		shdr_pgm.CompileLinkValidate(shdr_files);
		// insert shader program into container
		shdrpgms.emplace_back(shdr_pgm);
	}
}



void OpenGLObject::InitObjects(float userInput_x, float userInput_y, float userInput_sizeX,
							   float userInput_sizeY, float userInput_angleDisplacement, 
							   float userInput_angleSpeed)
{

	mdl_ref = 0;
	shd_ref = 0;

	position.x = userInput_x;
	position.y = userInput_y;

	using glm::radians;

	scaleModel.x = userInput_sizeX;
	scaleModel.y = userInput_sizeY;

	angleDisplacment = userInput_angleDisplacement;
	angleSpeed = userInput_angleSpeed;

	glm::mat3 Translate = glm::mat3
	{
		1, 0, 0,
		0, 1, 0,
		 position.x,  position.y, 1
	};

	glm::mat3 Rotation = glm::mat3
	{
		cosf(radians(angleDisplacment)), sinf(radians(angleDisplacment)) , 0,
		-sinf(radians(angleDisplacment)),  cosf(radians(angleDisplacment)) , 0,
		0, 0, 1
	};

	glm::mat3 Scale = glm::mat3
	{
		scaleModel.x, 0, 0,
		0, scaleModel.y, 0,
		0, 0, 1
	};

	float scaleX = 2.0f / windowSize.first;
	float scaleY = 2.0f / windowSize.second;

	glm::mat3 ScaleToWorldToNDC = glm::mat3
	{
		scaleX, 0, 0,
		0, scaleY, 0,
		0, 0, 1
	};
	// Instead of doing transpose, you can do what OpenGL matrix does:
	// Row-Major Order:				Column Major Order;
	//	   x0 y0 z0						 x0 x1 x2
	//	   x1 y1 z1						 y0 y1 y2
	//	   x2 y2 z2						 z0 z1 z2
	model_To_NDC_xform = ScaleToWorldToNDC* Translate * Rotation * Scale;

}


void OpenGLObject::DrawCollisionBox(float minX, float minY, float maxX, float maxY)
{

	float height = maxY - minY;
	float width = maxX - minX;


	float sX = minX - (width) / 2;
	float bX = maxX - (width) / 2;
	float sY = minY - (height) / 2;
	float bY = maxY - (height) / 2;



	// Define the vertices of the collision box in local coordinates (before transformation)
	glm::vec2 localVertices[4] = {
		//glm::vec2(sX, sY),
		//glm::vec2(bX, sY),
		//glm::vec2(bX, bY),
		//glm::vec2(sX, bY)

		glm::vec2(sX, sY),
		glm::vec2(bX, sY),
		glm::vec2(bX, bY),
		glm::vec2(sX, bY)



	};	//

	// Apply the transformation matrix to the local vertices
	glm::vec2 transformedVertices[4];
	for (int i = 0; i < 4; ++i) {
		transformedVertices[i] = glm::vec2(model_To_NDC_xform * glm::vec3(localVertices[i], 1.0f));
	}

	// Draw the transformed collision box
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 4; ++i) {
		glVertex2f(transformedVertices[i].x, transformedVertices[i].y);
	}
	glEnd();

}


/*=======================================================================================================================*/
/*=======================================================================================================================*/
/*======================================================TEXTURE==========================================================*/
/*=======================================================================================================================*/
/*=======================================================================================================================*/
/*=======================================================================================================================*/


int OpenGLObject::Setup_TextureObject(std::string filePath)
{
	GLuint textureObj_Handler;

	int width, height, channels;
	unsigned char* image = stbi_load(filePath.c_str(), &width, &height, &channels, STBI_rgb_alpha);

	if (!image)
	{
		std::cout << "Failed to load texture: " << filePath << std::endl;
		return 0; // Return 0 to indicate failure
	}

	glCreateTextures(GL_TEXTURE_2D, 1, &textureObj_Handler);
	glTextureStorage2D(textureObj_Handler, 1, GL_RGBA8, width, height);
	glTextureSubImage2D(textureObj_Handler, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);

	stbi_image_free(image); // Free the image data after it's uploaded to OpenGL

	return textureObj_Handler;
}


void OpenGLObject::OpenGLModel::VAO_Object::setTextureValue(float x, float y, float r, float g, float b)
{
	position.x = x;
	position.y = y;

	// Similarly, Color ...
	color.r = r;
	color.g = g;
	color.b = b;

}

void OpenGLObject::OpenGLModel::VAO_Object::setTexture(float s, float t)
{
	texture.s = s;
	texture.t = t;

}



/*=======================================================================================================================*/
/*=======================================================================================================================*/
/*===================================================OPENGL CAMERA=======================================================*/
/*=======================================================================================================================*/
/*=======================================================================================================================*/
/*=======================================================================================================================*/