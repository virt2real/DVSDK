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
 *  ======== rtcfg.c ========
 *  Common variables and functions used by non-RTSC config examples.
 */

/*
 */

#include <xdc/std.h>

#include <ti/xdais/ialg.h>

#include <ti/sdo/ce/Engine.h>

/*
 *  Extern declarations of stub funcions that will be linked into the
 *  app.
 */
extern IALG_Fxns VIDDEC_STUBS;
extern IALG_Fxns VIDENC_STUBS;
extern IALG_Fxns VIDDEC1_STUBS;
extern IALG_Fxns VIDENC1_STUBS;
extern IALG_Fxns IMGDEC_STUBS;
extern IALG_Fxns IMGENC_STUBS;
extern IALG_Fxns IMGDEC1_STUBS;
extern IALG_Fxns IMGENC1_STUBS;
extern IALG_Fxns SPHENC_STUBS;
extern IALG_Fxns SPHDEC_STUBS;
extern IALG_Fxns SPHENC1_STUBS;
extern IALG_Fxns SPHDEC1_STUBS;
extern IALG_Fxns AUDDEC_STUBS;
extern IALG_Fxns AUDENC_STUBS;
extern IALG_Fxns AUDDEC1_STUBS;
extern IALG_Fxns AUDENC1_STUBS;
extern IALG_Fxns SCALE_STUBS;
extern IALG_Fxns VIDDEC2_STUBS;
extern IALG_Fxns VIDTRANSCODE_STUBS;
extern IALG_Fxns VIDANALYTICS_STUBS;
extern IALG_Fxns VIDDEC2FRONT_STUBS;
extern IALG_Fxns VIDDEC2BACK_STUBS;
extern IALG_Fxns UNIVERSAL_STUBS;

/*
 * ======== ti.sdo.ce.alg.Settings Configuration ========
 */

/*
 *  The following variable is the base value of a group of IDs for the up to 20
 *  multi-process semaphores created by the alg module. In the case of Linux,
 *  the 20 consecutive interger values starting with this base will be used
 *  for internal Linux IPC objects. In the case of WinCE, these values will
 *  be converted to strings for creating named semaphores.
 *  This value should only be changed (in the remote chance) that it conflicts
 *  with another Linux IPC object in the system (Linux), or another named
 *  semaphore (WinCE).
 */
UInt32 ti_sdo_ce_alg_ipcKey = 0x4f474c41;

/*
 *  ====================================================
 *  None of the code below this line should be modified!
 *  ====================================================
 */

#include <ti/sdo/ce/osal/SemMP.h>
#include <ti/xdais/ialg.h>

unsigned int ti_sdo_ce_alg_ALG_maxGroups = 20;

SemMP_Handle _ALG_sems[20];

IALG_Handle _Algorithm_lockOwner[20] = {
     NULL, NULL, NULL, NULL, NULL,
     NULL, NULL, NULL, NULL, NULL,
     NULL, NULL, NULL, NULL, NULL,
     NULL, NULL, NULL, NULL, NULL,
};

int _ALG_groupUsed[20] = {
     0, 0, 0, 0, 0,
     0, 0, 0, 0, 0,
     0, 0, 0, 0, 0,
     0, 0, 0, 0, 0,
};

int _ALG_groupRefCount[20] = {
     0, 0, 0, 0, 0,
     0, 0, 0, 0, 0,
     0, 0, 0, 0, 0,
     0, 0, 0, 0, 0,
};

/*
 * ======== ti.sdo.ce.CERuntime ========
 */

#include <ti/sdo/ce/osal/Global.h>
#include <ti/sdo/ce/ipc/Comm.h>
#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/ce/osal/Queue.h>
#include <ti/sdo/ce/osal/Sem.h>
#include <ti/sdo/ce/osal/SemMP.h>
#include <ti/sdo/ce/osal/Thread.h>
#include <ti/sdo/ce/ipc/Processor.h>
#include <ti/sdo/ce/alg/Algorithm.h>
#include <ti/sdo/ce/osal/Lock.h>
#include <ti/sdo/ce/osal/LockMP.h>
#include <ti/sdo/ce/Server.h>
#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/rms.h>
#include <ti/sdo/ce/utils/xdm/XdmUtils.h>

#include <ti/sdo/utils/trace/gt.h>

Void RtCfg_init();


/*
 *  ======== CERuntime_init ========
 */
