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
 *  ======== Queue_posix.c ========
 */
#include <xdc/std.h>
#include <ti/sdo/ce/osal/Queue.h>

#include <pthread.h>

Queue_Attrs Queue_ATTRS;

static pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

/*
 *  ======== Queue_exit ========
 */
Void Queue_exit(Void)
{
}

/*
 *  ======== Queue_get ========
 */
Ptr Queue_get(Queue_Handle queue)
{
    Ptr elem;

    pthread_mutex_lock(&mut);   /* atomic begin */

    elem = Queue_dequeue(queue);

    pthread_mutex_unlock(&mut); /* atomic end */

    return (elem);
}

/*
 *  ======== Queue_init ========
 */
Bool Queue_init(Void)
{
    return (TRUE);
}

/*
 *  ======== Queue_put ========
 */
Void Queue_put(Queue_Handle queue, Ptr elem)
{
    pthread_mutex_lock(&mut);   /* atomic begin */

    Queue_enqueue(queue, elem);

    pthread_mutex_unlock(&mut); /* atomic end */
}

/*
 *  ======== Queue_extract ========
 */
Void Queue_extract(Queue_Elem *elem)
{
    pthread_mutex_lock(&mut);   /* atomic begin */

    Queue_remove(elem);

    pthread_mutex_unlock(&mut); /* atomic end */
}

/*
 *  @(#) ti.sdo.ce.osal.linux; 2, 0, 1,181; 12-2-2010 21:24:46; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

