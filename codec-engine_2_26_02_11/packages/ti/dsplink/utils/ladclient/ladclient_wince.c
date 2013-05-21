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
 *  ======== ladclient_wince.c ========
 */
#include <xdc/std.h>

#include <windows.h>

#include <ti/sdo/ce/osal/Global.h>
#include <ti/sdo/ce/osal/File.h>
#include <ti/sdo/ce/osal/wince/Reg.h>

#include <stdlib.h>
#include <string.h>

#include "ladclient.h"
#include <ti/dsplink/utils/lad/_lad.h>

#include <ti/sdo/ce/ipc/dsplink/_adapted_link_gpptypes.h>
#include <dsplink.h>
#include <errbase.h>

#include <proc.h>
#include <pool.h>
#include <msgq.h>
#include <pooldefs.h>


#define _LAD_MUTEX_NAME TEXT("TI_SDO_DSPLINK_UTILS_LADCLIENT")
#define TIMEOUT 0xffffffff /* TODO: Do we want a configurable value? */

#define LAD_REG_KEY TEXT("SOFTWARE\\Texas Instruments\\ti.sdo.dsplink.lad")

/*
 *  ======== LadKey Masks ========
 *  Used for specifying which LAD registry values to get or set.
 */
#define LadKey_NUMCLIENTSSTARTED  0x1
#define LadKey_LINKCONFIGID       0x2
#define LadKey_IMAGENAME          0x4
#define LadKey_DSPSTATUS          0x8
#define LadKey_CLIENTCONNECTED    0x10 // TODO: Remove?
#define LadKey_ALL                0x1f

/*
 * ======== DSP status masks ========
 * State of DSP startup.
 */
#define DspStatus_SETUP          0x1
#define DspStatus_ATTACHED       0x2
#define DspStatus_POOLSOPENED    0x4
#define DspStatus_TRANSPORTOPEND 0x8
#define DspStatus_RUNNING        0x10

/*
 *  ======== _LAD_ClientInfo ========
 */
typedef struct _LAD_ClientInfo {
    Bool connectedToLAD;    /* connection status */
    Bool startedOK;         /* successful startupDsp? */
    UInt32 PID;             /* client's process ID */
} _LAD_ClientInfo;

typedef struct LadRegData {
    Int32   numClientsStarted;
    Int32   linkConfigId;
    Char    imageName[LAD_MAXLENGTHIMAGENAME];
    UInt32  dspStatus;
} LadRegData;


//// Stuff from lad.c //////////////////////////////////////////////
extern Bool _LAD_getConfigId(String name, Uns * index);
extern String _LAD_getConfigName(Uns index);
extern Void _LAD_initConfig(Void);
extern DSP_STATUS _LAD_openAllPools();
extern DSP_STATUS _LAD_closeAllPools();

/* arrays defining known Link configurations (see ladconfig.c) */
extern LINKCFG_Object * linkConfig [LAD_MAXNUMLINKCONFIGS];
extern Void * mqtAttrs [LAD_MAXNUMLINKCONFIGS];

////////////////////////////////////////////////////////////////////

static Int assignClientId(Void);
static LAD_Status deInitLad(Void);
static LAD_Status getLadRegData(LadRegData *ladData, UInt32 ladKeys);
static LAD_Status setLadRegData(LadRegData *ladData, UInt32 ladKeys);
static LAD_Status initLad(Void);

static Int refCount = 0;
static _LAD_ClientInfo clientInfo[LAD_MAXNUMCLIENTS];

static Bool clientConnected[LAD_MAXNUMCLIENTS];
static Bool clientStarted[LAD_MAXNUMCLIENTS];
static Int clientCpu[LAD_MAXNUMCLIENTS];

static String ladkey = "SOFTWARE\\Texas Instruments\\ti.sdo.ce.lad";
static String linkConfigIdKey = "linkConfigId";
static String imageNameKey = "imageName";
static String numStartedKey = "numClientsStarted";
static String dspStatusKey = "dspStatus";
static String clientConnectedKey = "clientConnected"; // TODO: Remove?

static HANDLE _LAD_mutex = NULL;

static Bool verbose = FALSE;


/*
 *  ======== LAD_connect ========
 */
