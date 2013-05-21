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
 *  ======== Server.c ========
 */

#include <xdc/std.h>

#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/ce/osal/Global.h>

#include <ti/sdo/utils/trace/gt.h>

#include <ti/sdo/ce/Engine.h>

#include <ti/sdo/ce/Server.h>

#define GETENGINEHANDLE(s) (Engine_Handle)s

static Server_Status getServerStatus(Engine_Error err);

static Void cleanup(Void);

#if defined(xdc_target__isaCompatible_v5T) || defined(xdc_target__isaCompatible_v4T)
extern Int Global_useLinkArbiter;
#endif

/* REMEMBER: if you add an initialized static var, reinitialize it at cleanup */
Bool Server_holdingTraceToken = FALSE;
static Bool init = FALSE;
static GT_Mask curTrace;

/*
 *  ======== Server_connectTrace ========
 */
Server_Status Server_connectTrace(Server_Handle server, Int * token)
{
    Engine_Error engineStatus;
    Server_Status status;
    Int gotToken = FALSE;

    GT_2trace(curTrace, GT_ENTER, "Server_connectTrace('0x%x', 0x%x)\n",
        server, token);

    GT_assert(curTrace, ((server != NULL) && (token != NULL)));

    /* first check if process already connected for trace */
    if (Server_holdingTraceToken == TRUE) {
        status = Server_EINUSE;
    }

    /* else, request connect token from RMS */
    else {

        /* call Engine function to attempt connection */
        engineStatus = Engine_requestTraceToken(server);
        status = getServerStatus(engineStatus);

        /* if success, set flag indicating this process holds trace token */
        if (status == Server_EOK) {
            Server_holdingTraceToken = TRUE;
            gotToken = TRUE;
        }
    }

    /* set token value to return to caller: TRUE if *this* call got token */
    *token = gotToken;

    GT_2trace(curTrace, GT_ENTER, "Server_connectTrace> "
            "token(%d), return(%d)\n", gotToken, status);

    return (status);
}

/*
 *  ======== Server_disconnectTrace ========
 */
Server_Status Server_disconnectTrace(Server_Handle server, Int token)
{
    Server_Status status = Server_EOK;

    GT_2trace(curTrace, GT_ENTER, "Server_disconnectTrace('0x%x', 0x%x)\n",
        server, token);

    GT_assert(curTrace, (server != NULL));

    /*
     * if client passes token == TRUE, then companion call to connect actually
     * acquired the trace token, so release it back to RMS; else, if
     * token === FALSE, can simply ignore the request, and return Server_EOK
     */
    if (token == TRUE) {

        /* call Engine function to attempt disconnect */
        if (Engine_releaseTraceToken(server)) {
            /* if success, reset process-holding-token flag */
            Server_holdingTraceToken = FALSE;
        }
        else {
            status = Server_ERUNTIME;
        }
    }

    GT_1trace(curTrace, GT_ENTER, "Server_disconnectTrace> return(%d)\n",
            status);

    return (status);
}

/*
 *  ======== Server_fwriteTrace ========
 */
Int Server_fwriteTrace(Server_Handle server, String prefix, FILE *out)
{
    GT_3trace(curTrace, GT_ENTER, "Server_fwriteTrace('0x%x', %s, 0x%x)\n",
        server, prefix, out);

    GT_assert(curTrace, (server != NULL));

    /* call Engine function to write the trace data */
    return(Engine_fwriteTrace(GETENGINEHANDLE(server), prefix, out));
}

// TODO: Do we need this?
/*
 *  ======== Server_getAlgInfo ========
 */
Int Server_getAlgInfo(Server_Handle server, Int algNum,
        Server_AlgInfo *algInfo)
{
    Engine_AlgInfo  info;
    Engine_Error    err = Engine_EOK;
    Server_Status   status = Server_EOK;

    GT_3trace(curTrace, GT_ENTER, "Server_getAlgInfo('0x%x', %d, 0x%x)\n",
            server, algNum, algInfo);

    GT_assert(curTrace, (server != NULL));

    /* Call Engine function to get number of memory heaps on the DSP */
    err = Engine_getServerAlgInfo(server, algNum, &info);
    status = getServerStatus(err);

    if (status == Server_EOK) {
        /* Copy data from info to algInfo */
        algInfo->name = info.name;
        algInfo->typeTab = info.typeTab;
    }

    return (status);
}

/*
 *  ======== Server_getCpuLoad ========
 */
Int Server_getCpuLoad(Server_Handle server)
{
    Int load;

    GT_1trace(curTrace, GT_ENTER, "Server_getCpuLoad('0x%x')\n", server);

    GT_assert(curTrace, (server != NULL));

    /* call Engine function to get server's CPU load */
    load = Engine_getCpuLoad(GETENGINEHANDLE(server));

    return (load);
}

/*
 *  ======== Server_getMemStat ========
 */
Server_Status Server_getMemStat(Server_Handle server, Int segId,
    Server_MemStat *stat)
{
    Engine_Error    err = Engine_EOK;
    Server_Status   status = Server_EOK;

    GT_3trace(curTrace, GT_ENTER, "Server_getMemStat('0x%x', %d, 0x%x)\n",
        server, segId, stat);

    GT_assert(curTrace, (server != NULL) && (stat != NULL));

    /* Call Engine function to get heap info */
    err = Engine_getMemStat(server, segId, (Engine_MemStat *)stat);
    status = getServerStatus(err);

    GT_assert(curTrace, (status == Server_EOK) || (status == Server_ENOTFOUND)
           || (status == Server_ERUNTIME));

    return (status);
}

/*
 *  ======== Server_getNumAlgs ========
 */
