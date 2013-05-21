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
 *  ======== Sem.h ========
 */

/**
 *  @file       ti/sdo/ce/osal/Sem.h
 *
 *  @brief      The Codec Engine OSAL semaphore module. This module provides
 *              an inteface to manipulate semaphores that can be used for
 *              mutual exclusion and thread synchronization. For Linux OS,
 *              these semaphores can be used accross processes.
 *
 *  @sa         LockMP
 */

#ifndef ti_sdo_ce_osal_Sem_
#define ti_sdo_ce_osal_Sem_

#ifdef __cplusplus
extern "C" {
#endif


/** @ingroup    ti_sdo_ce_osal_Sem */
/*@{*/

/**
 *  @brief      Trace name for the Sem module
 */
#define Sem_GTNAME "ti.sdo.ce.osal.Sem"

/**
 *  @brief      Sem timeout values
 */
#define Sem_FOREVER (UInt32)-1  /**< Block until Sem is available */
#define Sem_POLL    (UInt32)0   /**< Return immediately */

/**
 *  @brief      Sem error codes
 */
#define Sem_EOK       0   /**< Success. */
#define Sem_ETIMEOUT -1   /**< Sem call timed out. */
#define Sem_EFAIL    -2   /**< General failure. */

/**
 *  @brief      Opaque handle to a Sem object.
 */
typedef struct Sem_Obj *Sem_Handle;

/**
 *  @brief      Id to identify a critical section.
 */
typedef Int Sem_Id;

/*
 *  ======== Sem_create ========
 */
/**
 *  @brief      Create a semaphore that can be used to synchronize threads
 *              within a single process.
 *
 *  @param[in]  key     Key to identify the semaphore.
 *
 *  @param[in]  count   The initial count of the semaphore.
 *
 *  @retval             Handle to a semaphore object.
 *
 *  @post               The return value is non-NULL on success, NULL on
 *                      failure.
 *
 *  @remarks    Semaphores created with this function are not guarenteed to
 *              work accross processes. To create semaphores that can be used
 *              by different processes, use SemMP_create().
 *
 *  @sa         Sem_delete(), SemMP_create().
*/
extern Sem_Handle Sem_create(Int key, Int count);

/*
 *  ======== Sem_delete ========
 */
/**
 *  @brief      Delete a semaphore.
 *
 *  @param[in]  sem     Handle returned from Sem_create().
 *
 *  @remarks    For Linux OS this call will decrement the reference count of
 *              the Sem_Obj's IPC semaphore, and if the reference count goes
 *              to zero, the IPC semaphore will be removed from the system.
 *
 *  @sa         Sem_create().
 */
extern Void Sem_delete(Sem_Handle sem);

/*
 *  ======== Sem_getCount ========
 */
/*
 *  @brief      Get semaphore count.
 *
 *  @param[in]  sem         A semaphore handle returned from Sem_create().
 *
 *  @retval     count of the semaphore.
 */
extern Int Sem_getCount(Sem_Handle sem);

/*
 *  ======== Sem_init ========
 */
/**
 *  @brief      Initialize the Sem module.
 *
 *  @remarks    This function must be called prior to using any of the Sem
 *              APIs.
 */
extern Void Sem_init(Void);

/*
 *  ======== Sem_pend ========
 */
/*
 *  @brief      Wait on a semaphore.
 *
 *  @param[in]  sem         A semaphore handle returned from Sem_create().
 *  @param[in]  timeout     A timeout value to wait on the semaphore.
 *
 *  @retval     Sem_EOK         Success.
 *  @retval     Sem_ETIMEOUT    The call timed out before the semaphore could
 *                              be acquired.
 *  @retval     Sem_EFAIL       A general failure occurred.
 *
 *  @sa         Sem_post().
 */
extern Int Sem_pend(Sem_Handle sem, UInt32 timeout);

/*
 *  ======== Sem_post ========
 */
/*
 *  @brief      Signal a semaphore.
 *
 *  @param[in]  sem     A semaphore handle returned from Sem_create().
 *
 *  @sa         Sem_pend().
 */
extern Void Sem_post(Sem_Handle sem);

/*@}*/

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* ti_sdo_ce_osal_Sem_*/
/*
 *  @(#) ti.sdo.ce.osal; 2, 0, 2,427; 12-2-2010 21:24:38; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