LAD_Status LAD_connect(LAD_ClientHandle * handle)
{
    LAD_Status  status = LAD_SUCCESS;
    Int         clientId;
    UInt32      pid;

//    DebugBreak();

    /* sanity check arg */
    if (handle == NULL) {
        return (LAD_INVALIDARG);
    }

    /* check and initialize on first connect request */
    if (refCount++ == 0) {

        /* TODO:M does this need to be atomized? */
        status = initLad();
        if (status != LAD_SUCCESS) {
            return (status);
        }
    }

    /* get caller's process ID */
    // TODO: Do we need a unique ID? For kernel drivers at startup, the
    // Process Id is the same.
    pid = Global_getProcessId();

    clientId = assignClientId();

    if (clientId == -1) {
        PRINTVERBOSE0("\nLAD_connect failed: To many connections!\n");
        *handle = (LAD_ClientHandle)-1;
        status = LAD_ACCESSDENIED;
    }
    else {
        /* setup client info */
        clientInfo[clientId].PID = pid;
        clientInfo[clientId].connectedToLAD = TRUE;
        *handle = (LAD_ClientHandle)clientId;
    }
 
    return (status);
}

/*
 *  ======== LAD_disconnect ========
 */
LAD_Status LAD_disconnect(LAD_ClientHandle handle)
{
    Int         clientId = (Int)handle;
    UInt32      clientIds = 0;
    UInt32      dataSize;
    LAD_Status  status = LAD_SUCCESS;

    /* sanity check args */
    if ((clientId >= LAD_MAXNUMCLIENTS) || (clientId < 0)) {
        return (LAD_INVALIDARG);
    }

    /* check for initialization and connection */
    if ((refCount <= 0) || 
        (clientInfo[clientId].connectedToLAD == FALSE)) {
        return (LAD_NOTCONNECTED);
    }

    /* if client started DSP, check client released DSP before disconnect */
    if (clientInfo[clientId].startedOK == TRUE) {
        return (LAD_STILLRUNNING);
    }

    /* Enter critical section. */
    WaitForSingleObject(_LAD_mutex, TIMEOUT);

    /* Read clientIds (bit mask) from registry (is this really needed?) */
    dataSize = sizeof(UInt32);
    if (!Reg_getValue(NULL, ladkey, clientConnectedKey,
                  (UInt8 *)&clientIds, &dataSize)) {
        status = LAD_FAILURE;
        PRINTVERBOSE0("\nLAD_disconnect: Failed to get reg value\n");
    }
    else {
        clientIds &= ~(1 << clientId);

        /* Write clientIds back to registry. */
        if (!(status = Reg_setValue(NULL, ladkey, clientConnectedKey,
                      REG_DWORD,  (UInt8 *)&clientIds, sizeof(UInt32),
                      Reg_NONVOLATILE))) {
            PRINTVERBOSE0("\nLAD_disconnect: Failed to set reg value\n");
        }
    }

    /* Leave critical section */
    ReleaseMutex(_LAD_mutex);

    /* reset connection status flag */
    clientInfo[clientId].connectedToLAD = FALSE;

    // Possible race condition if multiple threads within a process
    // calling LAD_disconnect().
    if (--refCount == 0) {
        deInitLad();
    }

    return(status);
}


/*
 *  ======== LAD_getDspStatus ========
 */
