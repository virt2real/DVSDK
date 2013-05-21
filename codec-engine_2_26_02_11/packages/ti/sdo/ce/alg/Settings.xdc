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
 *  ======== Settings ========
 *  Global OS Abstract Layer Configuration
 */
@Template("./Settings.xdt")

metaonly module Settings {

    /*!
     *  ======== useIdma3 ========
     *  True if IDMA3 needs to be supported.
     *
     *  @_nodoc
     */
    config bool useIdma3;

    /*!
     *  ======== useIres ========
     *  True if IRES needs to be supported.
     *
     *  @_nodoc
     */
    config bool useIres;

    /*!
     *  ======== useHeap ========
     *  Indicates that algorithm memory should be allocated from a heap.
     *
     *  Flag indicating whether algorithm memory should be allocated from
     *  a heap or from a pool.
     *
     *  This flag is currently only used when CMEM is used to allocate memory
     *  (e.g. ARM-side 'local' codecs).
     */
    config bool useHeap = false;

    /*!
     *  ======== useCache ========
     *  Indicates that algorithm memory should be cacheable.
     *
     *  This flag indicates whether algorithm memory should be allocated from
     *  cache-enabled buffers.
     *
     *  This flag is currently only used when CMEM is used to allocate memory
     *  (e.g. ARM-side 'local' codecs).
     *
     *  Note that when cache-enabled buffers are used, it is the application's
     *  responsibility to manage this cache.  See the various `Memory_` APIs
     *  for cache services.
     */
    config bool useCache = false;

    /*!
     *  ======== ipcKeyBase ========
     *  Default base value for ALG's semaphore keys.
     *  The SemMP objects created by ALG will use keys starting at this
     *  value, and incrementing with each new object. There are currently
     *  _ALG_NUMGROUPS (20) keys needed for ALG semaphores.
     *  The default value of ipcKeyBase is ascii code for "OGLA".
     *
     *  WARNING: This value should only be changed if it conflicts with
     *  another IPC key in the system that cannot be changed. If this value
     *  is changed, all programs using Codec Engine that will be run
     *  simultaneously must have the ipcKeyBase configured to the new value.
     *
     *  @_nodoc
     */
    config UInt32 ipcKeyBase = 0x4F474C41;

    /*!
     *  ======== MAXGROUPID ========
     *  Maximum group id.
     *
     *  @_nodoc
     */
    const Int MAXGROUPID = 20;

    /*!
     *  ======== groupUsed ========
     *  Array indicating whether or not there will be algorithms with a given
     *  groupId. If there is an algorithm with groupId i, then groupUsed[i]
     *  will be set to true.
     *
     *  @_nodoc
     */
    config bool groupUsed[MAXGROUPID] = [
            false, false, false, false, false,
            false, false, false, false, false,
            false, false, false, false, false,
            false, false, false, false, false
    ];

}
/*
 *  @(#) ti.sdo.ce.alg; 1, 0, 1,191; 12-2-2010 21:18:41; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

