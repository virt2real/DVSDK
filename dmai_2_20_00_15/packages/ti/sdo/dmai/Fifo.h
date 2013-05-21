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
 * @defgroup   ti_sdo_dmai_Fifo     Fifo
 *
 * @brief This module provides a uni-directional fifo queue for sending data
 *        pointers between threads. A typical example (no error checking):
 * 
 * @code
 *   #include <xdc/std.h>
 *   #include <ti/sdo/dmai/Fifo.h>
 *   Fifo_Attrs fAttrs = Fifo_Attrs_DEFAULT;
 *   Fifo_Handle hFifo;
 *
 *   Dmai_init();
 *   hFifo = Fifo_create(&fAttrs);
 * thread1:
 *   extern Fifo_Handle hFifo;
 *   Int message[] = { 1, 2, 3 };
 *   Fifo_put(hFifo, message);
 * thread2:
 *   extern Fifo_Handle hFifo;
 *   Int *msgPtr;
 *   Fifo_get(hFifo, &msgPtr);
 *   // msgPtr now points to the message[] array from main.
 * @endcode
 */

/** @ingroup    ti_sdo_dmai_Fifo */
/*@{*/

#ifndef ti_sdo_dmai_Fifo_h_
#define ti_sdo_dmai_Fifo_h_

#include <xdc/std.h>

#include <ti/sdo/dmai/Dmai.h>

/**
 * @brief       Handle through which to reference a Fifo.
 */
typedef struct Fifo_Object *Fifo_Handle;

/**
 * @brief       Attributes used to create a Fifo.
 * @see         Fifo_Attrs_DEFAULT.
 */
typedef struct Fifo_Attrs {
    /** 
     * @brief      Maximum elements that can be put on the Fifo at once
     * @remarks    For Bios only, Linux ignores this attribute
     */     
    Int maxElems;
} Fifo_Attrs;

/**
 * @brief       Default attributes for a Fifo.
 * @code
 * numElems     = 20
 * @endcode
 */
extern const Fifo_Attrs Fifo_Attrs_DEFAULT;

#if defined (__cplusplus)
extern "C" {
#endif

/**
 * @brief       Creates a fifo.
 *
 * @param[in]   attrs       #Fifo_Attrs to use for creating the Fifo.
 *
 * @retval      Handle for use in subsequent operations (see #Fifo_Handle).
 * @retval      NULL for failure.
 */
extern Fifo_Handle Fifo_create(Fifo_Attrs *attrs);

/**
 * @brief       Blocking call to receive a buffer pointer from a fifo.
 *
 * @param[in]   hFifo       #Fifo_Handle from which to receive a buffer.
 * @param[out]  ptrPtr      A pointer to the pointer to be set.
 *
 * @retval      Dmai_EOK if a buffer was successfully received.
 * @retval      Dmai_EFLUSH if the fifo was flushed.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Fifo_create must be called before this function.
 */
extern Int Fifo_get(Fifo_Handle hFifo, Ptr ptrPtr);

/**
 * @brief       Flushes a fifo. The other end will unblock and return the
 *              (non-negative) #Dmai_EFLUSH error code.
 *
 * @param[in]   hFifo       #Fifo_Handle which to flush.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Fifo_create must be called before this function.
 */
extern Int Fifo_flush(Fifo_Handle hFifo);

/**
 * @brief       Put a buffer pointer on the fifo.
 *
 * @param[in]   hFifo       #Fifo_Handle to which to send a buffer.
 * @param[in]   ptr         The pointer to put to the fifo.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Fifo_create must be called before this function.
 */
extern Int Fifo_put(Fifo_Handle hFifo, Ptr ptr);

/**
 * @brief       Determine number of entries (pointers) currently in fifo.
 *
 * @param[in]   hFifo       #Fifo_Handle which to investigate.
 *
 * @retval      Number of entries in the fifo on success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Fifo_create must be called before this function.
 */
extern Int Fifo_getNumEntries(Fifo_Handle hFifo);

/**
 * @brief       Deletes a previously created fifo.
 *
 * @param[in]   hFifo       #Fifo_Handle for the fifo to delete.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Fifo_create must be called before this function.
 */
extern Int Fifo_delete(Fifo_Handle hFifo);

#if defined (__cplusplus)
}
#endif

/*@}*/

#endif /* ti_sdo_dmai_Fifo_h_ */
