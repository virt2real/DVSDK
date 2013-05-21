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
 *  ======== GT_config_libC.c ========
 *  Description:
 *      OS-independent --
 *        configuration parameters for GT.  This file is separated from
 *      gt.c so that GT_assert() can reference the error function without 
 *      forcing the linker to include all the code for GT_set(), GT_init(), 
 *      etc. into a fully bound image.  Thus, GT_assert() can be retained in 
 *      a program for which GT_?trace() has been compiled out.
 */

#include <xdc/std.h>

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include <ti/sdo/utils/trace/gt.h>
#include "GT_config_libC.h"


/*
 *  ======== GTConfig_libcMalloc ========
 */
Ptr GTConfig_libcMalloc(Int size)
{
    return (malloc(size));
}


/*
 *  ======== GTConfig_libcFree ========
 */
Void GTConfig_libcFree(Ptr addr, Int size)
{
    free(addr);
}

/*
 *  ======== GTConfig_vprintf ========
 */
Void GTConfig_vprintf(String format, ...)
{
    va_list va;

    va_start(va, format);
    vprintf(format, va);
    va_end(va);

    fflush(stdout);
}

/*
 *  ======== GTConfig_nop ========
 */
Int GTConfig_nop(Void)
{
    return (0);
}

/*
 * ======== GTConfig_error ========
 *  purpose:
 *      Prints error onto the standard output.
 */
void GTConfig_error(String fmt, ...)
{
    Int arg1, arg2, arg3, arg4, arg5, arg6;

    va_list va;

    va_start(va, fmt);

    arg1 = va_arg(va, Int);
    arg2 = va_arg(va, Int);
    arg3 = va_arg(va, Int);
    arg4 = va_arg(va, Int);
    arg5 = va_arg(va, Int);
    arg6 = va_arg(va, Int);

    va_end(va);

    (*GT->PRINTFXN)("ERROR: ");
    (*GT->PRINTFXN)(fmt, arg1, arg2, arg3, arg4, arg5, arg6);
}
/*
 *  @(#) ti.sdo.ce.osal.noOS; 2, 0, 1,181; 12-2-2010 21:24:49; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

