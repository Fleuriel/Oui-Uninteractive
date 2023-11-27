/**************************************************************************
 * @file Scene1.cpp
 * @author CHEAH Tristan Tze Hong
 * @par DP email: t.cheah@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 27-11-2023
 * @brief This file contains the declaration of the Scene1 Class,
 *		  which is a subset of IComponent to be contained in GameObject. 
 *		  It holds  functions to enable scene1 transition in the engine.
 *************************************************************************/


#include "Scene1.h"
#include "TilemapLoader.h"
#include "HealthSystem.h"


/**************************************************************************
* @brief Constructor of Scene1
*************************************************************************/
Scene1::Scene1(unsigned int id) : IScene(id) {
	sceneID = id;
}



/**************************************************************************
* @brief Load for Scene1
* @return void
*************************************************************************/
void Scene1::Load(){
	// Prefabs
#ifdef _DEBUG 
	std::cout << "\nLoading prefabs from JSON file..." << std::endl;
#endif
	objectFactory->LoadPrefab(FILEPATH_PREFAB_DEFAULT);
}



/**************************************************************************
* @brief Initialize for Scene1
* @return void
*************************************************************************/
void Scene1::Initialize() {
	/*#ifdef _DEBUG
		std::cout << "\nDe-serializing objects from JSON file..." << std::endl;
	#endif
		//PLAYER OBJECT
		objectFactory->BuildObjectFromFile(FILEPATH_SCENES_TESTSCENEREADING);
	#ifdef _DEBUG
		std::cout << "De-serializing objects from JSON file... completed." << std::endl;
	#endif
	#ifdef _DEBUG	
		std::cout << "\nUpdating JSONEnemy2 during initialization..." << std::endl;
	#endif
		objectFactory->SaveObjectsToFile(FILEPATH_SCENES_TESTSCENEWRITING);

	#ifdef _DEBUG	
		std::cout << "Updating JSONEnemy2 during initialization... completed." << std::endl;
	#endif*/
	objectFactory->DestroyAllObjects();
	tilemapLoader->LoadTilemap("assets/scenes/TestLevel1.json");
	
	tilemapLoader->CreateGrid();
	objectFactory->BuildObjectFromFile("assets/scenes/TestLevel1.json");
	healthSys->ClearHealthbar();
}

/**************************************************************************
* @brief Updates Scene 1
* @param dt deltaTime for every single update.
* @return void
*************************************************************************/
void Scene1::Update(float dt) {
	dt;
	//scene transitions
}
/**************************************************************************
* @brief Draws Scene1
* @return void
*************************************************************************/
void Scene1::Draw() {
}
/**************************************************************************
* @brief Free For Scene1
* @return void
*************************************************************************/
void Scene1::Free() {
	// Save objects to JSON
	//objectFactory->SaveObjectsToFile(FILEPATH_SCENES_TESTSCENEWRITING);
	//free object memory
	objectFactory->DestroyAllObjects();
}
/**************************************************************************
* @brief Unloads Scene1 For Scene1
* @return void
*************************************************************************/
void Scene1::Unload() {
	//unload objects
}


/**************************************************************************
* @brief Destructor
*************************************************************************/
Scene1::~Scene1() {
}