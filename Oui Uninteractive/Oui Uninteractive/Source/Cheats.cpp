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
#include <SceneManager.h>
#include <HealthComponent.h>

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
	if (cheatCode == "skiplevel")
		SkipLevel();
	if (cheatCode == "victory")
		Victory();
	if (cheatCode == "defeat")
		Defeat();
	if (cheatCode == "godmodeon")
		GodModeOn();
	if (cheatCode == "godmodeoff")
		GodModeOff();
}

void SkipLevel() {
	sceneManager->nextSceneID++;
	std::cout << "SKIPLEVEL" << std::endl;
}

void Victory() {
	//sceneManager->nextSceneID = victorysceneid
	std::cout << "VICTORY" << std::endl;
}

void Defeat() {
	//sceneManager->nextSceneID = defeatsceneid
	std::cout << "DEFEAT" << std::endl;
}

void GodModeOn() {
	int invincibilityHP = 696969;
	GameObject* player = objectFactory->GetGameObjectsByType("Player")[0];
	if (player != nullptr){
		auto playercomponent = GET_COMPONENT(player, HealthComponent, ComponentType::HEALTH);
		playercomponent->currentHealth = invincibilityHP;
	}

	std::cout << "GODMODEON" << std::endl;
}

void GodModeOff() {
	// wait Austin gor gor push code
	GameObject* player = objectFactory->GetGameObjectsByType("Player")[0];
	if (player != nullptr) {
		auto playercomponent = GET_COMPONENT(player, HealthComponent, ComponentType::HEALTH);
		playercomponent->currentHealth = playercomponent->maxHealth;
	}
	std::cout << "DOGMODEON" << std::endl;
}