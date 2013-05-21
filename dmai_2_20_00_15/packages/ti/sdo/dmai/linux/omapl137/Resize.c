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

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Resize.h>
#include <ti/sdo/dmai/BufferGfx.h>

#define MODULE_NAME     "Resize"

const Resize_Attrs Resize_Attrs_DEFAULT = {
    0,
};

typedef struct Resize_Object {
    Int fd;
} Resize_Object;

/******************************************************************************
 * Resize_create
 ******************************************************************************/
Resize_Handle Resize_create(Resize_Attrs *attrs)
{
    return NULL;
}

/******************************************************************************
 * Resize_config
 ******************************************************************************/
Int Resize_config(Resize_Handle hResize,
                  Buffer_Handle hSrcBuf, Buffer_Handle hDstBuf)
{
    return Dmai_ENOTIMPL;
}

/******************************************************************************
 * Resize_execute
 ******************************************************************************/
Int Resize_execute(Resize_Handle hResize,
                   Buffer_Handle hSrcBuf, Buffer_Handle hDstBuf)
{
    return Dmai_ENOTIMPL;
}

/******************************************************************************
 * Resize_delete
 ******************************************************************************/
Int Resize_delete(Resize_Handle hResize)
{
    return Dmai_ENOTIMPL;
}
