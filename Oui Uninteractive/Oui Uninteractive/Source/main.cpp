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
	
	// The Main Window.
	while (!glfwWindowShouldClose(window))
	{

		if (CurrentGameState != NextGameState)
		{
			GameStateManagerUpdate();
		}
		else
		{
			NextGameState = CurrentGameState = PreviousGameState;
		}


		// Happen ONLY once,
		GameInit();

		while (CurrentGameState == NextGameState)
		{
			glfwPollEvents();
			GameUpdate();



			glfwSwapBuffers(window);
			if (CurrentGameState == STATE_QUIT)
				break;
		}

		GameCleanup();

		if (CurrentGameState == STATE_QUIT)
			break;
		std::cout << "hello\n";

		GameStateManagerUpdate();



		PreviousGameState = CurrentGameState;
		CurrentGameState = NextGameState;
	}


	// Free System if any before main closes.

	WindowCleanup();


	return 0;
}



