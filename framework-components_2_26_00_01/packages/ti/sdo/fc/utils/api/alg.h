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
 *  ======== alg.h ========
 */
#ifndef ALG_
#define ALG_

#include <ti/xdais/ialg.h>

#ifdef __cplusplus
extern "C" {
#endif
/*
 *  ======== ALG_Handle ========
 *  This handle type is used to reference all ALG instance objects
 */
typedef IALG_Handle ALG_Handle;

/*
 *  ======== ALG_activate ========
 *  Restore all shared persistant data associated with algorithm object
 */
extern Void ALG_activate(ALG_Handle alg);

/*
 *  ======== ALG_control ========
 *  Control algorithm object
 */
extern Int ALG_control(ALG_Handle alg, IALG_Cmd cmd, IALG_Status *sptr);

/*
 *  ======== ALG_create ========
 *  Create algorithm object and initialize its memory
 */
extern ALG_Handle ALG_create(IALG_Fxns *fxns, IALG_Handle p, IALG_Params *prms);

/*
 *  ======== ALG_deactivate ========
 *  Save all shared persistant data associated with algorithm object
 *  to some non-shared persistant memory.
 */
extern Void ALG_deactivate(ALG_Handle alg);

/*
 *  ======== ALG_delete ========
 *  Delete algorithm object and release its memory
 */
extern Void ALG_delete(ALG_Handle alg);

/*
 *  ======== ALG_exit ========
 *  Module finalization
 */
extern Void ALG_exit(Void);

/*
 *  ======== ALG_init ========
 *  Module initialization
 */
extern Void ALG_init(Void);

#ifdef __cplusplus
}
#endif

#endif  /* ALG_ */
/*
 *  @(#) ti.sdo.fc.utils.api; 1, 0, 0,264; 12-1-2010 17:26:05; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

