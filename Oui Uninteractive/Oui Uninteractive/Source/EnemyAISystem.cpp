/**************************************************************************
 * @file EnemyAISystem.h
 * @author HWANG Jing Rui, Austin
 * @par DP email: jingruiaustin.hwang@digipen.edu
 * @par Course:	CSD 2401
 * @par Software Engineering Project 3
 * @date 08-11-2023
 * @brief This file contains the definition of the EnemyAISystem class.
 *		  This system handles the state machine for the enemies.
 *************************************************************************/
#include "EnemyAISystem.h"
#include "ComponentFactory.h"
#include "Transform.h"
#include "Vector2D.h"

EnemyAISystem* enemyAISystem = nullptr;

/**************************************************************************
* @brief Constructor
*************************************************************************/
EnemyAISystem::EnemyAISystem() {
	if (enemyAISystem != nullptr) {
		return;
	}
	else {
		enemyAISystem = this;
	}
}

/**************************************************************************
* @brief Initialize the EnemyAI system
* @return void
*************************************************************************/
void EnemyAISystem::Initialize() {
	ComponentFactory<EnemyFSM>* cfPtr{ new ComponentFactory<EnemyFSM>(ComponentType::ENEMY_FSM) };
	objectFactory->AddComponentFactory(ComponentType::ENEMY_FSM, cfPtr);
}

/**************************************************************************
* @brief Update the EnemyAI system
* @return void
*************************************************************************/
void EnemyAISystem::Update(float dt) {
	if (sysManager->isPaused == false) {
		(void)dt;

		for (auto& it : enemyFSMMap) {
			// Update game object's current state
			if (it.second->currentState != nullptr)
				it.second->currentState->Update(it.first);

			// If within range of player, enter attack state
			Vec2 playerPos = Vec2(0, 0);
			Vec2 enemyPos = Vec2(0, 0);
			GameObject* player = objectFactory->GetGameObjectsByType("Player")[0];
			GameObject* enemy = objectFactory->GetGameObjectByName(it.second->GetOwner()->GetName());
			std::string enemyType{};

			if (player != nullptr) {
				Transform* playerTx = GET_COMPONENT(player, Transform, ComponentType::TRANSFORM);
				if (playerTx != nullptr) {
					playerPos = playerTx->position;
				}
			}
			if (enemy != nullptr) {
				enemyType = enemy->GetTexture(); // GetTexture() gets the enemy's type
				Transform* enemyTx = GET_COMPONENT(enemy, Transform, ComponentType::TRANSFORM);
				if (enemyTx != nullptr) {
					enemyPos = enemyTx->position;
				}
			}

			// "Common Guard" enemy changes state if player is within aggro range
			if (enemyType == "CommonGuard") {
				if (Vector2DDistance(playerPos, enemyPos) < it.second->aggroRange) {
					it.second->nextState = it.second->statesMap["EnemyAttack"];
				}
				else {
					it.second->nextState = it.second->statesMap["EnemyRoam"];
				}
			}
			// "Target" enemy flees if player is within aggro range
			else if (enemyType == "Target") {
				if (Vector2DDistance(playerPos, enemyPos) < it.second->aggroRange) {
					it.second->nextState = it.second->statesMap["EnemyFlee"];
				}
				else {
					it.second->nextState = it.second->currentState;
				}
			}

			// If next state is different from current state, exit current state
			if (it.second->nextState != it.second->currentState) {
				it.second->currentState->ExitState();
			}

			// Transition to the next state
			it.second->currentState = it.second->nextState;
		}
	}
}
