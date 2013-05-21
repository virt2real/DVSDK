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

#ifndef ti_sdo_dmai__Buffer_h_
#define ti_sdo_dmai__Buffer_h_

#include <xdc/std.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/BufTab.h>
#include <ti/sdo/dmai/BufferGfx.h>
#include <ti/sdo/dmai/VideoStd.h>
#include <ti/sdo/dmai/ColorSpace.h>

#define Buffer_Memory_Params_DEFAULT_DEFINE {   \
    Memory_CONTIGPOOL,                          \
    Memory_NONCACHED,                           \
    Memory_DEFAULTALIGNMENT,                    \
    0                                           \
}

typedef struct _Buffer_State {
    Int32                   numBytes;
    UInt16                  useMask;
} _Buffer_State;

typedef struct _Buffer_Object {
    Buffer_Type             type;
    _Buffer_State           origState;
    _Buffer_State           usedState;
    Memory_AllocParams      memParams;
    Int8                   *userPtr;
    Int32                   physPtr;
    Int                     id;
    Bool                    reference;
    BufTab_Handle           hBufTab;
    Int32                   virtualBufferSize;
} _Buffer_Object;

typedef struct _BufferGfx_Object {
    _Buffer_Object          buf;
    BufferGfx_Dimensions    origDim;
    BufferGfx_Dimensions    usedDim;
    Int16                   frameDone;
    Int32                   frameType;
    ColorSpace_Type         colorSpace;
} _BufferGfx_Object;

#if defined (__cplusplus)
extern "C" {
#endif

extern Void _Buffer_setId(Buffer_Handle hBuf, Int id);
extern Void _Buffer_setBufTab(Buffer_Handle hBuf, BufTab_Handle hBufTab);
extern Int32 _Buffer_getOriginalSize(Buffer_Handle hBuf);

extern Void _BufferGfx_getAttrs(Buffer_Handle hBuf, Buffer_Attrs *attrs);
extern Void _BufferGfx_init(Buffer_Handle hBuf, Buffer_Attrs *attrs);
extern Void _BufferGfx_setFrameDone(Buffer_Handle hBuf, Int16 frameDone);
extern Void _BufferGfx_toggleFrameDone(Buffer_Handle hBuf);
extern Int16 _BufferGfx_getFrameDone(Buffer_Handle hBuf);

#if defined (__cplusplus)
}
#endif

#endif // ti_sdo_dmai__Buffer_h_
