/**************************************************************************
 * @file OpenGLApplication.h
 * @author 	TAN Angus Yit Hoe
 * @co-author CHEAH Tristan Tze Hong, HWANG Jing Rui, Austin, LOW Wang Chun, Mark, CHAN Aaron Jun Xiang, QUEK Cheng Kwang Emery
 * @par DP email: tan.a@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 29-09-2023
 * @brief  
 * This file contains the headers for OpenGLApplication.cpp which
 * allows the creation and initialization of a OpenGL Application
 * Window which then allows user to draw functions and/or change states 
 * depending on the game state manager. 
 *************************************************************************/

#ifndef OPENGL_APPLICATION_H
#define OPENGL_APPLICATION_H

#include <GL/glew.h> // for access to OpenGL API declarations 
#include <GLFW/glfw3.h>
#include <OpenGLShaders.h>
#include <map>
#include <OpenGLObjects.h>
#include <ISystem.h>


#define GET_COMPONENT(GameObject, Component, ComponentType) (GameObject->GetComponentType<Component>(ComponentType))

extern GLFWwindow* windowNew;
extern OpenGLObject Objects;
extern std::pair<int, int> windowSize;

class OpenGLApplication : public ISystem{

public:
	// < Window Functions >
	/**************************************************************************
	* @brief		Set the parameters for the window, and then Initialize the
	*				Window.
	*				Then, Set parameters for OpenGL Context.
	*				> Drawing the Window.
	* @param  none
	* @return void
	*************************************************************************/
	static void OpenGLWindowInit();
	/**************************************************************************
	* @brief		Cleanup the Window at the end of the loop.
	*
	* @param  none
	* @return void
	*************************************************************************/
	static void OpenGLWindowCleanup();
	/**************************************************************************
	* @brief		Resize Window Callback
	* @param none
	* @return void
	*************************************************************************/
	static void OpenGLWindowResizeCallback(GLFWwindow* window, int width, int height);


	// < OpenGL Functions to Interact with Graphics Pipeline >
	/**************************************************************************
	* @brief		Initialize the Graphics Pipeline to enable usage of OpenGL
	*
	*				> Drawing the Window.
	*
	* @param  none
	* @return void
	*************************************************************************/
	static void OpenGLInit();

	/**************************************************************************
	* @brief		Updates anything that is required to be on the window.
	*				> Update Game Object
	*				> Update Background
	*				> Update Color
	*				> Draw
	* @param  none
	* @return void
	*************************************************************************/
	static void OpenGLUpdate();
	/**************************************************************************
	* @brief Cleanup the applcation process.
	* @param none
	* @return void
	*************************************************************************/
	static void OpenGLCleanup();



	void Initialize() override;

	virtual void Update(float dt) override;





#ifdef _DEBUG
	/**************************************************************************
	* @brief			Test Changing of States in the Game Engine..
	* @warning			OpenGLObjects init lines must be drawn for it to work.
	*
	* @param none
	* @return void
	*************************************************************************/
	static void OpenGLTestChangingStates();
#endif
	/**************************************************************************
	* @brief		Draws any thing that the window is required.
	*
	* @param none
	* @return void
	*************************************************************************/
	static void Draw();
	/**************************************************************************
	* @brief		Sets Background Color, Easier for people to see what it is
	*				for compared to glClearColor.
	* @param none
	* @return void
	*************************************************************************/
	static void OpenGLSetBackgroundColor(float r, float g, float b, float a);

	/**************************************************************************
	* @brief Constructor and Destructor
	*************************************************************************/
	OpenGLApplication() {};
	~OpenGLApplication() {};
};

#endif // OPENGL_APPLICATION_H
