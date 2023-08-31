
#ifndef OPENGL_APPLICATION_H
#define OPENGL_APPLICATION_H

#include <GL/glew.h> // for access to OpenGL API declarations 
#include <GLFW/glfw3.h>
#include <OpenGLShaders.h>
#include <map>
#include <OpenGLObjects.h>



extern GLFWwindow* window;
extern OpenGLObject Objects;

class OpenGLApplication {

public:

	// Functions to set data ...
	static void OpenGLInit(short width, short height);
	static void OpenGLUpdate();
	static void OpenGLCleanup();
//	static void OpenGLWindowInitialization(GLFWwindow*& window, GLint width, GLint height);
	static void OpenGLObjectsInitialization();
	static void render_square(glm::vec2 scaling, glm::vec2 position);

	static std::map<std::string, OpenGLObject> Object_Storage;


	static void Draw();

	//Shaders
	static std::vector<OpenGLShader> Shader;
	using VectorPairStrStr = std::vector <std::pair<std::string, std::string>>;
	static void OpenGLShadersInitialization();
	static OpenGLShader ShaderProgram;



};

#endif // OPENGL_APPLICATION_H
