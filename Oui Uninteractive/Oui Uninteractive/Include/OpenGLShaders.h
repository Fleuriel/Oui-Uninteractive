/**************************************************************************
 * @file OpenGLShaders.h
 * @author
 * @par DP email:
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 09-05-2023
 * @brief
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
class OpenGLShaderTrying
{
public:
	// the program ID
	unsigned int ID;

	// constructor reads and builds the shader
	OpenGLShaderTrying(const char* vertexPath, const char* fragmentPath) {
		// 1. retrieve the vertex/fragment source code from filePath
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		// ensure ifstream objects can throw exceptions:
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			// open files
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			// read file's buffer contents into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			// close file handlers
			vShaderFile.close();
			fShaderFile.close();
			// convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure& e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();
		// 2. compile shaders
		unsigned int vertex, fragment;
		// vertex shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");
		// fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "FRAGMENT");
		// shader Program
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		checkCompileErrors(ID, "PROGRAM");
		// delete the shaders as they're linked into our program now and no longer necessary
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	// use/activate the shader
	// activate the shader
	// ------------------------------------------------------------------------
	void use()
	{
		glUseProgram(ID);
	}
	// utility uniform functions
	// ------------------------------------------------------------------------
	void setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	// ------------------------------------------------------------------------
	void setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
private:

	// utility function for checking shader compilation/linking errors.
	// ------------------------------------------------------------------------
	void checkCompileErrors(unsigned int shader, std::string type)
	{
		int success;
		char infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}
};


class OpenGLShader
{

public:
	//OpenGLShader() : pgm_handle(0), is_linked(GL_FALSE) { /* empty by design */ }


	//
	static void Init();


	GLboolean CompileLinkValidate(std::vector<std::pair<GLenum, std::string>>);
	GLboolean CompileShaderFromFile(GLenum shader_type, const std::string& file_name);
	GLboolean CompileShaderFromString(GLenum shader_type, const std::string& shader_src);
	GLboolean Link();
	void Use();
	void UnUse();
	GLuint GetHandle() const;
	GLboolean Validate();

	GLboolean IsLinked() const;
	std::string GetLog() const;

	void DeleteShaderProgram();

	void SetUniform(GLchar const* name, GLboolean val);
	void SetUniform(GLchar const* name, GLint val);
	void SetUniform(GLchar const* name, GLfloat val);
	void SetUniform(GLchar const* name, GLfloat x, GLfloat y);
	void SetUniform(GLchar const* name, GLfloat x, GLfloat y, GLfloat z);
	void SetUniform(GLchar const* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	void SetUniform(GLchar const* name, glm::vec2 const& val);
	void SetUniform(GLchar const* name, glm::vec3 const& val);
	void SetUniform(GLchar const* name, glm::vec4 const& val);
	void SetUniform(GLchar const* name, glm::mat3 const& val);
	void SetUniform(GLchar const* name, glm::mat4 const& val);



	// display the list of active vertex attributes used by vertex shader
	void PrintActiveAttribs() const;

	// display the list of active uniform variables
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
	GLint GetUniformLocation(GLchar const* name);

	// return true if file (given in relative path) exists, false otherwise
	GLboolean FileExists(std::string const& file_name);

};


#endif // OPENGL_SHADERS_H