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

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sched.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>

#include <xdc/std.h>
#include <ti/sdo/ce/bioslog/LogClient.h>
#include <ti/sdo/utils/trace/gt.h>
#include <ti/sdo/ce/osal/Lock.h>
#include <ti/sdo/ce/osal/Global.h>

#include "TraceUtil.h"

#define ERR(fmt, args...)  fprintf(stderr, "TraceUtil> Error: "   fmt, ## args)
#define WARN(fmt, args...) fprintf(stderr, "TraceUtil> Warning: " fmt, ## args)
#define INFO(fmt, args...) if (verbose>0) fprintf(stderr, "TraceUtil> " fmt, ## args)
#define DBG(fmt, args...)  if (verbose>1) fprintf(stderr, "TraceUtil> " fmt, ## args)

#define MAXCMDLINESIZE 512

#define TRACECMD_ARMTRACEMASK     "tracemask="      /* followed by mask value */
#define TRACECMD_DSP0TRACEMASK    "dsp0tracemask="  /* followed by mask value */
#define TRACECMD_REFRESHPERIOD    "refreshperiod="  /* followed by number in ms, 0 = no refresh */
#define TRACECMD_RESETFILES       "resetfiles"      /* resets all open files */
#define TRACECMD_QUIT             "quit"            /* exits pipe thread */

#define SLEEPWHENNOREFRESH        (100 * 1000)      /* us to sleep when refresh = 0 */

/* External configuration generated variables */
extern String  TraceUtil_localTraceMask;
extern String  TraceUtil_localTraceFile;
extern String  TraceUtil_dsp0TraceMask;
extern String  TraceUtil_dsp0TraceFile;
extern String  TraceUtil_dsp0BiosFile;
extern String  TraceUtil_traceFileFlags;
extern Int     TraceUtil_refreshPeriod;
extern String  TraceUtil_cmdPipeFile;
extern String* TraceUtil_cmdAliases[];

/* TraceUtil_cmdAliases above may look like:
 * String *traceUtil_cmdAliases[] = {
 *     ptr to { "socrates=on",  "tracemask=*+5", "dsp0tracemask=+5", ..., NULL },
 *     ptr to { "socrates=off", "tracemask=*-5", "dsp0tracemask=-5", ..., NULL },
 *     NULL
 * };
 */

extern Int Global_useLinkArbiter;

/* REMINDER: if you add an initialized static var, reinitialize it at cleanup */
static Bool          curInit             = FALSE;
static FILE         *dsp0BiosFilePtr     = NULL;
static FILE         *dsp0TraceFilePtr    = NULL;
static FILE         *localTraceFilePtr   = NULL;
static String        cmdPipeFile         = NULL;
static FILE         *cmdPipeFilePtr      = NULL;
static String        dsp0mask            = NULL;
static Int           refresh;
static Int           verbose             = 0;

static pthread_t     traceThread         = NULL;
static Bool          traceThreadCreated  = FALSE;
static Bool          threadCreateFailed  = FALSE;
static Engine_Handle hEngine             = NULL;
static Server_Handle hServer             = NULL;
static Int           traceToken          = 0;

static pthread_t     pipeThread          = NULL;
static Bool          pipeThreadCreated   = FALSE;

static Bool          quit                = FALSE;

static Lock_Handle   moduleLock          = NULL;

extern Void GT_config_setOutTrace(FILE *newOutTrace);

/*
 * ======== fileSetCloseOnExec ========
 */
static Void fileSetCloseOnExec(FILE * file)
{
    if (file != NULL) {
        Int flags = fcntl( fileno( file ), F_GETFD );
        if (flags != -1) {
            fcntl( fileno( file ), F_SETFD, flags | FD_CLOEXEC);
        }
    }
}

/*
 * ======== processPipeCommand ========
 */
