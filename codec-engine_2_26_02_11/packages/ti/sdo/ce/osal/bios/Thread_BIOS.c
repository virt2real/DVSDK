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
 *  ======== Thread_BIOS.c ========
 */

#include <xdc/std.h>

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include <ti/bios/include/std.h>
#include <ti/bios/include/tsk.h>

#include <ti/sdo/ce/osal/Thread.h>

#include <ti/sdo/utils/trace/gt.h>

Thread_Attrs Thread_ATTRS = {
    1,    /* priority */
    0,    /* stack size */
    0,    /* stack seg */
    NULL, /* environ */
};

static Int curInit = 0;                 /* module init counter */
static GT_Mask curTrace = {NULL,NULL};

/*
 *  ======== Thread_create ========
 */
Thread_Handle Thread_create(Fxn fxn, Thread_Attrs *attrs, ...)
{
    va_list     args;
    Arg         arg[8];
    Int         i;
    TSK_Handle  tsk;
    TSK_Attrs    biosAttrs = TSK_ATTRS;

    GT_assert(curTrace, curInit > 0);

    if (attrs->priority != 0) {
        biosAttrs.priority  = attrs->priority;
    }
    if (attrs->stacksize != 0) {
        biosAttrs.stacksize  = attrs->stacksize;
    }
    if (attrs->stackseg != 0) {
        biosAttrs.stackseg  = attrs->stackseg;
    }
    if (attrs->environ != NULL) {
        biosAttrs.environ  = attrs->environ;
    }
    biosAttrs.name      = attrs->name;

    GT_4trace(curTrace, GT_4CLASS,
        "Thread_create > name: \"%s\", pri:  %d, stack size:  %d, "
        "stack seg: %d\n",
        biosAttrs.name, biosAttrs.priority, biosAttrs.stacksize,
        biosAttrs.stackseg);

    /* Pass up to 8 Args (from '...' above) to TSK_create */
    va_start(args, attrs);

    for (i = 0; i < 8; i++) {
        arg[i] = va_arg(args, Arg);
    }

    va_end(va);

    tsk = TSK_create(fxn, &biosAttrs, arg[0], arg[1], arg[2], arg[3], arg[4],
            arg[5], arg[6], arg[7]);

    return ((Thread_Handle)tsk);
}

/*
 *  ======== Thread_delete ========
 */
Void Thread_delete(Thread_Handle task)
{
    GT_assert(curTrace, curInit > 0);

    TSK_delete((TSK_Handle)task);
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

    return TSK_getenv((TSK_Handle)task);
}

/*
 *  ======== Thread_getname ========
 */
String Thread_getname(Thread_Handle task)
{
    String name = TSK_getname((TSK_Handle)task);

    GT_assert(curTrace, curInit > 0);

    return (name == NULL ? "" : name);
}

/*
 *  ======== Thread_getpri ========
 */
Int Thread_getpri(Thread_Handle task)
{
    GT_assert(curTrace, curInit > 0);

    return TSK_getpri((TSK_Handle)task);
}


/*
 *  ======== Thread_init ========
 */
Bool Thread_init(Void)
{
    if (curInit++ == 0) {

        GT_create(&curTrace, Thread_GTNAME);
    }

    return (TRUE);
}


/*
 *  ======== Thread_join ========
 */
Void Thread_join(Thread_Handle task)
{
#warn Assert disabled on Thread_join for BIOS as RMS_exit calls it
    /* assert(FALSE); */
}

/*
 *  ======== Thread_self ========
 */
Thread_Handle Thread_self()
{
    GT_assert(curTrace, curInit > 0);

    return ((Thread_Handle)TSK_self());
}

/*
 *  ======== Thread_setpri ========
 */
Int Thread_setpri(Thread_Handle task, Int newpri)
{
    GT_assert(curTrace, curInit > 0);

    return (TSK_setpri((TSK_Handle)task, newpri));
}

/*
 *  ======== Thread_stat ========
 */
Int Thread_stat(Thread_Handle task, Thread_Stat *buf)
{
    TSK_Stat statBuf;

    GT_assert(curTrace, curInit > 0);

    TSK_stat((TSK_Handle)task, &statBuf);

    buf->stacksize = statBuf.attrs.stacksize;
    buf->stackused = statBuf.used;

    return (0);
}

/*
 *  ======== Thread_yield ========
 */
Void Thread_yield()
{
    GT_assert(curTrace, curInit > 0);

    TSK_yield();
}

/*
 *  @(#) ti.sdo.ce.osal.bios; 2, 0, 1,182; 12-2-2010 21:24:43; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

