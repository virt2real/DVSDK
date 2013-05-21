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
/**
 *  @file       dbc.h
 *
 *  @brief      Design By Contract Definitions - Provides basic
 *              Design By Contract support, including asserts, preconditions,
 *              and postconditions.
 */

/**
 *  @defgroup   DSPDBC DBC
 *
 *              Design By Contract is a software methodology pioneered by Dr.
 *              Bertrand Meyers.  It utilitizes the concept of preconditions and
 *              postconditions to ensure program correctness.  For additional
 *              reference, please visit
 *              http://archive.eiffel.com/doc/manuals/technology/contract/.
 *
 *  @remarks    To enable the use of DBC in debug builds, add a
 *              "DBC_ASSERTS" define in your makefile or build package.
 */

#ifndef _DBC_
#define _DBC_


/** @ingroup DSPDBC */
/*@{*/


#ifdef __cplusplus
extern "C" {
#endif


/* DBC_ASSERTS is intended to be set to 1 in debug builds */
#if DBC_ASSERTS
#include <sys.h>
#define DBC_assert(c) if (!(c)) { \
        SYS_abort("Assertion Failed: file=%s, line=%d.\n", __FILE__, \
        __LINE__); }            /**< Assert a logical condition to be TRUE. */

#define DBC_require DBC_assert  /**< Assert a precondition to be TRUE. */
#define DBC_ensure  DBC_assert  /**< Assert a postcondition to be TRUE. */

#else

#define DBC_assert(c)   /**< Assert a logical condition to be TRUE. */
#define DBC_require(c)  /**< Assert a precondition to be TRUE. */
#define DBC_ensure(c)   /**< Assert a postcondition to be TRUE. */

#endif


#ifdef __cplusplus
}
#endif /* extern "C" */


/*@}*/ /* ingroup DSPDBC */


#endif /* _DBC_ */

/*
 *  @(#) ti.sdo.fc.utils; 1, 0, 2,286; 12-1-2010 17:26:08; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

