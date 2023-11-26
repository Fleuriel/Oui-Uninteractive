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

HealthSystem* healthSys = nullptr;

/**************************************************************************
* @brief Constructor
*************************************************************************/
HealthSystem::HealthSystem() {
	if (healthSys != nullptr) {
		return;
	}
	else {
		healthSys = this;
	}
}

/**************************************************************************
* @brief Initialize the health system
* @return void
*************************************************************************/
void HealthSystem::Initialize() {
	ComponentFactory<HealthComponent>* cfPtr{ new ComponentFactory<HealthComponent>(ComponentType::HEALTH) };
	objectFactory->AddComponentFactory(ComponentType::HEALTH, cfPtr);

	// Add handler for damage taken message
	AddMessageHandler("MSG_DAMAGE_TAKEN", (MessageHandler)DamageTaken);
}

/**************************************************************************
* @brief Update the health system
* @return void
*************************************************************************/
void HealthSystem::Update(float dt) {
	if (!sysManager->isPaused) {
		(void)dt;

		for (auto& it : healthComponentMap) {
			if (it.second->currentHealth <= 0) {
				objectFactory->DestroyObject(it.second->GetOwner());
			}
		}
	}
}

/**************************************************************************
* @brief Health Message (Damage Taken)
* @param HealthMessage* - ptr to message object
* @return void
*************************************************************************/
void HealthSystem::DamageTaken(DamageTakenMessage* msg) {
	HealthComponent* healthFirst{ GET_COMPONENT(msg->GetFirst(), HealthComponent, ComponentType::HEALTH) };
	HealthComponent* healthSecond{ GET_COMPONENT(msg->GetSecond(), HealthComponent, ComponentType::HEALTH) };

	if (msg->GetFirst()->GetType() == "Enemy") {
		--healthFirst->currentHealth;
	}
	else if (msg->GetSecond()->GetType() == "Enemy") {
		--healthSecond->currentHealth;
	}
}
