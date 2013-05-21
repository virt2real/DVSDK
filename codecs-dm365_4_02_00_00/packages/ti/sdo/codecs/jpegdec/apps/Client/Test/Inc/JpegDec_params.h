#include <stdio.h>

typedef struct jpegdec_params {
	char TestCaseId[6];
	char DumpORCompareflag1[10];
    char reference[200];
	char input[200];
	char output[200];
	int  Resize;
	int  DisplayWidth;
	int  rotation;
	int  areaDecode;
	int  maxWidth;
	int  maxHeight;
    int  forceChromaFormat;
	int  dataEndianness;
	int  subRegionUpLeftY;
	int  subRegionUpLeftX;
	int  subRegionDownRightX;
	int  subRegionDownRightY;	
}jpegdec_params;

typedef struct decprofiledata {
    char TestCaseId[6];
	int  avg_activatetime;
	int  avg_processtime;
	int  avg_time_IMCOP;
	int  avg_deactivatetime;
}profiledata;