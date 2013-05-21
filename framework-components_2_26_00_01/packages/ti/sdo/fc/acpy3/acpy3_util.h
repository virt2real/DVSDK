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
/**
 *  @file       ti/sdo/fc/acpy3/acpy3_util.h
 *
 *  @brief      DSP-side ACPY3 Library utility definitions.
 */

/**
 *  @defgroup   DSPACPY3_UTIL ACPY3 Utility Module
 *
 *              Utility data structures and functions for the ACPY3 library.
 */

#ifndef ACPY3_UTIL_
#define ACPY3_UTIL_

/** @ingroup    DSPACPY3_UTIL */
/*@{*/

#include <ti/xdais/ialg.h>
#include <ti/xdais/idma3.h>

#include "acpy3_instr.h"

/* Definitions are mostly for internal use, but are accessible if needed. */

/*
 *  Number of words in a PaRam Table entry
 *  (ie, sizeof(ACPY3_PaRamRegs) / sizeof(Uns).
 */
#define ACPY3_PARAMENTRYSIZE 8

#define _ACPY3_NUMQDMACHANNELS 8  /* number of QDMA channels */

#ifndef _ACPY3_DIRTY_BITS
#define _ACPY3_DIRTY_BITS  0 /* 1 to support dirty bits */
#endif

/*
 * Make sure the compiler setting for _ACPY3_DIRTY_BITS is the same for
 * previously compiled inline and non-inline
 */

#if _ACPY3_DIRTY_BITS
#define ACPY3_DIRTY_BITS_VERSION_MACRO asm (" .ref _ACPY3_dirtyBitsOn");
#define ACPY3_DIRTY_BITS_VERSION_NAME               ACPY3_dirtyBitsOn
#else
#define ACPY3_DIRTY_BITS_VERSION_MACRO asm (" .ref _ACPY3_dirtyBitsOff");
#define ACPY3_DIRTY_BITS_VERSION_NAME               ACPY3_dirtyBitsOff
#endif

/*
 * This is used to ensure that routines that were previously compiled
 * with inline ACPY3 functions are compatible with the current version
 * of ACPY3.
 * Therefore, whenever the ACPY3 code is modified such that it is no
 * longer compatible with the previous inline versions, the final
 * two digits of __ACPY3_inlineCompatibilityKey_NN should be incremented.
 * In that way, if in fact the code and version name does change, then
 * code with inline ACPY3 functions that was previously compiled will
 * show an unresolved reference when linking.  This will indicate
 * an incompatibility.
 * The value of _ACPY3_DIRTY_BITS must also be the same for routines
 * with inline functions previously compiled and for the current
 * version of ACPY3.  This protection is also implemented here.
 */
#define ACPY3_INLINE_COMPATIBILITY_KEY_NAME ACPY3_inlineCompatibilityKey_01
#define ACPY3_VERSION_MACRO    asm (" .ref _ACPY3_inlineCompatibilityKey_01"); \
                               ACPY3_DIRTY_BITS_VERSION_MACRO

/*
 *  Bits to set in PaRam Register Opts field.
 */
#define ACPY3_PARAMOPTS_AB_SYNC   (0x1 << 2)   /* AB_SYNC */
#define ACPY3_PARAMOPTS_TCC_INTEN (0x1 << 20)  /* TCC_INT_EN */
#define ACPY3_PARAMOPTS_STATIC    (0x1 << 3)   /* STATIC  */

/* TCC bits in Opts field of PaRam */
#define ACPY3_TCCMASK    0x3f000
#define ACPY3_TCCSHIFT   12       /* TCC starts at bit 12 of opts */
#define ACPY3_TCCBITS(tcc) (tcc << 12)

/* Dirty bit masks corresponding to PaRam Opts and link fields */
#define ACPY3_DIRTYOPTS 0x1
#define ACPY3_DIRTYLINK (1 << 5)

extern IDMA3_Handle  _ACPY3_qchLockTbl[_ACPY3_NUMQDMACHANNELS];

/*
 *  ======== ACPY3_MoreEnv ========
 *  Structure to represent part of the environment following the array of
 *  cache paRams.
 */
