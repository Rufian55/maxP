/******************************************************************************
* cs325-400-W17	Analysis of Algorithms	29 Jan 2017	Project 1
* Jonathon Horton	hortonjo@oregonstate.edu
* Chris Kearns		kearnsc@oregonstate.edu
* Dustin Pack		packdu@oregonstate.edu
*
* Program maxSumSubarray.cpp reads a text file of space delimited ints and 
* appends the Maximum Sum Subarray and sum of each line to a seperate text
* file. Compile with: g++ maxSumSubarray.cpp -o maxSum -g -Wall -std=c++11
* Call from CLI: "maxSum 1" to show with execution times, "maxSum 0" otherwise.
******************************************************************************/
#include "maxSumSubarray.hpp"

int main(int argc, char** argv) {
	if (argc < 2 || argc > 3 || atoi(argv[1]) < 0 || atoi(argv[1]) > 1) {
		cout << "Usage: \"maxSum 1 [input_file_name]\" or \"maxSum 0 [input_file_name]\"\n" <<
			"0 for do not show execution times, 1 to show the exection times.\n" <<
			"The input_file_name is optional, default is \"MSS_Problems.txt\"\n";
		exit(1);
	}

	int showTime = atoi(argv[1]);

	std::string theInputFile = "MSS_Problems.txt";
	if (argc == 3) {
		theInputFile = argv[2];
	}

	std::ifstream inputFile(theInputFile);

	std::vector<std::vector<int> > allData;	// 2D input vector.
	std::vector<std::vector<int> > results;	// 2d results vector.
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

	/* Since function maxSumsubarray_3() is recursive and involves multiple return statements,
	   we manually build results 2D vector here in main. Additionally, we time the call to 
	   maxSumSubarray_3 from main, so the call and final return, considered constants, are
	   included but considered negligible when comparing to the other maxSumSubArray functions.*/

	long long int maxSum;
 	std::vector<int> mssTotal; // 1D int vector (of length 1) to capture the maxSumSubarray total.
	results.clear();
	for (unsigned int i = 0; i < allData.size(); i++) {
		results.push_back(allData[i]);									// Add the input vector.
		results.push_back(getSubArray(allData[i]));							// Add the derived vector.

		// TIME FROM HERE...
		auto start = std::chrono::high_resolution_clock::now();				// [1]

		maxSum = maxSumSubArray_3(allData[i], 0, allData[i].size() - 1);			// Get the maxSum.

		auto end = std::chrono::high_resolution_clock::now();
		// ... TO HERE (line above).
		std::chrono::duration<double> execTime = end - start;

		if (showTime) {
			cout << std::fixed << "Elapsed time for maxSumSubArray_3, lineNum: "
				<< i + 1 << " = " << execTime.count() << '\n';
		}

		mssTotal.clear();
		mssTotal.push_back(maxSum);										// Add maxSum to mssTotal.
		results.push_back(mssTotal);										// Add the maxSum vector.
	}
	append2file(results);

	maxSumSubArray_4(allData, results, showTime);

	return 0;
}


/* Determine max sum of subarray with brute force method. All posible combinations
   of subarrays checked. O(n^3) [2] */
void maxSumSubArray_1(std::vector<std::vector<int> > allData, std::vector<std::vector<int> > &results, int showTime) {
	// 1D int vector to capture the maxSumSubarray elements.
	std::vector<int> resultsData;

	// 1D int vector (of length 1) to capture the maxSumSubarray total. 
	std::vector<int> mssTotal;

	// Clear 2D results vector (passed by ref, so old 1D vectors still hanging around).
	results.clear();

	// Process allData vector.
	for (unsigned int lineNum = 0; lineNum < allData.size(); lineNum++) {
		// TIME FROM HERE...
		auto start = std::chrono::high_resolution_clock::now();

		int max = INT_MIN;
		int sum = 0;
		int n = allData[lineNum].size();

		// Brute force n^3 [ ]
		for (int i = 0; i < n; i++) {
			for (int j = i; j < n; j++) {
				for (int k = i; k <= j; k++) {
					sum += allData[lineNum][k];
				}
				if (sum > max)
					max = sum;
				sum = 0; // Reset to 0 or sums all subarrays.
			}
		}

		auto end = std::chrono::high_resolution_clock::now();
		// ... TO HERE (line above).

		std::chrono::duration<double> execTime = end - start;

		if (showTime) {
			cout << std::fixed << "Elapsed time for maxSumSubArray_1, lineNum: " 
				<< lineNum + 1 << " = " << execTime.count() << '\n';
		}

		// Push the allData[lineNum] onto results.
		results.push_back(allData[lineNum]);

		// Push allData[lineNum][i] from index maxSumStart to maxSumEnd onto resultsData.
		resultsData.clear();

		resultsData = getSubArray(allData[lineNum]);

		// Push resultsData onto results.
		results.push_back(resultsData);

		// Push maxSum onto results[++i]
		mssTotal.clear();
		mssTotal.push_back(max);
		results.push_back(mssTotal);
	}
	append2file(results);
}


