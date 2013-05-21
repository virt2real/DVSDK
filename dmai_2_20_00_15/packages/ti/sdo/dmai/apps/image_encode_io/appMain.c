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
 * This application encodes a raw yuv file using a codec implementing the 
 * IMGENC interface.
 */

#include <stdio.h>

#include <xdc/std.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/CERuntime.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Time.h>
#include <ti/sdo/dmai/Buffer.h>
#include <ti/sdo/dmai/BufferGfx.h>
#include <ti/sdo/dmai/ce/Ienc.h>

#include "appMain.h"

/* Align buffers to this cache line size (in bytes)*/
#define BUFSIZEALIGN            128

/* vbuf size that has been selected based on size/performance tradeoff */
#define VBUFSIZE                20480

static Char vbufferIn[VBUFSIZE];
static Char vbufferOut[VBUFSIZE];

/******************************************************************************
 * readFrame
******************************************************************************/
Int readFrame(Buffer_Handle hBuf, FILE *outFile)
{
    Int8    *framePtr = Buffer_getUserPtr(hBuf);
    UInt32   ySize;                /* Size of Luma data */
    Uint32   cbcrSize;             /* Size of Chroma (cb and cr) data */
    Char    *colorFmt;

    BufferGfx_Dimensions dim;
    
    BufferGfx_getDimensions(hBuf, &dim);

    ySize = dim.width * dim.height;

    switch(BufferGfx_getColorSpace(hBuf)){
       case ColorSpace_UYVY:
           cbcrSize = dim.width * dim.height;
           colorFmt = "UYVY";
           break;
       case ColorSpace_YUV444P:
           cbcrSize = dim.width * dim.height * 2;
           colorFmt = "444P";
           break;
       case ColorSpace_YUV422P:
           cbcrSize = dim.width * dim.height;
           colorFmt = "422P";
           break;
       case ColorSpace_YUV420P:
           cbcrSize = dim.width * dim.height / 2;
           colorFmt = "420P";
           break;
       case ColorSpace_GRAY:
           cbcrSize = 0;
           colorFmt = "GRAY";
           break;
       default:
           printf("Unsupported input color space.\n");
           return -1;        
    }   

    if (fread(framePtr, 1, ySize + cbcrSize, outFile) != 
          ySize + cbcrSize) {
        printf("Failed to read data from file\n");
        return -1;
    }

    printf("Read %s frame size %d (%dx%d) from file\n",
           colorFmt,
           (Int) (ySize + cbcrSize),
           (Int) dim.width, (Int) dim.height);

    Buffer_setNumBytesUsed(hBuf, Buffer_getSize(hBuf));
    
    return 0;
}
    
/******************************************************************************
 * appMain
 ******************************************************************************/
