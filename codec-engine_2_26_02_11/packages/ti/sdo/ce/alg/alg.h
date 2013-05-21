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
 *  ======== alg.h ========
 */
#ifndef ti_sdo_ce_alg_ALG_
#define ti_sdo_ce_alg_ALG_

#include <ti/xdais/ialg.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ALG_GTNAME "ti.sdo.ce.alg"      /**< Name used to identify the GT
                                         *   module
                                         */


/*
 *  ======== ALG_Handle ========
 */
/**
 *  @brief      This handle type is used to reference all ALG instance objects.
 */
typedef IALG_Handle ALG_Handle;

/*
 *  ======== ALG_activate ========
 */
/**
 *  @brief      Restore all shared persistant data associated with algorithm
 *              object.
 *
 *  @param[in] groupId  Group which @c alg is associated with.
 *  @param[in] alg      Handle of algorithm to activate.
 *
 *  @todo       Typically handles are the first params passed to a fxn.
 *  @todo       Could we store the groupId in the alg handle at create time
 *              so we don't need to supply it to ALG_delete()?
 */
extern Void ALG_activate(Int groupId, ALG_Handle alg);

/*
 *  ======== ALG_addGroup ========
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
 *  @pre        ALG_init() must have been called.
 *  @pre        Calls to this function must be synchronized.
 *
 *  @retval     TRUE        Success.
 *  @retval     FALSE       An error has occurred.
 *
 *  @sa         ALG_removeGroup()
 */
extern Bool ALG_addGroup(Int groupId);

/*
 *  ======== ALG_control ========
 */
/**
 *  @brief      Control algorithm object.
 */
extern Int ALG_control(ALG_Handle alg, IALG_Cmd cmd, IALG_Status *sptr);

/**
 *  @brief      Algorithm Cacheable Memory types.
 *
 *  @enumWarning
 */
typedef enum ALG_CachedMemType {
    ALG_USECACHEDMEM_DEFAULT = -1,  /**< Use default cache setting */
    ALG_USECACHEDMEM_NONCACHED = 0, /**< Use non-cached memory */
    ALG_USECACHEDMEM_CACHED = 1     /**< Use cached memory */
} ALG_CachedMemType;


/*
 *  ======== ALG_create ========
 */
/**
 *  @brief      Create algorithm object and initialize its memory.
 *
 *  @param[in]  groupId         Group which alg should be created in.
 *  @param[in]  fxns            IALG function table
 *  @param[in]  p               Parent alg
 *  @param[in]  prms            Creation parameters
 *  @param[in]  useCachedMem    Indicates whether the memory should be
 *                              cached or not.
 *
 *  @retval     NULL            Failed to create algorithm
 *  @retval     non-NULL        Success - algorithm handle is returned
 *
 *  @sa         ALG_delete()
 */
extern ALG_Handle ALG_create(Int groupId, IALG_Fxns *fxns, IALG_Handle p,
        IALG_Params *prms, UInt32 useCachedMem);

/*
 *  ======== ALG_deactivate ========
 */
/**
 *  @brief      Save all shared persistant data associated with algorithm
 *              object to some non-shared persistant memory.
 *
 *  @param[in] groupId  Group which @c alg is associated with.
 *  @param[in] alg      Handle of algorithm to deactivate.
 *
 *  @todo       Typically handles are the first params passed to a fxn.
 *  @todo       Could we store the groupId in the alg handle at create time
 *              so we don't need to supply it to ALG_delete()?
 */
extern Void ALG_deactivate(Int groupId, ALG_Handle alg);

/*
 *  ======== ALG_delete ========
 */
/**
 *  @brief      Delete algorithm object and release its memory.
 *
 *  @param[in]  groupId         groupId which @c alg is associated with.
 *  @param[in]  alg             Handle of algorithm to delete.
 *  @param[in]  useCachedMem    Indicates whether memory was cached or not.
 *
 *  @todo       Typically handles are the first params passed to a fxn.
 *  @todo       Could we store the groupId in the alg handle at create time
 *              so we don't need to supply it to ALG_delete()?
 */
extern Void ALG_delete(Int groupId, ALG_Handle alg, UInt32 useCachedMem);

/*
 *  ======== ALG_acquireLock ========
 */
/**
 *  @brief      Acquire the scratch group lock by the algorithm.
 *
 *  @param[in]  groupId         groupId which @c alg is associated with.
 *  @param[in]  alg             handle of algorithm trying to acquire the lock.
 *
 *  @todo       Typically handles are the first params passed to a fxn.
 *  @todo       Could we store the groupId in the alg handle at create time
 *              so we don't need to supply it to ALG_delete()?
 */
extern Void ALG_acquireLock(Int groupId, IALG_Handle alg);


/*
 *  ======== ALG_releaseLock ========
 */
/**
 *  @brief      Release the scratch group lock held by this algorithm.
 *
 *  @param[in]  groupId         groupId which @c alg is associated with.
 *  @param[in]  alg             handle of algorithm releasing the lock.
 *
 *  @todo       Typically handles are the first params passed to a fxn.
 *  @todo       Could we store the groupId in the alg handle at create time
 *              so we don't need to supply it to ALG_delete()?
 */

extern Void ALG_releaseLock(Int groupId, IALG_Handle alg);

/*
 *  ======== ALG_removeGroup ========
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
 *  @pre        ALG_init() must have been called.
 *
 *  @sa         ALG_addGroup()
 */
extern Void ALG_removeGroup(Int groupId);

/*
 *  ======== ALG_exit ========
 *  Module finalization
 */
extern Void ALG_exit(Void);

/*
 *  ======== ALG_init ========
 *  Module initialization
 */
extern Void ALG_init(Void);

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.alg; 1, 0, 1,191; 12-2-2010 21:18:41; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

