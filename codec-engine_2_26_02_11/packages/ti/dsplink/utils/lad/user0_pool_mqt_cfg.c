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
 *  ======== user0_pool_mqt_cfg.c ========
 *
 *  This file contains the POOL and MQT attribute definitions for the "known"
 *  Link configuration of the Link sample apps, for LAD.
 *
 */

#include <dsplink.h>

#include <pool.h>
#include <proc.h>
#include <msgq.h>

#define NUMMSGPOOLS     4

#define NUMMSGINPOOL0   1
#define NUMMSGINPOOL1   2
#define NUMMSGINPOOL2   2
#define NUMMSGINPOOL3   4

#define APP_BUFFER_SIZE  DSPLINK_ALIGN (sizeof (MSGQ_MsgHeader),       \
                                        DSPLINK_BUF_ALIGN)
#if defined ZCPY_LINK
#define SAMPLEMQT_CTRLMSG_SIZE  ZCPYMQT_CTRLMSG_SIZE
ZCPYMQT_Attrs  user0_MqtAttrs;

#else /* if defined ZCPYMQT_LINK */
#if defined (PCPY_LINK)

#define SAMPLEMQT_CTRLMSG_SIZE  PCPYMQT_CTRLMSG_SIZE
PCPYMQT_Attrs  user0_MqtAttrs ;
#endif /* if defined (PCPY_LINK) */
#endif /* if defined ZCPY_LINK */

STATIC Uint32 SampleBufSizes [NUMMSGPOOLS] =
{
    APP_BUFFER_SIZE,
    SAMPLEMQT_CTRLMSG_SIZE,
    DSPLINK_ALIGN (sizeof (MSGQ_AsyncLocateMsg), DSPLINK_BUF_ALIGN),
    DSPLINK_ALIGN (sizeof (MSGQ_AsyncErrorMsg), DSPLINK_BUF_ALIGN)
} ;

STATIC Uint32 SampleNumBuffers [NUMMSGPOOLS] =
{
    NUMMSGINPOOL0,
    NUMMSGINPOOL1,
    NUMMSGINPOOL2,
    NUMMSGINPOOL3
} ;

#if defined ZCPY_LINK
SMAPOOL_Attrs user0_PoolAttrs =
{
    NUMMSGPOOLS,
    SampleBufSizes,
    SampleNumBuffers,
    TRUE
} ;
#else /* if defined ZCPYMQT_LINK */
#if defined (PCPY_LINK)
BUFPOOL_Attrs user0_PoolAttrs =
{
    NUMMSGPOOLS,
    SampleBufSizes,
    SampleNumBuffers
} ;
#endif /* if defined (PCPY_LINK) */
#endif /* if defined ZCPY_LINK */

/*
 *  @(#) ti.dsplink.utils.lad; 2, 0, 0,228; 12-2-2010 21:18:41; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

