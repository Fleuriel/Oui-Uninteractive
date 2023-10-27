/**************************************************************************
 * @file GameObject.h
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
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <vector>
#include "IComponent.h"
#include "IState.h"

class GameObject {
private:
	// ID to reperesent game object
	size_t gameObjectID;

	// String to represent game object name
	std::string gameObjectName;

	// String to represent game object type
	std::string gameObjectType;

	// String to represent game object state
	State gameObjectState;

	// Vector of components
	std::vector<IComponent*> componentList;	// may use typedef to represent vector in the future
	

public:
	// Set ObjectFactory as friend class to access gameObjectID
	friend class ObjectFactory;
	
	/**************************************************************************
	* @brief Constructor and Destructor
	*************************************************************************/
	GameObject(const std::string& name, const std::string& type, const State& state);
	~GameObject();
	
	/**************************************************************************
	* @brief Initialize components in componentList
	* @return void
	*************************************************************************/
	void Initialize();

	/**************************************************************************
	* @brief Add component to componentList
	* @param c - component pointer
	* @param t - component type
	* @return void
	*************************************************************************/
	void AddComponent(IComponent* c, ComponentType t);

	/**************************************************************************
	* @brief Remove component from componentList
	* @param c - component pointer
	* @return void
	*************************************************************************/
	void RemoveComponent(IComponent* c);

	/**************************************************************************
	* @brief Check if component is in componentList
	* @param c - component pointer
	* @return int - position of component in componentList
	*************************************************************************/
	int Has(ComponentType typeID);

	/**************************************************************************
	* @brief Get game object ID
	* @return size_t - game object ID
	*************************************************************************/
	size_t GetGameObjectID();

	/**************************************************************************
	* @brief Get game object name
	* @return std::string - game object name
	*************************************************************************/
	std::string GetName();

	/**************************************************************************
	* @brief Get game object type
	* @return std::string - game object type
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
	* @brief Get state of game object
	* @return State
	*************************************************************************/
	inline State GetState();
};

/**************************************************************************
* @brief Return the component type
* @return T* - component type
*************************************************************************/
template <typename T> T* GameObject::GetComponentType(ComponentType typeID) {
	return static_cast<T*>(GetComponent(typeID));
}

#endif
