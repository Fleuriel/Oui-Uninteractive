/**************************************************************************
 * @file		  JsonSerializer.h
 * @author
 * @par DP email:
 * @par Course:	  CSD 2401
 * @par			  Software Engineering Project 3
 * @date		  09-15-2023
 * @brief
 *************************************************************************/
#pragma once

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



/*
#include "ISerializer.h"

class JsonSerializer : public ISerializer {
	// Open serialization stream from a file
	virtual bool IsOpen(const std::string& fileName) = 0;

	// Check whether the stream is good
	virtual bool IsGood() = 0;

	// Virtual functions to read data types
	virtual void ReadInt(int& i) = 0;
	virtual void ReadFloat(float& f) = 0;
	virtual void ReadString(std::string& str) = 0;
};
*/