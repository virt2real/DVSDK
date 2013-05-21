/* --COPYRIGHT--,BSD
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
 * --/COPYRIGHT--*/

#include <stdlib.h>
#include <pthread.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Rendezvous.h>

#define MODULE_NAME     "Rendezvous"

typedef struct Rendezvous_Object {
    Int             orig;
    Int             count;
    Int             force;
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
} Rendezvous_Object;

const Rendezvous_Attrs Rendezvous_Attrs_DEFAULT = {
    0
};

/******************************************************************************
 * Rendezvous_create
 ******************************************************************************/
Rendezvous_Handle Rendezvous_create(Int count, Rendezvous_Attrs *attrs)
{
    Rendezvous_Handle hRv;

    if (attrs == NULL) {
        Dmai_err0("NULL attrs not supported\n");
        return NULL;
    }

    if ((count < 0) && (count != Rendezvous_INFINITE)) {
        Dmai_err1("Count (%d) must be > 0\n", count);
        return NULL;
    }

    hRv = calloc(1, sizeof(Rendezvous_Object));

    if (hRv == NULL) {
        Dmai_err0("Failed to allocate space for Rendezvous Object\n");
        return NULL;
    }

    pthread_mutex_init(&hRv->mutex, NULL);
    pthread_cond_init(&hRv->cond, NULL);

    hRv->count = count;
    hRv->orig = count;

    return hRv;
}

/******************************************************************************
 * Rendezvous_delete
 ******************************************************************************/
Int Rendezvous_delete(Rendezvous_Handle hRv)
{
    if (hRv) {
        pthread_mutex_destroy(&hRv->mutex);
        pthread_cond_destroy(&hRv->cond);
        free(hRv);
    }

    return Dmai_EOK;
}

/******************************************************************************
 * Rendezvous_meet
 ******************************************************************************/
Void Rendezvous_meet(Rendezvous_Handle hRv)
{
    assert(hRv);

    pthread_mutex_lock(&hRv->mutex);
    if (!hRv->force) {
        if (hRv->count > 0) {
            hRv->count--;
        }
        if ((hRv->count > 0) || (hRv->count == Rendezvous_INFINITE)) {
            pthread_cond_wait(&hRv->cond, &hRv->mutex);
        } 
        else {
            pthread_cond_broadcast(&hRv->cond);
            hRv->count = hRv->orig;
        }
    }
    pthread_mutex_unlock(&hRv->mutex);
}

/******************************************************************************
 * Rendezvous_force
 ******************************************************************************/
Void Rendezvous_force(Rendezvous_Handle hRv)
{
    assert(hRv);

    pthread_mutex_lock(&hRv->mutex);
    hRv->force = TRUE;
    pthread_cond_broadcast(&hRv->cond);
    pthread_mutex_unlock(&hRv->mutex);
}

/******************************************************************************
 * Rendezvous_reset
 ******************************************************************************/
Void Rendezvous_reset(Rendezvous_Handle hRv)
{
    assert(hRv);

    pthread_mutex_lock(&hRv->mutex);
    hRv->count = hRv->orig;
    hRv->force = FALSE;
    pthread_mutex_unlock(&hRv->mutex);
}

/******************************************************************************
 * Rendezvous_forceAndReset
 ******************************************************************************/
Void Rendezvous_forceAndReset(Rendezvous_Handle hRv)
{
    assert(hRv);

    pthread_mutex_lock(&hRv->mutex);
    pthread_cond_broadcast(&hRv->cond);
    hRv->count = hRv->orig;
    hRv->force = FALSE;
    pthread_mutex_unlock(&hRv->mutex);
}

