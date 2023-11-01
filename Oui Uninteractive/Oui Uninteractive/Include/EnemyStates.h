/**************************************************************************
 * @file EnemyStates.h
 * @author HWANG Jing Rui, Austin
 * @par DP email: jingruiaustin.hwang@digipen.edu
 * @par Course:	CSD 2401
 * @par Software Engineering Project 3
 * @date 26-10-2023
 * @brief This file contains the declaration of the enemy states.
 *		  The enemy states consists of:
 *		  - Roam
 *		  - Attack
 *************************************************************************/
#ifndef ENEMYSTATES_H
#define ENEMYSTATES_H

#include "IState.h"
//#include "BFS.h"

class EnemyRoam : public IState {
private:
	//BFS* bfs;
	//std::vector<Node*> pathToTake;
	//std::vector<Node> pathToTake;
	bool pathFound;
	bool printTest;

public:
	//void Initialize() override;
	EnemyRoam();
	void Update(size_t gameObjectID) override;
	~EnemyRoam() override;
};

class EnemyAttack : public IState {
private:

public:
	//void Initialize() override;
	EnemyAttack();
	void Update(size_t gameObjectID) override;
	~EnemyAttack() override;
};

#endif
