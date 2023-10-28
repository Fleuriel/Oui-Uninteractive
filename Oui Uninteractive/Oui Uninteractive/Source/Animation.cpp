#include <Animation.h>
//#include <OpenGLApplication.h>
#include <ParticleSystem.h>
#include "GameStateManager.h"


#define numberOfElements 1
std::vector<bool>timerSwitches(numberOfElements);
std::vector<double>timers(numberOfElements);
std::vector<std::pair<double, double>> gridInfoContainer[numberOfElements];
std::vector<int> IDContainer;

extern ParticleSystem particleSystem;

std::vector<std::pair<double, double>> Grid(int rows, int columns) {

	double width{ static_cast<double>(windowSize.first / columns) }, height{ static_cast<double>(windowSize.second / rows) };
	//std::cout << "WIDTH: " << width << " HEIGHT: " << height << "\n";

	std::vector<std::pair<double, double>> gridInfo;
	std::pair<double, double> boxDimensions{ width,height };
	gridInfo.emplace_back(boxDimensions);

	double topLeftxCoord{ (width / 2) - (windowSize.first / 2) }, topLeftyCoord{ (windowSize.second / 2) - (height / 2) };

	double xCoord = topLeftxCoord;
	double yCoord = topLeftyCoord;
	for (int i = 0; i < rows; ++i) {
		xCoord = topLeftxCoord;
		for (int i = 0; i < columns; ++i) {
			std::pair<double, double> coords{ xCoord, yCoord };
			gridInfo.emplace_back(coords);
			//Particle newparticle(xCoord, yCoord, width, height, 0, 0);
			xCoord += width;
		}
		yCoord -= height;
	}


	return gridInfo;
}

void UpdateAnimationTimers() {
	for (int i = 0; i < numberOfElements; ++i) {
		if (timerSwitches[i]) {
			timers[i] += GetDT();
		}
	}
}
int particleNumber{};
double Animationduration;
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

void Animation_Top_Left_To_Bottom_Right(int rows, int columns , double duration) {
	if (timerSwitches[animationTopLeftToBottomRight] == false) {
		timerSwitches[animationTopLeftToBottomRight] = true;
		gridInfoContainer[animationTopLeftToBottomRight] = Grid(rows, columns);
		Animationduration = duration;
		double postAnimationDuration = 5;
		std::pair<double, double> dimensions = gridInfoContainer[animationTopLeftToBottomRight][0];
		for (int c = 1; c <= gridInfoContainer[0].size() - 1; c++) {
			Particle newparticle(gridInfoContainer[animationTopLeftToBottomRight][c].first, gridInfoContainer[animationTopLeftToBottomRight][c].second,
				dimensions.first, dimensions.second, 0, 0, Animationduration + postAnimationDuration, false);
			IDContainer.push_back(newparticle.ID);
			particleSystem.particles.push_back(newparticle);
		}
	}
}

void Animation_Spiral_From_Top_Left(int rows, int columns, double duration) {
	
}