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
requires ti.xdais.dm.examples.viddec2split_copy;

/*!
 *  ======== package.xdc ========
 *  Simple Codec Engine compatible 'wrapper package',
 *  enabling the VIDDEC2_COPY split codecs
 *  distributed with xDAIS to be integrated into a Codec Engine-based
 *  system.
 *
 *  This codec illustrates how to provide Codec Engine-specific
 *  packaging around an existing algorithm.  It also demonstrates how
 *  a single codec package can supply more than one codec - in this
 *  case, both the encoder and decoder codecs are supported by this
 *  single codec package.
 *
 *  Five files are required to integrate into the Codec Engine:
 *  @p(dlist)
 *      - `package.xdc`
 *          This file is required to declare a globally unique name
 *          for this package and to list all codec interfaces
 *          available.  This package has two interfaces, VIDDEC2FRONT_COPY and
 *          VIDDEC2BACK_COPY.
 *      - `VIDDEC2FRONT_COPY.xdc`
 *          This file defines the VIDDEC2FRONT_COPY codec, which implements
 *          the ti.sdo.ce.video2.IVIDDEC2FRONT interface.
 *      - `VIDDEC2FRONT_COPY.xs`
 *          This file implements the functions required by the IVIDDEC2FRONT
 *          interface; these functions enable the codec to describe its
 *          non-functional requirements such as stack size.
 *      - `VIDDEC2BACK_COPY.xdc`
 *          This file defines the VIDDEC2BACK_COPY codec, which implements
 *          the ti.sdo.ce.video2.IVIDDEC2BACK interface.
 *      - `VIDDEC2BACK.xs`
 *          This file implements the functions required by the IVIDDEC2BACK
 *          interface; these functions enable the codec to describe its
 *          non-functional requirements such as stack size.
 *
 *  Integration into the Codec Engine requires no change to the codecs
 *  libraries.
 */
package ti.sdo.ce.examples.codecs.viddec2split_copy [1, 0, 0] {
    module VIDDEC2FRONT_COPY;
    module VIDDEC2BACK_COPY;
}
/*
 *  @(#) ti.sdo.ce.examples.codecs.viddec2split_copy; 1, 0, 0,163; 12-2-2010 21:23:13; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

