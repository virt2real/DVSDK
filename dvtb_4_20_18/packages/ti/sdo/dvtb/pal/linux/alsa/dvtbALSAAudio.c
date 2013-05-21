/*
 * dvtbALSAAudio.c
 *
 * ALSA driver Interface implementation
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


#include "dvtbALSAAudio.h"
#include "dvtbMemory.h"

void
monoToStereo(short *stereoSamples, short *monoSamples, int numSamples)
{
	int i;
	for (i = 0; i < numSamples; i++)
	{
		*stereoSamples++ = *monoSamples;
		*stereoSamples++ = 0;
		monoSamples++;
		//*stereoSamples++=*monoSamples++;
	}
}

DvevmStRetCode
dvtb_audioSetSampleRate(DvevmStAudioInfo *aud)
{
	return dvtb_audioControl(aud);
}

DvevmStRetCode
dvtb_audioControl(DvevmStAudioInfo *aud)
{
	int retVal;
	unsigned int period;
	unsigned int buffer_time = 0, period_time = 0;
	int var, tmp;
	int frame_bytes;
	snd_pcm_uframes_t buffsize;
	snd_pcm_uframes_t period_frames = 0, buffer_frames = 0;
	aud->access = SND_PCM_ACCESS_RW_INTERLEAVED;


	// Fill the params with the defaults
	if ((retVal = snd_pcm_hw_params_any(aud->handle, aud->hw_params)) < 0)
	{
		SYS_ERROR("cannot initialize hardware parameter structure (%s)\n", snd_strerror(retVal));
		return DVEVM_ST_FAIL;
	}
	else
	{
		SYS_DEBUG("snd_pcm_hw_params_malloc, successful\n");
	}

	// Set the access type to interleaved
	if ((retVal = snd_pcm_hw_params_set_access(aud->handle, aud->hw_params, aud->access)) < 0)
	{
		SYS_ERROR("cannot set access type (%s)\n", snd_strerror(retVal));
		return DVEVM_ST_FAIL;
	}
	else
	{
		SYS_DEBUG("snd_pcm_hw_params_set_access, successful\n");
	}

	// Set the format to 16 bit little endian
	if ((retVal = snd_pcm_hw_params_set_format(aud->handle, aud->hw_params, aud->format)) < 0)
	{
		SYS_ERROR("cannot set sample format (%s)\n", snd_strerror(retVal));
		return DVEVM_ST_FAIL;
	}
	else
	{
		SYS_DEBUG("snd_pcm_hw_params_set_format, successful\n");
	}

	aud->sampleSize = snd_pcm_format_width(aud->format);
	// Set the rate
	if ((retVal = snd_pcm_hw_params_set_rate_near(aud->handle, aud->hw_params, &(aud->sampleRate), 0)) < 0)
	{
		SYS_ERROR("cannot set sample rate (%s)\n", snd_strerror(retVal));
		return DVEVM_ST_FAIL;
	}
	else
	{
		SYS_DEBUG("snd_pcm_hw_params_set_rate_near, successful\n");
	}
	// Set the number of channels
	if ((retVal = snd_pcm_hw_params_set_channels(aud->handle, aud->hw_params, aud->numChannels)) < 0)
	{
		SYS_ERROR("cannot set channel count (%s)\n", snd_strerror(retVal));
		return DVEVM_ST_FAIL;
	}
	else
	{
		SYS_DEBUG("snd_pcm_hw_params_set_channels, successful\n");
	}

	if (buffer_time == 0 && buffer_frames == 0)
	{
		retVal = snd_pcm_hw_params_get_buffer_time_max(aud->hw_params, &buffer_time, 0);
		assert(retVal >= 0);

		if (buffer_time > 500000)
			buffer_time = 500000;
	}

	if (period_time == 0 && period_frames == 0)
	{
		if (buffer_time > 0)
			period_time = buffer_time / 4;
		else
			period_frames = buffer_frames / 4;
	}

	if (period_time > 0)
		retVal = snd_pcm_hw_params_set_period_time_near(aud->handle, aud->hw_params, &period_time, 0);
	else
		retVal = snd_pcm_hw_params_set_period_size_near(aud->handle, aud->hw_params, &period_frames, 0);

	assert(retVal >= 0);
	if (buffer_time > 0)
	{
		retVal = snd_pcm_hw_params_set_buffer_time_near(aud->handle, aud->hw_params, &buffer_time, 0);
	}
	else
	{
		retVal = snd_pcm_hw_params_set_buffer_size_near(aud->handle, aud->hw_params, &buffer_frames);
	}

	// Prepare the PCM interface with the parameters chosen
	if ((retVal = snd_pcm_hw_params(aud->handle, aud->hw_params)) < 0)
	{
		SYS_ERROR("cannot set hw parameters (%s)\n", snd_strerror(retVal));
		return DVEVM_ST_FAIL;
	}
	else
	{
		SYS_DEBUG("snd_pcm_hw_params, successful\n");
	}

	if (NULL != aud->buff1)
	{
		Memory_contigFree(aud->buff1, aud->buffsize);
		aud->buff1 = NULL;
	}

	if (NULL != aud->buff2)
	{
		Memory_contigFree(aud->buff2, aud->buffsize);
		aud->buff2 = NULL;
	}

	if ((retVal = snd_pcm_hw_params_get_buffer_size(aud->hw_params, &buffsize)) < 0)
	{
		SYS_ERROR("get buffer size failed (%s)\n", snd_strerror(retVal));
		return DVEVM_ST_FAIL;
	}

	if ((retVal = snd_pcm_hw_params_get_periods(aud->hw_params, &period, 0)) < 0)
	{
		SYS_ERROR("get period failed (%s)\n", snd_strerror(retVal));
		return DVEVM_ST_FAIL;
	}

	frame_bytes = (snd_pcm_format_width(aud->format) / 8) * aud->numChannels;
	aud->buffsize = 2 * (frame_bytes * (buffsize / period));

	if (aud->buffsize < aud->framesize)
	{
		tmp = (frame_bytes * (buffsize / period));
		var = aud->framesize / tmp;
		var += ((aud->framesize % tmp) != 0);
		aud->buffsize = var * tmp;
	}

	aud->buff1 = Memory_contigAlloc(aud->buffsize, Memory_DEFAULTALIGNMENT);
	aud->buff2 = Memory_contigAlloc(aud->buffsize, Memory_DEFAULTALIGNMENT);

	if (!aud->buff1 || !aud->buff2)
	{
		SYS_ERROR("can not allocate memory for buff1 or buff2 \n");
		return DVEVM_ST_FAIL;
	}

	aud->buffptr = &aud->buff1[0];
	aud->usedbuffer = 0;
	aud->bytesleft = aud->buffsize;

	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_audioSetSwParam(DvevmStAudioInfo *aud)
{
	int retVal=-1;
	snd_pcm_t *handle = aud->handle;
	snd_pcm_sw_params_t *swParams = aud->sw_params;
	snd_pcm_uframes_t transferAlign;
	snd_pcm_uframes_t thresholdBegin, thresholdEnd;
	unsigned minSleep = 0;
	snd_pcm_uframes_t chunkSize, bufSize;
	size_t n;
	int delayBegin=0, delayEnd=0, rate=0;

	snd_pcm_hw_params_get_period_size(aud->hw_params, &chunkSize, 0);
	snd_pcm_hw_params_get_buffer_size(aud->hw_params, &bufSize);

	snd_pcm_sw_params_current(handle, swParams);
	retVal = snd_pcm_sw_params_get_xfer_align(swParams, &transferAlign);
	if(0 > retVal)
	{
		SYS_ERROR("SetSwParam failed: get transfer align failed\n");
		return DVEVM_ST_FAIL;
	}

	retVal = snd_pcm_sw_params_set_sleep_min(handle, swParams, minSleep);
	if(0 > retVal)
	{
		SYS_ERROR("SetSwParam failed: set sleep min failed\n");
		return DVEVM_ST_FAIL;
	}

	rate = aud->sampleRate;
	n = chunkSize;
	retVal = snd_pcm_sw_params_set_avail_min(handle, swParams, n);
	if(0 > retVal)
	{
		SYS_ERROR("SetSwParam failed: set avail min failed\n");
		return DVEVM_ST_FAIL;
	}

	/* round up to closest transfer boundary */
	n = (bufSize / transferAlign) * transferAlign;

	if(0 < delayBegin)
		thresholdBegin = (double) rate * delayBegin / 1000000;
	else
		thresholdBegin = n + (double) rate * delayBegin / 1000000;

	if(1 > thresholdBegin)
		thresholdBegin = 1;
	if(n < thresholdBegin)
		thresholdBegin = n;
	retVal = snd_pcm_sw_params_set_start_threshold(handle, swParams, thresholdBegin);
	if(0 > retVal)
	{
		SYS_ERROR("SetSwParam failed: set start threshold failed\n");
		return DVEVM_ST_FAIL;
	}

	thresholdEnd = bufSize + (double) rate * delayEnd / 1000000;
	retVal = snd_pcm_sw_params_set_stop_threshold(handle, swParams, thresholdEnd);
	if(0 > retVal)
	{
		SYS_ERROR("SetSwParam failed: set stop threshold failed\n");
		return DVEVM_ST_FAIL;
	}

	retVal = snd_pcm_sw_params_set_xfer_align(handle, swParams, transferAlign);
	if(0 > retVal)
	{
		SYS_ERROR("SetSwParam failed: set transfer align failed\n");
		return DVEVM_ST_FAIL;
	}

	retVal = snd_pcm_sw_params(handle, swParams);
	if(0 > retVal)
	{
		SYS_ERROR("SetSwparam failed: set sw params failed\n");
		return DVEVM_ST_FAIL;
	}

	SYS_DEBUG("dvtb_audioSetSwParam is done \n");
	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_audioSetup(DvevmStAudioInfo *aud)
{
	int retVal;

	aud->buff1 = NULL;
	aud->buff2 = NULL;
	if (0 == aud->device[0])
		strcpy(aud->device, DEF_SND_DEVICE);

	if(NULL != dvtb_audioSetControlContentsPtr)
	{
		if(DVEVM_ST_FAIL == dvtb_audioSetControlContentsPtr(aud))
		{
			SYS_ERROR("unable to Set Control Contentents\n");
			return DVEVM_ST_FAIL;
		}
	}

	// Open the PCM interface
	if ((retVal = snd_pcm_open(&(aud->handle), aud->device, aud->mode, aud->blocking_mode)) < 0)
	{
		SYS_ERROR("cannot open audio device (%s)\n", snd_strerror(retVal));
		return DVEVM_ST_FAIL;
	}
	else
	{
		SYS_DEBUG("snd_pcm_open, successful\n");
	}

	// Allocate a PCM HW Param structure
	if ((retVal = snd_pcm_hw_params_malloc(&(aud->hw_params))) < 0)
	{
		SYS_ERROR("cannot allocate hardware parameter structure (%s)\n", snd_strerror(retVal));
		return DVEVM_ST_FAIL;
	}
	else
	{
		SYS_DEBUG("snd_pcm_hw_params_malloc, successful\n");
	}
	if (DVEVM_ST_FAIL == dvtb_audioControl(aud))
	{
		SYS_ERROR("Audio control failed   \n");
		dvtb_audioClose(aud);
		return DVEVM_ST_FAIL;
	}
	else
	{
		SYS_DEBUG("Audio control, successful\n");
	}
	if ((retVal = snd_pcm_sw_params_malloc(&(aud->sw_params))) < 0)
	{
		SYS_ERROR("cannot allocate software parameter structure (%s)\n", snd_strerror(retVal));
		dvtb_audioClose(aud);
		return DVEVM_ST_FAIL;
	}
	else
	{
		SYS_DEBUG("snd_pcm_sw_params_malloc, successful\n");
	}
	if (SND_PCM_STREAM_CAPTURE != aud->mode)
		dvtb_audioSetSwParam(aud);

	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_audioOut(DvevmStAudioInfo *aud, char *buff, int size)
{
	int retVal, left;
	int frame_byte = (snd_pcm_format_width(aud->format) / 8) * aud->numChannels;
	int i = 0;
#if 1
	// start : logic to avoide under run
	if (size <= aud->bytesleft)
	{
		memcpy(aud->buffptr, buff, size);
		aud->buffptr += size;
		aud->bytesleft -= size;
		size = 0;
	}
	else
	{
		left = aud->bytesleft;
		if (0 != left)
		{
			memcpy(aud->buffptr, buff, left);
		}
		if (0 == aud->usedbuffer)
		{
			aud->buffptr = aud->buff2;
			memcpy(aud->buffptr, &buff[left], size - left);
			aud->buffptr += (size - left);
			aud->bytesleft = aud->buffsize - (size - left);
			aud->usedbuffer = 1;
			buff = aud->buff1;
		}
		else
		{
			aud->buffptr = aud->buff1;
			memcpy(aud->buffptr, &buff[left], size - left);
			aud->buffptr += (size - left);
			aud->bytesleft = aud->buffsize - (size - left);
			aud->usedbuffer = 0;
			buff = aud->buff2;
		}

		size = aud->buffsize / frame_byte;

	}
	// end : logic to avoid underrun
#else
	size = size/frame_byte;
#endif

	while (size)
	{
		retVal = snd_pcm_writei(aud->handle, buff, size);
		if ((retVal < 0) && (retVal != -EAGAIN))
		{
			if (retVal == -EPIPE)
			{
				//TBD next release
				//SYS_DEBUG("audio underrun\n");
				snd_pcm_prepare(aud->handle);
			} else
			{
				SYS_ERROR("write to audio interface failed (%s) %d %d %d %d %d\n", snd_strerror(retVal), retVal, EAGAIN, EPIPE, EBUSY, EFAULT);
				return DVEVM_ST_FAIL;
			}
		}
		else
		{
			buff += retVal * frame_byte;
			size -= retVal;
		}
		if (size < 0)
		{
			SYS_ERROR("size can not be -ve  \n");
			return DVEVM_ST_FAIL;
		}
		i++;
	}
	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_audioIn(DvevmStAudioInfo *aud, char *buff, int size)
{
	int retVal = 0;
	int frame_bytes = (snd_pcm_format_width(aud->format) / 8) * aud->numChannels;
	char *buffPtr = buff;

	size = size / frame_bytes; // number of frames

	if (SND_PCM_NONBLOCK != aud->blocking_mode)
	{
		do
		{
			retVal = snd_pcm_readi(aud->handle, buffPtr, size);
			if (retVal > 0)
			{
				buffPtr += retVal * frame_bytes;
				size -= retVal;
			} else if (-EPIPE == retVal)
			{
				SYS_OUT("audio over run\n");
				snd_pcm_prepare(aud->handle);
			}
		} while (((1 <= retVal) || (-EPIPE == retVal)) && (0 < size));
	}
	else
	{
		while ((size > 0) && (0 <= retVal))
		{
			do
			{
				retVal = snd_pcm_readi(aud->handle, buff, size);
			} while (-EAGAIN == retVal);
			if (retVal > 0)
			{
				buff += retVal * frame_bytes;
				size -= retVal;
			}
		}
	}

	if (0 > retVal)
	{
		SYS_ERROR("read from audio interface failed (%s) %d \n", snd_strerror(retVal), retVal);
		return DVEVM_ST_FAIL;
	}

	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_audioClose(DvevmStAudioInfo *aud)
{
	// Free the param structure
	snd_pcm_drain(aud->handle);
	snd_pcm_hw_params_free(aud->hw_params);
	snd_pcm_sw_params_free(aud->sw_params);
	if (aud->buff1)
	{
		Memory_contigFree(aud->buff1, aud->buffsize);
	}
	if (aud->buff2)
	{
		Memory_contigFree(aud->buff2, aud->buffsize);
	}
	// Close the PCM interface
	snd_pcm_close(aud->handle);

	return DVEVM_ST_SUCCESS;
}
