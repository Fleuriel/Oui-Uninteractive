/**************************************************************************
 * @file EnemyStates.h
 * @author HWANG Jing Rui, Austin
 * @par DP email: jingruiaustin.hwang@digipen.edu
 * @par Course:	CSD 2401
 * @par Software Engineering Project 3
 * @date 26-10-2023
 * @brief
 *************************************************************************/
#ifndef ENEMYSTATES_H
#define ENEMYSTATES_H

#include "IState.h"

class EnemyRoam : public IState {
private:
	

public:
	//EnemyRoam() {}
	//~EnemyRoam() {}

	//void Enter();
	void Update(size_t gameObjectID) override;
	//void Exit();
};

class EnemyAttack : public IState {
private:

public:
	//EnemyAttack() {}
	//~EnemyAttack() {}

	//void Enter();
	void Update(size_t gameObjectID) override;
	//void Exit();
};

#endif
