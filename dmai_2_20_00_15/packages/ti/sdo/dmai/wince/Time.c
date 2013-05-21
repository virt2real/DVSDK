/* --COPYRIGHT--,BSD
 * Copyright (c) 2010, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/

#include <stdlib.h>
#include <windows.h>

#include <xdc/std.h>
#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Time.h>

#define MODULE_NAME     "Time"

typedef struct Time_Object {
    LARGE_INTEGER original;
    LARGE_INTEGER previous;
} Time_Object;

const Time_Attrs Time_Attrs_DEFAULT = {
    0
};

/* QueryPerformanceCounter is used for timing since it gives a far more
 * accurate timer resolution than getTickCount() if the platform
 * supports a high resolution timer. If not it is supposed to default
 * to 1ms resolution.
 */

/* To store Performance Frequency used in time calculations */
LARGE_INTEGER PerformanceFrequency;

/******************************************************************************
 * Time_create
 ******************************************************************************/
Time_Handle Time_create(Time_Attrs *attrs)
{
    Time_Handle hTime;

    if (attrs == NULL) {
        Dmai_err0("NULL attrs not supported\n");
        return NULL;
    }

    /* Store the PerformanceFrequency to be used for 
     * subsequent calculation based on PerformanceCounter.
     */
    if (!(QueryPerformanceFrequency(&PerformanceFrequency))) {
        Dmai_err0("Performance Frequency not supported\n");
        return NULL;
    }

    hTime = calloc(1, sizeof(Time_Object));

    if (hTime == NULL) {
        Dmai_err0("Failed to allocate space for Time Object\n");
        return NULL;
    }

    return hTime;
}

/******************************************************************************
 * Time_delete
 ******************************************************************************/
Int Time_delete(Time_Handle hTime)
{
    if (hTime) {
        free(hTime);
    }

    return Dmai_EOK;
}

/******************************************************************************
 * Time_reset
 ******************************************************************************/
Int Time_reset(Time_Handle hTime)
{
    LARGE_INTEGER curCounter;

    assert(hTime);

    if (!(QueryPerformanceCounter(&curCounter))) {
        Dmai_err0("Performance Counter not supported\n");
        return Dmai_EFAIL;
    }

    hTime->original = curCounter;
    hTime->previous = curCounter;

    return Dmai_EOK;
}

/******************************************************************************
 * Time_delta
 ******************************************************************************/
Int Time_delta(Time_Handle hTime, UInt32 *deltaPtr)
{
    LARGE_INTEGER curCounter;
    LARGE_INTEGER deltaCounter;

    assert(hTime);
    assert(deltaPtr);

    if (!(QueryPerformanceCounter(&curCounter))) {
        Dmai_err0("Performance Counter not supported\n");
        *deltaPtr = 0;
        return Dmai_EFAIL;
    }
    /* Calculate the delta in uS. */
    deltaCounter.QuadPart = curCounter.QuadPart - hTime->previous.QuadPart;
    deltaCounter.QuadPart = (deltaCounter.QuadPart * 1000000) / PerformanceFrequency.QuadPart;
    *deltaPtr = (UInt32)(deltaCounter.LowPart);

    hTime->previous = curCounter;
    return Dmai_EOK;
}

/******************************************************************************
 * Time_total
 ******************************************************************************/
Int Time_total(Time_Handle hTime, UInt32 *totalPtr)
{
    LARGE_INTEGER curCounter;
    LARGE_INTEGER deltaCounter;

    assert(hTime);
    assert(totalPtr);

    if (!(QueryPerformanceCounter(&curCounter))) {
        Dmai_err0("Performance Counter not supported\n");
        *totalPtr = 0;
        return Dmai_EFAIL;
    }
    /* Calculate the total delta in uS. */
    deltaCounter.QuadPart = curCounter.QuadPart - hTime->original.QuadPart;
    deltaCounter.QuadPart = (deltaCounter.QuadPart * 1000000) / PerformanceFrequency.QuadPart;

    *totalPtr = (UInt32)(deltaCounter.LowPart);
    return Dmai_EOK;
}
