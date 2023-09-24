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
#include <utility>

#define ROTATION_CLOCKWISE 1
#define ROTATION_ANTI_CLOCKWISE 0
#define GET_COMPONENT(GameObject, Component, ComponentType) (GameObject->GetComponentType<Component>(ComponentType))

extern GLFWwindow* window;
extern OpenGLObject Objects;
extern std::pair<unsigned short, unsigned short> windowSize;

class OpenGLApplication {

public:
	// Window Functions
	static void OpenGLWindowInit();
	static void OpenGLWindowCleanup();
	static void OpenGLWindowResizeCallback(GLFWwindow* window, int width, int height);


	// Functions to set data ...
	static void OpenGLInit();
	static void OpenGLUpdate();
	static void OpenGLCleanup();
	static void OpenGLTestChangingStates();

	//	static void OpenGLWindowInitialization(GLFWwindow*& window, GLint width, GLint height);
	static void OpenGLObjectsInitialization();
//	static void render_square(glm::vec2 scaling, glm::vec2 position);


	static void Draw();

	static void OpenGLSetBackgroundColor(float r, float g, float b, float a);


	//static std::list<OpenGLObject> objects; // singleton


};

#endif // OPENGL_APPLICATION_H
