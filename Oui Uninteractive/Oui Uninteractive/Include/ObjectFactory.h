/**************************************************************************
 * @file ObjectFactory.h
 * @author Hwang Jing Rui, Austin
 * @co-author Tristan Cheah Tze Hong
 * @par DP email: jingruiaustin.hwang@digipen.edu
 * @par DP email: t.cheah@digipen.edu
 * @par Course:	CSD 2401
 * @par	Software Engineering Project 3
 * @date 13-09-2023
 * @brief This file contains the definiton of the ObjectFactory class.
 *		  The functions include:
 *			- stringToEnum
 *			- enumToString
 *			- BuildObjectFromFile
 *			- BuildObjectRunTime
 *			- LoadPrefab
 *			- CloneObjects
 *			- Update
 *			- AssignObjectID
 *			- DestroyObject
 *			- DestroyAllObjects
 *			- GetGameObjectByID
 *			- GetGameObjectByName
 *			- GetGameObjectIDMap
 *			- AddComponentFactory
 *			- AddComponent
 *************************************************************************/
#ifndef OBJECT_FACTORY_H
#define OBJECT_FACTORY_H

#include <string>
#include <map>
#include <set>
#include "ISystem.h"
#include "GameObject.h"

class ComponentFactoryBase;

class ObjectFactory : public ISystem {
private:
	// ID to keep track of objects
	size_t gameObjectCurrentID;

	// Map of game objects to their ID
	std::map<size_t, GameObject*> gameObjectIDMap;

	// Set to manage the destruction of game objects
	std::set<GameObject*> gameObjectDestroyList;

	// Map of component factories
	std::map<componentType, ComponentFactoryBase*> componentFactoryMap;

	// Set to store prefabs
	std::set<GameObject*> prefabSet;

public:
	/**************************************************************************
	* @brief Constructor and Destructor
	*************************************************************************/
	ObjectFactory();
	~ObjectFactory();

	/**************************************************************************
	* @brief Convert a string to ComponentType enum
	* @param str - string to convert to ComponentType
	* @return ComponentType
	*************************************************************************/
	ComponentType StringToEnum(std::string str);

	/**************************************************************************
	* @brief Convert ComponentType enum to a string
	* @param ct - ComponentType to convert to string
	* @return std::string - name of ComponentType
	*************************************************************************/
	std::string EnumToString(ComponentType ct);

	/**************************************************************************
	* @brief Create a game object based on serialized data
	* @param filePath - directory of JSON file
	* @return void
	*************************************************************************/
	void BuildObjectFromFile(const std::string& filePath);

	/**************************************************************************
	* @brief Create a game object during run-time
	* @param name - name of GameObject
	* @return GameObject*
	*************************************************************************/
	GameObject* BuildObjectRunTime(const std::string& name);

	/**************************************************************************
	* @brief Load prefab JSON file
	* @param filePath - directory of JSON file
	* @return void
	*************************************************************************/
	void LoadPrefab(const std::string& filePath);

	/**************************************************************************
	* @brief Clone a game object
	* @param gameObjectID - ID of game object to clone
	* @return bool
	*************************************************************************/
	bool CloneObject(size_t gameObjectID);

	/**************************************************************************
	* @brief Save existing game object data to JSON file
	* @param filePath - directory of JSON file
	* @return void
	*************************************************************************/
	//void SaveObjectsToFile(const std::string& filePath);

	/**************************************************************************
	* @brief Update each game object in object factory
	* @param dt - delta time
	* @return void
	*************************************************************************/
	void Update(float dt);

	/**************************************************************************
	* @brief Assign an ID to a game object and add it to the map of game objects
	* @param gameObject - pointer to game object
	* @return void
	*************************************************************************/
	void AssignObjectID(GameObject* gameObject);

	/**************************************************************************
	* @brief Add a to-be-destroyed game object to the destroy list
	* @param gameObject - pointer to game object
	* @return void
	*************************************************************************/
	void DestroyObject(GameObject* gameObject);

	/**************************************************************************
	* @brief Destroy all game objects
	* @return void
	*************************************************************************/
	void DestroyAllObjects();

	/**************************************************************************
	* @brief Get a game object by ID
	* @param gameObjectID - ID of game object
	* @return GameObject*
	*************************************************************************/
	GameObject* GetGameObjectByID(size_t gameObjectID);

	/**************************************************************************
	* @brief Get a game object by name
	* @param name - name of GameObject
	* @return GameObject*
	*************************************************************************/
	GameObject* GetGameObjectByName(const std::string& name);

	/**************************************************************************
	* @brief Get all game objects
	* @return std::map<size_t, GameObject*>
	*************************************************************************/
	std::map<size_t, GameObject*> GetGameObjectIDMap();

	// messaging...

	/**************************************************************************
	* @brief Add component factory to map
	* @param componentName - name of component type
	* @param componentFactory - pointer to component factory base
	*************************************************************************/
	void AddComponentFactory(componentType componentName, ComponentFactoryBase* componentFactory);

	/**************************************************************************
	* @brief Add component with a specified component name to game object
	* @param componentName - name of component type
	* @param gameObject - pointer to game object
	* @return bool
	*************************************************************************/
	bool AddComponent(componentType name, GameObject* object);
};
extern ObjectFactory* objectFactory;

#endif
