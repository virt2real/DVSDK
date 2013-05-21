/*
 * dvtbSphPlayCore.c
 *
 * XDM0.9 Speech Decode related Core Functions
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

#include "dvtbSphPlayCore.h"
#include "dvtbUtils.h"

/*********************************************************************
 *	dvtb_sphDecProcessEndMessage:
 *	Description: Print "Number of speech frames" processed
 ********************************************************************/
void
dvtb_sphDecProcessEndMessage(DvevmStBool useAlgorithm, DvevmStBool fileBased, int nFrames)
{
	if (DVEVM_ST_FALSE == fileBased)//Driver based
	{
		if (useAlgorithm)
			SYS_OUT("Speech [Decode]+[Play] completed for <%d> frames\n", nFrames - 1);
		else
			SYS_OUT("Speech [Play] completed for <%d> frames\n", nFrames - 1);
	}
	else//File based
		SYS_OUT("Speech [Decode]+[dump] completed for <%d> frames\n", nFrames - 1);
}

/*********************************************************************
 *	dvtb_sphDecInitPtrs:
 *	Description: Initialize elements of structure DvevmStSphDecInfo
 ********************************************************************/
void
dvtb_sphDecInitPtrs(DvevmStSphDecInfo *sd)
{
	//Initialize CE handle to NULL
	sd->ceHdl = NULL;

	//Initialize codec handle to NULL
	sd->sdecHdl = NULL;

	//Initialize input and output buffer pointers to NULL
	sd->inBuf.start = NULL;
	sd->outBuf.start = NULL;
}

/*********************************************************************
 *	dvtb_sphDecHanInit:
 *	Description: Initialize CE and codec instance
 ********************************************************************/
DvevmStRetCode
dvtb_sphDecHanInit(DvevmStSphDecInfo *sd, char *engName)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	do //Dummy loop for easy clean up
	{
		//Initialize CE
		if (DVEVM_ST_FAIL == dvtb_ceInit(engName, &sd->ceHdl))
		{
			SYS_ERROR("Unable to initialize Codec Engine <%s>\n", engName);
			retCode = DVEVM_ST_FAIL;
			break;
		}

		// Initialize codec instance
		if (DVEVM_ST_FAIL == dvtb_sphDecInit(sd))
		{
			SYS_ERROR("Unable to initialize Speech Decoder <%s>\n", sd->sdecName);
			retCode = DVEVM_ST_FAIL;
			break;
		}
	}while(DVEVM_ST_FALSE);

	return retCode;
}

/*********************************************************************
 *	dvtb_sphDecHanClose:
 *	Description: Close codec instance and CE
 ********************************************************************/
void
dvtb_sphDecHanClose(DvevmStSphDecInfo *sd, char *engName)
{
	// Close codec instance
	dvtb_sphDecClose(sd);
	SYS_OUT("Speech Decoder <%s> closed\n", sd->sdecName);

	// close CE
	if (DVEVM_ST_FAIL == dvtb_ceDeInit(&sd->ceHdl))
		SYS_ERROR("Unable to close Engine <%s>\n", engName);
	else
		SYS_OUT("Engine <%s> closed\n", engName);
}

/*********************************************************************
 *	dvtb_sphDecDecProcess:
 *	Description: Decode speech frame
 ********************************************************************/
DvevmStRetCode
dvtb_sphDecDecProcess(DvevmStSphDecInfo *sd, int *decDuration)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	// fill output buffer with zero's
	memset(sd->outBuf.start, 0, sd->outBuf.size);

	// Decode speech frame
	if (DVEVM_ST_FAIL == dvtb_sphDecDecode(sd, decDuration))
	{
		SYS_ERROR("Unable to decode <%s> \n", sd->sdecName);

		sd->sdecCmd = XDM_GETSTATUS;
		if (DVEVM_ST_FAIL == dvtb_sphDecControl(sd))
			SYS_ERROR("Unable to get the status\n");
		else
		SYS_ERROR("Codec Error = %d\n", (int) sd->sdecStatus.extendedError);

		retCode = DVEVM_ST_FAIL;
	}

	return retCode;
}

/*********************************************************************
 *	dvtb_sphDecDecProcess:
 *	Description: Either write output to file of play through driver
 ********************************************************************/
DvevmStRetCode
dvtb_sphDecProcessOutBuff(DvevmStAudioInfo *aud, FILE *fp, char *buff, int nBytes, DvevmStBool fileBased)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	if (DVEVM_ST_TRUE == fileBased)
	{
		// Store the processed frame to target file
		if(DVEVM_ST_FAIL ==  dvtb_fileWrite(fp, buff, nBytes))
		{
			SYS_ERROR("Error in writing to file.\n");
			retCode = DVEVM_ST_FAIL;
		}
	}
	else
	{
		// Play output through driver
		if (DVEVM_ST_FAIL == dvtb_audioOut(aud, buff, nBytes))
		{
			SYS_ERROR("Unable to write into target device\n");
			retCode = DVEVM_ST_FAIL;
		}
	}

	return retCode;
}

