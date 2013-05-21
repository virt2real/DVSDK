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
#include <ti/sdo/ce/video2/split/viddec2.h>
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
#define EFRAMESIZE  (NSAMPLES * sizeof(Int8))  /* encoded frame */
#define OFRAMESIZE  (NSAMPLES * sizeof(Int8))  /* decoded frame (output) */
#define MAXVERSIONSIZE 128
#define MAXCONTEXTSIZE 4096

static XDAS_Int8 *inBuf;
static XDAS_Int8 *algContext;
static XDAS_Int8 *outBuf;
static XDAS_Int8 *versionBuf;   /* acquire optional version from codecs */

static String decoderFrontName  = "viddec2front_copy";
static String decoderBackName  = "viddec2back_copy";
static String engineName   = "viddec2split_copy";

static String usage = "%s: input-file output-file\n";

static Void decode(VIDDEC2FRONT_Handle front, VIDDEC2BACK_Handle back, FILE *in,
    FILE *out);

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
    VIDDEC2FRONT_Handle front = NULL;
    VIDDEC2BACK_Handle back = NULL;
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
        inFile = argv[1];
        outFile = argv[2];
    }
    else {
        GT_1trace(curMask, GT_7CLASS, usage, argv[0]);
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
    algContext = (XDAS_Int8 *)Memory_alloc(MAXCONTEXTSIZE, &allocParams);
    versionBuf = (XDAS_Int8 *)Memory_alloc(MAXVERSIONSIZE, &allocParams);

    if ((inBuf == NULL) || (algContext == NULL) || (outBuf == NULL) ||
            (versionBuf == NULL)) {

        goto end;
    }

    /* open file streams for input and output */
    if ((in = fopen(inFile, "rb")) == NULL) {
        GT_1trace(curMask, GT_7CLASS, "App-> ERROR: can't read file %s\n",
            inFile);
        goto end;
    }
    if ((out = fopen(outFile, "wb")) == NULL) {
        GT_1trace(curMask, GT_7CLASS, "App-> ERROR: can't write to file %s\n",
            outFile);
        goto end;
    }

    /* reset, load, and start DSP Engine */
    if ((ce = Engine_open(engineName, NULL, NULL)) == NULL) {
        GT_1trace(curMask, GT_7CLASS, "App-> ERROR: can't open engine %s\n",
            engineName);
        goto end;
    }

    /* allocate and initialize video decoder FRONT part on the engine */
    front = VIDDEC2FRONT_create(ce, decoderFrontName, NULL);
    if (front == NULL) {
        GT_1trace(curMask, GT_7CLASS,  "App-> ERROR: can't open codec %s\n",
            decoderFrontName);
        goto end;
    }

    /* allocate and initialize video decoder BACK on the engine */
    back = VIDDEC2BACK_create(ce, decoderBackName, NULL);
    if (back == NULL) {
        GT_1trace(curMask, GT_7CLASS, "App-> ERROR: can't open codec %s\n",
            decoderBackName);
        goto end;
    }

    /* use engine to encode, then decode the data */
    decode(front, back, in, out);

end:
    /* teardown the codecs */
    if (front) {
        VIDDEC2FRONT_delete(front);
    }
    if (back) {
        VIDDEC2BACK_delete(back);
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
    if (algContext) {
        Memory_free(algContext, MAXCONTEXTSIZE, &allocParams);
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
 *  ======== decode ========
 */
static Void decode(VIDDEC2FRONT_Handle front, VIDDEC2BACK_Handle back, FILE *in,
    FILE *out)
{
    Int                         n;
    Int32                       status;

    VIDDEC2_InArgs              frontInArgs;
    VIDDEC2FRONT_OutArgs        frontOutArgs;
    VIDDEC2_DynamicParams       frontDynParams;
    VIDDEC2FRONT_Status         frontStatus;

    VIDDEC2_OutArgs             backOutArgs;

    XDM_Context                 context;

    /* initialize all "sized" fields */
    frontInArgs.size            = sizeof(frontInArgs);
    frontOutArgs.size           = sizeof(frontOutArgs);
    backOutArgs.size            = sizeof(backOutArgs);
    frontDynParams.size         = sizeof(frontDynParams);
    frontStatus.fullStatus.size = sizeof(frontStatus.fullStatus);

    /* First, identify the context size required by this split codec.
     *
     * Note that we assert that no intermediate buffers are required for this
     * codec.  We also only support algContexts smaller than MAXCONTEXTSIZE.
     * Not all applications can make this assumption.
     */
    status = VIDDEC2FRONT_control(front, XDM_GETCONTEXTINFO, &frontDynParams,
            NULL, &frontStatus);

    if (status == VIDDEC2_EOK) {
        GT_assert(curMask, frontStatus.nextPartRequiredFlag == XDAS_FALSE);
        GT_assert(curMask, frontStatus.contextInfo.minContextSize <=
                MAXCONTEXTSIZE);
        GT_assert(curMask,
                frontStatus.contextInfo.minIntermediateBufSizes[0] == 0);
    }

    /*
     * Get the codec's version.
     *
     * Note that we assert the FRONT part can return this value without
     * requiring a BACK call.  Not all applications can make this assumption.
     */
    frontStatus.fullStatus.size = sizeof(frontStatus.fullStatus);
    context.numOutBufs = 1;
    context.outBufs[0].bufSize = MAXVERSIONSIZE;
    context.outBufs[0].buf = versionBuf;

    /*
     * Remember to NULL-initialize unused buffer pointers as they'll attempt
     * to be translated if the codec resides on another processor!
     */
    context.algContext.bufSize = 0;
    context.algContext.buf = NULL;
    context.numInOutBufs = context.numInBufs = 0;
    context.inOutBufs[0].buf = context.inBufs[0].buf = NULL;
    context.inOutBufs[0].bufSize = context.inBufs[0].bufSize = 0;

    context.intermediateBufs[0].buf = NULL;
    context.intermediateBufs[0].bufSize = 0;


    /* if the codec supports it, dump its version */
    status = VIDDEC2FRONT_control(front, XDM_GETVERSION, &frontDynParams,
        &context, &frontStatus);

    if (status == VIDDEC2_EOK) {
        GT_assert(curMask, frontStatus.nextPartRequiredFlag == XDAS_FALSE);
    }

    GT_1trace(curMask, GT_1CLASS, "Decoder version:  %s\n",
            (status == VIDDEC2_EOK ?
                ((char *)context.outBufs[0].buf) : "[unknown]"));

    /*
     * This app expects the encoder to provide 1 buf in and get 1 buf out,
     * and the buf sizes of the in and out buffer must be able to handle
     * NSAMPLES bytes of data.
     */
    frontStatus.fullStatus.size = sizeof(frontStatus.fullStatus);
    status = VIDDEC2FRONT_control(front, XDM_GETSTATUS, &frontDynParams, NULL,
        &frontStatus);
    if (status != VIDDEC2_EOK) {
        /* failure, report error and exit */
        GT_1trace(curMask, GT_7CLASS, "front control status = %ld\n", status);
        return;
    }
    else {
        /*
         * Again, this app assumes the codec's FRONT part can handle all
         * control() calls completely.
         */
        GT_assert(curMask, frontStatus.nextPartRequiredFlag == XDAS_FALSE);
    }


    /* Ensure this codec will meet our expected buffer use case (1 in, 1 out) */
    if ((1 < frontStatus.fullStatus.bufInfo.minNumInBufs) ||
        (IFRAMESIZE < frontStatus.fullStatus.bufInfo.minInBufSize[0]) ||
        (1 < frontStatus.fullStatus.bufInfo.minNumOutBufs) ||
        (OFRAMESIZE < frontStatus.fullStatus.bufInfo.minOutBufSize[0])) {

        /* failure, report error and exit */
        GT_0trace(curMask, GT_7CLASS,
            "Error:  decoder codec feature conflict\n");
        return;
    }

    /* prepare for process() loop */
    context.numInBufs = 1;
    context.inBufs[0].bufSize = NSAMPLES;
    context.inBufs[0].buf = inBuf;

    context.numOutBufs = 1;
    context.outBufs[0].bufSize = NSAMPLES;
    context.outBufs[0].buf = outBuf;

    context.algContext.bufSize = MAXCONTEXTSIZE;
    context.algContext.buf = algContext;

    /*
     * Remember to NULL-initialize unused buffer pointers as they'll attempt
     * to be translated if the codec resides on another processor!
     */
    context.numInOutBufs = 0;
    context.inOutBufs[0].buf = NULL;
    context.inOutBufs[0].bufSize = 0;

    context.intermediateBufs[0].buf = NULL;
    context.intermediateBufs[0].bufSize = 0;

    /*
     * Read complete frames from in, encode, decode, and write to out.
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
         * Decode the frame.
         *
         * Note, inputID == 0 is an error.  This example doesn't account
         * for the case where 'n + 1' wraps to zero.
         */
        frontInArgs.numBytes = IFRAMESIZE;
        frontInArgs.inputID = n + 1;
        status = VIDDEC2FRONT_process(front, &frontInArgs, &context,
                &frontOutArgs);

        GT_2trace(curMask, GT_2CLASS,
            "App-> FRONT frame %d process returned - 0x%x)\n", n, status);

        if (status != VIDDEC2_EOK) {
            GT_3trace(curMask, GT_7CLASS, "App-> FRONT frame %d processing "
                "FAILED, status=0x%x (extErr=0x%x)\n",
                n, status, frontOutArgs.extendedError);
            break;
        }

#ifdef CACHE_ENABLED
        /* TODO - handle caching of in, out, and inout buffers */
#endif

        /* call BACK */
        status = VIDDEC2BACK_process(back, &context, &backOutArgs);

        GT_2trace(curMask, GT_2CLASS,
            "App-> BACK frame %d process returned - 0x%x)\n", n, status);

        if (status != VIDDEC2_EOK) {
            GT_3trace(curMask, GT_7CLASS, "App-> BACK frame %d processing "
                "FAILED, status=0x%x (extErr=0x%x)\n",
                n, status, frontOutArgs.extendedError);
            break;
        }

        /* again, validate our assumption that we don't get out-of-order bufs */
        if (backOutArgs.decodedBufs.bufDesc[0].buf != outBuf) {
            GT_0trace(curMask, GT_7CLASS,
                "App-> Internal error.  Unsupported decoder\n");
            break;
        }

#ifdef CACHE_ENABLED
        /* Conditionally writeback outBuf */
        if (XDM_ISACCESSMODE_WRITE(
                backOutArgs.decodedBufs.bufDesc[0].accessMask)) {
            Memory_cacheWb(backOutArgs.decodedBufs.bufDesc[0].buf, OFRAMESIZE);
        }
#endif

        /* write to file */
        fwrite(backOutArgs.decodedBufs.bufDesc[0].buf, OFRAMESIZE, 1, out);
    }

    GT_1trace(curMask, GT_1CLASS, "%d frames decoded\n", n);
}
/*
 *  @(#) ti.sdo.ce.examples.apps.video2split_copy; 1, 0, 0,163; 12-2-2010 21:21:18; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

