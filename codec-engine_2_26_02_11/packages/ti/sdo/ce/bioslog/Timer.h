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
 *  ======== Timer.h ========
 */
#ifndef ti_sdo_ce_bioslog_Timer_
#define ti_sdo_ce_bioslog_Timer_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Timer_Obj {
    volatile Uint32     pid12;
    volatile Uint32     emumgt_clkspd;
    volatile Uint32     gpint_en;
    volatile Uint32     gpdir_dat;
    volatile Uint32     tim12;
    volatile Uint32     tim34;
    volatile Uint32     prd12;
    volatile Uint32     prd34;
    volatile Uint32     tcr;
    volatile Uint32     tgcr;
    volatile Uint32     wdtcr;
    volatile Uint32     tlgc;
    volatile Uint32     tlmr;
} Timer_Obj;

#define Timer_phys0 ((Timer_Obj *)0x01c21400)
#define Timer_phys1 ((Timer_Obj *)0x01c21800)

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.bioslog; 1, 0, 1,326; 12-2-2010 21:18:56; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

