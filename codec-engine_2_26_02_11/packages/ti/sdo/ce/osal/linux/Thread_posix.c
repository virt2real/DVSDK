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
 *  ======== Thread_posix.c ========
 */

#include <xdc/std.h>

#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>  /* for perror() */

#include <pthread.h>
#include <sched.h>

#include <ti/sdo/ce/osal/Thread.h>
#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/ce/osal/Global.h>

#include <ti/sdo/utils/trace/gt.h>

typedef struct Thread_Obj {
    pthread_t   pthread;
    pthread_attr_t pattrs;
    Fxn         fxn;
    Arg         args[8];
    String      name;
    Ptr         env;
    Int         pri;
    Bool        terminated;
    Int         pthreadStatus;
    Int         exitStatus;
} Thread_Obj;

Thread_Attrs Thread_ATTRS = {
    1,    /* priority */
    1024, /* stack size */
    0,    /* stack seg */
    NULL, /* environ */
};

static pthread_key_t taskKey;
static Void cleanup(Void *task);
static Void runStub(Thread_Obj *task);

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

    /* create a realtime thread */
    pthread_attr_init(&task->pattrs);
    if (FALSE) {    /* TODO:L pthread_create fails if we do this */
        struct sched_param priParam;
        pthread_attr_setschedpolicy(&task->pattrs, SCHED_FIFO);
        pthread_attr_getschedparam(&task->pattrs,  &priParam);
        priParam.sched_priority = task->pri;
        pthread_attr_setschedparam(&task->pattrs,  &priParam);
    }

    task->pthreadStatus = pthread_create(&task->pthread, &task->pattrs,
        (void *(*)(void *))runStub, (void*)task);
    if (task->pthreadStatus != 0) {
        perror("Thread_create");
        Thread_delete(task);
        return (NULL);
    }

    GT_1trace(curTrace, GT_ENTER, "Thread_create> Exit (task=0x%x)\n", task);

    return (task);
}

/*
 *  ======== Thread_delete ========
 */
Void Thread_delete(Thread_Handle task)
{
    GT_assert(curTrace, curInit > 0);

    GT_1trace(curTrace, GT_ENTER, "Thread_delete> Enter (task=0x%x)\n", task);

    if (task != NULL) {
        Bool cancel = (task->pthreadStatus == 0);

        if (task != Thread_self()) {
            if (cancel) {
                int result;

                result = pthread_cancel(task->pthread);
                GT_1trace(curTrace, GT_4CLASS, "Thread_delete> pthread_cancel "
                    "(0x%x)\n", result);
                result = pthread_join(task->pthread, NULL);
                GT_1trace(curTrace, GT_4CLASS, "Thread_delete> pthread_join "
                    "(0x%x)\n", result);
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
        pthread_key_delete(taskKey);
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

        GT_create(&curTrace, Thread_GTNAME);

        pthread_key_create(&taskKey, NULL);
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

    pthread_join(task->pthread, NULL);

    GT_1trace(curTrace, GT_ENTER, "Thread_join> Exit (task=0x%x)\n", task);
}

/*
 *  ======== Thread_self ========
 */
Thread_Handle Thread_self()
{
    GT_assert(curTrace, curInit > 0);

    return ((Thread_Handle)pthread_getspecific(taskKey));
}

/*
 *  ======== Thread_setpri ========
 */
Int Thread_setpri(Thread_Handle task, Int newPri)
{
    pthread_attr_t pattrs;
    struct sched_param priParam;
    Int    oldPri;

    GT_assert(curTrace, curInit > 0);

    pthread_attr_init(&pattrs);
    pthread_attr_getschedparam(&pattrs, &priParam);
    oldPri = priParam.sched_priority;
    priParam.sched_priority = newPri;
    task->pri = newPri;
    pthread_setschedparam(task->pthread, SCHED_FIFO, &priParam);
    return oldPri;
}

/*
 *  ======== Thread_stat ========
 */
Int Thread_stat(Thread_Handle task, Thread_Stat *buf)
{
    size_t stacksize;

    GT_assert(curTrace, curInit > 0);

#if 0
    void *stackaddr;

    /* get stack is the prefered method (when it's available): getstackaddr
     * does not guarantee that the address is the lowest address (it may be
     * the highest on architectures whose stack grows upward)
     */
    if (pthread_attr_getstack(&task->pattrs, &stackaddr, &stacksize) != 0) {
        return (-1);
    }
#else
    if (pthread_attr_getstacksize(&task->pattrs, &stacksize) != 0) {
        return (-1);
    }
#endif

    buf->stacksize = stacksize;
    buf->stackused = 0;     /* HACK! we should really compute this */

    return (0);
}

/*
 *  ======== Thread_yield ========
 */
Void Thread_yield()
{
    GT_assert(curTrace, curInit > 0);

    sched_yield();
}

/*
 *  ======== runStub ========
 */
static void runStub(Thread_Obj *task)
{
    pthread_setspecific(taskKey, task);

    /* PTHREAD_CANCEL_ASYNCHRONOUS is potentially dangerous: this allows
     * the thread to be cancelled in the middle of malloc, for example.
     */
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

    task->exitStatus = (Int)task->fxn(
        task->args[0], task->args[1], task->args[2], task->args[3],
        task->args[4], task->args[5], task->args[6], task->args[7]
    );

    pthread_exit(task);
}

/*
 *  ======== cleanup ========
 */
static Void cleanup(Void *ptr)
{
    if (--curInit == 0) {
        pthread_key_delete(taskKey);
    }
}
/*
 *  @(#) ti.sdo.ce.osal.linux; 2, 0, 1,181; 12-2-2010 21:24:47; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

