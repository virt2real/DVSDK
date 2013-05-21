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
 *  ======== shmbuf_util.h ========
 *  Utility functions for SHMBUF resource manager functions.
 */

#ifndef SHMBUF_UTIL_H_
#define SHMBUF_UTIL_H_

#include <ti/sdo/fc/ires/iresman.h>
#define ti_sdo_fc_ires_NOPROTOCOLREV

#include <ti/sdo/fc/ires/shmbuf/shmbuf.h>


extern IRES_Status SHMBUF_init(SHMBUF_Params *args);
extern IRES_Status SHMBUF_exit();
extern SHMBUF_Handle SHMBUF_get(IALG_Handle alg, SHMBUF_Args *args, 
        Int scratchId, IRES_Status *pStatus);
extern IRES_Status SHMBUF_free(IALG_Handle alg, SHMBUF_Handle res, 
        SHMBUF_Args *args, Int scratchId);
extern Void SHMBUF_getStaticProps(SHMBUF_Handle res, SHMBUF_Props *props);


#endif /* SHMBUF_UTIL_H_ */

/*
 *  @(#) ti.sdo.fc.rman.examples.shmbuf; 1, 0, 0,119; 12-1-2010 17:25:54; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

