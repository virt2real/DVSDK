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
 *  @file       ti/sdo/linuxutils/sdma/src/interface/sdma.c
 *
 *  @brief      SDMA Module interface Definitions (ARM) - 
 *              Allows algorithms to request and receive logical SDMA resources
 *              The SDMAK kernel module sdmak.ko must be installed before
 *              using these APIS.  To install sdmak.ko, enter
 *                  % insmod sdmak.ko
 *              on a Linux command line.
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include "sdma.h"

#ifdef __DEBUG
#define __D(fmt, args...) fprintf(stderr, "SDMA Debug: " fmt, ## args)
#else
#define __D(fmt, args...)
#endif

#define __E(fmt, args...) fprintf(stderr, "SDMA Error: " fmt, ## args)

#define OMAP_DMA_L4_BASE                     0x48000000
#define OMAP_DMA_BASE                        (OMAP_DMA_L4_BASE + 0x56000)
#define OMAP_DMA_REG_SIZE           4096
#define OMAP_DMA_REGGROUP_OFFSET    0x60

static int SDMA_dmaops_fd = -1;
static int SDMA_memfd = -1;
static int SDMA_refCount = 0;
static unsigned int SDMA_baseAddr = 0x0;

int SDMA_init() 
{
    int flags;
    int version;

    SDMA_refCount++;

    if (-1 == SDMA_dmaops_fd) {
        SDMA_dmaops_fd = open("/dev/sdma", O_RDONLY);
        if (-1 == SDMA_dmaops_fd) {
            __E("init: Failed to open /dev/sdma: '%s'\n", strerror(errno));

            return -1;
        }
    }    

    if (-1 == SDMA_memfd) {
        SDMA_memfd = open("/dev/mem", O_RDWR | O_SYNC);
        if (-1 == SDMA_memfd) {
            __E("init: Failed to open /dev/mem: '%s'\n", strerror(errno));

            return -1;
        }
    }

    SDMA_baseAddr = (int)mmap(0, OMAP_DMA_REG_SIZE,
                              PROT_READ | PROT_WRITE,
                              MAP_SHARED, SDMA_memfd, (off_t)OMAP_DMA_BASE);

    __D("init: successfully opened /dev/sdma, matching driver version...\n");

    version = SDMA_getVersion();
    if ((version & 0xffff0000) != (SDMA_VERSION & 0xffff0000)) {
        __E("init: major version mismatch between interface and driver.\n");
        __E("    needs driver version %#x, got %#x\n", SDMA_VERSION, version);
        SDMA_exit();

        return -1;
    }
    else if ((version & 0x0000ffff) < (SDMA_VERSION & 0x0000ffff)) {
        __E("init: minor version mismatch between interface and driver.\n");
        __E("    needs driver minor version %#x or greater.\n"
            "    got minor version %#x (full version %#x)\n",
            SDMA_VERSION & 0x0000ffff, version & 0x0000ffff, version);
        SDMA_exit();

        return -1;
    }

    __D("init: ... match good (%#x)\n", version);

    flags = fcntl(SDMA_dmaops_fd, F_GETFD);
    if (flags != -1) {
        fcntl(SDMA_dmaops_fd, F_SETFD, flags | FD_CLOEXEC);
    }
    else {
        __E("init: /dev/edma fcntl(F_GETFD) failed: '%s'\n", strerror(errno));
    }

    flags = fcntl(SDMA_memfd, F_GETFD);
    if (flags != -1) {
        fcntl(SDMA_memfd, F_SETFD, flags | FD_CLOEXEC);
    }
    else {
        __E("init: /dev/mem fcntl(F_GETFD) failed: '%s'\n", strerror(errno));
    }

    return 0;
}

int SDMA_exit() 
{
    SDMA_refCount--;

    if (0 >= SDMA_refCount) {
        if (-1 != SDMA_dmaops_fd) {
            close(SDMA_dmaops_fd);
        }
        SDMA_dmaops_fd = -1;

        if (-1 != SDMA_memfd) {
            close(SDMA_memfd);
        }
        SDMA_memfd = -1;

        //UNMAP SDMA_baseAdddress here
    }    

    return 0;
}

