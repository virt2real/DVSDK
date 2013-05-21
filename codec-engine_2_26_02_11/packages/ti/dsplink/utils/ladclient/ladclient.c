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
 *  ======== ladclient.c ========
 */
#include <xdc/std.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

#include "ladclient.h"
#include <ti/dsplink/utils/lad/_lad.h>

static Bool verbose = FALSE;

typedef struct _LAD_ClientInfo {
    Bool connectedToLAD;                          /* connection status */
    Bool startedOK;                               /* successful startupDsp? */
    Uns PID;                                      /* client's process ID */
    Char responseFIFOName[LAD_MAXLENGTHFIFONAME]; /* response FIFO name */
    FILE *responseFIFOFilePtr;                    /* FIFO file pointer */
} _LAD_ClientInfo;

static Bool initialized = FALSE;
static String commandFIFOFileName = LAD_COMMANDFIFO;
static FILE *commandFIFOFilePtr = NULL;
static _LAD_ClientInfo clientInfo[LAD_MAXNUMCLIENTS];

static LAD_Status putCommand(String commandString);
static LAD_Status getResponse(LAD_ClientHandle handle, String responseString);
static LAD_Status initWrappers(Void);
static Bool openCommandFIFO(Void);

/*
 *  ======== LAD_connect ========
 */
LAD_Status  LAD_connect(LAD_ClientHandle * handle)
{
    Char commandString[LAD_MAXLENGTHCOMMAND];
    Char responseString[LAD_MAXLENGTHRESPONSE];
    Char responseFIFOName[LAD_MAXLENGTHFIFONAME];
    LAD_Status status = LAD_SUCCESS;
    time_t currentTime;
    time_t startTime;
    struct stat statBuf;
    double delta;
    Int assignedId;
    FILE * filePtr;
    Char * ptr;
    Int pid;

    /* sanity check arg */
    if (handle == NULL) {
        return(LAD_INVALIDARG);
    }

    /* check and initialize on first connect request */
    if (initialized == FALSE) {

        /* TODO:M does this need to be atomized? */
        status = initWrappers();
        if (status != LAD_SUCCESS) {
            return(status);
        }
        initialized = TRUE;
    }

    /* get caller's process ID */
    pid = getpid();

    /* form name for dedicated response FIFO */
    sprintf(responseFIFOName, "%s%d", LAD_RESPONSEFIFOPATH, pid);

    PRINTVERBOSE2("\nLAD_connect: PID = %d, fifoName = %s\n", pid,
        responseFIFOName)

    /* check if FIFO already exists; if yes, reject the request */
    if (stat(responseFIFOName, &statBuf) == 0) {
        PRINTVERBOSE0("\nLAD_connect: already connected; request denied!\n")
        return(LAD_ACCESSDENIED);
    }

    /* build command string for LAD_CONNECT */
    sprintf(commandString, "%s%d%s%s%s%d%s%s%s", LAD_CMD, LAD_CONNECT, 
        LAD_SEPARATOR, responseFIFOName, LAD_SEPARATOR, pid, 
        LAD_SEPARATOR, LAD_PROTOCOLVERSION, LAD_CMDTERMINATOR);

    PRINTVERBOSE1("commandString = %s\n", commandString)

    /* send command to LAD */
    if ((status = putCommand(commandString)) != LAD_SUCCESS) {
        return(status);
    }

    /* now open the dedicated response FIFO for this client */
    startTime = time ((time_t *) 0);
    while ((filePtr = fopen(responseFIFOName, "r")) == NULL) {
        /* insert wait so yield, so LAD can process connect command sooner */
        usleep(100);  
        currentTime = time ((time_t *) 0);
        delta = difftime(currentTime, startTime);
        if (delta > LAD_CONNECTTIMEOUT) {
            return(LAD_IOFAILURE);
        }
    }

    /* now get LAD's response to the connection request */
    ptr = fgets(responseString, LAD_MAXLENGTHRESPONSE, filePtr);

    if (ptr != NULL) {

        PRINTVERBOSE1("\nLAD_connect: response = %s\n", responseString)

        /* extract LAD's response code and the client ID */
        ptr = strtok(responseString, LAD_SEPARATOR);
        if (ptr != NULL) {
 
            status = atoi(ptr);    /* status from LAD for connect request */

            /* if a successful connect ... */
            if (status == LAD_SUCCESS) {

                /* extract clientId */
                ptr = strtok(NULL, LAD_SEPARATOR);
                if (ptr != NULL) {
                    assignedId = atoi(ptr);
                    *handle = assignedId;

                    /* setup client info */
                    clientInfo[assignedId].PID = pid;
                    clientInfo[assignedId].responseFIFOFilePtr = filePtr;
                    strcpy(clientInfo[assignedId].responseFIFOName, 
                        responseFIFOName);
                    clientInfo[assignedId].connectedToLAD = TRUE;
                }
                else {
                    status = LAD_IOFAILURE;
                }
            }
        }
        else {
            status = LAD_IOFAILURE;
        }
    }
    else {
        PRINTVERBOSE0("\nLAD_connect: NULL ptr when getting LAD response!\n")
        status = LAD_IOFAILURE;
    }

    /* if connect failed, close client side of FIFO (LAD closes its side) */
    if (status != LAD_SUCCESS) {
        PRINTVERBOSE0("\nLAD_connect failed: closing client-side of FIFO...\n")
        fclose(filePtr);
    }
 
    return(status);
}


