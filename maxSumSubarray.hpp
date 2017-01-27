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
#include <chrono>
#include <cstdlib>
#include <unordered_map>
#include <climits>
#include <limits>

#define OK_2_DISPLAY_2_STDOUT 0

// Prototypes.
void maxSumSubArray_1(std::vector<std::vector<int> > allData, std::vector<std::vector<int> > &results, int showTime);
void maxSumSubArray_2(std::vector<std::vector<int> > allData, std::vector<std::vector<int> > &results, int showTime);
long long int maxSumSubArray_3(std::vector<int> input, int start, int end);
std::vector<int> getSubArray(std::vector<int> input);
void maxSumSubArray_4(std::vector<std::vector<int> > allData, std::vector<std::vector<int> > &results, int showTime);
bool fileExists(std::string fileName);
void append2file(std::vector<std::vector<int> > &results);
long long int MaxSuffix(std::vector<int> arr, long long int start, long long int end);
long long int MaxPrefix(std::vector<int> arr, long long int start, long long int end);
