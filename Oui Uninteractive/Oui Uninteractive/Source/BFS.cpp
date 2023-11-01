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
#include "Transform.h"

Node::Node(int x_, int y_, Node* parent_ = nullptr) : x(x_), y(y_), parent(parent_) {}

BFS::BFS(int r, int c) : rows(r), cols(c) {
    gameMap = std::vector<std::vector<int>>(rows, std::vector<int>(cols, 0));
    gridCreated = false;
}

void BFS::CreateGrid() {
    // grid
    float windowWidth = 1920.f;
    float windowHeight = 1017.f;
	float scaleTemp = windowHeight / static_cast<float>(rows);
    //float scaleTemp = 300.f;

    for (int i{}; i < rows; ++i) {
        for (int j{}; j < cols; ++j) {
            // Create walls
            GameObject* wall = objectFactory->BuildObjectRunTime("Wall", "Wall");
            objectFactory->AddComponent(ComponentType::TRANSFORM, wall);

            wall->Initialize();

            // Set position of wall
            GET_COMPONENT(wall, Transform, ComponentType::TRANSFORM)->scale = scaleTemp;
            GET_COMPONENT(wall, Transform, ComponentType::TRANSFORM)->position.x = j * scaleTemp + scaleTemp / 2 - windowWidth / 2;
            GET_COMPONENT(wall, Transform, ComponentType::TRANSFORM)->position.y = i * scaleTemp + scaleTemp / 2 - windowHeight / 2;
        }
    }

    gridCreated = true;
}

std::vector<Node> BFS::FindPath(int startX, int startY, int targetX, int targetY) {
    // Test walls
    /*gameMap[0][3] = 1;
    gameMap[1][2] = 1;
    gameMap[1][3] = 1;
    gameMap[2][3] = 1;
    gameMap[3][1] = 1;
    gameMap[3][2] = 1;
    gameMap[3][3] = 1;*/

    // Queue of nodes to determine path
    //std::queue<Node> nodeQueue;
    std::queue<Node> nodeQueue;

    // Path of nodes to follow
    //std::vector<Node*> path;
    std::vector<Node> path;

    // Start/end nodes
    Node startNode(startX, startY);

    std::vector<std::vector<int>> parentIndices(rows, std::vector<int>(cols, -1));


    nodeQueue.push(startNode);

    while (!nodeQueue.empty()) {
        Node currentNode{ nodeQueue.front() };
        nodeQueue.pop();

        // If the current node is the end node
        if (currentNode.x == targetX && currentNode.y == targetY) {
            // Trace parent nodes to get the path

            int currentIdx = currentNode.y * cols + currentNode.x;
            while (currentIdx != -1) {
                int parentX = currentIdx % cols;
                int parentY = currentIdx / cols;
                path.push_back(Node(parentX, parentY));
                currentIdx = parentIndices[parentY][parentX];
            }

            /*Node current = currentNode;
            while (current.parent != nullptr) {
                path.push_back(currentNode);
                currentNode = *currentNode.parent;
            }*/

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
                //Node n(currentNode->x, currentNode->y, currentNode->parent);
				//Node neighbourNode(checkX, checkY, &currentNode);
                
                Node neighbourNode(checkX, checkY);
				neighbourNode.parent = &currentNode;

                /*Node* neighbourNode{ new Node(checkX, checkY) };
                neighbourNode->parent = currentNode;*/

                // Add to node queue for further checking
                nodeQueue.push(neighbourNode);
            }
        }
    }

    while (!nodeQueue.empty()) {
        //delete nodeQueue.front();
        nodeQueue.pop();
    }

    return path;
}

void BFS::FollowPath(std::vector<Node> p) {
    //for (Node pathNode : p) {
    //    // Set target to pathNode
    //}
}

BFS::~BFS() {
	// Clear gameMap
    for (size_t i{}; i < gameMap.size(); ++i) {
        gameMap[i].clear();
    }
	gameMap.clear();

    // Erase nodes in nodeQueue


    // Erase nodes in path
	/*for (auto node : path) {
		delete node;
	}*/
    //for (int i{ (int)path.size() - 1 }; i >= 0; --i) {
    //    path[i]->next = nullptr;
    //    delete path[i];
    ////	//delete path[i];
    //}

    // DONT PUSH, MEMORY LEAKS
 //   for (size_t i{}; i < path.size(); ++i) {
	//	//delete path[i];
	//}
}
