#pragma once
#include "SceneManager.h"
#include "OpenGLApplication.h"
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
	sceneMap.insert(std::pair<size_t, IScene*>(0, new Scene1(0)));
	currScene = sceneMap[0];

	currSceneID = 0;
	nextSceneID = currSceneID;
	prevSceneID = currSceneID;

	currScene->Load();
}
SceneManager::~SceneManager() {
	std::map<size_t, IScene*>::iterator it = sceneMap.begin();
	for (; it != sceneMap.end(); it++) {
		delete it->second;
	}
}

void SceneManager::Load() {
	currScene->Load();
}
void SceneManager::InitScene() {
	currScene->Initialize();
}
void SceneManager::Update(float dt) {
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

#endif