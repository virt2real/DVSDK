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
 *  ======== Thread_noOS.c ========
 */

#include <xdc/std.h>

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include <ti/sdo/ce/osal/Thread.h>

#include <ti/sdo/utils/trace/gt.h>

Thread_Attrs Thread_ATTRS;

static Int curInit = 0;                 /* module init counter */
static GT_Mask curTrace = {NULL,NULL};

/*
 *  ======== Thread_create ========
 */
Thread_Handle Thread_create(Fxn fxn, Thread_Attrs *attrs, ...)
{
    GT_assert(curTrace, curInit > 0);

    return (Thread_Handle)(!0);
}

/*
 *  ======== Thread_delete ========
 */
Void Thread_delete(Thread_Handle task)
{
    GT_assert(curTrace, curInit > 0);
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

    return NULL;
}

/*
 *  ======== Thread_getname ========
 */
String Thread_getname(Thread_Handle task)
{
    GT_assert(curTrace, curInit > 0);

    return ("dummy task name");
}

/*
 *  ======== Thread_getpri ========
 */
Int Thread_getpri(Thread_Handle task)
{
    GT_assert(curTrace, curInit > 0);

    return (0);
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
}

/*
 *  ======== Thread_self ========
 */
Thread_Handle Thread_self()
{
    GT_assert(curTrace, curInit > 0);

    return (Thread_Handle)(!0);
}

/*
 *  ======== Thread_setpri ========
 */
Int Thread_setpri(Thread_Handle task, Int newpri)
{
    GT_assert(curTrace, curInit > 0);

    return (0);
}

/*
 *  ======== Thread_stat ========
 */
Int Thread_stat(Thread_Handle task, Thread_Stat *buf)
{
    GT_assert(curTrace, curInit > 0);

    return (-1);
}

/*
 *  ======== Thread_yield ========
 */
Void Thread_yield()
{
    GT_assert(curTrace, curInit > 0);

}
/*
 *  @(#) ti.sdo.ce.osal.noOS; 2, 0, 1,181; 12-2-2010 21:24:51; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

