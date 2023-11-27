/**************************************************************************
 * @file Sound.cpp
 * @author LOW Wang Chun, Mark - 100%
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
#include "SystemManager.h"

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
	result = system->init(512, FMOD_INIT_NORMAL, 0); // 512 max channels set
	if (result != FMOD_OK) {
		std::cout << "FMOD error: " << FMOD_ErrorString(result);
	}
	// Create channel groups
	for (int i = 0; i < SGCOUNT; i++) {
		FMOD::ChannelGroup* channelGroup;
		result = system->createChannelGroup(nullptr, &channelGroup);
		if (result != FMOD_OK) {
			std::cout << "FMOD error: " << FMOD_ErrorString(result);
		}
		soundGroups[i] = channelGroup;
	}
}


/**************************************************************************
* @brief Update function for the SoundManager class
* @param dt - delta time 
* @return No return
*************************************************************************/
void SoundManager::Update(float dt) {
	if (sysManager->isPaused == false) {
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
}


/**************************************************************************
* @brief This helper function gets the next available channel ID for assignment
* @return Returns an integer of the next available ID
*************************************************************************/
int SoundManager::getAvailableChannelID() {
	static int currID = 0;
	if (!availableIDs.empty()) {
		int id = availableIDs.front();
		availableIDs.pop();
		return id;
	}
	return currID++;
}


/**************************************************************************
* @brief This helper function recycles channel IDs
* @param[in] id - IDs to be recycled
* @return void
*************************************************************************/
void SoundManager::recycleChannelID(int id) {
	availableIDs.push(id);
}


/**************************************************************************
* @brief This function handles playing of SFX
* @param[in] sound - Name of the sound file to be played
* @return void
*************************************************************************/
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


/**************************************************************************
* @brief This function handles playing of BGM
* @param[in] sound - Name of the sound file to be played
* @return void
*************************************************************************/
void SoundManager::PlayBGM(const std::string& sound) {
	FMOD::Sound* bgmSound = assetManager.GetBGM(sound);
	FMOD::Channel* channel;
	bgmSound->setMode(FMOD_LOOP_NORMAL);
	result = system->playSound(bgmSound, soundGroups[SoundGroup::SGBGM], false, &channel);
	if (result != FMOD_OK) {
		std::cout << "FMOD error: " << FMOD_ErrorString(result);
		return;
	}
	int channelID = getAvailableChannelID();
	soundChannels[channelID] = channel;
}


/**************************************************************************
* @brief This function handles playing sounds with advanced options 
* @param[in] sound - Name of the sound file to be played
* @param[in] type - Type of sound to be played (BGM/SFX)
* @param[in] volume - Volume modifier of the sound when played
* @param[in] looping - Boolean to determine if sound loops after ending
* @param[in] group - Sound group to play the sound within
* @return void
*************************************************************************/
void SoundManager::PlayAdvanced(const std::string& sound, SoundType type, float volume, bool looping, SoundGroup group) {
	FMOD::Sound* fetchedSound = nullptr;
	FMOD::Channel* channel;
	if (type == SoundType::BGM) {
		fetchedSound = assetManager.GetBGM(sound);
	}
	else if (type == SoundType::SFX) {
		fetchedSound = assetManager.GetSFX(sound);
	}
	else {
		std::cout << "Error: Sound type does not exist";
	}
	fetchedSound->setMode(looping ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF);
	result = system->playSound(fetchedSound, soundGroups[group], false, &channel);
	if (result != FMOD_OK) {
		std::cout << "FMOD error: " << FMOD_ErrorString(result);
		return;
	}
	channel->setVolume(volume);
	int channelID = getAvailableChannelID();
	soundChannels[channelID] = channel;
}


/**************************************************************************
* @brief This function handles pausing of all sounds
* @return void
*************************************************************************/
void SoundManager::PauseAll() {
	for (auto& [id, channel] : soundChannels) {
		channel->setPaused(true);
	}
}


/**************************************************************************
* @brief This function handles pausing of all sounds within a given group
* @param[in] group - Sound group to pause
* @return void
*************************************************************************/
void SoundManager::PauseGroup(SoundGroup group) {
	soundGroups[group]->setPaused(true);
}


/**************************************************************************
* @brief This function handles resumption of all sounds
* @return void
*************************************************************************/
void SoundManager::ResumeAll() {
	for (auto& [id, channel] : soundChannels) {
		channel->setPaused(false);
	}
}


/**************************************************************************
* @brief This function handles resumption of all sound groups
* @param[in] group - Sound group to resume
* @return void
*************************************************************************/
void SoundManager::ResumeGroup(SoundGroup group) {
	soundGroups[group]->setPaused(false);
}


/**************************************************************************
* @brief This function handles stopping of all sounds
* @return void
*************************************************************************/
void SoundManager::StopAll() {
	for (auto& [id, channel] : soundChannels) {
		channel->stop();
	}
	soundChannels.clear();
}


/**************************************************************************
* @brief This function handles stopping of all sound groups
* @param[in] group - Sound group to stop
* @return void
*************************************************************************/
void SoundManager::StopGroup(SoundGroup group) {
	std::vector<int> channelsToRemove;
	for (auto& [id, channel] : soundChannels) {
		FMOD::ChannelGroup* currentGroup;
		channel->getChannelGroup(&currentGroup);
		if (currentGroup == soundGroups[group]) {
			channel->stop();
			channelsToRemove.push_back(id);
		}
	}

	for (int id : channelsToRemove) {
		soundChannels.erase(id);
	}
}


/**************************************************************************
* @brief This function sets the volume of sounds within a sound group
* @param[in] group - Sound group to pause
* @param[in] volume - Volume to set the group to
* @return void
*************************************************************************/
void SoundManager::SetGroupVolume(SoundGroup group, float volume) {
	soundGroups[group]->setVolume(volume);
}



/**************************************************************************
* @brief This function gets the volume of sounds within a sound group
* @param[in] group - Sound group to pause
* @return Returns float of the volume of the sound group
*************************************************************************/
float SoundManager::GetGroupVolume(SoundGroup group) {
	float volume;
	soundGroups[group]->getVolume(&volume);
	return volume;
}


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