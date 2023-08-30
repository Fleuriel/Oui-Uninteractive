#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <InputKeys.h>
#include <keyDefinition.h>
#include <iostream>
#include <InitializeEngine.h>


 std::vector<bool> keyStates(Number_of_working_keys, false);

 std::vector<bool> mouseStates(3, false);

#define UNREFERENCED_PARAMETER(P)(P)


void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mod)
{
	UNREFERENCED_PARAMETER(mod);
	UNREFERENCED_PARAMETER(scancode);
	

/***********************************************************************/
	if (action == GLFW_PRESS)
	{
		/*if (GLFW_KEY_ESCAPE == key)
		{
			glfwSetWindowShouldClose(window, GLFW_TRUE);
			//glfwWindowShouldClose(window);
			CurrentGameState = State_STOP;
		}*/


		/*-----------------------------------
        |            ALPHABETS              |
        -----------------------------------*/
		if (key >= GLFW_KEY_A && key <= GLFW_KEY_Z)
			keyStates[key - GLFW_KEY_A] = true;

		/*-----------------------------------
		|             NUMBERS               |
		-----------------------------------*/
		if (key >= GLFW_KEY_0 && key <= GLFW_KEY_9)
			keyStates[key - GLFW_KEY_0 + KEY_0] = true;

		/*-----------------------------------
		|              OTHERS               |
		-----------------------------------*/
		if (key == GLFW_KEY_SPACE)
			keyStates[KEY_SPACE] = true;

		if (key == GLFW_KEY_LEFT_ALT || key == GLFW_KEY_RIGHT_ALT)
			keyStates[KEY_ALT] = true;

		if (key == GLFW_KEY_LEFT_CONTROL || key == GLFW_KEY_RIGHT_CONTROL)
			keyStates[KEY_CTRL] = true;

		if (key == GLFW_KEY_LEFT_SHIFT || key == GLFW_KEY_RIGHT_SHIFT)
			keyStates[KEY_SHIFT] = true;

		if (key == GLFW_KEY_CAPS_LOCK)
			keyStates[KEY_CAPS] = true;

		if (key == GLFW_KEY_TAB)
			keyStates[KEY_TAB] = true;

		if (key == GLFW_KEY_ESCAPE)
			keyStates[KEY_ESC] = true;

		if (key == GLFW_KEY_ENTER)
			keyStates[KEY_ENTER] = true;



#ifdef _DEBUG
		std::cout << "Pressed Keys\n";
#endif
	}

/***********************************************************************/

	if (action == GLFW_RELEASE)
	{
		if (key >= GLFW_KEY_A && key <= GLFW_KEY_Z)
			keyStates[key - GLFW_KEY_A] = false;

		if (key >= GLFW_KEY_0 && key <= GLFW_KEY_9)
			keyStates[key - GLFW_KEY_0 + KEY_0] = false;

		if (key == GLFW_KEY_SPACE)
			keyStates[KEY_SPACE] = false;

		if (key == GLFW_KEY_LEFT_ALT || key == GLFW_KEY_RIGHT_ALT)
			keyStates[KEY_ALT] = false;

		if (key == GLFW_KEY_LEFT_CONTROL || key == GLFW_KEY_RIGHT_CONTROL)
			keyStates[KEY_CTRL] = false;

		if (key == GLFW_KEY_LEFT_SHIFT || key == GLFW_KEY_RIGHT_SHIFT)
			keyStates[KEY_SHIFT] = false;
		
		if (key == GLFW_KEY_CAPS_LOCK)
			keyStates[KEY_CAPS] = false;

		if (key == GLFW_KEY_TAB)
			keyStates[KEY_TAB] = false;

		if (key == GLFW_KEY_ESCAPE)
			keyStates[KEY_ESC] = false;

		if (key == GLFW_KEY_ENTER)
			keyStates[KEY_ENTER] = false;

#ifndef _DEBUG
		std::cout << (char)key << '\n';

		std::cout << "Released Keys\n";
#endif
	}

/***********************************************************************/


	//// checks for each of the keys if they are pressed ...
	//if (key >= GLFW_KEY_A && key <= GLFW_KEY_Z)
	//{
	//	keyStates[key - GLFW_KEY_A] = true;
	//}


/***********************************************************************/

}
