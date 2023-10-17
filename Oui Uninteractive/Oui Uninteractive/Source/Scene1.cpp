#include "Scene1.h"

Scene1::Scene1(unsigned int id) : IScene(id) {
	sceneID = id;
}
void Scene1::Load(){
	// Prefabs
#ifdef _DEBUG 
	std::cout << "\nLoading prefabs from JSON file..." << std::endl;
#endif
	objectFactory->LoadPrefab("../prefab/Prefab.JSON");
}
void Scene1::Initialize() {

	#ifdef _DEBUG
		std::cout << "\nDe-serializing objects from JSON file..." << std::endl;
	#endif
		//PLAYER OBJECT
		objectFactory->BuildObjectFromFile("../scenes/TestsceneReading.JSON");
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
void Scene1::Update(float dt) {
	if (GET_COMPONENT(objectFactory->GetGameObjectByID(0), Transform, ComponentType::TRANSFORM)->position.x > 1000) {
		sceneManager->nextSceneID = GameStateList::STATE_LEVEL_TEST;
	}
	//scene transitions
}
void Scene1::Draw() {

}
void Scene1::Free() {
	//free object memory
	objectFactory->DestroyAllObjects();
}
void Scene1::Unload() {
	//unload objects
}
Scene1::~Scene1() {

}