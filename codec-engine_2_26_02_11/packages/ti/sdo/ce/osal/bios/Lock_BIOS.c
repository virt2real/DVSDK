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
 *  ======== Lock_BIOS.c ========
 */
#include <xdc/std.h>

#include <ti/bios/include/std.h>
#include <ti/bios/include/sem.h>
#include <ti/bios/include/sys.h>
#include <ti/bios/include/tsk.h>

#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/ce/osal/Lock.h>

/*
 *  ======== Lock_Obj ========
 */
typedef struct Lock_Obj {
    TSK_Handle owner;
    Int        count;
    SEM_Handle mutex;
} Lock_Obj;

static Lock_Obj systemLock;

/*
 *  ======== Lock_ATTRS ========
 */
Lock_Attrs Lock_ATTRS = {
    0
};

/*
 *  ======== Lock_system ========
 */
Lock_Handle Lock_system = &systemLock;

/*
 *  ======== Lock_acquire ========
 */
Void Lock_acquire(Lock_Handle lock)
{
    if (TSK_self() == lock->owner) {
        lock->count++;
        return;
    }

    SEM_pend(lock->mutex, SYS_FOREVER);

    lock->owner = TSK_self();
}

/*
 *  ======== Lock_create ========
 */
Lock_Handle Lock_create(Lock_Attrs *attrs)
{
    Lock_Handle lock;
    
    if (attrs == NULL) {
        attrs = &Lock_ATTRS;
    }

    if ((lock = (Lock_Obj *)Memory_alloc(sizeof(Lock_Obj), NULL)) == NULL) {
        return (NULL);
    }

    lock->mutex = SEM_create(1, NULL);
    if (lock->mutex == NULL) {
        Lock_delete(lock);
        return (NULL);
    }

    lock->owner = NULL;
    lock->count = 0;

    return (lock);
}

/*
 *  ======== Lock_delete ========
 */
Void Lock_delete(Lock_Handle lock)
{
    if (lock != NULL) {
        if (lock->mutex != NULL) {
            SEM_delete(lock->mutex);
        }

        Memory_free(lock, sizeof (Lock_Obj), NULL);
    }
}

/*
 *  ======== Lock_init ========
 */
Void Lock_init(Void)
{
    static Bool curInit = FALSE;

    if (curInit == FALSE) {
        curInit = TRUE;

        Lock_system = Lock_create(NULL);
    }
}

/*
 *  ======== Lock_release ========
 */
Void Lock_release(Lock_Handle lock)
{
    if (TSK_self() == lock->owner) {
        if (lock->count > 0) {
            lock->count--;
            return;
        }
        else {
            lock->owner = NULL;
            SEM_post(lock->mutex);
        }
    }
}

/*
 *  @(#) ti.sdo.ce.osal.bios; 2, 0, 1,182; 12-2-2010 21:24:43; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

