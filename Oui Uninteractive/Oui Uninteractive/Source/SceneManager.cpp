#pragma once
#include "SceneManager.h"
#include <iostream>
#include "ObjectFactory.h"
#include "Transform.h"

#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
SceneManager* sceneManager = nullptr;
SceneManager::SceneManager() {
	if (sceneManager != nullptr) {
		return;
	}
	else {
		sceneManager = this;
	}
}
void SceneManager::Initialize() {
	// Prefabs
#ifdef _DEBUG 
	std::cout << "\nLoading prefabs from JSON file..." << std::endl;
#endif
	objectFactory->LoadPrefab("../prefab/Prefab.JSON");

#ifdef _DEBUG
	std::cout << "Loading prefabs from JSON file... completed." << std::endl;
#endif

	// De-serializing objects from JSON file

#ifdef _DEBUG
	std::cout << "\nDe-serializing objects from JSON file..." << std::endl;
#endif
	//PLAYER OBJECT
	objectFactory->BuildObjectFromFile("../scenes/TestsceneReading.JSON");
	objectFactory->GetGameObjectByID(0)->Initialize();


#ifdef _DEBUG
	std::cout << "De-serializing objects from JSON file... completed." << std::endl;
#endif

#ifdef _DEBUG
	std::cout << "\nBuilding an object from player prefab..." << std::endl;
#endif
	objectFactory->BuildObjectFromPrefab("PlayerObjFromPrefab", "Player");

#ifdef _DEBUG	
	std::cout << "Building an object from player prefab... completed." << std::endl;
#endif

#ifdef _DEBUG	
	std::cout << "\nCloning object with ID 0..." << std::endl;
#endif
	//AI OBJECT

	objectFactory->CloneObject(1);
	objectFactory->GetGameObjectByID(4)->Initialize();
	GET_COMPONENT(objectFactory->GetGameObjectByID(4), Transform, ComponentType::TRANSFORM)->position.y = 50;

#ifdef _DEBUG	
	std::cout << "Cloning object with ID 0... completed." << std::endl;
#endif

	// Modifying value of JSONEnemy2

#ifdef _DEBUG	
	std::cout << "\nUpdating JSONEnemy2 during initialization..." << std::endl;
#endif
	objectFactory->SaveObjectsToFile("../scenes/TestsceneWriting.JSON");

#ifdef _DEBUG	
	std::cout << "Updating JSONEnemy2 during initialization... completed." << std::endl;
#endif
}

void SceneManager::Update(float dt) {

}
SceneManager::~SceneManager() {

}
#endif