#include <stdio.h>

typedef struct dec_params {
    char TestCaseId[6];
    char DumpORCompareflag1[10];
    char reference[200];
    char input[200];
    char output[200];
    int  imgWidth;
    int  imgHeight;
    int  framerate;
    int  bitrate;
    int  chromaformat;
    int  subWindowWidth;
    int  subWindowHeight;
    int  intraPeriod;
    int  intraDcVlcThr;
    int  meRange;
    int  intraThres;
    int  intraAlgo;
    int  numMBRows;
    int  initQ;
    int  rcQ_MAX;
    int  rcQ_MIN;
    int  rateFix;
    int  rateFixRange;
    int  rotation;
    int  meAlgo;
    int  SkipMBAlgo;
    int  UMV;
    int  RCAlgo;
    int  IIDC;
    int  initQ_P;
    int  VBV_size;
}encoder_params;

typedef struct decprofiledata {
    char TestCaseId[6];
    int  avg_activatetime;
    int  avg_processtime;
    int  avg_time_IMCOP;
    int  avg_deactivatetime;
}profiledata;