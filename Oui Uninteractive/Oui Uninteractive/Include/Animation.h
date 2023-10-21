#include <vector>
#include <utility>

std::vector<std::pair<float, float>> Grid(int, int);
void UpdateAnimationTimers();
void UpdateAnimation();
void Animation_Top_Left_To_Bottom_Right(int rows, int columns, float speed);