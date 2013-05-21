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
 *  ======== Thread_posix.c ========
 */

#include <xdc/std.h>

#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>  /* for perror() */

#include <windows.h>
#include <linklist.h>

#include <ti/sdo/ce/osal/Thread.h>
#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/ce/osal/Global.h>

#include <ti/sdo/utils/trace/gt.h>

typedef struct Thread_Obj {
    HANDLE         hThread;
        DWORD              dwThreadId;
    Fxn         fxn;
    Arg         args[8];
    String      name;
    Ptr         env;
    Int         pri;
    Bool        terminated;
    Int         pthreadStatus;
    Int         exitStatus;
} Thread_Obj;

typedef struct Thread_Private_Data
{
        LIST_ENTRY      listEntry;
        DWORD                   dwThreadId;
        Thread_Handle   task;
} Thread_Private_Data;

Thread_Attrs Thread_ATTRS = {
    251,    /* priority */
    1024, /* stack size */
    0,    /* stack seg */
    NULL, /* environ */
};

Thread_Private_Data gThreadPrivateDataList;
int gListCSInitialized = 0;
CRITICAL_SECTION *pListCS = NULL;

static Void cleanup(Void *task);
static DWORD WINAPI runStub(LPVOID pThreadObj);

static Int curInit = 0;                 /* module init counter */
static GT_Mask curTrace = {NULL,NULL};

/*
 *  ======== Thread_create ========
 *  Note: Linux uses clone( ... CLONE_SIGHAND ...) to create threads.  This
 *  means that changing a signal handler in one thread will change the handler
 *  for all threads in a process.  However, it is possible to set different
 *  signal masks on a per-thread basis.
 */
Thread_Handle Thread_create(Fxn fxn, Thread_Attrs *attrs, ...)
{
    va_list va;
    Thread_Handle task;
    Int i;
        DWORD dwTID;
        Thread_Private_Data *pThreadPrivateData;

    GT_2trace(curTrace, GT_ENTER, "Thread_create> Enter (fxn=0x%x, attrs=0x%x)"
        "\n", fxn, attrs);

    GT_assert(curTrace, curInit > 0);

    if (attrs == NULL) {
        attrs = &Thread_ATTRS;
    }

    if ((task = (Thread_Handle)Memory_alloc(sizeof (Thread_Obj), NULL)) ==
        NULL) {
        return (NULL);
    }

    task->pri = attrs->priority;
    task->name = attrs->name;
    task->env = attrs->environ;

    task->terminated = FALSE;
    task->pthreadStatus = -1;

    task->fxn = fxn;

    /* copy up to 8 arguments from stack */
    va_start(va, attrs);
    for (i = 0; i < 8; i++) {
        task->args[i] = va_arg(va, Arg);
    }

        task->hThread = CreateThread(NULL, 0, runStub, (void*)task, CREATE_SUSPENDED, &dwTID);
        if (task->hThread)
        {
                // success
                task->pthreadStatus = 0;
                task->dwThreadId = dwTID;

                if (gListCSInitialized == 0)
                {
                        if (InterlockedIncrement(&gListCSInitialized) == 1)
                        {
                                // 1st time...initialize CS
                                CRITICAL_SECTION *pCS = (CRITICAL_SECTION*)malloc(sizeof(CRITICAL_SECTION));
                                if (pCS)
                                {
                                        InitializeCriticalSection(pCS);
                                        InterlockedExchange((LPLONG)&pListCS, (LONG)pCS);
                                }
                        }
                        else
                        {
                                InterlockedDecrement(&gListCSInitialized);
                                while (!pListCS);
                        }
                }
                else
                {
                        while (!pListCS);
                }

                pThreadPrivateData = (Thread_Private_Data*)malloc(sizeof(Thread_Private_Data));
                if (!pThreadPrivateData)
                {
                        return NULL;
                }

                EnterCriticalSection(pListCS);
                pThreadPrivateData->dwThreadId = dwTID;
                pThreadPrivateData->task = task;
                InsertTailList(&gThreadPrivateDataList.listEntry, &pThreadPrivateData->listEntry);
                LeaveCriticalSection(pListCS);

                if (task->pri < 100)
                {
                        RETAILMSG(1, (TEXT("WARNING: Thread_create(): thread priority set to %d!!!\r\n"), task->pri));
                }
                SetThreadPriority(task->hThread, task->pri);
                ResumeThread(task->hThread);
        }
        else
        {
                // failure
                task->pthreadStatus = 1;
        }


    GT_1trace(curTrace, GT_ENTER, "Thread_create> Exit (task=0x%x)\n", task);

    return (task);
}

