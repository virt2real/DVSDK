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
 *  ======== LogTracker.h =======
 */
#include <xdc/std.h>

#ifndef LogTracker_
#define LogTracker_

#ifdef xdc_target__isaCompatible_64P

#include <ti/bios/include/tsk.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  We use a separate LOG to handle create/exit/delete events to make sure
 *  that we don't miss any of these.
 *
 *  Format for this LOG:
 *      <sequence #>
 *      task handle
 *      name (4 bytes)
 *      name cont'd (4 bytes)
 *      name cont'd (4 bytes)   NOTE!  not NULL terminated if strlen > 15!
 *      timel
 *      timeh
 */
extern LOG_Obj ti_sdo_ce_bioslog_create;

/*
 *  Timesynch LOG -- used to synchronize time between Arm and DSP
 *
 *  Format for this LOG:
 *      <sequence #>
 *      Arm tod seconds
 *      Arm tod microseconds
 *      Arm GT time
 *      DSP GT time
 *      timer1 offset (difference in timer1 from ARM to DSP)
 *      timel
 *      timeh
 */
extern LOG_Obj ti_sdo_ce_bioslog_synch;

/*
 *  The 'track' LOG is used to track CPU load, EMIF counts,
 *  etc. 
 *
 *  Format for this LOG:
 *      <sequence #>
 *      EMIF counter 1
 *      EMIF counter 2
 *      CPU load
 *      0
 *      0
 *      timel
 *      timeh
 */
extern LOG_Obj ti_sdo_ce_bioslog_track;

/*
 *  ======== LogTracker_configEmifCounter ========
 *  configure the EMIF counter register
 */
extern Void LogTracker_configEmifCounter(Uint32 config, Uint32 master);

/*
 *  ======== LogTracker_createHook ========
 *  connect to TSK create hook
 */
extern Void LogTracker_createHook(TSK_Handle task);

/*
 *  ======== LogTracker_track ========
 *  add CPU load, EMIF, etc. info to the track log
 */
Void LogTracker_track(Void);

#ifdef __cplusplus
}
#endif

#endif
#endif
/*
 *  @(#) ti.sdo.ce.bioslog; 1, 0, 1,326; 12-2-2010 21:18:56; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

