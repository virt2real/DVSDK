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

#include <stdio.h>
#include <stdlib.h>

#include <alsa/asoundlib.h>

#include <xdc/std.h>
#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Sound.h>
#include <ti/sdo/dmai/Buffer.h>

#define MODULE_NAME     "Sound"

#define AUDIO_DEVICE    "plughw:0,0"
#define AUDIO_MIXER     "hw:0"

#ifdef CONFIG_SND_SOC_TLV320AIC3X
/* AIC3X specific elements */
#define RIGHT_LINE_CTRL_ELEM  "Right PGA Mixer Line1R Switch"
#define LEFT_LINE_CTRL_ELEM   "Left PGA Mixer Line1L Switch"

#define RIGHT_MIC_CTRL_ELEM   "Right PGA Mixer Mic3R Switch"
#define LEFT_MIC_CTRL_ELEM    "Left PGA Mixer Mic3L Switch"
#endif

#define PCM_TIMEOUT 40

typedef struct Sound_Object {
    Sound_Std               soundStd;
    snd_pcm_t              *rcIn;
    snd_pcm_t              *rcOut;
    Int32                   sampleRate;
    Int16                   channels;
    Int32                   periodSize;
    Int32                   bufSize;
    snd_pcm_hw_params_t    *hwParamsIn;
    snd_pcm_hw_params_t    *hwParamsOut;
    snd_pcm_sw_params_t    *swParamsIn;
    snd_pcm_sw_params_t    *swParamsOut;
} Sound_Object;

/******************************************************************************
 *   setMixerInput
 *****************************************************************************/
#ifdef CONFIG_SND_SOC_TLV320AIC3X
static Int setMixerControl (const Char *name, Int value)
{
    Int status;
    snd_hctl_t *hctl;
    snd_ctl_elem_id_t *id;
    snd_hctl_elem_t *elem;
    snd_ctl_elem_value_t *control;

    if ((status = snd_hctl_open(&hctl, AUDIO_MIXER, 0)) < 0) {
        Dmai_err2("setMixerControl %s open error: %s\n", AUDIO_MIXER, snd_strerror(status));
        return Dmai_EFAIL;;
    }

    if ((status = snd_hctl_load(hctl)) < 0) {
        Dmai_err2("setMixerControl %s load error: %s\n", AUDIO_MIXER, snd_strerror(status));
        return Dmai_EFAIL;;
    }

    snd_ctl_elem_id_alloca(&id);
    snd_ctl_elem_id_set_interface(id, SND_CTL_ELEM_IFACE_MIXER);
    snd_ctl_elem_id_set_name(id, name);
    elem = snd_hctl_find_elem(hctl, id);
    if (!elem) {
        Dmai_err1("setMixerControl %s find element error\n", 
            AUDIO_MIXER);
        snd_hctl_close(hctl);
        return Dmai_EFAIL;
    }

    snd_ctl_elem_value_alloca(&control);
    snd_ctl_elem_value_set_id(control, id);
    snd_ctl_elem_value_set_integer(control, 0, value);
    snd_hctl_elem_write(elem, control);

    snd_hctl_close(hctl);

    return Dmai_EOK;
}
#endif

/******************************************************************************
 *   setMixerVolume
 *****************************************************************************/
