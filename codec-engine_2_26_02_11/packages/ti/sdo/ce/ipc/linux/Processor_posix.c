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

#include <ti/sdo/utils/trace/gt.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/ce/ipc/Processor.h>

static String argv[] = {"", NULL};

Processor_Attrs Processor_ATTRS = {
    "dsp0",
    1,
    argv
};

/*
 *  ======== Processor_Obj ========
 */
typedef struct Processor_Obj {
    Int pid;
} Processor_Obj;

static GT_Mask curTrace = {NULL,NULL};

/*
 *  ======== Processor_create ========
 */
Processor_Handle Processor_create(String imageName, String linkCfg, 
    Processor_Attrs *attrs)
{
    Processor_Handle proc;

    GT_2trace(curTrace, GT_ENTER, "Processor_create> "
        "Enter(imageName='%s', attrs=0x%x)\n", imageName, attrs);

    if (attrs == NULL) {
        attrs = &Processor_ATTRS;
    }
    
    if ((proc = Memory_alloc(sizeof (Processor_Obj), NULL)) == NULL) {
        GT_0trace(curTrace, GT_7CLASS, "Processor_create> "
                  "ERROR: Memory_alloc failed\n");
        return (NULL);
    }

    if ((proc->pid = fork()) == 0) {
        execv(imageName, attrs->argv);
        perror("Processor_create: execv failed");
    }
    if (proc->pid < 0) {
        Processor_delete(proc);
        proc = NULL;
    }

    GT_1trace(curTrace, GT_ENTER, "Processor_create> "
        "return (0x%x)\n", proc);

    return (proc);
}

/*
 *  ======== Processor_delete ========
 */
Void Processor_delete(Processor_Handle proc)
{
    GT_1trace(curTrace, GT_ENTER, "Processor_delete> "
        "Enter(proc=0x%x)\n", proc);

    if (proc != NULL) {
        if (proc->pid > 0) {
            kill(proc->pid, SIGHUP);
        }

        GT_1trace(curTrace, GT_1CLASS,
            "Processor_delete(0x%x) freeing object ...\n", proc);
        Memory_free(proc, sizeof (Processor_Obj), NULL);
    }

    GT_0trace(curTrace, GT_ENTER, "Processor_delete> return.\n");
}


/*
 *  ======== Processor_init ========
 */
Void Processor_init(Void)
{
    static Bool curInit = FALSE;

    if (curInit != TRUE) {
        curInit = TRUE;

        GT_create(&curTrace, Processor_GTNAME);

    }
}

/*
 *  ======== Processor_wait ========
 */
Int Processor_wait(Processor_Handle proc)
{
    Int status;
    if (waitpid(proc->pid, &status, 0) < 0) {
        status = -1;
    }

    return (status);
}
/*
 *  @(#) ti.sdo.ce.ipc.linux; 2, 0, 1,179; 12-2-2010 21:24:23; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

