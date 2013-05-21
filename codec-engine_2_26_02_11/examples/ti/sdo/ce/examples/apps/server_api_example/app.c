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
 *
 *  Non-Codec-Engine-using part of the ARM-side Linux application, that at
 *  certain points talks to the Codec-Engine-using part of the ARM-side
 *  Linux application. The latter module is in file ceapp.c.
 *
 *  The call flow is: app.c functions -> ceapp.c functions -> CodecEngine libs
 */

#include <stdio.h>
#include <stdlib.h>

/*  Definition of buffer sizes for input data, encoded data, output data.
 *
 *  Our application reads a raw video file one block at the time at the
 *  input buffer. It calls ceapp to encodes that from the input buffer into the
 *  "encoded data" buffer. Then it calls ceapp to decode the video data from
 *  "encoded data" buffer into the output buffer. Finally it writes the
 *  output block to another file. This flow is illustrated here:
 *
 *  <input file block> ==(app)==>           [inBuf]      ==>
 *                     ==(ceapp/encoder)==> [encodedBuf] ==>
 *                     ==(ceapp/decoder)==> [outBuf]     ==>
 *                     ==(app)==>           <output file block>
 *
 *  For simplicity, below we define all blocks to be 1K, but those sizes
 *  could be arbitrary (though they must match).
 *
 *  Note: It is EXTREMELY important that the buffers that hold the data are not
 *  simply malloc()ed, but are actually physically contiguous. This is so
 *  because the buffers are passed on to the codecs running on the DSP
 *  verbatim (there is no buffer copying involved). CodecEngine
 *  (and the ceapp module) provides and API for allocating such buffers.
 */
#define INFRAMESIZE       (1024 * sizeof(char))  /* raw frame (input) */
#define ENCODEDFRAMESIZE  (1024 * sizeof(char))  /* encoded frame */
#define OUTFRAMESIZE      (1024 * sizeof(char))  /* decoded frame (output) */

/* prototypes of functions defined in ceapp.c: */
extern int   ceapp_init();            /* initialize the ceapp module */
extern char *ceapp_allocContigBuf(    /* allocate physically contiguous */
                int   bufSize,        /*   buffer of given size; description */
                char *bufDescription  /*   is used only for print */
                );
extern int   ceapp_validateBufSizes(  /* confirm that the enc/dec codecs */
                int inBufSize,        /*   support these buffer sizes */
                int encodedBufSize,   /*   for the raw input video, encoded */
                int outBufSize        /*   video data, and decoded output */
                );
extern int   ceapp_encodeBuf(         /* encode raw video data in inBuf */
                char *inBuf,          /*   and store result in encodedBuf */
                int   inBufSize,
                char *encodedBuf,
                int   encodedBufSize
                );
extern int   ceapp_decodeBuf(        /* decode data from encodedBuf and */
                char *encodedBuf,    /*   store resulting raw data in outBuf */
                int   encodedBufSize,
                char *outBuf,
                int   outBufSize
                );
extern void  ceapp_freeContigBuf(    /* free the contiguous buffer */
                char *buf,
                int   bufSize
                );
extern void  ceapp_exit();           /* exit the ceapp module */


/*
 *  ======== encodeDecodeFile ========
 *  This function reads blocks of the input file one at the time, encodes
 *  each block, decodes it, and writes the result to the output file.
 */
