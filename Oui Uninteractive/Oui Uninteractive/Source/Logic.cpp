/**************************************************************************
 * @file Logic.cpp
 * @author CHEAH Tristan Tze Hong
 * @par DP email: t.cheah@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 02-11-2023
 * @brief This file contains the definition of the Logic System.
 *		  This system is responsible for running the different scripts
 *		  attached to a logic component
 *************************************************************************/
#include "Logic.h"
#include "ComponentFactory.h"
#include <iostream>
#include "TestScript.h"
#include "EnemyFSM.h"
#include "PlayerShooting.h"
#include "BulletScript.h"
#include "WeaponPickupScript.h"
#include "PauseMenuLogic.h"

LogicSystem* logicSystem = nullptr;
/**************************************************************************
* @brief Constructor for Logic System
*************************************************************************/
LogicSystem::LogicSystem() {
	if (logicSystem != nullptr) {
		//instantiate physics system
		return;
	}
	else {
		logicSystem = this;
	}
}
/**************************************************************************
* @brief Initialize function for Logic
* @return void
*************************************************************************/
void LogicSystem::Initialize() {
	ComponentFactory<LogicComponent>* testPtr = new ComponentFactory<LogicComponent>(ComponentType::LOGICCOMPONENT);
	objectFactory->AddComponentFactory(ComponentType::LOGICCOMPONENT, testPtr);
	//SCRIPTS

	TestScript* testScript = new TestScript(std::string("testScript"));
	testScript->Initialize();

	TestScript2* testScript2 = new TestScript2(std::string("testScript2"));
	testScript2->Initialize();

	WeaponPickupScript* weaponPickupScript = new WeaponPickupScript(std::string("WeaponPickupScript"));
	weaponPickupScript->Initialize();

	PlayerShooting* playerShootingScript = new PlayerShooting(std::string("PlayerShooting"));
	playerShootingScript->Initialize();

	BulletScript* bulletScript = new BulletScript(std::string("BulletScript"));
	bulletScript->Initialize();

	PauseMenuLogic* pauseMenuScript = new PauseMenuLogic(std::string("PauseMenuLogic"));
	pauseMenuScript->Initialize();


}
/**************************************************************************
* @brief Update function for Logic System
* @param dt - delta time
* @return void
*************************************************************************/
void LogicSystem::Update(float dt) {
	if (sysManager->isPaused == false) {
		(void)dt;
		for (auto& iter : logicComponentMap) {
			for (unsigned int index : iter.second->scriptIndexSet) {
				scriptVec[index]->Update(iter.second->GetOwner()->GetGameObjectID());
			}
		}
	}
}
/**************************************************************************
* @brief Add Script to Logic System's script container
* @param IScript - new Script Object to be Added
* @return void
*************************************************************************/
void LogicSystem::AddLogicScript(IScript* newScript) {
	scriptVec.push_back(newScript);
}
/**************************************************************************
	* @brief Destructor for Collider System
*************************************************************************/
LogicSystem::~LogicSystem() {
	for (int i = 0; i < scriptVec.size(); i++) {
		delete scriptVec[i];
	}
}