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
 *  ======== dbg.h ========
 *
 *  DSP-side debug support.
 *
 */

#ifndef _DBGSUPPORT_
#define _DBGSUPPORT_


#ifdef _DBG_                    /* set when 'dbg' macro used in MAKE file */

#ifdef _DBG_WITH_SYS_
#include <sys.h>
#define TRACE 0 /* unused with _DBG_WITH_SYS, but necessary */

#define DBG_printf0(a,b) SYS_printf(b)
#define DBG_printf1(a,b,c) SYS_printf(b,c)
#define DBG_printf2(a,b,c,d) SYS_printf(b,c,d)

#elif defined(_DBG_WITH_GT_)

#include <ti/sdo/fc/utils/trace/gt.h>
extern GT_Mask ti_sdo_fc_GTMask;

#define DBG_printf0(a,b) GT_0trace(ti_sdo_fc_GTMask, GT_ENTER, b "\n")
#define DBG_printf1(a,b,c) GT_1trace(ti_sdo_fc_GTMask, GT_ENTER, b "\n", c)
#define DBG_printf2(a,b,c,d) GT_2trace(ti_sdo_fc_GTMask, GT_ENTER, b "\n", c, d)

#else

#include <log.h>
#define TRACE &bridge
extern LOG_Obj bridge;
#define DBG_printf0(a,b) LOG_printf(a,b)
#define DBG_printf1(a,b,c) LOG_printf(a,b,c)
#define DBG_printf2(a,b,c,d) LOG_printf(a,b,c,d)

#endif

#else /* !_DBG_ */

#define DBG_printf0(a,b)
#define DBG_printf1(a,b,c)
#define DBG_printf2(a,b,c,d)

#endif


#endif /* _DBGSUPPORT_ */

/*
 *  @(#) ti.sdo.fc.utils; 1, 0, 2,286; 12-1-2010 17:26:08; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

