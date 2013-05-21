/*
 * dvtbThreadManager.h
 *
 * DVTB(wince) Thread Interfaces
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

#ifndef _DVEVM_ST_THREAD_H
#define _DVEVM_ST_THREAD_H

#include "dvtbGlobal.h"
#include "dvtbParam.h"
#include "Thread.h"

#define MAX_THREADS             (8)

typedef struct
{
	DvevmStStatus inUse;
	DvevmStBool traceOn;

	Thread_Params thrParams;
	Thread_Handle thrHandle;

	DvevmStGlobalParams g;

	FILE *sourceFp;
	FILE *targetFp;

	FILE *sourceFp1;
	FILE *sourceFp2;
	FILE *sourceFp3;
	FILE *sourceFp4;
	FILE *sourceFp5;
	FILE *sourceFp6;
	FILE *sourceFp7;
	FILE *sourceFp8;

	DvevmStBool capture;

	DvevmStBool useAlgorithm;
} DvevmStThreadInfo;

extern DvevmStThreadInfo TH[MAX_THREADS];

void
dvtb_initThread();

void
dvtb_deleteThread(Thread_Handle *thrHandle);

DvevmStRetCode
dvtb_getFreeThread(unsigned int *index);

DvevmStRetCode
dvtb_createThread(Thread_RunFxn fxn, Thread_Params* params, Thread_Handle *thrHandle);

void
dvtb_sleepThread(int seconds);

void
dvtb_freeThread(DvevmStThreadInfo *T);

void
dvtb_waitThread();

#endif

