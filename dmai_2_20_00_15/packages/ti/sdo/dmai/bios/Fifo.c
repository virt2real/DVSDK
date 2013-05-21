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

#include <xdc/std.h>

#include <std.h>
#include <que.h>
#include <sem.h>
#include <mem.h>
#include <buf.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Fifo.h>

#define MODULE_NAME     "Fifo"

typedef struct Fifo_Object {
    SEM_Obj     sem;   /* Synchronization semaphore for queue */
    SEM_Obj     mutex; /* Mutex for mutual exclusion of fields in Fifo_Object */
    QUE_Obj     queue;
    Int         numBufs;
    Int16       flush;
    BUF_Handle  hBufPool; /* Buffer pool used for internal usage */
} Fifo_Object;

/* Structure that describes each element that is put on the Fifo */
typedef struct Fifo_Elem {
    QUE_Elem    elem;  /* Compulsory header for QUE usage */
    Ptr         ptr;
} Fifo_Elem;

const Fifo_Attrs Fifo_Attrs_DEFAULT = {
    20
};

/******************************************************************************
 * Fifo_create
 ******************************************************************************/
Fifo_Handle Fifo_create(Fifo_Attrs *attrs)
{
    Fifo_Handle hFifo;
    BUF_Attrs bAttrs = BUF_ATTRS;

    if (attrs == NULL) {
        return NULL;
    }
    
    hFifo = MEM_calloc(Dmai_Bios_segid, sizeof(Fifo_Object), 0);

    if (hFifo == NULL) {
        Dmai_err0("Failed to allocate space for Fifo Object\n");
        return NULL;
    }
    
    /* Allocate a buffer pool for messages */
    bAttrs.segid = Dmai_Bios_segid;
    hFifo->hBufPool = BUF_create(attrs->maxElems, sizeof(Fifo_Elem), 0, &bAttrs);
    if (hFifo->hBufPool == NULL) {
        Dmai_err0("Failed to allocate space for buffer pool\n");
        MEM_free(Dmai_Bios_segid, hFifo, sizeof(Fifo_Object));
        return NULL;
    }
    
    /* initialize the object */
    QUE_new(&hFifo->queue);
    SEM_new(&hFifo->sem, 0);
    SEM_new(&hFifo->mutex, 1);

    return hFifo;
}

/******************************************************************************
 * Fifo_delete
 ******************************************************************************/
Int Fifo_delete(Fifo_Handle hFifo)
{
    int ret = Dmai_EOK;

    if (hFifo) {
        if (MEM_free(Dmai_Bios_segid, hFifo, sizeof(Fifo_Object)) != TRUE) {
            ret = Dmai_EFAIL;
        }
        if (BUF_delete(hFifo->hBufPool) == 0) {
            ret = Dmai_EFAIL;
        }
    }
    
    return ret;
}

/******************************************************************************
 * Fifo_get
 ******************************************************************************/
Int Fifo_get(Fifo_Handle hFifo, Ptr ptrPtr)
{
    Int flush;
    Fifo_Elem * elem;
    Ptr * p = (Ptr *)ptrPtr;

    assert(hFifo);
    assert(ptrPtr);

    SEM_pend(&hFifo->mutex, SYS_FOREVER);
    flush = hFifo->flush;
    SEM_post(&hFifo->mutex);

    /* If pipe is already flushed, do not block */
    if (flush) {
        return Dmai_EFLUSH;
    }

    /* Wait for element from other thread */
    SEM_pend(&hFifo->sem, SYS_FOREVER);
   
    /* Handle flushed fifo */
    SEM_pend(&hFifo->mutex, SYS_FOREVER);
    flush = hFifo->flush;
    if (flush) {
        hFifo->flush = FALSE;
    }
    SEM_post(&hFifo->mutex);
    if (flush) {
        return Dmai_EFLUSH;
    }
    
    /* Get an element from the Fifo queue */
    elem = (Fifo_Elem *)QUE_get(&hFifo->queue);
    *p = elem->ptr;
    if (BUF_free(hFifo->hBufPool, elem) != TRUE) {
        return Dmai_EFAIL;
    }    

    SEM_pend(&hFifo->mutex, SYS_FOREVER);
    hFifo->numBufs--;
    SEM_post(&hFifo->mutex);

    return Dmai_EOK;
}

/******************************************************************************
 * Fifo_flush
 ******************************************************************************/
Int Fifo_flush(Fifo_Handle hFifo)
{
    assert(hFifo);

    SEM_pend(&hFifo->mutex, SYS_FOREVER);
    hFifo->flush = TRUE;
    SEM_post(&hFifo->mutex);

    /* Make sure any Fifo_get() calls are unblocked */
    SEM_post(&hFifo->sem);

    return Dmai_EOK;
}

/******************************************************************************
 * Fifo_put
 ******************************************************************************/
Int Fifo_put(Fifo_Handle hFifo, Ptr ptr)
{
    Fifo_Elem * elem;
    
    assert(hFifo);
    assert(ptr);

    SEM_pend(&hFifo->mutex, SYS_FOREVER);
    hFifo->numBufs++;
    SEM_post(&hFifo->mutex);

    elem = BUF_alloc(hFifo->hBufPool);
    if (elem == NULL) {
        Dmai_err0("Failed to allocate space for Fifo Object\n");
        return Dmai_EFAIL;
    }
    elem->ptr = ptr;
    
    /* Putting an element on the queue with ptr as payload */
    QUE_put(&hFifo->queue, (QUE_Elem *)elem);
    SEM_post(&hFifo->sem);
    
    return Dmai_EOK;
}

/******************************************************************************
 * Fifo_getNumEntries
 ******************************************************************************/
Int Fifo_getNumEntries(Fifo_Handle hFifo)
{
    Int numEntries;

    assert(hFifo);

    SEM_pend(&hFifo->mutex, SYS_FOREVER);
    numEntries = hFifo->numBufs;
    SEM_post(&hFifo->mutex);

    return numEntries;
}

