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
#ifndef _GROUPUTILS_H
#define _GROUPUTILS_H


/**
 *  @brief      Opaque handle to a Sem object.
 */
typedef struct SemMP_Obj *SemMP_Handle;

extern SemMP_Handle SemMP_create(Int key, Int count);

extern Void SemMP_delete(SemMP_Handle sem);

extern Int SemMP_pend(SemMP_Handle sem, UInt32 timeout);

extern Void SemMP_post(SemMP_Handle sem);

extern UInt32 _GROUPUTILS_ipcKeyBase;

/*
 * Internal state that can be used for resource book-keeping 
 */
typedef struct IRES_GROUPUTILS_InternalState {

    int size;
} IRES_GROUPUTILS_InternalState;

/* Id offset from _GROUPUTILS_ipcKeyBase to shared memory containing GROUPUTILS 
   object */
#define _GROUPUTILS_SHMID (_GROUPUTILS_ipcKeyBase)
 
/* Id offset from _GROUPUTILS_ipcKeyBase to semaphore used for critical sections*/
#define _GROUPUTILS_CSID (_GROUPUTILS_ipcKeyBase + 1)
 
/* Id offset from _GROUPUTILS_ipcKeyBase to lock used for protecting GROUPUTILS 
   object */
#define _GROUPUTILS_LOCKID (_GROUPUTILS_ipcKeyBase + 2)

/* Id offset from _GROUPUTILS_ipcKeyBase to semaphore used for managing 
   GROUPUTILS memory resources */
#define _GROUPUTILS_MEMID (_GROUPUTILS_ipcKeyBase + 3)


#endif /* _GROUPUTILS_H */
/*
 *  @(#) ti.sdo.fc.ires.grouputils; 1, 0, 0,32; 12-1-2010 17:25:14; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

