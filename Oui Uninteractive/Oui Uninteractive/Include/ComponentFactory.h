/**************************************************************************
 * @file		  ComponentFactory.h
 * @author
 * @par DP email:
 * @par Course:	  CSD 2401
 * @par			  Software Engineering Project 3
 * @date		  09-13-2023
 * @brief
 *************************************************************************/
#pragma once
#include "ComponentType.h"
class IComponent;

class ComponentFactoryBase 
{
public:
	ComponentType type;

	ComponentFactoryBase(ComponentType componentType) : type{ componentType } {};
	virtual ~ComponentFactoryBase() {}
	virtual IComponent* CreateComponent() = 0;
	
};

template <typename T>
class ComponentFactory : public ComponentFactoryBase {
public:
	ComponentFactory(ComponentType id) : ComponentFactoryBase(id) {

	}

	virtual IComponent* CreateComponent() {
		return new T();
	}
};
