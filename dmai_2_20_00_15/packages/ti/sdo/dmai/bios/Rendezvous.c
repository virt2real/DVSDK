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
#include <tsk.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Rendezvous.h>

#define MODULE_NAME     "Rendezvous"

typedef struct Rendezvous_Object {
    Int             count;
    Int             numWaiting;    
    Bool            force;
    SEM_Obj         sem;
} Rendezvous_Object;

const Rendezvous_Attrs Rendezvous_Attrs_DEFAULT = {
    0
};

/******************************************************************************
 * Rendezvous_create
 ******************************************************************************/
Rendezvous_Handle Rendezvous_create(Int count, Rendezvous_Attrs *attrs)
{
    Rendezvous_Handle hRv;

    if (attrs == NULL) {
        Dmai_err0("NULL attrs not supported\n");
        return NULL;
    }

    if ((count < 0) && (count != Rendezvous_INFINITE)) {
        Dmai_err1("Count (%d) must be > 0\n", count);
        return NULL;
    }

    hRv = MEM_calloc(Dmai_Bios_segid, sizeof(Rendezvous_Object), 0);
    
    if (hRv == NULL) {
        Dmai_err0("Failed to allocate space for Rendezvous Object\n");
        return NULL;
    }

    /* initialize the object */
    SEM_new(&hRv->sem, 0);
    hRv->numWaiting = 0;
    hRv->count = count;

    return hRv;
}

/******************************************************************************
 * Rendezvous_delete
 ******************************************************************************/
Int Rendezvous_delete(Rendezvous_Handle hRv)
{
    int ret = Dmai_EOK;
    
    if (hRv) {
        if (MEM_free(Dmai_Bios_segid, hRv, sizeof(Rendezvous_Object)) != TRUE) {
            ret = Dmai_EFAIL;
        };
    }
    
    return ret;
}

/******************************************************************************
 * Rendezvous_meet
 ******************************************************************************/
Void Rendezvous_meet(Rendezvous_Handle hRv)
{
    Int i;
    
    assert(hRv);
    TSK_disable();
    if (!hRv->force) {
        if ((hRv->numWaiting < hRv->count) || 
            (hRv->count == Rendezvous_INFINITE)) {
            hRv->numWaiting++;
        }
                
        /* If count is not reached, need to wait for others to arrive */
        if ((hRv->numWaiting < hRv->count) || 
            (hRv->count == Rendezvous_INFINITE)) {
            TSK_enable();
            SEM_pend(&hRv->sem, SYS_FOREVER);
        }
        else {
            /* all threads expected at rendezvous have arrived. Unblock all! */
            for (i = 0; i < hRv->count; i++) {
                SEM_post(&hRv->sem);
            }   
            hRv->numWaiting = 0;
            TSK_enable();
        }
    }
    else {
        TSK_enable();
    }
}

/******************************************************************************
 * Rendezvous_force
 ******************************************************************************/
Void Rendezvous_force(Rendezvous_Handle hRv)
{
    Int i;
    
    assert(hRv);

    TSK_disable();
    /* post the semaphore for all blocked tasks */
    for (i = 0; i < hRv->numWaiting; i++) {
        SEM_post(&hRv->sem);
    } 
    hRv->force = TRUE;
    TSK_enable();
}

/******************************************************************************
 * Rendezvous_reset
 ******************************************************************************/
Void Rendezvous_reset(Rendezvous_Handle hRv)
{
    assert(hRv);

    TSK_disable();
    hRv->numWaiting = 0;
    hRv->force = FALSE;
    TSK_enable();
}

/******************************************************************************
 * Rendezvous_forceAndReset
 ******************************************************************************/
Void Rendezvous_forceAndReset(Rendezvous_Handle hRv)
{
    Int i;
    
    assert(hRv);

    TSK_disable();
    /* post the semaphore for all blocked tasks */
    for (i = 0; i < hRv->numWaiting; i++) {
        SEM_post(&hRv->sem);
    } 
    hRv->numWaiting = 0;
    hRv->force = FALSE;
    TSK_enable();
}
