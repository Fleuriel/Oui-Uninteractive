/**************************************************************************
 * @file EnemyFSM.h
 * @author HWANG Jing Rui, Austin
 * @par DP email: jingruiaustin.hwang@digipen.edu
 * @par Course:	CSD 2401
 * @par Software Engineering Project 3
 * @date 27-10-2023
 * @brief
 *************************************************************************/
#ifndef ENEMY_FSM_H
#define ENEMY_FSM_H

#include <map>
#include <string>
#include "IScript.h"
#include "Logic.h"
#include "IState.h"
#include "EnemyStates.h"

#include "ObjectFactory.h"

class FSM : public IScript {
private:
	std::map<std::string, IState*> statesMap;
	IState* currentState;

public:
	void Initialize() {
 		logicSystem->AddLogicScript(this);

		statesMap["EnemyRoam"] = new EnemyRoam();
		statesMap["EnemyAttack"] = new EnemyAttack();

		currentState = statesMap["EnemyRoam"];
	};

	/*void AddState(std::string name, IState* state) {
		statesMap[name] = state;
	}*/

	/*void TransitionTo(std::string name) {
		currentState = statesMap[name];
	}*/

	void Update(size_t gameObjectID) {
		currentState->Update(gameObjectID);
	}

	void End() {}

	~FSM() {
		// Clear statesMap
		for (auto& state : statesMap) {
			delete state.second;
		}
		statesMap.clear();
	}
};

#endif
