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
 *  ======== iresman_addrspace.c ========
 *  Resource manager for algorithm-requested address space permission.
 */

#include <xdc/std.h>

/*
 * Define this, before including ires_<>.h, as that checks for this
 * define to avoid multiple inclusion of the static Protocol Version definition
 * of IRES_<>_PROTOCOLREVISION from the header file.
 */
#define ti_sdo_fc_ires_NOPROTOCOLREV

#include "iresman_addrspace.h"
#include "ires_addrspace.h"
#include "iresman_protocol_addrspace.h"

#include <ti/sdo/utils/trace/gt.h>

#include "_addrspace.h"

#ifdef xdc_target__os_Linux
#include <sys/mman.h>
#include <fcntl.h>
#elif xdc_target__os_WindowsCE
#include <windows.h>
#include <ti/sdo/winceutils/cmem/cmem.h>
#endif


/* Holds the internal state of an initialized object */
typedef struct IRESMAN_ADDRSPACE_InternalState {

    IRESMAN_PersistentAllocFxn * allocFxn;      /* Memory allocation Function */
    IRESMAN_PersistentFreeFxn * freeFxn;        /* Memory free Function */
} IRESMAN_ADDRSPACE_InternalState;

GT_Mask ti_sdo_fc_ires_addrspace_GTMask;
#define CURTRACE ti_sdo_fc_ires_addrspace_GTMask

/* Flag indicating if the resource manager is initialized */
static unsigned int _initialized = 0;


/* Flag indicating if gt has been initialized */
static int gtInit = 0;

/* Represents the IRES EDMA3 Resource manager */
static IRESMAN_ADDRSPACE_InternalState _resmanInternalState;

#ifdef xdc_target__os_Linux
/* Represents the /dev/mem file descriptor */
static int memfd = -1;

#elif xdc_target__os_WindowsCE

static DWORD dwPageSize = 0;
#endif

/* variable created by .xdt file, who's value varies based on config */
extern Bool ADDRSPACE_noTranslation;

/*
 *  ======== IRESMAN_ADDRSPACE_getProtocolName ========
 *  Function to return the name of the protocol
 */
String IRESMAN_ADDRSPACE_getProtocolName()
{
    String name;

    if (0 == gtInit) {
        GT_create(&ti_sdo_fc_ires_addrspace_GTMask,
                "ti.sdo.fc.ires.addrspace");

        GT_init();
        gtInit = 1;
    }

    GT_0trace(CURTRACE, GT_ENTER,
            "_IRESMAN_ADDRSPACE_getProtocolName> Enter\n");

    name = IRESMAN_ADDRSPACE_CONSTRUCTFXNS.getName();

    GT_1trace(CURTRACE, GT_ENTER,
            "_IRESMAN_ADDRSPACE_getProtocolName> Exit (Name=%s)\n",
            name);

    return (name);
}

/*
 *  ======== IRESMAN_ADDRSPACE_getProtocolRevision ========
 *  Function to return the revision of the protocol
 */
IRES_ProtocolRevision * IRESMAN_ADDRSPACE_getProtocolRevision()
{
    IRES_ProtocolRevision * version;

    if (0 == gtInit) {
        GT_create(&CURTRACE, "ti.sdo.fc.ires.addrspace");
        GT_init();
        gtInit = 1;
    }

    GT_0trace(CURTRACE, GT_ENTER,
            "_IRESMAN_ADDRSPACE_getProtocolRevision> Enter\n");

    version = IRESMAN_ADDRSPACE_CONSTRUCTFXNS.getRevision();

    GT_3trace(CURTRACE, GT_ENTER, "_IRESMAN_ADDRSPACE_getProtocolRevision> "
            "Exit (Version=(%d.%d.%d))\n", version->Major,
            version->Source, version->Radius);

    return (version);
}

/*
 *  ======== IRESMAN_ADDRSPACE_init ========
 *  Function to initialize the device specific resource manager implementation
 */
