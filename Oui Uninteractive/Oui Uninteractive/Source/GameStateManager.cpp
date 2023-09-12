/**************************************************************************
 * @file InitializeEngine.cpp
 * @author 
 * @par DP email: 
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 09-05-2023
 * @brief 
 *************************************************************************/

#include <GameStateManager.h>


unsigned int CurrentGameState;
unsigned int PreviousGameState;
unsigned int NextGameState;

bool changeStates = true;


std::chrono::high_resolution_clock::time_point currentTime;
std::chrono::high_resolution_clock::time_point previousTime;
std::chrono::duration<double> deltaTime;

double gameRunTime = 0;

/************************************************************************************
CreateWindow(short width, short height)

@brief creates a window application.
************************************************************************************/
void (*CreateWindow)(unsigned short width, unsigned short height) = OpenGLApplication::OpenGLWindowInit;
void (*WindowCleanup)() = OpenGLApplication::OpenGLWindowCleanup;


/************************************************************************************
Function Pointers

GameInit()
GameUpdate()
GameCleanup()

@brief creates a window application.
************************************************************************************/
void (*GameInit)()								= 0;
void (*GameUpdate)()							= 0;
void (*GameCleanup)()							= 0;


double seconds = 0;


void GameStateManagerInit(unsigned int setGameState)
{
	CurrentGameState = setGameState;
	
	PreviousGameState = NextGameState = CurrentGameState;


	GameStateManagerUpdate();	
}


void GameStateManagerUpdate()
{
	if (CurrentGameState == STATE_QUIT)
		return;

	if (glfwWindowShouldClose(window))
	{
		CurrentGameState = STATE_QUIT;
		return;
	}

	switch (CurrentGameState)
	{
	case STATE_GRAPHICS_TEST:
		GameInit = OpenGLApplication::OpenGLInit;
		GameUpdate = OpenGLApplication::OpenGLUpdate;
		GameCleanup = OpenGLApplication::OpenGLCleanup;
		break;
	case STATE_LEVEL_TEST:
		GameInit = OpenGLApplication::OpenGLInit;
		GameUpdate = OpenGLApplication::OpenGLTestChangingStates;
		GameCleanup = OpenGLApplication::OpenGLCleanup;
		//
		break;


	case STATE_GAME_TEST:


	default:
		break;
	}
}


void TimeUpdate()
{
	currentTime = std::chrono::high_resolution_clock::now();
	deltaTime = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - previousTime);
	previousTime = currentTime;
}

double GetDT()
{
	return deltaTime.count();
}

double GetFrames()
{
	return 1 / deltaTime.count();
}
#include <iostream>
bool GetFPS()
{
	seconds += GetDT();
	std::cout << seconds << GetDT() << '\n';
	if (seconds >= 1)
	{
		seconds = 0;
		return true;

	}
	else
		return false;



}

double GetGameRunTime()
{
	gameRunTime += GetDT();

	return gameRunTime;
}