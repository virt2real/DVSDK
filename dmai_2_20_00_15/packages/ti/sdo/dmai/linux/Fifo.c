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

#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include <xdc/std.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Fifo.h>

#define MODULE_NAME     "Fifo"

typedef struct Fifo_Object {
    pthread_mutex_t mutex;
    Int             numBufs;
    Int16           flush;
    Int             pipes[2];
} Fifo_Object;

const Fifo_Attrs Fifo_Attrs_DEFAULT = {
    0
};

/******************************************************************************
 * Fifo_create
 ******************************************************************************/
Fifo_Handle Fifo_create(Fifo_Attrs *attrs)
{
    Fifo_Handle hFifo;

    if (attrs == NULL) {
        Dmai_err0("NULL attrs not supported\n");
        return NULL;
    }

    hFifo = calloc(1, sizeof(Fifo_Object));

    if (hFifo == NULL) {
        Dmai_err0("Failed to allocate space for Fifo Object\n");
        return NULL;
    }

    if (pipe(hFifo->pipes)) {
        free(hFifo);
        return NULL;
    }

    pthread_mutex_init(&hFifo->mutex, NULL);

    return hFifo;
}

/******************************************************************************
 * Fifo_delete
 ******************************************************************************/
Int Fifo_delete(Fifo_Handle hFifo)
{
    int ret = Dmai_EOK;

    if (hFifo) {
        if (close(hFifo->pipes[0])) {
            ret = Dmai_EIO;
        }

        if (close(hFifo->pipes[1])) {
            ret = Dmai_EIO;
        }

        pthread_mutex_destroy(&hFifo->mutex);

        free(hFifo);
    }

    return ret;
}

/******************************************************************************
 * Fifo_get
 ******************************************************************************/
Int Fifo_get(Fifo_Handle hFifo, Ptr ptrPtr)
{
    Int flush;
    Int numBytes;

    assert(hFifo);
    assert(ptrPtr);

    pthread_mutex_lock(&hFifo->mutex);
    flush = hFifo->flush;
    pthread_mutex_unlock(&hFifo->mutex);

    if (flush) {
        return Dmai_EFLUSH;
    }

    numBytes = read(hFifo->pipes[0], ptrPtr, sizeof(Ptr));

    if (numBytes != sizeof(Ptr)) {
        pthread_mutex_lock(&hFifo->mutex);
        flush = hFifo->flush;
        if (flush) {
            hFifo->flush = FALSE;
        }
        pthread_mutex_unlock(&hFifo->mutex);

        if (flush) {
            return Dmai_EFLUSH;
        }
        return Dmai_EIO;
    }

    pthread_mutex_lock(&hFifo->mutex);
    hFifo->numBufs--;
    pthread_mutex_unlock(&hFifo->mutex);

    return Dmai_EOK;
}

/******************************************************************************
 * Fifo_flush
 ******************************************************************************/
Int Fifo_flush(Fifo_Handle hFifo)
{
    Char ch = 0xff;

    assert(hFifo);

    pthread_mutex_lock(&hFifo->mutex);
    hFifo->flush = TRUE;
    pthread_mutex_unlock(&hFifo->mutex);

    /* Make sure any Fifo_get() calls are unblocked */
    if (write(hFifo->pipes[1], &ch, 1) != 1) {
        return Dmai_EIO;
    }

    return Dmai_EOK;
}

/******************************************************************************
 * Fifo_put
 ******************************************************************************/
Int Fifo_put(Fifo_Handle hFifo, Ptr ptr)
{
    assert(hFifo);
    assert(ptr);

    pthread_mutex_lock(&hFifo->mutex);
    hFifo->numBufs++;
    pthread_mutex_unlock(&hFifo->mutex);

    if (write(hFifo->pipes[1], &ptr, sizeof(Ptr)) != sizeof(Ptr)) {
        return Dmai_EIO;
    }

    return Dmai_EOK;
}

/******************************************************************************
 * Fifo_getNumEntries
 ******************************************************************************/
Int Fifo_getNumEntries(Fifo_Handle hFifo)
{
    Int numEntries;

    assert(hFifo);

    pthread_mutex_lock(&hFifo->mutex);
    numEntries = hFifo->numBufs;
    pthread_mutex_unlock(&hFifo->mutex);

    return numEntries;
}

