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
 * @defgroup   ti_sdo_dmai_Pause    Pause
 *
 * @brief Implements a pause module to pause and resume processing in threads.
 *
 * @code
 * main:
 *   #include <xdc/std.h>
 *   #include <ti/sdo/dmai/Dmai.h>
 *   #include <ti/sdo/dmai/Pause.h>
 *   Pause_Handle hPause;
 *   Pause_Attrs pAttrs = Pause_Attrs_DEFAULT;
 *
 *   Dmai_init();
 *   hPause = Pause_create(&pAttrs);
 *
 * thread1:
 *   extern Pause_Handle hPause;
 *   Pause_on(hPause);
 *   // Do things! Anyone executing Pause_test(hPause) here will block.
 *   Pause off(hPause);
 *
 * thread2:
 *   extern Pause_Handle hPause;
 *   // If Pause_on(hPause) has been called, the below will block until
 *   // Pause_off(hPause) is called.
 *   Pause_test(hPause);
 * @endcode 
 */

#ifndef ti_sdo_dmai_Pause_h_
#define ti_sdo_dmai_Pause_h_

#include <xdc/std.h>

#include <ti/sdo/dmai/Dmai.h>

/** @ingroup    ti_sdo_dmai_Pause */
/*@{*/

/**
 * @brief       Handle through which to reference a Pause Object.
 */
typedef struct Pause_Object *Pause_Handle;

/**
 * @brief       Attributes used to create a Pause.
 * @see         Pause_Attrs_DEFAULT.
 */
typedef struct Pause_Attrs {
    /** @brief Currently no attributes for this module, but this may change. */
    Int dummy;
} Pause_Attrs;

/**
 * @brief       Default attributes for a Pause.
 */
extern const Pause_Attrs Pause_Attrs_DEFAULT;

#if defined (__cplusplus)
extern "C" {
#endif

/**
 * @brief       Creates a Pause object.
 *
 * @param[in]   attrs       #Pause_Attrs to use for creating the Pause Object.
 *
 * @retval      Handle for use in subsequent operations (see #Pause_Handle).
 * @retval      NULL for failure.
 */
extern Pause_Handle Pause_create(Pause_Attrs *attrs);

/**
 * @brief       Called to see if processing is supposed to pause. If so, block
 *              the execution of the thread. Otherwise continue.
 *
 * @param[in]   hPause      #Pause_Handle to test.
 *
 * @remarks     #Pause_create must be called before this function.
 */
extern Void Pause_test(Pause_Handle hPause);

/**
 * @brief       Called to set processing threads to pause.
 *
 * @param[in]   hPause      #Pause_Handle to pause.
 *
 * @remarks     #Pause_create must be called before this function.
 */
extern Void Pause_on(Pause_Handle hPause);

/**
 * @brief       Called to release processing threads currently paused.
 *
 * @param[in]   hPause      #Pause_Handle to release.
 *
 * @remarks     #Pause_create must be called before this function.
 */
extern Void Pause_off(Pause_Handle hPause);

/**
 * @brief       Deletes a Pause object.
 *
 * @param[in]   hPause      #Pause_Handle of the Paise object to delete.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Pause_create must be called before this function.
 */
extern Int Pause_delete(Pause_Handle hPause);

#if defined (__cplusplus)
}
#endif

/*@}*/

#endif /* ti_sdo_dmai_Pause_h_ */
