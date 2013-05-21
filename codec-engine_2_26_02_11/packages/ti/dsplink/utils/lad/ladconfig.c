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
 *  ======== ladconfig.c ========
 */

#include <xdc/std.h>

#include <stdio.h>
#include <string.h>

#include <ti/dsplink/utils/ladclient/ladclient.h>
#include "_lad.h"

#include <ti/sdo/ce/ipc/dsplink/_adapted_link_gpptypes.h>
#include <dsplink.h>

#include <proc.h>
#include <pool.h>
#include <msgq.h>
#include <pooldefs.h>

#define NUMPOOLSINCONFIG0               1
#define NUMPOOLSINCONFIG1               1
#define NUMPOOLSINCONFIG2               1
#define NUMPOOLSINCONFIGMESSAGE         1
#define NUMPOOLSINCONFIGNULL            1

/* known Link configurations */
extern LINKCFG_Object  user0_LINKCFG_Config;            /* config #0 */
extern LINKCFG_Object  user1_LINKCFG_Config;            /* config #1 */
extern LINKCFG_Object  user2_LINKCFG_Config;            /* config #2 */
extern LINKCFG_Object  message_LINKCFG_Config;          /* config #3 */

/* known POOL attr definitions */
extern SMAPOOL_Attrs user0_PoolAttrs;                   /* config #0 */
extern SMAPOOL_Attrs user1_PoolAttrs;                   /* config #1 */
extern SMAPOOL_Attrs user2_PoolAttrs;                   /* config #2 */
extern SMAPOOL_Attrs message_PoolAttrs;                 /* config #3 */

/* known MSGQ attr definitions */
extern ZCPYMQT_Attrs user0_MqtAttrs;                    /* config #0 */
extern ZCPYMQT_Attrs user1_MqtAttrs;                    /* config #1 */
extern ZCPYMQT_Attrs user2_MqtAttrs;                    /* config #2 */
extern ZCPYMQT_Attrs message_MqtAttrs;                  /* config #3 */

LINKCFG_Object * linkConfig [LAD_MAXNUMLINKCONFIGS] = {
    &user0_LINKCFG_Config,
    &user1_LINKCFG_Config,
    &user2_LINKCFG_Config,
    &message_LINKCFG_Config,
    NULL 
};

Void * mqtAttrs [LAD_MAXNUMLINKCONFIGS] = {
    &user0_MqtAttrs,
    &user1_MqtAttrs,
    &user2_MqtAttrs,
    &message_MqtAttrs,
    NULL 
};

static String configName [LAD_MAXNUMLINKCONFIGS] = {
    "user0",
    "user1",
    "user2",
    "message",
    "null"
};

static Int numPools[LAD_MAXNUMLINKCONFIGS] = { 
    NUMPOOLSINCONFIG0, 
    NUMPOOLSINCONFIG1,
    NUMPOOLSINCONFIG2, 
    NUMPOOLSINCONFIGMESSAGE, 
    NUMPOOLSINCONFIGNULL 
};

static Void * poolAttrsConfig0[NUMPOOLSINCONFIG0] = { &user0_PoolAttrs };
static Void * poolAttrsConfig1[NUMPOOLSINCONFIG1] = { &user1_PoolAttrs };
static Void * poolAttrsConfig2[NUMPOOLSINCONFIG2] = { &user2_PoolAttrs };
static Void * poolAttrsConfigMessage[NUMPOOLSINCONFIGMESSAGE] = { &message_PoolAttrs };
static Void * poolAttrsConfigNull[NUMPOOLSINCONFIGNULL] = { NULL };


/*
 *  ======== _LAD_getConfigId ========
 *  This function is called to map an Link configuration name to a numeric
 *  index.
 */
Bool _LAD_getConfigId(String name, Uns * index)
{
    Bool found = FALSE;
    Int i;

    for (i = 0; i < LAD_MAXNUMLINKCONFIGS; i++) {
        if (strcmp(name, configName[i]) == 0) {
            *index = i;
            found = TRUE;
            break;
        }
    }
   
    return(found);
}


/*
 *  ======== _LAD_getConfigName ========
 *  This function is called to map an Link config numeric index to the 
 *  corresponding configuration name.
 */
String _LAD_getConfigName(Uns index)
{
   return(configName[index]);
}


/*
 *  ======== _LAD_initConfig ========
 *  This function is called once during LAD initialization.  Its purpose is
 *  to enable some tweaking to static configuration objects.  Ideally these
 *  objects would be fully static, but there may be cases where it is required
 *  or easier to do at runtime.
 */
Void _LAD_initConfig(Void)
{

    /* for config #0 ... */
    user0_MqtAttrs.poolId = 0;

    /* for config #1 ... */
    user1_MqtAttrs.poolId = 0;

    /* for config #2 ... */
    user2_MqtAttrs.poolId = 0;

    /* for config #3 ... */
    message_MqtAttrs.poolId = 0;

    /* for config #4 ... */
}


/*
 *  ======== _LAD_openAllPools ========
 */
DSP_STATUS _LAD_openAllPools(Int linkConfigId)
{
    Void * * poolAttrs;
    DSP_STATUS status = DSP_EFAIL;
    Int i;

    /* get pool attributes table for this linkConfigId */
    switch (linkConfigId) {
        case 0:
            poolAttrs = poolAttrsConfig0;
            break;

        case 1:
            poolAttrs = poolAttrsConfig1;
            break;

        case 2:
            poolAttrs = poolAttrsConfig2;
            break;

        case 3:
            poolAttrs = poolAttrsConfigMessage;
            break;

        case 4:
            poolAttrs = poolAttrsConfigNull;
            break;

        default:
            poolAttrs = NULL;
            break;
    }

    if (poolAttrs != NULL) {

        /* call POOL_Open for all pools in this configuration */
        for (i = 0; i < numPools[linkConfigId]; i++) {
            status = POOL_Open(i, poolAttrs[i]);
            if (status != DSP_SOK) {
                break;
            }
        }
    }

    return(status); 
}


/*
 *  ======== _LAD_closeAllPools ========
 */
DSP_STATUS _LAD_closeAllPools(Int linkConfigId)
{
    DSP_STATUS status = DSP_EFAIL;
    Int i;

    /* call POOL_Close for all pools in this configuration */
    for (i = 0; i < numPools[linkConfigId]; i++) {
        status = POOL_Close(i);
        if (!DSP_SUCCEEDED(status)) {
            break;
        }
    }

    return (status); 
}
/*
 *  @(#) ti.dsplink.utils.lad; 2, 0, 0,228; 12-2-2010 21:18:40; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

