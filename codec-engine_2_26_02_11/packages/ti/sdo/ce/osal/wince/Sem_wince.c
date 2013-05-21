/*
 *  Copyright 2010 by Texas Instruments Incorporated.
 *
 */

/*
 *  Copyright 2008
 *  Texas Instruments Incorporated
 *
 *  All rights reserved.  Property of Texas Instruments Incorporated
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */
/*
 *  ======== Sem_posix.c ========
 */

#include <xdc/std.h>

#include <windows.h>

#include <ti/sdo/utils/trace/gt.h>
#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/ce/osal/Global.h>

#include <ti/sdo/ce/osal/Sem.h>


#define MAXCOUNT 0x1000 /* Maximum semaphore count */


/*
 *  ======== Sem_Obj ========
 */
typedef struct Sem_Obj {
    Int      count;
    HANDLE   sem;
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

    if (!(sem->sem = CreateSemaphore(NULL, count, MAXCOUNT, NULL))) {
        GT_0trace(curTrace, GT_7CLASS,
                "Sem_create> CreateSemaphore() failed\n");
        Memory_free(sem, sizeof(Sem_Obj), NULL);
        return (NULL);
    }

    sem->count = count;

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
        CloseHandle(sem->sem);
        Memory_free(sem, sizeof(Sem_Obj), NULL);
    }

    GT_0trace(curTrace, GT_ENTER, "Leaving Sem_delete>\n");
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

    // TODO: Protect this
    --sem->count;

    WaitForSingleObject(sem->sem, INFINITE);

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

    // TODO: Protect this
    ++sem->count;

    ReleaseSemaphore(sem->sem, 1, NULL);

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
 *  @(#) ti.sdo.ce.osal.wince; 1, 0, 0,82; 12-2-2010 21:25:05; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

