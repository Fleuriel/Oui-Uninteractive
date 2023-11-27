/**************************************************************************
 * @file InventoryComponent.h
 * @author QUEK Cheng Kwang, Emery - 100%
 * @par DP email: c.quek@digipen.edu
 * @par Course:	CSD 2401
 * @par Software Engineering Project 3
 * @date 25-11-2023
 * @brief This file contains the declaration of the inventory component.
 *************************************************************************/
#ifndef INVENTORYCOMPONENT_H
#define INVENTORYCOMPONENT_H

#include <map>
#include <string>
#include "IComponent.h"

class InventoryComponent : public IComponent {
public:
	/*std::map<size_t, GameObject*> Inventory;*/
	std::vector<std::string> Inventory;
	int currentWeaponID;

public:
	/**************************************************************************
	* @brief Constructor
	*************************************************************************/
	InventoryComponent();

	/**************************************************************************
	* @brief Destructor
	*************************************************************************/
	~InventoryComponent();

	/**************************************************************************
	* @brief Initialize the Inventory component
	* @return void
	*************************************************************************/
	void Initialize() override;

	/**************************************************************************
	* @brief Serialize Inventory component data from JSON
	* @param itr - iterator for JSON object
	* @return void
	*************************************************************************/
	void Serialize(rapidjson::Value::ConstMemberIterator& itr) override;

	/**************************************************************************
	* @brief Clone Inventory component
	* @return InventoryComponent* - pointer to cloned Inventory component
	*************************************************************************/
	InventoryComponent* Clone() const override;
};

#endif
