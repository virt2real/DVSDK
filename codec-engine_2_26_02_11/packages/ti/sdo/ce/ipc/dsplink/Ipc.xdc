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
 *  ======== Settings ========
 *  Dsplink ipc Settings.
 */
@Template("./Ipc.xdt")

metaonly module Ipc inherits ti.sdo.ce.ipc.IIpc {

    /*!
     *  ======== maxTimeout ========
     *  Maximum timeout allowed.
     *
     *  Users can specify a value here to indicate a 'cap' on the time
     *  which the IPC APIs in this package will wait before timing out.
     *  If the 'maxTimeout' value is encountered in a running system, it
     *  is treated as a system error.  Resources will be unlocked (e.g.
     *  MSGQ_pend() will return, releasing any DSP Link resources), and
     *  the thread that exceeded its maxTimeout will spin forever, never
     *  returning.  It will need to be deleted by another "monitor process".
     *
     *  This can be used in a system to detect if a remote processor has
     *  become unresponsive.
     *
     *  The default is 0xffffffff, which indicates that there is no cap and
     *  the underyling APIs can wait forever if so instructed.
     */
    config UInt32 maxTimeout = 0xffffffff;

    /*!
     *  ======== dspLinkCfg ========
     *  Use a specific DspLink configuration. This parameter does not need
     *  to be set if using the DspLinkCfg provided with Codec Engine.
     *  This parameter provides a default memory map and power control
     *  settings for supported platforms.
     */
    config IDspLinkCfg.Module dspLinkCfg;

    /*!
     *  ======== armCommMsgSize ========
     *  Default size for the Arm-DSP communication messages (MSGQ messages).
     */
    config UInt32 armCommMsgSize = 4 * 1024;

    /*!
     *  ======== armCommNumMsgs ========
     *  Number of <commMsgSize>-sized messages used for Arm-DSP communication.
     */
    config UInt32 armCommNumMsgs = 64;

    /*!
     *  ======== commLocateRetries ========
     *  number of times to retry Comm_locate() -- to find DSP server's MSGQ --
     *  before giving up.
     */
    config int commLocateRetries = 20;

    /*!
     *  ======== useLinkArbiter ========
     *  Control flag to indicate if Codec Engine should use the Link Arbiter
     *  Daemon (LAD) to arbitrate DSPLINK APIs that need arbitration.  Set to
     *  false means LAD should not be used; set to true means LAD should be
     *  used.
     *
     *  This feature may not be available on all devices.
     */
    config Bool useLinkArbiter = false;

    /*!
     *  ======== usePowerManagement ========
     *  If set to true, will attempt to include power-management code
     *  where applicable. If left undefined, an appropriate default value
     *  will be assigned based on the device type.
     *
     *  This feature may not be available on all devices.
     */
    config bool usePowerManagement;


    /*!
     *  ======== debug ========
     *  Enable the debug profile of the dsplink ipc module.
     */
    config Bool debug = false;
}
/*
 *  @(#) ti.sdo.ce.ipc.dsplink; 2, 0, 1,182; 12-2-2010 21:24:21; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

