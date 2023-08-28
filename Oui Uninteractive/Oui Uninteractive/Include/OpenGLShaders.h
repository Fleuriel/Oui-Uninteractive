#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>




class OpenGLShader
{

public:
	OpenGLShader() : pgm_handle(0), is_linked(GL_FALSE) { /* empty by design */ }

	GLboolean CompileLinkValidate(std::vector<std::pair<GLenum, std::string>>);

	GLboolean Link();
	void Use();
	void UnUse();
	GLuint GetHandle() const;







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

protected:



}; 



void OpenGLShader::PrintActiveAttribs() const {
#if 1
	GLint max_length, num_attribs;
	glGetProgramiv(pgm_handle, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &max_length);
	glGetProgramiv(pgm_handle, GL_ACTIVE_ATTRIBUTES, &num_attribs);
	GLchar* pname = new GLchar[max_length];
	std::cout << "Index\t|\tName\n";
	std::cout << "----------------------------------------------------------------------\n";
	for (GLint i = 0; i < num_attribs; ++i) {
		GLsizei written;
		GLint size;
		GLenum type;
		glGetActiveAttrib(pgm_handle, i, max_length, &written, &size, &type, pname);
		GLint loc = glGetAttribLocation(pgm_handle, pname);
		std::cout << loc << "\t\t" << pname << std::endl;
	}
	std::cout << "----------------------------------------------------------------------\n";
	delete[] pname;
#else
	GLint numAttribs;
	glGetProgramInterfaceiv(pgm_handle, GL_PROGRAM_INPUT, GL_ACTIVE_RESOURCES, &numAttribs);
	GLenum properties[] = { GL_NAME_LENGTH, GL_TYPE, GL_LOCATION };
	std::cout << "Active attributes:" << std::endl;
	for (GLint i = 0; i < numAttribs; ++i) {
		GLint results[3];
		glGetProgramResourceiv(pgm_handle, GL_PROGRAM_INPUT, i, 3, properties, 3, NULL, results);

		GLint nameBufSize = results[0] + 1;
		GLchar* pname = new GLchar[nameBufSize];
		glGetProgramResourceName(pgm_handle, GL_PROGRAM_INPUT, i, nameBufSize, NULL, pname);
		//   std::cout << results[2] << " " << pname << " " << getTypeString(results[1]) << std::endl;
		std::cout << results[2] << " " << pname << " " << results[1] << std::endl;
		delete[] pname;
	}
#endif
}

void OpenGLShader::PrintActiveUniforms() const {
	GLint max_length;
	glGetProgramiv(pgm_handle, GL_ACTIVE_UNIFORM_MAX_LENGTH, &max_length);
	GLchar* pname = new GLchar[max_length];
	GLint num_uniforms;
	glGetProgramiv(pgm_handle, GL_ACTIVE_UNIFORMS, &num_uniforms);
	std::cout << "Location\t|\tName\n";
	std::cout << "----------------------------------------------------------------------\n";
	for (GLint i = 0; i < num_uniforms; ++i) {
		GLsizei written;
		GLint size;
		GLenum type;
		glGetActiveUniform(pgm_handle, i, max_length, &written, &size, &type, pname);
		GLint loc = glGetUniformLocation(pgm_handle, pname);
		std::cout << loc << "\t\t" << pname << std::endl;
	}
	std::cout << "----------------------------------------------------------------------\n";
	delete[] pname;
}
