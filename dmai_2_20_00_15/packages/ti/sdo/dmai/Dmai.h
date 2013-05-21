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
 * @defgroup   ti_sdo_dmai_Dmai     Dmai
 *
 * @brief Common header file for all Dmai modules and applications.
 * 
 */

#ifndef ti_sdo_dmai_Dmai_h_
#define ti_sdo_dmai_Dmai_h_

#include <assert.h>
#include <stdio.h>

#include <xdc/std.h>
#include <ti/sdo/utils/trace/gt.h>

/** @ingroup    ti_sdo_dmai_Dmai */
/*@{*/

/*
 * Error codes used by DMAI functions. Negative values are errors,
 * while positive values indicate success.
 */
#define Dmai_EINVAL     -5   /**< Invalid input arguments (failure). */
#define Dmai_ENOMEM     -4   /**< No memory available (failure). */
#define Dmai_EIO        -3   /**< An IO error occured (failure). */
#define Dmai_ENOTIMPL   -2   /**< Functionality not implemented (failure). */
#define Dmai_EFAIL      -1   /**< General failure code (failure). */
#define Dmai_EOK         0   /**< General success code (success). */
#define Dmai_EFLUSH      1   /**< The command was flushed (success). */
#define Dmai_EPRIME      2   /**< The command was primed (success). */
#define Dmai_EFIRSTFIELD 3   /**< Only the first field was processed (success)*/
#define Dmai_EBITERROR   4   /**< There was a non fatal bit error (success). */
#define Dmai_ETIMEOUT    5   /**< The operation was timed out (success). */
#define Dmai_EEOF        6   /**< The operation reached end of file */
#define Dmai_EAGAIN      7   /**< The command needs to be rerun (success). */

/** @brief ***INTERNAL*** Debug message with 0 arguments */
#define Dmai_dbg0(fmt) \
    GT_0trace(ti_sdo_dmai_GTMask, GT_2CLASS, "[" MODULE_NAME "] " fmt)
/** @brief ***INTERNAL*** Debug message with 1 arguments */
#define Dmai_dbg1(fmt, arg1) \
    GT_1trace(ti_sdo_dmai_GTMask, GT_2CLASS, "[" MODULE_NAME "] " fmt, \
              arg1)
/** @brief ***INTERNAL*** Debug message with 2 arguments */
#define Dmai_dbg2(fmt, arg1, arg2) \
    GT_2trace(ti_sdo_dmai_GTMask, GT_2CLASS, "[" MODULE_NAME "] " fmt, \
              arg1, arg2)
/** @brief ***INTERNAL*** Debug message with 3 arguments */
#define Dmai_dbg3(fmt, arg1, arg2, arg3) \
    GT_3trace(ti_sdo_dmai_GTMask, GT_2CLASS, "[" MODULE_NAME "] " fmt, \
              arg1, arg2, arg3)
/** @brief ***INTERNAL*** Debug message with 4 arguments */
#define Dmai_dbg4(fmt, arg1, arg2, arg3, arg4) \
    GT_4trace(ti_sdo_dmai_GTMask, GT_2CLASS, "[" MODULE_NAME "] " fmt, \
              arg1, arg2, arg3, arg4)
/** @brief ***INTERNAL*** Debug message with 5 arguments */
#define Dmai_dbg5(fmt, arg1, arg2, arg3, arg4, arg5) \
    GT_5trace(ti_sdo_dmai_GTMask, GT_2CLASS, "[" MODULE_NAME "] " fmt, \
              arg1, arg2, arg3, arg4, arg5)
/** @brief ***INTERNAL*** Debug message with 6 arguments */
#define Dmai_dbg6(fmt, arg1, arg2, arg3, arg4, arg5, arg6) \
    GT_6trace(ti_sdo_dmai_GTMask, GT_2CLASS, "[" MODULE_NAME "] " fmt, \
              arg1, arg2, arg3, arg4, arg5, arg6)

/** @brief ***INTERNAL*** Error message with 0 arguments */
#define Dmai_err0(fmt) \
    GT_0trace(ti_sdo_dmai_GTMask, GT_7CLASS, "[" MODULE_NAME "] " fmt)
