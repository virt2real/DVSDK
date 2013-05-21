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
 *  ======== ires_vicp2.c ========
 */
#include <xdc/std.h>

#include "ires_vicp2.h"
#include "iresman_protocol_vicp2.h"
#include "_vicp2.h"

#ifdef xdc_target__os_Linux
#include <sys/mman.h>
#include <fcntl.h>
static int      memfd = -1;           //File descriptor for "/dev/mem"
#endif

static Bool getBaseAddress(unsigned int * config); 

/*
 * Process base address for VICP
 */
static unsigned int _VICP2_configBase = 0x0; 

#ifdef xdc_target__os_Linux
/*
 * Process base address for PSC 
 */
static unsigned int _VICP2_pscBase = 0x0; 
static unsigned int _VICP2_dmaViewConfigBase = 0x0;

#endif

extern void IRES_VICP2_getStaticProperties(IRES_Handle resourceHandle, 
        IRES_Properties * resourceProperties);

/**
 *  ======= IRES_VICP2_getProtocolName =======
 *  Return the name of the protocol 
 */
String IRES_VICP2_getName()
{
        return (IRES_VICP2_PROTOCOLNAME);
}


/**
 *  ======= IRES_VICP2_getRevision =======
 *  Return the revision of the protocol 
 */
IRES_ProtocolRevision * IRES_VICP2_getRevision ()
{
        return (&IRES_VICP2_PROTOCOLREVISION);
}

/**
 *  ======= IRES_VICP2_getMemRecs =======
 *  Provide the memory requirements for allocating the Logical Resource
 *  handle. 
 *
 *  The 'protocol' determines the size and attributes of the memory that 
 *  represents the logical resource. The size must be at least the size of 
 *  IRES_VICP2_Obj. 
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Status IRES_VICP2_getMemRecs(IRES_Handle handle, 
        IRES_ProtocolArgs * resProtocolArgs, IALG_MemRec *memRecs)
{

    //DBC_require(memRecs != NULL);
    //DBC_require(resProtocolArgs != NULL);

    memRecs[0].alignment = 4;
        memRecs[0].size = sizeof(_VICP2_IntObj);

    /*
     * IALG_EXTERNAL because we don't care where this memory is allocated
     */
    memRecs[0].space = IALG_EXTERNAL;

    /*
     * Memory should be persistent. 
     */
    memRecs[0].attrs = IALG_PERSIST;

    return (IRES_OK); /* number of MemRecs */
}

/**
 *  ======= IRES_VICP2_getNumMemRecs =======
 *  VICP protocol does not request any extra memory buffers. 
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
Int IRES_VICP2_getNumMemRecs(IRES_ProtocolArgs * protArgs)
{
    return ((Int)1);
}
    
/**
 *  ======= IRES_VICP2_constructHandle =======
 *  VICP Protocol specific initialization function to finalize the 
 *  creation of a resource object (handle). 
 *  The protocol::initHandle function can extend the IRES_VICP2_Obj struct
 *  and must store any additional allocated 'environment' memory 
 *  within the resource handle and return the IALG_MemRec descriptors
 *  in protocol::getEnvBuffDescriptors() function.
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Handle IRES_VICP2_constructHandle(
        IRES_ProtocolArgs * resProtocolArgs, 
        IALG_MemRec *memRecs, 
        IRESMAN_ConstructArgs * constructHandleArgs, 
        IRES_Status *status)
{
    IRES_VICP2_Handle handle = (IRES_VICP2_Handle)memRecs[0].base;
    Int i;
    unsigned int configBase;

    IRESMAN_VICP2_ConstructHandleArgs * constructArgs =
        (IRESMAN_VICP2_ConstructHandleArgs *)constructHandleArgs;

    //DBC_require(resProtocolArgs != NULL);
    //DBC_require(memRecs != NULL);
    //DBC_require(constructHandleArgs != NULL);
    //DBC_require(status != NULL);
    
    if (handle == NULL) {
        *status = IRES_ENORESOURCE;
        return (IRES_Handle) NULL;
    }

    ((IRES_VICP2_Handle)handle)->ires.getStaticProperties = 
            IRES_VICP2_getStaticProperties;                

    /*
     * Use the constructHandleargs to populate the ShadowPaRams with the 
     * correct link
     */
    handle->assignedIMX0 = constructArgs->assignedIMX0; 
    handle->assignedIMX1 = constructArgs->assignedIMX1; 
    handle->assignedNSF = constructArgs->assignedNSF; 
    handle->assignedMJCP = constructArgs->assignedMJCP; 

    (handle->ires).persistent = constructArgs->persistent;

    if (FALSE == getBaseAddress(&configBase)) {
        *status = IRES_ENORESOURCE;
        return (NULL);
    }    

    ((_VICP2_IntObj *)handle)->configBase = configBase;
    ((_VICP2_IntObj *)handle)->numBuffSwitches = constructArgs->numBuffSwitches;

    for (i = 0; i < constructArgs->numBuffSwitches; i++) {
        ((_VICP2_IntObj *)handle)->buffSwitchesOnly[i] = 
                constructArgs->buffSwitchesOnly[i] ;
    }

