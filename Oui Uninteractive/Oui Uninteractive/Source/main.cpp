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
#include <InitializeEngine.h>


int Mode;


int main()
{
	std::cout << "Hello World\n";
	//test.OpenGLInit(1000, 800);
	OpenGLApplication::OpenGLInit(1000, 800);



	EngineStartUp(State_GraphicsTest);
		
	while (CurrentGameState != State_STOP)
	{
#ifdef _DEBUG
		//std::cout << "State is not Stop\n";
#endif	
		EngineUpdate();
		while (NextGameState == CurrentGameState)
		{
#ifdef _DEBUG 
			std::cout << "Running Game\n";
#endif
			GameStateInit(900, 900);

			GameStateUpdate();


			//break;
			// Get FPS .. (Will do later)
			// GameApplication_Time = ;
			// GameApplication_Time += Game_DeltaTime;
		}

		// Free & Unload
		GameStateCleanup();

		std::cout << CurrentGameState << " state \n";

		PreviousGameState = CurrentGameState;
		CurrentGameState = NextGameState;
	}


	// Free System if any before main closes.


	OpenGLApplication::OpenGLCleanup();
	return 0;
}



