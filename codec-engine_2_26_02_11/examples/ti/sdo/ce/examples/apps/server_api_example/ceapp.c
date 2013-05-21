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
 *  The Codec Engine-using part of the Linux application, separated from the
 *  rest of the Linux app to simplify the interface towards the rest of
 *  the main app. CodecEngine API and especially APIs for individual codecs
 *  are much more capable than what we need for simple (dummy) audio
 *  encode/decode.
 */

/* include various Codec Engine header files */
#include <xdc/std.h>
#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/audio/auddec.h>
#include <ti/sdo/ce/audio/audenc.h>
#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/ce/CERuntime.h>
#include <ti/sdo/ce/Server.h>

#include <ti/sdo/ce/trace/gt.h>

/* Name of the heap used for allocating algorithm memory */
#define ALGHEAP "DDRALGHEAP"

static Void enumAlgs(String name);
static Server_Status getMemStats(Server_Handle server);

/* define names of codecs to use */
static String decoderName  = "auddec_copy";
static String encoderName  = "audenc_copy";
static String engineName   = "audio_copy";

/*  define handles to the CodecEngine and codecs to be used across ceapp_*
 *  function calls; we are not reentrant.
 */
Engine_Handle ceHandle  = NULL;
Server_Handle server = NULL;
AUDDEC_Handle decHandle = NULL;
AUDENC_Handle encHandle = NULL;

Ptr algHeapBase = NULL;
Uint32 algHeapSize = 0x100000; /* 1MB */

/*
 *  ======== traceDump ========
 *  dump contents of DSP trace -- this is a "pull" trace dumping: we read
 *  DSP's trace log whenever we think there might be something there.
 */
static void traceDump(Engine_Handle ceHandle)
{
    GT_disable(); /* temporarily disable tracing for this thread */
    Engine_fwriteTrace(ceHandle, "[DSP] ", stdout);
    GT_enable();
}

/*
 *  ======== ceapp_init ========
 */
