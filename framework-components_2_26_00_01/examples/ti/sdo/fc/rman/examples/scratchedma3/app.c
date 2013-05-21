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
 * */
#include <xdc/std.h>
#include <ti/sdo/fc/rman/rman.h>
#include <ti/sdo/fc/dskt2/dskt2.h>
#include <ti/sdo/fc/ires/iresman.h>
#include <ti/sdo/fc/ires/edma3chan/iresman_edma3Chan.h>
#include <ti/sdo/fc/ires/edma3chan/ires_edma3Chan.h>
#include <ires_algorithm.h>
#include <stdio.h>


#include <ti/sdo/fc/edma3/edma3_config.h>

#include <ti/sdo/utils/trace/gt.h>

/* #define MOD_NAME "ti.sdo.fc.rman"*/
#define MOD_NAME "*"
GT_Mask ti_sdo_fc_rman_examples_scratchEdma3_GTMask;


#include <ti/sdo/fc/utils/memleakcheck.h>

extern EDMA3_InstanceInitConfig DM6467_config;

/*
 * extern declaration 
 */
extern Int smain(Int argc, Char * argv[]);
extern Void _DSKT2_init();

Int main()
{
    IRES_Status status;

    GT_create(&ti_sdo_fc_rman_examples_scratchEdma3_GTMask, 
            "ti.sdo.fc.rman.examples.scratchEdma3");
    //Uncomment line below for trace
    GT_set(MOD_NAME "=4567");
/*
 * Call to _DSKT2_init is required as it leaks memory when DSKT2 is actually . 
 * Call it before you do MEM_stat
 */
    _DSKT2_init();

    MEMLEAKSET 
    MEMSTATINIT(myMemStat, temp, "Start DSKT2 initialized\n");

    status = RMAN_init(); 
    if (IRES_OK != status) {
        printf("RMAN initialization Failed \n");
        return -1;
    }

    MEMSTATUP(myMemStat,temp, "RMAN initialized \n");

    return 0;
}

/* ARGSUSED - this line tells the compiler to not generate compiler warnings 
 * for unused arguments */ 
Int smain(Int argc, Char * argv[])
{

    Int scratchId1 = 0;
        Int scratchId2 = 0;
    IALG_Status algStatus;
    IALG_Fxns * algFxns = &DUMRES_TI_IALG;
    IRES_Fxns * resFxns = &DUMRES_TI_IRES;
    DUMRES_TI_Handle algHandle1 = NULL; 
    DUMRES_TI_Handle algHandle2 = NULL; 
    EDMA3_Handle rmHandle = NULL;
    EDMA3_ResDesc resObj;
    IDUMRES_Params params;


    /*
     * Create 2 instances of the algorithm using "algFxns" 
     */
    params.algNum = 1;
    algHandle1 = (DUMRES_TI_Handle)DSKT2_createAlg(scratchId1, 
            (IALG_Fxns *)algFxns, NULL,(IALG_Params *)&params);
    if (algHandle1 == NULL) {
        printf("Alg creation failed for algHandle1\n");
        return -1;
    } 

    MEMSTATUP(myMemStat,temp, "Alg created 1 \n");

    params.algNum = 2;
    algHandle2 = (DUMRES_TI_Handle)DSKT2_createAlg(scratchId2, 
            (IALG_Fxns *)algFxns, NULL,(IALG_Params *)&params);
    if (algHandle2 == NULL) {
        printf("Alg creation failed for algHandle2\n");
        return -1;
    } 

    MEMSTATUP(myMemStat,temp, "Alg created 2 \n");

    /* Assign resources to the algorithm */
    if (IRES_OK != RMAN_assignResources((IALG_Handle)algHandle1,
                resFxns, scratchId1)) {
        GT_0trace(ti_sdo_fc_rman_examples_scratchEdma3_GTMask, GT_7CLASS,
                "Assign Resource Failed \n");
        goto AppEnd1;
    }

    MEMSTATUP(myMemStat,temp, "Resources assigned 1\n");

    /*
     * Activate the Algorithm
     */
    DSKT2_activateAlg(scratchId1, (IALG_Handle)algHandle1);

    /*
     * Activate All Resources
     */
    RMAN_activateAllResources((IALG_Handle)algHandle1, resFxns, scratchId1);

    /*
     * Use IALG interfaces to do something 
     */
    DSKT2_controlAlg((IALG_Handle)algHandle1, (IALG_Cmd)NULL, &algStatus);
    
    /* Assign resources to the second algorithm */
    if (IRES_OK != RMAN_assignResources((IALG_Handle)algHandle2,
                resFxns, scratchId2)) {
        printf("Assign Resource Failed \n");
        return -1;
    }

    MEMSTATUP(myMemStat,temp, "Resources assigned 2\n");

    /*
     * Deactivate All Resources
     */
    RMAN_deactivateAllResources((IALG_Handle)algHandle1, resFxns, scratchId1);

    /*
     * Deactivate algorithm 
     */
    DSKT2_deactivateAlg(scratchId1, (IALG_Handle)algHandle1);

    /*
     * Activate the Algorithm
     */
    DSKT2_activateAlg(scratchId2, (IALG_Handle)algHandle2);

    /*
     * Activate All Resources
     */
    RMAN_activateAllResources((IALG_Handle)algHandle2, resFxns, scratchId2);

    /*
     * Free resources assigned to this algorihtm
     */
    if (IRES_OK != RMAN_freeResources((IALG_Handle)(algHandle1),
                resFxns, scratchId1)) {
        printf("Free Resource Failed \n");
        return -1;
    }

    MEMSTATDOWN(myMemStat,temp, "Resources freed 1\n");
   
    /* 
     * Acquire the EDMA3 handle first
     */           
    rmHandle = EDMA3_getResourceManager(NULL, -1);
  
    if (NULL == rmHandle) {
        printf("Error obtaining SYSTEM resource Manager Handle \n");
        return (-1);
    }

    resObj.resId = 151; 
    resObj.type = EDMA3_RES_PARAM_SET;
    

    if (EDMA3_SOK != EDMA3_allocResource(rmHandle, &resObj)) {
        printf("Could not allocate this resource, as it is already owned by "
                "the algorithm\n");
    }

    resObj.resId = 256; 
    if (EDMA3_SOK != EDMA3_allocResource(rmHandle, &resObj)) {
        printf("Error, could not allocate resource %d\n"
                "ERROR for 6467, OK for 6446\n", resObj.resId);
    }
  
    if (EDMA3_SOK != EDMA3_releaseResourceManager(NULL, -1)) {
        printf("Error releasing system resource manager handle\n");
    } 

    /*
     * Deactivate All Resources
     */
    RMAN_deactivateAllResources((IALG_Handle)algHandle2, resFxns, scratchId2);

    /*
     * Deactivate algorithm 
     */
    DSKT2_deactivateAlg(scratchId2, (IALG_Handle)algHandle2);

    /*
     * Free resources assigned to this algorihtm
     */
    if (IRES_OK != RMAN_freeResources((IALG_Handle)(algHandle2),
                resFxns, scratchId2)) {
        printf("Free Resource Failed \n");
        return -1;
    }

    MEMSTATDOWN(myMemStat,temp, "Resources freed 2\n");
   
AppEnd1:
    /*
     * Free instance of the algorithm created
     */
    DSKT2_freeAlg(scratchId1, (IALG_Handle)algHandle1);

    MEMSTATDOWN(myMemStat,temp, "Free alg \n");

    /*
     * Free instance of the algorithm created
     */
    DSKT2_freeAlg(scratchId2, (IALG_Handle)algHandle2);

    MEMSTATDOWN(myMemStat,temp, "Free alg2 \n");

        RMAN_exit();

    MEMSTATDOWN(myMemStat,temp, "After RMAN_exit\n");

#if 0
    for (i = 0; i < MAXMEMSEGMENTS; i++) {
        retVal = MEM_stat(i, &stat);
        if (!retVal) {
            GT_assert(ti_sdo_fc_rman_examples_scratchEdma3_GTMask, 
                    memStat[i].size == 0);
        }
        else {
            if (memStat[i].used != stat.used) {
                GT_3trace(ti_sdo_fc_rman_examples_scratchEdma3_GTMask,
                        GT_7CLASS, "MEM seg [%d]: orig used = 0x%x, "
                        "curr used = 0x%x", i, memStat[i].used, 
                        stat.used);
                return (-1);
            }
        }
    }
#endif
    MEMLEAKCHECK

    return (0);
}


