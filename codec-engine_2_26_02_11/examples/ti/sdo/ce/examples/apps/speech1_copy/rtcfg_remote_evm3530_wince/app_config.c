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
 *  ======== app_config.c ========
 *  Configuration for evm3530 WINCE app. In this example, the Engine alg
 *  table has one local alg. Remote algs will be added at runtime.
 */

#include <xdc/std.h>

/*
 *  ======== Engine Configuration ========
 */
#include <ti/sdo/ce/CERuntime.h>
#include <ti/xdais/ialg.h>

#include <ti/xdais/idma3.h>

#include <ti/xdais/ires.h>

/* type tables for local algorithms */
extern IALG_Fxns SPHDEC1COPY_TI_ISPHDEC1COPY;

/*
 *  Use macros from CERuntime.h for setting up engine tables. Please see
 *  CERuntime.h for a description of their usage.
 */
CE_DECLARE_TYPE(
    decoder,                       /* name */
    "ti.sdo.ce.speech1.ISPHDEC1")  /* Inheritance hierarchy */

/*
 *  Set up the alg table.
 *  This app will have one local alg, "mysphdec1_copy", and one remote,
 *  "sphenc1_copy". Note that the name "decoder", passed to CE_LOCAL_ALG(),
 *  matches the name passed to CE_DECLARE_TYPE(). This is to associate the
 *  sphdec1_copy alg with the "ti.sdo.ce.speech1.ISPHDEC1" types string.
 */
CE_BEGIN_ALG_TABLE(local_table)
    CE_LOCAL_ALG(
        decoder,                      /* name used in CE_DECLARE_TYPE() */
        "mysphdec1_copy",             /* alg name */
        &SPHDEC1COPY_TI_ISPHDEC1COPY, /* IAlg functions */
        NULL,                         /* DMAN3 functions */
        NULL,                         /* IRES functions */
        0,                            /* Scratch group Id */
        Engine_USECACHEDMEM_DEFAULT)  /* Memory type: cached, non-cached etc */
CE_END_ALG_TABLE(local_table)

/*
 *  Set up the engine table. Note that the name "speech1_copy" passed to
 *  CE_ENGINE(), matches the name used in CE_BEGIN_ALG_TABLE(). This is to
 *  associate the alg table above with the engine.
 */
CE_BEGIN_ENGINE_TABLE(engineTab)
    CE_ENGINE(
        local_table,            /* CE_LOCAL_ALG() table name */
        "speech1_copy",         /* Engine name */
        "all.x64P")             /* Server name */
CE_END_ENGINE_TABLE(engineTab)


/*
 *  ======== ti.sdo.ce Settings Configuration ========
 */
Bool VISA_checked = FALSE;

/*
 * ======== ti.sdo.ce.alg.Settings Configuration ========
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
 *  @(#) ti.sdo.ce.examples.apps.speech1_copy; 1, 0, 0,263; 12-2-2010 21:20:25; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

