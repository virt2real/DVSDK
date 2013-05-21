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
 *  ======== Comm_posix.c ========
 */

#include <xdc/std.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/ce/ipc/Comm.h>

#include <ti/sdo/utils/trace/gt.h>

#define MSGSIZE     0x1000  /* maximum message size */
#define MSGTYPE     43      /* must be > 0 */
#define MAXRETRY    10      /* number of times to try to locate a queue */

typedef struct Comm_Obj {
    Int             id;
    Comm_QType      type;
    Ptr             callHandle;
    Comm_CallFxn    callFxn;
} Comm_Obj;

/*
 *  ======== Comm_ATTRS ========
 *  Default creation attrs
 */
Comm_Attrs Comm_ATTRS = {
    Comm_PEND
};

static Int nameToId(String name);
static String userName = "";

static Int curInit = 0;                 /* module init counter */
static GT_Mask curTrace = {NULL,NULL};

/*
 *  ======== Comm_alloc ========
 */
Int Comm_alloc(UInt16 poolId, Comm_Msg *msg, UInt16 size)
{
    Comm_Msg   mbuf;
    Int        retVal = Comm_EFAIL;    /* pessimistic */

    GT_assert(curTrace, curInit > 0);
    GT_assert(curTrace, msg != NULL);

    GT_3trace(curTrace, GT_ENTER, "Comm_alloc> "
        "Enter(poolId=0x%x, msg=0x%x, size=%d)\n", poolId, msg, size);

    /*
     * Ensure size < MSGSIZE and alloc larger MSGSIZE.  While not intuitive,
     * this enables XDM's "extended structs"
     */
    if (size > MSGSIZE) {
        GT_2trace(curTrace, GT_7CLASS, "Comm_alloc> requested msg size is "
                "larger than MSGSIZE (0x%x > 0x%x)\n", size, MSGSIZE);
        return (Comm_EFAIL);
    }

    if ((mbuf = (Comm_Msg)Memory_alloc(MSGSIZE, NULL)) != NULL) {
        mbuf->size = MSGSIZE;
        *((long *)mbuf) = MSGTYPE; /* must be > 0 */
        *msg = mbuf;
        retVal = Comm_EOK;
    }

    GT_2trace(curTrace, GT_ENTER, "Comm_alloc> msg=0x%x, returning (%d)\n",
        *msg, retVal);

    return (retVal);
}

/*
 *  ======== Comm_create ========
 */
Comm_Handle Comm_create(String queueName, Comm_Queue *queue,
    Comm_Attrs *attrs)
{
    Comm_Obj *comm;
    key_t key = nameToId(queueName);

    GT_assert(curTrace, curInit > 0);

    GT_3trace(curTrace, GT_ENTER, "Comm_create> "
        "Enter(queueName='%s', queue=0x%x, attrs=0x%x)\n",
        queueName, queue, attrs);

    if (attrs == NULL) {
        attrs = &Comm_ATTRS;
    }

    comm = (Comm_Obj *)Memory_alloc(sizeof(Comm_Obj), NULL);
    if (comm == NULL) {
        return (NULL);
    }

    comm->type = attrs->type;

    if (comm->type == Comm_PEND) {
        ;
    }
    else if (comm->type == Comm_CALL) {
        comm->callHandle = attrs->callHandle;
        comm->callFxn    = attrs->callFxn;
    }
    else {
        GT_assert(curTrace, FALSE);  /* unknown Comm type */
    }

    /*
     * Create a new message queue id for the "name" key
     */
    if ((comm->id = msgget(key, IPC_CREAT | 0644)) < 0) {
        fprintf(stderr, "msgget key = 0x%x\n", key);
        perror("Comm_create:msgget");
        Memory_free(comm, sizeof(Comm_Obj), NULL);
        return (NULL);
    }

    *queue = comm->id;

    GT_1trace(curTrace, GT_ENTER, "Comm_create> return (0x%x)\n", comm);

    return (comm);
}

/*
 *  ======== Comm_delete ========
 */
Void Comm_delete(Comm_Handle comm)
{
    GT_assert(curTrace, curInit > 0);

    GT_1trace(curTrace, GT_ENTER, "Comm_delete> "
        "Enter (comm=0x%x)\n", comm);

    if (comm != NULL) {
        if (comm->id >= 0) {
            msgctl(comm->id, IPC_RMID, NULL);
        }
        Memory_free(comm, sizeof(Comm_Obj), NULL);
    }

    GT_1trace(curTrace, GT_ENTER, "Comm_delete> return\n", comm);
}


/*
 *  ======== Comm_exit ========
 */
Void Comm_exit(Void)
{
    GT_assert(curTrace, curInit > 0);

    if (--curInit == 0) {
        Memory_exit();
    }
}


/*
 *  ======== Comm_free ========
 */
