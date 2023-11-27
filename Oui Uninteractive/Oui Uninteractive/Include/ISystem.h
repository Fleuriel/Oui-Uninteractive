/**************************************************************************
 * @file ISystem.h
 * @author HWANG Jing Rui, Austin - 100%
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

class ISystem {
public:
	IBroadcaster broadcaster;
	IObserver observer;

public:
	/**************************************************************************
	* @brief Constructor
	*************************************************************************/
	ISystem() : broadcaster{}, observer{} {};

	/**************************************************************************
	* @brief Initialize the current system (virtual, to be overridden)
	* @return void
	*************************************************************************/
	virtual void Initialize() {};

	/**************************************************************************
	* @brief Update the current system (virtual, to be overridden)
	* @param dt - delta-time
	* @return void
	*************************************************************************/
	virtual void Update(float dt) = 0;

	/**************************************************************************
	* @brief Destructor, terminate the current system (virtual, to be overridden)
	*************************************************************************/
	virtual ~ISystem() {};

	/**************************************************************************
	* @brief Register an observer to the current system
	* @param msg - name of message
	* @param ob - observer
	* @return void
	*************************************************************************/
	void RegisterObserver(const std::string& msg, IObserver* ob) {
		broadcaster.RegisterObserver(msg, ob);
	}

	/**************************************************************************
	* @brief Unregister an observer from the current system
	* @param msg - name of message
	* @param ob - observer
	* @return void
	*************************************************************************/
	void UnregisterObserver(const std::string& msg, IObserver* ob) {
		broadcaster.UnregisterObserver(msg, ob);
	}

	/**************************************************************************
	* @brief Send a message to the current system's observers
	* @param msg - pointer to IMessage object
	* @return void
	*************************************************************************/
	void SendToObservers(IMessage* msg) {
		broadcaster.SendToObservers(msg);
	}

	/**************************************************************************
	* @brief Add a message handler to the current system
	* @param msg - name of message
	* @param mh - message handler
	* @return void
	*************************************************************************/
	void AddMessageHandler(const std::string& msg, MessageHandler mh) {
		observer.AddMessageHandler(msg, mh);
	}
};

#endif
