/**************************************************************************
 * @file JsonSerializer.h
 * @author 
 * @par DP email: 
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 15-09-2023
 * @brief This file contains the declaration of the JsonSerializer class
 *		  The functions include:
 *			- ReadJSONFile
 *			- WriteJSONFile
 *************************************************************************/
#ifndef JSON_SERIALIZER_H
#define JSON_SERIALIZER_H

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/filewritestream.h"
#include <vector>
#include <fstream>

class JsonSerializer {
public:
	/**************************************************************************
	* @brief Read JSON file
	* @param filePath - directory of JSON file
	* @param docRef - reference to rapidjson document
	* @return bool - true if successful
	*************************************************************************/
	bool ReadJSONFile(const std::string& filePath, rapidjson::Document& docRef);

	/**************************************************************************
	* @brief Write to JSON file
	* @param filePath - directory of JSON file
	* @param docRef - reference to rapidjson document
	* @return bool - true if successful
	*************************************************************************/
	bool WriteJSONFile(const std::string& filePath, rapidjson::Document& docRef);
};

#endif
