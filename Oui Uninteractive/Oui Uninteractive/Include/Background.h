/**************************************************************************
 * @file Backgrounds.h
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

#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GL/GL.h>
#include <vector>
#include <map>
#include <string>
#include <iterator>
#include <OpenGLShaders.h>
#include <Vector2D.h>
#include <OpenGLObjects.h>


class Background
{
public:
	Background(): position (0,0), scaleModel(10,10), model_To_NDC_xform(glm::mat3(1.0)){};
	
	~Background(){};

	glm::vec2 position;							// translation
	glm::vec2 scaleModel;						// Scale for the Model
	glm::mat3 model_To_NDC_xform;				// Model to NDC 
	static GLuint mdl_ref, shd_ref;				// Model and Shader Reference

	static GLuint VAO, VBO;						// Object VAO VBO


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
	void Init();

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
	void Update(float newX, float newY, float scaleX, float scaleY);

	void SetBackGround(int);

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
	void Draw() const;

	//Shaders
	static std::vector<OpenGLShader>shdrpgms;
	using VectorPairStrStr = std::vector <std::pair<std::string, std::string>>;
	
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
	static void init_shdrpgms_cont(VectorPairStrStr const& vpss);

	/**************************************************************************
	 * @brief Set up an OpenGL texture object from an image file.
	 *
	 * This function loads an image from the specified file, creates an OpenGL texture object,
	 * and configures it with the image data.
	 *
	 * @param filePath The file path to the image file.
	 * @return The OpenGL texture object handler, or 0 if the texture setup failed.
	 *************************************************************************/
	static int Setup_TextureObject(std::string filePath);

	/**************************************************************************
	 * @brief Clean up OpenGL resources related to the background.
	 *
	 * This function is responsible for deleting OpenGL resources, specifically
	 * a vertex array object (VAO) and a vertex buffer object (VBO) associated with the background.
	 *
	 * @note This function assumes that OpenGL bindings are available and properly defined.
	*************************************************************************/
	static void Cleanup();

private:
	
};

extern Background background;
#endif 