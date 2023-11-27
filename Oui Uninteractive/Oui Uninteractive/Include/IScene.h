#pragma once
/**************************************************************************
 * @file PhysicsBody.h
 * @author CHEAH Tristan Tze Hong
 * @par DP email: t.cheah@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 27-09-2023
 * @brief This file contains the declaration of the IScene Class,
 *		  which is a IComponent to be contained in GameObject. It holds
 *		  functions to enable scene transition in the engine.
 *************************************************************************/


class IScene {
public:

	unsigned int sceneID;
	
	/**************************************************************************
	* @brief Constructor
	* @param id   [Set ID to sceneID]
	*************************************************************************/
	IScene(unsigned int id) {
		sceneID = id;
	};
	/**************************************************************************
	* @brief Load the instance of the IScene.
	*************************************************************************/
	virtual void Load() = 0;

	/**************************************************************************
	* @brief Initialize this instance of the IScene component via file
	*************************************************************************/
	virtual void Initialize() = 0;

	/**************************************************************************
	* @brief Update IScene System
	* @return void
	*************************************************************************/
	virtual void Update(float dt) = 0;

	/**************************************************************************
	* @brief Draws IScene Systems
	* @return void
	*************************************************************************/
	virtual void Draw() = 0;

	/**************************************************************************
	* @brief Free the IScene Systems
	* @return void
	*************************************************************************/
	virtual void Free() = 0;

	/**************************************************************************
	* @brief Unload the IScene Systems
	* @return void
	*************************************************************************/
	virtual void Unload() = 0;

	/**************************************************************************
	* @destructor
	*************************************************************************/
	virtual ~IScene() {};
};