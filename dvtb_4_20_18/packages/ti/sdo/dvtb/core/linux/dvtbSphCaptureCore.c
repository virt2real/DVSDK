/*
 * dvtbSphCaptureCore.c
 *
 * XDM0.9 Speech Encode related Core Functions
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
#include "dvtbSphCaptureCore.h"
#include "dvtbUtils.h"

void
dvtb_sphEncProcessEndMessage(DvevmStBool useAlgorithm, DvevmStBool fileBased, int seconds)
{
	if (DVEVM_ST_FALSE == fileBased)//Driver based
	{
		if (useAlgorithm)
			SYS_OUT("Speech [Capture]+[Encode] completed for %d seconds\n",	seconds);
		else
			SYS_OUT("Speech [Capture] completed for %d seconds\n", seconds);
	}
	else//File based
		SYS_OUT("Speech [File Read]+[Encode] completed\n");
}

void
dvtb_sphEncInitPtrs(DvevmStSphEncInfo *se)
{
	se->ceHdl = NULL;
	se->sencHdl = NULL;

	se->inBuf.start = NULL;
	se->outBuf.start = NULL;
}

DvevmStRetCode
dvtb_sphEncHanInit(DvevmStSphEncInfo *se, char *engName)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	do
	{
		if (DVEVM_ST_FAIL == dvtb_ceInit(engName, &se->ceHdl))
		{
			SYS_ERROR("Unable to initialize Codec Engine <%s>\n", engName);
			retCode = DVEVM_ST_FAIL;
			break;
		}

		if (DVEVM_ST_FAIL == dvtb_sphEncInit(se))
		{
			SYS_ERROR("Unable to initialize Speech Encoder <%s>\n", se->sencName);
			retCode = DVEVM_ST_FAIL;
			break;
		}

	}while(DVEVM_ST_FALSE);

	return retCode;
}

void
dvtb_sphEncHanClose(DvevmStSphEncInfo *se, char *engName)
{
	dvtb_sphEncClose(se);
	SYS_OUT("Speech Encoder <%s> closed\n", se->sencName);

	if (DVEVM_ST_FAIL == dvtb_ceDeInit(&se->ceHdl))
		SYS_ERROR("Unable to close Engine <%s>\n", engName);
	else
		SYS_OUT("Engine <%s> closed\n", engName);
}

DvevmStRetCode
dvtb_sphEncReadInput(DvevmStAudioInfo *aud, char *buff, FILE *fp, int bytesToRead, DvevmStBool fileBased, int *nBytes)
{
	DvevmStRetCode retval = DVEVM_ST_SUCCESS;

	if (DVEVM_ST_TRUE == fileBased)
	{
		if(DVEVM_ST_FAIL == dvtb_fileRead(fp, buff, bytesToRead, nBytes))
		{
			SYS_ERROR("Error in file read \n");
			retval = DVEVM_ST_FAIL;
		}
	}
	else
	{
		*nBytes = dvtb_audioIn(aud, buff, SPHENC1_FRAME_SIZE * 4);

		if(DVEVM_ST_FAIL == *nBytes)
			retval = DVEVM_ST_FAIL;
	}

	return retval;
}

DvevmStRetCode
dvtb_sphEncEncProcess(DvevmStSphEncInfo *se, char *buff, int *encDuration)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	if(DVEVM_ST_FAIL == dvtb_stereoToMono((short *) buff, (short *) se->inBuf.start, SPHENC_FRAME_SIZE))
	{
		SYS_ERROR("Unable to convert stereo to mono\n");
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		memset(se->outBuf.start, 0, se->outBuf.size);

		if (DVEVM_ST_FAIL == dvtb_sphEncEncode(se, encDuration))
		{
			SYS_ERROR("Unable to encode the input buffer\n");
			se->sencCmd = XDM_GETSTATUS;

			if (DVEVM_ST_FAIL == dvtb_sphEncControl(se))
				SYS_ERROR("Unable to get the status\n");
			else
				SYS_ERROR("Codec Error = %d\n", (int) se->sencStatus.extendedError);

			retCode = DVEVM_ST_FAIL;
		}
	}

	return retCode;
}
