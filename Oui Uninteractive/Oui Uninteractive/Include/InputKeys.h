#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#ifndef INPUTKEYS_H
#define INPUTKEYS_H

// A = 0, B = 1, C = 2 ... Z = 25
extern std::vector<bool> InputStates;

// Might need to change ...
extern std::vector<bool> mouseStates;

void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mod);

void mouseCallBack(GLFWwindow* window, int button, int action, int mod);

void scrollCallBack(GLFWwindow* window, double xOffset, double yOffset);


#endif // INPUTKEYS_H