IRES_Status IRESMAN_ADDRSPACE_init(IRESMAN_Params * initArgs)
{
    IRESMAN_AddrSpaceParams * resmanArgs = (IRESMAN_AddrSpaceParams *)initArgs;
#if xdc_target__os_WindowsCE
    SYSTEM_INFO  systemInfo;
#endif

    GT_assert(ti_sdo_fc_ires_addrspace, initArgs != NULL);

    /*  Check if already initialized */
    if (_initialized) {
        GT_0trace(CURTRACE, GT_ENTER,
                "_IRESMAN_ADDRSPACE_init> Exit (status=IRES_EEXISTS)\n");

       return (IRES_EEXISTS);
    }

    if (0 == gtInit) {
        GT_create(&CURTRACE, "ti.sdo.fc.ires.addrspace");
        GT_init();
        gtInit = 1;
    }

    GT_1trace(CURTRACE, GT_ENTER,
            "_IRESMAN_ADDRSPACE_init> Enter (initArgs=0x%x)\n", initArgs);

    /*
     * Information regarding the memory allocation/free functions
     * is stored as part of the internal state of the resource
     * manager
     */
    _resmanInternalState.allocFxn = resmanArgs->baseConfig.allocFxn;
    _resmanInternalState.freeFxn = resmanArgs->baseConfig.freeFxn;

#if xdc_target__os_WindowsCE
    /* Get the page size for Windows CE */
    GetSystemInfo(&systemInfo);
    dwPageSize = systemInfo.dwPageSize;

    if (CMEM_init() != 0) {
        GT_0trace(CURTRACE, GT_7CLASS,
                "_IRESMAN_ADDRSPACE_init> Exit (status=IRES_ENORESOURCE)\n");

       return (IRES_ENORESOURCE);
    }
#endif

    /* Set Initalized flag to 1 if successful */
     _initialized = 1;

    GT_0trace(CURTRACE, GT_ENTER,
            "_IRESMAN_ADDRSPACE_init> Exit (status=IRES_OK)\n");

     return (IRES_OK);
}

/*
 *  ======== IRESMAN_ADDRSPACE_exit ========
 *  Function called when RESMAN is no longer needed. Use it to free memory
 *  allocated etc
 */
IRES_Status IRESMAN_ADDRSPACE_exit()
{
    /* Check if initialized */
    GT_0trace(CURTRACE, GT_ENTER,
            "_IRESMAN_ADDRSPACE_exit> Enter \n");

    if (!(_initialized)) {
        GT_0trace(CURTRACE, GT_ENTER,
                "_IRESMAN_ADDRSPACE_exit> Exit (status=IRES_ENOINIT)\n");

        return (IRES_ENOINIT);
    }

    /*
     * Free up any memory that might be allocated in this module
     * Basically memory that has been used by the protocol implementation
     */

    /* Set the initialized flag to zero again */
    _initialized = 0;

    GT_0trace(CURTRACE, GT_ENTER,
            "_IRESMAN_ADDRSPACE_exit> Exit (status=IRES_OK)\n");

    GT_exit();

    return (IRES_OK);
}

