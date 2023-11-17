/**************************************************************************
 * @file main.cpp
 * @author 	TAN Angus Yit Hoe
 * @co-author CHEAH Tristan Tze Hong, HWANG Jing Rui, Austin, LOW Wang Chun, Mark, CHAN Aaron Jun Xiang, QUEK Cheng Kwang Emery
 * @par DP email: tan.a@digipen.edu, t.cheah@digipen.edu, jingruiaustin.hwang@digipen.edu, l.wangchunmark@digipen.edu, aaronjunxiang.chan@digipen.edu, c.quek@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 29-09-2023
 * @brief 
 * Main Function to run the program
 *************************************************************************/

#include <iostream>
#include <GameStateManager.h>
#include "Physics.h"
#include "SystemManager.h"
#include "ObjectFactory.h"
#include "TilemapLoader.h"
#include "EnemyAISystem.h"
#include "Logic.h"
#include "Sound.h"
#include "TransformSystem.h"
#include "SceneManager.h"
#include "FontManager.h"
#include "UI.h"

void TimeUpdate();



int main(){
	#if defined(DEBUG) | defined(_DEBUG)
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	#endif

	// check if the application is !glfwInit();
	if (!glfwInit())
		return -1;

	//CreateWindow();
	sysManager = new SystemManager();

	// Have Errors for now. need fix
	sysManager->AddSystem(new SoundManager());
	sysManager->AddSystem(new FontManager());
	sysManager->AddSystem(new OpenGLApplication());
	sysManager->AddSystem(new LogicSystem());
	sysManager->AddSystem(new ObjectFactory());
	sysManager->AddSystem(new TilemapLoader());
	sysManager->AddSystem(new ColliderSystem());
	sysManager->AddSystem(new Physics());
	sysManager->AddSystem(new EnemyAISystem());

	sysManager->AddSystem(new TransformSystem());
	sysManager->AddSystem(new SceneManager());
	sysManager->AddSystem(new UIManager());
	sysManager->Initialize();
	// Set callback for window close button (top right button).
	glfwSetWindowCloseCallback(windowNew, WindowCloseCallback);

	// Frame Buffer Callback for Window.
	glfwSetFramebufferSizeCallback(windowNew, OpenGLApplication::OpenGLWindowResizeCallback);
	// Initialize the GameStateManager
	// Initialize Game State, Input here.
	//GameStateManagerInit(STATE_GRAPHICS_TEST);
	
	// set previousTime as NOW. first, then will be able to calculate.
	previousTime = std::chrono::high_resolution_clock::now();

	// The Main Window.
	while (!glfwWindowShouldClose(windowNew)){
		// Changing in CurrentGameState would make it TRUE for this,
		// so it will update the manager, to change the state.
		if (sceneManager->currSceneID != GameStateList::STATE_RESTART){
			//GameStateManagerUpdate();
			sceneManager->Load();
		}
		// else initialize all states to be the same.
		else		{
			sceneManager->nextSceneID = sceneManager->currSceneID = sceneManager->prevSceneID;
		}

		sceneManager->InitScene();
		// Happen ONLY once, 
		// ONLY if changing of states
	//	GameInit();
		
		while (sceneManager->currSceneID == sceneManager->nextSceneID){
			// Acquire Time Updates, setup for deltaTime
			// For FPS, DeltaTime and Runtime
			TimeUpdate();
			


			sysManager->UpdateSystems(static_cast<float>(GetDT()));			

			
			// Swap Buffers with the window, similar to GOL in Y1T1 [OpenGL Function]
			glfwSwapBuffers(windowNew);

			// Poll the events from the window. [OpenGL Function]
			glfwPollEvents();

			// At the end, if check the state is quite else go away.
			if (sceneManager->currSceneID == STATE_QUIT)
				break;
		}

		// Before anything, cleanup as it is out of the state loop
	//	GameCleanup();
		sceneManager->Free();
		// QUIT [ After cleanup ]
		if (sceneManager->currSceneID == STATE_QUIT)
			break;

		std::cout << "State is NOT Quit\n";

		// Set the states.
		sceneManager->prevSceneID = sceneManager->currSceneID;
		sceneManager->currSceneID = sceneManager->nextSceneID;
	}


	// Free System if any before main closes.

	// Cleanup the window.

	//WindowCleanup();
	//objectFactory->SaveObjectsToFile("../scenes/TestsceneWriting.JSON");
	//objectFactory->DestroyAllObjects();
	sysManager->DestroySystem();
	delete sysManager;


	return 0;
}



/**************************************************************************
* @brief  Update the time, reduce clutter
* @return void
*************************************************************************/
void TimeUpdate(){
	sysManager->currentNumberOfSteps = 0;
	currentTime = std::chrono::high_resolution_clock::now();
	deltaTime = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - previousTime);
	previousTime = currentTime;
	sysManager->accumulatedTime += deltaTime.count();
	while (sysManager->accumulatedTime >= sysManager->fixedDeltaTime) {
		sysManager->accumulatedTime -= sysManager->fixedDeltaTime;
		sysManager->currentNumberOfSteps++;
	}

	if (sysManager->currentNumberOfSteps > sysManager->maxNoOfStep) {
		sysManager->currentNumberOfSteps = sysManager->maxNoOfStep;
	}
	
}