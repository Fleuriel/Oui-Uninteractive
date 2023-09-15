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

	// Vector of components
	std::vector<IComponent*> componentList;	// may use typedef to represent vector in the future

public:
	// Set ObjectFactory as friend class to access gameObjectID
	friend class ObjectFactory;

	GameObject() : gameObjectID{} {}
	~GameObject() {}

	// Game object factory stuff here
	
	// Initialize components in componentList
	void Initialize();

	//virtual void Update() = 0;
	//virtual void Render() = 0;

	// For future event/message system
	//void SendMessage(Event* event);

	// Add component to componentList
	void AddComponent(IComponent* c, ComponentType t);

	// Remove component from componentList
	void RemoveComponent(IComponent* c);

	// Check if component is in componentList
	bool Has(IComponent* c);

	// Get game object ID
	size_t GetGameObjectID();

	// Get component

	// Get component type
};
