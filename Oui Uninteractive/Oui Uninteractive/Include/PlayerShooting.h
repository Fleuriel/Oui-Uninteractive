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
			Vec2 playerPosition{ GET_COMPONENT(objectFactory->GetGameObjectByID(gameObjectID), Transform, ComponentType::TRANSFORM)->position };
			float playerScale{ GET_COMPONENT(objectFactory->GetGameObjectByID(gameObjectID), Transform, ComponentType::TRANSFORM)->scale };


			// Get mouse coordinates
			double mouseX, mouseY, convertedMouseX, convertedMouseY;
			glfwGetCursorPos(windowNew, &mouseX, &mouseY);
			convertedMouseX = mouseX;
			convertedMouseY = mouseY;
			OpenGLObject::FrameBufferMouseCoords(windowNew, &convertedMouseX, &convertedMouseY, OpenGLObject::cameraObject);

			// Set bullet spawn point
			bulletSpawnAngle = atan2(static_cast<float>(convertedMouseY) - playerPosition.y, static_cast<float>(convertedMouseX) - playerPosition.x);
			bulletSpawnOffset = playerScale;
			bulletSpawnPos.x = playerPosition.x + bulletSpawnOffset * cos(bulletSpawnAngle);
			bulletSpawnPos.y = playerPosition.y + bulletSpawnOffset * sin(bulletSpawnAngle);
			GET_COMPONENT(bullet, Transform, ComponentType::TRANSFORM)->position = bulletSpawnPos;
			GET_COMPONENT(bullet, Transform, ComponentType::TRANSFORM)->rotation = bulletSpawnAngle;
			
			// Set bullet shooting direction
			Vec2 shootingDirection;
			if (Vector2DDistance(playerPosition, Vec2(convertedMouseX, convertedMouseY)) >= bulletSpawnOffset) {
				shootingDirection.x = static_cast<float>(convertedMouseX) - bulletSpawnPos.x;
				shootingDirection.y = static_cast<float>(convertedMouseY) - bulletSpawnPos.y;
			}
			else {
				shootingDirection.x = bulletSpawnPos.x - playerPosition.x;
				shootingDirection.y = bulletSpawnPos.y - playerPosition.y;
			}
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
