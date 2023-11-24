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
 *        This file should only contain the behavior of enemies during
 *        its respective states.
 *************************************************************************/
#include <iostream>
#include <random>
#include "EnemyStates.h"
#include "ObjectFactory.h"
#include "TilemapLoader.h"
#include "Transform.h"
#include "PhysicsBody.h"

/**************************************************************************
* @brief Get the start node's X and Y position
* @param currentEnemy - pointer to current enemy
* @return std::pair<int, int> - pair of int (X and Y position)
*************************************************************************/
std::pair<int, int> GetStartNodePosition(Vec2 currentEnemyPos, BFS* bfs, float scale, std::pair<int, int> windowSize) {
    // Window width and height
    float windowWidth{ static_cast<float>(windowSize.first) };
    float windowHeight{ static_cast<float>(windowSize.second) };

	// Start Node's x and y index
    std::pair<int, int> startNodePos{};
    int& startX{ startNodePos.first };
    int& startY{ startNodePos.second };

    startX = static_cast<int>(std::round((currentEnemyPos.x - (scale - windowWidth) / 2) / scale));
    startY = static_cast<int>(std::round((currentEnemyPos.y - (scale - windowHeight) / 2) / scale));

    if (startX < 0)
        startX = 0;
    else if (startX >= bfs->GetCols())
        startX = bfs->GetCols() - 1;
    if (startY < 0)
        startY = 0;
    else if (startY >= bfs->GetRows())
        startY = bfs->GetRows() - 1;

    // If startX and startY is on an obstacle
    if (bfs->GetGameMap()[startY][startX] == 1) {
        // If startX + 1 is not on an obstacle
        if (startX + 1 < bfs->GetRows() && bfs->GetGameMap()[startY][startX + 1] == 0) {
            ++startX;
        }
        else if (startX - 1 >= 0 && bfs->GetGameMap()[startY][startX] == 0) {
            ++startX;
        }
    }

    return startNodePos;
}

/**************************************************************************************/

/**************************************************************************
* @brief Constructor for EnemyRoam
*************************************************************************/
EnemyRoam::EnemyRoam() : bfs(new BFS(tilemapLoader->GetTilemap())), transitioned(false), pathFound(false), pathPrinted(false), pathIndex(0) {
    windowWidth = windowSize.first;
    windowHeight = windowSize.second;
    scale = windowHeight / bfs->GetRows();
}

