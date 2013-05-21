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
 *  ======== rtcfg_wince.c ========
 *  Common variables and functions used by WinCE non-RTSC config examples.
 */

/*
 * ======== ti.sdo.utils.trace.GT ========
 */
#include <xdc/std.h>
#include <ti/sdo/utils/trace/gt.h>


extern Void GTConfig_printf(String fmt, ...);
extern Ptr GTConfig_malloc(Int size);

extern Int GTConfig_threadId(void);
extern void GTConfig_error(String fmt, ...);
extern void GTConfig_free(Ptr, Int);
extern UInt32 GTConfig_gettimeofday(void);
extern Int GTConfig_threadLock(void);
extern Int GTConfig_threadUnlock(void);
extern Int GTConfig_init(void);

GT_Config _ti_sdo_utils_trace_GT_params = {
    GTConfig_printf,
    NULL,
    GTConfig_threadId,
    GTConfig_error,
    GTConfig_malloc,
    GTConfig_free,
    GTConfig_gettimeofday,
    GTConfig_threadLock,
    GTConfig_threadUnlock,
    GTConfig_init
};

GT_Config *GT = &_ti_sdo_utils_trace_GT_params;
/*
 *  @(#) ti.sdo.ce.utils.rtcfg; 1, 0, 1,28; 12-2-2010 21:28:00; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