LAD_Status LAD_getDspStatus(LAD_ClientHandle handle, Int cpuId, 
        LAD_DspStatus * statusInfo)
{
    DSP_STATUS  linkStatus;
    PROC_State  procState;
    Int         clientId = (Int)handle;
    DWORD       waitStatus;
    String      linkConfigName = NULL;
    Int         linkConfigId = -1;
    Int         numStarted = -1;
    LadRegData  ladData;
    LAD_Status  status = LAD_SUCCESS;

    /* sanity check params */
    if ((statusInfo == NULL) || (clientId >= LAD_MAXNUMCLIENTS) ||
            (clientId < 0)) {
        return (LAD_INVALIDARG);
    }

    /* Check for initialization and connection */
    if ((refCount <= 0) || (clientInfo[clientId].connectedToLAD == FALSE)) {
        return (LAD_NOTCONNECTED);
    }

    /* Enter critical section */
    waitStatus = WaitForSingleObject(_LAD_mutex, TIMEOUT);

    if (waitStatus == WAIT_OBJECT_0) {
        /* query DSP state according to Link */
        linkStatus = PROC_getState(cpuId, &procState);
        if (linkStatus == DSP_SOK) {
            PRINTVERBOSE1("\nLAD_getDspStatus: PROC_getState - OK, state=%x\n",
                    procState);
        }
        else {
            PRINTVERBOSE1("\nLAD_getDspStatus: PROC_getState FAILED 0x%lx\n",
                    linkStatus);
            status = LAD_FAILURE;
        }
    }
    else if (waitStatus == WAIT_TIMEOUT) {
        PRINTVERBOSE0("\nLAD_getDspStatus: WaitForSingleObject() timed out\n");
        status = LAD_FAILURE;
    }
    else {
        PRINTVERBOSE0("\nLAD_getDspStatus: WaitForSingleObject() failed!\n");
        status = LAD_FAILURE;
    }

    if (status == LAD_SUCCESS) {
        ladData.imageName[0] = '\0';

        //if ((procState != ProcState_Loaded) &&
        //    (procState != ProcState_Started)) {
        if ((procState != LAD_LOADED) && (procState != LAD_STARTED)) {
            numStarted = 0;
        }
        else {
            /* Read LAD info from registry. */
            status = getLadRegData(&ladData, LadKey_ALL);
            if (status != LAD_SUCCESS) {
                PRINTVERBOSE0("\nLAD_getDspStatus: getLadRegData() failed\n");
            }
            else {
                /* Get linkConfigName from linkConfigId */
                if ((ladData.linkConfigId < 0) ||
                        (ladData.linkConfigId > LAD_MAXNUMLINKCONFIGS)) {
                    PRINTVERBOSE1("\nLAD_getDspStatus: Bad linkConfigId: %d\n",
                            ladData.linkConfigId);
                    status = LAD_FAILURE;
                }
                else {
                    linkConfigName = _LAD_getConfigName(ladData.linkConfigId);
                }
            }
        }

        statusInfo->dspState = (LAD_DspState)procState;
 
        /* Copy linkConfig and image names to statusInfo */
        if (linkConfigName != NULL) {
            strcpy(statusInfo->linkConfigName, linkConfigName);
        }
        strcpy(statusInfo->imageName, ladData.imageName);

        statusInfo->numClientsStarted = ladData.numClientsStarted;
    }

    if (waitStatus == WAIT_OBJECT_0) {
        ReleaseMutex(_LAD_mutex);
    }

    return (status);
}


/*
 *  ======== LAD_releaseDsp ========
 */
