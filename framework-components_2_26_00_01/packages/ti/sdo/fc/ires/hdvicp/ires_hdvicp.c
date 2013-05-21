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
 *  ======== ires_hdvicp.c ========
 */
#include <xdc/std.h>

#include <ti/sdo/utils/trace/gt.h>

#include "ires_hdvicp.h"
#include "iresman_protocol_hdvicp.h"
#include "_hdvicp.h"

#ifdef xdc_target__os_Linux

#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
static int memfd = -1;           //File descriptor for "/dev/mem" 
#endif

extern unsigned int _HDVICP_REGBASEADDR; 
extern unsigned int _HDVICP_MEMBASEADDR; 

#define _HDVICP_SYSSIZE 0x00200000 


/*
 * GT mask for the IRES_HDVICP module
 */
extern GT_Mask ti_sdo_fc_ires_hdvicp_GTMask;

extern void IRES_HDVICP_getStaticProperties(IRES_Handle resourceHandle,
        IRES_Properties * resourceProperties);

static void * memoryBaseAddress = NULL;
static void * registerBaseAddress = NULL;
static unsigned int pscBaseAddress = 0x0;

static int gtInit = 0;

/**
 *  ======= IRES_HDVICP_getProtocolName =======
 *  Return the name of the protocol
 */
String IRES_HDVICP_getName()
{

    if (0 == gtInit) {
        
        GT_init(); 

        GT_create(&ti_sdo_fc_ires_hdvicp_GTMask, "ti.sdo.fc.ires.hdvicp");
        
        gtInit = 1;
    }

    GT_0trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_ENTER, "IRES_HDVICP_getName> "
            "Enter\n");

    GT_1trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_ENTER, "IRES_HDVICP_getName> "
            "Exit (Name=%s)\n", IRES_HDVICP_PROTOCOLNAME);

    return (IRES_HDVICP_PROTOCOLNAME);
}

/**
 *  ======= IRES_HDVICP_getRevision =======
 *  Return the revision of the protocol
 */
IRES_ProtocolRevision * IRES_HDVICP_getRevision()
{
    if (0 == gtInit) {
        
        GT_init(); 

        GT_create(&ti_sdo_fc_ires_hdvicp_GTMask, "ti.sdo.fc.ires.hdvicp");
        
        gtInit = 1;
    }

    GT_0trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_ENTER, "IRES_HDVICP_getRevision>"            " Enter\n");

    GT_3trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_ENTER, "IRES_HDVICP_getRevision>"
            "Exit (Version=(%d.%d.%d))\n",
            IRES_HDVICP_PROTOCOLREVISION.Major,
            IRES_HDVICP_PROTOCOLREVISION.Source,
            IRES_HDVICP_PROTOCOLREVISION.Radius);

    return (&IRES_HDVICP_PROTOCOLREVISION);
}

/**
 *  ======= IRES_HDVICP_getMemRecs =======
 *  Provide the memory requirements for allocating the Logical Resource
 *  handle.
 *
 *  The 'protocol' determines the size and attributes of the memory that
 *  represents the logical resource. The size must be at least the size of
 *  IRES_HDVICP_Obj.
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Status IRES_HDVICP_getMemRecs(IRES_Handle handle,
        IRES_ProtocolArgs * resProtocolArgs, IALG_MemRec *memRecs)
{
    GT_assert(ti_sdo_fc_ires_hdvicp_GTMask, memRecs != NULL);
    GT_assert(ti_sdo_fc_ires_hdvicp_GTMask, resProtocolArgs != NULL);

    GT_3trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_ENTER,
            "IRES_HDVICP_getMemRecs> Enter (handle=0x%x, "
            "resProtocolArgs=0x%x, memRecs=0x%x)\n", handle, resProtocolArgs,
            memRecs);

    memRecs[0].alignment = 4;
    memRecs[0].size = sizeof(IRES_HDVICP_Obj);

    /*
     * IALG_EXTERNAL because we don't care where this memory is allocated
     */
    memRecs[0].space = IALG_EXTERNAL;

    /*
     * Memory should be persistent.
     */
    memRecs[0].attrs = IALG_PERSIST;

    GT_2trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_4CLASS,
            "IRES_HDVICP_getMemRecs> Amount of memory requested 0x%x, "
            "alignment 0x%x, space IALG_EXTERNAL attrs IALG_PERSIST\n",
            memRecs[0].size, memRecs[0].alignment);

    GT_0trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_ENTER,
            "IRES_HDVICP_getMemRecs> Exit (status=IRES_EOK)\n");

    return (IRES_OK); /* number of MemRecs */
}

