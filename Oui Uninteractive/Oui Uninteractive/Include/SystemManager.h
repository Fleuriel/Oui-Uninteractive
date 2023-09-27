#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H
/**************************************************************************
 * @file SystemManager.h
 * @author CHEAH Tristan Tze Hong
 * @par DP email: t.cheah@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 27-09-2023
 * @brief This file contains the declaration of the System Manager class,
 *		  which handles the Initialize, Update and Cleanup of all ISystems.

 *************************************************************************/
#include <vector>
#include "ISystem.h"

class SystemManager {
public:
	/**************************************************************************
	* @brief Default constructor for SystemManager
	*************************************************************************/
	SystemManager();
	/**************************************************************************
	* @brief Destructor for SystemManager
	*************************************************************************/
	~SystemManager();
	/**************************************************************************
	* @brief Initializes the Systems in the System vector
	* @return void
	*************************************************************************/
	void Initialize();
	/**************************************************************************
	* @brief Runs the Update function for all the Systems
	* @param dt - delta time for updating
	* @return void
	*************************************************************************/
	void UpdateSystems(float dt);
	/**************************************************************************
	* @brief Add an ISystem object to System Vector
	* @param system - Pointer to the system to be added
	* @return void
	*************************************************************************/
	void AddSystem(ISystem* system);
	/**************************************************************************
	* @brief Runs the destructor for all systems
	* @return void
	*************************************************************************/
	void DestroySystem();
private:
	//Vector of Systems
	std::vector<ISystem*> Systems;
};
//Global Pointer
extern SystemManager* sysManager;

#endif
