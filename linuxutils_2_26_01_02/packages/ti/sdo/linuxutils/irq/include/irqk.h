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
 */

#ifndef _IRQK_H
#define _IRQK_H

#if defined (__cplusplus)
extern "C" {
#endif

#define IRQK_VERSION    0x01000001U

/* macros for use wih IRQ_Request.resource */
#define IRQK_NONE               -1
#define IRQK_IMX0               0
#define IRQK_IMX1               1
#define IRQK_MJCP               2
#define IRQK_NSF                3
#define IRQK_HDVICP0            4
#define IRQK_HDVICP1            5

#define IRQK_NUMRESOURCES 6

/* macros for use wih IRQ_Request.flags */
#define IRQK_FIXEDLINE          0x00000000
#define IRQK_FLEXIBLELINE       0x00000001
#define IRQK_INTRLINEMASK       0x00000001

#define IRQK_NUMLINES 2

#define IRQK_IRQTYPE            0x00000000
#define IRQK_FIQTYPE            0x00000002
#define IRQK_INTRTYPEMASK       0x00000002

typedef struct IRQK_Request {
    int resource;
    int flags;
} IRQK_Request;

#define IRQK_IOCMAGIC   0x0000fc00

/* supported ioctl cmds for the driver. */
#define IRQK_IOCREQUESTIRQ      0
#define IRQK_IOCRELEASEIRQ      1
#define IRQK_IOCWAIT            2
#define IRQK_IOCDONE            3

#define IRQK_IOCCMDMASK                 0x000000ff

#if defined (__cplusplus)
}
#endif

#endif // _IRQK_H

/*
 *  @(#) ti.sdo.linuxutils.irq; 1, 0, 0,82; 11-30-2010 18:31:43; /db/atree/library/trees/linuxutils/linuxutils-j02x/src/ xlibrary

 */

