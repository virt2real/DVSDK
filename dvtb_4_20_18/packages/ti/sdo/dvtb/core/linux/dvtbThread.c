/*
 * dvtbThread.c
 *
 * DVTB(linux) Thread Interface implementation
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

#include "dvtbThread.h"
#include <ti/sdo/ce/utils/trace/TraceUtil.h>

DvevmStThreadInfo TH[MAX_THREADS];

void
dvtb_initThr()
{
	int i = 0;
	for (i = 0; i < MAX_THREADS; i++)
	{
		ZERO(TH[i]);
		TH[i].inUse = DVEVM_ST_FALSE;

		/* Initialize the thread attributes */
		pthread_attr_init(&TH[i].attr);

		/* Force the thread to use custom scheduling attributes */
		pthread_attr_setinheritsched(&TH[i].attr, PTHREAD_EXPLICIT_SCHED);

		/* Set the thread to be fifo real time scheduled */
		pthread_attr_setschedpolicy(&TH[i].attr, SCHED_FIFO);

		/* Set the thread priority */
		TH[i].schedParam.sched_priority = sched_get_priority_max(SCHED_FIFO) - i;
		pthread_attr_setschedparam(&TH[i].attr, &TH[i].schedParam);

	}
}

DvevmStRetCode
dvtb_getFreeThr(unsigned int *index)
{
	int i = 0;

	for (i = 0; i < MAX_THREADS; i++)
	{
		if (!TH[i].inUse)
		{
			*index = i;
			TH[i].inUse = DVEVM_ST_TRUE;
			memcpy(&(TH[i].g), G, sizeof(DvevmStGlobalParams));
			return DVEVM_ST_SUCCESS;
		}
	}

	return DVEVM_ST_FAIL;
}

void
dvtb_freeThr(DvevmStThreadInfo *T)
{
	T->inUse = DVEVM_ST_FALSE;
}

int
dvtb_threadCreate(pthread_t *thrId, pthread_attr_t *attr, void *routine, void *arg)
{
	int status;

	status = pthread_create(thrId, attr, routine, arg);

	return status;
}

void
dvtb_threadExit()
{
	pthread_exit(NULL);
}