/*
 *  ======== LAD_disconnect ========
 */
LAD_Status  LAD_disconnect(LAD_ClientHandle handle)
{
    Char commandString[LAD_MAXLENGTHCOMMAND];
    LAD_Status status = LAD_SUCCESS;
    Bool waiting = TRUE;
    struct stat statBuf;
    time_t currentTime;
    time_t startTime;
    double delta;

    /* sanity check args */
    if (handle >= LAD_MAXNUMCLIENTS) {
        return (LAD_INVALIDARG);
    }

    /* check for initialization and connection */
    if ((initialized == FALSE) || 
        (clientInfo[handle].connectedToLAD == FALSE)) {
        return (LAD_NOTCONNECTED);
    }

    /* if client started DSP, check client released DSP before disconnect */
    if (clientInfo[handle].startedOK == TRUE) {
        return (LAD_STILLRUNNING);
    }

    /* build command string for LAD_DISCONNECT */
    sprintf(commandString, "%s%d%s%d%s", LAD_CMD, LAD_DISCONNECT, 
        LAD_SEPARATOR, handle, LAD_CMDTERMINATOR);

    /* send command string to LAD */
    if ((status = putCommand(commandString)) != LAD_SUCCESS) {
        return(status);
    }

    /* on success, close the dedicated response FIFO */
    fclose(clientInfo[handle].responseFIFOFilePtr);

    /* now wait for LAD to close the connection ... */
    startTime = time ((time_t *) 0);
    while (waiting == TRUE) {

        /* do a minimal wait, to yield, so LAD can disconnect */
        usleep(1);  
        currentTime = time ((time_t *) 0);

        /* check to see if LAD has shutdown FIFO yet... */
        if (stat(clientInfo[handle].responseFIFOName, &statBuf) != 0) {
            waiting = FALSE;            /* yes, so done */
        }
        /* if not, check for timeout */
        else {
            delta = difftime(currentTime, startTime);
            if (delta > LAD_DISCONNECTTIMEOUT) {
                PRINTVERBOSE0("\nLAD_disconnect: timeout waiting for LAD!\n")
                return(LAD_IOFAILURE);
            }
        }
    }

    /* reset connection status flag */
    clientInfo[handle].connectedToLAD = FALSE;

    return(status);
}


/*
 *  ======== LAD_getDspStatus ========
 */
