/**************************************************************************
 * @file		  ObjectFactory.cpp
 * @author
 * @par DP email:
 * @par Course:	  CSD 2401
 * @par			  Software Engineering Project 3
 * @date		  09-13-2023
 * @brief
 *************************************************************************/
#include <iostream>
#include "ObjectFactory.h"
#include "JsonSerializer.h"
#include "ComponentFactory.h"

ObjectFactory* objectFactory = NULL;

/**************************************************************************
* @brief Convert a string to ComponentType enum
* @param str - string to convert to ComponentType
* @return ComponentType
*************************************************************************/
ComponentType ObjectFactory::stringToEnum(std::string str) {
	if (str == "PhysicsBody") {
		return ComponentType::PhysicsBody;
	}
	else if (str == "Transform") {
		return ComponentType::Transform;
	}
	else {
		return ComponentType::None;
	}
}

/**************************************************************************
* @brief Convert ComponentType enum to a string
* @param ct - ComponentType to convert to string
* @return std::string - name of ComponentType
*************************************************************************/
std::string ObjectFactory::enumToString(ComponentType ct) {
	if (ct == ComponentType::PhysicsBody) {
		return "PhysicsBody";
	}
	else if (ct == ComponentType::Transform) {
		return "Transform";
	}
	else {
		return "None";
	}
}

/**************************************************************************
* @brief Object Factory Initializer
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
			// Create GameObject
			GameObject* gameObject{new GameObject(obj["Name"].GetString())};

			// Get each component in object
			const rapidjson::Value& components{obj["Components"]};

			for (rapidjson::Value::ConstMemberIterator itr{components.MemberBegin()}; itr != components.MemberEnd(); ++itr) {
				componentName = itr->name.GetString();
				ComponentType type = stringToEnum(componentName);

				if (componentFactoryMap.find(type) == componentFactoryMap.end()) {
					std::cerr << "Component name not found." << std::endl;
				}

				else {
					// Set componentFactory to create the component itself
					ComponentFactoryBase* componentFactory = componentFactoryMap[type];

					// Create the component
					IComponent* component = componentFactory->CreateComponent();

					// Serialize to store component data
					component->Serialize(filePath, itr);

					// Add the component to the game object
					gameObject->AddComponent(component, componentFactory->type);
				}
			}
			
			// Assign an ID to the game object
			AssignObjectID(gameObject);

			// Initialize each object in map
			for (auto i{ gameObjectIDMap.begin() }; i != gameObjectIDMap.end(); ++i) {
				i->second->Initialize();
			}
		}		
	}
	else {
		std::cerr << "Failed to serialize object." << std::endl;
	}
}

/**************************************************************************
* @brief Create a game object during run-time
* @param name - name of GameObject
* @return GameObject*
*************************************************************************/
GameObject* ObjectFactory::BuildObjectRunTime(const std::string name) {
	GameObject* objectRunTime{new GameObject(name)};
	AssignObjectID(objectRunTime);
	return objectRunTime;
}

/**************************************************************************
* @brief Update each game object in object factory
* @param dt - delta time
*************************************************************************/
void ObjectFactory::Update(float dt) {
	std::set<GameObject*>::iterator it = gameObjectDestroyList.begin();

	// Destroy game objects in destroy list
	for (; it != gameObjectDestroyList.end(); it++) {
		GameObject* gameObject = *it;

		//Insert double free protection here
		delete gameObject;
	}

	gameObjectDestroyList.clear();
}

/**************************************************************************
* @brief Clone a game object
* @param gameObjectID - ID of game object to clone
* @return bool
*************************************************************************/
bool ObjectFactory::CloneObject(size_t gameObjectID) {
	if (gameObjectIDMap.find(gameObjectID) != gameObjectIDMap.end()) {
		GameObject* original = (gameObjectIDMap.find(gameObjectID)->second);
		GameObject* clone = BuildObjectRunTime(original->gameObjectName);

		for (int i = 0; i < original->componentList.size(); i++) {
			AddComponent(original->componentList[i]->componentType, clone);
		}

		clone->Initialize();
		return true;
	}
	else {
		return false;
	}
}

/**************************************************************************
* @brief Assign an ID to a game object and add it to the map of game objects
* @param gameObject - pointer to game object
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
*************************************************************************/
void ObjectFactory::DestroyObject(GameObject* gameObject) {
	gameObjectDestroyList.insert(gameObject);
}

/**************************************************************************
* @brief Destroy all game objects
*************************************************************************/
void ObjectFactory::DestroyAllObjects() {
	std::map<size_t, GameObject*>::iterator it = gameObjectIDMap.begin();

	while (it != gameObjectIDMap.end()) {
		delete it->second;
		it++;
	}
}


/**************************************************************************
* @brief Get a game object by ID
* @param gameObjectID - ID of game object
* @return GameObject*
*************************************************************************/
GameObject* ObjectFactory::GetGameObjectByID(size_t gameObjectID)
{
	if (gameObjectIDMap.find(gameObjectID) != gameObjectIDMap.end())
		return gameObjectIDMap[gameObjectID];

	return nullptr;
}

// Get all game objects
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
// 
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