#pragma once
/**************************************************************************
 * @file TransformSystem.h
 * @author CHEAH Tristan Tze Hong
 * @par DP email: t.cheah@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 02-11-2023
 * @brief This file contains the declaration of the Transform System.
 *		  This system is responsible updating the positions of the transforms
 *************************************************************************/
#include "ISystem.h"
#include "Transform.h"
#include "ComponentFactory.h"
#include "ObjectFactory.h"
#include "ColliderSystem.h"
class TransformSystem : public ISystem {
	/**************************************************************************
	* @brief Initialize function for Transform System
	* @return void
	*************************************************************************/
	void Initialize();
	/**************************************************************************
	* @brief Update function for Transform System
	* @param dt - delta time
	* @return void
	*************************************************************************/
	void Update(float dt);
};