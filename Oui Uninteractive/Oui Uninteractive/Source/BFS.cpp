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
#include "Collider.h"
#include "PhysicsBody.h"

/**************************************************************************
* @brief Constructor for Node
* @param x_ - x-index of Node
* @param y_ - y-index of Node
* @param parentX_ - x-index of Node's parent
* @param parentY_ - y-index of Node's parent
*************************************************************************/
Node::Node(int x_, int y_, int parentX_ = -1, int parentY_ = -1) : x(x_), y(y_), parentX(parentX_), parentY(parentY_) {}

/**************************************************************************
* @brief Constructor
* @param r - rows of grid
* @param c - columns of grid
*************************************************************************/
/*BFS::BFS(int r, int c) : rows(r), cols(c) {
    // Initialize containers
    gameMap = std::vector<std::vector<int>>(rows, std::vector<int>(cols, 0));
    visited = std::vector<std::vector<bool>>(rows, std::vector<bool>(cols, false));
    parent = std::vector<std::vector<Node>>(rows, std::vector<Node>(cols, Node(-1, -1)));

    // Test walls
    gameMap[3][0] = 1;
    gameMap[1][1] = 1;
    gameMap[3][1] = 1;
    gameMap[0][2] = 1;
    gameMap[3][2] = 1;
    gameMap[3][3] = 1;
}*/
BFS::BFS(std::vector<std::vector<int>> tilemap) : rows{}, cols{}  {
    // Initialize containers
    for (size_t i{}; i < tilemap.size(); ++i) {
        std::vector<int> tilemapRow;
        for (size_t j{}; j < tilemap[i].size(); ++j) {
			tilemapRow.push_back(tilemap[i][j]);
        }

		gameMap.push_back(tilemapRow);
    }
	rows = static_cast<int>(gameMap.size());
	cols = static_cast<int>(gameMap[0].size());

    visited = std::vector<std::vector<bool>>(rows, std::vector<bool>(cols, false));
    parent = std::vector<std::vector<Node>>(rows, std::vector<Node>(cols, Node(-1, -1)));
}

/**************************************************************************
* @brief Destructor
*************************************************************************/
BFS::~BFS() {
    // Clear containers
    for (size_t i{}; i < gameMap.size(); ++i) {
        gameMap[i].clear();
    }
    gameMap.clear();
}

/**************************************************************************
* @brief Create the grid
* @return bool - true if grid is created, false otherwise
*************************************************************************/
bool BFS::CreateGrid() {
    // Check if a wall object already exists
	std::map<size_t, GameObject*> objFacMap{ objectFactory->GetGameObjectIDMap() };
    std::map<size_t, GameObject*>::iterator it{ objFacMap.begin()};

    bool wallFound{ false };
    while (it != objFacMap.end()) {
        if (it->second->GetName().find("Wall") != std::string::npos) {
            wallFound = true;
            break;
        }
        ++it;
    }

	// Do not create grid if wall object already exists
    if (wallFound)
        return false;

    // Temp vars
    float windowWidth = 1300.f;
    float windowHeight = 1016.f;
    float scaleX = windowWidth / static_cast<float>(cols);
    float scaleY = windowHeight / static_cast<float>(rows);

    // Wall ID
    int wallID{};

    // Instantiate walls
    for (int i{}; i < rows; ++i) {
        for (int j{}; j < cols; ++j) {
            if (gameMap[i][j] == 1) {
                // Create walls
                std::string wallName = "Wall" + std::to_string(wallID);
                GameObject* wall = objectFactory->BuildObjectRunTime(wallName, "Wall");
                objectFactory->AddComponent(ComponentType::TRANSFORM, wall);
                objectFactory->AddComponent(ComponentType::COLLIDER, wall);
                objectFactory->AddComponent(ComponentType::PHYSICS_BODY, wall);

                ++wallID;
                wall->Initialize();

                // Set position and collider size of wall
                GET_COMPONENT(wall, PhysicsBody, ComponentType::PHYSICS_BODY)->isStatic = true;
                GET_COMPONENT(wall, Collider, ComponentType::COLLIDER)->boundingbox->txPtr->scale.x = scaleX;
                GET_COMPONENT(wall, Collider, ComponentType::COLLIDER)->boundingbox->txPtr->scale.y = scaleY;
                GET_COMPONENT(wall, Transform, ComponentType::TRANSFORM)->scale.x = scaleX;
                GET_COMPONENT(wall, Transform, ComponentType::TRANSFORM)->scale.y = scaleY;
                GET_COMPONENT(wall, Transform, ComponentType::TRANSFORM)->position.x = (j * scaleX) + (scaleX - windowWidth) / 2;
                GET_COMPONENT(wall, Transform, ComponentType::TRANSFORM)->position.y = (i * scaleY) + (scaleY - windowHeight) / 2;
            }
        }
    }

    return true;
}

/**************************************************************************
* @brief Find the path using Breadth-First Search algorithm
* @param startX - x-index of start node
* @param startY - y-index of start node
* @param targetX - x-index of target node
* @param targetY - y-index of target node
* @return std::vector<Node> - vector of nodes in the path
*************************************************************************/
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

/**************************************************************************
* @brief Get rows of grid
* @return int - rows of grid
*************************************************************************/
int BFS::GetRows() {
    return rows;
}

/**************************************************************************
* @brief Get columns of grid
* @return int - columns of grid
*************************************************************************/
int BFS::GetCols() {
    return cols;
}

/**************************************************************************
* @brief Get game map
* @return int - columns of grid
*************************************************************************/
std::vector<std::vector<int>> BFS::GetGameMap() {
    return gameMap;
}

/**************************************************************************
* @brief Reset the gameMap, visited and parent containers
* @return void
*************************************************************************/
void BFS::Reset() {
    // Reset visited and parent containers
	for (int i{}; i < visited.size(); ++i) {
		visited[i].clear();
	}
	visited.clear();

	for (int i{}; i < parent.size(); ++i) {
		parent[i].clear();
	}
	parent.clear();

    // Initialize containers
    visited = std::vector<std::vector<bool>>(rows, std::vector<bool>(cols, false));
    parent = std::vector<std::vector<Node>>(rows, std::vector<Node>(cols, Node(-1, -1)));
}
