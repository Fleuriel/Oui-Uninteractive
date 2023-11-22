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
#include <AssetManager.h>
#include <RandomUtilities.h>
#include <GameStateManager.h>
#include <stb_image.h>
#include "Editor.h"


unsigned int OpenGLObject::mdl_ref = 0; // Define and initialize mdl_ref
unsigned int OpenGLObject::shd_ref = 0; // Define and initialize shd_ref

OpenGLObject OpenGLObject::cameraTranslator(9);
OpenGLObject::Camera2D OpenGLObject::cameraObject;
glm::mat4 OpenGLObject::fontProjection;

// Vector for shdrpgms
std::vector<OpenGLShader> OpenGLObject::shdrpgms;

// Vector for models
std::vector<OpenGLObject::OpenGLModel> OpenGLObject::models;

// VAO and VBO initializiation
GLuint OpenGLObject::VAO = 0;
GLuint OpenGLObject::VBO = 0;
GLuint OpenGLObject::FBO = 0;
GLuint OpenGLObject::RBO = 0;
GLuint OpenGLObject::FrameTexture = 0;

extern int spritecol;



/**************************************************************************
* @brief  Initialize OpenGLObject that does Model Creation for future
*		  Drawing Capabilities and Shader Emplacement.
*
*
*
* @param  none
* @return void
*************************************************************************/
void OpenGLObject::Initialize() {
#ifdef _DEBUG
	std::cout << "OpenGLObject::Init()\n\n";
#endif // _DEBUG

	// Initialize Shaders for game.
	InitShaders();
	// Fonts
	InitFont();

	// Emplace model to the model vector
	models.emplace_back(OpenGLObject::Box_Model(color));


	cameraTranslator.InitObjects();

	OpenGLObject::cameraObject.Init(windowNew, &cameraTranslator);




	const GLint WIDTH = windowSize.first;
	const GLint HEIGHT = windowSize.second;

	// Generate the framebuffer
	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	// Generate and bind the texture
	glGenTextures(1, &FrameTexture);
	glBindTexture(GL_TEXTURE_2D, FrameTexture);

	// Configure the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Attach the texture to the framebuffer
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, FrameTexture, 0);

	// Generate and bind the renderbuffer
	glGenRenderbuffers(1, &RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, RBO);

	// Configure the renderbuffer
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WIDTH, HEIGHT);

	// Attach the renderbuffer to the framebuffer
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

	// Check if the framebuffer is complete
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!\n";

	// Unbind the framebuffer, texture, and renderbuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);




}


