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
 *  ======== GT_config_posix.c ========
 *  Description: GT_configuration for posix based systems.
 */
/* we define _XOPEN_SOURCE 500 to get declaration of pthread_mutexattr_settype
 * in the MonteVista headers
 */
#define _XOPEN_SOURCE 500

#include <xdc/std.h>

#include <pthread.h>

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>

#include <ti/sdo/utils/trace/gt.h>

#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/ce/osal/Global.h>
#include "GT_config_posix.h"


static Void   cleanup(Void);


/* REMINDER: if you add an initialized static var, reinitialize it at cleanup */
static Bool curInit = FALSE;

/* this one is global -- a backdoor for TraceUtil */
FILE *GT_config_traceOutStream = NULL;

/* this is a FILE pointer we opened, if any -- we remember it for closing */
static FILE  *traceOutStreamOpenedHere = NULL;

static Bool   GTConfig_gettimeofdayInit = FALSE;
static UInt32 initTime   = 0;

static pthread_mutex_t     mutex;
static pthread_mutexattr_t mattrs;

/*
 *  ======== GT_config_setOutTrace ========
 * [dm]TODO:M expose this func in an interface
 */
Void GT_config_setOutTrace(FILE *newOutTrace)
{
    GT_config_traceOutStream = newOutTrace;

    /* use line buffering to ensure timely output of trace */
    setvbuf(GT_config_traceOutStream, (char *)NULL, _IOLBF, 0);
}

/*
 *  ======== GTConfig_posixInit ========
 */
Int GTConfig_posixInit(Void)
{
    String fileName;
    String fileFlags = "a"; /* assign here to keep compiler quiet */

    if (curInit != TRUE) {

        curInit = TRUE;

        if ((fileName = getenv("CE_TRACEFILE")) != NULL) {
            if ((fileFlags = getenv("CE_TRACEFILEFLAGS")) == NULL) {
                fileFlags = "a";
            }
            GT_config_traceOutStream = fopen(fileName, fileFlags);
            if (GT_config_traceOutStream != NULL) {
                Int flags = fcntl(fileno(GT_config_traceOutStream), F_GETFD);
                if (flags != -1) {
                    fcntl(fileno(GT_config_traceOutStream), F_SETFD,
                         flags | FD_CLOEXEC);
                }
                traceOutStreamOpenedHere = GT_config_traceOutStream;
            }
        }
        if (GT_config_traceOutStream == NULL) {
            GT_config_traceOutStream = stdout;
            if ((fileName != NULL) && (fileName[0] != '\0')) {
                printf("Warning: could not open file '%s' in mode '%s' "
                    "for writing trace.\n", fileName, fileFlags);
            }
        }

        /* use line buffering to ensure timely output of trace */
        setvbuf(GT_config_traceOutStream, (char *)NULL, _IOLBF, 0);

        /* initialize mutex */
        pthread_mutexattr_init(&mattrs);
        /* "adaptive" below means "fast", as opposed to "recursive" */
        pthread_mutexattr_settype(&mattrs, PTHREAD_MUTEX_ADAPTIVE_NP);
        pthread_mutex_init(&mutex,  &mattrs);

        /* call Global_atexit() to schedule our cleanup. Global module
         * has not been initialized yet, but he knows we'll call him
         * here so he knows how to deal with this call.
         */
         Global_atexit((Fxn)cleanup);
    }
    return (1);
}

/*
 *  ======== cleanup ========
 */
static Void cleanup()
{
    Int status;

    if (curInit != FALSE) {

        curInit = FALSE;

        if (traceOutStreamOpenedHere != NULL) {
            fclose(traceOutStreamOpenedHere);
        }

        status = pthread_mutex_destroy(&mutex);

        /* destroy fails try to unlock before freeing the object */
        if (status != 0) {
            do {
                status = pthread_mutex_unlock(&mutex);
            } while (status == 0);
            pthread_mutex_destroy(&mutex);
        }
        pthread_mutexattr_destroy(&mattrs);

        /* reinit static vars */
        GT_config_traceOutStream = NULL;
        traceOutStreamOpenedHere = NULL;
        GTConfig_gettimeofdayInit = FALSE;
        initTime                 = 0;
    }
}


/*
 *  ======== GTConfig_tracePrintf ========
 */
Void GTConfig_tracePrintf(String format, ...)
{
    va_list va;

    if (GT_config_traceOutStream == NULL) {
        GT_config_traceOutStream = stdout;
    }

    va_start(va, format);
    vfprintf(GT_config_traceOutStream, format, va);
    va_end(va);

    /* don't flush GT_config_traceOutStream because flush is *very* expensive;
     * we use line buffering instead (see init()).
     */
    /* fflush(GT_config_traceOutStream); */
}


/*
 *  ======== GTConfig_threadId ========
 */
Int GTConfig_threadId(Void)
{
    pthread_t id = pthread_self();
    return ((Int)id);
}


/*
 *  ======== GTConfig_gettimeofday ========
 *  return wallclock time in usec (starting from the from the first call to
 *  this function)
 */
UInt32 GTConfig_gettimeofday(Void)
{
    struct timeval time;

    if (GTConfig_gettimeofdayInit == FALSE) {
        GTConfig_gettimeofdayInit = TRUE;
        gettimeofday(&time, NULL);
        initTime = time.tv_sec;
    }

    gettimeofday(&time, NULL);
    return ((time.tv_sec - initTime) * 1000000 + time.tv_usec);
}

/*
 *  ======== GTConfig_pthreadLock ========
 */
Int GTConfig_pthreadLock(Void)
{
    pthread_mutex_lock(&mutex);
    return(1);
}


/*
 *  ======== GTConfig_pthreadUnlock ========
 */
Int GTConfig_pthreadUnlock(Void)
{
    pthread_mutex_unlock(&mutex);
    return (1);
}
/*
 *  @(#) ti.sdo.ce.osal.linux; 2, 0, 1,181; 12-2-2010 21:24:45; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

