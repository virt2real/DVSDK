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
 *  ======== PC_config.c ========
 *  Configuration for non-RTSC config example. These values will most likely
 *  not need changing.
 */

#include <xdc/std.h>

/*
 *  ======== Global Configuration ========
 */
Bool Memory_skipVirtualAddressTranslation = FALSE;

/* This symbol is referenced by Server_init() */
Int Global_useLinkArbiter = FALSE;

/*
 * ======== ti.sdo.fc.global.Settings TEMPLATE ========
 */

Bool ti_sdo_fc_multiProcess = TRUE;

UInt32 Memory_maxCbListSize = 100;

/*
 * ======== ti.sdo.ce.alg.Settings ========
 */
/*
 *  ======== ti_sdo_ce_alg_ALG_useHeap ========
 *  Flag indicating whether algorithm memory should be allocated from
 *  a heap or from a pool.
 *
 *  This flag is currently only used when CMEM is used to allocate memory
 *  (e.g. ARM-side 'local' codecs).
 */
unsigned int ti_sdo_ce_alg_ALG_useHeap = FALSE;

/*!
 *  ======== ti_sdo_ce_alg_ALG_useCache ========
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
unsigned int ti_sdo_ce_alg_ALG_useCache = FALSE;
/*
 *  @(#) ti.sdo.ce.examples.apps.speech1_copy; 1, 0, 0,263; 12-2-2010 21:20:23; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

