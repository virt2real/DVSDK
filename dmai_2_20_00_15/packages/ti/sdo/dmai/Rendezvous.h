/* --COPYRIGHT--,BSD
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
 * --/COPYRIGHT--*/

/**
 * @defgroup   ti_sdo_dmai_Rendezvous   Rendezvous
 *
 * @brief Implements a thread synchronization module. It can be used for
 *        synchronizing the initialization of a number of threads. When a
 *        thread is done initializing it calls #Rendezvous_meet(), and when
 *        all threads has called this method they will all be unblocked to
 *        continue execution. Example below:
 *
 * @code
 * main:
 *   #include <xdc/std.h>
 *   #include <ti/sdo/dmai/Dmai.h>
 *   #include <ti/sdo/dmai/Rendezvous.h>
 *
 *   Rendezvous_Attrs rzvAttrs = Rendezvous_Attrs_DEFAULT;
 *   Dmai_init();
 *   // We want to synchronize 2 threads:
 *   Rendezvous_Handle hRv = Rendezvous_create(2, &rzvAttrs);
 *
 * thread1:
 *   extern Rendezvous_Handle hRv;
 *   // Do thread initialization
 *   // Thread will block here until thread2 is done with init also:
 *   Rendezvous_meet(hRv);
 *   // Do main loop when both threads are done initializing.
 *
 * thread2:
 *   extern Rendezvous_Handle hRv;
 *   // Do thread initialization
 *   // Thread will block here until thread1 is done with init also:
 *   Rendezvous_meet(hRv);
 *   // Do main loop when both threads are done initializing.
 * @endcode
 */

#ifndef ti_sdo_dmai_Rendezvous_h_
#define ti_sdo_dmai_Rendezvous_h_

#include <xdc/std.h>

#include <ti/sdo/dmai/Dmai.h>

/** @ingroup    ti_sdo_dmai_Rendezvous */
/*@{*/

/* Constant for infinite number of threads */
#define Rendezvous_INFINITE -1

/**
 * @brief       Handle through which to reference a Rendezvous Object.
 */
typedef struct Rendezvous_Object *Rendezvous_Handle;

/**
 * @brief       Attributes used to create a Rendezvous.
 * @see         Rendezvous_Attrs_DEFAULT.
 */
typedef struct Rendezvous_Attrs {
    /** @brief Currently no attributes for this module, but this may change. */
    Int dummy;
} Rendezvous_Attrs;

/**
 * @brief       Default attributes for a Rendezvous.
 */
extern const Rendezvous_Attrs Rendezvous_Attrs_DEFAULT;

#if defined (__cplusplus)
extern "C" {
#endif

/**
 * @brief       Creates a Rendezvous Object. Must be called before a
 *              #Rendezvous_Handle can be used in subsequent operations.
 *
 * @param       count       Number of threads to synchronize. Use
 *                          Rendezvous_INFINITE for a Rendezvous that can only
 *                          be unblocked with Rendezvous_force or 
 *                          Rendezvous_forceAndReset.  
 * @param[in]   attrs       #Rendezvous_Attrs to use for creating the
 *                          Rendezvous instance.
 *
 * @retval      Handle for use in subsequent operations (see #Rendezvous_Handle)
 * @retval      NULL for failure.
 */
extern Rendezvous_Handle Rendezvous_create(Int count, Rendezvous_Attrs *attrs);

/**
 * @brief       Called by a thread when it's ready to meet up with other
 *              threads. This will register that the thread is ready,
 *              and will block the calling thread until a total number of count
 *              threads have called this function on this Rendezvous object.
 *              When this happens, all threads are unblocked at once and the
 *              Rendezvous object will be reset to it's original count.
 *
 * @param       hRv         The #Rendezvous_Handle in which to meet.
 *
 * @remarks     #Rendezvous_create must be called before this function.
 */
extern Void Rendezvous_meet(Rendezvous_Handle hRv);

/**
 * @brief       This call forces all threads blocking in Rendezvous_meet to
 *              unblock no matter what the state of the Rendezvous object.
 *              Useful for e.g. error cleanup. To reuse a Rendezvous object
 *              after this call, #Rendezvous_reset must be called.
 *
 * @param       hRv         The #Rendezvous_Handle to force.
 *
 * @remarks     #Rendezvous_create must be called before this function.
 */
extern Void Rendezvous_force(Rendezvous_Handle hRv);

/**
 * @brief       This call resets the Rendezvous object to it's original count at
 *              opening time.
 *
 * @param       hRv        The #Rendezvous_Handle to reset.
 *
 * @remarks     #Rendezvous_create must be called before this function.
 */
extern Void Rendezvous_reset(Rendezvous_Handle hRv);

/**
 * @brief       This call is equivalent to calling #Rendezvous_force followed
 *              by #Rendezvous_reset in a single operation.  This will ensure
 *              that calls to #Rendezvous_meet will not fail to block 
 *              in-between the calls to Rendezvous_force and Rendezvous_reset
 *              if they were called separately.
 *
 * @param       hRv         The #Rendezvous_Handle to force.
 *
 * @remarks     #Rendezvous_create must be called before this function.
 */
extern Void Rendezvous_forceAndReset(Rendezvous_Handle hRv);

/**
 * @brief       Deletes a previously created Rendezvous object.
 *
 * @param       hRv        The #Rendezvous_Handle to delete.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Rendezvous_create must be called before this function.
 */
extern Int Rendezvous_delete(Rendezvous_Handle hRv);

#if defined (__cplusplus)
}
#endif

/*@}*/

#endif /* ti_sdo_dmai_Rendezvous_h_ */
