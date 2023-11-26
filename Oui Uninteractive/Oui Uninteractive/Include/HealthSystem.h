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

class DamageTakenMessage : public IMessage {
private:
	GameObject* first;
	GameObject* second;

public:
	/**************************************************************************
	* @brief Constructor
	*************************************************************************/
	DamageTakenMessage(GameObject* firstObj, GameObject* secondObj) : IMessage("MSG_DAMAGE_TAKEN"), first(firstObj), second(secondObj) {}

	/**************************************************************************
	* @brief Destructor
	*************************************************************************/
	~DamageTakenMessage() {}

	/**************************************************************************
	* @brief Get the first object
	* @return GameObject* - ptr to first object
	*************************************************************************/
	GameObject* GetFirst() { return first; }

	/**************************************************************************
	* @brief Get the second object
	* @return GameObject* - ptr to second object
	*************************************************************************/
	GameObject* GetSecond() { return second; }
};

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

	/**************************************************************************
	* @brief Health Message (Damage Taken)
	* @param HealthMessage* - ptr to message object
	* @return void
	*************************************************************************/
	static void DamageTaken(DamageTakenMessage* msg);

	// Map of HealthComponent
	std::map<size_t, HealthComponent*> healthComponentMap;
};

//Global pointer
extern HealthSystem* healthSys;

#endif