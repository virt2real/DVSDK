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
/*
 *  ======== LogProtocol.h =======
 */
#ifndef LogProtocol_
#define LogProtocol_

#ifdef __cplusplus
extern "C" {
#endif

#include <ti/sdo/ce/ipc/Comm.h>

#define LogProtocol_EOK         0
#define LogProtocol_EFAIL       1
#define LogProtocol_ECMD        2

typedef enum LogProtocol_CmdSet {
    LogProtocol_READLOGS,               /* read log files from DSP */
    LogProtocol_TIMESYNCH               /* timesynch command for DSP */
} LogProtocol_CmdSet;

/*
 * physAddr - DSP-friendly address of the transfer buffer where the DSP
 *            server will copy the LOG to
 * maxSize  - the maximum size of this buffer
 * id       - log id to copy data from, starts with 0, updated by DSP
 *            to contain current log id when log copy cannot fit
 *            in transfer buffer.  id is set to -1 when DSP has completed
 *            copying all LOG buffers.
 * offset   - starts with 0, updated by DSP to contain offset within
 *            current log when log copy cannot fit in transfer buffer.
 *            offset is undefined when id is set to -1 by DSP.
 * size     - number of bytes of valid data in the transfer buffer.
 */
typedef struct LogProtocol_ReadLogs {
    Uint32      physAddr;               /* IN */
    Uint32      maxSize;                /* IN */
    Int32       id;                     /* IN/OUT */
    Uint32      offset;                 /* IN/OUT */
    Uint32      size;                   /* OUT */
} LogProtocol_ReadLogs;

/*
 * todSeconds      - set to time.tv_secs by the client (Arm)
 * todMicroseconds - set to tim.tv_usecs by the client (Arm)
 * clientTimeGT    - GT time on the client (Arm) side.
 * clientSynch     - synch value from 10ms timer1 counter.  This is used to
 *                   synchronize time between DSP and ARM.
 * serverTimeGT    - GT time on the server (DSP) side.
 * offset          - difference between timer1 counter on DSP and ARM.  The
 *                   DSP computes this and accounts for possible wraparound.
 */
typedef struct LogProtocol_TimeSynch {
    Uint32      todSeconds;             /* IN */
    Uint32      todMicroseconds;        /* IN */
    Uint32      clientTimeGT;           /* IN */
    Uint32      clientSynch;            /* IN */
    Uint32      serverTimeGT;           /* OUT */
    Uint32      offset;                 /* OUT */
} LogProtocol_TimeSynch;


/*
 * Command buffer for commands and data to/from the server.
 */
typedef struct LogProtocol_Buf {
    Comm_MsgHeader      header;         /* for use by Comm (MSGQ) */
    Uint32              cmd;            /* command */
    Uint32              status;         /* status of the commmand */
    union {
        LogProtocol_ReadLogs    readLogs;
        LogProtocol_TimeSynch   timeSynch;
    } data;
} LogProtocol_Buf;

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.bioslog; 1, 0, 1,326; 12-2-2010 21:18:56; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

