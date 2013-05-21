/* 
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
 * 
 */
/*
 *  ======== Global_BIOS_load_PWRM.c ========
 */
#include <xdc/std.h>

#include <ti/bios/include/std.h>

#include <ti/bios/include/pwrm.h>

#include <ti/sdo/ce/osal/Memory.h>

Int Global_getLoad(Int * window);

/*
 *  ======== Global_getLoad ========
 */
Int Global_getLoad(Int * window)
{
    static PWRM_CPULoadInfo * loadHistory;
    static Bool curInit = FALSE;
    static Bool monitorOK = FALSE;
    static Uns numSlots = 0;
    PWRM_LoadMonitorInfo monitorInfo;
    Uns numSlotsAveraged = 0;
    Uns slotAverage = 0;
    Uns sumAverages = 0;
    Int load = 0;               /* default load is 0% */
    PWRM_Status status;
    Int i;

    /* on first execution setup load history buffer based upon monitor config */
    if (curInit != TRUE) {
        curInit = TRUE;
        status = PWRM_getLoadMonitorInfo(&monitorInfo);
        if (status == PWRM_SOK) {
            numSlots = monitorInfo.numSlots;

            if (numSlots > 0) {  /* make sure user configured some slots */
                                    
                /* alloc array for holding slot info */
                loadHistory = (PWRM_CPULoadInfo *)Memory_alloc(numSlots * 
                    sizeof(PWRM_CPULoadInfo), NULL);

                /* if all is good, declare monitoring OK */
                if (loadHistory != NULL) {
                    monitorOK = TRUE;
                }
            }
        }
    }

    /* calculate load only if monitor was initialized OK */
    if (monitorOK == TRUE) {

        /* call PWRM to fill history buffer */
        status = PWRM_getCPULoad(numSlots, loadHistory);

        if (status == PWRM_SOK) {

            /* compute average for each history slot */
            for (i = 0; i < numSlots; i++) {  
                
                 /* average only if slot has valid data */
                 if (loadHistory[i].totalCycles != 0) {

                     slotAverage = (loadHistory[i].busyCycles * 100) / 
                         loadHistory[i].totalCycles;
                     sumAverages += slotAverage;
                     numSlotsAveraged++;
                 }
            }

            /* now, combine slot averages to determine overall average load */
            if (numSlotsAveraged != 0) {
                load = sumAverages / numSlotsAveraged;
            }
        }
    }

    return(load);

}
/*
 *  @(#) ti.sdo.ce.osal.bios; 2, 0, 1,182; 12-2-2010 21:24:42; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

