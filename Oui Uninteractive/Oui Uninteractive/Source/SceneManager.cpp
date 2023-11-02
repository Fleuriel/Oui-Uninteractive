#pragma once
#include "SceneManager.h"
#include "OpenGLApplication.h"
#include "Editor.h"
// Game State List Enumeration

#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
SceneManager* sceneManager = nullptr;
SceneManager::SceneManager() {
	currScene = nullptr;
	currSceneID = 0;
	nextSceneID = currSceneID;
	prevSceneID = currSceneID;
	if (sceneManager != nullptr) {
		return;
	}
	else {
		sceneManager = this;
	}
}
void SceneManager::Initialize() {
	sceneMap.insert(std::pair<size_t, IScene*>(GameStateList::STATE_GRAPHICS_TEST, new Scene1(0)));
	sceneMap.insert(std::pair<size_t, IScene*>(GameStateList::STATE_LEVEL_TEST, new Scene2(0)));
	currScene = sceneMap[0];
	currSceneID = currScene->sceneID;
	nextSceneID = currSceneID;
	prevSceneID = currSceneID;
}
SceneManager::~SceneManager() {
	std::map<size_t, IScene*>::iterator it = sceneMap.begin();
	for (; it != sceneMap.end(); it++) {
		delete it->second;
	}
}
void SceneManager::Load() {
	if (currSceneID < sceneMap.size()) {
		currScene = sceneMap[currSceneID];
	}
	currScene->Load();
}
void SceneManager::InitScene() {
	currScene->Initialize();
}
void SceneManager::Update(float dt) {
	// Start time profiling for scenemanager
	TimeProfiler profiler(Editor::timeRecorder.scenemanagerTime);
	currScene->Update(dt);
	// if quit, exit
	if (currSceneID == STATE_QUIT)
		return;
	//  window is closed, exit
	if (glfwWindowShouldClose(windowNew)) {
		currSceneID = STATE_QUIT;
		return;
	}
}
void SceneManager::Draw() {

}
void SceneManager::Free() {
	currScene->Free();
}
void SceneManager::Unload() {
}

#endif