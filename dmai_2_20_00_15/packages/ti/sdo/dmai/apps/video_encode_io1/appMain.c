/* --COPYRIGHT--,BSD
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
 * --/COPYRIGHT--*/
/*
 * This application encodes a raw yuv file using a specified codec to an
 * elementary stream video file. The format of the yuv file depends on the
 * device, for dm6467 it's 420 planar while on dm355 it's 422 interleaved.
 */

#include <stdio.h>
#include <string.h>

#include <xdc/std.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/CERuntime.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Ccv.h>
#include <ti/sdo/dmai/Cpu.h>
#include <ti/sdo/dmai/Time.h>
#include <ti/sdo/dmai/BufTab.h>
#include <ti/sdo/dmai/Capture.h>
#include <ti/sdo/dmai/Framecopy.h>
#include <ti/sdo/dmai/BufferGfx.h>
#include <ti/sdo/dmai/ce/Venc1.h>

#include "appMain.h"

/* Temporary compilation error fix for OMAP 3530. 
   Remove the definition when it uses CE 2.22 or later */
#ifdef Dmai_Device_omap3530
#define XDM_YUV_420SP 9 
#endif

/* Align buffers to this cache line size (in bytes)*/
#define BUFSIZEALIGN            128

/* The input buffer height restriction */
#define CODECHEIGHTALIGN       16

/* vbuf size that has been selected based on size/performance tradeoff */
#define VBUFSIZE                20480

static Char vbufferIn[VBUFSIZE];
static Char vbufferOut[VBUFSIZE];
static Char vbufferRecon[VBUFSIZE];

/* These definitions missing in some OS build environments (eg: WinCE) */
#ifndef _IOFBF
    #define _IOFBF  0
#endif  /* _IOFBF */
#ifndef _IOLBF
    #define _IOLBF  1
#endif  /* _IOLBF */
#ifndef _IONBF
    #define _IONBF  2
#endif  /* _IONBF */

/******************************************************************************
 * readFrame420P
 ******************************************************************************/
Int readFrame420P(Buffer_Handle hBuf, FILE *outFile, Int imageHeight)
{
    Int8 *yPtr = Buffer_getUserPtr(hBuf);
    Int8 *cbcrPtr;
    Int y, x;

    BufferGfx_Dimensions dim;

    BufferGfx_getDimensions(hBuf, &dim);

    /* Write Y plane */
    for (y = 0; y < imageHeight; y++) {
        if (fread(yPtr, dim.width, 1, outFile) != 1) {
            fprintf(stderr,"Failed to read data from file\n");
            return -1;
        }

        yPtr += dim.lineLength;
    }

    /* Join Cb to CbCr interleaved */
    cbcrPtr = Buffer_getUserPtr(hBuf) + Buffer_getSize(hBuf) * 2 / 3;
    for (y = 0; y < imageHeight / 2; y++) {
      for (x = 0; x < dim.width; x += 2) {
        if (fread(&cbcrPtr[x], 1, 1, outFile) != 1) {
            fprintf(stderr,"Failed to read data from file\n");
            return -1;
        }
      }
      cbcrPtr += dim.lineLength;
    }

    /* Join Cr to CbCr interleaved */
    cbcrPtr = Buffer_getUserPtr(hBuf) + Buffer_getSize(hBuf) * 2 / 3;
    for (y = 0; y < imageHeight / 2; y++) {
      for (x = 1; x < dim.width; x += 2) {
        if (fread(&cbcrPtr[x], 1, 1, outFile) != 1) {
            fprintf(stderr,"Failed to read data from file\n");
            return -1;
        }
      }
      cbcrPtr += dim.lineLength;
    }

    printf("Read 420P frame size %d (%dx%d) from file\n",
           (Int) (dim.width * 3 / 2 * imageHeight),
           (Int) dim.width, (Int) imageHeight);

    Buffer_setNumBytesUsed(hBuf, Buffer_getSize(hBuf));

    return 0;
}

/******************************************************************************
 * readFrame420SP
 ******************************************************************************/