int ceapp_init()
{
    Uint32        base;
    Server_Status serr = Server_EOK;
    int           status = -1;    /* nonzero means failure */
    Memory_AllocParams allocParams;

    /* initialize Codec Engine runtime first */
    CERuntime_init();

    /* List all algorithms configured in this engine and their properties. */
    enumAlgs(engineName);

    /* reset, load, and start DSP Engine */
    if ((ceHandle = Engine_open(engineName, NULL, NULL)) == NULL) {
        printf("CEapp-> ERROR: can't open engine %s\n", engineName);
        goto init_end;
    }

    /* Get a handle the the Engine's Server */
    server = Engine_getServer(ceHandle);
    if (server == NULL) {
        printf("Failed to get server handle\n");
        goto init_end;
    }

    /* Print out initial memory configuration. */
    printf("\nOriginal configuration of server heaps:\n");
    serr = getMemStats(server);
    if (serr != Server_EOK) {
        printf("Failed to get MEM stats\n");
        goto init_end;
    }

    /*
     *  First try to create codecs with the original algorithm heap configured
     *  in the server. This should fail since the heap size is too small.
     */
    /* Attempt to allocate and initialize audio encoder on the engine */
    encHandle = AUDENC_create(ceHandle, encoderName, NULL);
    if (encHandle == NULL) {
        printf("CEapp-> ERROR: can't open codec %s - Will try again\n",
                encoderName);
    }
    else {
        printf("\nCEapp-> Opened codec %s\n", encoderName);
    }

    /* Attempte to allocate and initialize audio decoder on the engine */
    decHandle = AUDDEC_create(ceHandle, decoderName, NULL);
    if (decHandle == NULL) {
        printf("CEapp-> ERROR: can't open codec %s - Will try again\n",
                decoderName);
    }
    else {
        printf("CEapp-> Opened codec %s\n", decoderName);
    }

    if ((encHandle == NULL) || (decHandle == NULL)) {
        printf("CEapp-> Will attempt to recreate codecs after reconfiguring"
                " algorithm heap\n");
        if (encHandle != NULL) {
            AUDENC_delete(encHandle);
            encHandle = NULL;
        }
        if (decHandle != NULL) {
            AUDDEC_delete(decHandle);
            decHandle = NULL;
        }
    }

    /*
     *  Allocate a buffer to be used for algorithm heap. Buffer must be
     *  aligned on an 8-byte boundary.
     */
    allocParams.type = Memory_CONTIGPOOL;
    allocParams.flags = Memory_NONCACHED;
    allocParams.align = 0x8;
    allocParams.seg = 0;
    algHeapBase = Memory_alloc(algHeapSize, &allocParams);

    /* Get the Server address of the buffer. */
    base = Memory_getBufferPhysicalAddress(algHeapBase, algHeapSize, NULL);
    printf("New base, size of %s: 0x%x 0x%x\n", ALGHEAP, base, algHeapSize);

    /*  dump contents of DSP trace -- this is a "pull" trace dumping: we read
     *  DSP's trace log whenever we think there might be something there.
     */
    traceDump(ceHandle);

    /*
     *  Set the new base and size of the algorithm heap. This should fail
     *  if the codecs were created successfully.
     */
    serr = Server_redefineHeap(server, ALGHEAP, base, algHeapSize);
    if (serr != Server_EOK) {
        printf("Server_redefineHeap returned [%d], should have"
                " returned Server_EOK\n", serr);
        goto init_end;
    }

    printf("\nConfiguration of server heaps after reconfiguration:\n");

    /* Verify that this really happened on the target. */
    serr = getMemStats(server);
    if (serr != Server_EOK) {
        printf("Failed to get MEM stats\n");
        goto init_end;
    }

    /*
     *  Allocate and initialize audio encoder and decoder on the engine. This
     *  time it should succeed.
     */
    encHandle = AUDENC_create(ceHandle, encoderName, NULL);
    if (encHandle == NULL) {
        printf("CEapp-> ERROR: can't open codec %s\n", encoderName);
        goto init_end;
    }
    traceDump(ceHandle);

    /* allocate and initialize audio decoder on the engine */
    decHandle = AUDDEC_create(ceHandle, decoderName, NULL);
    if (decHandle == NULL) {
        printf("CEapp-> ERROR: can't open codec %s\n", decoderName);
        goto init_end;
    }

    printf("\nCEapp-> Creation of codecs succeeded!\n");
    traceDump(ceHandle);

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
    Memory_AllocParams allocParams;

    printf("CEapp-> Allocating contiguous buffer for '%s' of size %d...\n",
            description, bufSize);

    allocParams.type = Memory_CONTIGPOOL;
    allocParams.flags = Memory_NONCACHED;
    allocParams.align = Memory_DEFAULTALIGNMENT;
    allocParams.seg = 0;

    buf = (char *)Memory_alloc(bufSize, &allocParams);

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
    AUDDEC_DynamicParams  decDynParams;
    AUDENC_DynamicParams  encDynParams;
    AUDENC_Status         encStatus;
    AUDDEC_Status         decStatus;

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

    status = AUDENC_control(encHandle, XDM_GETSTATUS, &encDynParams,
        &encStatus);

    if (status != AUDENC_EOK) {
        printf("CEapp-> Audio Encoder control FAILED, status = %ld\n", status);
        goto validate_end;
    }
    traceDump(ceHandle);

    /* Validate this encoder codec will meet our buffer requirements */
    if((encStatus.bufInfo.minNumInBufs     > 1)         ||
        (encStatus.bufInfo.minInBufSize[0]  > inBufSize) ||
        (encStatus.bufInfo.minNumOutBufs    > 1)         ||
        (encStatus.bufInfo.minOutBufSize[0] > encodedBufSize)) {
        printf("CEapp-> ERROR: encoder does not meet buffer requirements.\n");
        goto validate_end;
    }
    traceDump(ceHandle);

    decStatus.size = sizeof(decStatus);
    decDynParams.size = sizeof(decDynParams);

    status = AUDDEC_control(decHandle, XDM_GETSTATUS, &decDynParams,
        &decStatus);
    if (status != AUDDEC_EOK) {
        printf("CEapp-> Audio Decoder control FAILED, status = %ld\n", status);
        goto validate_end;
    }
    traceDump(ceHandle);

    /* Validate this decoder codec will meet our buffer requirements */
    if((decStatus.bufInfo.minNumInBufs     > 1)              ||
        (decStatus.bufInfo.minInBufSize[0]  > encodedBufSize) ||
        (decStatus.bufInfo.minNumOutBufs    > 1)              ||
        (decStatus.bufInfo.minOutBufSize[0] > outBufSize)) {
        printf("CEapp-> ERROR: decoder does not meet buffer requirements.\n");
        goto validate_end;
    }
    traceDump(ceHandle);

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
    AUDENC_InArgs    encoderInArgs;
    AUDENC_OutArgs   encoderOutArgs;

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
    status = AUDENC_process(encHandle, &inBufDesc, &encodedBufDesc,
        &encoderInArgs, &encoderOutArgs);
    traceDump(ceHandle);

    if (status == AUDENC_EOK) {
        retval = 0;
    }
    else {
        printf("CEapp-> AUDENC_process() failed, status=%ld\n", status);
    }

    return retval;
}


/*
 *  ======== ceapp_decodeBuf ========
 */
