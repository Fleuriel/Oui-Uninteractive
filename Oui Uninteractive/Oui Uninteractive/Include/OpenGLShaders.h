
#ifndef OPENGL_SHADERS_H
#define OPENGL_SHADERS_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>



class OpenGLShader
{

public:
	OpenGLShader() : pgm_handle(0), is_linked(GL_FALSE) { /* empty by design */ }


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