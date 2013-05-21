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
 *  ======== GT_config_BIOS.c ========
 */

#include <xdc/std.h>
#include <ti/bios/include/std.h>

#include <ti/bios/include/sys.h>
#include <ti/bios/include/mem.h>
#include <ti/bios/include/tsk.h>
#include <ti/bios/include/swi.h>
#include <ti/bios/include/clk.h>
#include <ti/bios/include/sem.h>

#include <ti/sdo/utils/trace/gt.h>
#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/ce/osal/Trace.h>
#include <ti/sdo/utils/trace/CBuf.h>
#include "GT_config_BIOS.h"

/* trace buffer and its size, defined in Global.xdt */
extern Char Global_traceBuffer[];
extern Int  Global_traceBufferSize;

/* default memory segment for allocs, defined in Global.xdt */
extern Int Memory_SEGID;


static Bool        initFlag = FALSE;
static SEM_Handle  mutex    = NULL;
static CBuf_Handle traceBuf = NULL;

/*
 *  ======== GTConfig_biosInit ========
 */
Int GTConfig_biosInit(Void)
{
    if (initFlag != TRUE) {

        initFlag = TRUE;
        
        Trace_init();
        traceBuf = CBuf_create( Global_traceBuffer, 
                                Global_traceBufferSize, NULL );
        Trace_bind(traceBuf);
        
        mutex = SEM_create(1, NULL);
        if (mutex == NULL) {
            /* clean up the lock, unlock entries in the vtable */
            GT->LOCKFXN   = NULL;
            GT->UNLOCKFXN = NULL;
        }
    }

    return 1;
}


/*
 *  ======== GTConfig_sysPrintf ========
 */
Void GTConfig_sysPrintf(String format, ...)
{
    va_list va;

    va_start(va, format);

    SYS_vprintf(format, va);

    va_end(va);
}

/*
 *  ======== GTConfig_tskId ========
 */
Int GTConfig_tskId(Void)
{
    if (TSK_isTSK()) {
        return (Int)TSK_self();
    }
    else if (SWI_isSWI()) {
        return (Int)SWI_self();
    }
    else {
        return 0;
    }
}

/*
 *  ======== GTConfig_getTime ========
 */
UInt32 GTConfig_getTime(Void)
{
#ifdef xdc_target__isaCompatible_64P
#include <ti/bios/utils/c64p.h>
    return (C64P_getltime8());
#else
    return (CLK_gethtime());
#endif
}

/*
 * ======== GTConfig_sysPrintfError ========
 *  purpose:
 *      Prints error onto the standard output.
 */
void GTConfig_sysPrintfError(String fmt, ...)
{
    va_list va;

    SYS_printf("ASSERTION ERROR: ");

    va_start(va, fmt);

    SYS_vprintf(fmt, va);

    va_end(va);
}


/*
 *  ======== GTConfig_biosMemAlloc ========
 */
Ptr GTConfig_biosMemAlloc(Int size)
{
    return MEM_calloc(Memory_SEGID, size, 0);
}


/*
 *  ======== GTConfig_biosMemFree ========
 */
Void GTConfig_biosMemFree(Ptr addr, Int size)
{
    MEM_free(Memory_SEGID, addr, size);
}


/*
 *  ======== GTConfig_semPend ========
 */
Int GTConfig_semPend(Void)
{
    SEM_pend(mutex, SYS_FOREVER);
    return (1);
}


/*
 *  ======== GTConfig_semPost ========
 */
Int GTConfig_semPost(Void)
{
    SEM_post(mutex);
    return (1);
}
/*
 *  @(#) ti.sdo.ce.osal.bios; 2, 0, 1,182; 12-2-2010 21:24:42; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

