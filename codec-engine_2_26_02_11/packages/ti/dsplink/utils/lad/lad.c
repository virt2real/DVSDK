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
 *  ======== lad.c ========
 */

#include <xdc/std.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

#include <ti/dsplink/utils/ladclient/ladclient.h>
#include "_lad.h"

#include <ti/sdo/ce/ipc/dsplink/_adapted_link_gpptypes.h>
#include <dsplink.h>
#include <errbase.h>

#include <proc.h>
#include <pool.h>
#include <msgq.h>
#include <pooldefs.h>

#define DAEMON  1       /* 1 = run as a daemon; 0 = run as app */

static Bool logFile = FALSE;
static FILE *logPtr = NULL;

static String commandFIFOFile = LAD_COMMANDFIFO;
static FILE *commandFIFOFilePtr = NULL;

/* LAD client info arrays */
static Bool clientConnected[LAD_MAXNUMCLIENTS];
static Int clientCpu[LAD_MAXNUMCLIENTS];
static Uns clientPID[LAD_MAXNUMCLIENTS];
static Bool clientStarted[LAD_MAXNUMCLIENTS];
static Char clientFIFOName[LAD_MAXNUMCLIENTS][LAD_MAXLENGTHFIFONAME];
static FILE * responseFIFOFilePtr[LAD_MAXNUMCLIENTS];

/* LAD and DSP state flags */
/* NOTE: Currently LAD only supports a single attached DSP at any given time.
 * LAD uses the specified "cpuId" when making Link calls, but LAD itself only 
 * maintains a single instance of the following state flags, and therefore does
 * not support multiple clients simultaneously using multiple DSPs.
 */
static Int linkConfigIdDSP = -1;        /* index of loaded link config */
static Char imageNameDSP[LAD_MAXLENGTHIMAGENAME]; /* name of loaded image */
static String serverDir;                /* opt. server exe directory */
static Int numClientsStarted = 0;       /* # clients that called to start DSP */
static Bool setupDSP = FALSE;           /* PROC_Setup called */
static Bool attachedDSP = FALSE;        /* PROC_Attach called */
static Bool poolsOpenedDSP = FALSE;     /* pools have been opened */
static Bool startedDSP = FALSE;         /* PROC_Start called */
static Bool transportOpenedDSP = FALSE; /* MSGQ transport has been opened */

/* arrays defining known Link configurations (see ladconfig.c) */
extern LINKCFG_Object * linkConfig [LAD_MAXNUMLINKCONFIGS];
extern Void * mqtAttrs [LAD_MAXNUMLINKCONFIGS];

/* globals to ease breakout of command processing to separate functions: */
static Char commandString[LAD_MAXLENGTHCOMMAND];
static Char responseString[LAD_MAXLENGTHRESPONSE];

/* internal LAD routines (in ladconfig.c) */
extern Bool _LAD_getConfigId(String name, Uns * index);
extern String _LAD_getConfigName(Uns index);
extern Void _LAD_initConfig(Void);
extern DSP_STATUS _LAD_openAllPools();
extern DSP_STATUS _LAD_closeAllPools();

/* local internal routines */
static LAD_ClientHandle assignClientId(Void);
static Void cleanupDepartedClients(Void);
static Void connectToLAD(Void);
static Void disconnectFromLAD(Void);
static Void doDisconnect(Int clientId);
static Int doRelease(Int clientId);
static Void getDspStatus(Void);
static Void releaseDsp(Void);
static Void startupDsp(Void);
static void dumpLinkCfgObj(LINKCFG_Object *cfg);

/* known MSGQ attr definitions */
extern ZCPYMQT_Attrs user0_MqtAttrs;                    /* config #0 */
extern ZCPYMQT_Attrs user1_MqtAttrs;                    /* config #1 */
extern ZCPYMQT_Attrs user2_MqtAttrs;                    /* config #2 */
extern ZCPYMQT_Attrs message_MqtAttrs;                  /* config #3 */

/*
 *  ======== main ========
 */
