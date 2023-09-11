/**************************************************************************
 * @file OpenGLApplication.h
 * @author 
 * @par DP email: 
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 09-05-2023
 * @brief 
 *************************************************************************/

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
	static void OpenGLTestChangingStates();
	static void OpenGLWindowInit(unsigned short width, unsigned short height);
	static void OpenGLInit();
	static void OpenGLUpdate();
	static void OpenGLCleanup();
	static void OpenGLWindowCleanup();
//	static void OpenGLWindowInitialization(GLFWwindow*& window, GLint width, GLint height);
	static void OpenGLObjectsInitialization();
//	static void render_square(glm::vec2 scaling, glm::vec2 position);

	static std::map<std::string, OpenGLObject> Object_Storage;


	static void Draw();

	static void OpenGLSetBackgroundColor(float r, float g, float b, float a);





};

#endif // OPENGL_APPLICATION_H
