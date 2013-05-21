/*
 * dvtbAudPlay1Core.c
 *
 * DVTB(wince) XDM1.0 Audio Decode related Core Functions
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

#include "dvtbAudPlay1Core.h"
#include "dvtbMemory.h"

void
dvtb_audDec1ProcessEndMessage(DvevmStBool useAlgorithm, DvevmStBool fileBased, int nFrames)
{
        if (DVEVM_ST_FALSE == fileBased)//Driver based
        {
                if (useAlgorithm)
                        SYS_OUT("Audio [Decode]+[Play] completed for <%d> frames\n", nFrames - 1);
                else
                        SYS_OUT("Audio [Play] completed for <%d> frames\n", nFrames - 1);
        }
        else//File based
                SYS_OUT("Audio [Decode]+[dump] completed for <%d> frames\n", nFrames - 1);
}

void
dvtb_audDec1InitPtrs(DvevmStAudDec1Info *ad)
{
        int i = 0;

		ad->hTime = NULL;
        ad->ceHdl = NULL;
        ad->adecHdl = NULL;

        for (i = 0; i < MAX_XDM_BUFS; i++)
        {
                ad->inBuf.bufs[i] = NULL;
                ad->outBuf.bufs[i] = NULL;
        }
}

DvevmStRetCode
dvtb_audDec1HanInit(DvevmStAudDec1Info *ad, char *engName)
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


                if (DVEVM_ST_FAIL == dvtb_audDec1Init(ad))
                {
                        SYS_ERROR("Unable to initialize Audio Decoder <%s>\n", ad->adecName);
                        retCode = DVEVM_ST_FAIL;
                        break;
                }
        }while(DVEVM_ST_FALSE);

        return retCode;
}

void
dvtb_audDec1HanClose(DvevmStAudDec1Info *ad, char *engName)
{
        dvtb_audDec1Close(ad);
        SYS_OUT("Audio Decoder <%s> closed\n", ad->adecName);

        if (DVEVM_ST_FAIL == dvtb_ceDeInit(&ad->ceHdl))
                SYS_ERROR("Unable to close Engine <%s>\n", engName);
        else
                SYS_OUT("Engine <%s> closed\n", engName);
}


DvevmStRetCode
dvtb_audDec1OutBuffAlloc(DvevmStXdmBuffer *outBuf)
{
        DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

        if (DVEVM_ST_FAIL == dvtb_allocSingleBufCmem(&outBuf->bufs[0], outBuf->bufSizes[0]))
        {
                SYS_ERROR("Unable to allocate output buffer \n" );
                retCode = DVEVM_ST_FAIL;
        }

        return retCode;
}


void
dvtb_audDec1OutBuffFree(DvevmStXdmBuffer *outBuf)
{
        if(NULL != outBuf->bufs[0])
                dvtb_freeSingleBufCmem(outBuf->bufs[0], outBuf->bufSizes[0]);

}

DvevmStRetCode
dvtb_audDec1DecProcess(DvevmStAudDec1Info *ad, int *decDuration)
{
        DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

        do
        {
                if (DVEVM_ST_FAIL == dvtb_audDec1Decode(ad, decDuration))
                {
                        SYS_ERROR("Unable to decode <%s> \n", ad->adecName);
                        retCode = DVEVM_ST_FAIL;
                        break;
                }

                ad->adecCmd = XDM_GETSTATUS;
                if (DVEVM_ST_FAIL == dvtb_audDec1Control(ad))
                {
                        SYS_ERROR("Unable to get the status \n");
                        retCode = DVEVM_ST_FAIL;
                        break;
                }
        }while(DVEVM_ST_FALSE);

        return retCode;
}

#if 0
DvevmStRetCode
dvtb_audDec1ProcessOutBuff(DvevmStAudioInfo *aud, DvevmStBool fileBased, char *buff, int nBytes, FILE *fp)
{
        DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

        if (DVEVM_ST_TRUE == fileBased)
        {
                if(DVEVM_ST_FAIL ==  dvtb_fileWrite(fp, buff, nBytes))
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
dvtb_audDec1SetSampleRate(DvevmStAudioInfo *aud, int sampleRate)
{
        DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

        if (aud->sampleRate != sampleRate)
        {
                aud->sampleRate = sampleRate;
                if (DVEVM_ST_FAIL == dvtb_audioControl(aud))
                {
                        SYS_ERROR("Unable to set the sample rate\n");
                        retCode = DVEVM_ST_FAIL;
                }
        }

        return retCode;
}
#endif
int
dvtb_audDec1getOutPutBytes(IAUDDEC1_Status *adecStatus)
{
        int numchannels = 0, outputbitwidth = 0, nBytes = 0;

        numchannels = (adecStatus->channelMode == 0) ? 1 : 2;
        outputbitwidth = adecStatus->outputBitsPerSample;
        outputbitwidth = outputbitwidth >> 3;
        nBytes = (adecStatus->numSamples * outputbitwidth * numchannels);
        return nBytes;

}

DvevmStRetCode
dvtb_audDec1ReadInput(char *inBuffer, int *totalBytesConsumed, int *bytesRemaining, int buffsize, FILE *fp, int *nBytes)
{
        DvevmStRetCode retval = DVEVM_ST_SUCCESS;

        if(*bytesRemaining)
                memcpy(&inBuffer[0], &inBuffer[*totalBytesConsumed], *bytesRemaining);

        if (DVEVM_ST_FAIL == dvtb_fileRead(fp, &inBuffer[*bytesRemaining], buffsize - *bytesRemaining, nBytes))
        {
                SYS_ERROR("Error in file read \n");
                retval = DVEVM_ST_FAIL;

        }
        else
        {
                *nBytes += *bytesRemaining;
                *bytesRemaining = *nBytes;
                *totalBytesConsumed = 0;
        }

        return retval;
}


