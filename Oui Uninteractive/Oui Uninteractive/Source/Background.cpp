/**************************************************************************
 * @file Backgrounds.cpp
 * @author CHAN Aaron Jun Xiang
 * @par DP email: aaronjunxiang.chan@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 09-05-2023
 * @brief Implementation of the Background class for rendering background objects in OpenGL.
 *
 * This source file contains the implementation of the Background class, which is responsible for
 * rendering background objects in an OpenGL-based application. It includes functions for initializing,
 * updating, rendering, and cleaning up background objects. The class utilizes shaders, textures,
 * and transformation matrices to achieve rendering effects.
 *
 * @note This file assumes the existence of relevant header files, OpenGL bindings, and external libraries
 *       such as GLM and STB Image for image loading.
 *************************************************************************/


#include <Background.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>
#include "AssetManager.h"


std::vector<OpenGLShader> Background::shdrpgms; //singleton

unsigned int Background::mdl_ref = 0; // Define and initialize mdl_ref
unsigned int Background::shd_ref = 0; // Define and initialize shd_ref

extern std::pair<int,int> windowSize;	// to retrieve window size

GLuint Background::VAO = 0;	//initialize to 0
GLuint Background::VBO = 0; //initialize to 0

int backgroundTexture;	//Texture for background

extern AssetManager assetManager;

/**************************************************************************
 * @brief Initialize the Background class.
 *
 * This function initializes various properties and transformations related to the background,
 * including shaders, textures, and transformation matrices.
 *
 * @note This function assumes that certain global variables and functions like `init_shdrpgms_cont()`
 *       and `Background::Setup_TextureObject()` are available and properly defined.
 *       It also assumes that the class has member variables such as `bgTexture`, `mdl_ref`, `shd_ref`,
 *       `position`, `scaleModel`, and `model_To_NDC_xform` to store background-related information.
 *************************************************************************/
void Background::Init() {
#ifdef _DEBUG
	// Print debug information indicating the start of initialization
	std::cout << "Background::Init()\n\n";
#endif // _DEBUG

	// Define file names for vertex and fragment shaders
	VectorPairStrStr fileName{
		std::make_pair<std::string, std::string>
		("../shaders/Oui_Uninteractive_models.vert", "../shaders/Oui_Uninteractive_models.frag")
	};

	// Initialize shader programs using the provided file names
	init_shdrpgms_cont(fileName);


	// Load a background texture from a file
	backgroundTexture = assetManager.GetTexture("background");

	// Initialize model and shader references to zero
	mdl_ref = 0;
	shd_ref = 0;

	// Set the initial position of the background to (0, 0)
	position.x = 0;
	position.y = 0;

	// Set the scale of the background to match the window size
	scaleModel.x = static_cast<float>(windowSize.first);
	scaleModel.y = static_cast<float>(windowSize.second);

	// Create transformation matrices for translation, rotation, and scaling
	glm::mat3 Translate = glm::mat3 {
		1, 0, 0,
		0, 1, 0,
		 position.x,  position.y, 1
	};

	glm::mat3 Rotation = glm::mat3(
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	);

	glm::mat3 Scale = glm::mat3 {
		scaleModel.x, 0, 0,
		0, scaleModel.y, 0,
		0, 0, 1
	};

	// Compute a transformation matrix for scaling from model space to normalized device coordinates (NDC)
	float scaleX = 2.0f / windowSize.first;
	float scaleY = 2.0f / windowSize.second;

	glm::mat3 ScaleToWorldToNDC = glm::mat3 {
		scaleX, 0, 0,
		0, scaleY, 0,
		0, 0, 1
	};

	// Compute a transformation matrix for scaling from model space to normalized device coordinates (NDC)
	model_To_NDC_xform = ScaleToWorldToNDC * Translate * Rotation * Scale;

#ifdef _DEBUG
	// Print debug information indicating the end of initialization
	std::cout << '\n';
#endif

}


/**************************************************************************
* @brief		Updates each Background with Movement, Scale rotation.
*				Option for rotation has been added.
* 
* @param float  Acceleration of x-Axis
* @param float  Acceleration of y-Axis
* @param float  Scale on both X and Y axes. (Might need to change)
* @param float  Angle Rotation Speed
* @param bool   Boolean for Rotation Enable or Disable
* @return void
*************************************************************************/
void Background::Update(float newX, float newY, float scaleX, float scaleY) {	

	//Scale the model based on float variable.
	scaleModel = glm::vec2(scaleX, scaleY);
	//Set the new position.
	position = glm::vec2(newX, newY);

	
	// Compute the scale matrix
	glm::mat3 Scale = glm::mat3(
		scaleModel.x, 0.0f, 0.0f,
		0.0f, scaleModel.y, 0.0f,
		0.0f, 0.0f, 1.0f
	);


	// Compute the rotation matrix
	glm::mat3 Rotation = glm::mat3(
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	);


	// Compute the translation matrix
	glm::mat3 Translation = glm::mat3(
		1.0f, 0.0f, position.x,
		0.0f, 1.0f, position.y,
		0.0f, 0.0f, 1.0f
	);


	float valX = 2.0f / windowSize.first;
	float valY = 2.0f / windowSize.second;

	glm::mat3 ScaleToWorldToNDC = glm::mat3 {
		valX, 0, 0,
		0, valY, 0,
		0, 0, 1
	};


	// Compute the model-to-world-to-NDC transformation matrix
	model_To_NDC_xform = ScaleToWorldToNDC * glm::transpose(Translation) * glm::transpose(Rotation)  * glm::transpose(Scale);

}