Int readFrame420SP(Buffer_Handle hBuf, FILE *outFile, Int imageHeight)
{
    Int8 *yPtr = Buffer_getUserPtr(hBuf);
    Int8 *cbcrPtr;
    Int y;

    BufferGfx_Dimensions dim;

    BufferGfx_getDimensions(hBuf, &dim);

    /* Write Y plane */
    for (y = 0; y < imageHeight; y++) {
        if (fread(yPtr, dim.width, 1, outFile) != 1) {
            fprintf(stderr,"Failed to read data from file\n");
            return -1;
        }

        yPtr += dim.lineLength;
    }

    /* Join Cb to CbCr interleaved */
    cbcrPtr = Buffer_getUserPtr(hBuf) + Buffer_getSize(hBuf) * 2 / 3;
    for (y = 0; y < imageHeight / 2; y++) {
        if (fread(cbcrPtr, dim.width, 1, outFile) != 1) {
            fprintf(stderr,"Failed to read data from file\n");
            return -1;
        }
        cbcrPtr += dim.lineLength;
    }

    printf("Read 420SP frame size %d (%dx%d) from file\n",
           (Int) (dim.width * 3 / 2 * imageHeight),
           (Int) dim.width, (Int) imageHeight);

    Buffer_setNumBytesUsed(hBuf, Buffer_getSize(hBuf));

    return 0;
}

/******************************************************************************
 * readFrameUYVY
 ******************************************************************************/
Int readFrameUYVY(Buffer_Handle hBuf, FILE *outFile)
{
    Int8 *ptr = Buffer_getUserPtr(hBuf);
    Int y;

    BufferGfx_Dimensions dim;

    BufferGfx_getDimensions(hBuf, &dim);

    for (y = 0; y < dim.height; y++) {
        if (fread(ptr, dim.width * 2, 1, outFile) != 1) {
            fprintf(stderr,"Failed to read data from file\n");
            return -1;
        }

        ptr += dim.lineLength;
    }

    printf("Read UYVY frame size %d (%dx%d) from file\n",
           (Int) (dim.width * 2 * dim.height),
           (Int) dim.width, (Int) dim.height);

    Buffer_setNumBytesUsed(hBuf, dim.width * 2 * dim.height);

    return 0;
}


/******************************************************************************
 * processReconData
 *    Transform reconstructed buffer data into a UYVY frame.  The format of
 *    the reconstructed buffer data is expected to conform to the specification
 *    found in "MPEG4 Simple Profile Encoder Codec on DM355 User's Guide"
 *    (SPRUFE4C), and may not work for other codecs.
 ******************************************************************************/