static Void processPipeCommand(String command)
{
    Int    i, j, n;
    String mask;

    DBG( "Processing pipe command '%s'\n", command );

    /* first check if this command is an alias */
    for (i = 0; TraceUtil_cmdAliases[i] != NULL; i++) {
        if (!strcmp( TraceUtil_cmdAliases[i][0], command )) {
            for (j = 1; TraceUtil_cmdAliases[i][j] != NULL; j++) {
                processPipeCommand( TraceUtil_cmdAliases[i][j] );
            }
            return; /* we have finished processing the alias */
        }
    }

    if (strstr( command, TRACECMD_ARMTRACEMASK ) == command) {
        mask = command + strlen( TRACECMD_ARMTRACEMASK );

        INFO( "Setting Arm trace mask to '%s'\n", mask );
        GT_set( mask );
    }
    else if (strstr( command, TRACECMD_DSP0TRACEMASK ) == command) {
        mask = command + strlen( TRACECMD_DSP0TRACEMASK );

        INFO( "Setting DSP0 trace mask to '%s'\n", mask );

        if (moduleLock != NULL) {
            Lock_acquire( moduleLock );
        }

        Engine_setTrace(hEngine, mask);

        if (moduleLock != NULL) {
            Lock_release( moduleLock );
        }
    }
    else if (strstr( command, TRACECMD_REFRESHPERIOD ) == command) {
        n = atoi( command + strlen( TRACECMD_REFRESHPERIOD ) );

        INFO( "Setting trace refresh period to %d ms.\n", n );

        refresh = n * 1000;
    }
    else if (strstr( command, TRACECMD_RESETFILES ) == command) {
        INFO( "Resetting trace/log files.\n" );
        if (localTraceFilePtr != NULL   &&
            localTraceFilePtr != stdout &&
            localTraceFilePtr != stderr) {
            DBG( "Resetting Arm trace file.\n" );

            /* rewind file (stdio operation) then truncate it (OS operation) */
            rewind( localTraceFilePtr );
            ftruncate( fileno( localTraceFilePtr ), 0L );
        }
        if (dsp0TraceFilePtr != NULL   &&
            dsp0TraceFilePtr != stdout &&
            dsp0TraceFilePtr != stderr) {
            DBG("Resetting DSP trace file.\n");
            rewind(dsp0TraceFilePtr);
            ftruncate(fileno(dsp0TraceFilePtr), 0L);
        }
        if (dsp0BiosFilePtr != NULL) {
            DBG("Resetting DSP log file.\n");
            rewind(dsp0BiosFilePtr);
            ftruncate(fileno(dsp0BiosFilePtr), 0L);
        }
    }
    else {
        WARN("Unknown trace pipe command '%s'\n", command);
    }

}

/*
 * ======== pipeThrFxn ========
 */
static void *pipeThrFxn(void *arg)
{
    Char   cmdLine[ MAXCMDLINESIZE ], *s;
    struct stat statBuf;

    DBG("Trace pipe command thread started\n");

    pipeThreadCreated = TRUE;

    for (;;) {

        DBG("Opening command pipe named '%s'\n", cmdPipeFile);

        /* check if the specified pipe name is a real pipe */
        if (!stat( cmdPipeFile, &statBuf )) {
            if (!S_ISFIFO(statBuf.st_mode)) {
                WARN("Specified command pipe file \"%s\" is not a pipe (fifo)\n",
                     cmdPipeFile);
                return NULL;
            }
        }

        /* open the pipe. If the pipe exists but there's no writer, this is a
         * blocking call, until the writer appears
         */
        cmdPipeFilePtr = fopen(cmdPipeFile, "r");

        if (cmdPipeFilePtr == NULL) {
            DBG("Creating named pipe '%s' as it doesn't exist\n", cmdPipeFile);
            unlink( cmdPipeFile );
            if (mkfifo( cmdPipeFile, 0777 )) {
                WARN("Failed to create trace command pipe \"%s\"\n",
                     cmdPipeFile);
                return NULL;
            }
            /* the permissions above were and-ed by user's umask, so we force
             * the "rw all" flags here
             */
            chmod(cmdPipeFile, 0666);

            /* same thing -- blocking until the writer shows up */
            cmdPipeFilePtr = fopen(cmdPipeFile, "r");
            if (cmdPipeFilePtr == NULL) {
                WARN("Failed to open created trace command pipe \"%s\"\n",
                     cmdPipeFile);
                return NULL;
            }
        }
        fileSetCloseOnExec( cmdPipeFilePtr );

        DBG( "Reading command pipe\n" );

        signal(SIGPIPE, SIG_IGN);

        for (;;) {
            s = fgets( cmdLine, MAXCMDLINESIZE, cmdPipeFilePtr );

            /* if the return value is zero, it means the writer has closed the
             * pipe, e.g. when one does echo "hello there" >namedPipe
             * First the reader will find "hello there\n", then it will find
             * NULL. In that case, the reader like us should reopen the pipe.
             */
            if (s == NULL) {
                fclose( cmdPipeFilePtr );
                break;
            }

            if (cmdLine[ strlen( cmdLine ) - 1 ] == '\n') {
                cmdLine[ strlen( cmdLine ) - 1 ] = '\0';
            }

            if (!strcmp( cmdLine, TRACECMD_QUIT )) {
                DBG("Pipe thread received quit command, quitting [2]\n");
                fclose( cmdPipeFilePtr );
                /* unlink( cmdPipeFile ); -- no real need to do it*/
                return (void *)1;
            }

            processPipeCommand( cmdLine );
        }

        /* so the pipe "instance" we've been using is closed. Let's open
         * another in case the user ever wants to write something else.
         * We can only leave this state of existance by being killed.
         */
     }
}

