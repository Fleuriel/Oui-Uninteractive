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

// REFER TO keyDefinition.h for the index values
extern std::vector<bool> InputStates;

void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mod);

void mouseCallBack(GLFWwindow* window, int button, int action, int mod);

void scrollCallBack(GLFWwindow* window, double xOffset, double yOffset);

void windowCloseCallback(GLFWwindow* window);

#endif // INPUTKEYS_H