/**************************************************************************
 * @file ObjectFactory.h
 * @author HWANG Jing Rui, Austin - 70%
 * @co-author CHEAH Tristan Tze Hong - 30%
 * @par DP email: jingruiaustin.hwang@digipen.edu
 * @par DP email: t.cheah@digipen.edu
 * @par Course:	CSD 2401
 * @par	Software Engineering Project 3
 * @date 13-09-2023
 * @brief This file contains the declaration of the ObjectFactory class.
 *		  The functions include:
 *			- StringToEnum
 *			- EnumToString
 *			- BuildObjectFromFile
 *			- BuildObjectRunTime
 *			- BuildObjectFromPrefab
 *			- LoadPrefab
 *			- CloneObject
 *			- SaveObjectsToFile
 *			- Update
 *			- AssignObjectID
 *			- DestroyObject
 *			- DestroyAllObjects
 *			- GetGameObjectByID
 *			- GetGameObjectByName
 *			- GetGameObjectByType
 *			- GetGameObjectIDMap
 *			- GetPrefabMap
 *			- AddComponentFactory
 *			- AddComponent
 *			- RemoveComponent
 *			- AddPrefabToMap
 *			- RemovePrefabFromMap
 *************************************************************************/
#ifndef OBJECT_FACTORY_H
#define OBJECT_FACTORY_H

#include <string>
#include <map>
#include <set>
#include "ISystem.h"
#include "GameObject.h"
#include "Prefab.h"
#include "SystemManager.h"

#define GET_COMPONENT(GameObject, Component, ComponentType) (GameObject->GetComponentType<Component>(ComponentType))
#define GET_PREFAB_COMPONENT(Prefab, Component, ComponentType) (Prefab->GetComponentType<Component>(ComponentType))

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

	// Map to store prefabs
	std::map<std::string, Prefab*> prefabMap;

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
	* @param type - type of GameObject
	* @return GameObject*
	*************************************************************************/
	GameObject* BuildObjectRunTime(const std::string& name, const std::string& type);

	/**************************************************************************
	* @brief Create a game object based on a prefab in the prefab map
	* @param name - name of GameObject
	* @param type - type of GameObject
	* @return GameObject*
	*************************************************************************/
	GameObject* BuildObjectFromPrefab(const std::string& name, const std::string& type);

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
	* @brief Get rapidjson::Document object (containing JSON objects)
	* @param filePath - directory of JSON file
	* @return rapidjson::Document
	*************************************************************************/
	rapidjson::Document GetObjectDocSaving(const std::string& filePath);

	/**************************************************************************
	* @brief Save existing game object data to JSON file
	* @param filePath - directory of JSON file
	* @return void
	*************************************************************************/
	void SaveObjectsToFile(const std::string& filePath);

	/**************************************************************************
	* @brief Save prefab data to JSON file
	* @param filePath - directory of JSON file
	* @return void
	*************************************************************************/
	void SavePrefabsToFile(const std::string& filePath);

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
	* @brief Get a list of GameObject pointers of a specified type
	* @param name - type of GameObject
	* @return std::vector<GameObject*>
	*************************************************************************/
	std::vector<GameObject*> GetGameObjectsByType(const std::string& name);

	/**************************************************************************
	* @brief Get a prefab by name
	* @param name - name of Prefab
	* @return Prefab*
	*************************************************************************/
	Prefab* GetPrefabByName(const std::string& name);

	/**************************************************************************
	* @brief Get all game objects
	* @return std::map<size_t, GameObject*>
	*************************************************************************/
	std::map<size_t, GameObject*> GetGameObjectIDMap();
	
	/**************************************************************************
	* @brief Get all prefabs
	* @return std::map<size_t, Prefab*>
	*************************************************************************/
	std::map<std::string, Prefab*> GetPrefabMap();

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

	/**************************************************************************
	* @brief Remove a component from a game object
	* @param name - name of component type
	* @param object - pointer to game object
	* @return void
	*************************************************************************/
	void RemoveComponent(componentType name, GameObject* object);

	/**************************************************************************
	* @brief Add new prefab to map
	* @param newPrefab - pointer to new prefab
	* @param name - name of new prefab
	* @return void
	*************************************************************************/
	void AddPrefabToMap(Prefab* newPrefab, std::string name);

	/**************************************************************************
	* @brief Remove prefab from map
	* @param name - name of prefab
	* @return void
	*************************************************************************/
	void RemovePrefabFromMap(std::string name);
};
extern ObjectFactory* objectFactory;

#endif
