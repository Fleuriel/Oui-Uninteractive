/**************************************************************************
 * @file HealthComponent.h
 * @author HWANG Jing Rui, Austin
 * @par DP email: jingruiaustin.hwang@digipen.edu
 * @par Course:	CSD 2401
 * @par Software Engineering Project 3
 * @date 25-11-2023
 * @brief This file contains the declaration of the health component.
 *************************************************************************/
#ifndef HEALTHCOMPONENT_H
#define HEALTHCOMPONENT_H

#include <map>
#include <string>
#include "IComponent.h"

class HealthComponent : public IComponent {
public:
	int maxHealth;
	int currentHealth;

public:
	/**************************************************************************
	* @brief Constructor
	*************************************************************************/
	HealthComponent();

	/**************************************************************************
	* @brief Destructor
	*************************************************************************/
	~HealthComponent();

	/**************************************************************************
	* @brief Initialize the health component
	* @return void
	*************************************************************************/
	void Initialize() override;

	/**************************************************************************
	* @brief Serialize health component data from JSON
	* @param itr - iterator for JSON object
	* @return void
	*************************************************************************/
	void Serialize(rapidjson::Value::ConstMemberIterator& itr) override;

	/**************************************************************************
	* @brief Clone health component
	* @return HealthComponent* - pointer to cloned health component
	*************************************************************************/
	HealthComponent* Clone() const override;
};

#endif