/** @brief ***INTERNAL*** Error message with 1 arguments */
#define Dmai_err1(fmt, arg1) \
    GT_1trace(ti_sdo_dmai_GTMask, GT_7CLASS, "[" MODULE_NAME "] " fmt, \
              arg1)
/** @brief ***INTERNAL*** Error message with 2 arguments */
#define Dmai_err2(fmt, arg1, arg2) \
    GT_2trace(ti_sdo_dmai_GTMask, GT_7CLASS, "[" MODULE_NAME "] " fmt, \
              arg1, arg2)
/** @brief ***INTERNAL*** Error message with 3 arguments */
#define Dmai_err3(fmt, arg1, arg2, arg3) \
    GT_3trace(ti_sdo_dmai_GTMask, GT_7CLASS, "[" MODULE_NAME "] " fmt, \
              arg1, arg2, arg3)
/** @brief ***INTERNAL*** Error message with 4 arguments */
#define Dmai_err4(fmt, arg1, arg2, arg3, arg4) \
    GT_4trace(ti_sdo_dmai_GTMask, GT_7CLASS, "[" MODULE_NAME "] " fmt, \
              arg1, arg2, arg3, arg4)
/** @brief ***INTERNAL*** Error message with 5 arguments */
#define Dmai_err5(fmt, arg1, arg2, arg3, arg4, arg5) \
    GT_5trace(ti_sdo_dmai_GTMask, GT_7CLASS, "[" MODULE_NAME "] " fmt, \
              arg1, arg2, arg3, arg4, arg5)
/** @brief ***INTERNAL*** Error message with 6 arguments */
#define Dmai_err6(fmt, arg1, arg2, arg3, arg4, arg5, arg6) \
    GT_6trace(ti_sdo_dmai_GTMask, GT_7CLASS, "[" MODULE_NAME "] " fmt, \
              arg1, arg2, arg3, arg4, arg5, arg6)

/**
 * @brief       Utility macro for clearing structures.
 */
#define Dmai_clear(x) memset (&(x), 0, sizeof (x))

/**
 * @brief       Macro that can be used to round up 'val' to the closest
 *              multiple of the value passed in 'rounding'.   
 *              
 * @param[in]   val      The value to be rounded
 * @param[in]   rounding The closest multiple of which will be returned. Must be
 *                       a power of 2. 
 *    
 * @retval      Rounded result
 */ 
#define Dmai_roundUp(val, rounding) ( ( (val) & ((rounding) - 1) ) ? \
    (((val) & ~((rounding) - 1)) + (rounding)) : (val) )

/**
 * @brief       ***INTERNAL*** Name of GT Mask used for DMAI.
 */
#define Dmai_gtname "ti.sdo.dmai" 

/**
 * @brief       DSP/BIOS Segment ID from which to allocate all Dmai objects.
 */
#define Dmai_Bios_segid 0

/**
 * @brief Log Levels.
 */
typedef enum {
   /** @brief Default value when log level is not set */
   Dmai_LogLevel_Notset = -1,
   /** @brief No trace output */
   Dmai_LogLevel_None = 0,
   /** @brief Output only errors and warnings */
   Dmai_LogLevel_ErrorsWarnings,
   /** @brief Output all messages */
   Dmai_LogLevel_All
} Dmai_LogLevel;

                                        
#if defined (__cplusplus)
extern "C" {
#endif

/**
 * @brief       Set global DMAI debug level setting. Can be overriden
 *              by the DMAI_DEBUG environment variable on platforms where
 *              it is supported. Note that calling this API will result in all
 *              trace (including CE trace) to be directed to stdout.   
 *              
 * @param[in]   logLevel     The #Dmai_LogLevel to set to.
 *    
 * @retval      DMAI_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h. 
 * 
 * @remarks     #Dmai_init must be called before this function.   
 */ 
extern Int Dmai_setLogLevel(Dmai_LogLevel logLevel);

/**
 * @brief       Global GT trace mask declaration.
 */
extern GT_Mask ti_sdo_dmai_GTMask;

/**
 * @brief       Initializes DMAI. Must be called before any other DMAI
 *              module function.
 */
extern Void Dmai_init();

#if defined (__cplusplus)
}
#endif

/*@}*/

#endif /* ti_sdo_dmai_Dmai_h_ */
