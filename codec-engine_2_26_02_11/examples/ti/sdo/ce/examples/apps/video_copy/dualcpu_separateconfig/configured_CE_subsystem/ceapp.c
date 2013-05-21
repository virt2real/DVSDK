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
 *  ======== ceapp.c ========
 *  The CodecEngine-using part of the Linux application, separated from the
 *  rest of the Linux app to simplify the interface towards the rest of
 *  the main app. CodecEngine API and especially APIs for individual codecs
 *  are much more capable than what we need for simple (dummy) video
 *  encode/decode.
 */

/* include various CodecEngine header files */
#include <xdc/std.h>
#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/video/viddec.h>
#include <ti/sdo/ce/video/videnc.h>
#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/ce/CERuntime.h>
#include <ti/sdo/ce/utils/trace/TraceUtil.h>

/* define names of codecs to use */
static String decoderName  = "viddec_copy";
static String encoderName  = "videnc_copy";
static String engineName   = "video_copy";

/*  define handles to the CodecEngine and codecs to be used across ceapp_*
 *  function calls; we are not reentrant.
 */
Engine_Handle ceHandle  = NULL;
VIDDEC_Handle decHandle = NULL;
VIDENC_Handle encHandle = NULL;

/*
 *  ======== ceapp_init ========
 */
int ceapp_init()
{
    int status = -1;    /* nonzero means failure */

    /* initialize Codec Engine runtime first */
    CERuntime_init();

    /* reset, load, and start DSP Engine */
    if ((ceHandle = Engine_open(engineName, NULL, NULL)) == NULL) {
        printf("CEapp-> ERROR: can't open engine %s\n", engineName);
        goto init_end;
    }

    /* activate DSP trace collection thread */
    TraceUtil_start(engineName);

    /* allocate and initialize video encoder on the engine */
    encHandle = VIDENC_create(ceHandle, encoderName, NULL);
    if (encHandle == NULL) {
        printf("CEapp-> ERROR: can't open codec %s\n", encoderName);
        goto init_end;
    }

    /* allocate and initialize video decoder on the engine */
    decHandle = VIDDEC_create(ceHandle, decoderName, NULL);
    if (decHandle == NULL) {
        printf("CEapp-> ERROR: can't open codec %s\n", decoderName);
        goto init_end;
    }

    status = 0;     /* success */

init_end:

    return status;
}


/*
 *  ======== ceapp_allocContigBuf ========
 */
char *ceapp_allocContigBuf(int bufSize, char *description)
{
    char *buf;

    printf("CEapp-> Allocating contiguous buffer for '%s' of size %d...\n",
            description, bufSize);

    buf = (char *)Memory_contigAlloc(bufSize, Memory_DEFAULTALIGNMENT);

    if (buf == NULL) {
        printf("CEapp-> ERROR: Failed to allocate contiguous memory block.\n");
    }

    return (buf);
}


/*
 *  ======== ceapp_validateBufSizes ========
 */
int ceapp_validateBufSizes(int inBufSize, int encodedBufSize, int outBufSize)
{
    VIDDEC_DynamicParams  decDynParams;
    VIDENC_DynamicParams  encDynParams;
    VIDENC_Status         encStatus;
    VIDDEC_Status         decStatus;

    Int32                 status;
    int                   retval = -1;      /* nonzero means failure */

    /*
     * Query the encoder and decoder.
     * This app expects the encoder to provide 1 buf in and get 1 buf out,
     * and the buf sizes of the in and out buffer must be able to handle
     * NSAMPLES bytes of data.
     */
    encStatus.size = sizeof(encStatus);
    encDynParams.size = sizeof(encDynParams);

    status = VIDENC_control(encHandle, XDM_GETSTATUS, &encDynParams,
        &encStatus);

    if (status != VIDENC_EOK) {
        printf("CEapp-> Video Encoder control FAILED, status = %ld\n", status);
        goto validate_end;
    }

    /* Validate this encoder codec will meet our buffer requirements */
    if((encStatus.bufInfo.minNumInBufs     > 1)         ||
        (encStatus.bufInfo.minInBufSize[0]  > inBufSize) ||
        (encStatus.bufInfo.minNumOutBufs    > 1)         ||
        (encStatus.bufInfo.minOutBufSize[0] > encodedBufSize)) {
        printf("CEapp-> ERROR: encoder does not meet buffer requirements.\n");
        goto validate_end;
    }

    decStatus.size = sizeof(decStatus);
    decDynParams.size = sizeof(decDynParams);

    status = VIDDEC_control(decHandle, XDM_GETSTATUS, &decDynParams,
        &decStatus);
    if (status != VIDDEC_EOK) {
        printf("CEapp-> Video Decoder control FAILED, status = %ld\n", status);
        goto validate_end;
    }

    /* Validate this decoder codec will meet our buffer requirements */
    if((decStatus.bufInfo.minNumInBufs     > 1)              ||
        (decStatus.bufInfo.minInBufSize[0]  > encodedBufSize) ||
        (decStatus.bufInfo.minNumOutBufs    > 1)              ||
        (decStatus.bufInfo.minOutBufSize[0] > outBufSize)) {
        printf("CEapp-> ERROR: decoder does not meet buffer requirements.\n");
        goto validate_end;
    }

    retval = 0; /* success */

validate_end:

    return (retval);

}


