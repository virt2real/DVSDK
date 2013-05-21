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
 *  ======== fcpy_ti.h ========
 *  Interface header for the FCPY_TI module.
 */
#ifndef FCPY_TI_
#define FCPY_TI_

#ifndef IDMA3_USEFULLPACKAGEPATH
#define IDMA3_USEFULLPACKAGEPATH
#endif

#include <ti/xdais/ialg.h>
#include <ifcpy.h>
#include <ti/xdais/idma3.h>

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/

/*
 *  ======== FCPY_TI_Handle ========
 *  FCPY algorithm instance handle
 */
typedef struct FCPY_TI_Obj *FCPY_TI_Handle;

/*
 *  ======== FCPY_TI_exit ========
 *  Required module finalization function.
 */
extern Void FCPY_TI_exit(Void);

/*
 *  ======== FCPY_TI_init ========
 *  Required module initialization function.
 */
extern Void FCPY_TI_init(Void);

/*
 *  ======== FCPY_TI_IALG ========
 *  TI's implementation of FCPY's IALG interface
 */
extern IALG_Fxns FCPY_TI_IALG; 

/*
 *  ======== FCPY_TI_IFCPY ========
 *  TI's implementation of FCPY's IFCPY interface
 */
extern IFCPY_Fxns FCPY_TI_IFCPY; 

/*
 *  ======== FCPY_TI_IDMA3 ========
 *  TI's implementation of FCPY's IDMA2 interface
 */
extern IDMA3_Fxns FCPY_TI_IDMA3; 

#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /* FCPY_TI_ */


/*
 *  @(#) ti.sdo.fc.dman3.examples.fastcopy; 1, 0, 0,235; 12-1-2010 17:24:30; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

