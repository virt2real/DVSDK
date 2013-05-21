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
 *  ======== ti/sdo/ce/CERuntime.h ========
 */

/**
 *  @file       ti/sdo/ce/CERuntime.h
 *
 *  @brief      The Codec Engine Runtime init module.  Provides system
 *              wide initialization of the Codec Engine Runtime.
 */
/**
 *  @addtogroup   CODECENGINE     Codec Engine Runtime
 */

#ifndef CERuntime_
#define CERuntime_

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup    CODECENGINE */
/*@{*/

#include <ti/sdo/ce/Engine.h>

/*
 *  Macros for runtime configuration
 */


/* Define this symbol so alg table for an engine can be NULL */
#define CE_NULL_algs NULL

/*
 *  ======== CE_DECLARE_TYPE ========
 */
/**
 *  @brief      Declare an inheritanc hierarchy for an algorithm.
 *
 *  @param[in]  name    This is a symbol that will be associated with the
 *                      @c types argument. It will be used to generate an
 *                      internal variable name, so don't use the same name
 *                      for two different calls to @c CE_DECLARE_TYPE().
 *                      @c name should be used in CE_LOCAL_ALG() to
 *                      associate an alg to @c types.
 *
 *  @param[in]  types   This is a ';' separated string of inheritance
 *                      hierarchies. It is used to identify the codec class of
 *                      an algorithm. For example, the declaration:
 *                      @c CE_DECLARE_TYPE(mydecoder,
 *                                         "ti.sdo.ce.speech1.ISPHDEC1")
 *                      indicates that mydecoder (a name that will be used
 *                      in CE_LOCAL_ALG() to declare a speech decoder),
 *                      inherits the ti.sdo.ce.speech1.ISPHDEC1 interface.
 *
 *                      Another example is the following:
 *                      CE_DECLARE_TYPE(decoder,
 *                      "ti.sdo.ce.video.IVIDDEC;ti.sdo.ce.test.xvideo.IVIDE")
 *                      This says that the decoder inherits the
 *                      ti.sdo.ce.test.xvideo.IVIDE interface, which in turn
 *                      inherits the ti.sdo.ce.video.IVIDDEC interface.
 *
 *
 *  @sa CE_LOCAL_ALG()
 */
#define CE_DECLARE_TYPE(name, types)         \
                                             \
static String typeTab_##name [] = {          \
    types,                                   \
    NULL                                     \
};                                           \
                                             \
/*
 *  ======== CE_LOCAL_ALG ========
 */
/**
 *  @brief      Generates a structure containing data for a local algorithm.
 *              This macro must be called between the @c CE_BEGIN_ALG_TABLE()
 *              and @c CE_END_ALG_TABLE() macro calls.
 *              It is used in this manner:
 *
 *              CE_BEGIN_ALG_TABLE(engineName)
 *                  CE_LOCAL_ALG(name_1, ...)
 *                  CE_LOCAL_ALG(name_2, ...)
 *                  ...
 *                  CE_LOCAL_ALG(name_n, ...)
 *              CE_END_ALG_TABLE(engineName)
 *
 *  @param[in]  name      This symbol is used to associate the algorithm with
 *                        one of the @c types passed to @c CE_DECLARE_TYPE().
 *  @param[in]  algName   This is the string name that the applicaion will use
 *                        to create the algorithm, for example, "sphenc1_copy".
 *  @param[in]  ialgFxns  The address of the IALG_Fxns table for the algorithm.
 *  @param[in]  idma3Fxns The address of the algorithm's IDMA3_Fxns table, if
 *                        it has one, otherwise NULL.
 *  @param[in]  iresFxns  If the algorithm uses IRES, the address of its
 *                        IRES_Fxns table, otherwise NULL.
 *  @param[in]  groupId   Scratch group Id of algorithm.
 *  @param[in]  memType   The type of memory (cached, non-cached, or whatever
 *                        the default is), to allocate for the algorithm.
 *                        Choose from the following values for memType:
 *
 *                 Engine_USECACHEDMEM_DEFAULT - default memory allocation
 *                 Engine_USECACHEDMEM_NONCACHED - non-cached memory allocation
 *                 Engine_USECACHEDMEM_CACHED - cached memory allocation
 *
 *  @sa CE_DECLARE_TYPE
 *  @sa CE_BEGIN_ALG_TABLE
 */
#define CE_LOCAL_ALG(name, algName, ialgFxns, idma3Fxns, iresFxns, groupId, \
                     memType) \
                                             \
    { algName,        /* name */             \
      {0},            /* uuid */             \
      ialgFxns,       /* ialgFxns */         \
      idma3Fxns,      /* idma3Fxns */        \
      typeTab_##name, /* typeTab */          \
      TRUE,           /* isLocal */          \
      groupId,        /* groupId */          \
      0,              /* protocol */         \
      iresFxns,       /* iresFxns */         \
      NULL,           /* stub/skel params */ \
      memType,        /* cached mem type */  \
      NULL,           /* type - typeTab[0] will be used instead */ \
    },


/*
 *  ======== CE_BEGIN_ALG_TABLE ========
 */
/**
 *  @brief      Use this macro and the CE_END_ALG_TABLE() macro around
 *              CE_LOCAL_ALG() to generate an algorithm table for an engine.
 *              The usage is:
 *              CE_BEGIN_ALG_TABLE(engineAlgTab)
 *                  CE_LOCAL_ALG(name_1, ...)
 *                  CE_LOCAL_ALG(name_2, ...)
 *                  ...
 *                  CE_LOCAL_ALG(name_n, ...)
 *              CE_END_ALG_TABLE(engineAlgTab)
 *
 *  @param[in]  name  A symbol used to generate internal variable names.
 *                    Use the same name in CE_END_ALG_TABLE(), and in
 *                    the call to CE_ENGINE(), to associate an engine
 *                    with this algorithm table.
 *
 *  @sa CE_END_ALG_TABLE
 *  @sa CE_ENGINE
 */
