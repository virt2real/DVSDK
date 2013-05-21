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
 *  ======== LogTracker.c =======
 */

#include <xdc/std.h>

#ifdef xdc_target__isaCompatible_64P

#include <ti/bios/include/std.h>
#include <ti/bios/include/log.h>
#include <ti/bios/include/tsk.h>

#include <ti/bios/utils/Load.h>

#include <ti/sdo/ce/bioslog/LogTracker.h>

#include <string.h>

#define EMIFCNT1        (*((Uint32 *)0x20000040))
#define EMIFCNT2        (*((Uint32 *)0x20000044))
#define EMIFCONFIG      (*((Uint32 *)0x20000048))
#define EMIFMASTER      (*((Uint32 *)0x2000004C))


/*
 *  ======== LogTracker_createHook ========
 */
Void LogTracker_createHook(TSK_Handle task)
{
    Uint32 name[4];     /* need to copy to Uint32 to make sure aligned */

    memset(name, 0, sizeof(name));

    if (task->name != NULL) {
        strncpy((char *)name, task->name, sizeof(name));
    }

    LOG_event5(&ti_sdo_ce_bioslog_create,
        (Arg)task, (Arg)name[0], (Arg)name[1], (Arg)name[2], (Arg)name[3]);
}

/*
 *  ======== LogTracker_track ========
 */
Void LogTracker_track()
{
    LOG_event5(&ti_sdo_ce_bioslog_track,
        (Arg)EMIFCNT1, (Arg)EMIFCNT2, Load_getcpuload(), 0, 0);
}

/*
 *  ======== LogTracker_configEmifCounter ========
 */
Void LogTracker_configEmifCounter(Uint32 config, Uint32 master)
{
    EMIFCONFIG = config;
    EMIFMASTER = master;
}

#endif
/*
 *  @(#) ti.sdo.ce.bioslog; 1, 0, 1,326; 12-2-2010 21:18:56; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

