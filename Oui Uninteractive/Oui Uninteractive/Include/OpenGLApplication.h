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
#include <chrono>


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
//	static void render_square(glm::vec2 scaling, glm::vec2 position);

	static std::map<std::string, OpenGLObject> Object_Storage;


	static void Draw();




	// < TIME >
	static double GetDeltaTime();
	static double GetFPS();
	static std::chrono::high_resolution_clock::time_point currentTime;
	static std::chrono::high_resolution_clock::time_point previousTime;
	static std::chrono::duration<double> deltaTime;



};

#endif // OPENGL_APPLICATION_H
