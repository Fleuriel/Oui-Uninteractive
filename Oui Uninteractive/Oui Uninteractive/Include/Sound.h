/**************************************************************************
 * @file Sound.h
 * @author LOW Wang Chun, Mark
 * @par DP email: l.wangchunmark@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 09-05-2023
 * @brief This source file contains the decleration of the SoundManager class used to setup FMOD and handle playing of sounds
 *************************************************************************/
#ifndef SOUND_H
#define SOUND_H

#include <fmod/fmod.hpp>
#include <fmod/fmod_errors.h>
#include <vector>
#include <filesystem> 
#include <queue>
#include "ISystem.h"

class SoundManager : public ISystem {
public:
	SoundManager();
	void Initialize();
	virtual void Update(float dt);
	int getAvailableChannelID();
	void recycleChannelID(int id);
	~SoundManager();

	FMOD_RESULT result{ FMOD_OK }; // To store FMOD function results

	// Class enum for types of sounds
	enum class SoundType {
		BGM,
		SFX
	};
	// Class enum for channels
	enum SoundGroup {
		SGSFX, SGBGM, SG2, SG3, SG4, SG5, SG6, SG7, SG8, SG9, SGCOUNT
	};

	void PlaySFX(const std::string& sound);
	void PlayBGM(const std::string& sound);
	void PlayAdvanced(const std::string& sound, SoundType type, float volume, bool looping, SoundGroup group);
	void PauseAll();
	void PauseGroup(SoundGroup group);
	void ResumeAll();
	void ResumeGroup(SoundGroup group);
	void StopAll();
	void StopGroup(SoundGroup group);
	void SetGroupVolume(SoundGroup group, float volume);
	float GetGroupVolume(SoundGroup group);

	// Channels
	std::map<int, FMOD::Channel*> soundChannels;
	std::vector<FMOD::ChannelGroup*> soundGroups{ SGCOUNT };
	

	//int sfxChoice{0};
	
	FMOD::System* system{ nullptr };

	// Queue to store not assigned channel IDs
	std::queue<int> availableIDs;
	
};
extern SoundManager* soundManager;

#endif
