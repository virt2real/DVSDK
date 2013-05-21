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
 *  Illustrate use of "abstract" speech encoder.
 */
#include <xdc/std.h>
#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/ce/speech1/sphenc1.h>
#include <ti/xdais/xdas.h>

#include <stdio.h>
#include <stdlib.h>

#ifndef BUFALIGN
#define BUFALIGN Memory_DEFAULTALIGNMENT
#endif

#define NSAMPLES    32
#define IFRAMESIZE  (NSAMPLES * sizeof(Int16))  /* raw frame (input) */
#define OFRAMESIZE  (NSAMPLES * sizeof(Int8))   /* encoded frame (output) */
#define MAXVERSIONSIZE 128

static XDAS_Int8 *inBuf;
static XDAS_Int8 *outBuf;
static XDAS_Int8 *versionBuf;   /* acquire optional version from codec */

static String progName     = "app";
static String codecName    = "g711enc";
static String engineName   = "speech";

static String usage = "%s: input-file output-file\n";

static Void encode(SPHENC1_Handle enc, FILE *in, FILE *out);

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
    SPHENC1_Handle enc = NULL;
    FILE *in = NULL;
    FILE *out = NULL;
    String inFile, outFile;
    Memory_AllocParams allocParams;

    if (argc <= 1) {
        inFile = "./in.dat";
        outFile = "./out.dat";
        createInFileIfMissing(inFile);
    }
    else if (argc != 3) {
        fprintf(stderr, usage, argv[0]);
        exit(1);
    }
    else {
        progName = argv[0];
        inFile = argv[1];
        outFile = argv[2];
    }

    printf( "App-> Application started.\n");

    /* allocate input, output, and version string buffers */
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

    /* allocate and initialize speech encoder on engine, with default params */
    enc = SPHENC1_create(ce, codecName, NULL);
    if (enc == NULL) {
        fprintf(stderr, "%s: error: can't open codec %s\n",
            progName, codecName);
        goto end;
    }

    /* use engine to encode data */
    encode(enc, in, out);

end:
    /* teardown the codec */
    if (enc) {
        SPHENC1_delete(enc);
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

    printf("app done.\n");
    return (0);
}

/*
 *  ======== encode ========
 */
static Void encode(SPHENC1_Handle enc, FILE *in, FILE *out)
{
    Int                         n;
    XDM1_SingleBufDesc          inBufDesc;
    XDM1_SingleBufDesc          outBufDesc;
    Int32                       status;
    XDAS_Int32                  bufSize = NSAMPLES;

    SPHENC1_InArgs              encInArgs;
    SPHENC1_OutArgs             encOutArgs;
    SPHENC1_DynamicParams       encDynParams;
    SPHENC1_Status              encStatus;

    /* prepare "global" buffer descriptor settings */
    inBufDesc.bufSize = bufSize * sizeof(short);
    outBufDesc.bufSize = bufSize * sizeof(char);

    /* initialize all "sized" fields */
    encInArgs.size    = sizeof(encInArgs);
    encOutArgs.size   = sizeof(encOutArgs);
    encDynParams.size = sizeof(encDynParams);
    encStatus.size    = sizeof(encStatus);
    encStatus.data.buf     = versionBuf;
    encStatus.data.bufSize = MAXVERSIONSIZE;

    status = SPHENC1_control(enc, XDM_GETVERSION, &encDynParams, &encStatus);
    printf("Encoder version:  %s\n",
        (status == SPHENC1_EOK ? ((char *)encStatus.data.buf) : "[unknown]"));

    /*
     * Note that this function is not yet complete.  It's functional, but not
     * a good example to start from - yet.
     */

    /* prepare "global" buffer descriptor settings */
/*    inBufDesc.bufSizes = outBufDesc.bufSizes = */

    encInArgs.size = sizeof(encInArgs);
    /*
     * SPHENC1_process() requires SPHENC1_InArgs.data.buf to be a valid
     * pointer or NULL.
     */
    encInArgs.data.buf = NULL;

    /*
     * Read complete frames from in, encode, and write to out.
     */
    for (n = 0; fread(inBuf, IFRAMESIZE, 1, in) == 1; n++) {
        printf("App-> Processing frame %d...\n", n);

        /* prepare "per loop" buffer descriptor settings */
        inBufDesc.buf = inBuf;
        outBufDesc.buf = outBuf;

        /* encode the frame */
        status = SPHENC1_process(enc, &inBufDesc, &outBufDesc, &encInArgs,
            &encOutArgs);

        if (status != SPHENC1_EOK) {
            printf("App-> Encoder frame %d processing FAILED, status = 0x%x, "
                "extendedError = 0x%x\n", n, status, encOutArgs.extendedError);
            break;
        }

        /* write to file */
        fwrite(outBuf, OFRAMESIZE, 1, out);
    }

    printf("%d frames encoded\n", n);
}
/*
 *  @(#) ti.sdo.ce.examples.apps.speech; 1, 0, 0,77; 12-2-2010 21:20:24; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