/**
 *  ======= IRES_HDVICP_getNumMemRecs =======
 *  HDVICP protocol does not request any extra memory buffers.
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
Int IRES_HDVICP_getNumMemRecs(IRES_ProtocolArgs * protArgs)
{
    GT_1trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_ENTER,
            "IRES_HDVICP_getNumMemRecs> Enter (protArgs=0x%x)\n", protArgs);

    GT_0trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_ENTER,
            "IRES_HDVICP_getNumMemRecs> Exit (Num=1)\n");

    return ((Int)1);
}

/**
 *  ======= IRES_HDVICP_constructHandle =======
 *  HDVICP Protocol specific initialization function to finalize the
 *  creation of a resource object (handle).
 *  The protocol::initHandle function can extend the IRES_HDVICP_Obj struct
 *  and must store any additional allocated 'environment' memory
 *  within the resource handle and return the IALG_MemRec descriptors
 *  in protocol::getEnvBuffDescriptors() function.
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Handle IRES_HDVICP_constructHandle(
        IRES_ProtocolArgs * resProtocolArgs,
        IALG_MemRec *memRecs,
        IRESMAN_ConstructArgs * constructHandleArgs,
        IRES_Status *status)
{
    IRES_HDVICP_Handle handle = (IRES_HDVICP_Handle)memRecs[0].base;

    IRESMAN_HDVICP_ConstructHandleArgs * constructArgs =
        (IRESMAN_HDVICP_ConstructHandleArgs *)constructHandleArgs;

    GT_assert(ti_sdo_fc_ires_hdvicp_GTMask, resProtocolArgs != NULL);
    GT_assert(ti_sdo_fc_ires_hdvicp_GTMask, memRecs != NULL);
    GT_assert(ti_sdo_fc_ires_hdvicp_GTMask, constructHandleArgs != NULL);
    GT_assert(ti_sdo_fc_ires_hdvicp_GTMask, status != NULL);

    GT_3trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_ENTER,
            "IRES_HDVICP_constructHandle> Enter (protArgs=0x%x, memRecs=0x%x, "
            "constructHandleArgs=0x%x)\n", resProtocolArgs, memRecs,
            constructHandleArgs);

    if (handle == NULL) {

        *status = IRES_ENORESOURCE;

        GT_0trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_7CLASS,
                "IRES_HDVICP_constructHandle> NULL handle returned through "
                "memRecs\n");

        GT_0trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_ENTER,
                "IRES_HDVICP_constructHandle> Exit (handle=NULL)\n");

        return ((IRES_Handle)NULL);
    }

    (handle->ires).getStaticProperties = IRES_HDVICP_getStaticProperties;

    /*
     * Use the constructHandleargs to populate the handle withi the correct
     * id
     */
    handle->id = constructArgs->id;
    (handle->ires).persistent = constructArgs->persistent;

    if ((NULL == registerBaseAddress) || ((unsigned int)-1 == pscBaseAddress)) {

#ifdef xdc_target__os_Linux 
        memfd = open("/dev/mem", O_RDWR | O_SYNC); 
        if (-1 == memfd) {
           *status = IRES_EFAIL;
            return (NULL); 
        }
        registerBaseAddress = 
                (void *)mmap(0, _HDVICP_SYSSIZE, PROT_READ | PROT_WRITE,
                MAP_SHARED, memfd, (off_t)_HDVICP_REGBASEADDR);

        if (-1 == (unsigned int)registerBaseAddress) {
           *status = IRES_EFAIL;
            return (NULL); 
        }
        pscBaseAddress = 
                (unsigned int)mmap(0, _HDVICP_PSCSIZE, 
                PROT_READ | PROT_WRITE, MAP_SHARED, memfd,
                (off_t)_HDVICP_PSCBASE);

        if (-1 == pscBaseAddress) {
           *status = IRES_EFAIL;
            return (NULL); 
        }
#else
        registerBaseAddress = (void *)_HDVICP_REGBASEADDR;
#ifdef xdc_target__isaCompatible_64P

        /* Invalid field for C64P devices */
        pscBaseAddress = 0xFFFFFFFF;
#else
        pscBaseAddress = (unsigned int)_HDVICP_PSCBASE;
#endif
#endif
    }

    handle->registerBaseAddress = registerBaseAddress;
    handle->pscRegisterSpace = pscBaseAddress;

    if (NULL == memoryBaseAddress) {

#ifdef xdc_target__os_Linux 
        memoryBaseAddress = registerBaseAddress + 
                (_HDVICP_MEMBASEADDR - _HDVICP_REGBASEADDR);
#else
        memoryBaseAddress = (void *)_HDVICP_MEMBASEADDR;
#endif
    }

    handle->memoryBaseAddress = memoryBaseAddress;

    *status = IRES_OK;

    GT_2trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_ENTER,
            "IRES_HDVICP_constructHandle> Exit (status=%d, handle=0x%x)\n",
            *status, handle);

    return ((IRES_Handle)handle);
}

/**
 *  ======= IRES_HDVICP_getStaticProperties =======
 *  Returns the static properties of the particular resource
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
void IRES_HDVICP_getStaticProperties(IRES_Handle resourceHandle,
        IRES_Properties * resourceProperties)
{
    GT_2trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_ENTER,
            "IRES_HDVICP_getStaticProperties> Enter (resourceHandle=0x%x, "
            "resourceProperties=0x%x)\n", resourceHandle, resourceProperties);

#ifndef xdc_target__isaCompatible_64P
    ((IRES_HDVICP_Properties *)resourceProperties)->globalRegs = 
            (IRES_HDVICP_RegisterLayer *)
            (((IRES_HDVICP_Handle)resourceHandle)->registerBaseAddress);
#endif

    GT_0trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_ENTER,
            "IRES_HDVICP_getStaticProperties> Exit\n");
}

/**
 *  ======= IRES_HDVICP_destructHandle =======
 *  De-initialize the env stored in the IRES_HDVICP channel handle, before
 *  it is freed by the resource manager.
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Status IRES_HDVICP_destructHandle(IRES_Handle handle)
{
    GT_0trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_ENTER,
            "IRES_HDVICP_destructHandle> Enter\n");

    /*
     * Nothing allocated in this module
     * So nothing needs to be done.
     */
    GT_0trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_ENTER,
            "IRES_HDVICP_destructHandle> Exit (returnVal=IRES_OK)\n");

    return (IRES_OK);
}

IRESMAN_ConstructFxns IRESMAN_HDVICP_CONSTRUCTFXNS = {
    IRES_HDVICP_getName,
    IRES_HDVICP_getRevision,
    IRES_HDVICP_getMemRecs,
    IRES_HDVICP_getNumMemRecs,
    IRES_HDVICP_constructHandle,
    IRES_HDVICP_destructHandle
};
/*
 *  @(#) ti.sdo.fc.ires.hdvicp; 1, 0, 1,133; 12-1-2010 17:25:16; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

