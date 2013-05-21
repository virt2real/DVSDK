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
 *  ======== Queue.h ========
 */

#ifndef ti_sdo_ce_osal_Queue_
#define ti_sdo_ce_osal_Queue_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * QUEUEs
 * ======
 *
 *      Queues are doubly linked with dummy node to eliminate special
 *      cases for speed.
 *          _______        _______        _______      _______
 *  ,----->|_______|----->|_______|----->|_______|--->|_______|--//---,
 *  | ,----|_______|<-----|_______|<-----|_______|<---|_______|<-//-, |
 *  | |    prev           queue          elem         next          | |
 *  | |_____________________________________________________________| |
 *  |_________________________________________________________________|
 *
 */

typedef struct Queue_Elem {
    struct Queue_Elem *next;
    struct Queue_Elem *prev;
} Queue_Elem, *Queue_Handle;

typedef struct Queue_Elem Queue_Obj;

typedef struct Queue_Attrs {
    Int dummy;
} Queue_Attrs;

extern Queue_Attrs Queue_ATTRS;

/*
 *  ======== Queue_dequeue ========
 *
 *  get elem from front of "queue".
 *  This operation is *NOT* atomic.  External synchronization must
 *  be used to protect this queue from simultaneous access by interrupts
 *  or other tasks.
 *
 *               _______        _______        _______      _______
 *  Before:     |_______|----->|_______|----->|_______|--->|_______|--->
 *              |_______|<-----|_______|<-----|_______|<---|_______|<---
 *               prev           queue          elem         next
 *
 *
 *               _______        _______        _______
 *  After:      |_______|----->|___*___|----->|_______|--->
 *              |_______|<-----|_______|<-----|___*___|<---
 *               prev           queue          next
 *               _______
 *      elem -->|___x___|       * = modified
 *              |___x___|       x = undefined
 *
 */
static inline Ptr Queue_dequeue(Queue_Handle queue)
{
    Queue_Elem *elem = queue->next;
    Queue_Elem *next = elem->next;

    queue->next = next;
    next->prev = queue;

    return (elem);
}

/*
 *  ======== Queue_empty ========
 */
#define Queue_empty(queue)        ((queue)->next == (queue))

/*
 *  ======== Queue_enqueue ========
 *
 *  put "elem" at end of "queue".
 *  This operation is *NOT* atomic.  External synchronization must
 *  be used to protect this queue from simultaneous access by interrupts
 *  or other tasks.
 *
 *               _______        _______        _______
 *  Before:     |_______|----->|_______|----->|_______|--->
 *              |_______|<-----|_______|<-----|_______|<---
 *               prev           queue          next
 *               _______
 *      elem -->|___x___|       * = modified
 *              |___x___|       x = undefined
 *
 *               _______        _______        _______      _______
 *  After:      |___*___|----->|___*___|----->|_______|--->|_______|--->
 *              |_______|<-----|___*___|<-----|___*___|<---|_______|<---
 *               prev           elem          queue         next
 *
 */
static inline Void Queue_enqueue(Queue_Handle queue, Ptr elem)
{
    Queue_Elem *prev = queue->prev;

    ((Queue_Elem *)elem)->next = queue;
    ((Queue_Elem *)elem)->prev = prev;
    prev->next = (Queue_Elem *)elem;
    queue->prev = (Queue_Elem *)elem;
}

/*
 *  ======== Queue_extract ========
 *  Atomically remove elem from a queue.  If elem has already been removed
 *  or if it was never in a queue this operation is a nop.
 */
extern Void Queue_extract(Queue_Elem *elem);

/*
 *  ======== Queue_get ========
 *  atomically remove the first element in the queue.
 */
extern Ptr Queue_get(Queue_Handle queue);


/**
 * @brief       Initialize the Queue module.
 */
extern Bool Queue_init(Void);

/**
 * @brief       Finalize the Queue module.
 */
extern Void Queue_exit(Void);

/*
 *  ======== Queue_head ========
 *  return a reference to the head of the queue
 */
#define Queue_head(queue)         ((Ptr)((queue)->next))

/*
 *  ======== Queue_insert ========
 */
#define Queue_insert(qElem, elem) Queue_enqueue((Queue_Handle)qElem, elem)

/*
 *  ======== Queue_new ========
 *  Initialize a queue or an elem
 */
#define Queue_new(elem)           (elem)->next = (elem)->prev = (elem)

/*
 *  ======== Queue_next ========
 */
#define Queue_next(elem)          ((Ptr)((Queue_Elem *)(elem))->next)

/*
 *  ======== Queue_prev ========
 */
#define Queue_prev(elem)          ((Ptr)((Queue_Elem *)(elem))->prev)

/*
 *  ======== Queue_put ========
 *  Disable interrupts and put "elem" at end of "queue".
 */
extern Void Queue_put(Queue_Handle queue, Ptr elem);

/*
 *  ======== Queue_remove ========
 *  Remove elem from a queue.  If elem has already been removed
 *  or if it was never in a queue this operation is a nop.
 */
#define Queue_remove(elem) {\
    ((Queue_Elem *)elem)->prev->next = ((Queue_Elem *)elem)->next;  \
    ((Queue_Elem *)elem)->next->prev = ((Queue_Elem *)elem)->prev;  \
    }

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif
/*
 *  @(#) ti.sdo.ce.osal; 2, 0, 2,427; 12-2-2010 21:24:38; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