/*
 *  ======== Thread_delete ========
 */
Void Thread_delete(Thread_Handle task)
{
        // BUG!!!!  TerminateThread() won't work for kernel threads in CE6.0.  This has to be fixed.
        Thread_Private_Data *pThreadPrivateData;

    GT_assert(curTrace, curInit > 0);

    GT_1trace(curTrace, GT_ENTER, "Thread_delete> Enter (task=0x%x)\n", task);

    if (task != NULL) {
        Bool cancel = (task->pthreadStatus == 0);

        if (task != Thread_self()) {
            if (cancel) {
                BOOL result;

                                // DANGEROUS!!!  TODO: See if there is a way to signal thread to give it time to do cleanup before
                                // terminating thread.
                                result = TerminateThread(task->hThread, 0);
                                GT_1trace(curTrace, GT_4CLASS, "Thread_delete> TerminateThread() "
                    "(0x%x)\n", result);

                                WaitForSingleObject(task->hThread, INFINITE);
                                GT_0trace(curTrace, GT_4CLASS, "Thread_delete> WaitForSingleObject(task->hThread)");

                                // remove task from global threadPrivateData list
                                if (gListCSInitialized == 0)
                                {
                                        if (InterlockedIncrement(&gListCSInitialized) == 1)
                                        {
                                                // 1st time...initialize CS
                                                CRITICAL_SECTION *pCS = (CRITICAL_SECTION*)malloc(sizeof(CRITICAL_SECTION));
                                                if (pCS)
                                                {
                                                        InitializeCriticalSection(pCS);
                                                        InterlockedExchange((LPLONG)&pListCS, (LONG)pCS);
                                                }
                                        }
                                        else
                                        {
                                                InterlockedDecrement(&gListCSInitialized);
                                                while (!pListCS);
                                        }
                                }
                                else
                                {
                                        while (!pListCS);
                                }
                                EnterCriticalSection(pListCS);
                                pThreadPrivateData = CONTAINING_RECORD(&gThreadPrivateDataList.listEntry, Thread_Private_Data, listEntry);
                                while (pThreadPrivateData && pThreadPrivateData->listEntry.Flink != &gThreadPrivateDataList.listEntry)
                                {
                                        pThreadPrivateData = CONTAINING_RECORD(pThreadPrivateData->listEntry.Flink, Thread_Private_Data, listEntry);
                                        if (pThreadPrivateData->dwThreadId == task->dwThreadId)
                                        {
                                                RemoveEntryList(&pThreadPrivateData->listEntry);
                                                free(pThreadPrivateData);
                                                break;
                                        }
                                }
                                LeaveCriticalSection(pListCS);
            }
        }

        Memory_free(task, sizeof(Thread_Obj), NULL);
    }

    GT_1trace(curTrace, GT_ENTER, "Thread_delete> Exit (task=0x%x)\n", task);
}


/*
 *  ======== Thread_exit ========
 */
Void Thread_exit(Void)
{
    GT_assert(curTrace, curInit > 0);

    if (--curInit == 0) {
    }
}


/*
 *  ======== Thread_getenv ========
 */
Ptr Thread_getenv(Thread_Handle task)
{
    GT_assert(curTrace, curInit > 0);

        return (task->env);
}

/*
 *  ======== Thread_getname ========
 */
String Thread_getname(Thread_Handle task)
{
    GT_assert(curTrace, curInit > 0);

    return (task->name);
}

/*
 *  ======== Thread_getpri ========
 */
Int Thread_getpri(Thread_Handle task)
{
    GT_assert(curTrace, curInit > 0);

    return (task->pri);
}


/*
 *  ======== Thread_init ========
 */
Bool Thread_init(Void)
{
    if (curInit++ == 0) {
                InitializeListHead(&gThreadPrivateDataList.listEntry);

        GT_create(&curTrace, Thread_GTNAME);

        Global_atexit((Fxn)cleanup);
    }

    return (TRUE);
}


