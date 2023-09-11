/**************************************************************************
 * @file InitializeEngine.h
 * @author 
 * @par DP email: 
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 09-05-2023
 * @brief 
 *************************************************************************/

#ifndef GAME_STATE_MGR_H
#define GAME_STATE_MGR_H

#include <InputKeys.h>
#include <OpenGLApplication.h>
#include <OpenGLObjects.h>
#include <OpenGLShaders.h>



extern unsigned int InitializationGameState;
extern unsigned int CurrentGameState;
extern unsigned int PreviousGameState;
extern unsigned int NextGameState;

extern void (*CreateWindow)(unsigned short width, unsigned short height);
extern void (*WindowCleanup)();
extern void (*GameInit)();
extern void (*GameUpdate)();
extern void (*GameCleanup)();
// Game Time per Loop ....

extern double GameApplication_Time;
extern double Game_DeltaTime;

extern bool changeStates;

enum GameStateList
{
	STATE_MENU_TEST = 1,
	STATE_GRAPHICS_TEST,
	STATE_LEVEL_TEST,
	STATE_GAME_TEST,
	STATE_RESTART,
	STATE_QUIT
};



void GameStateManagerInit(unsigned int setGameState);

void GameStateChanger(unsigned int setGameState);

void GameStateManagerUpdate();


#endif