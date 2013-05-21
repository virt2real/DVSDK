/*
 * dvtbALSAAudio.h
 *
 * ALSA driver Interface
 *
 * Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/

#ifndef _DVEVM_ST_ALSAAUDIO_H
#define _DVEVM_ST_ALSAAUDIO_H

#include <alsa/asoundlib.h>
#include "dvtbGlobal.h"
#include "dvtbEngine.h"
#define DEF_SND_DEVICE          "plughw:0,0"
#define DEF_SAMPLE_SIZE         (16)            // Default Sample size
#define DEF_SAMPLE_RATE         (8000)         // Default Sample Rate
#define DEF_NUM_CHANNELS        (2)             // Default number of channels

#define AUD_FRAME_SIZE(_rate, _ch, _size)       ((_rate) * (_ch) * (_size) / 8)

typedef struct
{
	char device[MAX_NAME_LEN]; // Name of the audio device

	snd_pcm_t *handle;
	snd_pcm_hw_params_t *hw_params;
	snd_pcm_sw_params_t *sw_params;
	unsigned int sampleRate; // Number of samples per second
	int sampleSize; // Size of each sample in bits
	int numChannels; // Number of channels
	snd_pcm_stream_t mode; // Operating mode - capture/play
	snd_pcm_format_t format;
	snd_pcm_access_t access;
	int blocking_mode;
	char *buff1;
	char *buff2;
	char *buffptr;
	int usedbuffer;
	int bytesleft;
	int buffsize;
	int framesize;

} DvevmStAudioInfo;

DvevmStRetCode
dvtb_audioSetup(DvevmStAudioInfo *aud);

DvevmStRetCode
(*dvtb_audioSetControlContentsPtr)(DvevmStAudioInfo *aud);

DvevmStRetCode
dvtb_audioIn(DvevmStAudioInfo *aud, char *buff, int size);

DvevmStRetCode
dvtb_audioOut(DvevmStAudioInfo *aud, char *buff, int size);

DvevmStRetCode
dvtb_audioControl(DvevmStAudioInfo *aud);

DvevmStRetCode
dvtb_audioClose(DvevmStAudioInfo *aud);

DvevmStRetCode
dvtb_audioSetSwParam(DvevmStAudioInfo *aud);

DvevmStRetCode
dvtb_audioSetSampleRate(DvevmStAudioInfo *aud);

void
monoToStereo(short *stereoSamples, short *monoSamples, int numSamples);

#endif
