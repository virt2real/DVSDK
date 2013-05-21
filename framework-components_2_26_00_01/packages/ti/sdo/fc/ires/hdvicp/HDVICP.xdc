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
/*!
 *  ======== HDVICP ========
 *  HDVICP-specific IRES Resman and Protocol Implementation
 *
 */
@Template("./HDVICP.xdt")
 
metaonly module HDVICP {

    /*!
     *  ======== ipcKeyBase ========
     *  Linux only. Base value of keys of Linux IPC objects used by
     *  HDVICP. The IPC objects created by HDVICP will use keys starting 
     *  at this
     *  value, and incrementing with each new object. There are currently
     *  three IPC objects, so keys in the range of ipcKeyBase to ipcKeyBase + 2
     *  will be reserved for HDVICP. The default value of ipcKeyBase is
     *  ascii code for "PCIV".
     *
     *  WARNING: This value should only be changed if it conflicts with
     *  another IPC key in the system that cannot be changed. If this value
     *  is changed, all programs using HDVICP that will be run simultaneously
     *  must have the ipcKeyBase configured to the new value.
     *  @_nodoc
     */
    config UInt ipcKeyBase = 0x49564448;

    /*  @_nodoc */
    const Bool autoRegister = true;

    /*!
     *  ======== debug ========
     *  Enable the debug profile of the library.
     *
     *  This will likely result in a larger and slower library being linked in.
     * @_nodoc
     */
    config bool debug = false;

    /*!
     *  ======== trace ========
     *  Enable trace support
     * @_nodoc
     */
    config bool trace = false;
}
/*
 *  @(#) ti.sdo.fc.ires.hdvicp; 1, 0, 1,133; 12-1-2010 17:25:15; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

