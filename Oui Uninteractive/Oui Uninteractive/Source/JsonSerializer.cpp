/**************************************************************************
 * @file JsonSerializer.cpp
 * @author Mark Low
 * @par DP email: l.wangchunmark@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 15-09-2023
 * @brief This file contains the declaration of the JsonSerializer class
 *		  The functions include:
 *			- ReadJSONFile
 *			- WriteJSONFile
 *************************************************************************/
#include <iostream>
#include "JsonSerializer.h"

/**************************************************************************
* @brief Read JSON file
* @param filePath - directory of JSON file
* @param docRef - reference to rapidjson document
* @return bool - true if successful
*************************************************************************/
bool JsonSerializer::ReadJSONFile(const std::string& filePath, rapidjson::Document& docRef)
{
	// Open file
	std::ifstream file(filePath);

	// Check if file can be opened
	if (!file.is_open()) {
		std::cout << "JSON file not found." << std::endl;
		return false;
	}

	// Read the entire file content into a string
	std::string fileContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	// Close the file
	file.close();

	// Parse JSON data from the string
	docRef.Parse(fileContent.c_str());

	// Check for parsing errors
	if (docRef.HasParseError()) {
		std::cout << "Parsing error";
		return false;
	}

	return true; // Read successful
}

/**************************************************************************
* @brief Write to JSON file
* @param filePath - directory of JSON file
* @param docRef - reference to rapidjson document
* @return bool - true if successful
*************************************************************************/
bool JsonSerializer::WriteJSONFile(const std::string& filePath, rapidjson::Document& docRef)
{
	// Open file
	std::ofstream file(filePath);

	// Check if file can be opened
	if (!file.is_open()) {
		std::cout << "JSON file not found." << std::endl;
		return false;
	}

	// Setup stream and writer
	rapidjson::StringBuffer stringBuffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(stringBuffer);

	// Serialize JSON document to a string
	docRef.Accept(writer);

	// Write serialized data to output file
	file << stringBuffer.GetString() << std::endl;
	file.close();

	return true; // Write successful
}
