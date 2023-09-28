/**************************************************************************
 * @file Mapping.h
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


#include <vector>

class Mapping
{
public:

	int rows{};	//number of rows
	int columns{};	//number of columns
	std::vector<int> entitymap{};
	const char* filename{};	//name of file

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
	static bool MapBuilder(Mapping map);

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
	static bool MapReader(Mapping map);
};