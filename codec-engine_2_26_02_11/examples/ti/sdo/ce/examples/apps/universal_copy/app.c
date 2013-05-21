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
 *  ======== app.c ========
 */
#include <xdc/std.h>
#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/ce/universal/universal.h>
#include <ti/sdo/ce/trace/gt.h>

#include <string.h>  /* for memset */

#include <stdio.h>
#include <stdlib.h>

/*
 * If an XDAIS algorithm _may_ use DMA, buffers provided to it need to be
 * aligned on a cache boundary.
 */

#ifdef CACHE_ENABLED

/*
 * If buffer alignment isn't set on the compiler's command line, set it here
 * to a default value.
 */
#ifndef BUFALIGN
#define BUFALIGN 128
#endif
#else

/* Not a cached system, no buffer alignment constraints */
#define BUFALIGN Memory_DEFAULTALIGNMENT

#endif


#define NSAMPLES    1024  /* must be multiple of 128 for cache/DMA reasons */
#define IFRAMESIZE  (NSAMPLES * sizeof(Int8))  /* raw frame (input) */
#define OFRAMESIZE  (NSAMPLES * sizeof(Int8))  /* decoded frame (output) */
#define MAXVERSIONSIZE 128

static XDAS_Int8 *inBuf;
static XDAS_Int8 *outBuf;
static XDAS_Int8 *versionBuf;   /* acquire optional version from codecs */

static String progName     = "app";
static String universalName  = "universal_copy";
static String engineName   = "universal_copy";

static String usage = "%s: input-file output-file\n";

static Void processLoop(UNIVERSAL_Handle hUniversal, FILE *in, FILE *out);

extern GT_Mask curMask;

/*
 *  ======== createInFileIfMissing ========
 */
static void createInFileIfMissing( char *inFileName )
{
    int i;
    FILE *f = fopen(inFileName, "rb");
    if (f == NULL) {
        printf( "Input file '%s' not found, generating one.\n", inFileName );
        f = fopen( inFileName, "wb" );
        for (i = 0; i < 1024; i++) {
            fwrite( &i, sizeof( i ), 1, f );
        }
    }
    fclose( f );
}

/*
 *  ======== smain ========
 */
Int smain(Int argc, String argv[])
{
    Engine_Handle ce = NULL;
    UNIVERSAL_Handle hUniversal = NULL;
    FILE *in = NULL;
    FILE *out = NULL;
    String inFile, outFile;
    Memory_AllocParams allocParams;

    if (argc <= 1) {
        inFile = "./in.dat";
        outFile = "./out.dat";
        createInFileIfMissing(inFile);
    }
    else if (argc == 3) {
        progName = argv[0];
        inFile = argv[1];
        outFile = argv[2];
    }
    else {
        fprintf(stderr, usage, argv[0]);
        exit(1);
    }

    GT_0trace(curMask, GT_1CLASS, "App-> Application started.\n");

    /* allocate input, encoded, and output buffers */
    allocParams.type = Memory_CONTIGPOOL;
    allocParams.flags = Memory_NONCACHED;
    allocParams.align = BUFALIGN;
    allocParams.seg = 0;

    inBuf = (XDAS_Int8 *)Memory_alloc(IFRAMESIZE, &allocParams);
    outBuf = (XDAS_Int8 *)Memory_alloc(OFRAMESIZE, &allocParams);
    versionBuf = (XDAS_Int8 *)Memory_alloc(MAXVERSIONSIZE, &allocParams);

    if ((inBuf == NULL) || (outBuf == NULL) || (versionBuf == NULL)) {
        goto end;
    }

    /* open file streams for input and output */
    if ((in = fopen(inFile, "rb")) == NULL) {
        printf("App-> ERROR: can't read file %s\n", inFile);
        goto end;
    }
    if ((out = fopen(outFile, "wb")) == NULL) {
        printf("App-> ERROR: can't write to file %s\n", outFile);
        goto end;
    }

    /* reset, load, and start DSP Engine */
    if ((ce = Engine_open(engineName, NULL, NULL)) == NULL) {
        fprintf(stderr, "%s: error: can't open engine %s\n",
            progName, engineName);
        goto end;
    }

    /* allocate and initialize universal alg on the engine */
    hUniversal = UNIVERSAL_create(ce, universalName, NULL);
    if (hUniversal == NULL) {
        printf( "App-> ERROR: can't open codec %s\n", universalName);
        goto end;
    }

    /* use engine to encode, then decode the data */
    processLoop(hUniversal, in, out);

end:
    /* teardown the codec */
    if (hUniversal) {
        UNIVERSAL_delete(hUniversal);
    }

    /* close the engine */
    if (ce) {
        Engine_close(ce);
    }

    /* close the files */
    if (in) {
        fclose(in);
    }
    if (out) {
        fclose(out);
    }

    /* free buffers */
    if (inBuf) {
        Memory_free(inBuf, IFRAMESIZE, &allocParams);
    }
    if (outBuf) {
        Memory_free(outBuf, OFRAMESIZE, &allocParams);
    }
    if (versionBuf) {
        Memory_free(versionBuf, MAXVERSIONSIZE, &allocParams);
    }

    GT_0trace(curMask, GT_1CLASS, "app done.\n");
    return (0);
}

