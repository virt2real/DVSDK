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
 *  ======== Thread.h ========
 */
/**
 *  @file       ti/sdo/ce/osal/Thread.h
 *
 *  @brief      The Codec Engine OSAL Thread interface.  Provides the user
 *              an OS-independent Thread abstraction.
 */
/**
 *  @defgroup   ti_sdo_ce_osal_Thread     Codec Engine OSAL - Thread
 */

#ifndef ti_sdo_ce_osal_Thread_
#define ti_sdo_ce_osal_Thread_

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup    ti_sdo_ce_osal_THREAD */
/*@{*/

#define Thread_GTNAME "OT"

#define Thread_SUSPENDED   (-666)

#define Thread_MINPRI      1
#define Thread_MAXPRI      15

/*
 *  ======== Thread_Handle ========
 */
typedef struct Thread_Obj *Thread_Handle;

/**
 * @brief       Thread attributes.
 */
typedef struct Thread_Attrs {
    Int         priority;       /**< Task priority */
    Int         stacksize;      /**< Size of stack */
    Int         stackseg;       /**< Segment to allocate stack from */
    Ptr         environ;        /**< Environment pointer */
    String      name;           /**< Printable name */
} Thread_Attrs;

/**
 * @brief       Thread statistics.
 */
typedef struct Thread_Stat {
    Int         stacksize;      /**< Size of the thread's stack. */
    Int         stackused;      /**< Amount of the thread's stack used. */
} Thread_Stat;

extern Thread_Attrs Thread_ATTRS;     /**< Default thread attributes */

/**
 * @brief       Create a thread.
 */
extern Thread_Handle Thread_create(Fxn fxn, Thread_Attrs *attrs, ...);

/**
 * @brief       Delete a thread.
 */
extern Void Thread_delete(Thread_Handle task);

/**
 * @brief       Obtain a thread's priority.
 */
extern Int Thread_getpri(Thread_Handle task);

/**
 * @brief       Obtain a thread's environment.
 */
extern Ptr Thread_getenv(Thread_Handle task);

/**
 * @brief       Obtain a thread's name.
 */
extern String Thread_getname(Thread_Handle task);

/**
 * @brief       Initialize the Thread module.
 */
extern Bool Thread_init(Void);

/**
 * @brief       Finalize the Thread module.
 */
extern Void Thread_exit(Void);

/**
 * @brief       Wait for a thread to exit.
 */
extern Void Thread_join(Thread_Handle task);

/**
 * @brief       Acquire the currently executing thread's handle.
 */
extern Thread_Handle Thread_self(Void);

/**
 * @brief       Set a thread's priority.
 */
extern Int Thread_setpri(Thread_Handle task, Int newpri);


/**
 * @brief       Obtain a thread's statistics.
 */
extern Int Thread_stat(Thread_Handle task, Thread_Stat *buf);

/**
 * @brief       Yield the currently scheduled thread.
 */
extern Void Thread_yield(Void);


/*@}*/

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif
/*
 *  @(#) ti.sdo.ce.osal; 2, 0, 2,427; 12-2-2010 21:24:38; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