Void appMain(Args * args)
{
    IMGENC_Params           params      = Ienc_Params_DEFAULT;
    IMGENC_DynamicParams    dynParams   = Ienc_DynamicParams_DEFAULT;
    BufferGfx_Attrs         gfxAttrs    = BufferGfx_Attrs_DEFAULT;
    Buffer_Attrs            bAttrs      = Buffer_Attrs_DEFAULT;
    Time_Attrs              tAttrs      = Time_Attrs_DEFAULT;
    Ienc_Handle             hIe         = NULL;
    FILE                   *outFile     = NULL;
    FILE                   *inFile      = NULL;
    Engine_Handle           hEngine     = NULL;
    Time_Handle             hTime       = NULL;
    Int                     numFrame    = 0;
    Int                     totalBytes  = 0;
    Buffer_Handle           hOutBuf     = NULL;
    Buffer_Handle           hInBuf      = NULL;
    Int                     inBufSize, outBufSize;
    UInt32                  time;
    Int                     status;

    printf("Starting application...\n");
    
    /* Initialize the codec engine run time */
    CERuntime_init();
    
    /* Initialize DMAI */
    Dmai_init();
    
    if (args->benchmark) {
        hTime = Time_create(&tAttrs);

        if (hTime == NULL) {
            printf("Failed to create Time object\n");
            goto cleanup;
        }
    }

    /* Open input file */
    inFile = fopen(args->inFile, "rb");
    
    if (inFile == NULL) {
        printf("Failed to open input file %s\n", args->inFile);
        goto cleanup;
    }

    /* Using a larger vbuf to enhance performance of file i/o */
    if (setvbuf(inFile, vbufferIn, _IOFBF, sizeof(vbufferIn)) != 0) {
        printf("Failed to setvbuf on input file descriptor\n");
        goto cleanup;   
      } 

    
    /* Open output file */
    outFile = fopen(args->outFile, "wb");

    if (outFile == NULL) {
        printf("Failed to open output file %s\n", args->outFile);
        goto cleanup;
    }

    /* Using a larger vbuf to enhance performance of file i/o */
    if (setvbuf(outFile, vbufferOut, _IOFBF, sizeof(vbufferOut)) != 0) {
        printf("Failed to setvbuf on output file descriptor\n");
        goto cleanup;   
      }
    
    /* Open the codec engine */
    hEngine = Engine_open(args->engineName, NULL, NULL);

    if (hEngine == NULL) {
        printf("Failed to open codec engine: %s\n", args->engineName);
        goto cleanup;
    }

    params.maxWidth = args->width;
    params.maxHeight = args->height;
    switch (args->oColorSpace) {
        case ColorSpace_UYVY:
            printf("Using output color format UYVY\n");
            params.forceChromaFormat = XDM_YUV_422ILE;
            break;
        case ColorSpace_YUV420P:
            printf("Using output color format YUV420P\n");
            params.forceChromaFormat = XDM_YUV_420P;
            break;
        case ColorSpace_YUV422P:
            printf("Using output color format YUV422P\n");
            params.forceChromaFormat = XDM_YUV_422P;
            break;
        case ColorSpace_YUV444P:
            printf("Using output color format YUV444P\n");
            params.forceChromaFormat = XDM_YUV_444P;
            break;
        case ColorSpace_GRAY:
            printf("Using output color format GRAY\n");
            params.forceChromaFormat = XDM_GRAY;
            break;
        default:
            printf("Unsupported output color space.\n");
            goto cleanup;        
    }
    
    dynParams.inputWidth = params.maxWidth;
    dynParams.inputHeight = params.maxHeight;
    dynParams.captureWidth = params.maxWidth;
    dynParams.numAU = args->numAU;
    dynParams.qValue = args->qValue;

    switch (args->iColorSpace) {
        case ColorSpace_UYVY:
            printf("Using input color format UYVY\n");
            dynParams.inputChromaFormat = XDM_YUV_422ILE;
            break;
        case ColorSpace_YUV420P:
            printf("Using input color format YUV420P\n");
            dynParams.inputChromaFormat = XDM_YUV_420P;
            break;
        case ColorSpace_YUV422P:
            printf("Using input color format YUV422P\n");
            dynParams.inputChromaFormat = XDM_YUV_422P;
            break;
        case ColorSpace_YUV444P:
            printf("Using input color format YUV444P\n");
            dynParams.inputChromaFormat = XDM_YUV_444P;
            break;
        case ColorSpace_GRAY:
            printf("Using input color format GRAY\n");
            dynParams.inputChromaFormat = XDM_GRAY;
            break;
        default:
            printf("Unsupported input color space.\n");
            goto cleanup;        
    }
        
    /* Create the image encoder */
    hIe = Ienc_create(hEngine, args->codecName, &params, &dynParams);

    if (hIe == NULL) {
        printf("Failed to create image encoder: %s\n", args->codecName);
        goto cleanup;
    }

    /* Align buffers to cache line boundary */    
    gfxAttrs.bAttrs.memParams.align = bAttrs.memParams.align = BUFSIZEALIGN; 
    
    /* Use cached buffers if requested */    
    if (args->cache) {
        gfxAttrs.bAttrs.memParams.flags = bAttrs.memParams.flags 
            = Memory_CACHED;
    } 
    
    /* Calculate the buffer attributes */
    gfxAttrs.dim.width = args->width;
    gfxAttrs.dim.height = args->height;
    gfxAttrs.dim.lineLength = BufferGfx_calcLineLength(args->width, 
        args->iColorSpace);
    gfxAttrs.colorSpace = args->iColorSpace;

    inBufSize = Ienc_getInBufSize(hIe);

    /* Create input buffer */
    hInBuf = Buffer_create(Dmai_roundUp(inBufSize, BUFSIZEALIGN), 
        BufferGfx_getBufferAttrs(&gfxAttrs));

    if (hInBuf == NULL) {
        printf("Failed to allocate contiguous buffer\n");
        goto cleanup;
    }

    outBufSize = Ienc_getOutBufSize(hIe);

    /* Create output buffer */
    hOutBuf = Buffer_create(Dmai_roundUp(outBufSize, BUFSIZEALIGN), &bAttrs);

    if (hOutBuf == NULL) {
        printf("Failed to create contiguous buffer\n");
        goto cleanup;
    }

    printf("Reading input...\n");
  
    /* Read a yuv input frame */
    if (readFrame(hInBuf, inFile) < 0) {
        printf("Failed to read image from file\n");
        goto cleanup; 
    }
    
 
    printf("Encoding image...\n");  

    do {         
        if (args->benchmark) {
            if (Time_reset(hTime) < 0) {
                printf("Failed to reset timer\n");
                goto cleanup;
            }
        }
    
        if (args->cache) {
            /*  
             *  To meet xDAIS DMA Rule 7, when input buffers are cached, we 
             *  must writeback the cache into physical memory.  Also, per DMA 
             *  Rule 7, we must invalidate the output buffer from
             *  cache before providing it to any xDAIS algorithm.
             */
            Memory_cacheWbInv(Buffer_getUserPtr(hInBuf), Buffer_getSize(hInBuf));
        
            /* Per DMA Rule 7, our output buffer cache lines must be cleaned */
            Memory_cacheInv(Buffer_getUserPtr(hOutBuf), Buffer_getSize(hOutBuf));
        
            if (args->benchmark) {
                if (Time_delta(hTime, &time) < 0) {
                    printf("Failed to get timer delta\n");
                    goto cleanup;
                }
        
                printf("Pre-process cache maintenance: %uus \n", (Uns) time);
            }
        }
    
        /* Encode the image buffer */
        status = Ienc_process(hIe, hInBuf, hOutBuf);
        if (status < 0) {
            printf("Failed to encode image buffer\n");
            goto cleanup;
        }

        numFrame++;
        
        if (args->benchmark) {
            if (Time_delta(hTime, &time) < 0) {
                printf("Failed to get encode time\n");
                goto cleanup;
            }
    
            printf("[%d] Encode: %uus\n", numFrame, (Uns)time);
        }
    
        if (args->cache) {
            /* Writeback the outBuf. */
            Memory_cacheWb(Buffer_getUserPtr(hOutBuf), Buffer_getSize(hOutBuf));
        
            if (args->benchmark) {
                if (Time_delta(hTime, &time) < 0) {
                    printf("Failed to get timer delta\n");
                    goto cleanup;
                }
        
                printf("Post-process cache write back: %uus \n", (Uns) time);
            }
        }
            
        /* Write the encoded frame to the file system */
        if (Buffer_getNumBytesUsed(hOutBuf)) {
            if (fwrite(Buffer_getUserPtr(hOutBuf),
                       Buffer_getNumBytesUsed(hOutBuf), 1, outFile) != 1) {
                printf("Failed to write encoded image data to file\n");
                goto cleanup;
            }
        }
        
        totalBytes += Buffer_getNumBytesUsed(hOutBuf);
    } while (status != Dmai_EOK);
        
    if (args->benchmark) {
        if (Time_total(hTime, &time) < 0) {
            printf("Failed to get timer total\n");
            goto cleanup;
        }

        printf("Total: %uus\n", (unsigned int)time);
    }
            
    printf("Encode done \n");
    printf("Wrote encoded image of size %d to file \n", totalBytes);  
 
cleanup:
    /* Clean up the application */
    if (hOutBuf) {
        Buffer_delete(hOutBuf);
    }

    if (hInBuf) {
        Buffer_delete(hInBuf);
    }

    if (hIe) {
        Ienc_delete(hIe);
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

    if (hTime) {
        Time_delete(hTime);
    }

    printf("End of application.\n");
    
    return;
}
