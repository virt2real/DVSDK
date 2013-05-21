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
#include <string.h>

#include <xdc/std.h>
#include <ti/sdo/ce/osal/Sem.h>
#include <ti/sdo/ce/osal/Memory.h>

/* Needed for Buffer_Memory_Params_DEFAULT_DEFINE */
#include "priv/_Buffer.h"

#include <ti/sdo/dmai/Loader.h>

#define MODULE_NAME     "Loader"

/* These definitions missing in some OS build environments (eg: WinCE) */
#ifndef _IOFBF
    #define _IOFBF  0
#endif  /* _IOFBF */
#ifndef _IOLBF
    #define _IOLBF  1
#endif  /* _IOLBF */
#ifndef _IONBF
    #define _IONBF  2
#endif  /* _IONBF */

/* Internal object holding the state of the Loader */
typedef struct Loader_Object {
    Buffer_Handle       hBuf;
    Buffer_Handle       hReadBuffer;
    Sem_Handle          semStart;
    Sem_Handle          semLock;
    Sem_Handle          semWait;
    Sem_Handle          semRead;    /* a read is on-going */
    Int32               readSize;
    Int32               readAhead;
    FILE               *file;
    Int8               *w;          /* Where new data is written */
    Int8               *r1;         /* Start of data to be read */
    Int8               *r2;         /* End of data to be read */
    Char               *vBuf;
    Int                 flush;
    Int                 end;
    Int                 async;
    Int                 readerWaiting;
    UInt32              vBufSize;
    Memory_AllocParams  mParams;
    Bool                started;
} Loader_Object;

const Loader_Attrs Loader_Attrs_DEFAULT = {
    3 * 1024 * 1024,
    720 * 576 * 2,
    0,
    0,
    FALSE,
    Buffer_Memory_Params_DEFAULT_DEFINE
};

/******************************************************************************
 * cleanup
 ******************************************************************************/
static Int cleanup(Loader_Handle hLoader)
{
    Int ret = Dmai_EOK;

    if (hLoader->file) {
        if (fclose(hLoader->file)) {
            ret = Dmai_EFAIL;
        }
    }

    if (hLoader->vBuf) {
        if (Memory_free(hLoader->vBuf,
                        hLoader->vBufSize, &hLoader->mParams) == FALSE) {
            ret = Dmai_EFAIL;
        }
    }

    if (hLoader->hReadBuffer) {
        ret = Buffer_delete(hLoader->hReadBuffer);
    }

    if (hLoader->hBuf) {
        ret = Buffer_delete(hLoader->hBuf);
    }

    if (hLoader->semStart) {
        Sem_delete(hLoader->semStart);
    }

    if (hLoader->semLock) {
        Sem_delete(hLoader->semLock);
    }

    if (hLoader->semWait) {
        Sem_delete(hLoader->semWait);
    }

    if (hLoader->semRead) {
        Sem_delete(hLoader->semRead);
    }

    free(hLoader);

    return ret;
}

/******************************************************************************
 * waitForStart
 ******************************************************************************/
static inline Int waitForStart(Loader_Handle hLoader)
{
    if (hLoader->async) {
        if (Sem_pend(hLoader->semStart, Sem_FOREVER) != Sem_EOK) {
            Dmai_err0("Failed to pend on semaphore\n");
            return Dmai_EFAIL;
        }

        Sem_post(hLoader->semStart);
    }

    return Dmai_EOK;
}

/******************************************************************************
 * lock
 ******************************************************************************/
static inline Int lock(Loader_Handle hLoader)
{
    if (hLoader->async) {
        if (Sem_pend(hLoader->semLock, Sem_FOREVER) != Sem_EOK) {
            Dmai_err0("Failed to pend on semaphore\n");
            return Dmai_EFAIL;
        }
    }

    return Dmai_EOK;
}

/******************************************************************************
 * unlock
 ******************************************************************************/
