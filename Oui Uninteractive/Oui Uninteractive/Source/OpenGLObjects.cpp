/**************************************************************************
 * @file OpenGLObjects.cpp
 * @author 	TAN Angus Yit Hoe
 * @co-author CHEAH Tristan Tze Hong, HWANG Jing Rui, Austin, LOW Wang Chun, Mark, CHAN Aaron Jun Xiang, QUEK Cheng Kwang Emery
 * @par DP email: tan.a@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 29-09-2023
 * @brief 
 * This file compute the logic behind the box model and encapsulates the
 * shader programs into a vector to store it, and allows for usage of them
 * for Translation, Scale, Rotation, and setting up textures.
 
 *************************************************************************/

#include <GL/glew.h> // for access to OpenGL API declarations  (PUT THIS ON TOP OR ELSE HAVE ERROR)
#include <GLFW/glfw3.h>
#include <OpenGLObjects.h>
#include <glm/glm.hpp>
#include <OpenGLApplication.h>
#include <iostream>
#include <array>
#include <sstream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <RandomUtilities.h>
#include <GameStateManager.h>
#include <stb_image.h>


unsigned int OpenGLObject::mdl_ref = 0; // Define and initialize mdl_ref
unsigned int OpenGLObject::shd_ref = 0; // Define and initialize shd_ref


// Vector for shdrpgms
std::vector<OpenGLShader> OpenGLObject::shdrpgms;

// Vector for models
std::vector<OpenGLObject::OpenGLModel> OpenGLObject::models;
#ifdef _DEBUG
GLuint OpenGLObject::ShaderProgram{};
#endif

// VAO and VBO initializiation
GLuint OpenGLObject::VAO = 0;
GLuint OpenGLObject::VBO = 0;

// Global Variable to set it, and then use it eventually.
int bgTexture, firstTexture, secondTexture;




/**************************************************************************
* @brief		Initialize OpenGLObject that does Model Creation for future
*				Drawing Capabilities and Shader Emplacement.
* 
* @WARNING _DEBUG debug draws a model of square.
* 
* @param  none
* @return void
*************************************************************************/
void OpenGLObject::Init()
{
#ifdef _DEBUG
	std::cout << "OpenGLObject::Init()\n\n";
#endif // _DEBUG

	// Create file name
	VectorPairStrStr fileName{
		std::make_pair<std::string, std::string>
		("../shaders/Oui_Uninteractive.vert", "../shaders/Oui_Uninteractive.frag")
	};

	// Initialize the Shader Program
	init_shdrpgms_cont(fileName);


	firstTexture = OpenGLObject::Setup_TextureObject("../texture/pepethefrog.png");
	secondTexture = OpenGLObject::Setup_TextureObject("../texture/pepe.jpg");
	bgTexture = OpenGLObject::Setup_TextureObject("../texture/background.jpg");

	// Emplace model to the model vector
	models.emplace_back(OpenGLObject::Box_Model(color));

	
#ifdef _DEBUG // This is to Make sure that the graphics Pipeline WORKS as intended
			  // AND HAS TO BE UNCOMMENTED TO CHANGE STATES.!
			  // Draws a Box with color.
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
#endif
}


/**************************************************************************************
* @brief				Creates an OpenGLObject based on parameters set on this Box_Model
*
* @param color			Color <R,G,B>
* @return OpenGLObject  
***************************************************************************************/
OpenGLObject::OpenGLModel OpenGLObject::Box_Model(glm::vec3 color)
{
	struct Vertex {
		glm::vec2 position;        // Vertex position
		glm::vec3 color;           // Vertex color
		glm::vec2 textureCoord;    // Texture coordinates
	};

	// Define the vertices of a textured square
	std::vector<Vertex> vertices
	{
		 { glm::vec2(0.5f,  -0.5f), color, glm::vec2(1.0f, 1.0f) }, // Bottom-right
		 { glm::vec2(0.5f,   0.5f), color, glm::vec2(1.0f, 0.0f) }, // Top-right
		 { glm::vec2(-0.5f,  0.5f), color, glm::vec2(0.0f, 0.0f) }, // Top-left
		 { glm::vec2(-0.5f, -0.5f), color, glm::vec2(0.0f, 1.0f) }  // Bottom-left
	};

	// Create Model.
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

	// Set up index buffer for rendering
	std::array<GLushort, 4> idx_vtx = { 0, 1, 2, 3 };
	GLuint ebo_hdl;
	glCreateBuffers(1, &ebo_hdl);
	glNamedBufferStorage(ebo_hdl, sizeof(GLushort) * idx_vtx.size(), idx_vtx.data(), GL_DYNAMIC_STORAGE_BIT);
	glVertexArrayElementBuffer(vaoid, ebo_hdl);

	// Store information in the model structure
	mdl.vaoid = vaoid;
	mdl.primitive_type = GL_TRIANGLE_FAN; // Use GL_TRIANGLE_FAN for a square
	mdl.draw_cnt = static_cast<GLsizei>(idx_vtx.size());
	mdl.primitive_cnt = vertices.size();


	// return model
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

	
	
	//Scale the model based on float variable.
	scaleModel = glm::vec2(scaleX, scaleY);


	// Increase the position based on the xSpeed of the user.
	// i.e if the user acceleration is 0, then speed increase
	// of xAccel is 0, and position would not change.
	position = glm::vec2(newX, newY);

	// Boolean from the user to set if rotation is yes or no.
	if (enRot == true)
	{
		angleDisplacment = newAngle;
	}
	// in case user does not set, angleDisplacement will be in the range of
	// 0 ~ 360 || -360 ~ 0
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
		1.0f / (windowSize.first / 2), 0.0f, 0.0f,
		0.0f, 1.0f / (windowSize.second / 2), 0.0f,
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

	// Bind Texture to 6.
	glBindTextureUnit(6, tex);

	// Install the shader program
	shdrpgms[shd_ref].Use(); 

	// In Shader Program [uTex2d] is the texture uniform position.
	// set uniform uTex2d to #6.
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

	// Draw the Elements that are contained in the primitive
	glDrawElements(
		models[mdl_ref].primitive_type,
		models[mdl_ref].draw_cnt,
		GL_UNSIGNED_SHORT, nullptr);

	// Part 5: Clean up
	glBindVertexArray(0); // Unbind the VAO
	shdrpgms[shd_ref].UnUse(); // Uninstall the shader program
}

