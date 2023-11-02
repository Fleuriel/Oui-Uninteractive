/**************************************************************************
 * @file BFS.h
 * @author HWANG Jing Rui, Austin
 * @par DP email: jingruiaustin.hwang@digipen.edu
 * @par Course:	CSD 2401
 * @par Software Engineering Project 3
 * @date 27-10-2023
 * @brief This file contains the declaration of the Breadth-First Search
 *		  (BFS) pathfinding algorithm.
 *************************************************************************/
#ifndef BFS_H
#define BFS_H

#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

struct Node {
    int x, y;
    int parentX, parentY;

    // Node constructor
    Node(int x_, int y_, int parentX_, int parentY_);
};

class BFS {
private:
	// Rows and columns of grid
    int rows;
    int cols;

	// Grid of ints
    std::vector<std::vector<int>> gameMap;

    // Vector of bool to represent nodes that have been visited
    std::vector<std::vector<bool>> visited;

    // Vector of parent nodes
    std::vector<std::vector<Node>> parent;

public:
    BFS(int r, int c);
	~BFS();

    bool gridCreated;

    void CreateGrid();
    std::vector<Node> FindPath(int startX, int startY, int targetX, int targetY);
    void FollowPath(std::vector<Node> p, size_t gameObjectID);

    int GetRows();
    int GetCols();
};

#endif
