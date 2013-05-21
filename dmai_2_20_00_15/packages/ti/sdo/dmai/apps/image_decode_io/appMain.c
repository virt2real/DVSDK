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
 * This application decodes an elementary stream image file using a specified
 * codec to a raw yuv file using an xDM 0.9 codec. The default format of the yuv
 * file is 422 interleaved.
 */

#include <stdio.h>

#include <xdc/std.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/CERuntime.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Time.h>
#include <ti/sdo/dmai/Buffer.h>
#include <ti/sdo/dmai/ColorSpace.h>
#include <ti/sdo/dmai/ce/Idec.h>
#include <ti/sdo/dmai/BufferGfx.h>

#include "appMain.h"

/* Align buffers to this cache line size (in bytes)*/
#define BUFSIZEALIGN            128

/* vbuf size that has been selected based on size/performance tradeoff */
#define VBUFSIZE                20480

static Char vbuffer[VBUFSIZE];

/******************************************************************************
 * writeFrameUYVY
******************************************************************************/
static Int writeFrameUYVY(Buffer_Handle hBuf, FILE *outFile)
{
    Int8 *ptr = Buffer_getUserPtr(hBuf);

    BufferGfx_Dimensions dim;

    BufferGfx_getDimensions(hBuf, &dim);

    if (fwrite(ptr, 1, dim.width * dim.height * 2, outFile) != 
        dim.width * dim.height * 2) {
      printf("Failed to write data to disk\n");
      return -1;
    }

    printf("Wrote UYVY frame size %d (%dx%d) to disk\n",
           (Int) (dim.width * 2 * dim.height),
           (Int) dim.width, (Int) dim.height);

    return 0;
}

/******************************************************************************
 * writeFramePlanar
******************************************************************************/
Int writeFramePlanar(Buffer_Handle hBuf, FILE *outFile)
{
    Int8   *yPtr, *cbcrPtr;        
    UInt32  ySize;                /* Size of Luma data */
    Uint32  cbcrSize;             /* Size of Chroma (cb and cr) data */
    Uint32  cbOffset, crOffSet;   
    Char   *colorFmt;
 
    BufferGfx_Dimensions dim;
    BufferGfx_getDimensions(hBuf, &dim);    

    /*  The three color planes are evenly spaced in the output buffer. Each 
     *  plane has been allocated a size equal to the input creation parameter 
     *  maxWidth x maxHeight.              
     */     
    cbOffset = Buffer_getSize(hBuf) * 1/3;
    crOffSet = Buffer_getSize(hBuf) * 2/3;
    
    ySize = dim.width * dim.height;
    
    switch(BufferGfx_getColorSpace(hBuf)){
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
           printf("Unsupported output color space.\n");
           return -1;        
    }    

    /* Write Y plane */
    yPtr = Buffer_getUserPtr(hBuf);
    if (fwrite(yPtr, 1, ySize, outFile) != ySize ) {
        printf("Failed to write y data to disk\n");
        return -1;
    }

    /* Write Cb plane */
    cbcrPtr = Buffer_getUserPtr(hBuf) + cbOffset;   
    if (fwrite(cbcrPtr, 1, cbcrSize / 2 , outFile) != cbcrSize / 2 ) {
        printf("Failed to write y data to disk\n");
        return -1;
    }

    /* Write Cr plane */
    cbcrPtr = Buffer_getUserPtr(hBuf) + crOffSet;
    if (fwrite(cbcrPtr, 1, cbcrSize / 2  , outFile) != cbcrSize / 2 ) {
        printf("Failed to write y data to disk\n");
        return -1;
    }

    printf("Wrote %s image size %d (%dx%d) to disk\n",
           colorFmt, 
           (Int) (ySize + cbcrSize),
           (Int) dim.width, (Int) dim.height);

    return 0;
}

/******************************************************************************
 * appMain
 ******************************************************************************/
