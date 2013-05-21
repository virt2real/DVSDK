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
 *  ======== Algorithm.h ========
 */

/**
 *  @file       ti/sdo/ce/alg/Algorithm.h
 *
 *  @brief      The interface for creating algorithms.
 */
/**
 *  @defgroup   ti_sdo_ce_alg_Algorithm    Algorithm management
 */


#ifndef ti_sdo_ce_alg_Algorithm_
#define ti_sdo_ce_alg_Algorithm_

#ifdef __cplusplus
extern "C" {
#endif

#include <ti/xdais/ialg.h>

/** @ingroup    ti_sdo_ce_alg_Algorithm */
/*@{*/

#define Algorithm_GTNAME "ti.sdo.ce.alg.Algorithm"

/** @ingroup    ti_sdo_ce_alg_Algorithm */
/*@{*/

/**
 *  @brief      Algorithm Cacheable Memory types.
 *
 *  @enumWarning
 */
typedef enum Algorithm_CachedMemType {
    Algorithm_USECACHEDMEM_DEFAULT = -1,  /**< Use default cache setting */
    Algorithm_USECACHEDMEM_NONCACHED = 0, /**< Use non-cached memory */
    Algorithm_USECACHEDMEM_CACHED = 1     /**< Use cached memory */
} Algorithm_CachedMemType;


/**
 *  @brief      Opaque handle to an Algorithm instance.
 */
typedef struct Algorithm_Obj* Algorithm_Handle;

typedef struct Algorithm_Attrs {
    Int     groupId;        /**< Group into which this algorithm should be
                             *   associated with.
                             *
                             *   @remarks       Algorithms in the same group
                             *                  share resources.
                             *
                             *   @todo          Need to add some details about
                             *                  Cooperative pre-emption and/or
                             *                  how these shared resources are
                             *                  protected.
                             */
    Bool    useExtHeap;     /**< Flag indicating whether this algorithm
                             *   should be created entirely from external
                             *   memory, regardless of the memory type it
                             *   asks for.
                             */
    UInt32    useCachedMem; /**< Flag indicating whether this algorithm's memory
                             *   should be cached.
                             *
                             *   @sa    Algorithm_CachedMemType
                             */
} Algorithm_Attrs;


extern IALG_Handle _Algorithm_lockOwner[];

/*
 *  ======== Algorithm_addGroup ========
 */
/**
 *  @brief      Do any initialization necessary to use a particular scratch
 *              group. If there are no algorithms built into the app that
 *              are in a given scratch group, no locks will be created for
 *              that scratch group. If a dynamically loaded codec is to be
 *              run in a scratch group, there must be a lock for that scratch
 *              group. This function will create the lock, in case it has not
 *              been created yet, otherwise it will increment a reference
 *              count.
 *
 *  @param[in]  groupId     Scratch group number.
 *
 *  @pre        Algorithm_init() must have been called.
 *
 *  @retval     TRUE        Success.
 *  @retval     FALSE       An error has occurred.
 *
 *  @sa         Algorithm_removeGroup()
 */
extern Bool Algorithm_addGroup(Int groupId);

/*
 *  ======== Algorithm_create ========
 */
/**
 *  @brief      Create an instance of an algorithm.
 *
 *  @param[in]  fxns        Algorithm's XDAIS IALG interface functions.
 *  @param[in]  idma3Fxns   Optional algorithm's XDAIS IDMA3 interface
 *                          functions.
 *  @param[in]  iresFxns    Optional algorithm's XDAIS IRES interface
 *                          functions.
 *  @param[in]  params      Creation parameters for the algorithm.
 *  @param[in]  attrs       Creation attributes used by Algorithm.
 *
 *  @pre        Algorithm_init() must have been called.
 *
 *  @retval     NULL        An error has occurred.
 *  @retval     non-NULL    The handle to the newly created algorithm instance.
 *
 *  @sa         Algorithm_delete()
 */
extern Algorithm_Handle Algorithm_create(IALG_Fxns *fxns, Void *idma3Fxns,
        Void *iresFxns, IALG_Params *params, Algorithm_Attrs *attrs);

/*
 *  ======== Algorithm_activate ========
 */
/**
 *  @brief      Activate an algorithm instance.
 *
 *  @param[in]  alg     Handle to a created algorithm instance.
 *
 *  @pre        Algorithm_init() must have been called.
 *
 *  @sa         Algorithm_deactivate()
 */
extern Void Algorithm_activate(Algorithm_Handle alg);

/*
 *  ======== Algorithm_deactivate ========
 */
/**
 *  @brief      Deactivates an algorithm instance.
 *
 *  @param[in]  alg     Handle to a created algorithm instance.
 *
 *  @pre        Algorithm_init() must have been called.
 *
 *  @sa         Algorithm_activate()
 */
extern Void Algorithm_deactivate(Algorithm_Handle alg);

/*
 *  ======== Algorithm_delete ========
 */
/**
 *  @brief      Delete the instance of an algorithm.
 *
 *  @param[in]  alg     Handle to a created algorithm instance.
 *
 *  @pre        Algorithm_init() must have been called.
 *
 *  @pre        @c alg is a valid (non-NULL) handle which is
 *              in the created state.
 *
 *  @post       All resources allocated as part of the Algorithm_create()
 *              operation (memory, DMA channels, etc.) are freed.
 *
 *  @sa         Algorithm_create()
 */
extern Void Algorithm_delete(Algorithm_Handle alg);

/*
 *  ======== Algorithm_getNumRecs ========
 */
/**
 *  @brief      Get the number of IALG_MemRecs used by the instance of an
 *              algorithm.
 *
 *  @param[in]  alg     Handle to a created algorithm instance.
 *
 *  @pre        Algorithm_init() must have been called.
 *
 *  @pre        @c alg is a valid (non-NULL) handle which is
 *              in the created state.
 *
 *  @retval     > 0     Number of IALG_MemRecs used by the algorithm.
 *  @retval     0       No records for algorithm found.
 *  @retval     < 0     This API is not supported.
 *
 *  @sa         Algorithm_getMemRecs()
 */
extern Int Algorithm_getNumRecs(Algorithm_Handle alg);

/*
 *  ======== Algorithm_getMemRecs ========
 */
/**
 *  @brief      Get the IALG_MemRecs used by the instance of an algorithm.
 *
 *  @param[in]  alg     Handle to a created algorithm instance.
 *  @param[out] memTab  Array to store IALG_MemRecs.
 *  @param[in]  size    Maximum nuber of IALG_MemRecs to copy into memTab.
 *
 *  @pre        Algorithm_init() must have been called.
 *
 *  @pre        @c alg is a valid (non-NULL) handle which is
 *              in the created state.
 *  @pre        @c memTab is non-NULL
 *
 *  @post       If return value > 0, memTab[] will contain that number of
 *              IALG_MemRecs used by the algorithm.
 *
 *  @retval     > 0     Number of IALG_MemRecs used by the algorithm, copied
 *                      into the memTab array.
 *  @retval     0       No records for algorithm found.
 *  @retval     < 0     This API is not supported.
 *
 *  @sa         Algorithm_getNumRecs()
 */
extern Int Algorithm_getMemRecs(Algorithm_Handle alg, IALG_MemRec *memTab,
        Int size);

/*
 *  ======== Algorithm_init ========
 */
/**
 *  @brief      Module init function.
 *
 *  @remarks    This function must be called before any other functions in
 *              this module can be used.
 *
 *  @sa         Algorithm_exit()
 */
extern Void Algorithm_init(Void);


/*
 *  ======== Algorithm_exit ========
 */
/**
 *  @brief      Module exit function.
 *
 *  @remarks    After this function is called, no other functions in
 *              this module can be used until Algorithm_init() is called.
 */
extern Void Algorithm_exit(Void);


/*
 *  ======== Algorithm_getAlgHandle ========
 */
/**
 *  @brief      Obtain the XDAIS IALG handle of an algorithm.
 *
 *  @param[in]  alg     Handle to a created algorithm instance.
 *
 *  @pre        Algorithm_init() must have been called.
 */
extern IALG_Handle Algorithm_getAlgHandle(Algorithm_Handle alg);


/*
 *  ======== Algorithm_releaseLock ========
 */
/**
 *  @brief      Release the scratch group lock held by the XDAIS algorithm.
 *
 *  @param[in]  alg     Handle to a created algorithm instance.
 *
 *  @param[in]  groupId GroupId of the algorithm, releasing the lock
 *
 *  @pre        Algorithm_activate() must have been called.
 */
extern Void Algorithm_releaseLock(Int groupId, IALG_Handle alg);

/*
 *  ======== Algorithm_removeGroup ========
 */
/**
 *  @brief      Do any de-initialization necessary when a particular scratch
 *              group is no longer needed. If a dynamically loaded codec is
 *              unloaded, this function should be called to indicate that
 *              the scratch group that the codec ran in is no longer needed.
 *              This function will decrement a reference count, and if 0,
 *              remove any locks for the group.
 *
 *  @param[in]  groupId     Scratch group number.
 *
 *  @pre        Algorithm_init() must have been called.
 *
 *  @sa         Algorithm_addGroup()
 */
extern Void Algorithm_removeGroup(Int groupId);

/*
 *  ======== Algorithm_acquireLock ========
 */
/**
 *  @brief      Re-acquire the scratch group lock held by the XDAIS algorithm.
 *
 *  @param[in]  alg     Handle to a created algorithm instance.
 *
 *  @param[in]  groupId GroupId of the algorithm, releasing the lock
 *
 *  @pre        Algorithm_releaseLock() must have been called.
 */
extern Void Algorithm_acquireLock(Int groupId, IALG_Handle alg);

/*@}*/  /* ingroup */

#ifdef __cplusplus
}
#endif

#endif


/*
 *  @(#) ti.sdo.ce.alg; 1, 0, 1,191; 12-2-2010 21:18:41; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

