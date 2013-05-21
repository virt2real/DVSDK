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
 *  ======== Global ========
 *  Global OS Abstract Layer Configuration
 */
@Template("./Global.xdt")

metaonly module Global {

    /*!
     *  ======== os ========
     *  A specific OSAL implementations "Settings" module, for example,
     *  ti.sdo.ce.osal.bios.Settings or ti.sdo.ce.osal.linux.Settings.
     *  To set the OS of the executable to BIOS, set Global.os to:
     *  xdc.useModule('ti.sdo.ce.osal.bios.Settings').
     *
     *  When this config param is used, the {@ link ti.sdo.ce.ipc.Settings#ipc
     *  config param must also be set.
     *
     *  This should only be used to explicitly configure the OSAL to
     *  a package not provided with Codec Engine.  To use an OSAL provided
     *  by Codec Engine, it's recommended to configure the OSAL using
     *  the runtimeEnv config param instead of this one.
     *
     *  See {@ link http://wiki.davincidsp.com/index.php?title=CE_Config_Updates
     *  for more details}
     *
     *  @see runtimeEnv
     */
    config IOsal.Module os;

    /*!
     *  ======== RuntimeOS ========
     *  All runtime OSs that are abstracted by this package.
     *
     *  @see runtimeEnv
     */
    enum RuntimeEnv {
        NONE          = 0,   /*! no OS; threads are not truly supported */
        DSPBIOS       = 1,   /*! DSP/BIOS  */
        LINUX         = 2,   /*! Linux */
        DSPLINK_BIOS  = 3,   /*! DSPLINK + BIOS (DSP) */
        DSPLINK_LINUX = 4,   /*! DSPLINK + Linux (Arm) */
        WINCE         = 5,   /*! Windows CE */
        DSPLINK_WINCE = 6    /*! DSPLINK + Windows CE (Arm) */
    };

    /* Arm-side DSPLink configuration - Deprecated!! */

    /*!
     *  ======== DEFAULT_ARMDSPLINKCONFIG ========
     *  List of DSP memory segments and other parameters for DspLink
     *  configuration suitable for most "out of the box" DaVinci
     *  DSP servers.
     *  Note there must be exactly one segment of each of these types:
     *  "main", "system", and "reset".
     *
     *  Obsolete. This is now part of the ipc module.
     *  @_nodoc
     */
    const ti.sdo.ce.ipc.IIpc.ArmDspLinkConfig
        DEFAULT_ARMDSPLINKCONFIG = {
        memTable: [
            ["DDRALGHEAP", {addr: 0x88000000, size: 0x07A00000, type: "other"}],
            ["DDR2",       {addr: 0x8FA00000, size: 0x00400000, type: "main" }],
            ["DSPLINKMEM", {addr: 0x8FE00000, size: 0x00100000, type: "link" }],
            ["RESETCTRL",  {addr: 0x8FF00000, size: 0x00000080, type: "reset"}],
        ],
        doPowerControl : false,
    };

    /*!
     *  ======== armDspLinkConfig ========
     *  Arm-side DSPLINK configuration; if left undefined will be set to
     *  DEFAULT_ARMDSPLINKCONFIG, but with a warning. OBSOLETE -- used for
     *  compatibiility with CE 1.20 Arm app config scripts only; CE2.00 and
     *  later scripts should configure individual servers through
     *  the same-named field in the Engine instance.
     *
     *  Applies only to configurations where runtimeEnv == DSPLINK_LINUX
     *
     *  Obsolete. This is now part of the ipc module.
     *  @_nodoc
     */
    config ti.sdo.ce.ipc.IIpc.ArmDspLinkConfig armDspLinkConfig;

    /*!
     *  ======== runtimeEnv ========
     *  The runtime OS used to implement the abstractions provided by
     *  this package.
     *
     *  @see RuntimeEnv
     */
    config RuntimeEnv runtimeEnv;

    /*!
     *  ======== defaultMemSegId ========
     *  Default ID of the memory segment from which to allocate space
     *  (for Memory_alloc/free() calls, as opposed to Memory_segAlloc/Free()).
     *  Typically it's the segment where all other code and data go.
     *
     *  If left as "null", the system will try to find a BIOS segment named
     *  "DDR" or "DDR2" and assign its name to this field. In the future
     *  this auto-find feature may be removed, so it's best that user .cfg
     *  script set this value directly to what they know is appropriate segment.
     *
     *  Applies only to configurations where runtimeEnv == DSPBIOS or
     *  runtimeEnv == DSPLINK_BIOS
     */
    config String defaultMemSegId = null;

    /*!
     *  ======== armCommMsgSize ========
     *  Default size for the Arm-DSP communication messages (MSGQ messages).
     *
     *  Applies only to configurations where runtimeEnv == DSPLINK_LINUX
     */
    config UInt32 armCommMsgSize = 4 * 1024;

    /*!
     *  ======== armCommNumMsgs ========
     *  Number of <commMsgSize>-sized messages used for Arm-DSP communication.
     *
     *  Applies only to configurations where runtimeEnv == DSPLINK_LINUX
     */
    config UInt32 armCommNumMsgs = 64;

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
     *  Applies only to configurations where runtimeEnv == DSPLINK_BIOS
     */
    config Bool dspCommUseExactMatch = true;

    /*!
     *  ======== dspConfigureMsgqAndPool ========
     *  Set to true by default, instructs this module to generate code that
     *  configures BIOS MSGQ and POOL modules: symbols MSGQ_config and
     *  POOL_config. If set to false, and if BIOS is configured to use MSGQ,
     *  user application must define these symbols.
     *
     *  Applies only to configurations where runtimeEnv == DSPBIOS or
     *  runtimeEnv == DSPLINK_BIOS
     */
    config bool dspConfigureMsgqAndPool = true;

    /*!
     *  ======== dspUseMsgqAndPool ========
     *  If set to false, instructs Codecs Engine to cut out MSGQ and POOL
     *  references completely from the final image.
     *
     *  Applies only to configurations where runtimeEnv == DSPBIOS.
     */
    config bool dspUseMsgqAndPool = true;

    /*!
     *  ======== dspCommMsgSize ========
     *  Default size for the inter-DSP communication messages (MSGQ messages).
     *
     *  Applies only to configurations where runtimeEnv == DSPBIOS
     *  in special circumstances.
     *  @_nodoc
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
     * @_nodoc
     */
    config bool usePowerManagement;

    /*!
     *  ======== powerSaveMemoryBlockName ========
     *  The name of the segment to which power should be saved; if left null,
     *  will default to defaultMemSegId.
     *
     *  This feature may not be available on all devices.
     */
    config String powerSaveMemoryBlockName = null;

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
     */
    config Bool useLinkArbiter = false;

    /*!
     *  ======== commLocateRetries ========
     *  Number of times to retry Comm_locate() -- to find DSP server's MSGQ --
     *  before giving up.
     *
     *  Applies only to configurations where runtimeEnv == DSPLINK_LINUX
     */
    config int commLocateRetries = 20;

    /*!
     *  ======== traceBufferSize ========
     *  Size of the server trace buffer, in MAUs.
     *
     *  The server trace buffer is a circular buffer of characters written
     *  to by clients of ti.sdo.ce.osal.Trace (and ti.sdo.utils.trace.GT) and
     *  read by the Engine_*Trace() methods.
     *
     *  All the trace data in the target memory is stored into a globally
     *  visible character buffer
     *       Char Global_traceBuffer[ <traceBufferSize> ];
     *
     *  Applies only to configurations where runtimeEnv == DSPBIOS or
     *  runtimeEnv == DSPLINK_BIOS
     */
    config Int traceBufferSize = 32768;

    /*!
     *  ======== enableLogging ========
     *  If set to true, enable data generation necessary for CE benchmarking
     *  analysis.
     *
     *  Applies only to configurations where runtimeEnv == DSPBIOS or
     *  runtimeEnv == DSPLINK_BIOS
     */
    config bool enableLogging = true;

    /*!
     *  ======== logName ========
     *  Name of buffer used for capturing benchmarking data.
     *
     *  In BIOS environments, this is the name of the BIOS LOG.
     *
     *  Applies only to configurations where runtimeEnv == DSPBIOS or
     *  runtimeEnv == DSPLINK_BIOS
     */
    config String logName = "ti_sdo_ce_osal_LOG_Buffer";

    /*!
     *  ======== logSize ========
     *  Size of buffer used for capturing benchmarking data.
     *
     *  Applies only to configurations where runtimeEnv == DSPBIOS or
     *  runtimeEnv == DSPLINK_BIOS
     */
    config int logSize = 256;

    /*!
     *  ======== logType ========
     *  Type of buffer used for capturing benchmarking data.
     *
     *  This can be either "fixed" or "circular".
     *
     *  Applies only to configurations where runtimeEnv == DSPBIOS or
     *  runtimeEnv == DSPLINK_BIOS
     */
    config String logType = "circular";

    /*!
     *  ======== logSeg ========
     *  Memory segment for the buffer used for capturing benchmarking data.
     *
     *  Applies only to configurations where runtimeEnv == DSPBIOS or
     *  runtimeEnv == DSPLINK_BIOS
     */
    config String logSeg = null;

    /*!
     *  ======== skipVirtualAddressTranslation ========
     *  If set to true, will make Memory_getBufferPhysicalAddress()
     *  skip address translation and return the given address as the
     *  physical address. Needed when the VISA calls are made with
     *  physical buffer addresses instead of virtual ones, specifically
     *  in the multi-process-via-kernel-driver case.
     *
     *  Applies only to environments where virtual memory is used (e.g. Linux)
     *  @_nodoc
     */
    config bool skipVirtualAddressTranslation = false;

    /*!
     *  ======== embedBuildInfo ========
     *  Indication whether to embed build info (packages and their directories)
     *  into the generated executable for debugging/diagnostic purposes.
     *  Setting this to 'false' may reduce the static data size by around 1K.
     *  Applies to all configurations.
     */
    config Bool embedBuildInfo = true;

    /*!
     *  ======== addObjectToProgramInfoFile ========
     *  Internal method for adding an object to an XML-like program info file
     *  created alongside the executable
     * @_nodoc
     */
    function addObjectToProgramInfoFile( objName, obj );

    /*!
     *  ======== parseInfoFile ========
     *  Internal method for parsing an XML-like server program file
     *  that lies alongside the executable
     * @_nodoc
     */
    function parseInfoFile( infoFile );

    /*!
     *  ======== validate ========
     *  Internal validate method (see package.xs)
     * @_nodoc
     */
    function validate();

}
/*
 *  @(#) ti.sdo.ce.osal; 2, 0, 2,427; 12-2-2010 21:24:38; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

