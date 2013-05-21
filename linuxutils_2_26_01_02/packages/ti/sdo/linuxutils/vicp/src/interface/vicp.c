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
 *  @file       ti/sdo/linuxutils/vicp/src/interface/vicp.c
 *
 *  @brief      VICP Module interface Definitions (ARM) - 
 *              Allows algorithms to request and receive logical VICP resources
 *              The IRQK kernel module irqk.ko must be installed before
 *              using these APIS.  To install irqk.ko, enter
 *                  % insmod irqk.ko
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

#include <irqk.h>

#include "vicp.h"

#ifdef __DEBUG
#define __D(fmt, args...) fprintf(stderr, "VICP Debug: " fmt, ## args)
#else
#define __D(fmt, args...)
#endif

#define __E(fmt, args...) fprintf(stderr, "VICP Error: " fmt, ## args)


#if 0
#define LPSC_IMCOP      50
#define LPSC_KALEIDO    51

/* offsets from 0x01c40000 */
#define PD_PROTECTION_REG       0x00dc
#define PSC_REG                 0x1000
#define PTCMD_REG               0x1120
#define PTSTAT_REG              0x1128
#define MDCTL_IMCOP             (PSC_REG + 0xa00 + (4 * LPSC_IMCOP))
#define MDCTL_KALEIDO           (PSC_REG + 0xa00 + (4 * LPSC_KALEIDO))
#endif

static int resource_registered[VICP_NUMRESOURCES];

/* set VICP_irqk_fd to -2 to distinguish from failed open (-1) */
static int VICP_refCount = 0;
static int VICP_irqk_fd = -2;

#if 0
static int VICP_mem_fd = -1;

static void *pscRegisterSpace;

static void resource_enable_disable(int mdctl, int enable)
{
    volatile int *PTSTAT = (int *)(((int)pscRegisterSpace) + PTSTAT_REG);
        
    *(int*)(((int)pscRegisterSpace) + PD_PROTECTION_REG) = 0x9;
    if (enable) {
        *(int*)(((int)pscRegisterSpace) + mdctl) = 0x100 | 0x00000003;
    }
    else {
        *(int*)(((int)pscRegisterSpace) + mdctl) = 0x100;
    }
    *(int*)(((int)pscRegisterSpace) + PTCMD_REG) = 0x1; 

    /* check if the transition has happened */
    while(!((*PTSTAT & 0x00000001) == 0)) {
        ;
    }

}
#endif

static int validate_init()
{
    switch (VICP_irqk_fd) {
      case -3:
        __E("VICP_exit() already called, check stderr output for earlier "
            "VICP failure messages (possibly version mismatch).\n");

        return 0;

      case -2:
        __E("VICP_init() not called, you must initialize VICP before "
            "making API calls.\n");

        return 0;

      case -1:
        __E("IRQK file descriptor -1 (failed 'open()'), ensure IRQK "
            "kernel module irqk.ko has been installed with 'insmod'");

        return 0;

      default:
        return 1;
    }
}

int VICP_init() 
{
    int flags;
    int i;

    __D("init: entered - VICP_refCount %d, VICP_irqk_fd %d\n", VICP_refCount, VICP_irqk_fd);

    if (VICP_refCount == 0) {
        VICP_irqk_fd = open("/dev/irqk", O_RDONLY);
        if (-1 == VICP_irqk_fd) {
            __E("init: Failed to open /dev/irqk: '%s'\n", strerror(errno));

            return -1;
        }

        __D("init: successfully opened /dev/irqk\n");

#if 0
        if (-1 == VICP_mem_fd) {
            VICP_mem_fd = open("/dev/mem", O_RDWR | O_SYNC);
            if (-1 == VICP_mem_fd) {
                __E("init: Failed to open /dev/mem: '%s'\n", strerror(errno));

                close(VICP_irqk_fd);

                return -1;
            }
        }

        __D("init: successfully opened /dev/mem\n");

        __D("init: mmap()ing PSC register space @ 0x01c40000...\n");

        pscRegisterSpace = mmap(0, 0x2000, PROT_READ | PROT_WRITE, MAP_SHARED,
                                VICP_mem_fd, 0x01c40000);

        resource_enable_disable(MDCTL_IMCOP, 1);
#endif

        for (i = 0; i < VICP_NUMRESOURCES; i++) {
            resource_registered[i] = 0;
        }
    }

    __D("init: incrementing VICP_refCount...\n");

    VICP_refCount++;

    flags = fcntl(VICP_irqk_fd, F_GETFD);
    if (flags != -1) {
        fcntl(VICP_irqk_fd, F_SETFD, flags | FD_CLOEXEC);
    }
    else {
        __E("init: fcntl(F_GETFD) failed: '%s'\n", strerror(errno));
    }

    __D("init: exiting, returning success\n");

    return 0;
}

