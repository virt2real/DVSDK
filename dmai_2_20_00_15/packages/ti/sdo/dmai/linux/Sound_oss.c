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

/* Standard Linux headers */
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <linux/soundcard.h>

#include <xdc/std.h>
#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Sound.h>
#include <ti/sdo/dmai/Buffer.h>

#define MODULE_NAME     "Sound"

#define AUDIO_DEVICE    "/dev/dsp"
#define MIXER_DEVICE    "/dev/mixer"

typedef struct Sound_Object {
    Sound_Std         soundStd;
    Int               fd;
    Int32             sampleRate;
    Int16             channels;
} Sound_Object;

/******************************************************************************
 * monoToStereo
 ******************************************************************************/
static Void monoToStereo(Int8 *outBuf, Int8* inBuf, Int size)
{
    Int i;

    /* Expand mono to stereo */
    for (i = (size - 1); i >= 0; i--) {
        outBuf[4 * i]     = inBuf[2 * i];
        outBuf[4 * i + 1] = inBuf[2 * i + 1];
        outBuf[4 * i + 2] = inBuf[2 * i];
        outBuf[4 * i + 3] = inBuf[2 * i + 1];
    }
}

/******************************************************************************
 * stereoToMono
 ******************************************************************************/
static Void stereoToMono(Int16 *stereoSamples, Int16 *monoSamples,
                         Int numSamples)
{
    Int i;
    Int val;

    for (i=0; i < numSamples; i++) {
        val = *stereoSamples++;
        *monoSamples++ = (val + *stereoSamples++) / 2;
    }
}

/******************************************************************************
 * Sound_oss_create
 ******************************************************************************/
Sound_Handle Sound_oss_create(Sound_Attrs *attrs)
{
    int              vol         = attrs->leftGain | (attrs->rightGain << 8);
    int              channels    = 2;
    int              sampleRate  = attrs->sampleRate;
    int              format      = AFMT_S16_LE;
    int              mixerFd;
    int              recMask;
    int              recorder;
    int              mode;
    Sound_Handle     hSound;

    assert(attrs);

    hSound = calloc(1, sizeof(Sound_Object));

    if (hSound == NULL) {
        Dmai_err0("Failed to allocate space for Sound Object\n");
        return NULL;
    }

    /* Set the output volume */
    mixerFd = open(MIXER_DEVICE, O_RDONLY);

    if (mixerFd == -1) {
        Dmai_err1("Failed to open %s\n", MIXER_DEVICE);
        return NULL;
    }

    if (attrs->mode == Sound_Mode_OUTPUT ||
        attrs->mode == Sound_Mode_FULLDUPLEX) {

        if (ioctl(mixerFd, SOUND_MIXER_WRITE_VOLUME, &vol) == -1) {
            Dmai_err0("Failed to set the volume of line in.\n");
            close(mixerFd);
            return NULL;
        }
    }

    if (attrs->mode == Sound_Mode_INPUT ||
        attrs->mode == Sound_Mode_FULLDUPLEX) {

        if (attrs->soundInput == Sound_Input_MIC) {
            Dmai_dbg0("Microphone recorder selected\n");
            recorder = SOUND_MASK_MIC;
        }
        else {
            Dmai_dbg0("Line in recorder selected\n");
            recorder = SOUND_MASK_LINE;
        }

        if (ioctl(mixerFd, SOUND_MIXER_READ_RECMASK, &recMask) == -1) {
            Dmai_err0("Failed to ask mixer for available recorders.\n");
            close(mixerFd);
            return NULL;
        }

        if ((recMask & recorder) == 0) {
            Dmai_err0("Recorder not supported\n");
            close(mixerFd);
            return NULL;
        }

        if (ioctl(mixerFd, SOUND_MIXER_WRITE_RECSRC, &recorder) == -1) {
            Dmai_err0("Failed to set recorder.\n");
            close(mixerFd);
            return NULL;
        }

        if (ioctl(mixerFd, SOUND_MIXER_WRITE_IGAIN, &vol) == -1) {
            Dmai_err0("Failed to set the volume of line in.\n");
            close(mixerFd);
            return NULL;
        }
    }

    close(mixerFd);

    switch (attrs->mode) {
        case Sound_Mode_INPUT:
            mode = O_RDONLY;
            break;
        case Sound_Mode_OUTPUT:
            mode = O_WRONLY;
            break;
        case Sound_Mode_FULLDUPLEX:
            mode = O_RDWR;
            break;
        default:
            // Keep compiler happy, should not happen..
            Dmai_err1("Unknown sound mode %d\n", attrs->mode);
            return NULL;
    }

    /* Open the sound device for writing */
    hSound->fd = open(AUDIO_DEVICE, mode);

    if (hSound->fd == -1) {
        Dmai_err1("Failed to open the sound device (%s)\n", AUDIO_DEVICE);
        return NULL;
    }

    /* Set the sound format (only AFMT_S16_LE supported) */
    if (ioctl(hSound->fd, SNDCTL_DSP_SETFMT, &format) == -1) {
        Dmai_err1("Could not set format %d\n", format);
        return NULL;
    }

    /* Set the number of channels */
    if (ioctl(hSound->fd, SNDCTL_DSP_CHANNELS, &channels) == -1) {
        Dmai_err1("Could not set sound device to %d channels\n", channels);
        return NULL;
    }

    /* Set the sample rate */
    if (ioctl(hSound->fd, SNDCTL_DSP_SPEED, &sampleRate) == -1) {
        Dmai_err1("Could not set sample rate (%d)\n", sampleRate);
        return NULL;
    }

    hSound->soundStd = attrs->soundStd;
    hSound->sampleRate = attrs->sampleRate;
    hSound->channels   = attrs->channels;

    return hSound;
}

