/**************************************************************************
 * @file EnemyFSM.h
 * @author HWANG Jing Rui, Austin
 * @par DP email: jingruiaustin.hwang@digipen.edu
 * @par Course:	CSD 2401
 * @par Software Engineering Project 3
 * @date 27-10-2023
 * @brief
 *************************************************************************/
#ifndef ENEMYFSM_H
#define ENEMYFSM_H

#include <map>
#include <string>
#include "IScript.h"
#include "IState.h"
#include "EnemyStates.h"
#include "Logic.h"
#include "ObjectFactory.h"

class EnemyFSM : public IScript {
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

	void Update(size_t gameObjectID) {
		currentState->Update(gameObjectID);

		// If within range of player, enter attack state
		Vec2 playerPos = Vec2(0, 0);
		Transform* playerTx = GET_COMPONENT(objectFactory->GetGameObjectByName("JSONPlayer"), Transform, ComponentType::TRANSFORM);
		if (playerTx != nullptr) {
			playerPos = playerTx->position;
		}
		
		Transform* enemyTx = GET_COMPONENT(objectFactory->GetGameObjectByName("JSONPlayer"), Transform, ComponentType::TRANSFORM);
		Vec2 enemyPos = Vec2(0, 0);
		if (enemyTx != nullptr) {
			enemyPos = enemyTx->position;
		}

		if (Vector2DDistance(playerPos, enemyPos) < 300.0f) {
			currentState = statesMap["EnemyAttack"];
		}
		else {
			currentState = statesMap["EnemyRoam"];
		}
	}

	void End() {}

	~EnemyFSM() {
		// Clear statesMap
		for (auto& state : statesMap) {
			delete state.second;
		}
		statesMap.clear();
	}
};

#endif
