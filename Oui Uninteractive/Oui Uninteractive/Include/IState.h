/**************************************************************************
 * @file IState.h
 * @author HWANG Jing Rui, Austin
 * @par DP email: jingruiaustin.hwang@digipen.edu
 * @par Course:	CSD 2401
 * @par Software Engineering Project 3
 * @date 26-10-2023
 * @brief
 *************************************************************************/
#ifndef ISTATE_H
#define ISTATE_H

#include <map>
#include <string>
#include "ObjectFactory.h"

class IState
{
public:
	virtual void Update(size_t gameObjectID) = 0;
};

/*class FSM {
private:
	std::map<std::string, IState*> statesMap;
	IState* currentState;

public:
	FSM() {}

	void AddState(std::string name, IState* state) {
		statesMap[name] = state;
	}

	void TransitionTo(std::string name) {
		currentState = statesMap[name];
	}

	void Update() {
		currentState->Update();
	}
};*/

#endif