#ifdef xdc_target__os_Linux
    /*
     * Map the PSC address space as well _VICP2_dmaViewConfigBase 
     */            
    if (-1 == memfd) { 
        memfd = open("/dev/mem", O_RDWR | O_SYNC); 
            if (-1 == memfd) {
            *status = IRES_ENORESOURCE;
            return (NULL);
            }
    }
    if (0x0 == _VICP2_pscBase) {
        _VICP2_pscBase = (unsigned int)mmap(0, VICP2_PSCSIZE, 
                PROT_READ | PROT_WRITE, MAP_SHARED, memfd,
                (off_t)VICP2_PSCBASE);
            if (-1 == _VICP2_pscBase) {
            *status = IRES_ENORESOURCE;
            return (NULL);
            }
    }
    handle->pscRegisterSpace = _VICP2_pscBase;


    if (0x0 == _VICP2_dmaViewConfigBase) {
        _VICP2_dmaViewConfigBase = (unsigned int)mmap(0, _VICP2_regSize, 
                PROT_READ | PROT_WRITE, MAP_SHARED, memfd,
                (off_t)VICP2_DMAVIEWCONFIGBASE);
            if (-1 == _VICP2_dmaViewConfigBase) {
            *status = IRES_ENORESOURCE;
            return (NULL);
            }
    }
    handle->dmaViewConfigBaseAddr = _VICP2_dmaViewConfigBase;
        
#else
        handle->pscRegisterSpace = (unsigned int)VICP2_PSCBASE;
    handle->dmaViewConfigBaseAddr = (unsigned int)VICP2_DMAVIEWCONFIGBASE;
#endif

    /* First update the handles assigned IMCOP buffer addresses */   
    for (i = 0; i < IRES_VICP2_NUMBUFFERS; i++) {
        if (constructArgs->assignedIMCOPBuffers[i] != RESNA) {
            handle->assignedIMCOPBuffers[i] = configBase + 
                    _VICP2_buffOffsets[i];  
        }
        else {
            handle->assignedIMCOPBuffers[i] = RESNA;
        }
    }     

    handle->numMemBufs = constructArgs->numMemBufs;

    for (i = 0; i < constructArgs->numMemBufs; i++) {
        handle->assignedMemAddrs[i] = constructArgs->assignedMemAddrs[i] + 
                configBase; 
        handle->assignedMemSizes[i] = constructArgs->assignedMemSizes[i];
    }

    handle->configBaseAddress = _VICP2_configBase; 

    *status = IRES_OK;

    return (IRES_Handle)handle;
}

/**
 *  ======= IRES_VICP2_getStaticProperties =======
 *  Returns the static properties of the particular resource
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
void IRES_VICP2_getStaticProperties(IRES_Handle resourceHandle, 
        IRES_Properties * resourceProperties)
{
    int i;
    IRES_VICP2_Properties * properties = 
            (IRES_VICP2_Properties *)resourceProperties;

    _VICP2_IntObj * vicpObj =  (_VICP2_IntObj *)resourceHandle;

    unsigned int base = vicpObj->configBase;
    unsigned char ** bufferPtr = NULL;

    /* IRES_VICP2_Registers * _registers = &(vicpObj->registers); */

    /* TODO */

    properties->size = sizeof(IRES_VICP2_Properties);
    
    properties->buffers.size = sizeof(IRES_VICP2_Buffers);

    properties->buffers.vicp_cfg_base = (unsigned char *)base; 

    bufferPtr = &(properties->buffers.imgBufA_base); 
    for (i = 0; i < IRES_VICP2_NUMBUFFERS; i++) {
        if (_VICP2_buffOffsets[i] == RESNA) {
            *bufferPtr = (unsigned char *)RESNA; 
        }
        else {
            *bufferPtr = (unsigned char *)(_VICP2_buffOffsets[i] + base); 
        }
        bufferPtr++; 
    } 
}

/**
 *  ======= IRES_VICP2_destructHandle =======
 *  De-initialize the env stored in the IRES_VICP2 channel handle, before
 *  it is freed by the resource manager.
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Status IRES_VICP2_destructHandle(IRES_Handle handle)
{
    /*
     * Nothing allocated in this module
     * So nothing needs to be done.
     */
     return (IRES_OK);
}

IRESMAN_ConstructFxns IRESMAN_VICP2_CONSTRUCTFXNS = {
    IRES_VICP2_getName, 
    IRES_VICP2_getRevision, 
    IRES_VICP2_getMemRecs,
    IRES_VICP2_getNumMemRecs,
    IRES_VICP2_constructHandle,
    IRES_VICP2_destructHandle
};
 
static Bool getBaseAddress(unsigned int * config) 
{
#ifdef xdc_target__os_Linux
    /* This should be handled by the Linuxutils module, for now, handling it 
       here */

    if (0x0 == _VICP2_configBase) {

        if (_VICP2_dm365 || _VICP2_dm355) {
            if (-1 == memfd) { 
                memfd = open("/dev/mem", O_RDWR | O_SYNC); 
            }
    
            _VICP2_configBase = (unsigned int)mmap(0, 
                    _VICP2_regSize, PROT_READ | PROT_WRITE, MAP_SHARED, memfd,
                    (off_t)_VICP2_imcopConfigBase);
    
            if (-1 == _VICP2_configBase) {
                return (FALSE);
            }
        }
    }
    
    *config = _VICP2_configBase;
#else
        _VICP2_configBase = _VICP2_imcopConfigBase;
        *config = _VICP2_imcopConfigBase;
#endif
    return (TRUE);
} 
/*
 *  @(#) ti.sdo.fc.ires.vicp; 1, 0, 1,177; 12-1-2010 17:25:26; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

