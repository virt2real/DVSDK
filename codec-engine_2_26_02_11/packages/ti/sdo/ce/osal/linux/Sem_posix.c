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
 *  ======== Sem_posix.c ========
 */

#include <xdc/std.h>

#include <semaphore.h>

#include <ti/sdo/utils/trace/gt.h>
#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/ce/osal/Global.h>

#include <ti/sdo/ce/osal/Sem.h>

#define _Sem_SEMCOUNT 0 /* Array index of semaphore holding the count */
#define _Sem_REFCOUNT 1 /* Array index of semaphore holding the ref count */

#define NUMSEMS 2 /* Size of semaphore array */



/*
 *  ======== Sem_Obj ========
 */
typedef struct Sem_Obj {
    sem_t   sem;
    Int     id;     /* ID of IPC semaphore */
} Sem_Obj;

/*
 *  REMINDER: If you add an initialized static variable, reinitialize it at
 *  cleanup
 */
static Int curInit = 0;
static GT_Mask curTrace = {NULL, NULL};

static Void    cleanup(Void);

/*
 *  ======== Sem_create ========
 */
Sem_Handle Sem_create(Int key, Int count)
{
    Int     pshared = 0;  /* Semaphore is not shared by different processes */
    Sem_Obj *sem;

    GT_1trace(curTrace, GT_ENTER, "Sem_create> count: %d\n", count);

    if ((sem = (Sem_Obj *)Memory_alloc(sizeof(Sem_Obj), NULL)) == NULL) {
        GT_0trace(curTrace, GT_7CLASS, "Sem_create> Memory_alloc failed\n");
        return (NULL);
    }

    if (sem_init(&(sem->sem), pshared, count) != 0) {
        GT_0trace(curTrace, GT_7CLASS, "Sem_create> sem_init() failed\n");
        Memory_free(sem, sizeof(Sem_Obj), NULL);
        return (NULL);
    }

    GT_1trace(curTrace, GT_ENTER, "Leaving Sem_create> sem[0x%x]\n", sem);

    return (sem);
}

/*
 *  ======== Sem_delete ========
 */
Void Sem_delete(Sem_Handle sem)
{
    GT_1trace(curTrace, GT_ENTER, "Entered Sem_delete> sem[0x%x]\n", sem);

    if (sem != NULL) {
        sem_destroy(&(sem->sem));
        Memory_free(sem, sizeof(Sem_Obj), NULL);
    }

    GT_0trace(curTrace, GT_ENTER, "Leaving Sem_delete>\n");
}

/*
 *  ======== Sem_getCount ========
 */
Int Sem_getCount(Sem_Handle sem)
{
    Int      count = -1;

    if (sem_getvalue(&(sem->sem), &count) != 0) {
        GT_0trace(curTrace, GT_7CLASS,
                "Sem_getCount> sem_getvalue() failed\n");
    }

    return (count);
}

/*
 *  ======== Sem_init ========
 */
Void Sem_init(Void)
{
    if (curInit++ == 0) {
        GT_create(&curTrace, Sem_GTNAME);

        Global_atexit((Fxn)cleanup);
    }
}

/*
 *  ======== Sem_pend ========
 */
Int Sem_pend(Sem_Handle sem, UInt32 timeout)
{
    Int    status = Sem_EOK;

    GT_2trace(curTrace, GT_ENTER,
            "Entered Sem_pend> sem[0x%x] timeout[0x%x]\n", sem, timeout);

    /* Timeouts not supported yet */
    GT_assert(curTrace, timeout == Sem_FOREVER);

    sem_wait(&(sem->sem)); /* TODO: can try sem_timedwait */

    GT_2trace(curTrace, GT_ENTER, "Leaving Sem_pend> sem[0x%x] status[%d]\n",
            sem, status);

    return (status);
}

/*
 *  ======== Sem_post ========
 */
Void Sem_post(Sem_Handle sem)
{
    GT_1trace(curTrace, GT_ENTER, "Entered Sem_post> sem[0x%x]\n", sem);

    sem_post(&(sem->sem));

    GT_1trace(curTrace, GT_ENTER, "Leaving Sem_post> sem[0x%x]\n", sem);
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
 *  @(#) ti.sdo.ce.osal.linux; 2, 0, 1,181; 12-2-2010 21:24:47; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