LAD_Status LAD_releaseDsp(LAD_ClientHandle handle)
{
    Bool        setupDSP = FALSE;       /* PROC_Setup called */
    Bool        attachedDSP = FALSE;    /* PROC_Attach called */
    Bool        poolsOpenedDSP = FALSE; /* pools have been opened */
    Bool        dspRunning = FALSE;     /* PROC_Start called */
    Bool        transportOpenedDSP = FALSE; /* MSGQ transport opened */
    Int         clientId = (Int)handle;
    DWORD       waitStatus;
    LadRegData  ladData;
    DSP_STATUS  linkStatus = DSP_SOK;
    LAD_Status  status = LAD_SUCCESS;

    /* sanity check args */
    if ((clientId >= LAD_MAXNUMCLIENTS) || (clientId < 0)) {
        PRINTVERBOSE1("LAD_releaseDsp: Invalid clientId [%d]!\n", clientId);
        return (LAD_INVALIDARG);
    }

    /* check for initialization and connection */
    if ((refCount <= 0) || (clientInfo[clientId].connectedToLAD == FALSE)) {
        PRINTVERBOSE0("LAD_releaseDsp: Client not connected!\n");
        return (LAD_NOTCONNECTED);
    }

    /* if this client not connected nor started say denied */
    if (!clientConnected[clientId] || !clientStarted[clientId]) {
        // TODO: Figure out what to do with this.
        //return (LAD_ACCESSDENIED);
    }

    /* Enter critical section */
    waitStatus = WaitForSingleObject(_LAD_mutex, TIMEOUT);

    if (waitStatus != WAIT_OBJECT_0) {
        if (waitStatus == WAIT_TIMEOUT) {
            PRINTVERBOSE0("LAD_releaseDsp: WaitForSingleObject() timed out\n");
            status = LAD_FAILURE;
        }
        else {
            PRINTVERBOSE0("LAD_releaseDsp: WaitForSingleObject() failed!\n");
            status = LAD_FAILURE;
        }
    }

    if (status == LAD_SUCCESS) {
        /*
         *  Get number of clients, link config ID, DSP status from registry.
         */
        status = getLadRegData(&ladData, LadKey_NUMCLIENTSSTARTED |
                               LadKey_LINKCONFIGID | LadKey_DSPSTATUS);
        if (status != LAD_SUCCESS) {
            PRINTVERBOSE0("\nLAD_releaseDsp: getLadRegData() failed\n");
            goto failedLinkShutdown;
        }
        ladData.numClientsStarted--;

        /* Write numClientsStarted to registry */
        status = setLadRegData(&ladData, LadKey_NUMCLIENTSSTARTED);
        if (status != LAD_SUCCESS) {
            PRINTVERBOSE0("\nLAD_releaseDsp: setLadRegData() failed\n");
            goto failedLinkShutdown;
        }

        /* Last release must stop the DSP. */
        if ((status == LAD_SUCCESS) && (ladData.numClientsStarted == 0)) {

            if (ladData.dspStatus & DspStatus_TRANSPORTOPEND) {
                linkStatus = MSGQ_TransportClose(clientCpu[clientId]);
                if (linkStatus == DSP_SCLOSED) {
                    ladData.dspStatus &= ~DspStatus_TRANSPORTOPEND;
                }
                else {
                    PRINTVERBOSE1("\nMSGQ_TransportClose FAILED 0x%lx",
                            linkStatus);
                    status = LAD_FAILURE;
                    goto failedLinkShutdown;
                }
            }

            /* STOP DSP */
            if (ladData.dspStatus & DspStatus_RUNNING) {
                linkStatus = PROC_Stop(clientCpu[clientId]);
                if (linkStatus == DSP_SSTOPPED) {
                    ladData.dspStatus &= ~DspStatus_RUNNING;
                    PRINTVERBOSE0("\n   PROC_Stop - OK");
                }
                else {
                    PRINTVERBOSE1("\n   PROC_Stop FAILED 0x%lx", linkStatus);
                    status = LAD_FAILURE;
                    goto failedLinkShutdown;
                }
            }

            /* CLOSE POOLS */
            if (ladData.dspStatus & DspStatus_POOLSOPENED) {
                linkStatus = _LAD_closeAllPools(ladData.linkConfigId);
                if (linkStatus == DSP_SCLOSED) {
                    ladData.dspStatus &= ~DspStatus_POOLSOPENED;
                    PRINTVERBOSE0("\n   POOL_Close - OK");
                }
                else {
                    PRINTVERBOSE1("\n   POOL_Close FAILED 0x%lx", linkStatus);
                    status = LAD_FAILURE;
                    goto failedLinkShutdown;
                }
            }

            /* DETACH FROM DSP */
            if (ladData.dspStatus & DspStatus_ATTACHED) {
                linkStatus = PROC_Detach(clientCpu[clientId]);
                if (linkStatus == DSP_SDETACHED) {
                    ladData.dspStatus &= ~DspStatus_ATTACHED;
                    PRINTVERBOSE0("\n   PROC_Detach - OK");
                }
                else {
                    PRINTVERBOSE1("\n   PROC_Detach FAILED 0x%lx", linkStatus);
                    status = LAD_FAILURE;
                    goto failedLinkShutdown;
                }
            }

            /* "DESTROY" DSP */
            if (ladData.dspStatus & DspStatus_SETUP) {
                linkStatus = PROC_Destroy();
                if (linkStatus == DSP_SDESTROYED) {
                    ladData.dspStatus &= ~DspStatus_SETUP;
                    PRINTVERBOSE0("\n   PROC_Destroy - OK");
                }
                else {
                    PRINTVERBOSE1("\n  PROC_Destroy FAILED 0x%lx", linkStatus);
                    status = LAD_FAILURE;
                    goto failedLinkShutdown;
                }
            }

            status = LAD_SUCCESS;
        }
        else {
            /* This is not the last client */
            status = LAD_STILLRUNNING;
        }
    }

failedLinkShutdown:

    if ((ladData.numClientsStarted == 0) && (ladData.dspStatus !=(UInt32)-1)) {
        /* Write the updated DSP status to the registry */
        setLadRegData(&ladData, LadKey_DSPSTATUS);
    }

    if (waitStatus == WAIT_OBJECT_0) {
        ReleaseMutex(_LAD_mutex);
    }

    /* clear LAD startup flag for this client */
    if ((status == LAD_SUCCESS) || (status == LAD_STILLRUNNING)) {
        clientInfo[clientId].startedOK = FALSE;
    }

    return (status);
}


