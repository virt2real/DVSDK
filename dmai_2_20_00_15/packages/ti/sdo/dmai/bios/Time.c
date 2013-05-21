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

#include <xdc/std.h>

#include <std.h>
#include <clk.h>
#include <mem.h>
#include <hwi.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Time.h>

#define MODULE_NAME     "Time"

typedef struct Time_Object {
    UInt32 origHTime;
    UInt32 prevHTime;
    UInt32 origLTime;
    UInt32 prevLTime;
} Time_Object;

const Time_Attrs Time_Attrs_DEFAULT = {
    0
};

/******************************************************************************
 * getLHTimes
 ******************************************************************************/
static Void getLHTimes(UInt32 * tvLTime, UInt32 * tvHTime) 
{
    UInt32 newLTime;
        
    /* 
     * Ensure no timer interrupt is taken between getting CLK_getltime and
     * CLK_gethtime. Otherwise re-read the timer. 
     */
    do {
        *tvLTime = CLK_getltime();  
        *tvHTime = CLK_gethtime();
        newLTime = CLK_getltime();  
    } while (*tvLTime != newLTime);
}

/******************************************************************************
 * computeTimeDiff
 ******************************************************************************/
static ULLong computeTimeDiff(UInt32 oldLTime, UInt32 oldHTime, UInt32 newLTime,
    UInt32 newHTime)
{
    ULLong deltaTime;
    ULLong oldTime;
    ULLong newTime;
    
    /* 
     * Compute the number of high resolution ticks corresponding to the low
     * resolution times.
     */  
    oldTime = oldLTime * (ULLong)CLK_getprd();
    newTime = newLTime * (ULLong)CLK_getprd();
        
    /* 
     * Keep only high resolution ticks in excess of what's been counted by 
     * low resolution ticks 
     */
    oldHTime = oldHTime - (UInt32)(oldTime & 0xFFFFFFFF);
    newHTime = newHTime - (UInt32)(newTime & 0xFFFFFFFF);
    
    /* 
     * Add the remainder to the times
     */  
    oldTime += oldHTime; 
    newTime += newHTime;
    
    deltaTime = newTime - oldTime;
    
    return deltaTime;
}

/******************************************************************************
 * Time_create
 ******************************************************************************/
Time_Handle Time_create(Time_Attrs *attrs)
{
    Time_Handle hTime;

    if (attrs == NULL) {
        Dmai_err0("NULL attrs not valid\n");
    }

    hTime = (Time_Handle)MEM_calloc(Dmai_Bios_segid, sizeof(Time_Object), 0);

    if (hTime == NULL) {
        Dmai_err0("Failed to allocate space for Time Object\n");
        return NULL;
    }

    Dmai_dbg0("Note: Time module requires CPU frequency to be correctly set " \
        "in BIOS GBL module. Otherwise numbers returned may be inaccurate.\n");
    
    return hTime;
}

/******************************************************************************
 * Time_delete
 ******************************************************************************/
Int Time_delete(Time_Handle hTime)
{
    if (hTime) {
        if (MEM_free(Dmai_Bios_segid, hTime, sizeof(Time_Object)) == FALSE) {
            return Dmai_EFAIL;  
        }
    }

    return Dmai_EOK;
}

/******************************************************************************
 * Time_reset
 ******************************************************************************/
Int Time_reset(Time_Handle hTime)
{
    UInt32 tvHTime;
    UInt32 tvLTime;
    
    assert(hTime);

    getLHTimes(&tvLTime, &tvHTime);
    
    hTime->origHTime = tvHTime;
    hTime->prevHTime = tvHTime;
    hTime->origLTime = tvLTime;
    hTime->prevLTime = tvLTime;
    
    return Dmai_EOK;
}

/******************************************************************************
 * Time_delta
 ******************************************************************************/
Int Time_delta(Time_Handle hTime, UInt32 *deltaPtr)
{
    UInt32 tvHTime, tvLTime;
    ULLong deltaHTime;
    ULLong deltaTime;

    assert(hTime);
    assert(deltaPtr);

    getLHTimes(&tvLTime, &tvHTime);

    deltaHTime = computeTimeDiff(hTime->prevLTime, hTime->prevHTime, tvLTime,
        tvHTime);
         
    deltaTime = 125 * deltaHTime / (ULLong)(CLK_countspms() >> 3);
        
    *deltaPtr = deltaTime;

    /* Record new time */
    hTime->prevHTime = tvHTime;
    hTime->prevLTime = tvLTime;
    
    return Dmai_EOK;
}

/******************************************************************************
 * Time_total
 ******************************************************************************/
Int Time_total(Time_Handle hTime, UInt32 *totalPtr)
{
    UInt32 tvLTime, tvHTime;
    ULLong deltaHTime;
    ULLong deltaTime;
    
    assert(hTime);
    assert(totalPtr);

    getLHTimes(&tvLTime, &tvHTime);

    deltaHTime = computeTimeDiff(hTime->origLTime, hTime->origHTime, tvLTime,
        tvHTime);
         
    deltaTime = 125 * deltaHTime / (ULLong)(CLK_countspms() >> 3);

    *totalPtr = deltaTime;
 
    return Dmai_EOK;
}

