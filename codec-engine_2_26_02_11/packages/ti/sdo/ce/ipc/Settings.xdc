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
 *  Global Inter-Processor Communication Configuration
 */
@Template("./Settings.xdt")

metaonly module Settings {

    /*!
     *  ======== ipc ========
     *  Use a specific IIpc implementation.
     *
     *  This should only be used to explicitly configure the IPC to
     *  a package not provided with Codec Engine.  To use an IPC provided
     *  by Codec Engine, it's recommended to configure the IPC and OSAL
     *  together using the {@link ti.sdo.ce.osal.Global#runtimeEnv} config
     *  param instead of this one.
     *
     *  See {@link http://wiki.davincidsp.com/index.php?title=CE_Config_Updates
     *  for more details}
     */
    config IIpc.Module ipc;

    /*!
     *  ======== CommType ========
     *  Supported types of communication layers that the IPC can be built on:
     *
     *  eg DSPBIOS, DSPLINK, or posix.
     *
     *  Now obsolete. Leave here for awhile until examples, tests are updated.
     *  @_nodoc
     */
    enum CommType {
        COMM_BIOS        = 0,   /*! DSP/BIOS (DSP) */
        COMM_DSPLINKBIOS = 1,   /*! DSPLINK + BIOS (DSP) */
        COMM_DSPLINK     = 2,   /*! DSPLINK (Arm) */
        COMM_POSIX       = 3,   /*! Linux */
        COMM_NONE        = 4    /*! No OS */
    };

    /*!
     *  ======== CommType ========
     *  The type of communication layer that the IPC is built on.
     *
     *  Now obsolete. Leave here for awhile until examples, tests are updated.
     *  @_nodoc
     */
    config CommType commType;

    /*!
     *  ======== usesServer ========
     *  True if building a server. This will be used with osal.Global.os, in
     *  case app did not set commType, to try to figure out what commType
     *  should be set to.
     *
     *  @_nodoc
     */
    config bool usesServer = false;

    /*!
     *  ======== armCommMsgSize ========
     *  Default size for the Arm-DSP communication messages (MSGQ messages).
     *
     *  Applies only to configurations where runtimeEnv == DSPLINK_LINUX or
     *  DSPLINK_BIOS.
     *
     *  Now obsolete. Leave here for awhile until examples, tests are updated.
     *  @_nodoc
     */
    config UInt32 armCommMsgSize = 4 * 1024;

    /*!
     *  ======== armCommNumMsgs ========
     *  Number of <commMsgSize>-sized messages used for Arm-DSP communication.
     *
     *  Applies only to configurations where runtimeEnv == DSPLINK_LINUX
     *
     *  Now obsolete. Leave here for awhile until examples, tests are updated.
     *  @_nodoc
     */
    config UInt32 armCommNumMsgs = 64;

    /*!
     *  ======== commLocateRetries ========
     *  number of times to retry Comm_locate() -- to find DSP server's MSGQ --
     *  before giving up.
     *
     *  Applies only to configurations where runtimeEnv == DSPLINK_LINUX
     *
     *  Now obsolete. Leave here for awhile until examples, tests are updated.
     *  @_nodoc
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
     *
     *  Applies only to configurations where runtimeEnv == DSPLINK_LINUX
     *
     *  Now obsolete. Leave here for awhile until examples, tests are updated.
     *  @_nodoc
     */
    config Bool useLinkArbiter = false;

    /*!
     *  ======== dspConfigureMsgqAndPool ========
     *  Set to true by default, instructs this module to generate code that
     *  configures BIOS MSGQ and POOL modules: symbols MSGQ_config and
     *  POOL_config. If set to false, and if BIOS is configured to use MSGQ,
     *  user application must define these symbols.
     *
     *  Applies only to configurations where runtimeEnv == DSPBIOS or
     *  runtimeEnv == DSPLINK_BIOS
     *
     *  Now obsolete. Leave here for awhile until examples, tests are updated.
     *  @_nodoc
     */
    config bool dspConfigureMsgqAndPool = true;

    /*!
     *  ======== dspUseMsgqAndPool ========
     *  If set to false, instructs Codecs Engine to cut out MSGQ and POOL
     *  references completely from the final image.
     *
     *  Applies only to configurations where runtimeEnv == DSPBIOS.
     *
     *  Now obsolete. Leave here for awhile until examples, tests are updated.
     *  @_nodoc
     */
    config bool dspUseMsgqAndPool = true;

    /*!
     *  ======== dspCommNumMsgQueues ========
     *  Number of message queues (that can receive and store messages) on the
     *  DSP side. Each DSP node (task) needs one message queue.
     *
     *  Applies only to configurations where runtimeEnv == DSPBIOS or
     *  runtimeEnv == DSPLINK_BIOS
     *
     *  Now obsolete. Leave here for awhile until examples, tests are updated.
     *  @_nodoc
     */
    config UInt32 dspCommNumMsgQueues = 64;

    /*!
     *  ======== dspCommUseExactMatch ========
     *  Indicates that "exact match" must be used for comm messages allocated on
     *  the DSP side.
     *
     *  Applies only to configurations where runtimeEnv == DSPLINK_BIOS
     *
     *  Now obsolete. Leave here for awhile until examples, tests are updated.
     *  @_nodoc
     */
    config Bool dspCommUseExactMatch = true;

    /*!
     *  ======== dspCommMsgSize ========
     *  Default size for the inter-DSP communication messages (MSGQ messages).
     *
     *  Applies only to configurations where runtimeEnv == DSPBIOS
     *  in special circumstances.
     * @_nodoc
     */
    config UInt32 dspCommMsgSize = 1024;

    /*!
     *  ======== dspCommNumMsgs ========
     *  Number of <commMsgSize>-sized messages used for Arm-DSP communication.
     *
     *  Applies only to configurations where runtimeEnv == DSPBIOS
     *  in special circumstances.
     * @_nodoc
     */
    config UInt32 dspCommNumMsgs = 64;

    /*!
     *  ======== usePowerManagement ========
     *  If set to true, will attempt to include power-management code
     *  where applicable.
     *
     *  This feature may not be available on all devices.
     *
     *  Now obsolete. Leave here for awhile until examples, tests are updated.
     *  @_nodoc
     */
    config bool usePowerManagement;

    /*!
     *  ======== powerSaveMemoryBlockName ========
     *  The name of the segment to which power should be saved; if left null,
     *  will default to defaultMemSegId.
     *
     *  This feature may not be available on all devices.
     *
     *  Now obsolete. Leave here for awhile until examples, tests are updated.
     *  @_nodoc
     */
    config String powerSaveMemoryBlockName = null;

    config Bool debug = false;
}
/*
 *  @(#) ti.sdo.ce.ipc; 2, 0, 1,183; 12-2-2010 21:24:06; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

