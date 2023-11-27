/**************************************************************************
 * @file SceneManager.cpp
 * @author CHEAH Tristan Tze Hong
 * @par DP email: t.cheah@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 08-09-2023
 * @brief This file contains the declaration of the SceneManager to manage
 *		  Scenes.
 *************************************************************************/

#pragma once
#include "SceneManager.h"
#include "OpenGLApplication.h"
#include "Editor.h"
// Game State List Enumeration

#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
SceneManager* sceneManager = nullptr;


/**************************************************************************
* @brief Constructor
*************************************************************************/
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

/**************************************************************************
* @brief Initializes Scene Manager
* @return void
*************************************************************************/
void SceneManager::Initialize() {
	sceneMap.insert(std::pair<size_t, IScene*>(GameStateList::STATE_GRAPHICS_TEST, new Scene1(0)));
	sceneMap.insert(std::pair<size_t, IScene*>(GameStateList::STATE_LEVEL_TEST, new Scene2(1)));
	currScene = sceneMap[0];
	currSceneID = currScene->sceneID;
	nextSceneID = currSceneID;
	prevSceneID = currSceneID;
}

/**************************************************************************
* @brief Destructor
*************************************************************************/
SceneManager::~SceneManager() {
	std::map<size_t, IScene*>::iterator it = sceneMap.begin();
	for (; it != sceneMap.end(); it++) {
		delete it->second;
	}
}

/**************************************************************************
* @brief Loads Scene Manager
* @return void
*************************************************************************/
void SceneManager::Load() {
	if (currSceneID < sceneMap.size()) {
		currScene = sceneMap[currSceneID];
	}
	currScene->Load();
}

/**************************************************************************
* @brief Initializes Scene
* @return void
*************************************************************************/
void SceneManager::InitScene() {
	currScene->Initialize();
}

/**************************************************************************
* @brief Updates Scene Manager
* @param float dt	DeltaTime for per frame update
* @return void
*************************************************************************/
void SceneManager::Update(float dt) {
	if (sysManager->isPaused == false) {
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
}

/**************************************************************************
* @brief Draws Scene Manager
* @return void
*************************************************************************/
void SceneManager::Draw() {

}

/**************************************************************************
* @brief Frees Scene Manager
* @return void
*************************************************************************/
void SceneManager::Free() {
	currScene->Free();
}

/**************************************************************************
* @brief Unloads Scene Manager
* @return void
*************************************************************************/
void SceneManager::Unload() {
}

#endif