extern LAD_Status LAD_getDspStatus(LAD_ClientHandle handle, Int cpuId, 
    LAD_DspStatus * statusInfo)
{
    Char commandString[LAD_MAXLENGTHCOMMAND];
    Char responseString[LAD_MAXLENGTHRESPONSE];
    LAD_Status status = LAD_SUCCESS;
    Char * ptr;
    Char * str;

    /* sanity check params */
    if ((statusInfo == NULL) || (handle >= LAD_MAXNUMCLIENTS)) {
        return (LAD_INVALIDARG);
    }

    /* check for initialization and connection */
    if ((initialized == FALSE) || 
        (clientInfo[handle].connectedToLAD == FALSE)) {
        return (LAD_NOTCONNECTED);
    }

    /* build command string for LAD_GETDSPSTATUS */
    sprintf(commandString, "%s%d%s%d%s%d%s", LAD_CMD, LAD_GETDSPSTATUS, 
        LAD_SEPARATOR, handle, LAD_SEPARATOR, cpuId, LAD_CMDTERMINATOR);

    /* send command string to LAD */
    if ((status = putCommand(commandString)) != LAD_SUCCESS) {
        return(status);
    }

    /* get response from LAD */
    if ((status = getResponse(handle, responseString)) != LAD_SUCCESS) {
        return(status);
    }

    PRINTVERBOSE1("\nLAD_getDspStatus: response = %s\n", responseString)

    /* parse response string into statusInfo structure ... */

    /* extract LAD's response code */
    ptr = strtok(responseString, LAD_SEPARATOR);
    if (ptr != NULL) {
        str = ptr + strlen(LAD_RSP);
        status = atoi(str);

        /* continue parsing only if LAD status is good */
        if (status == LAD_SUCCESS) {
            /* extract DSP state */
            ptr = strtok(NULL, LAD_SEPARATOR);
            if (ptr != NULL) {
                statusInfo->dspState = (LAD_DspState) atoi(ptr);
            }
 
            /* extract linkConfigName */
            ptr = strtok(NULL, LAD_SEPARATOR);
            if (ptr != NULL) {
                strcpy(statusInfo->linkConfigName, ptr);
            }
 
            /* extract numClientsStarted */
            ptr = strtok(NULL, LAD_SEPARATOR);
            if (ptr != NULL) {
                statusInfo->numClientsStarted = atoi(ptr);
            }
 
            /* extract name of running image */
            ptr = strtok(NULL, LAD_SEPARATOR);
            if (ptr != NULL) {
                strcpy(statusInfo->imageName, ptr);
            }
        }
    }

    return(status);

}


/*
 *  ======== LAD_releaseDsp ========
 */
extern LAD_Status LAD_releaseDsp(LAD_ClientHandle handle)
{
    Char commandString[LAD_MAXLENGTHCOMMAND];
    Char responseString[LAD_MAXLENGTHRESPONSE];
    LAD_Status status;

    /* sanity check args */
    if (handle >= LAD_MAXNUMCLIENTS) {
        return (LAD_INVALIDARG);
    }

    /* check for initialization and connection */
    if ((initialized == FALSE) || 
        (clientInfo[handle].connectedToLAD == FALSE)) {
        return (LAD_NOTCONNECTED);
    }

    /* build command string for LAD_RELEASEDSP */
    sprintf(commandString, "%s%d%s%d%s", LAD_CMD, LAD_RELEASEDSP, 
        LAD_SEPARATOR, handle, LAD_CMDTERMINATOR);

    /* send command string to LAD */
    if ((status = putCommand(commandString)) != LAD_SUCCESS) {
        return(status);
    }

    /* get response from LAD */
    if ((status = getResponse(handle, responseString)) != LAD_SUCCESS) {
        return(status);
    }

    /* extract return code */
    status = atoi(responseString);

    /* clear LAD startup flag for this client */
    if ((status == LAD_SUCCESS) || (status == LAD_STILLRUNNING)) {
        clientInfo[handle].startedOK = FALSE;
    }

    return(status);
}


/*
 *  ======== LAD_startupDsp ========
 */
