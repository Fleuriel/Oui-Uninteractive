#pragma once
#include "SceneManager.h"

#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
SceneManager* sceneManager = nullptr;
SceneManager::SceneManager() {
	currScene = nullptr;
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
}

#endif