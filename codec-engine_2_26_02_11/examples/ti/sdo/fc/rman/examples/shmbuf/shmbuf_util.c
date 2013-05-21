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
 *  ======== shmbuf_util.c ========
 *  Utility functions for SHMBUF.
 */

#include <xdc/std.h>
#include <ti/sdo/fc/ires/iresman.h>
#define ti_sdo_fc_ires_NOPROTOCOLREV
#include <ti/sdo/fc/ires/shmbuf/shmbuf.h>


/*
 *  ======== SHMBUF_init ========
 */
IRES_Status SHMBUF_init(SHMBUF_Params *args)
{
    IRES_Status status;

    /* Returns IRES_OK on success */
    status = SHMBUF_MGRFXNS.init((IRESMAN_Params *)args);

    return (status);
}

/*
 *  ======== SHMBUF_exit ========
 */
IRES_Status SHMBUF_exit()
{
    IRES_Status status = IRES_OK;

    status = SHMBUF_MGRFXNS.exit();
    return (status);
}

/*
 *  ======== SHMBUF_get ========
 * This function allocates the buffer resource
 */
SHMBUF_Handle SHMBUF_get(IALG_Handle alg, SHMBUF_Args *args, Int scratchId,
        IRES_Status *pStatus)
{
    SHMBUF_Handle buf;

    buf = (SHMBUF_Handle)(SHMBUF_MGRFXNS.getHandle((IALG_Handle)alg, 
            (IRES_ProtocolArgs *)args, scratchId, pStatus));
    return (buf);
}

/*
 *  ======== SHMBUF_free ========
 */
IRES_Status SHMBUF_free(IALG_Handle alg, SHMBUF_Handle res, SHMBUF_Args *args,
        Int scratchId)
{
    IRES_Status status;

    status = SHMBUF_MGRFXNS.freeHandle((IALG_Handle)alg, (IRES_Handle)res,
            (IRES_ProtocolArgs *)args, scratchId);
    return (status);
}

/*
 *  ======== SHMBUF_getStaticProps ========
 */
Void SHMBUF_getStaticProps(SHMBUF_Handle res, SHMBUF_Props *props)
{
    (*(IRES_Handle)(res)).getStaticProperties((IRES_Handle)res,
            (IRES_Properties *)props);
}

/*
 *  Stub out LockMP functions so tests will build.
 */
typedef struct LockMP_Obj *LockMP_Handle;

Void LockMP_acquire(LockMP_Handle lock)
{
}

LockMP_Handle LockMP_create(Int key)
{
    return ((LockMP_Handle)-1);
}

Void LockMP_delete(LockMP_Handle lock)
{
}

Int LockMP_getRefCount(LockMP_Handle lock)
{
    return (1);
}

Void LockMP_release(LockMP_Handle lock)
{
}


/*
 *  @(#) ti.sdo.fc.rman.examples.shmbuf; 1, 0, 0,119; 12-1-2010 17:25:54; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

