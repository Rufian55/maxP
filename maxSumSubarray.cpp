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
using std::cout;
using std::cin;

// Prototypes.
void maxSumSubArray_1(std::vector<std::vector<int> > allData, std::vector<std::vector<int> > &results, int lineNum);

int main() {
	std::vector<std::vector<int> > allData;	// 2D input vector.
	std::vector<std::vector<int> > results;	// 2d results vector.

	std::ifstream inputFile("MSS_Problems.txt");
	std::string eachLine;
	int eachInt;

	// Input the text file of ints to allData.
	while (std::getline(inputFile, eachLine)) {
		std::vector<int> lineData;		// 1D vector.
		std::stringstream inputStream(eachLine);

		while (inputStream >> eachInt) {
			// Add the ints from each line to the 1D vector.
			lineData.push_back(eachInt);
		}
		// Push the 1D vector onto the 2D vector as one "line".
		allData.push_back(lineData);
	}
	inputFile.close();

	// Open the results file for writing.
	std::ofstream resultFile("MSS_Results.txt");

	// Find the maxSumSubarray. Vector results modified in place.
	for (unsigned int i = 0; i < allData.size(); i++) {
		maxSumSubArray_1(allData, results, i);

		// Write the 2D results vector to file.
		for (unsigned int h = 0; h < results.size(); h += 3) {
			for (unsigned int i = 0; i < results.size(); i++) {
				for (unsigned int j = 0; j < results[i].size(); j++) {
					resultFile << results[i][j];
					resultFile << " ";
				}
				resultFile << "\n";
			}
			resultFile << "\n";
		}
	}

	resultFile.close();
	return 0;
}


void maxSumSubArray_1(std::vector<std::vector<int> > allData, std::vector<std::vector<int> > &results, int lineNum) {

	// TIME FROM HERE...
	int maxSum = allData[lineNum][0];
	unsigned int maxSumStart = 0, maxSumEnd = 0;

	for (unsigned int i = 1; i < allData[lineNum].size(); i++) {
		int tempSum = 0;
		int j = i;
		while (j >= 0) {
			tempSum += allData[lineNum][j];
			if (tempSum > maxSum) {
				maxSum = tempSum;
				maxSumStart = j;
				maxSumEnd = i;
			}
			j--;
		}
	}
	// ...TO HERE!

	// 1D int vector to capture the maxSumSubarray elements.
	std::vector<int> resultsData;

	// 1D int vector (of length 1) to capture the maxSumSubarray total. 
	std::vector<int> mssTotal;

	// push the allData[i] onto results[i]
	results.push_back(allData[lineNum]);

	// push allData[++i][maxSumStart] to allData[i][maxSumEnd] onto results[i][j]
	resultsData.clear();
	for (unsigned int i = maxSumStart, j = 0; i <= maxSumEnd && j < allData.size(); i++, j++) {
		resultsData.push_back(allData[j][i]);
	}
	results.push_back(resultsData);

	// push maxSum onto results[++i]
	mssTotal.clear();
	mssTotal.push_back(maxSum);
	results.push_back(mssTotal);

/*
	cout << "\nMaxSum in the array : " << maxSum << '\n';
	cout << "MaxSumStart : " << allData[0][maxSumStart] << "  maxSumEnd : " << allData[0][maxSumEnd] << '\n';

	// Test print results.  works!
	for (unsigned int i = 0; i < results.size(); i++) {
		for (unsigned int j = 0; j < results[i].size(); j++) {
			cout << results[i][j];
			cout << " ";
		}
		cout << "\n";
	}
*/
}