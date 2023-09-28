/**************************************************************************
 * @file Mapping.cpp
 * @author CHAN Aaron Jun Xiang
 * @par DP email: aaronjunxiang.chan@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 09-05-2023
 * @brief Implementation of mapping functions.
 *
 * This file contains the implementation of two mapping-related functions: `MapBuilder` and `MapReader`.
 * These functions are used to build and save a mapping to a text file and read and load a mapping
 * from a text file, respectively. The mapping data includes the number of rows, columns, and an entity mapping.
 * These functions provide the functionality to create and manipulate mapping data files for the project.
 *
 * @see Mapping
 *************************************************************************/

#include <fstream>
#include <iostream>
#include <Mapping.h>
#include <string>


	/*************************************************************************
	 * @brief Build and save a mapping to a text file.
	 *
	 * This function takes a Mapping object and writes its data to a text file in a specified
	 * directory. The file is created with the provided filename and contains information about
	 * the number of rows and columns in the mapping, as well as the entity mapping data.
	 *
	 * @param map A Mapping object containing the mapping data to be saved.
	 * @return `true` if the mapping was successfully saved, `false` if an error occurred.
	 *************************************************************************/
	bool Mapping::MapBuilder(Mapping map) {

		//int mapsize{ map.rows* map.columns };

		// Define the directory path and file extension.
		std::string filepath{ "../maps/" };
		std::string extension{ ".txt" };

		// Create and open the output file stream.
		std::ofstream ofs{ filepath + map.filename + extension };

		// Check if the file stream is open and report an error if not.
		if (!ofs.is_open()) {
			std::cerr << "Error creating file." << std::endl;
			return false;
		}
		else {
			// Write the number of rows and columns to the file.
			ofs << "Rows: " << map.rows << std::endl;
			ofs << "Columns: " << map.columns << std::endl;

			// Write the entity mapping data to the file.
			for (int i = 0; i < map.rows; i++)
				for (int j = 0; j < map.columns; j++) {
					ofs << map.entitymap[i * map.columns + j] << " ";
					if (j == map.columns - 1)
						ofs << std::endl;
				}
		}

		// Close the file stream and return success.
		ofs.close();
		return true;
	}

	/*************************************************************************
	 * @brief Read and load a mapping from a text file.
	 *
	 * This function reads a mapping from a specified text file in a predefined directory
	 * and loads the data into the provided Mapping object. The file should contain information
	 * about the number of rows and columns in the mapping, as well as the entity mapping data.
	 *
	 * @param map A Mapping object where the loaded mapping data will be stored.
	 * @return `true` if the mapping was successfully read and loaded, `false` if an error occurred.
	 *************************************************************************/
	bool Mapping::MapReader(Mapping map) {

		// Define the directory path and file extension.
		std::string filepath{ "../maps/" };
		std::string extension{ ".txt" };

		// Create and open the input file stream.
		std::ifstream ifs{ filepath + map.filename + extension };

		// Check if the file stream is open and report an error if not.
		if (!ifs.is_open()) {
			std::cerr << "Error reading file." << std::endl;
			return false;
		}
		else {
			std::string text{};
			// Read and parse the number of rows from the file.
			std::getline(ifs, text, ' ');
			ifs >> map.rows;
			std::cout << text << map.rows;
			// Read and parse the number of columns from the file.
			std::getline(ifs, text, ' ');
			ifs >> map.columns;
			std::cout << text << map.columns << std::endl;

			// Resize the entity mapping vector based on the read rows and columns.
			map.entitymap.resize(map.rows * map.columns);
			
			// Read and populate the entity mapping data from the file.
			for (int i = 0; i < map.rows; i++)
				for (int j = 0; j < map.columns; j++) {
					ifs >> map.entitymap[i * map.columns + j];
					std::cout << map.entitymap[i * map.columns + j] << " ";
				}

			std::cout << std::endl;
		}

		// Close the file stream and return success.
		ifs.close();
		return true;
	}