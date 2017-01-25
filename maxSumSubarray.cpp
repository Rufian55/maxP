/******************************************************************************
* cs325-400-W17	Analysis of Algorithms	29 Jan 2017	Project 1
* Jonathon Horton	hortonjo@oregonstate.edu
* Chris Kearns		kearnsc@oregonstate.edu
* Dustin Pack		packdu@oregonstate.edu
*
* Program maxSumSubarray.cpp reads a text file of space delimited ints and 
* appends the Maximum Sum Subarray and sum of each line to a seperate text
* file. Compile with: g++ maxSumSubarray.cpp -o maxSum -g -Wall
* Call from CLI: "maxSum 1" to show with execution times, "maxSum 0" otherwise.
******************************************************************************/
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using std::cout;
#include <sys/stat.h>
#include <ctime>
#include <cstdlib>

class Timer {
	private:
		timespec begin, end;
	public:
		Timer() {
			clock_gettime(CLOCK_REALTIME, &begin);
		}
		double elapsed() {
			clock_gettime(CLOCK_REALTIME, &end);
			return end.tv_sec - begin.tv_sec + (end.tv_nsec - begin.tv_nsec);
	}
	void reset() {
		clock_gettime(CLOCK_REALTIME, &begin);
	}

};


// Prototypes.
void maxSumSubArray_1(std::vector<std::vector<int> > allData, std::vector<std::vector<int> > &results, int showTime);
void maxSumSubArray_2(std::vector<std::vector<int> > allData, std::vector<std::vector<int> > &results, int showTime);
void maxSumSubArray_3();
void maxSumSubArray_4();
bool fileExists(std::string fileName);
void append2file(std::vector<std::vector<int> > &results);

int main(int argc, char** argv) {
	if (argc != 2 || atoi(argv[1]) < 0 || atoi(argv[1]) > 1) {
		cout << "Usage: \"maxSum 1\" or \"maxSum 0\"\n" <<
			"0 for do not show execution times, 1 otherwise.\n";
		exit(1);
	}

	int showTime = atoi(argv[1]);

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

	// Since we will have multiple write/append calls, we delete the old
	// MSS_Results.txt file first to ensure a "clean start".
	if (fileExists("MSS_Results.txt")) {
		if (remove("MSS_Results.txt") != 0) {
			perror("Error deleting old MSS_Results.txt: ");
		}
	}

	// Find the maxSumSubarray and append to MSS_Results.txt. Vector results modified in place.
	maxSumSubArray_1(allData, results, showTime);
	maxSumSubArray_2(allData, results, showTime);
	maxSumSubArray_3();
	maxSumSubArray_4();

	return 0;
}


void maxSumSubArray_1(std::vector<std::vector<int> > allData, std::vector<std::vector<int> > &results, int showTime) {

	// 1D int vector to capture the maxSumSubarray elements.
	std::vector<int> resultsData;

	// 1D int vector (of length 1) to capture the maxSumSubarray total. 
	std::vector<int> mssTotal;

	// Clear 2D results vector (passed by ref, so old 1D vectors still hanging around).
	results.clear();

	Timer algoTime;

	/* Determine max sum of subarray with brute force method. All posible combinations
	   of subarrays checked. O(n^3) [3] */
	for (unsigned int lineNum = 0; lineNum < allData.size(); lineNum++) {
		// TIME FROM HERE...
		double start = algoTime.elapsed();

		int maxSum = allData[lineNum][0];
		unsigned int maxSumBegin = 0, maxSumEnd = 0;

		for (unsigned int i = 1; i < allData[lineNum].size(); i++) {
			int temp = 0;
			int j = i;
			while (j >= 0) {
				temp += allData[lineNum][j];
				if (temp > maxSum) {
					maxSum = temp;
					maxSumBegin = j;
					maxSumEnd = i;
				}
				j--;
			}
		}

		// ...TO HERE!
		algoTime.reset();
		double stop = algoTime.elapsed();
		// execTime a global.
		double execTime = ((start - stop) / (double)CLOCKS_PER_SEC);
		if (showTime) {
			cout << std::fixed << "Elapsed time for maxSumSubArray, lineNum: " << lineNum + 1 << " = " << execTime << '\n';
		}

		// Push the allData[lineNum] onto results.
		results.push_back(allData[lineNum]);

		// Push allData[lineNum][i] from index maxSumStart to maxSumEnd onto resultsData.
		resultsData.clear();
		for (unsigned int i = maxSumBegin; i <= maxSumEnd; i++) {
			resultsData.push_back(allData[lineNum][i]);
		}

		// Push resultsData onto results.
		results.push_back(resultsData);

		// Push maxSum onto results[++i]
		mssTotal.clear();
		mssTotal.push_back(maxSum);
		results.push_back(mssTotal);
	}
	append2file(results);
}


