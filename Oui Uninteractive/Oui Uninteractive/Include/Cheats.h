/**************************************************************************
 * @file Cheats.h
 * @author CHAN Aaron Jun Xiang
 * @par DP email: aaronjunxiang.chan@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 09-05-2023
 * @brief Implementation of cheat code functionalities for the game.
 *************************************************************************/

#include <vector>
#include <string>


/**************************************************************************
 * @brief Checks if a given cheat code is valid.
 * @param cheatCode The cheat code to check.
 * @return True if the cheat code is valid, false otherwise.
 *************************************************************************/
bool CheckCheatCode(const std::string&);

/**************************************************************************
 * @brief Skips to the next game level.
 *************************************************************************/
void SkipLevel();

/**************************************************************************
 * @brief Skips to the victory screen.
 *        Also changes the background and creates victory screen objects.
 *************************************************************************/
void Victory();

/**************************************************************************
 * @brief Skips to the defeat screen.
 *        Also changes the background and creates defeat screen objects.
 *************************************************************************/
void Defeat();

/**************************************************************************
 * @brief Activates god mode, making the player invulnerable with increased
		  damage.
 *************************************************************************/
void GodModeOn();

/**************************************************************************
 * @brief Deactivates god mode, restoring the player's health to its
		  maximum.
 *************************************************************************/
void GodModeOff();

/**************************************************************************
 * @brief Applies the effect of a cheat code.
 * @param cheatCode The cheat code to apply.
 *************************************************************************/
void Cheat(std::string);