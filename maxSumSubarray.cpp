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

// Prototypes.
void maxSumSubArray_1(std::vector<std::vector<int> > allData, std::vector<std::vector<int> > &results);

int main() {
	std::vector<std::vector<int> > allData;	// 2D input vector.
	std::vector<std::vector<int> > results;	// 2d results vector.

	std::ifstream inputFile("MSS_TestProblems.txt");
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

	// Find the maxSumSubarray. Vector results modified in place.
	maxSumSubArray_1(allData, results);

	return 0;
}


void maxSumSubArray_1(std::vector<std::vector<int> > allData, std::vector<std::vector<int> > &results) {

	// 1D int vector to capture the maxSumSubarray elements.
	std::vector<int> resultsData;

	// 1D int vector (of length 1) to capture the maxSumSubarray total. 
	std::vector<int> mssTotal;

	for (unsigned int lineNum = 0; lineNum < allData.size(); lineNum++) {
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
	
	// Push the allData[lineNum] onto results.
	results.push_back(allData[lineNum]);

	// Push allData[lineNum][i] from index maxSumStart to maxSumEnd onto resultsData.
	resultsData.clear();
	for (unsigned int i = maxSumStart; i <= maxSumEnd; i++) {
		resultsData.push_back(allData[lineNum][i]);
	}

	// Push resultsData onto results.
	results.push_back(resultsData);

	// push maxSum onto results[++i]
	mssTotal.clear();
	mssTotal.push_back(maxSum);
	results.push_back(mssTotal);
	}

	// Open the results file for writing.
	std::ofstream resultFile("MSS_Results.txt");

	int skipLines = 0;
	// Test print results.  Change "cout" to "resultFile" for file writing.
	for (unsigned int i = 0; i < results.size(); i++) {
		skipLines++;
		for (unsigned int j = 0; j < results[i].size(); j++) {
			cout << results[i][j];
			cout << " ";
		}
		cout << '\n';
		if (skipLines % 3 == 0) {
			cout << '\n';
		}
	}

	resultFile.close();
}