Int Comm_free(Comm_Msg msg)
{
    GT_assert(curTrace, curInit > 0);

    GT_1trace(curTrace, GT_ENTER, "Comm_free> Enter (msg=0x%x)\n", msg);

    Memory_free(msg, msg->size, NULL);

    return (Comm_EOK);
}


/*
 *  ======== Comm_get ========
 */
Int Comm_get(Comm_Queue queue, Comm_Msg *msg, UInt timeout)
{
    Comm_Msg tmp;
    Int len;

    GT_assert(curTrace, curInit > 0);

    GT_3trace(curTrace, GT_ENTER, "Comm_get> "
        "Enter(queue=0x%x, msg=0x%x, timeout=%d)\n", queue, msg, timeout);

    *msg = NULL;

    if (Comm_alloc(0, &tmp, MSGSIZE) == Comm_EOK) {
        do {
            len = msgrcv(queue, tmp, MSGSIZE - sizeof(long), MSGTYPE, 0);
            if (len >= 0) {
                tmp->size = MSGSIZE;
                *msg = tmp;
                return (Comm_EOK);
            }
        } while (errno == EINTR);

        perror("Comm_get");
        Comm_free(tmp);
    }

    return (Comm_EFAIL);
}

/*
 *  ======== Comm_getMsgSize ========
 */
Int Comm_getMsgSize(Comm_Msg msg)
{
    GT_assert(curTrace, curInit > 0);

    return (msg->size);
}

/*
 *  ======== Comm_getSrcQueue ========
 */
Int Comm_getSrcQueue(Comm_Msg msg, Comm_Queue *commQueue)
{
    GT_assert(curTrace, curInit > 0);

    *commQueue = msg->reserved4;     /* was: srcId */
    return (Comm_EOK);
}


/*
 *  ======== Comm_init ========
 */
Bool Comm_init(Void)
{
    if (curInit++ == 0) {

        GT_create(&curTrace, Comm_GTNAME);

        Memory_init();

        /* TODO:M not process safe (right?) */
        userName = getenv("LOGNAME");
        if (userName == NULL) {
            userName = "";
        }
    }

    return (TRUE);
}


/*
 *  ======== Comm_locate ========
 */
Int Comm_locate(String queueName, Comm_Queue *queue)
{
    key_t key = nameToId(queueName);
    Int qid;
    Int i;

    GT_assert(curTrace, curInit > 0);

    GT_2trace(curTrace, GT_ENTER, "Comm_locate> "
        "Enter(queueName='%s', queue=0x%x)\n", queueName, queue);

    for (i = 0; (qid = msgget(key, 0644)) < 0; i++) {
        if (i >= MAXRETRY) {
            perror("Comm_locate:msgget");
            return (Comm_EFAIL);
        }
        sleep(1);
    }

    *queue = qid;

    return (Comm_EOK);
}


/*
 *  ======== Comm_put ========
 */
Int Comm_put(Comm_Queue queue, Comm_Msg msg)
{
    GT_assert(curTrace, curInit > 0);

    GT_2trace(curTrace, GT_ENTER, "Comm_put> "
        "Enter(queue=0x%x, msg=0x%x)\n", queue, msg);

    if (msgsnd(queue, msg, msg->size - sizeof(long), IPC_NOWAIT) < 0) {
        perror("Comm_put");
        return (Comm_EFAIL);
    }

    Comm_free(msg);
    return (Comm_EOK);
}


/*
 *  ======== Comm_release ========
 */
Int Comm_release(Comm_Queue queue)
{
    GT_assert(curTrace, curInit > 0);

    GT_1trace(curTrace, GT_ENTER, "Comm_release> Enter(queue=0x%x)\n", queue);

    return (Comm_EOK);
}


/*
 *  ======== Comm_setSrcQueue ========
 */
Void Comm_setSrcQueue(Comm_Msg msg, Comm_Queue queue)
{
    GT_assert(curTrace, curInit > 0);

    msg->reserved4 = queue;
}

/*
 *  ======== nameToId ========
 *  This function must map name to an id, such that:
 *      1. the same name always results in the same id, and
 *      2. different names must result in different ids.
 */
static Int nameToId(String name)
{
    Int sum = 0;
    Int id = 0;
    Char *cp;

    GT_1trace(curTrace, GT_ENTER, "nameToId> Enter(name=%s)\n", name);

    if ((cp = strchr(name, '#')) != NULL) {
        id = atoi(cp + 1) << 16;
    }

    for (cp = name; *cp != '\0'; cp++) {
        sum += (Int)*cp;
    }
    id = (name - cp) + id;

    /* add user name to allow multiple developers to run tests concurrently */
    for (cp = userName; *cp != '\0'; cp++) {
        sum += (Int)*cp;
    }
    id = (sum << 6) + (userName - cp) + id;

    GT_1trace(curTrace, GT_ENTER, "nameToId> Exit(id=0x%x)\n", id);

    return (id);
}
/*
 *  @(#) ti.sdo.ce.ipc.linux; 2, 0, 1,179; 12-2-2010 21:24:22; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

