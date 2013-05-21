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
 *  Global OS Abstract Layer Configuration
 */
@Template("./Settings.xdt")

metaonly module Settings inherits ti.sdo.ce.osal.IOsal
{
    /*!
     *  ======== defaultMemSegId ========
     *  Default ID of the memory segment from which to allocate space
     *  (for Memory_alloc/free() calls, as opposed to Memory_segAlloc/Free()).
     *  Typically it's the segment where all other code and data go.
     *
     *  If left as "null", the system will try to find a BIOS segment named
     *  "DDR" or "DDR2" and assign its name to this field. In the future
     *  this auto-find feature may be removed, so it's best that user .cfg
     *  script set this value directly to what they know is appropriate
     *  segment.
     *
     *  Only set this parameter if not using ti.sdo.osal.Global.runtimeEnv
     *  to set the target OS.
     */
    config String defaultMemSegId = null;

    /*!
     *  ======== enableLogging ========
     *  If set to true, enable data generation necessary for CE benchmarking
     *  analysis.
     *
     *  Only set this parameter if not using ti.sdo.osal.Global.runtimeEnv
     *  to set the target OS.
     */
    config bool enableLogging = true;

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
     *  Only set this parameter if not using ti.sdo.osal.Global.runtimeEnv
     *  to set the target OS.
     */
    config Int traceBufferSize = 32768;

    /*!
     *  ======== logName ========
     *  Name of buffer used for capturing benchmarking data.
     *
     *  In BIOS environments, this is the name of the BIOS LOG.
     *
     *  Only set this parameter if not using ti.sdo.osal.Global.runtimeEnv
     *  to set the target OS.
     */
    config String logName = "ti_sdo_ce_osal_LOG_Buffer";

    /*!
     *  ======== logSize ========
     *  Size of buffer used for capturing benchmarking data.
     *
     *  Only set this parameter if not using ti.sdo.osal.Global.runtimeEnv
     *  to set the target OS.
     */
    config int logSize = 256;

    /*!
     *  ======== logType ========
     *  Type of buffer used for capturing benchmarking data.
     *
     *  This can be either "fixed" or "circular".
     *
     *  Only set this parameter if not using ti.sdo.osal.Global.runtimeEnv
     *  to set the target OS.
     */
    config String logType = "circular";

    /*!
     *  ======== logSeg ========
     *  Memory segment for the buffer used for capturing benchmarking data.
     *
     *  Only set this parameter if not using ti.sdo.osal.Global.runtimeEnv
     *  to set the target OS.
     */
    config String logSeg = null;

    /*!
     *  ======== debug ========
     *  Enable the debug profile of the osal BIOS module.
     *
     *  Deprecated, so don't document this.
     *  @_nodoc
     */
    config Bool debug = false;

    override bool supportsLogging();
}
/*
 *  @(#) ti.sdo.ce.osal.bios; 2, 0, 1,182; 12-2-2010 21:24:43; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

