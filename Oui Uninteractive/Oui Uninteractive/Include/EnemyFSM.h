/**************************************************************************
 * @file EnemyFSM.h
 * @author HWANG Jing Rui, Austin
 * @par DP email: jingruiaustin.hwang@digipen.edu
 * @par Course:	CSD 2401
 * @par Software Engineering Project 3
 * @date 27-10-2023
 * @brief This file contains the EnemyFSM script.
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
	IState* currentState{ nullptr };
	IState* nextState{ nullptr };
	float aggroRange{ 250.f };

public:
	EnemyFSM(std::string newName) : IScript(newName) {

	};
	/**************************************************************************
	* @brief Initialize the EnemyFSM script
	* @return void
	*************************************************************************/
	void Initialize() {
 		logicSystem->AddLogicScript(this);

		statesMap["EnemyRoam"] = new EnemyRoam();
		statesMap["EnemyAttack"] = new EnemyAttack();

		currentState = statesMap["EnemyRoam"];
	};

	/**************************************************************************
	* @brief Update the EnemyFSM script
	* @return void
	*************************************************************************/
	void Update(size_t gameObjectID) {
		currentState->Update(gameObjectID);

		// If within range of player, enter attack state
		Vec2 playerPos = Vec2(0, 0);
		Vec2 enemyPos = Vec2(0, 0);
		GameObject* player = objectFactory->GetGameObjectByName("JSONPlayer");
		GameObject* enemy = objectFactory->GetGameObjectByName("JSONEnemy1");

		if (player != nullptr) {

			Transform* playerTx = GET_COMPONENT(player, Transform, ComponentType::TRANSFORM);
			if (playerTx != nullptr) {
				playerPos = playerTx->position;
			}
		}
		if (enemy != nullptr) {
			Transform* enemyTx = GET_COMPONENT(enemy, Transform, ComponentType::TRANSFORM);

			if (enemyTx != nullptr) {
				enemyPos = enemyTx->position;
			}
		}

		if (Vector2DDistance(playerPos, enemyPos) < aggroRange) {
			nextState = statesMap["EnemyAttack"];
		}
		else {
			nextState = statesMap["EnemyRoam"];
		}

		if (nextState != currentState) {
			currentState->ExitState();
			currentState = nextState;
		}
	}

	/**************************************************************************
	* @brief End the EnemyFSM script
	* @return void
	*************************************************************************/
	void End() {}

	/**************************************************************************
	* @brief Destructor
	*************************************************************************/
	~EnemyFSM() {
		// Clear statesMap
		for (auto& state : statesMap) {
			delete state.second;
		}
		statesMap.clear();
	}
};

#endif
