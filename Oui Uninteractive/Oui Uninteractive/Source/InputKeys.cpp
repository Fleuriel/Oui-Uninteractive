#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <InputKeys.h>
#include <iostream>


 std::vector<bool> keyStatesAlphabet(26, false);

 std::vector<bool> mouseStates(3, false);

#define UNREFERENCED_PARAMETER(P)(P)


void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mod)
{
	UNREFERENCED_PARAMETER(mod);
	UNREFERENCED_PARAMETER(scancode);


/***********************************************************************/
	if (action == GLFW_PRESS)
	{
		if (GLFW_KEY_ESCAPE == key)
			glfwSetWindowShouldClose(window, GLFW_TRUE);


		if (key >= GLFW_KEY_A && key <= GLFW_KEY_Z)
		{
			keyStatesAlphabet[key - GLFW_KEY_A] = true;
		}

#ifndef _DEBUG
		std::cout << "Pressed Keys\n";
#endif
	}

/***********************************************************************/

	if (action == GLFW_RELEASE)
	{
		if (key >= GLFW_KEY_A && key <= GLFW_KEY_Z)
		{
			keyStatesAlphabet[key - GLFW_KEY_A] = false;
		}
#ifndef _DEBUG
		std::cout << (char)key << '\n';

		std::cout << "Released Keys\n";
#endif
	}

/***********************************************************************/


	//// checks for each of the keys if they are pressed ...
	//if (key >= GLFW_KEY_A && key <= GLFW_KEY_Z)
	//{
	//	keyStatesAlphabet[key - GLFW_KEY_A] = true;
	//}


/***********************************************************************/

}
