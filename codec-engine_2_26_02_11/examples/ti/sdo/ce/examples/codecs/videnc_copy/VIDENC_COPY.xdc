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
 *  ======== VIDENC_COPY ========
 *  VIDENC_COPY codec specification
 *
 *  This file specifies information necessary to integrate with the Codec
 *  Engine.
 *
 *  By inheriting ti.sdo.ce.video.IVIDENC, VIDENC_COPY declares that it "is
 *  a" video encoder algorithm.  This allows the codec engine to automatically
 *  supply simple stubs and skeletons for transparent execution of DSP
 *  codecs by the GPP.
 *
 *  In addition to declaring the type of the VIDENC_COPY algorithm, we declare the
 *  external symbol required by xDAIS that identifies the algorithms
 *  implementation functions.
 */
metaonly module VIDENC_COPY inherits ti.sdo.ce.video.IVIDENC
{
    /*!
     *  ======== ialgFxns ========
     *  name of this algorithm's xDAIS alg fxn table
     */
    override readonly config String ialgFxns = "VIDENCCOPY_TI_VIDENCCOPY";

    /*!
     *  ======== idma3Fxns ========
     *  Name of xDAIS alg IDMA3 Interface function table.
     *
     *  Note that this is used only if .useDMA is set to true.  If
     *  .useDMA is false (the default), this idma3Fxns config param is
     *  set to NULL during the package's close phase.
     */
    override readonly config String idma3Fxns = "VIDENCCOPY_TI_IDMA3";

    /*!
     *  ======== useDMA ========
     *  This config flag can be used to enable the DMA performance enhancments
     *  available for <i>some</i> targets this codec supports (e.g. C64P).
     *
     *  If you set this to true, this package will test whether DMA is
     *  available for the requested target.  If it's not available, a warning
     *  will be printed, and the codec will fall back to using the copy
     *  based version.
     */
    config Bool useDMA = false;
}
/*
 *  @(#) ti.sdo.ce.examples.codecs.videnc_copy; 1, 0, 0,262; 12-2-2010 21:23:14; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

