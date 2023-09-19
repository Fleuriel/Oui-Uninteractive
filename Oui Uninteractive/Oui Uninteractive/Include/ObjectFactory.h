/**************************************************************************
 * @file		  ObjectFactory.h
 * @author
 * @par DP email:
 * @par Course:	  CSD 2401
 * @par			  Software Engineering Project 3
 * @date		  09-13-2023
 * @brief
 *************************************************************************/
#pragma once

#include <string>
#include <map>
#include <set>
#include "ISystem.h"
#include "GameObject.h"

class ComponentFactoryBase;

class ObjectFactory : public ISystem {
private:
	// ID to keep track of objects
	size_t gameObjectCurrentID;

	// Map of game objects to their ID
	std::map<size_t, GameObject*> gameObjectIDMap;

	// Set to manage the destruction of game objects
	std::set<GameObject*> gameObjectDestroyList;

	// Map of component factories
	std::map<componentType, ComponentFactoryBase*> componentFactoryMap;

public:
	ObjectFactory();
	~ObjectFactory() {}
	ComponentType stringToEnum(std::string str);
	// Create a new game object from a file
	// To change parameter to the filename when implementing serialization in the future
	GameObject* BuildObjectFromFile(const std::string& filePath);

	// Serialize a game object
	GameObject* SerializeObject(const std::string& filePath);

	// Create a new game object during run-time
	GameObject* BuildObjectRunTime();

	bool CloneObject(size_t gameObjectID);

	// Update the object factory
	virtual void Update(float dt);

	// Assign an ID to a game object and add it to the map of game objects
	void AssignObjectID(GameObject* gameObject);

	// Add a to-be-destroyed game object to the destroy list
	void DestroyObject(GameObject* gameObject);

	// Destroy all game objects
	void DestroyAllObjects();

	// Get game object with a specified ID
	GameObject* GetGameObjectByID(size_t gameObjectID);

	// messaging...

	// Add component factory to map
	void AddComponentFactory(componentType componentName, ComponentFactoryBase* componentFactory);
	bool AddComponent(componentType name, GameObject* object);
};
extern ObjectFactory* objectFactory;