static inline Void unlock(Loader_Handle hLoader)
{
    if (hLoader->async) {
        Sem_post(hLoader->semLock);
    }
}

/******************************************************************************
 * reading
 ******************************************************************************/
static inline Int reading(Loader_Handle hLoader)
{
    if (hLoader->async) {
        if (Sem_pend(hLoader->semRead, Sem_FOREVER) != Sem_EOK) {
            Dmai_err0("Failed to pend on read semaphore\n");
            return Dmai_EFAIL;
        }
    }

    return Dmai_EOK;
}

/******************************************************************************
 * doneReading
 ******************************************************************************/
static inline Void doneReading(Loader_Handle hLoader)
{
    if (hLoader->async) {
        Sem_post(hLoader->semRead);
    }
}

/******************************************************************************
 * wait
 ******************************************************************************/
static inline Int wait(Loader_Handle hLoader)
{
    if (hLoader->async) {
        hLoader->readerWaiting = TRUE;
        unlock(hLoader);

        if (Sem_pend(hLoader->semWait, Sem_FOREVER) != Sem_EOK) {
            Dmai_err0("Failed to pend on semaphore\n");
            return Dmai_EFAIL;
        }
    }

    return Dmai_EOK;
}

/******************************************************************************
 * nowait
 ******************************************************************************/
static inline Void nowait(Loader_Handle hLoader)
{
    if (hLoader->async) {
        if (hLoader->readerWaiting) {
            Sem_post(hLoader->semWait);
        }

        hLoader->readerWaiting = FALSE;
    }
}

/******************************************************************************
 * start
 ******************************************************************************/
static inline Int start(Loader_Handle hLoader)
{
    if (hLoader->async) {
        /* Mutually exclude access to internal structures in async mode */
        if (lock(hLoader) < 0) {
            return Dmai_EFAIL;
        }

        if (!hLoader->started) {
            /* post semaphore only if not already started */
            Sem_post(hLoader->semStart);
            hLoader->started = TRUE;
        }

        unlock(hLoader);
    }

    return Dmai_EOK;
}

/******************************************************************************
 * stop
 ******************************************************************************/
static inline Int stop(Loader_Handle hLoader)
{
    if (hLoader->async) {
        if (Sem_pend(hLoader->semStart, Sem_FOREVER) != Sem_EOK) {
            Dmai_err0("Failed to pend on semaphore\n");
            return Dmai_EFAIL;
        }

        /* Mutually exclude access to internal structures in async mode */
        if (lock(hLoader) < 0) {
            return Dmai_EFAIL;
        }

        hLoader->started = FALSE;

        unlock(hLoader);
    }

    return Dmai_EOK;
}

/******************************************************************************
 * Loader_create
 ******************************************************************************/
