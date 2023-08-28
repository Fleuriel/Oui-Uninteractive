/*!
@file       glhelper.cpp
@author     pghali@digipen.edu
@coauthor   tan.a@digipen.edu
@date       26/05/2023

This file implements functionality useful and necessary to build OpenGL
applications including use of external APIs such as GLFW to create a
window and start up an OpenGL context and use GLEW to extract function
pointers to OpenGL implementations.

*//*__________________________________________________________________________*/

/*                                                                   includes
----------------------------------------------------------------------------- */
#include <glhelper.h>
#include <iostream>

/*                                                   objects with file scope
----------------------------------------------------------------------------- */
// static data members declared in GLHelper
GLint GLHelper::width;
GLint GLHelper::height;
GLdouble GLHelper::fps;
GLdouble GLHelper::delta_time;
std::string GLHelper::title;
GLFWwindow* GLHelper::ptr_window;

GLboolean GLHelper::keystateP = GL_FALSE;
GLboolean GLHelper::LMouseState = GL_FALSE;

#define UNREFERENCED_PARAMETER(P)(P)

/*  _________________________________________________________________________ */
/*! init

@param GLint width
@param GLint height
Dimensions of window requested by program

@param std::string title_str
String printed to window's title bar

@return bool
true if OpenGL context and GLEW were successfully initialized.
false otherwise.

Uses GLFW to create OpenGL context. GLFW's initialization follows from here:
http://www.glfw.org/docs/latest/quick.html
a window of size width x height pixels
and its associated OpenGL context that matches a core profile that is
compatible with OpenGL 4.5 and doesn't support "old" OpenGL, has 32-bit RGBA,
double-buffered color buffer, 24-bit depth buffer and 8-bit stencil buffer
with each buffer of size width x height pixels
*/
bool GLHelper::init(GLint w, GLint h, std::string t) {
    GLHelper::width = w;
    GLHelper::height = h;
    GLHelper::title = t;

    // Part 1
    if (!glfwInit()) {
        std::cout << "GLFW init has failed - abort program!!!" << std::endl;
        return false;
    }

    // In case a GLFW function fails, an error is reported to callback function
    glfwSetErrorCallback(GLHelper::error_cb);

    // Before asking GLFW to create an OpenGL context, we specify the minimum constraints
    // in that context:
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_RED_BITS, 8); glfwWindowHint(GLFW_GREEN_BITS, 8);
    glfwWindowHint(GLFW_BLUE_BITS, 8); glfwWindowHint(GLFW_ALPHA_BITS, 8);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); // window dimensions are static

    GLHelper::ptr_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!GLHelper::ptr_window) {
        std::cerr << "GLFW unable to create OpenGL context - abort program\n";
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(GLHelper::ptr_window);

    glfwSetFramebufferSizeCallback(GLHelper::ptr_window, GLHelper::fbsize_cb);
    glfwSetKeyCallback(GLHelper::ptr_window, GLHelper::key_cb);
    glfwSetMouseButtonCallback(GLHelper::ptr_window, GLHelper::mousebutton_cb);
    glfwSetCursorPosCallback(GLHelper::ptr_window, GLHelper::mousepos_cb);
    glfwSetScrollCallback(GLHelper::ptr_window, GLHelper::mousescroll_cb);

    // this is the default setting ...
    glfwSetInputMode(GLHelper::ptr_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    // Part 2: Initialize entry points to OpenGL functions and extensions
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        std::cerr << "Unable to initialize GLEW - error: "
            << glewGetErrorString(err) << " abort program" << std::endl;
        return false;
    }
    if (GLEW_VERSION_4_5) {
        std::cout << "Using glew version: " << glewGetString(GLEW_VERSION) << std::endl;
        std::cout << "Driver supports OpenGL 4.5\n" << std::endl;
    }
    else {
        std::cerr << "Driver doesn't support OpenGL 4.5 - abort program" << std::endl;
        return false;
    }

    return true;
}


/*  _________________________________________________________________________ */
/*! cleanup

@param none

@return none

For now, there are no resources allocated by the application program.
The only task is to have GLFW return resources back to the system and
gracefully terminate.
*/
void GLHelper::cleanup() {
    // Part 1
    glfwTerminate();
}

/*  _________________________________________________________________________*/
/*! key_cb

@param GLFWwindow*
Handle to window that is receiving event

@param int
the keyboard key that was pressed or released

@parm int
Platform-specific scancode of the key

@parm int
GLFW_PRESS, GLFW_REPEAT or GLFW_RELEASE
action will be GLFW_KEY_UNKNOWN if GLFW lacks a key token for it,
for example E-mail and Play keys.

@parm int
bit-field describing which modifier keys (shift, alt, control)
were held down

@return none

This function is called when keyboard buttons are pressed.
When the ESC key is pressed, the close flag of the window is set.
*/
void GLHelper::key_cb(GLFWwindow* pwin, int key, int scancode, int
    action, int mod) {
    UNREFERENCED_PARAMETER(mod);
    UNREFERENCED_PARAMETER(scancode);

    // key state changes from released to pressed
    if (GLFW_PRESS == action) {
        if (GLFW_KEY_ESCAPE == key) {
            glfwSetWindowShouldClose(pwin, GLFW_TRUE);
        }
#ifdef _DEBUG
        std::cout << "Pressed/Triggered (Mouse)\n";
#endif
        keystateP = (key == GLFW_KEY_P) ? GL_TRUE : GL_FALSE;
    }
    else if (GLFW_REPEAT == action) {
#ifdef _DEBUG
        std::cout << "Repeat/Held Down (Mouse)\n";
#endif
        // key state was and is being pressed
        keystateP = GL_FALSE;
    }
    else if (GLFW_RELEASE == action) {
#ifdef _DEBUG
        std::cout << "Released (Mouse)\n";
#endif
        // key start changes from pressed to released
        keystateP = GL_FALSE;
    }
}