int main(int argc, char * argv[])
{
    Int statusIO;
    Int command;
    Char * ptr;
    Char * str;
    Int flags;
    Int i;
#if DAEMON
    pid_t pid;
    pid_t sid;
#endif

    /* if more than two args: turn "ON" launch status printfs */
    if (argc > 2) {
        printf("\nLAD starting up...");
    }

    /* check for env variable indicating server exe repository */
    serverDir = getenv("LAD_SERVERPATH");
    if (serverDir != NULL) {
        printf("\nLAD_SERVERPATH = %s", serverDir);
    }
    else {
        printf("\nLAD_SERVERPATH = <NULL>");
    }

    /* change to LAD's working directory */
    if ((chdir(LAD_WORKINGDIR)) < 0) {

        /* if can't change directory assume it needs to be created, do it */
        if ((mkdir(LAD_WORKINGDIR, 0666)) < 0) {
            printf("\nERROR: Failed to create LAD's working directory!");
            exit(EXIT_FAILURE);
        }
        /* now change to the new directory */
        if ((chdir(LAD_WORKINGDIR)) < 0) {
            printf("\nERROR: Failed to change to LAD's working directory!");
            exit(EXIT_FAILURE);
        }
    }

    /* process command line args */
    if (argc > 1) {
        logPtr = fopen(argv[1], "w");
        if (logPtr == NULL) {
            printf("\nERROR: unable to open log file %s\n", argv[1]);
            exit(EXIT_FAILURE);
        } 
        else {
            logFile = TRUE;
            if (argc > 2) {
                printf("\nOpened log file: %s", argv[1]);
            }
            /* close log file upon LAD termination */ 
            flags = fcntl(fileno(logPtr), F_GETFD);
            if (flags != -1) {
                fcntl(fileno(logPtr), F_SETFD, flags | FD_CLOEXEC);
            }
        }
    }

#if DAEMON
    /* fork off a child process */
    pid = fork();

    /* if fork of child failed then exit immediately; no child created */
    if (pid < 0) {
        printf("\nERROR: Failed to fork child process!");
        exit(EXIT_FAILURE);
    }

    /* if pid > 0 this is the parent; time to die ... */
    if (pid > 0) {
        if (argc > 2) {
            printf("\nSpawned daemon: %s\n\n", argv[0]);
        }
        exit(EXIT_SUCCESS);
    }

    /* child continues from here (pid == 0) ... */

    /* change file mode mask */
    umask(0);

    /* create new session ID for the child */
    sid = setsid();

    /* exit with failure code if failed to get session ID... */
    if (sid < 0) {
        printf("\nERROR: Failed to acquire new session ID!");
        exit(EXIT_FAILURE);
    }

    /* disassociate from the standard file descriptors */
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    
#endif

    LOG0("\nInitializing LAD... ")
    
    /* TODO:L make sure LAD is not already running? */

    /* initialize client info arrays */
    for (i=0; i<LAD_MAXNUMCLIENTS; i++) {
        clientConnected[i] = FALSE;
        clientCpu[i] = 0;
        clientStarted[i] = FALSE;
        responseFIFOFilePtr[i] = NULL;
    }

    /* give some energy to any runtime config inits */
    LOG0("\n    running LAD config inits... ")
    _LAD_initConfig();

    /* if command FIFO exists from previous LAD session delete it now */
    unlink(commandFIFOFile);

    /* create command FIFO */
    statusIO = mkfifo(commandFIFOFile, 0777);
    if (statusIO != 0) {
        LOG2("\nERROR: unable to create %s, errno = %x\n", commandFIFOFile, 
            errno)
        return(0);
    }

    /* set FIFO permissions to read/write */
    chmod(commandFIFOFile, 0666);

opencommandFIFO:

    /* now open file for FIFO - will block until writer arrives... */
    LOG1("\n    opening FIFO: %s\n", commandFIFOFile)
    commandFIFOFilePtr = fopen(commandFIFOFile, "r");
    if (commandFIFOFilePtr == NULL) {
        LOG0("\nERROR: unable to open command FIFO\n")
        unlink(commandFIFOFile);
        return(0);
    }

    /* COMMAND PROCESSING LOOP */
    while(1) {

        /* read the next command packet */
        ptr = fgets(commandString, LAD_MAXLENGTHCOMMAND, commandFIFOFilePtr);

        /* 
         * if last client closes FIFO then it must be closed and reopened ...
         */
        if (ptr == NULL) {
            fclose(commandFIFOFilePtr);
            goto opencommandFIFO;
        }

        /* cleanup for any connected/started clients that have departed */
        cleanupDepartedClients();

        /* extract command code */
        ptr = strtok(commandString, LAD_SEPARATOR);
        if (ptr != NULL) {
            str = ptr + strlen(LAD_CMD);
            command = atoi(str);

            /* process individual commands */
            switch (command) {

                case LAD_CONNECT:
                    connectToLAD();
                    break;

                case LAD_DISCONNECT:
                    disconnectFromLAD();
                    break;
       
                case LAD_GETDSPSTATUS:
                    getDspStatus();
                    break;
       
                case LAD_STARTUPDSP:
                    startupDsp();
                    break;
                      
                case LAD_RELEASEDSP:
                    releaseDsp();
                    break;

                case LAD_EXIT:
                    goto exitNow;
                    break;

                default:
                    LOG1("\nUnrecognized command: 0x%x", command)
                    break;
            }
        }
        else {
            LOG0("\nNo valid command found, retrying...")
        }
    }

exitNow:
    if (logFile) {
        LOG0("\n\nLAD IS SELF TERMINATING...\n\n")
        fclose(logPtr);
    }
    unlink(commandFIFOFile);

    return(0);

}


