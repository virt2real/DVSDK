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
 *  @file       sdma.h
 *
 *  @brief      Describes the interface to the SDMA manager.
 *
 *  The sdma user interface library wraps file system calls to an associated
 *  kernel module (sdmak.ko), which needs to be loaded in order for calls to
 *  to this library to succeed.
 *
 *  To install sdmak.ko, enter
 *      % insmod sdmak.ko
 *  on a Linux command line.
 *
 *  SDMA channels are allocated (requested) from within the sdmak kernel
 *  driver through the SDMA_getChannels() API.  This request is granted by
 *  way of the kernel's request_dma() functionality (omap_request_dma() for
 *  the OMAP35x), so it will work in conjuntion with independent kernel DMA
 *  usage without conflict or custom kernel configuration.  The granted
 *  channel's registers are memory-mapped into the calling user address
 *  space to allow the application to directly access the DMA registers for
 *  that channel.
 *
 *  A DMA callback ISR is registered within the stock kernel DMA manager, and
 *  this ISR is used for completion notification (although it could be
 *  customized to handle any DMA-generated interrupt).  Notification to the
 *  user interface layer is accomplished by way of a user state structure
 *  whose address is passed to the sdmak kernel driver and which is directly
 *  written upon completion.  Atomic hand-shaking allows the kernel driver to
 *  know if the application is going to wait for the completion by way of the
 *  corresponding sdmak ioctl(), as opposed to just checking the user state
 *  structure, and post a channel-specific mutex only when needed (otherwise
 *  just the completion flag in the state structure is set).
 *
 *  Since the SDMA interface library doesn't use the GT tracing facility,
 *  there is one configuration option available for the SDMA module to control
 *  whether the debug or release interface library is used for building the
 *  application.  This config parameter is named 'debug' and is of type bool,
 *  and the default value is 'false'.
 *
 *  The following line is an example of enabling usage of the debug interface
 *  library:
 *      var sdma = xdc.useModule('ti.sdo.linuxutils.sdma.SDMA');
 *      sdma.debug = true;
 *  This will enable "SDMA Debug" statements to be printed to stdout.
 */
/**
 *  @defgroup   ti_sdo_linuxutils_sdma_SDMA  SDMA Manager
 *
 *  This is the API for the SDMA Manager.
 */

#ifndef ti_sdo_linuxutils_sdma_interface_sdma_
#define ti_sdo_linuxutils_sdma_interface_sdma_

