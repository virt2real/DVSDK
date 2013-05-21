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
requires ti.xdais.dm.examples.g711;

/*!
 *  ======== package.xdc ========
 *  Simple Codec Engine compatible 'wrapper package',
 *  enabling the G.711 encoder and decoder codecs
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
 *          available.  This package has two interfaces, G711ENC and
 *          G711DEC.
 *      - `G711ENC.xdc`
 *          This file defines the G711ENC codec, which implements
 *          the ti.sdo.ce.speech1.ISPHENC1 interface.
 *      - `G711ENC.xs`
 *          This file implements the functions required by the ISPHENC1
 *          interface; these functions enable the codec to describe its
 *          non-functional requirements such as stack size.
 *      - `G711DEC.xdc`
 *          This file defines the G711DEC codec, which implements
 *          the ti.sdo.ce.speech1.ISPHDEC1 interface.
 *      - `G711DEC.xs`
 *          This file implements the functions required by the ISPHDEC1
 *          interface; these functions enable the codec to describe its
 *          non-functional requirements such as stack size.
 *
 *  Integration into the Codec Engine requires no change to the codecs
 *  libraries.
 */
package ti.sdo.ce.examples.codecs.g711 [1, 0, 0] {
    module G711ENC;
    module G711DEC;
}
/*
 *  @(#) ti.sdo.ce.examples.codecs.g711; 1, 0, 0,262; 12-2-2010 21:22:03; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

