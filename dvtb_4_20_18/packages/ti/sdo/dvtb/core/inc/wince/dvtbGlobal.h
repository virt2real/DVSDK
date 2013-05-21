/*
 * dvtbGlobal.h
 *
 * Global header file for DVTB(wince)
 *
 * Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
 * 
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/

#ifndef _DVEVM_ST_GLOBAL_H
#define _DVEVM_ST_GLOBAL_H


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <Winsock2.h>

#include "xdc/std.h"


#define MAX_KEY_SIZE            (16)
#define MAX_NAME_LEN            (64)
#define MAX_LINE_SIZE           (512)
#define MAX_XDM_BUFS            (3)

#define MIN_USER_BUFFER_DISPLAY_BUFFERS  (3)
#define VIDDEC2_PLAY_MAX_BUFFERS (XDM_MAX_BUFFERS+MIN_USER_BUFFER_DISPLAY_BUFFERS+1)

#define DVTB_PROMPT            "<DVTB> $ "
#define NODSP_OPTION            "--nodsp"
#define SOURCE_FILE_OPTION      "-s"
#define TARGET_FILE_OPTION      "-t"

#define SOURCE_FILE1_OPTION     "-s1"
#define SOURCE_FILE2_OPTION     "-s2"
#define SOURCE_FILE3_OPTION     "-s3"
#define SOURCE_FILE4_OPTION     "-s4"
#define SOURCE_FILE5_OPTION     "-s5"
#define SOURCE_FILE6_OPTION     "-s6"
#define SOURCE_FILE7_OPTION     "-s7"
#define SOURCE_FILE8_OPTION     "-s8"

#define ZERO(_x)                memset(&(_x), 0, sizeof(_x))

#define DIM(_x)                 (sizeof(_x)/sizeof(_x[0]))

/* Macro definitions for default decoder/encoder names */

#define MAX_PITCH               (1920)
#define MAX_HEIGHT              (1080)
#define HD720_YRES              (720)
#define HD720_XRES              (1280)
#define NTSC_YRES               (480)
#define NTSC_XRES               (720)
#define PAL_YRES                (576)
#define PAL_XRES                (720)

#define XDM_MAX_BUFFERS          17

#define VID_FRAME_SIZE(_x, _y, _bpp)        ((_x) * (_y) * (_bpp) / 8)

/* Macro Definitions for logging */

#ifdef _DVEVM_ST_DEBUG_
#define SYS_DEBUG(STR, ...)       printf("[DVTB-DEBUG]: "__FILE__": " STR,__VA_ARGS__)
#else
#define SYS_DEBUG(STR, ...)
#endif
#define SYS_PRINTF(STR, ...)      printf(STR,__VA_ARGS__)
#define SYS_OUT(STR, ...)         printf("[DVTB-LOG]: "__FILE__": " STR, __VA_ARGS__)
#define SYS_ERROR(STR, ...)       fprintf(stderr, "[DVTB-ERROR]: "__FILE__": " STR, __VA_ARGS__)
#define SYS_PERROR(STR, ...)      fprintf(stderr, "[DVTB-ERROR]: " STR, __VA_ARGS__);


#define SYS_PERF(STR, ...)        fprintf(perfFp, STR, __VA_ARGS__)


#ifndef PERF_LOGFILE
#define PERF_LOGFILE            "perf-data.csv"
#endif
#define DVTB_ST_PROMPT()        printf("\n"DVTB_PROMPT)
#define DVEVM_ST_FLUSH()        fflush(stdout)

#define DVTBASSERT(_x)              { if (!(_x)) { SYS_ERROR("Assertion Failed :"); SYS_PRINTF(#_x); SYS_PRINTF("\n"); return DVEVM_ST_FAIL; } }


#define DELTA(t1, t2) (((t2.tv_sec*NUM_MICROSECS_IN_SEC)+t2.tv_usec)-((t1.tv_sec*NUM_MICROSECS_IN_SEC)+t1.tv_usec))

#define NUM_MICROSECS_IN_SEC     (1000000)
#define CHAR_ZERO       '\0'

