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
/*
 * ======== GTINFRA.xdc ========
 */
@Template("./GTINFRA.xdt")

metaonly module GTINFRA {

   /*
    *  
    */
    enum RuntimeEnv {
        NONE    = 0,
        DSPBIOS = 1,
        WINCE = 2
    };

    /*
     *  ======== runtimeEnv ========
     *  The runtime OS used to implement the abstractions provided by
     *  this package. If not set, "DSPBIOS" will be used as a default
     *  for DSP targets, and "NONE" for all others.
     */
    config RuntimeEnv runtimeEnv = NONE; 

    /*!
     *  ======== traceBufferSize ========
     *  Size of the server trace buffer, in MAUs.
     */       
    config Int traceBufferSize = 32768;

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

    /* @_nodoc */
    config Bool debug = false; 
 
}
/*
 *  @(#) ti.sdo.fc.utils.gtinfra; 1, 0, 0,187; 12-1-2010 17:26:10; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

