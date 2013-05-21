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
 *  ======== user2_pool_mqt_cfg.c ========
 *
 *  This file contains the POOL and MQT attribute definitions for the "known"
 *  default Link configuration of Codec Engine, for LAD.
 *
 */

#include <dsplink.h>

#include <pool.h>
#include <msgq.h>

/*
 *  ======== Comm_MSGSIZE ========
 *  Maximum size of communication buffers
 */
#define Comm_MSGSIZE (4 * 1024)

/** ===========================================================================
 *  @const  NUMMSGPOOLS
 *
 *  @desc   Number of BUF pools in the pool
 *  ===========================================================================
 */
#define NUMMSGPOOLS     2

/** ===========================================================================
 *  @const  NUMMSGINPOOL0
 *
 *  @desc   Number in first message pool.
 *  ===========================================================================
 */
#define NUMMSGINPOOL0   64

/** ===========================================================================
 *  @const  NUMMSGINPOOL1
 *
 *  @desc   Number in second message pool.
 *  ===========================================================================
 */
#define NUMMSGINPOOL1   16

/** ===========================================================================
 *  @name   commBufSizes
 *
 *  @desc   Message sizes managed by the pool.
 *  ===========================================================================
 */
static Uint32 commBufSizes[NUMMSGPOOLS] =
{
    Comm_MSGSIZE,
    ZCPYMQT_CTRLMSG_SIZE,
};

/** ===========================================================================
 *  @name   commNumBuffers
 *
 *  @desc   Number of messages in each pool managed by the pool.
 *  ===========================================================================
 */
static Uint32 commNumBuffers[NUMMSGPOOLS] =
{
    NUMMSGINPOOL0,
    NUMMSGINPOOL1,
};

/** ===========================================================================
 *  @name   Global_cePoolAttrs
 *
 *  @desc   Definition of attributes for the pool based on physical link used
 *          by the MQT.
 *  ===========================================================================
 */
SmaPoolAttrs user2_PoolAttrs =
{
    NUMMSGPOOLS,        /* number of buffer sizes */
    commBufSizes,       /* array of buffer sizes in this pool */
    commNumBuffers,     /* array of number of buffers of each size */
    TRUE                /* exact match required */
};

ZCPYMQT_Attrs user2_MqtAttrs; 

/*
 *  @(#) ti.dsplink.utils.lad; 2, 0, 0,228; 12-2-2010 21:18:43; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

