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

#include <filesystem>
#include <vector>
#include <fstream>
#include <chrono>
#include <cmath>
#include "GameStateManager.h"
#include "imgui.h"
#include "imgui_stdlib.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_stdlib.h"
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
#include "OpenGLObjects.h"
#include "FontManager.h"
#include "Filepaths.h"
#include "Collider.h"
#include "Logic.h"
#include "TilemapLoader.h"
#define NOMINMAX // Suppresses min/max keywords in windows to deconflict with std::min/max
#include <Windows.h>


#define GET_COMPONENT(GameObject, Component, ComponentType) (GameObject->GetComponentType<Component>(ComponentType))
#define GET_PREFAB_COMPONENT(Prefab, Component, ComponentType) (Prefab->GetComponentType<Component>(ComponentType))


class UsingImGui {
public:
	void Init(GLFWwindow* window, const char* glsl_vers);
	void LoadFonts();
	void CreateFrame();
	virtual void Update();
	void Draw();
	void Exit();
	static void HelpMarker(std::string desc);
};

class TimeProfiler {
public:
	TimeProfiler(float& recorder) : tStart(std::chrono::high_resolution_clock::now()), tRecorder(recorder) {}
	~TimeProfiler() {
		auto tEnd = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float, std::milli> duration = tEnd - tStart;
		tRecorder = duration.count();
	}
private:
	std::chrono::high_resolution_clock::time_point tStart;
	float& tRecorder;
};


class Editor {
public:
	void Init();
	void Update();
	void SetFileFilters();
	static void CreateMenuBar();
	static void CreateRenderWindow();
	static void CreateMasterPanel();
	static void CreatePrefabPanel();
	static void CreateSoundPanel();
	static void CreateObjectList();
	static void CreateDebugPanel();
	static void CreateAssetBrowser();
	static void CreateConsolePanel();

	//static void RenderDirectory(const std::string& path); // Helper function to render asset browser directory
	static void RenderDirectoryV2(const std::string& filePath); // Tester function for asset browser
public:
	static std::string browserInputPath;
	static std::string consoleTextInput;
	static bool browserDoubleClicked;
	static std::string browserSelectedItem;
	static std::pair<int, int> gameWindowOrigin;
	static std::pair<int, int> gameWindowSize;
	static GameObject* selected;
	static OpenGLObject selectedOutline;

public:
	// ImGui colour definitions
	static const ImU32 whiteColour = IM_COL32(0, 0, 0, 255); // White color
	static const ImU32 redColour = IM_COL32(255, 0, 0, 255); // Red color
	static const ImU32 greenColour = IM_COL32(0, 255, 0, 255); // Green color
	static const ImU32 blueColour = IM_COL32(0, 0, 255, 255); // Blue color
	static const ImU32 pinkColour = IM_COL32(255, 0, 127, 255); // Pink color
	static const ImU32 bananaColour = IM_COL32(255, 255, 0, 255); // Yellow color
	static const ImU32 purpleColour = IM_COL32(147, 0, 255, 255); // Purple color
	
	// Buffer and limit for recording FPS performance
	size_t maxFPSdata;
	static std::vector<float> fpsData;

public:
	// Panel settings
	static int iconSize;
	static int iconPadding;


struct SystemTime {
	float physicsTime;
	float graphicsTime;
	float editorTime;
	float soundTime;
	float particlesTime;
	float scenemanagerTime;
	float colliderTime;
	float transformTime;
};
static SystemTime timeRecorder;

private:
	static std::vector<std::string> prefabList;
	static std::map<std::string, LPCWSTR> fileFilterList;
};

// Store panel selection
struct Panels {
	bool gamePanel{ true };
	bool prefabPanel;
	bool soundPanel;
	bool objectPanel;
	bool assetBrowserPanel;
	bool debugPanel;
	bool consolePanel{ true };
};
static Panels panelList;

#endif
