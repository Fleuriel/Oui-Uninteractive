/**************************************************************************
 * @file PhysicsBody.h
 * @author CHEAH Tristan Tze Hong
 * @par DP email: t.cheah@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 27-09-2023
 * @brief This file contains the declaration of the PhysicsBody Class,
 *		  which is a IComponent to be contained in GameObject. It holds
 *		  all data pertaining to Physics calculations such as movement 
 *		  and rotation.
 *************************************************************************/
#ifndef PHYSICS_BODY_H
#define PHYSICS_BODY_H

#include "IComponent.h"
#include "Transform.h"
#include "Vector2D.h"
#include "GameObject.h"

//Forward declaration for PhysicsBody
class PhysicsBody;
class Force {
	float lifetime;
	float age;
	bool isActive;
};

class LinearForce : public Force {
	Vec2 direction;
	float magnitude;
};
class RotationalForce : public Force {
	float torque;
};
class ForceManager {
	std::vector<Force*> forceVec;
	void AddForce(Force* newForce);
	void Update();
	void CalculateResultantForce();
};


class AABB {
public:
	//Extents of the Axis Aligned Bounding Box
	Vec2 min, max;

	/**************************************************************************
	* @brief Default constructor for AABB
	*************************************************************************/
	AABB() {};
};

class PhysicsBody : public IComponent {
public:
	/**************************************************************************
	* @brief Default constructor for PhysicsBody component
	*************************************************************************/
	PhysicsBody();
	/**************************************************************************
	* @brief Destructor for PhysicsBody component
	*************************************************************************/
	~PhysicsBody();
	/**************************************************************************
	* @brief Initialize this instance of the PhysicsBody component
	* @return void
	*************************************************************************/
	virtual void Initialize();
	/**************************************************************************
	* @brief Initialize this instance of the PhysicsBody component via file
	* @param itr - iterator through json object
	* @return void
	*************************************************************************/
	virtual void Serialize(rapidjson::Value::ConstMemberIterator& itr);
	/**************************************************************************
	* @brief Function to Clone a PhysicsBody Component
	* @return PhysicsBody* - the cloned PhysicsBody
	*************************************************************************/
	virtual PhysicsBody* Clone() const;

	//Member Variables
	// 
	float mass;
	//Speed of Rotation
	float rotationSpeed;
	//Movement Speed
	float speed;
	//Pointer to Bounding Box object
	AABB* boundingbox;
	//Vector to hold velocity
	Vec2 velocity;
	//Variable to hold current rotation speed
	float currentRotationSpeed;
	//Acceleration value
	Vec2 acceleration;
	//Diretion vector of PhysicsBody
	Vec2 direction;
	//Ptr to transform component for each physics body
	Transform* txPtr; 
	// flag for engine to ignore objects that we won't move.
	bool isStatic; 

	ForceManager forceManager;
};

#endif
