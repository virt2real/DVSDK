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
 *  @file       ti/sdo/linuxutils/edma/src/interface/edma.c
 *
 *  @brief      EDMA Module interface Definitions (ARM) - 
 *              Allows algorithms to request and receive logical EDMA resources
 *              The EDMAK kernel module edmak.ko must be installed before
 *              using these APIS.  To install edmak.ko, enter
 *                  % insmod edmak.ko
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
#include "edma.h"

#ifdef __DEBUG
#define __D(fmt, args...) fprintf(stderr, "EDMA Debug: " fmt, ## args)
#else
#define __D(fmt, args...)
#endif

#define __E(fmt, args...) fprintf(stderr, "EDMA Error: " fmt, ## args)

#define EDMA_CCREGSIZE 0x8000
#define NUMPAENTRY(addr) (((((addr)>>12)&0x7)==0)?0:(0x10<<(((addr)>>12)&0x7)))
#define CCCFG 1


static int EDMA_dmaops_fd = -1;
static int EDMA_memfd = -1;
static int EDMA_refCount = 0;
static unsigned int EDMA_basePhysAddr = 0x0;

int EDMA_init() 
{
    int flags;
    int version;

    if (EDMA_refCount == 0) {
        if (-1 == EDMA_dmaops_fd) {
            EDMA_dmaops_fd = open("/dev/edma", O_RDONLY);
            if (-1 == EDMA_dmaops_fd) {
                __E("init: Failed to open /dev/edma: '%s'\n", strerror(errno));

                return -1;
            }
        }    

        if (-1 == EDMA_memfd) {
            EDMA_memfd = open("/dev/mem", O_RDWR | O_SYNC);
            if (-1 == EDMA_memfd) {
                __E("init: Failed to open /dev/mem: '%s'\n", strerror(errno));

                close(EDMA_dmaops_fd);

                return -1;
            }
        }
    }

    EDMA_refCount++;

    __D("init: successfully opened /dev/edma, matching driver version...\n");

    version = EDMA_getVersion();
    if ((version & 0xffff0000) != (EDMA_VERSION & 0xffff0000)) {
        __E("init: major version mismatch between interface and driver.\n");
        __E("    needs driver version %#x, got %#x\n", EDMA_VERSION, version);
        EDMA_exit();

        return -1;
    }
    else if ((version & 0x0000ffff) < (EDMA_VERSION & 0x0000ffff)) {
        __E("init: minor version mismatch between interface and driver.\n");
        __E("    needs driver minor version %#x or greater.\n"
            "    got minor version %#x (full version %#x)\n",
            EDMA_VERSION & 0x0000ffff, version & 0x0000ffff, version);
        EDMA_exit();

        return -1;
    }

    __D("init: ... match good (%#x)\n", version);

    flags = fcntl(EDMA_dmaops_fd, F_GETFD);
    if (flags != -1) {
        fcntl(EDMA_dmaops_fd, F_SETFD, flags | FD_CLOEXEC);
    }
    else {
        __E("init: /dev/edma fcntl(F_GETFD) failed: '%s'\n", strerror(errno));
    }

    flags = fcntl(EDMA_memfd, F_GETFD);
    if (flags != -1) {
        fcntl(EDMA_memfd, F_SETFD, flags | FD_CLOEXEC);
    }
    else {
        __E("init: /dev/mem fcntl(F_GETFD) failed: '%s'\n", strerror(errno));
    }

    return 0;
}

int EDMA_exit() 
{
    EDMA_refCount--;

    if (0 >= EDMA_refCount) {
        __D("exit: reference count 0\n");

        if (-1 != EDMA_dmaops_fd) {
            __D("exit: closing /dev/edma\n");

            close(EDMA_dmaops_fd);
        }
        EDMA_dmaops_fd = -1;

        if (-1 != EDMA_memfd) {
            __D("exit: closing /dev/mem\n");

            close(EDMA_memfd);
        }
        EDMA_memfd = -1;

        //UNMAP EDMA_baseAdddress here
    }    

    return 0;
}

