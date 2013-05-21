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
 *  ======== Lock.h ========
 */

#ifndef ti_sdo_ce_osal_Lock_
#define ti_sdo_ce_osal_Lock_

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== Lock_Handle ========
 */
typedef struct Lock_Obj *Lock_Handle;

/*
 *  ======== Lock_Attrs ========
 */
typedef struct Lock_Attrs {
    Int         type;       /* lock type */
} Lock_Attrs;

extern Lock_Attrs Lock_ATTRS;     /* default attributes */

/*
 *  ======== Lock_system ========
 */
extern Lock_Handle Lock_system;

/*
 *  ======== Lock_acquire ========
 */
extern Void Lock_acquire(Lock_Handle lock);

/*
 *  ======== Lock_create ========
 */
extern Lock_Handle Lock_create(Lock_Attrs *attrs);

/*
 *  ======== Lock_delete ========
 */
extern Void Lock_delete(Lock_Handle lock);

/*
 *  ======== Lock_init ========
 */
extern Void Lock_init(Void);

/*
 *  ======== Lock_release ========
 */
extern Void Lock_release(Lock_Handle lock);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif
/*
 *  @(#) ti.sdo.ce.osal; 2, 0, 2,427; 12-2-2010 21:24:38; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

