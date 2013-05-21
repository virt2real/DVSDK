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
 *  ======== bufres.c ========
 *  IRES implementation for the buffer resource.
 */

#include <xdc/std.h>

#include <ti/sdo/fc/ires/iresman.h>
#include <ti/sdo/utils/trace/gt.h>

#include "bufres.h"

#define MAXRECS 10
#define NUMRECS 1

/*
 *  ======== BUFRES_ConstructArgs ========
 *  Arguments passed to the constructHandle() function.
 */
typedef struct BUFRES_ConstructArgs {
    Int    size;    /* Size of this structure */

    /*
     *  Fields that will go into the BUFRES_Obj (that are not already in
     *  BUFRES_Args)
     */
    Void   *base;    /* Base address */
} BUFRES_ConstructArgs;

#if GT_TRACE
static GT_Mask curTrace;
#endif

/* Resource Manager Interface functions */
static String getProtocolName();
static IRES_ProtocolRevision * getRevision();
static IRES_Status initBuf(IRESMAN_Params *args);
static IRES_Status exitBuf();
static IRES_Handle getBuf(IALG_Handle alg, IRES_ProtocolArgs *args,
        Int scratchId, IRES_Status *status);
static IRES_Status freeBuf(IALG_Handle alg, IRES_Handle res,
        IRES_ProtocolArgs *args, Int scratchId);

/*
 *  ======== BUFRES_MGRFXNS ========
 *  Implementation of IRESMAN_Fxns interface. These functions are called
 *  (by a resource manager) to:
 *      - initialize the resource with config params
 *      - allocate resource based on args
 *      - free resource (based on args)
 *      - exit the resource
 */
IRESMAN_Fxns BUFRES_MGRFXNS = {
    getProtocolName,
    getRevision,
    initBuf,          /* init */
    exitBuf,          /* exit */
    getBuf,           /* getHandle */
    freeBuf,          /* freeHandle */
};

/* Resource Request Interface functions */
static IRES_Status getMemRecs(IRES_Handle ires, IRES_ProtocolArgs *args,
        IALG_MemRec *memRecs);
static Int getNumRecs(IRES_ProtocolArgs *args);
static IRES_Handle constructHandle(IRES_ProtocolArgs *args,
        IALG_MemRec *memRecs, IRESMAN_ConstructArgs *cArgs,
        IRES_Status *status);
static IRES_Status destructHandle(IRES_Handle ires);

/*
 *  ======== BUFRES_REQFXNS ========
 *  Implementation of IRESMAN_ConstructFxns. These functions get called by the
 *  resource's IRESMAN_Fxns when allocating a resource, to
 *      - determine how much memory is needed
 *      - initialize the allocated memory
 */
IRESMAN_ConstructFxns BUFRES_REQFXNS = {
    getProtocolName,
    getRevision,
    getMemRecs,          /* getResourceMemRecs */
    getNumRecs,          /* getNumMemRecs */
    constructHandle,     /* constructHandle */
    destructHandle,      /* destructHandle */
};

/* Resource Protocol Interface functions */
Void getStaticProps(IRES_Handle res, IRES_Properties *props);

/*
 *  ======== BUFRES_PROTOCOL ========
 *  Implementation of IRES_Protocol interface. This function can be queried to:
 *      - get static information about the resource.
 */
static IRESMAN_PersistentAllocFxn *allocFxn;
static IRESMAN_PersistentFreeFxn *freeFxn;

/*
 *  Internal types and objects for this resource manager.
 */

/*
 *  ======== BufRes ========
 *  Properties and state of the buffer resource.
 */
typedef struct BufRes {
    Void    *base;      /* Base address of buffer */
    Int      length;    /* Length of buffer */
    Int      scratchId; /* Scratch group Id of algorithms using this buffer */

    /*
     *  If 'mode' is IRES_SCRATCH, then the buffer can be shared by other
     *  algorithms within the same scratch group. If 'mode' is IRES_PERSISTENT,
     *  the buffer can only be used by the algorithm that is currently being
     *  granted the resource.
     */
    IRES_RequestMode mode;      /* IRES_SCRATCH or IRES_PERSISTENT */
    Int              refCount;  /* Number of algorithms using this buffer */
} BufRes;

static Void *bufAlloc(Int id, Int size, Int align);

