/**************************************************************************
 * @file Sound.h
 * @author
 * @par DP email:
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 09-05-2023
 * @brief This source file contains the code to setup and run the editor
 *************************************************************************/
#pragma once

#include <fmod/fmod.hpp>
#include <fmod/fmod_errors.h>
#include <vector>
#include <filesystem> 
#include "ISystem.h"

class SoundManager : public ISystem {
public:
	void Initialize();
	virtual void Update(float dt);
	void LoadSounds();
	void PlaySounds();

	 ~SoundManager() ;

	// File paths to the respective sounds
	std::filesystem::path bgmPath{"../Sounds/bgm"};
	std::filesystem::path sfxPath{"../Sounds/sfx"};

	FMOD_RESULT result; // To store FMOD function results

	// Container for sounds
	std::vector<FMOD::Sound*> bgmSounds{};
	std::vector<FMOD::Sound*> sfxSounds{};

	FMOD::Channel* channel1;

	// For storing more sounds in the future. Test using basic 1 sound first
	//std::vector<FMOD::Sound*> bgmSounds;
	//std::vector<FMOD::Sound*> sfxSounds;
	// Note to self: explore using a std::map to store a "sound name" and a sound object tgt
private:
	FMOD::System* system;
};
extern SoundManager* soundManager;

