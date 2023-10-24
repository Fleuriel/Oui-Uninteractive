/**************************************************************************
 * @file ObjectFactory.cpp
 * @author HWANG Jing Rui, Austin
 * @co-author CHEAH Tristan Tze Hong
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
 *			- CloneObjects
 *			- SaveObjectsToFile
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
#include <iostream>
#include "ObjectFactory.h"
#include "JsonSerializer.h"
#include "ComponentFactory.h"
#include "PhysicsBody.h"
#include "Transform.h"

ObjectFactory* objectFactory = NULL;

/**************************************************************************
* @brief Convert a string to ComponentType enum
* @param str - string to convert to ComponentType
* @return ComponentType
*************************************************************************/
ComponentType ObjectFactory::StringToEnum(std::string str) {
	if (str == "PhysicsBody") {
		return ComponentType::PHYSICS_BODY;
	}
	else if (str == "Transform") {
		return ComponentType::TRANSFORM;
	}
	else if (str == "LogicComponent") {
		return ComponentType::LOGICCOMPONENT;
	}
	else if (str == "Collider") {
		return ComponentType::COLLIDER;
	}
	else {
		return ComponentType::NONE;
	}
}

/**************************************************************************
* @brief Convert ComponentType enum to a string
* @param ct - ComponentType to convert to string
* @return std::string - name of ComponentType
*************************************************************************/
std::string ObjectFactory::EnumToString(ComponentType ct) {
	if (ct == ComponentType::PHYSICS_BODY) {
		return "PhysicsBody";
	}
	else if (ct == ComponentType::TRANSFORM) {
		return "Transform";
	}
	else if (ct == ComponentType::LOGICCOMPONENT) {
		return "LogicComponent";
	}
	else if (ct == ComponentType::COLLIDER) {
		return "Collider";
	}
	else {
		return "None";
	}
}

/**************************************************************************
* @brief Object Factory Constructor
*************************************************************************/
ObjectFactory::ObjectFactory() : gameObjectCurrentID{} {
	if (objectFactory != NULL) {
		return;
	}
	std::cout << "Component Fac: " << componentFactoryMap.size() << "\n";
	objectFactory = this;
}

/**************************************************************************
* @brief Object Factory Destructor
*************************************************************************/
ObjectFactory::~ObjectFactory() {
	for (auto& it : componentFactoryMap) {
		delete it.second;
	}
	componentFactoryMap.clear();
	gameObjectIDMap.clear();
	gameObjectDestroyList.clear();
	prefabMap.clear();
}

/**************************************************************************
* @brief Create a game object based on serialized data
* @param filePath - directory of JSON file
*************************************************************************/
void ObjectFactory::BuildObjectFromFile(const std::string& filePath) {
	// Create rapidjson doc object and serializer
	rapidjson::Document objDoc;
	JsonSerializer serializer;
	std::string componentName;
	
	// Read data from file
	if (serializer.ReadJSONFile(filePath, objDoc)) {
		// For each object in Objects array (in JSON file)
		for (auto& obj : objDoc["Objects"].GetArray()) {
			GameObject* gameObject{ new GameObject(obj["Name"].GetString(), obj["Type"].GetString()) };

			// Get each component(s) in current object
			const rapidjson::Value& components{ obj["Components"] };

			for (rapidjson::Value::ConstMemberIterator itr{ components.MemberBegin() }; itr != components.MemberEnd(); ++itr) {
				componentName = itr->name.GetString();
				ComponentType type = StringToEnum(componentName);

				if (!componentFactoryMap.contains(type)) {
					std::cerr << "Component name not found." << std::endl;
				}
				else {
					// Set componentFactory to create the component itself
					ComponentFactoryBase* componentFactory = componentFactoryMap[type];

					// Create the component
					IComponent* component = componentFactory->CreateComponent();

					// Serialize to store component data
					component->Serialize(itr);

					// Add the component to the game object
					gameObject->AddComponent(component, componentFactory->type);
				}
			}

			// Assign an ID to the game object
			AssignObjectID(gameObject);

			// Initialize the components in the current object
			gameObject->Initialize();
		}		
	}
	else {
		std::cerr << "Failed to serialize object." << std::endl;
	}
}

/**************************************************************************
* @brief Create a game object during run-time
* @param name - name of GameObject prefab
* @return GameObject*
*************************************************************************/
GameObject* ObjectFactory::BuildObjectRunTime(const std::string& name, const std::string& type) {
	GameObject* objectRunTime{new GameObject(name, type)};
	AssignObjectID(objectRunTime);
	return objectRunTime;
}