Void processReconData(IVIDEO1_BufDesc* reconBufs, Buffer_Handle hSrcBuf,
                      Buffer_Handle hDstBuf)
{
    Int16                 mbSizeY;
    Int16                 mbSizeX;
    Uint32                lumaColLength;
    Uint32                chromaColSize;
    Uint32                UYVYRowLength;
    Uint32                UYVYMbSize;
    UInt8                *lum_buf;
    UInt8                *chr_buf;
    UInt8                *curr_mb;
    UInt8                *curr_lum_mb;
    UInt8                *curr_chroma_mb;
    Int16                 i, j, k, l;
    BufferGfx_Dimensions  dim;

    /*
     * A single Master Block is 16x16 pixels.  Get our master block dimensions
     * by divding the pixel height and width by 16.
     */
    BufferGfx_getDimensions(hSrcBuf, &dim);

    mbSizeY = dim.height >> 4;
    mbSizeX = dim.width  >> 4;

    /*
     * Our luma buffer is a series of 16x16 byte blocks, and our chroma buffer
     * is a series of 16x8 byte blocks.  Each block corresponds to information
     * for one master block.  The first block in each buffer contains header
     * information.  Set lum_buf and chr_buf to the first block after the
     * header.
     */
    lum_buf = (UInt8*) (reconBufs->bufDesc[0].buf + 16 * 16);
    chr_buf = (UInt8*) (reconBufs->bufDesc[1].buf + 16 * 8);

    /*
     * The luma and chroma buffers are constructed in column-major order.
     * The blocks for a single column are followed by two padding blocks
     * before the next column starts.  Set lumaColLength and chromaColSize
     * to the number of bytes that must be skipped over to get to the next
     * column in the corresponding buffer.
     */
    lumaColLength = (16*16) * (mbSizeY + 2);
    chromaColSize = (16*8)  * (mbSizeY + 2);

    /*
     * Calculate the number of bytes that must be skipped over to go to the
     * next row in the reconstructed UYVY frame.  Also calculate how many
     * bytes in the UYVY file are needed to represent a single master block.
     */
    UYVYRowLength = 32 * mbSizeX;
    UYVYMbSize    = 32 * 16;

    /*
     * Copy the reconstructed buffer information into a UYVY frame.
     */
    for (i = 0; i < mbSizeX; i++) {
        for (j = 0; j < mbSizeY; j++) {

            /* Calculate input and output buffer offsets for the current */
            /* master block                                              */
            curr_lum_mb    = lum_buf + (lumaColLength * i) + (256 * j);
            curr_chroma_mb = chr_buf + (chromaColSize * i) + (128 * j);
            curr_mb        = (UInt8 *) Buffer_getUserPtr(hDstBuf) +
                                 (j * (UYVYMbSize * mbSizeX)) + (i * 32);

            /* Copy Luma information */
            for (k = 0; k < 16; k++) {
                for (l = 0; l < 16; l++) {
                    curr_mb[(k * UYVYRowLength) + (l * 2) + 1] =
                        curr_lum_mb[k * 16 + l];
                }
            }

            /* Copy Chroma information */
            for (k = 0; k < 8; k++) {
                for (l = 0; l < 16; l++) {
                    curr_mb[((k * 2) * UYVYRowLength) + (l * 2)] =
                        curr_chroma_mb[k * 16 + l];
                    curr_mb[((k * 2 + 1) * UYVYRowLength) + (l * 2)] =
                        curr_chroma_mb[k * 16 + l];
                }
            }
        }
    }

    Buffer_setNumBytesUsed(hDstBuf, dim.width * dim.height * 2);
}

/******************************************************************************
 * appMain
 ******************************************************************************/