/*
 *  ======== assignClientId ========
 */
static LAD_ClientHandle assignClientId(Void)
{
    Int clientId = -1;
    Int i;

    /* scan connection status flags to acquire a clientId */
    for (i = 0; i < LAD_MAXNUMCLIENTS; i++) {
        /* if slot open then provisionally select this clientId */
        if (clientConnected[i] == FALSE) {
             clientId = i;
             break;
        }
    }

    return(clientId);
}


/*
 *  ======== cleanupDepartedClients ========
 */
static Void cleanupDepartedClients(Void)
{
    Int killStat;
    Int i;

    /* scan all connections to verify client processes still exist... */
    for (i = 0; i < LAD_MAXNUMCLIENTS; i++) {

        /* if connected... */
        if (clientConnected[i] == TRUE) {

            /* check if the client process (PID) still exists */
            /*
             * NOTE - calling kill with signal value of 0 will perform
             * error checking, but not actually send a signal.  Will use this
             * error check to see if PID still exists.  An alternative was
             * to call getpgid.  This worked, but is apparently limited to 
             * USE_XOPEN_EXTENDED configurations.
             */
            killStat = kill(clientPID[i], 0);
            if ((killStat == -1) && (errno == ESRCH)) {

                LOG1("\nDETECTED CONNECTED CLIENT #%d HAS DEPARTED!", i)

                /* if client was 'started' may need to shutdown DSP... */
                if (clientStarted[i] == TRUE) {
                    LOG0("\nDoing RELEASE on behalf of client...")
                    doRelease(i);
                }

                /* will always need to do the disconnect... */
                LOG0("\nDoing DISCONNECT on behalf of client...")
                doDisconnect(i);

                LOG0("DONE\n")
            }
        }
    }
}


/*
 *  ======== connectToLAD ========
 */
static Void connectToLAD(Void)
{
    Char clientName[LAD_MAXLENGTHFIFONAME];
    Char clientProto[LAD_MAXLENGTHPROTOVERS];
    Bool connectDenied = FALSE;
    Int status = LAD_SUCCESS;
    FILE * filePtr;
    Int statusIO;
    Int clientId;
    Char * ptr;
    Int pid;

    /* extract client FIFO name */
    ptr = strtok(NULL, LAD_SEPARATOR);
    if (ptr != NULL) {
        strcpy(clientName, ptr);
    }

    /* extract client's PID */
    ptr = strtok(NULL, LAD_SEPARATOR);
    if (ptr != NULL) {
        pid = atoi(ptr);
    }

    /* extract client protocol version */
    ptr = strtok(NULL, LAD_SEPARATOR);
    if (ptr != NULL) {
        strcpy(clientProto, ptr);
    }

    /*
     * TODO:L here, and everywhere parse FIFO strings: should
     * add full error checking for incomplete or corrupted
     * strings? Since LAD to ladclient comms are "closed", and
     * tested, the likelihood of problems seems very low.
     * But should still consider doing full error checking
     * and, hopefully, recovery.
     */
    LOG0("\nLAD_CONNECT: \n")
    LOG1("    client FIFO name = %s\n", clientName)
    LOG1("    client PID = %d\n", pid)

    /* first check for proper communication protocol */
    if (strcmp(clientProto, LAD_PROTOCOLVERSION) != 0) {

        /* if no match then reject the request */
        LOG0("    ERROR: mismatch in communication protocol!\n")
        LOG1("        LAD protocol = %s\n", LAD_PROTOCOLVERSION) 
        LOG1("        client protocol = %s\n", clientProto) 
        status = LAD_INVALIDVERSION;

        /* set flag so know to close FIFO after response */
        connectDenied = TRUE;

        /* now jump forward a bit to send response */
        goto openResponseFIFO;    
    }

    /* determine this client's ID */
    clientId = assignClientId();

    /* if failed to acquire an ID then exit early */
    if (clientId == -1) {
        LOG0("    no free handle; too many connections!\n")
        status = LAD_ACCESSDENIED;

        /* set flag so know to close FIFO after response */
        connectDenied = TRUE;

    }
    else {
        LOG1("    assigned client handle = %d\n", clientId)

        /* save the client's FIFO name for when disconnect */
        strcpy(clientFIFOName[clientId],clientName);
    }

openResponseFIFO:

    /* create the dedicated response FIFO to the client */
    statusIO = mkfifo(clientName, 0777);
    if (statusIO != 0) {

        LOG2("\nERROR: unable to mkfifo %s, errno = %x\n", clientName, errno)

        /* send no response; connection request will timeout */
        goto doneconnect;
    }

    LOG1("    FIFO %s created\n", clientName)

    /* set FIFO permissions to read/write */
    chmod(clientName, 0666);

    filePtr = fopen(clientName, "w");
    if (filePtr == NULL) {
        LOG1("\nERROR: unable to open response FIFO %s\n", clientName)

        /* if failed open, still need to delete the FIFO */
        unlink(clientName);

        /* send no response; connection request will timeout */
        goto doneconnect;
    }

    LOG1("    FIFO %s opened for writing\n", clientName)

    /*
     * set "this client is connected" flag; this client ID is now "owned", and
     * is no longer provisional
     */
    if (connectDenied == FALSE) {
        responseFIFOFilePtr[clientId] = filePtr;
        clientPID[clientId] = pid;
        clientConnected[clientId] = TRUE;
        clientStarted[clientId] = FALSE;
    }

    /*
     *  build response string:
     *     status ;
     *     clientId ;
     */

    if (connectDenied == FALSE) {
        sprintf(responseString, "%d%s%d%s", status, LAD_SEPARATOR, clientId, 
            LAD_CMDTERMINATOR);
    }
    else {
        sprintf(responseString, "%d%s%d%s", status, LAD_SEPARATOR, 0, 
            LAD_CMDTERMINATOR);
    }

    /* put response string to FIFO */
    fputs(responseString, filePtr);
    fflush(filePtr);

    LOG1("    sent response %s", responseString)

    /* if connection was denied, must now close FIFO */
    if (connectDenied == TRUE) {
        LOG1("    connect denied; closing FIFO %s\n", clientName)
        fclose(filePtr);
        unlink(clientName);
        connectDenied = FALSE;
    }

    LOG0("DONE\n")

doneconnect:
    return;
}