int SDMA_getVersion(void)
{
    unsigned int version;
    int rv;

    __D("getVersion: entered\n");

    rv = ioctl(SDMA_dmaops_fd, SDMA_IOCGETVERSION | SDMA_IOCMAGIC, &version);
    if (rv != 0) {
        __E("getVersion: Failed to retrieve version from driver: %d.\n", rv);

        return -1;
    }

    __D("getVersion: exiting, ioctl SDMA_IOCGETVERSION returned %#x\n",
        version);

    return version;
}

SDMA_Status SDMA_getChannels(int numChannels, 
        SDMA_ChannelDescriptor chanArray[]) 
{
    union SDMA_requestDmaParams param;
    int i, j;

    if (SDMA_dmaops_fd < 0) {
        return (SDMA_ENOINIT);
    }

    for (i = 0; i < numChannels; i++) {
        param.ptransferState = &(chanArray[i].transferState);

        if (ioctl(SDMA_dmaops_fd, SDMA_IOCREQUESTDMA | SDMA_IOCMAGIC, &param) < 0) {
            __E("SDMA_IOCREQUESTDMA error\n");

            for (j = 0; j < i; j++) {
                //Release channels requested so far
                if (ioctl(SDMA_dmaops_fd, SDMA_IOCRELEASEDMA | SDMA_IOCMAGIC,
                    (unsigned long)&chanArray[j].chanNum) < 0) {

                    chanArray[j].chanNum = -1;                    

                    return (SDMA_EFAIL);
                }
            }

            return (SDMA_ENOCHANNEL);
        }

        chanArray[i].chanNum = param.channel;
        chanArray[i].addr = (void *)(SDMA_baseAddr + 0x80 +
                            (chanArray[i].chanNum * OMAP_DMA_REGGROUP_OFFSET)); 
        chanArray[i].transferState.transferCompleted = 1;
        chanArray[i].transferState.checkPending = 0;
    }

    return (SDMA_OK);
}

SDMA_Status SDMA_freeChannels(int numChannels, 
        SDMA_ChannelDescriptor chanArray[])
{
    SDMA_Status status = SDMA_OK;
    int i;

    if (SDMA_dmaops_fd < 0) {
        return (SDMA_ENOINIT);
    }

    for (i = 0; i < numChannels; i++) {
        if (ioctl(SDMA_dmaops_fd, SDMA_IOCRELEASEDMA | SDMA_IOCMAGIC,
            (unsigned long)&chanArray[i].chanNum) < 0) {

            __E("SDMA_IOCRELEASEDMA error\n");
            status = SDMA_EFAIL;

            break;
        }
    }

    return (status);
}

SDMA_Status SDMA_wait(SDMA_ChannelDescriptor *channel)
{
    SDMA_Status rv = SDMA_OK;

    if (SDMA_dmaops_fd < 0) {
        return (SDMA_ENOINIT);
    }

    channel->transferState.checkPending = 1;
    if (channel->transferState.transferCompleted) {
        if (channel->transferState.checkPending == 0) {
            /*
             * Even though we know that the transfer has completed, we
             * didn't check in time to stop the semaphore-post train, so
             * we must pend on the semaphore to clear it.
             */
            if (ioctl(SDMA_dmaops_fd, SDMA_IOCWAITFORCOMPLETION | SDMA_IOCMAGIC,
                (unsigned long)&(channel->chanNum)) < 0) {

                __E("SDMA_IOCWAITFORCOMPLETION error\n");
                rv = SDMA_EFAIL;
            }
        }
        else {
            channel->transferState.checkPending = 0;
        }
    }
    else {
        if (ioctl(SDMA_dmaops_fd, SDMA_IOCWAITFORCOMPLETION | SDMA_IOCMAGIC,
            (unsigned long)&(channel->chanNum)) < 0) {

            __E("SDMA_IOCWAITFORCOMPLETION error\n");
            rv = SDMA_EFAIL;
        }
    }

    return (rv);
}

SDMA_Status SDMA_check(SDMA_ChannelDescriptor *channel, int *pcompleted)
{
    if (SDMA_dmaops_fd < 0) {
        return (SDMA_ENOINIT);
    }

    *pcompleted = channel->transferState.transferCompleted;

    return (SDMA_OK);
}

/*
 *  @(#) ti.sdo.linuxutils.sdma; 1, 0, 0,95; 11-30-2010 18:31:50; /db/atree/library/trees/linuxutils/linuxutils-j02x/src/ xlibrary

 */

