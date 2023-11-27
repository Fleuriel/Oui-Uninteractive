/**************************************************************************
 * @file IScript.h
 * @author CHEAH Tristan Tze Hong
 * @par DP email: t.cheah@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 27-11-2023
 * @brief This file contains the declaration of the IScript Class to enable
 *		  Script transition between entities in the game.
 *************************************************************************/

#pragma once

#include <string>
class IScript {
public:

	/**************************************************************************
	* @brief Constructor
	*************************************************************************/
	IScript(std::string newName, bool gameplayFlag) {
		name = newName;
		isGameplay = gameplayFlag;
	};


	/**************************************************************************
	* @brief Initializes IScript System
	* @return void
	*************************************************************************/
	virtual void Initialize() {};

	/**************************************************************************
	* @brief Updates IScript System
	* @param size_t		Object ID
	* @return void
	*************************************************************************/
	virtual void Update(size_t) {};

	/**************************************************************************
	* @brief Ends IScript System
	* @return void
	*************************************************************************/
	virtual void End() {};

	/**************************************************************************
	* @brief Destructor
	*************************************************************************/
	virtual ~IScript() {};

	std::string name;

	bool isGameplay;
};