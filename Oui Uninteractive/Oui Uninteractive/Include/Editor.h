/**************************************************************************
 * @file Editor.h
 * @author
 * @par DP email:
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 09-05-2023
 * @brief This header file contains the code to setup and run the editor
 *************************************************************************/

#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

class UsingImGui {
public:
	void Init(GLFWwindow* window, const char* glsl_vers);
	void CreateFrame();
	virtual void Update();
	void Draw();
	void Exit();
};