/*
 * dvtbAppInit.c
 *
 * DVTB(linux) Application Initialization
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

#include "dvtbAppInit.h"
#include "dvtbGlobal.h"
#include "dvtbParam.h"
#include "dvtbSetParam.h"

#define SETP_USAGE  SYS_ERROR("Usage: setp <vpfe|vpbe|audio|sphenc|sphdec|videnc|viddec|imgdec|imgenc> [option] [value]\n")

DvevmStGlobalParams dvevmStGlobalParams;
DvevmStGlobalParams *G = &dvevmStGlobalParams;

DvevmStRetCode
dvtb_initParams()
{
  int index=0;
  ASSERT(G != NULL);

  memset(G, 0, sizeof(DvevmStGlobalParams));
  dvtb_initValues();

  for(index = 0;index < DVEVM_CODEC_NUM; index++)
    dvtb_setpStr(index, NULL);

  /************************************************************************************************/
  /***********     Drivers     ********************************************************************/
  /************************************************************************************************/
   dvtb_vpbeSetupPtr = &dvtb_vpbeSetup;
  /************************************************************************************************/

  /************************************************************************************************/
  /***********     XDM 0.9 Base     ***************************************************************/
  /************************************************************************************************/
  G->vdec.vdecParams.size = sizeof(VIDDEC_Params);
  G->vdec.vdecStatus.size = sizeof(VIDDEC_Status);
  G->vdec.vdecDynParams.size = sizeof(VIDDEC_DynamicParams);
  G->vdec.vdecInArgs.size = sizeof(VIDDEC_InArgs);
  G->vdec.vdecOutArgs.size = sizeof(VIDDEC_OutArgs);

  G->venc.vencParams.size = sizeof(VIDENC_Params);
  G->venc.vencStatus.size = sizeof(VIDENC_Status);
  G->venc.vencDynParams.size = sizeof(VIDENC_DynamicParams);
  G->venc.vencInArgs.size = sizeof(VIDENC_InArgs);
  G->venc.vencOutArgs.size = sizeof(VIDENC_OutArgs);

  G->sdec.sdecParams.size = sizeof(SPHDEC_Params);
  G->sdec.sdecStatus.size = sizeof(SPHDEC_Status);
  G->sdec.sdecDynParams.size = sizeof(SPHDEC_DynamicParams);
  G->sdec.sdecInArgs.size = sizeof(SPHDEC_InArgs);
  G->sdec.sdecOutArgs.size = sizeof(SPHDEC_OutArgs);

  G->senc.sencParams.size = sizeof(SPHENC_Params);
  G->senc.sencStatus.size = sizeof(SPHENC_Status);
  G->senc.sencDynParams.size = sizeof(SPHENC_DynamicParams);
  G->senc.sencInArgs.size = sizeof(SPHENC_InArgs);
  G->senc.sencOutArgs.size = sizeof(SPHENC_OutArgs);

  G->idec.idecParams.size = sizeof(IMGDEC_Params);
  G->idec.idecStatus.size = sizeof(IMGDEC_Status);
  G->idec.idecDynParams.size = sizeof(IMGDEC_DynamicParams);
  G->idec.idecInArgs.size = sizeof(IMGDEC_InArgs);
  G->idec.idecOutArgs.size = sizeof(IMGDEC_OutArgs);

  G->ienc.iencParams.size = sizeof(IMGENC_Params);
  G->ienc.iencStatus.size = sizeof(IMGENC_Status);
  G->ienc.iencDynParams.size = sizeof(IMGENC_DynamicParams);
  G->ienc.iencInArgs.size = sizeof(IMGENC_InArgs);
  G->ienc.iencOutArgs.size = sizeof(IMGENC_OutArgs);

  /************************************************************************************************/

  /************************************************************************************************/
  /***********     XDM 1.0 Base     ***************************************************************/
  /************************************************************************************************/

  /************************************************************************************************/

  /************************************************************************************************/
  /***********     XDM 1.0 Extended     ***********************************************************/
  /************************************************************************************************/

  /************************************************************************************************/

  /************************************************************************************************/
  /***********     XDM 1.2 Base     ***************************************************************/
  /************************************************************************************************/

  /************************************************************************************************/

  return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_initApp(void)
{
        DvevmStRetCode rc = DVEVM_ST_FAIL;

    	dvtb_ceRuntimeInit(&G->eng);
        rc = dvtb_initParams();
        return rc;
}

