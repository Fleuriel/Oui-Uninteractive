/**************************************************************************
 * @file Transition.h
 * @author Aaron Chan Jun Xiang
 * @par DP email: aaronjunxiang.chan@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 09-05-2023
 * @brief Declarations of transition-related functions and animations.
 *************************************************************************/


#include <vector>
#include <utility>


enum {
	animationTopLeftToBottomRight, animationSpiralFromTopLeft
};

std::vector<std::pair<double, double>> Grid(int, int);
void UpdateAnimationTimers();
void UpdateAnimation();
void Animation_Top_Left_To_Bottom_Right(int rows, int columns, double duration);
//void Animation_Spiral_From_Top_Left(int rows, int columns, double duration);