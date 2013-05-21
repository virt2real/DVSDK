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

#include <xdc/std.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <ti/sdo/utils/trace/gt.h>
#include <string.h>

#include "sharedMem.h"

#define CURTRACE ti_sdo_fc_utils_sharedMem_sharedMemory_GTMask

GT_Mask ti_sdo_fc_utils_sharedMem_sharedMemory_GTMask;

/* Align on 4-byte boundary */
#define ALIGN32(x) (Void *)((((UInt32)(x) + 3) / 4) * 4)

static Int curInit = 0;

/*
 *  ======== getSharedMemObj ========
 */
Void * SHM_getObj(LockMP_Handle lock, unsigned int shmSize, key_t key,
        SHM_InitFxn fxn, Int *shmId)
{
    Bool            shmExists = TRUE;
    Int             lockRefCount;
    Void * shmBase = NULL;

    if (curInit++ == 0) {
        GT_init();
        GT_create(&CURTRACE, SHM_GTNAME);
    }

    /* Enter critical section */
    LockMP_acquire(lock);

    /*
     *  Allocate or locate the chunk of shared memory where internal
     *  Shared Memory objects will be placed. This is to ensure that multiple
     *  processes will see the same Shared Memory objects.
     *  First attempt to get the shared memory without the IPC_CREAT
     *  flag, to see if it's already been created.
     */

    /* Create the shared memory if it doesn't exist yet */
    *shmId = shmget((key_t)(key), shmSize, 0666);

    if (*shmId == -1) {

        /*
         *  Failed to get the shared memory, so it probably hasn't been
         *  created yet.
         */
        *shmId = shmget((key_t)key, shmSize, 0666 | IPC_CREAT);

        if (*shmId == -1) {
            /* Couldn't create the shared memory */
            GT_1trace(CURTRACE, GT_7CLASS,
                    "_Shared Memory_initImpl> Failed to create shared memory "
                    "region, key = 0x%x\n", shmId);

            /* Exit critical section */
            LockMP_release(lock);

            /* Abort*/
            GT_assert(CURTRACE, *shmId != -1);

            return (FALSE);
        }
        else {
            /* The segment had not been created before */
            GT_1trace(CURTRACE, GT_ENTER,
                    "_Shared Memory_initImpl> Created shared memory, "
                    "key = 0x%x\n", *shmId);

            shmExists = FALSE;
        }
    }
    else {

        GT_1trace(CURTRACE, GT_ENTER,
                "_Shared Memory_initImpl> Shared memory, key = 0x%x already"
                " exists\n", *shmId);
    }

    /* Get the address of the shared memory region with shmat() */
    shmBase = shmat(*shmId, NULL, 0);

    if (shmBase == (void *)-1) {

        GT_1trace(CURTRACE, GT_7CLASS,
                "SHM_getObj> Failed to get shared memory "
                "address, key = 0x%x\n", *shmId);
        shmBase = (unsigned int)NULL;

        /* Exit critical section */
        LockMP_release(lock);

        /* Abort */
        GT_assert(CURTRACE, shmBase != NULL);

        return (NULL);
    }

    shmBase = ALIGN32(shmBase);
    GT_1trace(CURTRACE, GT_ENTER, "SHM_getObj> shmBase = 0x%lx\n", shmBase);

    if (shmExists) {
        /*
         *  Shared memory segment already exists. Check the Shared Memory lock
         *  reference count. Since the lock is created only once per
         *  process, if the lock reference count is 1, the calling process
         *  is the only one using Shared Memory global data. In that case, a
         *  process must have died, and we will re-initialize the Shared Memory
         *  global data.
         */
        lockRefCount = LockMP_getRefCount(lock);

        GT_1trace(CURTRACE, GT_ENTER, 
                "_Shared Memory_initImpl> "
                "Shared Memory lock reference count = %d\n", lockRefCount);

        if (lockRefCount == 1) {
            GT_0trace(CURTRACE, GT_5CLASS,
                    "_Shared Memory_initImpl> Warning: Shared Memory lock "
                    "reference count indicates no other processes are \n"
                    "currently using Shared Memory shared memory.\n"
                    "Re-initializing Shared Memory shared memory\n");

            /* This will cause the Shared Memory data to be re-initialized */
            shmExists = FALSE;
        }
    }

    if (!shmExists) {

        /* Initialize the reference count in the shared data area */
        GT_0trace(CURTRACE, GT_ENTER, "Initializing Shared Memory region\n");

        /* Initialize the _Shared Memory_data object to 0's */
        memset((Void *)shmBase, 0, shmSize);

        if (fxn) {
            fxn(shmBase);
        }
    }

    /* Exit critical section */
    LockMP_release(lock);

    return (shmBase);
}

/*
 *  ======== Shm_freeObj ========
 */
Bool SHM_freeObj(LockMP_Handle lock, Void * shmBase, Int shmId) 
{
    Int         refCount;
    struct shmid_ds    desc;
    Bool status = TRUE;

    /* Enter critical section */
    LockMP_acquire(lock);

    /*
     *  Don't move this block of code. Cannot detach shmBase until
     *  _Shared Memory_refCount is checked.
     */
    /* Detach the shared memory, but don't free it. */
    if (shmdt(shmBase) == -1) {
        /* error */
        GT_2trace(CURTRACE, GT_7CLASS,
                "Failed to detach shared memory [0x%x], key = 0x%x\n",
                shmBase, shmId);
        status = FALSE;
    }

    shmctl(shmId, IPC_STAT, &desc);

    refCount = desc.shm_nattch;

    if (refCount == 0) {
        if (shmctl(shmId, IPC_RMID, 0) == -1) {
        /* error */
            GT_2trace(CURTRACE, GT_7CLASS,
                    "Failed to free shared memory [0x%x], key = 0x%x\n",
                    shmBase, shmId);

            status = FALSE;
        }
    }

    /* Exit critical section */
    LockMP_release(lock);

    return (status);
}
/*
 *  @(#) ti.sdo.fc.utils; 1, 0, 2,286; 12-1-2010 17:26:08; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

