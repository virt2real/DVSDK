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
 *    This example communicates with a PCM speech encoder/decoder pair.
 */
#include <xdc/std.h>
#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/ce/speech1/sphdec1.h>
#include <ti/sdo/ce/speech1/sphenc1.h>
#include <ti/xdais/dm/ispeech1_pcm.h>
#include <ti/sdo/ce/trace/gt.h>

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

static XDAS_Int8 *inBuf;
static XDAS_Int8 *encodedBuf;
static XDAS_Int8 *outBuf;
static XDAS_Int8 *versionBuf;   /* acquire optional version from codecs */

static String progName     = "app";

static String decoderName  = "mysphdec1_copy";
static String encoderName  = "sphenc1_copy";
static String engineName   = "speech1_copy";

static String usage = "%s: input-file output-file\n";

static Void encode_decode(SPHENC1_Handle enc, SPHDEC1_Handle dec, FILE *in,
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
    SPHDEC1_Handle dec = NULL;
    SPHENC1_Handle enc = NULL;
    SPHDEC1_Params decParams;
    SPHENC1_Params encParams;

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

    /* allocate input, encoded, output, and version buffers */
    allocParams.type = Memory_CONTIGPOOL;
    allocParams.flags = Memory_NONCACHED;
    allocParams.align = BUFALIGN;
    allocParams.seg = 0;

    inBuf = (XDAS_Int8 *)Memory_alloc(IFRAMESIZE, &allocParams);
    encodedBuf = (XDAS_Int8 *)Memory_alloc(EFRAMESIZE, &allocParams);
    outBuf = (XDAS_Int8 *)Memory_alloc(OFRAMESIZE, &allocParams);
    versionBuf = (XDAS_Int8 *)Memory_alloc(MAXVERSIONSIZE, &allocParams);

    if ((inBuf == NULL) || (encodedBuf == NULL) || (outBuf == NULL) ||
        (versionBuf == NULL)) {

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

    /* allocate and initialize decoder in the engine */
    decParams.size = sizeof(decParams);
    decParams.compandingLaw = ISPEECH1_PCM_COMPAND_ULAW;
    /* no other create params are meaningful for PCM decoders */

    dec = SPHDEC1_create(ce, decoderName, &decParams);
    if (dec == NULL) {
        printf( "App-> ERROR: can't open codec %s\n", decoderName);
        goto end;
    }

    /* allocate and initialize encoder in the engine */
    encParams.size = sizeof(encParams);
    encParams.frameSize = IFRAMESIZE;
    encParams.compandingLaw = ISPEECH1_PCM_COMPAND_ULAW;
    /* no other create params are meaningful for PCM encoders */

    enc = SPHENC1_create(ce, encoderName, &encParams);
    if (enc == NULL) {
        fprintf(stderr, "%s: error: can't open codec %s\n",
            progName, encoderName);
        goto end;
    }

    /* use engine to encode, then decode the data */
    encode_decode(enc, dec, in, out);

end:
    /* teardown the codecs */
    if (enc) {
        SPHENC1_delete(enc);
    }
    if (dec) {
        SPHDEC1_delete(dec);
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
    if (encodedBuf) {
        Memory_free(encodedBuf, EFRAMESIZE, &allocParams);
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
 *  ======== encode_decode ========
 */
static Void encode_decode(SPHENC1_Handle enc, SPHDEC1_Handle dec, FILE *in,
    FILE *out)
{
    Int                         n;
    Int32                       status;

    SPHDEC1_InArgs              decInArgs;
    SPHDEC1_OutArgs             decOutArgs;
    SPHDEC1_DynamicParams       decDynParams;
    SPHDEC1_Status              decStatus;

    SPHENC1_InArgs              encInArgs;
    SPHENC1_OutArgs             encOutArgs;
    SPHENC1_DynamicParams       encDynParams;
    SPHENC1_Status              encStatus;

    XDM1_SingleBufDesc          inBufDesc;
    XDM1_SingleBufDesc          encodedBufDesc;
    XDM1_SingleBufDesc          outBufDesc;

    /* init buffer descriptor settings that don't change during processing */
    inBufDesc.bufSize = IFRAMESIZE;
    inBufDesc.buf = inBuf;
    encodedBufDesc.buf = encodedBuf;
    outBufDesc.buf = outBuf;

    /* initialize all "sized" fields */
    encInArgs.size    = sizeof(encInArgs);
    decInArgs.size    = sizeof(decInArgs);
    encOutArgs.size   = sizeof(encOutArgs);
    decOutArgs.size   = sizeof(decOutArgs);
    encDynParams.size = sizeof(encDynParams);
    decDynParams.size = sizeof(decDynParams);
    encStatus.size    = sizeof(encStatus);
    decStatus.size    = sizeof(decStatus);

    /*
     * We never use the decoder or encoder's inArgs.data fields, so
     * initialize them NULL.
     */
    decInArgs.data.buf = NULL;
    encInArgs.data.buf = NULL;

    /*
     * Note that we use versionBuf in both the encoder and decoder.  In this
     * application, this is okay, as there is always only one user of
     * the buffer.  Not all applications can make this assumption.
     */
    encStatus.data.buf     = decStatus.data.buf     = versionBuf;
    encStatus.data.bufSize = decStatus.data.bufSize = MAXVERSIONSIZE;

    /* if the codecs support it, dump their versions */
    status = SPHDEC1_control(dec, XDM_GETVERSION, &decDynParams, &decStatus);
    GT_1trace(curMask, GT_1CLASS, "Decoder version:  %s\n",
        (status == SPHDEC1_EOK ? ((char *)decStatus.data.buf) : "[unknown]"));

    status = SPHENC1_control(enc, XDM_GETVERSION, &encDynParams, &encStatus);
    GT_1trace(curMask, GT_1CLASS, "Encoder version:  %s\n",
        (status == SPHENC1_EOK ? ((char *)encStatus.data.buf) : "[unknown]"));

    /*
     * This app expects the encoder to provide 1 buf in and get 1 buf out,
     * and the buf sizes of the in and out buffer must be able to handle
     * NSAMPLES bytes of data.
     */
    status = SPHENC1_control(enc, XDM_GETSTATUS, &encDynParams, &encStatus);
    if (status != SPHENC1_EOK) {
        /* failure, report error and exit */
        GT_1trace(curMask, GT_7CLASS, "encode control status = %ld\n", status);
        return;
    }

    /* Validate this encoder codec will meet our buffer requirements */
    if ((IFRAMESIZE < encStatus.bufInfo.minInBufSize[0]) ||
        (EFRAMESIZE < encStatus.bufInfo.minOutBufSize[0])) {

        /* failure, report error and exit */
        GT_0trace(curMask, GT_7CLASS,
            "Error:  encoder codec feature conflict\n");
        return;
    }

    status = SPHDEC1_control(dec, XDM_GETSTATUS, &decDynParams, &decStatus);
    if (status != SPHDEC1_EOK) {
        /* failure, report error and exit */
        GT_1trace(curMask, GT_7CLASS, "decode control status = %ld\n", status);
        return;
    }

    /* Validate this decoder codec will meet our buffer requirements */
    if ((EFRAMESIZE < decStatus.bufInfo.minInBufSize[0]) ||
        (OFRAMESIZE < decStatus.bufInfo.minOutBufSize[0])) {

        /* failure, report error and exit */
        GT_0trace(curMask, GT_7CLASS,
            "App-> ERROR: decoder does not meet buffer requirements.\n");
        return;
    }

    /*
     * Read complete frames from in, encode, decode, and write to out.
     */
    for (n = 0; fread(inBuf, IFRAMESIZE, 1, in) == 1; n++) {

        /* reset potentially changed 'output' buffers to actual buf sizes. */
        encodedBufDesc.bufSize = EFRAMESIZE;
        outBufDesc.bufSize = OFRAMESIZE;


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
        Memory_cacheInv(encodedBuf, encodedBufDesc.bufSize);
#endif

        GT_1trace(curMask, GT_1CLASS, "App-> Processing frame %d...\n", n);

        /* encode the frame */
        status = SPHENC1_process(enc, &inBufDesc, &encodedBufDesc, &encInArgs,
            &encOutArgs);

        GT_2trace(curMask, GT_2CLASS,
            "App-> Encoder frame %d process returned - 0x%x)\n",
            n, status);

#ifdef CACHE_ENABLED
        /* Writeback this outBuf from the previous call.  Also, as encodedBuf
         * is an inBuf to the next process call, we must invalidate it also, to
         * clean buffer lines.
         */
        Memory_cacheWbInv(encodedBuf, encodedBufDesc.bufSize);

        /* Per DMA Rule 7, our output buffer cache lines must be cleaned */
        Memory_cacheInv(outBuf, outBufDesc.bufSize);
#endif

        if (status != SPHENC1_EOK) {
            GT_3trace(curMask, GT_7CLASS,
                "App-> Encoder frame %d processing FAILED, status = 0x%x, "
                "extendedError = 0x%x\n", n, status, encOutArgs.extendedError);
            break;
        }

        /* decode the frame */
        status = SPHDEC1_process(dec, &encodedBufDesc, &outBufDesc, &decInArgs,
           &decOutArgs);

        GT_2trace(curMask, GT_2CLASS,
            "App-> Decoder frame %d process returned - 0x%x)\n",
            n, status);

        if (status != SPHDEC1_EOK) {
            GT_3trace(curMask, GT_7CLASS,
                "App-> Decoder frame %d processing FAILED, status = 0x%x, "
                "extendedError = 0x%x\n", n, status, decOutArgs.extendedError);
            break;
        }

#ifdef CACHE_ENABLED
        /* Writeback the outBuf. */
        Memory_cacheWb(outBuf, outBufDesc.bufSize);
#endif
        /* write to file */
        fwrite(outBuf, outBufDesc.bufSize, 1, out);
    }

    GT_1trace(curMask, GT_1CLASS, "%d frames encoded/decoded\n", n);
}
/*
 *  @(#) ti.sdo.ce.examples.apps.speech1_copy; 1, 0, 0,263; 12-2-2010 21:20:22; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

