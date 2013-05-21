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
#include <string.h>

#include <xdc/std.h>

#include <ti/sdo/dmai/Buffer.h>
#include <ti/sdo/dmai/BufTab.h>
#include <ti/sdo/dmai/BufferGfx.h>

#include "priv/_Buffer.h"

#define MODULE_NAME     "BufTab"

#define PAGE_ALIGN      4096

typedef struct BufTab_Object {
    Buffer_Handle *hBufs;       /* Array of buffers in the BufTab. */
    Int            numBufs;     /* The number of buffers in the BufTab. */
    Buffer_Handle *hOrigBufs;
    Int            origNumBufs;
} BufTab_Object;

/******************************************************************************
 * cleanupBufs
 ******************************************************************************/
static Int cleanupBufs(Buffer_Handle *hBufs, Int numBufs)
{
    Int ret = Dmai_EOK;
    Int bufIdx;

    for (bufIdx=0; bufIdx < numBufs; bufIdx++) {
        if (hBufs[bufIdx]) {
            if (Buffer_delete(hBufs[bufIdx]) < 0) {
                ret = Dmai_EFAIL;
            }
        }
    }

    return ret;
}

/******************************************************************************
 * cleanup
 ******************************************************************************/
static Int cleanup(BufTab_Handle hBufTab)
{
    Int ret = Dmai_EOK;
    Int bufIdx, oldBufIdx;
    Int dupe;

    if (hBufTab->hOrigBufs) {
        for (bufIdx = 0; bufIdx < hBufTab->numBufs; bufIdx++) {
            dupe = FALSE;

            for (oldBufIdx = 0; oldBufIdx < hBufTab->origNumBufs; oldBufIdx++) {
                if (hBufTab->hOrigBufs[oldBufIdx] == hBufTab->hBufs[bufIdx]) {
                    dupe = TRUE; 
                }
            }

            if (!dupe) {
                Buffer_delete(hBufTab->hBufs[bufIdx]);
            }
        }

        free(hBufTab->hBufs);

        ret = cleanupBufs(hBufTab->hOrigBufs, hBufTab->origNumBufs);
        free(hBufTab->hOrigBufs);
    }
    else {
        ret = cleanupBufs(hBufTab->hBufs, hBufTab->numBufs);
        free(hBufTab->hBufs);
    }

    free(hBufTab);

    return ret;
}

/******************************************************************************
 * BufTab_create
 ******************************************************************************/
BufTab_Handle BufTab_create(Int numBufs, Int32 size, Buffer_Attrs *attrs)
{
    BufTab_Handle    hBufTab;
    Int              bufIdx;

    if (attrs == NULL) {
        Dmai_err0("Must provide attrs\n");
        return NULL;
    }

    hBufTab = (BufTab_Handle)calloc(1, sizeof(BufTab_Object));

    if (hBufTab == NULL) {
        Dmai_err0("Failed to allocate space for BufTab Object\n");
        return NULL;
    }

    Dmai_dbg1("Allocating BufTab for %d buffers\n", numBufs);

    hBufTab->hBufs = (Buffer_Handle*)calloc(numBufs, sizeof(Buffer_Handle));

    if (hBufTab->hBufs == NULL) {
        Dmai_err0("Failed to allocate space for Buffer Handles\n");
        free(hBufTab);
        return NULL;
    }

    hBufTab->numBufs = numBufs;

    if (hBufTab == NULL) {
        Dmai_err0("Failed to allocate BufTab Object\n");
        return NULL;
    }

    for (bufIdx=0; bufIdx < hBufTab->numBufs; bufIdx++) {
        hBufTab->hBufs[bufIdx] = Buffer_create(size, attrs);

        if (hBufTab->hBufs[bufIdx] == NULL) {
            Dmai_err1("Failed to allocate buffer %d for BufTab\n", bufIdx);
            cleanup(hBufTab);
            return NULL;
        }

        _Buffer_setId(hBufTab->hBufs[bufIdx], bufIdx);
        _Buffer_setBufTab(hBufTab->hBufs[bufIdx], hBufTab);
    }

    return hBufTab;
}
  
/******************************************************************************
 * BufTab_expand
 ******************************************************************************/
