/**************************************************************************
 * @file		  ISystem.h
 * @author
 * @par DP email:
 * @par Course:	  CSD 2401
 * @par			  Software Engineering Project 3
 * @date		  09-08-2023
 * @brief
 *************************************************************************/
#pragma once

class ISystem {
private:

public:
	// Initialize the system
	virtual void Initialize() = 0;

	// Update the system
	virtual void Update() = 0;

	// Terminate the system
	//virtual void Terminiate();
	virtual ~ISystem() {};
};