/*
#define DMA_CHANNEL_TO_EVENT_MAPPING_0          (0x30FF1FF0u)
#define DMA_CHANNEL_TO_EVENT_MAPPING_1          (0x003F07FFu)
*/
#define DMA_CHANNEL_TO_EVENT_MAPPING_0          (0x0)
#define DMA_CHANNEL_TO_EVENT_MAPPING_1          (0x0)

EDMA3_InstanceInitConfig DM6467_config = 
          {
            /* Resources owned by Region 1 */
            /* ownPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u,
            0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,
            0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,
            0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu},

            /* ownDmaChannels */
            {0xCF00E00Fu, 0xFF00F800u},

            /* ownQdmaChannels */
            {0x0000007Fu},

            /* ownTccs */
/*             {0xCF00E00Fu, 0xFF00F800u},*/
            {0xC0FF10F0u, 0xFF00F800u},

            /* Resources reserved by Region 1 */
            /* resvdPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u},

            /* resvdDmaChannels */
            {DMA_CHANNEL_TO_EVENT_MAPPING_0, DMA_CHANNEL_TO_EVENT_MAPPING_1},

            /* resvdQdmaChannels */
            {0x0u},

            /* resvdTccs */
            {DMA_CHANNEL_TO_EVENT_MAPPING_0, DMA_CHANNEL_TO_EVENT_MAPPING_1},
          };

EDMA3_InstanceInitConfig FULL_config = 
          {
            /* Resources owned by Region 1 */
            /* ownPaRAMSets */
            0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,
            0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,
            0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,
            0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,

            /* ownDmaChannels */
            {0xFFFFFFFF, 0xFFFFFFFF},

            /* ownQdmaChannels */
            {0xFFFFFFFF},

            /* ownTccs */
            {0xFFFFFFFF, 0xFFFFFFFF},

            /* Resources reserved by Region 1 */
            /* resvdPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u},

            /* resvdDmaChannels */
            {0x0, 0x0},

            /* resvdQdmaChannels */
            {0x0u},

            /* resvdTccs */
            {0x0, 0x0},
          };
/*
 *  @(#) ti.sdo.fc.rman.examples.scratchedma3; 1, 0, 0,30; 12-1-2010 17:25:51; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

