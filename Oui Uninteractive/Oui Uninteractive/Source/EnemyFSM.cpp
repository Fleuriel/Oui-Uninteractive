/**************************************************************************
 * @file EnemyFSM.cpp
 * @author HWANG Jing Rui, Austin
 * @par DP email: jingruiaustin.hwang@digipen.edu
 * @par Course:	CSD 2401
 * @par Software Engineering Project 3
 * @date 08-11-2023
 * @brief This file contains the definition of the EnemyFSM component.
 *************************************************************************/
#include "EnemyFSM.h"
#include "EnemyAISystem.h"
#include "EnemyStates.h"

 /**************************************************************************
 * @brief Constructor
 *************************************************************************/
EnemyFSM::EnemyFSM() : aggroRange(250.f), nextState(nullptr) {
	statesMap["EnemyRoam"] = new EnemyRoam();
	statesMap["EnemyAttack"] = new EnemyAttack();

	currentState = statesMap["EnemyRoam"];
}

/**************************************************************************
* @brief Destructor
*************************************************************************/
EnemyFSM::~EnemyFSM() {
	if (GetOwner() != nullptr) {
		enemyAISystem->enemyFSMMap.erase(GetOwner()->GetGameObjectID());
	}

	// Clear statesMap
	for (auto& state : statesMap) {
		delete state.second;
	}
	statesMap.clear();
}

/**************************************************************************
* @brief Initialize the EnemyFSM
* @return void
*************************************************************************/
void EnemyFSM::Initialize() {
	enemyAISystem->enemyFSMMap.insert(std::pair<size_t, EnemyFSM*>(GetOwner()->GetGameObjectID(), this));
}

/**************************************************************************
* @brief Serialize EnemyFSM data from JSON
* @param itr - iterator for JSON object
* @return void
*************************************************************************/
void EnemyFSM::Serialize(rapidjson::Value::ConstMemberIterator& itr) {
	const rapidjson::Value& components{ itr->value };

	aggroRange = components["AggroRange"].GetFloat();
}

/**************************************************************************
* @brief Clone EnemyFSM component
* @return EnemyFSM* - pointer to cloned EnemyFSM component
*************************************************************************/
EnemyFSM* EnemyFSM::Clone() const {
	EnemyFSM* newEnemyFSM{ new EnemyFSM() };
	newEnemyFSM->aggroRange = aggroRange;

	return newEnemyFSM;
}
