/**************************************************************************
 * @file InitializeEngine.cpp
 * @author 	TAN Angus Yit Hoe
 * @co-author CHEAH Tristan Tze Hong, HWANG Jing Rui, Austin, LOW Wang Chun, Mark, CHAN Aaron Jun Xiang, QUEK Cheng Kwang Emery
 * @par DP email: tan.a@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 29-09-2023
 * @brief 
 * 
 * This file allows the usage of the program to change the game state
 * from one to another.
 * Currently, it allows for calling time functions as well.
 *************************************************************************/

#include <GameStateManager.h>

// The three states, before, now and after.
unsigned int CurrentGameState;
unsigned int PreviousGameState;
unsigned int NextGameState;

// seconds for GetDT()
double seconds = 0;

// gameRunTime for the GetGameRunTime()
static double gameRunTime = 0;

/*
Chrono for previous time | previous Time and deltaTime.
*/
std::chrono::high_resolution_clock::time_point currentTime;
std::chrono::high_resolution_clock::time_point previousTime;
std::chrono::duration<double> deltaTime;

/************************************************************************************
Function Pointers

CreateWindow --> pointing to OpenGLWindowInit(); [DOES NOT CHANGE]
WindowCleanup --> pointing to OpenGLWindowCleanup(); [DOES NOT CHANGE]

@brief creates a window application.
************************************************************************************/
void (*CreateWindow)() = OpenGLApplication::OpenGLWindowInit;
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


/**************************************************************************
* @brief		Initialize the Game State Manager
*
*				
* @param  unsigned int 
* @return void
*************************************************************************/
void GameStateManagerInit(unsigned int setGameState) {
	// Set GameState to setGameState
	CurrentGameState = setGameState;
	
	// Set Previous Game State the same as all Game States
	PreviousGameState = NextGameState = CurrentGameState;

	// set the manager and update it.
	GameStateManagerUpdate();	
}

/**************************************************************************
* @brief		Update the GameStateManager based on the STATE that is
*				input whenever the program is running
*
* @param  none
* @return void
*************************************************************************/
void GameStateManagerUpdate() {
	// if quit, exit
	if (CurrentGameState == STATE_QUIT)
		return;

	//  window is closed, exit
	if (glfwWindowShouldClose(windowNew)){
		CurrentGameState = STATE_QUIT;
		return;
	}

	// switch the case
	switch (CurrentGameState) {
	case STATE_GRAPHICS_TEST:
		GameInit = OpenGLApplication::OpenGLInit;
		GameUpdate = OpenGLApplication::OpenGLUpdate;
		GameCleanup = OpenGLApplication::OpenGLCleanup;
		break;
#ifdef _DEBUG
	case STATE_LEVEL_TEST:
		GameInit = OpenGLApplication::OpenGLInit;
		GameUpdate = OpenGLApplication::OpenGLTestChangingStates;
		GameCleanup = OpenGLApplication::OpenGLCleanup;
		//
		break;
#endif

	case STATE_GAME_TEST:
		// nothing for now.

	default:
		break;
	}
}


/**************************************************************************
* @brief		Get DeltaTime of the Application.
*
* @param  none
* @return double
*************************************************************************/
double GetDT() {
	return deltaTime.count();
}

/**************************************************************************
* @brief		Get Number of Frames in one second

* @param  none
* @return double
*************************************************************************/
double GetFrames() {
	return 1.0 / deltaTime.count();
}
/**************************************************************************
* @brief		a boolean check for if the time has exceeded, in Seconds.

* @param  unsigned int
* @return bool True if > time set, false if not yet more than time
*************************************************************************/
bool IsTimeElapsed(unsigned int time) {
	// only run once.
	// Get Time Elapsed.
	seconds += GetDT();
#ifdef _DEBUG	
	//std::cout << seconds << GetDT() << '\n';
#endif
	// refresh seconds to 0
	if (seconds >= time) {
		seconds = 0;
		return true;

	}
	else
		return false;
}
/**************************************************************************
* @brief		Gets the RunTime of the entire game.
*
* @param  none
* @return double
*************************************************************************/
double GetGameRunTime() {

	// Increase gameRunTime by the DT
	gameRunTime += GetDT();

	// return double
	return gameRunTime;
}