/*
 *  ======== disconnectFromLAD ========
 */
static Void disconnectFromLAD(Void)
{
    Int clientId;
    Char * ptr;

    LOG0("\nLAD_DISCONNECT: ")

    ptr = strtok(NULL, LAD_SEPARATOR);
    if (ptr != NULL) {
        clientId = atoi(ptr);
        LOG1("\n    client handle = %x", clientId)
        doDisconnect(clientId);
    }

    LOG0("DONE\n")
    return;
}


/*
 *  ======== doDisconnect ========
 */
static Void doDisconnect(Int clientId)
{
    /* set "this client is not connected" flag */
    clientConnected[clientId] = FALSE;

    /* close and remove the response FIFO */
    LOG1("\n    closing FIFO %s\n", clientFIFOName[clientId])
    fclose(responseFIFOFilePtr[clientId]);
    unlink(clientFIFOName[clientId]);
}


/*
 *  ======== doRelease ========
 */
static Int doRelease(Int clientId)
{
    DSP_STATUS linkStatus = DSP_SOK;
    Int status = LAD_SUCCESS;

    /* update this and global started states */
    clientStarted[clientId] = FALSE;
    numClientsStarted--;

    /* if this was last release, then stop the DSP */
    if (numClientsStarted == 0) {

        /* make Link calls to stop the DSP... */

        /* CLOSE MSGQ TRANSPORT */
        if (transportOpenedDSP == TRUE) {
            linkStatus = MSGQ_TransportClose(clientCpu[clientId]);
            if (linkStatus == DSP_SCLOSED) {
                transportOpenedDSP = FALSE;
                LOG0("\n    MSGQ_TransportClose - OK")
            }
            else {
                LOG1("\nMSGQ_TransportClose FAILED 0x%lx", linkStatus)
                goto failedlinkshutdown;
            }
        }

        /* STOP DSP */
        if (startedDSP == TRUE) {
            linkStatus = PROC_Stop(clientCpu[clientId]);
            if (linkStatus == DSP_SSTOPPED) {
                startedDSP = FALSE;
                LOG0("\n    PROC_Stop - OK")
            }
            else {
                LOG1("\n    PROC_Stop FAILED 0x%lx", linkStatus)
                goto failedlinkshutdown;
            }
        }

        /* CLOSE POOLS */
        if (poolsOpenedDSP == TRUE) {
            linkStatus = _LAD_closeAllPools(linkConfigIdDSP);
            if (linkStatus == DSP_SCLOSED) {
                poolsOpenedDSP = FALSE;
                LOG0("\n    POOL_Close - OK")
            }
            else {
                LOG1("\n    POOL_Close FAILED 0x%lx", linkStatus)
                goto failedlinkshutdown;
            }
        }

        /* DETACH FROM DSP */
        if (attachedDSP == TRUE) {
            linkStatus = PROC_Detach(clientCpu[clientId]);
            if (linkStatus == DSP_SDETACHED) {
                attachedDSP = FALSE;
                LOG0("\n    PROC_Detach - OK")
            }
            else {
                LOG1("\n    PROC_Detach FAILED 0x%lx", linkStatus)
                goto failedlinkshutdown;
            }
        }

        /* "DESTROY" DSP */
        if (setupDSP == TRUE) {
            linkStatus = PROC_Destroy();
            if (linkStatus == DSP_SDESTROYED) {
                setupDSP = FALSE;
                LOG0("\n    PROC_Destroy - OK")
            }
            else {
                LOG1("\n    PROC_Destroy FAILED 0x%lx", linkStatus)
                goto failedlinkshutdown;
            }
        }

        return(LAD_SUCCESS);

failedlinkshutdown:
        return(LAD_FAILURE);

    }

    /* else, this is not last client, set return status as still running */
    else {
        status = LAD_STILLRUNNING;
    }

    return(status);
}


