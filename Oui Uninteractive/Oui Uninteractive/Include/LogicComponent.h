/**************************************************************************
 * @file LogicComponent.h
 * @author CHEAH Tristan Tze Hong
 * @par DP email: t.cheah@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 27-09-2023
 * @brief This file contains the declaration of the LogicComponent Class,
 *		  which is a IComponent to be contained in GameObject. It holds
 *		  all data pertaining to creating different behaviours for different
 *		  Game Objects
 *************************************************************************/

#pragma once
#include "IComponent.h"
#include <set>
class LogicComponent : public IComponent {
public:
	//set containing index of script to apply to object
	std::set<unsigned int> scriptIndexSet;
public:
	/**************************************************************************
	* @brief Initialize function for Logic Component
	* @return void
	*************************************************************************/
	void Initialize();
	/**************************************************************************
	* @brief Serialize function for logic component
	* @param itr - iterator through json object
	* @return void
	*************************************************************************/
	void Serialize(rapidjson::Value::ConstMemberIterator& itr) ;
	/**************************************************************************
	* @brief Function to Clone a Logic Component Component
	* @return LogicComponent* - the cloned Logic Component
	*************************************************************************/
	LogicComponent* Clone() const;
	/**************************************************************************
	* @brief Destructor for Logic component
	*************************************************************************/
	~LogicComponent() ;
	
};	