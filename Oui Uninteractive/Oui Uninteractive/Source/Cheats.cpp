/**************************************************************************
 * @file Cheats.cpp
 * @author CHAN Aaron Jun Xiang
 * @par DP email: aaronjunxiang.chan@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 09-05-2023
 * @brief Implementation of cheat code functionalities for the game.
 *************************************************************************/

#include <Cheats.h>
#include <algorithm>
#include <iostream>
#include <SceneManager.h>
#include <HealthComponent.h>
#include <Background.h>

 // List of available cheat codes
std::vector<std::string> cheatCodes{
	"skiplevel", // skip to next level
	"victory", // skip to winning screen
	"defeat", //skip to losing screen
	"godmodeon", // 2x dmg, invul
	"godmodeoff"
};

/**************************************************************************
 * @brief Checks if a given cheat code is valid.
 * @param cheatCode The cheat code to check.
 * @return True if the cheat code is valid, false otherwise.
 *************************************************************************/
bool CheckCheatCode(const std::string& cheatCode) {
    return std::any_of(cheatCodes.begin(), cheatCodes.end(), [&](const std::string& cheat) { return cheatCode == cheat; });
}

/**************************************************************************
 * @brief Applies the effect of a cheat code.
 * @param cheatCode The cheat code to apply.
 *************************************************************************/
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

/**************************************************************************
 * @brief Skips to the next game level.
 *************************************************************************/
void SkipLevel() {
	sceneManager->nextSceneID++;
	std::cout << "SKIPLEVEL" << std::endl;
}

/**************************************************************************
 * @brief Skips to the victory screen.
 *        Also changes the background and creates victory screen objects.
 *************************************************************************/
void Victory() {
	//sceneManager->nextSceneID = victorysceneid
	std::cout << "VICTORY" << std::endl;
}

/**************************************************************************
 * @brief Skips to the defeat screen.
 *        Also changes the background and creates defeat screen objects.
 *************************************************************************/
void Defeat() {
	//sceneManager->nextSceneID = defeatsceneid
	//Should change background to defeat screen (not the entire defeat screen as an object, then objects as buttons to click
	background.SetBackGround(assetManager.GetTexture("DefeatScreen"));
	objectFactory->BuildObjectFromFile(std::string("assets/scenes/DefeatScreen.json"));  //temporary
	std::cout << "DEFEAT" << std::endl;
}

/**************************************************************************
 * @brief Activates god mode, making the player invulnerable with increased 
		  damage.
 *************************************************************************/
void GodModeOn() {
	if (objectFactory->GetGameObjectsByType("Player").size() == 0)
		return;

	int invincibilityHP = 696969;
	GameObject* player = objectFactory->GetGameObjectsByType("Player")[0];
	if (player != nullptr){
		auto playercomponent = GET_COMPONENT(player, HealthComponent, ComponentType::HEALTH);
		playercomponent->currentHealth = invincibilityHP;
		playercomponent->maxHealth = invincibilityHP;
	}

	std::cout << "GODMODEON" << std::endl;
}

/**************************************************************************
 * @brief Deactivates god mode, restoring the player's health to its 
		  maximum.
 *************************************************************************/
void GodModeOff() {
	if (objectFactory->GetGameObjectsByType("Player").size() == 0)
		return;

	GameObject* player = objectFactory->GetGameObjectsByType("Player")[0];
	if (player != nullptr) {
		int prefabHealth = GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName("PlayerPrefab"), HealthComponent, ComponentType::HEALTH)->maxHealth;
		auto playercomponent = GET_COMPONENT(player, HealthComponent, ComponentType::HEALTH);
		playercomponent->currentHealth = prefabHealth;
		playercomponent->maxHealth = prefabHealth;
	}
	std::cout << "DOGMODEON" << std::endl;
}