static Int setMixerVolume (Sound_Attrs *attrs)
{
    Int status;
    snd_mixer_t *rcMixer;
    snd_mixer_elem_t    *elem;
    snd_mixer_selem_id_t    *sid;

    snd_mixer_selem_id_malloc (&sid);

    /* Open the mixer device */
    status = snd_mixer_open (&rcMixer, 0);

    if ( status<0 ) {
        Dmai_err2 ("Failed to open mixer on %s (%s)\n",
                   AUDIO_MIXER, snd_strerror (status));
        return Dmai_EFAIL;
    }

    /* Attach mixer with sound card */
    status = snd_mixer_attach (rcMixer,AUDIO_MIXER);

    if (status <0) {
        Dmai_err2 ("Failed to attach mixer on %s (%s)\n",
                   AUDIO_MIXER, snd_strerror (status));
        return Dmai_EFAIL;
    }

    /* Register mixer with selected elements */
    status = snd_mixer_selem_register (rcMixer, NULL, NULL);

    if (status <0) {
        Dmai_err2 ("Failed to register mixer on %s (%s)\n",
                   AUDIO_MIXER, snd_strerror (status));
        return Dmai_EFAIL;
    }
    /* Load mixer */
    status = snd_mixer_load (rcMixer);

    if (status <0) {
        Dmai_err2 ("Failed to load mixer on %s (%s)\n",
                   AUDIO_MIXER, snd_strerror (status));
        return Dmai_EFAIL;
    }

    for (elem = snd_mixer_first_elem (rcMixer); elem; 
            elem=snd_mixer_elem_next(elem)) {

        snd_mixer_selem_get_id(elem,sid);
        if (!snd_mixer_selem_is_active(elem))
            continue;

        if (attrs->mode == Sound_Mode_OUTPUT || 
             attrs->mode == Sound_Mode_FULLDUPLEX) {
            if (snd_mixer_selem_has_playback_channel(elem, 
                 SND_MIXER_SCHN_FRONT_LEFT))
                snd_mixer_selem_set_playback_volume (elem, 
                SND_MIXER_SCHN_FRONT_LEFT,attrs->leftGain);
            if (snd_mixer_selem_has_playback_channel(elem, 
                          SND_MIXER_SCHN_FRONT_RIGHT))
                snd_mixer_selem_set_playback_volume (elem, 
                          SND_MIXER_SCHN_FRONT_RIGHT,attrs->rightGain);
        }

        if (attrs->mode == Sound_Mode_INPUT || 
                    attrs->mode == Sound_Mode_FULLDUPLEX) {
            if (snd_mixer_selem_has_capture_channel(elem,
                    SND_MIXER_SCHN_FRONT_LEFT))
                snd_mixer_selem_set_capture_volume (elem, 
                           SND_MIXER_SCHN_FRONT_LEFT,attrs->leftGain);
            if (snd_mixer_selem_has_capture_channel(elem, 
                    SND_MIXER_SCHN_FRONT_RIGHT))
                snd_mixer_selem_set_capture_volume (elem, 
                           SND_MIXER_SCHN_FRONT_RIGHT,attrs->rightGain);
        }
    }

    snd_mixer_selem_id_free (sid);
    snd_mixer_close (rcMixer);

    return Dmai_EOK;
}

/******************************************************************************
 * initHwParams
 ******************************************************************************/
