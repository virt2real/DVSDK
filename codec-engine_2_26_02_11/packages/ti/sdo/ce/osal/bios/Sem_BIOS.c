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
 *  ======== Sem_BIOS.c ========
 */

#include <xdc/std.h>

#include <ti/bios/include/std.h>
#include <ti/bios/include/sem.h>

#include <ti/sdo/utils/trace/gt.h>
#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/ce/osal/Global.h>

#include <ti/sdo/ce/osal/Sem.h>


static Bool curInit = FALSE;
static GT_Mask curTrace = {NULL, NULL};

/*
 *  ======== Sem_create ========
 */
Sem_Handle Sem_create(Int key, Int count)
{
    SEM_Handle sem;

    GT_1trace(curTrace, GT_ENTER, "Sem_create> count %d\n", count);

    if ((sem = SEM_create(count, NULL)) == NULL) {
        GT_0trace(curTrace, GT_7CLASS, "Sem_create> SEM_create failed\n");
    }

    GT_1trace(curTrace, GT_ENTER, "Sem_create> sem: 0x%lx\n", sem);

    return ((Sem_Handle)sem);
}

/*
 *  ======== Sem_delete ========
 */
Void Sem_delete(Sem_Handle sem)
{
    GT_1trace(curTrace, GT_ENTER, "Sem_delete> sem: 0x%lx\n", sem);

    if (sem != NULL) {
        SEM_delete((SEM_Handle)sem);
    }
}

/*
 *  ======== Sem_getCount ========
 */
Int Sem_getCount(Sem_Handle sem)
{
    return (((SEM_Handle)sem)->count);
}

/*
 *  ======== Sem_init ========
 */
Void Sem_init(Void)
{
    if (curInit == FALSE) {
        curInit = TRUE;
        GT_create(&curTrace, Sem_GTNAME);
    }
}

/*
 *  ======== Sem_pend ========
 */
Int Sem_pend(Sem_Handle sem, UInt32 timeout)
{
    Int     status = Sem_EOK;

    if (SEM_pend((SEM_Handle)sem, timeout) == FALSE) {
        status = Sem_ETIMEOUT;
    }

    return (status);
}

/*
 *  ======== Sem_post ========
 */
Void Sem_post(Sem_Handle sem)
{
    SEM_post((SEM_Handle)sem);
}
/*
 *  @(#) ti.sdo.ce.osal.bios; 2, 0, 1,182; 12-2-2010 21:24:43; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