/*
 * ======== traceThrFxn ========
 */
static void *traceThrFxn(void *arg)
{
    String engineName = (String) arg;
    Server_Status status;
    FILE *f;

    /* determine DSP line prefix: "[DSP] " if local and DSP trace end up at the same
     * file, otherwise ""
     */
    char *dspPrefix = (dsp0TraceFilePtr == localTraceFilePtr) ? "[DSP] " : "";

    DBG("Trace thread started\n");

    hEngine = Engine_open(engineName, NULL, NULL);

    if (hEngine == NULL) {
        ERR("Failed to open codec engine \"%s\"\n", engineName);
        threadCreateFailed = TRUE;
        return ((void *) -1);
    }

    /* for multi-process situations, make sure can acquire server trace */
    if (Global_useLinkArbiter) {

        /* get server handle */
        hServer = Engine_getServer(hEngine);

        /* cleanup and abort if can't get server handle */
        if (hServer == NULL) {
            Engine_close(hEngine);
            ERR("Failed to get server handle\n");
            threadCreateFailed = TRUE;
            return ((void *) -1);
        }

        /* request server trace token */
        status = Server_connectTrace(hServer, &traceToken);

        /* cleanup and abort if trace could not acquire trace token */
        if (status != Server_EOK) {
            Engine_close(hEngine);
            ERR("Failed to connect for server trace\n");
            threadCreateFailed = TRUE;
            return ((void *) -1);
        }
    }

    /* else: if single-process, don't need to explictly connect for trace */

    Engine_setTrace(hEngine, dsp0mask);

    moduleLock = Lock_create(NULL);
    if (moduleLock == NULL) {
        WARN("Could not create pthread mutex.\n");
    }

    /* create the pipe thread now */
    if (cmdPipeFile != NULL && cmdPipeFile[0] != '\0') {
        if (pthread_create(&pipeThread, NULL, pipeThrFxn, NULL)) {
            ERR("Failed to create pipe thread\n");
        } else {
            /* run the thread just created so it can immediately execute
             * pending cmdPipe trace commands -- in case there are any
             */
            while (pipeThreadCreated == FALSE) {
                sched_yield();
            }
        }
    }

    /* TODO: remove? will LogClient_connect be inside CE? */
    /*
     * Note, call LogClient_connect() before releasing the main thread to
     * avoid context switching away _during_ the connect() call - which could
     * result in a skewed timesynch log.
     */
    if (dsp0BiosFilePtr != NULL) {
        LogClient_connect();
    }

    /* Release the spinning main thread to run */
    traceThreadCreated = TRUE;

    while (!quit) {

        if (refresh > 0) {

            DBG("Writing DSP logs\n");
            if (moduleLock != NULL) {
                Lock_acquire( moduleLock );
            }
            Engine_fwriteTrace(hEngine, dspPrefix, dsp0TraceFilePtr);

            if (dsp0BiosFilePtr != NULL) {
                LogClient_fwriteLogs(dsp0BiosFilePtr);
            }
            if (moduleLock != NULL) {
                Lock_release( moduleLock );
            }

            DBG("Sleeping for %d us\n", refresh);
            usleep(refresh);
        } else {
            DBG("Sleeping for %d us\n", SLEEPWHENNOREFRESH);
            usleep( SLEEPWHENNOREFRESH );
        }
    }

    if (refresh > 0) {

        DBG("Trace thread exiting, writing final DSP logs\n");

        /* try to collect anything that remained one more time */
        if (moduleLock != NULL) {
            Lock_acquire( moduleLock );
        }

        Engine_fwriteTrace(hEngine, dspPrefix, dsp0TraceFilePtr);

        if (dsp0BiosFilePtr != NULL) {
            LogClient_fwriteLogs(dsp0BiosFilePtr);
        }

        if (moduleLock != NULL) {
            Lock_release( moduleLock );
        }
    }

    if (dsp0BiosFilePtr != NULL) {
        LogClient_disconnect();
    }

    /* for multi-process situations, release trace token back to RMS */
    if (Global_useLinkArbiter) {
        Server_disconnectTrace(hServer, traceToken);
    }

    Engine_close(hEngine);

    DBG("Quitting trace thread\n");

    /* and killing our offspring. */
    if (pipeThread != NULL) {
        DBG("Telling pipe thread to quit\n");
        f = fopen(cmdPipeFile, "w");
        if (f != NULL) {
            fputs(TRACECMD_QUIT, f);
            fclose(f);
            DBG("Wrote quit command, waiting for the pipe thread to join\n");
            if (pthread_join(pipeThread, NULL)) {
                ERR("Failed to join pipe thread\n");
            }
            DBG("Pipe thread joined.\n");
        }
    }

    return ((void *) 1);
}

