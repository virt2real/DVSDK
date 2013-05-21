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
 * @defgroup   ti_sdo_dmai_Time     Time
 *
 * @brief This interface enables easy benchmarking using microseconds as unit.
 *
 * The maximum timespan measurable (delta or total) depends on the number of
 * bits of an unsigned long on your system (X), and is 2^X us. With 32-bit
 * unsigned longs this means 2^32 us which is almost 72 minutes.
 *
 * Typical usage (without error checking):
 *
 * @code
 *   #include <xdc/std.h>
 *   #include <ti/sdo/dmai/Dmai.h>
 *   #include <ti/sdo/dmai/Time.h>
 *   Uint32 time1, time2, timeTot;
 *   Time_Attrs tAttrs = Time_Attrs_DEFAULT;
 *   Time_Handle hTime;
 *
 *   Dmai_init();
 *   hTime = Time_create(&tAttrs);
 *   Time_reset(hTime);
 *   fxn1();
 *   Time_delta(hTime, &time1);
 *   fxn2();
 *   Time_delta(hTime), &time2);
 *   Time_total(hTime, &timeTot);
 *   printf("Time: fxn1 %u us, fxn2 %u us and total time %u us\n",
 *           (Uns) time1, (Uns) time2, (Uns) timeTot);
 * @endcode
 */

#ifndef ti_sdo_dmai_Time_h_
#define ti_sdo_dmai_Time_h_

#include <xdc/std.h>

#include <ti/sdo/dmai/Dmai.h>

/** @ingroup    ti_sdo_dmai_Time */
/*@{*/

/**
 * @brief       Handle through which to reference a Time Object.
 */
typedef struct Time_Object *Time_Handle;

/**
 * @brief       Attributes used to create a Time.
 * @see         Time_Attrs_DEFAULT.
 */
typedef struct Time_Attrs {
    /** @brief Currently no attributes for this module, but this may change. */
    Int dummy;
} Time_Attrs;

/**
 * @brief       Default attributes for a Time.
 */
extern const Time_Attrs Time_Attrs_DEFAULT;

#if defined (__cplusplus)
extern "C" {
#endif

/**
 * @brief       Creates a Time Object to use for benchmarking. Must be called
 *              before a #Time_Handle can be used for subsequent operations.
 *
 * @param[in]   attrs       #Time_Attrs to use for creating the Time Object.
 *
 * @retval      Handle for use in subsequent operations (see #Time_Handle).
 * @retval      NULL for failure.
 */
extern Time_Handle Time_create(Time_Attrs *attrs);

/**
 * @brief       Deletes a Time Object. After this call has been made no
 *              following Time API calls can be made on this #Time_Handle.
 *
 * @param[in]   hTime       The #Time_Handle of the Time Object to delete.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Time_create must be called before this function.
 */
extern Int Time_delete(Time_Handle hTime);

/**
 * @brief       Resets the state of the timer. Can be called multiple times
 *              and must be called before the #Time_delta and #Time_total
 *              functions are called.
 *
 * @param[in]   hTime       #Time_Handle to the Time Object to reset.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Time_create must be called before this function.
 */
extern Int Time_reset(Time_Handle hTime);

/**
 * @brief       Calculates the delta in microseconds between now and the last
 *              time delta was called (or when reset was called if that is
 *              more recent) on this #Time_Handle.
 *
 * @param[in]   hTime       Handle of the timer to calculate a delta on.
 * @param[out]  deltaPtr    Pointer to where the resulting value will be
 *                          stored if the operation was successful.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Time_create must be called before this function.
 */
extern Int Time_delta(Time_Handle hTime, Uint32 *deltaPtr);

/**
 * @brief       Calculates the delta in microseconds between now and the last
 *              time reset was called on this timer object.
 *
 * @param[in]   hTime       Handle of the timer to calculate a delta on.
 * @param[out]  totalPtr    Pointer to where the resulting value will be
 *                          stored if the operation was successful.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Time_create must be called before this function.
 */
extern Int Time_total(Time_Handle hTime, Uint32 *totalPtr);

#if defined (__cplusplus)
}
#endif

/*@}*/

#endif /* ti_sdo_dmai_Time_h_ */
