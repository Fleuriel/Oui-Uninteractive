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

class SoundManager {
public:
	void Init();
	void LoadSounds();
	void PlaySounds();
	void Shutdown();

	FMOD_RESULT result;
	FMOD::Sound* sound1, *sound2;
	FMOD::Channel* channel1;

	// For storing more sounds in the future. Test using basic 1 sound first
	//std::vector<FMOD::Sound*> bgmSounds;
	//std::vector<FMOD::Sound*> sfxSounds;
private:
	FMOD::System* system;
};