/*
 *  ======== LAD_startupDsp ========
 */
LAD_Status LAD_startupDsp(LAD_ClientHandle handle, Int cpuId, 
    String linkConfigName, String imageName)
{
    File_Stat   fileStat;
    Int         linkConfigIdDSP = -1;
    PROC_State  procState;
    Int         clientId = (Int)handle;
    Int         linkConfigId;
    Bool        startingDSP = FALSE;    /* Will start DSP */
    UInt32      dspStatus = 0;
    LadRegData  ladData;
    DWORD       waitStatus;
    DSP_STATUS  linkStatus = DSP_SOK;
    LAD_Status  status = LAD_SUCCESS;

    /* sanity check params  */
    if ((imageName == NULL) || (clientId >= LAD_MAXNUMCLIENTS) ||
            (clientId < 0)) {
        return (LAD_INVALIDARG);
    }

    /* check for initialization and connection */
    if ((refCount <= 0) || 
        (clientInfo[handle].connectedToLAD == FALSE)) {
        PRINTVERBOSE0(
            "\nLAD_startupDsp: rejecting since not connected to LAD\n");
        return (LAD_NOTCONNECTED);
    }

    /* Check that server file exists */
    if (File_stat(imageName, &fileStat) != File_EOK) {
        PRINTVERBOSE0("LAD_startupDSP: server file doesn't exist!\n");
        PRINTVERBOSE0("LAD_startupDSP: returning LAD_INVALIDARG\n");
        return (LAD_INVALIDARG);
    }

    /* map the Link config name to an index */
    if (_LAD_getConfigId(linkConfigName, (UInt32 *)&linkConfigId) == FALSE) {
        PRINTVERBOSE0("LAD_startupDsp: lookup of Link config name failed!\n");
        PRINTVERBOSE0("LAD_startupDsp: returning LAD_INVALIDARG\n");
        return (LAD_INVALIDARG);
    }

    PRINTVERBOSE1("\nLAD_startupDsp: linkConfigId = %x\n", linkConfigId);

    /*
     *  check if cpuId is valid for the linkConfigId. NOTE: MAX_DSPS is a
     *  compile define that is set in dsplinkcfg.pl.
     */
    if (cpuId > (MAX_DSPS - 1)) {
        PRINTVERBOSE0("LAD_startupDsp: cpuId out of range for Link config\n");
        PRINTVERBOSE0("LAD_startupDsp: returning LAD_INVALIDARG\n");
        return (LAD_INVALIDARG);
    }

    /* Enter critical section */
    waitStatus = WaitForSingleObject(_LAD_mutex, TIMEOUT);
    if (waitStatus != WAIT_OBJECT_0) {
        if (waitStatus == WAIT_TIMEOUT) {
            PRINTVERBOSE0("LAD_startupDsp: WaitForSingleObject() timed out\n");
            PRINTVERBOSE0("LAD_startupDsp: returning LAD_FAILURE\n");
            return (LAD_FAILURE);
        }
        else {
            PRINTVERBOSE0("LAD_startupDsp: WaitForSingleObject() failed!\n");
            PRINTVERBOSE0("LAD_startupDsp: returning LAD_FAILURE\n");
            return (LAD_FAILURE);
        }
    }

    /* Get the status of the DSP */
    linkStatus = PROC_getState(cpuId, &procState);

    if (linkStatus == DSP_SOK) {
        PRINTVERBOSE1("\nLAD_startupDsp: PROC state=%x\n", procState);
    }
    else {
        ReleaseMutex(_LAD_mutex);
        PRINTVERBOSE1("\nLAD_startupDsp: PROC_getState FAILED 0x%lx\n",
                linkStatus);
        PRINTVERBOSE0("LAD_startupDsp: returning LAD_FAILURE\n");
        return (LAD_FAILURE);
    }

    /* if DSP already started... */
    if (procState == LAD_STARTED) {

        /* Read LAD data from registry. */
        status = getLadRegData(&ladData, LadKey_ALL);
        if (status != LAD_SUCCESS) {
            PRINTVERBOSE0("\nLAD_startupDsp: getLadRegData() failed!\n");
        }
        else {
            /*  check for exact match */
            if (linkConfigId != ladData.linkConfigId) {
                PRINTVERBOSE0("LAD_startupDsp: linkConfig does not match\n");
                PRINTVERBOSE0("    the currintly loaded DSP.\n");
                PRINTVERBOSE0("    LAD_ACCESSDENIED\n");
                status = LAD_ACCESSDENIED;
            }
            if (strcmp(imageName, ladData.imageName) != 0) {
                /* when no match reject the request */
                PRINTVERBOSE0("LAD_startupDsp: imageName does not match\n");
                PRINTVERBOSE0("    the currintly loaded DSP.\n");
                PRINTVERBOSE0("    LAD_ACCESSDENIED\n");
                status = LAD_ACCESSDENIED;
            }
        }
        
        if (status == LAD_SUCCESS) {
            /* Image and link config match, increment started clients count */
            ladData.numClientsStarted++;
            setLadRegData(&ladData, LadKey_NUMCLIENTSSTARTED);

            clientCpu[clientId] = cpuId;
            clientStarted[clientId] = TRUE;
            status = LAD_ALREADYRUNNING;
            PRINTVERBOSE0("\n    LAD_ALREADYRUNNING")
        }
    }
    else {
        /* Start up the DSP */
        startingDSP = TRUE;
        dspStatus = 0;

        /* make Link calls to startup the DSP... */

        /* SETUP DSP */
        linkStatus = PROC_setup(linkConfig[linkConfigId]);
        if (DSP_SUCCEEDED(linkStatus)) {
            dspStatus |= DspStatus_SETUP;
            PRINTVERBOSE0("\n    PROC_setup - OK");
        }
        else {
            PRINTVERBOSE1("\n    PROC_setup FAILED 0x%lx", linkStatus);
            status = LAD_FAILURE;
            goto doneStartupDsp;
        }

        /* ATTACH TO DSP */
        linkStatus = PROC_Attach(cpuId, NULL);
        if (DSP_SUCCEEDED(linkStatus)) {
            dspStatus |= DspStatus_ATTACHED;
            PRINTVERBOSE0("\n    PROC_Attach - OK");
        }
        else {
            PRINTVERBOSE1("\n    PROC_Attach FAILED 0x%lx", linkStatus);
            status = LAD_FAILURE;
            goto doneStartupDsp;
        }

        /* LOAD DSP IMAGE */
        linkStatus = PROC_Load(cpuId, imageName, 0, NULL);
        if (DSP_SUCCEEDED(linkStatus)) {
            PRINTVERBOSE0("\n    PROC_Load - OK");
        }
        else {
            PRINTVERBOSE1("\n    PROC_Load FAILED 0x%lx", linkStatus);
            status = LAD_FAILURE;
            goto doneStartupDsp;
        }

        /* OPEN POOLS */
        linkStatus = _LAD_openAllPools(linkConfigId);
        if (DSP_SUCCEEDED(linkStatus)) {
            dspStatus |= DspStatus_POOLSOPENED;
            PRINTVERBOSE0("\n    POOL_Open - OK");
        }
        else {
            PRINTVERBOSE1("\n    POOL_Open FAILED 0x%lx", linkStatus);
            status = LAD_FAILURE;
            goto doneStartupDsp;
        }

        /* START DSP RUNNING */
        linkStatus = PROC_Start(cpuId);
        if (DSP_SUCCEEDED(linkStatus)) {
            dspStatus |= DspStatus_RUNNING;
            PRINTVERBOSE0("\n    PROC_Start - OK");
        }
        else {
            PRINTVERBOSE1("\n    PROC_Start FAILED 0x%lx", linkStatus);
            status = LAD_FAILURE;
            goto doneStartupDsp;
        }

        /* OPEN MESSAGE TRANSPORT */
        linkStatus = MSGQ_TransportOpen(cpuId, mqtAttrs[linkConfigId]);
        if (DSP_SUCCEEDED(linkStatus)) {
            dspStatus |= DspStatus_TRANSPORTOPEND;
            PRINTVERBOSE0("\n    MSGQ_TransportOpen - OK");
        }
        else {
            PRINTVERBOSE1("\n    MSGQ_TransportOpen FAILED 0x%lx", linkStatus);
            status = LAD_FAILURE;
            goto doneStartupDsp;
        }

doneStartupDsp:
        ladData.dspStatus = dspStatus;

        if (status == LAD_SUCCESS) {
            if (linkStatus != DSP_SOK) {
                /* Only write DSP status to registry */
                status = setLadRegData(&ladData, LadKey_DSPSTATUS);
            }
            else {
                ladData.linkConfigId = linkConfigId;
                strcpy(ladData.imageName, imageName);
                ladData.numClientsStarted = 1;

                status = setLadRegData(&ladData, LadKey_ALL);
            }    

            if (status != LAD_SUCCESS) {
                PRINTVERBOSE0("\nLAD_startupDsp: setLadRegData() failed!\n");
            }
            else {
                clientCpu[clientId] = cpuId;
                clientStarted[clientId] = TRUE;
            }
        }
        else {
            /*
             *  Even if we failed, write the DSP status so we know what
             *  functions to call when releasing DSP.
             */
            if (setLadRegData(&ladData, LadKey_DSPSTATUS) == LAD_SUCCESS) {
                // TODO: Cleanup depending on dspStatus.
            }
        }
    }

    /* Exit the critical section */
    if (waitStatus == WAIT_OBJECT_0) {
        ReleaseMutex(_LAD_mutex);
    }

    /* set flag so remember success on LAD startup */
    if ((status == LAD_SUCCESS) || (status == LAD_ALREADYRUNNING)) {
        clientInfo[clientId].startedOK = TRUE;
    }

    return (status);

}

