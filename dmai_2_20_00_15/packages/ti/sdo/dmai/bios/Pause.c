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

#include <xdc/std.h>

#include <std.h>
#include <sem.h>
#include <mem.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Pause.h>

#define MODULE_NAME     "Pause"

typedef struct Pause_Object {
    Int     pause;
    SEM_Obj mutex;
    SEM_Obj sem;
    Int     numTasks;
} Pause_Object;

const Pause_Attrs Pause_Attrs_DEFAULT = {
    0
};

/******************************************************************************
 * Pause_create
 ******************************************************************************/
Pause_Handle Pause_create(Pause_Attrs *attrs)
{
    Pause_Handle hPause;

    hPause = MEM_calloc(Dmai_Bios_segid, sizeof(Pause_Object), 0);

    if (hPause == NULL) {
        Dmai_err0("Failed to allocate space for Pause Object\n");
        return NULL;
    }

    /* initialize the object */
    SEM_new(&hPause->sem, 0);
    SEM_new(&hPause->mutex, 1);    
    hPause->numTasks = 0;
    hPause->pause = 0;

    return hPause;
}

/******************************************************************************
 * Pause_delete
 ******************************************************************************/
Int Pause_delete(Pause_Handle hPause)
{
    int ret = Dmai_EOK;
    
    if (hPause) {
        if (MEM_free(Dmai_Bios_segid, hPause, sizeof(Pause_Object)) != TRUE) {
            ret = Dmai_EFAIL;
        }
    }
    
    return ret;
}

/******************************************************************************
 * Pause_test
 ******************************************************************************/
Void Pause_test(Pause_Handle hPause)
{
    assert(hPause);

    /* 
     * We need to ensure that if we get preempted just before pending on 
     * hPause->sem that the correct number of SEM_post calls would still be 
     * performed to unblock this task if Pause_off is called. This is why we
     * need to use numTasks to keep track of the number of tasks pending or
     * about to pend.    
     */      
    SEM_pend(&hPause->mutex, SYS_FOREVER);
    if (hPause->pause == 1) {
        hPause->numTasks++;
        SEM_post(&hPause->mutex);
        SEM_pend(&hPause->sem, SYS_FOREVER);
    }
    else {
        SEM_post(&hPause->mutex);   
    }
}

/******************************************************************************
 * Pause_on
 ******************************************************************************/
Void Pause_on(Pause_Handle hPause)
{
    assert(hPause);

    SEM_pend(&hPause->mutex, SYS_FOREVER);
    hPause->pause = 1;
    SEM_post(&hPause->mutex);
}

/******************************************************************************
 * Pause_off
 ******************************************************************************/
Void Pause_off(Pause_Handle hPause)
{
    UInt i;
    
    assert(hPause);

    SEM_pend(&hPause->mutex, SYS_FOREVER);
    
    if (hPause->pause == 1) {
        hPause->pause = 0;
        /* Unblock all waiting tasks */
        for (i = hPause->numTasks; i > 0; i--) {
            SEM_post(&hPause->sem);
        }
        hPause->numTasks = 0;
    }

    SEM_post(&hPause->mutex);
}
