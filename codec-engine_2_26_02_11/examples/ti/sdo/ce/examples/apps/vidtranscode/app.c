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
#include <ti/sdo/ce/vidtranscode/vidtranscode.h>
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
static String transcoderName  = "vidtranscode_copy";
static String engineName   = "vidtranscode";

static String usage = "%s: input-file output-file\n";

static Void transcode(VIDTRANSCODE_Handle transcoder, FILE *in, FILE *out);

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
    VIDTRANSCODE_Handle transcoder = NULL;
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

    /* allocate and initialize video transcoder on the engine */
    transcoder = VIDTRANSCODE_create(ce, transcoderName, NULL);
    if (transcoder == NULL) {
        printf( "App-> ERROR: can't open codec %s\n", transcoderName);
        goto end;
    }

    /* use engine to encode, then decode the data */
    transcode(transcoder, in, out);

end:
    /* teardown the codec */
    if (transcoder) {
        VIDTRANSCODE_delete(transcoder);
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
 *  ======== transcode ========
 */
static Void transcode(VIDTRANSCODE_Handle transcoder, FILE *in, FILE *out)
{
    Int                         n;
    Int32                       status;

    VIDTRANSCODE_InArgs         tcInArgs;
    VIDTRANSCODE_OutArgs        tcOutArgs;
    VIDTRANSCODE_DynamicParams  tcDynParams;
    VIDTRANSCODE_Status         tcStatus;

    XDM1_BufDesc                tcInBufDesc;

    XDM_BufDesc                 tcOutBufDesc;
    XDAS_Int8                  *dst[XDM_MAX_IO_BUFFERS];
    XDAS_Int32                  outBufSizes[XDM_MAX_IO_BUFFERS];

    /* clear and initialize the buffer descriptors */
    memset(dst,     0, sizeof(dst[0])     * XDM_MAX_IO_BUFFERS);

    dst[0]     = outBuf;

    tcInBufDesc.numBufs = tcOutBufDesc.numBufs = 1;

    tcOutBufDesc.bufSizes  = outBufSizes;

    tcInBufDesc.descs[0].bufSize = outBufSizes[0] = NSAMPLES;

    tcInBufDesc.descs[0].buf = inBuf;
    tcOutBufDesc.bufs     = dst;

    /* initialize all "sized" fields */
    tcInArgs.size    = sizeof(tcInArgs);
    tcOutArgs.size   = sizeof(tcOutArgs);
    tcDynParams.size = sizeof(tcDynParams);
    tcStatus.size    = sizeof(tcStatus);

    /* if the codecs support it, dump their versions */
    tcStatus.data.buf = versionBuf;
    tcStatus.data.bufSize = MAXVERSIONSIZE;

    status = VIDTRANSCODE_control(transcoder, XDM_GETVERSION, &tcDynParams,
        &tcStatus);
    GT_1trace(curMask, GT_1CLASS, "Transcoder version:  %s\n",
        (status == VIDTRANSCODE_EOK ?
            ((char *)tcStatus.data.buf) : "[unknown]"));

    /*
     * This app expects the transcoder to accept 1 buf in and provide 1 buf out,
     * and the buf sizes of the in and out buffer must be able to handle
     * NSAMPLES bytes of data.
     */
    status = VIDTRANSCODE_control(transcoder, XDM_GETSTATUS, &tcDynParams,
        &tcStatus);
    if (status != VIDTRANSCODE_EOK) {
        /* failure, report error and exit */
        GT_1trace(curMask, GT_7CLASS, "transcode control status = %ld\n",
            status);
        return;
    }

    /* Validate this transcoder will meet our buffer requirements */
    if ((tcInBufDesc.numBufs < tcStatus.bufInfo.minNumInBufs) ||
        (IFRAMESIZE < tcStatus.bufInfo.minInBufSize[0]) ||
        (tcOutBufDesc.numBufs < tcStatus.bufInfo.minNumOutBufs) ||
        (OFRAMESIZE < tcStatus.bufInfo.minOutBufSize[0])) {

        /* failure, report error and exit */
        GT_0trace(curMask, GT_7CLASS,
            "Error:  transcoder codec feature conflict\n");
        return;
    }

    /*
     * Read complete frames from in, transcode, and write to out.
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
        tcInArgs.inputID = n + 1;
        tcInArgs.numBytes = IFRAMESIZE;
        status = VIDTRANSCODE_process(transcoder, &tcInBufDesc, &tcOutBufDesc,
            &tcInArgs, &tcOutArgs);

        GT_2trace(curMask, GT_2CLASS,
            "App-> Transcoder frame %d process returned - 0x%x)\n", n, status);

        if (status != VIDTRANSCODE_EOK) {
            GT_3trace(curMask, GT_7CLASS,
                "App-> Transcoder frame %d processing FAILED, status = 0x%x, "
                "extendedError = 0x%x\n", n, status, tcOutArgs.extendedError);
            break;
        }

        /*
         * So far, so good.  Validate our assumption that the transcoder
         * provided outBuf as it's tcOutArgs->encodedBuf[0].buf.  If
         * that's not the case, we may be dealing with a codec that's
         * giving us out of order frames... and this simple app
         * doesn't support that.
         */
        if (tcOutArgs.encodedBuf[0].buf != outBuf) {
            GT_0trace(curMask, GT_7CLASS,
                "App-> Internal error.  Unsupported transcoder\n");
            break;
        }

#ifdef CACHE_ENABLED
        /*
         * Conditionally writeback the transcoded buf from the previous
         * call.
         */
        if (XDM_ISACCESSMODE_WRITE(tcOutArgs.encodedBuf[0].accessMask)) {
            Memory_cacheWb(outBuf, OFRAMESIZE);
        }
#endif

        /* write to file */
        fwrite(dst[0], OFRAMESIZE, 1, out);
    }

    GT_1trace(curMask, GT_1CLASS, "%d frames transcoded\n", n);
}
/*
 *  @(#) ti.sdo.ce.examples.apps.vidtranscode; 1, 0, 0,225; 12-2-2010 21:21:50; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

