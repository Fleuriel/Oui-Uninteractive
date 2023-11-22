/**************************************************************************
 * @file TilemapLoader.cpp
 * @author HWANG Jing Rui, Austin
 * @par DP email: jingruiaustin.hwang@digipen.edu
 * @par Course:	CSD 2401
 * @par	Software Engineering Project 3
 * @date 17-11-2023
 * @brief This file contains the definition of the TilemapLoader class.
 *************************************************************************/
#include <iostream>
#include "JsonSerializer.h"
#include "TilemapLoader.h"

TilemapLoader* tilemapLoader = NULL;

/**************************************************************************
* @brief Constructor
*************************************************************************/
TilemapLoader::TilemapLoader() {
	tilemapLoader = this;
}

/**************************************************************************
* @brief Destructor
*************************************************************************/
TilemapLoader::~TilemapLoader() {

}

/**************************************************************************
* @brief Load tilemap from scene JSON file
* @param filePath - path to scene JSON file
* @param tilemap - tilemap to be set
* @return bool - true if tilemap is loaded, false otherwise
*************************************************************************/
bool TilemapLoader::LoadTilemap(const std::string& filePath) {
	if (tilemap.size() > 0) {
		ClearTilemap();
	}

	// Create rapidjson doc object and serializer
	rapidjson::Document objDoc;
	JsonSerializer serializer;
	std::string componentName;

	// Read data from file
	if (serializer.ReadJSONFile(filePath, objDoc)) {
		// Return false if file has no tilemap
		if (!objDoc.HasMember("Tilemap")) {
			std::cerr << "File does not contain tilemap." << std::endl;
			return false;
		}

		// For each row array in tilemap array
		for (auto& row : objDoc["Tilemap"].GetArray()) {
			std::vector<int> tilemapRow;
			
			// For each column in row array
			for (auto& col : row.GetArray()) {
				tilemapRow.push_back(col.GetInt());
			}

			tilemap.push_back(tilemapRow);
		}

		std::reverse(tilemap.begin(), tilemap.end());

		return true;
	}
	else {
		std::cerr << "Failed to load tilemap data." << std::endl;
		return false;
	}
}

/**************************************************************************
* @brief Save tilemap to scene JSON file
* @param filePath - path to scene JSON file
* @return void
*************************************************************************/
void TilemapLoader::SaveTilemap(const std::string& filePath) {

}

/**************************************************************************
* @brief Clear tilemap
* @return void
*************************************************************************/
void TilemapLoader::ClearTilemap() {
	for (size_t i{}; i < tilemap.size(); i++) {
		tilemap[i].clear();
	}
	tilemap.clear();
}

/**************************************************************************
* @brief Get tilemap
* @return std::vector<std::vector<int>> - tilemap
*************************************************************************/
std::vector<std::vector<int>> TilemapLoader::GetTilemap() {
	return tilemap;
}

/**************************************************************************
* @brief Update tilemap loader
* @param dt - delta time
* @return void
*************************************************************************/
void TilemapLoader::Update(float dt) {
	(void)dt;
}