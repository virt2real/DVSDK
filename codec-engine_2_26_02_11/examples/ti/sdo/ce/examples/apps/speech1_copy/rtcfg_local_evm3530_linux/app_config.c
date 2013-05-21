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
 *  Configuration for evm3530 Linux app. In this example, all algorithms
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

/* algorithm function tables */
extern IALG_Fxns SPHDEC1COPY_TI_ISPHDEC1COPY;
extern IALG_Fxns SPHENC1COPY_TI_ISPHENC1COPY;

/* extern declarations of algorithms' IDMA3_Fxns, if any */

/* extern declarations of algorithms' IRES_Fxns, if any */

/*
 *  Declare an inheritance hierarchy for each algorithm using the
 *  CE_DECLARE_TYPE() MACRO.
 *
 *  The arguments to CE_DECLARE_TYPE(name, types) are:
 *
 *  name: This symbol is used to associate with the 'types' argument, and
 *        the same name should be used again in CE_LOCAL_ALG() so that the
 *        algorithm is associated with the correct "types".
 *
 *  types: This is a ';' separated string of inheritance hierarchies. The
 *         example below declares that "decoder" inherits the
 *         ti.sdo.ce.speech1.ISPHDEC1 interface, and encoder inherits
 *         the ti.sdo.ce.speech1.ISPHENC1 interface.
 *
 *         Another example is the following:
 *         CE_DECLARE_TYPE(decoder,
 *                   "ti.sdo.ce.video.IVIDDEC;ti.sdo.ce.test.xvideo.IVIDE")
 *         This says that the decoder inherits the ti.sdo.ce.test.xvideo.IVIDE
 *         interface, which in turn, inherits the ti.sdo.ce.video.IVIDDEC
 *         interface.
 */
CE_DECLARE_TYPE(
    decoder,                       /* name */
    "ti.sdo.ce.speech1.ISPHDEC1")  /* Inheritance hierarchy */
CE_DECLARE_TYPE(
    encoder,                       /* name */
    "ti.sdo.ce.speech1.ISPHENC1")  /* Inheritance hierarchy */

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
        decoder,                      /* name used in CE_DECLARE_TYPE() */
        "mysphdec1_copy",             /* alg name */
        &SPHDEC1COPY_TI_ISPHDEC1COPY, /* IAlg functions */
        NULL,                         /* DMAN3 functions */
        NULL,                         /* IRES functions */
        0,                            /* Scratch group Id */
        Engine_USECACHEDMEM_DEFAULT)  /* Memory type: cached, non-cached etc */

    CE_LOCAL_ALG(
        encoder,                      /* name used in CE_DECLARE_TYPE() */
        "sphenc1_copy",               /* alg name */
        &SPHENC1COPY_TI_ISPHENC1COPY, /* IAlg functions */
        NULL,                         /* DMAN3 functions */
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
        "speech1_copy",         /* Engine name */
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
 *  @(#) ti.sdo.ce.examples.apps.speech1_copy; 1, 0, 0,263; 12-2-2010 21:20:24; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

