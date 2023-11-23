/**************************************************************************
 * @file Sound.cpp
 * @author LOW Wang Chun, Mark
 * @par DP email: l.wangchunmark@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 09-05-2023
 * @brief This source file contains the definition of the SoundManager class used to setup FMOD and handle playing of sounds
 *************************************************************************/

#include <iostream>
#include "Sound.h"
#include "Editor.h"
#include "AssetManager.h"

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
* @brief Initializer for SoundManager class
* @return No return
*************************************************************************/
void SoundManager::Initialize() {
	// Create main system object
	result = FMOD::System_Create(&system);
	if (result != FMOD_OK) {
		std::cout << "FMOD error: " << FMOD_ErrorString(result);
	}
	// Initailize FMOD
	result = system->init(512, FMOD_INIT_NORMAL, 0); // 100 max channels set
	if (result != FMOD_OK) {
		std::cout << "FMOD error: " << FMOD_ErrorString(result);
	}
}


/**************************************************************************
* @brief Update function for the SoundManager class
* @param dt - delta time 
* @return No return
*************************************************************************/
void SoundManager::Update(float dt) {
	// Start time profiling for sound system
	TimeProfiler profiler(Editor::timeRecorder.soundTime);
		
	system->update();

	// Check which channel is still playing for automatic removal once stopped
	std::vector<int> removeCHs;
	for (auto& [id, channel] : soundChannels) {
		bool isPlaying = false;
		channel->isPlaying(&isPlaying);
		if (!isPlaying) {
			removeCHs.push_back(id);
		}
	}
	// Recycle channels to pool
	for (int id : removeCHs) {
		soundChannels.erase(id);
		recycleChannelID(id);
	}
	(void)dt;
}



int SoundManager::getAvailableChannelID() {
	static int currID = 0;
	
	if (!availableIDs.empty()) {
		int id = availableIDs.front();
		availableIDs.pop();
		return id;
	}
	return currID++;
}


void SoundManager::recycleChannelID(int id) {
	availableIDs.push(id);
}


void SoundManager::PlaySFX(const std::string& sound) {
	FMOD::Sound* sfxSound = assetManager.GetSFX(sound);
	FMOD::Channel* channel;
	result = system->playSound(sfxSound, soundGroups[SoundGroup::SGSFX], false, &channel);
	if (result != FMOD_OK) {
		std::cout << "FMOD error: " << FMOD_ErrorString(result);
		return;
	}
	int channelID = getAvailableChannelID();
	soundChannels[channelID] = channel;
}

//**************************************************************************
//* @brief This function plays the BGM sounds
//* @return No return
//*************************************************************************/
//void SoundManager::PlayBGMSounds() {
//	// Play BGM once clicked
//	bool playStatus1, playStatus2;
//	bgmChannels[0]->isPlaying(&playStatus1);
//	if (bgmChannels[0] == nullptr || !playStatus1) {
//		result = system->playSound(assetManager.GetBGM("Nightshift__BGM2_Loop_70bpm.wav"), nullptr, true, &bgmChannels[0]);
//		if (result != FMOD_OK) {
//			std::cout << "FMOD error: " << FMOD_ErrorString(result);
//			return;
//		}
//	}
//	
//	bgmChannels[1]->isPlaying(&playStatus2);
//	if (bgmChannels[1] == nullptr || !playStatus2) {
//		result = system->playSound(assetManager.GetBGM("Suspense.wav"), nullptr, true, &bgmChannels[1]);
//		if (result != FMOD_OK) {
//			std::cout << "FMOD error: " << FMOD_ErrorString(result);
//			return;
//		}
//	}
//	
//}
//
//
///**************************************************************************
//* @brief This function plays the SFX sounds
//* @return No return
//*************************************************************************/
//void SoundManager::PlaySFXSounds() {
//	// Play SFX once clicked
//	sfxChannels[0]->stop();
//	result = system->playSound(assetManager.GetSFX("Gunshot.wav"), nullptr, false, &sfxChannels[0]);
//	if (result != FMOD_OK) {
//		std::cout << "FMOD error: " << FMOD_ErrorString(result);
//	}
//}
//
//
//
///**************************************************************************
//* @brief These functions handle pausing the channels
//* @param selectedChannel - Pointer to a FMOD channel to play sound to
//* @return No return
//*************************************************************************/
//void SoundManager::TogglePlayChannel(FMOD::Channel* selectedChannel) {
//	bool pausedState;
//	selectedChannel->getPaused(&pausedState);
//	selectedChannel->setPaused(!pausedState);
//}


/**************************************************************************
* @brief This destructor handles shutdown of the sound system
* @return No return
*************************************************************************/
SoundManager::~SoundManager() {
	if (system) {
		
		assetManager.FreeSounds();

		system->close();
		system->release();
		system = nullptr;
	}
}