int ceapp_decodeBuf(char *encodedBuf, int encodedBufSize,
                     char *outBuf,     int outBufSize)
{
    /* declare codec I/O buffer descriptors for the codec's process() func. */
    XDM_BufDesc      encodedBufDesc;
    XDM_BufDesc      outBufDesc;

    /* declare in and out argument descriptors for process() */
    AUDDEC_InArgs    decoderInArgs;
    AUDDEC_OutArgs   decoderOutArgs;

    Int32            status;
    int              retval = -1;      /* nonzero means failure */

    /* declare arrays describing I/O buffers and their sizes */
    XDAS_Int8*       encodedBufs    [ XDM_MAX_IO_BUFFERS ];
    XDAS_Int32       encodedBufSizes[ XDM_MAX_IO_BUFFERS ];
    XDAS_Int8*       outBufs        [ XDM_MAX_IO_BUFFERS ];
    XDAS_Int32       outBufSizes    [ XDM_MAX_IO_BUFFERS ];

    /* define the arrays describing I/O buffers and their sizes */
    encodedBufs[0]      = encodedBuf;
    encodedBufSizes[0]  = encodedBufSize;
    outBufs[0]          = outBuf;
    outBufSizes[0]      = outBufSize;

    /* define I/O buffer descriptors using lengths and addrs of arrays above */
    encodedBufDesc.numBufs  = 1;
    encodedBufDesc.bufs     = encodedBufs;
    encodedBufDesc.bufSizes = encodedBufSizes;
    outBufDesc.numBufs      = 1;
    outBufDesc.bufs         = outBufs;
    outBufDesc.bufSizes     = outBufSizes;

    /* fill in the input arguments structure */
    decoderInArgs.size = sizeof(decoderInArgs);
    decoderInArgs.numBytes = encodedBufSize;
    decoderOutArgs.size = sizeof(decoderOutArgs);

    /* decode the frame, pass addrs of the structures we populated above */
    status = AUDDEC_process(decHandle, &encodedBufDesc, &outBufDesc,
        &decoderInArgs, &decoderOutArgs);

    traceDump(ceHandle);

    if (status == AUDDEC_EOK) {
        retval = 0;
    }
    else {
        printf("CEapp-> AUDDEC_process() failed, status=%ld\n", status);
    }

    return (retval);
}


/*
 *  ======== ceapp_freeContigBuf ========
 */
void ceapp_freeContigBuf(char *buf, int bufSize)
{
    Memory_AllocParams allocParams;

    allocParams.type = Memory_CONTIGPOOL;
    allocParams.flags = Memory_NONCACHED;
    allocParams.align = Memory_DEFAULTALIGNMENT;
    allocParams.seg = 0;

    Memory_free(buf, bufSize, &allocParams);
}


/*
 *  ======== ceapp_exit ========
 */
void ceapp_exit()
{
    Server_Status serr = Server_EOK;

    /* teardown the codecs and the engine */
    if (encHandle != NULL) {
        AUDENC_delete(encHandle);
        traceDump(ceHandle);
    }
    if (decHandle != NULL) {
        AUDDEC_delete(decHandle);
        traceDump(ceHandle);
    }

    /* Restore algorithm heap */
    serr = Server_restoreHeap(server, ALGHEAP);
    if (serr != Server_EOK) {
        printf("Unable to restore heap %s: [%d]\n", ALGHEAP, serr);
    }

    printf("\nConfiguration of server heaps after restoring:\n");

    /* Verify that this really happened on the target. */
    serr = getMemStats(server);
    if (serr != Server_EOK) {
        printf("Failed to get MEM stats\n");
    }

    /* Free the buffer that was allocated for the algorithm heap. */
    if (algHeapBase) {
        Memory_contigFree(algHeapBase, algHeapSize);
    }

    if (ceHandle != NULL) {
        Engine_close(ceHandle);
    }
}

/*
 *  ======== enumAlgs ========
 */
static Void enumAlgs(String name)
{
    Engine_AlgInfo      algInfo;
    Int                 numAlgs;
    Int                 i;
    String              loc;
    Engine_Error        status;

    status = Engine_getNumAlgs(name, &numAlgs);

    if (status == Engine_EOK) {
        printf("%s: numAlgs = %d\n", name, numAlgs);
    }
    else {
        printf("Engine_getNumAlgs(%s) error: %d\n", name, status);
        return;
    }

    algInfo.algInfoSize = sizeof(Engine_AlgInfo);

    for (i = 0; i < numAlgs; i++) {
        status = Engine_getAlgInfo(name, &algInfo, i);
        if (status == Engine_EOK) {
            loc = (algInfo.isLocal) ? "local" : "remote";
            printf("  alg[%d].name = %s: %s\n", i, algInfo.name, loc);
        }
        else {
            printf("Engine_getAlgInfo(%s) error: %d\n", name, status);
            return;
        }
    }
}

/*
 *  ======== getMemStats ========
 */
static Server_Status getMemStats(Server_Handle server)
{
    Server_MemStat stat;
    Int            i;
    Int            numSegs;
    Server_Status  serr = Server_EOK;

    serr = Server_getNumMemSegs(server, &numSegs);
    if (serr != Server_EOK) {
        printf("Server_getNumMemSegs() error: %d\n", serr);
        return (serr);
    }

    /* Check memory usage */
    for (i = 0; i < numSegs; i++) {
        serr = Server_getMemStat(server, i, &stat);
        if (serr != Server_EOK) {
            printf("Server_getMemStat() error: %d\n", serr);
            return (serr);
        }
        printf("Seg %d: [%10s] base [0x%08x] size[0x%08x] used[0x%08x]"
                " max block[0x%08x]\n", i, stat.name, stat.base, stat.size,
                stat.used, stat.maxBlockLen);
    }

    return (serr);
}

/*
 *  @(#) ti.sdo.ce.examples.apps.server_api_example; 1,0,0,235; 12-2-2010 21:19:55; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

