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
 *  @file       edma.h
 *
 *  @brief      Describes the interface to the EDMA manager.
 *
 *  The edma user interface library wraps file system calls to an associated
 *  kernel module (edmak.ko), which needs to be loaded in order for calls to
 *  to this library to succeed.
 *
 *  To install edmak.ko, enter
 *      % insmod edmak.ko
 *  on a Linux command line.
 *
 *  EDMA channels are allocated (requested) from within the edmak kernel
 *  driver through the EDMA_getResource() API.  This request is granted by
 *  way of the kernel's request_dma() functionality (davinci_request_dma() for
 *  the DM365), so it will work in conjuntion with independent kernel DMA
 *  usage without conflict or custom kernel configuration.
 *
 *  EDMA registers can be mapped to a process's address by way of the API
 *  EDMA_mapBaseAddress().  The EDMA registers are memory-mapped into the
 *  calling process' user address space to allow the application to directly
 *  access the EDMA registers.
 *
 *  Resource allocation is tracked at the process level by way of a 'process
 *  registration' list.  The initial allocator of a resource (the process that
 *  calls EDMA_getResource()) is automatically added to the registration list,
 *  and further processes can become registered for the same resource by way
 *  of the EDMA_registerResource() API (and unregister with the
 *  EDMA_unregister() API).  This registration list for each resource (logical
 *  channel) allows for resource ownership tracking and cleanup on a
 *  per-process basis, so that when a process exits or dies without having
 *  explicitly freed/unregistered its resources, they get automatically
 *  unregistered (and freed when no more registered processes exist).  Only
 *  when the last registered process frees a resource (either explictily, or
 *  by auto-cleanup) does a resource actually get freed back to the kernel.
 *
 *  Since the EDMA interface library doesn't use the GT tracing facility,
 *  there is one configuration option available for the EDMA module to control
 *  whether the debug or release interface library is used for building the
 *  application.  This config parameter is named 'debug' and is of type bool,
 *  and the default value is 'false'.
 *
 *  The following line is an example of enabling usage of the debug interface
 *  library:
 *      var edma = xdc.useModule('ti.sdo.linuxutils.edma.EDMA');
 *      edma.debug = true;
 *  This will enable "EDMA Debug" statements to be printed to stdout.
 */
/**
 *  @defgroup   ti_sdo_linuxutils_edma_EDMA  EDMA Manager
 *
 *  This is the API for the EDMA manager.
 */

#ifndef ti_sdo_linuxutils_edma_interface_edma_
#define ti_sdo_linuxutils_edma_interface_edma_

