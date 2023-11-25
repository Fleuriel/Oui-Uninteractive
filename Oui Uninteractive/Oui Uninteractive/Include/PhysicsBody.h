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
#include <bitset>

//Forward declaration for PhysicsBody
class PhysicsBody;
enum FORCE_INDEX {
	INTERNAL = 0,
	EXTERNAL = 1,
	FRICTION = 2
};
class LinearForce {
public:
	/**************************************************************************
	* @brief Constructor for LinearForce
	*************************************************************************/
	LinearForce(float lifetime, bool isActive, float magnitude);
	float lifetime;
	float age;
	bool isActive;
	Vec2 direction;
	float magnitude;
};
class ForceManager {
public:
	/**************************************************************************
	* @brief Constructor for ForceManager
	*************************************************************************/
	ForceManager();
	std::vector<LinearForce*> forceVec;
	/**************************************************************************
	* @brief Add a Force Object to ForceManager
	* @param force - force object to add
	* @return void
	*************************************************************************/
	void AddForce(LinearForce* newForce);
	/**************************************************************************
	* @brief Applies another Vector to a Force in the Force Vectpr
	* @param dir - direction of new force
	* @param magnitude - magnitude of the force
	* @param lifetime - lifetime of the new force
	* @param index - index of force to apply new force to
	* @return void
	*************************************************************************/
	void ApplyToForce(Vec2 direction, float magnitude, float lifetime, FORCE_INDEX index);
	/**************************************************************************
	* @brief Deactivate force if active
	* @param index - index of force to deactivate
	* @return void
	*************************************************************************/
	void DeactivateForce(FORCE_INDEX index);
	/**************************************************************************
	* @brief Deactivate force if active
	* @param index - index of force to deactivate
	* @return void
	*************************************************************************/
	void DeactivateForce(int index);
	/**************************************************************************
	* @brief Setter for isActive flag
	* @param activeFlag - the flag to set to
	* @param index - index of force to change
	* @return void
	*************************************************************************/
	void SetActive(bool activeFlag, FORCE_INDEX index);
	/**************************************************************************
	* @brief Setter for Direction
	* @param dir - direction to set to
	* @param index - index of force to change
	* @return void
	*************************************************************************/
	void SetDirection(Vec2 newDir, FORCE_INDEX index);
	/**************************************************************************
	* @brief Setter for Magnitude variable
	* @param index - index of force to set
	* @param new_mag - value to set to
	* @return void
	*************************************************************************/
	void SetMagnitude(float new_magnitude, FORCE_INDEX index);
	/**************************************************************************
	* @brief Update function for forceManager
	* @param dt - delta time
	* @return void
	*************************************************************************/
	void Update(float dt);
	/**************************************************************************
	* @brief Setter for Lifetime
	* @param lf - lifetime to set to
	* @param index - index of force to change
	* @return void
	*************************************************************************/
	void SetLifetime(float lifetime, FORCE_INDEX index);
	/**************************************************************************
	* @brief Calculate the resultant force of all the current active Forces
	* @return Vec2
	*************************************************************************/
	Vec2 CalculateResultantForce();
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
	float frictionForce;

	ForceManager forceManager;
};

#endif
