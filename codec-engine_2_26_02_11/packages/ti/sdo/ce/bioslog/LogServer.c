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
 *  ======== LogServer.c ========
 */
#include <xdc/std.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>

#include <ti/bios/include/std.h>
#include <ti/bios/include/bcache.h>
#include <ti/bios/include/log.h>
#include <ti/bios/include/sys.h>

#include <ti/sdo/utils/trace/gt.h>
#include <ti/sdo/ce/ipc/Comm.h>
#include <ti/sdo/ce/osal/Thread.h>

#include "LogServer.h"
#include "LogProtocol.h"
#include "LogTracker.h"

#include "Timer.h"

#ifndef xdc_target__isaCompatible_64P
extern void _disable_interrupts();
extern void _enable_interrupts();
#endif

#define SERVERQUEUENAME         "ti_sdo_ce_bioslog_LogServer"

/* Assumes 64x 8-word timestamp LOG! */
#define LOGELEMSIZE             (8 * sizeof(Uint32))

typedef struct Header {
    Int32       id;
    Uint32      size;
} Header;

#define GTNAME "LS"
static GT_Mask curTrace;

static Comm_Queue       serverMsgQueue = Comm_INVALIDMSGQ;

static Uint32 exec(LogProtocol_Buf *buf);
static Void server(Void);

static Uint32 readLogs(LogProtocol_Buf *buf);
static Uint32 timeSynch(LogProtocol_Buf *buf);

static Int              logNum;
static LOG_Obj          *logTab;

extern LOG_Obj          ti_sdo_ce_bioslog_create;
extern LOG_Obj          ti_sdo_ce_bioslog_synch;

extern Int              LogServer_stackSize;
/*
 *  ======== LogServer_init ========
 */
Void LogServer_init(Void)
{
    static Bool curInit = FALSE;
    Thread_Attrs        attrs;
    extern far Int  LOG_A_TABBEG;
    extern far Int  LOG_A_TABLEN;

    if (!curInit) {
        curInit = TRUE;

        GT_create(&curTrace, GTNAME);

        logNum = (Int)&LOG_A_TABLEN;
        logTab = (LOG_Obj *)&LOG_A_TABBEG;

        attrs = Thread_ATTRS;
        attrs.name      = "LogServer";
        attrs.priority  = Thread_MINPRI;
        attrs.stacksize = LogServer_stackSize;

        Thread_create((Fxn)server, &attrs);
    }
}

/*
 *  ======== exec ========
 */
static Uint32 exec(LogProtocol_Buf *buf)
{
    GT_1trace(curTrace, GT_ENTER, "exec(cmd = %d)\n", buf->cmd);

    switch (buf->cmd) {
        case LogProtocol_READLOGS:
            return (readLogs(buf));

        case LogProtocol_TIMESYNCH:
            return (timeSynch(buf));

        default:
            return (LogProtocol_ECMD);
    }
}

/*
 *  ======== readLogs ========
 */
static Uint32 readLogs(LogProtocol_Buf *buf)
{
    Int         i;
    Int32       id;
    Uint32      offset, logsize;
    Char        *src, *dst, *srcEnd, *dstEnd;
    Header      *header;

    static      Int createLogId = -1, synchLogId = -1;

    GT_0trace(curTrace, GT_ENTER, "readLogs()\n");

    id = buf->data.readLogs.id;
    offset = buf->data.readLogs.offset;

    dst = (Char *)buf->data.readLogs.physAddr;
    dstEnd = (Char *)buf->data.readLogs.physAddr + buf->data.readLogs.maxSize;

    /* first time find the indices for the two special logs, synch and create */
    if (createLogId == -1) {
        for (i = id; i < logNum; i++) {
            if (&logTab[i] == &ti_sdo_ce_bioslog_create) {
                createLogId = i;
            }
            else if (&logTab[i] == &ti_sdo_ce_bioslog_synch) {
                synchLogId = i;
            }
        }
    }


    for (; id < logNum; id++) {
        src = (Char *)logTab[id].bufbeg + offset;
        srcEnd = (Char *)logTab[id].bufbeg + logTab[id].lenmask + 1;

        header = (Header *)dst;

        if (dst + sizeof(Header) >= dstEnd) {
            /*
             * No room for this LOG!  Tell client where to resume ...
             */
            buf->data.readLogs.id = id;
            buf->data.readLogs.offset = offset;

            goto done;
        }

        dst = dst + sizeof(Header);

        logsize = 0;
        while ((src < srcEnd) && ((dst + LOGELEMSIZE) < dstEnd)) {
            /*
             * Skip empty records.
             *
             * Do not disable interrupts.  If an entry shows up in the
             * meantime, we'll get it next time.
             */
            if (*(Uint32 *)src == 0xffffffff) {
                src += LOGELEMSIZE;
                offset += LOGELEMSIZE;
                continue;
            }

            _disable_interrupts();

            if ((id != createLogId) && (id != synchLogId)) {
                for (i=0; i < LOGELEMSIZE; i++) {
                    *dst++ = *src;
                    *src++ = 0xff;          /* mark buffer empty */
                }
            } else {
                for (i=0; i < LOGELEMSIZE; i++) {
                    *dst++ = *src;
                    src++;
                }
            }

            _enable_interrupts();

            offset += LOGELEMSIZE;
            logsize += LOGELEMSIZE;
        }

        header->id = id;
        header->size = logsize;

        if (dst + LOGELEMSIZE >= dstEnd) {
            /*
             *  tell client where to resume
             */
            buf->data.readLogs.id = id;
            buf->data.readLogs.offset = offset;

            goto done;
        }

        GT_3trace(curTrace, GT_2CLASS,
            "readLogs: id = %d, curSize = %d, maxSize = %d\n",
            id, dst - (Char *)buf->data.readLogs.physAddr,
            buf->data.readLogs.maxSize);

        offset = 0;             /* get ready for next LOG */
    }

    buf->data.readLogs.id = -1;         /* we're done! */

done:

    buf->data.readLogs.size = dst - (Char *)buf->data.readLogs.physAddr;

    /*
     * force data out of CACHE into shared memory
     * BCACHE will round size up to cache alignment.
     */
    BCACHE_wb((void *)buf->data.readLogs.physAddr,
        buf->data.readLogs.size, TRUE);

    GT_3trace(curTrace, GT_2CLASS,
        "readLogs: returns id = %d, offset = %d, curSize = %d, maxSize = %d\n",
        buf->data.readLogs.id, buf->data.readLogs.size,
        buf->data.readLogs.maxSize);

    return (LogProtocol_EOK);
}

