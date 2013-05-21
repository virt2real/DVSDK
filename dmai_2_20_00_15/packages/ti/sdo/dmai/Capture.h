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
 * @defgroup   ti_sdo_dmai_Capture   Capture
 *
 * @brief Creates an interface instance to the capture device driver. This
 *        module will allow you to get and return capture buffers from the v4l2
 *        capture device. All platforms support the driver allocating it's own
 *        buffers, and some (like dm6467) support the user allocating contiguous
 *        buffers using CMEM and passing them in at creation. Typical use case
 *        for driver allocated buffers (dm6446 video window 0):
 *
 * @code
 *   #include <xdc/std.h>
 *   #include <ti/sdo/dmai/Dmai.h>
 *   #include <ti/sdo/dmai/Capture.h>
 *   #include <ti/sdo/dmai/BufferGfx.h>
 *   BufferGfx_Handle cBuf;
 *   Capture_Attrs cAttrs = Capture_Attrs_DM6446_DM355_DEFAULT;
 *   Capture_Handle hCapture;
 *
 *   Dmai_init();
 *   hCapture = Capture_create(NULL, &cAttrs);
 *   while (1) {
 *       Capture_get(hCapture, &cBuf);
 *       // Process captured buffer "cBuf".
 *       Capture_put(hCapture, cBuf);
 *   }
 *   Capture_delete(hCapture);
 * @endcode
 */

#ifndef ti_sdo_dmai_Capture_h_
#define ti_sdo_dmai_Capture_h_

#include <xdc/std.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/BufTab.h>
#include <ti/sdo/dmai/VideoStd.h>
#include <ti/sdo/dmai/BufferGfx.h>
#include <ti/sdo/dmai/ColorSpace.h>

/** @ingroup    ti_sdo_dmai_Capture */
/*@{*/

/**
 * @brief       Video capture inputs.
 */
typedef enum {
    /** @brief S-Video video input */
    Capture_Input_SVIDEO = 0,

    /** @brief Composite video input */
    Capture_Input_COMPOSITE,

    /** @brief Component video input */
    Capture_Input_COMPONENT,

    /** @brief Camera/Imager card video input 
      * @remarks only applicable on DM368
      */
    Capture_Input_CAMERA,

    Capture_Input_COUNT
} Capture_Input;

/**
 * @brief Attributes used to create a Capture device driver instance.
 *
 * @see Capture_Attrs_DM6446_DM355_DEFAULT
 * @see Capture_Attrs_DM6467_DEFAULT
 */
typedef struct Capture_Attrs {
    /** @brief Number of buffers the driver is to use, either allocated
      * from the device driver or the supplied #BufTab_Handle. */
    Int                numBufs;

    /** @brief Which video input to use. */
    Capture_Input      videoInput;

    /** @brief Width of image to crop (if supported by H/W, otherwise ignored).
      * If set to a negative value, no cropping will be used. This value needs
      * to be even. */
    Int32              cropWidth;

    /** @brief Height of image to crop (if supported by H/W, otherwise ignored).
      * If set to a negative value, no cropping will be used. */
    Int32              cropHeight;

    /** @brief X pos of image to crop (if supported by H/W, otherwise ignored).
      * If set to a negative value, no cropping will be used. */
    Int32              cropX;

    /** @brief Y pos of image to crop (if supported by H/W, otherwise ignored).
      * If set to a negative value, no cropping will be used. */
    Int32              cropY;

    /** @brief Name of the Linux v4l2 capture device to use.
      *
      * @remarks Only applicable on Linux.
      */
    Char              *captureDevice;

    /** @brief When using the dm6446 resizer to @ref ti_sdo_dmai_Smooth the
      * captured images, 2 extra rows at the top and 4 extra rows at the
      * bottom needs to be captured (if possible).
      *
      * @remarks Only applicable for dm6446 / dm357 Linux.
      */
    Bool               smoothPad;

    /** @brief To force a certain video standard without auto detection,
      * set this variable to something other than #VideoStd_AUTO.
      */
    VideoStd_Type      videoStd;

    /** @brief To force a certain decoder on dm6467 instead of
      * auto detecting which decoder supports your #Capture_Attrs.videoInput,
      * set this to a value > -1. See the VPIF device driver guide on which
      * values apply (VIDIOC_S_STD ioctl). This is useful when auto detection
      * doesn't work, e.g. when two EVM:s are interconnected.
      *
      * @remarks The detected #Capture_Input on the decoder still needs to
      * correspond to the #Capture_Attrs.videoInput set, or the function will
      * fail.
      * @remarks Only applicable for dm6467 Linux.
      */
    Int                decoderIdx;
    
    /** @brief Output color format
      *
      * @remarks Only applicable for dm365 Linux.
      */    
    ColorSpace_Type    colorSpace;

    /** @brief  Capture image size
      *         
      * @remarks Only height and width elements are used. 
      * @remarks Set it to NULL, if resolution needs to be auto detected.
      * @remarks Only applicable for dm365 Linux.      
      */    
    BufferGfx_Dimensions *captureDimension;

    /** @brief Set the resizer/previewer to "on the fly mode". In this
      * mode the capture device is chained with previewer/resizer to resize
      * and do chroma conversion on the fly.
      *
      * @remarks Only applicable for dm365 Linux.
      * @remarks If this flag is set for composite input, the captured
      * frames will be de-interlaced automatically.
      * @remarks If this flag is enabled the kernel command line parameter
      * dm365_imp.oper_mode should be set to '1', otherwise '0'.
      */
     Bool onTheFly;
} Capture_Attrs;

