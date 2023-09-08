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

class IComponent {
private:
	// Pointer to base owning composition

public:
	//GetOwner() {return base};
	//HasSibling()
	//Serialize()

	virtual void Initialize() = 0;
	virtual ~IComponent() {};
};
