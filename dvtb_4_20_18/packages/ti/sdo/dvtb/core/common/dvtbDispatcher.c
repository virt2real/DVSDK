/*
 * dvtbDispatcher.c
 *
 * DVTB Dispatcher
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

#include "dvtbDispatcher.h"
#include "dvtbFuncDispatcher.h"
#include "dvtbApisDispatcher.h"
#include "dvtbSetParam.h"
#include "dvtbGetParam.h"
#include "dvtbVersion.h"

typedef enum dvevmStCmd
{
	FUNC = 0,
//	PERF,
	STRS,
	STBL,
	APIS,
	SETP,
	GETP,
	VERSION,
	CTRL,
	MAX_CMDS
} DvevmStCmd;

static DvevmStExecInfo dvevmStCmdInfo[MAX_CMDS] =
{
		{ "func", dvtb_funcExecute },
//		{ "perf", NULL },
		{ "strs", NULL },
		{ "stbl", NULL },
		{ "apis", dvtb_apisExecute },
		{ "setp", dvtb_setpExecute },
		{ "getp", dvtb_getpExecute },
		{ "version", dvtb_printVersion },
		{ "ctrl", NULL },
};

DvevmStRetCode
dvtb_execute(int numTokens, char **tokens)
{
	DvevmStRetCode retval = DVEVM_ST_FAIL;
	int i = 0;

	for (i = 0; i < MAX_CMDS; i++)
	{
		if (0 == strcmp(*tokens, dvevmStCmdInfo[i].key))
		{
			if (NULL == dvevmStCmdInfo[i].dptr)
				retval = DVEVM_ST_NOTSUPPORTED;
			else
				retval = dvevmStCmdInfo[i].dptr(numTokens - 1, ++tokens);
				
      return retval;
		}
	}

	SYS_ERROR("Command <%s> invalid\n", *tokens);
	return retval;
}
