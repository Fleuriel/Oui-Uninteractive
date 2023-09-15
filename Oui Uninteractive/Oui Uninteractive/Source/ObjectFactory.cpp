#include "ObjectFactory.h"
#include <iostream>
ObjectFactory* objectFactory = NULL;

ObjectFactory::ObjectFactory() : gameObjectCurrentID{} {
	if (objectFactory != NULL) {
		return;
	}
	std::cout << "Component Fac: " << componentFactoryMap.size() << "\n";
	objectFactory = this;
}
// No serialization as of now
GameObject* ObjectFactory::BuildObjectFromFile(std::string componentName) {
	//GameObject* object{new GameObject()};
	//return object;
	return nullptr;
}

// Serialize a game object

// Create a game object during run-time
GameObject* ObjectFactory::BuildObjectRunTime() {
	GameObject* objectRunTime{new GameObject()};
	AssignObjectID(objectRunTime);
	return objectRunTime;
}

// Add a to-be-destroyed game object to the destroy list
void ObjectFactory::DestroyObject(GameObject* gameObject) {

}

// Assign an ID to a game object and add it to the map of game objects
void ObjectFactory::AssignObjectID(GameObject* gameObject) {
	// Assign ID to gameObject
	gameObject->gameObjectID = gameObjectCurrentID;

	// Add gameObject to the map
	gameObjectIDMap[gameObjectCurrentID] = gameObject;

	// Increment ID
	++gameObjectCurrentID;
}

// Destroy all game objects
void ObjectFactory::DestroyAllObjects() {

}

// Get a game object by ID
GameObject* ObjectFactory::GetGameObjectByID(size_t gameObjectID)
{
	if (gameObjectIDMap.find(gameObjectID) != gameObjectIDMap.end())
		return gameObjectIDMap[gameObjectID];

	return nullptr;
}

// Add component factory to map
void ObjectFactory::AddComponentFactory(std::string componentName, ComponentFactoryBase* componentFactory)
{
	//componentFactoryMap[componentName] = componentFactory;
	componentFactoryMap.insert(std::pair(componentName, componentFactory));
}

void ObjectFactory::Update(float dt) {
	std::set<GameObject*>::iterator it = gameObjectDestroyList.begin();

	for (; it != gameObjectDestroyList.end(); it++) {
		GameObject* gameObject = *it;


		//Insert double free protection here
		delete gameObject;
	}
	gameObjectDestroyList.clear();
}
/*bool ObjectFactory::AddComponent(std::string componentName) {
	std::map<std::string, ComponentFactoryBase*>::iterator it = componentFactoryMap.find(componentName);
	if (it != componentFactoryMap.end()) {
		ComponentFactoryBase* factory = it->second;
		
		//IComponent* component = factory->create();
	}
	else {
		return false;
	}
	return true;
}*/