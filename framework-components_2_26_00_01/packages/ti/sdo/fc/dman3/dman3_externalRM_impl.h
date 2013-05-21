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
 *  ======== dman3_externalRM_impl.h ========
 *
 *  DMAN3 internal implementation declarations.
 */

#ifndef _DMAN3_EXTERNALRM_IMPL
#define _DMAN3_EXTERNALRM_IMPL

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/

#include <std.h>
#include <ti/sdo/fc/dman3/rmm.h>

#include <ti/sdo/edma3/rm/edma3_rm.h>

#include <ti/sdo/utils/trace/gt.h>
extern GT_Mask ti_sdo_fc_dman3_GTMask;

/* Maximum number of TCCs available */
#define _DMAN3_MAXNUMTCCS    64

/* Maximum number of IDMA3 Channels that can be requested */ 
#define _DMAN3_MAXCHANS      32 

/*
 *  QCHMAP: Queue to channel map register which specifies which parameter
 *  entry in bits 13-5 and the trigger word (which is word 7 in ACPY3
 *  implementation), in bits 4-2.
 */
// TODO: These 2 defines will go away with EDMA3 regs structures
#define QCHMAPOFFSET 0x200
#define PARAMOFFSET 0x4000
#define PARAMENTRYSIZE 8  /* Number of words in PaRam entry */

/* Byte offsets of QDMA registers */
#define QDMAQNUMOFFSET  0x0260
#define QUETCMAPOFFSET  0x0280
#define QUEPRIOFFSET    0x0284
#define QRAE0OFFSET     0x0380
#define QEESROFFSET     0x108C

/* Sizes of EDMA3 register and PaRam regions to map */
#define EDMA3REGSIZE 0x2000
#define PARAMREGSIZE 0x800

/*
 *  Number of words and MAUs in one PaRam entry. PARAMSIZEMAUS should be
 *  sizeof(ACPY3_PaRamRegs), but use #define since we can't include ACPY3
 *  header file here.
 */
#define PARAMSIZE 8
#define PARAMSIZEMAUS (PARAMSIZE * sizeof(Int))

/*
 * Convenience macros
 */
#define _DMAN3_qdmaCounter(i) _DMAN3_qdmaCounter[((i) < 0) ? \
        DMAN3_MAXGROUPS : (i)]
#define _DMAN3_numQdmaGroup(i) ti_sdo_fc_dman3_DMAN3_numQdmaGroup[((i) < 0) ? \
        DMAN3_MAXGROUPS : (i)]
#define _DMAN3_qdma(i) _DMAN3_qdmaBase[((i) < 0) ? DMAN3_MAXGROUPS : (i)]

/*
 *  ======== DMAN3_ContextObj ========
 *  Context object is per IDMA3_Handle. Contains internal information outside of
 *  IDMA3_Handle that describes the resources held by the handle   
 */
typedef struct DMAN3_ContextObj {
    Int           groupId;      /* Group ID for TCCs, PaRams (may not be reqd)*/
    Int           scratchId;    /* Group ID for scratch Env */
    IALG_Handle   algHandle;  
    EDMA3_RM_Handle rmHandle;
    Int           qdmaBase; 
    Int           numQdmas; 
    Int           nextQdmaChannel; 
} DMAN3_ContextObj;

typedef struct DMAN3_ContextObj *DMAN3_Context;

typedef struct DMAN3_QdmaObj {
    Uns            index;
    Bool           available;  
    Uns            scratch;
} DMAN3_QdmaObj;

/*
 *  ======== _DMAN_initParams ========
 *  Initialize DMAN3_PARAMS with static configuration parameters
 */
extern Void _DMAN3_initParams(Void);
    
/*
 *  ======== _DMAN_initImpl   ========
 *  Implementation of DMAN3_init function which expects DMAN3_PARAMS
 *  to be initialized independent of RTSC or C configuration
 */
extern Void _DMAN3_initImpl(Void);

extern far Int           _DMAN3_heapInt;
extern far Int           _DMAN3_heapExt;
extern far Int           _DMAN3_heapIdma3;
extern far Uns           _DMAN3_qdmaIndex;   

extern far DMAN3_ScratchAllocFxn _DMAN3_allocScratch;
extern far DMAN3_ScratchFreeFxn _DMAN3_freeScratch;
extern far DMAN3_QdmaObj * DMAN3_QDMA;
extern UInt32 _DMAN3_qdmaBase[DMAN3_MAXGROUPS + 1]; 
extern UInt32 _DMAN3_qdmaCounter[DMAN3_MAXGROUPS + 1]; 

extern __FAR__ Bool ti_sdo_fc_dman3_DMAN3_useCustomDma;



#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /*_DMAN3_*/
/*
 *  @(#) ti.sdo.fc.dman3; 1, 0, 4,300; 12-1-2010 17:24:25; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