/**************************************************************************
* @brief		 Cleanup the Object Creation.
* @param  none
* @return void
*************************************************************************/
void OpenGLObject::Cleanup()
{
	// Cleanup the VAO, VBO and Shader Program
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
#ifdef _DEBUG
	glDeleteProgram(ShaderProgram);
#endif
}

/**************************************************************************
* @brief		Initialize the Shaders for Graphics Pipeline for Object to
*				Render and/or Translate their objects.
*
* @param  VPSS  std::vector <std::pair<std::string, std::string>>
* @return void
*************************************************************************/
void OpenGLObject::init_shdrpgms_cont(VectorPairStrStr const& vpss) {
	for (auto const& x : vpss) {
		// Create Vector for pair of Enum and String
		std::vector<std::pair<GLenum, std::string>> shdr_files;
		// Emplace back into the shdr_files vector
		shdr_files.emplace_back(std::make_pair(GL_VERTEX_SHADER, x.first));
		shdr_files.emplace_back(std::make_pair(GL_FRAGMENT_SHADER, x.second));
		// Create Shader
		OpenGLShader shdr_pgm;
		// Validate the shader program (shdr_Files).
		shdr_pgm.CompileLinkValidate(shdr_files);
		// insert shader program into container
		shdrpgms.emplace_back(shdr_pgm);
	}
}


