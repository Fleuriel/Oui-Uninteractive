/**************************************************************************
 * @file Prefab.h
 * @author HWANG Jing Rui, Austin
 * @par DP email: jingruiaustin.hwang@digipen.edu
 * @par Course:	CSD 2401
 * @par Software Engineering Project 3
 * @date 01-11-2023
 * @brief This file contains the declaration of the Prefab class.
 *************************************************************************/
#include "ObjectFactory.h"
#ifndef PREFAB_H
#define PREFAB_H

#include "IComponent.h"

class Prefab {
private:
	// String to represent prefab name
	std::string prefabName;

	// String to represent prefab type
	std::string prefabType;

	// Bool to check whether prefab is using sprite or texture
	bool usingSprite;

	// Vector of components for prefab
	std::vector<IComponent*> prefabComponentList;

public:
	// Set ObjectFactory as friend class to access prefabComponentList
	friend class ObjectFactory;

	/**************************************************************************
	* @brief Constructor and Destructor
	*************************************************************************/
	Prefab(const std::string& name, const std::string& type);
	~Prefab();

	/**************************************************************************
	* @brief Add component to prefabComponentList
	* @param c - component pointer
	* @param t - component type
	* @return void
	*************************************************************************/
	void AddComponent(IComponent* c, ComponentType t);

	/**************************************************************************
	* @brief Remove component from prefabComponentList
	* @param c - component pointer
	* @return void
	*************************************************************************/
	void RemoveComponent(IComponent* c);

	/**************************************************************************
	* @brief Check if component is in prefabComponentList
	* @param c - component pointer
	* @return int - position of component in prefabComponentList
	*************************************************************************/
	int Has(ComponentType typeID);

	/**************************************************************************
	* @brief Get prefab name
	* @return std::string - prefab name
	*************************************************************************/
	std::string GetName();

	/**************************************************************************
	* @brief Get prefab type
	* @return std::string - prefab type
	*************************************************************************/
	std::string GetType();

	/**************************************************************************
	* @brief Get component with component type
	* @param typeID - component type
	* @return IComponent*
	*************************************************************************/
	IComponent* GetComponent(ComponentType typeID);

	/**************************************************************************
	* @brief Return the component type
	* @param typeID - component type
	* @return T* - component type
	*************************************************************************/
	template <typename T> T* GetComponentType(ComponentType typeID);

	/**************************************************************************
	* @brief Return the list of components type
	* @param typeID - component type
	* @return std::vector - container of components
	*************************************************************************/
	std::vector<IComponent*> GetPrefabComponentList();

	/**************************************************************************
	* @brief Check whether sprite or texture is used
	* @return true if using sprite. false if texture instead.
	*************************************************************************/
	bool IsUsingSprite();

	/**************************************************************************
	* @brief Set whether sprite/texture is used
	* @param flag - flag to set whether sprite/texture is used
	* @return void
	*************************************************************************/
	void SetUsingSprite(bool flag);
};

/**************************************************************************
* @brief Return the component type
* @return T* - component type
*************************************************************************/
template <typename T> T* Prefab::GetComponentType(ComponentType typeID) {
	return static_cast<T*>(GetComponent(typeID));
}

#endif
