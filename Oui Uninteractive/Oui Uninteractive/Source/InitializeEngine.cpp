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
		GameStateInit = OpenGLApplication::OpenGLInit;
		GameStateUpdate = OpenGLApplication::OpenGLUpdate;
		GameStateCleanup = OpenGLApplication::OpenGLCleanup;
		break;
	case State_GameTesting:



	case State_LevelTest:


	case State_STOP:
		
		return;

	default:
		break;
	}
}