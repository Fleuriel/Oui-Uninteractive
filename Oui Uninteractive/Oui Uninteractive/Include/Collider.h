/**************************************************************************
 * @file Collider.h
 * @author CHEAH Tristan Tze Hong
 * @par DP email: t.cheah@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 02-11-2023
 * @brief This file contains the declaration of the Collider Class,
 *		  which is a IComponent to be contained in GameObject. It holds all
 *		  data pertaining to collision detection/response
 *************************************************************************/
#pragma once
#include "IComponent.h"
#include "Vector2D.h"
#include "Transform.h"


#ifndef COLLIDER_H
#define COLLIDER_H
class Collider;
class Collider : public IComponent {
public:
	class AABB {
	public:
		//Extents of the Axis Aligned Bounding Box
		Vec2 min, max, x, y, center;
		//Reference back to Collider Transform
		Transform* txPtr;
		/**************************************************************************
		* @brief Constructor for AABB struct within Collider
		*************************************************************************/
		AABB();
	};
	/**************************************************************************
	* @brief Initialize function for Collider Component
	* @return void
	*************************************************************************/
	void Initialize();
	/**************************************************************************
	* @brief Serialize function for Collider component
	* @param itr - iterator through json object
	* @return void
	*************************************************************************/
	void Serialize(rapidjson::Value::ConstMemberIterator& itr);
	/**************************************************************************
	* @brief Function to Clone a Collider Component
	* @return Collider* - the cloned Collider
	*************************************************************************/
	Collider* Clone() const;
	/**************************************************************************
	* @brief Constructor for Collider
	*************************************************************************/
	Collider();
	/**************************************************************************
	* @brief Destructor for Collider
	*************************************************************************/
	~Collider();
	//Pointer to Collider Transform
	Transform* tx;
	//Pointer to Collider's bounding box
	AABB* boundingbox;
	//Contact Time of Collider
	float contactTime;
	//Contact Normal of Collider
	Vec2 contactNormal;
};
#endif