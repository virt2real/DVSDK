/* 
 *  Copyright 2010
 *  Texas Instruments Incorporated
 *
 *  All rights reserved.  Property of Texas Instruments Incorporated
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 * 
 */

/*
 *  ======== dman3_config.c ========
 *  Configuration for DMAN3 Parameters
 */
#include <std.h>
#include <ti/sdo/fc/dman3/dman3.h>

#define DMAN3MAXQDMACHANNELS 8;
#define DMAN3NUMQDMACHANNELS 4;
#define DMAN3NUMQDMACHANNELSLLRM 1;

extern int L1DHEAP; /* Heap Label for L1DRAM memory allocation */
extern int EXTMEMHEAP; /* Heap Label for external memory allocation */

#define DMAN3HEAPINTERNAL L1DHEAP;
#define DMAN3HEAPEXTERNAL EXTMEMHEAP;
#define DMAN3PARAMBASEINDEX 78;
#define DMAN3NUMPARAMENTRIES 48;

#define DMAN3TCCALLOCATIONMASKL 0xffffffff;
/* Keep this H mask 0, as Freon has only 32 Tccs */
#define DMAN3TCCALLOCATIONMASKH 0x0;
#define DMAN3QDMACHANNELS CFG_QDMA_CHANNELS;

#ifndef EDMA3_CONFIG
static Uns CFG_QDMA_CHANNELS[4] = { 0, 1, 2, 3};
#endif


fastcopy_dman3_config()
{
        /* When using the DMAN3 on LLD, only these three are required to be set */
    DMAN3_PARAMS.heapInternal       = DMAN3HEAPINTERNAL;
    DMAN3_PARAMS.heapExternal       = DMAN3HEAPEXTERNAL;
        DMAN3_PARAMS.numQdmaChannels    = DMAN3NUMQDMACHANNELSLLRM;

#ifndef EDMA3_CONFIG
        DMAN3_PARAMS.numQdmaChannels    = DMAN3NUMQDMACHANNELS;
    DMAN3_PARAMS.paRamBaseIndex     = DMAN3PARAMBASEINDEX;
    DMAN3_PARAMS.numPaRamEntries    = DMAN3NUMPARAMENTRIES;
    DMAN3_PARAMS.tccAllocationMaskH = DMAN3TCCALLOCATIONMASKH;
    DMAN3_PARAMS.tccAllocationMaskL = DMAN3TCCALLOCATIONMASKL;
    DMAN3_PARAMS.qdmaChannels       = CFG_QDMA_CHANNELS;
    DMAN3_PARAMS.maxQdmaChannels    = DMAN3MAXQDMACHANNELS;
    DMAN3_PARAMS.maxTCs             = 2;
#endif
}
/*
 *  @(#) ti.sdo.fc.dman3.examples.fastcopy; 1, 0, 0,235; 12-1-2010 17:24:30; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

