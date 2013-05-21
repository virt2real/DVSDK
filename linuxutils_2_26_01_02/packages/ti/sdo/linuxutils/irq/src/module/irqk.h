/*
 *  Copyright 2010 by Texas Instruments Incorporated.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; version 2 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>
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