/*
 *  ======== assignClientId ========
 */
static Int assignClientId(Void)
{
    UInt32  clientIds = 0;
    Int     clientId = -1;
    Int     i;
    UInt32  dataSize = sizeof(UInt32);
    Bool    status;

#if LAD_MAXNUMCLIENTS > 32
#error "LAD_MAXNUMCLIENTS exceeds maximum allowed"
#endif

    /* Enter critical section */
    WaitForSingleObject(_LAD_mutex, TIMEOUT);

    /* Read clientConnected (bit mask?) from registry */
    status = Reg_getValue(NULL, ladkey, clientConnectedKey,
            (UInt8 *)&clientIds, &dataSize);

    if (status) {
        /* The data already exists in the registry */

        for (i = 0; i < LAD_MAXNUMCLIENTS; i++) {
            /* if slot open then select this clientId */
            if ((clientIds & (1 << i)) == 0) {
                clientId = i;
                clientIds |= (1 << i);

                // TODO: Write clientIds to registry?

                break;
            }
        }
    }
    else {
        /* Assume we are the first to put data in the registry. */
        clientIds = clientId = 1;
        status = TRUE;
    }

    /* Write clientIds to registry. */
    if (!(status = Reg_setValue(NULL, ladkey, clientConnectedKey, REG_DWORD,
                  (UInt8 *)&clientIds, sizeof(UInt32), Reg_NONVOLATILE))) {
        PRINTVERBOSE0("\nLAD assignClientId: Failed to set reg value\n");
        clientId = -1;
    }

    /* Leave critical section. */
    ReleaseMutex(_LAD_mutex);

    return (clientId);
}