Server_Status Server_getNumAlgs(Server_Handle server, Int *numAlgs)
{
    Engine_Error    err = Engine_EOK;
    Server_Status   status = Server_EOK;

    GT_2trace(curTrace, GT_ENTER, "Server_getNumAlgs('0x%x', 0x%x)\n",
        server, numAlgs);

    GT_assert(curTrace, (server != NULL) && (numAlgs != NULL));

    /* Call Engine function to get number of memory heaps on the DSP */
    err = Engine_getNumServerAlgs(server, numAlgs);
    status = getServerStatus(err);

    GT_assert(curTrace, (status == Server_EOK) || (status == Server_ERUNTIME));

    if (status != Server_EOK) {
        *numAlgs = 0;
    }

    return (status);
}

/*
 *  ======== Server_getNumMemSegs ========
 */
Server_Status Server_getNumMemSegs(Server_Handle server, Int *numSegs)
{
    Engine_Error    err = Engine_EOK;
    Server_Status   status = Server_EOK;

    GT_2trace(curTrace, GT_ENTER, "Server_getNumMemSegs('0x%x', 0x%x)\n",
        server, numSegs);

    GT_assert(curTrace, (server != NULL) && (numSegs != NULL));

    /* Call Engine function to get number of memory heaps on the DSP */
    err = Engine_getNumMemSegs(server, numSegs);
    status = getServerStatus(err);

    GT_assert(curTrace, (status == Server_EOK) || (status == Server_ERUNTIME));

    if (status != Server_EOK) {
        *numSegs = 0;
    }

    return (status);
}

/*
 *  ======== Server_init ========
 */
Void Server_init(Void)
{
    if (init == FALSE) {
        init = TRUE;

        GT_create(&curTrace, Server_GTNAME);

        GT_0trace(curTrace, GT_ENTER, "Server_init()\n");

#if defined(xdc_target__isaCompatible_v5T) || defined(xdc_target__isaCompatible_v4T)
        /* for single CE process: set flag, this process owns all DSP trace */
        GT_1trace(curTrace, GT_ENTER,
                "Server_init> Global_useLinkArbiter = %d\n",
                Global_useLinkArbiter);
        if (!Global_useLinkArbiter) {
            Server_holdingTraceToken = TRUE;
        }
#else
        GT_0trace(curTrace, GT_ENTER, "Server_init> We're not an "
                "xdc_target__isaCompatible_v5T or v4T.\n");
#endif

        Global_atexit((Fxn)cleanup);
    }
}

/*
 *  ======== Server_redefineHeap ========
 */
Server_Status Server_redefineHeap(Server_Handle server, String name,
        Uint32 base, Uint32 size)
{
    Engine_Error    err = Engine_EOK;
    Server_Status   status = Server_EOK;

    GT_4trace(curTrace, GT_ENTER,
            "Server_redefineHeap('0x%x', %s, 0x%x, 0x%x)\n", server, name,
            base, size);

    GT_assert(curTrace, server != NULL);
    GT_assert(curTrace, !(base & 0x7));    /* base must be 8-byte aligned */

    /* Call engine function to change algorithm heap base and size */
    err = Engine_redefineHeap(server, name, base, size);
    status = getServerStatus(err);

    GT_assert(curTrace, (status == Server_EOK) || (status == Server_EINVAL) ||
            (status == Server_ENOTFOUND) || (status == Server_EINUSE) ||
              (status == Server_ERUNTIME));

    return (status);
}

/*
 *  ======== Server_restoreHeap ========
 */
Server_Status Server_restoreHeap(Server_Handle server, String name)
{
    Engine_Error    err = Engine_EOK;
    Server_Status   status = Server_EOK;

    GT_2trace(curTrace, GT_ENTER, "Server_restoreHeap('0x%x %s)\n", server,
            name);

    GT_assert(curTrace, server != NULL);

    /* Call Engine function to reset the named heap's base and size */
    err = Engine_restoreHeap(server, name);
    status = getServerStatus(err);

    GT_assert(curTrace, (status == Server_EOK) || (status == Server_EINVAL) ||
            (status == Server_ENOTFOUND) || (status == Server_EINUSE) ||
              (status == Server_ERUNTIME));

    return (status);
}

/*
 *  ======== Server_setTrace ========
 */
Int Server_setTrace(Server_Handle server, String mask)
{
    Engine_Error engineStatus;

    GT_2trace(curTrace, GT_ENTER, "Server_setTrace('0x%x', %s)\n",
        server, mask);

    GT_assert(curTrace, (server != NULL));

    /* call Engine function set the server's trace mask */
    engineStatus = Engine_setTrace(GETENGINEHANDLE(server), mask);

    return(getServerStatus(engineStatus));
}

/*
 *  ======== cleanup ========
 */
static Void cleanup(Void)
{
    if (init != FALSE) {
        init = FALSE;

        /* reinitialize static vars */
        Server_holdingTraceToken = FALSE;
    }
}

/*
 *  ======== getServerStatus ========
 *  Convert Engine error code to server status.
 */
static Server_Status getServerStatus(Engine_Error err)
{
    switch (err) {
        case Engine_EOK:
            return (Server_EOK);
        case Engine_ENOSERVER:
            return (Server_ENOSERVER);
        case Engine_ENOMEM:
            return (Server_ENOMEM);
        case Engine_ERUNTIME:
            return (Server_ERUNTIME);
        case Engine_EINVAL:
            return (Server_EINVAL);
        case Engine_EWRONGSTATE:
            return (Server_EWRONGSTATE);
        case Engine_EINUSE:
            return (Server_EINUSE);
        case Engine_ENOTFOUND:
            return (Server_ENOTFOUND);
        default:
            return (Server_EFAIL);
    }
}
/*
 *  @(#) ti.sdo.ce; 1, 0, 6,432; 12-2-2010 21:19:08; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

