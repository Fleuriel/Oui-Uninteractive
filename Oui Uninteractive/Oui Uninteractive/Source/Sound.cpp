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

 // Initialize global pointer
SoundManager* soundManager = nullptr;

SoundManager::SoundManager() {
	if (soundManager != nullptr) {
		// Instantiate sound system
		return;
	}
	else {
		soundManager = this;
	}
}

 /* ============================================
	 @brief 
		This function initializes the sound system
	 @return
		 No return
	============================================ */
void SoundManager::Initialize() {
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
	LoadSounds();
}

void SoundManager::Update(float dt) {
	//PlayBGMSounds();
	//PlaySFXSounds();
	system->update();
}

/* ============================================
	@brief
	   This function loads the sounds from the file directories
	@return
		No return
   ============================================ */
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

/* ============================================
	@brief
	   This function plays the sounds
	@return
		No return
   ============================================ */
void SoundManager::PlayBGMSounds() {
	// Play BGM once clicked
	if (bgmChannel == nullptr) {
		result = system->playSound(bgmSounds[1], nullptr, true, &bgmChannel);
	}
	if (result != FMOD_OK) {
		std::cout << "FMOD error: " << FMOD_ErrorString(result);
	}
}

void SoundManager::PlaySFXSounds() {
	// Play SFX once clicked
	channel1->stop();
	result = system->playSound(sfxSounds[sfxChoice], nullptr, false, &channel1);
	if (result != FMOD_OK) {
		std::cout << "FMOD error: " << FMOD_ErrorString(result);
	}
}



/* ============================================
	@brief
	   These functions handle pausing the channels
	@return
		No return
   ============================================ */
void SoundManager::TogglePlayChannel(FMOD::Channel* selectedChannel) {
	bool pausedState;
	selectedChannel->getPaused(&pausedState);
	selectedChannel->setPaused(!pausedState);
}


/* ============================================
	@brief
	   This destructor handles shutdown of the sound system
	@return
		No return
   ============================================ */
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