/*
 * ======== TraceUtil_init ========
 */
Void TraceUtil_init()
{
    String mask;
    String fileName;
    String flags;
    String s;
    Char   armTraceFileName[ MAXCMDLINESIZE ];

    extern Void GT_config_setOutTrace(FILE *newOutTrace);

    if (getenv( "CE_DEBUG" ) != NULL) {
        return;
    }

    if (curInit == TRUE) {
        return;
    }
    curInit = TRUE;

    s = getenv("TRACEUTIL_VERBOSE");
    if (s != NULL) {
        verbose = (s[0] == '2' ? 2 : 1);
    }

    INFO("Relevant environment variables:\n");
    #define INFO_ENV(env,pad) INFO("%s %s= %s\n", \
            (env), (pad), getenv(env) ? getenv(env) : "undefined")
    INFO_ENV("CE_TRACE", "               ");
    INFO_ENV("CE_TRACEFILE", "           ");
    INFO_ENV("TRACEUTIL_DSP0TRACEFILE", "");
    INFO_ENV("TRACEUTIL_DSP0BIOSFILE", " ");
    INFO_ENV("TRACEUTIL_DSP0TRACEMASK", "");
    INFO_ENV("TRACEUTIL_REFRESHPERIOD", "");
    INFO_ENV("CE_TRACEFILEFLAGS", "      ");
    INFO_ENV("TRACEUTIL_CMDPIPE", "      ");
    INFO_ENV("TRACEUTIL_VERBOSE", "      ");

    /*
     * We run after GT has performed initialization but before
     * anything has been printed yet.
     */

    flags = getenv("CE_TRACEFILEFLAGS");

    if (flags == NULL) {
        flags = TraceUtil_traceFileFlags;
    }
    if (flags == NULL || flags[0] == '\0') {
        flags = "w";
    }

    /* Local trace file */
    fileName = getenv("CE_TRACEFILE");

    if (fileName == NULL) {
        fileName = TraceUtil_localTraceFile;
    }

    INFO("Local trace file name: %s\n", (fileName && fileName[0]) ?
         fileName : "stdout");

    armTraceFileName[0] = '\0';

    /* NULL means stdout */
    if (fileName != NULL && fileName[0] != '\0') {
        localTraceFilePtr = fopen(fileName, flags);

        if (localTraceFilePtr == NULL) {
            WARN("Failed to open local log file \"%s\", using stdout\n",
                fileName);
            localTraceFilePtr = stdout;
        } else {
            strncpy(armTraceFileName, fileName, MAXCMDLINESIZE);
            fileSetCloseOnExec(localTraceFilePtr);
        }
    }
    else {
        localTraceFilePtr = stdout;
    }

    GT_config_setOutTrace(localTraceFilePtr);

    /* DSP CE trace file */
    fileName = getenv("TRACEUTIL_DSP0TRACEFILE");

    if (fileName == NULL) {
        fileName = TraceUtil_dsp0TraceFile;
    }

    INFO("DSP CE trace file name: %s\n", (fileName && fileName[0]) ?
         fileName : "stdout");

    /* NULL means stdout */
    if (fileName != NULL && fileName[0] != '\0') {

        if (!strcmp(armTraceFileName, fileName)) {
            /* local and DSP trace names are the same */
            dsp0TraceFilePtr = localTraceFilePtr;
        } else {
            dsp0TraceFilePtr = fopen(fileName, flags);
            if (dsp0TraceFilePtr == NULL) {
                WARN("Failed to open dsp CE log file \"%s\", using stdout\n",
                    fileName);
                dsp0TraceFilePtr = stdout;
            } else {
                fileSetCloseOnExec(dsp0TraceFilePtr);
            }
        }
    }
    else {
        dsp0TraceFilePtr = stdout;
    }

    /* DSP/BIOS trace file */
    fileName = getenv("TRACEUTIL_DSP0BIOSFILE");

    if (fileName == NULL) {
        fileName = TraceUtil_dsp0BiosFile;
    }

    INFO("DSP/BIOS log file name: %s\n", (fileName && fileName[0]) ?
         fileName : "none");

    if (fileName != NULL && fileName[0] != '\0') {
        dsp0BiosFilePtr = fopen(fileName, flags);

        if (dsp0BiosFilePtr == NULL) {
            WARN("Failed to open dsp/bios log file \"%s\", disabling log\n",
                fileName);
        } else {
            fileSetCloseOnExec(dsp0BiosFilePtr);
        }
    }

    /* trace command pipe we open in the separate thread -- because whoever comes
     * first to the pipe is blocked until another pipe party arives. So we don't
     * want to block here, in the main thread, and we only determine its name.
     */
    cmdPipeFile = getenv("TRACEUTIL_CMDPIPE");

    if (cmdPipeFile == NULL) {
        cmdPipeFile = TraceUtil_cmdPipeFile;
    }
    INFO("Command pipe name: %s\n", (cmdPipeFile && cmdPipeFile[0]) ?
         cmdPipeFile : "none");

    /* Set the local trace mask */
    mask = getenv("CE_TRACE");

    if (mask == NULL) {
        mask = TraceUtil_localTraceMask;
    }

    INFO("Arm trace mask: \"%s\"\n", mask);
    GT_set(mask);

    /* Set the remote trace mask */
    dsp0mask = getenv("TRACEUTIL_DSP0TRACEMASK");

    if (dsp0mask == NULL) {
        dsp0mask = TraceUtil_dsp0TraceMask;
    }

    INFO("DSP trace mask: \"%s\"\n", dsp0mask);
    setenv("CE_DSP0TRACE", dsp0mask, 1);

    Global_atexit((Fxn)TraceUtil_exit);
}

