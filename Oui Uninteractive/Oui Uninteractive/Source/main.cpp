#include <iostream>
#include <InitializeEngine.h>


int Mode;


int main()
{
	std::cout << "Hello World\n";



	EngineStartUp(State_GraphicsTest);



	
	while (CurrentGameState != State_STOP)
	{
#ifdef _DEBUG
		std::cout << "State is not Stop\n";
#endif
		while (NextGameState == CurrentGameState)
		{
#ifdef _DEBUG 
			std::cout << "Running Game\n";
#endif
			GameStateInit(1366, 768);

			GameStateUpdate();



			// Get FPS .. (Will do later)
			// GameApplication_Time = ;
			// GameApplication_Time += Game_DeltaTime;
		}

		// Free & Unload
		GameStateCleanup();

		std::cout << CurrentGameState << '\n';



		break;
	}


	// Free System if any before main closes.



	return 0;
}