Void CERuntime_init(Void)
{
    GT_init();

    /* if CE_DEBUG is set, turn on tracing and DSP auto trace collection */
    if (Global_getenv("CE_DEBUG") != NULL) {
        extern Bool   Engine_alwaysCollectDspTrace;
        extern String Engine_ceDebugDspTraceMask;

        Engine_alwaysCollectDspTrace = TRUE;

        if (Global_getenv("CE_DEBUG")[0] == '1') {
            GT_set("*+67,CE-3,GT_time=0,GT_prefix=1235");
            Engine_ceDebugDspTraceMask = "*+67,GT_prefix=1235,GT_time=3";
        }
        else if (Global_getenv("CE_DEBUG")[0] == '2') {
            GT_set(
                "*+01234567,CE-3,ti.sdo.ce.osal.SemMP=67,OG=467,OM=4567,OC=67,GT_time=0,GT_prefix=1235");
            Engine_ceDebugDspTraceMask =
                "*+01234567,CR=67,ti.sdo.fc.dman3-2,ti.sdo.fc.dskt2-2,GT_prefix=1235,GT_time=3";
        } else {
            GT_set("*+01234567,CE-3,GT_time=0,GT_prefix=12345");
            Engine_ceDebugDspTraceMask = "*+01234567,GT_prefix=12345,GT_time=3";
        }
    }

    if (Global_getenv("CE_CHECK") != NULL) {
        extern Bool VISA_checked;

        /*
         * Currently just change _this_ processor's value... perhaps we should
         * enable remote processors as well?
         */
        if (Global_getenv("CE_CHECK")[0] == '1') {
            VISA_checked = TRUE;
            /* turn on all GT_7CLASS trace (errors) */
            GT_set("*+7");
        } else if (Global_getenv("CE_CHECK")[0] == '0') {
            VISA_checked = FALSE;
        } else {
            /* leave it whatever it was... maybe we should drop a warning? */
        }
    }

    /* allow user to over-ride via CE_TRACE. */
    GT_set(Global_getenv("CE_TRACE"));
    Global_init();

    Sem_init();
    SemMP_init();


    Memory_init();
    Queue_init();
    Comm_init();
    Thread_init();
    Processor_init();
    LockMP_init();  /* Must be called before DMAN3_init() */
    Algorithm_init();
    XdmUtils_init();
    Lock_init();

    Engine_init();
    Server_init();

    RtCfg_init();
}

/*
 *  ======== CERuntime_exit ========
 */
Void CERuntime_exit(Void)
{
    Global_exit();
}

/* for backward compatibility with xdc-m based tools */
Void ti_sdo_ce_CERuntime_init__F(Void) {
    CERuntime_init();
}

Void RtCfg_init()
{
    Engine_addStubFxns("AUDDEC_STUBS",   &AUDDEC_STUBS);
    Engine_addStubFxns("AUDENC_STUBS",   &AUDENC_STUBS);
    Engine_addStubFxns("AUDDEC1_STUBS",  &AUDDEC1_STUBS);
    Engine_addStubFxns("AUDENC1_STUBS",  &AUDENC1_STUBS);
    Engine_addStubFxns("IMGDEC_STUBS",   &IMGDEC_STUBS);
    Engine_addStubFxns("IMGENC_STUBS",   &IMGENC_STUBS);
    Engine_addStubFxns("IMGDEC1_STUBS",  &IMGDEC1_STUBS);
    Engine_addStubFxns("IMGENC1_STUBS",  &IMGENC1_STUBS);
    Engine_addStubFxns("SPHDEC_STUBS",   &SPHDEC_STUBS);
    Engine_addStubFxns("SPHENC_STUBS",   &SPHENC_STUBS);
    Engine_addStubFxns("SPHDEC1_STUBS",  &SPHDEC1_STUBS);
    Engine_addStubFxns("SPHENC1_STUBS",  &SPHENC1_STUBS);
    Engine_addStubFxns("VIDDEC_STUBS",   &VIDDEC_STUBS);
    Engine_addStubFxns("VIDENC_STUBS",   &VIDENC_STUBS);
    Engine_addStubFxns("VIDDEC1_STUBS",  &VIDDEC1_STUBS);
    Engine_addStubFxns("VIDENC1_STUBS",  &VIDENC1_STUBS);
    Engine_addStubFxns("VIDDEC2_STUBS",  &VIDDEC2_STUBS);
    Engine_addStubFxns("VIDDEC2FRONT_STUBS", &VIDDEC2FRONT_STUBS);
    Engine_addStubFxns("VIDDEC2BACK_STUBS",  &VIDDEC2BACK_STUBS);
    Engine_addStubFxns("VIDTRANSCODE_STUBS", &VIDTRANSCODE_STUBS);
    Engine_addStubFxns("VIDANALYTICS_STUBS", &VIDANALYTICS_STUBS);
    Engine_addStubFxns("UNIVERSAL_STUBS",    &UNIVERSAL_STUBS);
}

/*
 *  ======== Global Configuration ========
 */
#include <ti/sdo/ce/osal/Log.h>

Log_Handle ti_sdo_ce_dvtLog = NULL;

Bool ti_sdo_ce_Engine_noCommName = FALSE;

/* List of all packages and their versions and paths, for diagnostics */
String Global_buildInfo[] = {
    NULL
};
/*
 *  @(#) ti.sdo.ce.utils.rtcfg; 1, 0, 1,28; 12-2-2010 21:28:00; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

