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
	// Coordinates of Node and its parent
    int x, y;
    int parentX, parentY;

    /**************************************************************************
    * @brief Constructor for Node
    * @param x_ - x-index of Node
    * @param y_ - y-index of Node
    * @param parentX_ - x-index of Node's parent
    * @param parentY_ - y-index of Node's parent
    *************************************************************************/
    Node(int x_, int y_, int parentX_, int parentY_);
};

class BFS {
private:
	// Rows and columns of grid
    int rows;
    int cols;

    // Wall ID
    int wallID;

	// Grid of ints
    std::vector<std::vector<int>> gameMap;

    // Vector of bool to represent nodes that have been visited
    std::vector<std::vector<bool>> visited;

    // Vector of parent nodes
    std::vector<std::vector<Node>> parent;

public:
    // Check if the grid has been created
    bool gridCreated;

    /**************************************************************************
    * @brief Constructor
    * @param r - rows of grid
    * @param c - columns of grid
    *************************************************************************/
    BFS(int r, int c);

    /**************************************************************************
    * @brief Destructor
    *************************************************************************/
	~BFS();

    /**************************************************************************
    * @brief Create the grid
    * @return void
    *************************************************************************/
    void CreateGrid();

    /**************************************************************************
    * @brief Find the path using Breadth-First Search algorithm
	* @param startX - x-index of start node
	* @param startY - y-index of start node
	* @param targetX - x-index of target node
	* @param targetY - y-index of target node
	* @return std::vector<Node> - vector of nodes in the path
    *************************************************************************/
    std::vector<Node> FindPath(int startX, int startY, int targetX, int targetY);

    /**************************************************************************
	* @brief Get rows of grid
	* @return int - rows of grid
    *************************************************************************/
    int GetRows();
    
    /**************************************************************************
	* @brief Get columns of grid
	* @return int - columns of grid
    *************************************************************************/
    int GetCols();

    /**************************************************************************
    * @brief Get game map
    * @return std::vector<std::vector<int>>
    *************************************************************************/
    std::vector<std::vector<int>> GetGameMap();

    /**************************************************************************
    * @brief Reset the gameMap, visited and parent containers
    * @return void
    *************************************************************************/
    void Reset();
};

#endif
