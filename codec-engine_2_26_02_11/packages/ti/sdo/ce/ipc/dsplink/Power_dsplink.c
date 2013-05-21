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
 *  ======== Power_dsplink_linux.c ========
 */
#include <xdc/std.h>

#include <ti/sdo/utils/trace/gt.h>
#include <ti/bios/power/lpm.h>

#include <ti/sdo/ce/osal/Global.h>
#include <ti/sdo/ce/ipc/Power.h>

/*
 *  ======== Power_Obj ========
 */
typedef struct Power_Obj {
    Int dummy;
} Power_Obj;

/* REMINDER: if you add an initialized static var, reinitialize it at cleanup */
static Bool curInit = FALSE;
static GT_Mask curTrace;

static Void cleanup(Void);

/*
 *  ======== Power_init ========
 */
Void Power_init()
{
    if (curInit != TRUE) {
        curInit = TRUE;
        GT_create(&curTrace, Power_GTNAME);

        /* initialize the LPM module */
        LPM_init();

        Global_atexit((Fxn)cleanup);
    }
}


/*
 *  ======== Power_on ========
 */
Int Power_on(Power_Handle *handle)
{
    LPM_Status      lpmStat = LPM_SOK;
    LPM_Handle      hLPM;
    Int             retVal = Power_EFAIL;

    GT_1trace(curTrace, GT_ENTER, "Power_on> Enter(handle=0x%x)\n", handle);

    if (handle == NULL) {
        GT_0trace(curTrace, GT_7CLASS, "Power_on> "
            "Error: handle ptr is NULL\n");
        goto Power_on_return;
    }

    GT_0trace(curTrace, GT_2CLASS, "Power_on> "
        "Opening Local Power Manager for the DSP on /dev/lpm0...\n");

    lpmStat = LPM_open("/dev/lpm0", &hLPM);
    if (lpmStat != LPM_SOK) {
        GT_0trace(curTrace, GT_7CLASS, "Power_on> "
            "Opening Local Power Manager for the DSP on /dev/lpm0 FAILED\n");
        goto Power_on_return;
    }

    GT_0trace(curTrace, GT_2CLASS, "Power_on> Turning on DSP power...\n");

    lpmStat = LPM_on(hLPM);
    if (lpmStat != LPM_SOK) {
        GT_0trace(curTrace, GT_7CLASS, "Power_on> "
            "Turning on DSP power FAILED\n");
        goto Power_on_return;
    }

    *handle = (Power_Handle)hLPM;
    retVal   = Power_EOK;

Power_on_return:

    GT_1trace(curTrace, GT_2CLASS, "Power_on> return (%d)\n", retVal);

    return retVal;
}


/*
 *  ======== Power_off ========
 */
Int Power_off( Power_Handle handle )
{
    LPM_Handle  hLPM     = (LPM_Handle)handle;
    LPM_Status  lpmStat  = !LPM_SOK;
    Int         retVal   = Power_EOK;

    GT_1trace(curTrace, GT_ENTER, "Power_off> Enter (handle=0x%x)\n", handle);

    if (handle == NULL) {
        goto Power_off_return;
    }

    GT_0trace(curTrace, GT_2CLASS, "Power_off> Turning off DSP power...\n");

    lpmStat = LPM_off(hLPM);
    if (lpmStat != LPM_SOK) {
        GT_1trace(curTrace, GT_6CLASS, "Power_off> "
            "Turning off DSP power FAILED, status=0x%x\n", lpmStat);
    }

    GT_0trace(curTrace, GT_2CLASS, "Power_off> "
        "Closing Local Power Manager object...\n");
    lpmStat = LPM_close(hLPM);

    if (lpmStat != LPM_SOK) {
        GT_1trace(curTrace, GT_6CLASS, "Power_off> "
            "Closing LPM FAILED, status=0x%x\n", lpmStat);
    }

    retVal = (lpmStat == LPM_SOK) ? Power_EOK : Power_EFAIL;

Power_off_return:

    GT_1trace(curTrace, GT_ENTER, "Power_off> return (%d)\n", retVal);

    return (retVal);
}


/*
 *  ======== Power_connect ========
 */
Int Power_connect(Power_Handle handle)
{
#if defined(POWER_NOT_SUPPORTED)
    Int         retVal   = Power_EOK;
#else
    LPM_Handle  hLPM     = (LPM_Handle)handle;
    LPM_Status  lpmStat  = !LPM_SOK;
    Int         retVal   = Power_EOK;

    GT_1trace(curTrace, GT_ENTER, "Power_connect> "
        "Enter (handle=0x%x)\n", handle );

    GT_0trace(curTrace, GT_2CLASS, "Power_connect> "
        "Calling LPM_connect to connect to the DSP power handler...\n");

    lpmStat = LPM_connect(hLPM);

    if (lpmStat != LPM_SOK) {
        GT_1trace(curTrace, GT_6CLASS, "Power_connect> "
            "LPM_connect FAILED, status=0x%x\n", lpmStat);
        retVal = Power_EFAIL;
    }

    GT_1trace(curTrace, GT_ENTER, "Power_connect> return (%d)\n", retVal);
#endif

    return (retVal);
}

/*
 *  ======== Power_disconnect ========
 */
Int Power_disconnect(Power_Handle handle)
{
#if defined(POWER_NOT_SUPPORTED)
    Int         retVal   = Power_EOK;
#else
    LPM_Handle  hLPM     = (LPM_Handle)handle;
    LPM_Status  lpmStat  = !LPM_SOK;
    Int         retVal   = Power_EOK;

    GT_1trace(curTrace, GT_ENTER, "Power_disconnect> "
        "Enter (handle=0x%x)\n", handle );

    GT_0trace(curTrace, GT_2CLASS, "Power_disconnect> "
        "Calling LPM_disconnect to disconnect from the DSP power handler...\n");

    lpmStat = LPM_disconnect(hLPM);

    if (lpmStat != LPM_SOK) {
        GT_1trace(curTrace, GT_6CLASS, "Power_disconnect> "
            "LPM_disconnect FAILED, status=0x%x\n", lpmStat);
        retVal = Power_EFAIL;
    }

    GT_1trace(curTrace, GT_ENTER, "Power_disconnect> return (%d)\n", retVal);
#endif

    return retVal;
}

/*
 *  ======== cleanup ========
 */
static Void cleanup()
{
    if (curInit != FALSE) {
        curInit = FALSE;

        LPM_exit();
    }
}
/*
 *  @(#) ti.sdo.ce.ipc.dsplink; 2, 0, 1,182; 12-2-2010 21:24:21; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

