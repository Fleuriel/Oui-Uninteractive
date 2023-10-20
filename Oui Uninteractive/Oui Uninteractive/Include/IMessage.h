/**************************************************************************
 * @file IMessage.h
 * @author HWANG Jing Rui, Austin
 * @par DP email: jingruiaustin.hwang@digipen.edu
 * @par Course:	CSD 2401
 * @par Software Engineering Project 3
 * @date 09-10-2023
 * @brief
 *************************************************************************/
#ifndef IMESSAGE_H
#define IMESSAGE_H

#include <string>
#include <map>
#include <vector>

enum class MessageType
{
	MSG_NONE = 0,
	MSG_QUIT,
	MSG_COLLISION
};

class IMessage {
private:
	//MessageType messageID;
	std::string messageID;

public:
	//IMessage(MessageType message) : messageID(message) {}
	IMessage(const std::string& message) : messageID(message) {}
	virtual ~IMessage() {}

	std::string GetMessageID() { return messageID; }
};

// Define a message handler
typedef void (*MessageHandler)(IMessage* msg);

class IObserver {
private:
	std::string messageID;
	std::map<std::string, MessageHandler> messageHandlerMap;

public:
	IObserver() {}
	~IObserver() {}

	//void HandleMessage() {}
	void AddMessageHandler(const std::string& message, MessageHandler mh) { messageHandlerMap.emplace(message, mh); }
	void RemoveMessageHandler(const std::string& message) { messageHandlerMap.erase(message); }
	MessageHandler GetMessageHandler(const std::string& message) { return messageHandlerMap[message]; }
};

class IBroadcaster {
private:
	std::string messageID;
	//std::map<IObserver* , std::string> observerMap;
	std::multimap<std::string, IObserver*> observerMap;
	//std::vector<IObserver*> observersList;

public:
	IBroadcaster() {}
	~IBroadcaster() {}

	/*void RegisterObserver(IObserver* observer, const std::string& message) { 
		observerMap.emplace(observer, message); 
	}*/

	void RegisterObserver(const std::string& message, IObserver* observer) {
		observerMap.emplace(message, observer);
	}

	//void UnregisterObserver(IObserver* observer) { observerMap.erase(observer); }
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

	void SendToObservers(IMessage* msg) { msg = nullptr; }

	void ProcessMessage(IMessage* msg) { msg = nullptr; }

	/*virtual void RegisterObserver(const std::string& message, IObserver* observer) = 0;
	virtual void UnregisterObserver(std::string message, IObserver* observer) = 0;
	virtual void SendToObservers(IMessage* msg) = 0;
	virtual void ProcessMessage(IMessage* msg) = 0;*/
};

#endif
