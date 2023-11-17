/**************************************************************************
 * @file TilemapLoader.cpp
 * @author HWANG Jing Rui, Austin
 * @par DP email: jingruiaustin.hwang@digipen.edu
 * @par Course:	CSD 2401
 * @par	Software Engineering Project 3
 * @date 17-11-2023
 * @brief This file contains the declaration of the TilemapLoader class.
 *************************************************************************/
#ifndef TILEMAP_LOADER_H
#define TILEMAP_LOADER_H

#include <string>
#include <map>

class TilemapLoader {
private:


public:
	/**************************************************************************
	* @brief Constructor and Destructor
	*************************************************************************/
	TilemapLoader();
	~TilemapLoader();

	/**************************************************************************
	* @brief Load tilemap from scene JSON file
	* @param filePath - path to scene JSON file
	* @param tilemap - tilemap to be set
	* @return bool - true if tilemap is loaded, false otherwise
	*************************************************************************/
	bool LoadTilemap(const std::string& filePath, std::vector<std::vector<int>>& tilemap);

	/**************************************************************************
	* @brief Save tilemap to scene JSON file
	* @param filePath - path to scene JSON file
	* @return void
	*************************************************************************/
	void SaveTilemap(const std::string& filePath);
};
extern TilemapLoader* tilemapLoader;

#endif
