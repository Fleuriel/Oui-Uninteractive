/**************************************************************************
 * @file ComponentFactory.h
 * @author Hwang Jing Rui, Austin
 * @co-author CHEAH Tristan Tze Hong
 * @par DP email: jingruiaustin.hwang@digipen.edu
 * @par DP email: t.cheah@digipen.edu
 * @par Course:	CSD 2401
 * @par	Software Engineering Project 3
 * @date 13-09-2023
 * @brief This file contains the definition of the ComponentFactory class
 *************************************************************************/
#ifndef COMPONENT_FACTORY_H
#define COMPONENT_FACTORY_H

#include "ComponentType.h"
//Forward Declaration
class IComponent;


class ComponentFactoryBase 
//base interface for component factories
{
public:
	ComponentType type;
	/**************************************************************************
	* @brief non-default constructor for ComponentFactoryBase
	*************************************************************************/
	ComponentFactoryBase(ComponentType componentType) : type{ componentType } {};
	/**************************************************************************
	* @brief Destructor for ComponentFactoryBase
	*************************************************************************/
	virtual ~ComponentFactoryBase() {}
	/**************************************************************************
	* @brief CreateComponent function to be overriden by each type
	*		 of ComponentFactory
	* @return IComponent*
	*************************************************************************/
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

#endif
