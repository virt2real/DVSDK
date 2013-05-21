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
 *  ======== LockMP.h ========
 */

/**
 *  @file       ti/sdo/ce/osal/LockMP.h
 *
 *  @brief      The Codec Engine OSAL LockMP module. This module provides
 *              an inteface to manipulate locks that can be used for
 *              protecting resources shared accross processes. This is an
 *              enhancement of the OSAL Lock module which can only protect
 *              resources shared by threads within a single process.
 *              Unlike an OSAL Sem object, a LockMP (and a Lock) object
 *              allow a thread that currently owns the lock to re-acquire
 *              the lock without blocking (ie, calls to LockMP_acquire()
 *              can be nested).
 *
 *  @sa         Sem
 */

#ifndef ti_sdo_ce_osal_LockMP_
#define ti_sdo_ce_osal_LockMP_

#ifdef __cplusplus
extern "C" {
#endif


/** @ingroup    ti_sdo_ce_osal_LockMP */
/*@{*/

/**
 *  @brief      Trace name for the LockMP module
 */
#define LockMP_GTNAME "ti.sdo.ce.osal.LockMP"

/*
 *  ======== LockMP_Handle ========
 */
/**
 *  @brief      Opaque handle to a LockMP object.
 */
typedef struct LockMP_Obj *LockMP_Handle;

/*
 *  ======== LockMP_acquire ========
 */
/*
 *  @brief      Acquire a lock.
 *
 *  @param[in]  lock        A LockMP handle returned from LockMP_create().
 *
 *  @remarks    If the lock is currently owned by another thread,
 *              LockMP_acquire() will block until the owning thread has
 *              released it.
 *
 *  @sa         LockMP_release().
 */
extern Void LockMP_acquire(LockMP_Handle lock);

/*
 *  ======== LockMP_create ========
 */
/**
 *  @brief      Create a lock for protecting resources shared accross multiple
 *              processes.
 *
 *  @param[in]  key     An integer to identify the lock.
 *
 *  @retval             Handle to a LockMP object.
 *
 *  @pre                For Linux OS, @c key is not IPC_PRIVATE (#define'd
 *                      to be 0 in <bits/ipc.h>).
 *
 *  @post               The return value is non-NULL on success, NULL on
 *                      failure.
 *
 *  @remarks    For Linux OS the LockMP objects are implemented with IPC
 *              semaphores and can be shared accross processes. The @c key is
 *              used to create or get the IPC semaphore, and hence should
 *              not be @c IPC_PRIVATE. If the IPC semaphore with the same key
 *              has already been created, @c LockMP_create() will increment its
 *              reference count. Care should be taken to ensure that the keys
 *              do not collide with keys used for other Linux IPC objects in
 *              the system.
 *
 *  @remarks    For Linux OS, each process that creates a lock must
 *              also delete it. This ensures that the underlying Linux IPC
 *              semaphore's reference count goes to zero, at which point
 *              @c LockMP_delete() will free it. Failure to delete the lock
 *              will result in the Linux IPC semaphore remaining in the
 *              system even after all processes that created it have exited.
 *              In that case, the IPC semaphore will have to be deleted
 *              manually (through the Linux @c ipcrm command) or through a
 *              system reboot.
 *
 *  @sa         LockMP_delete().
*/
extern LockMP_Handle LockMP_create(Int key);

/*
 *  ======== LockMP_delete ========
 */
/**
 *  @brief      Delete a LockMP object.
 *
 *  @param[in]  lock    Handle returned from LockMP_create().
 *
 *  @remarks    For Linux OS this call will decrement the reference count of
 *              the LockMP_Obj's IPC semaphore, and if the reference count goes
 *              to zero, the IPC semaphore will be removed from the system.
 *
 *  @sa         LockMP_create().
 */
extern Void LockMP_delete(LockMP_Handle lock);

/*
 *  ======== LockMP_getCount ========
 */
/*
 *  @brief      Get Lock count.
 *
 *  @param[in]  lock        A lock handle returned from LockMP_create().
 *
 *  @remarks    This is the number of times LockMP_acquire() has been called
 *              minus the number of times LockMP_release() has been called.
 *              The lock should be acquired before calling this function
 *              to ensure that the value returned is consitent with the lock's
 *              count.
 *
 *  @retval     count of the lock.
 */
extern Int LockMP_getCount(LockMP_Handle lock);

/*
 *  ======== LockMP_getRefCount ========
 */
/*
 *  @brief      Get the reference count of a lock.
 *
 *  @param[in]  lock         A lock handle returned from LockMP_create().
 *
 *
 *  @remarks    The lock should be acquired before calling this function
 *              to ensure that the value returned is consitent with the lock's
 *              reference count.
 *
 *  @retval     Reference count of the lock.
 */
extern Int LockMP_getRefCount(LockMP_Handle lock);

/*
 *  ======== LockMP_init ========
 */
/**
 *  @brief      Initialize the LockMP module.
 *
 *  @remarks    This function must be called prior to using any of the LockMP
 *              APIs.
 */
extern Void LockMP_init(Void);

/*
 *  ======== LockMP_release ========
 */
/*
 *  @brief      Release a lock obtained through LockMP_acquire().
 *
 *  @param[in]  lock    A LockMP handle returned from LockMP_create().
 *
 *  @pre        The current thread must own the lock.
 *
 *  @remarks    The lock will be not be available to other threads until the
 *              owning thread has called LockMP_release() the same number of
 *              times that it has called LockMP_acquire().
 *
 *  @sa         LockMP_acquire().
 */
extern Void LockMP_release(LockMP_Handle lock);

/*@}*/

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* ti_sdo_ce_osal_LockMP_ */
/*
 *  @(#) ti.sdo.ce.osal; 2, 0, 2,427; 12-2-2010 21:24:38; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

