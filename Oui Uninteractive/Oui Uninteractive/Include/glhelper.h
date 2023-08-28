/* !
@file		glhelper.h
@author		pghali@digipen.edu
@coauthor	tan.a@digipen.edu
@date       19/07/2023

This file contains the declaration of namespace Helper that encapsulates the
functionality required to create an OpenGL context using GLFW; use GLEW
to load OpenGL extensions; initialize OpenGL state; and finally initialize
the OpenGL application by calling initalization functions associated with
objects participating in the application.

*//*__________________________________________________________________________*/

/*                                                                      guard
----------------------------------------------------------------------------- */
#ifndef GLHELPER_H
#define GLHELPER_H

/*                                                                   includes
----------------------------------------------------------------------------- */
#include <GL/glew.h> // for access to OpenGL API declarations 
#include <GLFW/glfw3.h>
#include <string>
#include <vector>

/*  _________________________________________________________________________ */
struct GLHelper
  /*! GLHelper structure to encapsulate initialization stuff ...
  */
{
  static bool init(GLint w, GLint h, std::string t);
  static void cleanup();

  // callbacks ...
  static void error_cb(int error, char const* description);
  static void fbsize_cb(GLFWwindow *ptr_win, int w, int h);
  // I/O callbacks ...
  static void key_cb(GLFWwindow *pwin, int key, int scancode, int action, int mod);
  static void mousebutton_cb(GLFWwindow *pwin, int button, int action, int mod);
  static void mousescroll_cb(GLFWwindow *pwin, double xoffset, double yoffset);
  static void mousepos_cb(GLFWwindow *pwin, double xpos, double ypos);

  static void update_time(double fpsCalcInt = 1.0);

  static GLint width, height;			// Width and height of the window.
  static GLdouble fps;					// FPS of the window
  static GLdouble delta_time;			// time taken to complete most recent game loop
  static std::string title;				// Title of the window
  static GLFWwindow *ptr_window;		// the pointer of the window client.

  /*  _________________________________________________________________________ */
  /*! parameters
  
   At this point, we might assume that I need to use more keys, therefore to mitigate repetitiveness
   of initializing 26 times, I Created a vector container for my bool ...
  */
  static std::vector<bool> keyStatesAlphabet;
  static std::vector<bool> mouseStates;

  static GLboolean keystateP;			// keystate boolean for 'P' Key
  static GLboolean LMouseState;			// Mouse state boolean for 'L Mouse Button/Mouse Button 1' 
  static void print_specs();
};

#endif /* GLHELPER_H */
