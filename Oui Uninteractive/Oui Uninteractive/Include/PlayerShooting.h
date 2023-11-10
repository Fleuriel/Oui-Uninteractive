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
#include <iostream>
#include "IScript.h"
#include "Logic.h"
#include "ObjectFactory.h"
#include "PhysicsBody.h"

#define PI 3.141592653589793

class PlayerShooting : public IScript {
public:
	size_t bulletNumber;
	Vec2 bulletSpawnPos;
	float bulletSpawnAngle;
	float bulletSpawnOffset;

	/**************************************************************************
	* @brief Constructor
	*************************************************************************/
	PlayerShooting(std::string newName) : IScript(newName), bulletNumber(0), bulletSpawnPos(Vec2()), bulletSpawnAngle(0.f), bulletSpawnOffset() {}

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
		if (inputSystem.GetMouseState(GLFW_MOUSE_BUTTON_RIGHT)) {
			// Create bullet object from prefab
			std::string bulletName{ "Bullet" + std::to_string(bulletNumber) };
			GameObject* bullet = objectFactory->BuildObjectFromPrefab(bulletName, "BulletPrefab");
			++bulletNumber;

			// Get player
			GameObject* player{ objectFactory->GetGameObjectByID(gameObjectID) };

			// Get mouse coordinates
			double mouseX, mouseY, convertedMouseX, convertedMouseY;
			glfwGetCursorPos(windowNew, &mouseX, &mouseY);
			convertedMouseX = mouseX;
			convertedMouseY = mouseY;
			OpenGLObject::FrameBufferMouseCoords(windowNew, &convertedMouseX, &convertedMouseY, OpenGLObject::cameraObject);

			// Set bullet spawn point
			//GET_COMPONENT(bullet, Transform, ComponentType::TRANSFORM)->position = GET_COMPONENT(player, Transform, ComponentType::TRANSFORM)->position;
			bulletSpawnAngle = atan2(static_cast<float>(convertedMouseY) - GET_COMPONENT(player, Transform, ComponentType::TRANSFORM)->position.y,
				static_cast<float>(convertedMouseX) - GET_COMPONENT(player, Transform, ComponentType::TRANSFORM)->position.x);
			bulletSpawnOffset = GET_COMPONENT(player, Transform, ComponentType::TRANSFORM)->scale;
			bulletSpawnPos.x = GET_COMPONENT(player, Transform, ComponentType::TRANSFORM)->position.x + bulletSpawnOffset * cos(bulletSpawnAngle * PI / 180.0f);
			bulletSpawnPos.y = GET_COMPONENT(player, Transform, ComponentType::TRANSFORM)->position.y + bulletSpawnOffset * sin(bulletSpawnAngle * PI / 180.0f);
			GET_COMPONENT(bullet, Transform, ComponentType::TRANSFORM)->position = bulletSpawnPos;
			GET_COMPONENT(bullet, Transform, ComponentType::TRANSFORM)->rotation = bulletSpawnAngle;


			//GET_COMPONENT(bullet, Transform, ComponentType::TRANSFORM)->position.y += 200;
			//GET_COMPONENT(bullet, PhysicsBody, ComponentType::PHYSICS_BODY)->velocity = GET_COMPONENT(objectFactory->GetGameObjectByID(gameObjectID), PhysicsBody, ComponentType::PHYSICS_BODY)->direction * 1000;
			
			// Set bullet shooting direction
			/*float shootingAngle = atan2(static_cast<float>(convertedMouseY) - GET_COMPONENT(player, Transform, ComponentType::TRANSFORM)->position.y,
				static_cast<float>(convertedMouseX) - GET_COMPONENT(player, Transform, ComponentType::TRANSFORM)->position.x);*/
			
			//float shootingAngle = atan2(static_cast<float>(convertedMouseY) - bulletSpawnPos.y, static_cast<float>(convertedMouseX) - bulletSpawnPos.x);

			//Vec2 shootingDirection(static_cast<float>(convertedMouseX) - bulletSpawnPos.x, static_cast<float>(convertedMouseY) - bulletSpawnPos.y);
			Vec2 shootingDirection(static_cast<float>(convertedMouseX) - bulletSpawnPos.x, static_cast<float>(convertedMouseY) - bulletSpawnPos.y);
			Vector2DNormalize(shootingDirection, shootingDirection);

			// Set bullet velocity
			GET_COMPONENT(bullet, PhysicsBody, ComponentType::PHYSICS_BODY)->velocity = shootingDirection * GET_COMPONENT(bullet, PhysicsBody, ComponentType::PHYSICS_BODY)->speed;
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