/*
 *  ======== IRESMAN_ADDRSPACE_getHandles ========
 *  Function that returns the IRES_Handle to the resource requested using the
 *  IRES_ResourceProtocolArgs
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Handle IRESMAN_ADDRSPACE_getHandles( IALG_Handle algHandle,
        IRES_ProtocolArgs * protocolArgs, Int scratchGroupId,
        IRES_Status * status)
{
    IALG_MemRec resourceMemRecs[1];
    IALG_MemRec constructHandleMemRec;
    Int numMemRecs;

    IRES_Handle resourceHandle = (IRES_Handle)NULL;
    IRESMAN_ADDRSPACE_ConstructHandleArgs * constructArgs = NULL;
    IRES_ADDRSPACE_ProtocolArgs * protArgs = (IRES_ADDRSPACE_ProtocolArgs *)
            protocolArgs;

//#ifdef xdc_target__os_Linux
    unsigned int mapAddr = 0x0;
    unsigned int mapLen = 0x0;
    int prot = 0x0;
    int cmemStatus;
//#endif

    GT_2trace(CURTRACE, GT_ENTER,
            "_IRESMAN_ADDRSPACE_getHandles> Enter (protocolArgs=0x%x, "
            "scratchGroupId=%d)\n", protocolArgs, scratchGroupId);

    GT_assert(CURTRACE, protocolArgs);

    if (_initialized != 1) {
        *status =  IRES_ENORESOURCE;

        GT_0trace(CURTRACE, GT_7CLASS,
                "_IRESMAN_ADDRSPACE_getHandles> RMAN register for ADDRSPACE "
                "resource not happened successfully. Please call RMAN_register "
                "before trying to assign or release resources\n");

        return (NULL);
    }

    numMemRecs = IRESMAN_ADDRSPACE_CONSTRUCTFXNS.getNumMemRecs
        ( (IRES_ProtocolArgs *)protocolArgs);

    IRESMAN_ADDRSPACE_CONSTRUCTFXNS.getMemRecs((IRES_Handle)NULL,
            (IRES_ProtocolArgs *) protocolArgs, resourceMemRecs);

    /*
     * Allocate memory for the constructHandle Arguments
     */
    constructHandleMemRec.size = sizeof(IRESMAN_ADDRSPACE_ConstructHandleArgs);
    constructHandleMemRec.alignment = 4;
    constructHandleMemRec.space = IALG_ESDATA;
    constructHandleMemRec.attrs = IALG_PERSIST;

    if (FALSE == _resmanInternalState.allocFxn(&constructHandleMemRec, 1)) {

        GT_2trace(CURTRACE, GT_7CLASS,
                "_IRESMAN_ADDRSPACE_getHandles> Error allocating memory for "
                "construct args of size 0x%x, alignment 0x%x, space IALG_ESDATA"
                ", attrs IALG_PERSIST\n", constructHandleMemRec.size,
                constructHandleMemRec.alignment);

        GT_0trace(CURTRACE, GT_ENTER,
                "_IRESMAN_ADDRSPACE_getHandles> Exit (handle=NULL, "
                "status=IRES_ENOMEM)\n");

        *status = IRES_ENOMEM;
        return (NULL);
    }

    if (FALSE == _resmanInternalState.allocFxn(resourceMemRecs, numMemRecs)) {

        GT_2trace(CURTRACE, GT_7CLASS,
                "_IRESMAN_ADDRSPACE_getHandles> Error allocating memory for "
                "resource handle of size 0x%x, alignment 0x%x, space "
                "IALG_ESDATA, attrs IALG_PERSIST\n", resourceMemRecs->size,
                resourceMemRecs->alignment);

        /* Free constructHandleMemRec */
        _resmanInternalState.freeFxn(&constructHandleMemRec, 1);

        GT_0trace(CURTRACE, GT_ENTER,
                "_IRESMAN_ADDRSPACE_getHandles> Exit (handle=NULL, "
                "status=IRES_ENOMEM)\n");

        *status = IRES_ENOMEM;
        return (NULL);

    }

    /* Build the resource here */
    constructArgs = constructHandleMemRec.base;

    if (ADDRSPACE_noTranslation) {
        constructArgs->addr = protArgs->addr;
        constructArgs->len = protArgs->len;
    }
    else {
#ifdef ADDRSPACE_STD
        constructArgs->addr = protArgs->addr;
        constructArgs->len = protArgs->len;
#else

#ifdef xdc_target__os_Linux
        if (-1 == memfd) {
            memfd = open("/dev/mem", O_RDWR | O_SYNC);

            if (-1 == memfd) {
                *status =  IRES_ENORESOURCE;

                GT_0trace(CURTRACE, GT_7CLASS,
                        "_IRESMAN_ADDRSPACE_getHandles> Error opening "
                        "file descriptor for /dev/mem\n");

                /* Free the memory for the ConstructArgs */
                _resmanInternalState.freeFxn(&constructHandleMemRec, 1);

                GT_0trace(CURTRACE, GT_ENTER,
                    "_IRESMAN_ADDRSPACE_getHandles> Exit (handle=NULL, "
                    "status=IRES_ENORESOURCE)\n");

                return (NULL);
            }
        }

        if (protArgs->attrib & IRES_ADDRSPACE_READ) {
            prot |= PROT_READ;
        }

        if (protArgs->attrib & IRES_ADDRSPACE_WRITE) {
            prot |= PROT_WRITE;
        }

        if (protArgs->attrib & IRES_ADDRSPACE_EXEC) {
            prot |= PROT_EXEC;
        }

        if (protArgs->attrib & IRES_ADDRSPACE_NONE) {
            prot |= PROT_NONE;
        }

        /* Align addr to 4K boundary */
        mapAddr = (unsigned int)(protArgs->addr) & 0xFFFFF000;

        /* Adjust the length to be mapped accordingly */
        mapLen = (unsigned int)(protArgs->addr) - mapAddr +
                (unsigned int)protArgs->len;

        /* Store the actual mapped area as base */
        constructArgs->mapBase = (unsigned int)mmap(0, (unsigned int)mapLen,
                prot, MAP_SHARED, memfd, (off_t)mapAddr);

        if (constructArgs->mapBase == (unsigned int)-1) {

            *status =  IRES_ENORESOURCE;

            GT_2trace(CURTRACE, GT_7CLASS,
                   "_IRESMAN_ADDRSPACE_getHandles> Error in the mmap"
                   "command for addr 0x%x and len 0x%x\n", mapAddr, mapLen);

            /* Free the memory for the ConstructArgs */
            _resmanInternalState.freeFxn(&constructHandleMemRec, 1);

            GT_0trace(CURTRACE, GT_ENTER,
                    "_IRESMAN_ADDRSPACE_getHandles> Exit (handle=NULL, "
                    "status=IRES_ENORESOURCE)\n");

            return (NULL);
        }

        constructArgs->mapLen = mapLen;

        /* Store the address to be returned to algorithm */
        constructArgs->addr = (Void *) (constructArgs->mapBase +
                (protArgs->addr - mapAddr));

        /* Store the length to be mapped */
        constructArgs->len = protArgs->len;

#elif xdc_target__os_WindowsCE
        /* Align addr to page boundary */
        mapAddr = (unsigned int)(protArgs->addr) & ~(dwPageSize - 1);

        /* Adjust the length to be a multiple of page size */
        mapLen = ((unsigned int)(protArgs->addr) - mapAddr + 
                (unsigned int)protArgs->len + dwPageSize - 1) &
            ~(dwPageSize - 1);

        cmemStatus = CMEM_mapAddress(mapAddr, mapLen, 0,
                &(constructArgs->mapBase));

        if (cmemStatus != 0) {
            GT_3trace(CURTRACE, GT_7CLASS,
                   "_IRESMAN_ADDRSPACE_getHandles> CMEM_mapAddress(0x%x, "
                    "0x%x) failed: %d\n", mapAddr, mapLen, cmemStatus);

            /* Free the memory for the ConstructArgs */
            _resmanInternalState.freeFxn(&constructHandleMemRec, 1);

            GT_0trace(CURTRACE, GT_ENTER, "_IRESMAN_ADDRSPACE_getHandles> "
                    "Exit (handle=NULL)\n");
            return (NULL);
        }

        /* Save physical address and length for unmapping later */
        constructArgs->mapLen = mapLen;

        /* Store the address to be returned to algorithm */
        constructArgs->addr = (Void *)(constructArgs->mapBase +
                ((UInt32)protArgs->addr - mapAddr));

        /* Store the length passed in by the algorithm */
        constructArgs->len = protArgs->len;
#else
        constructArgs->addr = protArgs->addr; 
        constructArgs->len = protArgs->len;
#endif
#endif
    }

    /* Build the resource here */

    /*
     * Use IRES_ADDRSPACE_RESOURCEPROTOCOL to init the resource protocol
     * if required
     */
    resourceHandle = IRESMAN_ADDRSPACE_CONSTRUCTFXNS.constructHandle(
            protocolArgs, resourceMemRecs, (IRESMAN_ConstructArgs *)
            constructArgs, status);

    /* Free the memory for the ConstructArgs */
    _resmanInternalState.freeFxn(&constructHandleMemRec, 1);

    GT_2trace(CURTRACE, GT_ENTER,
            "_IRESMAN_ADDRSPACE_getHandles> Exit (status=%d, "
            "resourceHandle=0x%x)\n", *status, resourceHandle);

    return (resourceHandle);
}

