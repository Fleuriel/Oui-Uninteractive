#include <Animation.h>
//#include <OpenGLApplication.h>
#include <ParticleSystem.h>
#include "GameStateManager.h"


#define numberOfElements 1
std::vector<bool>timerSwitches(numberOfElements);
std::vector<float>timers(numberOfElements);
std::vector<std::pair<float, float>> gridInfoContainer[numberOfElements];
std::vector<int> IDContainer;

extern ParticleSystem particleSystem;

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
		}
	}
}
int particleNumber{};
float Animationduration;
void UpdateAnimation() {
	if (timerSwitches[animationTopLeftToBottomRight] == true) {
		

		if ( timers[animationTopLeftToBottomRight] > particleNumber * Animationduration / (gridInfoContainer[animationTopLeftToBottomRight].size() - 1)) {
			particleSystem.particles[IDContainer[particleNumber]-1].visibility = true;
			++particleNumber;
		}

		if (timers[animationTopLeftToBottomRight] > Animationduration) {
			timerSwitches[animationTopLeftToBottomRight] = false;
			timers[animationTopLeftToBottomRight] = 0.f;
			particleNumber = 0;
			std::cout << "PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP";
		}
		
	}
}

void Animation_Top_Left_To_Bottom_Right(int rows, int columns , float duration) {
	if (timerSwitches[animationTopLeftToBottomRight] == false) {
		timerSwitches[animationTopLeftToBottomRight] = true;
		gridInfoContainer[animationTopLeftToBottomRight] = Grid(rows, columns);
		Animationduration = duration;
		float postAnimationDuration = 5;
		std::pair<float, float> dimensions = gridInfoContainer[animationTopLeftToBottomRight][0];
		for (int c = 1; c <= gridInfoContainer[0].size() - 1; c++) {
			Particle newparticle(gridInfoContainer[animationTopLeftToBottomRight][c].first, gridInfoContainer[animationTopLeftToBottomRight][c].second,
				dimensions.first, dimensions.second, 0, 0, Animationduration + postAnimationDuration, false);
			IDContainer.push_back(newparticle.ID);
			particleSystem.particles.push_back(newparticle);
		}
	}
}

void Animation_Spiral_From_Top_Left(int rows, int columns, float duration) {
	
}