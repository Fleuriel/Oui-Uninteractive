/**************************************************************************
 * @file InitializeEngine.cpp
 * @author 
 * @par DP email: 
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 09-05-2023
 * @brief 
 *************************************************************************/

#include <InitializeEngine.h>



unsigned int InitializationGameState;
unsigned int CurrentGameState;
unsigned int PreviousGameState;
unsigned int NextGameState;


void (*GameStateInit)(short width, short height)    = 0;
void (*GameStateUpdate)()  = 0;
void (*GameStateCleanup)() = 0;

void EngineStartUp(unsigned int Initialize)
{
	InitializationGameState = Initialize;

	CurrentGameState	= InitializationGameState;
	PreviousGameState	= InitializationGameState;
	NextGameState		= InitializationGameState;


	EngineUpdate();
}


void EngineUpdate()
{
	if (CurrentGameState == 4)
		return;

	if (glfwWindowShouldClose(window))
	{
		CurrentGameState = State_STOP;
		return;
	}

	switch (CurrentGameState)
	{
	case State_GraphicsTest:
		GameStateInit = SceneGameTesting::GameTestingInit;
		GameStateUpdate = SceneGameTesting::GameTestingUpdate;
		GameStateCleanup = SceneGameTesting::GameTestingCleanup;
		//GameStateInit = OpenGLApplication::OpenGLInit;
		//GameStateUpdate = OpenGLApplication::OpenGLUpdate;
		//GameStateCleanup = OpenGLApplication::OpenGLCleanup;
		break;
	case State_GameTesting:
		GameStateInit = SceneGameTesting2::GameTesting2Init;
		GameStateUpdate = SceneGameTesting2::GameTesting2Update;
		GameStateCleanup = SceneGameTesting2::GameTesting2Cleanup;
		break;



	case State_LevelTest:


	case State_STOP:
		
		return;

	default:
		break;
	}
}