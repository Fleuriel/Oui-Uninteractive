#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <InputKeys.h>
#include <keyDefinition.h>
#include <iostream>
#include <InitializeEngine.h>


 std::vector<bool> InputStates(Number_of_Input_States, false);

#define UNREFERENCED_PARAMETER(P)(P)

 int lastkeyedcommand;

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
			InputStates[key - GLFW_KEY_0 + INPUT_0] = true;

		/*-----------------------------------
		|              OTHERS               |
		-----------------------------------*/
		if (key == GLFW_KEY_SPACE)
			InputStates[INPUT_SPACE] = true;

		if (key == GLFW_KEY_LEFT_ALT || key == GLFW_KEY_RIGHT_ALT)
			InputStates[INPUT_ALT] = true;

		if (key == GLFW_KEY_LEFT_CONTROL || key == GLFW_KEY_RIGHT_CONTROL)
			InputStates[INPUT_CTRL] = true;

		if (key == GLFW_KEY_LEFT_SHIFT || key == GLFW_KEY_RIGHT_SHIFT)
			InputStates[INPUT_SHIFT] = true;

		if (key == GLFW_KEY_CAPS_LOCK)
			InputStates[INPUT_CAPS] = !InputStates[INPUT_CAPS];

		if (key == GLFW_KEY_TAB)
			InputStates[INPUT_TAB] = true;

		if (key == GLFW_KEY_ESCAPE)
			InputStates[INPUT_ESC] = true;

		if (key == GLFW_KEY_ENTER)
			InputStates[INPUT_ENTER] = true;

		/*-----------------------------------
		|             COMMANDS              |
		-----------------------------------*/
		if (key == GLFW_KEY_C && mod & GLFW_MOD_CONTROL) {
			InputStates[INPUT_COPY] = true;
			lastkeyedcommand = INPUT_COPY;
		}

		if (key == GLFW_KEY_V && mod & GLFW_MOD_CONTROL && InputStates[INPUT_COPY]) {
			InputStates[INPUT_PASTE] = true;
			lastkeyedcommand = INPUT_PASTE;
		}

		if (key == GLFW_KEY_X && mod & GLFW_MOD_CONTROL) {
			InputStates[INPUT_CUT] = true;
			lastkeyedcommand = INPUT_CUT;
		}

		if (key == GLFW_KEY_Z && mod & GLFW_MOD_CONTROL) {
			InputStates[INPUT_UNDO] = true;
			lastkeyedcommand = INPUT_UNDO;
		}

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
			InputStates[key - GLFW_KEY_0 + INPUT_0] = false;

		/*-----------------------------------
		|              OTHERS               |
		-----------------------------------*/
		if (key == GLFW_KEY_SPACE)
			InputStates[INPUT_SPACE] = false;

		if (key == GLFW_KEY_LEFT_ALT || key == GLFW_KEY_RIGHT_ALT)
			InputStates[INPUT_ALT] = false;

		if (key == GLFW_KEY_LEFT_CONTROL || key == GLFW_KEY_RIGHT_CONTROL)
			InputStates[INPUT_CTRL] = false;

		if (key == GLFW_KEY_LEFT_SHIFT || key == GLFW_KEY_RIGHT_SHIFT)
			InputStates[INPUT_SHIFT] = false;
		
		if (key == GLFW_KEY_CAPS_LOCK) {}
		
		if (key == GLFW_KEY_TAB)
			InputStates[INPUT_TAB] = false;

		if (key == GLFW_KEY_ESCAPE)
			InputStates[INPUT_ESC] = false;

		if (key == GLFW_KEY_ENTER)
			InputStates[INPUT_ENTER] = false;
		
		/*-----------------------------------
		|             COMMANDS              |
		-----------------------------------*/
		InputStates[INPUT_PASTE] = false;
		InputStates[INPUT_CUT] = false;


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
					InputStates[INPUT_LCLICK] = true;
					break;
				case GLFW_RELEASE:
					InputStates[INPUT_LCLICK] = false;
					break;
				default:
					break;
			}
			break;
		case GLFW_MOUSE_BUTTON_RIGHT:
			switch (action)
			{
				case GLFW_PRESS:
					InputStates[INPUT_RCLICK] = true;
					break;
				case GLFW_RELEASE:
					InputStates[INPUT_RCLICK] = false;
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}

}

float mouse_scroll_total_Y_offset;	// KEEPS TRACK OF TOTAL VERTICAL SCROLLING

void scrollCallBack(GLFWwindow* window, double xOffset, double yOffset ) {

	//Update variable to track total vertical scrolling
	mouse_scroll_total_Y_offset += yOffset;

	//Change the scroll states based on y offset value
	InputStates[INPUT_SCROLLUP] = (yOffset > 0) ? true : false;
	InputStates[INPUT_SCROLLDOWN] = (yOffset < 0) ? true : false;

}