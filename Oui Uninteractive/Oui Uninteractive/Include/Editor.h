/**************************************************************************
 * @file Editor.h
 * @author Mark Low
 * @par DP email: l.wangchunmark@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 13-09-2023
 * @brief This source file contains the code to setup and run the editor
 *************************************************************************/
#ifndef EDITOR_H
#define EDITOR_H

#include "GameStateManager.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/filewritestream.h"
#include <vector>
#include <fstream>
#include "Sound.h"
#include "ObjectFactory.h"
#include "Transform.h"
#include "PhysicsBody.h"
#include "Input.h"

#define GET_COMPONENT(GameObject, Component, ComponentType) (GameObject->GetComponentType<Component>(ComponentType))


class UsingImGui {
public:
	void Init(GLFWwindow* window, const char* glsl_vers);
	void CreateFrame();
	virtual void Update();
	void Draw();
	void Exit();
	static void HelpMarker(std::string desc);
};


class Editor {
public:
	void Init();
	static void CreateMasterPanel();
	static void CreateSoundPanel();
	static void CreateObjectList();
	static void CreateDebugPanel();

public:
	bool soundPanel;
private:

};

// Store panel selection
struct Panels {
	bool soundPanel;
	bool objectPanel;
	bool debugPanel;
};
static Panels panelList;

#endif
