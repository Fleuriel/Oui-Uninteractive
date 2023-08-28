#include <vector>



#ifndef INPUTKEYS_H
#define INPUTKEYS_H


extern std::vector<bool> keyStatesAlphabet;

// Might need to change ...
extern std::vector<bool> mouseStates;

void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mod);



#endif // INPUTKEYS_H