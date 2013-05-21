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

#include <ti/sdo/ce/osal/Memory.h>

#include "priv/_Buffer.h"

#define MODULE_NAME     "Buffer"

const Memory_AllocParams Buffer_Memory_Params_DEFAULT =
        Buffer_Memory_Params_DEFAULT_DEFINE;

const Buffer_Attrs Buffer_Attrs_DEFAULT = {
    Buffer_Memory_Params_DEFAULT_DEFINE,
    Buffer_Type_BASIC,
    1,
    FALSE
};

/******************************************************************************
 * _Buffer_init
 ******************************************************************************/
static Void _Buffer_init(Buffer_Handle hBuf, Int32 size, Buffer_Attrs *attrs)
{
    hBuf->memParams             = attrs->memParams;
    hBuf->type                  = attrs->type;

    hBuf->origState.useMask     = attrs->useMask;
    hBuf->origState.numBytes    = size;

    if (attrs->type == Buffer_Type_GRAPHICS) {
        _BufferGfx_init(hBuf, attrs);
    }
}

/******************************************************************************
 * Buffer_create
 ******************************************************************************/
Buffer_Handle Buffer_create(Int32 size, Buffer_Attrs *attrs)
{
    Buffer_Handle hBuf;
    UInt32        objSize;

    if (attrs == NULL) {
        Dmai_err0("Must provide attrs\n");
        return NULL;
    }

    if (attrs->type != Buffer_Type_BASIC &&
        attrs->type != Buffer_Type_GRAPHICS) {

        Dmai_err1("Unknown Buffer type (%d)\n", attrs->type);
        return NULL;
    }

    objSize = attrs->type == Buffer_Type_GRAPHICS ? sizeof(_BufferGfx_Object) :
                                                    sizeof(_Buffer_Object);

    hBuf = (Buffer_Handle) calloc(1, objSize);

    if (hBuf == NULL) {
        Dmai_err0("Failed to allocate space for Buffer Object\n");
        return NULL;
    }

    _Buffer_init(hBuf, size, attrs);

    if (!attrs->reference) {
        hBuf->userPtr = (Int8*)Memory_alloc(size, &attrs->memParams);

        if (hBuf->userPtr == NULL) {
            printf("Failed to allocate memory.\n");
            free(hBuf);
            return NULL;
        }

        hBuf->physPtr = Memory_getBufferPhysicalAddress(hBuf->userPtr,
                                                        size, NULL);

        Dmai_dbg3("Alloc Buffer of size %u at 0x%x (0x%x phys)\n",
                  (Uns) size, (Uns) hBuf->userPtr, (Uns) hBuf->physPtr);
    }

    hBuf->reference = attrs->reference;

    return hBuf;
}

/******************************************************************************
 * Buffer_getAttrs
 ******************************************************************************/
Void Buffer_getAttrs(Buffer_Handle hBuf, Buffer_Attrs *attrs)
{
    assert(hBuf);
    assert(attrs);

    if (hBuf->type == Buffer_Type_GRAPHICS) {
        _BufferGfx_getAttrs(hBuf, attrs);
    }

    attrs->memParams            = hBuf->memParams;
    attrs->type                 = hBuf->type;
    attrs->useMask              = hBuf->origState.useMask;
}

/******************************************************************************
 * Buffer_clone
 ******************************************************************************/
Buffer_Handle Buffer_clone(Buffer_Handle hBuf)
{
    BufferGfx_Attrs     gfxAttrs = BufferGfx_Attrs_DEFAULT;
    Buffer_Handle       hNewBuf;

    Buffer_getAttrs(hBuf, BufferGfx_getBufferAttrs(&gfxAttrs));

    hNewBuf = Buffer_create(hBuf->origState.numBytes,
                            BufferGfx_getBufferAttrs(&gfxAttrs));

    if (hNewBuf == NULL) {
        Dmai_err0("Failed to create new Buffer while cloning\n");
        return NULL;
    }

    return hNewBuf;
}

/******************************************************************************
 * Buffer_print
 ******************************************************************************/
