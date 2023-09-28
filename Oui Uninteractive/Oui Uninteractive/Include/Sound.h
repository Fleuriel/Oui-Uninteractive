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
#include "ISystem.h"

class SoundManager : public ISystem {
public:
	SoundManager();
	void Initialize();
	virtual void Update(float dt);
	void LoadSounds();
	void PlayBGMSounds();
	void PlaySFXSounds();
	void TogglePlayChannel(FMOD::Channel* selectedChannel);

	 ~SoundManager() ;

	// File paths to the respective sounds
	std::filesystem::path bgmPath{"../sounds/bgm"};
	std::filesystem::path sfxPath{"../sounds/sfx"};

	FMOD_RESULT result; // To store FMOD function results

	// Container for sounds
	std::vector<FMOD::Sound*> bgmSounds{};
	std::vector<FMOD::Sound*> sfxSounds{};

	// Channels
	std::vector<FMOD::Channel*> bgmChannels{3};
	std::vector<FMOD::Channel*> sfxChannels{3};

	int sfxChoice;

private:
	FMOD::System* system;
};
extern SoundManager* soundManager;

#endif
