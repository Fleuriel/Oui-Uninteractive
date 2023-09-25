/**************************************************************************
 * @file		  JsonSerializer.h
 * @author
 * @par DP email:
 * @par Course:	  CSD 2401
 * @par			  Software Engineering Project 3
 * @date		  09-15-2023
 * @brief
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
	void Init();
	bool ReadJSONFile(const std::string& filePath, rapidjson::Document& docRef);
	bool WriteJSONFile(const std::string& filePath, rapidjson::Document& docRef);
};

#endif
