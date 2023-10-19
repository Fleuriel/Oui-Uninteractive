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
enum FORCE_INDEX {
	INTERNAL = 0,
	EXTERNAL = 1
};
class LinearForce {
public:
	LinearForce(float lifetime, bool isActive, float magnitude);
	float lifetime;
	float age;
	bool isActive;
	Vec2 direction;
	float magnitude;
};
class RotationalForce  {
	public:
		float lifetime;
		float age;
		bool isActive;
		float torque;
};
class ForceManager {
public:
	ForceManager();
	std::vector<LinearForce*> forceVec;
	void AddForce(LinearForce* newForce);
	void ApplyToForce(Vec2 direction, float magnitude, float lifetime, FORCE_INDEX index);
	void DeactivateForce(FORCE_INDEX index);
	void DeactivateForce(int index);
	void SetActive(bool activeFlag, FORCE_INDEX index);
	void SetDirection(Vec2 newDir, FORCE_INDEX index);
	void SetMagnitude(float new_magnitude, FORCE_INDEX index);
	void Update(float dt);
	Vec2 CalculateResultantForce();
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

/*----------TESTING MESSAGING SYSTEM----------*/
class MessageCollision : public IMessage {
public:
	// Message information

};
/*----------TESTING MESSAGING SYSTEM----------*/

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


	/*----------TESTING MESSAGING SYSTEM----------*/
	virtual void RegisterObserver(IObserver* observer);
	virtual void UnregisterObserver(IObserver* observer);
	virtual void NotifyObservers(IMessage* msg);
	/*----------TESTING MESSAGING SYSTEM----------*/

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
	float frictionForce;

	ForceManager forceManager;
};

#endif
