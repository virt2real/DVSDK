/*
 * dvtbAACHEPlay1Core.c
 *
 * XDM1.0 AACHE Decode related Core Functions
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

#include "dvtbAACHEPlay1Core.h"
#include "dvtbMemory.h"

void
dvtb_aacheDec1ProcessEndMessage(DvevmStBool useAlgorithm, DvevmStBool fileBased, int nFrames)
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
dvtb_aacheDec1InitPtrs(DvevmStAacheDec1Info *ad)
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
dvtb_aacheDec1HanInit(DvevmStAacheDec1Info *ad, char *engName)
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


                if (DVEVM_ST_FAIL == dvtb_aacheDec1Init(ad))
                {
                        SYS_ERROR("Unable to initialize Audio Decoder <%s>\n", ad->adecName);
                        retCode = DVEVM_ST_FAIL;
                        break;
                }
        }while(DVEVM_ST_FALSE);

        return retCode;
}

void
dvtb_aacheDec1HanClose(DvevmStAacheDec1Info *ad, char *engName)
{
        dvtb_aacheDec1Close(ad);
        SYS_OUT("Audio Decoder <%s> closed\n", ad->adecName);

        if (DVEVM_ST_FAIL == dvtb_ceDeInit(&ad->ceHdl))
                SYS_ERROR("Unable to close Engine <%s>\n", engName);
        else
                SYS_OUT("Engine <%s> closed\n", engName);
}


DvevmStRetCode
dvtb_aacheDec1DecProcess(DvevmStAacheDec1Info *ad, int *decDuration)
{
        DvevmStRetCode retCode = DVEVM_ST_SUCCESS;

        do
        {
                if (DVEVM_ST_FAIL == dvtb_aacheDec1Decode(ad, decDuration))
                {
                        SYS_ERROR("Unable to decode <%s> \n", ad->adecName);
                        retCode = DVEVM_ST_FAIL;
                        break;
                }

                ad->adecCmd = XDM_GETSTATUS;
                if (DVEVM_ST_FAIL == dvtb_aacheDec1Control(ad))
                {
                        SYS_ERROR("Unable to get the status \n");
                        retCode = DVEVM_ST_FAIL;
                        break;
                }
        }while(DVEVM_ST_FALSE);

        return retCode;
}

