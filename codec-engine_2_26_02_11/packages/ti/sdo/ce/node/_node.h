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
 *  ======== _node.h ========
 *  Private (internal) NODE module definitions.
 */
/**
 *  @file       ti/sdo/ce/node/_node.h
 *
 *  @brief      Private (internal) NODE module definitions
 */
/**
 *  @addtogroup ti_sdo_ce_NODE      CE NODE API
 */

#ifndef ti_sdo_ce_node__NODE_
#define ti_sdo_ce_node__NODE_

#include <ti/sdo/ce/osal/Thread.h>
#include <ti/sdo/ce/ipc/Comm.h>
#include <ti/sdo/ce/skel.h>

#include <ti/sdo/ce/node/node.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup    ti_sdo_ce_NODE */
/*@{*/

#include <ti/sdo/utils/trace/gt.h>

extern GT_Mask _NODE_curTrace;

typedef struct NODE_Obj * NODE_Handle;

/*
 *  ======== NODE_Fxns ========
 */
/**
 *  @brief      Table of functions defining the interface of a node.
 *
 *  @remarks    Typically, node's set NODE_Fxns.exec to NODE_EXECFXN.
 *
 *  @sa         NODE_EXECFXN()
 */
typedef struct NODE_Fxns {
    /**
     *  @brief  Signature of a node's create phase.
     *
     *  @param[in]      argLen  size of @c argBuf.
     *  @param[in]      argBuf  creation parameters.
     *  @param[in]      nodeName        The string name of the algorithm
     *                                  to create.
     *  @param[in]      node            A handle to the current node.
     *
     *  @remarks        A node's create phase is responsible for creating a
     *                  remote algorithm.
     *
     *  @remarks        Typically, a node's create phase
     *                  simply invokes the same application API called by
     *                  the application on the application processor.
     *
     *  @remarks        The handle returned by the application API's create
     *                  is typically stored in the node's environment using
     *                  NODE_setEnv().  It's then used in the delete() phase
     *                  to call the application API's delete function.
     *
     *  @sa             NODE_setEnv(), delete()
     */
    NODE_Status (*create)(Int argLen, Char *argBuf, String nodeName,
        NODE_Handle node);

    /**
     *  @brief  A node's execute phase.
     *
     *  @param[in]      node    A handle to the current node.
     *
     *  @remarks        Typically, this is set to NODE_EXECFXN().
     *
     *  @sa     NODE_EXECFXN()
     */
    NODE_Status (*exec)(NODE_Handle node);

    /**
     *  @brief  A node's execute phase.
     *
     *  @param[in]      node    A handle to the current node.
     *
     *  @remarks        Typically, this is set to NODE_EXECFXN().
     *
     *  @sa     NODE_EXECFXN()
     */
    NODE_Status (*destroy)(NODE_Handle node);
} NODE_Fxns;

/*
 *  ======== NODE_EXECFXN ========
 */
/**
 *  @brief      Default exec function.
 *
 *  @remarks    Using this default exec fxn requires NODE_Fxns.call to be
 *              implemented.
 *
 *  @sa         NODE_Fxns
 */
extern NODE_Status NODE_EXECFXN(NODE_Handle node);

extern NODE_Status NODE_CREATEFXN(Int argLen, Char *argBuf, String nodeName,
    NODE_Handle node);
extern NODE_Status NODE_DESTROYFXN(NODE_Handle node);

/** @cond INTERNAL */

typedef struct NODE_Attrs {
    Int initPriority;
    Int stackSize;
    Int stackSeg;
} NODE_Attrs;

typedef struct NODE_Desc {
    String          name;
    NODE_Uuid       uuid;
    SKEL_Fxns       *skelFxns;
    NODE_Attrs      *nodeAttrs;
    Int             rpcProtocolVersion;  /* format of RPC msg'ing */

    /*
     *  The following fields are only used for passing information about
     *  the server algs up to the Arm.
     */
    String          stubFxnsName;        /* Name of stub functions */
    String          typeTab;             /* TypeTab in ';' separated string */
} NODE_Desc;

/*
 *  ======== NODE_Stat ========
 */
typedef struct NODE_Stat {
    Int         stackSize;
    Int         stackUsed;
} NODE_Stat;

typedef struct NODE_Obj {
    Thread_Handle   self;
    Comm_Queue      send;           /* queue id for message reply comm queue */
    Comm_Queue      recv;           /* queue id for received msg comm queue */
    Comm_Handle     msgq;           /* handle for created recv queue */
    Ptr             moreEnv;        /* node-specific object handle */
    Int             initPriority;
    SKEL_Fxns       *skelFxns;      /* app skeleton fxns table */
    Int             status;         /* saved exec fxn exit status */
} NODE_Obj;

/* default attributes */
extern NODE_Attrs NODE_ATTRS;

/*
 *  ======== NODE_create ========
 *
 *  Create a NODE object using the supplied "create" function.
 *
 *  argLength: length of the argument string
 *  argString: argument string to be passed to create function
 *  attrs: NODE attributes
 *
 *  return: status (success or error code)
 *
 */
extern NODE_Status NODE_create(NODE_Desc *desc,
    Int argLength, String argString, Comm_Queue sendQueue, String name,
    NODE_Handle *node);

/*
 *  ======== NODE_delete ========
 *
 *  Delete a NODE object after its associated task has exited.
 *
 *  node: previously created node object
 *  deleteFxn: function to be called to delete resources from create
 *
 *  returns: status
 */
extern Int NODE_delete(NODE_Handle node);

/*
 *  ======== NODE_start ========
 *
 *  Start execution of a NODE's task by invoking the supplied execute function
 *  in the context of a separate thread.
 *
 *  node: previously create NODE object
 *  execFxn: execute function that constitutes NODE's thread body
 *
 */
extern NODE_Status NODE_start(NODE_Handle node);

/*
 *  ======== NODE_getRecvQueue ========
 *
 *  Retrieve the Comm handle for the queue to use for receiving messages.
 */
static inline Comm_Queue NODE_getRecvQueue(NODE_Handle node)
{
    return (node->recv);
}

/*
 *  ======== NODE_getSendQueue ========
 *
 *  Retrieve the Comm handle for the queue to use for sending messages.
 */
static inline Comm_Queue NODE_getSendQueue(NODE_Handle node)
{
    return (node->send);
}

/*
 *  ======== NODE_stat ========
 *  Get node's current status
 */
extern Int NODE_stat(NODE_Handle node, NODE_Stat *statBuf);

/** @endcond */

/*
 *  ======== NODE_getEnv ========
 */
/**
 *  @brief      Obtain a node's private environment.
 *
 *  @param[in]  node    Handle to a node.
 *
 *  @retval     The value of the node's environment.
 *
 *  @remarks    This service is used to obtain an environment previously set
 *              by NODE_setEnv().
 *
 *  @sa         NODE_setEnv()
 */
static inline Ptr NODE_getEnv(NODE_Handle node)
{
    return (node->moreEnv);
}

/*
 *  ======== NODE_setEnv ========
 */
/**
 *  @brief      Set a node's private environment.
 *
 *  @param[in]  node    Handle to a node.
 *  @param[in]  env     The value to set the node's environment to.
 *
 *  @sa         NODE_getEnv()
 */
static inline Void NODE_setEnv(NODE_Handle node, Ptr env)
{
    node->moreEnv = env;
}

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.node; 1, 0, 0,427; 12-2-2010 21:24:36; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

