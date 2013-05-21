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
 *  ======== SemMP.h ========
 */

/**
 *  @file       ti/sdo/ce/osal/SemMP.h
 *
 *  @brief      The Codec Engine OSAL semaphore module. This module provides
 *              an inteface to manipulate semaphores that can be used for
 *              mutual exclusion and thread synchronization. For Linux OS,
 *              these semaphores can be used accross processes.
 *
 *  @sa         LockMP
 */

#ifndef ti_sdo_ce_osal_SemMP_
#define ti_sdo_ce_osal_SemMP_

#ifdef __cplusplus
extern "C" {
#endif


/** @ingroup    ti_sdo_ce_osal_Sem */
/*@{*/

/**
 *  @brief      Trace name for the Sem module
 */
#define SemMP_GTNAME "ti.sdo.ce.osal.SemMP"

/**
 *  @brief      Sem timeout values
 */
#define SemMP_FOREVER (UInt32)-1  /**< Block until Sem is available */
#define SemMP_POLL    (UInt32)0   /**< Return immediately */

/**
 *  @brief      Sem error codes
 */
#define SemMP_EOK       0   /**< Success. */
#define SemMP_ETIMEOUT -1   /**< Sem call timed out. */
#define SemMP_EFAIL    -2   /**< General failure. */

/**
 *  @brief      Opaque handle to a Sem object.
 */
typedef struct SemMP_Obj *SemMP_Handle;

/*
 *  ======== SemMP_create ========
 */
/**
 *  @brief      Create a semaphore.
 *
 *  @param[in]  key     An integer to identify the semaphore.
 *  @param[in]  count   The initial count of the semaphore.
 *
 *  @retval             Handle to a semaphore object.
 *
 *  @pre                For Linux OS, @c key is not IPC_PRIVATE (#define'd
 *                      to be 0 in <bits/ipc.h>).
 *
 *  @post               The return value is non-NULL on success, NULL on
 *                      failure.
 *
 *  @remarks    For Linux OS these semaphores are implemented with IPC
 *              semaphores and can be shared accross processes. The @c key is
 *              used to create or get the IPC semaphore, and hence should
 *              not be @c IPC_PRIVATE. If the IPC semaphore with the same key
 *              has already been created, @c SemMP_create() will increment its
 *              reference count. Care should be taken to ensure that the keys
 *              do not collide with keys used for other Linux IPC objects in
 *              the system.
 *
 *  @remarks    For Linux OS, each process that creates a semaphore must
 *              also delete it. This ensures that the underlying Linux IPC
 *              semaphore's reference count goes to zero, at which point
 *              @c SemMP_delete() will free it. Failure to delete the semaphores
 *              will result in the Linux IPC semaphore remaining in the
 *              system even after all processes that created it have exited.
 *              In that case, the IPC semaphore will have to be deleted
 *              manually (through the Linux @c ipcrm command) or through a
 *              system reboot.
 *              Processes that end abnormally (eg, with ^C) may need to have
 *              a signal handler cleanup its semaphores.
 *
 *  @sa         SemMP_delete().
*/
extern SemMP_Handle SemMP_create(Int key, Int count);

/*
 *  ======== SemMP_delete ========
 */
/**
 *  @brief      Delete a semaphore.
 *
 *  @param[in]  sem     Handle returned from SemMP_create().
 *
 *  @remarks    For Linux OS this call will decrement the reference count of
 *              the SemMP_Obj's IPC semaphore, and if the reference count goes
 *              to zero, the IPC semaphore will be removed from the system.
 *
 *  @sa         SemMP_create().
 */
extern Void SemMP_delete(SemMP_Handle sem);

/*
 *  ======== SemMP_getCount ========
 */
/*
 *  @brief      Get semaphore count.
 *
 *  @param[in]  sem         A semaphore handle returned from SemMP_create().
 *
 *  @retval     count of the semaphore.
 */
extern Int SemMP_getCount(SemMP_Handle sem);

/*
 *  ======== SemMP_getRefCount ========
 */
/*
 *  @brief      Get the reference count of a semaphore.
 *
 *  @param[in]  sem         A semaphore handle returned from SemMP_create().
 *
 *  @retval     Reference count of the semaphore.
 */
extern Int SemMP_getRefCount(SemMP_Handle sem);

/*
 *  ======== SemMP_init ========
 */
/**
 *  @brief      Initialize the Sem module.
 *
 *  @remarks    This function must be called prior to using any of the Sem
 *              APIs.
 */
extern Void SemMP_init(Void);

/*
 *  ======== SemMP_pend ========
 */
/*
 *  @brief      Wait on a semaphore.
 *
 *  @param[in]  sem         A semaphore handle returned from SemMP_create().
 *  @param[in]  timeout     A timeout value to wait on the semaphore.
 *
 *  @retval     SemMP_EOK         Success.
 *  @retval     SemMP_ETIMEOUT    The call timed out before the semaphore could
 *                              be acquired.
 *  @retval     SemMP_EFAIL       A general failure occurred.
 *
 *  @sa         SemMP_post().
 */
extern Int SemMP_pend(SemMP_Handle sem, UInt32 timeout);

/*
 *  ======== SemMP_post ========
 */
/*
 *  @brief      Signal a semaphore.
 *
 *  @param[in]  sem     A semaphore handle returned from SemMP_create().
 *
 *  @sa         SemMP_pend().
 */
extern Void SemMP_post(SemMP_Handle sem);

/*@}*/

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* ti_sdo_ce_osal_SemMP_*/
/*
 *  @(#) ti.sdo.ce.osal; 2, 0, 2,427; 12-2-2010 21:24:38; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

