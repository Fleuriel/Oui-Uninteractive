#include "Scene1.h"

Scene1::Scene1(unsigned int id) : IScene(id) {
	sceneID = id;
}
void Scene1::Load(){
	// Prefabs
#ifdef _DEBUG 
	std::cout << "\nLoading prefabs from JSON file..." << std::endl;
#endif
	objectFactory->LoadPrefab(FILEPATH_PREFAB);
}
void Scene1::Initialize() {
	#ifdef _DEBUG
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
	#endif
}
void Scene1::Update(float dt) {
	dt;
	//scene transitions
}
void Scene1::Draw() {
}
void Scene1::Free() {
	// Save objects to JSON
	objectFactory->SaveObjectsToFile(FILEPATH_SCENES_TESTSCENEWRITING);
	//free object memory
	objectFactory->DestroyAllObjects();
}
void Scene1::Unload() {
	//unload objects
}
Scene1::~Scene1() {
}