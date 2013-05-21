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

metaonly module Settings inherits ti.sdo.ce.osal.IOsal {
    /*!
     *  ======== ipcKeyBase ========
     *  Default value for IPC key needed by linux SemMP module for implementing
     *  a critical section.
     *  The default value of the ipcKeyBase is ascii code for "LASO".
     *
     *  WARNING: This value should only be changed if it conflicts with
     *  another IPC key in the system that cannot be changed. If this value
     *  is changed, all programs using Codec Engine that will be run
     *  simultaneously must have the ipcKeyBase configured to the new value.
     *
     * @_nodoc
     */
    config UInt32 ipcKeyBase = 0x4C41534F;

    /*!
     *  ======== maxCbListSize ========
     *  Maximum length of Contiguous Block List.
     *
     *  The maximum length of the contiguous block list
     *  used to speed up virtual-to-physical address translation of Arm
     *  buffer addresses.  The length indicates how many contiguous blocks
     *  are kept in the list, and was introduced to prevent performance
     *  degradation for applictions whose pattern of memory accesses made
     *  this list grow very large.  Most "regular" applications will not see
     *  a difference in performance with the introduction of this cut-off.
     *
     *  Applies to Linux only.
     */
    config UInt32 maxCbListSize = 100;

    /*!
     *  ======== debug ========
     *  Enable the debug profile of the osal Linux module.
     *
     *  This parameter is no longer supported.  See the profile config param
     *  in the ti.sdo.ce.global.Settings module.
     *
     *  @_nodoc
     */
    config Bool debug = false;
}
/*
 *  @(#) ti.sdo.ce.osal.linux; 2, 0, 1,181; 12-2-2010 21:24:47; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

