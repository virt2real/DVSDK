/*
 * dvtbTime.c
 *
 * GetTime Interface implementation
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

#include "dvtbTime.h"
#include "dvtbMemory.h"
#include "dvtbGlobal.h"


typedef struct Time_Object 
{
    LARGE_INTEGER original;
    LARGE_INTEGER previous;
} Time_Object;

LARGE_INTEGER PerformanceFrequency;

Time_Handle 
dvtb_timeCreate()
{
    Time_Handle hTime;

    /* Store the PerformanceFrequency to be used for 
     * subsequent calculation based on PerformanceCounter.
     */
    if (!(QueryPerformanceFrequency(&PerformanceFrequency))) 
	{
		SYS_ERROR("Unable to query Performance Frequency \n");
        hTime = NULL;
    }
	else
	{
		if(DVEVM_ST_FAIL == dvtb_allocSingleBufCmem((char **)&hTime,sizeof (Time_Object)))
		{
			hTime = NULL;
			SYS_ERROR("Unable to allocate memory for handle \n");
		}
	}

    return hTime;
}

DvevmStRetCode 
dvtb_timeDelete(Time_Handle hTime)
{
    if (hTime)
	{
        dvtb_freeSingleBufCmem((char *)hTime, sizeof (Time_Object));
    }

    return DVEVM_ST_SUCCESS;
}

DvevmStRetCode 
dvtb_timeReset(Time_Handle hTime)
{
    DVTBASSERT(hTime);

    if (!(QueryPerformanceCounter(&hTime->original))) 
	{
        SYS_ERROR("Unable to query Performance Counter \n");
        return DVEVM_ST_FAIL;
    }
	hTime->previous = hTime->original;

	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_timeDelta(Time_Handle hTime, int *delta)
{
    LARGE_INTEGER curCounter;
    LARGE_INTEGER deltaCounter;

    DVTBASSERT(hTime);
    DVTBASSERT(delta);

    if (!(QueryPerformanceCounter(&curCounter))) 
	{
        SYS_ERROR("Unable to query Performance Counter \n");
        *delta = 0;
        return DVEVM_ST_FAIL;
    }
    /* Calculate the delta in uS. */
    deltaCounter.QuadPart = curCounter.QuadPart - hTime->previous.QuadPart;
    deltaCounter.QuadPart = (deltaCounter.QuadPart * 1000000) / PerformanceFrequency.QuadPart;
    *delta = (int)(deltaCounter.LowPart);

    hTime->previous = curCounter;
    return DVEVM_ST_SUCCESS;
}
