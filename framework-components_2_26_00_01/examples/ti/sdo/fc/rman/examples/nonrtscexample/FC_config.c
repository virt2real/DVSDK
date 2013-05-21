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
 *  ======== FC_config.c ========
 *  Configuration for other modules of FC (besides RMAN) being used.
 */

#include <xdc/std.h>
#include <ti/bios/include/std.h>
#include <ti/bios/include/tsk.h>
#include <ti/bios/include/hwi.h>
#include <ti/bios/include/sem.h>


#include <ti/sdo/fc/rman/rman.h>
#include <ti/sdo/fc/ires/hdvicp/iresman_hdvicp.h>
#include <ti/sdo/fc/ires/hdvicp/ires_hdvicp.h>

#include <ti/sdo/fc/dskt2/dskt2.h>

#include <ti/sdo/utils/trace/gt.h>

extern Ptr myMalloc(Int size);
extern Void printfCaller(String fmt, ...);

/*
 * XDT created scratch size array for DSKT2
 *
 */
far Int SCRATCH_ARRAY = {0};
DSKT2_CacheWBInvFxn DSKT2_cacheWBInvFxn = NULL;

GT_Config _ti_sdo_utils_trace_GT_params = {
    printfCaller,
    NULL,
    NULL,
    NULL,
    myMalloc,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};
GT_Config *GT = &_ti_sdo_utils_trace_GT_params;

static IRESMAN_HdVicpParams configParams = { sizeof(IRESMAN_Params), 
        DSKT2_allocPersistent, DSKT2_freePersistent };

static IRESMAN_Fxns * _resmans[] = {&IRESMAN_HDVICP};  

static IRESMAN_Params * _resmanArgs[] = 
        {(IRESMAN_Params *)&configParams};

/* 
 * For RMAN auto-registration 
 */
IRES_Status RMAN_autoRegister()
{
    /* Statically register entries with RMAN */
    RMAN_numRegistryEntries  = 1;
    RMAN_registryEntries = _resmans; 
    RMAN_registryResmanArgs = _resmanArgs;

    return (IRES_OK);
}
/*
 *  @(#) ti.sdo.fc.rman.examples.nonrtscexample; 1, 0, 0,30; 12-1-2010 17:25:48; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

