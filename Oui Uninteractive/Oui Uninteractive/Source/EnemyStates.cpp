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

// FOR TESTING OF BFS //
/*#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

int rows{ 10 };
int cols{ 10 };
std::vector<std::vector<int>> gameMap(rows, std::vector<int>(cols, 0));
bool pathFound{ false };

struct Node {
    float x, y;
    Node* parent;

    // Node constructor
    Node(int x_, int y_) : x(x_), y(y_), parent(nullptr) {}
};

std::vector<Node*> BFS(int startX, int startY, int targetX, int targetY) {
    // Test walls
    //gameMap[0][3] = 1;
    //gameMap[1][2] = 1;
    //gameMap[1][3] = 1;
    //gameMap[2][3] = 1;
    //gameMap[3][1] = 1;
    //gameMap[3][2] = 1;
    //gameMap[3][3] = 1;

    // Queue of nodes to determine path
    std::queue<Node*> nodeQueue;

    // Path of nodes to follow
    std::vector<Node*> path;

    // Start/end nodes
    Node* startNode{ new Node(startX, startY) };
    Node* endNode{ new Node(targetX, targetY) };

    nodeQueue.push(startNode);

    while (!nodeQueue.empty()) {
        Node* currentNode = nodeQueue.front();
        nodeQueue.pop();

        // If the current node is the end node
        if (currentNode->x == endNode->x && currentNode->y == endNode->y) {
            // Trace parent nodes to get the path
            Node* current{ currentNode };
            while (current != nullptr) {
                path.push_back(current);
                current = current->parent;
            }
            std::reverse(path.begin(), path.end());
            break;
        }

        // Check neighbouring nodes
        for (int neighbourY{ -1 }; neighbourY <= 1; ++neighbourY) {
            for (int neighbourX{ -1 }; neighbourX <= 1; ++neighbourX) {
                // Ignore if on the current node
                if (neighbourX == 0 && neighbourY == 0)
                    continue;

                // Set variables for position of node to check
                int checkX = currentNode->x + neighbourX;
                int checkY = currentNode->y + neighbourY;

                // Ignore if neighbour check goes out of range
                if (checkX < 0 || checkX >= cols || checkY < 0 || checkY >= rows)
                    continue;

                // Ignore if neighbour is an obstacle (e.g. wall)
                if (gameMap[checkX][checkY] == 1)
                    continue;

                //---CORNER CHECKS---//
                // Top-left corner
                if (neighbourX == -1 && neighbourY == -1) {
                    // Edge on the right/bottom is an obstacle
                    if (gameMap[checkX + 1][checkY] == 1 || gameMap[checkX][checkY + 1] == 1)
                        continue;
                }

                // Top-right corner
                if (neighbourX == 1 && neighbourY == -1) {
                    // Edge on the left/bottom is an obstacle
                    if (gameMap[checkX - 1][checkY] == 1 || gameMap[checkX][checkY + 1] == 1)
                        continue;
                }

                // Bottom-left corner
                if (neighbourX == -1 && neighbourY == 1) {
                    // Edge on the top/right is an obstacle
                    if (gameMap[checkX][checkY - 1] == 1 || gameMap[checkX + 1][checkY] == 1)
                        continue;
                }

                // Bottom-right corner
                if (neighbourX == 1 && neighbourY == 1) {
                    // Edge on the top/left is an obstacle
                    if (gameMap[checkX][checkY - 1] == 1 || gameMap[checkX - 1][checkY] == 1)
                        continue;
                }
                //---CORNER CHECKS---//

                // Initialize neighbour node
                Node* neighbour = new Node(checkX, checkY);
                neighbour->parent = currentNode;

                // Add to node queue for further checking
                nodeQueue.push(neighbour);
            }
        }
    }

    // Clean up memory for nodes.
    while (!nodeQueue.empty()) {
        delete nodeQueue.front();
        nodeQueue.pop();
    }

    return path;
}*/
// FOR TESTING OF BFS //


//EnemyRoam::EnemyRoam() : bfs(new BFS(10, 10)), pathFound(false), printTest(false) {}
EnemyRoam::EnemyRoam() : pathFound(false), printTest(false) {}

void EnemyRoam::Update(size_t gameObjectID) {
	//std::cout << "Does this work on " << objectFactory->GetGameObjectByID(gameObjectID)->GetName() << std::endl;
    
    //if (!pathFound) {
    //    // Find path
    //    pathToTake = bfs->FindPath(1, 1, 2, 0);

    //    if (pathToTake.size() > 0) {
    //        pathFound = true;
    //    }
    //}
    //else {
    //    if (!printTest) {
    //        // Start traversing path
    //        std::cout << "Start\n";
    //        
    //        // Print the path
    //        for (const Node& node : pathToTake) {
    //            std::cout << "(" << node.x << ", " << node.y << ") -> ";
    //        }
    //        std::cout << "End" << std::endl;

    //        printTest = true;

    //        /*for (Node* node : pathToTake) {
    //            delete node;
    //        }*/
    //        pathToTake.clear();
    //    }
    //}
    

    /*if (!pathFound) {
        std::cout << "Start\n";
        std::vector<Node*> path = BFS(0, 0, 6, 7);
        // Print the path.
        for (Node* node : path) {
            std::cout << "(" << node->x << ", " << node->y << ") -> ";
        }
        std::cout << "End" << std::endl;

        // Clean up memory.
        for (Node* node : path) {
            delete node;
        }
        pathFound = true;
    }*/
}

EnemyRoam::~EnemyRoam() {
    // Erase path vector
    /*for (Node* node : pathToTake) {
        delete node;
    }*/

    //pathToTake.clear();

    // Delete bfs pointer
	//delete bfs;
}

EnemyAttack::EnemyAttack() {}

void EnemyAttack::Update(size_t gameObjectID) {
	//std::cout << "TRANSITIONED TO ATTACK STATE LMAO\n" << std::endl;
}

EnemyAttack::~EnemyAttack() {
}