/*  _________________________________________________________________________*/
/*! mousebutton_cb

@param GLFWwindow*
Handle to window that is receiving event

@param int
the mouse button that was pressed or released
GLFW_MOUSE_BUTTON_LEFT and GLFW_MOUSE_BUTTON_RIGHT specifying left and right
mouse buttons are most useful

@parm int
action is either GLFW_PRESS or GLFW_RELEASE

@parm int
bit-field describing which modifier keys (shift, alt, control)
were held down

@return none

This function is called when mouse buttons are pressed.
*/
void GLHelper::mousebutton_cb(GLFWwindow* pwin, int button, int action, int mod) {
    UNREFERENCED_PARAMETER(pwin);
    UNREFERENCED_PARAMETER(mod);

    switch (button) {
    case GLFW_MOUSE_BUTTON_LEFT:
#ifdef _DEBUG
        std::cout << "Left mouse button ";
#endif


        break;
    case GLFW_MOUSE_BUTTON_RIGHT:
#ifdef _DEBUG
        std::cout << "Right mouse button ";
#endif
        break;
    }
    switch (action) {
    case GLFW_PRESS:
#ifdef _DEBUG
        std::cout << "pressed!!!" << std::endl;
#endif
        // key state changes from released to pressed
        LMouseState = (button == GLFW_MOUSE_BUTTON_LEFT) ? GL_TRUE : GL_FALSE;
        break;

    case GLFW_RELEASE:

#ifdef _DEBUG
        std::cout << "released!!!" << std::endl;
#endif

        // else set to false.
        LMouseState = GL_FALSE;

        break;
    }
}

/*  _________________________________________________________________________*/
/*! mousepos_cb

@param GLFWwindow*
Handle to window that is receiving event

@param double
new cursor x-coordinate, relative to the left edge of the client area

@param double
new cursor y-coordinate, relative to the top edge of the client area

@return none

This functions receives the cursor position, measured in screen coordinates but
relative to the top-left corner of the window client area.
*/
void GLHelper::mousepos_cb(GLFWwindow* pwin, double xpos, double ypos) {


    UNREFERENCED_PARAMETER(pwin);
    UNREFERENCED_PARAMETER(xpos);
    UNREFERENCED_PARAMETER(ypos);
#ifdef _DEBUG
    std::cout << "Mouse cursor position: (" << xpos << ", " << ypos << ")" << std::endl;
#endif
}

/*  _________________________________________________________________________*/
/*! mousescroll_cb

@param GLFWwindow*
Handle to window that is receiving event

@param double
Scroll offset along X-axis

@param double
Scroll offset along Y-axis

@return none

This function is called when the user scrolls, whether with a mouse wheel or
touchpad gesture. Although the function receives 2D scroll offsets, a simple
mouse scroll wheel, being vertical, provides offsets only along the Y-axis.
*/
void GLHelper::mousescroll_cb(GLFWwindow* pwin, double xoffset, double yoffset) {


    UNREFERENCED_PARAMETER(pwin);
    UNREFERENCED_PARAMETER(xoffset);
    UNREFERENCED_PARAMETER(yoffset);

#ifdef _DEBUG
    std::cout << "Mouse scroll wheel offset: ("
        << xoffset << ", " << yoffset << ")" << std::endl;
#endif
}

/*  _________________________________________________________________________ */
/*! error_cb

@param int
GLFW error code

@parm char const*
Human-readable description of the code

@return none

The error callback receives a human-readable description of the error and
(when possible) its cause.
*/
void GLHelper::error_cb(int error, char const* description) {

    UNREFERENCED_PARAMETER(error);
    UNREFERENCED_PARAMETER(description);

#ifdef _DEBUG
    std::cerr << "GLFW error: " << description << std::endl;
#endif
}

/*  _________________________________________________________________________ */
/*! fbsize_cb

@param GLFWwindow*
Handle to window that is being resized

@parm int
Width in pixels of new window size

@parm int
Height in pixels of new window size

@return none

This function is called when the window is resized - it receives the new size
of the window in pixels.
*/
void GLHelper::fbsize_cb(GLFWwindow* ptr_win, int w, int h) {

    UNREFERENCED_PARAMETER(ptr_win);
#ifdef _DEBUG
    std::cout << "fbsize_cb getting called!!!" << std::endl;
#endif
    // use the entire framebuffer as drawing region
    glViewport(0, 0, w, h);
    // later, if working in 3D, we'll have to set the projection matrix here ...
}

