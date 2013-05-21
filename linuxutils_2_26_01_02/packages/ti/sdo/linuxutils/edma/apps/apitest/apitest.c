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
 * apitest.c
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>

#include <edma.h>

//For Rob's bad DM355 board (hangs kernel when trying to access TCC 0)
//#define TCC0_BAD

int test_consecutive_params(void);
int test_register(void);

int main(int argc, char *argv[])
{
    int tcc;
#ifdef TCC0_BAD
    int lockout_channel;
#endif
    int channel;
    int channels[64];
    int i;
    int param;
    int nParam;
    EDMA_Status status;
    void *pBase;

    status = EDMA_init();
    if (status == -1) {
        printf("EDMA_init() failed, exiting\n");

        exit(-1);
    }

    printf("calling EDMA_mapBaseAddress(&pBase)...\n");
    EDMA_mapBaseAddress(&pBase);

    nParam = 1;

#ifdef TCC0_BAD
    /*
     * Lockout channel 0 w/ non-0 TCC (relies on the fact that EDMAANY will
     * choose channel 0), also locks out channel 25 (don't care if it fails).
     */
    tcc = 25;
    status = EDMA_getResource(EDMA_EDMAANY, &tcc, &lockout_channel, &param, nParam);
    printf("EDMA_getResource(EDMA_EDMAANY, %d): status=%d, lockout_channel=%d, tcc=%d, param=%d\n", nParam, status, lockout_channel, tcc, param);

    if (status != EDMA_OK) {
        printf("failed (which is OK)\n");
    }
#endif

#ifndef TCC0_BAD
    /* just try a normal allocation first */
    status = EDMA_getResource(0, &tcc, &channel, &param, nParam);
    printf("EDMA_getResource(0, %d): status=%d, channel=%d, tcc=%d, param=%d\n", nParam, status, channel, tcc, param);

    if (status != EDMA_OK) {
        printf("failed\n");
    }
    else {
        status = EDMA_freeResource(channel, nParam);
        printf("EDMA_freeResource(%d, %d): status=%d\n", channel, nParam, status);
    }
#endif

    for (i = 0; i < 64; i++) {
        channels[i] = 0;
    }

    do {
        /* EDMA_EDMAANY */
        tcc = EDMA_TCCSYMM;
        status = EDMA_getResource(EDMA_EDMAANY, &tcc, &channel, &param, nParam);
        printf("EDMA_getResource(EDMA_EDMAANY, %d): status=%d, channel=%d, tcc=%d, param=%d\n", nParam, status, channel, tcc, param);

        if (status != EDMA_OK) {
            printf("failed\n");
        }

        if (status == EDMA_OK) {
            channels[channel] = 1;
        }
    } while (status == EDMA_OK);

    for (i = 0; i < 64; i++) {
        if (channels[i]) {
            status = EDMA_freeResource(i, nParam);
            printf("EDMA_freeResource(%d, %d): status=%d\n", i, nParam, status);
        }
    }


    /* EDMA_QDMA# */
    tcc = EDMA_TCCANY;
    status = EDMA_getResource(EDMA_QDMA1, &tcc, &channel, &param, nParam);
    printf("EDMA_getResource(EDMA_QDMA1, %d): status=%d, channel=%d, tcc=%d, param=%d\n", nParam, status, channel, tcc, param);

    if (status != EDMA_OK) {
        printf("failed\n");
    }
    else {
        status = EDMA_freeResource(channel, nParam);
        printf("EDMA_freeResource(%d, %d): status=%d\n", channel, nParam, status);
    }

    /* EDMA_EDMA# */
    status = EDMA_getResource(1, &tcc, &channel, &param, nParam);
    printf("EDMA_getResource(1, %d): status=%d, channel=%d, tcc=%d, param=%d\n", nParam, status, channel, tcc, param);

    if (status != EDMA_OK) {
        printf("failed\n");
    }
    else {
        status = EDMA_freeResource(channel, nParam);
        printf("EDMA_freeResource(%d, %d): status=%d\n", channel, nParam, status);
    }

    test_consecutive_params();

#ifdef TCC0_BAD
    status = EDMA_freeResource(lockout_channel, nParam);
    printf("EDMA_freeResource(%d, %d): status=%d (freeing lockout_channel)\n", lockout_channel, nParam, status);
#endif

    if ((status = test_register()) != 0) {
        printf("test_register() failed (%d)\n", status);
    }

    /* EDMA_EDMA# */
    status = EDMA_getResource(1, &tcc, &channel, &param, nParam);
    printf("EDMA_getResource(1, %d): status=%d, channel=%d, tcc=%d, param=%d\n", nParam, status, channel, tcc, param);

    if (status != EDMA_OK) {
        printf("failed, exiting...\n");

        exit(2);
    }

    /* Exit w/o explicitly freeing the resource above (it will auto-free) */
    EDMA_exit();

    printf("test done, exiting ...\n");

    exit(EXIT_SUCCESS);
}