Int BufTab_expand(BufTab_Handle hBufTab, Int numBufs)
{
    Buffer_Handle *hOldBufs, hBuf;
    Int oldNumBufs, bufIdx, minIdx = 0;
    Int32 minSize = ~(1<<31);

    assert(hBufTab);
    assert(hBufTab->numBufs > 0);

    for (bufIdx = 0; bufIdx < hBufTab->numBufs; bufIdx++) {
        if (_Buffer_getOriginalSize(hBufTab->hBufs[bufIdx]) < minSize) {
            minSize = _Buffer_getOriginalSize(hBufTab->hBufs[bufIdx]);
            minIdx = bufIdx;
        }
    }

    hOldBufs = hBufTab->hBufs;
    oldNumBufs = hBufTab->numBufs;

    /* Allocate space for the Buffer Handles */
    hBufTab->hBufs = (Buffer_Handle*)calloc(hBufTab->numBufs + numBufs,
                                            sizeof(Buffer_Handle));

    if (hBufTab->hBufs == NULL) {
        Dmai_err0("Failed to allocate space for Buffer Handles\n");
        return Dmai_ENOMEM;
    }

    memcpy(hBufTab->hBufs, hOldBufs, sizeof(Buffer_Handle) * oldNumBufs);
    hBufTab->numBufs = oldNumBufs + numBufs;

    for (bufIdx = 0; bufIdx < numBufs; bufIdx++) {
        hBuf = Buffer_clone(hBufTab->hBufs[minIdx]);

        if (hBuf == NULL) {
            Dmai_err0("Failed to clone buffer\n");
            cleanupBufs(&hBufTab->hBufs[oldNumBufs], bufIdx);
            free(hBufTab->hBufs);
            hBufTab->hBufs = hOldBufs;
            return Dmai_ENOMEM;
        }

        _Buffer_setId(hBuf, oldNumBufs + bufIdx);
        _Buffer_setBufTab(hBuf, hBufTab);
        hBufTab->hBufs[oldNumBufs + bufIdx] = hBuf;
    }

    free(hOldBufs);

    return Dmai_EOK;
}

/******************************************************************************
 * BufTab_chunk
 ******************************************************************************/
Int BufTab_chunk(BufTab_Handle hBufTab, Int numBufs, Int32 bufSize)
{
    BufferGfx_Attrs gfxAttrs = BufferGfx_Attrs_DEFAULT;
    Int bufIdxOld, bufIdxNew = 0;
    Buffer_Handle hOldBuf, hNewBuf;
    Int32 numBytes, oldSize, alignedSize;
    Int8  *virtPtr;
    Int32 alignment;

    assert(hBufTab);
    assert(bufSize > 0);
    assert(numBufs > 0);

    if (hBufTab->hOrigBufs) {
        Dmai_err0("BufTab already chunked, collapse it first\n");
        return Dmai_EFAIL;
    }

    /*
     * Make sure the chunked buffers preserve the alignment of the buffers
     * originally created. If Memory_DEFAULTALIGNMENT has been used, we have
     * no way of knowing which alignment was actually used since the value is
     * -1 and means different things on different operating systems. In this
     * case we use the most conservative setting which is page alignment on
     * Linux ARM.
     */
    alignment = hBufTab->hBufs[0]->memParams.align == Memory_DEFAULTALIGNMENT ?
        PAGE_ALIGN : hBufTab->hBufs[0]->memParams.align;

    if (bufSize & ~(alignment - 1)) {
        alignedSize = (bufSize & ~(alignment - 1)) + alignment;
    }
    else {
        alignedSize = bufSize;
    }

    Dmai_dbg5("Trying to chunk BufTab with %d buffers of size %u aligned on %u "
              "to %d buffers of size %u\n", BufTab_getNumBufs(hBufTab),
              (Uns) _Buffer_getOriginalSize(BufTab_getBuf(hBufTab, 0)), (Uns) alignment,
              numBufs, (Uns) bufSize);

    Buffer_getAttrs(hBufTab->hBufs[0], BufferGfx_getBufferAttrs(&gfxAttrs));
    gfxAttrs.bAttrs.reference = TRUE;

    /* Save the original BufTab state */
    hBufTab->hOrigBufs   = hBufTab->hBufs;
    hBufTab->origNumBufs = hBufTab->numBufs;

    /* Allocate new Buffer handles */
    hBufTab->hBufs = (Buffer_Handle*)calloc(numBufs, sizeof(Buffer_Handle));

    if (hBufTab->hBufs == NULL) {
        Dmai_err0("Failed to allocate space for Buffer Handles\n");
        return Dmai_ENOMEM;
    }

    /* Chunk up the old buffers for new buffer requirements */
    for (bufIdxOld = 0; bufIdxOld < hBufTab->origNumBufs; bufIdxOld++) {
        hOldBuf = hBufTab->hOrigBufs[bufIdxOld];

        if (Buffer_getUseMask(hOldBuf)) {
            hBufTab->hBufs[bufIdxNew++] = hOldBuf;
        }
        else {
            virtPtr = Buffer_getUserPtr(hOldBuf);
            oldSize = _Buffer_getOriginalSize(hOldBuf);
            numBytes = 0;

            while (bufIdxNew < numBufs &&
                   numBytes + bufSize < oldSize) {

                hNewBuf = Buffer_create(bufSize,
                                        BufferGfx_getBufferAttrs(&gfxAttrs));

                if (hNewBuf == NULL) {
                    Dmai_err0("Failed to allocate Buffer Object\n");
                    return Dmai_ENOMEM;
                }

                Buffer_setUserPtr(hNewBuf, virtPtr);
                _Buffer_setId(hNewBuf, bufIdxNew);
                _Buffer_setBufTab(hNewBuf, hBufTab);

                hBufTab->hBufs[bufIdxNew] = hNewBuf;
                virtPtr += alignedSize;
                numBytes += alignedSize;

                bufIdxNew++;
            }
        }

        if (bufIdxNew == numBufs) {
            break;
        }
    }

    Dmai_dbg2("New chunked BufTab has %d buffers, still need %d buffers\n",
              bufIdxNew, numBufs - bufIdxNew);

    hBufTab->numBufs = bufIdxNew;

    return numBufs - bufIdxNew;
}