LAD_Status  LAD_startupDsp(LAD_ClientHandle handle, Int cpuId, 
    String linkConfigName, String imageName)
{
    Char commandString[LAD_MAXLENGTHCOMMAND];
    Char responseString[LAD_MAXLENGTHRESPONSE];
    LAD_Status status;

    /* sanity check params  */
    if ((imageName == NULL) || (handle >= LAD_MAXNUMCLIENTS)) {
        return (LAD_INVALIDARG);
    }

    /* check for initialization and connection */
    if ((initialized == FALSE) || 
        (clientInfo[handle].connectedToLAD == FALSE)) {
        PRINTVERBOSE0(
            "\nLAD_startupDsp: rejecting since not connected to LAD\n")
        return (LAD_NOTCONNECTED);
    }

    /* build command string for LAD_STARTUPDSP */
    sprintf(commandString, "%s%d%s%d%s%s%s%s%s%d%s", LAD_CMD, LAD_STARTUPDSP, 
        LAD_SEPARATOR, cpuId, LAD_SEPARATOR, linkConfigName, LAD_SEPARATOR,
        imageName, LAD_SEPARATOR, handle, LAD_CMDTERMINATOR);

    /* send command string to LAD */
    if ((status = putCommand(commandString)) != LAD_SUCCESS) {
        return(status);
    }

    /* get response from LAD */
    if ((status = getResponse(handle, responseString)) != LAD_SUCCESS) {
        return(status);
    }

    /* extract return code */
    status = atoi(responseString);

    /* set flag so remember success on LAD startup */
    if ((status == LAD_SUCCESS) || (status == LAD_ALREADYRUNNING)) {
        clientInfo[handle].startedOK = TRUE;
    }

    return(status);

}


/*
 *  ======== getResponse ========
 */
static LAD_Status getResponse(LAD_ClientHandle handle, String responseString)
{
    LAD_Status status = LAD_SUCCESS;
    Char * ptr;

    ptr = fgets(responseString, LAD_MAXLENGTHRESPONSE, 
        clientInfo[handle].responseFIFOFilePtr);

    if (ptr == NULL) {
        PRINTVERBOSE0("\ngetResponse: ptr = NULL!\n")
        status = LAD_IOFAILURE;
    }

    PRINTVERBOSE2("\ngetResponse: client = %d, responseString = %s\n", handle, 
        responseString)

    return(status);
}


/*
 *  ======== initWrappers ========
 */
static LAD_Status initWrappers(Void)
{
    Int i;

    /* initialize the client info structures */
    for (i = 0; i < LAD_MAXNUMCLIENTS; i++) {
        clientInfo[i].connectedToLAD = FALSE;
        clientInfo[i].startedOK = FALSE;
        clientInfo[i].responseFIFOFilePtr = NULL;
    }

    /* now open LAD's command FIFO */
    if (openCommandFIFO() == FALSE) {
        return(LAD_IOFAILURE);
    }
    else {
        return(LAD_SUCCESS);
    }
}


/*
 *  ======== openCommandFIFO ========
 */
static Bool openCommandFIFO(Void)
{
    /* open a file for writing to FIFO */
    commandFIFOFilePtr = fopen(commandFIFOFileName, "w");

    if (commandFIFOFilePtr == NULL) {
        PRINTVERBOSE2("\nERROR: failed to open %s, errno = %x\n", 
            commandFIFOFileName, errno)
        return(FALSE);
    }

    return(TRUE);
}


/*
 *  ======== putCommand ========
 */
static LAD_Status putCommand(String commandString) 
{
    LAD_Status status = LAD_SUCCESS;
    Int stat;

    /* put command string to FIFO */
    stat = fputs(commandString, commandFIFOFilePtr);

    if (stat == (Int) NULL) {
        PRINTVERBOSE0("\nputCommand: stat for fputs = NULL!\n")
        status = LAD_IOFAILURE;
    }
    else {
        stat = fflush(commandFIFOFilePtr);

        if (stat == (Int) EOF) {
            PRINTVERBOSE0("\nputCommand: stat for fflush = EOF!\n")
            status = LAD_IOFAILURE;
        }
    }

    return(status);
}
/*
 *  @(#) ti.dsplink.utils.ladclient; 1, 0, 0,239; 12-2-2010 21:18:40; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

