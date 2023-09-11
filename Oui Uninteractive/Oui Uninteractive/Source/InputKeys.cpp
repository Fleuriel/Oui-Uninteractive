/**************************************************************************
 * @file InputKeys.cpp
 * @author 
 * @par DP email: 
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 09-05-2023
 * @brief 
 *************************************************************************/

#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <InputKeys.h>
#include <keyDefinition.h>
#include <iostream>
#include <GameStateManager.h>


 std::vector<bool> InputStates(NUMBER_OF_INPUT_STATES, false);

#define UNREFERENCED_PARAMETER(P)(P)

int lastkeyedcommand;

/**************************************************************************
 * @brief Callback function for handling keyboard input in a GLFW window.
 * 
 * This function is a callback used with the GLFW library to handle keyboard input events.
 * 
 * @param window The GLFW window that received the input.
 * @param key The keyboard key code that was pressed or released.
 * @param scancode The system-specific scancode of the key.
 * @param action The action taken (GLFW_PRESS, GLFW_RELEASE, GLFW_REPEAT).
 * @param mod Bitfield describing which modifier keys (e.g., Shift, Ctrl, Alt) were held down.
 * 
 * This function updates various input states based on the keyboard input events.
 * - When a key is pressed (action == GLFW_PRESS), it updates the InputStates array
 *   to record the state of alphabets, numbers, special keys, and keyboard commands.
 * - It also responds to specific key combinations like Ctrl+C, Ctrl+V, Ctrl+X, and Ctrl+Z
 *   for copy, paste, cut, and undo commands, respectively.
 * - Additionally, it can set or clear certain input states based on the key pressed,
 *   such as Caps Lock, Tab, and Escape.
 *
 * @note The UNREFERENCED_PARAMETER macro is used to suppress unused parameter warnings.
 * @note This function is typically registered with GLFW using glfwSetKeyCallback().
 *
 * @see InputStates - The array used to store the state of various keyboard keys.
 * @see glfwSetKeyCallback() - Function to register this callback with GLFW.
 *************************************************************************/
void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mod)
{
	UNREFERENCED_PARAMETER(scancode);
	

/***********************************************************************/
	if (action == GLFW_PRESS)
	{
		if (GLFW_KEY_ESCAPE == key)
		{
			glfwSetWindowShouldClose(window, GLFW_TRUE);
			//glfwWindowShouldClose(window);
			CurrentGameState = STATE_QUIT;
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
		InputStates[INPUT_UNDO] = false;


#ifndef _DEBUG
		std::cout << "Released Keys\n";
#endif
	}

}

/**************************************************************************
 * @brief Callback function for handling mouse button input in a GLFW window.
 * 
 * This function is a callback used with the GLFW library to handle mouse button input events.
 * 
 * @param window The GLFW window that received the input.
 * @param button The mouse button that was pressed or released (GLFW_MOUSE_BUTTON_LEFT or GLFW_MOUSE_BUTTON_RIGHT).
 * @param action The action taken (GLFW_PRESS or GLFW_RELEASE).
 * @param mod Bitfield describing which modifier keys (e.g., Shift, Ctrl, Alt) were held down.
 * 
 * This function updates the InputStates array based on mouse button input events. It specifically
 * records the state of the left and right mouse buttons (INPUT_LCLICK and INPUT_RCLICK) based on
 * whether they are pressed or released.
 *
 * @note The UNREFERENCED_PARAMETER macro is used to suppress unused parameter warnings.
 * @note This function is typically registered with GLFW using glfwSetMouseButtonCallback().
 *
 * @see InputStates - The array used to store the state of various input events.
 * @see glfwSetMouseButtonCallback() - Function to register this callback with GLFW.
 *************************************************************************/
void mouseCallBack(GLFWwindow* window, int button, int action, int mod) {

	//UNREFERENCED_PARAMETER(window);
	//UNREFERENCED_PARAMETER(mod);

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

/**************************************************************************
 * @brief Callback function for handling mouse scroll wheel input in a GLFW window.
 * 
 * This function is a callback used with the GLFW library to handle mouse scroll wheel input events.
 * 
 * @param window The GLFW window that received the input.
 * @param xOffset The horizontal scroll offset (not used in this function).
 * @param yOffset The vertical scroll offset, indicating the amount of scrolling.
 * 
 * This function updates the `mouse_scroll_total_Y_offset` variable to keep track of the total vertical
 * scrolling that has occurred. It also sets the InputStates array to indicate whether scrolling
 * is in the upward (INPUT_SCROLLUP) or downward (INPUT_SCROLLDOWN) direction based on the `yOffset` value.
 *
 * @param mouse_scroll_total_Y_offset A global variable that tracks the total vertical scrolling.
 * @param InputStates The array used to store the state of various input events.
 *
 * @note The UNREFERENCED_PARAMETER macro is not used in this function.
 * @note This function is typically registered with GLFW using glfwSetScrollCallback().
 *
 * @see mouse_scroll_total_Y_offset - Global variable to track total vertical scrolling.
 * @see InputStates - The array used to store the state of various input events.
 * @see glfwSetScrollCallback() - Function to register this callback with GLFW.
 *************************************************************************/
void scrollCallBack(GLFWwindow* window, double xOffset, double yOffset ) {

	//UNREFERENCED_PARAMETER(window);
	//UNREFERENCED_PARAMETER(xOffset);

	//Update variable to track total vertical scrolling
	mouse_scroll_total_Y_offset += yOffset;

	//Change the scroll states based on y offset value
	InputStates[INPUT_SCROLLUP] = (yOffset > 0) ? true : false;
	InputStates[INPUT_SCROLLDOWN] = (yOffset < 0) ? true : false;

}