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
 *  ======== rman_config.c ========
 *  Creates an RMAN_PARAMS structure to be used by non-RTSC build, 
 *  By default RMAN pre-registers the NULL RESOURCE
 *  Use this to pre-register more resources 
 */

#include <xdc/std.h>
#include <rman.h>


#define RMAN_PARAMS_NUMREGISTRIES 10        /* Number of entries in RMAN table*/
#define RMAN_PARAMS_ALLOCFXN NULL           /* RMAN memory allocation function*/
#define RMAN_PARAMS_FREEFXN NULL            /* RMAN memory free function */
#define RMAN_PARAMS_YIELDSAMEPRI FALSE      /* Support for same-priority yield*/
#define RMAN_PARAMS_YIELDFXN NULL           /* Custom yield function */  

/**
 * RMAN_PARAMS structure can be over-ridden with actual values 
 */
RMAN_Params RMAN_PARAMS = {

    RMAN_PARAMS_NUMREGISTRIES,

    RMAN_PARAMS_ALLOCFXN, 

    RMAN_PARAMS_FREEFXN,

    RMAN_PARAMS_YIELDFXN,

    RMAN_PARAMS_YIELDSAMEPRI
};

/* Table of user-configured size to store the registration entries */ 
__FAR__ IRESMAN_Fxns * RMAN_TABLE[RMAN_PARAMS_NUMREGISTRIES];

/* Table of user-configured size to store the freed entries */ 
__FAR__ short RMAN_FREE_ENTRIES[RMAN_PARAMS_NUMREGISTRIES];
/*
 *  @(#) ti.sdo.fc.rman; 2, 0, 0,207; 12-1-2010 17:25:37; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