static Int initHwParams(snd_pcm_t *rc, snd_pcm_hw_params_t *hwParams,
                        Sound_Attrs *attrs, Sound_Handle hSound)
{
    Int status;
    snd_pcm_uframes_t periodSize, bufSize;
    Uns buffer_time = 0;

    /* Fill the params with the defaults */
    status = snd_pcm_hw_params_any(rc, hwParams);

    if (status < 0) {
        Dmai_err2("Failed to init ALSA hardware param structure on %s (%s)\n",
                  AUDIO_DEVICE, snd_strerror(status));
        return Dmai_EFAIL;
    }

    /* Set the access type to interleaved */
    status = snd_pcm_hw_params_set_access(rc, hwParams,
                                          SND_PCM_ACCESS_RW_INTERLEAVED);

    if (status < 0) {
        Dmai_err2("Failed to set ALSA access type on %s (%s)\n",
                  AUDIO_DEVICE, snd_strerror(status));
        return Dmai_EFAIL;
    }

    /* Set the format to 16 bit little endian */
    status = snd_pcm_hw_params_set_format(rc, hwParams, SND_PCM_FORMAT_S16_LE);

    if (status < 0) {
        Dmai_err2("Failed to set sample format on %s (%s)\n",
                  AUDIO_DEVICE, snd_strerror(status));
        return Dmai_EFAIL;
    }

    /* Set the sample rate */
    status = snd_pcm_hw_params_set_rate_near(rc, hwParams,
                                             (Uns *) &attrs->sampleRate, 0);

    if (status < 0) {
        Dmai_err3("Failed to set sample rate to %d on %s (%s)\n",
                  attrs->sampleRate, AUDIO_DEVICE, snd_strerror(status));
        return Dmai_EFAIL;
    }

    /* Set the number of channels to 2 */
    status = snd_pcm_hw_params_set_channels(rc, hwParams, attrs->channels);

    if (status < 0) {
        Dmai_err3("Failed to set channel count to %d on %s (%s)\n",
                  attrs->channels, AUDIO_DEVICE, snd_strerror(status));
        return Dmai_EFAIL;
    }

    /* Set period size equal to input buffer size */    
    periodSize = hSound->periodSize;
    status = snd_pcm_hw_params_set_period_size_near (rc, hwParams,
                                                      &periodSize, 0);
    
    if (status < 0) {
        Dmai_err3("Failed to set the period size to %d on %s (%s)\n",
                  periodSize, AUDIO_DEVICE, snd_strerror(status));
        return Dmai_EFAIL;
    }

    if (periodSize != hSound->periodSize) {
        Dmai_dbg4("Failed to set buffer size (%d) , got (%d) on %s (%s)\n",
                    hSound->periodSize, periodSize, AUDIO_DEVICE,
                    snd_strerror(status));
        hSound->periodSize = periodSize;
    }

    /* Set the maximum buffer time */    
    status = snd_pcm_hw_params_get_buffer_time_max(hwParams, &buffer_time, 0);

    if (status < 0) {
        Dmai_err2("Failed to get maximum buffer time on %s (%s)\n",
                   AUDIO_DEVICE, snd_strerror(status));
        return Dmai_EFAIL;
    }

    if (buffer_time > 500000) {
        buffer_time = 500000;
    }

    status = snd_pcm_hw_params_set_buffer_time_near(rc, hwParams, 
                &buffer_time, 0);

    if (status < 0) {
        Dmai_err2("Failed to set maximum buffer time on %s (%s)\n",
                   AUDIO_DEVICE, snd_strerror(status));
        return Dmai_EFAIL;
    }

    /* Prepare the PCM interface with the choosen parameters */
    status = snd_pcm_hw_params(rc, hwParams);

    if (status < 0) {
        Dmai_err2("Failed to set ALSA parameters on %s (%s)\n",
                  AUDIO_DEVICE, snd_strerror(status));
        return Dmai_EFAIL;
    }

    /* Do sanity check */
    snd_pcm_hw_params_get_period_size(hwParams, &periodSize, 0);
    snd_pcm_hw_params_get_buffer_size(hwParams, &bufSize);
    
    if (periodSize == bufSize) {
        Dmai_err2("Can't use period size equal to buf size (%d == %d)\n",
                    periodSize, bufSize);
        return Dmai_EFAIL;
    }

    hSound->periodSize = periodSize;
    hSound->bufSize = bufSize;
    
    return Dmai_EOK;
}

/******************************************************************************
 * initSwParams 
 * ***************************************************************************/
static Int initSwParams(snd_pcm_t *rc, snd_pcm_sw_params_t *swParams,
                        Sound_Handle hSound, Int delay)
{
    Int status;
    snd_pcm_uframes_t start_threshold, stop_threshold;

    /* Get the current sw params */
    status = snd_pcm_sw_params_current (rc, swParams);
    
    if (status < 0) {
        Dmai_err2 ("Failed to read the current swparams on %s (%s)\n",
                   AUDIO_DEVICE, snd_strerror(status));
        return Dmai_EFAIL;
    }

    /* Set the available min */
    status = snd_pcm_sw_params_set_avail_min(rc, swParams, hSound->periodSize);
    
    if (status < 0) {
        Dmai_err3 ("Failed to set avail min to (%d) on %s (%s)\n",
                   hSound->periodSize, AUDIO_DEVICE, snd_strerror(status));
        return Dmai_EFAIL;
    }

    /* Set the start threshold */
    if (delay) {
        start_threshold = 1;
    }
    else {
        start_threshold = hSound->bufSize;
    }

    status = snd_pcm_sw_params_set_start_threshold(rc, swParams, 
                start_threshold);

    if (status < 0) {
        Dmai_err3 ("Failed to set start threashold to (%d) on %s (%s)\n",
                    start_threshold, AUDIO_DEVICE, snd_strerror(status));
        return Dmai_EFAIL;
    }

    /* Set the stop threshold */
    stop_threshold = hSound->bufSize;

    status = snd_pcm_sw_params_set_stop_threshold(rc, swParams, 
                stop_threshold);

    if (status < 0) {
        Dmai_err3 ("Failed to set start threashold to (%d) on %s (%s)\n",
                     stop_threshold, AUDIO_DEVICE, snd_strerror(status));
        return Dmai_EFAIL;
    }

    /* Write the swparams */
    status = snd_pcm_sw_params(rc, swParams);

    if (status < 0) {
        Dmai_err2 ("Failed to set swparams on %s (%s)\n", AUDIO_DEVICE,
                   snd_strerror(status));
        return Dmai_EFAIL;
    }

    return Dmai_EOK;
    
}

