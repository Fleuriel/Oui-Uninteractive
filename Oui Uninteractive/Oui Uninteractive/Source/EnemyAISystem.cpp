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
	(void)dt;

	for (auto& it : enemyFSMMap) {
		// Update game object's current state
		if (it.second->currentState != nullptr)
			it.second->currentState->Update(it.first);

		// If within range of player, enter attack state
		Vec2 playerPos = Vec2(0, 0);
		Vec2 enemyPos = Vec2(0, 0);
		GameObject* player = objectFactory->GetGameObjectByName("JSONPlayer");
		GameObject* enemy = objectFactory->GetGameObjectByName(it.second->GetOwner()->GetName());
		std::string enemyType{};

		if (player != nullptr) {
			Transform* playerTx = GET_COMPONENT(player, Transform, ComponentType::TRANSFORM);
			if (playerTx != nullptr) {
				playerPos = playerTx->position;
			}
		}
		if (enemy != nullptr) {
			enemyType = enemy->GetType();
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
				it.second->nextState = it.second->statesMap["EnemyRoam"];
			}
		}

		if (it.second->nextState != it.second->currentState) {
			it.second->currentState->ExitState();
			it.second->currentState = it.second->nextState;
		}
		else {
			it.second->currentState = it.second->nextState;
		}
	}
}

/**************************************************************************
* @brief Create the grid
* @return bool - true if grid is created, false otherwise
*************************************************************************/
/*bool EnemyAISystem::CreateGrid() {
	// Check if a wall object already exists
	std::map<size_t, GameObject*> objFacMap{ objectFactory->GetGameObjectIDMap() };
	std::map<size_t, GameObject*>::iterator it{ objFacMap.begin() };

	bool wallFound{ false };
	while (it != objFacMap.end()) {
		if (it->second->GetName().find("Wall") != std::string::npos) {
			wallFound = true;
			break;
		}
		++it;
	}

	// Do not create grid if wall object already exists
	if (wallFound)
		return false;

	// Temp vars
	float windowWidth = 1920.f;
	float windowHeight = 1017.f;
	float scaleTemp = windowHeight / static_cast<float>(rows);

	// Wall ID
	int wallID{};

	// Instantiate walls
	for (int i{}; i < rows; ++i) {
		for (int j{}; j < cols; ++j) {
			if (gameMap[i][j] == 1) {
				// Create walls
				std::string wallName = "Wall" + std::to_string(wallID);
				GameObject* wall = objectFactory->BuildObjectRunTime(wallName, "Wall");
				objectFactory->AddComponent(ComponentType::TRANSFORM, wall);
				objectFactory->AddComponent(ComponentType::COLLIDER, wall);
				objectFactory->AddComponent(ComponentType::PHYSICS_BODY, wall);

				++wallID;
				wall->Initialize();

				// Set position and collider size of wall
				GET_COMPONENT(wall, PhysicsBody, ComponentType::PHYSICS_BODY)->isStatic = true;
				GET_COMPONENT(wall, Collider, ComponentType::COLLIDER)->boundingbox->txPtr->scale = scaleTemp;
				GET_COMPONENT(wall, Transform, ComponentType::TRANSFORM)->scale = scaleTemp;
				GET_COMPONENT(wall, Transform, ComponentType::TRANSFORM)->position.x = (j * scaleTemp) + (scaleTemp - windowWidth) / 2;
				GET_COMPONENT(wall, Transform, ComponentType::TRANSFORM)->position.y = (i * scaleTemp) + (scaleTemp - windowHeight) / 2;
			}
		}
	}

	return true;
}*/