Loader_Handle Loader_create(Char *fileName, Loader_Attrs *attrs)
{
    Buffer_Attrs        bAttrs        = Buffer_Attrs_DEFAULT;
    Loader_Handle       hLoader;

    if (!fileName || !attrs || !attrs->readSize || !attrs->readBufSize) {
        Dmai_err0("Must supply a file name and valid attributes\n");
        return NULL;
    }
 
    hLoader = (Loader_Handle)calloc(1, sizeof(Loader_Object));

    if (hLoader == NULL) {
        Dmai_err0("Failed to allocate Loader Object\n");
        return NULL;
    }
    
    bAttrs.memParams = attrs->mParams;

    Dmai_dbg4("Creating Loader for %s with buffer size %d, window size %d, "
        "alignment %d\n", fileName, attrs->readBufSize, 
        attrs->readSize, attrs->mParams.align);

    /* Open the file for binary reading */
    hLoader->file = fopen(fileName, "rb");

    if (hLoader->file == NULL) {
        Dmai_err1("Failed to open %s\n", fileName);
        cleanup(hLoader);
        return NULL;
    }

    /* Using a bigger input buffer for stdio enhances RTDX performance */
    if (attrs->vBufSize) {
        hLoader->mParams = Memory_DEFAULTPARAMS;
        hLoader->vBuf = Memory_alloc(attrs->vBufSize, &hLoader->mParams);

        if (hLoader->vBuf == NULL) {
            Dmai_err1("Failed to allocate memory (%d) for stdio buffer\n",
                      attrs->vBufSize);
            cleanup(hLoader);
            return NULL;
        }

        hLoader->vBufSize = attrs->vBufSize;

        if (setvbuf(hLoader->file, hLoader->vBuf,
                    _IOFBF, attrs->vBufSize) != 0) {

            Dmai_err1("Failed setvbuf (%d) on file descriptor\n",
                      attrs->vBufSize);
            cleanup(hLoader);
            return NULL;
        }
    }

    /* Create the ring buffer which will hold the data */
    hLoader->hReadBuffer = Buffer_create(attrs->readBufSize, &bAttrs);

    if (hLoader->hReadBuffer == NULL) {
        Dmai_err0("Failed to allocate ring buffer\n");
        cleanup(hLoader);
        return NULL;
    }

    /* Invalidate the created pool in case it is cached */
    if (hLoader->mParams.flags == Memory_CACHED)
    {
        Memory_cacheInv(Buffer_getUserPtr(hLoader->hReadBuffer), 
            attrs->readBufSize);
    }

    bAttrs.reference = TRUE;
    hLoader->hBuf = Buffer_create(attrs->readSize, &bAttrs);

    if (hLoader->hBuf == NULL) {
        Dmai_err0("Failed to allocate window buffer object\n");
        cleanup(hLoader);
        return NULL;
    }

    if (attrs->async) {
        hLoader->semStart = Sem_create(0, 0);
        hLoader->semLock = Sem_create(1, 1);
        hLoader->semWait = Sem_create(2, 0);
        hLoader->semRead = Sem_create(3, 1);

        if (hLoader->semStart == NULL ||
            hLoader->semLock == NULL ||
            hLoader->semWait == NULL) {

            Dmai_err0("Failed to create semaphores\n");
            cleanup(hLoader);
            return NULL;
        }
    }

    hLoader->readSize = attrs->readSize;
    hLoader->readAhead = attrs->async ? attrs->readAhead : 0;
    hLoader->async = attrs->async;
    hLoader->started = FALSE;

    return hLoader;
}

/******************************************************************************
 * Loader_prime
 ******************************************************************************/
Int Loader_prime(Loader_Handle hLoader, Buffer_Handle *hBufPtr)
{
    Buffer_Handle hReadBuffer = hLoader->hReadBuffer;
    Int numBytes;

    assert(hLoader);
    assert(hBufPtr);

    /* We will read from the file */
    if (reading(hLoader) < 0) {
        return Dmai_EFAIL;
    }

    /* Mutually exclude access to internal structures in async mode */
    if (lock(hLoader) < 0) {
        doneReading(hLoader);
        return Dmai_EFAIL;
    }

    /* rewind replaced by fseek/clearerr combination which is more generic 
     * and works under multiple OSes
     */
    fseek(hLoader->file, 0, SEEK_SET);
    clearerr(hLoader->file);

    /* Read a full 'window' of encoded data */
    numBytes = fread(Buffer_getUserPtr(hReadBuffer), 1,
                     hLoader->readSize, hLoader->file);

    /* Must be able to provide a full window to the app (codec) */
    if (numBytes < hLoader->readSize && ferror(hLoader->file)) {
        unlock(hLoader);
        doneReading(hLoader);
        Dmai_err0("Error reading data from video file\n");
        return Dmai_EIO;
    }

    /* Initialize state */
    hLoader->r1 = Buffer_getUserPtr(hReadBuffer);
    hLoader->r2 = Buffer_getUserPtr(hReadBuffer) + numBytes;
    hLoader->w = hLoader->r2;

    *hBufPtr = hLoader->hBuf;

    Buffer_setUserPtr(*hBufPtr, hLoader->r1);
    Buffer_setSize(*hBufPtr, numBytes);
    Buffer_setNumBytesUsed(*hBufPtr, numBytes);

    hLoader->end = FALSE;

    if (numBytes == 0) {
        unlock(hLoader);
        doneReading(hLoader);
        Dmai_dbg0("File is 0 bytes\n");
        return Dmai_EEOF;
    }

    /* After Priming, WB if the pool is CACHED */
    if (hLoader->mParams.flags == Memory_CACHED)
    {
        Memory_cacheWb(Buffer_getUserPtr(hReadBuffer), 
            hLoader->readSize);
    }

    /* Are we at the end of the file? */
    if (numBytes < hLoader->readSize) {
        hLoader->end = TRUE;
        unlock(hLoader);

        doneReading(hLoader);

        return Dmai_EEOF;
    }

    unlock(hLoader);
    doneReading(hLoader);

    /* Make sure other thread wakes up and tries reading again in async mode */
    nowait(hLoader);

    /* Start the loader */
    if (start(hLoader) < 0) {
        Dmai_err0("Failed to start loader.\n");
        return Dmai_EFAIL;
    }

    return Dmai_EOK;
}

