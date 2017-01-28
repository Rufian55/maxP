/**********************************************************************
* Program randArr generates a set of random numbers when generating
* input files for testing the maxSumSubarry.cpp, etc. programs.
* Usage:  ./randNum n > outputFile.txt
***********************************************************************/
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <ctime>
using namespace std;

int main(int argc, char *argv[]) {
	// Check usage.
	if (argc < 2) {
		cout << "USAGE: " << argv[0] << " n" << endl;
		cout << "or:    " << argv[0] << " n > outputFile" << endl;
		return 0;
	}

	// Bring in target value from command line.
	unsigned long long int targetN;
	sscanf(argv[1], "%llu", &targetN);

	// Seed random number gen.
	srand((unsigned)time(0));
	int ran;

	for (unsigned long long int count = 0; count < targetN; count++) {
		ran = (rand() % 256) - 128;
		cout << ran << " ";
	}
	cout << endl;

	return 0;
}