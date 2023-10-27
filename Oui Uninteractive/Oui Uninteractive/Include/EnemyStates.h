/**************************************************************************
 * @file IMessage.h
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
public:
	void Enter();
	void Update();
	void Exit();
};

class EnemyAttack : public IState {
public:
	void Enter();
	void Update();
	void Exit();
};

#endif
