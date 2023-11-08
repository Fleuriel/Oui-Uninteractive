/**************************************************************************
 * @file ComponentType.h
 * @author HWANG Jing Rui, Austin
 * @par DP email: jingruiaustin.hwang@digipen.edu
 * @par Course: CSD 2401
 * @par	Software Engineering Project 3
 * @date 10-09-2023
 * @brief This file contains an enumeration of the component types.
 *************************************************************************/
#ifndef COMPONENT_TYPE_H
#define COMPONENT_TYPE_H

typedef enum class ComponentType {
	PHYSICS_BODY = 0,
	TRANSFORM,
	LOGICCOMPONENT,
	COLLIDER,
	ENEMY_FSM,
	COUNT
} componentType;

#endif