/*  _________________________________________________________________________*/
/*! update_time

@param double
fps_calc_interval: the interval (in seconds) at which fps is to be
calculated

This function must be called once per game loop. It uses GLFW's time functions
to compute:
1. the interval in seconds between each frame
2. the frames per second every "fps_calc_interval" seconds
*/
void GLHelper::update_time(double fps_calc_interval) {
    // get elapsed time (in seconds) between previous and current frames
    static double prev_time = glfwGetTime();
    double curr_time = glfwGetTime();
    delta_time = curr_time - prev_time;
    prev_time = curr_time;

    // fps calculations
    static double count = 0.0; // number of game loop iterations
    static double start_time = glfwGetTime();
    // get elapsed time since very beginning (in seconds) ...
    double elapsed_time = curr_time - start_time;

    ++count;

    // update fps at least every 10 seconds ...
    fps_calc_interval = (fps_calc_interval < 0.0) ? 0.0 : fps_calc_interval;
    fps_calc_interval = (fps_calc_interval > 10.0) ? 10.0 : fps_calc_interval;
    if (elapsed_time > fps_calc_interval) {
        GLHelper::fps = count / elapsed_time;
        start_time = curr_time;
        count = 0.0;
    }
}






// Printing the specifications of GPU to the terminal
void GLHelper::print_specs()
{
    // Declare and Definition of variables...
    GLubyte const* str_GPU_Vendor = glGetString(GL_VENDOR);                             // String type for GPU Vendor
    GLubyte const* str_GPU_Renderer = glGetString(GL_RENDERER);                           // String type for GPU Renderer
    GLubyte const* str_GPU_Ver = glGetString(GL_VERSION);                            // String type for GPU Version
    GLubyte const* str_GPU_Shader_Ver = glGetString(GL_SHADING_LANGUAGE_VERSION);           // String type for GPU Shader


    // Versions....
    GLint   tex_GPU_Major_Ver;                                                               // OpenGL Function to acquire integer values
    GLint   tex_GPU_Minor_Ver;                                                               // OpenGL Function to acquire integer values

    glGetIntegerv(GL_MAJOR_VERSION, &tex_GPU_Major_Ver);                                     // GL Major
    glGetIntegerv(GL_MINOR_VERSION, &tex_GPU_Minor_Ver);                                     // GL Minor


    // Vertex/Indices Count
    GLint   tex_Vert_Cnt;                                                                    // Integer type for vertices counts.   (ONLY FOR CURRENT PLATFORM)
    GLint   tex_Ind_Cnt;                                                                     // Integer type for indices counts.    (ONLY FOR CURRENT PLATFORM)
    GLint   tex_GL_Max_Texture_Sz;                                                           // Integer type for max texture size.  (ONLY FOR CURRENT PLATFORM)
    GLint   tex_Max_Viewport_Dim[2];                                                         // Dimensions are such as [1366 x 768]. therefore Dim[2] = Dim[X], Dim[Y]

    glGetIntegerv(GL_MAX_ELEMENTS_VERTICES, &tex_Vert_Cnt);                                  // OpenGL Function to acquire integer values
    glGetIntegerv(GL_MAX_ELEMENTS_INDICES, &tex_Ind_Cnt);                                    // OpenGL Function to acquire integer values
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &tex_GL_Max_Texture_Sz);                              // OpenGL Function to acquire integer values
    glGetIntegerv(GL_MAX_VIEWPORT_DIMS, tex_Max_Viewport_Dim);                               // OpenGL Function to acquire integer values

    // Is the GPU using double buffering?
    GLboolean doubleBuffer;                                                                  // Boolean type for doubleBuffer
    glGetBooleanv(GL_DOUBLEBUFFER, &doubleBuffer);                                           // OpenGL Function to acquire boolean values.

    // Printing out the variables...
    std::cout << "GPU Vendor: " << str_GPU_Vendor << '\n';
    std::cout << "GL Renderer: " << str_GPU_Renderer << '\n';
    std::cout << "GL Version: " << str_GPU_Ver << '\n';
    std::cout << "GL Shader Version: " << str_GPU_Shader_Ver << '\n';
    std::cout << "GL Major Version: " << tex_GPU_Major_Ver << '\n';
    std::cout << "GL Minor Version: " << tex_GPU_Minor_Ver << '\n';
    std::cout << "Current OpenGL Context is " << (doubleBuffer ? "double buffered\n" : "not double buffered\n");
    std::cout << "Maximum Vertex Count: " << tex_Vert_Cnt << '\n';
    std::cout << "Maximum Indices Count: " << tex_Ind_Cnt << '\n';
    std::cout << "GL Maximum texture size: " << tex_GL_Max_Texture_Sz << '\n';
    std::cout << "Maximum Viewport Dimensions: " << tex_Max_Viewport_Dim[0] << " x " << tex_Max_Viewport_Dim[1] << '\n';
}
