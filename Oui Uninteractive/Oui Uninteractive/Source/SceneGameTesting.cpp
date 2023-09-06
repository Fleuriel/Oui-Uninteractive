#include <SceneGameTesting.h>
#include <keyDefinition.h>
#include <InitializeEngine.h>
#include <iostream>
void SceneGameTesting::GameTestingInit(short temp, short temp2) {
	//OpenGLApplication::OpenGLInit(temp, temp2);
	
}
void SceneGameTesting::GameTestingUpdate() {
		OpenGLApplication::OpenGLUpdate();
		//window->OpenGLUpdate();
	
		
		if (InputStates[INPUT_2]) {
			NextGameState = State_GameTesting;
		}
	
}
void SceneGameTesting::GameTestingCleanup() {
	

}