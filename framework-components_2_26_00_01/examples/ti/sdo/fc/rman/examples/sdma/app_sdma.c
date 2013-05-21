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
/*
 * ======== app.c ========
 */

#include <xdc/std.h>


#define ti_sdo_fc_ires_NOPROTOCOLREV
#include <ti/sdo/fc/ires/sdma/ires_sdma.h>
#include <ti/sdo/fc/scpy/scpy.h>
#include <ti/sdo/linuxutils/sdma/include/sdma.h>
#include <ti/sdo/linuxutils/cmem/include/cmem.h>

#include <stdio.h>
#include <stdlib.h>

#include <ti/sdo/utils/trace/gt.h>
#define CURTRACE ti_sdo_fc_rman_examples_sdma

#define NUMTRANSFERS 2
#define BUF_SIZE 4096
#define MODNAME "*"

static GT_Mask CURTRACE;

/*
 * Tasks
 */
extern Int sdmaTask(Int argc, Char * argv[]);
extern Void myIdle();

/*
 * extern declaration
 */
extern Int smain(Int argc, Char * argv[]);


Int main(Int argc, String argv[])
{

    GT_init();
    GT_create(&ti_sdo_fc_rman_examples_sdma,"ti.sdo.fc.rman.examples.sdma");
        GT_set(MODNAME "=01234567");
/*      GT_set("ti.sdo.fc.rman" "=4567");*/
/*      GT_set("ti.sdo.fc.ires.sdma" "=01234567");*/

    GT_0trace(ti_sdo_fc_rman_examples_sdma, GT_ENTER, "_main> Enter \n");

    GT_0trace(ti_sdo_fc_rman_examples_sdma, GT_ENTER, "_main> Exit \n");

    return (sdmaTask(argc, argv));
}

/*
 * Idle task can do the cleanup ?
 */
Void myIdle()
{
    GT_0trace(ti_sdo_fc_rman_examples_sdma, GT_ENTER, "_myIdle> Enter \n");
    GT_0trace(ti_sdo_fc_rman_examples_sdma, GT_ENTER, "_myIdle> Exit \n");
}

/* ARGSUSED - this line tells the compiler to not generate compiler warnings
 * for unused arguments */
/*
 *  ======== smain ========
 */
