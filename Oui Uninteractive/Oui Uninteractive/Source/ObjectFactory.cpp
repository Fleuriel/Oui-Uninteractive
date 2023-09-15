/**************************************************************************
 * @file		  ObjectFactory.cpp
 * @author
 * @par DP email:
 * @par Course:	  CSD 2401
 * @par			  Software Engineering Project 3
 * @date		  09-13-2023
 * @brief
 *************************************************************************/
#include <iostream>
#include "ObjectFactory.h"
#include "JsonSerializer.h"
#include "ComponentFactory.h"

ObjectFactory* objectFactory = NULL;

ObjectFactory::ObjectFactory() : gameObjectCurrentID{} {
	if (objectFactory != NULL) {
		return;
	}
	objectFactory = this;
}
// No serialization as of now
GameObject* ObjectFactory::BuildObjectFromFile(const std::string& filePath) {
	//GameObject* object{new GameObject()};
	GameObject* object{SerializeObject(filePath)};
	object->Initialize();
	return object;
}

// Serialize a game object
GameObject* ObjectFactory::SerializeObject(const std::string& filePath) {
	// Create rapidjson doc object and serializer
	rapidjson::Document objDoc;
	JsonSerializer serializer;
	std::string componentName;

	// Read data from file
	if (serializer.ReadJSONFile(filePath, objDoc)) {
		// Create GameObject
		GameObject* gameObject{};

		// Extract components from JSON file
		for (auto& it : objDoc.GetObject()) {
			// Get component name
			componentName = it.name.GetString();

			if (componentFactoryMap.find(componentName) == componentFactoryMap.end()) {
				std::cerr << "Component name not found." << std::endl;
			}
			else {
				// Create ComponentFactory to create the component itself
				ComponentFactoryBase* componentFactory = componentFactoryMap[componentName];

				// Create the component
				IComponent* component = componentFactory->CreateComponent();

				// Serialize to get component data
				component->Serialize(filePath, serializer);

				// Add the component to the game object
				gameObject->AddComponent(component, componentFactory->type);
			}
		}

		return gameObject;
	}
	else {
		std::cerr << "Failed to serialize object." << std::endl;
		return NULL;
	}
}

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