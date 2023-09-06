/**************************************************************************
 * @file InitializeEngine.h
 * @author 
 * @par DP email: 
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 09-05-2023
 * @brief 
 *************************************************************************/

#include <InputKeys.h>
#include <OpenGLApplication.h>
#include <SceneGameTesting.h>
#include <SceneGameTesting2.h>
#include <OpenGLObjects.h>
#include <OpenGLShaders.h>

extern unsigned int InitializationGameState;
extern unsigned int CurrentGameState;
extern unsigned int PreviousGameState;
extern unsigned int NextGameState;

extern void (*GameStateInit)(short width, short height);
extern void (*GameStateUpdate)();
extern void (*GameStateCleanup)();

// Game Time per Loop ....

extern double GameApplication_Time;
extern double Game_DeltaTime;


enum GameStateList
{
	//State_GAMEPLAY = 0,
	//State_RESTART,
	//State_QUIT,
	//State_LEVEL_EDITOR
	State_GraphicsTest = 1,
	State_LevelTest,
	State_GameTesting,
	State_STOP
};



void EngineStartUp(unsigned int Initialize);

void EngineUpdate();