/******************************************************************************
 * Loader_readData
 ******************************************************************************/
Int Loader_readData(Loader_Handle hLoader)
{
    Int delta, toRead, numBytes;
    UInt32 ringBufferEnd, catchUp;
    Int8 *ptr;

    assert(hLoader);

    if (hLoader->flush) {
        return Dmai_EFLUSH;
    }

    /* Wait for the priming to be done before reading data in async mode*/
    if (waitForStart(hLoader) < 0) {
        return Dmai_EFAIL;
    }

    reading(hLoader);

    /* Mutually exclude access to internal structures in async mode */
    if (lock(hLoader) < 0) {
        doneReading(hLoader);
        return Dmai_EFAIL;
    }

    ringBufferEnd = (UInt32) Buffer_getUserPtr(hLoader->hReadBuffer) +
                    (UInt32) Buffer_getSize(hLoader->hReadBuffer);

    delta = hLoader->w - hLoader->r1;

    /* Do we need to read more data? */
    if (delta < hLoader->readSize + hLoader->readAhead) {
        toRead = hLoader->readSize + hLoader->readAhead - delta;

        /* Will this write fit in the ring buffer? */
        if ((UInt32) hLoader->w + toRead > ringBufferEnd) {
            
            if (Buffer_getUserPtr(hLoader->hReadBuffer) + delta >= hLoader->r1){
                Dmai_err0("You need a bigger ring buffer\n");
                unlock(hLoader);
                doneReading(hLoader);
                return Dmai_EINVAL;
            }

            ptr = hLoader->r1;

            /* Allow other thread getting frames while memcpy is performed */
            unlock(hLoader);
            memcpy(Buffer_getUserPtr(hLoader->hReadBuffer), ptr, delta);

            /* After Copying, WB if the pool is CACHED */
            if (hLoader->mParams.flags == Memory_CACHED)
            {
                Memory_cacheWb(Buffer_getUserPtr(hLoader->hReadBuffer), 
                    delta);
            }

            /* Reacquire lock and compensate for intermediate processing */
            if (lock(hLoader) < 0) {
                doneReading(hLoader);
                return Dmai_EFAIL;
            }

            catchUp = hLoader->r1 - ptr;

            /* Reset ring buffer pointers to beginning of buffer */
            hLoader->w = Buffer_getUserPtr(hLoader->hReadBuffer) + delta;
            hLoader->r1 = Buffer_getUserPtr(hLoader->hReadBuffer) + catchUp;
            hLoader->r2 = Buffer_getUserPtr(hLoader->hReadBuffer) + catchUp +
                            (delta - hLoader->readAhead);
        }

        /* Read more data from file */
        numBytes = fread(hLoader->w, 1, toRead, hLoader->file);

        if (numBytes < toRead && ferror(hLoader->file)) {
            Dmai_err0("Error reading data from file\n");
            unlock(hLoader);
            doneReading(hLoader);
            return Dmai_EIO;
        }

        /* After Reading, WB if the pool is CACHED */
        if (hLoader->mParams.flags == Memory_CACHED)
        {
            Memory_cacheWb(hLoader->w, toRead);
        }

        hLoader->w += numBytes;

        /* Are we at the end of the file? */
        if (numBytes == 0) {
            hLoader->end = TRUE;
            unlock(hLoader);

            doneReading(hLoader);

            /* Stop the loader to allow repriming */
            if (stop(hLoader) < 0) {
                return Dmai_EFAIL;
            }

            return Dmai_EEOF;
        }

        unlock(hLoader);
        doneReading(hLoader);
    }
    else {
        doneReading(hLoader);

        /* Wait for the other thread to catch up in async mode */
        wait(hLoader);
    }

    return Dmai_EOK;
}

