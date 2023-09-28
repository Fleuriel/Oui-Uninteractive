/**************************************************************************
 * @file main.cpp
 * @author 	TAN Angus Yit Hoe
 * @co-author CHEAH Tristan Tze Hong, HWANG Jing Rui, Austin, LOW Wang Chun, Mark, CHAN Aaron Jun Xiang, QUEK Cheng Kwang Emery
 * @par DP email: 
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 09-05-2023
 * @brief 
 *************************************************************************/

#include <iostream>
#include <GameStateManager.h>
#include "Physics.h"
#include "SystemManager.h"
#include "ObjectFactory.h"
#include "Sound.h"


void TimeUpdate();

int main()
{
	#if defined(DEBUG) | defined(_DEBUG)
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	#endif

	// check if the application is !glfwInit();
	if (!glfwInit())
		return -1;

	CreateWindow();
	SystemManager* sysManager = new SystemManager();
	sysManager->AddSystem(new ObjectFactory());
	sysManager->AddSystem(new Physics());
	sysManager->AddSystem(new SoundManager());
	sysManager->Initialize();
	// Set callback for window close button (top right button).
	glfwSetWindowCloseCallback(windowNew, WindowCloseCallback);

	// Frame Buffer Callback for Window.
	glfwSetFramebufferSizeCallback(windowNew, OpenGLApplication::OpenGLWindowResizeCallback);
	// Initialize the GameStateManager
	// Initialize Game State, Input here.
	GameStateManagerInit(STATE_GRAPHICS_TEST);
	
	// set previousTime as NOW. first, then will be able to calculate.
	previousTime = std::chrono::high_resolution_clock::now();

	// The Main Window.
	while (!glfwWindowShouldClose(windowNew))
	{
		// Changing in CurrentGameState would make it TRUE for this,
		// so it will update the manager, to change the state.
		if (CurrentGameState != NextGameState)
		{
			GameStateManagerUpdate();
		}
		// else initialize all states to be the same.
		else
		{
			NextGameState = CurrentGameState = PreviousGameState;
		}


		// Happen ONLY once, 
		// ONLY if changing of states
		GameInit();

		while (CurrentGameState == NextGameState)
		{
			// Acquire Time Updates, setup for deltaTime
			// For FPS, DeltaTime and Runtime
			TimeUpdate();
			
			// Poll the events from the window. [OpenGL Function]
			glfwPollEvents();

			sysManager->UpdateSystems(static_cast<float>(GetDT()));

			// Update the Game Loop, based on the currentGameState
			GameUpdate();
			

			// Swap Buffers with the window, similar to GOL in Y1T1 [OpenGL Function]
			glfwSwapBuffers(windowNew);


			// At the end, if check the state is quite else go away.
			if (CurrentGameState == STATE_QUIT)
				break;
		}

		// Before anything, cleanup as it is out of the state loop
		GameCleanup();

		// QUIT [ After cleanup ]
		if (CurrentGameState == STATE_QUIT)
			break;

		std::cout << "State is NOT Quit\n";

		GameStateManagerUpdate();


		// Set the states.
		PreviousGameState = CurrentGameState;
		CurrentGameState = NextGameState;
	}


	// Free System if any before main closes.

	// Cleanup the window.

	WindowCleanup();
	objectFactory->SaveObjectsToFile("../scenes/TestsceneWriting.JSON");
	objectFactory->DestroyAllObjects();
	sysManager->DestroySystem();
	delete sysManager;


	return 0;
}



/**************************************************************************
* @brief  Update the time, reduce clutter
* @return void
*************************************************************************/
void TimeUpdate()
{
	currentTime = std::chrono::high_resolution_clock::now();
	deltaTime = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - previousTime);
	previousTime = currentTime;
}