/* ========================================================================== */
/*                                                                            */
/*  NAME                                                                      */
/*     idma3_create.c                                                         */
/*                                                                            */
/*  DESCRIPTION                                                               */
/*    This file contains a simple implementation of the idma3_create API      */
/*				                                                              */
/*                                                                            */
/* ========================================================================== */

#include <alg.h>
#include <ti/xdais/xdas.h>
#include <ti/xdais/idma3.h>
#include <ti/xdais/dm/xdm.h>
#include <stdlib.h>
#include <_alg.h>
#include"mp4vdec_edma.h"
#define NUM_EXTRA_PARAM_ENTRIES 14

const unsigned char paramMp4decEntries[14]={64,65,66,67,68,69,70,71,72,73,74,75,76,77};




IDMA3_Obj handle[1];

Int _DMA_allocChannels(IDMA3_ChannelRec *dmaTab, Int n)
{
  #ifdef ENABLE_IDMA3
	Uint32 idxCnt;
	for(idxCnt = 0; idxCnt < n; idxCnt++)
	{
        /* Check if the algorithm is requesting for more 
         * than 32 channels */
		if(dmaTab[idxCnt].numTransfers > 32) return 0;
        
        /* allocate space for DMA channel handle - This should be 
         * ideally done by DMAN3 module */
        dmaTab[idxCnt].handle = (IDMA3_Handle) malloc(sizeof(IDMA3_Obj));
        if(dmaTab[idxCnt].handle == NULL) return 0;
        
		dmaTab[idxCnt].handle->tccTable = NULL;
		dmaTab[idxCnt].handle->numTccs = dmaTab[idxCnt].numWaits;
		dmaTab[idxCnt].handle->numPaRams = dmaTab[idxCnt].numTransfers;		
		/* Here are we are deriving the actual physical address of the 
		 * ParamSet we are allocating 
		 */
		dmaTab[idxCnt].handle->paRamAddr = (Uns*)
				(0x1c04000 + (paramMp4decEntries[NUM_EXTRA_PARAM_ENTRIES/*idxCnt*/-1]*0x20));
		/* dmaTab->numWaits would specify the number of PaRam spaces 
		 * required and dmaTab->numTransfers would indicate number of 
		 * tccs required by the codec component 
		 */
	}
#endif
    return n;

}

/*
 *  ======== IDMA3_create ========
 */
IALG_Handle IDMA3_create(IDMA3_Fxns *fxns, IALG_Handle p)
{
#ifdef ENABLE_IDMA3
    IDMA3_ChannelRec *dmaTab;
    Int n;

    if (fxns != NULL) {
        n = fxns->dmaGetChannelCnt != NULL ? fxns->dmaGetChannelCnt() : IALG_DEFMEMRECS;

        if ((dmaTab = (IDMA3_ChannelRec *)malloc(n * sizeof (IDMA3_ChannelRec)))) {

            n = fxns->dmaGetChannels(p, dmaTab);
            if (n <= 0) {
                return (NULL);
            }

            if (_DMA_allocChannels(dmaTab, n)) {
                if (fxns->dmaInit(p, dmaTab) == IALG_EOK) {
                    free(dmaTab);
                    return (p);
                }
            }
            free(dmaTab);
        }
    }

#endif
	return (p);

    

}