/*
 *  ======== getDspStatus ========
 */
static Void getDspStatus(Void)
{
    DSP_STATUS linkStatus;
    PROC_State procState;
    Int clientId;
    Int cpuId;
    Int status;
    Char * ptr;


    ptr = strtok(NULL, LAD_SEPARATOR);
    if (ptr != NULL) {
        clientId = atoi(ptr);
    }
    ptr = strtok(NULL, LAD_SEPARATOR);
    if (ptr != NULL) {
        cpuId = atoi(ptr);
    }

    LOG0("\nLAD_GETDSPSTATUS: ")
    LOG1("\n    client handle = %x", clientId)
    LOG1("\n    cpuId = %x", cpuId)

    /* query DSP state according to Link */
    linkStatus = PROC_getState(cpuId, &procState);
    if (linkStatus == DSP_SOK) {

        LOG1("\n    PROC_getState - OK, state = %x", procState)
        status = LAD_SUCCESS;
    }
    else {
        LOG1("\n    PROC_getState FAILED 0x%lx", linkStatus)
        status = LAD_FAILURE;
    }

    /*
     *  build response string:
     *     RSP=
     *     status ;
     *     dspState ;
     *     linkConfig ;
     *     numClientsStarted ;
     *     imageName ;
     */

    /* 
     * if DSP not loaded or running fake linkConfigId and imageName so don't 
     * explode response string
     */
    if ( (procState != LAD_LOADED) &&
         (procState != LAD_STARTED) ) {

        sprintf(responseString, "%s%d%s%d%s%s%s%d%s%s%s",
            LAD_RSP, status, LAD_SEPARATOR,
            procState, LAD_SEPARATOR,
            LAD_NULL, LAD_SEPARATOR,
            numClientsStarted, LAD_SEPARATOR,
            LAD_NULL, LAD_CMDTERMINATOR);
    }
    else {

        sprintf(responseString, "%s%d%s%d%s%s%s%d%s%s%s",
            LAD_RSP, status, LAD_SEPARATOR,
            procState, LAD_SEPARATOR,
            _LAD_getConfigName(linkConfigIdDSP), LAD_SEPARATOR,
            numClientsStarted, LAD_SEPARATOR,
            imageNameDSP, LAD_CMDTERMINATOR);
    }

    /* put response string to FIFO */
    fputs(responseString, responseFIFOFilePtr[clientId]);
    fflush(responseFIFOFilePtr[clientId]);

    LOG1("\n    sent response %s", responseString)
    LOG0("DONE\n")

    return;
}


/*
 *  ======== releaseDsp ========
 */
static Void releaseDsp(Void)
{
    Int status = LAD_SUCCESS;
    Int clientId;
    Char * ptr;

    LOG0("\nLAD_RELEASEDSP: ")

    ptr = strtok(NULL, LAD_SEPARATOR);
    if (ptr != NULL) {
        clientId= atoi(ptr);

        LOG1("\n    client handle = %x", clientId)

        /* if this client not connected nor started say denied */
        if ((clientConnected[clientId] == FALSE) ||
            (clientStarted[clientId] == FALSE) ) {
            status = LAD_ACCESSDENIED;
        }
        else {
            status = doRelease(clientId);
        }

        /* build response string */
        sprintf(responseString, "%d\n", status);

        /* put response string to FIFO */
        fputs(responseString, responseFIFOFilePtr[clientId]);
        fflush(responseFIFOFilePtr[clientId]);

        LOG1("\n    sent response %s", responseString)
    }

    LOG0("DONE\n")
    return;
}


