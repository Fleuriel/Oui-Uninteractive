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

// < MAIN.CPP>
extern unsigned int InitializationGameState;
extern unsigned int CurrentGameState;
extern unsigned int PreviousGameState;
extern unsigned int NextGameState;

extern void (*CreateWindow)();
extern void (*WindowCleanup)();
extern void (*GameInit)();
extern void (*GameUpdate)();
extern void (*GameCleanup)();


// Game State List Enumeration
enum GameStateList
{
	STATE_MENU_TEST = 1,
	STATE_GRAPHICS_TEST,
	STATE_LEVEL_TEST,
	STATE_GAME_TEST,
	STATE_RESTART,
	STATE_QUIT
};


/**************************************************************************
* @brief		Initialize the Game State Manager
*
*
* @param  unsigned int
* @return void
*************************************************************************/
void GameStateManagerInit(unsigned int setGameState);
/**************************************************************************
* @brief		Update the GameStateManager based on the STATE that is
*				input whenever the program is running
*
* @param  none
* @return void
*************************************************************************/
void GameStateManagerUpdate();

// Time Functions
/**************************************************************************
* @brief  Update the time, reduce clutter
* @return void
*************************************************************************/
void TimeUpdate();
/**************************************************************************
* @brief		Get DeltaTime of the Application.
*
* @param  none
* @return double
*************************************************************************/
double GetDT();
/**************************************************************************
* @brief		Get Number of Frames in one second

* @param  none
* @return double
*************************************************************************/
double GetFrames();
/**************************************************************************
* @brief		a boolean check for if the time has exceeded, in Seconds.

* @param  unsigned int
* @return bool True if > time set, false if not yet more than time
*************************************************************************/
bool IsTimeElapsed(unsigned int time);
/**************************************************************************
* @brief		Gets the RunTime of the entire game.
*
* @param  none
* @return double
*************************************************************************/
double GetGameRunTime();
#endif