/* ARGSUSED */
Int sdmaTask(Int argc, Char * argv[])
{
    IRES_SDMA_Obj sdmaObj[NUMTRANSFERS];
    Int numChannels = NUMTRANSFERS;
    SDMA_ChannelDescriptor chanArray[NUMTRANSFERS]; 
    CMEM_AllocParams cmem_params;
    Int ret,i,j;
    Bool status = TRUE;

    cmem_params.type = CMEM_POOL;
    cmem_params.flags = CMEM_NONCACHED;
 
    ret = CMEM_init();

    unsigned *src_addr = (unsigned *)CMEM_alloc(BUF_SIZE, &cmem_params);
    unsigned *dest_addr = (unsigned *)CMEM_alloc(BUF_SIZE, &cmem_params);
    unsigned *dest2_addr = (unsigned *)CMEM_alloc(BUF_SIZE, &cmem_params);

    SCPY_AddrParams src = {OMAP_DMA_AMODE_POST_INC,(unsigned)src_addr,0,0};
    SCPY_AddrParams dest = {OMAP_DMA_AMODE_POST_INC,(unsigned)dest_addr,0,0};
    SCPY_TransferParams trans_params = {OMAP_DMA_DATA_TYPE_S32,BUF_SIZE/4,1};
    SCPY_Params scpy_params = {&src,&dest,&trans_params};
    SCPY_AddrParams dest2 = {OMAP_DMA_AMODE_POST_INC,(unsigned)dest2_addr,0,0};
    SCPY_Params scpy2_params = {&src,&dest2,&trans_params};
 
     
    /* Fill src buffer with C0FFEE00 */
    for(i=0;i < ((int)BUF_SIZE / 4);i++) {
        src_addr[i] = 0xC0FFEE00;
    }
 
    /* Fill dest buffer with DEADBEEF */
    for(i=0;i < ((int)BUF_SIZE / 4);i++) {
        dest_addr[i] = 0xDEADBEEF;
    }
 
    /* Fill dest buffer with DEADBEEF */
    for(i=0;i < ((int)BUF_SIZE / 4);i++) {
        dest2_addr[i] = 0xDEADBEEF;
    }
            
    /* Populate chanArray */ 
    for (i = 0; i < numChannels; i++) {
        chanArray[i].chanNum = -1;   /* Channel number will be returned here */ 
        chanArray[i].addr = NULL;   /* Address will be returned here */ 
    } 

    GT_0trace(ti_sdo_fc_rman_examples_sdma, GT_ENTER, "_sdmaTask> Enter \n");

    if (0 == SDMA_init()) {

        if (SDMA_OK == SDMA_getChannels(numChannels, chanArray)) {

            for (i = 0; i < numChannels; i++) {

                GT_2trace(CURTRACE, GT_4CLASS, "sdmaTask> Channel returned %d "
                        "Addr 0x%x\n",chanArray[i].chanNum, chanArray[i].addr);
    
                sdmaObj[i].channel = &chanArray[i];
            }
            SCPY_init();
    
            /* Call SCPY APIs*/
    
            /* Configure transfer parameters for the first channel */
            SCPY_configure(&sdmaObj[0], &scpy_params);

            /* Configure transfer parameters for the second channel */
            SCPY_configure(&sdmaObj[1], &scpy2_params);
         
            /* Fill dest with C0FFEE */
            SCPY_start(&sdmaObj[0]);

            /* Fill dest2 with C0FFEE */
            SCPY_start(&sdmaObj[1]);
         
            /* Wait for transfer 1 to finish */
            SCPY_wait(&sdmaObj[0]);            
         
            /* Check for C0FFEE */
            for(j=0;j < ((int)BUF_SIZE / 4);j++) {
                if (dest_addr[j] != 0xC0FFee00) { 
                    status = FALSE;
                    break;
                } 
                //printf("%x:%d\t",dest_addr[j],j);
            }

            if (FALSE == status) {
                GT_0trace(CURTRACE, GT_4CLASS, "sdmaTask> SDMA Transfer Error\n");
            }
            else {
                GT_0trace(CURTRACE, GT_4CLASS, "sdmaTask> SDMA Transfer "
                        "Succeeded\n");
            }

            
            /* Wait for transfer 2 to finish */
            SCPY_wait(&sdmaObj[1]);            
        
            status = TRUE;
            /* Check for C0FFEE */
            for(j=0;j < ((int)BUF_SIZE / 4);j++) {
                if (dest2_addr[j] != 0xC0FFee00) { 
                    status = FALSE;
                    break;
                } 
                //printf("%x:%d\t",dest2_addr[j],j);
            } 

            if (FALSE == status) {
                GT_0trace(CURTRACE, GT_4CLASS, "sdmaTask> SDMA Transfer Error\n");
            }
            else {
                GT_0trace(CURTRACE, GT_4CLASS, "sdmaTask> SDMA Transfer "
                        "Succeeded\n");
            }

            SCPY_exit();
        
            /* Free channels */    
            if (SDMA_OK != SDMA_freeChannels(numChannels, chanArray)) {
                //error
            }
        }
        else {
            //error
        }
    
        if (0 != SDMA_exit()) {
            //error 
        }
    }
    else {
        //error
    }
    

    GT_0trace(ti_sdo_fc_rman_examples_sdma, GT_ENTER, "_sdmaTask> Exit \n");

    return 0;
}
/*
 *  @(#) ti.sdo.fc.rman.examples.sdma; 1, 0, 0,132; 12-1-2010 17:25:55; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

