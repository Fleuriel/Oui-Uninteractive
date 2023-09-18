/**************************************************************************
 * @file		  GameObject.cpp
 * @author
 * @par DP email:
 * @par Course:	  CSD 2401
 * @par			  Software Engineering Project 3
 * @date		  09-08-2023
 * @brief
 *************************************************************************/

#include "GameObject.h"

// For future event/message system
/*void SendMessage(Event* event) {

}*/

/**************************************************************************
* @brief Initialize game object
*************************************************************************/
void GameObject::Initialize() {
	// Initialize each component in componentList
	for (size_t i{}; i < componentList.size(); ++i) {
		componentList[i]->base = this;
		componentList[i]->Initialize();
	}
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
	// Remove component
}

/**************************************************************************
* @brief Check if component is in componentList
* @param c - component pointer
* @return bool - true if component is in componentList
*************************************************************************/
int GameObject::Has(ComponentType type) {
	std::vector<IComponent*>::iterator it = componentList.begin();
	while (it != componentList.end()) {
		if ((*it)->componentType == type) {
			return it - componentList.begin();
		}
		it++;
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
IComponent* GameObject::GetComponent(ComponentType typeID) {
	int index = Has(typeID);
	if (index >= 0) {
		return componentList.at(index);
	}
	return nullptr;
}
