#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <InputKeys.h>
#include <keyDefinition.h>
#include <iostream>
#include <InitializeEngine.h>


 std::vector<bool> InputStates(Number_of_working_keys, false);

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
		{
			glfwSetWindowShouldClose(window, GLFW_TRUE);
			//glfwWindowShouldClose(window);
			CurrentGameState = State_STOP;
		}


		/*-----------------------------------
        |            ALPHABETS              |
        -----------------------------------*/
		if (key >= GLFW_KEY_A && key <= GLFW_KEY_Z)
			InputStates[key - GLFW_KEY_A] = true;

		/*-----------------------------------
		|             NUMBERS               |
		-----------------------------------*/
		if (key >= GLFW_KEY_0 && key <= GLFW_KEY_9)
			InputStates[key - GLFW_KEY_0 + KEY_0] = true;

		/*-----------------------------------
		|              OTHERS               |
		-----------------------------------*/
		if (key == GLFW_KEY_SPACE)
			InputStates[KEY_SPACE] = true;

		if (key == GLFW_KEY_LEFT_ALT || key == GLFW_KEY_RIGHT_ALT)
			InputStates[KEY_ALT] = true;

		if (key == GLFW_KEY_LEFT_CONTROL || key == GLFW_KEY_RIGHT_CONTROL)
			InputStates[KEY_CTRL] = true;

		if (key == GLFW_KEY_LEFT_SHIFT || key == GLFW_KEY_RIGHT_SHIFT)
			InputStates[KEY_SHIFT] = true;

		if (key == GLFW_KEY_CAPS_LOCK)
			InputStates[KEY_CAPS] = !InputStates[KEY_CAPS];

		if (key == GLFW_KEY_TAB)
			InputStates[KEY_TAB] = true;

		if (key == GLFW_KEY_ESCAPE)
			InputStates[KEY_ESC] = true;

		if (key == GLFW_KEY_ENTER)
			InputStates[KEY_ENTER] = true;

		/*-----------------------------------
		|             COMMANDS              |
		-----------------------------------*/
		if (key == GLFW_KEY_C && mod & GLFW_MOD_CONTROL)
			InputStates[KEY_COPY] = true;

		if (key == GLFW_KEY_V && mod & GLFW_MOD_CONTROL && InputStates[KEY_COPY])
			InputStates[KEY_PASTE] = true;

		if (key == GLFW_KEY_X && mod & GLFW_MOD_CONTROL)
			InputStates[KEY_CUT] = true;

		if (key == GLFW_KEY_Z && mod & GLFW_MOD_CONTROL)
			InputStates[KEY_UNDO] = true;

#ifdef _DEBUG
		std::cout << "Pressed Keys\n";
#endif
	}

/***********************************************************************/
	
	if (action == GLFW_RELEASE)
	{

		/*-----------------------------------
		|            ALPHABETS              |
		-----------------------------------*/
		if (key >= GLFW_KEY_A && key <= GLFW_KEY_Z)
			InputStates[key - GLFW_KEY_A] = false;

		/*-----------------------------------
		|             NUMBERS               |
		-----------------------------------*/
		if (key >= GLFW_KEY_0 && key <= GLFW_KEY_9)
			InputStates[key - GLFW_KEY_0 + KEY_0] = false;

		/*-----------------------------------
		|              OTHERS               |
		-----------------------------------*/
		if (key == GLFW_KEY_SPACE)
			InputStates[KEY_SPACE] = false;

		if (key == GLFW_KEY_LEFT_ALT || key == GLFW_KEY_RIGHT_ALT)
			InputStates[KEY_ALT] = false;

		if (key == GLFW_KEY_LEFT_CONTROL || key == GLFW_KEY_RIGHT_CONTROL)
			InputStates[KEY_CTRL] = false;

		if (key == GLFW_KEY_LEFT_SHIFT || key == GLFW_KEY_RIGHT_SHIFT)
			InputStates[KEY_SHIFT] = false;
		
		if (key == GLFW_KEY_CAPS_LOCK) {}
		
		if (key == GLFW_KEY_TAB)
			InputStates[KEY_TAB] = false;

		if (key == GLFW_KEY_ESCAPE)
			InputStates[KEY_ESC] = false;

		if (key == GLFW_KEY_ENTER)
			InputStates[KEY_ENTER] = false;
		
		/*-----------------------------------
		|             COMMANDS              |
		-----------------------------------*/
		InputStates[KEY_PASTE] = false;
		InputStates[KEY_CUT] = false;


#ifndef _DEBUG
		std::cout << "Released Keys\n";
#endif
	}

}

void mouseCallBack(GLFWwindow* window, int button, int action, int mod) {
	switch (button) {
		case GLFW_MOUSE_BUTTON_LEFT:
			switch (action)
			{
				case GLFW_PRESS:
					InputStates[KEY_LCLICK] = true;
					break;
				case GLFW_RELEASE:
					InputStates[KEY_LCLICK] = false;
					break;
				default:
					break;
			}
			break;
		case GLFW_MOUSE_BUTTON_RIGHT:
			switch (action)
			{
				case GLFW_PRESS:
					InputStates[KEY_RCLICK] = true;
					break;
				case GLFW_RELEASE:
					InputStates[KEY_RCLICK] = false;
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}

}