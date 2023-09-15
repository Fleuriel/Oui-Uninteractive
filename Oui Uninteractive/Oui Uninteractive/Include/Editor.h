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
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/filewritestream.h"
#include <vector>
#include <fstream>

class UsingImGui {
public:
	void Init(GLFWwindow* window, const char* glsl_vers);
	void CreateFrame();
	virtual void Update();
	void Draw();
	void Exit();
};


class Editor {
public:
	void Init();
	bool ReadJSONFile(const char* filePath, rapidjson::Document &docRef);
	bool WriteJSONFile(const char* filePath, rapidjson::Document& docRef);
private:

};

// Temporry simulation of obj data 
struct tempObjData {
	std::string name;
	int size;
	std::string colour;
	float smell;
	bool alive;
};	
static tempObjData objList;