Void appMain(Args * args)
{
    IMGDEC_Params           params       = Idec_Params_DEFAULT;
    IMGDEC_DynamicParams    dynParams    = Idec_DynamicParams_DEFAULT;
    Buffer_Attrs            bAttrs       = Buffer_Attrs_DEFAULT;
    BufferGfx_Attrs         gfxAttrs     = BufferGfx_Attrs_DEFAULT;
    Time_Attrs              tAttrs       = Time_Attrs_DEFAULT;   
    Idec_Handle             hId          = NULL;
    Engine_Handle           hEngine      = NULL;
    Time_Handle             hTime        = NULL;
    Buffer_Handle           hInBuf       = NULL;
    Buffer_Handle           hOutBuf      = NULL;
    FILE                   *outFile      = NULL;
    FILE                   *inFile       = NULL;
    Int                     numBytes     = 0;
    Int                     ret          = Dmai_EOK;
    UInt32                  time;

    printf("Starting application...\n");
    
    if (args->benchmark) {
        hTime = Time_create(&tAttrs);

        if (hTime == NULL) {
            printf("Failed to create Time object\n");
            goto cleanup;
        }
    }

    /* Initialize the codec engine run time */
    CERuntime_init();

    /* Initialize DMAI */
    Dmai_init();

    /* Open input file */
    inFile = fopen(args->inFile, "rb");

    if (inFile == NULL) {
        printf("Failed to open file %s\n", args->inFile);
        goto cleanup;
    }
    
    /* Open output file */
    outFile = fopen(args->outFile, "wb");
    
    if (outFile == NULL) {
        printf("Failed to create output file %s\n", args->outFile);
        goto cleanup;
    }

    /* Using a larger vbuf to enhance performance of file i/o */
    if (setvbuf(outFile, vbuffer, _IOFBF, sizeof(vbuffer)) != 0) {
        printf("Failed to setvbuf on file descriptor\n");
        goto cleanup;   
    }
    
    /* Open the codec engine */
    hEngine = Engine_open(args->engineName, NULL, NULL);

    if (hEngine == NULL) {
        printf("Failed to open codec engine %s\n", args->engineName);
        goto cleanup;
    }
    
    /*
     * Set output color format to UYVY or Planar output.
     * Here XDM_DEFUALT sets the output planar format to
     * the planar fromat of the encoded image.
     *           
     */
    if (args->oColorSpace == ColorSpace_UYVY){
        params.forceChromaFormat = XDM_YUV_422ILE;
    }
    else{
        params.forceChromaFormat = XDM_DEFAULT;
    }

    /* Create the image decoder */
    hId = Idec_create(hEngine, args->codecName, &params, &dynParams);

    if (hId == NULL) {
        printf("Failed to create image decoder: %s\n", args->codecName);
        goto cleanup;
    }

    /* Align buffers to cache line boundary */    
    gfxAttrs.bAttrs.memParams.align = bAttrs.memParams.align = BUFSIZEALIGN; 
    
    /* Use cached buffers if requested */    
    if (args->cache) {
        gfxAttrs.bAttrs.memParams.flags = bAttrs.memParams.flags 
            = Memory_CACHED;
    } 

    gfxAttrs.colorSpace     = args->oColorSpace;
    gfxAttrs.dim.width      = params.maxWidth;
    gfxAttrs.dim.height     = params.maxHeight;
    gfxAttrs.dim.lineLength = BufferGfx_calcLineLength(params.maxWidth,
                                                       gfxAttrs.colorSpace);

    /* Create an output buffer for decoded data */
    hOutBuf = Buffer_create(Dmai_roundUp(Idec_getOutBufSize(hId), BUFSIZEALIGN),
                            BufferGfx_getBufferAttrs(&gfxAttrs));

    if (hOutBuf == NULL) {
        printf("Failed to create contiguous buffers\n");
        goto cleanup;
    }

    /* Create an input buffer for encoded data */
    hInBuf = Buffer_create(Dmai_roundUp(Idec_getInBufSize(hId), BUFSIZEALIGN), 
        &bAttrs);

    if (hInBuf == NULL) {
        printf("Failed to create contiguous buffers\n");
        goto cleanup;
    }
   
    /* Read encoded image data */
    numBytes = fread(Buffer_getUserPtr(hInBuf), 1,
                     Idec_getInBufSize(hId), inFile);
                     
    Buffer_setNumBytesUsed(hInBuf, numBytes);

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

    /* Decode the image frame */
    ret = Idec_process(hId, hInBuf, hOutBuf);
    
    if (ret < 0) {
        printf("Failed to decode image buffer\n");
        goto cleanup;
    }
    
    if (args->benchmark) {
        if (Time_delta(hTime, &time) < 0) {
            printf("Failed to get timer delta\n");
            goto cleanup;
        }
    
        printf("Frame - Decode: %uus \n", (unsigned int)time);
    }
    
    if (args->cache) {
        /* Writeback the outBuf. */
        Memory_cacheWb(Buffer_getUserPtr(hOutBuf), Buffer_getSize(hOutBuf));
    
        if (args->benchmark) {
            if (Time_delta(hTime, &time) < 0) {
                printf("Failed to get timer delta\n");
                goto cleanup;
            }
    
            printf("Post-process cache write back: %uus ", (Uns) time);
        }
    }
    
    /* Write decoded image to a file */
    if (BufferGfx_getColorSpace(hOutBuf) == ColorSpace_UYVY){
        if (writeFrameUYVY(hOutBuf, outFile) < 0) {
           printf("Failed to write image to file\n");
           goto cleanup; 
       }
    }
    else if (BufferGfx_getColorSpace(hOutBuf) == ColorSpace_YUV420P
             || ColorSpace_YUV422P || ColorSpace_YUV444P || ColorSpace_GRAY ){
        /* For XDM_GRAY ignoring the color planes */
        if (args->oColorSpace == ColorSpace_GRAY){
            BufferGfx_setColorSpace (hOutBuf, ColorSpace_GRAY); 
        }    
        if (writeFramePlanar(hOutBuf, outFile) < 0) {
           printf("Failed to write image to file\n");
           goto cleanup; 
       }
    }
    else {
        printf("Invalid output colorspace.\n");
        goto cleanup;     
    }
    
    if (args->benchmark) {
        if (Time_total(hTime, &time) < 0) {
            printf("Failed to get timer total\n");
            goto cleanup;
        }
    
        printf("Total: %uus\n", (unsigned int)time);
    }
       
cleanup:
    /* Clean up the application */
    if (hId) {
        Idec_delete(hId);
    }
    
    if (hInBuf) {
        Buffer_delete(hInBuf);
    }

    if (hOutBuf) {
        Buffer_delete(hOutBuf);
    }

    if (hEngine) {
        Engine_close(hEngine);
    }

    if (hTime) {
        Time_delete(hTime);
    }

    if (inFile) {
        fclose(inFile);
    }
 
    if (outFile) {
        fclose(outFile);
    }
    
    printf("End of application.\n");
    
    return;
}
