/**************************************************************************
 * @file TilemapLoader.h
 * @author HWANG Jing Rui, Austin - 100%
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
#include "ISystem.h"

extern std::pair<int, int> windowSize;

class TilemapLoader : public ISystem {
private:
	std::vector<std::vector<int>> tilemap;

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
	bool LoadTilemap(const std::string& filePath);

	/**************************************************************************
	* @brief Save tilemap to scene JSON file
	* @param filePath - path to scene JSON file
	* @return void
	*************************************************************************/
	rapidjson::Document SaveTilemap(const std::string& filePath);

	/**************************************************************************
	* @brief Clear tilemap
	* @return void
	*************************************************************************/
	void ClearTilemap();

	/**************************************************************************
	* @brief Get tilemap
	* @return std::vector<std::vector<int>> - tilemap
	*************************************************************************/
	std::vector<std::vector<int>> GetTilemap();

	/**************************************************************************
	* @brief Update tilemap loader
	* @param dt - delta time
	* @return void
	*************************************************************************/
	void Update(float dt);

	/**************************************************************************
	* @brief Create the grid
	* @return bool - true if grid is created, false otherwise
	*************************************************************************/
	bool CreateGrid();
};
extern TilemapLoader* tilemapLoader;

#endif
