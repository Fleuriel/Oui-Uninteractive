#include "SystemManager.h"

//Global pointer 
SystemManager* sysManager;
/**************************************************************************
* @brief Default constructor for SystemManager
*************************************************************************/
SystemManager::SystemManager() {
	sysManager = this;
}
/**************************************************************************
* @brief Destructor for SystemManager
*************************************************************************/
SystemManager::~SystemManager() {

}
/**************************************************************************
* @brief Initializes the Systems in the System vector
* @return void
*************************************************************************/
void SystemManager::Initialize() {
	for (int i = 0; i < Systems.size(); i++) {
		Systems[i]->Initialize();
	}
}
/**************************************************************************
* @brief Runs the Update function for all the Systems
* @param dt - delta time for updating
* @return void
*************************************************************************/
void SystemManager::UpdateSystems(float dt) {
	for (int i = 0; i < Systems.size(); i++) {
		Systems[i]->Update(dt);
	}
}
/**************************************************************************
* @brief Add an ISystem object to System Vector
* @param system - Pointer to the system to be added
* @return void
*************************************************************************/
void SystemManager::AddSystem(ISystem* system) {
	Systems.push_back(system);

}
/**************************************************************************
* @brief Runs the destructor for all systems
* @return void
*************************************************************************/
void SystemManager::DestroySystem() {
	for (int i = 0; i < Systems.size(); i++) {
		delete Systems[Systems.size() - i - 1];
	}
}