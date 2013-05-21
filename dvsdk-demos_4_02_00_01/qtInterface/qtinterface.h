/*
 * qtinterface.h
 *
 * This module handles the global definitions and declarations for 
 * the QT interface.
 *
 * Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/ 
 * 
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef _QTINTERFACE_H
#define _QTINTERFACE_H

/* Named pipes for commands and status */
#define CMD_FIFO_FILE          "/tmp/DVSDK_DEMOS_CMD"
#define CONFIG_FIFO_FILE       "/tmp/DVSDK_DEMOS_CONFIG"
#define KB_CMD_FIFO_FILE       "/tmp/DVSDK_DEMOS_KB_CMD"
#define STATUS_FIFO_FILE       "/tmp/DVSDK_DEMOS_STATUS"

/* Maximum number of info items that can be displayed at once */
#define QTINTERFACE_MAXITEMS 12

/* Maximum string size for each info item */
#define QTINTERFACE_MAXSTRINGSIZE 256

/* Maximum number of configuration items supported (EOF counts as one) */
#define QTINTERFACE_MAXCONFIGITEMS 10

typedef enum QtInterface_Command {
    QtInterface_Play,
    QtInterface_Pause,
    QtInterface_Stop,
    QtInterface_Inc,
    QtInterface_Dec,
    QtInterface_Hide,
} QtInterface_Command;

#endif
