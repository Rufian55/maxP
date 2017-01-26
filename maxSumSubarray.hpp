/******************************************************************************
* cs325-400-W17	Analysis of Algorithms	29 Jan 2017	Project 1
* Jonathon Horton	hortonjo@oregonstate.edu
* Chris Kearns		kearnsc@oregonstate.edu
* Dustin Pack		packdu@oregonstate.edu
*
* Program maxSumSubarray.hpp is the header file for maxSumSubarray.cpp
* Call from CLI: "maxSum 1" to show with execution times, "maxSum 0" otherwise.
* See makefile for compilation.
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
#include <unordered_map>
#include <climits>


class Timer {
private:
	timespec begin, end;
public:
	Timer() {
		clock_gettime(CLOCK_REALTIME, &begin);
	}
	double elapsed() {
		clock_gettime(CLOCK_REALTIME, &end);
		return end.tv_sec - begin.tv_sec + (end.tv_nsec - begin.tv_nsec) * 100;
	}
	void reset() {
		clock_gettime(CLOCK_REALTIME, &begin);
	}

};


// Prototypes.
void maxSumSubArray_1(std::vector<std::vector<int> > allData, std::vector<std::vector<int> > &results, int showTime);
void maxSumSubArray_2(std::vector<std::vector<int> > allData, std::vector<std::vector<int> > &results, int showTime);
int maxSumSubArray_3(std::vector<int> input, int start, int end);
std::vector<int> getSubArray(std::vector<int> input);
void maxSumSubArray_4();
bool fileExists(std::string fileName);
void append2file(std::vector<std::vector<int> > &results);
int MaxSuffix(std::vector<int> arr, int start, int end);
int MaxPrefix(std::vector<int> arr, int start, int end);

