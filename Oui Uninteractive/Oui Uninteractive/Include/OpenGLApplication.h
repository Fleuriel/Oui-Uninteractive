
#ifndef OPENGL_APPLICATION_H
#define OPENGL_APPLICATION_H

#include <GL/glew.h> // for access to OpenGL API declarations 
#include <GLFW/glfw3.h>
#include <OpenGLShaders.h>



extern GLFWwindow* window;

class OpenGLApplication {

public:

	// Functions to set data ...
	static void OpenGLInit(short width, short height);
	static void OpenGLUpdate();
	static void OpenGLCleanup();
	static void OpenGLWindowInitialization(GLFWwindow* window);
	static void OpenGLObjectsInitialization();
	




	//Shaders
//	std::vector<OpenGLShader> Shader;
	//static void OpenGLShadersInitialization();


};

#endif // OPENGL_APPLICATION_H
