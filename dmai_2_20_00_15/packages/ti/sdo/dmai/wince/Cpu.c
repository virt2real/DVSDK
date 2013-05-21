/* --COPYRIGHT--,BSD
 * Copyright (c) 2010, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/

#include <windows.h>

#include <xdc/std.h>
#include <ti/sdo/ce/osal/Global.h>
#include <ti/sdo/dmai/Cpu.h>
#include <ti/sdo/dmai/Dmai.h>

#define MODULE_NAME     "Cpu"

typedef struct Cpu_Object {
    Cpu_Device  device;
} Cpu_Object;

static Char *deviceName[Cpu_Device_COUNT] = {
    "DM355",
    "DM365",
    "DM6446",
    "DM6467",
    "DM6437",
    "OMAP3530",
    "OMAPL137",
    "OMAPL138",
    "DM3730"
};

const Cpu_Attrs Cpu_Attrs_DEFAULT = {
    0
};

/******************************************************************************
 * getType
 ******************************************************************************/
static Int getDevice(Cpu_Device *device)
{
#ifdef Dmai_Device_dm6446
    *device = Cpu_Device_DM6446;
    return Dmai_EOK;        
#else
#ifdef Dmai_Device_dm6437
    *device = Cpu_Device_DM6437;
    return Dmai_EOK;        
#else
#ifdef Dmai_Device_dm6467
    *device = Cpu_Device_DM6467;
    return Dmai_EOK;        
#else
#ifdef Dmai_Device_dm355
    *device = Cpu_Device_DM355;
    return Dmai_EOK;    
#else
#ifdef Dmai_Device_omap3530
    *device = Cpu_Device_OMAP3530;
    return Dmai_EOK;    
#else
#ifdef Dmai_Device_dm3730
    *device = Cpu_Device_DM3730;
    return Dmai_EOK;    
#else
    Dmai_err0("Unknown Cpu Type!\n");
    return Dmai_EFAIL;
#endif
#endif
#endif
#endif
#endif
#endif
}

/******************************************************************************
 * Cpu_getDevice
 ******************************************************************************/
Int Cpu_getDevice(Cpu_Handle hCpu, Cpu_Device *device)
{
    if (hCpu) {
        *device = hCpu->device;
    }
    else {
        if (getDevice(device) < 0) {
            Dmai_err0("Failed to get device type\n");
            return Dmai_EFAIL;
        }
    }

    return Dmai_EOK;
}

/******************************************************************************
 * Cpu_getDeviceName
 ******************************************************************************/
Char *Cpu_getDeviceName(Cpu_Device device)
{
    return deviceName[device];
}

/******************************************************************************
 * Cpu_getLoad
 ******************************************************************************/
Int Cpu_getLoad(Cpu_Handle hCpu, Int *cpuLoad)
{
    static DWORD startTick = 0;
    static DWORD endTick = 0;
    static DWORD idleStart = 0;
    static DWORD idleEnd = 0;
    DWORD load;
    
    startTick = endTick;
    endTick = GetTickCount();
    idleStart = idleEnd;
    idleEnd = GetIdleTime();
    
    load = 100 - ((100 * (idleEnd - idleStart)) / (endTick - startTick)); 
    
    *cpuLoad = load;

    return Dmai_EOK;
}

/******************************************************************************
 * Cpu_create
 ******************************************************************************/
Cpu_Handle Cpu_create(Cpu_Attrs *attrs)
{
    Cpu_Handle hCpu;
    
    hCpu = calloc(1, sizeof(Cpu_Object));

    if (hCpu == NULL) {
        Dmai_err0("Failed to allocate space for Cpu Object\n");
        return NULL;
    }

    /* Determine type of device */
    if (getDevice(&hCpu->device) < 0) {
        Dmai_err0("Failed to get device type\n");
        free(hCpu);
        return NULL;
    }

    return hCpu;
}

/******************************************************************************
 * Cpu_delete
 ******************************************************************************/
Int Cpu_delete(Cpu_Handle hCpu)
{
    if (hCpu) {
        free(hCpu);
    }

    return Dmai_EOK;
}
