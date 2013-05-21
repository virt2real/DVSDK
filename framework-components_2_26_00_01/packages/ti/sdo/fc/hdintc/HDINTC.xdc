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
 *  ======== HDINTC ========
 *  HDVICP Interrupt Registry Callback Library
 */
@Template("./HDINTC.xdt")

metaonly module HDINTC {

    /*!
     *  ======== interruptVectorId_0 ========
     *  Map this to an unused interrupt vector ID
     */
    config UInt interruptVectorId_0;

    /*!
     *  ======== interruptVectorId_1 ========
     *  Map this to an unused interrupt vector ID
     */
    config UInt interruptVectorId_1;

    /*!
     *  ======== hdvicpInterruptEventNo_0  ========
     *  This must match the physical event-id associated with the HDVICP
     *  processor:0 interrupts that need to be serviced by GEM, via the
     *  interrupt line selected by 'interruptVectorId_0'.
     */
    config UInt hdvicpInterruptEventNo_0;

    /*!
     *  ======== hdvicpInterruptEventNo_1  ========
     *  This must match the physical event-id associated with the HDVICP
     *  processor:0 interrupts that need to be serviced by GEM, via the
     *  interrupt line selected by 'interruptVectorId_0'.
     */
    config UInt hdvicpInterruptEventNo_1;

    /*!
     *  ======== biosInterruptVectorId_0 ========
     *  Map this to an unused interrupt vector ID
     *  This vector Id is going to be used to set up a BIOS ISR
     */
    config UInt biosInterruptVectorId_0;

    /*!
     *  ======== biosInterruptVectorId_1 ========
     *  Map this to an unused interrupt vector ID
     *  This vector Id is going to be used to set up a BIOS ISR
     */
    config UInt biosInterruptVectorId_1;

    /*!
     *  ======== biosInterruptEventNo_0  ========
     *  This must correspond to an unused event on this device. This is a dummy
     *  event that will be mapped to the biosInterruptVectorId_0 above. 
     *  This interrupt will be software triggered (by writing to the ISR). 
     *  It won't be triggered by an actual event. 
     */
    config UInt biosInterruptEventNo_0;

    /*!
     *  ======== biosInterruptEventNo_1  ========
     *  This must correspond to an unused event on this device. This is a dummy
     *  event that will be mapped to the biosInterruptVectorId_1 above. 
     *  This interrupt will be software triggered (by writing to the ISR). 
     *  It won't be triggered by an actual event. 
     */
    config UInt biosInterruptEventNo_1;

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

    /*!
     *  ======== spinloop ========
     *  Use 'spinloop' implementation.
     *
     *  When set to true, the services which wait for the HDVICP
     *  completion interrupt will spin, rather than use a semaphore. 
     */
    config bool spinloop = false;
}
/*
 *  @(#) ti.sdo.fc.hdintc; 1, 0, 4,133; 12-1-2010 17:24:48; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

