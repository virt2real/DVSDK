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
 *  ======== SHMBUF ========
 *  Linux shared memory IRES Resman and Protocol Implementation
 */
@Template("./SHMBUF.xdt")

metaonly module SHMBUF {

    /*!
     *  ======== persistentAllocFxn ========
     *  Function for allocating memory for SHMBUF's internal objects.
     */
    config String persistentAllocFxn = null;
 
    /*!
     *  ======== persistentFreeFxn ========
     *  Function for freeing memory used by SHMBUF implementation's
     *  internal objects.
     *
     *  This is not required to be set.
     */
    config String persistentFreeFxn = null;

    /*!
     *  ======== key ========
     *  Key to identify buffer.
     */
    config UInt32 key = 0x53425546; /* "SBUF" */

    /*!
     *  ======== bufsize ========
     *  The length of the buffer resource.
     */
    config UInt32 bufsize = 0;

    /*!
     *  ======== debug ========
     *  Enable the debug profile of the library.
     *
     *  This will likely result in a larger and slower library being linked in.
     *  @_nodoc
     */
    config bool debug = false;

    /*!
     *  ======== trace ========
     *  Enable trace support
     *  @_nodoc
     */
    config bool trace = false;
}
/*
 *  @(#) ti.sdo.fc.ires.shmbuf; 1, 0, 0,119; 12-1-2010 17:25:22; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

