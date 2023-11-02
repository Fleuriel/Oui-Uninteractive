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
#include <random>
#include "EnemyStates.h"
#include "ObjectFactory.h"
#include "Transform.h"
#include "PhysicsBody.h"

/**************************************************************************
* @brief Constructor for EnemyRoam
*************************************************************************/
EnemyRoam::EnemyRoam() : bfs(new BFS(5, 5)), transitioned(false), pathFound(false), pathPrinted(false), pathIndex(0) {
    windowWidth = 1920.f;
    windowHeight = 1080.f;
    scaleTemp = windowHeight / bfs->GetRows();
}

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
    //int startX = 1, startY = 0, targetX = 3, targetY = 4;

    // Set start Node's x and y index
    int startX{}, startY{};

    Vec2 currentEnemyPos = Vec2(0, 0);
    GameObject* currentEnemy = objectFactory->GetGameObjectByID(gameObjectID);
    if (currentEnemy != nullptr) {
        Transform* currentEnemyTx = GET_COMPONENT(currentEnemy, Transform, ComponentType::TRANSFORM);
        if (currentEnemyTx != nullptr) {
            currentEnemyPos = currentEnemyTx->position;
            startX = static_cast<int>((currentEnemyPos.x - (scaleTemp - windowWidth) / 2) / scaleTemp);
            startY = static_cast<int>((currentEnemyPos.y - (scaleTemp - windowHeight) / 2) / scaleTemp);

            // If startX and startY is on an obstacle
            if (bfs->GetGameMap()[startY][startX] == 1) {
				// If startX + 1 is not on an obstacle
                if (startX + 1 < bfs->GetRows() && bfs->GetGameMap()[startY][startX + 1] == 0) {
                    ++startX;
                }
                else if (startX - 1 >= 0 && bfs->GetGameMap()[startY][startX - 1] == 0) {
                    ++startX;
                }
            }
        }
    }

    // Get a random number for targetX and targetY
    std::random_device randomDevice;
    std::mt19937 gen(randomDevice());
    std::uniform_int_distribution<int> range(0, 4);

    int targetX = range(gen);
    int targetY = range(gen);

    // Reseed the generator with a new random value
    gen.seed(randomDevice());

    // Find another target coordinate if it is currently a wall
    while (bfs->GetGameMap()[targetY][targetX] == 1) {
        targetX = range(gen);
        targetY = range(gen);
    }
    
    // If grid not created, create grid
    /*if (!bfs->gridCreated) {
        bfs->CreateGrid();
    }*/

    // Create grid
    bfs->CreateGrid();

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
            // Enemy to traverse along path to take
            // While not within range of node, move towards node
            Vec2 nodePos;
            Node currentNode = pathToTake[pathIndex];
            nodePos.x = (currentNode.x * scaleTemp) + (scaleTemp - windowWidth) / 2;
            nodePos.y = (currentNode.y * scaleTemp) + (scaleTemp - windowHeight) / 2;

			// If enemy is within range of node, move towards node
            if (Vector2DDistance(currentEnemyPos, nodePos) > 3) {
                Vec2 direction = Vec2(nodePos.x - currentEnemyPos.x, nodePos.y - currentEnemyPos.y);
                Vector2DNormalize(direction, direction);
                GET_COMPONENT(currentEnemy, PhysicsBody, ComponentType::PHYSICS_BODY)->velocity = direction * 300;
            }
			// Increase index if within range, moving towards next node
            else if (Vector2DDistance(currentEnemyPos, nodePos) <= 3) {
                GET_COMPONENT(currentEnemy, PhysicsBody, ComponentType::PHYSICS_BODY)->velocity = Vec2(0, 0);
                ++pathIndex;
                std::cout << "Travelled to node (" << currentNode.x << ", " << currentNode.y << ")" << std::endl;
            }
		}
        else {
            pathPrinted = false;
            pathFound = false;
            pathIndex = 0;
            bfs->Reset();
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
    bfs->Reset();
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
        std::cout << "\nTRANSITIONED TO ATTACK STATE" << std::endl;
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