#define CE_BEGIN_ALG_TABLE(name)        \
static Engine_AlgDesc CE_##name##_algs[] = {


/*
 *  ======== CE_END_ALG_TABLE ========
 */
/**
 *  @brief      Use this macro after CE_BEGIN_ALG_TABLE() and CE_LOCAL_ALG()
 *              for generating an algorithm table for an engine.
 *              The usage is:
 *              CE_BEGIN_ALG_TABLE(engineAlgTab)
 *                  CE_LOCAL_ALG(name_1, ...)
 *                  CE_LOCAL_ALG(name_2, ...)
 *                  ...
 *                  CE_LOCAL_ALG(name_n, ...)
 *              CE_END_ALG_TABLE(engineAlgTab)
 *
 *  @param[in]  name  This must be the same symbol name passed to the
 *                    previous @c CE_BEGIN_ALG_TABLE() call.
 *
 *  @sa CE_BEGIN_ALG_TABLE
 *  @sa CE_ENGINE
 */
#define CE_END_ALG_TABLE(name) \
    {NULL},                    \
};

/*
 *  ======== CE_ENGINE ========
 */
/**
 *  @brief      Generates a structure containing data for an engine. This
 *              macro must be called between the @c CE_BEGIN_ENGINE_TABLE()
 *              and @c CE_END_ENGINE_TABLE() macro calls.
 *              It is used in this manner:
 *
 *              CE_BEGIN_ENGINE_TABLE(name)
 *                  CE_ENGINE(algTab_0, "engine_0", NULL)
 *                  CE_ENGINE(algTab_1, "engine_1", "server.x64P")
 *              CE_END_ENGINE_TABLE(name)
 *
 *  @param[in]  algTab Symbol to associate an alg table to this engine. Use
 *                     the name passed to CE_BEGIN_ALG_TABLE() to associate
 *                     that alg table with this engine.
 *  @param[in]  engineName      String name of this Engine.  This is used by
 *                              the application in the call to Engine_open().
 *  @param[in]  serverName      Optional Server name.
 *
 *  @sa CE_BEGIN_ALG_TABLE
 *  @sa CE_BEGIN_ENGINE_TABLE
 */
#define CE_ENGINE(algTab, engineName, serverName) \
    { engineName,    /* engine naem */          \
      CE_##algTab##_algs,/* alg table */            \
      serverName,    /* optional server name */ \
      NULL,          /* link config id */       \
      0,             /* # of algs (filled in at runtime) */  \
    },


/*
 *  ======== CE_BEGIN_ENGINE_TABLE ========
 */
/**
 *  @brief      Use this macro and the CE_END_ENGINE_TABLE() macro around
 *              CE_ENGINE() to generate an engine table for the applicaion.
 *              The usage is:
 *              CE_BEGIN_ENGINE_TABLE(name)
 *                  CE_ENGINE(algTab_1, ...)
 *                  CE_ENGINE(algTab_2, ...)
 *                  ...
 *                  CE_ENGINE(algTab_n, ...)
 *              CE_END_ENGINE_TABLE(name)
 *
 *  @param[in]  name  A symbol used to generate internal variable
 *                    names. Use the same name in CE_END_ENGINE_TABLE().
 *
 *  @sa CE_END_ENGINE_TABLE
 *  @sa CE_ENGINE
 */
#define CE_BEGIN_ENGINE_TABLE(name) \
static Engine_AlgDesc _localAlgs_000[] = {    \
    {NULL},                                   \
};                                            \
                                              \
static Engine_Desc name##_000[] = {

/*
 *  ======== CE_END_ENGINE_TABLE ========
 */
/**
 *  @brief      Use this macro and the CE_BEGIN_ENGINE_TABLE() macro around
 *              CE_ENGINE() to generate an engine table for the applicaion.
 *              The usage is:
 *              CE_BEGIN_ENGINE_TABLE(name)
 *                  CE_ENGINE(algTab_1, ...)
 *                  CE_ENGINE(algTab_2, ...)
 *                  ...
 *                  CE_ENGINE(algTab_n, ...)
 *              CE_END_ENGINE_TABLE(name)
 *
 *  @param[in]  name  A symbol used to generate internal variable
 *                    names. Use the same name in CE_BEGIN_ENGINE_TABLE().
 *
 *  @sa CE_BEGIN_ENGINE_TABLE
 *  @sa CE_ENGINE
 */
#define CE_END_ENGINE_TABLE(name)             \
    {"local",                                 \
     _localAlgs_000,                          \
     NULL,                                    \
     NULL,                                    \
     0,                                       \
    },                                        \
    {NULL, NULL, NULL, NULL, 0}               \
};                                            \
                                              \
Engine_Config Engine_config = {               \
    name##_000,                               \
    "local"                                   \
};

/*
 *  ======== CERuntime_exit ========
 */
/**
 *  @brief      Exit the Codec Engine Runtime.
 *
 *  @remarks    This function finalizes the Codec Engine modules used in
 *              the current configuration.
 */
extern Void CERuntime_exit(Void);


/*
 *  ======== CERuntime_init ========
 */
/**
 *  @brief      Initialize the Codec Engine Runtime.
 *
 *  @remarks    This function must be called prior to using any Codec Engine
 *              APIs; it initializes all Codec Engine modules used in the
 *              the current configuration.
 */
extern Void CERuntime_init(Void);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce; 1, 0, 6,432; 12-2-2010 21:19:06; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

