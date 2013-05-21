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
 *  ======== Sem_noOS.c ========
 *  Mock semaphore implementation 
 */
#include <xdc/std.h>
#include <assert.h>


/*
 *  ======== Sem_Obj ========
 */
typedef struct Sem_Obj {
    Int count;
} Sem_Obj;

typedef Sem_Obj * Sem_Handle;

static int index= 0;

static Sem_Obj semArr[200];


/*
 *  ======== Sem_create ========
 */
/* ARGSUSED */
Sem_Handle Sem_create(Int key, Int count)
{
    Sem_Handle sem;

/*
    if ((sem = (Sem_Obj *)Memory_alloc(sizeof(Sem_Obj), NULL)) == NULL) {
        return (NULL);
    }
*/
    sem = &semArr[index++]; 

    sem->count = count;

    return (sem);
}

/*
 *  ======== Sem_delete ========
 */
/* ARGSUSED */
Void Sem_delete(Sem_Handle sem)
{
    if (sem != NULL) {
        //assert(sem->count >= 0);
/*          Memory_free(sem, sizeof (Sem_Obj), NULL);*/
    }
}

/*
 *  ======== Sem_getCount ========
 */
Int Sem_getCount(Sem_Handle sem)
{
    return (sem->count);
}

/*
 *  ======== Sem_init ========
 */
Void Sem_init(Void)
{
}

/*
 *  ======== Sem_pend ========
 */
/* ARGSUSED */
Int Sem_pend(Sem_Handle sem, UInt32 timeout)
{
    sem->count--;

    return (0);
}

/*
 *  ======== Sem_post ========
 */
Void Sem_post(Sem_Handle sem)
{
    sem->count++;
}

/*
 *  ======== Sem_reset ========
 */
Void Sem_reset(Sem_Handle sem, Int count)
{
    sem->count = count;
}
/*
 *  @(#) ti.sdo.fc.rman.examples; 1, 0, 0,123; 12-1-2010 17:25:37; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

