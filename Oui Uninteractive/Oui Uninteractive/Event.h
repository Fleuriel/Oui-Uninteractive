/**************************************************************************
 * @file		  Event.h
 * @author		  
 * @par DP email: 
 * @par Course:	  CSD 2401
 * @par			  Software Engineering Project 3
 * @date		  09-08-2023
 * @brief
 *************************************************************************/
#pragma once

enum class EventType
{
	None = 0,
	Quit,
	Collide
	/*None,
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