/******************************************************************************
 * Sound_alsa_delete
 ******************************************************************************/
Int Sound_alsa_delete(Sound_Handle hSound)
{
    if (hSound) {
        if (hSound->rcIn) {
            snd_pcm_close(hSound->rcIn);
        }

        if (hSound->rcOut) {
            snd_pcm_close(hSound->rcOut);
        }

        if (hSound->hwParamsIn) {
            /* Free the H/W param structure */
            snd_pcm_hw_params_free(hSound->hwParamsIn);
        }

        if (hSound->swParamsIn) {
            /* Free the S/W param structure */
            snd_pcm_sw_params_free(hSound->swParamsIn);
        }

        if (hSound->hwParamsOut) {
            /* Free the H/W param structure */
            snd_pcm_hw_params_free(hSound->hwParamsOut);
        }

        if (hSound->swParamsOut) {
            /* Free the S/W param structure */
            snd_pcm_sw_params_free(hSound->swParamsOut);
        }

        free(hSound);

        snd_config_update_free_global();

    }

    return Dmai_EOK;
}

/******************************************************************************
 * Sound_alsa_create
 ******************************************************************************/
Sound_Handle Sound_alsa_create(Sound_Attrs *attrs)
{
    Sound_Handle hSound;
    Int status;
    snd_output_t    *log;

    assert(attrs);

    snd_output_stdio_attach(&log, stdout, 0);

    hSound = calloc(1, sizeof(Sound_Object));

    if (hSound == NULL) {
        Dmai_err0("Failed to allocate space for Sound Object\n");
        return NULL;
    }

    hSound->soundStd = attrs->soundStd;
    hSound->sampleRate = attrs->sampleRate;
    hSound->channels = attrs->channels;
    hSound->periodSize  = attrs->bufSize;

    if (attrs->mode == Sound_Mode_INPUT ||
        attrs->mode == Sound_Mode_FULLDUPLEX) {

        status = snd_pcm_open(&hSound->rcIn, AUDIO_DEVICE,
                              SND_PCM_STREAM_CAPTURE, 0);

        if (status < 0) {
            Dmai_err2("Failed to open ALSA sound device for input %s (%s)\n",
                      AUDIO_DEVICE, snd_strerror(status));
            Sound_alsa_delete(hSound);
            return NULL;
        }

        /* Allocate a PCM SW and HW Param structure */
        status = snd_pcm_hw_params_malloc(&hSound->hwParamsIn);

        if (status < 0) {
            Dmai_err2("Failed to alloc hardware param structure on %s (%s)\n",
                      AUDIO_DEVICE, snd_strerror(status));
            Sound_alsa_delete(hSound);
            return NULL;
        }

        status = snd_pcm_sw_params_malloc(&hSound->swParamsIn);

        if (status < 0) {
            Dmai_err2("Failed to alloc software param structure on %s (%s)\n",
                      AUDIO_DEVICE, snd_strerror(status));
            Sound_alsa_delete(hSound);
            return NULL;
        }

        if (initHwParams(hSound->rcIn,hSound->hwParamsIn,attrs,hSound) < 0) {
            Sound_alsa_delete(hSound);
            return NULL;
        }

        if (initSwParams(hSound->rcIn,hSound->swParamsIn,hSound,1) < 0) {
            Sound_alsa_delete(hSound);
            return NULL;
        }
       
        Dmai_dbg1("", snd_pcm_dump(hSound->rcIn, log)); 
    }

    if (attrs->mode == Sound_Mode_OUTPUT ||
        attrs->mode == Sound_Mode_FULLDUPLEX) {

        status = snd_pcm_open(&hSound->rcOut, AUDIO_DEVICE,
                              SND_PCM_STREAM_PLAYBACK, 0);

        if (status < 0) {
            Dmai_err2("Failed to open ALSA sound device for output %s (%s)\n",
                      AUDIO_DEVICE, snd_strerror(status));
            Sound_alsa_delete(hSound);
            return NULL;
        }

        /* Allocate a PCM SW and HW Param structure */
        status = snd_pcm_hw_params_malloc(&hSound->hwParamsOut);

        if (status < 0) {
            Dmai_err2("Failed to alloc hardware param structure on %s (%s)\n",
                      AUDIO_DEVICE, snd_strerror(status));
            Sound_alsa_delete(hSound);
            return NULL;
        }

        status = snd_pcm_sw_params_malloc(&hSound->swParamsOut);

        if (status < 0) {
            Dmai_err2("Failed to alloc hardware param structure on %s (%s)\n",
                      AUDIO_DEVICE, snd_strerror(status));
            Sound_alsa_delete(hSound);
            return NULL;
        }

        if (initHwParams(hSound->rcOut,hSound->hwParamsOut,attrs,hSound) < 0) {
            Sound_alsa_delete(hSound);
            return NULL;
        }

        if (initSwParams(hSound->rcOut,hSound->swParamsOut,hSound,0) < 0) {
            Sound_alsa_delete(hSound);
            return NULL;
        }

        if (setMixerVolume (attrs) <0) {
            Dmai_err0("Failed to configure sound mixer device\n");
        }

        Dmai_dbg1("", snd_pcm_dump(hSound->rcOut, log)); 
    }

#ifdef CONFIG_SND_SOC_TLV320AIC3X
    if (attrs->mode != Sound_Mode_OUTPUT) {
        if (attrs->soundInput == Sound_Input_MIC) {
            if(setMixerControl(RIGHT_LINE_CTRL_ELEM, 0) != Dmai_EOK) {
                Dmai_err0("Failed to configure Right_PGA_Mixer_Line1R_Switch\n");
                Sound_alsa_delete(hSound);
                return NULL;
            }
            if(setMixerControl(LEFT_LINE_CTRL_ELEM, 0) != Dmai_EOK) {
                Dmai_err0("Failed to configure Left_PGA_Mixer_Line1L_Switch\n");
                Sound_alsa_delete(hSound);
                return NULL;
            }
            if(setMixerControl(RIGHT_MIC_CTRL_ELEM, 1) != Dmai_EOK) {
                Dmai_err0("Failed to configure Right_PGA_Mixer_Mic3R_Switch\n");
                Sound_alsa_delete(hSound);
                return NULL;
            }
            if(setMixerControl(LEFT_MIC_CTRL_ELEM, 1) != Dmai_EOK) {
                Dmai_err0("Failed to configure Left_PGA_Mixer_Mic3L_Switch\n");
                Sound_alsa_delete(hSound);
                return NULL;
            }
        } else if (attrs->soundInput == Sound_Input_LINE) {
            if(setMixerControl(RIGHT_LINE_CTRL_ELEM, 1) != Dmai_EOK) {
                Dmai_err0("Failed to configure Right_PGA_Mixer_Line1R_Switch\n");
                Sound_alsa_delete(hSound);
                return NULL;
            }
            if(setMixerControl(LEFT_LINE_CTRL_ELEM, 1) != Dmai_EOK) {
                Dmai_err0("Failed to configure Left_PGA_Mixer_Line1L_Switch\n");
                Sound_alsa_delete(hSound);
                return NULL;
            }
            if(setMixerControl(RIGHT_MIC_CTRL_ELEM, 0) != Dmai_EOK) {
                Dmai_err0("Failed to configure Right_PGA_Mixer_Mic3R_Switch\n");
                Sound_alsa_delete(hSound);
                return NULL;
            }
            if(setMixerControl(LEFT_MIC_CTRL_ELEM, 0) != Dmai_EOK) {
                Dmai_err0("Failed to configure Left_PGA_Mixer_Mic3L_Switch\n");
                Sound_alsa_delete(hSound);
                return NULL;
            }
        }
    }
#endif
    snd_output_close(log);
    return hSound;
}

