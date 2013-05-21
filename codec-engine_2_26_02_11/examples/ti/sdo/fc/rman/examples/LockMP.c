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
 *  ======== LockMP_noOS.c ========
 *  Mock implementation of an MP Lock. Replace with CE OSAL in real program 
 */

#include <xdc/std.h>


/*
 *  ======== LockMP_Obj ========
 */
typedef struct LockMP_Obj {
    Int count;
    Int key;
} LockMP_Obj;

typedef LockMP_Obj * LockMP_Handle; 

static LockMP_Obj lockArr[100];

static int index = 0;
 
/*
 *  ======== LockMP_acquire ========
 */
Void LockMP_acquire(LockMP_Handle lock)
{
    int i;
    for (i = 0; i < index; i++) {
        if (lockArr[i].key == lock->key) {
            lockArr[i].count++;
            return;
        }
    } 
    while(1);
}

/*
 *  ======== LockMP_create ========
 */
LockMP_Handle LockMP_create(Int key)
{
    lockArr[index].key = key; 
    lockArr[index].count = 1;
    index++;
    return (&lockArr[index-1]);
}

/*
 *  ======== LockMP_delete ========
 */
/* ARGSUSED */
Void LockMP_delete(LockMP_Handle lock)
{
    int i;
    for (i = 0; i < index; i++) {
        if (&lockArr[i] == lock) {
            lockArr[i].count = 0;
            lockArr[index].key = NULL; 
        }
    }
}

/*
 *  ======== LockMP_getCount ========
 */
/* ARGSUSED */
Int LockMP_getCount(LockMP_Handle lock)
{
    int i;
    for (i = 0; i < index; i++) {
        if (lockArr[i].key == lock->key) {
            return lockArr[i].count;
        }
    } 
    while(1);
}

/*
 *  ======== LockMP_getRefCount ========
 */
Int LockMP_getRefCount(LockMP_Handle lock)
{
    return (LockMP_getCount(lock));
}

/*
 *  ======== LockMP_init ========
 */
Void LockMP_init(Void)
{
}

/*
 *  ======== LockMP_release ========
 */
Void LockMP_release(LockMP_Handle lock)
{
    int i;
    for (i = 0; i < index; i++) {
        if (lockArr[i].key == lock->key) {
            lockArr[i].count--;
            return;
        }
    } 
    while(1);
}

/*
 *  @(#) ti.sdo.fc.rman.examples; 1, 0, 0,123; 12-1-2010 17:25:37; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

