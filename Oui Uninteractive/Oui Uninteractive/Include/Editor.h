/**************************************************************************
 * @file Editor.h
 * @author LOW Wang Chun, Mark
 * @par DP email: l.wangchunmark@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 13-09-2023
 * @brief This source file contains the code to setup and run the editor
 *************************************************************************/
#ifndef EDITOR_H
#define EDITOR_H

#include <vector>
#include <fstream>
#include <chrono>
#include "GameStateManager.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "implot.h"
#include "implot_internal.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/filewritestream.h"
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
	void Update();
	static void CreateMasterPanel();
	static void CreateSoundPanel();
	static void CreateObjectList();
	static void CreateDebugPanel();

public:
	bool soundPanel;

public:
	// ImGui colour definitions
	static const ImU32 whiteColour = IM_COL32(0, 0, 0, 255); // White color
	static const ImU32 redColour = IM_COL32(255, 0, 0, 255); // Red color
	static const ImU32 greenColour = IM_COL32(0, 255, 0, 255); // Green color
	static const ImU32 blueColour = IM_COL32(0, 0, 255, 255); // Blue color
	static const ImU32 pinkColour = IM_COL32(255, 0, 127, 255); // Pink color
	static const ImU32 yellowColour = IM_COL32(255, 255, 0, 255); // Yellow color
	static const ImU32 purpleColour = IM_COL32(147, 0, 255, 255); // Purple color
	
	// Buffer and limit for recording FPS performance
	size_t maxFPSdata;
	static std::vector<float> fpsData;

struct SystemTime {
	float physicsTime;
	float graphicsTime;
	float editorTime;
	float soundTime;
	float particlesTime;
};
static SystemTime timeRecorder;

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