typedef struct ACPY3_MoreEnv {
    /* pointer to ACPY3_QDMA_IPR or ACPY3_QDMA_IPRH for final tcc */
    Uns   *iprRegister;
    /* mask into ACPY3_QDMA_IPR or ACPY3_QDMA_IPRH for final tcc */
    Uns    iprMask;
    Uns    icrlMask;    /* mask into ACPY3_QDMA_ICR for clearing TCCs */
    Uns    icrhMask;    /* mask into ACPY3_QDMA_ICRH for clearing TCCs */
    Void  *scratchEnv;
    Void  *persistEnv;
    unsigned short numTccs;
    unsigned short numPaRams;
    short  prevWaitIdOfFinal; /* original waitId of Final PaRam */
#ifdef  _ACPY3_INSTR_
    ACPY3_INSTR_Hooks * hooks;
    ACPY3_INSTR_ExtendedHooks * extendedHooks;
#endif /* _ACPY3_INSTR_ */

#ifdef _ACPY3_DIRTY_BITS
    /*
     * This field belongs at the end of the ACPY3_MoreEnv structure.
     * The size of the dirty bit table is variable, and is returned by the
     * ACPY3_getEnvMem structure.  Also, initialization of this structure moves
     * around some pointers that might cause issues if this is NOT the last
     * field of the structure.
     */
    unsigned char dirtyBitTable[1];
#endif

} ACPY3_MoreEnv;


/*
 *  ACPY3_PaRamRegs is the structure where we define the
 *  8-word PARAM Table Entry.
 */
typedef struct ACPY3_PaRamRegs {

    /*
     * Field 0: OPTIONS field
     */
    Uns                  opt;

    /*
     * Field 1: Source address (SRC)
     */
    Void *               src;

    /*
     * Field 2: BCNT | ACNT.
     *     ACNT: number of bytes in each 1D vector to be transferred
     *     BCNT: number of frames (i.e. 1D vectors) to be transferred.
     */
    unsigned short       acnt;
    unsigned short       bcnt;

    /*
     * Field 3: Destination address(DST)
     */
    Void *               dst;

    /*
     * Field 4: Src/Dst Element Indexes
     *     DSTBIDX: gap btw 1st bytes of consecutive dest 1-d vects
     *     SRCBIDX: gap btw 1st bytes of consecutive src  1-d vects
     */
    unsigned short       srcElementIndex;
    unsigned short       dstElementIndex;

    /*
     * Field 5: BCNTRLD (bcnt reload value) | LINK.
     */
    unsigned short       link;
    unsigned short       bCntrld;

    /*
     * Field 6: Src/Dst Frame Indexes
     *     DSTCIDX: gap in bytes between consecutive dest frames
     *     SRCCIDX: gap in bytes between consecutive src  frames
     */
    unsigned short       srcFrameIndex;
    unsigned short       dstFrameIndex;

    /*
     * Field 7: Number of blocks
     *     CCNT:    number of 2D frames  in 3D transfers
     */
    unsigned short       ccnt;
    unsigned short       rsvd; /* reserved 16bits */

} ACPY3_PaRamRegs;


/*
 *  ======== ACPY3_getPaRamCache ========
 *  Mostly for internal use -- but could be helpful utility API.
 *  Returns the address of the cached PaRAM Regs stored within the
 *  logical channel handle's 'env' associated with a given transferNo
 *  NOTE: The PARAM blocks are assigned in DESCENDING order within the
 *  env PARAM CACHE area.
 */
static __inline volatile
ACPY3_PaRamRegs * ACPY3_getPaRamCache(IDMA3_Handle handle,
        short transferNo)
{
    return ((ACPY3_PaRamRegs *)handle->env - (transferNo + 1));

}


/*
 *  ======== ACPY3_getPaRamPhysicalAddress ========
 *  Returns the address of the Physical PaRAM Regs associated with the
 *  logical channel handle's transfer
 */
static __inline volatile
Uns *ACPY3_getPaRamPhysicalAddress(IDMA3_Handle handle, short transferNo)
{
    /*
     * PARAM addresses are assigned to transferNo's in decending order
     */
#if ACPY3_PARAMENTRYSIZE == 8
    return ((Uns *)(handle->paRamAddr - (transferNo << 3)));
#else
    return ((Uns *)(handle->paRamAddr - (transferNo * ACPY3_PARAMENTRYSIZE)));
#endif
}
/*
 *  ======== ACPY3_getPaRamLinkIndex ============
 *  Returns the PARAM ID of the Physical PaRAM Regs associated with the
 *  logical channel handle's transfer for configuring the LINK field in linked
 *  transfers.
 */
static __inline
Uns ACPY3_getPaRamLinkIndex(IDMA3_Handle handle, short transferNo)
{
    return (((Uns)(handle->paRamAddr -
#if ACPY3_PARAMENTRYSIZE == 8
                    (transferNo << 3))) & 0xFFFF);
#else
                    (transferNo * ACPY3_PARAMENTRYSIZE))) & 0xFFFF);
#endif
}


/*
 *  ======== ACPY3_initQdmaSettings ========
 */
extern Void ACPY3_initQdmaSettings(Void);


/*@}*/

#endif  /* ACPY3_UTIL_ */

/*
 *  @(#) ti.sdo.fc.acpy3; 1, 0, 4,301; 12-1-2010 17:24:25; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

