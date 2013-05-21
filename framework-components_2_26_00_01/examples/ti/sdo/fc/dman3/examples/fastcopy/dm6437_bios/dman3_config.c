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
 *  ======== dman3_config.c ========
 *  Configuration for DMAN3 Parameters 
 */
#include <std.h>
#include <ti/sdo/fc/dman3/dman3.h>

static Uns CFG_QDMA_CHANNELS[4] = { 0, 1, 2, 3};
#define DMAN3MAXQDMACHANNELS 8;
#define DMAN3NUMQDMACHANNELS 4;

extern int L1DHEAP; /* Heap Label for L1DRAM memory allocation */
extern int EXTMEMHEAP; /* Heap Label for external memory allocation */

#define DMAN3HEAPINTERNAL L1DHEAP;
#define DMAN3HEAPEXTERNAL EXTMEMHEAP;
#define DMAN3PARAMBASEINDEX 78;
#define DMAN3NUMPARAMENTRIES 48;
#define DMAN3TCCALLOCATIONMASKH 0xffffffff;
#define DMAN3TCCALLOCATIONMASKL 0x0;
#define DMAN3QDMACHANNELS CFG_QDMA_CHANNELS;

fastcopy_dman3_config()
{
    DMAN3_PARAMS.heapInternal = DMAN3HEAPINTERNAL;
    DMAN3_PARAMS.heapExternal = DMAN3HEAPEXTERNAL;

#ifndef EDMA3_CONFIG
    DMAN3_PARAMS.numQdmaChannels    = DMAN3NUMQDMACHANNELS;
    DMAN3_PARAMS.paRamBaseIndex     = DMAN3PARAMBASEINDEX;
    DMAN3_PARAMS.numPaRamEntries    = DMAN3NUMPARAMENTRIES;
    DMAN3_PARAMS.tccAllocationMaskH = DMAN3TCCALLOCATIONMASKH;
    DMAN3_PARAMS.tccAllocationMaskL = DMAN3TCCALLOCATIONMASKL;
    DMAN3_PARAMS.qdmaChannels = CFG_QDMA_CHANNELS;
    DMAN3_PARAMS.maxQdmaChannels = DMAN3MAXQDMACHANNELS;
    DMAN3_PARAMS.numQdmaChannels = DMAN3NUMQDMACHANNELS;
#endif
}
/*
 *  @(#) ti.sdo.fc.dman3.examples.fastcopy; 1, 0, 0,235; 12-1-2010 17:24:29; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

