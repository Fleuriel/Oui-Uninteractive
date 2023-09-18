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

// Object Factory initializer
ObjectFactory::ObjectFactory() : gameObjectCurrentID{} {
	if (objectFactory != NULL) {
		return;
	}
	std::cout << "Component Fac: " << componentFactoryMap.size() << "\n";
	objectFactory = this;
}
// Create a game object from a JSON file
GameObject* ObjectFactory::BuildObjectFromFile(const std::string& filePath) {
	//GameObject* object{new GameObject()};
	GameObject* object{SerializeObject(filePath)};
	object->Initialize();
	return object;
}

// Serialize game object data from a JSON file
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
		// Assign an ID to the game object
		AssignObjectID(gameObject);

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

// Update each game obejct in object factory
void ObjectFactory::Update(float dt) {
	std::set<GameObject*>::iterator it = gameObjectDestroyList.begin();

	for (; it != gameObjectDestroyList.end(); it++) {
		GameObject* gameObject = *it;

		//Insert double free protection here
		delete gameObject;
	}
	gameObjectDestroyList.clear();
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

// Add a to-be-destroyed game object to the destroy list
void ObjectFactory::DestroyObject(GameObject* gameObject) {
	gameObjectDestroyList.insert(gameObject);
}

// Destroy all game objects
void ObjectFactory::DestroyAllObjects() {
	std::map<size_t, GameObject*>::iterator it = gameObjectIDMap.begin();

	while (it != gameObjectIDMap.end()) {
		delete it->second;
		it++;
	}
}

// Get a game object by ID
GameObject* ObjectFactory::GetGameObjectByID(size_t gameObjectID)
{
	if (gameObjectIDMap.find(gameObjectID) != gameObjectIDMap.end())
		return gameObjectIDMap[gameObjectID];

	return nullptr;
}

// Add component factory to map
void ObjectFactory::AddComponentFactory(std::string componentName, ComponentFactoryBase* componentFactory) {
	componentFactoryMap.insert(std::pair(componentName, componentFactory));
}

// Add component with a specified component name to game object
bool ObjectFactory::AddComponent(std::string componentName, GameObject* object) {
	// Get component factory
	std::map<std::string, ComponentFactoryBase*>::iterator it = componentFactoryMap.find(componentName);

	// Check if component factory exists
	if (it != componentFactoryMap.end()) {
		// Add component to game object
		ComponentFactoryBase* factory = it->second;
		IComponent* component = factory->CreateComponent();

		object->AddComponent(component, factory->type);
	}
	else {
		return false;
	}

	return true;
}