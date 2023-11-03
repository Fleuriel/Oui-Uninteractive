/**************************************************************************
 * @file Transition.cpp
 * @author Aaron Chan Jun Xiang
 * @par DP email: aaronjunxiang.chan@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 09-05-2023
 * @brief Implementation of transition-related functions and animations.
 *************************************************************************/

#include <Transition.h>
//#include <OpenGLApplication.h>
#include <ParticleSystem.h>
#include "GameStateManager.h"


#define numberOfElements 1
std::vector<bool>timerSwitches(numberOfElements);
std::vector<double>timers(numberOfElements);
std::vector<std::pair<double, double>> gridInfoContainer[numberOfElements];
std::vector<size_t> IDContainer;

int particleNumber{};
double Animationduration;

extern ParticleSystem particleSystem;


/**************************************************************************
 * @brief Generate a grid of coordinates.
 *
 * This function generates a grid of coordinates for a specified number of
 * rows and columns. The grid is positioned at the center of the screen
 * and evenly distributes the coordinates within the window size.
 *
 * @param rows The number of rows in the grid.
 * @param columns The number of columns in the grid.
 *
 * @return A vector of coordinate pairs representing the grid.
 *************************************************************************/
std::vector<std::pair<double, double>> Grid(int rows, int columns) {

	double width{ static_cast<double>(windowSize.first / columns) }, height{ static_cast<double>(windowSize.second / rows) };
	//std::cout << "WIDTH: " << width << " HEIGHT: " << height << "\n";

	std::vector<std::pair<double, double>> gridInfo;
	std::pair<double, double> boxDimensions{ width,height };
	gridInfo.emplace_back(boxDimensions);

	double topLeftxCoord{ (width / 2) - (static_cast<double>(windowSize.first) / 2) }, topLeftyCoord{ (static_cast<double>(windowSize.second) / 2) - (height / 2) };

	double xCoord = topLeftxCoord;
	double yCoord = topLeftyCoord;
	for (int i = 0; i < rows; ++i) {
		xCoord = topLeftxCoord;
		for (int j = 0; j < columns; ++j) {
			std::pair<double, double> coords{ xCoord, yCoord };
			gridInfo.emplace_back(coords);
			//Particle newparticle(xCoord, yCoord, width, height, 0, 0);
			xCoord += width;
		}
		yCoord -= height;
	}


	return gridInfo;
}

/**************************************************************************
 * @brief Update animation timers.
 *
 * This function updates animation timers for a set of elements. It checks
 * if the timer switch is active for each element and increments the timers
 * accordingly.
 *************************************************************************/
void UpdateAnimationTimers() {
	for (int i = 0; i < numberOfElements; ++i) {
		if (timerSwitches[i]) {
			timers[i] += GetDT();
		}
	}
}

/**************************************************************************
 * @brief Update animation based on timers and particle visibility.
 *
 * This function updates the animation for particles based on timers and
 * their visibility. It checks the timer switch for the 'animationTopLeftToBottomRight'
 * animation and increments the particleNumber when a certain time threshold is reached.
 * The function also handles resetting the animation when all particles have been shown
 * or when the animation duration is exceeded.
 *************************************************************************/
void UpdateAnimation() {
	if (timerSwitches[animationTopLeftToBottomRight] == true) {
		

		if ( timers[animationTopLeftToBottomRight] > static_cast<double> (particleNumber) * Animationduration / static_cast<double>(gridInfoContainer[animationTopLeftToBottomRight].size() - 1)) {

			particleSystem.particles[IDContainer[particleNumber]-1].visibility = true;
			//std::cout << "PARTICLE NUMBER : " << particleNumber;
			++particleNumber;
		}

		/*
		Choose one if statement.
		first if statement prioritises printing all particles, even if the program lagged and printed them at the wrong time
		second if statement prioritises following the animation duration
		*/


		if ((particleNumber > gridInfoContainer[0].size()-2) || timers[animationTopLeftToBottomRight] > Animationduration) {
			timerSwitches[animationTopLeftToBottomRight] = false;
			timers[animationTopLeftToBottomRight] = 0.f;
			particleNumber = 0;
		}
		
	}
}

/**************************************************************************
 * @brief Start the 'animationTopLeftToBottomRight' animation.
 *
 * This function initiates the animation with the specified number of rows, columns, and duration.
 * It sets the timer switch for the 'animationTopLeftToBottomRight' animation, generates the grid
 * information, and creates particles with the given dimensions and animation duration. The animation
 * will run for the specified duration and then keep the particles visible for an additional 'postAnimationDuration'.
 *
 * @param rows The number of rows in the grid.
 * @param columns The number of columns in the grid.
 * @param duration The duration of the animation.
 *************************************************************************/
void Animation_Top_Left_To_Bottom_Right(int rows, int columns , double duration) {
	if (timerSwitches[animationTopLeftToBottomRight] == false) {
		timerSwitches[animationTopLeftToBottomRight] = true;
		gridInfoContainer[animationTopLeftToBottomRight] = Grid(rows, columns);
		Animationduration = duration;
		double postAnimationDuration = 5;
		std::pair<double, double> dimensions = gridInfoContainer[animationTopLeftToBottomRight][0];
		for (int c = 1; c <= gridInfoContainer[0].size() - 1; c++) {
			Particle newparticle(static_cast<int>(gridInfoContainer[animationTopLeftToBottomRight][c].first), static_cast<int>(gridInfoContainer[animationTopLeftToBottomRight][c].second),
				static_cast<float>(dimensions.first), static_cast<float>(dimensions.second), 0, 0, static_cast<float>(Animationduration + postAnimationDuration), false);
			IDContainer.push_back(newparticle.ID);
			particleSystem.particles.push_back(newparticle);
		}
	}
}

//void Animation_Spiral_From_Top_Left(int rows, int columns, double duration) {}