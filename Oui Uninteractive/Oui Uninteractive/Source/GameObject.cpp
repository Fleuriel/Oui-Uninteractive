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
#include "PhysicsBody.h"

/**************************************************************************
* @brief Default Constructor
*************************************************************************/
GameObject::GameObject(const std::string& name, const std::string& type) : gameObjectID{}, gameObjAnimationFrame{}, usingSprite(false) {
	gameObjectName = name;
	gameObjectType = type;
	
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
	std::cout << "Initialized " << gameObjectName << std::endl;
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
			delete c;
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
	if (componentList.size() > 0) {
		for (int i{}; i < componentList.size(); ++i) {
			if (componentList[i]->componentType == typeID) {
				return i;
			}
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
void GameObject::SetName(std::string newName) {
	gameObjectName = newName;
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
* @brief Get the direction the game object is facing (for animations)
* @return int - 1 if facing up
*				2 if facing right
*				3 if facing down
*				4 if facing left
*************************************************************************/
int GameObject::GetSpriteDirection(float directionX, float directionY) {
	if (directionX == 0 && directionY == 1) {
		return 1;
	}
	if (directionX == 1 && directionY == 0) {
		return 2;
	}
	if (directionX == 0 && directionY == -1) {
		return 3;
	}
	if (directionX == -1 && directionY == 0) {
		return 4;
	}
	return 0;
}

/**************************************************************************
* @brief Get the animation frame (column) of the game object
* @return int - frame of game object
*************************************************************************/
int GameObject::GetAnimationFrame() {
	return gameObjAnimationFrame;
}

/**************************************************************************
* @brief Get the direction the game object is facing (for animations)
* @param frame - frame to set animation to
* @return void
*************************************************************************/
void GameObject::SetAnimationFrame(int frame) {
	gameObjAnimationFrame = frame;
}

/**************************************************************************
* @brief Check whether sprite or texture is used
* @return true if using sprite. false if texture instead.
*************************************************************************/
bool GameObject::IsUsingSprite() {
	return usingSprite;
}

/**************************************************************************
* @brief Set whether sprite/texture is used
* @param flag - flag to set whether sprite/texture is used
* @return void
*************************************************************************/
void GameObject::SetUsingSprite(bool flag) {
	usingSprite = flag;
}

/**************************************************************************
* @brief Get texture of game object
* @return std::string - texture
*************************************************************************/
std::string GameObject::GetTexture() {
	return textureName;
}

/**************************************************************************
* @brief Set texture of game object
* @param std::string - texture name
* @return void
*************************************************************************/
void GameObject::SetTexture(std::string tex) {
	textureName = tex;
}