typedef enum
{
	DVEVM_ST_STATUS_AVAILABLE = 0,
	DVEVM_ST_STATUS_BLOCKED = 1,
	DVEVM_ST_STATUS_RUNNING = 2,
	DVEVM_ST_STATUS_COMPLETED = 3,
} DvevmStStatus;

typedef enum
{
	DVEVM_ST_FAIL = -1,
	DVEVM_ST_SUCCESS = 0,
	DVEVM_ST_PNDG = 2,
	DVEVM_ST_NOTSUPPORTED
} DvevmStRetCode;

typedef enum
{
	DVEVM_ST_FALSE = 0,
	DVEVM_ST_TRUE = 1
} DvevmStBool;

typedef enum
{
	DVEVM_ST_ENCODE = 0,
	DVEVM_ST_DECODE = 1,
	DVEVM_ST_ENCDEC = 2,
	DVEVM_ST_APPSPECIFIC = 3
} DvevmStClassType;


typedef enum
{
	DVEVM_ST_PLAY = 0,
	DVEVM_ST_CAPTURE = 1
} DvevmStMode;

typedef struct
{
	unsigned int size;
	char *start;
} DvevmStBuffer;

typedef struct
{
	unsigned int numBufs;
	char *bufs[MAX_XDM_BUFS];
	int bufSizes[MAX_XDM_BUFS];
} DvevmStXdmBuffer;

typedef enum
{
	DVEVM_ST_STANDARD_NA = 0,
	DVEVM_ST_NTSC = 1,
	DVEVM_ST_1080I_30 = 2,
	DVEVM_ST_720P_60 = 3,
	DVEVM_ST_PAL = 4,
	DVEVM_ST_720P_50 = 5,
	DVEVM_ST_1080I_25 = 6,
	DVEVM_ST_480P_60 = 7,
	DVEVM_ST_576P_50 = 8
} DvevmStDisplayStd;

typedef enum
{
	DVEVM_ST_OUTPUT_NA = 0,
	DVEVM_ST_COMPOSITE = 1,
	DVEVM_ST_SVIDEO = 2,
	DVEVM_ST_COMPONENT = 3
} DvevmStDisplayOutput;

typedef enum
{
	VID_FMT_YUYV,
	VID_FMT_UYVY,
	VID_FMT_YUV420,
	VID_FMT_YUV422P,
	VID_FMT_YUV410,
	VID_FMT_YVU420,
	VID_FMT_RGB565,
	VID_FMT_YUV422UVP,
	VID_FMT_YUV420SP,
	VID_STD_1080I_60
} DvevmStVidFmt;

typedef DvevmStRetCode (* DvevmStDispatcher)(int numTokens, char **tokens);

typedef struct
{
	char key[MAX_KEY_SIZE];
	DvevmStDispatcher dptr;
} DvevmStExecInfo;

typedef struct
{
	int id;
	DvevmStXdmBuffer buffer;
	DvevmStBool isFree;
} DvevmStBufElement;

typedef struct outBuffsInUse
{
	unsigned int bufID;
	unsigned char * displayBufs;
	DvevmStBool outBufInUseFlag;
	DvevmStBool freeIt;
}DvevmStOutBuffsInUse;

typedef struct timeval DvevmStTime;

typedef struct
{
	char statName[MAX_NAME_LEN]; // Name of the stat being profiled

	int statVal; // Value of stat being profiled
	int cpuLoad; // Average CPU load for this stat val
	int latency; // Average latency caused by CE
	int maxCpuLoad; // Maximum CPU load for this stat val
	int maxLatency; // Maximum latency caused by CE
	int minCpuLoad; // Minimum CPU load for this stat val
	int minLatency; // Minimum latency caused by CE
	int numIterations; // Number of iterations profiled
	DvevmStTime lastProfileTime; // Timestamp of last profile
} DvevmStPerfStat;

extern int errno;
extern char PRINT_BUFF[MAX_LINE_SIZE];
extern FILE *perfFp;

DvevmStTime lastprofileTime;
void
dvtb_reportStatus(DvevmStRetCode rc, char *str);

#endif