EDMA_Status EDMA_mapBaseAddress(void **pvirtAddr)
{
    int status;
    int *edmaRegs;
    int numPaRAM;
    int numBytes;

    __D("mapBaseAddress: entered\n");

    if (EDMA_dmaops_fd < 0) {
        __D("mapBaseAddress: /dev/edma not opened\n");

        return (EDMA_ENOINIT);
    }

    if (EDMA_basePhysAddr == 0) {
        __D("mapBaseAddress: retrieving base address from EDMA driver ...\n");

        if ((status = ioctl(EDMA_dmaops_fd,
                            EDMA_IOCGETBASEPHYSADDR | EDMA_IOCMAGIC,
                            &EDMA_basePhysAddr)) != 0) {

            __D("mapbaseAddress: ... failed (%d), returning -1\n", status);

            return -1;
        }

        __D("mapbaseAddress: ... got it (%#x)\n", EDMA_basePhysAddr);
    }
    else {
        __D("mapBaseAddress: using stored base address (%#x)\n", EDMA_basePhysAddr);
    }

    /* just map enough space to access CCCFG register */
    edmaRegs = mmap(0, 8, PROT_READ | PROT_WRITE,
                    MAP_SHARED, EDMA_memfd, (off_t)EDMA_basePhysAddr);

    numPaRAM = NUMPAENTRY(edmaRegs[CCCFG]);

    /* toss the mapping */
    munmap(edmaRegs, 8);

    numBytes = 0x4000 + (numPaRAM * 8 * 4);

    __D("mapping 0x%x bytes to user virtual address ...\n", numBytes);

    *pvirtAddr = mmap(0, numBytes, PROT_READ | PROT_WRITE,
                      MAP_SHARED, EDMA_memfd, (off_t)EDMA_basePhysAddr);

    __D("mapbaseAddress: ... got it (%p)\n", *pvirtAddr);

    return EDMA_OK;
}

int EDMA_getVersion(void)
{
    unsigned int version;
    int rv;

    __D("getVersion: entered\n");

    if (EDMA_dmaops_fd < 0) {
        __D("getVersion: /dev/edma not opened\n");

        return (EDMA_ENOINIT);
    }

    rv = ioctl(EDMA_dmaops_fd, EDMA_IOCGETVERSION | EDMA_IOCMAGIC, &version);
    if (rv != 0) {
        __E("getVersion: Failed to retrieve version from driver: %d.\n", rv);

        return -1;
    }

    __D("getVersion: exiting, ioctl EDMA_IOCGETVERSION returned %#x\n",
        version);

    return version;
}

EDMA_Status EDMA_getResource(int dev_id, int *tcc, int *channel, int *param,
                             int nParams)
{
    struct EDMA_requestDmaParams request;

    __D("getResource: entered - dev_id=%d, *tcc=%d, *param=%d, nParams=%d\n",
        dev_id, *tcc, *param, nParams);

    if (EDMA_dmaops_fd < 0) {
        __D("getResource: /dev/edma not opened\n");

        return (EDMA_ENOINIT);
    }

    request.dev_id = dev_id;
    request.tcc = *tcc;
    request.param = *param;
    request.eventq_no = 0;
    request.nParam = nParams;

    if (ioctl(EDMA_dmaops_fd, EDMA_IOCREQUESTDMA | EDMA_IOCMAGIC,
              &request) < 0) {
        __E("EDMA_IOCREQUESTDMA error\n");

        return (EDMA_ENOCHANNEL);
    }

    *channel = request.channel;
    *tcc = request.tcc;
    *param = request.param;

    __D("getResource: exiting, ioctl EDMA_IOCREQUESTDMA returned channel %d"
        ", tcc %d, param %d\n", *channel, *tcc, *param);

    return (EDMA_OK);
}

EDMA_Status EDMA_registerResource(int lch)
{
    EDMA_Status status = EDMA_OK;
    int ioctl_status;

    __D("registerResource: entered - lch=%d\n", lch);

    if (EDMA_dmaops_fd < 0) {
        __D("registerResource: /dev/edma not opened\n");

        return (EDMA_ENOINIT);
    }

    if ((ioctl_status = ioctl(EDMA_dmaops_fd, EDMA_IOCREGUSER | EDMA_IOCMAGIC,
                              (unsigned long)&lch)) < 0) {

        __E("EDMA_IOCREGUSER error\n");

        status = EDMA_EFAIL;
    }

    __D("registerResource: exiting, ioctl EDMA_IOCREGUSER returned %d\n",
        ioctl_status);

    return (status);
}

EDMA_Status EDMA_freeResource(int lch, int nParams)
{
    EDMA_Status status = EDMA_OK;
    struct EDMA_releaseDmaParams request;
    int ioctl_status;

    __D("freeResource: entered - lch=%d, nParams=%d\n", lch, nParams);

    if (EDMA_dmaops_fd < 0) {
        __D("freeResource: /dev/edma not opened\n");

        return (EDMA_ENOINIT);
    }

    request.channel = lch;
    request.nParam = nParams;

    if ((ioctl_status = ioctl(EDMA_dmaops_fd,
                              EDMA_IOCRELEASEDMA | EDMA_IOCMAGIC,
                              (unsigned long)&request)) < 0) {

        __E("EDMA_IOCRELEASEDMA error\n");

        status = EDMA_EFAIL;
    }

    __D("freeResource: exiting, ioctl EDMA_IOCRELEASEDMA returned %d\n",
        ioctl_status);

    return (status);
}

EDMA_Status EDMA_unregister(int lch, int nParams)
{
    __D("unregister: delegating to EDMA_freeResource()...\n");

    return EDMA_freeResource(lch, nParams);
}

/*
 *  @(#) ti.sdo.linuxutils.edma; 1, 0, 0,92; 11-30-2010 18:31:36; /db/atree/library/trees/linuxutils/linuxutils-j02x/src/ xlibrary

 */

