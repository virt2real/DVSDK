#include <stdio.h>

typedef struct dec_params {
	char TestCaseId[6];
	char DumpORCompareflag1[10];
    char reference[100];
	char input[100];
	char output[100];
	int  maxWidth;
	int  maxHeight;
	int  dataEndianness;
	int  forceChromaFormat;
	int  rotation;
	int  displayWidth;
    int  meRange;
	int  unrestrictedMV;
}decoder_params;

typedef struct decprofiledata {
    char TestCaseId[6];
	int  avg_activatetime;
	int  avg_processtime;
	int  avg_time_IMCOP;
	int  avg_deactivatetime;
}profiledata;
