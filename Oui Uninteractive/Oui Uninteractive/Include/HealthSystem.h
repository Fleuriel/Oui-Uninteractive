/**************************************************************************
 * @file EnemyAISystem.h
 * @author HWANG Jing Rui, Austin
 * @par DP email: jingruiaustin.hwang@digipen.edu
 * @par Course:	CSD 2401
 * @par Software Engineering Project 3
 * @date 08-11-2023
 * @brief This file contains the declaration of the EnemyAISystem class.
 *		  This system handles the state machine for the enemies.
 *************************************************************************/
#ifndef HEALTHSYSTEM_H
#define HEALTHSYSTEM_H

#include "ISystem.h"
#include "HealthComponent.h"
#include "ObjectFactory.h"

class HealthSystem : public ISystem {
private:

public:
	/**************************************************************************
	* @brief Constructor
	*************************************************************************/
	HealthSystem();

	/**************************************************************************
	* @brief Initialize the health system
	* @return void
	*************************************************************************/
	void Initialize() override;

	/**************************************************************************
	* @brief Update the health system
	* @return void
	*************************************************************************/
	void Update(float dt) override;

	// Map of HealthComponent
	std::map<size_t, HealthComponent*> healthComponentMap;
};

//Global pointer
extern HealthSystem* healthSystem;

#endif