/**************************************************************************
* @brief Create a game object based on a prefab in the prefab map
* @param name - name of GameObject
* @param type - type of GameObject (name of prefab)
* @return GameObject*
*************************************************************************/
GameObject* ObjectFactory::BuildObjectFromPrefab(const std::string& name, const std::string& type) {
	// Check if prefab type exists
	if (prefabMap.find(type) == prefabMap.end()) {
		return nullptr;
	}
	else {
		GameObject* gameObject{ new GameObject(name, type) };
	
		std::string componentName;

		for (size_t i{}; i < prefabMap[type].size(); ++i) {
			componentName = prefabMap[type][i];
			ComponentType componentType{ StringToEnum(componentName) };

			if (componentFactoryMap.find(componentType) == componentFactoryMap.end()) {
				std::cerr << "Component name not found." << std::endl;
			}
			else {
				// Set componentFactory to create the component itself
				ComponentFactoryBase* componentFactory = componentFactoryMap[componentType];

				// Create the component
				IComponent* component = componentFactory->CreateComponent();

				// Add the component to the game object
				gameObject->AddComponent(component, componentFactory->type);
			}
		}
		// Assign an ID to the game object
		AssignObjectID(gameObject);

		// Initialize the components in the current object
		gameObject->Initialize();

		return gameObject;
	}
}

/**************************************************************************
* @brief Load prefab JSON file
* @param filePath - directory of JSON file
* @return void
*************************************************************************/
void ObjectFactory::LoadPrefab(const std::string& filePath) {
	// Create rapidjson doc object and serializer
	rapidjson::Document objDoc;
	JsonSerializer serializer;
	std::string componentName;

	// Read data from file
	if (serializer.ReadJSONFile(filePath, objDoc)) {
		// For each object in Objects array (in JSON file)
		for (auto& obj : objDoc["Objects"].GetArray()) {
			std::string prefabName{ obj["Name"].GetString() };
			std::vector<std::string> prefabComponents{};

			// Get each component(s) in current prefab object
			for (auto& cmp : obj["Components"].GetArray()) {
				prefabComponents.push_back(cmp.GetString());
			}

			// Add the prefab to the prefab map
			prefabMap[prefabName] = prefabComponents;
		}
	}
	else {
		std::cerr << "Failed to load prefabs." << std::endl;
	}
}

/**************************************************************************
* @brief Clone a game object
* @param gameObjectID - ID of game object to clone
* @return bool
*************************************************************************/
bool ObjectFactory::CloneObject(size_t gameObjectID) {
	if (gameObjectIDMap.find(gameObjectID) != gameObjectIDMap.end()) {
		GameObject* original = (gameObjectIDMap.find(gameObjectID)->second);

		std::string objectStr;
		objectStr += "Object" + std::to_string(gameObjectCurrentID + 1);

		GameObject* clone = BuildObjectRunTime(objectStr, original->gameObjectType);

		for (int i = 0; i < original->componentList.size(); i++) {
			clone->AddComponent(original->componentList.at(i)->Clone(), original->componentList[i]->componentType);
		}

		clone->Initialize();
		return true;
	}
	else {
		return false;
	}
}

/**************************************************************************
* @brief Save existing game object data to JSON file
* @param filePath - directory of JSON file
* @return void
*************************************************************************/
void ObjectFactory::SaveObjectsToFile(const std::string& filePath) {
	rapidjson::Document objDoc;
	rapidjson::Document::AllocatorType& allocator = objDoc.GetAllocator();
	JsonSerializer serializer;
	serializer.ReadJSONFile(filePath, objDoc);

	// Setting object for output JSON
	objDoc.SetObject();

	// Adding object count
	objDoc.AddMember("ObjectCount", gameObjectIDMap.size(), allocator);
	
	// Add objects to Objects array
	rapidjson::Value writeObjects(rapidjson::kArrayType);
	for (const auto& it : gameObjectIDMap) {
		const GameObject* gameObject = it.second;
		rapidjson::Value jsonObj(rapidjson::kObjectType);	// Create JSON object
		rapidjson::Value stringVar;

		// Add name and type members to JSON object
		stringVar.SetString(gameObject->gameObjectName.c_str(), allocator);
		jsonObj.AddMember("Name", stringVar, allocator);
		stringVar.SetString(gameObject->gameObjectType.c_str(), allocator);
		jsonObj.AddMember("Type", stringVar, allocator);

		// Components object
		rapidjson::Value components(rapidjson::kObjectType);

		for (const auto& cmp : gameObject->componentList) {
			// Create individual component
			rapidjson::Value individualComponent(rapidjson::kObjectType);
			std::string componentName{ EnumToString(cmp->componentType) };

			// Add component data
			if (componentName == "PhysicsBody") {
				individualComponent.AddMember("VelocityX", GET_COMPONENT(it.second, PhysicsBody, ComponentType::PHYSICS_BODY)->velocity.x, allocator);
				individualComponent.AddMember("VelocityY", GET_COMPONENT(it.second, PhysicsBody, ComponentType::PHYSICS_BODY)->velocity.y, allocator);
				individualComponent.AddMember("RotationSpeed", GET_COMPONENT(it.second, PhysicsBody, ComponentType::PHYSICS_BODY)->rotationSpeed, allocator);
				individualComponent.AddMember("Speed", GET_COMPONENT(it.second, PhysicsBody, ComponentType::PHYSICS_BODY)->speed, allocator);
			}
			else if (componentName == "Transform") {
				individualComponent.AddMember("PositionX", GET_COMPONENT(it.second, Transform, ComponentType::TRANSFORM)->position.x, allocator);
				individualComponent.AddMember("PositionY", GET_COMPONENT(it.second, Transform, ComponentType::TRANSFORM)->position.y, allocator);
				individualComponent.AddMember("Rotation", GET_COMPONENT(it.second, Transform, ComponentType::TRANSFORM)->rotation, allocator);
				individualComponent.AddMember("Scale", GET_COMPONENT(it.second, Transform, ComponentType::TRANSFORM)->scale, allocator);
			}
			
			// Add individual component to components object
			rapidjson::Value componentNameJson;
			componentNameJson.SetString(componentName.c_str(), allocator);
			components.AddMember(componentNameJson, individualComponent, allocator);
		}

		// Add components members to JSON object
		jsonObj.AddMember("Components", components, allocator);

		// Add JSON object to Objects array
		writeObjects.PushBack(jsonObj, allocator);
	}

	// Add object array to output JSON
	objDoc.AddMember("Objects", writeObjects, allocator);

	if (serializer.WriteJSONFile(filePath, objDoc)) {
		std::cout << "Successfully saved objects to file." << std::endl;
	}
}

