/**************************************************************************
* @file IScript.h
* @author CHEAH Tristan Tze Hong - 100%
* @par DP email: t.cheah@digipen.edu
* @par Course:	CSD 2401
* @par Software Engineering Project 3
* @date 06-10-2023
* @brief This file contains the script interface.
*************************************************************************/
#ifndef ISCRIPT_H
#define ISCRIPT_H

#include <string>

class IScript {
public:
	IScript(std::string newName, bool gameplayFlag) {
		name = newName;
		isGameplay = gameplayFlag;
	};
	virtual void Initialize() {};
	virtual void Update(size_t) {};
	virtual void End() {};
	virtual ~IScript() {};
	std::string name;
	bool isGameplay;
};

#endif
