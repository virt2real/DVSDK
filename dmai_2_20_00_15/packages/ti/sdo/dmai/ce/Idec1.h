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

/**
 * @defgroup   ti_sdo_dmai_Idec1    Idec1
 *
 * @brief Provides a simple interface to IMGDEC1 (XDM 1.0) based algorithms.
 *        Typical usage (JPEG, no error checking):
 *
 * @code
 *     #include <stdio.h>
 *     #include <xdc/std.h>
 *     #include <ti/sdo/ce/Engine.h>
 *     #include <ti/sdo/ce/CERuntime.h>
 *     #include <ti/sdo/dmai/Dmai.h>
 *     #include <ti/sdo/dmai/Buffer.h>
 *     #include <ti/sdo/dmai/Loader.h>
 *     #include <ti/sdo/dmai/ColorSpace.h>
 *     #include <ti/sdo/dmai/ce/Idec1.h>
 *     #include <ti/sdo/dmai/BufferGfx.h>
 *     
 *     IMGDEC1_Params          params       = Idec1_Params_DEFAULT;
 *     IMGDEC1_DynamicParams   dynParams    = Idec1_DynamicParams_DEFAULT;
 *     Buffer_Attrs            bAttrs       = Buffer_Attrs_DEFAULT;
 *     BufferGfx_Attrs         gfxAttrs     = BufferGfx_Attrs_DEFAULT;
 *     Idec1_Handle            hId          = NULL;
 *     Engine_Handle           hEngine      = NULL;
 *     Buffer_Handle           hInBuf       = NULL;
 *     Buffer_Handle           hOutBuf      = NULL;
 *     Int                     numBytes     = 0;
 *     FILE                    *inFile; 
 *        
 *     CERuntime_init();
 *     Dmai_init();
 *     hEngine = Engine_open("myengine", NULL, NULL);
 *     hId = Idec1_create(hEngine, "jpegdec", &params, &dynParams);
 *     gfxAttrs.colorSpace     = ColorSpace_UYVY;
 *     gfxAttrs.dim.width      = params.maxWidth;
 *     gfxAttrs.dim.height     = params.maxHeight;
 *     gfxAttrs.dim.lineLength = BufferGfx_calcLineLength(params.maxWidth, 
 *                                                        gfxAttrs.colorSpace);
 *     hOutBuf = Buffer_create(Idec1_getOutBufSize(hId), 
 *                             BufferGfx_getBufferAttrs(&gfxAttrs));
 *     hInBuf = Buffer_create(Idec1_getInBufSize(hId), &bAttrs);
 *     numBytes = fread(Buffer_getUserPtr(hInBuf), 1, Idec1_getInBufSize(hId), 
 *                      inFile);
 *     Buffer_setNumBytesUsed(hInBuf, numBytes);       
 *     Idec1_process(hId, hInBuf, hOutBuf);
 *      
 *     Buffer_delete(hOutBuf);
 *     Buffer_delete(hInBuf); 
 *     Idec1_delete(hId);
 *     Engine_close(hEngine);
 *     fclose(inFile); 
 * @endcode       
 */
 
#ifndef ti_sdo_dmai_ce_Idec1_h_
#define ti_sdo_dmai_ce_Idec1_h_

#include <xdc/std.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/image1/imgdec1.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Buffer.h>

/** @ingroup    ti_sdo_dmai_Idec1 */
/*@{*/

/**
 * @brief       Handle through which to reference an Image Decode algorithm.
 */
typedef struct Idec1_Object *Idec1_Handle;

/**
 * @brief       Default XDM parameters for an Image Decode algorithm.
 * @code
 *     size                 = sizeof(IMGDEC1_Params),
 *     maxHeight            = 576,
 *     maxWidth             = 720,
 *     maxScans             = 15,
 *     dataEndianness       = XDM_BYTE,
 *     forceChromaFormat    = XDM_YUV_422ILE,
 * @endcode
 */
extern const IMGDEC1_Params Idec1_Params_DEFAULT;

/**
 * @brief       Default XDM dynamic parameters for an Image Decode algorithm.
 * @code
 *     size                 = sizeof(IMGDEC1_DynamicParams),
 *     numAU                = XDM_DEFAULT, 
 *     decodeHeader         = XDM_DECODE_AU,
 *     displayWidth         = 0,
 * @endcode
 */
extern const IMGDEC1_DynamicParams Idec1_DynamicParams_DEFAULT;

#if defined (__cplusplus)
extern "C" {
#endif

/**
 * @brief       Creates an Image Decode (XDM 1.0) algorithm instance.
 *
 * @param[in]   hEngine     An opened engine containing the algorithm to create.
 * @param[in]   codecName   The name of the algorithm to open. Corresponds to
 *                          the string name given in the .cfg file.
 * @param[in]   params      XDM parameters to use while creating the codec.
 * @param[in]   dynParams   XDM dynamic parameters to use while creating the
 *                          codec. 
 *
 * @retval      Handle for use in subsequent operations (see #Idec1_Handle).
 * @retval      NULL for failure.
 */
extern Idec1_Handle Idec1_create(Engine_Handle hEngine,
                               Char *codecName,
                               IMGDEC1_Params *params,
                               IMGDEC1_DynamicParams *dynParams);

/**
 * @brief       Decodes an image buffer.
 *
 * @param[in]   hId         The #Idec1_Handle to use for decoding.
 * @param[in]   hInBuf      The #Buffer_Handle for the buffer containing the
 *                          encoded data.
 * @param[in]   hOutBuf     The #Buffer_Handle for the buffer to fill with
 *                          decoded data.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Idec1_create must be called before this function.
 */
extern Int Idec1_process(Idec1_Handle hId, Buffer_Handle hInBuf,
                        Buffer_Handle hOutBuf);

/**
 * @brief       Deletes an Image Decode algorithm instance.
 *
 * @param[in]   hId         The #Idec1_Handle to delete.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Idec1_create must be called before this function.
 */
extern Int Idec1_delete(Idec1_Handle hId);

/**
 * @brief       Get the IMGDEC1 handle from the Idec1 module instance.
 *
 * @param[in]   hId         The #Idec1_Handle for which to get the IMGDEC1 handle.
 *
 * @retval      Handle to the image decode algorithm, see the XDM documentation
 *              for IMGDEC1.
 *
 * @remarks     #Idec1_create must be called before this function.
 */
extern IMGDEC1_Handle Idec1_getVisaHandle(Idec1_Handle hId);

/**
 * @brief       Get the input buffer size required by the codec.
 *
 * @param[in]   hId         The #Idec1_Handle for which to get the buffer size.
 *
 * @retval      Size in bytes of the input buffer required.
 *
 * @remarks     #Idec1_create must be called before this function.
 */
extern Int32 Idec1_getInBufSize(Idec1_Handle hId);

/**
 * @brief       Get the output buffer size required by the codec.
 *
 * @param[in]   hId         The #Idec1_Handle for which to get the buffer size.
 *
 * @retval      Size in bytes of the output buffer required.
 *
 * @remarks     #Idec1_create must be called before this function.
 */
extern Int32 Idec1_getOutBufSize(Idec1_Handle hId);

#if defined (__cplusplus)
}
#endif

/*@}*/

#endif /* ti_sdo_dmai_ce_Idec1_h_ */
 
