/**************************************************************************
 * @file Transform.cpp
 * @author CHEAH Tristan Tze Hong
 * @par DP email: t.cheah@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 27-09-2023
 * @brief This file contains the definition of the Transform Class,
 *		  which is a IComponent to be contained in GameObject. It holds
 *		  all data pertaining to the positioning of GameObject such as 
 *		  rotation and position.
 *************************************************************************/
#include "Transform.h"
/**************************************************************************
* @brief Default constructor for Transform component
*************************************************************************/
Transform::Transform() {
	position = Vec2(0,0);
	previousPosition = position;
	rotation = 0;
	scale = Vec2(100, 100);
	shape = new OpenGLObject(1);
}
/**************************************************************************
* @brief Destructor for Transform component
*************************************************************************/
Transform::~Transform() {
	delete shape;
}
/**************************************************************************
* @brief Initialize function for the Transform Component
* @return void
*************************************************************************/
void Transform::Initialize() {
	//Produce the OpenGLObject based off the Transform component variables
	shape->InitObjects();
}
/**************************************************************************
* @brief Initialize this instance of the Transform component via file
* @param filePath - file path to read from
* @param itr - iterator through json object
* @return void
*************************************************************************/
void Transform::Serialize(rapidjson::Value::ConstMemberIterator& itr) {
	const rapidjson::Value& components{ itr->value };
	position.x = components["PositionX"].GetFloat();
	position.y = components["PositionY"].GetFloat();
	rotation = components["Rotation"].GetFloat();
	scale.x = components["ScaleX"].GetFloat();
	scale.y = components["ScaleY"].GetFloat();
}
/**************************************************************************
* @brief Function to Clone a Transform Component
* @return Transform* - the cloned Transform
*************************************************************************/
Transform* Transform::Clone() const {
	Transform* newTransform = new Transform();
	newTransform->position = position;
	newTransform->scale = scale;
	newTransform->rotation = rotation;
	return newTransform;
}