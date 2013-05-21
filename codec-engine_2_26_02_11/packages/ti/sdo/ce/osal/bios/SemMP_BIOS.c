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
 *  ======== Sem.c ========
 */
#include <xdc/std.h>
#include <assert.h>

#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/ce/osal/Sem.h>
#include <ti/sdo/ce/osal/SemMP.h>


/*
 *  ======== SemMP_create ========
 */
SemMP_Handle SemMP_create(Int key, Int count)
{
    SemMP_Handle sem;

    sem = (SemMP_Handle)Sem_create(key, count);

    return ((SemMP_Handle)sem);
}

/*
 *  ======== SemMP_delete ========
 */
Void SemMP_delete(SemMP_Handle sem)
{
    if (sem != NULL) {
        Sem_delete((Sem_Handle)sem);
    }
}

/*
 *  ======== SemMP_getCount ========
 */
Int SemMP_getCount(SemMP_Handle sem)
{
    return (Sem_getCount((Sem_Handle)sem));
}

/*
 *  ======== SemMP_getRefCount ========
 */
Int SemMP_getRefCount(SemMP_Handle sem)
{
    return (-1);
}

/*
 *  ======== SemMP_init ========
 */
Void SemMP_init(Void)
{
}

/*
 *  ======== SemMP_pend ========
 */
Int SemMP_pend(SemMP_Handle sem, UInt32 timeout)
{
    return (Sem_pend((Sem_Handle)sem, timeout));
}

/*
 *  ======== SemMP_post ========
 */
Void SemMP_post(SemMP_Handle sem)
{
    Sem_post((Sem_Handle)sem);
}
/*
 *  @(#) ti.sdo.ce.osal.bios; 2, 0, 1,182; 12-2-2010 21:24:43; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