/******************************************************************************
 * Sound_oss_delete
 ******************************************************************************/
Int Sound_oss_delete(Sound_Handle hSound)
{
    if (hSound) {
        if (hSound->fd > -1) {
            close(hSound->fd);
        }

        free(hSound);
    }

    return Dmai_EOK;
}

/******************************************************************************
 * Sound_oss_read
 ******************************************************************************/
Int Sound_oss_read(Sound_Handle hSound, Buffer_Handle hBuf)
{
    Int32 bufSize, numBytes;

    assert(hSound);
    assert(hBuf);

    bufSize = Buffer_getSize(hBuf);

    if (read(hSound->fd, Buffer_getUserPtr(hBuf), bufSize) == -1) {
        Dmai_err1("Error reading the data from sound device (%s)\n",
                  strerror(errno));
        return Dmai_EIO;
    }

    /* Half the used size if we convert mono to stereo */
    numBytes = hSound->channels == 1 ? bufSize / 2 : bufSize;
    Buffer_setNumBytesUsed(hBuf, numBytes);

    /* Device driver only supports 2 channels */
    if (hSound->channels == 1) {
        stereoToMono((Int16 *) Buffer_getUserPtr(hBuf),
                     (Int16 *) Buffer_getUserPtr(hBuf),
                     Buffer_getNumBytesUsed(hBuf) / 2);
    }

    return Dmai_EOK;
}

/******************************************************************************
 * Sound_oss_write
 ******************************************************************************/
Int Sound_oss_write(Sound_Handle hSound, Buffer_Handle hBuf)
{
    Int numBytes;
    Int8 *bufPtr;

    assert(hSound);
    assert(hBuf);

    bufPtr = Buffer_getUserPtr(hBuf);
    numBytes = hSound->channels == 1 ? Buffer_getNumBytesUsed(hBuf) * 2 :
                                       Buffer_getNumBytesUsed(hBuf);


    /* Device driver only supports 2 channels */
    if (hSound->channels == 1) {
        monoToStereo(bufPtr, bufPtr, Buffer_getNumBytesUsed(hBuf));
    }

    if (write(hSound->fd, bufPtr, numBytes) == -1) {
        Dmai_err1("Error writing data to sound device(%s)\n", strerror(errno));
        return Dmai_EIO;
    }

    return Dmai_EOK;
}
