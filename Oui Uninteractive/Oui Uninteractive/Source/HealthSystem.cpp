/**************************************************************************
 * @file HealthSystem.cpp
 * @author HWANG Jing Rui, Austin - 100%
 * @par DP email: jingruiaustin.hwang@digipen.edu
 * @par Course:	CSD 2401
 * @par Software Engineering Project 3
 * @date 25-11-2023
 * @brief This file contains the definition of the HealthSystem class.
 *************************************************************************/
#include "HealthSystem.h"
#include "ComponentFactory.h"
#include "Transform.h"

HealthSystem* healthSys = nullptr;
extern std::pair<int, int> windowSize;

/**************************************************************************
* @brief Constructor
*************************************************************************/
HealthSystem::HealthSystem() : nextMaxHP{}, nextCurrentHP{} {
	if (healthSys != nullptr) {
		return;
	}
	else {
		healthSys = this;
	}
}

/**************************************************************************
* @brief Initialize the health system
* @return void
*************************************************************************/
void HealthSystem::Initialize() {
	ComponentFactory<HealthComponent>* cfPtr{ new ComponentFactory<HealthComponent>(ComponentType::HEALTH) };
	objectFactory->AddComponentFactory(ComponentType::HEALTH, cfPtr);

	// Add handler for damage taken message
	AddMessageHandler("MSG_DAMAGE_TAKEN", (MessageHandler)DamageTaken);
}

/**************************************************************************
* @brief Update the health system
* @return void
*************************************************************************/
void HealthSystem::Update(float dt) {
	if (!sysManager->isPaused) {
		(void)dt;

		for (auto& it : healthComponentMap) {
			if (it.second->currentHealth <= 0) {
				objectFactory->DestroyObject(it.second->GetOwner());
			}
			if (it.second->currentHealth > it.second->maxHealth) {
				it.second->currentHealth = it.second->maxHealth;
			}
			
			if (it.second->GetOwner()->GetType() == "Player") {
				if (nextMaxHP != it.second->maxHealth || nextCurrentHP != it.second->currentHealth) {
					for (size_t i{}; i < playerHealthbar.size(); ++i) {
						objectFactory->DestroyObject(playerHealthbar[i]);
					}
					playerHealthbar.clear();

					DrawHealthbar();
				}
			}
		}
	}
}

/**************************************************************************
* @brief Health Message (Damage Taken)
* @param HealthMessage* - ptr to message object
* @return void
*************************************************************************/
void HealthSystem::DamageTaken(DamageTakenMessage* msg) {
	HealthComponent* healthFirst{ GET_COMPONENT(msg->GetFirst(), HealthComponent, ComponentType::HEALTH) };
	HealthComponent* healthSecond{ GET_COMPONENT(msg->GetSecond(), HealthComponent, ComponentType::HEALTH) };

	// Player bullet and enemy collision
	if (msg->GetFirst()->GetType() == "Enemy" && msg->GetSecond()->GetType() == "BulletPrefab") {
		healthFirst->currentHealth -= healthSecond->maxHealth;
	}
	else if (msg->GetSecond()->GetType() == "Enemy" && msg->GetFirst()->GetType() == "BulletPrefab") {
		healthSecond->currentHealth -= healthFirst->maxHealth;
	}

	// Player bullet and enemy collision
	if (msg->GetFirst()->GetType() == "Player" && msg->GetSecond()->GetType() == "EnemyBulletPrefab") {
		//objectFactory->GetGameObjectByName("Heart" + std::to_string(healthFirst->currentHealth))->SetTexture("Heart-BG");
		healthFirst->currentHealth -= healthSecond->maxHealth;
	}
	else if (msg->GetSecond()->GetType() == "Player" && msg->GetFirst()->GetType() == "EnemyBulletPrefab") {
		healthSecond->currentHealth -= healthFirst->maxHealth;
	}
}

/**************************************************************************
* @brief Clear healthbar vector
* @return void
*************************************************************************/
void HealthSystem::ClearHealthbar() {
	playerHealthbar.clear();
}

/**************************************************************************
* @brief Draw player healthbar
* @return void
*************************************************************************/
void HealthSystem::DrawHealthbar() {
	for (auto& it : healthComponentMap) {
		if (it.second->GetOwner()->GetType() == "Player") {
			if (it.second->maxHealth <= 10) {
				// Create player healthbar
				for (int i{}; i < it.second->maxHealth; ++i) {
					// Create bullet object from prefab
					std::string heartName{ "Heart" + std::to_string(i + 1) };
					GameObject* heart = objectFactory->BuildObjectFromPrefab(heartName, "HeartPrefab");
					GET_COMPONENT(heart, Transform, ComponentType::TRANSFORM)->position.x = (static_cast<float>(-windowSize.first) / 3.f) + i * GET_COMPONENT(heart, Transform, ComponentType::TRANSFORM)->scale.x;
					GET_COMPONENT(heart, Transform, ComponentType::TRANSFORM)->position.y = (static_cast<float>(windowSize.second) / 4.f);

					playerHealthbar.push_back(heart);
				}

				// Update player healthbar textures
				for (int i{}; i < it.second->currentHealth - 1; ++i) {
					playerHealthbar[i]->SetTexture("Heart");
				}
				for (int i{ it.second->currentHealth }; i < it.second->maxHealth; ++i) {
					playerHealthbar[i]->SetTexture("Heart-BG");
				}

				nextMaxHP = it.second->maxHealth;
				nextCurrentHP = it.second->currentHealth;
			}
			else {
				// godmode
				// Create player healthbar
				std::string heartName{ "HeartGodmode" };
				GameObject* heart = objectFactory->BuildObjectFromPrefab(heartName, "HeartPrefab");
				GET_COMPONENT(heart, Transform, ComponentType::TRANSFORM)->position.x = (static_cast<float>(-windowSize.first) / 3.f);
				GET_COMPONENT(heart, Transform, ComponentType::TRANSFORM)->position.y = (static_cast<float>(windowSize.second) / 4.f);

				playerHealthbar.push_back(heart);

				// Update player healthbar textures
				playerHealthbar[0]->SetTexture("InfinityHeart");

				nextMaxHP = it.second->maxHealth;
				nextCurrentHP = it.second->currentHealth;
			}

			return;
		}
	}
}
