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
#include <Sound.h>

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
	static void CreateMasterPanel();
	static void CreateSoundPanel();
	static void CreateObjectList();
	static bool ReadJSONFile(std::string filePath, rapidjson::Document &docRef);
	static bool WriteJSONFile(std::string filePath, rapidjson::Document& docRef);

public:
	bool soundPanel;
private:

};

// Store panel selection
struct Panels {
	bool soundPanel;
	bool objectPanel;
	bool Panel1;
};
static Panels panelList;

// Temporary simulation of obj data 
struct tempObjData {
	std::string name;
	int size;
	std::string colour;
	float smell;
	bool alive;
};	
static tempObjData objList;