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
 *  ======== appScratch.c ========
 *  Creates multiple algorithms, that request a bunch of resources in different
 *  /same (specified) scratch group.
 */

#include <xdc/std.h>

#include <ti/sdo/fc/rman/rman.h>
#include <ti/sdo/utils/trace/gt.h>

#include <ti/sdo/fc/ires/vicp/iresman_vicp2.h>
#include <ti/sdo/fc/ires/examples/codecs/vicp2codec1/vicp2codec1_ti.h>


#include <ti/sdo/ce/alg/Algorithm.h>

#include <stdio.h>
#include <stdlib.h>

GT_Mask ti_sdo_fc_ires_vicp_test_GTMask;

/*
 * extern declaration
 */
extern Int smain(Int argc, Char * argv[]);
extern int sleep(unsigned int secs);
extern Int myIdle(Int argc, Char * argv[]);

static Bool result = TRUE;

/* ARGSUSED */
Int main(Int argc, Char * argv[])
{
    IRES_Status status;

    GT_create(&ti_sdo_fc_ires_vicp_test_GTMask,"ti.sdo.fc.ires.vicp.test");
/*      GT_set("*" "=01234567");*/

        GT_init();
        Memory_init();
        Global_init();
        SemMP_init();
    LockMP_init();
    Algorithm_init();


    status = RMAN_init();
    if (IRES_OK != status) {
        printf("RMAN initialization Failed \n");
        return -1;
    }


#ifndef xdc_target__isaCompatible_64P
    return (smain(argc, argv));
#else
    return (0);
#endif

}

/* ARGSUSED - this line tells the compiler to not generate compiler warnings
 * for unused arguments */
Int smain(Int argc, Char * argv[])
{

    IRES_Status status = IRES_OK;
    Int scratchId[20] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1};
    IALG_Fxns * algFxns = (IALG_Fxns *)&VICP2CODEC1_TI_CODECIRES;
    IRES_Fxns * resFxns = &VICP2CODEC1_TI_IRES;
    Algorithm_Handle dumHandle[20] = { NULL, NULL, NULL, NULL, NULL,
                NULL, NULL, NULL, NULL, NULL, NULL, NULL,NULL, NULL,
                NULL, NULL, NULL, NULL, NULL, NULL };
    IVICP2CODEC1_Params params;
    IALG_Handle alg = NULL;
    Int numAlgs = 3;
    Int i,k;
    Algorithm_Attrs attrs;

#ifdef xdc_target__os_Linux

    if (argc > 1) {
        numAlgs = atoi(argv[1]);
    }

    if (argc > 2) {
        for (i = 0; i < argc-2; i++) {
            scratchId[i] = atoi(argv[i+2]);
        }
    }
#endif

#ifdef LATEACQUIRE
    numAlgs = 1;        //2;
    scratchId[0] = 0;
    scratchId[1] = 0;
#endif

    Algorithm_init();

    for (i = 0; i < numAlgs; i++) {

        /*
         * Create an instance of the algorithm using "algFxns"
         */

        attrs.groupId = 0;
        attrs.groupId = TRUE;

        dumHandle[i] = Algorithm_create((IALG_Fxns *)algFxns,
                NULL, resFxns, (IALG_Params *)&params, &attrs);

        if (dumHandle[i] == NULL) {
            printf("Alg creation failed, Alg %d\n",i);
            return (-1);
        }
        else {

            /* Resources have been assigned */

            /*
             * Activate the Algorithm
             */
            printf("Activating Alg 0x%x\n", dumHandle[i]);
            Algorithm_activate((Algorithm_Handle)dumHandle[i]);
            printf("Activated Alg 0x%x\n", dumHandle[i]);

            alg = Algorithm_getAlgHandle(dumHandle[i]);

            result = ((IVICP2CODEC1_Fxns *)(&VICP2CODEC1_TI_CODECIRES))->
                    useVICP(alg);

            /*
             * Deactivate All Resources
             */
            printf("Deactivating Alg 0x%x\n", dumHandle[i]);
            Algorithm_deactivate((Algorithm_Handle)dumHandle[i]);
        }

        if (!(result))
            break;
    }

    if (result)
    for (i = 0; i < numAlgs; i++) {

        if (IRES_OK != status) {
            printf("Free Resource Failed \n");
            result = FALSE;
        }
        Algorithm_delete((IALG_Handle)dumHandle[i]);
    }

    Algorithm_exit();

#ifndef xdc_target__isaCompatible_64P
    return (myIdle(argc, argv));
#else
    return (0);
#endif

}

/* ARGSUSED */
Int myIdle(Int argc, Char * argv[])
{
    IRES_Status status;

    status = RMAN_exit();
    if (IRES_OK != status) {
        result = FALSE;
    }

    if (result) {
        printf("TEST PASSED\n");
    }
    else {
        printf("TEST FAILED.\n");
    }
    return (0);
}
/*
 *  @(#) ti.sdo.fc.rman.examples.lateacquire; 1, 0, 0,32; 12-1-2010 17:25:45; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

