/**************************************************************************
 * @file InputKeys.cpp
 * @author CHAN Aaron Jun Xiang
 * @par DP email: aaronjunxiang.chan@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 09-05-2023
 * @brief This file does Input Handling and Callback Functions.
 *		  The functions include:
 *			- KeyCallBack
 * 			- MouseCallBack
 * 			- ScrollCallBack
 * 			- UpdateStatesForNextFrame
 * 			- WindowCloseCallback
 *************************************************************************/

#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <Input.h>
#include <iostream>
#include "SceneManager.h"
#include <array>
#include <functional>
#include <Physics.h>
#include <Editor.h>	
#include <ParticleSystem.h>


// Define an array to keep track of key states
std::array<int, GLFW_KEY_LAST + 1> keyStates;

// Define an array to keep track of mouse button states
std::array<bool, GLFW_MOUSE_BUTTON_LAST + 1> mouseButtonStates;

// 1 for scrolling up, 0 for not scrolling, -1 for scrolling down
int mouseScrollState{ 0 };

// true for on, false for off
bool capsLockReleased{ true };
bool capsLockOn{ false };

// Container to store commands (not implemented yet)
std::map<std::string, std::function<void()>> shortcuts;

//shortcuts["Ctrl+S"] = SaveFunction;
//shortcuts["Ctrl+Z"] = UndoFunction;

extern ParticleSystem particleSystem;


#define UNREFERENCED_PARAMETER(P)(P)
bool GetKeyInput(int glfwKey) {
	if (keyStates[glfwKey]) {
		return true;
	}
	else {
		return false;
	}
}
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
 * - When a key is pressed (action == GLFW_PRESS), it updates the keyStates array
 *   to record the state of alphabets, numbers, special keys, and keyboard commands.
 * - It also responds to specific key combinations like Ctrl+C, Ctrl+V, Ctrl+X, and Ctrl+Z
 *   for copy, paste, cut, and undo commands, respectively.
 * - Additionally, it can set or clear certain input states based on the key pressed,
 *   such as Caps Lock, Tab, and Escape.
 *
 * @note The UNREFERENCED_PARAMETER macro is used to suppress unused parameter warnings.
 * @note This function is typically registered with GLFW using glfwSetKeyCallback().
 *
 * @see keyStates - The array used to store the state of various keyboard keys.
 * @see glfwSetKeyCallback() - Function to register this callback with GLFW.
 *************************************************************************/
void KeyCallBack(GLFWwindow* window3, int key, int scancode, int action, int mod)
{
	(void)window3;
	(void)mod;
	(void)action;
	(void)scancode;

	// Return if unknown key pressed (e.g. multimedia keys)
	if (key == GLFW_KEY_UNKNOWN)
		return;

	// Suppress unused parameter warnings
	UNREFERENCED_PARAMETER(scancode);
	
	/* 
	Update the state of the pressed key
	 - If the key is pressed (action == GLFW_PRESS) and its state was not previously pressed,
	   set its state to 1 (pressed).
	 - If the key is released (action == GLFW_RELEASE), set its state to 0 (not pressed).
	 - If the key is held down (action == GLFW_REPEAT), set its state to 2 (held down).
	*/ 
	keyStates[key] = (action == GLFW_PRESS && keyStates[key] == 0) ? 1 : (action == GLFW_RELEASE) ? 0 : 2;
	//std::cout << "keyval : " << keyStates[key] << std::endl;

	#ifdef _DEBUG
		// Print debug information based on the key action (press, hold, release)
		std::cout << ((action == GLFW_PRESS) ? "Pressed Keys\n" : (action == GLFW_REPEAT) ? "Held Keys\n" : "Released Keys\n");
	#endif

		if (key == GLFW_KEY_CAPS_LOCK) capsLockReleased = (action == GLFW_RELEASE) ? true : false;
}