static Int curInit = 0;

/* The resource */
static BufRes buffer = {
    NULL,         /* base */
    0,            /* length */
    -1,           /* scratchId */
    IRES_SCRATCH, /* mode */
    0             /* refCount */
};

/* ======== IMPLEMENTATION ======== */

/*
 *  ======== IRES RESOURCE MANAGER FUNCTIONS ========
 *  getProtocolName, getRevision, initBuf, exitBuf, getBuf, freeBuf
 */

/*
 *  ======== getProtocolName ========
 */
static String getProtocolName()
{
    return (BUFRES_PROTOCOLNAME);
}

/*
 *  ======== getRevision ========
 */
static IRES_ProtocolRevision * getRevision()
{
    return (&BUFRES_PROTOCOLVERSION);
}

/*
 *  ======== initBuf ========
 *  Initialize the BUFRES resource manager.
 */
static IRES_Status initBuf(IRESMAN_Params *args)
{
    BUFRES_Params    *cArgs = (BUFRES_Params *)args;
    IRES_Status       status = IRES_OK;

    if (curInit++) {
        /* Already initialized */
        return (IRES_EINIT);
    }

    GT_init();
    GT_create(&curTrace, BUFRES_GTNAME);

    GT_0trace(curTrace, GT_ENTER, "BUFRES initBuf> entered\n");

    GT_assert(curTrace, args != NULL);
    GT_assert(curTrace, args->allocFxn != NULL);
    GT_assert(curTrace, args->freeFxn != NULL);

    allocFxn = args->allocFxn;
    freeFxn = args->freeFxn;

    /* Initialize the Buffer Resource Manager based on config params */
    buffer.base = cArgs->base;
    buffer.length = cArgs->length;
    buffer.scratchId = -1;
    buffer.refCount = 0;

    GT_1trace(curTrace, GT_ENTER, "BUFRES initBuf> returning 0x%x\n", status);

    return (status);
}

/*
 *  ======== exitBuf ========
 */
static IRES_Status exitBuf()
{
    GT_0trace(curTrace, GT_ENTER, "BUFRES exit>\n");

    if (--curInit == 0) {
        /* clean up */
        buffer.base = NULL;
        buffer.length = 0;
        buffer.scratchId = -1;
        buffer.refCount = 0;
    }

    return (IRES_OK);
}

/*
 *  ======== getBuf ========
 * This function allocates the buffer resource
 */