/******************************************************************************
 * xrunRecovery
 * ***************************************************************************/
static Int xrunRecovery(snd_pcm_t *rc, Int err)
{
    Dmai_dbg0("Recovering from underrun\n");

    if (err == -EPIPE) {
        if (snd_pcm_prepare(rc) < 0) {
            Dmai_err1("Failed to recover from over or underrun on %s\n",
                      AUDIO_DEVICE);
            return Dmai_EFAIL;
        }
    }
    else if (err == -ESTRPIPE) {
        while ((err = snd_pcm_resume(rc)) == -EAGAIN) {
            sleep (1);  /* wait until the suspend flag is released */
        }

        if (snd_pcm_prepare(rc) < 0) {
            Dmai_err1("Failed to recover from over or underrun on %s\n",
                      AUDIO_DEVICE);
            return Dmai_EFAIL;
        }
    }
    else {
        return Dmai_EFAIL;
    }

    return Dmai_EOK;
} 

/******************************************************************************
 * Sound_alsa_read
 ******************************************************************************/
Int Sound_alsa_read(Sound_Handle hSound, Buffer_Handle hBuf)
{
    Int32 numSamples, readSamples;
    Int8 *bufPtr;

    assert(hSound);
    assert(hBuf);
    
    readSamples = Buffer_getSize(hBuf) / (2 * hSound->channels);

    bufPtr = Buffer_getUserPtr(hBuf);

    while (readSamples > 0) {
        numSamples = snd_pcm_readi(hSound->rcIn, bufPtr, readSamples);

        if (numSamples == -EAGAIN) 
            continue;

        if (numSamples < 0) {
            if (xrunRecovery(hSound->rcIn,numSamples) < 0) {
                Dmai_err2 ("Failed to read from %s (%s)\n",
                            AUDIO_DEVICE, strerror(numSamples));
                return Dmai_EFAIL;
            }
        }
        else {
            bufPtr += numSamples * 2 * hSound->channels;
            readSamples -= numSamples;
        }
    }

    Buffer_setNumBytesUsed(hBuf, Buffer_getSize(hBuf));

    return Dmai_EOK;
}

