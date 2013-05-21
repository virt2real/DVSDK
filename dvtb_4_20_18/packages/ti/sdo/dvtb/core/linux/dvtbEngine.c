/*
 * dvtbEngine.c
 *
 * Implementation of Interface to Codec Engine
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

#include "dvtbEngine.h"
#include <ti/sdo/ce/Engine.h>

#include <stdio.h>

static Engine_Handle myHdl;
void
dvtb_printDspTrace()
{
	Engine_fwriteTrace(myHdl, "[DSP] ", stdout);
	fflush(stdout);
}

DvevmStRetCode
dvtb_ceInit(char *engineName, Engine_Handle *hdl)
{
	Engine_Error err;

	ASSERT(engineName != NULL);
	ASSERT(hdl != NULL);

	*hdl = Engine_open(engineName, NULL, &err);
	myHdl = *hdl;
	if (NULL == *hdl)
	{
		SYS_ERROR("Engine <%s> open failed. Status => %d\n", engineName, err);
		return DVEVM_ST_FAIL;
	}
	else
	{
		SYS_OUT("Engine <%s> opened.\n", engineName);
		SYS_DEBUG("Engine Handle %x\n", (unsigned int) *hdl);
		return DVEVM_ST_SUCCESS;
	}
}

DvevmStRetCode
dvtb_ceOpen(DvevmStEngineInfo *ce)
{
	return dvtb_ceInit(ce->name, &ce->hdl);
}

DvevmStRetCode
dvtb_ceMem(DvevmStEngineInfo *ce)
{
	ASSERT(ce != NULL);
	ASSERT(ce->hdl != NULL);

	ce->mem = Engine_getUsedMem(ce->hdl);
	if (0 == ce->mem)
	{
		ce->err = Engine_getLastError(ce->hdl);
		SYS_ERROR("Unable (%d) to get used memory for Engine <%s>\n", ce->err, ce->name);
		return DVEVM_ST_FAIL;
	}
	else
	{
		SYS_OUT("Engine <%s> => Used Memory : %d MAUs\n", ce->name, ce->mem);
		return DVEVM_ST_SUCCESS;
	}
}

DvevmStRetCode
dvtb_ceCpu(DvevmStEngineInfo *ce)
{
	ASSERT(ce != NULL);
	ASSERT(ce->hdl != NULL);

	ce->cpu = Engine_getCpuLoad(ce->hdl);
	if (ce->cpu < 0)
	{
		ce->err = Engine_getLastError(ce->hdl);
		SYS_ERROR("Unable (%d) to get CPU load for Engine <%s>\n", ce->err, ce->name);
		return DVEVM_ST_FAIL;
	}
	else
	{
		SYS_OUT("Engine <%s> => CPU Load : %d MAUs\n", ce->name, ce->cpu);
		return DVEVM_ST_SUCCESS;
	}

}

DvevmStRetCode
dvtb_ceRuntimeInit(DvevmStEngineInfo *ce)
{
	CERuntime_init( );
	SYS_DEBUG("Codec Engine Runtime initialized\n");
	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_ceClose(DvevmStEngineInfo *ce)
{
	ASSERT(ce != NULL);
	ASSERT(ce->hdl != NULL);

	Engine_close(ce->hdl);
	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_ceDeInit(Engine_Handle *hdl)
{
	if (hdl == NULL)
	{
		SYS_ERROR("Invalid Engine Handle\n");
		return DVEVM_ST_FAIL;
	}

	Engine_close((*hdl));
	hdl = NULL;
	return DVEVM_ST_SUCCESS;
}