/*
 *  ======== deInitLad ========
 */
static LAD_Status deInitLad(Void)
{
    Int i;

    for (i = 0; i < LAD_MAXNUMCLIENTS; i++) {
        clientConnected[i] = FALSE;
        clientStarted[i] = FALSE;
    }

    if (_LAD_mutex) {
        CloseHandle(_LAD_mutex);
        _LAD_mutex = NULL;
    }

    return (LAD_SUCCESS);
}

/*
 *  ======== getLadRegData ========
 */
static LAD_Status getLadRegData(LadRegData *ladData, UInt32 ladKeys)
{
    Int         dataSize;
    LAD_Status  status = LAD_SUCCESS;

    // Assert ladData != NULL

    /* Initialize ladData fields to bad values, in case registry read fails. */
    ladData->linkConfigId = -1;
    ladData->imageName[0] = 0;
    ladData->numClientsStarted = -1;
    ladData->dspStatus = (UInt32)-1;

    if (ladKeys & LadKey_LINKCONFIGID) {
        /* Get linkConfigId from registry. */
        dataSize = sizeof(ladData->linkConfigId);

        if (!Reg_getValue(NULL, ladkey, linkConfigIdKey,
                    (UInt8 *)&(ladData->linkConfigId), &dataSize)) {
            PRINTVERBOSE0("\nLAD_getDspStatus: Reg_getValue() failed");
            PRINTVERBOSE0("    for linkConfigId\n");
            status = LAD_FAILURE;
        }
    }

    if (ladKeys & LadKey_IMAGENAME) {
        /* Get imageName from registry */
        if (status == LAD_SUCCESS) {
            dataSize = sizeof(ladData->imageName);
            if (!Reg_getValue(NULL, ladkey, imageNameKey,
                        (UInt8 *)&(ladData->imageName), &dataSize)) {
                PRINTVERBOSE0("\nLAD_getDspStatus: Reg_getValue() failed");
                PRINTVERBOSE0("    for image name\n");
                status = LAD_FAILURE;
            }
        }
    }

    if (ladKeys & LadKey_NUMCLIENTSSTARTED) {
        /* Read "numClientsStarted" from registry. */
        if (status == LAD_SUCCESS) {
            dataSize = sizeof(ladData->numClientsStarted);
            if (!Reg_getValue(NULL, ladkey, numStartedKey,
                        (UInt8 *)&(ladData->numClientsStarted), &dataSize)) {
                PRINTVERBOSE0("\nLAD getNumStarted: Reg_getValue() failed\n");
                status = LAD_FAILURE;
            }
        }
    }

    if (ladKeys & LadKey_DSPSTATUS) {
        /* Read "dspStatus" from registry. */
        if (status == LAD_SUCCESS) {
            dataSize = sizeof(ladData->dspStatus);
            if (!Reg_getValue(NULL, ladkey, dspStatusKey,
                        (UInt8 *)&(ladData->dspStatus), &dataSize)) {
                PRINTVERBOSE0("\nLAD getNumStarted: Reg_getValue() failed\n");
                status = LAD_FAILURE;
            }
        }
    }

    return (status);
}

