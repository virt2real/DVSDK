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
 *  ======== RMAN ========
 *  Resource Manager for shared C64x+ resources.
 */
@Template("./RMAN.xdt")
 
metaonly module RMAN {

    /*!
     *  ======== tableSize  ========
     * Total number of individual resource manager (IRESMAN implementation) 
     * entries that will be registered with RMAN (including both static and 
     * dynamic)
     */
    config UInt tableSize = 10;

    /*!
     *  ======== maxAlgs  ========
     * Maximum number of algorithm instances that will be using the RMAN 
     * module. 
     */
    config UInt maxAlgs = 32;

    /*!
     *  ======== useDSKT2 ========
     *  Flag indicating if DSKT2 should be used for memory allocation and
     *  for supporting algorithm yields.    
     *
     *  Setting this flag to `false` will disable cooperative preemption support
     *  for algorithms in RMAN.
     */
    config Bool useDSKT2 = true;

    /*!
     *  ======== persistentAllocFxn ========
     *  Function for allocating persistent memory for RMAN's and other IRESMAN
     *  implementation's internal objects.
     *
     *  The signature of the persistent alloc function is:
     *      extern Bool persistentAllocFxn(IALG_MemRec * memTab, Int numRecs); 
     *
     *  This is required to be supplied ONLY if {@link #useDSKT2} is set to
     *  `false`.
     */
    config String persistentAllocFxn = null;
 
    /*!
     *  ======== persistentFreeFxn ========
     *  Function for freeing persistent memory used by RMAN and other IRESMAN
     *  implementation's internal objects.
     *
     *  The signature of hte persistentFreeFxn is:
     *
     *      extern Void persistentFreeFxn(IALG_MemRec *memTab, Int numRecs);
     *
     *  This is required to be supplied ONLY if {@link #useDSKT2} is set to
     *  `false`.
     */
    config String persistentFreeFxn = null;

    /*!
     *  ======== yieldSamePriority ========
     * Flag indicating if yields to same priority should happen or not
     *
     * This is required only if {@link #useDSKT2} is set to `true`.
     */
    config bool yieldSamePriority = false;

    /*!
     *  ======== semCreateFxn ========
     * Function to create semaphores used by various individual resource 
     * manager(s) registered with RMAN.
     *
     *  Function signature is:
     *  @p(code)
     * Void * _semCreate(Int key, Int count);
     */
    config String semCreateFxn = null;

    /*!
     *  ======== semDeleteFxn ========
     * Function to delete semaphores used by various individual resource 
     * manager(s) registered with RMAN.
     *
     *  Function signature is:
     *  @p(code)
     *  Void _semDelete(Void * sem);
     */
    config String semDeleteFxn = null;

    /*!
     *  ======== semPendFxn ========
     * Function to pend on semaphores used by various resource manager(s) 
     * registered with RMAN.
     *
     *  Function signature is:
     *  @p(code)
     *  Int _semPend(Void * sem, UInt32 timeout);
     */
    config String semPendFxn = null;
    
    /*!
     *  ======== semPostFxn ========
     * Function to post on Semaphores used by various resource manager(s) 
     * registered with RMAN.
     *
     *  Function signature is:
     *  @p(code)
     * Void _semPost(Void * sem); 
     */
    config String semPostFxn = null;

    /*!
     *  ======== debug ========
     *  Enable the debug profile of the RMAN module.
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
     *  ======== trace ========
     *  Enable trace in the RMAN library.
     *
     *  This will result in a larger and slower library being linked in,
     *  but it will provide trace statements for debugging purposes.
     *  @_nodoc   
     */
    config bool trace = false;

    /*!
     *  ======== lockFxn ========
     *  Deprecated
     *  Function for handling the release and lock of scratch groups required
     *  during yield to higher or same priority algorithm
     *  Void _acquireLock(Int scratchId);
     * @_nodoc
     */
    config String lockFxn = null;
 
    /*!
     *  ======== unlockFxn ========
     *  Deprecated
     *  Function for handling the release and lock of scratch groups required
     *  during yield to higher or same priority algorithm
     *  Void _releaseLock(Int scratchId);
     * @_nodoc
     */
    config String unlockFxn = null;
 
    /*!
     *  ======== setContext ========
     *  Deprecated
     *  Function for handling setting and obtaining the Yield context of a
     *  scratch group during yield to higher or same priority algorithm
     *  Void _setContext(Int scratchId, IRES_YieldContextHandle context);
     * @_nodoc
     */
    config String setContextFxn = null;

    /*!
     *  ======== getContext ========
     *  Deprecated
     *  Function for handling setting and obtaining the Yield context of a
     *  scratch group during yield to higher or same priority algorithm
     *  IRES_YieldContextHandle _getContext(Int scratchId);
     * @_nodoc
     */
    config String getContextFxn = null;
 
    /*!
     *  ======== yieldFxn ========
     *  Deprecated
     *  Function to call to yield to another task of the same priority.
     *  Required only if the yieldSamePriority flag is set to "true".
     * @_nodoc
     */
    config String yieldFxn = null;
}
/*
 *  @(#) ti.sdo.fc.rman; 2, 0, 0,207; 12-1-2010 17:25:37; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

