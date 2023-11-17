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

#define PI 3.141592653589793

class PlayerShooting : public IScript {
public:
	size_t bulletNumber;
	Vec2 bulletSpawnPos;
	float bulletSpawnAngle;
	float bulletSpawnOffset;
	int shootingInterval; // Scuffed method for now

	/**************************************************************************
	* @brief Constructor
	*************************************************************************/
	PlayerShooting(std::string newName) : IScript(newName), bulletNumber(0), bulletSpawnPos(Vec2()), bulletSpawnAngle(0.f), bulletSpawnOffset(0.f), shootingInterval(0) {}

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
			if (shootingInterval == 0) {
				// Create bullet object from prefab
				std::string bulletName{ "Bullet" + std::to_string(bulletNumber) };
				GameObject* bullet = objectFactory->BuildObjectFromPrefab(bulletName, "BulletPrefab");
				++bulletNumber;

				// Get player
				Vec2 playerPos{ GET_COMPONENT(objectFactory->GetGameObjectByID(gameObjectID), Transform, ComponentType::TRANSFORM)->position };
				//float playerScale{ GET_COMPONENT(objectFactory->GetGameObjectByID(gameObjectID), Transform, ComponentType::TRANSFORM)->scale };

				// Get mouse coordinates
				double mouseX{}, mouseY{}, convertedMouseX{}, convertedMouseY{};
				glfwGetCursorPos(windowNew, &mouseX, &mouseY);
				convertedMouseX = mouseX;
				convertedMouseY = mouseY;
				OpenGLObject::FrameBufferMouseCoords(windowNew, &convertedMouseX, &convertedMouseY, OpenGLObject::cameraObject);
				Vec2 convertedMousePos{ static_cast<float>(convertedMouseX), static_cast<float>(convertedMouseY) };

				// Set bullet spawn point
				bulletSpawnAngle = atan2(static_cast<float>(convertedMouseY) - playerPos.y, static_cast<float>(convertedMouseX) - playerPos.x);
			/*	bulletSpawnOffset = playerScale;
				bulletSpawnPos.x = playerPos.x + bulletSpawnOffset * cos(bulletSpawnAngle);
				bulletSpawnPos.y = playerPos.y + bulletSpawnOffset * sin(bulletSpawnAngle);*/
				GET_COMPONENT(bullet, Transform, ComponentType::TRANSFORM)->position = bulletSpawnPos;
				GET_COMPONENT(bullet, Transform, ComponentType::TRANSFORM)->rotation = bulletSpawnAngle;

				// Set bullet shooting direction
				Vec2 shootingDirection;
				/*if (Vector2DDistance(playerPos, convertedMousePos) >= bulletSpawnOffset) {
					shootingDirection.x = static_cast<float>(convertedMouseX) - playerPos.x;
					shootingDirection.y = static_cast<float>(convertedMouseY) - playerPos.y;
				}
				else {
					shootingDirection.x = bulletSpawnPos.x - playerPos.x;
					shootingDirection.y = bulletSpawnPos.y - playerPos.y;
				}
				Vector2DNormalize(shootingDirection, shootingDirection);*/

				// Set bullet velocity
				GET_COMPONENT(bullet, PhysicsBody, ComponentType::PHYSICS_BODY)->velocity = shootingDirection * GET_COMPONENT(bullet, PhysicsBody, ComponentType::PHYSICS_BODY)->speed;

				++shootingInterval;
			}
			else {
				++shootingInterval;
				if (shootingInterval >= 30) {
					shootingInterval = 0;
				}
			}
		}
		else {
			shootingInterval = 0;
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