/*
 *  ======== initLad ========
 */
static LAD_Status initLad(Void)
{
    Int i;

    Reg_init();

    for (i = 0; i < LAD_MAXNUMCLIENTS; i++) {
        clientConnected[i] = FALSE;
        clientStarted[i] = FALSE;
    }

    if ((_LAD_mutex = CreateMutex(NULL, FALSE, _LAD_MUTEX_NAME)) == NULL) {
        PRINTVERBOSE0("\nLAD initialization: Failed to create mutex\n");
        return (LAD_FAILURE);
    }

    return (LAD_SUCCESS);
}

/*
 *  ======== setLadRegData ========
 */
static LAD_Status setLadRegData(LadRegData *ladData, UInt32 ladKeys)
{
    Int         dataSize;
    LAD_Status  status = LAD_SUCCESS;

    if (ladKeys & LadKey_LINKCONFIGID) {
        /* Set linkConfigId in registry. */
        dataSize = sizeof(ladData->linkConfigId);

        if (!Reg_setValue(NULL, ladkey, linkConfigIdKey, REG_DWORD,
                    (UInt8 *)&(ladData->linkConfigId),
                    dataSize, Reg_NONVOLATILE)) {
            PRINTVERBOSE0("\nLAD setLadRegData: Reg_setValue() failed\n");
            status = LAD_FAILURE;
        }
    }

    if (ladKeys & LadKey_NUMCLIENTSSTARTED) {
        /* Write "numClientsStarted" to registry. */
        dataSize = sizeof(ladData->numClientsStarted);

        if (!Reg_setValue(NULL, ladkey, numStartedKey, REG_DWORD,
                    (UInt8 *)&(ladData->numClientsStarted),
                    dataSize, Reg_NONVOLATILE)) {
            PRINTVERBOSE0("\nLAD setLadRegData: Reg_setValue() failed\n");
            status = LAD_FAILURE;
        }
    }

    if (ladKeys & LadKey_DSPSTATUS) {
        /* Write "dspStatus" to registry. */
        dataSize = sizeof(ladData->dspStatus);

        if (!Reg_setValue(NULL, ladkey, dspStatusKey, REG_DWORD,
                    (UInt8 *)&(ladData->dspStatus),
                    dataSize, Reg_NONVOLATILE)) {
            PRINTVERBOSE0("\nLAD setLadRegData: Reg_setValue() failed\n");
            status = LAD_FAILURE;
        }
    }

    return (status);
}
/*
 *  @(#) ti.dsplink.utils.ladclient; 1, 0, 0,239; 12-2-2010 21:18:40; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