/******************************************************************************
 * Sound_alsa_write
 ******************************************************************************/
Int Sound_alsa_write(Sound_Handle hSound, Buffer_Handle hBuf)
{
    Int32 numSamples, writeSamples;
    Int8 *bufPtr;

    assert(hSound);
    assert(hBuf);

    writeSamples = Buffer_getNumBytesUsed(hBuf) / (2 * hSound->channels);
    bufPtr = Buffer_getUserPtr(hBuf);

    while (writeSamples > 0) {
#if defined(Dmai_Device_dm365) || defined(Dmai_Device_dm368)
        /* start by doing a blocking wait for free space. */
        snd_pcm_wait (hSound->rcOut, PCM_TIMEOUT);
#endif

        numSamples = snd_pcm_writei(hSound->rcOut, bufPtr, writeSamples);

        if (numSamples == -EAGAIN) 
            continue;

        if (numSamples < 0) {
            if (xrunRecovery(hSound->rcOut,numSamples) < 0) {
                Dmai_err2 ("Failed to write to %s (%s)\n",
                            AUDIO_DEVICE, strerror(numSamples));
                return Dmai_EFAIL;
            }
        }
        else {
            bufPtr += numSamples * 2 * hSound->channels;
            writeSamples -= numSamples;
        }
    }

    Buffer_setNumBytesUsed(hBuf, Buffer_getSize(hBuf));

    return Dmai_EOK;
}
