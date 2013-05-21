/* --COPYRIGHT--,BSD
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
 * --/COPYRIGHT--*/

#include <string.h>
#include <stdlib.h>

#include <xdc/std.h>

#include <ti/sdo/ce/osal/Global.h>
#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/ce/osal/Sem.h>
#include <ti/sdo/utils/trace/gt.h>

#include <ti/sdo/dmai/Dmai.h>

#define MODULE_NAME     "Dmai"

/*
 * Mask to enable GT tracing 
 */
GT_Mask ti_sdo_dmai_GTMask = {NULL, NULL};

extern Void GT_config_setOutTrace(FILE *newOutTrace);

static Bool logLevelSetByEnv = FALSE;

/******************************************************************************
 * Dmai_setLogLevel
 ******************************************************************************/
Int Dmai_setLogLevel(Dmai_LogLevel logLevel)
{
    /* Set the log level if environment variable DMAI_DEBUG is not set */
    if (logLevelSetByEnv == FALSE) {
        switch (logLevel) {
            case 0: 
                GT_set("ti.sdo.dmai=");        
                break;
            case 1:
                GT_set("ti.sdo.dmai=67");
                GT_config_setOutTrace(stdout);
                break;
            case 2:
                GT_set("ti.sdo.dmai=01234567");
                GT_config_setOutTrace(stdout);
                break;
            default:
                /* Invalid level. */
                return Dmai_EINVAL;
        }
        Dmai_dbg1("Log level set to %d.\n", logLevel);
    }
    else {
        Dmai_dbg0("Using log level set by DMAI_DEBUG.\n");
    }
    
    return Dmai_EOK;
}

/******************************************************************************
 * Dmai_init
 ******************************************************************************/
Void Dmai_init()
{
    if (ti_sdo_dmai_GTMask.modName == NULL) {
        GT_init();

        Memory_init();
        Sem_init();

        GT_create(&ti_sdo_dmai_GTMask, Dmai_gtname);
   
        if (getenv("DMAI_DEBUG") != NULL) { 
            logLevelSetByEnv = TRUE;
            switch (getenv("DMAI_DEBUG")[0]) {
                case '0': 
                    GT_set("ti.sdo.dmai=");  
                    break;
                case '1':
                    GT_set("ti.sdo.dmai=67");
                    GT_config_setOutTrace(stdout); 
                    break;
                case '2':
                    GT_set("ti.sdo.dmai=01234567");
                    GT_config_setOutTrace(stdout); 
                    break;
                default:
                    /* Invalid parameter. Do nothing. */   
                    break;
            }
            Dmai_dbg1("Dmai log level set to '%c'. Note that calling "
                      "CERuntime_init after this point may cause unexpected "
                      "change to DMAI tracing behavior.\n",
                      getenv("DMAI_DEBUG")[0]);
        }
    }
    return;
}
