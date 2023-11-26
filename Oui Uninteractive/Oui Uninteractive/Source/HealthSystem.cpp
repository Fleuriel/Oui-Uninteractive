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
#include "HealthSystem.h"
#include "ComponentFactory.h"

HealthSystem* healthSystem = nullptr;

/**************************************************************************
* @brief Constructor
*************************************************************************/
HealthSystem::HealthSystem() {
	if (healthSystem != nullptr) {
		return;
	}
	else {
		healthSystem = this;
	}
}

/**************************************************************************
* @brief Initialize the health system
* @return void
*************************************************************************/
void HealthSystem::Initialize() {
	ComponentFactory<HealthComponent>* cfPtr{ new ComponentFactory<HealthComponent>(ComponentType::HEALTH) };
	objectFactory->AddComponentFactory(ComponentType::HEALTH, cfPtr);
}

/**************************************************************************
* @brief Update the health system
* @return void
*************************************************************************/
void HealthSystem::Update(float dt) {
	if (sysManager->isPaused == false) {
		(void)dt;

		for (auto& it : healthComponentMap) {
			if (it.second->currentHealth <= 0) {
				objectFactory->DestroyObject(it.second->GetOwner());
			}
		}
	}
}
