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
/* This "requires" list describes what packages to import into this bundle */
requires ti.sdo.ce;
requires ti.sdo.ce.node;
requires ti.sdo.ce.ipc;
requires ti.sdo.ce.ipc.bios;
requires ti.sdo.ce.ipc.dsplink;
requires ti.sdo.ce.ipc.dsplink.dsp;
requires ti.sdo.ce.ipc.linux;
requires ti.sdo.ce.ipc.noOS;
requires ti.sdo.ce.osal;
requires ti.sdo.ce.osal.bios;
requires ti.sdo.ce.osal.linux;
requires ti.sdo.ce.osal.wince;
requires ti.sdo.ce.osal.wince.utils;
requires ti.sdo.ce.osal.noOS;
requires ti.sdo.ce.alg;
requires ti.sdo.ce.trace;
requires ti.sdo.ce.speech;
requires ti.sdo.ce.speech1;
requires ti.sdo.ce.video;
requires ti.sdo.ce.video1;
requires ti.sdo.ce.video2;
requires ti.sdo.ce.audio;
requires ti.sdo.ce.audio1;
requires ti.sdo.ce.global;
requires ti.sdo.ce.image;
requires ti.sdo.ce.image1;
requires ti.sdo.ce.universal;
requires ti.sdo.ce.vidtranscode;
requires ti.sdo.ce.vidanalytics;
requires ti.sdo.ce.video2.split;

requires ti.sdo.ce.bioslog;

requires ti.sdo.ce.utils;
requires ti.sdo.ce.utils.rtcfg;
requires ti.sdo.ce.utils.trace;
requires ti.sdo.ce.utils.xdm;

requires ti.dsplink.utils.lad;
requires ti.dsplink.utils.ladclient;

requires ti.sdo.ce.examples.codecs;
requires ti.sdo.ce.examples.codecs.viddec1_copy;
requires ti.sdo.ce.examples.codecs.videnc1_copy;
requires ti.sdo.ce.examples.codecs.imgdec1_copy;
requires ti.sdo.ce.examples.codecs.imgenc1_copy;
requires ti.sdo.ce.examples.codecs.sphdec1_copy;
requires ti.sdo.ce.examples.codecs.sphenc1_copy;
requires ti.sdo.ce.examples.codecs.auddec1_copy;
requires ti.sdo.ce.examples.codecs.audenc1_copy;
requires ti.sdo.ce.examples.codecs.auddec1_ires;
requires ti.sdo.ce.examples.codecs.viddec2_copy;

requires ti.sdo.ce.examples.codecs.viddec_copy;
requires ti.sdo.ce.examples.codecs.videnc_copy;
requires ti.sdo.ce.examples.codecs.imgdec_copy;
requires ti.sdo.ce.examples.codecs.imgenc_copy;
requires ti.sdo.ce.examples.codecs.sphdec_copy;
requires ti.sdo.ce.examples.codecs.sphenc_copy;
requires ti.sdo.ce.examples.codecs.auddec_copy;
requires ti.sdo.ce.examples.codecs.audenc_copy;

requires ti.sdo.ce.examples.codecs.g711;
requires ti.sdo.ce.examples.codecs.scale;
requires ti.sdo.ce.examples.codecs.vidtranscode_copy;
requires ti.sdo.ce.examples.codecs.vidanalytics_copy;

requires ti.sdo.ce.examples.codecs.viddec2split_copy;
requires ti.sdo.ce.examples.codecs.universal_copy;

requires ti.sdo.ce.examples.extensions;
requires ti.sdo.ce.examples.extensions.scale;

requires ti.sdo.ce.examples.servers;
requires ti.sdo.ce.examples.servers.all_codecs;
requires ti.sdo.ce.examples.servers.all_codecs_new_config;
requires ti.sdo.ce.examples.servers.server_api_example;
requires ti.sdo.ce.examples.servers.audio1_ires;

requires ti.sdo.ce.examples.buildutils;
requires ti.sdo.ce.examples.apps;
requires ti.sdo.ce.examples.apps.video_copy;
requires ti.sdo.ce.examples.apps.image_copy;
requires ti.sdo.ce.examples.apps.speech_copy;
requires ti.sdo.ce.examples.apps.audio_copy;
requires ti.sdo.ce.examples.apps.server_api_example;
requires ti.sdo.ce.examples.apps.server_trace;

requires ti.sdo.ce.examples.apps.video2_copy;
requires ti.sdo.ce.examples.apps.video1_copy;
requires ti.sdo.ce.examples.apps.image1_copy;
requires ti.sdo.ce.examples.apps.speech1_copy;
requires ti.sdo.ce.examples.apps.audio1_copy.sync;
requires ti.sdo.ce.examples.apps.audio1_copy.async;
requires ti.sdo.ce.examples.apps.audio1_ires;

requires ti.sdo.ce.examples.apps.video2split_copy;

requires ti.sdo.ce.examples.apps.vidtranscode;
requires ti.sdo.ce.examples.apps.vidanalytics;

requires ti.sdo.ce.examples.apps.universal_copy;
requires ti.sdo.ce.examples.apps.scale;
requires ti.sdo.ce.examples.apps.speech;
requires ti.sdo.ce.examples.apps.speech_copy_LAD;

requires ti.sdo.ce.wizards.genserver;
requires ti.sdo.ce.wizards.gencodecpkg;

/*!
 *  ======== codec_engine ========
 *  The Codec Engine product package
 *
 *  This package is a "bundle" of packages required to use the Codec Engine
 *  API's to run algorithms.  It also includes packages required to add new
 *  algorithms to a system using the Codec Engine.
 *
 */
package codec_engine_2_26_02_11 [1, 0, 0] {
}
/*
 *  @(#) codec_engine_2_26_02_11; 1, 0, 0,1; 12-2-2010 21:43:09; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

