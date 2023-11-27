/**************************************************************************
 * @file InputKeys.h
 * @author CHAN Aaron Jun Xiang - 100%
 * @par DP email: aaronjunxiang.chan@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 09-05-2023
 * @brief This file contains the implementation of the InputKeys class, which
 *		  provides functions to manage keyboard and mouse input states.
 *************************************************************************/
#ifndef INPUTKEYS_H
#define INPUTKEYS_H

#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <array>
#include <string>

void toggleFullScreen();

class InputSystem
{
public:

	/**************************************************************************
	 * @brief Constructor for the InputSystem class.
	 * @param None
	 * @return None
	 *************************************************************************/
	InputSystem();

	/**************************************************************************
	 * @brief Destructor for the InputSystem class.
	 * @param None
	 * @return None
	 *************************************************************************/
	~InputSystem();

	/**************************************************************************
	 * @brief Retrieves the state of a specific keyboard key.
	 * @param index The index of the keyboard key to check.
	 * @return An integer representing the state of the key: 0 for released, 1 for pressed, 2 for held.
	 *************************************************************************/
	int GetKeyState(int);

	/**************************************************************************
	 * @brief Sets the state of a specific keyboard key.
	 * @param index The index of the keyboard key to set the state for.
	 * @param value An integer representing the state to set: 0 for released, 1 for pressed, 2 for held.
	 * @return None
	 *************************************************************************/
	void SetKeyState(int, int);

	/**************************************************************************
	 * @brief Retrieves the state of a specific mouse button.
	 * @param index The index of the mouse button to check.
	 * @return A boolean indicating the state of the mouse button: true for pressed, false for released.
	 *************************************************************************/
	bool GetMouseState(int);

	/**************************************************************************
	 * @brief Sets the state of a specific mouse button.
	 * @param index The index of the mouse button to set.
	 * @param value The new state to assign: 1 for pressed, 0 for released.
	 *************************************************************************/
	void SetMouseState(int, int);

	/**************************************************************************
	 * @brief Retrieves the state of the mouse scroll wheel.
	 * @return An integer representing the scroll state: 1 for scrolling up, 0 for no scrolling, -1 for scrolling down.
	 *************************************************************************/
	int GetScrollState();

	/**************************************************************************
	 * @brief Sets the state of the mouse scroll wheel.
	 * @param value An integer representing the scroll state: 1 for scrolling up, 0 for no scrolling, -1 for scrolling down.
	 *************************************************************************/
	void SetScrollState(int);

	/**************************************************************************
	 * @brief Updates the total Y offset of the mouse scroll wheel.
	 * @param val The value to add to the total Y offset.
	 *************************************************************************/
	void UpdateScrollTotalYOffset(float);

	/**************************************************************************
	 * @brief Retrieves the total Y offset of the mouse scroll wheel.
	 * @return The total Y offset value.
	 *************************************************************************/
	float GetScrollTotalYOffset();


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
	void UpdateStatesForNextFrame();

	bool cheater{ false };
	bool typePW{ false };
	std::string hiddenconsole{};

private:
	// Define an array to keep track of key states
	std::array<int, GLFW_KEY_LAST + 1> keyStates{};

	// Define an array to keep track of mouse button states
	std::array<bool, GLFW_MOUSE_BUTTON_LAST + 1> mouseButtonStates{};

	// 1 for scrolling up, 0 for not scrolling, -1 for scrolling down
	int mouseScrollState{ 0 };

	// keeps track of total vertical scrolling
	float mouse_scroll_total_Y_offset;	

};



extern InputSystem inputSystem;


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
void KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mod);

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
void MouseCallBack(GLFWwindow* window, int button, int action, int mod);

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
void ScrollCallBack(GLFWwindow* window, double xOffset, double yOffset);

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
void WindowCloseCallback(GLFWwindow* window);

/**************************************************************************
 * @brief Callback function for handling window focus changes.
 *
 * This function is registered as a callback to be called when the focus of the
 * GLFW window changes. It is designed to respond to the window losing or gaining focus,
 * particularly when the user alt-tabs away from or back to the window.
 *
 * If the window loses focus (alt-tabbed away), it checks whether certain conditions
 * are met (not currently loading assets or the file browser not being open), and
 * if so, it minimizes the window and pauses all sounds using GLFW's `glfwIconifyWindow`
 * and a sound manager.
 *
 * If the window gains focus (alt-tabbed back), it restores the window using `glfwRestoreWindow`
 * and resumes all sounds through the sound manager.
 *
 * @param window The GLFW window that triggered the callback.
 * @param focused An integer indicating whether the window has gained (GLFW_TRUE) or lost (GLFW_FALSE) focus.
 *************************************************************************/
void windowFocusCallback(GLFWwindow* window, int focused);




#endif // INPUTKEYS_H