Int appMain(Args * args)
{
    VIDENC1_Params         params    = Venc1_Params_DEFAULT;
    VIDENC1_DynamicParams  dynParams = Venc1_DynamicParams_DEFAULT;
    BufferGfx_Attrs        gfxAttrs  = BufferGfx_Attrs_DEFAULT;
    Buffer_Attrs           bAttrs    = Buffer_Attrs_DEFAULT;
    Time_Attrs             tAttrs    = Time_Attrs_DEFAULT;
    Venc1_Handle           hVe1      = NULL;
    FILE                  *outFile   = NULL;
    FILE                  *reconFile = NULL;
    FILE                  *inFile    = NULL;
    Engine_Handle          hEngine   = NULL;
    Time_Handle            hTime     = NULL;
    Bool                   flushed   = FALSE;
    Bool                   mustExit  = FALSE;
    BufTab_Handle          hBufTab   = NULL;
    Buffer_Handle          hOutBuf   = NULL;
    Buffer_Handle          hFreeBuf  = NULL;                           
    Buffer_Handle          hInBuf    = NULL;
    Buffer_Handle          hReconBuf = NULL;
    Int                    numFrame  = 0;
    Int                    flushCntr = 1;
    Int                    bufIdx;
    Int                    inBufSize, outBufSize;
    Cpu_Device             device;
    Int                    numBufs;
    ColorSpace_Type        colorSpace;
    UInt32                 time;
    Int                    ret = Dmai_EOK;

    printf("Starting application...\n");
    
    /* Initialize the codec engine run time */
    CERuntime_init();
    
    /* Initialize DMAI */
    Dmai_init();

    /* Determine which device the application is running on */
    if (Cpu_getDevice(NULL, &device) < 0) {
        ret = Dmai_EFAIL;
        fprintf(stderr,"Failed to determine target board\n");
        goto cleanup;
    }

    if (args->benchmark) {
        hTime = Time_create(&tAttrs);

        if (hTime == NULL) {
            ret = Dmai_EFAIL;
            fprintf(stderr,"Failed to create Time object\n");
            goto cleanup;
        }
    }

    /* Open the input file with raw yuv data */
    inFile = fopen(args->inFile, "rb");
    
    if (inFile == NULL) {
        ret = Dmai_EFAIL;
        fprintf(stderr,"Failed to open input file %s\n", args->inFile);
        goto cleanup;
    }

    /* Using a larger vbuf to enhance performance of file i/o */
    if (setvbuf(inFile, vbufferIn, _IOFBF, sizeof(vbufferIn)) != 0) {
        ret = Dmai_EFAIL;
        fprintf(stderr,"Failed to setvbuf on input file descriptor\n");
        goto cleanup;   
    }
    
    /* Open the output file where to put encoded data */
    outFile = fopen(args->outFile, "wb");

    if (outFile == NULL) {
        ret = Dmai_EFAIL;
        fprintf(stderr,"Failed to open output file %s\n", args->outFile);
        goto cleanup;
    }

    /* Using a larger vbuf to enhance performance of file i/o */
    if (setvbuf(outFile, vbufferOut, _IOFBF, sizeof(vbufferOut)) != 0) {
        ret = Dmai_EFAIL;
        fprintf(stderr,"Failed to setvbuf on output file descriptor\n");
        goto cleanup;   
    }
        
    /* Open the output file where to put reconstructed frames */
    if (args->writeReconFrames) {
        reconFile = fopen(args->reconFile, "wb");

        if (reconFile == NULL) {
            ret = Dmai_EFAIL;
            fprintf(stderr,"Failed to open output file %s\n", args->reconFile);
            goto cleanup;
        }

        /* Using a larger vbuf to enhance performance of file i/o */
        if (setvbuf(reconFile, vbufferRecon, _IOFBF,
                    sizeof(vbufferRecon)) != 0) {
            ret = Dmai_EFAIL;
            fprintf(stderr,"Failed to setvbuf on output file descriptor\n");
            goto cleanup;   
        }
    }
        
    /* Open the codec engine */
    hEngine = Engine_open(args->engineName, NULL, NULL);

    if (hEngine == NULL) {
        ret = Dmai_EFAIL;
        fprintf(stderr,"Failed to open codec engine: %s\n", args->engineName);
        goto cleanup;
    }

    /* Set up codec parameters depending on bit rate */
    if (args->bitRate < 0) {
        /* Variable bit rate */
        params.rateControlPreset = IVIDEO_NONE;

        /* 
         * If variable bit rate use a bogus bit rate value (> 0)
         * since it will be ignored.
         */
        params.maxBitRate        = 2000000;
    }
    else {
        /* Constant bit rate */
        params.rateControlPreset = IVIDEO_LOW_DELAY;
        params.maxBitRate        = args->bitRate;
    }
 
    /* Set up codec parameters depending on device */
    switch (device) {
        case Cpu_Device_DM6467:
            params.inputChromaFormat = XDM_YUV_420SP;
            params.reconChromaFormat = XDM_CHROMA_NA;
            break;
        case Cpu_Device_DM355:
            params.inputChromaFormat = XDM_YUV_422ILE;
            params.reconChromaFormat = XDM_YUV_420P;
            break;            
        case Cpu_Device_DM365:
        case Cpu_Device_DM368:
            params.inputChromaFormat = XDM_YUV_420SP;
            params.reconChromaFormat = XDM_YUV_420SP;
            break;
        case Cpu_Device_DM3730:
            params.rateControlPreset = IVIDEO_STORAGE;
            params.inputChromaFormat = XDM_YUV_422ILE;
            break;
        default:
            params.inputChromaFormat = XDM_YUV_422ILE;
            break;
    }

    params.maxWidth              = args->width;
    params.maxHeight             = args->height;

    /* Workaround for SDOCM00068944: h264fhdvenc fails 
       to create codec when params.dataEndianness is 
       set as XDM_BYTE */
    if(device == Cpu_Device_DM6467) {
        if (!strcmp(args->codecName, "h264fhdvenc")) {
            params.dataEndianness        = XDM_LE_32;
        }
    }

    params.maxInterFrameInterval = 1;
    dynParams.targetBitRate      = params.maxBitRate;
    dynParams.inputWidth         = params.maxWidth;
    dynParams.inputHeight        = params.maxHeight;

    /* Create the video encoder */
    hVe1 = Venc1_create(hEngine, args->codecName, &params, &dynParams);

    if (hVe1 == NULL) {
        ret = Dmai_EFAIL;
        fprintf(stderr,"Failed to create video encoder: %s\n", args->codecName);
        goto cleanup;
    }

    /* Ask the codec how much input data it needs */
    inBufSize = Venc1_getInBufSize(hVe1);

    /* Ask the codec how much space it needs for output data */
    outBufSize = Venc1_getOutBufSize(hVe1);

    /* Which color space to use in the graphics buffers depends on the device */
    colorSpace = ((device == Cpu_Device_DM6467)||
                  (device == Cpu_Device_DM365) ||
                  (device == Cpu_Device_DM368)) ? ColorSpace_YUV420PSEMI :
                                               ColorSpace_UYVY;

    /* Align buffers to cache line boundary */    
    gfxAttrs.bAttrs.memParams.align = bAttrs.memParams.align = BUFSIZEALIGN; 
    
    /* Use cached buffers if requested */    
    if (args->cache) {
        gfxAttrs.bAttrs.memParams.flags = bAttrs.memParams.flags 
            = Memory_CACHED;
    } 
    
    gfxAttrs.dim.width      = args->width;
    gfxAttrs.dim.height     = args->height;
    if ((device == Cpu_Device_DM6467) || (device == Cpu_Device_DM365)
       || (device == Cpu_Device_DM368)) {
        gfxAttrs.dim.height = Dmai_roundUp(gfxAttrs.dim.height, CODECHEIGHTALIGN);
    }
    gfxAttrs.dim.lineLength = BufferGfx_calcLineLength(args->width, colorSpace);
    gfxAttrs.colorSpace     = colorSpace;
    
    if (inBufSize < 0) {
        ret = Dmai_EFAIL;
        fprintf(stderr,"Failed to calculate buffer attributes\n");
        goto cleanup;
    }

    /* Number of input buffers required */
    if(params.maxInterFrameInterval>1) {
        /* B frame support */
        numBufs = params.maxInterFrameInterval;
    }
    else {
        numBufs = 1;
    }

    /* Create a table of input buffers of the size requested by the codec */
    hBufTab = 
        BufTab_create(numBufs, Dmai_roundUp(inBufSize, BUFSIZEALIGN),
            BufferGfx_getBufferAttrs(&gfxAttrs));
    
    if (hBufTab == NULL) {
        ret = Dmai_EFAIL;
        fprintf(stderr,"Failed to allocate contiguous buffers\n");
        goto cleanup;
    }

    /* Set input buffer table */
    Venc1_setBufTab(hVe1, hBufTab);

    /* Create the reconstructed frame buffer for raw yuv data */
    if (args->writeReconFrames) {
        hReconBuf =
            Buffer_create(Dmai_roundUp(inBufSize, BUFSIZEALIGN), 
                BufferGfx_getBufferAttrs(&gfxAttrs));

        if (hReconBuf == NULL) {
            ret = Dmai_EFAIL;
            fprintf(stderr,"Failed to allocate contiguous buffer\n");
            goto cleanup;
        }
    }

    /* Create the output buffer for encoded video data */
    hOutBuf = Buffer_create(Dmai_roundUp(outBufSize, BUFSIZEALIGN), &bAttrs);

    if (hOutBuf == NULL) {
        ret = Dmai_EFAIL;
        fprintf(stderr,"Failed to create contiguous buffer\n");
        goto cleanup;
    }
  
    while (1) {

        /* Get a buffer for input */
        hInBuf = BufTab_getFreeBuf(hBufTab);

        if (hInBuf == NULL) {
            ret = Dmai_EFAIL;
            fprintf(stderr,"Failed to get a free contiguous buffer from BufTab\n");
            BufTab_print(hBufTab);
            goto cleanup;
        }

        if (args->benchmark) {
            if (Time_reset(hTime) < 0) {
                ret = Dmai_EFAIL;
                fprintf(stderr,"Failed to reset timer\n");
                goto cleanup;
            }
        }

        /* Read a yuv input frame */
        printf("\n Frame %d: ", numFrame);
        if ((device == Cpu_Device_DM6467)||
            (device == Cpu_Device_DM365) ||
            (device == Cpu_Device_DM368)) {
            if(args->sp) {
                if (readFrame420SP(hInBuf, inFile, args->height) < 0) {
                    ret = Dmai_EFAIL;
                    goto cleanup;
                }
            } else {
                if (readFrame420P(hInBuf, inFile, args->height) < 0) {
                    ret = Dmai_EFAIL;
                    goto cleanup;
                }
            }
        }
        else {
            if (readFrameUYVY(hInBuf, inFile) < 0) {
                ret = Dmai_EFAIL;
                mustExit = TRUE;
            }
        }

        if (++numFrame == args->numFrames||mustExit == TRUE){
            if(!(params.maxInterFrameInterval>1)) {
                /* No B-frame support */
                printf("... exiting \n");
                goto cleanup;
            }

            /* 
             * When encoding a stream with B-frames, ending the processing
             * requires to free the buffer held by the encoder. This is done by
             * flushing the encoder and performing a last process() call
             * with a dummy input buffer.
             */             
            printf("\n... exiting with flush (B-frame stream) \n"); 
            flushCntr = params.maxInterFrameInterval-1;
            flushed = TRUE;
            Venc1_flush(hVe1);
        }

        if (args->benchmark) {
            if (Time_delta(hTime, &time) < 0) {
                ret = Dmai_EFAIL;
                fprintf(stderr,"Failed to get timer delta\n");
                goto cleanup;
            }

            printf("Read time: %uus\n", (Uns)time);
        }

        /*
         * Following flushing loop will iterate more than one time only 
         * when the encoder completes processing by flushing the frames
         * held by the encoder. All flushed frames will be encoded as P 
         * or I frames.
         */

        for(bufIdx = 0; bufIdx < flushCntr; bufIdx++) { 

            if (args->cache) {
                /*  
                *  To meet xDAIS DMA Rule 7, when input buffers are cached, we 
                *  must writeback the cache into physical memory.  Also, per DMA 
                *  Rule 7, we must invalidate the output buffer from
                *  cache before providing it to any xDAIS algorithm.
                */
                Memory_cacheWbInv(Buffer_getUserPtr(hInBuf),
                                    Buffer_getSize(hInBuf));
    
                /* Per DMA Rule 7, our output buffer cache lines must be cleaned */
                Memory_cacheInv(Buffer_getUserPtr(hOutBuf),
                                    Buffer_getSize(hOutBuf));
    
                if (args->benchmark) {
                    if (Time_delta(hTime, &time) < 0) {
                        ret = Dmai_EFAIL;
                        fprintf(stderr,"Failed to get timer delta\n");
                        goto cleanup;
                    }
    
                    printf("Pre-process cache maintenance: %uus \n", (Uns) time);
                }
            }

            /* Make sure the whole buffer is used for input */
            BufferGfx_resetDimensions(hInBuf);

            /* Encode the video buffer */
            if (Venc1_process(hVe1, hInBuf, hOutBuf) < 0) {
                ret = Dmai_EFAIL;
                fprintf(stderr,"Failed to encode video buffer\n");
                goto cleanup;
            }

            /* if encoder generated output content, free released buffer */
            if (Buffer_getNumBytesUsed(hOutBuf)>0) {
                /* Get free buffer */
                hFreeBuf = Venc1_getFreeBuf(hVe1);
                /* Free buffer */
                BufTab_freeBuf(hFreeBuf);
            }
            /* if encoder did not generate output content */
            else {
                /* if non B frame sequence */
                /* encoder skipped frame probably exceeding target bitrate */
                if (params.maxInterFrameInterval<=1) {
                    /* free buffer */
                    printf(" Encoder generated 0 size frame\n");
                    BufTab_freeBuf(hInBuf);
                }
            }

            if (args->benchmark) {
                if (Time_delta(hTime, &time) < 0) {
                    ret = Dmai_EFAIL;
                    fprintf(stderr,"Failed to get encode time\n");
                    goto cleanup;
                }

                printf("[%d] Encode: %uus\n", numFrame, (Uns)time);
            }

            if (args->cache) {
                /* Writeback the outBuf. */
                Memory_cacheWb(Buffer_getUserPtr(hOutBuf), 
                                      Buffer_getSize(hOutBuf));
    
                if (args->benchmark) {
                    if (Time_delta(hTime, &time) < 0) {
                        ret = Dmai_EFAIL;
                        fprintf(stderr,"Failed to get timer delta\n");
                        goto cleanup;
                    }
    
                    printf("Post-process cache write back: %uus \n", (Uns) time);
                }
            }
        
            /* Write the encoded frame to the file system */
            if (Buffer_getNumBytesUsed(hOutBuf)) {
                if (fwrite(Buffer_getUserPtr(hOutBuf),
                  Buffer_getNumBytesUsed(hOutBuf), 1, outFile) != 1) {
                    ret = Dmai_EFAIL;
                    fprintf(stderr,"Failed to write encoded video data to file\n");
                    goto cleanup;
                }
            }

            /* Write the reconstructed frame to the file system */
            if (args->writeReconFrames) {
                processReconData(Venc1_getReconBufs(hVe1), hInBuf, hReconBuf);

                if (Buffer_getNumBytesUsed(hReconBuf)) {
                    if (fwrite(Buffer_getUserPtr(hReconBuf),
                      Buffer_getNumBytesUsed(hReconBuf), 1, reconFile) != 1) {
                        ret = Dmai_EFAIL;
                        fprintf(stderr,"Failed to write reconstructed frame to file\n");
                        goto cleanup;
                    }
                }
            }

            if (args->benchmark) {
                if (Time_delta(hTime, &time) < 0) {
                    ret = Dmai_EFAIL;
                    printf("Failed to get timer delta\n");
                    goto cleanup;
                }

                printf("File write time: %uus\n", (Uns)time);

                if (Time_total(hTime, &time) < 0) {
                    ret = Dmai_EFAIL;
                    fprintf(stderr,"Failed to get timer total\n");
                    goto cleanup;
                }

                printf("Total: %uus\n", (Uns)time);
            }
        }

        /* If the codec flushing completed, exit main thread */
        if (flushed) {
            /* Free dummy input buffer used for flushing process() calls */               
            printf("freeing dummy input buffer ... \n");
            BufTab_freeBuf(hInBuf);
            break;
        }
    }

cleanup:
    /* Clean up the application */
    if (hOutBuf) {
        Buffer_delete(hOutBuf);
    }

    if (hReconBuf) {
        Buffer_delete(hReconBuf);
    }

    if (hVe1) {
        Venc1_delete(hVe1);
    }

    if (hBufTab) {
        BufTab_delete(hBufTab);
    }

    if (hEngine) {
        Engine_close(hEngine);
    }

    if (inFile) {
        fclose(inFile);
    }
   
    if (outFile) {
        fclose(outFile);
    }

    if (reconFile) {
        fclose(reconFile);
    }

    if (hTime) {
        Time_delete(hTime);
    }

    printf("End of application.\n");

    if (ret == Dmai_EFAIL)
        return 1;
    else    
        return 0;
}