Void Buffer_print(Buffer_Handle hBuf)
{
    printf("[%d] @ 0x%x (0x%x phys) numBytes %d (%d) useMask %u (%u) ref %s"
           " vSize %d\n",
               hBuf->id, (Uns) hBuf->userPtr, (Uns) hBuf->physPtr,
               (Int)hBuf->usedState.numBytes, (Int)hBuf->origState.numBytes,
               hBuf->usedState.useMask, hBuf->origState.useMask,
               hBuf->reference ? "yes" : "no", (Int)hBuf->virtualBufferSize);

    if (hBuf->type == Buffer_Type_GRAPHICS) {
        _BufferGfx_Object *gfxObjectPtr = (_BufferGfx_Object *) hBuf;

        if (gfxObjectPtr->usedDim.width == 0 ||
            gfxObjectPtr->usedDim.height == 0 ||
            gfxObjectPtr->usedDim.lineLength == 0) {

            printf("\tWidth %d, Height %d, LineLength %d\n",
                   (Int) gfxObjectPtr->origDim.width,
                   (Int) gfxObjectPtr->origDim.height,
                   (Int) gfxObjectPtr->origDim.lineLength);
        }
        else {
            printf("\tWidth %d (%d) Height %d (%d) Pos %dx%d "
                   "LineLength %d (%d)\n",
                   (Int) gfxObjectPtr->usedDim.width,
                   (Int) gfxObjectPtr->origDim.width,
                   (Int) gfxObjectPtr->usedDim.height,
                   (Int) gfxObjectPtr->origDim.height,
                   (Int) gfxObjectPtr->usedDim.x,
                   (Int) gfxObjectPtr->usedDim.y,
                   (Int) gfxObjectPtr->usedDim.lineLength,
                   (Int) gfxObjectPtr->origDim.lineLength);
        }
    }
}

/******************************************************************************
 * Buffer_freeUseMask
 ******************************************************************************/
Void Buffer_freeUseMask(Buffer_Handle hBuf, UInt16 useMask)
{
    assert(hBuf);

    hBuf->usedState.useMask &= ~useMask;
}

/******************************************************************************
 * Buffer_setUseMask
 ******************************************************************************/
Void Buffer_setUseMask(Buffer_Handle hBuf, UInt16 useMask)
{
    assert(hBuf);

    hBuf->usedState.useMask = useMask;
}

/******************************************************************************
 * Buffer_resetUseMask
 ******************************************************************************/
Void Buffer_resetUseMask(Buffer_Handle hBuf)
{
    assert(hBuf);

    hBuf->usedState.useMask = hBuf->origState.useMask;
}

/******************************************************************************
 * Buffer_getUseMask
 ******************************************************************************/
UInt16 Buffer_getUseMask(Buffer_Handle hBuf)
{
    assert(hBuf);

    return hBuf->usedState.useMask;
}

/******************************************************************************
 * Buffer_getId
 ******************************************************************************/
Int Buffer_getId(Buffer_Handle hBuf)
{
    assert(hBuf);

    return hBuf->id;
}

/******************************************************************************
 * Buffer_getUserPtr
 ******************************************************************************/
Int8 *Buffer_getUserPtr(Buffer_Handle hBuf)
{
    assert(hBuf);

    return hBuf->userPtr;
}

/******************************************************************************
 * Buffer_getPhysicalPtr
 ******************************************************************************/
Int32 Buffer_getPhysicalPtr(Buffer_Handle hBuf)
{
    assert(hBuf);

    return hBuf->physPtr;
}

/******************************************************************************
 * Buffer_getSize
 ******************************************************************************/
Int32 Buffer_getSize(Buffer_Handle hBuf)
{
    assert(hBuf);

    return (hBuf->virtualBufferSize ? 
        hBuf->virtualBufferSize : hBuf->origState.numBytes);
}

/******************************************************************************
 * Buffer_getSize
 ******************************************************************************/
Int32 _Buffer_getOriginalSize(Buffer_Handle hBuf)
{
    assert(hBuf);

    return hBuf->origState.numBytes;
}

/******************************************************************************
 * Buffer_getType
 ******************************************************************************/
Buffer_Type Buffer_getType(Buffer_Handle hBuf)
{
    assert(hBuf);

    return hBuf->type;
}

/******************************************************************************
 * Buffer_getNumBytesUsed
 ******************************************************************************/
Int32 Buffer_getNumBytesUsed(Buffer_Handle hBuf)
{
    assert(hBuf);

    return hBuf->usedState.numBytes;
}

/******************************************************************************
 * Buffer_setNumBytesUsed
 ******************************************************************************/
Void Buffer_setNumBytesUsed(Buffer_Handle hBuf, Int32 numBytes)
{
    assert(hBuf);

    hBuf->usedState.numBytes = numBytes;
}

/******************************************************************************
 * _Buffer_setId (INTERNAL)
 ******************************************************************************/
