/*
 * dvtbALSAControlContent.c
 *
 * ALSA driver specific functions to set flags
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

#include "dvtbALSAControlContent.h"
#include <errno.h>
#include <ctype.h>

DvevmStRetCode
dvtb_audioSetControl(DvevmStAudioInfo *aud , char *element, char *elementValue)
{
	DvevmStRetCode retCode=DVEVM_ST_SUCCESS;

	int retVal=-1;
	char *elementValPtr=NULL;
	char soundcard[64]="default";
	unsigned int i=0, count=0;
	long valToSet=0;
	int cond1=0, cond2=0, cond3=0, cond4=0, cond5=0;

	static snd_ctl_t *handle=NULL;
	snd_ctl_elem_info_t *info=NULL;
	snd_ctl_elem_id_t *id=NULL;
	snd_ctl_elem_value_t *control=NULL;
	snd_ctl_elem_type_t type;

	snd_ctl_elem_info_alloca(&info);
	snd_ctl_elem_id_alloca(&id);
	snd_ctl_elem_value_alloca(&control);

	do
	{
		if(NULL == element)
		{
			SYS_ERROR("Audio Set Control failed: Control Element is NULL \n");
			retCode = DVEVM_ST_FAIL;
			break;
		}
	
		snd_ctl_elem_id_set_interface(id, SND_CTL_ELEM_IFACE_MIXER);

		snd_ctl_elem_id_set_name(id, element);
		
		retVal = snd_ctl_open(&handle, soundcard, 0);
		if(0 > retVal)
		{
			SYS_ERROR("Audio Set Control failed: Sound Control open error: %s\n", snd_strerror(retVal));
			retCode = DVEVM_ST_FAIL;
			break;
		}

		snd_ctl_elem_info_set_id(info, id);

		retVal = snd_ctl_elem_info(handle, info);

		if(0 > retVal)
		{
			SYS_ERROR("Audio Set Control failed: Cannot find the given element\n");
			snd_ctl_close(handle);
			handle = NULL;
			retCode = DVEVM_ST_FAIL;
			break;
		}

		snd_ctl_elem_info_get_id(info, id);

		type = snd_ctl_elem_info_get_type(info);
		count = snd_ctl_elem_info_get_count(info);
		snd_ctl_elem_value_set_id(control, id);

		elementValPtr = (char *)elementValue;
		for(i=0; ((i<count) && (i<128) && (elementValPtr) && (*elementValPtr)); i++)
		{
			if(SND_CTL_ELEM_TYPE_BOOLEAN == type)
			{
				valToSet = 0;
				cond1 = strncasecmp(elementValPtr, "on", 2);
				cond2 = strncasecmp(elementValPtr, "up", 2);
				cond3 = strncasecmp(elementValPtr, "yes", 3);
				cond4 = strncasecmp(elementValPtr, "toggle", 6);
				cond5 = isdigit(*elementValPtr);
				if((0 == cond1) || (0 == cond2))
				{
					valToSet = 1;
					elementValPtr += 2;
				}
				else if(0 == cond3)
				{
					valToSet = 1;
					elementValPtr += 3;
				}
				else if(0 == cond4)
				{
					valToSet = snd_ctl_elem_value_get_boolean(control, i);
					valToSet = valToSet > 0 ? 0 : 1;
					elementValPtr += 6;
				}
				else if(cond5)
				{
					valToSet = atoi(elementValPtr) > 0 ? 1 : 0;
					while (isdigit(*elementValPtr))
						elementValPtr++;
				}
				else
				{
					while (*elementValPtr && *elementValPtr != ',')
						elementValPtr++;
				}

				snd_ctl_elem_value_set_boolean(control, i, valToSet);
			}
			else if((SND_CTL_ELEM_TYPE_INTEGER == type) || (SND_CTL_ELEM_TYPE_INTEGER64 == type) || (SND_CTL_ELEM_TYPE_ENUMERATED == type) || (SND_CTL_ELEM_TYPE_BYTES == type))
			{
				SYS_ERROR("Selected type not implemented");
				retCode = DVEVM_ST_FAIL;
			}
			else
			{
				//do nothing
			}

			if(DVEVM_ST_FAIL == retCode)
				break;

			if (!strchr(elementValue, ','))
				elementValPtr = (char *)elementValue;
			else if (*elementValPtr == ',')
				++elementValPtr;
		}

		if(DVEVM_ST_FAIL == retCode)
			break;

		retVal = snd_ctl_elem_write(handle, control);
		if(0 > retVal)
		{
			snd_ctl_close(handle);
			handle = NULL;
			retCode = DVEVM_ST_FAIL;
			break;
		}
		
		snd_ctl_close(handle);
		handle = NULL;		
	}while(DVEVM_ST_FALSE);

	return retCode;
}

DvevmStRetCode
dvtb_audioSetControlContents(DvevmStAudioInfo *aud)
{
	char elementValue = '1';

	if (SND_PCM_STREAM_CAPTURE == aud->mode)
	{
		if(DVEVM_ST_FAIL == dvtb_audioSetControl(aud,"Analog Left AUXL Capture Switch",&elementValue))
		{
			SYS_ERROR("Unable to set \"Analog Left AUXL Capture Switch\" \n");
			return DVEVM_ST_FAIL;
		}
		if(DVEVM_ST_FAIL == dvtb_audioSetControl(aud,"Analog Right AUXR Capture Switch",&elementValue))
		{
			SYS_ERROR("Unable to set \"Analog Right AUXR Capture Switch\" \n");
			return DVEVM_ST_FAIL;
		}
	}

	return 	DVEVM_ST_SUCCESS;
}