/**
 * @brief Handle through which to reference a Capture device instance.
 */
typedef struct Capture_Object *Capture_Handle;

/**
 * @brief Default attributes for video window 0 on dm6446 and dm355.
 * @code
 * numBufs          = 3,
 * videoInput       = Capture_Input_COMPOSITE,
 * cropWidth        = -1,
 * cropHeight       = -1,
 * cropX            = -1,
 * cropY            = -1,
 * captureDevice    = "/dev/video0",
 * smoothPad        = FALSE,
 * videoStd         = VideoStd_AUTO,
 * decoderIdx       = -1,
 * colorSpace       = ColorSpace_UYVY,
 * captureDimension = NULL,
 * onTheFly         = FALSE
 * @endcode
 */
extern const Capture_Attrs Capture_Attrs_DM6446_DM355_DEFAULT;

/**
 * @brief Default attributes for video window 0 on dm6467.
 * @code
 * numBufs          = 3,
 * videoInput       = Capture_Input_COMPONENT,
 * cropWidth        = -1,
 * cropHeight       = -1,
 * cropX            = -1,
 * cropY            = -1,
 * captureDevice    = "/dev/video0",
 * smoothPad        = FALSE,
 * videoStd         = VideoStd_AUTO,
 * decoderIdx       = -1
 * colorSpace       = ColorSpace_YUV422PSEMI,
 * captureDimension = NULL,
 * onTheFly         = FALSE
 * @endcode
 */
extern const Capture_Attrs Capture_Attrs_DM6467_DEFAULT;

/**
 * @brief Default attributes for video window 0 on dm365.
 * @code
 * numBufs          = 3,
 * videoInput       = Capture_Input_COMPONENT,
 * cropWidth        = -1,
 * cropHeight       = -1,
 * cropX            = -1,
 * cropY            = -1,
 * captureDevice    = "/dev/video0",
 * smoothPad        = FALSE,
 * videoStd         = VideoStd_AUTO,
 * decoderIdx       = -1
 * colorSpace       = ColorSpace_YUV420PSEMI,
 * captureDimension = NULL,
 * onTheFly         = TRUE
 * @endcode
 */
extern const Capture_Attrs Capture_Attrs_DM365_DEFAULT;

/**
 * @brief Default attributes for video window 0 on omapl138.
 * @code
 * numBufs          = 3,
 * videoInput       = Capture_Input_COMPOSITE,
 * cropWidth        = -1,
 * cropHeight       = -1,
 * cropX            = -1,
 * cropY            = -1,
 * captureDevice    = "/dev/video0",
 * smoothPad        = FALSE,
 * videoStd         = VideoStd_AUTO,
 * decoderIdx       = -1
 * colorSpace       = ColorSpace_YUV422PSEMI,
 * captureDimension = NULL,
 * onTheFly         = FALSE
 * @endcode
 */
