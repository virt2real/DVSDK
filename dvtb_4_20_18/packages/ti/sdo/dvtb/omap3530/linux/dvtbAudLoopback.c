/*
 * dvtbAudLoopback.c
 *
 * ALSA specific Audio loop back Functionality
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
#include "dvtbAudLoopback.h"
#include "dvtbDefs.h"
#include "dvtbUtils.h"

#define FRAME_SIZE       (1024)


void
dvtb_AudLoopback(DvevmStThreadInfo *T)
{
	char *buff = NULL, tempBuff[FRAME_SIZE*2];

	int loop = 1000,  nBytes = DVEVM_ST_FAIL;

	DvevmStAudioInfo aud_playback; // Audio Driver Info
	DvevmStRetCode retval = DVEVM_ST_FAIL;
	DvevmStBool usecaseFailed = DVEVM_ST_FALSE, audioCapDevOpened =	DVEVM_ST_FALSE, audioPlayDevOpened =	DVEVM_ST_FALSE;

	if (T->sourceFp)
	{
		SYS_ERROR("Source file is not needed \n");
		dvtb_fileClose(&T->sourceFp, &T->targetFp);
		dvtb_freeThr(T);
		dvtb_threadExit( );
	}

	if (T->targetFp)
	{
		SYS_ERROR("Target file is not needed \n");
		dvtb_fileClose(&T->sourceFp, &T->targetFp);
		dvtb_freeThr(T);
		dvtb_threadExit( );
	}

	do
	{

		memcpy(&aud_playback, &T->g.aud, sizeof(aud_playback));
		T->g.aud.mode = SND_PCM_STREAM_CAPTURE;
		retval = dvtb_audioSetup(&T->g.aud);
		if (DVEVM_ST_FAIL == retval)
		{
			SYS_ERROR("Unable to initialize Audio device <%s> for capture\n", T->g.aud.device);
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}
		audioCapDevOpened = DVEVM_ST_TRUE;
		SYS_OUT("Audio Device <%s> initialized for capture\n", T->g.aud.device);

		aud_playback.mode = SND_PCM_STREAM_PLAYBACK;
		retval = dvtb_audioSetup(&aud_playback);
		if (DVEVM_ST_FAIL == retval)
		{
			SYS_ERROR("Unable to setup Audio device <%s> for playback\n", aud_playback.device);
			usecaseFailed = DVEVM_ST_TRUE;
			break;
		}
		audioPlayDevOpened = DVEVM_ST_TRUE;

		SYS_OUT("Audio device <%s> initialized for playback\n", aud_playback.device);

		while (loop--)
		{
			buff = tempBuff;

			nBytes = dvtb_audioIn(&T->g.aud, buff, FRAME_SIZE);
			if (DVEVM_ST_FAIL == nBytes)
			{
				SYS_ERROR("Failed to capture\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}

			nBytes = dvtb_audioOut(&aud_playback, buff, FRAME_SIZE);
			if (DVEVM_ST_FAIL == nBytes)
			{
				SYS_ERROR("Unable to write into target device\n");
				usecaseFailed = DVEVM_ST_TRUE;
				break;
			}
		}
	} while (DVEVM_ST_FALSE); // Dummy loop

	if(DVEVM_ST_TRUE == audioCapDevOpened)
	{
		dvtb_audioClose(&T->g.aud);
		SYS_OUT("Audio capture Device <%s>  is closed\n", T->g.aud.device);
	}

	if(DVEVM_ST_TRUE == audioPlayDevOpened)
	{
		dvtb_audioClose(&aud_playback);
		SYS_OUT("Audio Playback device <%s> is closed.\n", aud_playback.device);
	}

	if(DVEVM_ST_TRUE == usecaseFailed)
		SYS_OUT("Audio Loopback usecase completed with error\n");
	else
		SYS_OUT("Audio Loopback usecase Successfully completed \n");

	dvtb_freeThr(T);
	dvtb_threadExit( );
}