/* ARGSUSED */
static IRES_Handle getBuf(IALG_Handle alg, IRES_ProtocolArgs *args,
        Int scratchId, IRES_Status *pStatus)
{
    BUFRES_ConstructArgs cArgs;
    BUFRES_Handle        res = NULL;
    IALG_MemRec          memRecs[MAXRECS];
    Int                  nRecs;
    Int                  length;
    Int                  align;
    Void                *base = NULL;
    IRES_RequestMode     mode;
    IRES_Status          status = IRES_OK;
    IRES_Status          retVal;

    GT_0trace(curTrace, GT_ENTER, "BUFRES getBuf> entered>\n");

    GT_assert(curTrace, pStatus != NULL);
    GT_assert(curTrace, args != NULL);

    length = ((BUFRES_Args *)args)->length;
    align = ((BUFRES_Args *)args)->align;
    mode = args->mode; /* IRES_SCRATCH or IRES_PERSISTENT */

    GT_3trace(curTrace, GT_ENTER, "BUFRES getBuf> length [0x%x], "
            "align [0x%x], mode = %s>\n", length, align,
            (mode == IRES_PERSISTENT) ? "IRES_PERSISTENT" : "IRES_SCRATCH");

    if (curInit == 0) {
        *pStatus = IRES_ENOINIT;
        return (NULL);
    }

    /* TODO: acquire a lock */

    /*
     *  The buffer can be used for the resource request if it is currently
     *  being used by another algorithm with the same scratchId, or if
     *  the buffer is not currently being used. The memory chunk of the
     *  requested size and alignment must also fit in the buffer.
     */
    if (((mode == IRES_SCRATCH) && (mode == buffer.mode) &&
                (scratchId == buffer.scratchId)) ||
            (buffer.refCount == 0)) {
        if ((base = bufAlloc(0, length, align)) == NULL) {
            /* The requested memory will not fit in the buffer */
            GT_0trace(curTrace, GT_6CLASS, "BUFRES getBuf> buffer resource"
                    " allocation failed.\n");
            status = IRES_ENORESOURCE;
        }
    }
    else {
        /* Buffer is in use */
        status = IRES_ENORESOURCE;
    }

    if (status == IRES_OK) {
        /*
         *  Found available resource, now allocate memory to construct
         *  a BUFRES handle to pass back to the algorithm.
         */
        /* Number of buffers needed to construct a BUFRES object */
        nRecs = getNumRecs(args);

        if (nRecs > MAXRECS) {
            /* Error: Weren't expecting to allocate this many buffers */
            status = IRES_EFAIL;
        }
        else {
            /*
             *  Fill in memRecs[] with memory requirements to allocate the
             *  BUFRES object.
             */
            retVal = getMemRecs(NULL, args, memRecs);
            if (retVal != IRES_OK) {
                status = IRES_ENOMEM;
            }
            else {
                /* Now allocate memory used to construct the BUFRES object */
                if (!allocFxn(memRecs, nRecs)) {
                    status = IRES_ENOMEM;
                }
            }
        }
    }

    if (status == IRES_OK) {
        /* Init cArgs with whatever is necessary to construct BUFRES object */
        cArgs.size = sizeof(BUFRES_ConstructArgs);
        cArgs.base = base;

        /* Initialize the buffers */
        res = (BUFRES_Handle)constructHandle(args, memRecs,
                (IRESMAN_ConstructArgs *)&cArgs, &retVal);

        if (retVal != IRES_OK) {
            freeFxn(memRecs, nRecs);
            status = IRES_EFAIL;
        }
        else {
            /*
             *  Increment the reference count on the buffer and set
             *  scratchId, mode
             */
            buffer.refCount++;
            buffer.scratchId = scratchId;
            buffer.mode = mode;
        }
    }

    /* TODO: release lock */

    *pStatus = status;

    GT_1trace(curTrace, GT_ENTER, "BUFRES getBuf> returning handle 0x%x\n",
            res);

    return ((IRES_Handle)res);
}

/*
 *  ======== freeBuf ========
 */
/* ARGSUSED */
static IRES_Status freeBuf(IALG_Handle alg, IRES_Handle res,
        IRES_ProtocolArgs *args, Int scratchId)
{
    IALG_MemRec   memRecs[MAXRECS];
    Int           nRecs;
    IRES_Status   retVal;
    IRES_Status status = IRES_OK;

    GT_assert(curTrace, res != NULL);

    /* Free the resource */
    /* Get the number of buffers to allocate for allocating the resource */
    nRecs = getNumRecs(args);

    if (nRecs > MAXRECS) {
        /* Error: Weren't expecting to allocate this many buffers */
        return (IRES_EFAIL);
    }

    /* Fill in memRecs[] with data needed to allocate the buffers */
    retVal = getMemRecs(res, args, memRecs);
    if (retVal != IRES_OK) {
        return (IRES_EFAIL);
    }

    /* De-initialize the IRES object */
    retVal = destructHandle(res);
    if (retVal != IRES_OK) {
        return (IRES_EFAIL);
    }

    /* Now free the memory */
    freeFxn(memRecs, nRecs);

    /* Decrement the reference count on the buffer */
    /* TODO: acquire lock */
    if (--buffer.refCount == 0) {
        buffer.scratchId = -1;
        buffer.mode = IRES_SCRATCH;
    }

    /* release lock */

    return (status);
}

/*
 *  ======== IRES RESOURCE PROTOCOL INTERFACE FUNCTIONS ========
 *  getStaticProps
 */

/*
 *  ======== getStaticProps ========
 */
/* ARGSUSED */
Void getStaticProps(IRES_Handle res, IRES_Properties *props)
{
    GT_assert(curTrace, res != NULL);
    GT_assert(curTrace, props != NULL);

    ((BUFRES_Props *)props)->base = buffer.base;
    ((BUFRES_Props *)props)->length = buffer.length;
}


/*
 *  ======== IRES RESOURCE REQUEST INTERFACE FUNCTIONS ========
 *  constructHandle, destructHandle, getMemRecs, getNumRecs
 */

/*
 *  ======== constructHandle ========
 */
