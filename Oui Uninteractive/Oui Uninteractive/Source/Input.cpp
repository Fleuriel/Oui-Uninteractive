/**************************************************************************
 * @file InputKeys.cpp
 * @author CHAN Aaron Jun Xiang
 * @par DP email: aaronjunxiang.chan@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 09-05-2023
 * @brief This file contains the implementation of the InputKeys class, which
 *		  provides functions to manage keyboard and mouse input states.
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
#include <Cheats.h>
#include <AssetManager.h>

InputSystem inputSystem;

// true for on, false for off
bool capsLockReleased{ true };
bool capsLockOn{ false };


// Pointer to the window
extern GLFWwindow* windowNew;



/**************************************************************************
 * @brief Constructor for the InputSystem class.
 * @param None
 * @return None
 *************************************************************************/
InputSystem::InputSystem()
{

}

/**************************************************************************
 * @brief Destructor for the InputSystem class.
 * @param None
 * @return None
 *************************************************************************/
InputSystem::~InputSystem()
{
	
}

/**************************************************************************
 * @brief Retrieves the state of a specific keyboard key.
 * @param index The index of the keyboard key to check.
 * @return An integer representing the state of the key: 0 for released, 1 for pressed, 2 for held.
 *************************************************************************/
int InputSystem::GetKeyState(int index) {
	return keyStates[index];
}

/**************************************************************************
 * @brief Sets the state of a specific keyboard key.
 * @param index The index of the keyboard key to set the state for.
 * @param value An integer representing the state to set: 0 for released, 1 for pressed, 2 for held.
 * @return None
 *************************************************************************/
void InputSystem::SetKeyState(int index, int value) {
	keyStates[index] = value;
}

/**************************************************************************
 * @brief Retrieves the state of a specific mouse button.
 * @param index The index of the mouse button to check.
 * @return A boolean indicating the state of the mouse button: true for pressed, false for released.
 *************************************************************************/
bool InputSystem::GetMouseState(int index) {
	return mouseButtonStates[index];
}

/**************************************************************************
 * @brief Sets the state of a specific mouse button.
 * @param index The index of the mouse button to set.
 * @param value The new state to assign: 1 for pressed, 0 for released.
 *************************************************************************/
void InputSystem::SetMouseState(int index, int value) {
	mouseButtonStates[index] = value;
}
/**************************************************************************
 * @brief Retrieves the state of the mouse scroll wheel.
 * @return An integer representing the scroll state: 1 for scrolling up, 0 for no scrolling, -1 for scrolling down.
 *************************************************************************/
int InputSystem::GetScrollState() {
	return mouseScrollState;
}

/**************************************************************************
 * @brief Sets the state of the mouse scroll wheel.
 * @param value An integer representing the scroll state: 1 for scrolling up, 0 for no scrolling, -1 for scrolling down.
 *************************************************************************/
void InputSystem::SetScrollState(int value) {
	mouseScrollState = value;
}

/**************************************************************************
 * @brief Updates the total Y offset of the mouse scroll wheel.
 * @param val The value to add to the total Y offset.
 *************************************************************************/
void InputSystem::UpdateScrollTotalYOffset(float val) {
	mouse_scroll_total_Y_offset += val;
}

/**************************************************************************
 * @brief Retrieves the total Y offset of the mouse scroll wheel.
 * @return The total Y offset value.
 *************************************************************************/
float InputSystem::GetScrollTotalYOffset() {
	return mouse_scroll_total_Y_offset;
}


int windowedWidth{};
int windowedHeight{};
int windowedXPos{};
int windowedYPos{};
bool fullScreen{};

void toggleFullScreen() {
	// Toggle fullscreen state
	if (glfwGetWindowMonitor(windowNew) == nullptr) {
		// If not fullscreen, make it fullscreen
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);

		// Store window dimensions before going fullscreen
		glfwGetWindowSize(windowNew, &windowedWidth, &windowedHeight);
		glfwGetWindowPos(windowNew, &windowedXPos, &windowedYPos);

		glfwSetWindowMonitor(windowNew, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);

		fullScreen = true;
	}
	else {
		// If fullscreen, make it windowed
		GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* primaryMode = glfwGetVideoMode(primaryMonitor);

		glfwSetWindowMonitor(windowNew, nullptr, windowedXPos, windowedYPos, windowedWidth, windowedHeight, GLFW_DONT_CARE);

		fullScreen = false;
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

	if (!inputSystem.typePW && !inputSystem.cheater) {

		/*
		Update the state of the pressed key
		 - If the key is pressed (action == GLFW_PRESS) and its state was not previously pressed,
		   set its state to 1 (pressed).
		 - If the key is released (action == GLFW_RELEASE), set its state to 0 (not pressed).
		 - If the key is held down (action == GLFW_REPEAT), set its state to 2 (held down).
		*/
		inputSystem.SetKeyState(key, (action == GLFW_PRESS && inputSystem.GetKeyState(key) == 0) ? 1 : (action == GLFW_RELEASE) ? 0 : 2);


#ifdef _DEBUG
		// Print debug information based on the key action (press, hold, release)
		//std::cout << ((action == GLFW_PRESS) ? "Pressed Keys\n" : (action == GLFW_REPEAT) ? "Held Keys\n" : "Released Keys\n");
#endif

		if (key == GLFW_KEY_CAPS_LOCK) capsLockReleased = (action == GLFW_RELEASE) ? true : false;

		

	}
	
	if (key == GLFW_KEY_F11 && action == GLFW_PRESS)
		toggleFullScreen();

	
	if (key == GLFW_KEY_F1 && action == GLFW_PRESS) { 
		std::cout << std::endl;
		inputSystem.typePW = true; 
	}

	if (inputSystem.typePW) {
		if (action == GLFW_PRESS) {
			if (key >= GLFW_KEY_A && key <= GLFW_KEY_Z) {
				char newchar{ 'a' + static_cast<char>(key - GLFW_KEY_A) };
					inputSystem.hiddenconsole += newchar;
				std::cout << newchar;
			}
			if (key == GLFW_KEY_ENTER) {
				if (inputSystem.hiddenconsole == "developermodeon") {
					inputSystem.cheater = true;
				}

				inputSystem.typePW = false;
				inputSystem.hiddenconsole = std::string("");
				std::cout << std::endl;
			}
		}
	}

	
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

	inputSystem.SetMouseState(button, (action == GLFW_PRESS) ? 1 : 0);

}


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
	inputSystem.UpdateScrollTotalYOffset(static_cast<float>(yOffset));

	//Change the scroll states based on y offset value
	inputSystem.SetScrollState((yOffset > 0) ? 1 : (yOffset == 0) ? 0 : -1);
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
void InputSystem::UpdateStatesForNextFrame() {

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




void windowFocusCallback(GLFWwindow* window, int focused) {
	// If alt tabbed away
	if (focused == GLFW_FALSE) {

		// Minimizes window if alt tabbed away
		if (!(assetManager.Currentlyloading || Editor::fileBrowserOpen))
			glfwIconifyWindow(windowNew);
		soundManager->PauseAll();

	}
	// If alt tabbed back to window
	else {

		// Resores window if alt tabbed back
		glfwRestoreWindow(windowNew);
		soundManager->ResumeAll();

	}

}

