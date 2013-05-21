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
 *  Configuration for evm3530 WinCE app. In this example, all algorithms
 *  are local.
 */

#include <xdc/std.h>


/*
 *  ======== Engine Configuration ========
 */
#include <ti/sdo/ce/CERuntime.h>
#include <ti/xdais/ialg.h>

#include <ti/xdais/idma3.h>

#include <ti/xdais/ires.h>

/*
 *  This example uses macros from CERuntime.h to set up algorithm and engine
 *  tables. Please see CERuntime.h for a description of these macro usages.
 */

/* Declare types for algorithms */
CE_DECLARE_TYPE(
    viddec1_copy,                /* name */
    "ti.sdo.ce.video1.IVIDDEC1") /* Inheritance hierarchy */
CE_DECLARE_TYPE(
    videnc1_copy,        /* name */
    "ti.sdo.ce.video1.IVIDENC1") /* Inheritance hierarchy */

/* Extern declarations algorithms' function tables */
extern IALG_Fxns VIDDEC1COPY_TI_IVIDDEC1COPY;
extern IALG_Fxns VIDENC1COPY_TI_IVIDENC1COPY;
extern IDMA3_Fxns VIDENC1COPY_TI_IDMA3;

/*
 *  Create a table of engine algorithm descriptors for an engine's local
 *  algorithms, using the CE_BEGIN_ALG_TABLE(), CE_END_ALG_TABLE(), and
 *  CE_LOCAL_ALG() macros.
 *
 *  The table is declared in the following manner:
 *
 *      CE_BEGIN_ALG_TABLE(algTableName)
 *          CE_LOCAL_ALG(name, ...)
 *          CE_LOCAL_ALG(name, ...)
 *          ...
 *          CE_LOCAL_ALG(name, ...)
 *      CE_END_ALG_TABLE(algTableName)
 *
 *  The argument to CE_BEGIN_ALG_TABLE(algTableName) is:
 *
 *  algTableName: This is a name used to identify the table, so it can later
 *        be associated with a given engine.
 *
 *  The arguments to CE_LOCAL_ALG(name, algName, ialgFxns, idma3Fxns, iresFxns,
 *                                groupId, memType) are:
 *
 *  name: This symbol is used to associate the algorithm with one of the
 *        'types' declared above with CE_DECLARE_TYPE().
 *  algName: This is the name that will be used to create the algorithm, for
 *        example, "mysphdec1_copy", will be the name passed to
 *        SPHDEC1_create().
 *  ialgFxns: This is the address of the IAlg_Fxns table for the algorithm.
 *  idma3Fxns: Address of the IDMA3_Fxns table for the algorithm, if it uses
 *        the IDMA3 interface to obtain DMA resources.
 *  iresFxns: The address of the algorithm's IRES_Fxns table, if it uses IRES.
 *  groupId: The algorithm's scratch group Id.
 *  memType: The type of memory (cached, non-cached, or whatever the default
 *         is), to allocate for the algorithm. Choose from the following values
 *         for memType:
 *             Engine_USECACHEDMEM_DEFAULT - default memory allocation
 *             Engine_USECACHEDMEM_NONCACHED - non-cached memory allocation
 *             Engine_USECACHEDMEM_CACHED - cached memory allocation
 *
 */
CE_BEGIN_ALG_TABLE(local_table)
    CE_LOCAL_ALG(
        viddec1_copy,                 /* name used in CE_DECLARE_TYPE() */
        "viddec1_copy",               /* alg name */
        &VIDDEC1COPY_TI_IVIDDEC1COPY, /* IAlg functions */
        NULL,                         /* DMAN3 functions */
        NULL,                         /* IRES functions */
        0,                            /* Scratch group Id */
        Engine_USECACHEDMEM_DEFAULT)  /* Memory type: cached, non-cached etc */

    CE_LOCAL_ALG(
        videnc1_copy,                 /* name used in CE_DECLARE_TYPE() */
        "videnc1_copy",               /* alg name */
        &VIDENC1COPY_TI_IVIDENC1COPY, /* IAlg functions */
        &VIDENC1COPY_TI_IDMA3,        /* DMAN3 functions */
        NULL,                         /* IRES functions */
        0,                            /* Scratch group Id */
        Engine_USECACHEDMEM_DEFAULT)  /* Memory type: cached, non-cached etc */
CE_END_ALG_TABLE(local_table)

/*
 *  Create the table of engines. Use the CE_BEGIN_ENGINE_TABLE() and
 *  CE_END_ENGINE_TABLE() macros around CE_DECLARE_ENGINE().
 *
 *  The argument to CE_BEGIN_ENGINE_TABLE() and CE_END_ENGINE_TABLE() is
 *  a name that will be used to generate internal data structures, so make
 *  sure to use the same name for both macros.
 *
 *  The arguments to CE_DECLARE_ENGINE(name, engineName, serverName) are
 *  the following:
 *
 *  name: Use the same name passed to CE_BEGIN_ALG_TABLE(), so the engine
 *        can be associated with that alg table.
 *  engineName: This is a string that will be used to open the engine with
 *        Engine_open().
 *  serverName: String name of server, if there is one, otherwise set to NULL.
 */
CE_BEGIN_ENGINE_TABLE(engineTab)
    CE_ENGINE(
        local_table,            /* CE_LOCAL_ALG() table name */
        "video1_copy",          /* Engine name */
        NULL)                   /* Server name */
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
 * ======== ti.sdo.fc.global.Settings Configuration ========
 */
Bool ti_sdo_fc_multiProcess = TRUE;
/*
 *  @(#) ti.sdo.ce.examples.apps.video1_copy; 1, 0, 0,264; 12-2-2010 21:21:07; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

