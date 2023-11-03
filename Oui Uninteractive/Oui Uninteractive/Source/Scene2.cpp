#pragma once
#include "Scene2.h"
Scene2::Scene2(unsigned int id) : IScene(id) {
	sceneID = id;
}
void Scene2::Load() {
	// Prefabs
#ifdef _DEBUG 
	std::cout << "\nLoading prefabs from JSON file..." << std::endl;
#endif
}
void Scene2::Initialize() {

#ifdef _DEBUG
	std::cout << "\nDe-serializing objects from JSON file..." << std::endl;
#endif
	//PLAYER OBJECT
	objectFactory->BuildObjectFromFile(FILEPATH_SCENES_TESTSCENEREADING2);
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
	std::cout << "\nCloning object with ID 1..." << std::endl;
#endif
	//AI OBJECT

#ifdef _DEBUG	
	std::cout << "Cloning object with ID 0... completed." << std::endl;
#endif
	// Modifying value of JSONEnemy2

#ifdef _DEBUG	
	std::cout << "\nUpdating JSONEnemy2 during initialization..." << std::endl;
#endif
	objectFactory->SaveObjectsToFile(FILEPATH_SCENES_TESTSCENEREADING2);

#ifdef _DEBUG	
	std::cout << "Updating JSONEnemy2 during initialization... completed." << std::endl;
#endif
}
void Scene2::Update(float dt) {
	dt;
	if (inputSystem.GetKeyState(GLFW_KEY_0)) {
		sceneManager->nextSceneID = GameStateList::STATE_GRAPHICS_TEST;
	}
	
	//scene transitions
}
void Scene2::Draw() {
	
}
void Scene2::Free() {
	// Save onjects to JSON
	objectFactory->SaveObjectsToFile(FILEPATH_SCENES_TESTSCENEREADING2);
	//free object memory
	objectFactory->DestroyAllObjects();
}
void Scene2::Unload() {
	//unload objects
}
Scene2::~Scene2() {
}