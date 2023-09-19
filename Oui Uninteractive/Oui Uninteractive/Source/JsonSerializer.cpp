/**************************************************************************
 * @file		  JsonSerializer.cpp
 * @author
 * @par DP email:
 * @par Course:	  CSD 2401
 * @par			  Software Engineering Project 3
 * @date		  09-15-2023
 * @brief
 *************************************************************************/
#include <iostream>
#include "JsonSerializer.h"

void JsonSerializer::Init()
{
	// Define path
	/*const char* filePath = "../Editor/objekt.json";

	// Create rapidjson doc object
	rapidjson::Document objDoc;
	// Read data from file
	if (ReadJSONFile(filePath, objDoc)) { // Printing out to console to see
		tempObjList.name = objDoc["name"].GetString();
		std::cout << objDoc["name"].GetString() << std::endl;
		tempObjList.size = objDoc["size"].GetInt();
		std::cout << objDoc["size"].GetInt() << std::endl;
		tempObjList.colour = objDoc["colour"].GetString();
		std::cout << objDoc["colour"].GetString() << std::endl;
		tempObjList.smell = objDoc["smell"].GetFloat();
		std::cout << objDoc["smell"].GetFloat() << std::endl;
		tempObjList.alive = objDoc["alive"].GetBool();
		std::cout << objDoc["alive"].GetBool() << std::endl;
	}
	// Simulate size change
	int finalSize = tempObjList.size *= 2;
	objDoc["size"] = finalSize;

	if (WriteJSONFile(filePath, objDoc)) {
		std::cout << "If you open the file again and see the size double then Yay everything works";
	}*/
}

//void JsonSerializer::InitObjects(const std::string& filePath) {
//	// Create rapidjson doc object
//	rapidjson::Document objDoc;
//	// Read the scene file
//	if (ReadJSONFile(filePath, objDoc)) {
//		std::cout << objDoc["ObjectCount"].GetInt();
//	}
//	
//
//}

// Read JSON file. Returns true if successful.
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

// Write to JSON file. Returns true if successful.
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
