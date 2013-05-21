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
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>

#include <xdc/std.h>
#include <ti/sdo/dmai/Ir.h>
#include <ti/sdo/dmai/Dmai.h>

#include <ti/sdo/dmai/linux/priv/i2c-dev.h>

#define IR_I2C_DEVICE "/dev/i2c/0"
#define IR_I2C_DEV_ADDR 0x23

#define MODULE_NAME     "Ir"

typedef struct Ir_Object {
    int      fd;
    int      oldval;
} Ir_Object;

const Ir_Attrs Ir_Attrs_DEFAULT = {
    0
};

#if 0
/******************************************************************************
 * getIrVal
 ******************************************************************************/
static int getIrVal(Ir_Handle hIr, int *val)
{
    char buf[4];

    buf[0] = 2;
    buf[1] = 3;

    if (write(hIr->fd, buf, 2) != 2) {
        Dmai_err1("Failed to write get IR value command to i2c device (%s)\n",
                  strerror(errno));

        return Dmai_EIO;
    }

    usleep(100);

    if (read(hIr->fd, buf, 4) != 4) {
        Dmai_err0("Failed to read RTC data\n");
        return Dmai_EIO;
    }

    *val = buf[2] | (buf[3] << 8);

    return Dmai_EOK;
}
#endif

/******************************************************************************
 * Ir_create
 ******************************************************************************/
Ir_Handle Ir_create(Ir_Attrs *attrs)
{
#if 0
    Ir_Handle hIr;

    hIr = calloc(1, sizeof(Ir_Object));

    if (hIr == NULL) {
        Dmai_err0("Failed to allocate space for Ir Object\n");
        return NULL;
    }

    hIr->fd = open(IR_I2C_DEVICE, O_RDWR);

    if (hIr->fd < 0) {
        Dmai_err0("Error while opening i2c device\n");
        return NULL;
    }

    if (ioctl(hIr->fd, I2C_SLAVE, IR_I2C_DEV_ADDR) == -1) {
        Dmai_err1("Failed to set I2C_SLAVE to %#x\n", IR_I2C_DEV_ADDR);
        return NULL;
    }

    if (getIrVal(hIr, &hIr->oldval) < 0) {
        return NULL;
    }

    return hIr;
#endif
    return (Ir_Handle) 1;
}

/******************************************************************************
 * Ir_getKey
 ******************************************************************************/
Int Ir_getKey(Ir_Handle hIr, Ir_Key *key)
{
#if 0
    Int val;
    Int ret = Dmai_EOK;

    assert(hIr);
    assert(key);

    ret = getIrVal(hIr, &val);

    if (ret >= 0) {
        if (val != hIr->oldval) {
            *key = val & ~(1<<11);
            hIr->oldval = val;
        }
        else {
            *key = 0;
        }
    }

    usleep(100);

    return ret;
#endif
    *key = 0;
    return Dmai_EOK;
}

/******************************************************************************
 * Ir_delete
 ******************************************************************************/
Int Ir_delete(Ir_Object *hIr)
{
#if 0
    if (close(hIr->fd) == -1) {
        Dmai_err0("Failed to close i2c device\n");
        return Dmai_EIO;
    }
#endif
    return Dmai_EOK;
}