/**************************************************************************
 * @brief Callback function for handling mouse button input in a GLFW window.
 * 
 * This function is a callback used with the GLFW library to handle mouse button input events.
 * 
 * @param window The GLFW window that received the input.
 * @param button The mouse button that was pressed or released.
 * @param action The action taken (GLFW_PRESS or GLFW_RELEASE).
 * @param mod Bitfield describing which modifier keys (e.g., Shift, Ctrl, Alt) were held down.
 * 
 * This function updates the mouseButtonStates array based on mouse button input events. It specifically
 * records the state of the mouse buttons based on whether they are pressed or released.
 *
 * @note The UNREFERENCED_PARAMETER macro is used to suppress unused parameter warnings.
 * @note This function is typically registered with GLFW using glfwSetMouseButtonCallback().
 *
 * @see mouseButtonStates - The array used to store the state of various input events.
 * @see glfwSetMouseButtonCallback() - Function to register this callback with GLFW.
 *************************************************************************/
void MouseCallBack(GLFWwindow* window4, int button, int action, int mod) {

	(void)window4;

	(void)mod;
	//UNREFERENCED_PARAMETER(window);
	//UNREFERENCED_PARAMETER(mod);

	mouseButtonStates[button] = (action == GLFW_PRESS) ? 1 : 0;

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
 * scrolling that has occurred. It also sets the mouseScrollState variable to indicate whether scrolling
 * is in the upward (INPUT_SCROLLUP) or downward (INPUT_SCROLLDOWN) direction based on the `yOffset` value.
 *
 * @param mouse_scroll_total_Y_offset A global variable that tracks the total vertical scrolling.
 * @param mouseScrollState The array used to store the state of various input events.
 *
 * @note The UNREFERENCED_PARAMETER macro is not used in this function.
 * @note This function is typically registered with GLFW using glfwSetScrollCallback().
 *
 * @see mouse_scroll_total_Y_offset - Global variable to track total vertical scrolling.
 * @see mouseScrollState - The array used to store the state of various input events.
 * @see glfwSetScrollCallback() - Function to register this callback with GLFW.
 *************************************************************************/
void ScrollCallBack(GLFWwindow* window5, double xOffset, double yOffset ) {

	(void)xOffset;
	(void)window5;
	//UNREFERENCED_PARAMETER(window);
	//UNREFERENCED_PARAMETER(xOffset);

	//Update variable to track total vertical scrolling
	mouse_scroll_total_Y_offset += static_cast<float>(yOffset);

	//Change the scroll states based on y offset value
	mouseScrollState = (yOffset > 0) ? 1 : (yOffset == 0) ? 0 : -1;
}


/**************************************************************************
 * @brief Updates the states of keyboard keys and mouse scroll for the next frame.
 *
 * This function is typically called once per frame to update the state of keyboard
 * keys and reset the mouse scroll state for the next frame.
 *
 * @note It assumes that the `keyStates` array has been previously initialized to store
 *       the state of each keyboard key, and `mouseScrollState` has been initialized
 *       to store the state of the mouse scroll wheel.
 *************************************************************************/
void UpdateStatesForNextFrame() {

	// Loop through all keyboard keys (represented by indices)
	for (size_t i = 0; i < GLFW_KEY_LAST + 1; ++i) {

		// Update the state of each key
		// If the key state is 1 (pressed in the current frame), change it to 2 (held down)
		// If the key state is 0 (not pressed), it remains 0
		keyStates[i] = (keyStates[i] == 1) ? 2 : keyStates[i];
	}

	// Reset the mouse scroll state to 0 for the next frame
	mouseScrollState = 0;
}

/**************************************************************************
 * @brief Callback function for handling the window close event in a GLFW window.
 *
 * This function is a callback used with the GLFW library to handle the event
 * when the user attempts to close the application window.
 *
 * @param window The GLFW window that is being closed.
 *
 * When this function is triggered, it sets the `NextGameState` variable to a value
 * representing the state of quitting or closing the application. The specific value
 * used depends on the project's design and how it handles game states or application
 * flow control.
 *
 * @note NextGameState is a global variable used to manage the state of the application.
 *       The value assigned here typically represents the intention to quit or close
 *       the application.
 *************************************************************************/
void WindowCloseCallback(GLFWwindow* window6){
	(void)window6;
	NextGameState = STATE_QUIT;
}