static int encodeDecodeFile(char *inFileName, char *outFileName)
{
    /* pointers to contiguous shared data buffers (shared b/w Arm and DSP) */
    static char *inBuf      = NULL; /* to contig-alloc for INFRAMESIZE */
    static char *encodedBuf = NULL; /* to contig-alloc for ENCODEDFRAMESIZE */
    static char *outBuf     = NULL; /* to contig-alloc for OUTFRAMESIZE */

    FILE *inFile = NULL, *outFile = NULL;
    int  status, n;

    /* open file streams for input and output */
    if ((inFile = fopen(inFileName, "rb")) == NULL) {
        printf("App-> ERROR: can't read file %s\n", inFileName);
        exit(1);
    }
    if ((outFile = fopen(outFileName, "wb")) == NULL) {
        printf("App-> ERROR: can't write to file %s\n", outFileName);
        exit(1);
    }

    /* initialize the ceapp which in turns initializes Codec Engine */
    status = ceapp_init();

    if (status != 0) {
        goto end;
    }

    /*  Allocate the tree contiguous buffers.
     *  If we were reading input from the camera device instead of the file,
     *  we would mmap() the camera memory to inBuf and use it as such without
     *  allocating it. (Driver buffers are contiguous.) Same is true for
     *  display device's memory ("framebuffer") being mapped to outBuf.
     *  The encodedBuf, however, we would have to contig-allocate in either
     *  case, since that buffer holds the data the encoder writes to and
     *  decoder reads from.
     *  The text description we pass alongside are used only in a printf.
     */
    inBuf      = ceapp_allocContigBuf(INFRAMESIZE,      "input data");
    encodedBuf = ceapp_allocContigBuf(ENCODEDFRAMESIZE, "encoded data");
    outBuf     = ceapp_allocContigBuf(OUTFRAMESIZE,     "output data");

    if (inBuf == NULL || encodedBuf == NULL || outBuf == NULL) {
        printf("App-> Error allocating buffers (%p, %p, %p)!\n",
            inBuf, encodedBuf, outBuf);
        status = -1;
        goto end;
    }

    /*
     *  Optional call: validate that the codecs we'll use really support the
     *  sizes we specify here. There's no reason why they shouldn't, in this
     *  particular case.
     */
    status = ceapp_validateBufSizes(INFRAMESIZE, ENCODEDFRAMESIZE,
                                     OUTFRAMESIZE);
    if (status != 0) {
        goto end;
    }

    /*
     * Read complete frames from the speech dev, and write
     * encoded data to an output file file
     */
    for (n = 0 ;; n++) {
        printf("App-> Processing frame %d...\n", n);

        if (fread(inBuf, INFRAMESIZE, 1, inFile) == 0) { /* until EOF */
            break;
        }

        status = ceapp_encodeBuf(inBuf,       INFRAMESIZE,
                                  encodedBuf, ENCODEDFRAMESIZE);
        if(status != 0) {
            printf("App-> ERROR: Encoding frame %d FAILED\n", n);
            goto end;
        }

        status = ceapp_decodeBuf(encodedBuf,  ENCODEDFRAMESIZE,
                                  outBuf,     OUTFRAMESIZE);
        if (status != 0) {
            printf("App-> ERROR: Decoding frame %d FAILED\n", n);
            goto end;
        }

        /* write to file */
        fwrite(outBuf, OUTFRAMESIZE, 1, outFile);
    }

    printf("App-> Finished encoding and decoding %d frames\n", n);

    status = 0;  /* success */

end:
    /* close the files */
    fclose(inFile);
    fclose(outFile);

    /* free the contiguous buffers */
    if (inBuf != NULL) {
        ceapp_freeContigBuf(inBuf, INFRAMESIZE);
    }
    if (encodedBuf != NULL) {
        ceapp_freeContigBuf(encodedBuf, ENCODEDFRAMESIZE);
    }
    if (outBuf != NULL) {
        ceapp_freeContigBuf(outBuf, OUTFRAMESIZE);
    }

    /* quit the CE application */
    ceapp_exit();

    /* and return success (0) or failure (non-0) */
    return status;
}


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
 *  ======== main ========
 */
int main(int argc, char *argv[])
{
    char *inFileName, *outFileName;

    if (argc <= 1) {
        inFileName  = "in.dat";
        outFileName = "out.dat";
        createInFileIfMissing(inFileName);
    }
    else if (argc != 3 && argc != 4) {
        printf("Usage: %s input-file output-file\n", argv[0]);
        exit(1);
    }
    else {
        inFileName = argv[1];
        outFileName = argv[2];
    }

    printf("App-> Application started.\n");

    if (encodeDecodeFile(inFileName, outFileName) == 0) {
        printf("App-> Application finished successfully.\n");
    }
    else {
        printf("App-> Application FAILED.\n");
    }

    return 0;
}
/*
 *  @(#) ti.sdo.ce.examples.apps.server_api_example; 1,0,0,235; 12-2-2010 21:19:54; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

