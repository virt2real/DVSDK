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
 *  ======== DSKT2 ========
 *  XDAIS algorithm management library.
 */
@Template("./DSKT2.xdt")

metaonly module DSKT2 {

    /*!
     *  ======== DEFAULTSEG ========
     *  Default segment to allocate memory from.
     */
    const string DEFAULTSEG = "IRAM";

    /*!
     *  ======== DARAM0 ========
     *  IALG memory space mapping of IALG_DARAM0.  This must match a BIOS heap.
     */
    config string DARAM0     = DEFAULTSEG;

    /*!
     *  ======== DARAM1 ========
     *  IALG memory space mapping of IALG_DARAM1.  This must match a BIOS heap.
     */
    config string DARAM1     = DEFAULTSEG;

    /*!
     *  ======== DARAM2 ========
     *  IALG memory space mapping of IALG_DARAM2.  This must match a BIOS heap.
     */
    config string DARAM2     = DEFAULTSEG;

    /*!
     *  ======== SARAM0 ========
     *  IALG memory space mapping of IALG_SARAM0.  This must match a BIOS heap.
     */
    config string SARAM0     = DEFAULTSEG;

    /*!
     *  ======== SARAM1 ========
     *  IALG memory space mapping of IALG_SARAM1.  This must match a BIOS heap.
     */
    config string SARAM1     = DEFAULTSEG;

    /*!
     *  ======== SARAM2 ========
     *  IALG memory space mapping of IALG_SARAM2.  This must match a BIOS heap.
     */
    config string SARAM2     = DEFAULTSEG;

    /*!
     *  ======== ESDATA ========
     *  IALG memory space mapping of IALG_ESDATA.  This must match a BIOS heap.
     */
    config string ESDATA     = DEFAULTSEG;

    /*!
     *  ======== IPROG ========
     *  IALG memory space mapping of IALG_IPROG.  This must match a BIOS heap.
     */
    config string IPROG      = DEFAULTSEG;

    /*!
     *  ======== EPROG ========
     *  IALG memory space mapping of IALG_EPROG.  This must match a BIOS heap.
     */
    config string EPROG      = DEFAULTSEG;


    /*!
     *  ======== DSKT2_HEAP ========
     *  Memory segment for internal DSKT2 data structures.
     *
     *  Objects internal to the DSKT2 module will be allocated from this heap.
     */
    config string DSKT2_HEAP = DEFAULTSEG;

    /*!
     *  ======== ALLOW_EXTERNAL_SCRATCH ========
     *  Allow external memory to be used for algorithm scratch memory requests.
     *
     *  If an algorithm requests scratch memory, and insufficient scratch
     *  memory is available, scratch buffers will be allocated in external
     *  memory if property is 'true'.
     */
    config bool   ALLOW_EXTERNAL_SCRATCH = true;

    /*!
     *  ======== DARAM_SCRATCH_SIZES ========
     *  Shared IALG_DARAM0 scratch group sizes.
     */
    config UInt   DARAM_SCRATCH_SIZES[] =
                  [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0];

    /*!
     *  ======== SARAM_SCRATCH_SIZES ========
     *  Shared IALG_SARAM0 scratch group sizes.
     */
    config UInt   SARAM_SCRATCH_SIZES[] =
                  [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0];

    /*!
     *  ======== debug ========
     *  Enable the debug profile of the DSKT2 module.
     *
     *  This will result in a larger and slower library being linked in,
     *  but it will provide extra parameter checking to ensure callers are
     *  meeting the API requirements.
     *
     *  If these API requirements are not met, `SYS_abort()` will be called.
     *  @_nodoc
     */
    config bool debug = false;

    /*!
     *  ======== cacheWritebackInvalidateFxn ========
     *  Name of function implementing cache writeback invalidate.
     *
     *  This function must have the following signature:
     *  @p(code)
     *  (*DSKT2_CacheWBInvFxn)(Ptr blockPtr, size_t byteCnt, bool wait)
     *  @p
     *
     *  For C6000 platforms DSKT2 calls this function to ensure that the
     *  algorithm instance memory is not resident in cache when it is
     *  instantiated. This is necessary for compliance with XDAIS C6000 DMA
     *  Rules and Guidelines.
     */
    config String cacheWritebackInvalidateFxn = "BCACHE_wbInv";

    /*!
     *  ======== trace ========
     *  Enable trace in the DSKT2 library.
     *
     *  This will result in a larger and slower library being linked in,
     *  but it will provide trace statements for debugging purposes.
     *  @_nodoc
     */
    config bool trace = false;
}

/*
 *  @(#) ti.sdo.fc.dskt2; 1, 0, 4,300; 12-1-2010 17:24:35; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

