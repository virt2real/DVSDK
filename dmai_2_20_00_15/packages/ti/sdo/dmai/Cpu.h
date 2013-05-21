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

/**
 * @defgroup   ti_sdo_dmai_Cpu      Cpu
 *
 * @brief Describes the local Cpu (on a #Cpu_Device with several Cpu cores).
 *        On Linux, it depends on certain strings from the /proc file system,
 *        so if you change these platform strings, this module may not work
 *        properly. Typical usage (no error checking):
 *
 * @code
 *   #include <xdc/std.h>
 *   #include <ti/sdo/dmai/Cpu.h>
 *   #include <ti/sdo/dmai/Dmai.h>
 *   Cpu_Device device;
 *   Int load;
 *   Cpu_Handle hCpu;
 *   Cpu_Attrs cpuAttrs = Cpu_Attrs_DEFAULT;
 *
 *   Dmai_init();
 *   hCpu = Cpu_create(&cpuAttrs);
 *   Cpu_getDevice(hCpu, &device);
 *
 *   Cpu_getLoad(hCpu, &load);
 *   printf("Device type is %s and cpu is loaded %d%%\n",
 *          Cpu_getDeviceName(device), load);
 *   Cpu_delete(hCpu);
 * @endcode
 */

#ifndef ti_sdo_dmai_Cpu_h_
#define ti_sdo_dmai_Cpu_h_

#include <xdc/std.h>

#include <ti/sdo/dmai/Dmai.h>

/** @ingroup    ti_sdo_dmai_Cpu */
/*@{*/

/**
 * @brief Types of devices which a Cpu may be part of.
 */
typedef enum {
    /** @brief TMS320DM355 */
    Cpu_Device_DM355 = 0,

    /** @brief TMS320DM365 */
    Cpu_Device_DM365,

    /** @brief TMS320DM368 */
    Cpu_Device_DM368,

    /** @brief TMS320DM6446 */
    Cpu_Device_DM6446,

    /** @brief TMS320DM6467 */
    Cpu_Device_DM6467,

    /** @brief TMS320DM6437 */
    Cpu_Device_DM6437,

    /** @brief OMAP3530 */
    Cpu_Device_OMAP3530,

    /** @brief OMAP-L137 */
    Cpu_Device_OMAPL137,

    /** @brief OMAPL138 */
    Cpu_Device_OMAPL138,

    /** @brief DM3730 */
    Cpu_Device_DM3730,

    Cpu_Device_COUNT
} Cpu_Device;

/**
 * @brief Handle through which to reference a Cpu descriptor.
 */
typedef struct Cpu_Object *Cpu_Handle;

/**
 * @brief       Attributes used to create a Cpu.
 * @see         Cpu_Attrs_DEFAULT.
 */
typedef struct Cpu_Attrs {
    /** @brief Currently no attributes for this module, but this may change. */
    Int dummy;
} Cpu_Attrs;

/**
 * @brief       Default attributes for a Cpu.
 */
extern const Cpu_Attrs Cpu_Attrs_DEFAULT;

#if defined (__cplusplus)
extern "C" {
#endif

/**
 * @brief       Creates a Cpu descriptor.
 *
 * @param[in]   attrs       #Cpu_Attrs to use for creating the Cpu descriptor.
 *
 * @retval      Handle for use in subsequent operations (see #Cpu_Handle).
 * @retval      NULL for failure.
 */
extern Cpu_Handle Cpu_create(Cpu_Attrs *attrs);

/**
 * @brief       Get the device type the application is running on.
 *
 * @param[in]   hCpu        The #Cpu_Handle of the Cpu to get the type of.
 *                          If NULL is passed in the type will be determined
 *                          anyway, but it will take longer.
 * @param[out]  device      The #Cpu_Device is returned here.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 */
extern Int Cpu_getDevice(Cpu_Handle hCpu, Cpu_Device *device);

/**
 * @brief       Get the string name of a certain device type.
 *
 * @param[in]   device      The #Cpu_Device to get the string name of.
 *
 * @retval      "Null terminated string" describing the Cpu.
 */
extern Char *Cpu_getDeviceName(Cpu_Device device);

/**
 * @brief       Get the current load from the Cpu.
 *
 * @param[in]   hCpu        The #Cpu_Handle to get the cpu load from.
 * @param[out]  cpuLoad     The cpu load is returned here.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 */
extern Int Cpu_getLoad(Cpu_Handle hCpu, Int *cpuLoad);

/**
 * @brief       Delete the Cpu descriptor.
 *
 * @param[in]   hCpu        The #Cpu_Handle to the descriptor to delete.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 */
extern Int Cpu_delete(Cpu_Handle hCpu);

#if defined (__cplusplus)
}
#endif

/*@}*/

#endif /* ti_sdo_dmai_linux_Cpu_h_ */