void maxSumSubArray_2(std::vector<std::vector<int> > allData, std::vector<std::vector<int> > &results, int showTime) {

	// 1D int vector to capture the maxSumSubarray elements.
	std::vector<int> resultsData;

	// 1D int vector (of length 1) to capture the maxSumSubarray total. 
	std::vector<int> mssTotal;

	// Clear 2D results vector (passed by ref, so old 1D vectors still hanging around).
	results.clear();

	Timer algoTime;

	/* Determine max sum of subarray with brute force method. Keeps track of largest
		subarray checked during iteration. O(n^2) [3] */
	for (unsigned int lineNum = 0; lineNum < allData.size(); lineNum++) {
		// TIME FROM HERE...
		double start = algoTime.elapsed();

		int maxSum = allData[lineNum][0];
		unsigned int maxSumBegin = 0, maxSumEnd = 0;

		for (unsigned int i = 1; i < allData[lineNum].size(); i++) {
			int temp = 0;
			int j = i;
			int start = maxSumBegin;
			while (j >= start) {
				temp += allData[lineNum][j];
				if (temp > maxSum) {
					maxSum = temp;
					maxSumBegin = j;
					maxSumEnd = i;
				}
				j--;
			}
		}

		// ...TO HERE!
		algoTime.reset();
		double stop = algoTime.elapsed();
		// execTime a global.
		double execTime = ((start - stop) / (double)CLOCKS_PER_SEC);
		if (showTime) {
			cout << std::fixed << "Elapsed time for maxSumSubArray, lineNum: " << lineNum + 1 << " = " << execTime << '\n';
		}

		// Push the allData[lineNum] onto results.
		results.push_back(allData[lineNum]);

		// Push allData[lineNum][i] from index maxSumStart to maxSumEnd onto resultsData.
		resultsData.clear();
		for (unsigned int i = maxSumBegin; i <= maxSumEnd; i++) {
			resultsData.push_back(allData[lineNum][i]);
		}

		// Push resultsData onto results.
		results.push_back(resultsData);

		// Push maxSum onto results[++i]
		mssTotal.clear();
		mssTotal.push_back(maxSum);
		results.push_back(mssTotal);
	}
	append2file(results);
}


void maxSumSubArray_3() {

}


void maxSumSubArray_4() {

}


// Uses stat() to check for file existence. [1]
bool fileExists(std::string fileName) {
	struct stat buffer;
	return (stat(fileName.c_str(), &buffer) == 0);
}


// Appends results data to text file. 
void append2file(std::vector<std::vector<int> > &results) {

	// Open the results file for appending.	[2]
	std::ofstream resultFile("MSS_Results.txt", std::ios_base::app);

	int skipLines = 0;
	// Test print results.  Change "cout" to "resultFile" for file writing.
	for (unsigned int i = 0; i < results.size(); i++) {
		skipLines++;
		for (unsigned int j = 0; j < results[i].size(); j++) {
//			cout << results[i][j];
			resultFile << results[i][j];
//			cout << " ";
			resultFile << " ";

		}
//		cout << '\n';
		resultFile << '\n';
		if (skipLines % 3 == 0) {
//			cout << '\n';
			resultFile << '\n';
		}
	}
	resultFile.close();
}


/* CITATIONS: Code adapted from the following sources:
[1] http://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c
[2] http://stackoverflow.com/questions/26084885/appending-to-a-file-with-ofstream
[3] http://cpluspluscode.blogspot.com/2012/11/maximum-subarray-problem.html
*/