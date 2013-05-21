/*
 * dvtbGetParam.c
 *
 * Implemenation for getting the parameters of DVTB Classes
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

#include "dvtbGlobal.h"
#include "dvtbGetParam.h"
#include "dvtbParam.h"

DvevmStRetCode
dvtb_getParam(unsigned int index, void *valp)
{
	int *val = (int *) valp;
	char *str = (char *) valp;
	ASSERT(index < DVEVM_CODEC_NUM);

	SYS_DEBUG("Getting params[%d]: ", index);
	SYS_OUT("Getting params[%d]: ", index);
	switch (MAP[index].fieldType)
	{
		case DVEVM_ST_INT:
			*val = (int) (MAP[index].value);
			break;

		case DVEVM_ST_STR:
			str = (char *) MAP[index].value;
			break;

		case DVEVM_ST_CHAR:
			*val = (char) ((int) MAP[index].value);
			break;

		case DVEVM_ST_SHORT:
			*val = (short) ((int) MAP[index].value);
			break;

		default:
			GETP_USAGE;
			return DVEVM_ST_FAIL;
	}
	return DVEVM_ST_SUCCESS;
}

DvevmStRetCode
dvtb_displayParam(unsigned int index)
{
	ASSERT(index < DVEVM_CODEC_NUM);

	switch (MAP[index].fieldType)
	{
		case DVEVM_ST_INT:
			SYS_PRINTF("\t %-24s\t =>  %d\n", MAP[index].fieldName, *(int *) MAP[index].value);
			break;
		case DVEVM_ST_STR:
			SYS_PRINTF("\t %-24s\t =>  %s\n", MAP[index].fieldName, (char *) MAP[index].value);
			break;
		case DVEVM_ST_CHAR:
			SYS_PRINTF("\t %-24s\t =>  %d\n", MAP[index].fieldName, (XDAS_Int8)*(char *) MAP[index].value);
			break;
		case DVEVM_ST_SHORT:
			SYS_PRINTF("\t %-24s\t =>  %d\n", MAP[index].fieldName, *(short *) MAP[index].value);
			break;
		default:
			SYS_PRINTF("\t %-24s\t => <undefined>\n", MAP[index].fieldName);
	}

	return DVEVM_ST_SUCCESS;
}

/*option = display value for a given parameter */
DvevmStRetCode
dvtb_getpExecute(int numTokens, char **tokens)
{
	int index = 0;
	DvevmStRetCode rc = DVEVM_ST_FAIL;
	DvevmStBool paramFound = DVEVM_ST_FALSE;

	if (0 == numTokens)
	{
		GETP_USAGE;
		return DVEVM_ST_FAIL;
	}

	for (index = 0; index < DVEVM_CODEC_NUM; index++)
	{
		if (0 == strcmp(MAP[index].className, tokens[0]))
		{
			if (NULL == tokens[1])
			{
				dvtb_displayParam(index);
				paramFound = DVEVM_ST_TRUE;
			}
			else if (0 == strcmp(MAP[index].fieldName, tokens[1]))
			{
				dvtb_displayParam(index);
				paramFound = DVEVM_ST_TRUE;
				break;
			}
		}
	}

	rc = (DVEVM_ST_TRUE == paramFound) ? DVEVM_ST_SUCCESS : DVEVM_ST_FAIL;
	return rc;
}