/*
 *  ======== timeSynch ========
 */
static Uint32 timeSynch(LogProtocol_Buf *buf)
{
#ifdef xdc_target__isaCompatible_64P
    Uint32      t0, t1, period;

    GT_0trace(curTrace, GT_ENTER, "timeSynch()\n");

    buf->data.timeSynch.serverTimeGT = GT_curTime();

    t0 = buf->data.timeSynch.clientSynch;       // timer1 count from Arm
    t1 = Timer_phys1->tim34;                    // timer1 count on DSP

    if (t1 < t0) {
        /* counter wrapped!  compute offset based on period */
        period = Timer_phys1->prd34;

        buf->data.timeSynch.offset = (period - t0) + t1;
    }
    else {
        buf->data.timeSynch.offset = t1 - t0;
    }

    LOG_event5(&ti_sdo_ce_bioslog_synch,
        buf->data.timeSynch.todSeconds,
        buf->data.timeSynch.todMicroseconds,
        buf->data.timeSynch.clientTimeGT,
        buf->data.timeSynch.serverTimeGT,
        buf->data.timeSynch.offset
    );

    GT_3trace(curTrace, GT_2CLASS, "timeSynch: t0 = %d, t1 = %d, offset = %d\n",
        t0, t1, buf->data.timeSynch.offset);
#endif

    return (LogProtocol_EOK);
}

/*
 *  ======== server ========
 *  The server thread
 */
static Void server(Void)
{
    LogProtocol_Buf     *buf;
    Int                 commStatus;
    Comm_Handle         serverMsgHandle = NULL;
    Comm_Queue          sendersMsgQueue;

    GT_0trace(curTrace, GT_ENTER, "server()\n");

    serverMsgHandle = Comm_create(SERVERQUEUENAME, &serverMsgQueue, NULL);
    if (serverMsgHandle == NULL) {
        SYS_abort("LogServer: Comm_create %s failed!\n", SERVERQUEUENAME);
    }

    GT_1trace(curTrace, GT_2CLASS, "server: serverMsgQueue = 0x%08x\n",
        serverMsgQueue);

    for (;;) {
        GT_0trace(curTrace, GT_2CLASS, "server: waiting for cmd\n");

        commStatus = Comm_get(serverMsgQueue, (Comm_Msg *)&buf, Comm_FOREVER);
        if (commStatus != Comm_EOK) {
            SYS_abort("LogServer: Comm_get failed!\n");
        }

        GT_1trace(curTrace, GT_2CLASS, "server: buf->cmd = %d\n",
                buf->cmd);

        buf->status = exec(buf);

        /* find out where to send the reply ... */
        commStatus = Comm_getSrcQueue((Comm_Msg)buf, &sendersMsgQueue);

        /* ... and send it */
        Comm_put(sendersMsgQueue, (Comm_Msg)buf);
    }
}
/*
 *  @(#) ti.sdo.ce.bioslog; 1, 0, 1,326; 12-2-2010 21:18:56; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

