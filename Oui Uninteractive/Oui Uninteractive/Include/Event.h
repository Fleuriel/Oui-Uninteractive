/**************************************************************************
 * @file		  Event.h
 * @author		  
 * @par DP email: 
 * @par Course:	  CSD 2401
 * @par			  Software Engineering Project 3
 * @date		  09-08-2023
 * @brief
 *************************************************************************/
#ifndef EVENT_H
#define EVENT_H

enum class EventType
{
	NONE = 0,
	Quit,
	Collide
	/*NONE,
	WindowClose,
	WindowResize,
	WindowFocus,
	WindowLostFocus,
	WindowMoved,
	KeyPressed,
	KeyReleased,
	KeyTyped,
	MouseButtonPressed,
	MouseButtonReleased,
	MouseMoved,
	MouseScrolled*/
};

class Event {
private:
	EventType eventID;

public:
	Event(EventType event) : eventID(event) {}
	~Event() {}
};

#endif
