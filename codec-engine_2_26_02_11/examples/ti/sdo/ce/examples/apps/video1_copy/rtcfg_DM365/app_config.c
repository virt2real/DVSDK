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
 *  Configuration for DM365 Linux app. In this example, all algorithms
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
    videnc1_copy,                /* name */
    "ti.sdo.ce.video1.IVIDENC1") /* Inheritance hierarchy */

/* Extern declarations algorithms' function tables */
extern IALG_Fxns VIDDEC1COPY_TI_IVIDDEC1COPY;
extern IALG_Fxns VIDENC1COPY_TI_IVIDENC1COPY;
extern IDMA3_Fxns VIDENC1COPY_TI_IDMA3;

/*
 *  Set up the alg table.
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
        Engine_USECACHEDMEM_DEFAULT)  /* Memory type */
CE_END_ALG_TABLE(local_table)

/*
 *  Set up the engin table.
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
 * ======== ti.sdo.fc.global.Settings Configuration ========
 */

Bool ti_sdo_fc_multiProcess = TRUE;


/*
 * ======== ti.sdo.ce.alg.Settings Configuration ========
 */

unsigned int ti_sdo_ce_alg_ALG_useHeap = FALSE;
unsigned int ti_sdo_ce_alg_ALG_useCache = FALSE;

/*
 *  @(#) ti.sdo.ce.examples.apps.video1_copy; 1, 0, 0,264; 12-2-2010 21:21:06; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

