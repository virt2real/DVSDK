/*
 * 
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
/* This "requires" list describes what packages to import into this bundle */
requires ti.sdo.fc.global;
requires ti.sdo.fc.dskt2;
requires ti.sdo.fc.dman3;
requires ti.sdo.fc.acpy3;

requires ti.sdo.fc.ires;
requires ti.sdo.fc.ires.addrspace;
requires ti.sdo.fc.ires.bufres;
requires ti.sdo.fc.ires.edma3chan;
requires ti.sdo.fc.ires.grouputils;
requires ti.sdo.fc.ires.hdvicp;
requires ti.sdo.fc.ires.memtcm;
requires ti.sdo.fc.ires.nullresource;
requires ti.sdo.fc.ires.sdma;
requires ti.sdo.fc.ires.shmbuf;
requires ti.sdo.fc.ires.vicp;

requires ti.sdo.fc.memutils;

requires ti.sdo.fc.rman;

requires ti.sdo.fc.utils;
requires ti.sdo.fc.utils.api;
requires ti.sdo.fc.utils.gtinfra;

requires ti.sdo.fc.edma3;
requires ti.sdo.fc.scpy;
requires ti.sdo.fc.hdintc;
requires ti.sdo.fc.hdvicpsync;
requires ti.sdo.fc.vicpsync;

requires ti.sdo.utils.trace;

/* Examples */
requires ti.sdo.fc.dman3.examples.fastcopy;
requires ti.sdo.fc.examples.dmaxfer;
requires ti.sdo.fc.examples.dma;
requires ti.sdo.fc.ires.examples.codecs.auddec1;
requires ti.sdo.fc.ires.examples.codecs.template;
requires ti.sdo.fc.ires.examples.codecs.edmacodec1;
requires ti.sdo.fc.ires.examples.codecs.idma3codec1;
requires ti.sdo.fc.ires.examples.codecs.vicp2codec1;

requires ti.sdo.fc.rman.examples;
requires ti.sdo.fc.rman.examples.addrspace;
requires ti.sdo.fc.rman.examples.bufres;
requires ti.sdo.fc.rman.examples.bufres_yield;
requires ti.sdo.fc.rman.examples.dmaxferscratch;
requires ti.sdo.fc.rman.examples.dummyedma3;
requires ti.sdo.fc.rman.examples.hdvicp;
requires ti.sdo.fc.rman.examples.lateacquire;
requires ti.sdo.fc.rman.examples.memtcm;
requires ti.sdo.fc.rman.examples.nonrtscexample;
requires ti.sdo.fc.rman.examples.nullresource;
requires ti.sdo.fc.rman.examples.scratchedma3;
requires ti.sdo.fc.rman.examples.sdma;
requires ti.sdo.fc.rman.examples.shmbuf;
requires ti.sdo.fc.rman.examples.staticreg;
requires ti.sdo.fc.rman.examples.vicp;
requires ti.sdo.fc.rman.examples.vicpsync;

/*!
 *  ======== framework_components ========
 *  The Framework Components product package.
 *
 *  This package is a "bundle" of several Framework Components packages.
 */
package framework_components_2_26_00_01 [1, 0, 0] {
}
/*
 *  @(#) framework_components_2_26_00_01; 1, 0, 0,1; 12-1-2010 17:31:36; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

