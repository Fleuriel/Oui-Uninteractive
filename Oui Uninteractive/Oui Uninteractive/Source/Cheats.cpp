/**************************************************************************
 * @file Cheats.cpp
 * @author CHAN Aaron Jun Xiang
 * @par DP email: aaronjunxiang.chan@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 09-05-2023
 * @brief 
 *************************************************************************/

#include <Cheats.h>
#include <algorithm>
#include <iostream>

std::vector<std::string> cheatCodes{
	"skiplevel", // skip to next level
	"victory", // skip to winning screen
	"defeat", //skip to losing screen
	"godmodeon", // 2x dmg, invul
	"godmodeoff"
};

bool CheckCheatCode(const std::string& cheatCode) {
    return std::any_of(cheatCodes.begin(), cheatCodes.end(), [&](const std::string& cheat) { return cheatCode == cheat; });
}

void Cheat(std::string cheatCode) {
	if (cheatCode == "skiplevel") {
		SkipLevel();
	}
	if (cheatCode == "victory") {
		Victory();
	}
	if (cheatCode == "defeat") {
		Defeat();
	}
	if (cheatCode == "godmodeon") {
		GodModeOn();
	}
	if (cheatCode == "godmodeoff") {
		GodModeOff();
	}
}

void SkipLevel() {
	std::cout << "SKIPLEVEL" << std::endl;
}

void Victory() {
	std::cout << "VICTORY" << std::endl;
}

void Defeat() {
	std::cout << "DEFEAT" << std::endl;
}

void GodModeOn() {
	std::cout << "GODMODEON" << std::endl;
}

void GodModeOff() {
	std::cout << "DOGMODEON" << std::endl;
}