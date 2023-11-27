/**************************************************************************
 * @file EnemyFSM.h
 * @author HWANG Jing Rui, Austin - 100%
 * @par DP email: jingruiaustin.hwang@digipen.edu
 * @par Course:	CSD 2401
 * @par Software Engineering Project 3
 * @date 27-10-2023
 * @brief This file contains the declaration of the EnemyFSM component.
 *************************************************************************/
#ifndef ENEMYFSM_H
#define ENEMYFSM_H

#include <map>
#include <string>
#include "IComponent.h"
#include "IState.h"

class EnemyFSM : public IComponent {
public:
	std::map<std::string, IState*> statesMap;
	IState* currentState;
	IState* nextState;
	float aggroRange;

public:
	/**************************************************************************
	* @brief Constructor
	*************************************************************************/
	EnemyFSM();

	/**************************************************************************
	* @brief Destructor
	*************************************************************************/
	~EnemyFSM();

	/**************************************************************************
	* @brief Initialize the EnemyFSM
	* @return void
	*************************************************************************/
	void Initialize() override;

	/**************************************************************************
	* @brief Serialize EnemyFSM data from JSON
	* @param itr - iterator for JSON object
	* @return void
	*************************************************************************/
	void Serialize(rapidjson::Value::ConstMemberIterator& itr) override;

	/**************************************************************************
	* @brief Clone EnemyFSM component
	* @return EnemyFSM* - pointer to cloned EnemyFSM component
	*************************************************************************/
	EnemyFSM* Clone() const override;
};

#endif
