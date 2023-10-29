/**************************************************************************
 * @file Transform.h
 * @author CHEAH Tristan Tze Hong
 * @par DP email: t.cheah@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 27-09-2023
 * @brief This file contains the declaration of the Transform Class,
 *		  which is a IComponent to be contained in GameObject. It holds
 *		  all data pertaining to the positioning of GameObject such as
 *		  rotation and position.
 *************************************************************************/

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Vector2D.h"
#include "IComponent.h"
#include "GameObject.h"
#include "OpenGLObjects.h"

class Transform : public IComponent {
public:
	/**************************************************************************
	* @brief Default constructor for Transform component
	*************************************************************************/
	Transform();
	/**************************************************************************
	* @brief Destructor for Transform component
	*************************************************************************/
	~Transform();
	/**************************************************************************
	* @brief Initialize function for the Transform Component
	* @return void
	*************************************************************************/
	virtual void Initialize();
	/**************************************************************************
	* @brief Initialize this instance of the Transform component via file
	* @param itr - iterator through json object
	* @return void
	*************************************************************************/
	void Serialize(rapidjson::Value::ConstMemberIterator& itr);
	/**************************************************************************
	* @brief Function to Clone a Transform Component
	* @return Transform* - the cloned Transform
	*************************************************************************/
	virtual Transform* Clone() const;
	//Member Variables
	Vec2 position;
	Vec2 previousPosition;
	float scale;
	float rotation;
	OpenGLObject* shape;
};

#endif TRANSFORM_H