/*
 *  ======== IRESMAN_ADDRSPACE_freeHandle ========
 *  Frees handles back to the resource pool resources to free
 */
/*  ARGSUSED - this line tells the compiler not to warn about unused args */
IRES_Status IRESMAN_ADDRSPACE_freeHandle(IALG_Handle algHandle, IRES_Handle
        algResourceHandle, IRES_ProtocolArgs * protocolArgs,
        Int scratchGroupId)
{
    IALG_MemRec resourceMemRecs[1];
    Int numMemRecs;
    IRES_Status status = IRES_OK;
    int cmemStatus;

//#ifdef xdc_target__os_Linux
    unsigned int addr;
    unsigned int len;
//#endif
    GT_assert(CURTRACE, protocolArgs);
    GT_assert(CURTRACE, algResourceHandle);

    GT_3trace(CURTRACE, GT_ENTER,
            "_IRESMAN_ADDRSPACE_freeHandles> Enter (handle=0x%x, "
            "protocolArgs=0x%x, scratchGroupId=%d)\n", algResourceHandle,
            protocolArgs, scratchGroupId);

    if (_initialized != 1) {
        status =  IRES_ENORESOURCE;

        GT_0trace(CURTRACE, GT_7CLASS,
                "_IRESMAN_ADDRSPACE_getHandles> RMAN register for ADDRSPACE "
                "resource not happened successfully. Please call RMAN_register"
                " before trying to assign or release resources\n");

        return (status);
    }


    /*
     * Obtain memory resources to free and free them
     */
    numMemRecs = IRESMAN_ADDRSPACE_CONSTRUCTFXNS.getNumMemRecs
        ( (IRES_ProtocolArgs *)protocolArgs);

    IRESMAN_ADDRSPACE_CONSTRUCTFXNS.getMemRecs((IRES_Handle)NULL,
            (IRES_ProtocolArgs *) protocolArgs, resourceMemRecs);

    /* Set Base address of Memory location to free */
    resourceMemRecs[0].base = algResourceHandle;

    /*
     * Use IRES_ADDRSPACE_RESOURCEPROTOCOL to de-init the resource protocol
     * if required
     */
    IRESMAN_ADDRSPACE_CONSTRUCTFXNS.destructHandle(algResourceHandle);

#ifdef xdc_target__os_Linux
    addr = ((IRES_ADDRSPACE_IntObj *)algResourceHandle)->mapBase;
    len = ((IRES_ADDRSPACE_IntObj *)algResourceHandle)->mapLen;

    munmap((void *)addr, (size_t)len);
#elif xdc_target__os_WindowsCE
    addr = ((IRES_ADDRSPACE_IntObj *)algResourceHandle)->mapBase;
    len = ((IRES_ADDRSPACE_IntObj *)algResourceHandle)->mapLen;

    cmemStatus = CMEM_unmapAddress(addr, len);
    if (cmemStatus != 0) {
        GT_1trace(CURTRACE, GT_7CLASS, "_IRESMAN_ADDRSPACE_freeHandles> "
                "CMEM_unmapAddress() failed: %d\n", cmemStatus);
    }
#endif
    /*
     * Free the memory for the handles
     */
    _resmanInternalState.freeFxn(resourceMemRecs, numMemRecs);

    GT_0trace(CURTRACE, GT_ENTER,
            "_IRESMAN_ADDRSPACE_freeHandles> Exit (status=IRES_OK)\n");

    return (IRES_OK);
}

IRESMAN_Fxns IRESMAN_ADDRSPACE =  {
    IRESMAN_ADDRSPACE_getProtocolName,
    IRESMAN_ADDRSPACE_getProtocolRevision,
    IRESMAN_ADDRSPACE_init,
    IRESMAN_ADDRSPACE_exit,
    IRESMAN_ADDRSPACE_getHandles,
    IRESMAN_ADDRSPACE_freeHandle
};

IRESMAN_AddrSpaceParams IRESMAN_ADDRSPACE_DEFAULTPARAM;

IRESMAN_Fxns * ADDRSPACE_getIresmanFxns()
{
    return ((Void *)(&IRESMAN_ADDRSPACE));
}

IRESMAN_Params * ADDRSPACE_getDefaultParams()
{
    IRESMAN_ADDRSPACE_DEFAULTPARAM.baseConfig.size =
            sizeof(IRESMAN_Params);

    return ((IRESMAN_Params *)&IRESMAN_ADDRSPACE_DEFAULTPARAM);
}
/*
 *  @(#) ti.sdo.fc.ires.addrspace; 1, 0, 0,61; 12-1-2010 17:24:55; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