/* Determine max sum of subarray with brute force method. Keeps track of largest
	subarray checked during iteration. O(n^2) [3] */
void maxSumSubArray_2(std::vector<std::vector<int> > allData, std::vector<std::vector<int> > &results, int showTime) {
	// 1D int vector to capture the maxSumSubarray elements.
	std::vector<int> resultsData;

	// 1D int vector (of length 1) to capture the maxSumSubarray total. 
	std::vector<int> mssTotal;

	// Clear 2D results vector (passed by ref, so old 1D vectors still hanging around).
	results.clear();

	// Process allData vector.
	for (unsigned int lineNum = 0; lineNum < allData.size(); lineNum++) {
		// TIME FROM HERE...
		auto start = std::chrono::high_resolution_clock::now();

		long long int maxSum = 0;

		for (unsigned long long int i = 0; i < allData[lineNum].size(); i++) {
			long long int tempSum = 0;
			for (unsigned long long int j = i; j < allData[lineNum].size(); j++) {
				tempSum += allData[lineNum][j];
				if (tempSum > maxSum)
					maxSum = tempSum;
			}
		}

		auto end = std::chrono::high_resolution_clock::now();
		// ... TO HERE (line above).

		std::chrono::duration<double> execTime = end - start;

		if (showTime) {
			cout << std::fixed << "Elapsed time for maxSumSubArray_2, lineNum: " 
				<< lineNum + 1 << " = " << execTime.count() << '\n';
		}

		// Push the allData[lineNum] onto results.
		results.push_back(allData[lineNum]);

		// Push allData[lineNum][i] from index maxSumStart to maxSumEnd onto resultsData.
		resultsData.clear();

		resultsData = getSubArray(allData[lineNum]);

		// Push resultsData onto results.
		results.push_back(resultsData);

		// Push maxSum onto results[++i]
		mssTotal.clear();
		mssTotal.push_back(maxSum);
		results.push_back(mssTotal);
	}
	append2file(results);
}

/* Algorithm 3: Divide and Conquer
*  This algorithm will split the array into halves recursively and recombine.
*  We know the maximum subarray will be in the first half, the second half, or made
*  from the end of the first half and the beginning of the second half. O(nlogn).*/
long long int maxSumSubArray_3(std::vector<int> arr, int start, int end) {
	if (start == end)	// Base case n = 1
		return arr[start];
	else {			// Anything bigger gets broken down.
		long long int mid = (start + end) / 2;

		long long int leftMax = maxSumSubArray_3(arr, start, mid);
		long long int rightMax = maxSumSubArray_3(arr, mid + 1, end);

		long long int suffix = MaxSuffix(arr, start, mid);
		long long int prefix = MaxPrefix(arr, mid + 1, end);

		// Return whichever has the highest value.
		if (leftMax >= rightMax && leftMax >= (suffix + prefix)) {
			return leftMax;
		}
		else if (rightMax >= leftMax && rightMax >= (suffix + prefix)) {
			return rightMax;
		}
		else {
			return (suffix + prefix);
		}
	}
}

/* The iterative method that scans the array left to right, keeping the best
   sum and current sum. Runs O(n). [4] */
