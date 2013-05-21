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

#ifdef CONFIG_INPUT_DM355EVM
#include "ti/sdo/dmai/linux/priv/_Event.h"
#endif

#include <ti/sdo/dmai/Ir.h>

#define MODULE_NAME     "Ir"

/******************************************************************************
 * Ir_create
 ******************************************************************************/
Ir_Handle Ir_create(Ir_Attrs *attrs)
{
#ifdef CONFIG_INPUT_DM355EVM
    return (_Event_Ir_create(attrs));
#else
    Dmai_err0("not implemented\n");
    return NULL;
#endif
}

/******************************************************************************
 * Ir_getKey
 ******************************************************************************/
Int Ir_getKey(Ir_Handle hIr, Ir_Key *key)
{
#ifdef CONFIG_INPUT_DM355EVM
    return (_Event_Ir_getKey(hIr, key));
#else
    Dmai_err0("not implemented\n");
    return Dmai_ENOTIMPL;
#endif
}

/******************************************************************************
 * Ir_delete
 ******************************************************************************/
Int Ir_delete(Ir_Handle hIr)
{
#ifdef CONFIG_INPUT_DM355EVM
    return(_Event_Ir_delete(hIr));
#else
    Dmai_err0("not implemented\n");
    return Dmai_ENOTIMPL;
#endif
}

