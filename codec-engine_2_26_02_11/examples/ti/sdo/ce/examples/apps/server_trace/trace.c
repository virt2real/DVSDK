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
 *  ======== trace.c ========
 */
#include <xdc/std.h>
#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/utils/trace/TraceUtil.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

#define PULLTRACE      0
#define TRACEUTIL      1
#define MAXTRACESTRING 128

/*
 * USAGE NOTES:
 *   1) LAD must be started before executing this app.
 *
 *   2) The execution mode is determined by the number of arguments specified
 *      when the app is invoked:
 *           No args:   TraceUtil mode.
 *           Two args:  Standard output mode.
 *
 *   3) In TraceUtil mode the DSP server trace and LOG data is pulled from
 *      the DSP via the TraceUtil utility, and stored to files.  Trace
 *      masks, refresh rate, file names, etc. are described in the TraceUtil
 *      documentation.  The application is terminated when the <Enter> key
 *      is pressed.
 *
 *      For example, the command to invoke the app in TraceUtil mode, with a
 *      refresh rate of 50msec, and DSP-side trace mask of *=0167:
 *
 *          TRACEUTIL_REFRESHPERIOD="50" TRACEUTIL_DSP0TRACEMASK="*=0167"
 *              ./trace_remote.x470MV
 *
 *   4) In Standard output mode, DSP trace data is periodically pulled from
 *      the DSP and dumped to stdout.  The two arguments for this mode are:
 *           arg1 = refresh rate (in msec)
 *           arg2 = initial DSP-side trace mask
 *
 *      For example, to refresh every 50msec, and enable levels 0 and 1 trace
 *      for all modules :
 *          ./trace_remote.x470MV 50 *=01
 *
 *      Once started, new DSP trace mask values can be typed in the command
 *      shell, followed by <Enter>, which will cause the new trace mask to be
 *      sent over to the DSP.  When just <Enter> is pressed the app will
 *      terminate.
 *
 *      Output can be directed to a file via simple redirection, or via tee.
 *      For example, to dump the data to log.txt:
 *          ./trace_remote.x470MV 50 *=01 > log.txt
 *
 *      and, to tee the data to log.txt, while simultaneously viewing it in the
 *      shell:
 *          ./trace_remote.x470MV 50 *=01 | tee log.txt
 *
 *      For both cases, new trace mask values (or just <Enter>) can be
 *      specified in the command shell (stdin).
 *
 */

static String usage = "\nUsage: %s [pollrate(msec) tracemask]\n\n";
static String engineName = "dummy";
Engine_Handle engine = NULL;
static fd_set fdMask;

static void dumpTrace(Server_Handle server);
static Bool checkInput(String newTraceMask);

/*
 *  ======== smain ========
 */
Int smain(Int argc, String argv[])
{
    Char newTraceMask[MAXTRACESTRING];
    Server_Handle server = NULL;
    Bool finished = FALSE;
    Uns mode = PULLTRACE;
    Server_Status status;
    Int traceToken;
    String mask;
    Uns rate;

    /* interpret PULLTRACE mode args */
    if (argc == 3) {
        rate = atoi(argv[1]);
        mask = argv[2];
    }

    /* else, if no args, set mode to TRACEUTIL */
    else if (argc == 1) {
        mode = TRACEUTIL;
    }
    /* else, show usage */
    else {
        fprintf(stderr, usage, argv[0]);
        goto done;
    }

    /* reset, load, and start DSP Engine */
    if ((engine = Engine_open(engineName, NULL, NULL)) == NULL) {
        fprintf(stderr, "Error: can't open engine %s!\n", engineName);
        goto done;
    }

    /* setup file descriptor mask for checking for user key input */
    FD_ZERO(&fdMask);
    FD_SET(STDIN_FILENO, &fdMask);

    /* if standard output mode... */
    if (mode == PULLTRACE) {

        printf("Trace polling rate: %d msec\n", rate);
        rate *= 1000;
        printf("DSP trace mask: %s\n", mask);

        /* get server handle */
        server = Engine_getServer(engine);
        if (server == NULL) {
            fprintf(stderr, "Error: can't get server handle!\n");
            goto closeEngine;
        }

        /* connect for server trace data */
        status = Server_connectTrace(server, &traceToken);
        if (status == Server_EINUSE) {
            fprintf(stderr,
                "Error: server trace already in use by another process!\n");
            goto closeEngine;
        }
        else if (status != Server_EOK) {
            fprintf(stderr, "Error: server connect failed, status = 0x%x!\n",
                status);
            goto closeEngine;
        }

        /* server trace mask */
        status = Server_setTrace(server, mask);
        if (status != (Int) Engine_EOK) {
            fprintf(stderr, "Error: unable to set trace mask, status = 0x%x!\n",
                status);
            goto closeEngine;
        }

        printf("Hit <Enter> to exit, or, new trace mask and then <Enter>...\n");

        while (finished == FALSE) {

            dumpTrace(server);

            usleep(rate);

            if (checkInput(newTraceMask) == TRUE) {
                if (strlen(newTraceMask) == 0) {
                    finished = TRUE;
                }
                else {
                    printf("setting new trace mask: %s\n", newTraceMask);
                    status = Server_setTrace(server, newTraceMask);
                    if (status != (Int) Engine_EOK) {
                        fprintf(stderr,
                           "Error updating trace mask, status = 0x%x!\n",
                           status);
                    }
                }
            }
        };

        /* discconnect from server trace data */
        status = Server_disconnectTrace(server, traceToken);
        if (status != Server_EOK) {
            fprintf(stderr,
              "Error: unable to disconnect from server trace, status = 0x%x!\n",
                status);
        }
    }

    /* else, startup TraceUtil to retrieve trace/LOG data and write to files */
    else {

        TraceUtil_start(engineName);

        printf("Started TraceUtil thread\nHit <Enter> to exit...\n");

        getchar();

        TraceUtil_stop();
    }

    printf("Done.\n");

closeEngine:

    /* close the engine */
    if (engine) {
        Engine_close(engine);
    }

done:
    return (0);
}


/*
 *  ======== dumpTrace ========
 */
static void dumpTrace(Server_Handle server)
{
    Int count;

    count = Server_fwriteTrace((Server_Handle)server, "", stdout);

    if (count == -1) {
        fprintf(stderr, "Error retrieving trace: 0x%x!\n",
            Engine_getLastError(engine));
    }
}


/*
 * ======== checkInput ========
 */
static Bool checkInput(Char newTraceMask[])
{
    struct timeval timeout;
    Bool retVal = FALSE;
    fd_set testMask;
    Int status;
    Int i;

    testMask = fdMask;
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;

    status = select(FD_SETSIZE, &testMask, NULL, NULL, &timeout);

    if (status == -1) {
        fprintf(stderr, "Error: unable to check stdin for keypress!\n");
    }
    else if (status != 0) {

        /* read the user input */
        fgets(newTraceMask, MAXTRACESTRING, stdin);

        /* remove trailing new line */
        for (i=0; i< MAXTRACESTRING; i++) {
            if (newTraceMask[i] == '\n') {
                newTraceMask[i] = '\0';
                break;
            }
        }
        retVal = TRUE;
    }

    return(retVal);
}
/*
 *  @(#) ti.sdo.ce.examples.apps.server_trace; 1, 0, 0,217; 12-2-2010 21:20:12; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

