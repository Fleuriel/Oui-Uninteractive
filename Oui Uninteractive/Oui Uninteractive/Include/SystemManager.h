#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

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
