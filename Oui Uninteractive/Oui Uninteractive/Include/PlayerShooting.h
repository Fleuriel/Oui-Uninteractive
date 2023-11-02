/**************************************************************************
 * @file PlayerShooting.h
 * @author HWANG Jing Rui, Austin
 * @par DP email: jingruiaustin.hwang@digipen.edu
 * @par Course:	CSD 2401
 * @par Software Engineering Project 3
 * @date 29-10-2023
 * @brief This file contains the script for player shooting.
 *************************************************************************/
#ifndef PLAYER_SHOOTING_H
#define PLAYER_SHOOTING_H

#include <map>
#include <string>
#include "IScript.h"
#include "Logic.h"
#include "ObjectFactory.h"
#include "PhysicsBody.h"
#include <iostream>

class PlayerShooting : public IScript {
public:
	/**************************************************************************
	* @brief Initialize the PlayerShooting script
	* @return void
	*************************************************************************/
	void Initialize() {
		logicSystem->AddLogicScript(this);
	};

	/**************************************************************************
	* @brief Update the PlayerShooting script
	* @return void
	*************************************************************************/
	void Update(size_t gameObjectID) {
		if (inputSystem.GetMouseState(GLFW_MOUSE_BUTTON_RIGHT)) {
			// Create bullet object during runtime
			GameObject* bullet = objectFactory->BuildObjectRunTime("Bullet", "Bullet");
			objectFactory->AddComponent(ComponentType::PHYSICS_BODY, bullet);
			objectFactory->AddComponent(ComponentType::TRANSFORM, bullet);

			bullet->Initialize();

			// Set velocity
			GET_COMPONENT(bullet, Transform, ComponentType::TRANSFORM)->position = GET_COMPONENT(objectFactory->GetGameObjectByID(gameObjectID), Transform, ComponentType::TRANSFORM)->position;
			GET_COMPONENT(bullet, Transform, ComponentType::TRANSFORM)->position.y += 200;
			GET_COMPONENT(bullet, PhysicsBody, ComponentType::PHYSICS_BODY)->velocity = GET_COMPONENT(objectFactory->GetGameObjectByID(gameObjectID), PhysicsBody, ComponentType::PHYSICS_BODY)->direction * 1000;
		}
	}

	/**************************************************************************
	* @brief End the PlayerShooting script
	* @return void
	*************************************************************************/
	void End() {}

	/**************************************************************************
	* @brief Destructor
	*************************************************************************/
	~PlayerShooting() {}
};

#endif
