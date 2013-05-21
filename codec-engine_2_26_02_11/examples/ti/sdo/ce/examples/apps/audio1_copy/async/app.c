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
#include <ti/sdo/ce/audio1/auddec1.h>
#include <ti/sdo/ce/audio1/audenc1.h>
#include <ti/sdo/ce/trace/gt.h>

#include <string.h>  /* for memset */

#include <stdio.h>
#include <stdlib.h>

/*
 * If an xDAIS algorithm _may_ use DMA, buffers provided to it need to be
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

#define NBUFFERS 2
#define UPDATE_INDEX(idx, n) if (++(idx) == (n)) (idx) = 0


/*
 * Audio encoders support 'ancillory data'.  You can enable/disable this
 * example app's use of this feature with this #define.
 */
#define USE_ANCDATA 1

#if USE_ANCDATA
/*
 * For the sake of example, we demonstrate the usage of the audio encoder's
 * Ancillary data field.  The size of this will likely vary.
 */
#define ENCANCBUFSIZE (NSAMPLES * sizeof(Int8))

#endif

/*
 * Assume the audio encoder's inputBitsPerSample is 16.  If we can't assume
 * this, we'd set the value during AUDENC1_create's create params.
 */
#define ENCBITSPERSAMPLE 16

static XDAS_Int8 *inBuf[NBUFFERS];
static XDAS_Int8 *encodedBuf[NBUFFERS + 1];
static XDAS_Int8 *outBuf[NBUFFERS];
static XDAS_Int8 *versionBuf;   /* acquire optional version from codecs */

#if USE_ANCDATA
static XDAS_Int8 *ancBuf[NBUFFERS];
#endif

static AUDDEC1_InArgs              decInArgs[NBUFFERS + 1];
static AUDDEC1_OutArgs             decOutArgs[NBUFFERS];
static AUDDEC1_DynamicParams       decDynParams;
static AUDDEC1_Status              decStatus;

static AUDENC1_InArgs              encInArgs[NBUFFERS];
static AUDENC1_OutArgs             encOutArgs[NBUFFERS + 1];
static AUDENC1_DynamicParams       encDynParams;
static AUDENC1_Status              encStatus;

static XDM1_BufDesc                inBufDesc[NBUFFERS];
static XDM1_BufDesc                encodedBufDesc[NBUFFERS + 1];
static XDM1_BufDesc                outBufDesc[NBUFFERS];

static String progName     = "app";
static String decoderName  = "auddec1_copy:::3";
static String encoderName  = "audenc1_copy:::3";
static String engineName   = "audio1_copy";

static String usage = "%s: input-file output-file\n";

static Void encode_decode(AUDENC1_Handle enc, AUDDEC1_Handle dec, FILE *in,
    FILE *out);

extern GT_Mask curMask;

/*
 *  ======== createInFileIfMissing ========
 */
static void createInFileIfMissing(char *inFileName)
{
    int i;
    FILE *f = fopen(inFileName, "rb");
    if (f == NULL) {
        printf("Input file '%s' not found, generating one.\n", inFileName);
        f = fopen( inFileName, "wb" );
        for (i = 0; i < 1024; i++) {
            fwrite(&i, sizeof(i), 1, f);
        }
    }
    fclose(f);
}

/*
 *  ======== smain ========
 */