/******************************************************************************
 * Loader_getFrame
 ******************************************************************************/
Int Loader_getFrame(Loader_Handle hLoader, Buffer_Handle hBuf)
{
    Int32 delta;
    Int ret = Dmai_EOK;

    assert(hLoader);
    assert(hBuf);
    assert(hBuf == hLoader->hBuf);

    /* Mutually exclude access to internal structures in async mode */
    if (lock(hLoader) < 0) {
        return Dmai_EFAIL;
    }

    /* Increment the read pointers from current buffer */
    hLoader->r1 += Buffer_getNumBytesUsed(hBuf);
    hLoader->r2 += Buffer_getNumBytesUsed(hBuf);

    /* In async mode the data is read automatically */
    if (!hLoader->async) {
        ret = Loader_readData(hLoader);

        if (ret < 0) {
            return ret;
        }
    }

    /* How far ahead is the writer? */
    delta = hLoader->w - hLoader->r1;

    if (delta <= 0) {
        /* No bytes left, are we at end of file? */
        if (hLoader->end) {
            Buffer_setUserPtr(hBuf, NULL);
            Buffer_setSize(hBuf, 0);
            Buffer_setNumBytesUsed(hBuf, 0);
            ret = Dmai_EEOF;
        }
        else {
            Dmai_err0("Reader not keeping up with processing\n");
            ret = Dmai_EIO;
        }
    }
    else {
        /* Return new pointers to the next frame */
        Buffer_setUserPtr(hBuf, hLoader->r1);
        if (delta > hLoader->readSize) {
            Buffer_setSize(hBuf, hLoader->readSize);
            Buffer_setNumBytesUsed(hBuf, hLoader->readSize);
        }
        else {
            Buffer_setSize(hBuf, delta);
            Buffer_setNumBytesUsed(hBuf, delta);
        }
    }

    /* Make sure other thread wakes up and tries reading again in async mode */
    nowait(hLoader);

    unlock(hLoader);

    return ret;
}

/******************************************************************************
 * Loader_flush
 ******************************************************************************/
Int Loader_flush(Loader_Handle hLoader)
{
    /* Make sure the reader other thread (if any) is unlocked */
    hLoader->flush = TRUE;
    /* Start the loader */
    if (start(hLoader) < 0) {
        Dmai_err0("Failed to start loader during flush.\n");
        return Dmai_EFAIL;
    }
    unlock(hLoader);
    nowait(hLoader);

    return Dmai_EOK;
}

/******************************************************************************
 * Loader_delete
 ******************************************************************************/
Int Loader_delete(Loader_Handle hLoader)
{
    Int ret = Dmai_EOK;

    if (hLoader) {
        ret = cleanup(hLoader);
    }

    return ret;
}
