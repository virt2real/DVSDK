/*
 * dvtbPwrManagerHan.c
 *
 * Power Manager Functionality
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

#include "dvtbPwrManagerHan.h"
#include "dvtbPwrManager.h"
#include "dvtbUtils.h"
#define SCALING_GOVERNOR        "/sys/devices/system/cpu/cpu0/cpufreq/scaling_governor"
#define VDD1_OPP_VALUE          "/sys/power/vdd1_opp_value"
#define VDD2_OPP_VALUE          "/sys/power/vdd2_opp_value"
#define CPU_IDLE_STATE          "/sys/power/cpuidle_deepest_state"

DvevmStRetCode
dvtb_writeSysFsInt(char *fileName, unsigned int *val)
{
	FILE *fp;
	int tmp;
	
	if (DVEVM_ST_FAIL == dvtb_fileOpen(&fp, fileName, "w"))
	{
		SYS_ERROR("Failed to open %s for writing\n", fileName);
		return DVEVM_ST_FAIL;
	}
	if (fprintf(fp, "%d", *val) < 0)
	{
		SYS_ERROR("Failed to write sysfs variable %s to %d\n", fileName, *val);
		fclose(fp);
		return DVEVM_ST_FAIL;
	}
	fclose(fp);

	if (DVEVM_ST_FAIL == dvtb_fileOpen(&fp, fileName, "r"))	
	{
		SYS_ERROR("Failed to open %s for reading\n", fileName);
		return DVEVM_ST_FAIL;
	}
	if (fscanf(fp, "%d", &tmp) < 0)
	{
		SYS_ERROR("Failed to read sysfs value from %s\n", fileName);
		fclose(fp);
		return DVEVM_ST_FAIL;
	}
	fclose(fp);
	if (*val != tmp)
	{
		SYS_ERROR("Failed to verify variable %s to %d (is %d)\n", fileName, *val, tmp);
		*val = tmp;
		return DVEVM_ST_FAIL;
	}
	return DVEVM_ST_SUCCESS;

}

DvevmStRetCode
dvtb_writeSysFsStr(char *fileName, char *val)
{
	FILE *fp;
	char *valString;
	int read;

	//   valString = malloc(strlen(val) + 1);
	valString = malloc(MAX_NAME_LEN + 1);
	if (NULL == valString)
	{
		SYS_ERROR("Failed to allocate memory for temporary string\n");
		return DVEVM_ST_FAIL;
	}

	
	if (DVEVM_ST_FAIL == dvtb_fileOpen(&fp, fileName, "w"))
	{
		SYS_ERROR("Failed to open %s for writing\n", fileName);
		free(valString);
		return DVEVM_ST_FAIL;
	}

	if (1 != fwrite(val, strlen(val) + 1, 1, fp))
	{
		SYS_ERROR("Failed to write sysfs variable %s to %s\n", fileName, val);
		fclose(fp);
		free(valString);
		return DVEVM_ST_FAIL;
	}

	fclose(fp);
	
	if (DVEVM_ST_FAIL == dvtb_fileOpen(&fp, fileName, "r"))
	{
		SYS_ERROR("Failed to open %s for reading\n", fileName);
		free(valString);
		return DVEVM_ST_FAIL;
	}

	//fread(valString, 1, strlen(val) + 1, fp);
	read = fread(valString, 1, MAX_NAME_LEN, fp);
	if (0 != ferror(fp))
	{
		SYS_ERROR("Failed to read sysfs value from %s\n", fileName);
		fclose(fp);
		free(valString);
		return DVEVM_ST_FAIL;
	}
	fclose(fp);
	valString[read - 1] = 0;
	if (0 != strcmp(valString, val))
	{
		SYS_ERROR("Failed to verify sysfs variable %s to %s (is %s)\n", fileName, val, valString);
		strcpy(val, valString);
		free(valString);
		return DVEVM_ST_FAIL;
	}

	free(valString);
	return DVEVM_ST_SUCCESS;
}
void
dvtb_PwrManager(DvevmStThreadInfo *T)
{
	char string[MAX_NAME_LEN];
	int val;
	strcpy(string, T->g.pmanager.scalingGovernor);
	if (DVEVM_ST_FAIL == dvtb_writeSysFsStr(SCALING_GOVERNOR,T->g.pmanager.scalingGovernor))
	{
		SYS_ERROR("Could not set  scaling governor to %s \n", string);
	}
	val = T->g.pmanager.vdd1PState;
	if (DVEVM_ST_FAIL == dvtb_writeSysFsInt(VDD1_OPP_VALUE,&T->g.pmanager.vdd1PState))
	{
		SYS_ERROR("Could not set  VDD1 OPP VALUE to %d \n", val);
	}
	val = T->g.pmanager.vdd2PState;
	if (DVEVM_ST_FAIL == dvtb_writeSysFsInt(VDD2_OPP_VALUE,&T->g.pmanager.vdd2PState))
	{
		SYS_ERROR("Could not set  VDD2 OPP VALUE to %d \n", val);
	}
	val = T->g.pmanager.cpuIdleState;
	if (DVEVM_ST_FAIL == dvtb_writeSysFsInt(CPU_IDLE_STATE,&T->g.pmanager.cpuIdleState))
	{
		SYS_ERROR("Could not set CPU IDLE STATE to %d\n", val);
	}

	SYS_OUT("Scaling Governor %s \n", T->g.pmanager.scalingGovernor);
	SYS_OUT(" VDD1 OPP Value   %d \n", T->g.pmanager.vdd1PState);
	SYS_OUT(" VDD2 OPP Value   %d \n", T->g.pmanager.vdd2PState);
	SYS_OUT(" CPU IDLE STATE   %d \n", T->g.pmanager.cpuIdleState);
	dvtb_freeThr(T);
	dvtb_threadExit( );
}
