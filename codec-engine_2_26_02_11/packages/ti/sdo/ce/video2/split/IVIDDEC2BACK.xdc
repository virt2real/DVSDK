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
 *  ======== ti.sdo.ce.video2split.IVIDDEC2BACK ========
 *  Video decode split algorithm (BACK) configuration interface for xDM
 *  IVIDDEC2BACK interface.
 *
 *  All split video decoder codecs which implement IVIDDEC2BACK must
 *  implement this meta-only configuration interface.
 */
metaonly interface IVIDDEC2BACK inherits ti.sdo.ce.ICodec
{
    override config String serverFxns = "VIDDEC2BACK_SKEL";
    override config String stubFxns = "VIDDEC2BACK_STUBS";

    override readonly config Int rpcProtocolVersion = 0;
    override readonly config Bool codecClassConfigurable = true;

    const Int XDM_MAX_CONTEXT_BUFFERS = 32;

    /*!
     *  ======== manageInBufsCache =======
     *  Codec Class configuration param
     *
     *  Determines whether cache will be managed on the DSP for each of the
     *  (up to 16) input buffers given to the codec's "process()" call.
     *
     *  If this flag is set to "false" for one or more
     *  elements, the cache for the corresponding input buffer will not be
     *  invalidated before the process() call. Skipping unnecessary cache
     *  invalidation improves performance, especially if a buffer is large.
     *
     *  (If element "i" in this array is set to true, cache for inBufs[i] will
     *  be invalidated only if the buffer is supplied, of course.)
     *
     *  For example, if you know that a particular codec of this class always
     *  reads the data from its inBufs[1] buffer only via DMA, you can set
     *  manageInBufsCache[1] = false;
     */
    config Bool manageInBufsCache[ XDM_MAX_CONTEXT_BUFFERS ] = [
        true, true, true, true, true, true, true, true,
        true, true, true, true, true, true, true, true,
        true, true, true, true, true, true, true, true,
        true, true, true, true, true, true, true, true,
    ];

    /*!
     *  ======== manageOutBufsCache =======
     *  Codec Class configuration param
     *
     *  Determines whether cache will be managed on the DSP for each of the
     *  (up to 16) output buffers given to the codec's "process()" call.
     *
     *  If this flag is set to "false" for one or more
     *  elements, the cache for the corresponding output buffer will not be
     *  invalidated before the process() call.
     *  Skipping unnecessary cache invalidation improves
     *  performance. Whether the buffer will be written back after the process()
     *  call depends on the algorithm and cannot be controlled here.
     *
     *  For example, if you know that a particular codec of this class always
     *  writes the data to its outBufs[2] buffer only via DMA, you can set
     *  manageOutBufsCache[2] = false;
     */
    config Bool manageOutBufsCache[ XDM_MAX_CONTEXT_BUFFERS ] = [
        true, true, true, true, true, true, true, true,
        true, true, true, true, true, true, true, true,
        true, true, true, true, true, true, true, true,
        true, true, true, true, true, true, true, true,
    ];

    /*!
     *  ======== manageIntermediateBufsCache =======
     *  Codec Class configuration param
     *
     *  Determines whether cache will be managed on the DSP for each of the
     *  (up to 16) output buffers given to the codec's "process()" call.
     *
     *  If this flag is set to "false" for one or more
     *  elements, the cache for the corresponding intermediate buffer won't be
     *  invalidated before the process() call.
     *  Skipping unnecessary cache invalidation improves
     *  performance. Whether the buffer will be written back after the process()
     *  call depends on the algorithm and cannot be controlled here.
     */
    config Bool manageIntermediateBufsCache[ XDM_MAX_CONTEXT_BUFFERS ] = [
        true, true, true, true, true, true, true, true,
        true, true, true, true, true, true, true, true,
        true, true, true, true, true, true, true, true,
        true, true, true, true, true, true, true, true,
    ];
}
/*
 *  @(#) ti.sdo.ce.video2.split; 1, 0, 0,165; 12-2-2010 21:28:38; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

