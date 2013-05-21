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
 *  ======== LogClient.c =======
 */
#include <xdc/std.h>

#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>

#ifdef xdc_target__os_Linux
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/time.h>
#endif

#include <ti/sdo/utils/trace/gt.h>

#include <ti/sdo/ce/ipc/Comm.h>
#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/ce/osal/Thread.h>
#include <ti/sdo/ce/osal/Global.h>

#include "LogClient.h"
#include "LogProtocol.h"

#include "Timer.h"

#define GTNAME "LC"

#define CLIENTQUEUENAME "ti_sdo_ce_bioslog_LogClient"
#define SERVERQUEUENAME "ti_sdo_ce_bioslog_LogServer"

/* REMINDER: if you add an initialized static var, reinitialize it at cleanup */
static Bool curInit = FALSE;

static GT_Mask curTrace;

static Comm_Queue       clientMsgQueue = Comm_INVALIDMSGQ;
static Comm_Handle      clientMsgHandle = NULL;
static Comm_Queue       serverMsgQueue = Comm_INVALIDMSGQ;

static LogProtocol_Buf  *buf = NULL;

static char             *userAddr = NULL;       /* user address */
static Uint32           physAddr = 0;           /* DSP-friendly address */

static int              connectedOK = 0;        /* connected or not */

#ifdef xdc_target__os_Linux
static int              memfd;
#endif


/*
 * Type for a permanently allocated Comm(MSGQ) message to be used as
 * contiguous buffer for data exchange
 */
typedef struct Msg_DataBuf {
    Comm_MsgHeader      header;         /* for use by Comm (MSGQ) */
    Char dataBuf[1];  /* from here till the end of message is data */
} Msg_DataBuf;

static Msg_DataBuf *msgDataBuf = NULL;

/* size for the message above; must be calculated because we can only
 * put data starting from a 128-byte boundary, and we don't know
 * where exactly the address of dataBuf[] above will be, but it will
 * most likely be 4K -128, because all Comm messages are 4K size
 * (that's what Comm_MSGSIZE is), each such message is likely to be 128-byte
 * aligned, so 128byte offset from it is where the data starts.
 */
static UInt32  maxDataBufSize = 0;


static Void send(LogProtocol_Buf *buffer);
static Void cleanup(Void);

/*
 *  ======== LogClient_connect ========
 */
/*!
 *  @brief      Connect to a LogServer.
 *
 *  @pre        Must be called after DSP has been started
 *
 *  @todo       Determine whether this needs to be protected from multiple
 *              'connect'ers.  There's a global 'buf' that isn't protected!
 */
Bool LogClient_connect()
{
    Int         status;

    connectedOK = 0;

    GT_0trace(curTrace, GT_ENTER, "LogClient_connect> "
        "Enter()\n");

    /*
     * Allocate a MSGQ message to be used as data placeholder;
     * we know it's contiguous so that's why we use it, though
     * we'll never actually pass it along
     */
    status = Comm_alloc(
             0, /* pool Id. TODO:M should be Engine_getMemId(engine) */
             (Comm_Msg*)&msgDataBuf,
             Comm_MSGSIZE /* max allowed msg size in CE */
             );
    if (status != Comm_EOK) {
        GT_0trace(curTrace, GT_7CLASS, "LogClient_connect> "
            "Error: failed to allocate Comm (MSGQ) message.\n");
        msgDataBuf = NULL;
        return FALSE;
    }

    /* get the address and 128-byte align it, then calculate max size */
    userAddr = &(msgDataBuf->dataBuf[0]);
    if (((Uint32)userAddr & 0x7F) != 0) {
        userAddr = (char *)(((Uint32)userAddr | 0x7F) + 1);
    }
    maxDataBufSize = Comm_MSGSIZE -
        (Uint32)((Char *)userAddr - (Char *)&msgDataBuf->header);

    physAddr = Memory_getBufferPhysicalAddress(userAddr, maxDataBufSize, NULL);

    if (physAddr == 0) {
        GT_0trace(curTrace, GT_7CLASS, "LogClient_connect> "
            "Error: Memory_getBufferPhysicalAddress() failed.\n");
        return (FALSE);
    }

    GT_3trace(curTrace, GT_2CLASS, "LogClient_connect> "
        "msgDataBuf=0x%x, userAddr=0x%x, physAddr=0x%x\n",
        msgDataBuf, userAddr, physAddr );

    clientMsgHandle = Comm_create(CLIENTQUEUENAME, &clientMsgQueue, NULL);
    if (clientMsgHandle == NULL) {
        GT_0trace(curTrace, GT_7CLASS, "LogClient_connect> "
            "Error: failed to create client queue.\n");
        return (FALSE);
    }

    GT_1trace(curTrace, GT_2CLASS, "LogClient_connect> "
            "clientMsgQueue = 0x%08x\n", clientMsgQueue);

    status = Comm_locate(SERVERQUEUENAME, &serverMsgQueue);
    if (status != Comm_EOK) {
        GT_1trace(curTrace, GT_7CLASS, "LogClient_connect> "
            "Error: failed to locate server queue (0x%x). "
            "Check if your DSP image has BIOS logging enabled\n",
            status);
        return (FALSE);
    }

    GT_1trace(curTrace, GT_2CLASS, "LogClient_connect> "
            "serverMsgQueue = 0x%08x\n", serverMsgQueue);

    status = Comm_alloc(0, (Comm_Msg *)&buf, sizeof(LogProtocol_Buf));
    if (status != Comm_EOK) {
        GT_1trace(curTrace, GT_7CLASS, "LogClient_connect> "
            "Error: failed to alloc commmand buf (0x%x)\n",
            status);
        return (FALSE);
    }

    GT_1trace(curTrace, GT_2CLASS, "LogClient_connect> "
        "buf = 0x%08x\n", buf);

    connectedOK = 1;

    /*
     * Send a couple timesynch messages across.
     */
    LogClient_timeSynch();
    LogClient_timeSynch();

    GT_0trace(curTrace, GT_ENTER, "LogClient_connect> "
        "return\n");

    return (TRUE);
}

