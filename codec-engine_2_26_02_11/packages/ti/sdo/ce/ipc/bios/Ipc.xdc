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
 *  ======== Ipc ========
 *  BIOS ipc settings.
 */
@Template("./Ipc.xdt")

metaonly module Ipc inherits ti.sdo.ce.ipc.IIpc {
    /*!
     *  ======== armCommMsgSize ========
     *  Default size for the Arm-DSP communication messages (MSGQ messages).
     *
     *  Applies only to configurations where DSP Link is used.
     */
    config UInt32 armCommMsgSize = 4 * 1024;

    /*!
     *  ======== dspConfigureMsgqAndPool ========
     *  Set to true by default, instructs this module to generate code that
     *  configures BIOS MSGQ and POOL modules: symbols MSGQ_config and
     *  POOL_config. If set to false, and if BIOS is configured to use MSGQ,
     *  user application must define these symbols.
     */
    config bool dspConfigureMsgqAndPool = true;

    /*!
     *  ======== dspUseMsgqAndPool ========
     *  If set to false, instructs Codecs Engine to cut out MSGQ and POOL
     *  references completely from the final image.
     *
     *  Must be set to true if DSP Link is used.
     */
    config bool dspUseMsgqAndPool = true;

    /*!
     *  ======== dspCommNumMsgQueues ========
     *  Number of message queues (that can receive and store messages) on the
     *  DSP side. Each DSP node (task) needs one message queue.
     *
     *  Applies only to configurations where runtimeEnv == DSPBIOS or
     *  runtimeEnv == DSPLINK_BIOS
     */
    config UInt32 dspCommNumMsgQueues = 64;

    /*!
     *  ======== dspCommUseExactMatch ========
     *  Indicates that "exact match" must be used for comm messages allocated
     *  on the DSP side.
     *
     *  Applies only to configurations where DSP Link is used.
     */
    config Bool dspCommUseExactMatch = true;

    /*!
     *  ======== dspCommMsgSize ========
     *  Default size for the inter-DSP communication messages (MSGQ messages).
     *
     *  Applies only to configurations where DSP Link is not used, in special
     *  circumstances.
     * @_nodoc
     */
    config UInt32 dspCommMsgSize = 1024;

    /*!
     *  ======== dspCommNumMsgs ========
     *  Number of <commMsgSize>-sized messages used for Arm-DSP communication.
     *
     *  Applies only to configurations where DSP Link is not used, in special
     *  circumstances.
     * @_nodoc
     */
    config UInt32 dspCommNumMsgs = 64;

    /*!
     *  ======== usePowerManagement ========
     *  Enable power Management
     *
     *  If set to true, will attempt to include power-management code
     *  where applicable.
     *
     *  This feature may not be available on all devices.
     */
    config bool usePowerManagement = false;

    /*!
     *  ======== powerSaveMemoryBlockName ========
     *  Memory segment name for context save/restore.
     *
     *  The name of the segment to which power should be saved; if left null,
     *  will default to defaultMemSegId.
     *
     *  This feature may not be available on all devices.
     */
    config String powerSaveMemoryBlockName = null;

    /*!
     *  ======== debug ========
     *  Enable the debug profile
     *
     *  Now obsolete. Leave here for awhile until users update.
     *  @_nodoc
     */
    config Bool debug = false;

    /*!
     * ======== dspLinkUsed ========
     * Returns true if the executable should be built with DSP Link
     *
     * @_nodoc
     */
    bool dspLinkUsed();

}
/*
 *  @(#) ti.sdo.ce.ipc.bios; 2, 0, 1,179; 12-2-2010 21:24:02; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

