/**************************************************************************
 * @file IMessage.h
 * @author HWANG Jing Rui, Austin
 * @par DP email: jingruiaustin.hwang@digipen.edu
 * @par Course:	CSD 2401
 * @par Software Engineering Project 3
 * @date 26-10-2023
 * @brief
 *************************************************************************/
#ifndef ISTATE_H
#define ISTATE_H

class IState
{
public:
	virtual void Enter() = 0;
	virtual void Update() = 0;
	virtual void Exit() = 0;

	virtual ~IState() {};
};

#endif
