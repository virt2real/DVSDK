/*
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
 *
 */

/**
 *  @file       vicp.h
 *
 *  @brief      Describes the interface to the VICP manager.
 *
 *  The VICP user interface library wraps file system calls to an associated
 *  kernel module (irqk.ko), which needs to be loaded in order for calls to
 *  to this library to succeed.
 *
 *  To install irqk.ko, enter
 *      % insmod irqk.ko
 *  on a Linux command line.
 */
/**
 *  @defgroup   ti_sdo_linuxutils_vicp_VICP  VICP Manager
 *
 *  This is the API for the VICP Manager.
 */

#ifndef ti_sdo_linuxutils_vicp_interface_vicp_
#define ti_sdo_linuxutils_vicp_interface_vicp_

#if defined (__cplusplus)
extern "C" {
#endif

/** @ingroup    ti_sdo_linuxutils_vicp_VICP */
/*@{*/

#define VICP_VERSION 0x01000000


/**
 *  @brief     Status codes for VICP API return values.
 */
typedef enum VICP_Status {
    VICP_OK = 0,        /**< OK */
    VICP_EFAIL,         /**< general failure */
    VICP_ENOCHANNEL,    /**< no channels available */
    VICP_ENOINIT        /**< VICP_init() not called */
} VICP_Status;

/**
 *  @brief     Resource types to be used for all APIs.
 */
typedef enum VICP_ResourceType {
    VICP_IMX0,
    VICP_IMX1,
    VICP_MJCP,
    VICP_NSF,
    VICP_HDVICP0,
    VICP_HDVICP1,
} VICP_ResourceType;

#define VICP_NUMRESOURCES 6

/**
 *  @brief     Source of VICP resource interrupt.
 *
 *  @remarks   VICP_FIXED tells the IRQ driver to use the interrupt that's
 *             dedicated for use with the particular VICP_ResourceType.
 *
 *  @remarks   VICP_FLEXIBLE tells the IRQ driver to use the "flexible"
 *             VICP interrupt, which can be driven by all VICP_ResourceType
 *             except VICP_MJCP.
 */
typedef enum VICP_InterruptLine {
    VICP_FIXED,
    VICP_FLEXIBLE
} VICP_InterruptLine;

/**
 *  @brief     Type of ARM interrupt support.
 */
typedef enum VICP_InterruptType {
    VICP_IRQ,
    VICP_FIQ
} VICP_InterruptType;

/**
 *  @brief     VICP initialization API
 */
int VICP_init(void);

/**
 *  @brief      VICP finalization API
 */
int VICP_exit(void);

/**
 *  @brief     Registers resource with requested interrupt type.
 */
VICP_Status VICP_register(VICP_ResourceType resource,
                          VICP_InterruptLine intrLine,
                          VICP_InterruptType intrType);

/**
 *  @brief     Frees previously requested resource.
 */
VICP_Status VICP_unregister(VICP_ResourceType resource);

/**
 *  @brief     Waits for the transfer corresponding to this resource to
 *             complete.
 */
VICP_Status VICP_wait(VICP_ResourceType resource);

/**
 *  @brief     Checks if the transfer corresponding to this resource is
 *             complete.
 */
VICP_Status VICP_done(VICP_ResourceType resource, int *done);

/*@}*/

#if defined (__cplusplus)
}
#endif

#endif
/*
 *  @(#) ti.sdo.linuxutils.vicp; 1, 0, 0,82; 11-30-2010 18:31:57; /db/atree/library/trees/linuxutils/linuxutils-j02x/src/ xlibrary

 */

