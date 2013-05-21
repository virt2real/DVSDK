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
#include <ti/sdo/dmai/VideoStd.h>
#include <ti/sdo/dmai/BufferGfx.h>

#include "priv/_Buffer.h"

#define MODULE_NAME     "BufferGfx"

const BufferGfx_Attrs BufferGfx_Attrs_DEFAULT = {
    {
        Buffer_Memory_Params_DEFAULT_DEFINE,
        Buffer_Type_GRAPHICS,
        1
    },
    ColorSpace_NOTSET,
    {
        0, 0, 0, 0, 0
    }
};

/******************************************************************************
 * _BufferGfx_getObjectPtr (INTERNAL)
 ******************************************************************************/
_BufferGfx_Object *_BufferGfx_getObjectPtr(Buffer_Handle hBuf)
{
    assert(hBuf);

    if (hBuf->type != Buffer_Type_GRAPHICS) {
        return NULL;
    }

    return (_BufferGfx_Object *) hBuf;
}

/******************************************************************************
 * BufferGfx_getBufferAttrs
 ******************************************************************************/
Buffer_Attrs *BufferGfx_getBufferAttrs(BufferGfx_Attrs *gfxAttrs)
{
    if (gfxAttrs->bAttrs.type != Buffer_Type_GRAPHICS) {
        return NULL;
    }

    return (Buffer_Attrs *) gfxAttrs;
}

/******************************************************************************
 * BufferGfx_calcSize
 ******************************************************************************/
Int32 BufferGfx_calcSize(VideoStd_Type videoStd,
                         ColorSpace_Type colorSpace)
{
    BufferGfx_Dimensions dim;

    if (VideoStd_getResolution(videoStd, &dim.width, &dim.height) < 0) {
        return Dmai_EINVAL;
    }

    dim.lineLength = BufferGfx_calcLineLength(dim.width, colorSpace);

    if (dim.lineLength < 0) {
        return dim.lineLength;
    }

    return BufferGfx_calcSizeDim(&dim, colorSpace);
}

/******************************************************************************
 * BufferGfx_calcSizeDim
 ******************************************************************************/
Int32 BufferGfx_calcSizeDim(BufferGfx_Dimensions *dimPtr,
                            ColorSpace_Type colorSpace)
{
    Int32 bufSize;

    if (colorSpace == ColorSpace_YUV422PSEMI) {
        bufSize = dimPtr->lineLength * dimPtr->height * 2;
    }
    else if (colorSpace == ColorSpace_YUV420PSEMI || 
             colorSpace == ColorSpace_YUV420P) {
        bufSize = dimPtr->lineLength * dimPtr->height * 3 / 2;
    }
    else {
        bufSize = dimPtr->lineLength * dimPtr->height;
    }

    return bufSize;
}

/******************************************************************************
 * BufferGfx_calcDimensions
 ******************************************************************************/
Int BufferGfx_calcDimensions(VideoStd_Type videoStd,
                             ColorSpace_Type colorSpace,
                             BufferGfx_Dimensions *dimPtr)
{
    assert(dimPtr);

    if (VideoStd_getResolution(videoStd, &dimPtr->width, &dimPtr->height) < 0) {
        return Dmai_EINVAL;
    }

    dimPtr->lineLength = BufferGfx_calcLineLength(dimPtr->width, colorSpace);

    if (dimPtr->lineLength < 0) {
        return dimPtr->lineLength;
    }

    dimPtr->x = 0;
    dimPtr->y = 0;

    return Dmai_EOK;
}

/******************************************************************************
 * BufferGfx_resetDimensions
 ******************************************************************************/
Void BufferGfx_resetDimensions(Buffer_Handle hBuf)
{
    BufferGfx_Dimensions dim;

    assert(hBuf);

    Dmai_clear(dim);

    BufferGfx_setDimensions(hBuf, &dim);
}

/******************************************************************************
 * BufferGfx_calcLineLength
 ******************************************************************************/
Int32 BufferGfx_calcLineLength(Int32 width, ColorSpace_Type colorSpace)
{
    Int bpp = ColorSpace_getBpp(colorSpace);

    if (bpp < 0) {
        return bpp;
    }

    return width * bpp / 8;
}

/******************************************************************************
 * BufferGfx_getFrameType
 ******************************************************************************/

Int32 BufferGfx_getFrameType(Buffer_Handle hBuf)
{
    _BufferGfx_Object *gfxObjectPtr = _BufferGfx_getObjectPtr(hBuf); 

    assert(gfxObjectPtr);

    return gfxObjectPtr->frameType;
}

/******************************************************************************
 * BufferGfx_setFrameType
 ******************************************************************************/
Void BufferGfx_setFrameType(Buffer_Handle hBuf, Int32 frameType)
{
    _BufferGfx_Object *gfxObjectPtr = _BufferGfx_getObjectPtr(hBuf);

    assert(gfxObjectPtr);

    gfxObjectPtr->frameType = frameType;
}

/******************************************************************************
 * BufferGfx_getColorSpace
 ******************************************************************************/
