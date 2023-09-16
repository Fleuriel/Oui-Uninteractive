/**************************************************************************
 * @file		  IComponent.h
 * @author
 * @par DP email:
 * @par Course:	  CSD 2401
 * @par			  Software Engineering Project 3
 * @date		  09-08-2023
 * @brief
 *************************************************************************/
#pragma once

#include "ComponentType.h"
#include "JsonSerializer.h"
class GameObject;
class IComponent {
private:

	// Pointer to base owning composition
	GameObject* base;
public:
	//HasSibling()
	friend class GameObject;
	// Specify the type of component
	ComponentType componentType;
	
	// Initialize component
	virtual void Initialize() = 0;

	// Get order of component
	GameObject* GetOwner();
	
	// Each component to serialize their own data
	/* Usage(to change*):
	
	rapidjson::Document objDoc;
	if (serializer.ReadJSONFile(filePath, objDoc)) {
		body.someVar = objDoc["body"]["someVar"].GetString();
	}
	
	*/
	virtual void Serialize(const std::string& filePath, JsonSerializer& serializer) {};


	virtual ~IComponent() {};
};
GameObject* IComponent::GetOwner() {
	return base;
}
