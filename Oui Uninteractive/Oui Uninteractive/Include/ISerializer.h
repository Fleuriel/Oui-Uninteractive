#pragma once

#include <string>

class ISerializer {
public:
	// Open serialization stream from a file
	virtual bool IsOpen(const std::string& fileName) = 0;

	// Check whether the stream is good
	virtual bool IsGood() = 0;

	// Virtual functions to read data types
	virtual void ReadInt(int& i) = 0;
	virtual void ReadFloat(float& f) = 0;
	virtual void ReadString(std::string& str) = 0;
};