/*
 *  ======== startupDsp ========
 */
static Void startupDsp(Void)
{
    Char configName[LAD_MAXLENGTHCONFIGNAME];
    Char imageName[LAD_MAXLENGTHIMAGENAME];
    Char serverPath[LAD_MAXLENGTHIMAGENAME];
    DSP_STATUS linkStatus = DSP_SOK;
    Int status = LAD_SUCCESS;
    struct stat statBuf;
    Int linkConfigId;
    Int clientId;
    Int cpuId;
    Char * ptr;

    ptr = strtok(NULL, LAD_SEPARATOR);
    if (ptr != NULL) {
        cpuId = atoi(ptr);
    }
    ptr = strtok(NULL, LAD_SEPARATOR);
    if (ptr != NULL) {
        strcpy(configName, ptr);
    }
    ptr = strtok(NULL, LAD_SEPARATOR);
    if (ptr != NULL) {
        strcpy(imageName, ptr);
    }
    ptr = strtok(NULL, LAD_SEPARATOR);
    if (ptr != NULL) {
        clientId = atoi(ptr);
    }

    LOG0("\nLAD_STARTUPDSP: ")
    LOG1("\n    cpuId = %x", cpuId)
    LOG1("\n    configName = %s", configName)
    LOG1("\n    imageName = %s", imageName)
    if ((imageName[0] != '/') && (serverDir != NULL)) {
        strcpy(serverPath, serverDir);
        strcpy((serverPath + strlen(serverDir)), "/");
        strcpy((serverPath + strlen(serverDir) + 1), imageName);
        strcpy(imageName, serverPath);
        LOG1("\n    absolute server path = %s", imageName)
    }
    LOG1("\n    client handle = %x", clientId)

    /* check that server file exists */
    if (stat(imageName, &statBuf) != 0) {
        status = LAD_INVALIDARG;
        LOG0("\n    server executable file doesn't exist!")
        LOG0("\n    LAD_INVALIDARG")
        goto buildstartupresp;
    }

    /* map the Link config name to an index */
    if (_LAD_getConfigId(configName, (Uns *) &linkConfigId) == FALSE) {
        status = LAD_INVALIDARG;
        LOG0("\n    lookup of Link config name failed!")
        LOG0("\n    LAD_INVALIDARG")
        goto buildstartupresp;
    }

    LOG1("\n    linkConfigId = %x", linkConfigId)

    /* check if cpuId is valid for the linkConfigId */
    if (cpuId > (MAX_DSPS - 1)) {
        status = LAD_INVALIDARG;
        LOG0("\n    cpuId out of range for Link config")
        LOG0("\n    LAD_INVALIDARG")
        goto buildstartupresp;
    }

    /* if DSP already started... */
    if (startedDSP == TRUE) {
        /*  check for exact match */
        if ( (linkConfigId != linkConfigIdDSP) || 
             (strcmp(imageName,imageNameDSP) != 0) ) {

            /* when no match reject the request */
            status = LAD_ACCESSDENIED;
            LOG0("\n    LAD_ACCESSDENIED")
        }
        else {
            /* when match, inc started clients count */
            numClientsStarted++;
            clientCpu[clientId] = cpuId;
            clientStarted[clientId] = TRUE;
            status = LAD_ALREADYRUNNING;
            LOG0("\n    LAD_ALREADYRUNNING")
        }
    }

    /* else, start it up */
    else {

        /* make Link calls to startup the DSP... */

        /* reset link-usage state flags */
        setupDSP = FALSE;
        attachedDSP = FALSE;
        poolsOpenedDSP = FALSE;
        transportOpenedDSP = FALSE;

        /* SETUP DSP */
        dumpLinkCfgObj(linkConfig[linkConfigId]);

        linkStatus = PROC_setup(linkConfig[linkConfigId]);
        if (linkStatus == DSP_SOK) {
            setupDSP = TRUE;
            LOG0("\n    PROC_setup - OK")
        }
        else {
            LOG1("\n    PROC_setup FAILED 0x%lx", linkStatus)
            goto donelinkstartup;
        }

        /* ATTACH TO DSP */
        linkStatus = PROC_Attach(cpuId, NULL);
        if (linkStatus == DSP_SOK) {
            attachedDSP = TRUE;
            LOG0("\n    PROC_Attach - OK")
        }
        else {
            LOG1("\n    PROC_Attach FAILED 0x%lx", linkStatus)
            goto donelinkstartup;
        }

        /* LOAD DSP IMAGE */
        linkStatus = PROC_Load(cpuId, imageName, 0, NULL);
        if (linkStatus == DSP_SOK) {
            LOG0("\n    PROC_Load - OK")
        }
        else {
            LOG1("\n    PROC_Load FAILED 0x%lx", linkStatus)
            goto donelinkstartup;
        }

        /* OPEN POOLS */
        linkStatus = _LAD_openAllPools(linkConfigId);
        if (linkStatus == DSP_SOK) {
            poolsOpenedDSP = TRUE;
            LOG0("\n    POOL_Open - OK")
        }
        else {
            LOG1("\n    POOL_Open FAILED 0x%lx", linkStatus)
            goto donelinkstartup;
        }

        /* START DSP RUNNING */
        linkStatus = PROC_Start(cpuId);
        if (linkStatus == DSP_SOK) {
            startedDSP = TRUE;
            LOG0("\n    PROC_Start - OK")
        }
        else {
            LOG1("\n    PROC_Start FAILED 0x%lx", linkStatus)
            goto donelinkstartup;
        }

        /* OPEN MESSAGE TRANSPORT */
        linkStatus = MSGQ_TransportOpen(cpuId, mqtAttrs[linkConfigId]);
        if (linkStatus == DSP_SOK) {
            transportOpenedDSP = TRUE;
            LOG0("\n    MSGQ_TransportOpen - OK")
        }
        else {
            LOG1("\n    MSGQ_TransportOpen FAILED 0x%lx", linkStatus)
            goto donelinkstartup;
        }

donelinkstartup:
        if (linkStatus == DSP_SOK) {
            linkConfigIdDSP = linkConfigId;
            strcpy(imageNameDSP,imageName);
            numClientsStarted = 1;
            clientCpu[clientId] = cpuId;
            clientStarted[clientId] = TRUE;
            status = LAD_SUCCESS;
            LOG0("\n    LAD_SUCCESS")
        }
        else {
            status = LAD_FAILURE;
            LOG0("\n    LAD_FAILURE")
        }
    }

buildstartupresp:
    /* build response string */
    sprintf(responseString, "%d\n", status);

    /* put response string to FIFO */
    fputs(responseString, responseFIFOFilePtr[clientId]);
    fflush(responseFIFOFilePtr[clientId]);

    LOG1("\n    sent response string %s", responseString)
    LOG0("DONE\n")

    return;
}

