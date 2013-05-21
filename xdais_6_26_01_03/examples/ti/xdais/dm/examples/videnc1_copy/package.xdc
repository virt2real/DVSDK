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
 *  ======== package.xdc ========
 *  Simple XDM IVIDENC1-compatible video encoder.
 *
 *  This example codec provides a reference for two features of XDM.  Also,
 *  It implements the IDMA3 interface, using the Framework Components' ACPY3
 *  component to utilize DMA.  (Note the comments in the examples' package.bld,
 *  which describe that this dependency on ACPY3 is determined at build-time,
 *  and the DMA-based "copy" is only built if ACPY3 is found in the system.
 *  More specifically, it is only build if the ti.sdo.fc.acpy3 package is found
 *  on the builder's package path.)
 *
 *  First, it demonstrates a simple implementation of the IVIDENC1 interface.
 *  The implementation of the process() function is a simple memcpy.
 *
 *  The second feature demonstrated is the ability to extend XDM's base
 *  interfaces.  In addition to supporting the base interface, it extends
 *  IVIDENC1_InArgs with a codec-specific IVIDENC1CPY_InArgs.  This "InArgs"
 *  struct defines an additional "maxBytes" field, which enables the
 *  application to limit the number of bytes to copy into the output buffer.
 */
package ti.xdais.dm.examples.videnc1_copy [2, 0, 0] {
    module VIDENC1_COPY;
}
/*
 *  @(#) ti.xdais.dm.examples.videnc1_copy; 2, 0, 0,209; 9-18-2010 14:46:29; /db/wtree/library/trees/dais/dais-t03x/src/ xlibrary

 */

