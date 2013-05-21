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

#include <xdc/std.h>
#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Sound.h>

#define MODULE_NAME     "Sound"

const Sound_Attrs Sound_Attrs_STEREO_DEFAULT = {
    44100,
    2,
    127,
    127,
    Sound_Mode_FULLDUPLEX,
    Sound_Input_MIC,
    Sound_Std_ALSA,
    2048,
};

const Sound_Attrs Sound_Attrs_MONO_DEFAULT = {
    8000,
    1,
    127,
    127,
    Sound_Mode_FULLDUPLEX,
    Sound_Input_MIC,
    Sound_Std_ALSA,
    2048,
};

typedef struct Sound_Object {
    Sound_Std         soundStd;
} Sound_Object;

/* OSS API prototypes */
extern Sound_Handle Sound_oss_create(Sound_Attrs *attrs);
extern Int Sound_oss_delete(Sound_Handle hSound);
extern Int Sound_oss_read(Sound_Handle hSound, Buffer_Handle hBuf);
extern Int Sound_oss_write(Sound_Handle hSound, Buffer_Handle hBuf);

/* ALSA API prototypes */
extern Sound_Handle Sound_alsa_create(Sound_Attrs *attrs);
extern Int Sound_alsa_delete(Sound_Handle hSound);
extern Int Sound_alsa_read(Sound_Handle hSound, Buffer_Handle hBuf);
extern Int Sound_alsa_write(Sound_Handle hSound, Buffer_Handle hBuf);

/* Function tables for run time lookup */
static Sound_Handle (*createFxns[Sound_Std_COUNT])(Sound_Attrs *attrs) = {
    Sound_oss_create,
    Sound_alsa_create,
};

static Int (*deleteFxns[Sound_Std_COUNT])(Sound_Handle hSound) = {
    Sound_oss_delete,
    Sound_alsa_delete,
};

static Int (*readFxns[Sound_Std_COUNT])(Sound_Handle hSound,
                                        Buffer_Handle hBuf) = {
    Sound_oss_read,
    Sound_alsa_read,
};

static Int (*writeFxns[Sound_Std_COUNT])(Sound_Handle hSound,
                                         Buffer_Handle hBuf) = {
    Sound_oss_write,
    Sound_alsa_write,
};


/******************************************************************************
 * Sound_create
 ******************************************************************************/
Sound_Handle Sound_create(Sound_Attrs *attrs)
{
    return createFxns[attrs->soundStd](attrs);
}

/******************************************************************************
 * Sound_delete
 ******************************************************************************/
Int Sound_delete(Sound_Handle hSound)
{
    return deleteFxns[hSound->soundStd](hSound);
}

/******************************************************************************
 * Sound_read
 ******************************************************************************/
Int Sound_read(Sound_Handle hSound, Buffer_Handle hBuf)
{
    return readFxns[hSound->soundStd](hSound, hBuf);
}

/******************************************************************************
 * Sound_write
 ******************************************************************************/
Int Sound_write(Sound_Handle hSound, Buffer_Handle hBuf)
{
    return writeFxns[hSound->soundStd](hSound, hBuf);
}
