#include <SceneGameTesting2.h>
#include <InitializeEngine.h>
#include <keyDefinition.h>
#include <iostream>
void SceneGameTesting2::GameTesting2Init(short temp, short temp2) {
	//OpenGLApplication::OpenGLInit(temp, temp2);

}
void SceneGameTesting2::GameTesting2Update() {

	OpenGLApplication::OpenGLUpdate();
	
	if (InputStates[INPUT_1]) {
		NextGameState = State_GraphicsTest;
	}
	

}
void SceneGameTesting2::GameTesting2Cleanup() {


}