/******************************************************************************
 * BufTab_collapse
 ******************************************************************************/
Int BufTab_collapse(BufTab_Handle hBufTab)
{
    Int dupe, bufIdx, oldBufIdx;

    assert(hBufTab);

    if (hBufTab->hOrigBufs) {
        for (bufIdx = 0; bufIdx < hBufTab->numBufs; bufIdx++) {
            dupe = FALSE;

            for (oldBufIdx = 0; oldBufIdx < hBufTab->origNumBufs; oldBufIdx++) {
                if (hBufTab->hOrigBufs[oldBufIdx] == hBufTab->hBufs[bufIdx]) {
                    dupe = TRUE;
                }
            }

            if (!dupe) {
                if (!hBufTab->hBufs[bufIdx]->reference) {
                    Buffer_delete(hBufTab->hBufs[bufIdx]);
                }
                else {
                    free(hBufTab->hBufs[bufIdx]);
                }
            }
        }

        free(hBufTab->hBufs);

        hBufTab->hBufs = hBufTab->hOrigBufs;
        hBufTab->numBufs = hBufTab->origNumBufs;
        hBufTab->hOrigBufs = NULL;
        hBufTab->origNumBufs = 0;
    }

    return Dmai_EOK;
}

/******************************************************************************
 * BufTab_print
 ******************************************************************************/
Void BufTab_print(BufTab_Handle hBufTab)
{
    Int bufIdx;

    assert(hBufTab);

    printf("BufTab:\n");
    for (bufIdx = 0; bufIdx < BufTab_getNumBufs(hBufTab); bufIdx++) {
        Buffer_print(BufTab_getBuf(hBufTab, bufIdx));
    }
    printf("\n");
}

/******************************************************************************
 * BufTab_freeAll
 ******************************************************************************/
Void BufTab_freeAll(BufTab_Handle hBufTab)
{
    Buffer_Handle hBuf;
    Int bufIdx;

    assert(hBufTab);

    for (bufIdx = 0; bufIdx < BufTab_getNumBufs(hBufTab); bufIdx++) {
        hBuf = BufTab_getBuf(hBufTab, bufIdx);
        Buffer_setUseMask(hBuf, 0);
    }
}

/******************************************************************************
 * BufTab_getFreeBuf
 ******************************************************************************/
Buffer_Handle BufTab_getFreeBuf(BufTab_Handle hBufTab)
{
    Int bufIdx;
    UInt16 useMask;

    assert(hBufTab);

    for (bufIdx = 0; bufIdx < hBufTab->numBufs; bufIdx++) {
        useMask = Buffer_getUseMask(hBufTab->hBufs[bufIdx]);
        if (!useMask) {
            Buffer_resetUseMask(hBufTab->hBufs[bufIdx]);
            break;
        }
    }

    if (bufIdx == hBufTab->numBufs) {
        return NULL;
    }

    return BufTab_getBuf(hBufTab, bufIdx);
}

/******************************************************************************
 * BufTab_getBuf
 ******************************************************************************/
Buffer_Handle BufTab_getBuf(BufTab_Handle hBufTab, Int bufIdx)
{
    assert(hBufTab);

    return hBufTab->hBufs[bufIdx];
}

/******************************************************************************
 * BufTab_getNumBufs
 ******************************************************************************/
Int BufTab_getNumBufs(BufTab_Handle hBufTab)
{
    assert(hBufTab);

    return hBufTab->numBufs;
}

/******************************************************************************
 * BufTab_freeBuf
 ******************************************************************************/
Void BufTab_freeBuf(Buffer_Handle hBuf)
{
    assert(hBuf);

    Buffer_setUseMask(hBuf, 0);
}

/******************************************************************************
 * BufTab_delete
 ******************************************************************************/
Int BufTab_delete(BufTab_Handle hBufTab)
{
    Int ret = Dmai_EOK;

    if (hBufTab) {
        ret = cleanup(hBufTab);
    }

    return ret;
}