/*
 *  ======== ceapp_encodeBuf ========
 */
int ceapp_encodeBuf(char *inBuf,      int inBufSize,
                     char *encodedBuf, int encodedBufSize)
{
    /* declare codec I/O buffer descriptors for the codec's process() func. */
    XDM_BufDesc      inBufDesc;
    XDM_BufDesc      encodedBufDesc;

    /* declare in and out argument descriptors for process() */
    VIDENC_InArgs    encoderInArgs;
    VIDENC_OutArgs   encoderOutArgs;

    /* declare arrays describing I/O buffers and their sizes */
    XDAS_Int8*       inBufs         [ XDM_MAX_IO_BUFFERS ];
    XDAS_Int32       inBufSizes     [ XDM_MAX_IO_BUFFERS ];
    XDAS_Int8*       encodedBufs    [ XDM_MAX_IO_BUFFERS ];
    XDAS_Int32       encodedBufSizes[ XDM_MAX_IO_BUFFERS ];

    Int32            status;
    int              retval = -1;      /* nonzero means failure */

    /* define the arrays describing I/O buffers and their sizes */
    inBufs[0]          = inBuf;
    inBufSizes[0]      = inBufSize;
    encodedBufs[0]     = encodedBuf;
    encodedBufSizes[0] = encodedBufSize;

    /* define I/O buffer descriptors using lengths and addrs of arrays above */
    inBufDesc.numBufs       = 1;
    inBufDesc.bufs          = inBufs;
    inBufDesc.bufSizes      = inBufSizes;
    encodedBufDesc.numBufs  = 1;
    encodedBufDesc.bufs     = encodedBufs;
    encodedBufDesc.bufSizes = encodedBufSizes;

    /* fill in the input arguments structure; we have nothing for this case */
    encoderInArgs.size = sizeof(encoderInArgs);
    encoderOutArgs.size = sizeof(encoderOutArgs);

    /* encode the frame, pass addrs of the structures we populated above */
    status = VIDENC_process(encHandle, &inBufDesc, &encodedBufDesc,
        &encoderInArgs, &encoderOutArgs);

    if (status == VIDENC_EOK) {
        retval = 0;
    }
    else {
        printf("CEapp-> VIDENC_process() failed, status = 0x%lx, "
            "extendedError = 0x%lx\n", status, encoderOutArgs.extendedError);
    }

    return retval;
}


/*
 *  ======== ceapp_decodeBuf ========
 */
int ceapp_decodeBuf(char *encodedBuf, int encodedBufSize,
                     char *outBuf,     int outBufSize)
{
    XDM_BufDesc      encodedBufDesc;
    XDM_BufDesc      outBufDesc;

    VIDDEC_InArgs    decoderInArgs;
    VIDDEC_OutArgs   decoderOutArgs;

    Int32            status;
    int              retval = -1;      /* nonzero means failure */

    XDAS_Int8*       encodedBufs    [ XDM_MAX_IO_BUFFERS ];
    XDAS_Int32       encodedBufSizes[ XDM_MAX_IO_BUFFERS ];
    XDAS_Int8*       outBufs        [ XDM_MAX_IO_BUFFERS ];
    XDAS_Int32       outBufSizes    [ XDM_MAX_IO_BUFFERS ];

    encodedBufs[0]      = encodedBuf;
    encodedBufSizes[0]  = encodedBufSize;
    outBufs[0]          = outBuf;
    outBufSizes[0]      = outBufSize;

    encodedBufDesc.numBufs  = 1;
    encodedBufDesc.bufs     = encodedBufs;
    encodedBufDesc.bufSizes = encodedBufSizes;
    outBufDesc.numBufs      = 1;
    outBufDesc.bufs         = outBufs;
    outBufDesc.bufSizes     = outBufSizes;

    decoderInArgs.size = sizeof(decoderInArgs);
    decoderOutArgs.size = sizeof(decoderOutArgs);

    status = VIDDEC_process(decHandle, &encodedBufDesc, &outBufDesc,
        &decoderInArgs, &decoderOutArgs);

    if (status == VIDDEC_EOK) {
        retval = 0;
    }
    else {
        printf("CEapp-> VIDDEC_process() failed, status = 0x%lx, "
            "extendedError = 0x%lx\n", status, decoderOutArgs.extendedError);
    }

    return (retval);
}


/*
 *  ======== ceapp_freeContigBuf ========
 */
void ceapp_freeContigBuf(char *buf, int bufSize)
{
    Memory_contigFree(buf, bufSize);
}


/*
 *  ======== ceapp_exit ========
 */
void ceapp_exit()
{
    /* teardown the codecs and the engine */
    if (encHandle != NULL) {
        VIDENC_delete(encHandle);
    }
    if (decHandle != NULL) {
        VIDDEC_delete(decHandle);
    }
    TraceUtil_stop();  /* close tracing thread */
    if (ceHandle != NULL) {
        Engine_close(ceHandle);
    }
}
/*
 *  @(#) ti.sdo.ce.examples.apps.video_copy; 1, 0, 0,77; 12-2-2010 21:21:30; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