int test_consecutive_params(void)
{
    int tcc;
    int channel;
    int param;
    int nParam;
    EDMA_Status status;
    int channel1;
    int channel2;
    int holeChannel;

    /*
     * Test consecutive PaRAM allocation.
     * First, allocate some number > 1 ...
     */
    nParam = 5;
    tcc = -1;
//    param = -1;
    param = 64;
    status = EDMA_getResource(EDMA_PARAMANY, &tcc, &channel1, &param, nParam);
    printf("EDMA_getResource(EDMA_PARAMANY, %d): status=%d, start channel1=%d, tcc=%d, param=%d\n", nParam, status, channel1, tcc, param);

    if (status != EDMA_OK) {
        printf("failed, returning...\n");

        return status;
    }

    /* allocate some number (> 1 again) more in order to create a "hole" */
    nParam = 5;
    tcc = -1;
    param = 64;
    status = EDMA_getResource(EDMA_PARAMANY, &tcc, &channel2, &param, nParam);
    printf("EDMA_getResource(EDMA_PARAMANY, %d): status=%d, start channel2=%d, tcc=%d, param=%d\n", nParam, status, channel2, tcc, param);

    if (status != EDMA_OK) {
        printf("failed, cleaning up & returning...\n");

        /* clean up */
        status = EDMA_freeResource(channel1, nParam);
        printf("EDMA_freeResource(%d, %d): status=%d\n", channel1, nParam, status);

        return status;
    }

    /* save channel associated with hole */
    holeChannel = channel1;

    /* free first group to create a hole */
    status = EDMA_freeResource(channel1, nParam);
    printf("EDMA_freeResource(%d, %d): status=%d\n", channel1, nParam, status);

    /* allocate one more than the hole size, to show the hole is skipped */
    nParam = 6;
    tcc = -1;
    param = 64;
    status = EDMA_getResource(EDMA_PARAMANY, &tcc, &channel, &param, nParam);
    printf("EDMA_getResource(EDMA_PARAMANY, %d): status=%d, start channel=%d, tcc=%d, param=%d\n", nParam, status, channel, tcc, param);

    if (status != EDMA_OK) {
        printf("failed, cleaning up & returning...\n");

        /* clean up */
        status = EDMA_freeResource(channel2, 5);
        printf("EDMA_freeResource(%d, 5): status=%d\n", channel2, status);

        return status;
    }

    status = EDMA_freeResource(channel, nParam);
    printf("EDMA_freeResource(%d, %d): status=%d\n", channel, nParam, status);

    /* this allocation should hit the hole */
    nParam = 5;
    tcc = -1;
    param = 64;
    status = EDMA_getResource(EDMA_PARAMANY, &tcc, &channel, &param, nParam);
    printf("EDMA_getResource(EDMA_PARAMANY, %d): status=%d, start channel=%d, tcc=%d, param=%d\n", nParam, status, channel, tcc, param);

    if (status == EDMA_OK) {
        if (channel != holeChannel) {
            printf("channel(%d) != holeChannel(%d), test failed\n", channel, holeChannel);
        }
        else {
            printf("channel(%d) == holeChannel(%d)\n", channel, holeChannel);
        }

        status = EDMA_freeResource(channel, nParam);
        printf("EDMA_freeResource(%d, %d): status=%d\n", channel, nParam, status);
    }

    /* free second group to clean up */
    status = EDMA_freeResource(channel2, nParam);
    printf("EDMA_freeResource(%d, %d): status=%d\n", channel2, nParam, status);

    return status;
}

int test_register(void)
{
    int tcc;
    int channel;
    int param;
    EDMA_Status status;

    /* EDMA_EDMA# */
    printf("calling EDMA_getResource()...\n");
    status = EDMA_getResource(1, &tcc, &channel, &param, 1);
    printf("EDMA_getResource(1, 1): status=%d, channel=%d, tcc=%d, param=%d\n", status, channel, tcc, param);

    if (status != EDMA_OK) {
        printf("failed, returning...\n");

        return -1;
    }

    printf("calling EDMA_registerResource(%d)...\n", channel);
    status = EDMA_registerResource(channel);
    printf("EDMA_registerResource(%d) called\n", channel);

    if (status != EDMA_OK) {
        printf("failed, returning...\n");

        return -1;
    }

    printf("calling EDMA_unregister(%d, 1)...\n", channel);
    status = EDMA_unregister(channel, 1);
    printf("EDMA_unregister(%d, 1) called\n", channel);

    if (status != EDMA_OK) {
        printf("failed, returning...\n");

        return -1;
    }

    printf("calling EDMA_freeResource(%d, 1)...\n", channel);
    status = EDMA_freeResource(channel, 1);
    printf("EDMA_freeResource(%d, 1) called\n", channel);

    if (status != EDMA_OK) {
        printf("failed, returning...\n");

        return -1;
    }

    printf("calling EDMA_registerResource(%d) (should fail)\n", channel);
    status = EDMA_registerResource(channel);
    printf("EDMA_registerResource(%d) called (should fail)\n", channel);

    if (status == EDMA_OK) {
        printf("test failed (EDMA_registerResource(%d) succeeded when it should fail), returning...\n", channel);

        return -1;
    }

    return 0;
}

/*
 *  @(#) ti.sdo.linuxutils.edma; 1, 0, 0,92; 11-30-2010 18:31:36; /db/atree/library/trees/linuxutils/linuxutils-j02x/src/ xlibrary

 */

