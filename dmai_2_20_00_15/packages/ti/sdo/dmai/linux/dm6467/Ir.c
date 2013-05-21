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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>

#ifdef CONFIG_CIR
#include <linux/cir.h>
#endif

#include <xdc/std.h>

#include <ti/sdo/dmai/Ir.h>
#include <ti/sdo/dmai/Dmai.h>

#define MODULE_NAME     "Ir"

#define CIR_DEVICE "/dev/cir"

typedef struct Ir_Object {
    int      fd;
    int      gotkey;
    UInt16   prev;
} Ir_Object;

const Ir_Attrs Ir_Attrs_DEFAULT = {
    0
};

/******************************************************************************
 * Ir_create
 ******************************************************************************/
Ir_Handle Ir_create(Ir_Attrs *attrs)
{
#ifdef CONFIG_CIR
    Ir_Handle hIr;

    hIr = calloc(1, sizeof(Ir_Object));

    if (hIr == NULL) {
        Dmai_err0("Failed to allocate space for Ir Object\n");
        return NULL;
    }

    hIr->fd = open (CIR_DEVICE, O_RDONLY | O_NONBLOCK, 0);

    if (hIr->fd < 0) {
        Dmai_err1("Unable to open the CIR device %s\n", CIR_DEVICE);
        free(hIr);
        return NULL;
    }

    return hIr;
#else
    Dmai_err0("not implemented\n");
    return NULL;
#endif
}

#ifdef CONFIG_CIR
/******************************************************************************
 * validateKey
 ******************************************************************************/
static Int validateKey(Int val)
{
    if (val != Ir_Key_POWER         && val != Ir_Key_CHANINC &&
        val != Ir_Key_CHANDEC       && val != Ir_Key_VOLINC &&
        val != Ir_Key_VOLDEC        && val != Ir_Key_OK &&
        val != Ir_Key_MUTE          && val != Ir_Key_MENUDONE &&
        val != Ir_Key_INFOSELECT    && val != Ir_Key_SLEEP &&
        val != Ir_Key_SUBTITLE      && val != Ir_Key_REPEAT &&
        val != Ir_Key_1             && val != Ir_Key_2 &&
        val != Ir_Key_3             && val != Ir_Key_4 &&
        val != Ir_Key_5             && val != Ir_Key_6 &&
        val != Ir_Key_7             && val != Ir_Key_8 &&
        val != Ir_Key_9             && val != Ir_Key_0 &&
        val != Ir_Key_ENTER         && val != Ir_Key_INPUT &&
        val != Ir_Key_REWIND        && val != Ir_Key_PLAY &&
        val != Ir_Key_FASTFORWARD   && val != Ir_Key_RECORD &&
        val != Ir_Key_UP            && val != Ir_Key_DOWN &&
        val != Ir_Key_LEFT          && val != Ir_Key_RIGHT &&
        val != Ir_Key_STOP          && val != Ir_Key_PAUSE) {

        Dmai_dbg1("Ir key %d not valid\n", val);
        return 0;
    }

    return 1;
}
#endif

/******************************************************************************
 * Ir_getKey
 ******************************************************************************/
Int Ir_getKey(Ir_Handle hIr, Ir_Key *key)
{
#ifdef CONFIG_CIR
    UInt16 buf;
    Int val;

    *key = 0;

    if (read(hIr->fd, &buf, sizeof(UInt16)) < 0) {
        if (errno != EAGAIN) {
            Dmai_err0("Unable to read from the CIR device\n");
            return Dmai_EFAIL;
        }
    }
    else {
        if (buf != hIr->prev) {
            val = 0x3000 | ( buf & 0x07FF );

            if (validateKey(val)) {
                *key = val;
            }

            hIr->prev = buf;
        }

        ioctl(hIr->fd, CIR_FLUSH);
    }

    return Dmai_EOK;
#else
    Dmai_err0("not implemented\n");
    return NULL;
#endif
}

/******************************************************************************
 * Ir_delete
 ******************************************************************************/
Int Ir_delete(Ir_Handle hIr)
{
#ifdef CONFIG_CIR
    if (hIr) {
        if (hIr->fd != -1) {
            close(hIr->fd);
        }

        free(hIr);
    }

    return Dmai_EOK;
#else
    Dmai_err0("not implemented\n");
    return NULL;
#endif
}
