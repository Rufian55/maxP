Instructions for program maxSub.

1. In a Linux* working directory of your choice, unzip cs325_400_W17_Group20_Assign_1.zip
2. You should see maxSumSubarray.cpp, maxSumSubarray.hpp, makefile, MSS_Results.txt,
   cs325_400_W17_Group20_Assign_1.pdf, this README.txt, and randArr.cpp.
3. From the command line type "make".
4. maxSub usage is as follows:

	maxSub {0 or 1} [inputFile.txt]

	0 will omit timing data for all 4 algorithms.
	1 will print to stdout timing data for all 4 algorithms for each line
	  seperated by a newline character contained within the inputFile.txt

	[inputFile.txt] is optional and can be named anything as long as it
			is a text file containing integers separated by spaces.
			Multiple lines of input are accepted and each is processed.
			Omitting the inputFile.txt argument will cause maxSum to
			use the default file MSS_Problems.txt as input.  All output
			of maxSum is written to MSS_Results.txt by default.

			Grader: type "./maxSub 0" and then "cat MSS_Results.txt".
				You will need to provide an input text file otherise
				MSS_Results.txt is written empty.
				Be sure to look at MSS_Results.txt before you
				overwrite it, but if the input file is MSS_Problems.txt
				then MSS_Results.txt will be overwritten with identical
				data as we submitted in the zip file.

5. randArr.cpp is not compiled with the provided makefile.  randArr.cpp is provided
   for Grader inspection only, but can be compiled with "gcc randArr.cpp -o ranGen"

* The zip file was created using WinRar.