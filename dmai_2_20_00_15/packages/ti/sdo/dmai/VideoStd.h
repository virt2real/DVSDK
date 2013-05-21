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
 * @defgroup   ti_sdo_dmai_VideoStd     VideoStd
 *
 * @brief This module describes the video standards (D1 NTSC, D1 PAL, 720P,
 *        1080I etc.) used by the various DMAI modules. It has no state,
 *        so no creation of an instance is required.
 */

#ifndef ti_sdo_dmai_VideoStd_h_
#define ti_sdo_dmai_VideoStd_h_

#include <ti/sdo/dmai/Dmai.h>

/** @ingroup    ti_sdo_dmai_VideoStd */
/*@{*/
#define VideoStd_QVGA_WIDTH       320     /**< Width in pixels of QVGA */
#define VideoStd_QVGA_HEIGHT      240     /**< Height in pixels of QVGA */

#define VideoStd_CIF_WIDTH       352     /**< Width in pixels of CIF */
#define VideoStd_CIF_HEIGHT      288     /**< Height in pixels of CIF */

#define VideoStd_SIF_WIDTH       352     /**< Width in pixels of SIF */
#define VideoStd_SIF_NTSC_HEIGHT 240     /**< Height in pixels of SIF NTSC */
#define VideoStd_SIF_PAL_HEIGHT  288     /**< Height in pixels of SIF PAL */

#define VideoStd_VGA_WIDTH       640     /**< Width in pixels of VGA */
#define VideoStd_VGA_HEIGHT      480     /**< Height in pixels of VGA */

#define VideoStd_D1_WIDTH        720     /**< Width in pixels of D1 */
#define VideoStd_D1_NTSC_HEIGHT  480     /**< Height in pixels of D1 NTSC */
#define VideoStd_D1_PAL_HEIGHT   576     /**< Height in pixels of D1 PAL */

#define VideoStd_480P_WIDTH      720     /**< Width in pixels for 480P */
#define VideoStd_480P_HEIGHT     480     /**< Height in pixels for 480P */

#define VideoStd_576P_WIDTH      720     /**< Width in pixels for 576P */
#define VideoStd_576P_HEIGHT     576     /**< Height in pixels for 576P */

#define VideoStd_720P_WIDTH      1280    /**< Width in pixels of 720P */
#define VideoStd_720P_HEIGHT     720     /**< Height in pixels of 720P */

#define VideoStd_1080I_WIDTH     1920    /**< Width in pixels of 1080I */
#define VideoStd_1080I_HEIGHT    1080    /**< Height in pixels of 1080I */

#define VideoStd_1080P_WIDTH     1920    /**< Width in pixels of 1080P */
#define VideoStd_1080P_HEIGHT    1080    /**< Height in pixels of 1080P */

/*
 * WARNING! When adding a member to this enumerated type, make sure you
 * add members to the arrays in linux/Capture.c and linux/Display.c.
 */

/** @brief Video standards */
typedef enum {
    VideoStd_AUTO = 0,      /**< Automatically select standard (if supported) */
    VideoStd_CIF,           /**< CIF @ 30 frames per second */
    VideoStd_SIF_NTSC,      /**< SIF @ 30 frames per second */
    VideoStd_SIF_PAL,       /**< SIF @ 25 frames per second */
    VideoStd_VGA,           /**< VGA (640x480) @ 60 frames per second */
    VideoStd_D1_NTSC,       /**< D1 NTSC @ 30 frames per second */
    VideoStd_D1_PAL,        /**< D1 PAL @ 25 frames per second */
    VideoStd_480P,          /**< D1 Progressive NTSC @ 60 frames per second */
    VideoStd_576P,          /**< D1 Progressive PAL @ 50 frames per second */
    VideoStd_720P_60,       /**< 720P @ 60 frames per second */
    VideoStd_720P_50,       /**< 720P @ 50 frames per second */
    VideoStd_720P_30,       /**< 720P @ 30 frames per second */
    VideoStd_1080I_30,      /**< 1080I @ 30 frames per second */
    VideoStd_1080I_25,      /**< 1080I @ 25 frames per second */
    VideoStd_1080P_30,      /**< 1080P @ 30 frames per second */
    VideoStd_1080P_25,      /**< 1080P @ 25 frames per second */
    VideoStd_1080P_24,      /**< 1080P @ 24 frames per second */
    VideoStd_QVGA,          /**< QVGA @ 30 frames per second */
    VideoStd_1080P_60,      /**< 1080P @ 60 frames per second */
    VideoStd_1080P_50,      /**< 1080P @ 50 frames per second */    
    VideoStd_1080I_60,      /**< 1080I @ 60 frames per second */    
    VideoStd_COUNT
} VideoStd_Type;

#if defined (__cplusplus)
extern "C" {
#endif

/**
 * @brief       Returns the resolution of a given video standard.
 *
 * @param[in]   videoStd        The #VideoStd_Type to return the resolution of.
 * @param[out]  widthPtr        A pointer to where the width is returned.
 * @param[out]  heightPtr       A pointer to where the height is returned.
 *
 * @retval      Dmai_EOK on success.
 * @retval      "Negative value" for failure, see Dmai.h.
 */
extern Int VideoStd_getResolution(VideoStd_Type videoStd,
                                  Int32 *widthPtr, Int32 *heightPtr);

#if defined (__cplusplus)
}
#endif

/*@}*/

#endif /* ti_sdo_dmai_VideoStd_h_ */
