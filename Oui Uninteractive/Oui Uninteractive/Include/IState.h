/**************************************************************************
 * @file IState.h
 * @author HWANG Jing Rui, Austin
 * @par DP email: jingruiaustin.hwang@digipen.edu
 * @par Course:	CSD 2401
 * @par Software Engineering Project 3
 * @date 26-10-2023
 * @brief This file contains the interface for States.
 *************************************************************************/
#ifndef ISTATE_H
#define ISTATE_H

#include <map>
#include <string>
#include "ObjectFactory.h"

class IState
{
public:
	//virtual void Initialize() = 0;
	IState() {}
	virtual void Update(size_t gameObjectID) = 0;
	virtual void ExitState() = 0;
	virtual ~IState() {}
};

#endif
