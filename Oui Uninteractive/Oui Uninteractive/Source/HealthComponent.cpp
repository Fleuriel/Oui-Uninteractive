/**************************************************************************
 * @file HealthComponent.h
 * @author HWANG Jing Rui, Austin
 * @par DP email: jingruiaustin.hwang@digipen.edu
 * @par Course:	CSD 2401
 * @par Software Engineering Project 3
 * @date 25-11-2023
 * @brief This file contains the definition of the health component.
 *************************************************************************/
#include "HealthComponent.h"
#include "HealthSystem.h"

 /**************************************************************************
 * @brief Constructor
 *************************************************************************/
HealthComponent::HealthComponent() : maxHealth{}, currentHealth(maxHealth) {
}

/**************************************************************************
* @brief Destructor
*************************************************************************/
HealthComponent::~HealthComponent() {
	if (GetOwner() != nullptr) {
		healthSys->healthComponentMap.erase(GetOwner()->GetGameObjectID());
	}
}

/**************************************************************************
* @brief Initialize the health component
* @return void
*************************************************************************/
void HealthComponent::Initialize() {
	healthSys->healthComponentMap.insert(std::pair<size_t, HealthComponent*>(GetOwner()->GetGameObjectID(), this));
}

/**************************************************************************
* @brief Serialize HealthComponent data from JSON
* @param itr - iterator for JSON object
* @return void
*************************************************************************/
void HealthComponent::Serialize(rapidjson::Value::ConstMemberIterator& itr) {
	const rapidjson::Value& components{ itr->value };
	maxHealth = components["MaxHealth"].GetInt();
	currentHealth = maxHealth;
}

/**************************************************************************
* @brief Clone health component
* @return HealthComponent* - pointer to cloned health component
*************************************************************************/
HealthComponent* HealthComponent::Clone() const {
	HealthComponent* newHealthComponent{ new HealthComponent() };
	newHealthComponent->maxHealth = maxHealth;
	newHealthComponent->currentHealth = currentHealth;

	return newHealthComponent;
}
