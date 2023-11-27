/**************************************************************************
 * @file TilemapLoader.cpp
 * @author HWANG Jing Rui, Austin - 100%
 * @par DP email: jingruiaustin.hwang@digipen.edu
 * @par Course:	CSD 2401
 * @par	Software Engineering Project 3
 * @date 17-11-2023
 * @brief This file contains the definition of the TilemapLoader class.
 *************************************************************************/
#include <iostream>
#include "JsonSerializer.h"
#include "TilemapLoader.h"
#include "ObjectFactory.h"
#include "PhysicsBody.h"
#include "Collider.h"

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
	for (size_t i{}; i < tilemap.size(); i++) {
		tilemap[i].clear();
	}
	tilemap.clear();
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
rapidjson::Document TilemapLoader::SaveTilemap(const std::string& filePath) {
	rapidjson::Document objDoc;
	rapidjson::Document::AllocatorType& allocator = objDoc.GetAllocator();
	JsonSerializer serializer;
	serializer.ReadJSONFile(filePath, objDoc);

	// Setting object for output JSON
	objDoc.SetObject();

	// Add rows to Tilemap array
	rapidjson::Value tilemapArray(rapidjson::kArrayType);
	for (auto rowIt{ tilemap.rbegin() }; rowIt != tilemap.rend(); ++rowIt) {
		std::vector<int> row{ *rowIt };

		// Add column data to Row array
		rapidjson::Value rowArray(rapidjson::kArrayType);
		for (int const& col : row) {
			rapidjson::Value colValue;
			colValue.SetInt(col);
			rowArray.PushBack(colValue, allocator);
		}
		
		tilemapArray.PushBack(rowArray, allocator);
	}

	// Add Tilemap array to output JSON
	objDoc.AddMember("Tilemap", tilemapArray, allocator);

	return objDoc;
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
	if (sysManager->isPaused == false) {
		(void)dt;
	}
}

/**************************************************************************
* @brief Create the grid
* @return bool - true if grid is created, false otherwise
*************************************************************************/
bool TilemapLoader::CreateGrid() {
	// Return false if there is no tilemap
	if (tilemap.size() == 0)
		return false;
	if (tilemap[0].size() == 0)
		return false;

	// Get number of rows and columns
	int rows{ static_cast<int>(tilemap.size()) };
	int cols{ static_cast<int>(tilemap[0].size()) };

	// Store window width/height and scale factor
	float windowWidth{ static_cast<float>(windowSize.first) };
	float windowHeight{ static_cast<float>(windowSize.second) };
	float scaleX{ windowWidth / static_cast<float>(cols) };
	float scaleY{ windowHeight / static_cast<float>(rows) };

	// Wall ID
	int wallID{};

	// Instantiate walls
	for (int i{}; i < rows; ++i) {
		for (int j{}; j < cols; ++j) {
			if (tilemap[i][j] == 1) {
				// Create walls
				std::string wallName = "Wall" + std::to_string(wallID);
				GameObject* wall{ objectFactory->BuildObjectFromPrefab(wallName, "WallPrefab") };
				++wallID;

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
