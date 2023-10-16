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
//#include <map>
#include <vector>

enum class MessageType
{
	MSG_NONE = 0,
	MSG_QUIT,
	MSG_COLLISION
};

class IMessage {
private:
	MessageType messageID;

public:
	IMessage(MessageType message) : messageID(message) {}
	virtual ~IMessage() {}
};

class IBroadcaster {
private:
	std::string message;

	//std::map
	std::vector<IObserver*> observersList;

public:
	IBroadcaster() {}
	~IBroadcaster() {}

	void RegisterObserver(IObserver* observer);
	void SendToObservers();
	void UnregisterObserver();
	void ProcessMessage();
};

class IObserver {
private:
	std::string message;

public:
	IObserver() {}
	~IObserver() {}

	void HandleMessage();
};

#endif
