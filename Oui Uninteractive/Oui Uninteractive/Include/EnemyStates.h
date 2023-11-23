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
#include "BFS.h"

/**************************************************************************
* @brief Get the start node's X and Y position
* @param currentEnemy - pointer to current enemy
* @return std::pair<int, int> - pair of int (X and Y position)
*************************************************************************/
//std::pair<int, int> GetStartNodePosition(Vec2 currentEnemyPos, BFS* bfs, float scale, float windowWidth, float windowHeight);

class EnemyRoam : public IState {
private:
	BFS* bfs;
	std::vector<Node> pathToTake;
	bool transitioned;
	bool pathFound;
	bool pathPrinted;
	int pathIndex;

	// TEMPORARY VARIABLES
	float windowWidth;
	float windowHeight;
	float scale;

public:
	/**************************************************************************
	* @brief Constructor
	*************************************************************************/
	EnemyRoam();

	/**************************************************************************
	* @brief Update the EnemyRoam state
	* @param gameObjectID - ID of enemy
	* @return void
	*************************************************************************/
	void Update(size_t gameObjectID) override;

	/**************************************************************************
	* @brief Exit the EnemyRoam state
	* @return void
	*************************************************************************/
	void ExitState() override;

	/**************************************************************************
	* @brief Destructor
	*************************************************************************/
	~EnemyRoam() override;
};

class EnemyAttack : public IState {
private:
	bool transitioned;

public:
	/**************************************************************************
	* @brief Constructor
	*************************************************************************/
	EnemyAttack();

	/**************************************************************************
	* @brief Update the EnemyAttack state
	* @param gameObjectID - ID of enemy
	* @return void
	*************************************************************************/
	void Update(size_t gameObjectID) override;

	/**************************************************************************
	* @brief Exit the EnemyAttack state
	* @return void
	*************************************************************************/
	void ExitState() override;

	/**************************************************************************
	* @brief Destructor
	*************************************************************************/
	~EnemyAttack() override;
};

class EnemyFlee : public IState {
private:
	BFS* bfs;
	std::vector<Node> pathToTake;
	bool transitioned;
	bool pathFound;
	bool pathPrinted;
	int pathIndex;

	// TEMPORARY VARIABLES
	float windowWidth;
	float windowHeight;
	float scale;

public:
	/**************************************************************************
	* @brief Constructor
	*************************************************************************/
	EnemyFlee();

	/**************************************************************************
	* @brief Update the EnemyRoam state
	* @param gameObjectID - ID of enemy
	* @return void
	*************************************************************************/
	void Update(size_t gameObjectID) override;

	/**************************************************************************
	* @brief Exit the EnemyRoam state
	* @return void
	*************************************************************************/
	void ExitState() override;

	/**************************************************************************
	* @brief Destructor
	*************************************************************************/
	~EnemyFlee() override;
};

#endif
