/**************************************************************************
 * @file EnemyStates.cpp
 * @author HWANG Jing Rui, Austin
 * @par DP email: jingruiaustin.hwang@digipen.edu
 * @par Course:	CSD 2401
 * @par	Software Engineering Project 3
 * @date 26-10-2023
 * @brief This file contains the definition of the enemy states.
 *		  The enemy states consists of:
 *		  - Roam
 *		  - Attack
 *        This file should only contain the behaviour of enemies during
 *        its respective states.
 *************************************************************************/
#include <iostream>
#include "EnemyStates.h"
#include "ObjectFactory.h"
#include "Transform.h"
#include "PhysicsBody.h"

/**************************************************************************
* @brief Constructor for EnemyRoam
*************************************************************************/
EnemyRoam::EnemyRoam() : bfs(new BFS(5, 5)), transitioned(false), pathFound(false), pathPrinted(false), pathIndex(0) {}

/**************************************************************************
* @brief Update the EnemyRoam state
* @return void
*************************************************************************/
void EnemyRoam::Update(size_t gameObjectID) {
	if (!transitioned) {
		std::cout << "\nTRANSITIONED TO ROAM STATE" << std::endl;
		transitioned = true;
	}

    // Temporary variables
	int startX = 1, startY = 0, targetX = 3, targetY = 4;
    
    // If grid not created, create grid
    if (!bfs->gridCreated) {
        bfs->CreateGrid();
    }

    if (!pathFound) {
        // Find path
		pathToTake = bfs->FindPath(startX, startY, targetX, targetY);

        if (pathToTake.size() > 0) {
            pathFound = true;
        }
    }
    else {
        if (!pathPrinted) {
            // Start traversing path
            std::cout << "Start\n";
            
            // Print the path
            for (const Node& node : pathToTake) {
                std::cout << "(" << node.x << ", " << node.y << ") -> ";
            }
            std::cout << "End" << std::endl;

            pathPrinted = true;
        }

		if (pathIndex < pathToTake.size()) {
            // TEMPORARY VARIABLES
            float windowWidth = 1920.f;
            float windowHeight = 1017.f;
            float scaleTemp = windowHeight / bfs->GetRows();

            // Enemy to traverse along path to take
            // While not within range of node, move towards node
            Vec2 currentEnemyPos = Vec2(0, 0);
            Vec2 nodePos;
			Node currentNode = pathToTake[pathIndex];
            nodePos.x = (currentNode.x * scaleTemp) + (scaleTemp - windowWidth) / 2;
            nodePos.y = (currentNode.y * scaleTemp) + (scaleTemp - windowHeight) / 2;

            GameObject* currentEnemy = objectFactory->GetGameObjectByID(gameObjectID);
            if (currentEnemy != nullptr) {
                Transform* currentEnemyTx = GET_COMPONENT(currentEnemy, Transform, ComponentType::TRANSFORM);
                if (currentEnemyTx != nullptr) {
                    currentEnemyPos = currentEnemyTx->position;
                }
            }

			// If within range of node, move towards node
            if (Vector2DDistance(currentEnemyPos, nodePos) > 5) {
                Vec2 direction = Vec2(nodePos.x - currentEnemyPos.x, nodePos.y - currentEnemyPos.y);
                Vector2DNormalize(direction, direction);
                GET_COMPONENT(currentEnemy, PhysicsBody, ComponentType::PHYSICS_BODY)->velocity = direction * 300;
            }
			// Increase index if within range, moving towards next node
            else if (Vector2DDistance(currentEnemyPos, nodePos) <= 5) {
                GET_COMPONENT(currentEnemy, PhysicsBody, ComponentType::PHYSICS_BODY)->velocity = Vec2(0, 0);
                ++pathIndex;
                std::cout << "Travelled to node (" << currentNode.x << ", " << currentNode.y << ")" << std::endl;
            }
		}
    }
}

/**************************************************************************
* @brief Exit the EnemyRoam state
* @return void
*************************************************************************/
void EnemyRoam::ExitState() {
    transitioned = false; 
    pathFound = false;
    pathPrinted = false;
    pathIndex = 0;

    pathToTake.clear();
}

/**************************************************************************
* @brief Destructor for EnemyRoam
*************************************************************************/
EnemyRoam::~EnemyRoam() {
    pathToTake.clear();
	delete bfs;
}

/**************************************************************************
* @brief Constructor for EnemyAttack
*************************************************************************/
EnemyAttack::EnemyAttack() : transitioned(false) {}

/**************************************************************************
* @brief Update the EnemyAttack state
* @return void
*************************************************************************/
void EnemyAttack::Update(size_t gameObjectID) {
    if (!transitioned) {
        std::cout << "\nTRANSITIONED TO ATTACK STATE\n" << std::endl;
        transitioned = true;
    }
}

/**************************************************************************
* @brief Exit the EnemyAttack state
* @return void
*************************************************************************/
void EnemyAttack::ExitState() {
	transitioned = false;
}

/**************************************************************************
* @brief Destructor for EnemyAttack
*************************************************************************/
EnemyAttack::~EnemyAttack() {
}