/*
 * ======== TraceUtil_start ========
 */
Int TraceUtil_start(String engineName)
{
    String         refreshPeriod;
    Bool           hasServer = FALSE;
    Int            i;
    Int            nAlgs;
    Engine_AlgInfo algInfo;
    Engine_Error   status;

    if (getenv( "CE_DEBUG" ) != NULL) {
        printf( "TraceUtil_start> note: CE_DEBUG env. var is set, so TraceUtil "
                "is not active (unset CE_DEBUG if you need TraceUtil)\n" );
        return (TRACEUTIL_SUCCESS);
    }

    /*
     *  Determine whether or not this engine has a server. If not, do not
     *  start the trace thread.
     */
    algInfo.algInfoSize = sizeof(Engine_AlgInfo);
    status = Engine_getNumAlgs(engineName, &nAlgs);
    if (status != Engine_EOK) {
        ERR("TraceUtil_start((\"%s\"): Failed to get engine information\n",
                engineName);
        return (TRACEUTIL_FAILURE);
    }

    for (i = 0; i < nAlgs; i++) {
        status = Engine_getAlgInfo(engineName, &algInfo, i);

        if (status != Engine_EOK) {
            ERR("TraceUtil_start((\"%s\"): Failed to get engine information\n",
                    engineName);
            return (TRACEUTIL_FAILURE);
        }

        if (algInfo.isLocal == FALSE) {
            hasServer = TRUE;
            break;
        }
    }

    if (!hasServer) {
        WARN("TraceUtil_start(\"%s\"): not starting trace thread since "
                "engine has no remote algs\n",
                engineName);

        /* TODO: Return success or failure in this case? */
        return (TRACEUTIL_FAILURE);
    }

    /* Get the refresh period */
    refreshPeriod = getenv("TRACEUTIL_REFRESHPERIOD");

    if (refreshPeriod != NULL) {
        refresh = atoi(refreshPeriod) * 1000;
    }
    else {
        refresh = TraceUtil_refreshPeriod * 1000;
    }

    INFO("DSP Trace refresh period: %d ms\n", refresh / 1000);

    /* create the collection thread if either the refresh period
     * is non-0, or there is a pipe option
     */
    if ((refresh != 0) ||
        (cmdPipeFile != NULL && cmdPipeFile[0] != '\0') ) {
        if (pthread_create(&traceThread, NULL, traceThrFxn,
                (void *) engineName)) {
            ERR("Failed to create log thread\n");
            return (TRACEUTIL_FAILURE);
        }
        /* make sure this thread runs before we continue */
        while (traceThreadCreated == FALSE) {
            sched_yield();
            if (threadCreateFailed == TRUE) {
                ERR("Aborting TraceUtil_start\n");
                return (TRACEUTIL_FAILURE);
            }
        }
    }

    return (TRACEUTIL_SUCCESS);
}

