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
 *  ======== SemMP_posix.c ========
 */

#include <xdc/std.h>

#include <stdlib.h>
#include <windows.h>

#include <ti/sdo/utils/trace/gt.h>
#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/ce/osal/Global.h>

#include <ti/sdo/ce/osal/SemMP.h>


/* Maximum tries to enter critical section before printing warning */
#define MAXCOUNT 100000


/*
 *  ======== SemMP_Obj ========
 */
typedef struct SemMP_Obj {
    HANDLE id;     /* ID of IPC semaphore */
} SemMP_Obj;

/*
 *  REMINDER: If you add an initialized static variable, reinitialize it at
 *  cleanup
 */
static Int curInit = 0;
static GT_Mask curTrace = {NULL, NULL};

static Void    cleanup(Void);


/*
 *  ======== SemMP_create ========
 */
SemMP_Handle SemMP_create(Int key, Int count)
{
    HANDLE     mutexId;
    HANDLE     semId;
    SemMP_Obj *sem;
        TCHAR      tszKey[MAX_PATH + 1] = TEXT("");

    GT_2trace(curTrace, GT_ENTER, "SemMP_create> key: 0x%x count: %d\n", key,
            count);

    if ((sem = (SemMP_Obj *)Memory_alloc(sizeof(SemMP_Obj), NULL)) == NULL) {
        GT_0trace(curTrace, GT_7CLASS, "SemMP_create> Memory_alloc failed\n");
        return (NULL);
    }

        _stprintf(tszKey, TEXT("%d"), key);
        sem->id = CreateSemaphore(NULL, count, count, tszKey);

        GT_1trace(curTrace, GT_ENTER, "SemMP_create> semId: 0x%x\n", sem->id);

    GT_1trace(curTrace, GT_ENTER, "Leaving SemMP_create> sem[0x%x]\n", sem);

    return (sem);
}

/*
 *  ======== SemMP_delete ========
 */
Void SemMP_delete(SemMP_Handle sem)
{
    HANDLE     mutexId;
    Int     refCount;

    GT_1trace(curTrace, GT_ENTER, "Entered SemMP_delete> sem[0x%x]\n", sem);

    if (sem != NULL) {
        GT_1trace(curTrace, GT_ENTER, "SemMP_delete> sem: 0x%x\n", sem->id);

                CloseHandle(sem->id);

        Memory_free(sem, sizeof(SemMP_Obj), NULL);
    }

    GT_0trace(curTrace, GT_ENTER, "Leaving SemMP_delete>\n");
}

/*
 *  ======== SemMP_getCount ========
 */
Int SemMP_getCount(SemMP_Handle sem)
{
    Int      count = 0;

    // not supported in WinCE - if we ever get here, we may have to look at
    // the caller's code and do additional porting
        ASSERT(FALSE);

    return (count);
}

/*
 *  ======== SemMP_getRefCount ========
 */
Int SemMP_getRefCount(SemMP_Handle sem)
{
    Int      count = 0;

    // not supported in WinCE - if we ever get here, we may have to look at
    // the caller's code and do additional porting
        ASSERT(FALSE);

    return (count);
}

/*
 *  ======== SemMP_init ========
 */
Void SemMP_init(Void)
{
    if (curInit++ == 0) {
        GT_create(&curTrace, SemMP_GTNAME);

        Global_atexit((Fxn)cleanup);
    }
}

/*
 *  ======== SemMP_pend ========
 */
Int SemMP_pend(SemMP_Handle sem, UInt32 timeout)
{
    Int    status = SemMP_EOK;

    GT_2trace(curTrace, GT_ENTER,
            "Entered SemMP_pend> sem[0x%x] timeout[0x%x]\n", sem, timeout);

        WaitForSingleObject(sem->id, INFINITE);

        GT_1trace(curTrace, GT_ENTER, "Leaving SemMP_pend> sem[0x%x]\n", sem);

    return (status);
}

/*
 *  ======== SemMP_post ========
 */
Void SemMP_post(SemMP_Handle sem)
{
    GT_1trace(curTrace, GT_ENTER, "Entered SemMP_post> sem[0x%x]\n", sem);

        ReleaseSemaphore(sem->id, 1, NULL);

    GT_1trace(curTrace, GT_ENTER, "Leaving SemMP_post> sem[0x%x]\n", sem);
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