/**************************************************************************
* @brief Render the background using OpenGL.
* 
 * This function is responsible for rendering the background using OpenGL.
 * It involves setting up texture units, binding shader programs, sending uniform data to shaders,
 * and performing the rendering operation.
 *
 * @note This function assumes that certain global variables and functions like `OpenGLObject::models`,
 *       `shdrpgms`, and OpenGL bindings are available and properly defined.
*************************************************************************/
void Background::Draw() const {
	// Bind the background texture to texture image unit 6
	int tex{};
	switch (texID) {
	case 0:
		tex = backgroundTexture;
		break;
	default:
		break;
	}

	glBindTextureUnit(6, tex);

	shdrpgms[shd_ref].Use(); // Use the shader program for rendering

	// Set the uniform for the texture unit (uTex2d) in the shader
	shdrpgms[shd_ref].SetUniform("uTex2d", 6);
	// Bind the object's Vertex Array Object (VAO)
	glBindVertexArray(OpenGLObject::models[mdl_ref].vaoid);

	// Copy the object's 3x3 model-to-NDC matrix to the vertex shader
	GLint uniform_var_loc1 = glGetUniformLocation(shdrpgms[shd_ref].GetHandle(), "uModel_to_NDC");
	if (uniform_var_loc1 >= 0) {
		glUniformMatrix3fv(uniform_var_loc1, 1, GL_FALSE, glm::value_ptr(Background::model_To_NDC_xform));
	}
	else {
		std::cout << "Uniform variable doesn't exist!!!" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	// Render the object using glDrawElements or glDrawArrays
	glDrawElements(
		OpenGLObject::models[mdl_ref].primitive_type,
		OpenGLObject::models[mdl_ref].draw_cnt,
		GL_UNSIGNED_SHORT, nullptr);




	// Clean up: Unbind the VAO and uninstall the shader program
	glBindVertexArray(0);
	shdrpgms[shd_ref].UnUse();
}

/**************************************************************************
 * @brief Clean up OpenGL resources related to the background.
 *
 * This function is responsible for deleting OpenGL resources, specifically
 * a vertex array object (VAO) and a vertex buffer object (VBO) associated with the background.
 *
 * @note This function assumes that OpenGL bindings are available and properly defined.
*************************************************************************/
void Background::Cleanup() {
	// Delete the vertex array object (VAO)
	glDeleteVertexArrays(1, &VAO);
	// Delete the vertex buffer object (VBO)
	glDeleteBuffers(1, &VBO);
}


/**************************************************************************
 * @brief Initialize OpenGL shader programs based on pairs of shader file paths.
 *
 * This function initializes OpenGL shader programs by compiling, linking, and validating
 * vertex and fragment shaders specified in pairs of file paths provided in the `vpss` vector.
 *
 * @param vpss A vector of pairs, where each pair contains file paths to a vertex shader (first)
 *             and a fragment shader (second).
 * @note This function assumes that OpenGLShader class and necessary OpenGL bindings are available
 *       and properly defined.
*************************************************************************/
void Background::init_shdrpgms_cont(VectorPairStrStr const& vpss) {
	for (auto const& x : vpss) {

		// Create a vector to hold pairs of shader type (GL_VERTEX_SHADER or GL_FRAGMENT_SHADER) and file path
		std::vector<std::pair<GLenum, std::string>> shdr_files;

		// Add the vertex shader file path to the vector with shader type GL_VERTEX_SHADER
		shdr_files.emplace_back(std::make_pair(GL_VERTEX_SHADER, x.first));

		// Add the fragment shader file path to the vector with shader type GL_FRAGMENT_SHADER
		shdr_files.emplace_back(std::make_pair(GL_FRAGMENT_SHADER, x.second));

		// Create an OpenGLShader object
		OpenGLShader shdr_pgm;

		// Compile, link, and validate the shader program using the shader files
		shdr_pgm.CompileLinkValidate(shdr_files);

		// Insert the compiled shader program into the container (shdrpgms)
		shdrpgms.emplace_back(shdr_pgm);
	}
}

/**************************************************************************
 * @brief Set up an OpenGL texture object from an image file.
 *
 * This function loads an image from the specified file, creates an OpenGL texture object,
 * and configures it with the image data.
 *
 * @param filePath The file path to the image file.
 * @return The OpenGL texture object handler, or 0 if the texture setup failed.
 *************************************************************************/
int Background::Setup_TextureObject(std::string filePath) {
	GLuint textureObj_Handler; // OpenGL texture object handler

	int width, height, channels;

	// Load the image from the file using stb_image
	unsigned char* image = stbi_load(filePath.c_str(), &width, &height, &channels, STBI_rgb_alpha);

	if (!image) {
		// If the image loading fails, print an error message and return 0 (failure)
		std::cout << "Failed to load texture: " << filePath << std::endl;
		return 0; // Return 0 to indicate failure
	}

	// Create an OpenGL texture object
	glCreateTextures(GL_TEXTURE_2D, 1, &textureObj_Handler);

	// Allocate storage for the texture with RGBA8 format
	glTextureStorage2D(textureObj_Handler, 1, GL_RGBA8, width, height);

	// Upload the image data to the texture object
	glTextureSubImage2D(textureObj_Handler, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);

	// Free the image data after it's uploaded to OpenGL
	stbi_image_free(image);

	// Return the OpenGL texture object handler
	return textureObj_Handler;
}


