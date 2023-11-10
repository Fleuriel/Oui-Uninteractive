/**************************************************************************
 * @file BulletLifetimeScript.h
 * @author HWANG Jing Rui, Austin
 * @par DP email: jingruiaustin.hwang@digipen.edu
 * @par Course:	CSD 2401
 * @par Software Engineering Project 3
 * @date 10-11-2023
 * @brief This file contains the script for bullet lifetime.
 *************************************************************************/
#ifndef BULLET_LIFETIME_H
#define BULLET_LIFETIME_H

#include <string>
#include "IScript.h"
#include "Logic.h"
#include "ObjectFactory.h"
#include "Vector2D.h"

class BulletLifetime : public IScript {
public:
	// TO IMPLEMENT DT IN THE FUTURE
	int timeElapsed;

	/**************************************************************************
	* @brief Constructor
	*************************************************************************/
	BulletLifetime(std::string newName) : IScript(newName) , timeElapsed(0) {}

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
		timeElapsed++;

		if (timeElapsed >= 60) {
			objectFactory->DestroyObject(objectFactory->GetGameObjectByID(gameObjectID));
			timeElapsed = 0;
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
	~BulletLifetime() {}
};

#endif