/*
 *  ======== Thread_join ========
 */
Void Thread_join(Thread_Handle task)
{
    GT_assert(curTrace, curInit > 0);

    GT_1trace(curTrace, GT_ENTER, "Thread_join> Enter (task=0x%x)\n", task);

        WaitForSingleObject(task->hThread, INFINITE);

    GT_1trace(curTrace, GT_ENTER, "Thread_join> Exit (task=0x%x)\n", task);
}

/*
 *  ======== Thread_self ========
 */
Thread_Handle Thread_self()
{
        DWORD dwTID;
        Thread_Handle retVal = NULL;
        Thread_Private_Data *pThreadPrivateData;
    GT_assert(curTrace, curInit > 0);

        dwTID = GetCurrentThreadId();
        if (gListCSInitialized == 0)
        {
                if (InterlockedIncrement(&gListCSInitialized) == 1)
                {
                        // 1st time...initialize CS
                        CRITICAL_SECTION *pCS = (CRITICAL_SECTION*)malloc(sizeof(CRITICAL_SECTION));
                        if (pCS)
                        {
                                InitializeCriticalSection(pCS);
                                InterlockedExchange((LPLONG)&pListCS, (LONG)pCS);
                        }
                }
                else
                {
                        InterlockedDecrement(&gListCSInitialized);
                        while (!pListCS);
                }
        }
        else
        {
                while (!pListCS);
        }
        EnterCriticalSection(pListCS);
        pThreadPrivateData = CONTAINING_RECORD(&gThreadPrivateDataList.listEntry,
                                           Thread_Private_Data, listEntry);
        while (pThreadPrivateData &&
           pThreadPrivateData->listEntry.Flink !=
           &gThreadPrivateDataList.listEntry)
        {
                pThreadPrivateData =
            CONTAINING_RECORD(pThreadPrivateData->listEntry.Flink,
                              Thread_Private_Data, listEntry);
                if (pThreadPrivateData->dwThreadId == dwTID)
                {
                        retVal = pThreadPrivateData->task;
                        break;
                }
        }
        LeaveCriticalSection(pListCS);

        return retVal;
}

/*
 *  ======== Thread_setpri ========
 */
Int Thread_setpri(Thread_Handle task, Int newPri)
{
    Int    oldPri;

    GT_assert(curTrace, curInit > 0);

        oldPri = GetThreadPriority(task->hThread);
    SetThreadPriority(task->hThread, newPri);

    return oldPri;
}

/*
 *  ======== Thread_stat ========
 */
Int Thread_stat(Thread_Handle task, Thread_Stat *buf)
{

    GT_assert(curTrace, curInit > 0);

        // WINCE doesn't support this
        buf->stacksize = 0;
    buf->stackused = 0;     /* HACK! we should really compute this */

    return (0);
}

/*
 *  ======== Thread_yield ========
 */
Void Thread_yield()
{
    GT_assert(curTrace, curInit > 0);

        Sleep(0);
}

/*
 *  ======== runStub ========
 */
static DWORD WINAPI runStub(LPVOID pThreadObj)
{

    ((Thread_Obj*)pThreadObj)->exitStatus = (Int)((Thread_Obj*)pThreadObj)->fxn(
        ((Thread_Obj*)pThreadObj)->args[0], ((Thread_Obj*)pThreadObj)->args[1],
                ((Thread_Obj*)pThreadObj)->args[2], ((Thread_Obj*)pThreadObj)->args[3],
        ((Thread_Obj*)pThreadObj)->args[4], ((Thread_Obj*)pThreadObj)->args[5],
                ((Thread_Obj*)pThreadObj)->args[6], ((Thread_Obj*)pThreadObj)->args[7]
    );

        return ((Thread_Obj*)pThreadObj)->exitStatus;
}

/*
 *  ======== cleanup ========
 */
static Void cleanup(Void *ptr)
{
    if (--curInit == 0) {
    }
}
/*
 *  @(#) ti.sdo.ce.osal.linux; 2, 0, 1,36; 6-18-2008 01:29:08; /db/atree/library/trees/ce-i15x/src/
 */

/*
 *  @(#) ti.sdo.ce.osal.wince; 1, 0, 0,82; 12-2-2010 21:25:05; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

