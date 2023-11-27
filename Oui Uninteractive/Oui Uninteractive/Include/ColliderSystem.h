/**************************************************************************
 * @file ColliderSystem.h
 * @author CHEAH Tristan Tze Hong - 100%
 * @par DP email: t.cheah@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 02-11-2023
 * @brief This file contains the declaration of the Collider System.
 *		  This system is responsible for collision detection and sending the 
 *		  collision response message to the Physics System.
 *************************************************************************/
#pragma once

#ifndef COLLIDERSYS_H
#define COLLIDERSYS_H

#include <map>
#include "Collider.h"
#include "Collision.h"
#include "ISystem.h"
#include "ObjectFactory.h"
#include "ComponentFactory.h"
#include "ComponentType.h"
#include "Editor.h"
#include "HealthComponent.h"
#include "HealthSystem.h"

class ColliderSystem : public ISystem {
public:
	/**************************************************************************
	* @brief Constructor for Collider System
	*************************************************************************/
	ColliderSystem();
	/**************************************************************************
	* @brief Initialize function for ColliderSystem
	* @return void
	*************************************************************************/
	virtual void Initialize();
	/**************************************************************************
	* @brief Update function for ColliderSystem
	* @param dt - delta time
	* @return void
	*************************************************************************/
	virtual void Update(float dt);
	//map of collider to game object id
	std::map<size_t, Collider*> colliderMap;
};
extern ColliderSystem* colliderSys;
#endif