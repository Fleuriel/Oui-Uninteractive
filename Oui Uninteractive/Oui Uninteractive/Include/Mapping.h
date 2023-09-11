
#include <vector>

class Mapping
{
public:

	int rows{};
	int columns{};
	std::vector<int> entitymap{};
	const char* filename{};

	static bool MapBuilder(Mapping map);
	static bool MapReader(Mapping map);
};