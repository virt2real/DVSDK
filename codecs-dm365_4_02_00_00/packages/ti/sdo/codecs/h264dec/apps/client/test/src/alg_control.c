/*
 ******************************************************************************
 *  
 * XDAS Based Application
 *
 * This module shows XDAS Interface.
 * Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/ 
 * ALL RIGHTS RESERVED 
 ******************************************************************************
 */
/*
 *  ======== alg_control.c ========
 *  ALG_control implementation.  This is common to all implementations
 *  of the ALG module.
 */
#include <xdc/std.h>
#include <ti/sdo/fc/utils/api/alg.h>
#include <ti/xdais/ialg.h>

/*
 *  ======== ALG_control ========
 */
Int ALG_control(ALG_Handle alg, IALG_Cmd cmd, IALG_Status *statusPtr)
{
    if (alg && alg->fxns->algControl) {
        return (alg->fxns->algControl(alg, cmd, statusPtr));
    }

    return (IALG_EFAIL);
}
/*
 *  @(#) ti.sdo.fc.utils.api; 1, 0, 0,163; 7-16-2008 18:39:20; /db/atree/library/trees/fc-f19x/src/
 */

