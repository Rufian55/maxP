/******************************************************************************
* Program maxSumSubarray.cpp reads a text file of space delimited ints and 
* writes the Maximum Sum Subarray and sum of each line to a seperate text file. 
* Compile with: g++ maxSumSubarray.cpp -o maxSum -g -Wall
* cs325-400-W17	29 Jan 2017	Project 1
******************************************************************************/
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

int main() {
	std::vector<std::vector<int> > allData;	// 2D final vector.
	std::ifstream file("MSS_Problems.txt");
	std::string eachLine;
	int eachInt;

	// Process the text file of ints.
	while (std::getline(file, eachLine)) {
		std::vector<int> lineData;		// 1D vector.
		std::stringstream inputStream(eachLine);

		while (inputStream >> eachInt) {

			// Some vague test comment...
			// Add the ints from each line to the 1D vector.
			lineData.push_back(eachInt);
		}
		// Push the 1D vector onto the 2D vector as one "line".
		allData.push_back(lineData);
	}
	return 0;
}