ColorSpace_Type BufferGfx_getColorSpace(Buffer_Handle hBuf)
{
    _BufferGfx_Object *gfxObjectPtr = _BufferGfx_getObjectPtr(hBuf);

    assert(gfxObjectPtr);

    return gfxObjectPtr->colorSpace;
}

/******************************************************************************
 * BufferGfx_setColorSpace
 ******************************************************************************/
Void BufferGfx_setColorSpace(Buffer_Handle hBuf, ColorSpace_Type colorSpace)
{
    _BufferGfx_Object *gfxObjectPtr = _BufferGfx_getObjectPtr(hBuf);

    assert(gfxObjectPtr);

    gfxObjectPtr->colorSpace = colorSpace;
}

/******************************************************************************
 * BufferGfx_getDimensions
 ******************************************************************************/
Void BufferGfx_getDimensions(Buffer_Handle hBuf,
                              BufferGfx_Dimensions *dimPtr)
{
    _BufferGfx_Object *gfxObjectPtr = _BufferGfx_getObjectPtr(hBuf);

    assert(gfxObjectPtr);
    assert(dimPtr);

    if (gfxObjectPtr->usedDim.width == 0 &&
        gfxObjectPtr->usedDim.height == 0 &&
        gfxObjectPtr->usedDim.lineLength == 0) {

        *dimPtr = gfxObjectPtr->origDim;
    }
    else {
        *dimPtr = gfxObjectPtr->usedDim;
    }
}

/******************************************************************************
 * BufferGfx_setDimensions
 ******************************************************************************/
Int BufferGfx_setDimensions(Buffer_Handle hBuf, BufferGfx_Dimensions *dimPtr)
{
    _BufferGfx_Object *gfxObjectPtr = _BufferGfx_getObjectPtr(hBuf);

    assert(gfxObjectPtr);
    assert(dimPtr);

    gfxObjectPtr->usedDim = *dimPtr;

    return Dmai_EOK;
}

/******************************************************************************
 * BufferGfx_setMaxDimensions
 ******************************************************************************/
Int BufferGfx_setMaxDimensions(Buffer_Handle hBuf, BufferGfx_Dimensions *dimPtr)
{
    _BufferGfx_Object *gfxObjectPtr = _BufferGfx_getObjectPtr(hBuf);

    assert(gfxObjectPtr);
    assert(dimPtr);

    if (!hBuf->reference) {
        return Dmai_EINVAL;
    }

    gfxObjectPtr->origDim = *dimPtr;

    return Dmai_EOK;
}

/******************************************************************************
 * _BufferGfx_setFrameDone (INTERNAL)
 ******************************************************************************/
Void _BufferGfx_setFrameDone(Buffer_Handle hBuf, Int16 frameDone)
{
    _BufferGfx_Object *gfxObjectPtr = _BufferGfx_getObjectPtr(hBuf);

    assert(gfxObjectPtr);

    gfxObjectPtr->frameDone = frameDone;
}

/******************************************************************************
 * _BufferGfx_toggleFrameDone (INTERNAL)
 ******************************************************************************/
Void _BufferGfx_toggleFrameDone(Buffer_Handle hBuf)
{
    _BufferGfx_Object *gfxObjectPtr = _BufferGfx_getObjectPtr(hBuf);

    assert(gfxObjectPtr);

    gfxObjectPtr->frameDone ^= 1;
}

/******************************************************************************
 * _BufferGfx_getFrameDone (INTERNAL)
 ******************************************************************************/
Int16 _BufferGfx_getFrameDone(Buffer_Handle hBuf)
{
    _BufferGfx_Object *gfxObjectPtr = _BufferGfx_getObjectPtr(hBuf);

    assert(gfxObjectPtr);

    return gfxObjectPtr->frameDone;
}

/******************************************************************************
 * _BufferGfx_getObjectPtr (INTERNAL)
 ******************************************************************************/
Void _BufferGfx_init(Buffer_Handle hBuf, Buffer_Attrs *attrs)
{
    _BufferGfx_Object *gfxObjPtr = _BufferGfx_getObjectPtr(hBuf);
    BufferGfx_Attrs *gfxAttrs = (BufferGfx_Attrs *) attrs;

    assert(gfxObjPtr);

    gfxObjPtr->frameDone = 1;
    gfxObjPtr->colorSpace = gfxAttrs->colorSpace;
    gfxObjPtr->origDim = gfxAttrs->dim;
    gfxObjPtr->origDim.x = 0;
    gfxObjPtr->origDim.y = 0;
}

/******************************************************************************
 * _BufferGfx_getAttrs (INTERNAL)
 ******************************************************************************/
Void _BufferGfx_getAttrs(Buffer_Handle hBuf, Buffer_Attrs *attrs)
{
    _BufferGfx_Object *gfxObjPtr = _BufferGfx_getObjectPtr(hBuf);
    BufferGfx_Attrs *gfxAttrs = (BufferGfx_Attrs *) attrs;

    assert(gfxObjPtr);

    gfxAttrs->colorSpace    = gfxObjPtr->colorSpace;
    gfxAttrs->dim           = gfxObjPtr->origDim;
}

