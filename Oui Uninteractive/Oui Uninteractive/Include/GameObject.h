/**************************************************************************
 * @file		  GameObject.h
 * @author
 * @par DP email:
 * @par Course:	  CSD 2401
 * @par			  Software Engineering Project 3
 * @date		  09-08-2023
 * @brief
 *************************************************************************/
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <vector>
#include "IComponent.h"

class GameObject {
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
	std::string GetName();
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

	// Check if component is in componentList
	int Has(ComponentType typeID);

	// Get game object ID
	size_t GetGameObjectID();

//	Get component with component type
	IComponent* GetComponent(ComponentType typeID);

	// Get component type
	template <typename T> T* GetComponentType(ComponentType typeID);
};

template <typename T> T* GameObject::GetComponentType(ComponentType typeID) {
	return static_cast<T*>(GetComponent(typeID));
}

#endif
