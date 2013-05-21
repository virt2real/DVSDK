/*
 * dvtbAC3Play1Core.c
 *
 * XDM1.0 AC3 Decode related Core Functions
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

#include "dvtbAC3Play1Core.h"
#include "dvtbMemory.h"
#define NUM_CHANS 6

void
dvtb_ac3Dec1ProcessEndMessage(DvevmStBool useAlgorithm, DvevmStBool fileBased, int nFrames)
{
        if (DVEVM_ST_FALSE == fileBased)//Driver based
        {
                if (useAlgorithm)
                        SYS_OUT("AACHE [Decode]+[Play] completed for <%d> frames\n", nFrames - 1);
                else
                        SYS_OUT("AACHE [Play] completed for <%d> frames\n", nFrames - 1);
        }
        else//File based
                SYS_OUT("AACHE [Decode]+[dump] completed for <%d> frames\n", nFrames - 1);
}

void
dvtb_ac3Dec1InitPtrs(DvevmStAC3Dec1Info *ad)
{
        int i = 0;

        ad->ceHdl = NULL;
        ad->adecHdl = NULL;

        for (i = 0; i < MAX_XDM_BUFS; i++)
        {
                ad->inBuf.bufs[i] = NULL;
                ad->outBuf.bufs[i] = NULL;
        }
}

DvevmStRetCode
dvtb_ac3Dec1HanInit(DvevmStAC3Dec1Info *ad, char *engName)
{
        DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

        do //Dummy loop for easy clean up
        {
                if (DVEVM_ST_FAIL == dvtb_ceInit(engName, &ad->ceHdl))
                {
                        SYS_ERROR("Unable to initialize Codec Engine <%s>\n", engName);
                        retCode = DVEVM_ST_FAIL;
                        break;
                }


                if (DVEVM_ST_FAIL == dvtb_ac3Dec1Init(ad))
                {
                        SYS_ERROR("Unable to initialize Audio Decoder <%s>\n", ad->adecName);
                        retCode = DVEVM_ST_FAIL;
                        break;
                }
        }while(DVEVM_ST_FALSE);

        return retCode;
}

void
dvtb_ac3Dec1HanClose(DvevmStAC3Dec1Info *ad, char *engName)
{
        dvtb_ac3Dec1Close(ad);
        SYS_OUT("Audio Decoder <%s> closed\n", ad->adecName);

        if (DVEVM_ST_FAIL == dvtb_ceDeInit(&ad->ceHdl))
                SYS_ERROR("Unable to close Engine <%s>\n", engName);
        else
                SYS_OUT("Engine <%s> closed\n", engName);
}


DvevmStRetCode
dvtb_ac3Dec1DecProcess(DvevmStAC3Dec1Info *ad, int *decDuration)
{
        DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

        do
        {
                if (DVEVM_ST_FAIL == dvtb_ac3Dec1Decode(ad, decDuration))
                {
                        SYS_ERROR("Unable to decode <%s> \n", ad->adecName);
                        retCode = DVEVM_ST_FAIL;
                        break;
                }

                ad->adecCmd = XDM_GETSTATUS;
                if (DVEVM_ST_FAIL == dvtb_ac3Dec1Control(ad))
                {
                        SYS_ERROR("Unable to get the status \n");
                        retCode = DVEVM_ST_FAIL;
                        break;
                }
        }while(DVEVM_ST_FALSE);

        return retCode;
}

DvevmStRetCode
dvtb_ac3Dec1ProcessOutBuff(DvevmStAudioInfo *aud, DvevmStAC3Dec1Info *ad, DvevmStBool fileBased, char *buff, int nBytes, FILE *fp1, FILE *fp2, FILE *fp3)
{
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;
	
	if (DVEVM_ST_TRUE == fileBased)
	{
		if(DVEVM_ST_FAIL ==  dvtb_ac3WriteToThreeStereoFiles((XDAS_Int32 **)&buff, (XDAS_Int32) ad->adecOutArgs.auddec_outArgs.channelMode, fp1, fp2, fp3, (XDAS_Int32) ad->adecOutArgs.auddec_outArgs.numSamples, (XDAS_Int32) ad->adecParams.auddec_params.outputPCMWidth, (XDAS_Int32) ad->adecStatus.auddec_status.pcmFormat, (XDAS_Int32) ad->adecOutArgs.auddec_outArgs.lfeFlag) )
		{
			SYS_ERROR("Error in writing to file.\n");
			retCode = DVEVM_ST_FAIL;
		}
	}
	else
	{
		if (DVEVM_ST_FAIL == dvtb_audioOut(aud, buff, nBytes))
		{
			SYS_ERROR("Unable to write into target device\n");
			retCode = DVEVM_ST_FAIL;
		}
	}
	
	return retCode;
}


DvevmStRetCode
dvtb_ac3WriteToThreeStereoFiles(XDAS_Int32 **ppData, XDAS_Int32 channelMode, FILE *fp1, FILE *fp2, FILE *fp3 , XDAS_Int32 samples, XDAS_Int32 bit_precision, XDAS_Int32 pcmFormat, XDAS_Int32 lfeFlag)
{
	XDAS_Int32 *pL, *pR;
	XDAS_UInt32 offset;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	offset = (pcmFormat == IAUDIO_BLOCK) ? samples : 1;

	// Dump L/R, Ls/Rs and C/sw to three different stereo PCM files

	if( (NULL == fp1) || (NULL == fp2) || (NULL == fp3))
	{
		SYS_ERROR("dvtb_ac3WriteToThreeStereoFiles: output file is NULL \n");
		retCode = DVEVM_ST_FAIL;
	}
	else
	{
		if ((channelMode == IAUDIO_1_0) && (lfeFlag == XDAS_FALSE))
		{
			pL = ppData[0];
			if (DVEVM_ST_FAIL == dvtb_ac3WriteToAStereoFile(pL,NULL, fp1, samples, bit_precision, pcmFormat, 1))
			{
				SYS_ERROR("dvtb_ac3WriteToThreeStereoFiles: fail to write in out file \n");
				retCode = DVEVM_ST_FAIL;
			}
		}
		else if ((channelMode == IAUDIO_2_0 || channelMode == IAUDIO_11_0) && (lfeFlag == XDAS_FALSE))
		{
			pL = ppData[0];
			pR = (bit_precision == 24) ? ppData[0]+offset : (XDAS_Int32 *)((XDAS_Int16 *)ppData[0]+offset);
			if (DVEVM_ST_FAIL == dvtb_ac3WriteToAStereoFile(pL,pR, fp1, samples, bit_precision, pcmFormat, 2))
			{
				SYS_ERROR("dvtb_ac3WriteToThreeStereoFiles: fail to write in out file \n");
				retCode = DVEVM_ST_FAIL;
			}
		}
		else
		{
			pL = ppData[0];
			pR = (bit_precision == 24) ? ppData[0]+offset : (XDAS_Int32 *)((XDAS_Int16 *)ppData[0]+offset);
			if (DVEVM_ST_FAIL == dvtb_ac3WriteToAStereoFile(pL,pR, fp1, samples, bit_precision, pcmFormat, NUM_CHANS))
			{
				SYS_ERROR("dvtb_ac3WriteToThreeStereoFiles: fail to write in out file \n");
				retCode = DVEVM_ST_FAIL;
			}
			else
			{	
				pL = (bit_precision == 24) ? ppData[0]+(offset*2) : (XDAS_Int32 *)((XDAS_Int16 *)ppData[0]+(offset*2));
				pR = (bit_precision == 24) ? ppData[0]+(offset*3) : (XDAS_Int32 *)((XDAS_Int16 *)ppData[0]+(offset*3));
				if (DVEVM_ST_FAIL == dvtb_ac3WriteToAStereoFile(pL,pR, fp2, samples, bit_precision, pcmFormat, NUM_CHANS))
				{
					SYS_ERROR("dvtb_ac3WriteToThreeStereoFiles: fail to write in out file \n");
					retCode = DVEVM_ST_FAIL;
				}
				else
				{
					pL = (bit_precision == 24) ? ppData[0]+(offset*4) : (XDAS_Int32 *)((XDAS_Int16 *)ppData[0]+(offset*4));
					pR = (bit_precision == 24) ? ppData[0]+(offset*5) : (XDAS_Int32 *)((XDAS_Int16 *)ppData[0]+(offset*5));
					if (DVEVM_ST_FAIL == dvtb_ac3WriteToAStereoFile(pL,pR, fp3, samples, bit_precision, pcmFormat, NUM_CHANS))
					{
						SYS_ERROR("dvtb_ac3WriteToThreeStereoFiles: fail to write in out file \n");
						retCode = DVEVM_ST_FAIL;
					}
				}
			}
		}
	}	


    return retCode;
}



DvevmStRetCode
dvtb_ac3WriteToAStereoFile(XDAS_Int32 *pLeft, XDAS_Int32 *pRght, FILE *fp, XDAS_Int32 samples, XDAS_Int32 bit_precision, XDAS_Int32 pcmFormat, XDAS_Int32 numChans)
{
	int i = 0, bytesPerSample = 0, l = 0, r = 0, size = 0;
	XDAS_Int16 *pOut1, *pOut2;
	DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

	bytesPerSample = (bit_precision == 16)?2:3; // 16 or 24-bit

	do
	{
		if (bit_precision == 24)
		{
			if (pcmFormat == IAUDIO_BLOCK || numChans == 1)
			{
				for(i=0; i<samples; i++)
				{
					// signal is in 1Q31 format
					l = pLeft[i];
					// convert 1Q31 signal to 16 or 24 bit for dumping
					l = l>>(32-bit_precision);
					
					if(DVEVM_ST_FAIL == dvtb_fileWrite(fp, (char *)&l, bytesPerSample))
					{
						SYS_ERROR("dvtb_ac3WriteToAStereoFile: Failed in trying to write Left channel data \n");
						retCode = DVEVM_ST_FAIL;
						break;
					}
					
					if (NULL != pRght)
					{
						// signal is in 1Q31 format
						r = pRght[i];
						// convert 1Q31 signal to 16 or 24 bit for dumping
						r = r>>(32-bit_precision);
	
						if(DVEVM_ST_FAIL == dvtb_fileWrite(fp, (char *)&r, bytesPerSample))
						{
							SYS_ERROR("dvtb_ac3WriteToAStereoFile: Failed in trying to write Right channel data \n");
							retCode = DVEVM_ST_FAIL;
							break;
						}
					}
				}
			}
			else
			{
				size = samples*numChans;
				for(i = 0; i < size; i += numChans)
				{
					// signal is in 1Q31 format
					l = pLeft[i];
					// convert 1Q31 signal to 16 or 24 bit for dumping
					l = l>>(32-bit_precision);

					if(DVEVM_ST_FAIL == dvtb_fileWrite(fp, (char *)&l, bytesPerSample))
					{
						SYS_ERROR("dvtb_ac3WriteToAStereoFile: Failed in trying to write Left channel data \n");
						retCode = DVEVM_ST_FAIL;
						break;
					}			
	
					if (NULL != pRght)
					{
						// signal is in 1Q31 format
						r = pRght[i];
						// convert 1Q31 signal to 16 or 24 bit for dumping
						r = r>>(32-bit_precision);
						if(DVEVM_ST_FAIL == dvtb_fileWrite(fp, (char *)&r, bytesPerSample))
						{
							SYS_ERROR("dvtb_ac3WriteToAStereoFile: Failed in trying to write Right channel data \n");
							retCode = DVEVM_ST_FAIL;
							break;
						}				
	
					}
				}
			}	
		}
		else
		{
			pOut1 = (XDAS_Int16 *)pLeft;
			pOut2 = (XDAS_Int16 *)pRght;
			if (pcmFormat == IAUDIO_BLOCK || numChans == 1)
			{
				for(i=0; i<samples; i++)
				{
					// signal is in 1Q31 format
					if(DVEVM_ST_FAIL == dvtb_fileWrite(fp, (char *)&pOut1[i], bytesPerSample))
					{
						SYS_ERROR("dvtb_ac3WriteToAStereoFile: Failed in trying to write Left channel data \n");
						retCode = DVEVM_ST_FAIL;
						break;
					}			
					
	
					if (pRght != NULL)
					{
						if(DVEVM_ST_FAIL == dvtb_fileWrite(fp, (char *)&pOut2[i], bytesPerSample))
						{
							SYS_ERROR("dvtb_ac3WriteToAStereoFile: Failed in trying to write Right channel data \n");
							retCode = DVEVM_ST_FAIL;
							break;
						}			
					}
				}
			}
			else
			{
				size = samples*numChans;
				for(i=0; i < size; i+=numChans)
				{
					// signal is in 1Q31 format
					if(DVEVM_ST_FAIL == dvtb_fileWrite(fp, (char *)&pOut1[i], bytesPerSample))
					{
						SYS_ERROR("dvtb_ac3WriteToAStereoFile: Failed in trying to write Left channel data \n");
						retCode = DVEVM_ST_FAIL;
						break;
					}			
					if (pRght != NULL)
					{
						if(DVEVM_ST_FAIL == dvtb_fileWrite(fp, (char *)&pOut2[i], bytesPerSample))
						{
							SYS_ERROR("dvtb_ac3WriteToAStereoFile: Failed in trying to write Right channel data \n");
							retCode = DVEVM_ST_FAIL;
							break;
						}			
					}
				}
			}	
		}
	}while(DVEVM_ST_FALSE);

    return retCode;
}

