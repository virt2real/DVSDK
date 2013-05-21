/* --COPYRIGHT--,BSD
 * Copyright (c) $(CPYYEAR), Texas Instruments Incorporated
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

#ifndef ti_sdo_dmai__Event_h_
#define ti_sdo_dmai__Event_h_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <linux/input.h>

#include <xdc/std.h>
#include <ti/sdo/dmai/Ir.h>

#include <xdc/std.h>

#define MODULE_NAME     "Ir"

#define IR_INPUT_DEVICE   "/dev/input/event0"

/* Minimum time between two identical events reported to application.*/
#define IR_EVENT_REPEAT_RATE 250000

typedef struct Ir_Object {
    int              fd;
    UInt16           prev_val;
    struct timeval   prev_time;
} Ir_Object;

const Ir_Attrs Ir_Attrs_DEFAULT = {
    0
};

/*
 * Mapping for IR input event key codes
 */

static inline Ir_Key _Event_key_map(Int code) 
{
    switch (code) 
    {
        case KEY_POWER:
            return Ir_Key_POWER;
        case KEY_CHANNELUP:
            return Ir_Key_CHANINC;
        case KEY_CHANNELDOWN:
            return Ir_Key_CHANDEC;
        case KEY_VOLUMEUP:
            return Ir_Key_VOLINC;
        case KEY_VOLUMEDOWN:
            return Ir_Key_VOLDEC;
        case KEY_UP:
            return Ir_Key_UP;
        case KEY_DOWN:
            return Ir_Key_DOWN;
        case KEY_LEFT:
            return Ir_Key_LEFT;
        case KEY_RIGHT:
            return Ir_Key_RIGHT;
        case KEY_OK:
            return Ir_Key_OK;
        case KEY_MUTE:
            return Ir_Key_MUTE;
        case KEY_MENU:
            return Ir_Key_MENUDONE;
        case KEY_SELECT:
            return Ir_Key_INFOSELECT;
        case KEY_SLEEP:
            return Ir_Key_SLEEP;
        case KEY_SUBTITLE:
            return Ir_Key_SUBTITLE;
        case KEY_PREVIOUS:
            return Ir_Key_REPEAT;
        case KEY_NUMERIC_1:
            return Ir_Key_1;
        case KEY_NUMERIC_2:
            return Ir_Key_2;
        case KEY_NUMERIC_3:
            return Ir_Key_3;
        case KEY_NUMERIC_4:
            return Ir_Key_4;
        case KEY_NUMERIC_5:
            return Ir_Key_5;
        case KEY_NUMERIC_6:
            return Ir_Key_6;
        case KEY_NUMERIC_7:
            return Ir_Key_7;
        case KEY_NUMERIC_8:
            return Ir_Key_8;
        case KEY_NUMERIC_9:
            return Ir_Key_9;
        case KEY_NUMERIC_0:
            return Ir_Key_0;
        case KEY_ENTER:
            return Ir_Key_ENTER;
        case KEY_MODE:
            return Ir_Key_INPUT;
        case KEY_REWIND:
            return Ir_Key_REWIND;
        case KEY_PLAY:
            return Ir_Key_PLAY;
        case KEY_FASTFORWARD:
            return Ir_Key_FASTFORWARD;
        case KEY_RECORD:   
            return Ir_Key_RECORD;
        case KEY_STOP:
            return Ir_Key_STOP;
        case KEY_PAUSE:
            return Ir_Key_PAUSE;
        default:
            Dmai_err1("Unknown key pressed (%d)\n", code);
            return code;
    }
    return 0;
}

static inline Ir_Handle _Event_Ir_create(Ir_Attrs *attrs)
{
    Ir_Handle hIr;
    
    hIr = calloc(1, sizeof(Ir_Object));

    if (hIr == NULL) {
        Dmai_err0("Failed to allocate space for Ir Object\n");
        return NULL;
    }

    hIr->fd = open(IR_INPUT_DEVICE, O_RDWR | O_NONBLOCK);

    if (hIr->fd < 0) {
        Dmai_err0("Error while opening input event device\n");
        return NULL;
    }

    return hIr;    
}

static inline Int _Event_Ir_getKey(Ir_Handle hIr, Ir_Key *key)
{
    Int ret = Dmai_EOK;
    struct input_event ev[4];
    Int                rd;
    UInt32             time;
    time_t             s;
    suseconds_t        us;

    assert(hIr);
    assert(key);

    *key = 0;
    
    rd = read(hIr->fd, ev, sizeof(struct input_event) * 4);
    if (rd < (int) sizeof(struct input_event)) {
        if (errno != EAGAIN) {
            Dmai_err1("Error reading input event (%s)\n", strerror(errno));
            return Dmai_EIO;
        }
    } else {

        s    = ev[0].time.tv_sec  - hIr->prev_time.tv_sec;
        us   = ev[0].time.tv_usec - hIr->prev_time.tv_usec;
        time = s * 1000000l + us;

        if ((ev[0].code != hIr->prev_val)  
            || (time > IR_EVENT_REPEAT_RATE)){

            *key = _Event_key_map(ev[0].code);

            hIr->prev_val  = ev[0].code;
            hIr->prev_time = ev[0].time;
        }
    }

    return ret;    
}

static inline Int _Event_Ir_delete(Ir_Object *hIr)
{
    if (hIr) {
        if (close(hIr->fd) == -1) {
            Dmai_err0("Failed to close input event device\n");
            return Dmai_EIO;
        }
    }

    return Dmai_EOK;
}

#endif /* ti_sdo_dmai__Event_h_ */
