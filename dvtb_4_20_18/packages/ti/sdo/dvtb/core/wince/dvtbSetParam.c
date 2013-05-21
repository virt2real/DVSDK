/*
 * dvtbSetParam.c
 *
 * Implementation for setting the parameters of the DVTB Classes
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

#include "dvtbSetParam.h"
#include "dvtbGlobal.h"
#include "dvtbParam.h"

DvevmStRetCode
dvtb_setParam(unsigned int index, void *val)
{
	DVTBASSERT(index < DVEVM_CODEC_NUM);
	switch (MAP[index].fieldType)
	{
		case DVEVM_ST_INT:
			*(int *) MAP[index].value = (int) val;
			break;

		case DVEVM_ST_SHORT:
			*(short *) MAP[index].value = (short) ((int) val);
			break;

		case DVEVM_ST_STR:
			strcpy(MAP[index].value, (char *) val);
			break;

		case DVEVM_ST_CHAR:
			*(char *) MAP[index].value = (char) ((int) val);
			break;

		default:
			SYS_ERROR("Invalid parameter <%s> => <%s>\n", MAP[index].className, MAP[index].fieldName);
	}

	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_setpStr(unsigned int index, char *val)
{
	void *valParam;

	DVTBASSERT(index < DVEVM_CODEC_NUM);

	if (NULL == val)
		valParam = MAP[index].defaultValue;
	else
	{
		if (DVEVM_ST_INT == MAP[index].fieldType)
			valParam = (int *) atoi(val);
		else if (DVEVM_ST_SHORT == MAP[index].fieldType)
			valParam = (int *) atoi(val);
		else if (DVEVM_ST_CHAR == MAP[index].fieldType)
			valParam = (int *) atoi(val);
		else
			valParam = (char *) val;
	}

	dvtb_setParam(index, valParam);

	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_setpExecute(int numTokens, char **tokens)
{
	int index = 0;
	DvevmStBool paramFound = DVEVM_ST_FALSE;
	DvevmStRetCode rc = DVEVM_ST_FAIL;

	if ((numTokens < 1) || (numTokens > 3))
	{
		//    SETP_USAGE;
		SYS_OUT("Invalid setp command\n");
	}
	else
	{
		for (index = 0; index < (int)DVEVM_CODEC_NUM; index++)
		{
			if (0 == strcmp(MAP[index].className, tokens[0]))
			{
				if (NULL == tokens[1])
				{
					rc = dvtb_setpStr(index, NULL);
					paramFound = DVEVM_ST_TRUE;
				} else if (0 == strcmp(MAP[index].fieldName, tokens[1]))
				{
					if (NULL == tokens[2])
						rc = dvtb_setpStr(index, NULL);
					else
						rc = dvtb_setpStr(index, tokens[2]);

					paramFound = DVEVM_ST_TRUE;
					break;
				}
			}
		}
	}

	rc = (DVEVM_ST_TRUE == paramFound) ? DVEVM_ST_SUCCESS : DVEVM_ST_FAIL;
	return rc;
}
