#include <fstream>
#include <iostream>
#include <Mapping.h>
#include <string>


	bool Mapping::MapBuilder(Mapping map) {
		//int mapsize{ map.rows* map.columns };
		std::string filepath{ "../maps/" };
		std::string extension{ ".txt" };
		std::ofstream ofs{ filepath + map.filename + extension };
		if (!ofs.is_open()) {
			std::cerr << "Error creating file." << std::endl;
			return false;
		}
		else {
			ofs << "Rows: " << map.rows << std::endl;
			ofs << "Columns: " << map.columns << std::endl;

			for (int i = 0; i < map.rows; i++)
				for (int j = 0; j < map.columns; j++) {
					ofs << map.entitymap[i * map.columns + j] << " ";
					if (j == map.columns - 1)
						ofs << std::endl;
				}
		}

		return true;
	}

	bool Mapping::MapReader(Mapping map) {
		std::string filepath{ "../maps/" };
		std::string extension{ ".txt" };
		std::ifstream ifs{ filepath + map.filename + extension };
		if (!ifs.is_open()) {
			std::cerr << "Error reading file." << std::endl;
			return false;
		}
		else {
			std::string text{};
			std::getline(ifs, text, ' ');
			ifs >> map.rows;
			std::cout << text << map.rows;
			std::getline(ifs, text, ' ');
			ifs >> map.columns;
			std::cout << text << map.columns << std::endl;

			map.entitymap.resize(map.rows * map.columns);
			

			for (int i = 0; i < map.rows; i++)
				for (int j = 0; j < map.columns; j++) {
					ifs >> map.entitymap[i * map.columns + j];
					std::cout << map.entitymap[i * map.columns + j] << " ";
				}

			std::cout << std::endl;
		}

		return true;
	}