Int smain(Int argc, String argv[])
{
    Engine_Handle ce = NULL;
    AUDDEC1_Handle dec = NULL;
    AUDENC1_Handle enc = NULL;
    FILE *in = NULL;
    FILE *out = NULL;
    String inFile, outFile;
    Int i;
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

    /* allocate buffers */
    allocParams.type = Memory_CONTIGPOOL;
    allocParams.flags = Memory_NONCACHED;
    allocParams.align = BUFALIGN;
    allocParams.seg = 0;

    for (i = 0; i < NBUFFERS; i++) {
        inBuf[i] = (XDAS_Int8 *)Memory_alloc(IFRAMESIZE, &allocParams);
        encodedBuf[i] = (XDAS_Int8 *)Memory_alloc(EFRAMESIZE, &allocParams);
        outBuf[i] = (XDAS_Int8 *)Memory_alloc(OFRAMESIZE, &allocParams);
#if USE_ANCDATA
        ancBuf[i] = (XDAS_Int8 *)Memory_alloc(ENCANCBUFSIZE, &allocParams);
        if (ancBuf[i] == NULL) {
            goto end;
        }
#endif

        if ((inBuf[i] == NULL) || (encodedBuf[i] == NULL) ||
            (outBuf[i] == NULL)) {

            goto end;
        }
    }
    /* we need one more encoded buffer than the others */
    encodedBuf[NBUFFERS] = (XDAS_Int8 *)Memory_alloc(EFRAMESIZE,
            &allocParams);
    if (encodedBuf[NBUFFERS] == NULL) {
        goto end;
    }

    versionBuf = (XDAS_Int8 *)Memory_alloc(MAXVERSIONSIZE, &allocParams);
    if (versionBuf == NULL) {
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

    /* allocate and initialize video decoder on the engine */
    dec = AUDDEC1_create(ce, decoderName, NULL);
    if (dec == NULL) {
        printf( "App-> ERROR: can't open codec %s\n", decoderName);
        goto end;
    }

    /* allocate and initialize video encoder on the engine */
    enc = AUDENC1_create(ce, encoderName, NULL);
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
        AUDENC1_delete(enc);
    }
    if (dec) {
        AUDDEC1_delete(dec);
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
    for (i = 0; i < NBUFFERS; i++) {
        if (inBuf[i]) {
            Memory_free(inBuf[i], IFRAMESIZE, &allocParams);
        }
        if (encodedBuf[i]) {
            Memory_free(encodedBuf[i], EFRAMESIZE, &allocParams);
        }
        if (outBuf[i]) {
            Memory_free(outBuf[i], OFRAMESIZE, &allocParams);
        }
#if USE_ANCDATA
        if (ancBuf[i]) {
            Memory_free(ancBuf[i], ENCANCBUFSIZE, &allocParams);
        }
#endif
    }
    if (encodedBuf[NBUFFERS]) {
        Memory_free(encodedBuf[NBUFFERS], EFRAMESIZE, &allocParams);
    }
    if (versionBuf) {
        Memory_free(versionBuf, MAXVERSIONSIZE, &allocParams);
    }

    GT_0trace(curMask, GT_1CLASS, "app done.\n");
    return (0);
}

Int32 encodeIssue(AUDENC1_Handle enc, int in, int out)
{
    Int32 status;

#if USE_ANCDATA
    /* we send the same data as inBuf as ancillory data */
    memcpy(ancBuf[in], inBuf[in], ENCANCBUFSIZE);
#endif

    /* Deal with cache issues, if necessary */
#ifdef CACHE_ENABLED
#ifdef xdc_target__isaCompatible_64P
    /*
     *  fread() on this processor is implemented using CCS's stdio, which
     *  is known to write into the cache, not physical memory.  To meet
     *  xDAIS DMA Rule 7, we must writeback the cache into physical
     *  memory.  Also, per DMA Rule 7, we must invalidate the buffer's
     *  cache before providing it to any xDAIS algorithm.
     */
    Memory_cacheWbInv(inBuf[in], IFRAMESIZE);
#else
#error Unvalidated config - add appropriate fread-related cache maintenance
#endif

#if USE_ANCDATA
    /* ancBuf is an inBuf, filled via memcpy (i.e. CPU writes) */
    Memory_cacheWbInv(ancBuf[in], ENCANCBUFSIZE);
#endif

    /* Per DMA Rule 7, our output buffer cache lines must be cleaned */
    Memory_cacheInv(encodedBuf[out], EFRAMESIZE);
#endif

    GT_4trace(curMask, GT_1CLASS, "App-> inBuf[%d]=%#x, outBuf[%d]=%#x\n",
              in, inBufDesc[in].descs[0].buf,
              out, encodedBufDesc[out].descs[0].buf);

    /*
     * Encode the frame.  Note that .numInSamples is the number of
     * _samples_ not bytes.  IFRAMESIZE is in 8-bit bytes, so there's a
     * little math here to get .numInSamples right.
     */
    encInArgs[in].numInSamples =
        (IFRAMESIZE / (ENCBITSPERSAMPLE / (8 /* bits per byte */)));

    status = AUDENC1_processAsync(enc, &inBufDesc[in],
                                  &encodedBufDesc[out],
                                  &encInArgs[in],
                                  &encOutArgs[out]);

    GT_1trace(curMask, GT_2CLASS,
              "App-> Encoder processAsync returned 0x%x\n", status);
    if (status != AUDENC1_EOK) {
        GT_0trace(curMask, GT_7CLASS, "App-> Encodcer processing FAILED\n");
    }

    return status;
}

Int32 encodeReclaim(AUDENC1_Handle enc, int in, int out)
{
    Int32 status;

    GT_4trace(curMask, GT_1CLASS, "App-> inBuf[%d]=%#x, outBuf[%d]=%#x\n",
              in, inBufDesc[in].descs[0].buf,
              out, encodedBufDesc[out].descs[0].buf);

    status = AUDENC1_processWait(enc, &inBufDesc[in],
                                 &encodedBufDesc[out],
                                 &encInArgs[in],
                                 &encOutArgs[out],
                                 AUDENC1_FOREVER);

#ifdef CACHE_ENABLED
    /*
     * Since encodedBuf is an inBuf to the next process call, we
     * must invalidate it, to clean buffer lines.
     */
    Memory_cacheWbInv(encodedBuf[out], EFRAMESIZE);
#endif

    GT_1trace(curMask, GT_2CLASS,
              "App-> Encoder processWait returned 0x%x\n", status);
    if (status != AUDENC1_EOK) {
        GT_1trace(curMask, GT_7CLASS,
                  "App-> Encodcer processing FAILED, extendedError = 0x%x\n",
                  encOutArgs[out].extendedError);
    }

    return status;
}

Int32 decodeIssue(AUDDEC1_Handle dec, int in, int out)
{
    Int32 status;

#ifdef CACHE_ENABLED
    /* Per DMA Rule 7, our output buffer cache lines must be cleaned */
    Memory_cacheInv(outBuf[out], OFRAMESIZE);
#endif

    /* decode the frame */
    decInArgs[in].numBytes = EFRAMESIZE;

    GT_4trace(curMask, GT_1CLASS, "App-> inBuf[%d]=%#x, outBuf[%d]=%#x\n",
              in, encodedBufDesc[in].descs[0].buf,
              out, outBufDesc[out].descs[0].buf);

    status = AUDDEC1_processAsync(dec, &encodedBufDesc[in],
                                  &outBufDesc[out],
                                  &decInArgs[in],
                                  &decOutArgs[out]);

    GT_1trace(curMask, GT_2CLASS,
              "App-> Decoder processAsync returned 0x%x\n", status);
    if (status != AUDDEC1_EOK) {
        GT_0trace(curMask, GT_7CLASS, "App-> Decoder processing FAILED\n");
    }

    return status;
}

Int32 decodeReclaim(AUDDEC1_Handle dec, int in, int out)
{
    Int32 status;

    GT_4trace(curMask, GT_1CLASS, "App-> inBuf[%d]=%#x, outBuf[%d]=%#x\n",
              in, encodedBufDesc[in].descs[0].buf,
              out, outBufDesc[out].descs[0].buf);

    status = AUDDEC1_processWait(dec, &encodedBufDesc[in],
                                 &outBufDesc[out],
                                 &decInArgs[in],
                                 &decOutArgs[out],
                                 AUDDEC1_FOREVER);

#ifdef CACHE_ENABLED
    /* Writeback the outBuf. */
    Memory_cacheWb(outBuf[out], OFRAMESIZE);
#endif

    GT_1trace(curMask, GT_2CLASS,
              "App-> Decoder processWait returned 0x%x\n", status);
    if (status != AUDDEC1_EOK) {
        GT_1trace(curMask, GT_7CLASS,
                  "App-> Decoder processing FAILED, extendedError = 0x%x\n",
                  decOutArgs[out].extendedError);
    }

    return status;
}

/*
 *  ======== encode_decode ========
 */
static Void encode_decode(AUDENC1_Handle enc, AUDDEC1_Handle dec, FILE *in,
    FILE *out)
{
    Bool                        last;
    Int                         i;
    Int                         n;
    Int32                       status;
    Int                         decProcessIn = 0;
    Int                         decWaitIn = 0;
    Int                         decProcessOut = 0;
    Int                         decWaitOut = 0;
    Int                         encProcessIn = 0;
    Int                         encProcessOut = 0;

    for (i = 0; i < NBUFFERS; i++) {
        inBufDesc[i].descs[0].buf = inBuf[i];
        outBufDesc[i].descs[0].buf = outBuf[i];
        encodedBufDesc[i].descs[0].buf = encodedBuf[i];
        inBufDesc[i].numBufs = encodedBufDesc[i].numBufs =
          outBufDesc[i].numBufs = 1;
        inBufDesc[i].descs[0].bufSize = encodedBufDesc[i].descs[0].bufSize =
          outBufDesc[i].descs[0].bufSize = NSAMPLES;

        /* initialize all "sized" fields */
        encInArgs[i].size    = sizeof(encInArgs[i]);
        decInArgs[i].size    = sizeof(decInArgs[i]);
        encOutArgs[i].size   = sizeof(encOutArgs[i]);
        decOutArgs[i].size   = sizeof(decOutArgs[i]);

        /* ancillary data to encode */
#if USE_ANCDATA
        encInArgs[i].ancData.buf = ancBuf[i];
        encInArgs[i].ancData.bufSize = ENCANCBUFSIZE;
#else
        /* Be sure to initialize these to NULL! */
        encInArgs[i].ancData.buf = NULL;
        encInArgs[i].ancData.bufSize = 0;
#endif
    }
    encodedBufDesc[NBUFFERS].descs[0].buf = encodedBuf[NBUFFERS];
    encodedBufDesc[NBUFFERS].numBufs = 1;
    encodedBufDesc[NBUFFERS].descs[0].bufSize = NSAMPLES;
    encOutArgs[NBUFFERS].size = sizeof(encOutArgs[NBUFFERS]);
    decInArgs[NBUFFERS].size = sizeof(decInArgs[NBUFFERS]);

    encDynParams.size = sizeof(encDynParams);
    decDynParams.size = sizeof(decDynParams);
    encStatus.size    = sizeof(encStatus);
    decStatus.size    = sizeof(decStatus);

    /*
     * Note that we use versionBuf in both the encoder and decoder.  In this
     * application, this is okay, as there is always only one user of
     * the buffer.  Not all applications can make this assumption.
     */
    encStatus.data.buf     = decStatus.data.buf     = versionBuf;
    encStatus.data.bufSize = decStatus.data.bufSize = MAXVERSIONSIZE;

    /* if the codecs support it, dump their versions */
    status = AUDDEC1_control(dec, XDM_GETVERSION, &decDynParams, &decStatus);
    GT_1trace(curMask, GT_1CLASS, "Decoder version:  %s\n",
        (status == AUDDEC1_EOK ? ((char *)decStatus.data.buf) : "[unknown]"));

    status = AUDENC1_control(enc, XDM_GETVERSION, &encDynParams, &encStatus);
    GT_1trace(curMask, GT_1CLASS, "Encoder version:  %s\n",
        (status == AUDENC1_EOK ? ((char *)encStatus.data.buf) : "[unknown]"));

    /*
     * This app expects the encoder to accept 1 buf in and get 1 buf out,
     * and the buf sizes of the in and out buffer must be able to handle
     * NSAMPLES bytes of data.
     */
    status = AUDENC1_control(enc, XDM_GETBUFINFO, &encDynParams, &encStatus);
    if (status != AUDENC1_EOK) {
        /* failure, report error and exit */
        GT_1trace(curMask, GT_7CLASS, "encode control status = %ld\n", status);
        return;
    }

    /* Validate this encoder codec will meet our buffer requirements */
    if ((inBufDesc[0].numBufs < encStatus.bufInfo.minNumInBufs) ||
        (IFRAMESIZE < encStatus.bufInfo.minInBufSize[0]) ||
        (encodedBufDesc[0].numBufs < encStatus.bufInfo.minNumOutBufs) ||
        (EFRAMESIZE < encStatus.bufInfo.minOutBufSize[0])) {

        /* failure, report error and exit */
        GT_0trace(curMask, GT_7CLASS,
            "Error:  encoder codec feature conflict\n");
        return;
    }

    status = AUDDEC1_control(dec, XDM_GETBUFINFO, &decDynParams, &decStatus);
    if (status != AUDDEC1_EOK) {
        /* failure, report error and exit */
        GT_1trace(curMask, GT_7CLASS, "decode control status = %ld\n", status);
        return;
    }

    /* Validate this decoder codec will meet our buffer requirements */
    if ((encodedBufDesc[0].numBufs < decStatus.bufInfo.minNumInBufs) ||
        (EFRAMESIZE < decStatus.bufInfo.minInBufSize[0]) ||
        (outBufDesc[0].numBufs < decStatus.bufInfo.minNumOutBufs) ||
        (OFRAMESIZE < decStatus.bufInfo.minOutBufSize[0])) {

        /* failure, report error and exit */
        GT_0trace(curMask, GT_7CLASS,
            "App-> ERROR: decoder does not meet buffer requirements.\n");
        return;
    }

    /*
     * Read complete frames from in, encode, decode, and write to out.
     */
    for (n = 0; fread(inBuf[encProcessIn], IFRAMESIZE, 1, in) == 1; n++) {

        GT_1trace(curMask, GT_1CLASS, "App-> Processing encode frame %d...\n",
                  n);
        status = encodeIssue(enc, encProcessIn, encProcessOut);
        if (status != AUDENC1_EOK) {
            goto done;
        }

        UPDATE_INDEX(encProcessIn, NBUFFERS);
        UPDATE_INDEX(encProcessOut, NBUFFERS + 1);

        if (n == 0) {
            /*
             *  "Poor man's prologue" - need to feed encoder two buffers of
             *  input before reclaiming encoded data.
             */
            continue;
        }

        GT_1trace(curMask, GT_1CLASS, "App-> Waiting for encoded frame %d...\n",
                  n - 1);
        status = encodeReclaim(enc, decProcessOut, decProcessIn);
        if (status != AUDENC1_EOK) {
            goto done;
        }

        GT_1trace(curMask, GT_1CLASS, "App-> Processing decode frame %d...\n",
                  n - 1);
        status = decodeIssue(dec, decProcessIn, decProcessOut);
        if (status != AUDDEC1_EOK) {
            goto done;
        }

        UPDATE_INDEX(decProcessIn, NBUFFERS + 1);
        UPDATE_INDEX(decProcessOut, NBUFFERS);

        if (n == 1) {
            /*
             *  "Poor man's prologue" - need to feed decoder two buffers of
             *  input before reclaiming decoded data.
             */
            continue;
        }

        GT_1trace(curMask, GT_1CLASS, "App-> Waiting for decoded frame %d...\n",
                  n - 2);
        status = decodeReclaim(dec, decWaitIn, decWaitOut);
        if (status != AUDDEC1_EOK) {
            goto done;
        }

        GT_2trace(curMask, GT_1CLASS, "App-> Writing outBuf[%d]=%#x\n",
                  decWaitOut, outBuf[decWaitOut]);

        /* write to file */
        fwrite(outBuf[decWaitOut], OFRAMESIZE, 1, out);

        UPDATE_INDEX(decWaitIn, NBUFFERS + 1);
        UPDATE_INDEX(decWaitOut, NBUFFERS);
    }

    /*
     *  Due to the buffering achieved with async calls, at this point we still
     *  need to:
     *     - drain one buffer from the encoder
     *     - feed encoded buffer to the decoder
     *     - drain two buffers from the decoder
     *     - write decoded buffers to file
     */
    GT_1trace(curMask, GT_1CLASS, "App-> Waiting for encoded frame %d...\n",
              n - 1);
    status = encodeReclaim(enc, decProcessOut, decProcessIn);
    if (status != AUDENC1_EOK) {
        goto done;
    }

    /* decode the frame */
    GT_1trace(curMask, GT_1CLASS, "App-> Processing decode frame %d...\n",
              n - 1);
    status = decodeIssue(dec, decProcessIn, decProcessOut);
    if (status != AUDDEC1_EOK) {
        goto done;
    }

    UPDATE_INDEX(decProcessIn, NBUFFERS + 1);
    UPDATE_INDEX(decProcessOut, NBUFFERS);

    last = TRUE;

last_frame:
    GT_1trace(curMask, GT_1CLASS, "App-> Waiting for decoded frame %d...\n",
              n - 2);
    status = decodeReclaim(dec, decWaitIn, decWaitOut);
    if (status != AUDDEC1_EOK) {
        goto done;
    }

    GT_2trace(curMask, GT_1CLASS, "App-> Writing outBuf[%d]=%#x\n",
              decWaitOut, outBuf[decWaitOut]);

    /* write to file */
    fwrite(outBuf[decWaitOut], OFRAMESIZE, 1, out);

    UPDATE_INDEX(decWaitIn, NBUFFERS + 1);
    UPDATE_INDEX(decWaitOut, NBUFFERS);

    if (last) {
        /*
         *  "Poor man's epilogue" - need to reclaim and write last
         *  decoded buffer.
         */
        n++;
        last = FALSE;
        goto last_frame;
    }

done:
    GT_1trace(curMask, GT_1CLASS, "%d frames encoded/decoded\n", n - 2);
}

/*
 *  @(#) ti.sdo.ce.examples.apps.audio1_copy.async; 1, 0, 0,168; 12-2-2010 21:19:14; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

