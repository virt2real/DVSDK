/*
 * Thread.h
 *
 * Thread Interface
 *
 * Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/

#ifndef ti_osal_THREAD_
#define ti_osal_THREAD_

#include <xdc/std.h>

// Status returned by compareOsPriorities when an error occurs (Int)-2
#define Thread_COMPAREPRI_FAILED -2
// Status returned by getPri when an error occurs (Int)-2
#define Thread_GETPRI_FAILED -2
// Invalid OS priority value (Int)Thread.Priority_INVALID
#define Thread_INVALID_PRIORITY Thread_Priority_INVALID

// Thread priorities which are mapped to OS specific value
typedef enum Thread_Priority {
    Thread_Priority_LOWEST,
    Thread_Priority_BELOW_NORMAL,
    Thread_Priority_NORMAL,
    Thread_Priority_ABOVE_NORMAL,
    Thread_Priority_HIGHEST,
    Thread_Priority_INVALID
} Thread_Priority;

// Typedef for thread function
typedef Void (*Thread_RunFxn)(IArg);

// Struct to hold thread statistics from stat
typedef struct Thread_Stat {
    SizeT stackSize;
    SizeT stackUsed;
} Thread_Stat;

// Instance config-params structure
typedef struct Thread_Params {
    String name;		// anme of thread
    IArg arg;                   // Thread function argument. Default is 0
    Ptr tls;                    // User-specified thread local storage
    Int osPriority;             // OS specific thread priority
    Thread_Priority priority;   // Thread priority;
    SizeT stackSize;            // Thread stack size;
} Thread_Params;

typedef struct Thread_Object* Thread_Handle;

//Init Thread module
Void Thread1_init(Void);
// Compare two os specific priority values and find out which one represents a higher priority
Int Thread1_compareOsPriorities( Int p1, Int p2 );
// Acquire the currently executing thread's handle
Thread_Handle Thread1_self();
// Yield the currently scheduled thread
Bool Thread1_yield();
// Sleep for certain number of microseconds
Bool Thread1_sleep( UInt timeout );

// Initialize this config-params structure with supplier-specified defaults before instance creation
Void Thread1_Params_init( Thread_Params *params );
// Allocate and initialize a new instance object and return its handle
Thread_Handle Thread1_create( Thread_RunFxn fxn, Thread_Params *params );
// Finalize and free this previously allocated instance object
Void Thread1_delete( Thread_Handle *handleP );
// Obtain a thread's environment
Ptr Thread1_getTls( Thread_Handle handle );
// Obtain a thread's os specific priority
Int Thread1_getOsPriority( Thread_Handle handle );
// Obtain a thread's priority
Thread_Priority Thread1_getPriority( Thread_Handle handle );
// Join on a Thread
Bool Thread1_join( Thread_Handle handle );
// Change a thread's environment
Void Thread1_setTls( Thread_Handle handle, Ptr env );
// Set a thread's os priority
Bool Thread1_setOsPriority( Thread_Handle handle, Int newPri );
// Set a thread's priority
Bool Thread1_setPriority( Thread_Handle handle, Thread_Priority newPri );
// Get thread statistics
Bool Thread1_stat( Thread_Handle handle, Thread_Stat *buf );

#endif

