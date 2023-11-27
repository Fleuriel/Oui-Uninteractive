/**************************************************************************
 * @file IComponent.h
 * @author HWANG Jing Rui, Austin - 100%
 * @par DP email: jingruiaustin.hwang@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 08-09-2023
 * @brief This file contains the declaration of the IComponent class, which
 *		  the interface for all components
 *************************************************************************/
#ifndef ICOMPONENT_H
#define ICOMPONENT_H

#include "ComponentType.h"
#include "JsonSerializer.h"

//Forward Declaration
class GameObject;

class IComponent {
private:
	// Pointer to base owning composition
	GameObject* base;

public:
	// GameObject to be able to access base pointer
	friend class GameObject;

	// Specify the type of component
	ComponentType componentType;
	
	/**************************************************************************
	* @brief Initialize component (to be overridden)
	* @return void
	*************************************************************************/
	virtual void Initialize() {};

	/**************************************************************************
	* @brief Return pointer to base GameObject
	* @return GameObject*
	*************************************************************************/
	GameObject* GetOwner() {
		return base;
	}

	/**************************************************************************
	* @brief Serialize function to be overloaded by each component.
	* Usage inside respective Component.cpp file:
	* 
	* const rapidjson::Value& components{itr->value};
	* variableName = components["VariableName"].GetFloat();	// Float variable
	* 
	* @param itr - iterator pointing to the current component
	* @return void
	*************************************************************************/
	virtual void Serialize(rapidjson::Value::ConstMemberIterator& itr) = 0;

	/**************************************************************************
	* @brief Clone function to be overloaded by each individual component
	* Usage inside respective Component.cpp file:
	* @return IComponent*
	*************************************************************************/
	virtual IComponent* Clone() const = 0;

	/**************************************************************************
	* @brief Destructor
	*************************************************************************/
	virtual ~IComponent() {};
};

#endif
