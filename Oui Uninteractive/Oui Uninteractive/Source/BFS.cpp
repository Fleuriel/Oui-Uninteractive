/**************************************************************************
 * @file BFS.cpp
 * @author HWANG Jing Rui, Austin
 * @par DP email: jingruiaustin.hwang@digipen.edu
 * @par Course:	CSD 2401
 * @par Software Engineering Project 3
 * @date 27-10-2023
 * @brief This file contains the definition of the Breadth-First Search
 *		  (BFS) pathfinding algorithm.
 *************************************************************************/
#include "BFS.h"
#include "ObjectFactory.h"
#include "PhysicsBody.h"
#include "Transform.h"

Node::Node(int x_, int y_, int parentX_ = -1, int parentY_ = -1) : x(x_), y(y_), parentX(parentX_), parentY(parentY_) {}

BFS::BFS(int r, int c) : rows(r), cols(c) {
    // Initialize containers
	for (int i{}; i < rows; ++i) {
        std::vector<int> gameMapVector;
        std::vector<bool> visitedVector;
        std::vector<Node> parentVector;
		
        for (int j{}; j < cols; ++j) {
			gameMapVector.push_back(0);
			visitedVector.push_back(false);
            parentVector.push_back(Node(-1, -1));
		}

		gameMap.push_back(gameMapVector);
		visited.push_back(visitedVector);
		parent.push_back(parentVector);
	}

    gridCreated = false;

    // Test walls
    gameMap[3][0] = 1;
    gameMap[1][1] = 1;
    gameMap[3][1] = 1;
    gameMap[0][2] = 1;
    gameMap[3][2] = 1;
    gameMap[3][3] = 1;
}

void BFS::CreateGrid() {
    // grid
    float windowWidth = 1920.f;
    float windowHeight = 1017.f;
	float scaleTemp = windowHeight / static_cast<float>(rows);

    for (int i{}; i < rows; ++i) {
        for (int j{}; j < cols; ++j) {
            if (gameMap[i][j] == 1) {
                // Create walls
                GameObject* wall = objectFactory->BuildObjectRunTime("Wall", "Wall");
                objectFactory->AddComponent(ComponentType::TRANSFORM, wall);

                wall->Initialize();

                // Set position of wall
                GET_COMPONENT(wall, Transform, ComponentType::TRANSFORM)->scale = scaleTemp;
                GET_COMPONENT(wall, Transform, ComponentType::TRANSFORM)->position.x = (j * scaleTemp) + (scaleTemp - windowWidth) / 2;
                GET_COMPONENT(wall, Transform, ComponentType::TRANSFORM)->position.y = (i * scaleTemp) + (scaleTemp - windowHeight) / 2;
            }
        }
    }

    gridCreated = true;
}

std::vector<Node> BFS::FindPath(int startX, int startY, int targetX, int targetY) {
    // Queue of nodes to determine path
    std::queue<Node> nodeQueue;

    // Path of nodes to follow
    std::vector<Node> path;

    // Add start node to queue
    Node startNode(startX, startY);
    nodeQueue.push(startNode);

    while (!nodeQueue.empty()) {
        Node currentNode(nodeQueue.front().x, nodeQueue.front().y, nodeQueue.front().parentX, nodeQueue.front().parentY);
        nodeQueue.pop();

        // If the current node is the end node
        if (currentNode.x == targetX && currentNode.y == targetY) {
            // Trace parent nodes to get the path
            while (!(currentNode.x == startNode.x && currentNode.y == startNode.y)) {
                path.push_back(currentNode);
                currentNode = parent[currentNode.y][currentNode.x];
            }
            path.push_back(startNode);

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
                int checkX = currentNode.x + neighbourX;
                int checkY = currentNode.y + neighbourY;

                // Ignore if neighbour check goes out of range
                if (checkX < 0 || checkX >= cols || checkY < 0 || checkY >= rows)
                    continue;

                // Ignore if neighbour is an obstacle (e.g. wall)
                if (gameMap[checkY][checkX] == 1)
                    continue;

                // Ignore if node has been visited
                if (visited[checkY][checkX])
                    continue;

                //---CORNER CHECKS---//
                // Top-left corner
                if (neighbourX == -1 && neighbourY == -1) {
                    // Edge on the right/bottom is an obstacle
                    if (gameMap[checkY][checkX + 1] == 1 || gameMap[checkY + 1][checkX] == 1)
                        continue;
                }

                // Top-right corner
                if (neighbourX == 1 && neighbourY == -1) {
                    // Edge on the left/bottom is an obstacle
                    if (gameMap[checkY][checkX - 1] == 1 || gameMap[checkY + 1][checkX] == 1)
                        continue;
                }

                // Bottom-left corner
                if (neighbourX == -1 && neighbourY == 1) {
                    // Edge on the top/right is an obstacle
                    if (gameMap[checkY - 1][checkX] == 1 || gameMap[checkY][checkX + 1] == 1)
                        continue;
                }

                // Bottom-right corner
                if (neighbourX == 1 && neighbourY == 1) {
                    // Edge on the top/left is an obstacle
                    if (gameMap[checkY - 1][checkX] == 1 || gameMap[checkY][checkX - 1] == 1)
                        continue;
                }
                //---CORNER CHECKS---//

                // Neighbour node has been visited and parent node is currennt node
				visited[checkY][checkX] = true;
				parent[checkY][checkX] = currentNode;

                // Add neighbouring node to node queue for further checking
                Node neighbourNode(checkX, checkY, currentNode.x, currentNode.y);
                nodeQueue.push(neighbourNode);
            }
        }
    }

    // Clear containers
    while (!nodeQueue.empty()) {
        nodeQueue.pop();
    }

    return path;
}

int BFS::GetRows() {
    return rows;
}

int BFS::GetCols() {
    return cols;
}

BFS::~BFS() {
	// Clear containers
    for (size_t i{}; i < gameMap.size(); ++i) {
        gameMap[i].clear();
    }
	gameMap.clear();
}
