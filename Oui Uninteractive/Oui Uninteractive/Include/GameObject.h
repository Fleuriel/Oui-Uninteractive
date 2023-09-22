/**************************************************************************
 * @file		  GameObject.h
 * @author
 * @par DP email:
 * @par Course:	  CSD 2401
 * @par			  Software Engineering Project 3
 * @date		  09-08-2023
 * @brief
 *************************************************************************/
#pragma once

#include <vector>
#include "IComponent.h"

// THIS WILL PROBABLY BE THE COMPOSITION CLASS

class GameObject {

// maybe include using statements

private:
	// ID to reperesent game object
	size_t gameObjectID;

	// String to represent game object name
	std::string gameObjectName;

	// Vector of components
	std::vector<IComponent*> componentList;	// may use typedef to represent vector in the future
	

public:
	// Set ObjectFactory as friend class to access gameObjectID
	friend class ObjectFactory;
	
	GameObject(const std::string name);
	~GameObject();

	// Game object factory stuff here
	
	// Initialize components in componentList
	void Initialize();

	//void Update();
	//virtual void Render() = 0;

	// For future event/message system
	//void SendMessage(Event* event);

	// Add component to componentList
	void AddComponent(IComponent* c, ComponentType t);

	// Remove component from componentList
	void RemoveComponent(IComponent* c);

	// Return position of component with typeID in componentList
	int Has(ComponentType typeID);

	// Get game object ID
	size_t GetGameObjectID();

	// Get game object name
	// For testing
	std::string GetGameObjectName();

	// Get componentlist
	// For testing
	std::vector<IComponent*> GetComponentList();

	// Get component
	IComponent* GetComponent(ComponentType typeID);

	// Get component type
	template <typename T> T* GetComponentType(ComponentType typeID);
};

template <typename T> T* GameObject::GetComponentType(ComponentType typeID) {
	return static_cast<T*>(GetComponent(typeID));
}

