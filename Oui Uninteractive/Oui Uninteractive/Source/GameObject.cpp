/**************************************************************************
 * @file		  GameObject.cpp
 * @author
 * @par DP email:
 * @par Course:	  CSD 2401
 * @par			  Software Engineering Project 3
 * @date		  09-08-2023
 * @brief
 *************************************************************************/

#include <algorithm>
#include <iostream>
#include "GameObject.h"

// For future event/message system
/*void SendMessage(Event* event) {

}*/

/**************************************************************************
* @brief Initializer
*************************************************************************/
GameObject::GameObject(const std::string name) : gameObjectID{} {
	gameObjectName = name;
}

/**************************************************************************
* @brief Destructor
*************************************************************************/
GameObject::~GameObject() {}

/**************************************************************************
* @brief Initialize components in componentList
*************************************************************************/
void GameObject::Initialize() {
	for (size_t i{}; i < componentList.size(); ++i) {
		componentList[i]->base = this;
		componentList[i]->Initialize();
	}
	std::cout << "Initialized " << gameObjectName << std::endl;  // Debugging
}

/**************************************************************************
* @brief Add component to componentList
* @param c - component pointer
* @param t - component type
*************************************************************************/
void GameObject::AddComponent(IComponent* c, ComponentType t) {
	c->componentType = t;
	componentList.push_back(c);
}

/**************************************************************************
* @brief Remove component from componentList
* @param c - component pointer
*************************************************************************/
void GameObject::RemoveComponent(IComponent* c) {
	for (size_t i{}; i < componentList.size(); ++i) {
		if (componentList[i] == c) {
			componentList.erase(componentList.begin() + i);
			return;
		}
	}
}

/**************************************************************************
* @brief Check if component is in componentList
* @param c - component pointer
* @return int - position of component in componentList
*************************************************************************/
int GameObject::Has(ComponentType typeID) {
	for (int i{}; i < componentList.size(); ++i) {
		if (componentList[i]->componentType == typeID) {
			return i;
		}
	}
	return false;
}

/**************************************************************************
* @brief Get game object ID
* @return size_t - game object ID
*************************************************************************/
size_t GameObject::GetGameObjectID() {
	return gameObjectID;
}

/**************************************************************************
* @brief Get component with component type
* @return IComponent*
*************************************************************************/
IComponent* GameObject::GetComponent(ComponentType typeID) {
	int index = Has(typeID);
	if (index >= 0) {
		return componentList.at(index);
	}
	return nullptr;
}