extern const Capture_Attrs Capture_Attrs_OMAPL138_DEFAULT;

/**
 * @brief Default attributes for video window 0 on omap3530.
 * @code
 * numBufs          = 3,
 * videoInput       = Capture_Input_COMPOSITE,
 * cropWidth        = -1,
 * cropHeight       = -1,
 * cropX            = -1,
 * cropY            = -1,
 * captureDevice    = "/dev/video0",
 * smoothPad        = FALSE,
 * videoStd         = VideoStd_AUTO,
 * decoderIdx       = -1
 * colorSpace       = ColorSpace_UYVY,
 * captureDimension = NULL,
 * onTheFly         = FALSE
 * @endcode
 */
extern const Capture_Attrs Capture_Attrs_OMAP3530_DEFAULT;

#if defined (__cplusplus)
extern "C" {
#endif

/**
 * @brief       Creates a Capture driver instance.
 *
 * @param[in]   hBufTab     The BufTab with buffers to use with the capture
 *                          device. If NULL is passed, the capture driver will
 *                          allocate it's own buffers.
 *
 * @param[in]   attrs       #Capture_Attrs to use for creating the Capture
 *                          driver instance.
 *
 * @retval      Handle for use in subsequent operations (see #Capture_Handle).
 * @retval      NULL for failure.
 */
extern Capture_Handle Capture_create(BufTab_Handle hBufTab,
                                     Capture_Attrs *attrs);

/**
 * @brief       Detects the video standard of the input connected to a video
 *             
 * @param[in]   hCapture    The #Capture_Handle of the device driver instance
 *                          to get the video standard of. If this is set to
 *                          NULL a temporary instance will be created for this
 *                          call.
 * @param[out]  videoStdPtr The #VideoStd_Type of the capture device will be
 *                          returned here.
 *
 * @param[in]   attrs       #Capture_Attrs which will be used to create the
 *                          capture driver instance.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 */
extern Int Capture_detectVideoStd(Capture_Handle hCapture,
                                  VideoStd_Type *videoStdPtr,
                                  Capture_Attrs *attrs);
/**
 * @brief       Receive a captured buffer from the capture device driver.
 *
 * @param[in]   hCapture    The #Capture_Handle to get a buffer from.
 * @param[out]  hBufPtr     A pointer to the #Buffer_Handle received.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Capture_create must be called before this function.
 */
extern Int Capture_get(Capture_Handle hCapture, Buffer_Handle *hBufPtr);

/**
 * @brief       Send a captured buffer to the capture device driver instance
 *              to be filled with captured data.
 *
 * @param[in]   hCapture    The #Capture_Handle to send a buffer to.
 * @param[in]   hBuf        A #Buffer_Handle to send to the capture device.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Capture_create must be called before this function.
 */
extern Int Capture_put(Capture_Handle hCapture, Buffer_Handle hBuf);

/**
 * @brief       Deletes a Capture device driver instance.
 *
 * @param[in]   hCapture    The #Capture_Handle to delete.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Capture_create must be called before this function.
 */
extern Int Capture_delete(Capture_Handle hCapture);

/**
 * @brief       Get the #VideoStd_Type of a previously created Capture
 *              device driver instance.
 *
 * @param[in]   hCapture    The #Capture_Handle to get #VideoStd_Type of.
 *
 * @retval      #VideoStd_Type used by Capture device driver.
 *
 * @remarks     #Capture_create must be called before this function.
 */
extern VideoStd_Type Capture_getVideoStd(Capture_Handle hCapture);

/**
 * @brief       Get the #BufTab_Handle of a previously created Capture
 *              device driver instance.
 *
 * @param[in]   hCapture    The #Capture_Handle to get the #BufTab_Handle from.
 *
 * @retval      #VideoStd_Type used by Capture device driver.
 *
 * @remarks     #Capture_create must be called before this function.
 */
extern BufTab_Handle Capture_getBufTab(Capture_Handle hCapture);

#if defined (__cplusplus)
}
#endif

/*@}*/

#endif /* ti_sdo_dmai_Capture_h_ */
