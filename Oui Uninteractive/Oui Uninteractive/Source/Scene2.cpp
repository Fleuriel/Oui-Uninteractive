/**************************************************************************
 * @file Scene2.cpp
 * @author CHEAH Tristan Tze Hong
 * @par DP email: t.cheah@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 27-11-2023
 * @brief This file contains the declaration of the Scene2 Class,
 *		  which is a subset of IComponent to be contained in GameObject.
*		  It holds  functions to enable scene2 transition in the engine.
 *************************************************************************/

#pragma once
#include "Scene2.h"

/**************************************************************************
* @brief Constructor
*************************************************************************/
Scene2::Scene2(unsigned int id) : IScene(id) {
	sceneID = id;
}

/**************************************************************************
* @brief Load Scene2
* @return void
*************************************************************************/
void Scene2::Load() {
	// Prefabs
#ifdef _DEBUG 
	std::cout << "\nLoading prefabs from JSON file..." << std::endl;
#endif
}
/**************************************************************************
* @brief Initializes Scene2
* @return void
*************************************************************************/
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

/**************************************************************************
* @brief Updates Scene2
* @param dt		Deltatime for update per frame
* @return void
*************************************************************************/
void Scene2::Update(float dt) {
	dt;
	//scene transitions
}

/**************************************************************************
* @brief Draws Scene2
* @return void
*************************************************************************/
void Scene2::Draw() {
	
}

/**************************************************************************
* @brief Frees Scene2
* @return void
*************************************************************************/
void Scene2::Free() {
	// Save onjects to JSON
	objectFactory->SaveObjectsToFile(FILEPATH_SCENES_TESTSCENEREADING2);
	//free object memory
	objectFactory->DestroyAllObjects();
}

/**************************************************************************
* @brief Unloads Scene2
* @return void
*************************************************************************/
void Scene2::Unload() {
	//unload objects
}

/**************************************************************************
* @brief Destructor
*************************************************************************/
Scene2::~Scene2() {
}