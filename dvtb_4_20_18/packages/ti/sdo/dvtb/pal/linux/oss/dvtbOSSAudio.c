/*
 * dvtbOSSAudio.c
 *
 * OSS driver Interface implementation
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

#include "dvtbOSSAudio.h"

DvevmStRetCode
dvtb_audioControl(DvevmStAudioInfo *aud)
{
	ASSERT(aud != NULL);
	ASSERT(aud->sndFd != DVEVM_ST_FAIL);

	if (DVEVM_ST_FAIL == ioctl(aud->sndFd, SNDCTL_DSP_SETFMT, &(aud->sampleSize)))
	{
		SYS_PERROR("Unable to set the sample size : %d", aud->sampleSize);
	}
	else if (DVEVM_ST_FAIL == ioctl(aud->sndFd, SNDCTL_DSP_SPEED, &(aud->sampleRate)))
	{
		SYS_PERROR("Unable to set the sample rate : %d", aud->sampleRate);
	}
	else if (DVEVM_ST_FAIL == ioctl(aud->sndFd, SNDCTL_DSP_CHANNELS, &(aud->numChannels)))
	{
		SYS_PERROR("Unable to set the number of channels : %d", aud->numChannels);
	}
	else
	{
		SYS_DEBUG("\nAudio Device <%s> Control:\n", aud->device);
		SYS_DEBUG("Sample Size => %d\n", aud->sampleSize);
		SYS_DEBUG("Sample Rate => %d\n", aud->sampleRate);
		SYS_DEBUG("Channel Nos => %d\n", aud->numChannels);
		return DVEVM_ST_SUCCESS;
	}

	return DVEVM_ST_FAIL;
}

DvevmStRetCode
dvtb_audioSetup(DvevmStAudioInfo *aud)
{
	DvevmStRetCode rc = DVEVM_ST_FAIL;
	int opMode = 0;
	int recMask = 0, sndMask = 0;
	int mixerFd = DVEVM_ST_FAIL;
	int vol = 100 | (100 << 8);

	ASSERT(aud != NULL);

	aud->sndFd = DVEVM_ST_FAIL;
	aud->sampleSize = (DVEVM_ST_FAIL == aud->sampleSize) ? DEF_SAMPLE_SIZE : aud->sampleSize;
	aud->sampleRate = (DVEVM_ST_FAIL == aud->sampleRate) ? DEF_SAMPLE_RATE : aud->sampleRate;
	aud->numChannels = (DVEVM_ST_FAIL == aud->numChannels) ? DEF_NUM_CHANNELS : aud->numChannels;
	aud->frameSize = aud->sampleRate * aud->sampleSize * aud->numChannels / 8;

	opMode = (DVEVM_ST_CAPTURE == aud->mode) ? O_RDONLY : O_WRONLY;
	sndMask = (MIC == aud->src) ? SOUND_MASK_MIC : SOUND_MASK_LINE;

	if (0 == aud->device[0])
		strcpy(aud->device, DEF_SND_DEVICE);

	if (DVEVM_ST_CAPTURE == aud->mode)
	{
		if (DVEVM_ST_FAIL == (mixerFd = open(DEF_MIXER_DEVICE, O_RDONLY)))
		{
			SYS_ERROR("Unable to open mixer device : %s\n", DEF_MIXER_DEVICE);
		}
		else if (DVEVM_ST_FAIL == ioctl(mixerFd, SOUND_MIXER_READ_RECMASK, &recMask))
		{
			SYS_PERROR("Unable to query audio device\n");
		}
		else if (0 == (recMask & sndMask))
		{
			SYS_PERROR("Recorder not supported\n");
		}
		else if (DVEVM_ST_FAIL == ioctl(mixerFd, SOUND_MIXER_WRITE_RECSRC, &sndMask))
		{
			SYS_PERROR("Unable to set recorder.\n");
		}
		else if (ioctl(mixerFd, SOUND_MIXER_WRITE_IGAIN, &vol) == -1)
		{
			SYS_PERROR("Unable to set the volume of line in.\n");
		}
		else
		{
			SYS_OUT("Mixer device <%s> successfully configured\n", DEF_MIXER_DEVICE);
			rc = DVEVM_ST_SUCCESS;
		}

		close(mixerFd);
		if (DVEVM_ST_FAIL == rc)
			return rc;
	}

	if (DVEVM_ST_FAIL == (aud->sndFd = open(aud->device, opMode)))
	{
		SYS_PERROR("Unable to initialize audio device : %s", aud->device);
	}
	else if (DVEVM_ST_FAIL == dvtb_audioControl(aud))
	{
		SYS_ERROR("Unable to set audio parameters\n");
	}
	else
	{
		SYS_DEBUG("Initialized the audio device : %s\n", aud->device);
		return DVEVM_ST_SUCCESS;
	}

	return DVEVM_ST_FAIL;
}

DvevmStRetCode
dvtb_audioIn(DvevmStAudioInfo *aud, char *buff, int size)
{
	int nBytes = DVEVM_ST_FAIL;
	int blksize = DVEVM_ST_FAIL;
	int count = 0;
	char *buffPtr = buff;

	ASSERT(aud != NULL);
	ASSERT(buff != NULL);
	ASSERT(aud->sndFd != DVEVM_ST_FAIL);
	ASSERT(aud->mode == DVEVM_ST_CAPTURE);

	if (DVEVM_ST_FAIL == ioctl(aud->sndFd, SNDCTL_DSP_GETBLKSIZE, &blksize))
	{
		SYS_PERROR("Unable to get block size of audio driver : %d", aud->sndFd);
		return DVEVM_ST_FAIL;
	}

	while (count < size)
	{
		if ((size - count) < blksize)
			blksize = size - count;

		if (DVEVM_ST_FAIL == (nBytes = read(aud->sndFd, buffPtr, blksize)))
		{
			SYS_PERROR("Unable to read %d bytes from audio device\n", blksize);
			return DVEVM_ST_FAIL;
		}

		count += blksize;
		buffPtr += blksize;
	}

	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_audioOut(DvevmStAudioInfo *aud, char *buff, int size)
{
	int nBytes = DVEVM_ST_FAIL;
	int blksize = DVEVM_ST_FAIL;
	int count = 0;
	char *buffPtr = buff;

	ASSERT(aud != NULL);
	ASSERT(buff != NULL);
	ASSERT(aud->sndFd != DVEVM_ST_FAIL);
	ASSERT(aud->mode == DVEVM_ST_PLAY);

	if (DVEVM_ST_FAIL == ioctl(aud->sndFd, SNDCTL_DSP_GETBLKSIZE, &blksize))
	{
		SYS_PERROR("Unable to get block size of audio driver : %d", aud->sndFd);
		return DVEVM_ST_FAIL;
	}

	while (count < size)
	{
		if ((size - count) < blksize)
			blksize = size - count;

		if (DVEVM_ST_FAIL == (nBytes = write(aud->sndFd, buffPtr, blksize)))
		{
			SYS_PERROR("Unable to write %d bytes to audio device\n", blksize);
			return DVEVM_ST_FAIL;
		}

		count += blksize;
		buffPtr += blksize;
	}

	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_audioClose(DvevmStAudioInfo *aud)
{
	ASSERT(aud != NULL);

	close(aud->sndFd);
	aud->sndFd = DVEVM_ST_FAIL;

	return DVEVM_ST_SUCCESS;
}