/*
 * ======== TraceUtil_stop ========
 */
Int TraceUtil_stop(Void)
{
    quit = TRUE;

    DBG("TraceUtil_stop called\n");

    if (traceThread != NULL) {
        if (pthread_join(traceThread, NULL)) {
            ERR("Failed to join log thread\n");
            return (TRACEUTIL_FAILURE);
        }
    }

    traceThread = NULL;
    hEngine = NULL;
    quit = FALSE;

    return (TRACEUTIL_SUCCESS);
}

/*
 * ======== TraceUtil_exit ========
 */
Void TraceUtil_exit()
{
    if (curInit == FALSE) {
        return;
    }
    curInit = FALSE;

    DBG("TraceUtil_exit called\n");

    if (moduleLock != NULL) {
        Lock_delete(moduleLock);
    }

    if (dsp0BiosFilePtr != NULL) {
        fflush(dsp0BiosFilePtr);
        fclose(dsp0BiosFilePtr);
    }
    if ((dsp0TraceFilePtr != NULL) && (dsp0TraceFilePtr != stdout) &&
        (dsp0TraceFilePtr != stderr) &&
        (dsp0TraceFilePtr != localTraceFilePtr)) {
        fflush(dsp0TraceFilePtr);
        fclose(dsp0TraceFilePtr);
    }
    if ((localTraceFilePtr != NULL) && (localTraceFilePtr != stdout) &&
        (localTraceFilePtr != stderr)) {
        fflush(localTraceFilePtr);
        fclose(localTraceFilePtr);
    }

    /* re-initialize static vars */
    dsp0BiosFilePtr     = NULL;
    dsp0TraceFilePtr    = NULL;
    localTraceFilePtr   = NULL;
    cmdPipeFile         = NULL;
    cmdPipeFilePtr      = NULL;
    dsp0mask            = NULL;
    verbose             = 0;
    traceThread         = NULL;
    traceThreadCreated  = FALSE;
    threadCreateFailed  = FALSE;
    hEngine             = NULL;
    hServer             = NULL;
    traceToken          = 0;
    pipeThread          = NULL;
    pipeThreadCreated   = FALSE;
    quit                = FALSE;
    moduleLock          = NULL;

}

/*
 *  @(#) ti.sdo.ce.utils.trace; 1, 0, 1,307; 12-2-2010 21:28:04; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

