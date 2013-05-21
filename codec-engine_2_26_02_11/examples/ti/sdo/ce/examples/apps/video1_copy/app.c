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
#include <ti/sdo/ce/video1/viddec1.h>
#include <ti/sdo/ce/video1/videnc1.h>
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

static XDAS_Int8 *inBuf;
static XDAS_Int8 *encodedBuf;
static XDAS_Int8 *outBuf;
static XDAS_Int8 *versionBuf;   /* acquire optional version from codecs */

static String progName     = "app";
static String decoderName  = "viddec1_copy";
static String encoderName  = "videnc1_copy";
static String engineName   = "video1_copy";

static String usage = "%s: input-file output-file\n";

static Void encode_decode(VIDENC1_Handle enc, VIDDEC1_Handle dec, FILE *in,
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
    VIDDEC1_Handle dec = NULL;
    VIDENC1_Handle enc = NULL;
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

    /* allocate and initialize video decoder on the engine */
    dec = VIDDEC1_create(ce, decoderName, NULL);
    if (dec == NULL) {
        printf( "App-> ERROR: can't open codec %s\n", decoderName);
        goto end;
    }

    /* allocate and initialize video encoder on the engine */
    enc = VIDENC1_create(ce, encoderName, NULL);
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
        VIDENC1_delete(enc);
    }
    if (dec) {
        VIDDEC1_delete(dec);
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
static Void encode_decode(VIDENC1_Handle enc, VIDDEC1_Handle dec, FILE *in,
    FILE *out)
{
    Int                         n;
    Int32                       status;

    VIDDEC1_InArgs              decInArgs;
    VIDDEC1_OutArgs             decOutArgs;
    VIDDEC1_DynamicParams       decDynParams;
    VIDDEC1_Status              decStatus;

    VIDENC1_InArgs              encInArgs;
    VIDENC1_OutArgs             encOutArgs;
    VIDENC1_DynamicParams       encDynParams;
    VIDENC1_Status              encStatus;

    IVIDEO1_BufDescIn           encInBufDesc;

    XDM_BufDesc                 encOutBufDesc;
    XDAS_Int8                  *encoded[XDM_MAX_IO_BUFFERS];
    XDAS_Int32                  encBufSizes[XDM_MAX_IO_BUFFERS];

    XDM1_BufDesc                decInBufDesc;

    XDM_BufDesc                 decOutBufDesc;
    XDAS_Int8                  *dst[XDM_MAX_IO_BUFFERS];
    XDAS_Int32                  outBufSizes[XDM_MAX_IO_BUFFERS];

    /* clear and initialize the buffer descriptors */
    memset(encoded, 0, sizeof(encoded[0]) * XDM_MAX_IO_BUFFERS);
    memset(dst,     0, sizeof(dst[0])     * XDM_MAX_IO_BUFFERS);

    encoded[0] = encodedBuf;
    dst[0]     = outBuf;

    encInBufDesc.numBufs = encOutBufDesc.numBufs = decInBufDesc.numBufs =
        decOutBufDesc.numBufs = 1;

    encOutBufDesc.bufSizes  = encBufSizes;
    decOutBufDesc.bufSizes  = outBufSizes;

    encInBufDesc.bufDesc[0].bufSize = encBufSizes[0] =
        decInBufDesc.descs[0].bufSize = outBufSizes[0] = NSAMPLES;

    encInBufDesc.bufDesc[0].buf = inBuf;
    encOutBufDesc.bufs = encoded;
    decInBufDesc.descs[0].buf = encoded[0];
    decOutBufDesc.bufs     = dst;

    encInBufDesc.frameWidth     = 0;  /* TODO */
    encInBufDesc.frameHeight    = 0;  /* TODO */
    encInBufDesc.framePitch     = 0;  /* TODO */

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
     * Note that we use versionBuf in both the encoder and decoder.  In this
     * application, this is okay, as there is always only one user of
     * the buffer.  Not all applications can make this assumption.
     */
    encStatus.data.buf     = decStatus.data.buf     = versionBuf;
    encStatus.data.bufSize = decStatus.data.bufSize = MAXVERSIONSIZE;

    /* if the codecs support it, dump their versions */
    status = VIDDEC1_control(dec, XDM_GETVERSION, &decDynParams, &decStatus);
    GT_1trace(curMask, GT_1CLASS, "Decoder version:  %s\n",
        (status == VIDDEC1_EOK ? ((char *)decStatus.data.buf) : "[unknown]"));

    status = VIDENC1_control(enc, XDM_GETVERSION, &encDynParams, &encStatus);
    GT_1trace(curMask, GT_1CLASS, "Encoder version:  %s\n",
        (status == VIDENC1_EOK ? ((char *)encStatus.data.buf) : "[unknown]"));

    /*
     * This app expects the encoder to provide 1 buf in and get 1 buf out,
     * and the buf sizes of the in and out buffer must be able to handle
     * NSAMPLES bytes of data.
     */
    status = VIDENC1_control(enc, XDM_GETSTATUS, &encDynParams, &encStatus);
    if (status != VIDENC1_EOK) {
        /* failure, report error and exit */
        GT_1trace(curMask, GT_7CLASS, "encode control status = %ld\n", status);
        return;
    }

    /* Validate this encoder codec will meet our buffer requirements */
    if ((encInBufDesc.numBufs < encStatus.bufInfo.minNumInBufs) ||
        (IFRAMESIZE < encStatus.bufInfo.minInBufSize[0]) ||
        (encOutBufDesc.numBufs < encStatus.bufInfo.minNumOutBufs) ||
        (EFRAMESIZE < encStatus.bufInfo.minOutBufSize[0])) {

        /* failure, report error and exit */
        GT_0trace(curMask, GT_7CLASS,
            "Error:  encoder codec feature conflict\n");
        return;
    }

    status = VIDDEC1_control(dec, XDM_GETSTATUS, &decDynParams, &decStatus);
    if (status != VIDDEC1_EOK) {
        /* failure, report error and exit */
        GT_1trace(curMask, GT_7CLASS, "decode control status = %ld\n", status);
        return;
    }

    /* Validate this decoder codec will meet our buffer requirements */
    if ((decInBufDesc.numBufs < decStatus.bufInfo.minNumInBufs) ||
        (EFRAMESIZE < decStatus.bufInfo.minInBufSize[0]) ||
        (decOutBufDesc.numBufs < decStatus.bufInfo.minNumOutBufs) ||
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
        Memory_cacheInv(encodedBuf, EFRAMESIZE);
#endif

        GT_1trace(curMask, GT_1CLASS, "App-> Processing frame %d...\n", n);

        /*
         * Encode the frame.
         *
         * Note, inputID == 0 is an error.  This example doesn't account
         * for the case where 'n + 1' wraps to zero.
         */
        encInArgs.inputID = n + 1;
        status = VIDENC1_process(enc, &encInBufDesc, &encOutBufDesc, &encInArgs,
            &encOutArgs);

        GT_2trace(curMask, GT_2CLASS,
            "App-> Encoder frame %d process returned - 0x%x)\n", n, status);

        if (status != VIDENC1_EOK) {
            GT_3trace(curMask, GT_7CLASS,
                "App-> Encoder frame %d processing FAILED, status = 0x%x, "
                "extendedError = 0x%x\n", n, status, encOutArgs.extendedError);
            break;
        }

        /*
         * So far, so good.  Validate our assumption that the encoder
         * provided encodedBuf as it's encOutArgs->encodedBuf.buf.  If
         * that's not the case, we may be dealing with a codec that's
         * giving us out of order frames... and this simple app
         * doesn't support that.
         */
        if (encOutArgs.encodedBuf.buf != encodedBuf) {
            GT_0trace(curMask, GT_7CLASS,
                "App-> Internal error.  Unsupported encoder\n");
            break;
        }

#ifdef CACHE_ENABLED
        /*
         * Conditionally writeback the encoded buf from the previous
         * call.  Also, as encodedBuf is an inBuf to the next process
         * call, conditionally invalidate it as well.
         */
        if (XDM_ISACCESSMODE_WRITE(encOutArgs.encodedBuf.accessMask)) {
            Memory_cacheWbInv(encodedBuf, EFRAMESIZE);
        }

        /*
         * Per DMA Rule 7, our output buffer cache lines (for the
         * upcoming decoder) must be cleaned.
         */
        Memory_cacheInv(outBuf, OFRAMESIZE);
#endif

        /*
         * Decode the frame.
         *
         * Note, inputID == 0 is an error.  This example doesn't account
         * for the case where 'n + 1' wraps to zero.
         */
        decInArgs.numBytes = EFRAMESIZE;
        decInArgs.inputID = n + 1;
        status = VIDDEC1_process(dec, &decInBufDesc, &decOutBufDesc,
            &decInArgs, &decOutArgs);

        GT_2trace(curMask, GT_2CLASS,
            "App-> Decoder frame %d process returned - 0x%x)\n", n, status);

        if (status != VIDDEC1_EOK) {
            GT_2trace(curMask, GT_7CLASS,
                "App-> Decoder frame %d processing FAILED, status = 0x%x\n",
                n, status);
            break;
        }

        /* again, validate our assumption that we don't get out-of-order bufs */
        if (decOutArgs.decodedBufs.bufDesc[0].buf != outBuf) {
            GT_0trace(curMask, GT_7CLASS,
                "App-> Internal error.  Unsupported decoder\n");
            break;
        }

#ifdef CACHE_ENABLED
        /* Conditionally writeback the decoded buf */
        if (XDM_ISACCESSMODE_WRITE(
                decOutArgs.decodedBufs.bufDesc[0].accessMask)) {
            Memory_cacheWb(outBuf, OFRAMESIZE);
        }
#endif

        /* write to file */
        fwrite(dst[0], OFRAMESIZE, 1, out);
    }

    GT_1trace(curMask, GT_1CLASS, "%d frames encoded/decoded\n", n);
}
/*
 *  @(#) ti.sdo.ce.examples.apps.video1_copy; 1, 0, 0,264; 12-2-2010 21:21:05; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

