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
 * @defgroup   ti_sdo_dmai_Sound    Sound
 *
 * @brief Implements an interface to the sound device driver. This will allow
 *        you to read and write data to the sound device driver. Typical usage
 *        of this module (mono loopback example, no error checking):
 *
 * @code
 *   #include <xdc/std.h>
 *   #include <ti/sdo/dmai/Dmai.h>
 *   #include <ti/sdo/dmai/Sound.h>
 *   #include <ti/sdo/dmai/Buffer.h>
 *   Buffer_Attrs bAttrs = Buffer_Attrs_DEFAULT;
 *   Sound_Attrs sAttrs = Sound_Attrs_MONO_DEFAULT;
 *   Buffer_Handle hBuf;
 *   Sound_Handle hSound;
 *
 *   Dmai_init();
 *   hBuf = Buffer_create(1024, &bAttrs);
 *   hSound = Sound_create(&sAttrs);
 *   while (1) {
 *       Sound_read(hSound, hBuf);
 *       // Process read data in hBuf.
 *       Sound_write(hSound, hBuf);
 *   }
 *   Sound_delete(hSound);
 *   Buffer_delete(hBuf);
 * @endcode
 */

#ifndef ti_sdo_dmai_Sound_h_
#define ti_sdo_dmai_Sound_h_

#include <xdc/std.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Buffer.h>

/** @ingroup    ti_sdo_dmai_Sound */
/*@{*/

/**
 * @brief       Max number of characters in the sound device name.
 */
#define Sound_MAXDEVNAME 20

/**
 * @brief       Sound standards supported on Linux (OSS and ALSA).
 */
typedef enum {
    /** @brief OSS sound standard */
    Sound_Std_OSS = 0,

    /** @brief ALSA sound standard */
    Sound_Std_ALSA,

    Sound_Std_COUNT
} Sound_Std;

/**
 * @brief       Sound device driver opened for reading, writing or both.
 */
typedef enum {
    /** @brief Output only */
    Sound_Mode_OUTPUT,

    /** @brief Output only */
    Sound_Mode_INPUT,

    /** @brief Both input and output (if supported) */
    Sound_Mode_FULLDUPLEX,

    Sound_Mode_COUNT
} Sound_Mode;

/**
 * @brief       Sound inputs.
 */
typedef enum {
    /** @brief Microphone input */
    Sound_Input_MIC,

    /** @brief Line in input */
    Sound_Input_LINE,

    Sound_Input_COUNT
} Sound_Input;

/**
 * @brief       Handle through which to reference a Sound device driver.
 */
typedef struct Sound_Object *Sound_Handle;

/**
 * @brief       Attributes used to create a Sound device driver instance.
 * @see         Sound_Attrs_STEREO_DEFAULT
 * @see         Sound_Attrs_MONO_DEFAULT
 */
typedef struct Sound_Attrs {
    /** @brief Sample rate of the sound device. */
    Int32                sampleRate;

    /** @brief Number of channels (1 for mono or 2 for stereo supported). */
    Int                  channels;

    /** @brief Gain between 0-100 of the left channel */
    Int32                leftGain;

    /** @brief Gain between 0-100 of the right channel */
    Int32                rightGain;

    /** @brief Sound device driver opened for input, output or both */
    Sound_Mode           mode;

    /** @brief Select which input to use */
    Sound_Input          soundInput;

    /** @brief Device driver standard to use. (see #Sound_Std). 
      *
      * @remarks Only applicable on Linux.
      */
    Sound_Std            soundStd;

    /** @brief Maximum input and (or) output buffer size. 
      * 
      * @remarks Only applicable for ALSA.
      */
    Int                  bufSize;
} Sound_Attrs;

/**
 * @brief       Default attributes for a stereo Sound device driver.
 * @code
 *    sampleRate        = 44100,
 *    channels          = 2,
 *    leftGain          = 100,
 *    rightGain         = 100,
 *    mode              = Sound_Mode_FULLDUPLEX,
 *    soundInput        = Sound_Input_MIC,
 *    bufSize           = 4096,
 * @endcode
 */
extern const Sound_Attrs Sound_Attrs_STEREO_DEFAULT;

/**
 * @brief       Default attributes for a mono Sound device driver.
 * @code
 *    sampleRate        = 8000,
 *    channels          = 1,
 *    leftGain          = 100,
 *    rightGain         = 100,
 *    mode              = Sound_Mode_FULLDUPLEX,
 *    soundInput        = Sound_Input_MIC,
 *    bufSize           = 4096,
 * @endcode
 */
extern const Sound_Attrs Sound_Attrs_MONO_DEFAULT;

#if defined (__cplusplus)
extern "C" {
#endif

/**
 * @brief       Creates a Sound device driver instance.
 *
 * @param[in]   attrs       #Sound_Attrs to use for creating the Sound
 *                          device driver instance.
 *
 * @retval      Handle for use in subsequent operations (see #Sound_Handle).
 * @retval      NULL for failure.
 */
extern Sound_Handle Sound_create(Sound_Attrs *attrs);

/**
 * @brief       Write a buffer to the sound output. This function can only
 *              be called if the driver was opened for writing.
 *
 * @param[in]   hSound      The #Sound_Handle to write to.
 * @param[in]   hBuf        The #Buffer_Handle of the buffer to write to
 *                          the sound device driver.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Sound_create must be called before this function.
 * @remarks     If mono samples are being written, only half of the submitted
 *              buffer can be filled with data, as the Sound module will
 *              convert the mono samples to stereo before sending them to
 *              the device driver and need the extra space.
 */
extern Int Sound_write(Sound_Handle hSound, Buffer_Handle hBuf);

/**
 * @brief       Fill a buffer from the sound input. This function can only
 *              be called if the driver was opened for reading.
 *
 * @param[in]   hSound      The #Sound_Handle to read from.
 * @param[in]   hBuf        The #Buffer_Handle of the buffer to fill using the
 *                          sound device driver.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Sound_create must be called before this function.
 * @remarks     If mono samples are being read, only half of the Buffer will
 *              be filled with data, use #Buffer_getNumBytesUsed to get
 *              the actual number.
 */
extern Int Sound_read(Sound_Handle hSound, Buffer_Handle hBuf);

/**
 * @brief       Deletes a Sound device driver instance.
 *
 * @param[in]   hSound      The #Sound_Handle to delete.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Sound_create must be called before this function.
 */
extern Int Sound_delete(Sound_Handle hSound);

#if defined (__cplusplus)
}
#endif

/*@}*/

#endif /* ti_sdo_dmai_Sound_h_ */