/**************************************************************************
* @brief		Initialize the Shaders for Graphics Pipeline for Object to
*				Render and/or Translate their objects.
*
* @param  float User Input X coordinate
* @param  float User Input Y Coordinate
* @param  float User Input Size X (Scale X Axis)
* @param  float User Input Size Y (Scale Y Axis)
* @param  float User Input Angle Displacement (Anti Clockwise)
* @param  float User Input Angle Speed (Speed of rotation)
* 
* @return void
*************************************************************************/
void OpenGLObject::InitObjects(float userInput_x, float userInput_y, float userInput_sizeX,
							   float userInput_sizeY, float userInput_angleDisplacement, 
							   float userInput_angleSpeed)
{

	// Initialize the object of model and shader reference to 0
	mdl_ref = 0;
	shd_ref = 0;

	// set position x and y to the user input
	position.x = userInput_x;
	position.y = userInput_y;

	using glm::radians;

	// set scale to user input
	scaleModel.x = userInput_sizeX;
	scaleModel.y = userInput_sizeY;

	// set Angle parameters to user input
	angleDisplacment = userInput_angleDisplacement;
	angleSpeed = userInput_angleSpeed;

	// matrix for translate
	glm::mat3 Translate = glm::mat3
	{
		1, 0, 0,
		0, 1, 0,
		 position.x,  position.y, 1
	};

	// matrix for rotation
	glm::mat3 Rotation = glm::mat3
	{
		cosf(radians(angleDisplacment)), sinf(radians(angleDisplacment)) , 0,
		-sinf(radians(angleDisplacment)),  cosf(radians(angleDisplacment)) , 0,
		0, 0, 1
	};

	// matrix for scale
	glm::mat3 Scale = glm::mat3
	{
		scaleModel.x, 0, 0,
		0, scaleModel.y, 0,
		0, 0, 1
	};

	// set the scale for the World to NDC coords.
	float scaleX = 2.0f / windowSize.first;
	float scaleY = 2.0f / windowSize.second;

	// Scale To World NDC-coordinates matrix
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


/**************************************************************************
* @brief		Draws a Debug Collision Box (AABB)
*
* @param  Vector2D	Minimum Coordinates of AABB
* @param  Vector2D  Maximum Coordinates of AABB
*
* @return void
*************************************************************************/
void OpenGLObject::DrawCollisionBox(Vector2D min, Vector2D max)
{
	// get the points of the AABB
	float sX = min.x;
	float bX = max.x;
	float sY = min.y;
	float bY = max.y;

	using glm::radians;
	
	// set angle displacement to 0, as we do not need to rotate
	angleDisplacment = 0;

	// Set Scale to World NDC
	glm::mat3 ScaleToWorldToNDC = glm::mat3(
		1.0f / (windowSize.first / 2), 0.0f, 0.0f,
		0.0f, 1.0f / (windowSize.second / 2), 0.0f,
		0.0f, 0.0f, 1.0f
	);
	// Instead of doing transpose, you can do what OpenGL matrix does:
	// Row-Major Order:				Column Major Order;
	//	   x0 y0 z0						 x0 x1 x2
	//	   x1 y1 z1						 y0 y1 y2
	//	   x2 y2 z2						 z0 z1 z2
	model_To_NDC_xform = ScaleToWorldToNDC /** Translate*/;

	// Define the vertices of the collision box in local coordinates (before transformation)
	glm::vec2 localVertices[4] = {

		glm::vec2(sX, sY),
		glm::vec2(bX, sY),
		glm::vec2(bX, bY),
		glm::vec2(sX, bY)

	};

	// Apply the transformation matrix to the local vertices
	glm::vec2 transformedVertices[4];
	for (int i = 0; i < 4; ++i) {
		// set the vertices
		transformedVertices[i] = glm::vec2(model_To_NDC_xform * glm::vec3(localVertices[i], 1.0f));
	}

	// Draw the transformed collision box
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 4; ++i) {
		// set the vertex and draw the lines, based on GL_LINE_LOOP
		glVertex2f(transformedVertices[i].x, transformedVertices[i].y);
	}
	// End the loop
	glEnd();

}


/*=======================================================================================================================*/
/*=======================================================================================================================*/
/*======================================================TEXTURE==========================================================*/
/*=======================================================================================================================*/
/*=======================================================================================================================*/
/*=======================================================================================================================*/

/**************************************************************************
* @brief		Setup Texture Object into the parameters (int)
*
* @param  std::string filePath of the Texture.
* @return int	Texture Handler
*************************************************************************/
int OpenGLObject::Setup_TextureObject(std::string filePath)
{
	// Create a int variable for texture Object
	GLuint textureObj_Handler;

	// width, height and channels for the image
	int width, height, channels;
	// Load the image into *image
	unsigned char* image = stbi_load(filePath.c_str(), &width, &height, &channels, STBI_rgb_alpha);

	// If no image is generated, failed.
	if (!image)
	{
		std::cout << "Failed to load texture: " << filePath << std::endl;
		return 0; // Return 0 to indicate failure
	}

	// Create Texture into Texture2D, reference to TextureObjHandler
	glCreateTextures(GL_TEXTURE_2D, 1, &textureObj_Handler);
	// Store the data into Storage2D
	glTextureStorage2D(textureObj_Handler, 1, GL_RGBA8, width, height);
	// Store the sub data into the sub Image
	glTextureSubImage2D(textureObj_Handler, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);

	// Free the image data after it's uploaded to OpenGL
	stbi_image_free(image); 

	// Return int value of a texture.
	return textureObj_Handler;
}


/**************************************************************************
* @brief		set Texture Positon, Color
*
* @param  float x axis of texture
* @param  float y axis of texture
* @param  float r Red Color Value
* @param  float g Green Color Value
* @param  float b Blue Color Value
* 
* @return void
*************************************************************************/
void OpenGLObject::OpenGLModel::VAO_Object::setTextureValue(float x, float y, float r, float g, float b)
{
	// Set Position X and Y
	position.x = x;
	position.y = y;

	// Similarly, Color ...
	color.r = r;
	color.g = g;
	color.b = b;

}

/**************************************************************************
* @brief		set Texture Positon, Color
*
* @param  float s axis of texture
* @param  float t axis of texture
*
* @return void
*************************************************************************/
void OpenGLObject::OpenGLModel::VAO_Object::setTexture(float s, float t)
{
	// Set Texture S and T coordinates.
	texture.s = s;
	texture.t = t;

}

/*=======================================================================================================================*/
/*=======================================================================================================================*/
/*===================================================OPENGL CAMERA=======================================================*/
/*=======================================================================================================================*/
/*=======================================================================================================================*/
/*=======================================================================================================================*/