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

class GameObject {
private:
	// ID to reperesent game object
	size_t gameObjectID;

	// String to represent game object name
	std::string gameObjectName;

	// String to represent game object type
	std::string gameObjectType;

	// Vector of components
	std::vector<IComponent*> componentList;
	
	// Int to store animation frame
	int gameObjAnimationFrame;

	// Bool to check whether game object is using sprite or texture
	bool usingSprite;

	// String to represent texture name
	std::string textureName;

public:
	// Set ObjectFactory as friend class to access gameObjectID
	friend class ObjectFactory;
	
	/**************************************************************************
	* @brief Constructor and Destructor
	*************************************************************************/
	GameObject(const std::string& name, const std::string& type);
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
	* @brief Set game object name
	* @param newName - new game object name
	* @return void
	*************************************************************************/
	void SetName(std::string newName);

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
	* @brief Get the direction the game object is facing (for animations)
	* @return int - 1 if facing up
	*				2 if facing right
	*				3 if facing down
	*				4 if facing left
	*************************************************************************/
	int GetSpriteDirection(float directionX, float directionY);

	/**************************************************************************
	* @brief Get the animation frame (column) of the game object
	* @return int - frame of game object
	*************************************************************************/
	int GetAnimationFrame();

	/**************************************************************************
	* @brief Get the direction the game object is facing (for animations)
	* @param frame - frame to set animation to
	* @return void
	*************************************************************************/
	void SetAnimationFrame(int frame);

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

	/**************************************************************************
	* @brief Get texture of game object
	* @return std::string - texture
	*************************************************************************/
	std::string GetTexture();

	/**************************************************************************
	* @brief Set texture of game object
	* @param std::string - texture name
	* @return void
	*************************************************************************/
	void SetTexture(std::string tex);
};

/**************************************************************************
* @brief Return the component type
* @return T* - component type
*************************************************************************/
template <typename T> T* GameObject::GetComponentType(ComponentType typeID) {
	return static_cast<T*>(GetComponent(typeID));
}

#endif