/*
 *  ======== processLoop ========
 */
static Void processLoop(UNIVERSAL_Handle hUniversal, FILE *in, FILE *out)
{
    Int                         n;
    Int32                       status;

    UNIVERSAL_InArgs            universalInArgs;
    UNIVERSAL_OutArgs           universalOutArgs;
    UNIVERSAL_DynamicParams     universalDynParams;
    UNIVERSAL_Status            universalStatus;

    XDM1_BufDesc                universalInBufDesc;
    XDM1_BufDesc                universalOutBufDesc;

    /* initialize bufDescs */
    universalInBufDesc.numBufs = universalOutBufDesc.numBufs = 1;
    universalInBufDesc.descs[0].bufSize = universalOutBufDesc.descs[0].bufSize =
        NSAMPLES;

    universalInBufDesc.descs[0].buf = inBuf;
    universalOutBufDesc.descs[0].buf = outBuf;

    /* initialize all "sized" fields */
    universalInArgs.size    = sizeof(universalInArgs);
    universalOutArgs.size   = sizeof(universalOutArgs);
    universalDynParams.size = sizeof(universalDynParams);
    universalStatus.size    = sizeof(universalStatus);

    /* if the codecs support it, dump their versions */
    universalStatus.data.numBufs = 1;
    universalStatus.data.descs[0].buf = versionBuf;
    universalStatus.data.descs[0].bufSize = MAXVERSIONSIZE;
    universalStatus.data.descs[1].buf = NULL;

    status = UNIVERSAL_control(hUniversal, XDM_GETVERSION, &universalDynParams,
        &universalStatus);
    GT_1trace(curMask, GT_1CLASS, "Alg version:  %s\n",
        (status == UNIVERSAL_EOK ?
            ((char *)universalStatus.data.descs[0].buf) : "[unknown]"));

    /*
     * Read complete frames from in, process them, and write to out.
     */
    for (n = 0; fread(inBuf, IFRAMESIZE, 1, in) == 1; n++) {

#ifdef CACHE_ENABLED
#ifdef xdc_target__isaCompatible_64P
        /*
         *  fread() on this processor is implemented using CCS's stdio, which
         *  is known to write into the cache, not physical memory.  To meet
         *  xDAIS DMA Rule 7, we must writeback the cache into physical
         *  memory.  Also, per DMA Rule 7, we must invalidate the buffer's
         *  cache before providing it to any xDAIS algorithm.
         */
        Memory_cacheWbInv(inBuf, IFRAMESIZE);
#else
#error Unvalidated config - add appropriate fread-related cache maintenance
#endif
        /* Per DMA Rule 7, our output buffer cache lines must be cleaned */
        Memory_cacheInv(outBuf, OFRAMESIZE);
#endif

        GT_1trace(curMask, GT_1CLASS, "App-> Processing frame %d...\n", n);

        /*
         * Transcode the frame.
         *
         * Note, inputID == 0 is an error.  This example doesn't account
         * for the case where 'n + 1' wraps to zero.
         */
        status = UNIVERSAL_process(hUniversal, &universalInBufDesc,
                &universalOutBufDesc, NULL, &universalInArgs, &universalOutArgs);

        GT_2trace(curMask, GT_2CLASS,
            "App-> Alg frame %d process returned - 0x%x)\n", n, status);

        if (status != UNIVERSAL_EOK) {
            GT_3trace(curMask, GT_7CLASS,
                    "App-> Alg frame %d processing FAILED, status = 0x%x, "
                    "extendedError = 0x%x\n", n, status,
                    universalOutArgs.extendedError);
            break;
        }

#ifdef CACHE_ENABLED
        /*
         * Conditionally writeback the processed buf from the previous
         * call.
         */
        if (XDM_ISACCESSMODE_WRITE(universalOutBufDesc.descs[0].accessMask)) {
            Memory_cacheWb(outBuf, OFRAMESIZE);
        }
#endif

        /* write to file */
        fwrite(outBuf, OFRAMESIZE, 1, out);
    }

    GT_1trace(curMask, GT_1CLASS, "%d frames processed\n", n);
}
/*
 *  @(#) ti.sdo.ce.examples.apps.universal_copy; 1, 0, 0,139; 12-2-2010 21:20:54; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