int VICP_exit() 
{
    int result = 0;
    int i;

    __D("exit: entered - VICP_refCount %d, VICP_irqk_fd %d\n", VICP_refCount, VICP_irqk_fd);

    __D("exit: decrementing ref_count\n");

    VICP_refCount--;

    if (0 >= VICP_refCount) {
        if (-1 != VICP_irqk_fd) {
            result = close(VICP_irqk_fd);

            __D("exit: VICP_refCount == 0, closed /dev/irqk (%s)\n",
                result == -1 ? strerror(errno) : "succeeded");
        }
        /* setting -3 allows to distinguish IRQ exit from IRQ failed */
        VICP_irqk_fd = -3;

#if 0
        resource_enable_disable(MDCTL_IMCOP, 0);

        if (-1 != VICP_mem_fd) {
            munmap(pscRegisterSpace, 0x2000);
            close(VICP_mem_fd);
        }
        VICP_mem_fd = -1;
#endif

        for (i = 0; i < VICP_NUMRESOURCES; i++) {
            resource_registered[i] = 0;
        }
    }    

    __D("exit: exiting, returning %d\n", result);

    return result;
}

VICP_Status VICP_register(VICP_ResourceType resource,
                          VICP_InterruptLine intrLine,
                          VICP_InterruptType intrType)
{
    int rv;
    IRQK_Request req;

    __D("register: resource %d, intrLine %d, intrType %d\n", resource,
        intrLine, intrType);

    if (!validate_init()) {
        return VICP_ENOINIT;
    }

    if (resource_registered[resource]) {
        __D("register: resource already registered, returning success...\n");

        return VICP_OK;
    }

    __D("register: requesting resource...\n");

    req.resource = resource;
    req.flags = intrLine == VICP_FIXED ? IRQK_FIXEDLINE : IRQK_FLEXIBLELINE;
    req.flags |= intrType == VICP_IRQ ? IRQK_IRQTYPE : IRQK_FIQTYPE;

    if ((rv = ioctl(VICP_irqk_fd, IRQK_IOCREQUESTIRQ | IRQK_IOCMAGIC, &req))
        != 0) {
        __E("VICP_register() ioctl failed: %d\n", rv);

        return VICP_EFAIL;
    }

    resource_registered[resource] = 1;

    __D("register: request succeeded, returning success...\n");

    return VICP_OK;
}

VICP_Status VICP_unregister(VICP_ResourceType resource)
{
    int rv;

    __D("unregister: resource %d\n", resource);

    if (!validate_init()) {
        return VICP_ENOINIT;
    }

    __D("unregister: releasing resource...\n");

    if ((rv = ioctl(VICP_irqk_fd, IRQK_IOCRELEASEIRQ | IRQK_IOCMAGIC,
         &resource)) != 0) {
        __E("VICP_unregister() ioctl failed: %d\n", rv);

        return VICP_EFAIL;
    }

    resource_registered[resource] = 0;

    __D("unregister: release succeeded, returning success...\n");

    return VICP_OK;
}

VICP_Status VICP_wait(VICP_ResourceType resource)
{
    int rv;

    __D("wait: resource %d\n", resource);

    if (!validate_init()) {
        return VICP_ENOINIT;
    }

    __D("wait: waiting on resource...\n");

    if ((rv = ioctl(VICP_irqk_fd, IRQK_IOCWAIT | IRQK_IOCMAGIC, &resource))
        != 0) {
        __E("VICP_wait() ioctl failed: %d\n", rv);

        return VICP_EFAIL;
    }

    __D("wait: returning success\n");

    return VICP_OK;
}

VICP_Status VICP_done(VICP_ResourceType resource, int *done)
{
    int rv;

    __D("done: resource %d\n", resource);

    if (!validate_init()) {
        return VICP_ENOINIT;
    }

    __D("done: checking resource...\n");

    if ((rv = ioctl(VICP_irqk_fd, IRQK_IOCDONE | IRQK_IOCMAGIC, &resource))
        != 0) {
        __E("VICP_done() ioctl failed: %d\n", rv);

        return VICP_EFAIL;
    }

    *done = (int)resource;

    __D("done: returning success, *done %d\n", *done);

    return VICP_OK;
}

/*
 *  @(#) ti.sdo.linuxutils.vicp; 1, 0, 0,82; 11-30-2010 18:31:57; /db/atree/library/trees/linuxutils/linuxutils-j02x/src/ xlibrary

 */

