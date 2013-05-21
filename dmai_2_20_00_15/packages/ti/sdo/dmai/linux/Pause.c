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

#include <xdc/std.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Pause.h>

#define MODULE_NAME     "Pause"

typedef struct Pause_Object {
    Int             pause;
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
} Pause_Object;

const Pause_Attrs Pause_Attrs_DEFAULT = {
    0
};

/******************************************************************************
 * Pause_create
 ******************************************************************************/
Pause_Handle Pause_create(Pause_Attrs *attrs)
{
    Pause_Handle hPause;

    hPause = calloc(1, sizeof(Pause_Object));

    if (hPause == NULL) {
        Dmai_err0("Failed to allocate space for Pause Object\n");
        return NULL;
    }

    pthread_mutex_init(&hPause->mutex, NULL);
    pthread_cond_init(&hPause->cond, NULL);

    hPause->pause = 0;

    return hPause;
}

/******************************************************************************
 * Pause_delete
 ******************************************************************************/
Int Pause_delete(Pause_Handle hPause)
{
    if (hPause) {
        pthread_mutex_destroy(&hPause->mutex);
        pthread_cond_destroy(&hPause->cond);
        free(hPause);
    }

    return Dmai_EOK;
}

/******************************************************************************
 * Pause_test
 ******************************************************************************/
Void Pause_test(Pause_Handle hPause)
{
    assert(hPause);

    pthread_mutex_lock(&hPause->mutex);
    if (hPause->pause == 1) {
        pthread_cond_wait(&hPause->cond, &hPause->mutex);
    }
    pthread_mutex_unlock(&hPause->mutex);
}

/******************************************************************************
 * Pause_on
 ******************************************************************************/
Void Pause_on(Pause_Handle hPause)
{
    assert(hPause);

    pthread_mutex_lock(&hPause->mutex);
    hPause->pause = 1;
    pthread_mutex_unlock(&hPause->mutex);
}

/******************************************************************************
 * Pause_off
 ******************************************************************************/
Void Pause_off(Pause_Handle hPause)
{
    assert(hPause);

    pthread_mutex_lock(&hPause->mutex);
    if (hPause->pause == 1) {
        hPause->pause = 0;
        pthread_cond_broadcast(&hPause->cond);
    }
    pthread_mutex_unlock(&hPause->mutex);
}
