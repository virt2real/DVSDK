/*
 * dvtbThreadManager.c
 *
 * DVTB(wince) Thread Interface implementation
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

#include "dvtbThreadManager.h"

DvevmStThreadInfo TH[MAX_THREADS];

void
dvtb_initThread()
{
	int i = 0;
	for (i = 0; i < MAX_THREADS; i++)
	{
		ZERO(TH[i]);
		TH[i].inUse = DVEVM_ST_STATUS_AVAILABLE;

		Thread1_Params_init(&TH[i].thrParams);
	}
}

void
dvtb_deleteThread(Thread_Handle *thrHandle)
{
	Thread1_delete(thrHandle);
}

DvevmStRetCode
dvtb_getFreeThread(unsigned int *index)
{
	int i = 0;

	for (i = 0; i < MAX_THREADS; i++)
	{
		if(DVEVM_ST_STATUS_COMPLETED == TH[i].inUse)
		{
			dvtb_deleteThread(&TH[i].thrHandle);
			TH[i].inUse = DVEVM_ST_STATUS_AVAILABLE;
		}
	}

	for (i = 0; i < MAX_THREADS; i++)
	{
		if (DVEVM_ST_STATUS_AVAILABLE == TH[i].inUse)
		{
			*index = i;
			TH[i].inUse = DVEVM_ST_STATUS_BLOCKED;
			memcpy(&(TH[i].g), G, sizeof(DvevmStGlobalParams));
			return DVEVM_ST_SUCCESS;
		}
	}

	return DVEVM_ST_FAIL;
}

DvevmStRetCode
dvtb_createThread(Thread_RunFxn fxn, Thread_Params* params, Thread_Handle *thrHandle)
{
	DvevmStRetCode retVal = DVEVM_ST_SUCCESS;
	*thrHandle = Thread1_create(fxn, params);

	if(NULL == *thrHandle)
	{
		SYS_ERROR("Thread_create fails. \n");
		retVal = DVEVM_ST_FAIL;
	}

	return retVal;
}

//Sleep for certain number of seconds
void
dvtb_sleepThread(int seconds)
{
	unsigned int microSeconds = seconds * 1000000;

	//timeout should be in microseconds
	Thread1_sleep(microSeconds);
}

void
dvtb_freeThread(DvevmStThreadInfo *T)
{
	while(DVEVM_ST_STATUS_RUNNING != T->inUse)
		dvtb_sleepThread(1);

	T->inUse = DVEVM_ST_STATUS_COMPLETED;
}

void
dvtb_waitThread()
{
	while(1)
	{
        	//Wait for main thread to terminate
                dvtb_sleepThread(1);
	}
}