void maxSumSubArray_4(std::vector<std::vector<int> > allData, std::vector<std::vector<int> > &results, int showTime) {
	std::vector<int> resultsData;	// 1D int vector to capture the maxSumSubarray elements.
	std::vector<int> mssTotal;	// 1D int vector (of length 1) to capture the maxSumSubarray total.

	// Clear 2D results vector (passed by ref, so old 1D vectors still hanging around).
	results.clear();

	// Process the 2D vector allData.
	for (unsigned int lineNum = 0; lineNum < allData.size(); lineNum++) {
		long long int currentSum = 0;
		long long int maxSum = std::numeric_limits<int>::min();  //Initially set MaxSum to lowest possible integer.
		long long int currentArrayStart = 0;
		long long int maxStart = 0; //Beginning index of the max subarray
		long long int maxEnd = 0; //Ending index of the max subarray

		// TIME FROM HERE...
		auto start = std::chrono::high_resolution_clock::now();

		/* Determine max sum. O(n) */
		for (unsigned int i = 0; i < allData[lineNum].size(); i++) {
			currentSum = currentSum + allData[lineNum][i];
			if (currentSum > maxSum) {
				maxSum = currentSum;
				maxStart = currentArrayStart;
				maxEnd = i;
			}
			else if (currentSum < 0) {
				currentSum = 0;
				currentArrayStart = i + 1;
			}
		}

		auto end = std::chrono::high_resolution_clock::now();
		// ... TO HERE (line above).

		std::chrono::duration<double> execTime = end - start;

		if (showTime) {
			cout << std::fixed << "Elapsed time for maxSumSubArray_4, lineNum: " 
				<< lineNum + 1 << " = " << execTime.count() << '\n';
		}

		// Push the allData[lineNum] onto results.
		results.push_back(allData[lineNum]);

		// Push allData[lineNum][i] from index maxSumStart to maxSumEnd onto resultsData.
		resultsData.clear();

		for (long long int i = maxStart; i <= maxEnd; i++) {
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


// Uses stat() to check for file existence. [5]
bool fileExists(std::string fileName) {
	struct stat buffer;
	return (stat(fileName.c_str(), &buffer) == 0);
}


// Appends results data to text file. //cout's are for testing.
void append2file(std::vector<std::vector<int> > &results) {

	// Open the results file for appending.	[6]
	std::ofstream resultFile("MSS_Results.txt", std::ios_base::app);

	int skipLines = 0;
	// Test print results.  Change "cout" to "resultFile" for file writing.
	for (unsigned int i = 0; i < results.size(); i++) {
		skipLines++;
		for (unsigned int j = 0; j < results[i].size(); j++) {
			if(OK_2_DISPLAY_2_STDOUT == 1){
				cout << results[i][j];
				cout << " ";
			}
			else {
				resultFile << results[i][j];
				resultFile << " ";
			}
		}

		if (OK_2_DISPLAY_2_STDOUT == 1) {
			cout << '\n';
		}
		else {
			resultFile << '\n';
		}

		if (skipLines % 3 == 0) {
			if (OK_2_DISPLAY_2_STDOUT == 1) {
				cout << '\n';
			}
			else {
				resultFile << '\n';
			}
		}
	}
	resultFile.close();
}


/******************************************************************************
* Helper functions for maxSumSubArray_3, which will compute maximum prefix and
* suffixes and append maxSumSubArray found info to MSS_Results.txt
******************************************************************************/

// Finds the rightmost maximum sum
long long int MaxSuffix(std::vector<int> arr, long long int start, long long int end) {
	long long int maxSum = arr[end];
	long long int sum = 0;
	for (long long int j = end; j >= start; j--) {
		sum = sum + arr[j];
		if (sum > maxSum)
			maxSum = sum;
	}
	return maxSum;
}

// Finds the leftmost maximum sum
long long int MaxPrefix(std::vector<int> arr, long long int start, long long int end) {
	long long int maxSum = arr[start];
	long long int sum = 0;
	for (long long int j = start; j <= end; j++) {
		sum = sum + arr[j];
		if (sum > maxSum)
			maxSum = sum;
	}
	return maxSum;
}


// Returns subArray "?" from input vector arr.
std::vector<int> getSubArray(std::vector<int> arr) {
	long long int n = arr.size();	// Get size of input vector.
	std::vector<int> subArray;	// Create vector to be returned.
	long long int max2date = INT_MIN;
	long long int maxEnd = 0;
	long long int start = 0;
	long long int end = 0;
	long long int temp = 0;
	// O(n).
	for (long long int i = 0; i < n; i++) {
		maxEnd += arr[i];
		if (max2date < maxEnd) {
			max2date = maxEnd;
			start = temp;
			end = i;
		}
		if (maxEnd < 0) {
			maxEnd = 0;
			temp = i + 1;
		}
	}
	for (long long int i = start; i <= end; i++) {
		subArray.push_back(arr[i]);
	}
	return subArray;
}


/* CITATIONS: Code adapted from the following sources:
[1] http://en.cppreference.com/w/cpp/chrono/high_resolution_clock/now
[2] https://github.com/julycoding/The-Art-Of-Programming-By-July/blob/master/ebook/en/07.0.md
[3] https://users.cs.fiu.edu/~weiss/dsaa_c++/code/MaxSumTest.cpp
[4] Introduction to Algorithms, 3rd ed., CLRS, pg. 214, Minimum and Maximum Algorithm.
[5] http://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c
[6] http://stackoverflow.com/questions/26084885/appending-to-a-file-with-ofstream
*/