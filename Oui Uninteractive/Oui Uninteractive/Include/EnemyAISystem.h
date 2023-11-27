/**************************************************************************
 * @file EnemyAISystem.h
 * @author HWANG Jing Rui, Austin - 100%
 * @par DP email: jingruiaustin.hwang@digipen.edu
 * @par Course:	CSD 2401
 * @par Software Engineering Project 3
 * @date 08-11-2023
 * @brief This file contains the declaration of the EnemyAISystem class.
 *		  This system handles the state machine for the enemies.
 *************************************************************************/
#ifndef ENEMYAI_SYSTEM_H
#define ENEMYAI_SYSTEM_H

#include "ISystem.h"
#include "EnemyFSM.h"
#include "ObjectFactory.h"

class EnemyAISystem : public ISystem {
private:
	
public:
	/**************************************************************************
	* @brief Constructor
	*************************************************************************/
	EnemyAISystem();

	/**************************************************************************
	* @brief Initialize the EnemyAI system
	* @return void
	*************************************************************************/
	void Initialize() override;

	/**************************************************************************
	* @brief Update the EnemyAI system
	* @return void
	*************************************************************************/
	void Update(float dt) override;

	// Map of EnemyFSM
	std::map<size_t, EnemyFSM*> enemyFSMMap;
};

//Global pointer
extern EnemyAISystem* enemyAISys;

#endif