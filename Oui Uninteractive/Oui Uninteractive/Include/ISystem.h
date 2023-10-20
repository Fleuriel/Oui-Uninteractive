/**************************************************************************
 * @file ISystem.h
 * @author HWANG Jing Rui, Austin
 * @par DP email: jingruiaustin.hwang@digipen.edu
 * @par Course: CSD 2401
 * @par	Software Engineering Project 3
 * @date 08-09-2023
 * @brief This file contains the declaration of the ISystem class, which 
 *		  is the interface for systems to be implemented in the game.
 *************************************************************************/
#ifndef ISYSTEM_H
#define ISYSTEM_H

#include "IMessage.h"

class ISystem : public IBroadcaster {
public:
	// Initialize the system
	virtual void Initialize() {};

	// Update the system
	virtual void Update(float dt) = 0;

	// Terminate the system
	virtual ~ISystem() {};

	/*----------TESTING MESSAGING SYSTEM----------*/
	/*virtual void RegisterObserver(IObserver* observer) = 0;
	virtual void UnregisterObserver(IObserver* observer) = 0;
	virtual void NotifyObservers(IMessage* msg) = 0;*/

	/*void RegisterObserver(const std::string& message, IObserver* observer) override {

	}

	virtual void UnregisterObserver(std::string message, IObserver* observer) override {

	}

	virtual void SendToObservers(IMessage* msg) override {

	}

	virtual void ProcessMessage(IMessage* msg) override {

	}*/

	/*----------TESTING MESSAGING SYSTEM----------*/
};

#endif