/**************************************************************************
* @brief Update the EnemyRoam state
* @param gameObjectID - ID of enemy
* @return void
*************************************************************************/
void EnemyRoam::Update(size_t gameObjectID) {
    if (!transitioned) {
        std::cout << "\nTRANSITIONED TO ROAM STATE" << std::endl;
        transitioned = true;
    }

    // Set start Node's x and y index
    GameObject* currentEnemy{ objectFactory->GetGameObjectByID(gameObjectID) };
    Vec2 currentEnemyPos{ Vec2(0, 0) };
    std::pair<int, int> startNodePos{};
    if (currentEnemy != nullptr) {
        Transform* currentEnemyTx = GET_COMPONENT(currentEnemy, Transform, ComponentType::TRANSFORM);
        if (currentEnemyTx != nullptr) {
            currentEnemyPos = currentEnemyTx->position;
            startNodePos = GetStartNodePosition(currentEnemyPos, bfs, scale, windowSize);
        }
    }
    int startX{ startNodePos.first };
    int startY{ startNodePos.second };

    // Get a random number for targetX and targetY
    std::random_device randomDevice;
    std::mt19937 gen(randomDevice());
    std::uniform_int_distribution<int> rangeX(0, 15);
    std::uniform_int_distribution<int> rangeY(0, 8);

    int targetX{ rangeX(gen) };
    int targetY{ rangeY(gen) };

    // Reseed the generator with a new random value
    gen.seed(randomDevice());

    // Find another target coordinate if it is currently a wall
    while (bfs->GetGameMap()[targetY][targetX] == 1) {
        targetX = rangeX(gen);
        targetY = rangeY(gen);
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
            // Enemy to traverse along path to take
            // While not within range of node, move towards node
            Vec2 nodePos;
            Node currentNode = pathToTake[pathIndex];
            nodePos.x = (currentNode.x * scale) + (scale - windowWidth) / 2;
            nodePos.y = (currentNode.y * scale) + (scale - windowHeight) / 2;

			// If enemy is within range of node, move towards node
            if (Vector2DDistance(currentEnemyPos, nodePos) > 3) {
                Vec2 direction = Vec2(nodePos.x - currentEnemyPos.x, nodePos.y - currentEnemyPos.y);
                Vector2DNormalize(direction, direction);
                float currentSpeed{ GET_COMPONENT(currentEnemy, PhysicsBody, ComponentType::PHYSICS_BODY)->speed };
                GET_COMPONENT(currentEnemy, PhysicsBody, ComponentType::PHYSICS_BODY)->velocity = direction * currentSpeed;
            }
			// Increase index if within range, moving towards next node
            else if (Vector2DDistance(currentEnemyPos, nodePos) <= 3) {
                GET_COMPONENT(currentEnemy, PhysicsBody, ComponentType::PHYSICS_BODY)->velocity = Vec2(0, 0);
                ++pathIndex;
                std::cout << "Travelled to node (" << currentNode.x << ", " << currentNode.y << ")" << std::endl;
            }
		}
        else {
            pathFound = false;
            pathPrinted = false;
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

/**************************************************************************************/

/**************************************************************************
* @brief Constructor for EnemyAttack
*************************************************************************/
EnemyAttack::EnemyAttack() : transitioned(false) {}

/**************************************************************************
* @brief Update the EnemyAttack state
* @param gameObjectID - ID of enemy
* @return void
*************************************************************************/
void EnemyAttack::Update(size_t gameObjectID) {
    (void)gameObjectID;
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

/**************************************************************************************/

/**************************************************************************
* @brief Constructor for EnemyFlee
*************************************************************************/
EnemyFlee::EnemyFlee() : bfs(new BFS(tilemapLoader->GetTilemap())), transitioned(false), pathFound(false), pathPrinted(false), pathIndex(0) {
    windowWidth = windowSize.first;
    windowHeight = windowSize.second;
    scale = windowHeight / bfs->GetRows();
}

/**************************************************************************
* @brief Update the EnemyFlee state
* @param gameObjectID - ID of enemy
* @return void
*************************************************************************/
void EnemyFlee::Update(size_t gameObjectID) {
    if (!transitioned) {
        std::cout << "\nTRANSITIONED TO FLEE STATE" << std::endl;
        transitioned = true;
    }

    // Set start Node's x and y index
    GameObject* currentEnemy{ objectFactory->GetGameObjectByID(gameObjectID) };
    Vec2 currentEnemyPos{ Vec2(0, 0) };
    std::pair<int, int> startNodePos{};
    if (currentEnemy != nullptr) {
        Transform* currentEnemyTx = GET_COMPONENT(currentEnemy, Transform, ComponentType::TRANSFORM);
        if (currentEnemyTx != nullptr) {
            currentEnemyPos = currentEnemyTx->position;
            startNodePos = GetStartNodePosition(currentEnemyPos, bfs, scale, windowSize);
        }
    }
    int startX{ startNodePos.first };
    int startY{ startNodePos.second };

    // Find target node from tilemap (target node is '2')
    int targetX{}, targetY{};
    std::vector<std::vector<int>> gameMap{ bfs->GetGameMap() };
    for (auto row{ gameMap.begin() }; row != gameMap.end(); ++row) {
        auto col{ std::find(row->begin(), row->end(), 2) };
        if (col != row->end()) {
            targetX = static_cast<int>(std::distance(row->begin(), col));
            targetY = static_cast<int>(std::distance(gameMap.begin(), row));
            break;
        }
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
            std::cout << "Start (fleeing)\n";

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
            nodePos.x = (currentNode.x * scale) + (scale - windowWidth) / 2;
            nodePos.y = (currentNode.y * scale) + (scale - windowHeight) / 2;

            // If enemy is within range of node, move towards node
            if (Vector2DDistance(currentEnemyPos, nodePos) > 3) {
                Vec2 direction = Vec2(nodePos.x - currentEnemyPos.x, nodePos.y - currentEnemyPos.y);
                Vector2DNormalize(direction, direction);
                float currentSpeed{ GET_COMPONENT(currentEnemy, PhysicsBody, ComponentType::PHYSICS_BODY)->speed };
                GET_COMPONENT(currentEnemy, PhysicsBody, ComponentType::PHYSICS_BODY)->velocity = direction * currentSpeed;
            }
            // Increase index if within range, moving towards next node
            else if (Vector2DDistance(currentEnemyPos, nodePos) <= 3) {
                GET_COMPONENT(currentEnemy, PhysicsBody, ComponentType::PHYSICS_BODY)->velocity = Vec2(0, 0);
                ++pathIndex;
                std::cout << "Travelled to node (" << currentNode.x << ", " << currentNode.y << ")" << std::endl;
            }
        }
        /* else {
			std::cout << "TARGET ESCAPED" << std::endl;
        }*/
    }
}

/**************************************************************************
* @brief Exit the EnemyFlee state
* @return void
*************************************************************************/
void EnemyFlee::ExitState() {
    transitioned = false;
    pathFound = false;
    pathPrinted = false;
    pathIndex = 0;

    pathToTake.clear();
    bfs->Reset();
}

/**************************************************************************
* @brief Destructor for EnemyFlee
*************************************************************************/
EnemyFlee::~EnemyFlee() {
    pathToTake.clear();
	delete bfs;
}