/*
 *  ======== LogClient_disconnect ========
 *  Disconnect client from the Log server.
 */
Void LogClient_disconnect(Void)
{
    GT_0trace(curTrace, GT_ENTER, "LogClient_disconnect()\n");

    if (buf != NULL) {
        Comm_free((Comm_Msg)buf);
    }

    if (clientMsgHandle != NULL) {
        Comm_delete(clientMsgHandle);
    }

    if (msgDataBuf != NULL) {
        Comm_free((Comm_Msg)msgDataBuf);
    }
}

/*
 *  ======== LogClient_fwriteLogs ========
 */
Void LogClient_fwriteLogs(FILE *out)
{
    Int32       minusone = -1;
    Uint32      zero = 0;

    GT_1trace(curTrace, GT_ENTER, "LogClient_fwriteLogs(0x%08x)\n", out);

    if (!connectedOK) {
        GT_0trace(curTrace, GT_6CLASS, "LogClient_fwriteLogs> "
            "Warning: not connected to the BIOS log server on the DSP, "
            "cannot collect any BIOS log data.\n");
        return;
    }

    buf->cmd = LogProtocol_READLOGS;
    buf->data.readLogs.physAddr = physAddr;
    buf->data.readLogs.maxSize = maxDataBufSize;
    buf->data.readLogs.size = 0;
    buf->data.readLogs.id = 0;          /* start with LOG index 0 */
    buf->data.readLogs.offset = 0;      /* at address offset 0 */

    /*
     * The server sets 'id' to -1 when done transferring the LOG buffers.
     * The server sets 'id' to "in progress" LOG and 'offset' to byte
     * offset where it left off so that subsequent call to READLOGS can resume
     * at the right point.
     */
    while (buf->data.readLogs.id >= 0) {/* server sets id to -1 when done */
        GT_4trace(curTrace, GT_2CLASS, "LogClient_fwriteLogs> "
            "physAddr = 0x%08x, maxSize = %d, id = %d, offset = %d\n",
            buf->data.readLogs.physAddr,
            buf->data.readLogs.maxSize,
            buf->data.readLogs.id,
            buf->data.readLogs.offset);

        send(buf);

        GT_3trace(curTrace, GT_2CLASS, "LogClient_fwriteLogs> "
            "maxSize = %d, size = %d, offset = %d\n",
            buf->data.readLogs.maxSize, buf->data.readLogs.size,
            buf->data.readLogs.offset);

        fwrite(userAddr, 1, buf->data.readLogs.size, out);
    }

    /*
     *  tag end of block with -1, 0
     */
    fwrite(&minusone, 1, sizeof(minusone), out);
    fwrite(&zero, 1, sizeof(zero), out);

    fflush(out);        /* push data to device */
}


