/*
 * dvtbSphPlay1Core.c
 *
 * XDM1.0 Speech Decode related Core Functions
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

#include "dvtbSphPlay1Core.h"
#include "dvtbUtils.h"

void
dvtb_sphDec1ProcessEndMessage(DvevmStBool useAlgorithm, DvevmStBool fileBased, int nFrames)
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

void
dvtb_sphDec1InitPtrs(DvevmStSphDec1Info *sd)
{
	sd->ceHdl = NULL;
	sd->sdecHdl = NULL;

	sd->inBuf.start = NULL;
	sd->outBuf.start = NULL;
}

DvevmStRetCode
dvtb_sphDec1HanInit(DvevmStSphDec1Info *sd, char *engName)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	if ((!(strcmp(sd->sdecName, "g722dec"))) && (sd->sdecParams.codecSelection == 1))
		sd->inBuf.size = SPHDEC1_INBUF_SIZE * 2; /* #define SPHDEC1_INBUF_SIZE       (80) */

	if (!(strcmp(sd->sdecName, "ilbcdec")))
	{
		if (sd->sdecParams.codecSelection == 0)
			sd->inBuf.size = PRM_SIZE_20; /* #define PRM_SIZE_20  38  */
		else
			sd->inBuf.size = PRM_SIZE_30; /* #define PRM_SIZE_30  50 */

		sd->outBuf.size = 480;
	}

	do //Dummy loop for easy clean up
	{
		if (DVEVM_ST_FAIL == dvtb_ceInit(engName, &sd->ceHdl))
		{
			SYS_ERROR("Unable to initialize Codec Engine <%s>\n", engName);
			retCode = DVEVM_ST_FAIL;
			break;
		}

		if (DVEVM_ST_FAIL == dvtb_sphDec1Init(sd))
		{
			SYS_ERROR("Unable to initialize Speech Decoder <%s>\n", sd->sdecName);
			retCode = DVEVM_ST_FAIL;
			break;
		}
	}while(DVEVM_ST_FALSE);

	return retCode;
}

void
dvtb_sphDec1HanClose(DvevmStSphDec1Info *sd, char *engName)
{
	dvtb_sphDec1Close(sd);
	SYS_OUT("Speech Decoder <%s> closed\n", sd->sdecName);

	if (DVEVM_ST_FAIL == dvtb_ceDeInit(&sd->ceHdl))
		SYS_ERROR("Unable to close Engine <%s>\n", engName);
	else
		SYS_OUT("Engine <%s> closed\n", engName);
}

DvevmStRetCode
dvtb_sphDec1DecProcess(DvevmStSphDec1Info *sd, int size,  int *decDuration)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	do
	{
		if (!(strcmp(sd->sdecName, "ilbcdec")))
		{
			if (DVEVM_ST_FAIL == dvtb_sphDec1Control1(sd))
			{
				SYS_ERROR("Unable to SETSTATUS Speech Decoder <%s>\n", sd->sdecName);
				retCode = DVEVM_ST_FAIL;
				break;
			}
		}

		if ((!(strcmp(sd->sdecName, "g722dec"))) && (sd->sdecParams.codecSelection == 1))
		{
			if (DVEVM_ST_FAIL == dvtb_byteSwapBitStream((char *) sd->inBuf.start, (short) size))
			{
				SYS_ERROR("Unable to Swap bytes in bitstream \n");
				retCode = DVEVM_ST_FAIL;
				break;
			}
		}

		memset(sd->outBuf.start, 0, sd->outBuf.size);

		if (DVEVM_ST_FAIL == dvtb_sphDec1Decode(sd, decDuration))
		{
			SYS_ERROR("Unable to decode <%s> \n", sd->sdecName);
			retCode = DVEVM_ST_FAIL;
			break;
		}
	}while(DVEVM_ST_FALSE);
	return retCode;
}

int
dvtb_sphDec1GetOutputBytes(DvevmStSphDec1Info *sd, int size)
{
	int nBytes = DVEVM_ST_FAIL;

	if (!(strcmp(sd->sdecName, "g722dec")))
	{
		if (!(sd->sdecParams.codecSelection == 1))
			nBytes = size * 4;
		else
			nBytes = size;
	}
	else if (!(strcmp(sd->sdecName, "ilbcdec")))
	{
		if (sd->sdecParams.codecSelection == 0)
			nBytes = 320;
		else
			nBytes = 480;
	}
	else
		nBytes = size * 2;

	return nBytes;

}

DvevmStRetCode
dvtb_sphDec1ReadInput(DvevmStSphDec1Info *sd, int size, FILE *fp, int *nBytes)
{
	int bytesToRead = 0;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	if (!(strcmp(sd->sdecName, "ilbcdec")))
	{
		if (sd->sdecParams.codecSelection == 0)
			bytesToRead = 38;
		else
			bytesToRead = 50;
	}
	else
		bytesToRead = size;

	if(DVEVM_ST_FAIL == dvtb_fileRead(fp, (char *)sd->inBuf.start, bytesToRead, nBytes))
	{
		SYS_ERROR("Error in file read \n");
		retCode = DVEVM_ST_FAIL;
	}

	return retCode;
}

DvevmStRetCode
dvtb_sphDec1ProcessOutBuff(DvevmStAudioInfo *aud, FILE *fp, char *buff, int nBytes, DvevmStBool fileBased)
{
	int k = 0;
	char tempBuff[320];
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
		for (k = 0; k < nBytes; k += 2)
		{
			tempBuff[k * 2] = tempBuff[k * 2 + 2] = buff[k];
			tempBuff[k * 2 + 1] = tempBuff[k * 2 + 3] = buff[k + 1];
		}

		if (DVEVM_ST_FAIL == dvtb_audioOut(aud, tempBuff, nBytes * 2))
		{
			SYS_ERROR("Unable to write into target device\n");
			retCode = DVEVM_ST_FAIL;
		}
	}

	return retCode;

}
