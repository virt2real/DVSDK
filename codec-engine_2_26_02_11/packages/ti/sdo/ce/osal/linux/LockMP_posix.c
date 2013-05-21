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
 *  ======== LockMP_posix.c ========
 */

#include <xdc/std.h>

#include <pthread.h>

#include <sys/types.h>
#include <unistd.h>

#include <ti/sdo/utils/trace/gt.h>
#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/ce/osal/Global.h>
#include <ti/sdo/ce/osal/SemMP.h>

#include <ti/sdo/ce/osal/LockMP.h>

/*
 *  ======== LockMP_Obj ========
 */
typedef struct LockMP_Obj {
    SemMP_Handle  sem;    /*  IPC semaphore */
    Int           value;  /*  Number of times Lock has been acquired */
    pthread_t     owner;  /*  ID of owning thread */
    pid_t         pid;    /*  ID of owning process (in case thread id is not
                           *  unique across processes.
                           */
} LockMP_Obj;

/*
 *  REMINDER: If you add an initialized static variable, reinitialize it at
 *  cleanup
 */
static Bool curInit = FALSE;
static GT_Mask curTrace = {NULL, NULL};

static Void    cleanup(Void);

/*
 *  ======== LockMP_acquire ========
 */
Void LockMP_acquire(LockMP_Handle lock)
{
    pthread_t       self;
    pid_t           pid;
    Int             status = SemMP_EOK;

    GT_1trace(curTrace, GT_ENTER, "Entered LockMP_acquire> lock[0x%x]\n",
            lock);

    self = pthread_self();
    pid = getpid();

    if ((lock->owner != self) || (lock->pid != pid)) {
        /* This thread does not currently own the lock */
        status = SemMP_pend(lock->sem, SemMP_FOREVER);
        GT_assert(curTrace, status == SemMP_EOK);
    }

    if (status == SemMP_EOK) {
        lock->pid = pid;
        lock->owner = self;
        lock->value++;
    }

    GT_1trace(curTrace, GT_ENTER, "Leaving LockMP_acquire> lock[0x%x]\n",
            lock);
}

/*
 *  ======== LockMP_create ========
 */
LockMP_Handle LockMP_create(Int key)
{
    LockMP_Obj *lock;

    GT_1trace(curTrace, GT_ENTER,
            "LockMP_create> key: 0x%x count: %d attrs: 0x%x\n", key);

    lock = (LockMP_Obj *)Memory_alloc(sizeof(LockMP_Obj), NULL);
    if (lock == NULL) {
        GT_0trace(curTrace, GT_7CLASS, "LockMP_create> Memory_alloc failed\n");
        return (NULL);
    }

    /* Create IPC semaphore with count 1 */
    lock->sem = SemMP_create(key, 1);
    if (lock->sem == NULL) {
        GT_0trace(curTrace, GT_7CLASS, "LockMP_create> SemMP_create failed\n");
        LockMP_delete(lock);
        return (NULL);
    }

    lock->value = 0;
    lock->owner = (pthread_t)NULL;
    lock->pid = (pid_t)NULL;

    GT_1trace(curTrace, GT_ENTER, "Leaving LockMP_create> lock[0x%x]\n", lock);

    return (lock);
}

/*
 *  ======== LockMP_delete ========
 */
Void LockMP_delete(LockMP_Handle lock)
{
    GT_1trace(curTrace, GT_ENTER, "Entered LockMP_delete> lock[0x%x]\n", lock);

    if (lock != NULL) {
        if (lock->sem != NULL) {
            SemMP_delete(lock->sem);
        }

        Memory_free(lock, sizeof(LockMP_Obj), NULL);
    }

    GT_0trace(curTrace, GT_ENTER, "Leaving LockMP_delete>\n");
}

/*
 *  ======== LockMP_getCount ========
 */
Int LockMP_getCount(LockMP_Handle lock)
{
    return (lock->value);
}

/*
 *  ======== LockMP_getRefCount ========
 */
Int LockMP_getRefCount(LockMP_Handle lock)
{
    return (SemMP_getRefCount(lock->sem));
}

/*
 *  ======== LockMP_init ========
 */
Void LockMP_init(Void)
{
    if (curInit++ == 0) {
        GT_create(&curTrace, LockMP_GTNAME);

        Global_atexit((Fxn)cleanup);
    }
}

/*
 *  ======== LockMP_release ========
 */
Void LockMP_release(LockMP_Handle lock)
{
    GT_1trace(curTrace, GT_ENTER, "Entered LockMP_release>lock[0x%x]\n", lock);

    GT_assert(curTrace, lock->owner == pthread_self());
    GT_assert(curTrace, lock->pid == getpid());
    GT_assert(curTrace, lock->value > 0);

    lock->value--;

    if (lock->value == 0) {
        lock->owner = (pthread_t)NULL;
        lock->pid = (pid_t)NULL;
        SemMP_post(lock->sem);
    }

    GT_1trace(curTrace, GT_ENTER, "Leaving LockMP_release>lock[0x%x]\n", lock);
}

/*
 *  ======== cleanup ========
 */
static Void cleanup(Void)
{
    GT_assert(curTrace, curInit > 0);

    if (--curInit == 0) {
        /* Nothing to do */
    }
}
/*
 *  @(#) ti.sdo.ce.osal.linux; 2, 0, 1,181; 12-2-2010 21:24:46; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

