/**************************************************************************
 * @file OpenGLShaders.h
 * @author 	TAN Angus Yit Hoe
 * @co-author CHEAH Tristan Tze Hong, HWANG Jing Rui, Austin, LOW Wang Chun, Mark, CHAN Aaron Jun Xiang, QUEK Cheng Kwang Emery
 * @par DP email: tan.a@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 29-09-2023
 * @brief
 * This file contains the headers for OpenGLShaders.cpp to 
 * compute the logic behind shader programs and allow for users
 * to use the functions to link, use, use uniform for shaders
 *************************************************************************/

#ifndef OPENGL_SHADERS_H
#define OPENGL_SHADERS_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class OpenGLShader {

public:

	/**************************************************************************
	* @brief		CompileLinkValidate
	*
	* @param std::vector<std::pair<GLenum, std::string>>
	* @return void
	*************************************************************************/
	GLboolean CompileLinkValidate(std::vector<std::pair<GLenum, std::string>>);
	/**************************************************************************
	* @brief		Compile Shader From File
	*
	* @param GLenum 	shader Type i.e. Frag Shader | Vert Shader
	* @param std::string string of the file name
	* 
	* @return void
	*************************************************************************/
	GLboolean CompileShaderFromFile(GLenum shader_type, const std::string& file_name);
	/**************************************************************************
	* @brief		Compile Shader from String
	*
	* @param GLenum		shader Type i.e. Frag Shader | Vert Shader
	* @param std::string string of the shader soruce
	* 
	* @return GLboolean
	*************************************************************************/
	GLboolean CompileShaderFromString(GLenum shader_type, const std::string& shader_src);
	/**************************************************************************
	* @brief		Link the Shader
	*
	* @param none
	* @return GLboolean
	*************************************************************************/
	GLboolean Link();
	/**************************************************************************
	* @brief		Use the Shader
	*
	* @param none
	* @return void
	*************************************************************************/
	void Use();
	/**************************************************************************
	* @brief		Unuse the shader
	*
	* @param none
	* @return void
	*************************************************************************/
	void UnUse();
	/**************************************************************************
	* @brief		Get Handle of the Shader
	*
	* @param none
	* @return GLuint
	*************************************************************************/
	GLuint GetHandle() const;
	/**************************************************************************
	* @brief		Validate the Shader
	*
	* @param NONE
	* @return GLboolean
	*************************************************************************/
	GLboolean Validate();

	/**************************************************************************
	* @brief		Check if the Shader is linked.
	*
	* @param NONE
	* @return GLboolean
	*************************************************************************/
	GLboolean IsLinked() const;
	/**************************************************************************
	* @brief		Gets Log of the shader if there are any errors
	*
	* @param NONE
	* @return std::string
	*************************************************************************/
	std::string GetLog() const;
	/**************************************************************************
	* @brief		Deletes Shader Program
	*
	* @param name
	* @param ...   boolean | int | float | x,y, | x,y,z, | x,y,z,w | vec2 |
	*				vec3| vec4 | mat3 | mat4
	* @return void
	*************************************************************************/
	void DeleteShaderProgram();

	/**************************************************************************
	* @brief		Gets Uniform Location
	*
	* @param name	
	* @param ...   boolean | int | float | x,y, | x,y,z, | x,y,z,w | vec2 |
	*				vec3| vec4 | mat3 | mat4
	* @return void
	*************************************************************************/
	void SetUniform(GLchar const* name, GLboolean val);
	/**************************************************************************
	* @brief		Gets Uniform Location
	*
	* @param name
	* @param ...   boolean | int | float | x,y, | x,y,z, | x,y,z,w | vec2 |
	*				vec3| vec4 | mat3 | mat4
	* @return void
	*************************************************************************/
	void SetUniform(GLchar const* name, GLint val);
	/**************************************************************************
	* @brief		Gets Uniform Location
	*
	* @param name
	* @param ...   boolean | int | float | x,y, | x,y,z, | x,y,z,w | vec2 |
	*				vec3| vec4 | mat3 | mat4
	* @return void
	*************************************************************************/
	void SetUniform(GLchar const* name, GLfloat val);
	/**************************************************************************
	* @brief		Gets Uniform Location
	*
	* @param name
	* @param ...   boolean | int | float | x,y, | x,y,z, | x,y,z,w | vec2 |
	*				vec3| vec4 | mat3 | mat4
	* @return void
	*************************************************************************/
	void SetUniform(GLchar const* name, GLfloat x, GLfloat y);
	/**************************************************************************
	* @brief		Gets Uniform Location
	*
	* @param name
	* @param ...   boolean | int | float | x,y, | x,y,z, | x,y,z,w | vec2 |
	*				vec3| vec4 | mat3 | mat4
	* @return void
	*************************************************************************/
	void SetUniform(GLchar const* name, GLfloat x, GLfloat y, GLfloat z);
	/**************************************************************************
	* @brief		Gets Uniform Location
	*
	* @param name
	* @param ...   boolean | int | float | x,y, | x,y,z, | x,y,z,w | vec2 |
	*				vec3| vec4 | mat3 | mat4
	* @return void
	*************************************************************************/
	void SetUniform(GLchar const* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
		/**************************************************************************
	* @brief		Gets Uniform Location
	*
	* @param name
	* @param ...   boolean | int | float | x,y, | x,y,z, | x,y,z,w | vec2 |
	*				vec3| vec4 | mat3 | mat4
	* @return void
	*************************************************************************/
	void SetUniform(GLchar const* name, glm::vec2 const& val); 
	/**************************************************************************
	* @brief		Gets Uniform Location
	*
	* @param name	
	* @param ...   boolean | int | float | x,y, | x,y,z, | x,y,z,w | vec2 |
	*				vec3| vec4 | mat3 | mat4
	* @return void
	*************************************************************************/
	void SetUniform(GLchar const* name, glm::vec3 const& val); 	
	/**************************************************************************
	* @brief		Gets Uniform Location
	*
	* @param name	
	* @param ...   boolean | int | float | x,y, | x,y,z, | x,y,z,w | vec2 |
	*				vec3| vec4 | mat3 | mat4
	* @return void
	*************************************************************************/
	void SetUniform(GLchar const* name, glm::vec4 const& val); 	
	/**************************************************************************
	* @brief		Gets Uniform Location
	*
	* @param name	
	* @param ...   boolean | int | float | x,y, | x,y,z, | x,y,z,w | vec2 |
	*				vec3| vec4 | mat3 | mat4
	* @return void
	*************************************************************************/
	void SetUniform(GLchar const* name, glm::mat3 const& val);
	/**************************************************************************
	* @brief		Gets Uniform Location
	*
	* @param name
	* @param ...   boolean | int | float | x,y, | x,y,z, | x,y,z,w | vec2 |
	*				vec3| vec4 | mat3 | mat4
	* @return void
	*************************************************************************/
	void SetUniform(GLchar const* name, glm::mat4 const& val);


	/**************************************************************************
	* @brief		display the list of active vertex attributes used by vertex 
					shader
	*
	* @param name
	* @param ...   boolean | int | float | x,y, | x,y,z, | x,y,z,w | vec2 |
	*				vec3| vec4 | mat3 | mat4
	* @return void
	*************************************************************************/
	void PrintActiveAttribs() const;

	/**************************************************************************
	* @brief		display the list of active uniform variables
	*
	* @param name
	* @param ...   boolean | int | float | x,y, | x,y,z, | x,y,z,w | vec2 |
	*				vec3| vec4 | mat3 | mat4
	* @return void
	*************************************************************************/
	void PrintActiveUniforms() const;
private:
	enum ShaderType {

		VERTEX_SHADER = GL_VERTEX_SHADER,
		FRAGMENT_SHADER = GL_FRAGMENT_SHADER,
		GEOMETRY_SHADER = GL_GEOMETRY_SHADER,
		TESS_CONTROL_SHADER = GL_TESS_CONTROL_SHADER,
		TESS_EVALUATION_SHADER = GL_TESS_EVALUATION_SHADER,

	};


	GLuint pgm_handle = 0;  // handle to linked shader program object
	GLboolean is_linked = GL_FALSE; // has the program successfully linked?
	std::string log_string; // log for OpenGL compiler and linker messages

	// use OpenGL API to return the location of an uniform variable with
	// name "name" using program handle encapsulated by object of this class type
	
	/**************************************************************************
	* @brief		Gets the Unfirom Location of the shader
	*
	* @param GLchar
	* @return GLint
	*************************************************************************/
	GLint GetUniformLocation(GLchar const* name);
	/**************************************************************************
	* @brief	 return true if file (given in relative path) exists, false otherwise
	*
	* @param std::string fileName
	* @return GLboolean
	*************************************************************************/
	GLboolean FileExists(std::string const& file_name);

};


#endif // OPENGL_SHADERS_H