/**************************************************************************************
* @brief  Creates an OpenGLObject based on parameters set on this Box_Model
*
* @param  color	  Color <R,G,B>
* @return OpenGLObject
***************************************************************************************/
OpenGLObject::OpenGLModel OpenGLObject::Box_Model(glm::vec3 color) {
	struct Vertex {
		glm::vec2 position;        // Vertex position
		glm::vec3 color;           // Vertex color
		glm::vec2 textureCoord;    // Texture coordinates
	};

	// Define the vertices of a textured square
	std::vector<Vertex> vertices{
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
* @brief  Updates each OpenGLObject with Movement, Scale rotation.
*		  Option for rotation has been added.
*
* @param  float  Acceleration of x-Axis
* @param  float  Acceleration of y-Axis
* @param  float  Scale on both X and Y axes. (Might need to change)
* @param  float  Angle Rotation Speed
* @param  bool   Boolean for Rotation Enable or Disable
* @return void
*************************************************************************/
void OpenGLObject::Update(float newX, float newY, float scaleX, float scaleY, float newAngle, bool enRot) {
	//std::cout << "Object Update\n";
	// Compute the angular displacement in radians


	//Scale the model based on float variable.
	scaleModel = glm::vec2(scaleX, scaleY);


	position = glm::vec2(newX, newY);

	// Boolean from the user to set if rotation is yes or no.
	if (enRot == true) {
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
		cosf(glm::radians(angleDisplacment)), sinf(glm::radians(angleDisplacment)), 0.0f,
		-sinf(glm::radians(angleDisplacment)), cosf(glm::radians(angleDisplacment)), 0.0f,
		0.0f, 0.0f, 1.0f
	);

	// Compute the translation matrix
	glm::mat3 Translation = glm::mat3(
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		position.x, position.y, 1.0f
	);


	// Compute the scaling matrix to map from world coordinates to NDC coordinates
	glm::mat3 ScaleToWorldToNDC = glm::mat3(
		2.0f / (Editor::gameWindowSize.first), 0.0f, 0.0f,
		0.0f, 2.0f / (Editor::gameWindowSize.second), 0.0f,
		0.0f, 0.0f, 1.0f
	);



	// Compute the model-to-world-to-NDC transformation matrix
	model_To_NDC_xform = cameraObject.World_to_NDC_xform * Translation * Rotation * Scale;

}
/**************************************************************************
* @brief  Updates each OpenGLObject with Movement, Scale rotation.
*		  Option for rotation has been added.
*
* @param  Matrix3x3  scale
* @param  Matrix3x3  rotate
* @param  Matrix3x3  translate
* @return void
*************************************************************************/
void OpenGLObject::Update(Matrix3x3 scale, Matrix3x3 rotate, Matrix3x3 translate) {
	// 0 ~ 360 || -360 ~ 0
	if (angleDisplacment >= 360.0f || angleDisplacment <= -360.0f)
		angleDisplacment = 0.0f;


	// Compute the scale matrix
	glm::mat3 Scale = glm::mat3(
		scale.m00, 0.0f, 0.0f,
		0.0f, scale.m11, 0.0f,
		0.0f, 0.0f, 1.0f
	);

	// Compute the rotation matrix
	glm::mat3 Rotation = glm::mat3(
		rotate.m00, rotate.m01, 0.0f,
		rotate.m10, rotate.m11, 0.0f,
		0.0f, 0.0f, 1.0f
	);

	// Compute the translation matrix
	glm::mat3 Translation = glm::mat3(
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		translate.m20, translate.m21, 1.0f
	);


	// Compute the scaling matrix to map from world coordinates to NDC coordinates
	glm::mat3 ScaleToWorldToNDC = glm::mat3(
		2.0f / (Editor::gameWindowSize.first), 0.0f, 0.0f,
		0.0f, 2.0f / (Editor::gameWindowSize.second), 0.0f,
		0.0f, 0.0f, 1.0f
	);


	// Compute the model-to-world-to-NDC transformation matrix
	model_To_NDC_xform = cameraObject.World_to_NDC_xform * Translation * Rotation * Scale;

}


/**************************************************************************
* @brief  Draws the OpenGLObject.
*
* @param  none
* @return void
*************************************************************************/
void OpenGLObject::Draw(std::string type, bool spriteUsage, Vec2 vel) const {
	//texture object is to use texture image unit 6
	int tex{};
	int shaderNumber{ static_cast<int>(SHADER_ORDER::MODEL) };

	std::string movement = (vel.x || vel.y) ? "_Walk" : "_Idle";

	if (spriteUsage) {
		shaderNumber = static_cast<int>(SHADER_ORDER::SPRITES);
		tex = assetManager.GetSprite(type + movement).GetTexture();
	}
	if (type == "Weapon") {
		tex = assetManager.GetTexture("KnifeSprite");
	}
	if (type == "Camera") {
		shaderNumber = static_cast<int>(SHADER_ORDER::CAMERA);
	}

	// Bind Texture to 6.
	glBindTextureUnit(6, tex);

	// Install the shader program
	shdrpgms[shaderNumber].Use();

	// In Shader Program [uTex2d] is the texture uniform position.
	// set uniform uTex2d to #6.
	if (shaderNumber == static_cast<int>(SHADER_ORDER::MODEL)) {
		shdrpgms[static_cast<int>(SHADER_ORDER::MODEL)].SetUniform("uTex2d", 6);
	}

	if (shaderNumber == static_cast<int>(SHADER_ORDER::SPRITES)) {
		shdrpgms[static_cast<int>(SHADER_ORDER::SPRITES)].SetUniform("uTex2d", 6);

		int spriterow{};

		if (type == "Player"){
			double mouseX; // = io.MousePos.x;
			double mouseY; // = io.MousePos.y;
			glfwGetCursorPos(windowNew, &mouseX, &mouseY);
			OpenGLObject::FrameBufferMouseCoords(windowNew, &mouseX, &mouseY, OpenGLObject::cameraObject);
			
			Vec2 playerPos = GET_COMPONENT(objectFactory->GetGameObjectByName("JSONPlayer"), Transform, ComponentType::TRANSFORM)->position;

	

			std::cout << "Mouse X : " << mouseX << "\t";
			std::cout << "Mouse Y : " << mouseY << "\t";
			std::cout << playerPos.x << '\t' << playerPos.y << '\t';
			Vec2 vec = { static_cast<float>(mouseX) - playerPos.x , static_cast<float>(mouseY) - playerPos.y };

			spriterow = ((vec.x>0)?2:3);
		}
		else {
			if (movement == "_Walk")
				spriterow = (((vel.x > 0) ? vel.x : -vel.x) < ((vel.y > 0) ? vel.y : -vel.y)) ? (vel.y < 0) ? 0 : 1 : (vel.x > 0) ? 2 : 3;
			else
				spriterow = 0;
		}

		shdrpgms[static_cast<int>(SHADER_ORDER::SPRITES)].SetUniform("col_To_Draw", spritecol);
		shdrpgms[static_cast<int>(SHADER_ORDER::SPRITES)].SetUniform("rows", assetManager.GetSprite(type + movement).GetRows());
		shdrpgms[static_cast<int>(SHADER_ORDER::SPRITES)].SetUniform("cols", assetManager.GetSprite(type + movement).GetColumns());
		shdrpgms[static_cast<int>(SHADER_ORDER::SPRITES)].SetUniform("row_To_Draw", spriterow);
	}


	// Part 2: Bind object's VAO handle
	glBindVertexArray(models[mdl_ref].vaoid); // Bind object's VAO handle

	// Part 3: Copy object's 3x3 model-to-NDC matrix to vertex shader

	GLint uniform_var_loc1 = glGetUniformLocation(shdrpgms[shaderNumber].GetHandle(), "uModel_to_NDC");
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
	shdrpgms[shaderNumber].UnUse(); // Uninstall the shader program
}

/**************************************************************************
* @brief		 Cleanup the Object Creation.
* @param  none
* @return void
*************************************************************************/
void OpenGLObject::Cleanup() {
	// Cleanup the VAO, VBO and Shader Program
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

}




/**************************************************************************
* @brief  Initialize the Shaders for Graphics Pipeline for Object to
*		  Render and/or Translate their objects.
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
	float userInput_angleSpeed) {

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
	glm::mat3 Translate = glm::mat3{
		1, 0, 0,
		0, 1, 0,
		 position.x,  position.y, 1
	};

	// matrix for rotation
	glm::mat3 Rotation = glm::mat3{
		cosf(radians(angleDisplacment)), sinf(radians(angleDisplacment)) , 0,
		-sinf(radians(angleDisplacment)),  cosf(radians(angleDisplacment)) , 0,
		0, 0, 1
	};

	// matrix for scale
	glm::mat3 Scale = glm::mat3{
		scaleModel.x, 0, 0,
		0, scaleModel.y, 0,
		0, 0, 1
	};

	// set the scale for the World to NDC coords.
	float scaleX = 2.0f / windowSize.first;
	float scaleY = 2.0f / windowSize.second;

	// Scale To World NDC-coordinates matrix
	glm::mat3 ScaleToWorldToNDC = glm::mat3{
		scaleX, 0, 0,
		0, scaleY, 0,
		0, 0, 1
	};
	// Instead of doing transpose, you can do what OpenGL matrix does:
	// Row-Major Order:				Column Major Order;
	//	   x0 y0 z0						 x0 x1 x2
	//	   x1 y1 z1						 y0 y1 y2
	//	   x2 y2 z2						 z0 z1 z2
	model_To_NDC_xform = cameraObject.World_to_NDC_xform * Translate * Rotation * Scale;
}


/**************************************************************************
* @brief  Draws a Debug Collision Box (AABB)
*
* @param  Vector2D	Minimum Coordinates of AABB
* @param  Vector2D  Maximum Coordinates of AABB
*
* @return void
*************************************************************************/
void OpenGLObject::DrawCollisionBox(Vector2D min, Vector2D max) {
	// get the points of the AABB

	float MinimumX = min.x;
	float MaximumX = max.x;
	float MinimumY = min.y;
	float MaximumY = max.y;



	//std::cout << Editor::gameWindowOrigin.first << '\t' << Editor::gameWindowOrigin.second << "\tWin Size\t" << Editor::gameWindowSize.first << '\t' << Editor::gameWindowSize.second << '\n';


//	MinimumX += Editor::gameWindowOrigin.first ;
//	MaximumX += Editor::gameWindowOrigin.first ;
	//MinimumY = Editor::gameWindowOrigin.second;
	//MaximumY = Editor::gameWindowOrigin.second;


	float sX = static_cast<float>(MinimumX);
	float bX = static_cast<float>(MaximumX);
	float sY = static_cast<float>(MinimumY);
	float bY = static_cast<float>(MaximumY);



	//	std::cout << "Smol: " << sX- (Editor::gameWindowSize.first)/2 - Editor::gameWindowOrigin.first << ' ' << sY - Editor::gameWindowSize.second /2<< "\tBogg " << bX << ' ' << bY << '\n';

	using glm::radians;

	// set angle displacement to 0, as we do not need to rotate
	angleDisplacment = 0;

	glm::mat3 ScaleToWorldToNDC = glm::mat3(
		2.0f / Editor::gameWindowSize.first, 0.0f, 0.0f,
		0.0f, 2.0f / Editor::gameWindowSize.second, 0.0f,
		0.0f, 0.0f, 1.0f
	);

	// Set Scale to World NDC
	//glm::mat3 ScaleToWorldToNDC = glm::mat3(
	//	2.0f / windowSize.first, 0.0f, 0.0f,
	//	0.0f, 2.0f /windowSize.second, 0.0f,
	//	0.0f, 0.0f, 1.0f
	//);

	model_To_NDC_xform = cameraObject.World_to_NDC_xform; /** Translate*/;

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
* @brief  set Texture Positon, Color
*
* @param  float x axis of texture
* @param  float y axis of texture
* @param  float r Red Color Value
* @param  float g Green Color Value
* @param  float b Blue Color Value
*
* @return void
*************************************************************************/
void OpenGLObject::OpenGLModel::VAO_Object::setTextureValue(float x, float y, float r, float g, float b) {

	// Set Position X and Y
	position.x = x;
	position.y = y;

	// Similarly, Color ...
	color.r = r;
	color.g = g;
	color.b = b;

}

/**************************************************************************
* @brief  set Texture Positon, Color
*
* @param  float s axis of texture
* @param  float t axis of texture
*
* @return void
*************************************************************************/
void OpenGLObject::OpenGLModel::VAO_Object::setTexture(float s, float t) {
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



/**************************************************************************
* @brief  Initialize Camera
*
* @param  GLFWwindow* pointer to the window
* @param  OpenGLObject* pointer to another object to contain
		  position coordinates
*
* @return void
*************************************************************************/
void OpenGLObject::Camera2D::Init(GLFWwindow* camWindow, OpenGLObject* ptr) {

	(void)camWindow;

	// Set a OpenGLObject to the pointer that is inputted, i.e. another OpenGLObject
	Cam = ptr;

	Left   = -1.0f;
	Right  = 1.0f;
	Bottom = -1.0f;
	Top	   = 1.0f;

	cameraProjection = glm::ortho(Left, Right, Bottom, Top, -1.0f, 1.0f);


	/*
					< Initialize for initial creation >
	Create the Frame Buffer Width and Height(This must be here as the
	FBuffer will update	 Every single time, it is zoom in/out /move		*/

	aspectRatio = static_cast<GLdouble>(Editor::gameWindowSize.first) / static_cast<GLdouble>(Editor::gameWindowSize.first);


	// compute camera's up and right vectors ...
	up = glm::vec2{ -sinf(glm::radians(Cam->orientation.x)), cosf(glm::radians(Cam->orientation.x)) };

	// compute camera's right vectors (U)
	right = glm::vec2{ cosf(glm::radians(Cam->orientation.x)), sinf(glm::radians(Cam->orientation.x)) };


	//heightRatio = height / 1000;


	// view transform 
	view_xform = glm::mat3
	{
		1, 0, 0,
		0, 1, 0,
		-Cam->position.x, -Cam->position.y, 1
	};
	// Camera to NDC
	CameraWindow_to_NDC_xform = glm::mat3{
		2.f / (height * aspectRatio), 0, 0,
		0, 2.f / height , 0,
		0, 0, 1
	};

	// World to NDC transform
	// Set the World to NDC transform for the camera
	//World_to_NDC_xform = CameraWindow_to_NDC_xform * view_xform;
	World_to_NDC_xform = CameraWindow_to_NDC_xform * cameraProjection;

}
/**************************************************************************
* @brief  Update Camera
*
* @param  GlfwWindow*  Pointer to the camera window (window to move)
* @param  int x axis of the camera to move
* @param  int y axis of the camera to move
*
* @return void
*************************************************************************/
void OpenGLObject::Camera2D::Update(GLFWwindow* camWindow, int positionX, int positionY) {

	using glm::radians;

	(void)camWindow;

	
	cameraProjection = glm::ortho(Left, Right, Bottom, Top, -1.0f, 1.0f);
	

	// ZOOM in
	//if (inputSystem.GetScrollState() == 1) 
	if (inputSystem.GetKeyState(GLFW_KEY_UP) == 2)
	{
		// Height Decrement by 1.1f
		height -= heightChangeValue;

	}

	// ZOOM OUT
	//if (inputSystem.GetScrollState() == -1)
	if (inputSystem.GetKeyState(GLFW_KEY_DOWN) == 2)
	{
		// Height Increment by 1.1f
		height += heightChangeValue;

	}


	if (inputSystem.GetKeyState(GLFW_KEY_F6) == 2)
		height = 1000;	
	if (inputSystem.GetKeyState(GLFW_KEY_F7) == 2)
		height = 1500;	
	if (inputSystem.GetKeyState(GLFW_KEY_F8) == 2)
		height = 2000;

	if (Left >= 0)
		Left		= 0;

	if (Right <= 0)
		Right		= 0;

	if (Top <= 0)
		Top			= 0;

	if (Bottom >= 0)
		Bottom		= 0;



	// Set minimum parameter of height < Depth >
	if (height <= min_height)
	{
		height = min_height;
	}

	// Set maximum parameter of height < Depth >
	if (height >= max_height)
	{
		height = max_height;
	}



	/*
					< Initialize for initial creation >
	Create the Frame Buffer Width and Height(This must be here as the
	FBuffer will update	 Every single time, it is zoom in/out /move		*/

	aspectRatio = static_cast<GLfloat>(Editor::gameWindowSize.first) / static_cast<GLfloat>(Editor::gameWindowSize.second);

	view_xform =glm::mat3
	{
		1, 0, 0,
		0, 1, 0,
		-Cam->position.x, -Cam->position.y, 1
	};


	// Set the Camer Window to NDC xform
	CameraWindow_to_NDC_xform = glm::mat3{
		2.f / (Editor::gameWindowSize.first) * (1000 /cameraObject.height ), 0, 0,
		0, 2.f / Editor::gameWindowSize.second * (1000 /cameraObject.height), 0,
		0, 0, 1
	};



	// World to NDC transform
	// Set the World to NDC transform for the camera
	//	World_to_NDC_xform = CameraWindow_to_NDC_xform * view_xform ;

	
	World_to_NDC_xform = CameraWindow_to_NDC_xform * view_xform;

	// Update the camera position using the Cam pointer
	Cam->CameraUpdate(positionX, positionY);
}

/**************************************************************************
* @brief  Update camera position
*
* @param  int set coordinate [x]
* @param  int set coordinate [y]
*
* 
* @return void
*************************************************************************/
void OpenGLObject::CameraUpdate(int posX, int posY) {
	//std::cout << "Object Update\n";
	// Compute the angular displacement in radians


	//Scale the model based on float variable.
	scaleModel = glm::vec2(0, 0);

	position = glm::vec2(posX, posY);


	cameraObject.posX = posX;
	cameraObject.posY = posY;


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
		cosf(glm::radians(angleDisplacment)), sinf(glm::radians(angleDisplacment)), 0.0f,
		-sinf(glm::radians(angleDisplacment)), cosf(glm::radians(angleDisplacment)), 0.0f,
		0.0f, 0.0f, 1.0f
	);

	// Compute the translation matrix
	glm::mat3 Translation = glm::mat3(
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		position.x, position.y, 1.0f
	);


	// Compute the scaling matrix to map from world coordinates to NDC coordinates
	glm::mat3 ScaleToWorldToNDC = glm::mat3(
		2.0f / Editor::gameWindowSize.first, 0.0f, 0.0f,
		0.0f, 2.0f / Editor::gameWindowSize.second, 0.0f,
		0.0f, 0.0f, 1.0f
	);


	// Compute the model-to-world-to-NDC transformation matrix
	model_To_NDC_xform = cameraObject.World_to_NDC_xform * Translation * Rotation * Scale;

}


/*=======================================================================================================================*/
/*=======================================================================================================================*/
/*==================================================GRAPHIC SHADERS======================================================*/
/*=======================================================================================================================*/
/*=======================================================================================================================*/
/*=======================================================================================================================*/


/**************************************************************************
* @brief  Initialize Shaders
*
* @param  no param
*
* @return void
*************************************************************************/
void OpenGLObject::InitShaders()
{
	// Create file name
	VectorPairStrStr MODELSSHADER{
		std::make_pair<std::string, std::string>
		("assets/shaders/Oui_Uninteractive_models.vert", "assets/shaders/Oui_Uninteractive_models.frag")
	};

	VectorPairStrStr FONTSHADER{
		std::make_pair<std::string, std::string>
		("assets/shaders/Oui_Uninteractive_font.vert", "assets/shaders/Oui_Uninteractive_font.frag")
	};

	VectorPairStrStr CAMERASHADER{
		std::make_pair<std::string, std::string>
		("assets/shaders/Oui_Uninteractive_camera.vert", "assets/shaders/Oui_Uninteractive_camera.frag")
	};

	VectorPairStrStr SPRITESHADER{
		std::make_pair<std::string, std::string>
		("assets/shaders/Oui_Uninteractive_models_sprites.vert", "assets/shaders/Oui_Uninteractive_models_sprites.frag")
	};


	// Initialize the Shader Program for Models
	std::cout << "Initializing model shader" << std::endl;
	init_shdrpgms_cont(MODELSSHADER);

	// Initialize the Shader Program for Fonts
	std::cout << "Initializing font shader" << std::endl;
	init_shdrpgms_cont(FONTSHADER);

	// Initialize the Shader Program for Camera
	std::cout << "Initializing camera shader" << std::endl;
	init_shdrpgms_cont(CAMERASHADER);

	// Initialize the Shader Program for Sprites
	std::cout << "Initializing sprite shader" << std::endl;
	init_shdrpgms_cont(SPRITESHADER);

}


/**************************************************************************
* @brief  Initialize the Shaders for Graphics Pipeline for Object to
*		  Render and/or Translate their objects.
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

/*=======================================================================================================================*/
/*=======================================================================================================================*/
/*====================================================OPENGL FONTS=======================================================*/
/*=======================================================================================================================*/
/*=======================================================================================================================*/
/*=======================================================================================================================*/

/**************************************************************************
* @brief  Initialize the Shaders for Graphics Pipeline for fonts.
*
*
* @param  NONE
* @return void
*************************************************************************/
void OpenGLObject::InitFont()
{
	// Initialize the Projection matrix for the fonts to render into the screen
	fontProjection = glm::ortho(0.0f, static_cast<float>(windowSize.first), 0.0f, static_cast<float>(windowSize.second));
	// Use the shader
	shdrpgms[static_cast<int>(SHADER_ORDER::FONT)].Use();

	// Find the uniform location and create matrix4fv to it.
	glUniformMatrix4fv(glGetUniformLocation(shdrpgms[1].GetHandle(), "projection"), 1, GL_FALSE, glm::value_ptr(fontProjection));

	// For FONTS VAO and VBOs
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

/*=======================================================================================================================*/
/*=======================================================================================================================*/
/*======================================================LIGHTING=========================================================*/
/*=======================================================================================================================*/
/*=======================================================================================================================*/
/*=======================================================================================================================*/





/*=======================================================================================================================*/
/*=======================================================================================================================*/
/*=======================================================OTHERS==========================================================*/
/*=======================================================================================================================*/
/*=======================================================================================================================*/
/*=======================================================================================================================*/

/**************************************************************************
* @brief  Change the mouse coordinates from getMousePosition to frame
*		  buffer coordinates
*
* @param  GLFWwindow*	pointer to the window
* @param  double*		sets a value in return. [x]
* @param  double*		sets a value in return. [y]
* @param  Camera2D		camera object of original class: OpenGLObject.


@return void
*************************************************************************/
void OpenGLObject::FrameBufferMouseCoords(GLFWwindow* originalWindow, double* x, double* y, OpenGLObject::Camera2D camera)
{

	
	(void)originalWindow;
	// set a variable original X and Y
	double originalX = *x - Editor::gameWindowOrigin.first;
	double originalY = *y - Editor::gameWindowOrigin.second;

	//std::cout << originalX << '\t' << originalY << '\t';


	// get the center coordinates of the frame buffer window.
	int centerX = Editor::gameWindowSize.first / 2.0;
	int centerY = Editor::gameWindowSize.second / 2.0;

	//std::cout << centerX << '\t' << centerY << '\t';

	// Calculate corrected coordinates relative to the camera's position.
	double correctedX = (originalX - centerX) + camera.posX * 0.77;
	double correctedY = centerY - originalY + camera.posY * 0.77;  // Note the y-coordinate inversion


	//std::cout << correctedX << '\t' << correctedY << '\t';

	// set value of X and Y, (valueX, valueY) to the respective y values,
	// Y no change as no difference. X, on the other hand needs to be multiplied with the multiplier of height.,
	float valueX = correctedX;
	float valueY = correctedY;


	valueX /= 0.77;
	valueY /= 0.77;

	// set valueX to multiply by camera height.
	//valueX *= camera.height;



	*x = std::floor(valueX);
	*y = std::floor(valueY);
	

	//std::cout << '\n';
	//std::cout << *x << '\t' << *y <<'\t' <<" Camera PositionX: " << cameraObject.posX << '\t' << cameraObject.posY << '\n';

}