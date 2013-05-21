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
 *  ======== VIDENC1_COPY ========
 *  VIDENC1_COPY codec specification
 *
 *  This file specifies information necessary to integrate with the Codec
 *  Engine.
 *
 *  By inheriting ti.sdo.ce.video1.IVIDENC1, VIDENC1_COPY declares
 *  that it "is a" video 1.0 encoder algorithm.  This allows the Codec
 *  Engine to automatically supply simple stubs and skeletons for
 *  transparent execution of DSP codecs by the GPP.
 *
 *  In addition to declaring the type of the VIDENC1_COPY algorithm, we
 *  declare the external symbol required by xDAIS that identifies the
 *  algorithms implementation functions.
 */
metaonly module VIDENC1_COPY inherits ti.sdo.ce.video1.IVIDENC1
{
    /* handle to underlying algorithm's module - for convenience. */
    readonly config ti.xdais.dm.examples.videnc1_copy.VIDENC1_COPY.Module alg =
        ti.xdais.dm.examples.videnc1_copy.VIDENC1_COPY;

    override readonly config String ialgFxns = "VIDENC1COPY_TI_IVIDENC1COPY";

    override readonly config String idma3Fxns = "VIDENC1COPY_TI_IDMA3";
}
/*
 *  @(#) ti.sdo.ce.examples.codecs.videnc1_copy; 1, 0, 0,261; 12-2-2010 21:23:12; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

