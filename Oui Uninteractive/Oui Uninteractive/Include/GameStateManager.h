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

#include <Input.h>
#include <OpenGLApplication.h>
#include <OpenGLObjects.h>
#include <OpenGLShaders.h>

#include <chrono>

 // < TIME >

extern std::chrono::high_resolution_clock::time_point currentTime;
extern std::chrono::high_resolution_clock::time_point previousTime;
extern std::chrono::duration<double> deltaTime;

extern unsigned int InitializationGameState;
extern unsigned int CurrentGameState;
extern unsigned int PreviousGameState;
extern unsigned int NextGameState;

extern void (*CreateWindow)();
extern void (*WindowCleanup)();
extern void (*GameInit)();
extern void (*GameUpdate)();
extern void (*GameCleanup)();
// Game Time per Loop ....

extern double GameApplication_Time;
extern double Game_DeltaTime;

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

void GameStateManagerUpdate();

// Time Functions
void TimeUpdate();

double GetDT();

double GetFrames();

bool IsTimeElapsed(unsigned int time);

double GetGameRunTime();
#endif