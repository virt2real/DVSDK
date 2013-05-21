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
requires ti.xdais.dm.examples.sphdec1_copy;

/*!
 *  ======== package.xdc ========
 *  Simple Codec Engine compatible speech 1.0 "decoder", wrapping the speech
 *  1.0 decode copy codec distributed with xDAIS.
 *
 *  This codec illustrates the simplest integration into the Codec
 *  Engine.  Only three files are required to integrate into the codec engine:
 *  @p(dlist)
 *      - `package.xdc`
 *          This file is required to declare a name for this package and to
 *          list all codec interfaces available.
 *      - `SPHDEC1_COPY.xdc`
 *          This file specifies a codec (named SPHDEC1_COPY) that is
 *          provided by this package.
 *      - `SPHDEC1_COPY.xs`
 *          This file implements the functions required by the ICodec
 *          interface; these functions enable the codec to describe its
 *          non-functional requirements such as stack size.
 *
 *  Integration into the Codec Engine requires no change to the codecs
 *  libraries.
 */
package ti.sdo.ce.examples.codecs.sphdec1_copy [1, 0, 0] {
    module SPHDEC1_COPY;
}
/*
 *  @(#) ti.sdo.ce.examples.codecs.sphdec1_copy; 1, 0, 0,261; 12-2-2010 21:22:35; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