#if defined (__cplusplus)
extern "C" {
#endif

/** @ingroup    ti_sdo_linuxutils_sdma_SDMA */
/*@{*/

#define SDMA_VERSION    0x01010000U

/**
 *  @brief     SDMAK ioctl() commands.
 */
#define SDMA_IOCMAGIC                   0x0000fb00
#define SDMA_IOCCMDMASK                 0x000000ff

#define SDMA_IOCREQUESTDMA              1
#define SDMA_IOCRELEASEDMA              2
#define SDMA_IOCWAITFORCOMPLETION       3
#define SDMA_IOCGETVERSION              4

/**
 *  @brief     State structure shared between SDMAK and SDMA user layers.
 *
 *  @remarks   The address of a struct SDMA_transferState instance gets
 *             passed down to the SDMAK module during the @c SDMA_IOCREQUESTDMA
 *             ioctl() operation and is registered with the received channel.
 *             It is therefore vital that the structure address that is
 *             registered with the kernel module points to the actual location
 *             that is queried and written during a "wait" operation.
 */
struct SDMA_transferState {
    volatile int transferCompleted;    /**< flag for channel completion */
    volatile int checkPending;         /**< completion check hand-shaking flag */
};

/**
 *  @brief     SDMAK ioctl input/output parameters.
 */
union SDMA_requestDmaParams {
    struct SDMA_transferState *ptransferState;    /**< user address of user-owned transfer state structure, input for REQEST_DMA ioctl() */
    int channel;                                  /**< granted channel number, output from SDMA_IOCREQUESTDMA ioctl() */
};

/**
 *  @brief     Descriptor for a channel granted with a SDMA_IOCREQUESTDMA ioctl().
 *
 *  @remarks   The address of the transferState member is passed down to the
 *             SDMAK module during the @c SDMA_IOCREQUESTDMA ioctl().  The
 *             SDMAK module maps this address and queries and writes to it
 *             during the completion ISR activity.  It is therefore vital that
 *             the address of the descriptor passed to @c SDMA_getChannels() is
 *             in persistent memory that is live for the duration of SDMA
 *             channel usage.
 *
 *  @sa        SDMA_getChannels()
 *  @sa        SDMA_freeChannels()
 *  @sa        SDMA_wait()
 *  @sa        SDMA_check()
 */
typedef struct SDMA_ChannelDescriptor {
    int chanNum;            /**< channel number */
    unsigned int * addr;    /**< user virtual address of granted DMA registers */
    struct SDMA_transferState transferState;    /**< used for completion checking, whose address is passed down to sdmak kernel driver */
} SDMA_ChannelDescriptor;

/**
 *  @brief     Status codes for SDMA API return values.
 */
typedef enum SDMA_Status {
    SDMA_OK = 0,        /**< OK */
    SDMA_EFAIL,         /**< general failure */
    SDMA_ENOCHANNEL,    /**< no channels available */
    SDMA_ENOINIT        /**< SDMA_init() not called */
} SDMA_Status;


/**
 *  @brief     SDMA initialization API
 */
int SDMA_init(void);

/**
 *  @brief      SDMA finalization API
 */
int SDMA_exit(void);

/**
 *  @brief     Returns available logical channels.
 *
 *  @param     numChannels  number of requested channels.
 *  @param     chanArray    pointer to SDMA_ChannelDescriptor storage of
 *             sufficient size to hold numChannels descriptors.  All
 *             structure array fields are filled by this API (in other words,
 *             no fields need to be filled by the caller prior to the call).
 *
 *  @remark    chanArray must be allocated from memory that persists over
 *             the life of the channel's usage, since the address of the
 *             chanArray will be used by the SDMA kernel driver.  This
 *             implies that the contents of the passed chanArray should
 *             not be copied to another SDMA_ChannelDescriptor that is then
 *             used for the subsequent operations.
 *
 *  @remark    Fails if the requested number of channels is not available.
 *
 *  @sa        SDMA_freeChannels()
 */
SDMA_Status SDMA_getChannels(int numChannels,
        SDMA_ChannelDescriptor chanArray[]);

/**
 *  @brief     Frees previously requested logical channels.
 *
 *  @param     numChannels  number of requested channels.
 *  @param     chanArray    pointer to SDMA_ChannelDescriptor storage of
 *             sufficient size to hold numChannels descriptors.  This will
 *             typically be the same pointer passed to SDMA_getChannels().
 *
 *  @sa        SDMA_getChannels()
 */
SDMA_Status SDMA_freeChannels(int numChannels,
        SDMA_ChannelDescriptor chanArray[]);

/**
 *  @brief     Waits for the transfer corresponding to this descriptor to
 *             complete.
 *
 *  @param     channel  pointer to the single channel for which to wait.
 *
 *  @remarks   SDMA_wait() first checks the transferComplete flag of the
 *             struct SDMA_transferState in channel.  This flag is directly
 *             written by the SDMAK module's completion ISR.  If this flag
 *             is not set to 1, SDMA_wait() will issue a
 *             @c SDMA_IOCWAITFORCOMPLETION
 *             ioctl(), which will block inside the SDMAK module and become
 *             unblocked by the completion ISR.
 *
 *  @sa        SDMA_check()
 */
SDMA_Status SDMA_wait(SDMA_ChannelDescriptor * channel);

/**
 *  @brief     Checks the status of the transfer corresponding to this
 *             descriptor and returns it in the *pcompleted field.
 *
 *  @param     channel     pointer to single channel to check.
 *  @param     pcompleted  pointer to completion status.
 *
 *  @remarks   copies the contents of the transferComplete flag of the
 *             struct SDMA_transferState in channel into *pcompleted (does
 *             not issue any ioctl()).
 *
 *  @sa        SDMA_wait()
 */
SDMA_Status SDMA_check(SDMA_ChannelDescriptor * channel, int *pcompleted);

/**
 * @brief Retrieve version from SDMA driver.
 *
 * @return Installed SDMA driver's version number.
 *
 * @pre Must have called SDMA_init()
 */
int SDMA_getVersion(void);

/*@}*/

#if defined (__cplusplus)
}
#endif

#endif
/*
 *  @(#) ti.sdo.linuxutils.sdma; 1, 0, 0,95; 11-30-2010 18:31:50; /db/atree/library/trees/linuxutils/linuxutils-j02x/src/ xlibrary

 */