#if defined (__cplusplus)
extern "C" {
#endif

/** @ingroup    ti_sdo_linuxutils_edma_EDMA */
/*@{*/

#define EDMA_VERSION    0x02000000U

/**
 *  @brief    Values for dev_id parameter of EDMA_getResource()
 */
/*
 * To make implementation easier, we're matching the values below to
 * similar values in the kernel header file include/asm/arch/edma.h.
 * However, we're not tied to the LSP #defines since we translate from
 * our #defines below to the LSP #defines in the kernel module edmak.ko.
 * What this means is that we are free to change the ones below, but must
 * be sure to not clash with EDMA channel numbers directly
 * (0 -> (EDMA_NUM_DMACH - 1)).
 */
#define EDMA_TCCANY             1001
#define EDMA_TCCSYMM            1005
#define EDMA_PARAMANY           1006
#define EDMA_PARAMFIXEDEXACT    1007
#define EDMA_PARAMFIXEDNOTEXACT 1008
#define EDMA_EDMAANY            1003
#define EDMA_QDMAANY            1004
#define EDMA_QDMA0              512     /* should be > all arch's # PaRAM */

#define EDMA_QDMA1    EDMA_QDMA(1)
#define EDMA_QDMA2    EDMA_QDMA(2)
#define EDMA_QDMA3    EDMA_QDMA(3)
#define EDMA_QDMA4    EDMA_QDMA(4)
#define EDMA_QDMA5    EDMA_QDMA(5)
#define EDMA_QDMA6    EDMA_QDMA(6)
#define EDMA_QDMA7    EDMA_QDMA(7)

/**
 *  @brief     macro used to translate from a QDMA channel # to the numerical
 *             range used by EDMA_getResource() & EDMA_freeResource() for
 *             representing a QDMA channel.
 *
 *  @sa        EDMA_QDMA2NUM()
 */
#define EDMA_QDMA(n)  (EDMA_QDMA0 + (n))

/**
 *  @brief     macro to translate from EDMA_QDMA0 -> EDMA_QDMA7 namespace to
 *             actual QDMA number 0 -> 7.
 *
 *  @remarks   when requesting a QDMA channel from EDMA_getResource(), the
 *             returned channel # is not directly usable as a QDMA channel #.
 *             This macro translates from the "magic number" range to the
 *             actual QDMA channel # (0 -> 7).
 *
 *  @sa        EDMA_getResource()
 *  @sa        EDMA_freeResource()
 *  @sa        EMDA_QDMA()
 */
#define EDMA_QDMA2NUM(qdma)  (qdma - EDMA_QDMA0)

/**
 *  @brief     EDMAK ioctl() commands.
 */
typedef enum {
    EDMA_IOCREQUESTDMA = 1,
    EDMA_IOCRELEASEDMA,
    EDMA_IOCGETVERSION,
    EDMA_IOCGETBASEPHYSADDR,
    EDMA_IOCREGUSER
} EDMA_commmands;

#define EDMA_IOCMAGIC                   0x0000fd00
#define EDMA_IOCCMDMASK                 0x000000ff

/**
 *  @brief     EDMAK ioctl input/output parameters.
 */
struct EDMA_requestDmaParams {
    int dev_id;                                   /**< requested resource EDMA #|EDMA_EDMAANY|EMDA_QDMA(0 -> 7)|EDMA_QDMAANY|EDMA_PARAMANY, input to EDMA_IOCREQUESTDMA ioctl() */
    int eventq_no;                                /**< event queue number, input to EDMA_IOCREQUESTDMA ioctl() */
    int tcc;                                      /**< requested/granted TCC number, input and/or output to and/or from EDMA_IOCREQUESTDMA ioctl() */
    int param;                                    /**< requested/granted PaRAM number, input and/or output to and/or from EDMA IOCREQUESTDMA ioctl() */
    int nParam;
    int channel;                                  /**< granted channel number, output from EDMA_IOCREQUESTDMA ioctl() */
};

/**
 *  @brief     EDMAK ioctl input parameters.
 */
struct EDMA_releaseDmaParams {
    int channel;
    int nParam;
};

/**
 *  @brief     Status codes for EDMA API return values.
 */
typedef enum EDMA_Status {
    EDMA_OK = 0,        /**< OK */
    EDMA_EFAIL,         /**< general failure */
    EDMA_ENOCHANNEL,    /**< no channels available */
    EDMA_ENOINIT        /**< EDMA_init() not called */
} EDMA_Status;


/**
 *  @brief     EDMA initialization API
 */
int EDMA_init(void);

/**
 *  @brief      EDMA finalization API
 */
int EDMA_exit(void);

/**
 *  @brief     Returns user space virtual address of EDMA base registers.
 *
 *  @param     pvirtAddr    pointer to storage for virtual address.
 */
EDMA_Status EDMA_mapBaseAddress(void **pvirtAddr);

/**
 *  @brief     Returns available logical channels.
 *
 *  @param     devId        EDMA channel # or EDMA_QDMA(0 -> # QDMAs) or
 *             EDMA_EDMAANY or EDMA_QDMAANY or EDMA_PARAMANY.
 *  @param     tcc          pointer to TCC #.  Serves as input or output or
 *             both, depending on the type of resource requested (devId).
 *  @param     channel      pointer to channel #.  Serves as output parameter
 *             only (explicit channel # request has channel # in devId
 *             parameter).
 *  @param     param        pointer to PaRAM #.  Serves as input or output or
 *             both, depending on the type of resource requested (devId).
 *  @param     nParams      number of consecutive PaRAMs to allocate, applies
 *             only when devId is EDMA_PARAMANY.
 *
 *  @remark    Fails if the requested resource(s) is not available.
 *
 *  @remark    The following information shows which function parameters are
 *             valid for all types of allocations:
 *             devId            input parameters      output parameters
 *             -----            ----------------      -----------------
 *             EDMA #           none                  channel, tcc, param*#
 *             EDMA_EDMAANY     tcc                   channel, tcc, param*
 *             EDMA_QDMA#       tcc                   channel, tcc, param
 *             EDMA_QDMAANY     tcc                   channel, tcc, param
 *             EDMA_PARAMANY    nParams               channel, tcc, param*
 *             * channel and param are the same value
 *             # channel and tcc are the same value
 *
 *  @sa        EDMA_freeResource()
 *  @sa        EDMA_registerResource()
 *  @sa        EDMA_unregister()
 *  @sa        EDMA_QDMA()
 *  @sa        EDMA_QDMA2NUM()
 */
EDMA_Status EDMA_getResource(int devId, int *tcc, int *channel, int *param,
                             int nParams);

/**
 *  @brief     Frees previously requested logical channel.
 *
 *  @param     lch   channel number.
 *             EDMA channels range from 0 -> (# channels).
 *             PaRAM channels range from (# channels) -> (# PaRAMs).
 *             QDMA channels range from EDMA_QDMA(0 -> # QDMAs).
 *  @param     nParams   number of consecutive PaRAMs to free, starting at
 *             lch, applies only when lch is a PaRAM identifier.
 *
 *  @sa        EDMA_getResource()
 *  @sa        EDMA_registerResource()
 *  @sa        EDMA_unregister()
 *  @sa        EDMA_QDMA()
 *  @sa        EDMA_QDMA2NUM()
 */
EDMA_Status EDMA_freeResource(int lch, int nParams);

/**
 * @brief Retrieve version from EDMA driver.
 *
 * @return Installed EDMA driver's version number.
 *
 * @pre Must have called EDMA_init()
 */
int EDMA_getVersion(void);

/**
 *  @brief     Registers calling process as a user of lch.
 *
 *  @param     lch        Resource (channel) # returned by EDMA_getResource().
 *
 *  @remark    Fails if the requested resource is not already allocated.
 *
 *  @remark    Each call by the same process adds the process to the
 *             registration list a separate time, so that each call must be
 *             matched by a corresponding EDMA_unregister() call.
 *
 *  @sa        EDMA_unregister()
 *  @sa        EDMA_getResource()
 *  @sa        EDMA_freeResource()
 */
EDMA_Status EDMA_registerResource(int lch);

/**
 *  @brief     Unregisters calling process as a user of lch.
 *
 *  @param     lch        Resource (channel) # returned by EDMA_getResource().
 *  @param     nParams    number of PaRAMs, if lch represents a set of PaRAMS.
 *
 *  @remark    Fails if the calling process is not already registered for lch.
 *
 *  @remark    A process must match each EDMA_registerResource() call with a
 *             call to EDMA_unregister().
 *
 *  @sa        EDMA_freeResource()
 *  @sa        EDMA_getResource()
 *  @sa        EDMA_registerResource()
 */
EDMA_Status EDMA_unregister(int lch, int nParams);

/*@}*/

#if defined (__cplusplus)
}
#endif

#endif
/*
 *  @(#) ti.sdo.linuxutils.edma; 1, 0, 0,92; 11-30-2010 18:31:36; /db/atree/library/trees/linuxutils/linuxutils-j02x/src/ xlibrary

 */

