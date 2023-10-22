#include <Animation.h>
//#include <OpenGLApplication.h>
#include <ParticleSystem.h>
#include "GameStateManager.h"


#define numberOfElements 1
std::vector<bool>timerSwitches(numberOfElements);
std::vector<float>timers(numberOfElements);
std::vector<std::pair<float, float>> gridInfoContainer[numberOfElements];

std::vector<std::pair<float, float>> Grid(int rows, int columns) {

	float width{ static_cast<float>(windowSize.first / columns) }, height{ static_cast<float>(windowSize.second / rows) };
	//std::cout << "WIDTH: " << width << " HEIGHT: " << height << "\n";

	std::vector<std::pair<float, float>> gridInfo;
	std::pair<float, float> boxDimensions{ width,height };
	gridInfo.emplace_back(boxDimensions);

	float topLeftxCoord{ (width / 2) - (windowSize.first / 2) }, topLeftyCoord{ (windowSize.second / 2) - (height / 2) };

	float xCoord = topLeftxCoord;
	float yCoord = topLeftyCoord;
	for (int i = 0; i < rows; ++i) {
		xCoord = topLeftxCoord;
		for (int i = 0; i < columns; ++i) {
			std::pair<float, float> coords{ xCoord, yCoord };
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
			//std::cout << "TIMERRRRRRRRRRR" << timers[i] << "\n";
		}
	}
	//std::cout << "\nTIMERRRRRRRRR" << timers[0] << "\n";
}
int particleNumber = 1;
float Animationduration;
void UpdateAnimation() {
	if (timerSwitches[0] == true) {

		std::pair<float, float> dimensions = gridInfoContainer[0][0];

		float postanimationlifespan = 5;
		

		if ( timers[0] > particleNumber * Animationduration / (gridInfoContainer[0].size() - 1)) {
			Particle newparticle(gridInfoContainer[0][particleNumber].first, gridInfoContainer[0][particleNumber].second,
				dimensions.first, dimensions.second,
				0, 0,
				postanimationlifespan + Animationduration - particleNumber * Animationduration / (gridInfoContainer[0].size() - 1));
			++particleNumber;
		}

		if (particleNumber > gridInfoContainer[0].size()-1) {
			timerSwitches[0] = false;
			timers[0] = 0.f;
			particleNumber = 1;
		}


		
	}
}

void Animation_Top_Left_To_Bottom_Right(int rows, int columns , float duration) {
	if (!timerSwitches[0]) {
		timerSwitches[0] = true;
		gridInfoContainer[0] = Grid(rows, columns);
		Animationduration = duration;
	}
	//std::pair<float, float>dimensions{ 0.f,0.f };

	//int num = 0;
	//for (std::pair<float, float> info : Grid(rows, columns)) {
	//	if (!(dimensions.first * dimensions.second)) {
	//		dimensions = info;
	//		continue;
	//	}

	//	Particle newparticle(info.first, info.second, dimensions.first, dimensions.second, 0, 0);
	//	//std::cout << "Particle Number : " << ++num;
	//}

}