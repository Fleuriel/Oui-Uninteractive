/**************************************************************************
 * @file IMessage.h
 * @author HWANG Jing Rui, Austin - 100%
 * @par DP email: jingruiaustin.hwang@digipen.edu
 * @par Course:	CSD 2401
 * @par Software Engineering Project 3
 * @date 09-10-2023
 * @brief This file contains the interfaces for Message, Observer
 * 		  and Broadcaster.
 *************************************************************************/
#ifndef IMESSAGE_H
#define IMESSAGE_H

#include <string>
#include <map>
#include <vector>

class IMessage {
private:
	std::string messageID;

public:
	/**************************************************************************
	* @brief IMessage constructor
	* @param message - name of message
	*************************************************************************/
	IMessage(const std::string& message) : messageID(message) {}

	/**************************************************************************
	* @brief Virtual destructor
	*************************************************************************/
	virtual ~IMessage() {}

	/**************************************************************************
	* @brief Return the component type
	* @param typeID - component type
	* @return T* - component type
	*************************************************************************/
	std::string GetMessageID() { 
		return messageID; 
	}
};

// Define a message handler
typedef void (*MessageHandler)(IMessage*);

class IObserver {
private:
	std::string messageID;
	std::map<std::string, MessageHandler> messageHandlerMap;

public:
	/**************************************************************************
	* @brief IObserver default constructor
	*************************************************************************/
	IObserver() {}

	/**************************************************************************
	* @brief IObserver value constructor
	* @param id - name of message
	*************************************************************************/
	IObserver(const std::string& id) : messageID(id) {}

	/**************************************************************************
	* @brief IObserver destructor
	*************************************************************************/
	~IObserver() {}

	/**************************************************************************
	* @brief Add a message handler to handle the specified message
	* @param message - name of message
	* @param mh - message handler
	* @return void
	*************************************************************************/
	void AddMessageHandler(const std::string& message, MessageHandler mh) {
		messageHandlerMap.emplace(message, mh); 
	}

	/**************************************************************************
	* @brief Remove a specified message handler
	* @param message - name of message
	* @return void
	*************************************************************************/
	void RemoveMessageHandler(const std::string& message) { 
		messageHandlerMap.erase(message);
	}

	/**************************************************************************
	* @brief Get a specified message handler
	* @param message - name of message
	* @return message handler
	*************************************************************************/
	MessageHandler GetMessageHandler(const std::string& message) { 
		return messageHandlerMap[message]; 
	}
};

class IBroadcaster {
private:
	std::string messageID;
	std::multimap<std::string, IObserver*> observerMap;

public:
	/**************************************************************************
	* @brief IBroadcaster constructor
	*************************************************************************/
	IBroadcaster() {}

	/**************************************************************************
	* @brief IObserver destructor
	*************************************************************************/
	~IBroadcaster() {}

	/**************************************************************************
	* @brief Register an observer
	* @param message - name of message
	* @param observer - pointer to observer
	* @return void
	*************************************************************************/
	// Broadcaster to register observer
	void RegisterObserver(const std::string& message, IObserver* observer) {
		observerMap.emplace(message, observer);
	}

	/**************************************************************************
	* @brief Unregister an observer
	* @param message - name of message
	* @param observer - pointer to observer
	* @return void
	*************************************************************************/
	void UnregisterObserver(std::string message, IObserver* observer) {
		typedef std::multimap<std::string, IObserver*>::iterator iterator;
		std::pair<iterator, iterator> itPair = observerMap.equal_range(message);

		iterator it = itPair.first;
		for (; it != itPair.second; ++it) {
			if (it->second == observer) {
				observerMap.erase(it);
				break;
			}
		}
	}

	/**************************************************************************
	* @brief Send a message to all observers
	* @param msg - pointer to message
	* @return void
	*************************************************************************/
	void SendToObservers(IMessage* msg) {
		// Send message to observers who subscribed to specified message
		typedef std::multimap<std::string, IObserver*>::iterator iterator;
		std::pair<iterator, iterator> itPair = observerMap.equal_range(msg->GetMessageID());

		iterator it = itPair.first;
		for (; it != itPair.second; ++it) {
			// Call the function pointed to by GetMessageHandler
			it->second->GetMessageHandler(msg->GetMessageID())(msg);
		}
	}
};

#endif
