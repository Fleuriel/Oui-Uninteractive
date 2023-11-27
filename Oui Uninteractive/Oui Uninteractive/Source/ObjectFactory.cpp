/**************************************************************************
 * @file ObjectFactory.cpp
 * @author HWANG Jing Rui, Austin
 * @co-author CHEAH Tristan Tze Hong
 * @par DP email: jingruiaustin.hwang@digipen.edu
 * @par DP email: t.cheah@digipen.edu
 * @par Course:	CSD 2401
 * @par	Software Engineering Project 3
 * @date 13-09-2023
 * @brief This file contains the definition of the ObjectFactory class.
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
#include <iostream>
#include "ObjectFactory.h"
#include "JsonSerializer.h"
#include "ComponentFactory.h"
#include "PhysicsBody.h"
#include "Transform.h"
#include "LogicComponent.h"
#include "Collider.h"
#include "EnemyFSM.h"
#include "HealthComponent.h"

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
	else if (str == "EnemyFSM") {
		return ComponentType::ENEMY_FSM;
	}
	else if (str == "HealthComponent") {
		return ComponentType::HEALTH;
	}
	else if (str == "InventoryComponent") {
		return ComponentType::INVENTORY;
	}
	else {
		return ComponentType::COUNT;
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
	else if (ct == ComponentType::ENEMY_FSM) {
		return "EnemyFSM";
	}
	else if (ct == ComponentType::HEALTH) {
		return "HealthComponent";
	}
	else if (ct == ComponentType::INVENTORY) {
		return "InventoryComponent";
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

	for (auto& it : prefabMap) {
		delete it.second;
	}
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
			gameObject->SetUsingSprite(obj["UsingSprite"].GetBool());
			gameObject->SetTexture(obj["Texture"].GetString());

			// Get each component(s) in current object
			const rapidjson::Value& components{ obj["Components"] };

			for (rapidjson::Value::ConstMemberIterator itr{ components.MemberBegin() }; itr != components.MemberEnd(); ++itr) {
				componentName = itr->name.GetString();
				if (componentName == "InventoryComponent") {
					int deez = 0;
				}
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
		std::cerr << "Failed to de-serialize object." << std::endl;
	}
}

/**************************************************************************
* @brief Create a game object during run-time
* @param name - name of GameObject prefab
* @return GameObject*
*************************************************************************/
GameObject* ObjectFactory::BuildObjectRunTime(const std::string& name, const std::string& type) {
	GameObject* objectRunTime{ new GameObject(name, type) };
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
		gameObject->SetUsingSprite(prefabMap[type]->IsUsingSprite());
		gameObject->SetTexture(prefabMap[type]->GetTexture());
		
		// Copy component list from prefab to newly-created game object
		for (size_t i{}; i < prefabMap[type]->prefabComponentList.size(); ++i) {
			gameObject->AddComponent(prefabMap[type]->prefabComponentList[i]->Clone(), prefabMap[type]->prefabComponentList[i]->componentType);
		}

		// Assign an ID to the game object
		AssignObjectID(gameObject);

		// Initialize the components in the newly-created game object	
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
			Prefab* prefab{ new Prefab(obj["Name"].GetString(), obj["Type"].GetString()) };
			prefab->SetUsingSprite(obj["UsingSprite"].GetBool());
			prefab->SetTexture(obj["Texture"].GetString());

			// Get each component(s) in current prefab
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
					prefab->AddComponent(component, componentFactory->type);
				}
			}

			// Add prefab to prefab map
			prefabMap[prefab->GetName()] = prefab;
		}
	}
	else {
		std::cerr << "Failed to de-serialize prefab." << std::endl;
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
		clone->SetUsingSprite(original->IsUsingSprite());

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
* @brief Get rapidjson::Document object (containing JSON objects)
* @param filePath - directory of JSON file
* @return rapidjson::Document
*************************************************************************/
rapidjson::Document ObjectFactory::GetObjectDocSaving(const std::string& filePath) {
	rapidjson::Document objDoc;
	rapidjson::Document::AllocatorType& allocator = objDoc.GetAllocator();
	JsonSerializer serializer;
	serializer.ReadJSONFile(filePath, objDoc);

	// Setting object for output JSON
	objDoc.SetObject();

	// Store object count
	int objectCount{};

	// Add objects to Objects array
	rapidjson::Value writeObjects(rapidjson::kArrayType);
	for (const auto& it : gameObjectIDMap) {
		if (it.second->GetType() == "Wall") {
			continue;
		}	
		const GameObject* gameObject = it.second;
		rapidjson::Value jsonObj(rapidjson::kObjectType);	// Create JSON object
		rapidjson::Value stringVar;

		// Add name and type members to JSON object
		stringVar.SetString(gameObject->gameObjectName.c_str(), allocator);
		jsonObj.AddMember("Name", stringVar, allocator);
		stringVar.SetString(gameObject->gameObjectType.c_str(), allocator);
		jsonObj.AddMember("Type", stringVar, allocator);
		stringVar.SetBool(gameObject->usingSprite);
		jsonObj.AddMember("UsingSprite", stringVar, allocator);
		stringVar.SetString(gameObject->textureName.c_str(), allocator);
		jsonObj.AddMember("Texture", stringVar, allocator);

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
				individualComponent.AddMember("Mass", GET_COMPONENT(it.second, PhysicsBody, ComponentType::PHYSICS_BODY)->mass, allocator);
				individualComponent.AddMember("IsStatic", GET_COMPONENT(it.second, PhysicsBody, ComponentType::PHYSICS_BODY)->isStatic, allocator);
				individualComponent.AddMember("FrictionForce", GET_COMPONENT(it.second, PhysicsBody, ComponentType::PHYSICS_BODY)->frictionForce, allocator);
			}
			else if (componentName == "Transform") {
				individualComponent.AddMember("PositionX", GET_COMPONENT(it.second, Transform, ComponentType::TRANSFORM)->position.x, allocator);
				individualComponent.AddMember("PositionY", GET_COMPONENT(it.second, Transform, ComponentType::TRANSFORM)->position.y, allocator);
				individualComponent.AddMember("Rotation", GET_COMPONENT(it.second, Transform, ComponentType::TRANSFORM)->rotation, allocator);
				individualComponent.AddMember("ScaleX", GET_COMPONENT(it.second, Transform, ComponentType::TRANSFORM)->scale.x, allocator);
				individualComponent.AddMember("ScaleY", GET_COMPONENT(it.second, Transform, ComponentType::TRANSFORM)->scale.y, allocator);
			}
			else if (componentName == "LogicComponent") {
				// Save ScriptID in an array
				rapidjson::Value scriptIDArray(rapidjson::kArrayType);
				for (auto& scriptID : GET_COMPONENT(it.second, LogicComponent, ComponentType::LOGICCOMPONENT)->scriptIndexSet) {
					scriptIDArray.PushBack(scriptID, allocator);
				}

				// Add array to individual component
				individualComponent.AddMember("ScriptID", scriptIDArray, allocator);
			}
			else if (componentName == "Collider") {
				individualComponent.AddMember("ColliderSizeX", GET_COMPONENT(it.second, Collider, ComponentType::COLLIDER)->tx->scale.x, allocator);
				individualComponent.AddMember("ColliderSizeY", GET_COMPONENT(it.second, Collider, ComponentType::COLLIDER)->tx->scale.y, allocator);
				individualComponent.AddMember("ColliderRotation", GET_COMPONENT(it.second, Collider, ComponentType::COLLIDER)->tx->rotation, allocator);
			}
			else if (componentName == "EnemyFSM") {
				individualComponent.AddMember("AggroRange", GET_COMPONENT(it.second, EnemyFSM, ComponentType::ENEMY_FSM)->aggroRange, allocator);
			}
			else if (componentName == "HealthComponent") {
				individualComponent.AddMember("MaxHealth", GET_COMPONENT(it.second, HealthComponent, ComponentType::HEALTH)->maxHealth, allocator);
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

		// Increment object counter
		++objectCount;
	}

	// Adding object count member
	objDoc.AddMember("ObjectCount", objectCount, allocator);

	// Add object array to output JSON
	objDoc.AddMember("Objects", writeObjects, allocator);

	return objDoc;
}

/**************************************************************************
* @brief Save existing game object data to JSON file
* @param filePath - directory of JSON file
* @return void
*************************************************************************/
void ObjectFactory::SaveObjectsToFile(const std::string& filePath) {
	rapidjson::Document objDoc{ GetObjectDocSaving(filePath) };
	JsonSerializer serializer;

	if (serializer.WriteJSONFile(filePath, objDoc)) {
		std::cout << "Successfully saved objects to file." << std::endl;
	}
}

/**************************************************************************
* @brief Save prefabs to JSON file
* @param filePath - directory of JSON file
* @return void
*************************************************************************/
void ObjectFactory::SavePrefabsToFile(const std::string& filePath) {
	rapidjson::Document objDoc;
	rapidjson::Document::AllocatorType& allocator = objDoc.GetAllocator();
	JsonSerializer serializer;
	serializer.ReadJSONFile(filePath, objDoc);

	// Setting object for output JSON
	objDoc.SetObject();

	// Adding object count
	objDoc.AddMember("ObjectCount", prefabMap.size(), allocator);

	// Add objects to Objects array
	rapidjson::Value writeObjects(rapidjson::kArrayType);
	for (const auto& it : prefabMap) {
		const Prefab* prefab = it.second;
		rapidjson::Value jsonObj(rapidjson::kObjectType);	// Create JSON object
		rapidjson::Value stringVar;

		// Add name and type members to JSON object
		stringVar.SetString(prefab->prefabName.c_str(), allocator);
		jsonObj.AddMember("Name", stringVar, allocator);
		stringVar.SetString(prefab->prefabName.c_str(), allocator);
		jsonObj.AddMember("Type", stringVar, allocator);
		stringVar.SetString(prefab->textureName.c_str(), allocator);
		jsonObj.AddMember("Texture", stringVar, allocator);
		stringVar.SetBool(prefab->usingSprite);
		jsonObj.AddMember("UsingSprite", stringVar, allocator);

		// Components object
		rapidjson::Value components(rapidjson::kObjectType);

		for (const auto& cmp : prefab->prefabComponentList) {
			// Create individual component
			rapidjson::Value individualComponent(rapidjson::kObjectType);
			std::string componentName{ EnumToString(cmp->componentType) };

			// Add component data
			if (componentName == "PhysicsBody") {
				individualComponent.AddMember("VelocityX", GET_COMPONENT(it.second, PhysicsBody, ComponentType::PHYSICS_BODY)->velocity.x, allocator);
				individualComponent.AddMember("VelocityY", GET_COMPONENT(it.second, PhysicsBody, ComponentType::PHYSICS_BODY)->velocity.y, allocator);
				individualComponent.AddMember("RotationSpeed", GET_COMPONENT(it.second, PhysicsBody, ComponentType::PHYSICS_BODY)->rotationSpeed, allocator);
				individualComponent.AddMember("Speed", GET_COMPONENT(it.second, PhysicsBody, ComponentType::PHYSICS_BODY)->speed, allocator);
				individualComponent.AddMember("Mass", GET_COMPONENT(it.second, PhysicsBody, ComponentType::PHYSICS_BODY)->mass, allocator);
				individualComponent.AddMember("IsStatic", GET_COMPONENT(it.second, PhysicsBody, ComponentType::PHYSICS_BODY)->isStatic, allocator);
				individualComponent.AddMember("FrictionForce", GET_COMPONENT(it.second, PhysicsBody, ComponentType::PHYSICS_BODY)->frictionForce, allocator);
			}
			else if (componentName == "Transform") {
				individualComponent.AddMember("PositionX", GET_COMPONENT(it.second, Transform, ComponentType::TRANSFORM)->position.x, allocator);
				individualComponent.AddMember("PositionY", GET_COMPONENT(it.second, Transform, ComponentType::TRANSFORM)->position.y, allocator);
				individualComponent.AddMember("Rotation", GET_COMPONENT(it.second, Transform, ComponentType::TRANSFORM)->rotation, allocator);
				individualComponent.AddMember("ScaleX", GET_COMPONENT(it.second, Transform, ComponentType::TRANSFORM)->scale.x, allocator);
				individualComponent.AddMember("ScaleY", GET_COMPONENT(it.second, Transform, ComponentType::TRANSFORM)->scale.y, allocator);
			}
			else if (componentName == "LogicComponent") {
				// Save ScriptID in an array
				rapidjson::Value scriptIDArray(rapidjson::kArrayType);
				for (auto& scriptID : GET_COMPONENT(it.second, LogicComponent, ComponentType::LOGICCOMPONENT)->scriptIndexSet) {
					scriptIDArray.PushBack(scriptID, allocator);
				}

				// Add array to individual component
				individualComponent.AddMember("ScriptID", scriptIDArray, allocator);
			}
			else if (componentName == "Collider") {
				individualComponent.AddMember("ColliderSizeX", GET_COMPONENT(it.second, Collider, ComponentType::COLLIDER)->tx->scale.x, allocator);
				individualComponent.AddMember("ColliderSizeY", GET_COMPONENT(it.second, Collider, ComponentType::COLLIDER)->tx->scale.y, allocator);
				individualComponent.AddMember("ColliderRotation", GET_COMPONENT(it.second, Collider, ComponentType::COLLIDER)->tx->rotation, allocator);
			}
			else if (componentName == "EnemyFSM") {
				individualComponent.AddMember("AggroRange", GET_COMPONENT(it.second, EnemyFSM, ComponentType::ENEMY_FSM)->aggroRange, allocator);
			}
			else if (componentName == "HealthComponent") {
				individualComponent.AddMember("MaxHealth", GET_COMPONENT(it.second, HealthComponent, ComponentType::HEALTH)->maxHealth, allocator);
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
	if (sysManager->isPaused == false) {
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
* @brief Get a list of GameObject pointers of a specified type
* @param name - type of GameObject
* @return std::vector<GameObject*>
*************************************************************************/
std::vector<GameObject*> ObjectFactory::GetGameObjectsByType(const std::string& type) {
	std::map<size_t, GameObject*>::iterator it{ gameObjectIDMap.begin() };
	std::vector<GameObject*> objects;

	while (it != gameObjectIDMap.end()) {
		if (it->second->gameObjectType == type) {
			objects.push_back(it->second);

			if (type == "Player")
				break;
		}

		++it;
	}

	return objects;
}

/**************************************************************************
* @brief Get a prefab by name
* @param name - name of Prefab
* @return Prefab*
*************************************************************************/
Prefab* ObjectFactory::GetPrefabByName(const std::string& name) {
	std::map<std::string, Prefab*>::iterator it{ prefabMap.begin() };

	while (it != prefabMap.end()) {
		if (it->second->prefabName == name) {
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
* @brief Get all prefabs
* @return std::map<size_t, Prefab*>
*************************************************************************/
std::map<std::string, Prefab*> ObjectFactory::GetPrefabMap() {
	return prefabMap;
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

/**************************************************************************
* @brief Remove a component from a game object
* @param name - name of component type
* @param object - pointer to game object
* @return void
*************************************************************************/
void ObjectFactory::RemoveComponent(componentType name, GameObject* object) {
	int componentIndex = object->Has(name);
	if (componentIndex != -1) {
		object->RemoveComponent(object->componentList[componentIndex]);
	}
}

/**************************************************************************
* @brief Add new prefab to map
* @param newPrefab - pointer to new prefab
* @param name - name of new prefab
* @return void
*************************************************************************/
void ObjectFactory::AddPrefabToMap(Prefab* newPrefab, std::string name) {
	prefabMap.insert(std::pair<std::string, Prefab*>(name, newPrefab));
}

/**************************************************************************
* @brief Remove prefab from map
* @param name - name of prefab
* @return void
*************************************************************************/
void ObjectFactory::RemovePrefabFromMap(std::string name) {
	delete prefabMap[name];
	prefabMap.erase(name);
}
