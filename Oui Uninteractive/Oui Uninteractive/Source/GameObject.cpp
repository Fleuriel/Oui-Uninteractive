/**************************************************************************
 * @file GameObject.cpp
 * @author HWANG Jing Rui, Austin
 * @co-author CHEAH Tristan Tze Hong
 * @par DP email: jingruiaustin.hwang@digipen.edu
 * @par DP email: t.cheah@digipen.edu
 * @par Course:	CSD 2401
 * @par	Software Engineering Project 3
 * @date 08-09-2023
 * @brief This file contains the definition of the GameObject class.
 *		  The functions include:
 *			- Initialize
 *			- AddComponent
 *			- RemoveComponent
 *			- Has
 *			- GetGameObjectID
 *			- GetName
 *			- GetType
 *			- GetComponent
 *			- GetComponentType
 *************************************************************************/
#include <algorithm>
#include <iostream>
#include "GameObject.h"

/**************************************************************************
* @brief Default Constructor
*************************************************************************/
GameObject::GameObject(const std::string& name, const std::string& type, const State& state) : gameObjectID{} {
	gameObjectName = name;
	gameObjectType = type;
	gameObjectState = state;
}

/**************************************************************************
* @brief Destructor
*************************************************************************/
GameObject::~GameObject() {
	for (int i{}; i < componentList.size(); ++i)
		delete componentList[i];
}

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
	return -1;
}

/**************************************************************************
* @brief Get game object ID
* @return size_t - game object ID
*************************************************************************/
size_t GameObject::GetGameObjectID() {
	return gameObjectID;
}

/**************************************************************************
* @brief Get game object name
* @return std::string - game object name
*************************************************************************/
std::string GameObject::GetName() {
	return gameObjectName;
}

/**************************************************************************
* @brief Get game object type
* @return std::string - game object type
*************************************************************************/
std::string GameObject::GetType() {
	return gameObjectType;
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

/**************************************************************************
	* @brief Get state of game object
	* @return State
	*************************************************************************/
State GameObject::GetState() {
	return gameObjectState;
}
