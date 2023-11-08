/**************************************************************************
 * @file Logic.h
 * @author CHEAH Tristan Tze Hong
 * @par DP email: t.cheah@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 02-11-2023
 * @brief This file contains the declaration of the Logic System.
 *		  This system is responsible for running the different scripts
 *		  attached to a logic component
 *************************************************************************/

#pragma once
#include "ISystem.h"
#include "IScript.h"
#include "LogicComponent.h"
#include "ObjectFactory.h"
#include <vector>
enum LOGIC_ENUM {
	TEST_SCRIPT1 = 0,
	PLAYER_MOVEMENT,
	PLAYER_ATTACK
};
class LogicSystem : public ISystem {
public:
	/**************************************************************************
	* @brief Constructor for Logic System
	*************************************************************************/
	LogicSystem();
	/**************************************************************************
	* @brief Initialize function for Logic
	* @return void
	*************************************************************************/
	void Initialize();
	/**************************************************************************
	* @brief Update function for Logic System
	* @param dt - delta time
	* @return void
	*************************************************************************/
	void Update(float dt);
	/**************************************************************************
	* @brief Add Script to Logic System's script container
	* @param IScript - new Script Object to be Added
	* @return void
	*************************************************************************/
	void AddLogicScript(IScript* newScript);
	/**************************************************************************
	* @brief Destructor for Logic System
	*************************************************************************/
	~LogicSystem();

	//insert script container
	std::vector<IScript*> scriptVec;
	//insert logic component container
	std::map<size_t, LogicComponent*> logicComponentMap;
};
extern LogicSystem* logicSystem;