/**************************************************************************
* @brief Update each game object in object factory
* @param dt - delta time
* @return void
*************************************************************************/
void ObjectFactory::Update(float dt) {
	(void)dt;
	std::set<GameObject*>::iterator setIt = gameObjectDestroyList.begin();

	// Destroy game objects in destroy list
	for (; setIt != gameObjectDestroyList.end(); ++setIt) {
		GameObject* gameObject = *setIt;
		std::map<size_t, GameObject*>::iterator mapIt = gameObjectIDMap.find(gameObject->gameObjectID);

		delete gameObject;
		gameObjectIDMap.erase(mapIt);
	}

	gameObjectDestroyList.clear();
}

/**************************************************************************
* @brief Assign an ID to a game object and add it to the map of game objects
* @param gameObject - pointer to game object
* @return void
*************************************************************************/
void ObjectFactory::AssignObjectID(GameObject* gameObject) {
	// Assign ID to gameObject
	gameObject->gameObjectID = gameObjectCurrentID;
		
	// Add gameObject to the map
	gameObjectIDMap[gameObjectCurrentID] = gameObject;

	// Increment current ID
	++gameObjectCurrentID;
}

/**************************************************************************
* @brief Add a to-be-destroyed game object to the destroy list
* @param gameObject - pointer to game object
* @return void
*************************************************************************/
void ObjectFactory::DestroyObject(GameObject* gameObject) {
	gameObjectDestroyList.insert(gameObject);
}

/**************************************************************************
* @brief Destroy all game objects
* @return void
*************************************************************************/
void ObjectFactory::DestroyAllObjects() {
	std::map<size_t, GameObject*>::iterator it = gameObjectIDMap.begin();

	while (it != gameObjectIDMap.end()) {
		/*for (int i = 0; i < it->second->componentList.size(); i++) {
			delete it->second->componentList.at(i);
		}*/
		delete it->second;
		++it;
	}
	gameObjectIDMap.clear();
	gameObjectCurrentID = 0;
}

/**************************************************************************
* @brief Get a game object by ID
* @param gameObjectID - ID of game object
* @return GameObject*
*************************************************************************/
GameObject* ObjectFactory::GetGameObjectByID(size_t gameObjectID) {
	if (gameObjectIDMap.find(gameObjectID) != gameObjectIDMap.end())
		return gameObjectIDMap[gameObjectID];

	return nullptr;
}

/**************************************************************************
* @brief Get a game object by name
* @param name - name of GameObject
* @return GameObject*
*************************************************************************/
GameObject* ObjectFactory::GetGameObjectByName(const std::string& name) {
	std::map<size_t, GameObject*>::iterator it{gameObjectIDMap.begin()};

	while (it != gameObjectIDMap.end()) {
		if (it->second->gameObjectName == name) {
			return it->second;
		}

		++it;
	}

	return nullptr;
}
/**************************************************************************
* @brief Get all game objects
* @return std::map<size_t, GameObject*>
*************************************************************************/
std::map<size_t, GameObject*> ObjectFactory::GetGameObjectIDMap() {
	return gameObjectIDMap;
}
/**************************************************************************
* @brief Add component factory to map
* @param componentName - name of component type
* @param componentFactory - pointer to component factory base
*************************************************************************/
void ObjectFactory::AddComponentFactory(componentType componentName, ComponentFactoryBase* componentFactory) {
	componentFactoryMap.insert(std::pair(componentName, componentFactory));
}
/**************************************************************************
* @brief Add component with a specified component name to game object
* @param componentName - name of component type
* @param gameObject - pointer to game object
* @return bool
*************************************************************************/
bool ObjectFactory::AddComponent(componentType componentName, GameObject* gameObject) {
	// Get component factory
	std::map<componentType, ComponentFactoryBase*>::iterator it = componentFactoryMap.find(componentName);

	// Check if component factory exists
	if (it != componentFactoryMap.end()) {
		// Add component to game object
		ComponentFactoryBase* factory = it->second;
		IComponent* component = factory->CreateComponent();

		gameObject->AddComponent(component, factory->type);
	}
	else {
		return false;
	}

	return true;
}