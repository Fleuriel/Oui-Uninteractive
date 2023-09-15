/**************************************************************************
 * @file main.cpp
 * @author 
 * @par DP email: 
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 09-05-2023
 * @brief 
 *************************************************************************/

#include <iostream>
#include <GameStateManager.h>
#include "Physics.h"


int Mode;


int main()
{
	std::cout << "Hello World\n";
	if (!glfwInit())
		return -1;

	CreateWindow(900, 900);
		

	// Initialize the GameStateManager
	// Someone needs to put 
	GameStateManagerInit(STATE_GRAPHICS_TEST);
	
	previousTime = std::chrono::high_resolution_clock::now();

	// The Main Window.
	while (!glfwWindowShouldClose(window))
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

			GameUpdate();
			//needs to be changed, currently input is being checked before physics
		//	physicsSys->Update(GetDT());


			// Swap Buffers with the window, similar to GOL in Y1T1 [OpenGL Function]
			glfwSwapBuffers(window);



			//std::cout << GetDeltaTime() << '\n';
			
			// Running the Runtime in cout, will need to change eventually.
			//std::cout << GetGameRunTime() << '\n';


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


	return 0;
}



