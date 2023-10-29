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
 *************************************************************************/
#include <iostream>
#include "EnemyStates.h"


// BFS TO BE MOVED TO ANOTHER FILE
#include <vector>
#include <queue>
#include <algorithm>

const int mapWidth = 10;
const int mapHeight = 10;
int gameMap[mapWidth][mapHeight];

struct Node {
    int x, y;       // Position on the map.
    Node* parent;   // Parent node in the path.

    Node(int _x, int _y) : x(_x), y(_y), parent(nullptr) {}
};

std::vector<Node*> BFS(int startX, int startY, int goalX, int goalY) {
    std::queue<Node*> openSet;
    std::vector<Node*> path;

    Node* startNode = new Node(startX, startY);
    Node* goalNode = new Node(goalX, goalY);

    openSet.push(startNode);

    while (!openSet.empty()) {
        Node* currentNode = openSet.front();
        openSet.pop();
        std::cout << "HERE??\n";
        if (currentNode->x == goalNode->x && currentNode->y == goalNode->y) {
            // Goal reached, reconstruct the path.
            Node* current = currentNode;
            while (current != nullptr) {
                path.push_back(current);
                current = current->parent;
            }
            std::reverse(path.begin(), path.end());
            break;
        }

        // Generate neighboring nodes.
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) continue;

                int newX = currentNode->x + dx;
                int newY = currentNode->y + dy;

                if (newX < 0 || newX >= mapWidth || newY < 0 || newY >= mapHeight) continue;
                if (gameMap[newX][newY] == 1) continue;  // Obstacle check.

                Node* neighbor = new Node(newX, newY);
                neighbor->parent = currentNode;

                openSet.push(neighbor);
            }
        }
    }

    // Clean up memory for nodes.
    while (!openSet.empty()) {
        delete openSet.front();
        openSet.pop();
    }

    return path;
}
// BFS TO BE MOVED TO ANOTHER FILE

void EnemyRoam::Update(size_t gameObjectID) {
	std::cout << "Does this work on " << objectFactory->GetGameObjectByID(gameObjectID)->GetName() << std::endl;

	// Pathfinding
    /*std::cout << "Start\n";
    std::vector<Node*> path = BFS(0, 0, 1, 3);
    // Print the path.
    for (Node* node : path) {
        std::cout << "(" << node->x << ", " << node->y << ") -> ";
    }
    std::cout << "End" << std::endl;

    // Clean up memory.
    for (Node* node : path) {
        delete node;
    }*/
}

void EnemyAttack::Update(size_t gameObjectID) {
	std::cout << "TRANSITIONED TO ATTACK STATE LMAO\n" << std::endl;
}
