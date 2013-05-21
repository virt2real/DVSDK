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
 * */
/*!
 *  ======== GROUPUTILS ========
 *  Framework Components Edma3 specific IRES Resman and Protocol Implementation
 *
 */
@Template("./GROUPUTILS.xdt")

metaonly module GROUPUTILS {

    /*!
     *  ======== ipcKeyBase ========
     *  Linux only. Base value of keys of Linux IPC objects used by
     *  GROUPUTILS. The IPC objects created by GROUPUTILS will use keys starting 
     *  at this
     *  value, and incrementing with each new object. There are currently
     *  three IPC objects, so keys in the range of ipcKeyBase to ipcKeyBase + 2
     *  will be reserved for GROUPUTILS. The default value of ipcKeyBase is
     *  ascii code for "SLIT".
     *
     *  WARNING: This value should only be changed if it conflicts with
     *  another IPC key in the system that cannot be changed. If this value
     *  is changed, all programs using GROUPUTILS that will be run simultaneously
     *  must have the ipcKeyBase configured to the new value.
     *  @_nodoc
     */
    config UInt ipcKeyBase = 0x534C4954;

    /*  @_nodoc */
    const Bool autoRegister = true;

    /* @_nodoc */
    config bool debug = false;

    /* @_nodoc */
    config bool trace = false;

    /* @_nodoc */
    config String lockScratchGroupFxn = null; 

    /* @_nodoc */
    config String unlockScratchGroupFxn = null; 

    /* We also need a package-name that implements these functions*/ 
    config String scratchFxnPackage = null; 

    /*!
     *  ======== semCreateFxn ========
     * Function to create semaphores used by various individual resource
     * manager(s) registered with RMAN.
     *
     *  Function signature is:
     *  @p(code)
     * Void * _semCreate(Int key, Int count);
     */
    config String semCreateFxn = null;
 
    /*!
     *  ======== semDeleteFxn ========
     * Function to delete semaphores used by various individual resource
     * manager(s) registered with RMAN.
     *
     *  Function signature is:
     *  @p(code)
     *  Void _semDelete(Void * sem);
     */
    config String semDeleteFxn = null;
  
    /*!
     *  ======== semPendFxn ========
     * Function to pend on semaphores used by various resource manager(s)
     * registered with RMAN.
     *
     *  Function signature is:
     *  @p(code)
     *  Int _semPend(Void * sem, UInt32 timeout);
     */
    config String semPendFxn = null;
  
    /*!
     *  ======== semPostFxn ========
     * Function to post on Semaphores used by various resource manager(s)
     * registered with RMAN.
     *
     *  Function signature is:
     *  @p(code)
     * Void _semPost(Void * sem);
     */
    config String semPostFxn = null;
}

/*
 *  @(#) ti.sdo.fc.ires.grouputils; 1, 0, 0,32; 12-1-2010 17:25:14; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

