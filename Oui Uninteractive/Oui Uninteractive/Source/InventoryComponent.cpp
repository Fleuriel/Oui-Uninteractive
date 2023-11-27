/**************************************************************************
 * @file InventoryComponent.h
 * @author HWANG Jing Rui, Austin
 * @par DP email: jingruiaustin.hwang@digipen.edu
 * @par Course:	CSD 2401
 * @par Software Engineering Project 3
 * @date 25-11-2023
 * @brief This file contains the definition of the health component.
 *************************************************************************/
#include "InventoryComponent.h"

 /**************************************************************************
 * @brief Constructor
 *************************************************************************/
InventoryComponent::InventoryComponent()  {
	currentWeaponID = -1;
}

/**************************************************************************
* @brief Destructor
*************************************************************************/
InventoryComponent::~InventoryComponent() {
	
}

/**************************************************************************
* @brief Initialize the health component
* @return void
*************************************************************************/
void InventoryComponent::Initialize() {
	
}

/**************************************************************************
* @brief Serialize HealthComponent data from JSON
* @param itr - iterator for JSON object
* @return void
*************************************************************************/
void InventoryComponent::Serialize(rapidjson::Value::ConstMemberIterator& itr) {
	
}

/**************************************************************************
* @brief Clone health component
* @return HealthComponent* - pointer to cloned health component
*************************************************************************/
InventoryComponent* InventoryComponent::Clone() const {
	InventoryComponent* newInventoryComponent{ new InventoryComponent() };

	return newInventoryComponent;
}
