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
 *  ======== bufres_util.c ========
 *  Utility functions for BUFRES.
 */

#include <xdc/std.h>

#include <ti/bios/include/std.h>

#include <ti/sdo/fc/utils/dbc.h>

#include <ti/sdo/fc/ires/iresman.h>


/*
 * As this file uses the BUFRES_PROTOCOL definitions, define this before
 * including "bufres.h"
 */
#define ti_sdo_fc_ires_NOPROTOCOLREV
#include <ti/sdo/fc/rman/examples/bufres_yield/bufres.h>

/*
 *  ======== BUFRES_init ========
 */
IRES_Status BUFRES_init(BUFRES_Params *args)
{
    IRES_Status status;

    /* Returns IRES_OK on success */
    status = BUFRES_MGRFXNS.init((IRESMAN_Params *)args);

    return (status);
}

/*
 *  ======== BUFRES_exit ========
 */
IRES_Status BUFRES_exit()
{
    IRES_Status status = IRES_OK;

    status = BUFRES_MGRFXNS.exit();
    return (status);
}

/*
 *  ======== BUFRES_get ========
 * This function allocates the buffer resource
 */
BUFRES_Handle BUFRES_get(IALG_Handle h, BUFRES_Args *args, Int scratchId,
        IRES_Status *pStatus)
{
    BUFRES_Handle buf;

    buf = (BUFRES_Handle)(BUFRES_MGRFXNS.getHandle(h, (IRES_ProtocolArgs *)args,
                                  scratchId, pStatus));
    return (buf);
}

/*
 *  ======== BUFRES_free ========
 */
IRES_Status BUFRES_free(IALG_Handle h, BUFRES_Handle res, BUFRES_Args *args,
        Int scratchId)
{
    IRES_Status status;

    status = BUFRES_MGRFXNS.freeHandle(h, (IRES_Handle)res,
            (IRES_ProtocolArgs *)args, scratchId);
    return (status);
}

/*
 *  ======== BUFRES_getStaticProps ========
 */
Void BUFRES_getStaticProps(BUFRES_Handle res, BUFRES_Props *props)
{
    (*(IRES_Handle)(res)).getStaticProperties((IRES_Handle)res,
            (IRES_Properties *)props);
}

/*
 *  @(#) ti.sdo.fc.rman.examples.bufres_yield; 1, 0, 0,177; 12-1-2010 17:25:39; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

