#include <iostream>
#include <InitializeEngine.h>


int Mode;


int main()
{
	std::cout << "Hello World\n";



	EngineStartUp(State_GraphicsTest);



	
	while (CurrentGameState != State_STOP)
	{
		std::cout << "hello\n";
		while (NextGameState == CurrentGameState)
		{
			GameStateInit(1366, 768);

			GameStateUpdate();


			// Get FPS .. (Will do later)
			// GameApplication_Time = ;
			// GameApplication_Time += Game_DeltaTime;
		}

		// Free & Unload
		GameStateCleanup();


		PreviousGameState = CurrentGameState;
		CurrentGameState = NextGameState;
	}


	// Free System if any before main closes.



	return 0;
}



