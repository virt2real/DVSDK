/* --COPYRIGHT--,BSD
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
 * --/COPYRIGHT--*/
/*
 * This application encodes an elementary stream speech file using a specified
 * XDM speech codec to an output file.
 */

#include <stdio.h>
#include <string.h>

#include <stdlib.h>

#include <xdc/std.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/CERuntime.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Time.h>
#include <ti/sdo/dmai/Buffer.h>
#include <ti/sdo/dmai/ce/Senc1.h>

#include "appMain.h"

/* Align buffers to this cache line size (in bytes)*/
#define BUFSIZEALIGN            128

/* vbuf size that has been selected based on size/performance tradeoff */
#define VBUFSIZE                20480

static Char vbuffer[VBUFSIZE];

/* These definitions missing in some OS build environments (eg: WinCE) */
#ifndef _IOFBF
    #define _IOFBF  0
#endif  /* _IOFBF */
#ifndef _IOLBF
    #define _IOLBF  1
#endif  /* _IOLBF */
#ifndef _IONBF
    #define _IONBF  2
#endif  /* _IONBF */

/******************************************************************************
 * appMain
 ******************************************************************************/
Void appMain(Args * args)
{
    Buffer_Attrs            bAttrs      = Buffer_Attrs_DEFAULT;
    Time_Attrs              tAttrs      = Time_Attrs_DEFAULT;
    SPHENC1_Params          params      = Senc1_Params_DEFAULT;
    SPHENC1_DynamicParams   dynParams   = Senc1_DynamicParams_DEFAULT;
    Senc1_Handle            hSe1        = NULL;
    Engine_Handle           hEngine     = NULL;
    Buffer_Handle           hOutBuf     = NULL;
    Buffer_Handle           hInBuf      = NULL;
    Time_Handle             hTime       = NULL;
    FILE                   *inFile      = NULL;
    FILE                   *outFile     = NULL;
    Int                     numFrame    = 0;
    Int32                   bytesRead;
    UInt32                  time;

   printf("Starting application...\n");

   if (args->benchmark) {
        hTime = Time_create(&tAttrs);

        if (hTime == NULL) {
            printf("Failed to create Time object\n");
            goto cleanup;
        }
    }

    /* Initialize the codec engine run time */
    CERuntime_init();

    /* Initialize DMAI */
    Dmai_init();

    /* Open the output file */
    outFile = fopen(args->outFile, "wb");

    if (outFile == NULL) {
        printf("Failed to create output file %s\n", args->outFile);
        goto cleanup;
    }

    /* Open the input file */
    inFile = fopen(args->inFile, "rb");

    if (inFile == NULL) {
        printf("Failed to open input file %s\n", args->inFile);
        goto cleanup;
    }

    /* Using a larger vbuf to enhance performance of file i/o */
        if (setvbuf(outFile, vbuffer, _IOFBF, sizeof(vbuffer)) != 0) {
            printf("Failed to setvbuf on file descriptor\n");
            goto cleanup;
    }

    /* Open the codec engine */
    hEngine = Engine_open(args->engineName, NULL, NULL);

    if (hEngine == NULL) {
        printf("Failed to open codec engine %s\n", args->engineName);
        goto cleanup;
    }
    
    params.compandingLaw = args->compandingLaw;

    /* Create the SPHENC1 based speech encoder */
    hSe1 = Senc1_create(hEngine, args->codecName, &params, &dynParams);

    if (hSe1 == NULL) {
        printf("Failed to create %s\n", args->codecName);
        goto cleanup;
    }

    /* Align buffers to cache line boundary */    
    bAttrs.memParams.align = BUFSIZEALIGN; 
    
    /* Use cached buffers if requested */  
    if (args->cache) {
        bAttrs.memParams.flags = Memory_CACHED;
    } 
    
    /* Create an output buffer for encoded data */
    hOutBuf = Buffer_create(
        Dmai_roundUp(Senc1_getOutBufSize(hSe1), BUFSIZEALIGN), &bAttrs); 

    if (hOutBuf == NULL) {
        printf("Failed to create contiguous buffer\n");
        goto cleanup;
    }

    /* Create an input buffer for input data */
    hInBuf = Buffer_create(Dmai_roundUp(Senc1_getInBufSize(hSe1), BUFSIZEALIGN),
                           &bAttrs);

    if (hInBuf == NULL) {
        printf("Failed to create contiguous buffer\n");
        goto cleanup;
    }

    while (numFrame++ < args->numFrames) {
        printf("Frame %d: ", numFrame);
        if (args->benchmark) {
            if (Time_reset(hTime) < 0) {
                printf("Failed to reset timer\n");
                goto cleanup;
            }
        }

        /* Read raw PCM data from input file */
        bytesRead = fread(Buffer_getUserPtr(hInBuf), 1,
                          Senc1_getInBufSize(hSe1), inFile);

        if (bytesRead < Senc1_getInBufSize(hSe1)) {
            if (ferror(inFile)) {
                printf("Failed to read data from input file\n");
                goto cleanup;
            }
             printf("Failed to read full frame %ld bytes, read %ld bytes\n",
                                    Senc1_getInBufSize(hSe1),bytesRead);
             goto cleanup;
        }

        Buffer_setNumBytesUsed(hInBuf, bytesRead);

        if (args->benchmark) {
            if (Time_delta(hTime, &time) < 0) {
                printf("Failed to get timer delta\n");
                goto cleanup;
            }
            printf("Read: %uus ", (Uns) time);
        }

        if (args->cache) {
            /*
             *  To meet xDAIS DMA Rule 7, when input buffers are cached, we
             *  must writeback the cache into physical memory.  Also, per DMA
             *  Rule 7, we must invalidate the output buffer from
             *  cache before providing it to any xDAIS algorithm.
             */
            Memory_cacheWbInv(Buffer_getUserPtr(hInBuf),
                              Buffer_getSize(hInBuf));

            /* Per DMA Rule 7, our output buffer cache lines must be cleaned */
            Memory_cacheInv(Buffer_getUserPtr(hOutBuf),
                            Buffer_getSize(hOutBuf));

            if (args->benchmark) {
                if (Time_delta(hTime, &time) < 0) {
                    printf("Failed to get timer delta\n");
                    goto cleanup;
                }
                printf("Pre-process cache maintenance: %uus ", (Uns) time);
            }
        }

        /* Encode the speech buffer */
        if (Senc1_process(hSe1, hInBuf, hOutBuf) < 0) {
            printf("Failed to encode speech buffer\n");
            goto cleanup;
        }

        if (args->benchmark) {
            if (Time_delta(hTime, &time) < 0) {
                printf("Failed to get timer delta\n");
                goto cleanup;
            }
            printf("Encode: %uus ", (Uns) time);
        }

        if (args->cache) {
            /* Writeback the outBuf. */
            Memory_cacheWb(Buffer_getUserPtr(hOutBuf), Buffer_getSize(hOutBuf));

            if (args->benchmark) {
                if (Time_delta(hTime, &time) < 0) {
                    printf("Failed to get timer delta\n");
                    goto cleanup;
                }
                printf("Post-process cache write back: %uus ", (Uns) time);
            }
        }

        printf("Write encoded speech data to output file \n");

        /* Write the encoded frame to the file system */
        if (Buffer_getNumBytesUsed(hOutBuf)) {
            if (fwrite(Buffer_getUserPtr(hOutBuf),
                       Buffer_getNumBytesUsed(hOutBuf), 1, outFile) != 1) {
                printf("Failed to write encoded speech data to file\n");
                goto cleanup;
            }
        }

        if (args->benchmark) {
            if (Time_delta(hTime, &time) < 0) {
                printf("Failed to get timer delta\n");
                goto cleanup;
            }
            printf("Write: %uus ", (Uns) time);

            if (Time_total(hTime, &time) < 0) {
                printf("Failed to get timer total\n");
                goto cleanup;
            }

            printf("Total: %uus\n", (unsigned int)time);
        }
    }
cleanup:
    /* Clean up the application */
    if (hSe1) {
        Senc1_delete(hSe1);
    }

    if (hInBuf) {
        Buffer_delete(hInBuf);
    }

    if (hOutBuf) {
        Buffer_delete(hOutBuf);
    }

    if (hEngine) {
        Engine_close(hEngine);
    }

    if (hTime) {
        Time_delete(hTime);
    }

    if (inFile) {
        fclose(inFile);
    }

    if (outFile) {
        fclose(outFile);
    }

    printf("End of application.\n");

    return;
}

