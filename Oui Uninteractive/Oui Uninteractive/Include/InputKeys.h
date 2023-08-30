#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#ifndef INPUTKEYS_H
#define INPUTKEYS_H

// A = 0, B = 1, C = 2 ... Z = 25
extern std::vector<bool> keyStatesAlphabet;

// Might need to change ...
extern std::vector<bool> mouseStates;

void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mod);



#endif // INPUTKEYS_H