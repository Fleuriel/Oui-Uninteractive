//#include <fstream>
//#include <iostream>
//#include <Mapping.h>
//#include <string>
//
//
//	bool Mapping::MapBuilder(const char* mapname) {
//		int mapsize{ Mapping::rows * Mapping::columns };
//		std::string filepath{ "../maps/" };
//		std::string extension{ ".txt" };
//		std::ofstream ofs{ filepath + mapname + extension };
//		if (!ofs.is_open()) {
//			std::cerr << "Error creating file." << std::endl;
//			return false;
//		}
//		else {
//			ofs << "Rows: " << Mapping::rows << std::endl;
//			ofs << "Columns: " << Mapping::columns << std::endl;
//
//			for (int i = 0; i < columns; i++) {
//				for (int j = 0; j < rows; j++) {
//					ofs << entitymap[i * rows + j] << " ";
//					if (j == rows - 1)
//						ofs << std::endl;
//				}
//			}
//		}
//
//		return true;
//	}
//
//	bool Mapping::MapReader(const char* mapname) {
//		std::string filepath{ "../maps/" };
//		std::string extension{ ".txt" };
//		std::ifstream ifs{ filepath + mapname + extension };
//		if (!ifs.is_open()) {
//			std::cerr << "Error reading file." << std::endl;
//			return false;
//		}
//		else {
//			int rows{}, columns{};
//			std::string text{};
//			std::getline(ifs, text, ' ');
//			ifs >> rows;
//			std::cout << text << rows;
//			std::getline(ifs, text, ' ');
//			ifs >> columns;
//			std::cout << text << columns;
//
//			
//
//		}
//
//		return true;
//	}