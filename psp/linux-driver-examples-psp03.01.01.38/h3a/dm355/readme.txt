NAME:
	aew_example : Functionality of Auto Exposure and White balance (AEW)
	af_example  : Functionality of Auto Focus (AF)  

SYNOPSIS
	aew_example
	af_example 

DESCRIPTION
aew_example
	This executable is used to verify the functionalities of the AEW.
af_example
        This executable is used to verify the functionalities of the AF.

OPTIONS
	Both the executables have three options.

	t : To choose the type of the test. It has three possibilities
		f or F - For Functionality tests.
		s or S - For Stress tests.
		p or P - For performance tests.
	c : To choose different test cases. Valid options are from 2 to 7.
	n : To choose a test in the particular test case. Valid options depend
	    on the test case choosen.
		For test case 2 : options are from 1 to 8 (AEW) and 1 to 7 (AF).
		For test case 3 : option is 1.
		For test case 4 : option is 1.
		For test case 5 : options are from 1 to 3.
		For test case 6 : options are 1 to 3 (AEW) and 1 to 4 (AF).
		For test case 7 : option is 1.

EXAMPLE USAGE
To get the configured AEW paramwters:
./aew_example -t f -c 4 -n 1

The output will be a text file aew_samp.txt which will have the configured
values for the AEW parameters.

To get the configured AF paramwters:
./af_example -t f -c 4 -n 1

The output will be a text file af_samp.txt which will have the configured
values for the AF parameters.

COPYRIGHT
	Refer to the source headers

KNOWN ISSUES

VERSION
	PSP 3.0

CHANGELOG
	1.0