#define sstring(p) #p
#define H( pref ) LOG1( "linkCfg->%s\n", sstring(pref) )
#define S( pref, field ) LOG2( "  %s = \"%s\"\n", #field, cfg->pref field )
#define N( pref, field ) LOG2( "  %s = 0x%x\n", #field, (unsigned)(cfg->pref field) )
#define B( pref, field ) LOG2( "  %s = %s\n", #field, cfg->pref field ? "TRUE" : "FALSE" )
#define BLANK LOG0( "\n" );

void dumpLinkCfgObj(LINKCFG_Object *cfg)
{
    int i;
    DSP_BootMode doDspCtrl;
    char *bootString;

    doDspCtrl = cfg->dspConfigs[0]->dspObject->doDspCtrl;
    switch (doDspCtrl) {
      case DSP_BootMode_Boot_NoPwr:
        bootString = "DSP_BootMode_Boot_NoPwr";
        break;
      case DSP_BootMode_Boot_Pwr:
        bootString = "DSP_BootMode_Boot_Pwr";
        break;
      case DSP_BootMode_NoLoad_NoPwr:
        bootString = "DSP_BootMode_NoLoad_NoPwr";
        break;
      case DSP_BootMode_NoLoad_Pwr:
        bootString = "DSP_BootMode_NoLoad_Pwr";
        break;
      case DSP_BootMode_NoBoot:
        bootString = "DSP_BootMode_NoBoot";
        break;
      default:
        bootString = "<INVALID SETTING>";
        break;
    }

    LOG1("\n\nLINKCFG_Object generated for PROC_setup(%p) ...\n", cfg);
    
    H(gppObject->);
    #undef P
    #define P gppObject->
    S( P, name );
    N( P, maxMsgqs );
    N( P, maxChnlQueue );
    N( P, poolTableId );
    N( P, numPools );
    // LINKCFG_Gpp );
    
    BLANK
    
    H(dspConfigs[0]->dspObject->);
    #undef P
    #define P dspConfigs[0]->dspObject->
        S( P, name );
        N( P, dspArch );
        S( P, loaderName );
        B( P, autoStart );
        S( P, execName );
        // N( P, doDspCtrl );
        LOG1("  doDspCtrl = %s\n", bootString);
        N( P, resumeAddr );
        N( P, resetVector );
        N( P, resetCodeSize );
        N( P, maduSize );
        N( P, cpuFreq );
        N( P, endian );
        N( P, wordSwap );
        N( P, memTableId );
        N( P, memEntries );
        N( P, linkDrvId );
        N( P, arg1 );
        N( P, arg2 );
        N( P, arg3 );
        N( P, arg4 );
        N( P, arg5 );
    
    BLANK
    
    H(dspConfigs[0]->linkDrvObjects->);
    #undef P
    #define P dspConfigs[0]->linkDrvObjects->
        S( P, name );
        N( P, hshkPollCount );
        N( P, memEntry );
        N( P, ipsTableId );
        N( P, numIpsEntries );
        N( P, poolTableId );
        N( P, numPools );
        N( P, dataTableId );
        N( P, numDataDrivers );
        N( P, mqtId );
        N( P, ringIoTableId );
        N( P, mplistTableId );
        N( P, mpcsTableId );
    // LINKCFG_LinkDrv );

    
    BLANK
    
    H(dspConfigs[0]->memTables[0][i].);
    #undef P
    #define P dspConfigs[0]->memTables[0][i].
    for (i = 0; i < cfg->dspConfigs[0]->dspObject->memEntries; i++) {
        LOG1( "entry #%d:\n", i );
        N( P, entry );
        S( P, name );
        N( P, physAddr );
        N( P, dspVirtAddr );
        N( P, gppVirtAddr );
        N( P, size );
        B( P, shared );
        B( P, syncd );
    } // LINKCFG_MemEntry );
    
    BLANK
    
    H(dspConfigs[0]->ipsTables[0][i].);
    #undef P
    #define P dspConfigs[0]->ipsTables[0][i].
    for (i = 0; i < cfg->dspConfigs[0]->linkDrvObjects->numIpsEntries; i++) {
        LOG1( "entry #%d:\n", i );
        S( P, name );
        N( P, numIpsEvents );
        N( P, memEntry );
        N( P, gppIntId );
        N( P, dspIntId );
        N( P, dspIntVectorId );
        N( P, arg1 );
        N( P, arg2 );        
    } // LINKCFG_Ips );

    BLANK
    
    H(dspConfigs[0]->poolTables[0][i].);
    #undef P
    #define P dspConfigs[0]->poolTables[0][i].
    for (i = 0; i < cfg->gppObject->numPools; i++) {
        LOG1( "entry #%d:\n", i );
        S( P, name );
        N( P, memEntry );
        N( P, poolSize );
        N( P, ipsId );
        N( P, ipsEventNo );
        N( P, poolMemEntry );
        N( P, arg1 );
        N( P, arg2 );
    } // LINKCFG_Pool );

    BLANK
    
    H(dspConfigs[0]->dataTables[0][i].);
    #undef P
    #define P dspConfigs[0]->dataTables[0][i].
    for (i = 0; i < cfg->dspConfigs[0]->linkDrvObjects->numDataDrivers; i++) {
        LOG1( "entry #%d:\n", i );
        S( P, name );
        N( P, baseChnlId );
        N( P, numChannels );
        N( P, maxBufSize );
        N( P, memEntry );
        N( P, poolId );
        N( P, queuePerChnl );
        N( P, ipsId );
        N( P, ipsEventNo );
        N( P, arg1 );
        N( P, arg2 );
    } // LINKCFG_DataDrv );

    BLANK
    
    H(dspConfigs[0]->mqtObjects->);
    #undef P
    #define P dspConfigs[0]->mqtObjects->
        S( P, name );
        N( P, memEntry );
        N( P, maxMsgSize );
        N( P, ipsId );
        N( P, ipsEventNo );
        N( P, arg1 );
        N( P, arg2 );
    // LINKCFG_Mqt );

    BLANK
    

    H(dspConfigs[0]->ringIoObjects->);
    #undef P
    #define P dspConfigs[0]->ringIoObjects->
        S( P, name );
        N( P, memEntry );
        N( P, maxEntries );
        N( P, ipsId );
        N( P, ipsEventNo );
    // LINKCFG_RingIo );

    BLANK
    

    H(dspConfigs[0]->mplistObjects->);
    #undef P
    #define P dspConfigs[0]->mplistObjects->
        S( P, name );
        N( P, memEntry );
        N( P, maxEntries );
        N( P, ipsId );
        N( P, ipsEventNo );
    // LINKCFG_MpList );

    BLANK
    

    H(dspConfigs[0]->mpcsObjects->);
    #undef P
    #define P dspConfigs[0]->mpcsObjects->
        S( P, name );
        N( P, memEntry );
        N( P, maxEntries );
        N( P, ipsId );
        N( P, ipsEventNo );
    // LINKCFG_Mpcs );
}

/*
 *  @(#) ti.dsplink.utils.lad; 2, 0, 0,228; 12-2-2010 21:18:39; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

