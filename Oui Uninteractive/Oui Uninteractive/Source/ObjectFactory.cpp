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

// Object Factory initializer
ObjectFactory::ObjectFactory() : gameObjectCurrentID{} {
	if (objectFactory != NULL) {
		return;
	}
	std::cout << "Component Fac: " << componentFactoryMap.size() << "\n";
	objectFactory = this;
}

// Object Factory destructor
ObjectFactory::~ObjectFactory() {
	for (auto& it : componentFactoryMap) {
		delete it.second;
	}
}

// Create a game object based on serialized data
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
			GameObject* gameObject{new GameObject()};
			gameObject->gameObjectName = obj["Name"].GetString();;

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

// Create a game object during run-time
GameObject* ObjectFactory::BuildObjectRunTime() {
	GameObject* objectRunTime{new GameObject()};
	AssignObjectID(objectRunTime);
	return objectRunTime;
}

// Update each game object in object factory
void ObjectFactory::Update(float dt) {
	std::set<GameObject*>::iterator it = gameObjectDestroyList.begin();

	for (; it != gameObjectDestroyList.end(); it++) {
		GameObject* gameObject = *it;

		//Insert double free protection here
		delete gameObject;
	}
	gameObjectDestroyList.clear();
}

// Clone a game object
bool ObjectFactory::CloneObject(size_t gameObjectID) {
	//std::map<size_t, GameObject*>::iterator it = gameObjectIDMap.begin();
	
	if (gameObjectIDMap.find(gameObjectID) != gameObjectIDMap.end()) {
		GameObject* original = (gameObjectIDMap.find(gameObjectID)->second);
		GameObject* clone = BuildObjectRunTime();

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

// Assign an ID to a game object and add it to the map of game objects
void ObjectFactory::AssignObjectID(GameObject* gameObject) {
	// Assign ID to gameObject
	gameObject->gameObjectID = gameObjectCurrentID;

	// Add gameObject to the map
	gameObjectIDMap[gameObjectCurrentID] = gameObject;

	// Increment ID
	++gameObjectCurrentID;
}

// Add a to-be-destroyed game object to the destroy list
void ObjectFactory::DestroyObject(GameObject* gameObject) {
	gameObjectDestroyList.insert(gameObject);
}

// Destroy all game objects
void ObjectFactory::DestroyAllObjects() {
	std::map<size_t, GameObject*>::iterator it = gameObjectIDMap.begin();

	while (it != gameObjectIDMap.end()) {
		delete it->second;
		it++;
	}
}

// Get a game object by ID
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

// Add component factory to map
void ObjectFactory::AddComponentFactory(componentType componentName, ComponentFactoryBase* componentFactory) {
	componentFactoryMap.insert(std::pair(componentName, componentFactory));
}

// Add component with a specified component name to game object
bool ObjectFactory::AddComponent(componentType componentName, GameObject* object) {
	// Get component factory
	std::map<componentType, ComponentFactoryBase*>::iterator it = componentFactoryMap.find(componentName);

	// Check if component factory exists
	if (it != componentFactoryMap.end()) {
		// Add component to game object
		ComponentFactoryBase* factory = it->second;
		IComponent* component = factory->CreateComponent();

		object->AddComponent(component, factory->type);
	}
	else {
		return false;
	}

	return true;
}