/* ARGSUSED */
static IRES_Handle constructHandle(IRES_ProtocolArgs *args,
        IALG_MemRec *memRecs, IRESMAN_ConstructArgs *cArgs,
        IRES_Status *status)
{
    BUFRES_Handle   res;

    GT_assert(curTrace, args != NULL);
    GT_assert(curTrace, cArgs != NULL);
    GT_assert(curTrace, memRecs != NULL);
    GT_assert(curTrace, status != NULL);

    /*
     *  Piece the allocated buffers together to form the BUFRES_Obj.
     *  In this case, only one buffer has been allocated, so piecing
     *  together is unnecessary.
     */
    res = (BUFRES_Handle)(memRecs->base);
    res->ires.getStaticProperties = getStaticProps;
    res->ires.persistent = (args->mode == IRES_PERSISTENT) ? 1 : 0;

    res->base = ((BUFRES_ConstructArgs *)cArgs)->base;
    res->length = ((BUFRES_Args *)args)->length;

    *status = IRES_OK;
    return ((IRES_Handle)res);
}

/*
 *  ======== destructHandle ========
 */
/* ARGSUSED */
static IRES_Status destructHandle(IRES_Handle res)
{
    /*
     *  Do any de-initialization necessary on the BUFRES_Obj. In this case,
     *  nothing needs to be done.
     */
    return (IRES_OK);
}


/*
 *  ======== getMemRecs ========
 *  Fill in the memRecs table with the values needed to allocate a
 *  BUFRES_Obj.
 */
/* ARGSUSED */
static IRES_Status getMemRecs(IRES_Handle ires, IRES_ProtocolArgs *args,
        IALG_MemRec *memRecs)
{
    IRES_Status status = IRES_OK;

    if (ires == NULL) {
        /* Fill memRecs[] with data needed to allocate the object */
        memRecs[0].size = sizeof(BUFRES_Obj);
        memRecs[0].alignment = 0;
        memRecs[0].attrs = IALG_PERSIST;
        memRecs[0].space = IALG_EXTERNAL;
    }
    else {
        /*
         *  Fill memRec[] with data on buffers allocated to create the
         *  object. (In this case, only one buffer was allocated).
         */
        memRecs[0].base = (Void *)ires;
        memRecs[0].size = sizeof(BUFRES_Obj);
        memRecs[0].alignment = 0;
        memRecs[0].attrs = IALG_PERSIST;
        memRecs[0].space = IALG_EXTERNAL;
    }

    return (status);
}

/*
 *  ======== getNumRecs ========
 */
/* ARGSUSED */
static Int getNumRecs(IRES_ProtocolArgs *args)
{
    /* Only one buffer is needed to construct a BUFRES_Obj */
    return (NUMRECS);
}

/*
 *  ======== Internal Functions ========
 */

/*
 *  ======== bufAlloc ========
 */
/* ARGSUSED */
static Void *bufAlloc(Int id, Int size, Int align)
{
    Uint32     alignSize;
    Uint32     alignBytes;
    Uint32     remainBytes;
    Uint32     base;

    /* 'align' must be 0 or a power of 2, 0 means no alignment */
    alignBytes = (align == 0) ? 1 : align;
    base = (Uint32)buffer.base;

    if (base & (alignBytes - 1)) {
        /* The base of the buffer is not aligned on 'alignBytes' boundary */
        remainBytes = alignBytes - (base & (alignBytes - 1));
        alignSize = size + remainBytes;
        base = base + remainBytes;
    }
    else {
        /* buffer is already aligned */
        alignSize = size;
    }

    if (alignSize <= buffer.length) {
        return ((Void *)base);
    }
    else {
        return (NULL);
    }
}


BUFRES_Params IRESMAN_BUFRES_DEFAULTPARAM;

IRESMAN_Fxns * BUFRES_getIresmanFxns()
{
    return ((Void *)(&BUFRES_MGRFXNS));
}


IRESMAN_Params * BUFRES_getDefaultParams()
{
    IRESMAN_BUFRES_DEFAULTPARAM.iresConfig.size = sizeof(IRESMAN_Params);

    return ((IRESMAN_Params *)&IRESMAN_BUFRES_DEFAULTPARAM);
}
/*
 *  @(#) ti.sdo.fc.ires.bufres; 1, 0, 0,177; 12-1-2010 17:24:58; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

