/**************************************************************************
 * @file EnemyStates.cpp
 * @author HWANG Jing Rui, Austin
 * @par DP email: jingruiaustin.hwang@digipen.edu
 * @par Course:	CSD 2401
 * @par	Software Engineering Project 3
 * @date 26-10-2023
 * @brief This file contains 
 *************************************************************************/
#include <iostream>
#include "EnemyStates.h"

void EnemyRoam::Update(size_t gameObjectID) {
	//std::cout << "Does this work on " << objectFactory->GetGameObjectByID(gameObjectID)->GetName() << std::endl;
	
	// If collision message detected, change state

}

void EnemyAttack::Update(size_t gameObjectID) {
	std::cout << "TRANSITIONED TO ATTACK STATE LMAO\n" << std::endl;
}
