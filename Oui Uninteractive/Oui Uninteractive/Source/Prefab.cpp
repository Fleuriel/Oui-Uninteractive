/**************************************************************************
 * @file Prefab.cpp
 * @author HWANG Jing Rui, Austin - 100%
 * @par DP email: jingruiaustin.hwang@digipen.edu
 * @par Course:	CSD 2401
 * @par Software Engineering Project 3
 * @date 01-11-2023
 * @brief This file contains the definition of the Prefab class.
 *************************************************************************/
#include "Prefab.h"

/**************************************************************************
* @brief Constructor
*************************************************************************/
Prefab::Prefab(const std::string& name, const std::string& type) {
	prefabName = name;
	prefabType = type;
}

/**************************************************************************
* @brief Destructor
*************************************************************************/
Prefab::~Prefab() {
	for (int i{}; i < prefabComponentList.size(); ++i)
		delete prefabComponentList[i];
}

/**************************************************************************
* @brief Add component to prefabComponentList
* @param c - component pointer
* @param t - component type
* @return void
*************************************************************************/
void Prefab::AddComponent(IComponent* c, ComponentType t) {
	c->componentType = t;
	prefabComponentList.push_back(c);

	std::map<size_t, GameObject*> copyMap = objectFactory->GetGameObjectIDMap();
	for (std::map<size_t, GameObject*>::iterator it = copyMap.begin(); it != copyMap.end(); it++) {
		if ((*it).second->GetType() == GetType()) {
			objectFactory->AddComponent(t, objectFactory->GetGameObjectByID((*it).second->GetGameObjectID()));
		}
	}
}

/**************************************************************************
* @brief Remove component from prefabComponentList
* @param c - component pointer
* @return void
*************************************************************************/
void Prefab::RemoveComponent(IComponent* c) {
	if (c != nullptr) {
		for (size_t i{}; i < prefabComponentList.size(); ++i) {
			if (prefabComponentList[i] == c) {
				prefabComponentList.erase(prefabComponentList.begin() + i);
				break;
			}
		}
		std::map<size_t, GameObject*> copyMap = objectFactory->GetGameObjectIDMap();
		for (std::map<size_t, GameObject*>::iterator it = copyMap.begin(); it != copyMap.end(); it++) {
			if ((*it).second->GetType() == GetType()) {
				objectFactory->RemoveComponent(c->componentType, objectFactory->GetGameObjectByID((*it).second->GetGameObjectID()));
			}
		}
	}
}

/**************************************************************************
* @brief Check if component is in prefabComponentList
* @param c - component pointer
* @return int - position of component in prefabComponentList
*************************************************************************/
int Prefab::Has(ComponentType typeID) {
	for (int i{}; i < prefabComponentList.size(); ++i) {
		if (prefabComponentList[i]->componentType == typeID) {
			return i;
		}
	}
	return -1;
}

/**************************************************************************
* @brief Get prefab name
* @return std::string - prefab name
*************************************************************************/
std::string Prefab::GetName() {
	return prefabName;
}

/**************************************************************************
* @brief Get prefab type
* @return std::string - prefab type
*************************************************************************/
std::string Prefab::GetType() {
	return prefabType;
}

/**************************************************************************
* @brief Get component with component type
* @param typeID - component type
* @return IComponent*
*************************************************************************/
std::vector<IComponent*> Prefab::GetPrefabComponentList() {
	return prefabComponentList;
}

/**************************************************************************
* @brief Get component with component type
* @param typeID - component type
* @return IComponent*
*************************************************************************/
IComponent* Prefab::GetComponent(ComponentType typeID) {
	int index = Has(typeID);
	if (index >= 0) {
		return prefabComponentList.at(index);
	}
	return nullptr;
}

/**************************************************************************
* @brief Check whether sprite or texture is used
* @return true if using sprite. false if texture instead.
*************************************************************************/
bool Prefab::IsUsingSprite() {
	return usingSprite;
}

/**************************************************************************
* @brief Set whether sprite/texture is used
* @param flag - flag to set whether sprite/texture is used
* @return void
*************************************************************************/
void Prefab::SetUsingSprite(bool flag) {
	usingSprite = flag;
}

/**************************************************************************
* @brief Get texture of game object
* @return std::string - texture
*************************************************************************/
std::string Prefab::GetTexture() {
	return textureName;
}

/**************************************************************************
* @brief Set texture of game object
* @param std::string - texture name
* @return void
*************************************************************************/
void Prefab::SetTexture(std::string tex) {
	textureName = tex;
}
