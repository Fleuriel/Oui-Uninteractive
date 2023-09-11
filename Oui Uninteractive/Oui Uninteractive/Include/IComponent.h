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

class IComponent {
private:

	// Pointer to base owning composition

public:
	//GetOwner() {return base};
	//HasSibling()
	//Serialize()


	// Specify the type of component
	ComponentType componentType;

	virtual void Initialize() = 0;
	virtual ~IComponent() {};
};
