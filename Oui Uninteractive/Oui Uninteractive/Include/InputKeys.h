/**************************************************************************
 * @file InputKeys.h
 * @author 
 * @par DP email: 
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 09-05-2023
 * @brief 
 *************************************************************************/

#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#ifndef INPUTKEYS_H
#define INPUTKEYS_H

// Define an array to keep track of key states
extern std::array<int, GLFW_KEY_LAST + 1> keyStates;

// Define an array to keep track of mouse button states
extern std::array<bool, GLFW_MOUSE_BUTTON_LAST + 1> mouseButtonStates;

// 1 for scrolling up, 0 for not scrolling, -1 for scrolling down
extern int mouseScrollState;

void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mod);

void mouseCallBack(GLFWwindow* window, int button, int action, int mod);

void scrollCallBack(GLFWwindow* window, double xOffset, double yOffset);

void windowCloseCallback(GLFWwindow* window);

#endif // INPUTKEYS_H