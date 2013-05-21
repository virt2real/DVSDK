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
 * */
/*!
 *  ======== MEMTCM ========
 *  IRES Resman and Protocol Implementation to manager ARM TCM memory on DM365
 *
 */
@Template("./MEMTCM.xdt")
 
metaonly module MEMTCM {

    /*
     *  ======== cmemBlockId ========
     *  Block-id should be the same as that used by CMEM to represent the TCM 
     *  memory block. This blockId is used to allocate memory from TCM 
     * (via CMEM). For e.g, if the insmod command of CMEM is as follows for TCM:
     *      insmod cmem.ko allowOverlap=1 phys_start_1=0x00001000 
     *              phys_end_1=0x00008000 pools_1=1x28672 
     *  then the cmemBlockId should be set to 1, etc. 
     */
    config Int cmemBlockId;

    /*!
     *  ======== ipcKeyBase ========
     *  Linux only. Base value of keys of Linux IPC objects used by
     *  MEMTCM. The IPC objects created by MEMTCM will use keys starting 
     *  at this
     *  value, and incrementing with each new object. There are currently
     *  three IPC objects, so keys in the range of ipcKeyBase to ipcKeyBase + 2
     *  will be reserved for MEMTCM. The default value of ipcKeyBase is
     *  ascii code for "MCTM".
     *
     *  WARNING: This value should only be changed if it conflicts with
     *  another IPC key in the system that cannot be changed. If this value
     *  is changed, all programs using VICP2 that will be run simultaneously
     *  must have the ipcKeyBase configured to the new value.
     *  @_nodoc
     */
    config UInt ipcKeyBase = 0x4D43544D;
    

    /*  @_nodoc */
    const Bool autoRegister = true;

    /* @_nodoc */
    config bool debug = false;

    /* @_nodoc */
    config bool trace = false;
}

/*
 *  @(#) ti.sdo.fc.ires.memtcm; 1, 0, 0,45; 12-1-2010 17:25:17; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

