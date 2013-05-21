#include <stdio.h>

typedef struct enc_params {
	char TestCaseId[6];
	char DumpORCompareflag1[10];
    char reference[200];
	char input[200];
	char output[200];
	int  maxWidth;
	int  maxHeight;
	int  inputWidth;
	int  inputHeight;
	int  maxScans;
	int  dataEndianness;
	int  forceChromaFormat;
    int  inputChromaFormat;
	int  captureWidth;
	int  numAU;
	int  generateHeader;
	int  qValue;
	int  rstInterval;
	int  roatation;
	int  disableEOI;
}jpgenc_params;

typedef struct decprofiledata {
    char TestCaseId[6];
	int  avg_activatetime;
	int  avg_processtime;
	int  avg_time_IMCOP;
	int  avg_deactivatetime;
}profiledata;