/*
 *  ======== LogClient_init ========
 */
Void LogClient_init(Void)
{
    if (curInit != TRUE) {
        curInit = TRUE;

        GT_create(&curTrace, GTNAME);

#ifdef xdc_target__os_Linux
        memfd = open("/dev/mem", O_RDWR | O_SYNC);

        if (memfd < 0 ) {
            GT_0trace(curTrace, GT_7CLASS,
                "LogClient_init: open('/dev/mem') failed.\n");

            /* TODO: how to fail here? */
            return;
        }
#endif

        Global_atexit((Fxn)cleanup);
    }
}

/*
 *  ======== cleanup ========
 */
static Void cleanup()
{
    if (curInit != FALSE) {
        curInit = FALSE;

#ifdef xdc_target__os_Linux
        if (memfd > 0) {
            close(memfd);
        }
#endif

        /* reinit static variables */
        clientMsgQueue  = Comm_INVALIDMSGQ;
        clientMsgHandle = NULL;
        serverMsgQueue  = Comm_INVALIDMSGQ;
        buf             = NULL;
        userAddr        = NULL;
        physAddr        = 0;
        connectedOK     = 0;
        msgDataBuf      = NULL;
        maxDataBufSize  = 0;
    }
}


/*
 *  ======== LogClient_timeSynch ========
 */
extern Void LogClient_timeSynch(Void)
{
#ifdef xdc_target__os_Linux
    Timer_Obj   *timer1 = NULL;

    GT_0trace(curTrace, GT_ENTER, "LogClient_timeSynch()\n");

    buf->cmd = LogProtocol_TIMESYNCH;

{
    /*
     *  TODO:  This mmap() code should be moved to init() or connect()
     *  Need to make sure that mmap with fopen/O_SYNC is indeed
     *  really does make non-cached buffer.
     */
    Uint32              addr, offset, size;
    struct timeval      time;

    addr = (Uint32)Timer_phys1;
    offset = addr & (4096 - 1);     // compute offset within page
    addr = addr & ~(4096 - 1);      // round down to aligned page base
    size = 4096;                    // round up to page size

    timer1 = mmap(0,                // Preferred start address
        size,                       // Length to be mapped
        PROT_READ | PROT_WRITE,     // really only need read access
        MAP_SHARED,                 // Shared memory
        memfd,                      // File descriptor
        addr);                      // The byte offset from fd

    if (timer1 == MAP_FAILED) {
        GT_2trace(curTrace, GT_7CLASS,
            "mmap(0, %d, #, #, #, 0x%08x) failed!\n", size, addr);

            /* TODO: how to fail here? */
            return;
    }

    timer1 = (Timer_Obj *)((Uint32)timer1 + offset);

    gettimeofday(&time, NULL);

    buf->data.timeSynch.todSeconds = time.tv_sec;
    buf->data.timeSynch.todMicroseconds = time.tv_usec;
}

    buf->data.timeSynch.clientTimeGT = GT_curTime();
    buf->data.timeSynch.clientSynch = timer1->tim34;

    send(buf);

    GT_5trace(curTrace, GT_3CLASS,
         "LogClient_timeSynch: tod = [%d, %d] Arm GT = %d, DSP GT = %d, DSP offset = %d\n",
        buf->data.timeSynch.todSeconds,
        buf->data.timeSynch.todMicroseconds,
        buf->data.timeSynch.clientTimeGT,
        buf->data.timeSynch.serverTimeGT,
        buf->data.timeSynch.offset
    );

    munmap(timer1, 4096);
#endif
}

/*
 *  ======== send ========
 */
static Void send(LogProtocol_Buf *buffer)
{
    GT_1trace(curTrace, GT_ENTER, "send(cmd = %d)\n", buffer->cmd);

    /* set our queue id so that server can send reply back to us */
    Comm_setSrcQueue((Comm_Msg)buffer, clientMsgQueue);

    Comm_put(serverMsgQueue, (Comm_Msg)buffer);

    GT_0trace(curTrace, GT_2CLASS, "send: before get\n");

    Comm_get(clientMsgQueue, (Comm_Msg *)&buffer, Comm_FOREVER);

    GT_0trace(curTrace, GT_2CLASS, "send: after get\n");
}

/*
 */
/*
 *  @(#) ti.sdo.ce.bioslog; 1, 0, 1,326; 12-2-2010 21:18:56; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

