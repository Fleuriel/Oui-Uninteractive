/**************************************************************************
 * @file Sound.cpp
 * @author
 * @par DP email:
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 09-05-2023
 * @brief This source file contains the code to setup and run the editor
 *************************************************************************/

#include <Sound.h>
#include <iostream>

 /* ============================================
	 @brief 
		This function initializes the sound system
	 @return
		 No return
	============================================ */
void SoundManager::Init() {	
	// Create main system object
	result = FMOD::System_Create(&system);
	if (result != FMOD_OK) {
		std::cout << "FMOD error: " << FMOD_ErrorString(result);
	}
	// Initailize FMOD
	result = system->init(2, FMOD_INIT_NORMAL, 0);
	if (result != FMOD_OK) {
		std::cout << "FMOD error: " << FMOD_ErrorString(result);
	}
}

/* ============================================
	@brief
	   This function loads the sounds from the file directory
	@return
		No return
   ============================================ */
void SoundManager::LoadSounds() {
	sound1 = sound2 = nullptr;

	result = system->createSound("../Sounds/bgm/lebanon.mp3", FMOD_DEFAULT, 0, &sound1);
	if (result != FMOD_OK) {
		std::cout << "FMOD error: " << FMOD_ErrorString(result);
	}

	result = system->createSound("../Sounds/bgm/bestsong.mp3", FMOD_DEFAULT, 0, &sound2);	
	if (result != FMOD_OK) {
		std::cout << "FMOD error: " << FMOD_ErrorString(result);
	}
}

/* ============================================
	@brief
	   This function plays the sounds
	@return
		No return
   ============================================ */
void SoundManager::PlaySounds() {
	channel1 = nullptr;
	result = system->playSound(sound2, 0, false, &channel1);
	if (result != FMOD_OK) {
		std::cout << "FMOD error: " << FMOD_ErrorString(result);
	}
}

/* ============================================
	@brief
	   This function handles shutdown of the sound system
	@return
		No return
   ============================================ */
void SoundManager::Shutdown() {
	if (system) {
		system->release();
		system->close();
		system = nullptr;
	}
}