Void _Buffer_setId(Buffer_Handle hBuf, Int id)
{
    assert(hBuf);

    hBuf->id = id;
}

/******************************************************************************
 * _Buffer_setBufTab (INTERNAL)
 ******************************************************************************/
Void _Buffer_setBufTab(Buffer_Handle hBuf, BufTab_Handle hBufTab)
{
    assert(hBuf);

    hBuf->hBufTab = hBufTab;
}

/******************************************************************************
 * Buffer_setUserPtr
 ******************************************************************************/
Int Buffer_setUserPtr(Buffer_Handle hBuf, Int8 *ptr)
{
    assert(hBuf);

    if (!hBuf->reference) {
        return Dmai_EINVAL;
    }

    hBuf->userPtr = ptr;

    if (ptr) {
        hBuf->physPtr = Memory_getBufferPhysicalAddress(hBuf->userPtr, 4, NULL);
    }
    else {
        hBuf->physPtr = 0;
    }

    Dmai_dbg2("Set user pointer 0x%x (physical 0x%x)\n",
              (Uns) hBuf->userPtr, (Uns) hBuf->physPtr);

    return Dmai_EOK;
}

/******************************************************************************
 * Buffer_setSize
 ******************************************************************************/
Int Buffer_setSize(Buffer_Handle hBuf, Int32 size)
{
    assert(hBuf);

    if (!hBuf->reference) {
        return Dmai_EINVAL;
    }

    hBuf->origState.numBytes = size;

    return Dmai_EOK;
}

/******************************************************************************
 * Buffer_setVirtualSize
 ******************************************************************************/
Int Buffer_setVirtualSize(Buffer_Handle hBuf, Int32 size)
{
    assert(hBuf);

    hBuf->virtualBufferSize = size;

    return Dmai_EOK;
}

/******************************************************************************
 * Buffer_getBufTab
 ******************************************************************************/
BufTab_Handle Buffer_getBufTab(Buffer_Handle hBuf)
{
    assert(hBuf);

    return hBuf->hBufTab;
}

/******************************************************************************
 * Buffer_isReference
 ******************************************************************************/
Bool Buffer_isReference(Buffer_Handle hBuf)
{
    assert(hBuf);

    return hBuf->reference;
}

/******************************************************************************
 * Buffer_delete
 ******************************************************************************/
Int Buffer_delete(Buffer_Handle hBuf)
{
    Int ret = Dmai_EOK;

    if (hBuf) {
        if (!hBuf->reference && hBuf->userPtr) {
            Dmai_dbg3("Free Buffer of size %u at 0x%x (0x%x phys)\n",
                      (Uns) hBuf->origState.numBytes,
                      (Uns) hBuf->userPtr,
                      (Uns) hBuf->physPtr);

            if (!Memory_free(hBuf->userPtr, hBuf->origState.numBytes,
                             &hBuf->memParams)) {
                ret = Dmai_EFAIL;
            }
        }

        free(hBuf);
    }

    return ret;
}

/******************************************************************************
 * Buffer_copy
 ******************************************************************************/
Int Buffer_copy(Buffer_Handle hSrcBuf, Buffer_Handle hDstBuf)
{
    assert(hSrcBuf);
    assert(hDstBuf);
    assert(hSrcBuf->type == Buffer_Type_BASIC ||
           hSrcBuf->type == Buffer_Type_GRAPHICS);

    if(hSrcBuf->type != hDstBuf->type) {
        Dmai_err1("Cannot copy to Buffer type (%d)\n", hDstBuf->type);
        return Dmai_EFAIL;
    }

    if (!hDstBuf->reference && hDstBuf->userPtr) {
        Dmai_dbg3("Free Buffer of size %u at 0x%x (0x%x phys)\n",
                  (Uns) hDstBuf->origState.numBytes,
                  (Uns) hDstBuf->userPtr,
                  (Uns) hDstBuf->physPtr);

        if (!Memory_free(hDstBuf->userPtr, hDstBuf->origState.numBytes,
                         &hDstBuf->memParams)) {
            return Dmai_EFAIL;
        }
    }

    if(hSrcBuf->type == Buffer_Type_GRAPHICS) {
        *(_BufferGfx_Object *) hDstBuf = *(_BufferGfx_Object *) hSrcBuf;
    } else {
        *(_Buffer_Object *) hDstBuf = *(_Buffer_Object *) hSrcBuf;
    }

    hDstBuf->reference = TRUE;

    return Dmai_EOK;
}

