/**************************************************************************
 * @file Sound.cpp
 * @author Mark Low
 * @par DP email: l.wangchunmark@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 09-05-2023
 * @brief This source file contains the definition of the SoundManager class used to setup FMOD and handle playing of sounds
 *************************************************************************/

#include <iostream>
#include "Sound.h"
#include "Editor.h"

 // Initialize global pointer
SoundManager* soundManager = nullptr;

/**************************************************************************
* @brief Default constructor for SoundManager class
*************************************************************************/
SoundManager::SoundManager() {
	if (soundManager != nullptr) {
		// Instantiate sound system
		return;
	}
	else {
		soundManager = this;
	}
}


/**************************************************************************
* @brief Default constructor for PhysicsBody component
* @return No return
*************************************************************************/
void SoundManager::Initialize() {
	// Create main system object
	result = FMOD::System_Create(&system);
	if (result != FMOD_OK) {
		std::cout << "FMOD error: " << FMOD_ErrorString(result);
	}
	// Initailize FMOD
	result = system->init(10, FMOD_INIT_NORMAL, 0); // 10 max channels set
	if (result != FMOD_OK) {
		std::cout << "FMOD error: " << FMOD_ErrorString(result);
	}
	LoadSounds();
}


/**************************************************************************
* @brief Update function for the SoundManager class
* @param dt - delta time 
* @return No return
*************************************************************************/
void SoundManager::Update(float dt) {
	std::chrono::high_resolution_clock::time_point timeStart = std::chrono::high_resolution_clock::now();
	
	system->update();

	std::chrono::high_resolution_clock::time_point timeEnd = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float, std::milli> duration = timeEnd - timeStart;
	Editor::timeRecorder.soundTime = duration.count();
}


/**************************************************************************
* @brief This function loads the sounds from the file directories
* @return No return
*************************************************************************/
void SoundManager::LoadSounds() {
	// Search BGM directory and load sounds
	for (const auto& i : std::filesystem::directory_iterator(bgmPath)) {
		FMOD::Sound* newSound;
		result = system->createSound(i.path().string().c_str(), FMOD_DEFAULT, 0, &newSound);
		if (result != FMOD_OK) {
			std::cout << "FMOD error: " << FMOD_ErrorString(result);
		}
		bgmSounds.push_back(newSound);
	}
	// Search SFX directory and load sounds
	for (const auto& i : std::filesystem::directory_iterator(sfxPath)) {
		FMOD::Sound* newSound;
		result = system->createSound(i.path().string().c_str(), FMOD_DEFAULT, 0, &newSound);
		if (result != FMOD_OK) {
			std::cout << "FMOD error: " << FMOD_ErrorString(result);
		}
		sfxSounds.push_back(newSound);
	}
}


/**************************************************************************
* @brief This function plays the BGM sounds
* @return No return
*************************************************************************/
void SoundManager::PlayBGMSounds() {
	// Play BGM once clicked
	bool playStatus1, playStatus2;
	bgmChannels[0]->isPlaying(&playStatus1);
	if (bgmChannels[0] == nullptr || !playStatus1) {
		result = system->playSound(bgmSounds[0], nullptr, true, &bgmChannels[0]);
		if (result != FMOD_OK) {
			std::cout << "FMOD error: " << FMOD_ErrorString(result);
			return;
		}
	}
	
	bgmChannels[1]->isPlaying(&playStatus2);
	if (bgmChannels[1] == nullptr || !playStatus2) {
		result = system->playSound(bgmSounds[1], nullptr, true, &bgmChannels[1]);
		if (result != FMOD_OK) {
			std::cout << "FMOD error: " << FMOD_ErrorString(result);
			return;
		}
	}
	
}


/**************************************************************************
* @brief This function plays the SFX sounds
* @return No return
*************************************************************************/
void SoundManager::PlaySFXSounds() {
	// Play SFX once clicked
	sfxChannels[0]->stop();
	result = system->playSound(sfxSounds[sfxChoice], nullptr, false, &sfxChannels[0]);
	if (result != FMOD_OK) {
		std::cout << "FMOD error: " << FMOD_ErrorString(result);
	}
}



/**************************************************************************
* @brief These functions handle pausing the channels
* @param selectedChannel - Pointer to a FMOD channel to play sound to
* @return No return
*************************************************************************/
void SoundManager::TogglePlayChannel(FMOD::Channel* selectedChannel) {
	bool pausedState;
	selectedChannel->getPaused(&pausedState);
	selectedChannel->setPaused(!pausedState);
}


/**************************************************************************
* @brief This destructor handles shutdown of the sound system
* @return No return
*************************************************************************/
SoundManager::~SoundManager() {
	if (system) {
		// Free individual BGM sounds
		for (const auto& i : bgmSounds) {
			i->release();
		}
		// Free individual SFX sounds
		for (const auto& i : sfxSounds) {
			i->release();
		}
		system->close();
		system->release();
		system = nullptr;
	}
}