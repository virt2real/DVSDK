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
/**
 *  @file       ti/sdo/fc/acpy3/acpy3_instr.h
 *
 *  @brief      ACPY3 Instrumentation API definitions.
 *
 *  @remark     These APIs are available only for the instrumented build of
 *              the ACPY3 library.
 */

#ifndef ti_sdo_fc_acpy_ACPY3_INSTR_
#define ti_sdo_fc_acpy_ACPY3_INSTR_

/** @ingroup    DSPACPY3 */
/*@{*/

#include <ti/xdais/idma3.h>


/** @cond INTERNAL */
#ifndef _ACPY3_INSTR_
    #define ACPY3_INSTR_CALLHOOKFXN(hooks, handle,hookId)
#else
    #define ACPY3_INSTR_CALLHOOKFXN(hooks, handle, hookId)\
        if(NULL != hooks)\
        {\
            if (NULL!= hooks->InstrHooks[hookId].fxn)\
            {\
                hooks->InstrHooks[hookId].fxn(handle, hooks->\
                    InstrHooks[hookId].args);\
            }\
        }
#endif /* _ACPY3_INSTR_ */

/** @endcond */

/**
 *  @brief   Number of primary instrumentation hook functions
 */
#define ACPY3_INSTR_NUMHOOKS 4
#define ACPY3_INSTR_NUMEXTENDEDHOOKS 22


/**
 *  @brief   Primary instrumentation hook function names.
 */
typedef enum ACPY3_INSTR_HookType {
    ACPY3_INSTR_START_ENTER = 0,
    ACPY3_INSTR_START_EXIT,
    ACPY3_INSTR_WAIT_ENTER,
    ACPY3_INSTR_WAIT_EXIT
} ACPY3_INSTR_HookType;


/**
 *  @brief    Extended instrumentation hook function names.
 */
typedef enum ACPY3_INSTR_ExtendedHookType {
    ACPY3_INSTR_WAITLINKED_ENTER,
    ACPY3_INSTR_WAITLINKED_EXIT,
    ACPY3_INSTR_ACTIVATE_ENTER,
    ACPY3_INSTR_ACTIVATE_EXIT,
    ACPY3_INSTR_DEACTIVATE_ENTER,
    ACPY3_INSTR_DEACTIVATE_EXIT,
    ACPY3_INSTR_COMPLETE_ENTER,
    ACPY3_INSTR_COMPLETE_EXIT,
    ACPY3_INSTR_COMPLETELINKED_ENTER,
    ACPY3_INSTR_COMPLETELINKED_EXIT,
    ACPY3_INSTR_CONFIGURE_ENTER,
    ACPY3_INSTR_CONFIGURE_EXIT,
    ACPY3_INSTR_FASTCONFIGURE16_ENTER,
    ACPY3_INSTR_FASTCONFIGURE16_EXIT,
    ACPY3_INSTR_FASTCONFIGURE32_ENTER,
    ACPY3_INSTR_FASTCONFIGURE32_EXIT,
    ACPY3_INSTR_SETFINAL_ENTER,
    ACPY3_INSTR_SETFINAL_EXIT,
    ACPY3_INSTR_SETFASTFINAL_ENTER,
    ACPY3_INSTR_SETFASTFINAL_EXIT,
    ACPY3_INSTR_INIT_ENTER,
    ACPY3_INSTR_INIT_EXIT,
    ACPY3_INSTR_EXIT_ENTER,
    ACPY3_INSTR_EXIT_EXIT
} ACPY3_INSTR_ExtendedHookType;


/**
 *  @brief    Function signature for hook instrumentation function.
 */
typedef void (*ACPY3_INSTR_HookFxn)(IDMA3_Handle handle, void *param);


/**
 *  @brief   Structure that holds the instrumentation hook function and
 *           its arguments.
 */
typedef struct ACPY3_INSTR_Hook {
    ACPY3_INSTR_HookFxn fxn;
    void * args;
} ACPY3_INSTR_Hook;


/**
 *  @brief    Array of the primary instrumentation hook functions and
 *            their arguments.
 */
typedef struct ACPY3_INSTR_Hooks {
    ACPY3_INSTR_Hook InstrHooks[ACPY3_INSTR_NUMHOOKS];
} ACPY3_INSTR_Hooks;


/**
 *  @brief    Array of the extended instrumentation hook functions and
 *            their arguments.
 */
typedef struct ACPY3_INSTR_ExtendedHooks {
    ACPY3_INSTR_Hook InstrHooks[ACPY3_INSTR_NUMEXTENDEDHOOKS];
} ACPY3_INSTR_ExtendedHooks;


/**
 *  @brief      Registering the hook functions for instrumentation.
 *
 *  @param[in]  handle            IDMA3 channel handle.
 *  @param[in]  hooks             Primary instrumentation hook functions array
 *  @param[in]  extended_hooks    Extended instrumentation hook functions array
 */
Void ACPY3_INSTR_registerHooks(IDMA3_Handle handle, ACPY3_INSTR_Hooks * hooks,
    ACPY3_INSTR_ExtendedHooks  * extended_hooks);


/**
 *  @brief      Un-registering the hook functions for instrumentation.
 *
 *  @param[in]  handle            IDMA3 channel handle.
 */
Void ACPY3_INSTR_unregisterHooks(IDMA3_Handle handle);

/*@}*/

#endif /* ti_sdo_fc_acpy_ACPY3_INSTR_ */
/*
 *  @(#) ti.sdo.fc.acpy3; 1, 0, 4,301; 12-1-2010 17:24:25; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

