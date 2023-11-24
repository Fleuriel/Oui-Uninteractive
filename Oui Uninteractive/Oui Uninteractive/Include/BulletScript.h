/**************************************************************************
 * @file BulletScript.h
 * @author HWANG Jing Rui, Austin
 * @par DP email: jingruiaustin.hwang@digipen.edu
 * @par Course:	CSD 2401
 * @par Software Engineering Project 3
 * @date 10-11-2023
 * @brief This file contains the script for player's bullet.
 *************************************************************************/
#ifndef BULLET_SCRIPT_H
#define BULLET_SCRIPT_H

#include <string>
#include "IScript.h"
#include "Logic.h"
#include "ObjectFactory.h"
#include "Vector2D.h"

class BulletScript : public IScript {
public:
	/**************************************************************************
	* @brief Constructor
	*************************************************************************/
	BulletScript(std::string newName) : IScript(newName) {}

	/**************************************************************************
	* @brief Initialize the PlayerShooting script
	* @return void
	*************************************************************************/
	void Initialize() {
		logicSystem->AddLogicScript(this);
	}

	/**************************************************************************
	* @brief Update the PlayerShooting script
	* @return void
	*************************************************************************/
	void Update(size_t gameObjectID) {
		GameObject* bullet{ objectFactory->GetGameObjectByID(gameObjectID) };
		
		// Variables for bullet collision check
		float contactTime{};
		Vec2 normal(0.f, 0.f);

		// Check for bullet collision with walls
		for (auto& obj : objectFactory->GetGameObjectIDMap()) {
			if (obj.second->GetType() == "WallPrefab" || obj.second->GetName().find("Bullet") != std::string::npos) {
				if (CollisionMovingRectRect(*GET_COMPONENT(bullet, Collider, ComponentType::COLLIDER)->boundingbox, 
											*GET_COMPONENT(obj.second, Collider, ComponentType::COLLIDER)->boundingbox, 
											GET_COMPONENT(bullet, PhysicsBody, ComponentType::PHYSICS_BODY)->velocity - GET_COMPONENT(obj.second, PhysicsBody, ComponentType::PHYSICS_BODY)->velocity, 
											contactTime, normal, static_cast<float>(GetDT()), 
											GET_COMPONENT(bullet, PhysicsBody, ComponentType::PHYSICS_BODY)->velocity)) {
					objectFactory->DestroyObject(bullet);
				}
			}
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
	~BulletScript() {}
};

#endif
