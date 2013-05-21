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
#include <xdc/std.h>
#include <ti/sdo/fc/edma3/edma3_config.h>
#include <ti/sdo/fc/rman/rman.h>

/* When using XDC build, this information is auto-generated. 
   When using "C" based PJTs, this file will be required */

/* 
 * Declare semaphore related functions before using them
 */
extern RMAN_SemHandle mySemCreate(Int key, Int count);
extern Void mySemDelete(RMAN_SemHandle sem);
extern Int mySemPend(RMAN_SemHandle sem, unsigned int count);
extern Void mySemPost(RMAN_SemHandle sem);

/*
 * Declare alloc/Free functions before using them
 */
extern Bool myAlloc(IALG_MemRec *memTab, Int numRecs);
extern Void myFree(IALG_MemRec *memTab, Int numRecs);


/*
 *  ======== EDMA3_createResourceManagerObject ========
 *  Creates a resource manager object based on the underlying SOC
 */
EDMA3_Result EDMA3_createResourceManagerObject()
{
    EDMA3_Result status;
    EDMA3_MiscParam param = {NULL , NULL};

    param.isSlave = (EDMA3_PARAMS.globalInit == 1) ? 0 : 1;

    status = EDMA3_create(EDMA3_PHYSICALID,
            (EDMA3_GblConfigParams *)(EDMA3_PARAMS.globalConfig), &param);

    return (status);
}

/*
 *  ======== EDMA3_deleteResourceManagerObject ========
 *  Deletes the resource manager object based on the underlying SOC
 */
EDMA3_Result EDMA3_deleteResourceManagerObject()
{
    EDMA3_Result status;

    status = EDMA3_delete(EDMA3_PHYSICALID, (const void *)NULL);

    return (status);
}



    
/*
 *  ======== EDMA3_semCreate ========
 *  Function to create a Semaphore given a key
 */ 
void * EDMA3_semCreate(Int key, Int count)
{
    /*
     * Call RMAN's configured semCreateFxn, cast the returned semaphore value
     * to the Semaphore type expected by EDMA3 RM.
     */
    return ((void *)mySemCreate(key, count));
}

/*
 *  ======== EDMA3_semDelete ========
 *  Function to delete a given Semaphore
 */
void EDMA3_semDelete(EDMA3_OS_Sem_Handle hSem)
{
    mySemDelete((RMAN_SemHandle)hSem);
}

/*
 *  ======== edma3OsSemGive ========
 *  Function to Post a semaphore
 *  This function is called internally by the EDMA3 Low level Resource Manager
 */
EDMA3_Result edma3OsSemGive(EDMA3_OS_Sem_Handle hSem)
{
    EDMA3_Result semGiveResult = EDMA3_SOK;
    if(NULL == hSem) {
        semGiveResult = EDMA3_E_INVALID_PARAM;
    }
    else {
        mySemPost((RMAN_SemHandle)hSem);
    }
    return (semGiveResult);
}

/* 
 *  ======== edma3OsSemTake ========
 *  Function to Pend on a semaphore 
 *  This function is called internally by the EDMA3 Low level Resource Manager
 */
EDMA3_Result edma3OsSemTake(EDMA3_OS_Sem_Handle hSem, int mSecTimeout)
{    
    EDMA3_Result semTakeResult = EDMA3_SOK;
    unsigned short semPendResult;

    if(NULL == hSem) {
        semTakeResult = EDMA3_E_INVALID_PARAM;
    }
    else {
        semPendResult = mySemPend((RMAN_SemHandle)hSem,
                (UInt32)mSecTimeout);
        if (semPendResult != 0) {
            semTakeResult = EDMA3_E_SEMAPHORE;
        }
    }

    return (semTakeResult);
}

/*
 *  ======== edma3OsProtectEntry ========
 *  OS critical section protect (Entry) function
 */
void edma3OsProtectEntry (int level, unsigned int *intState)
{
    if (((level == EDMA3_OS_PROTECT_INTERRUPT)
        || (level == EDMA3_OS_PROTECT_INTERRUPT_TC_ERROR))
        && (intState == NULL)) {
        return;
    }
    else {
        switch (level) {
            /* Disable all (global) interrupts */
            case EDMA3_OS_PROTECT_INTERRUPT :
                *intState = HWI_disable();
                break;

            /* Disable scheduler */
            case EDMA3_OS_PROTECT_SCHEDULER :
                TSK_disable();
                break;

            /* Disable scheduler */
            case EDMA3_OS_PROTECT_INTERRUPT_XFER_COMPLETION :
                TSK_disable();
                break;

            /* Disable scheduler */
            case EDMA3_OS_PROTECT_INTERRUPT_CC_ERROR :
                TSK_disable();
                break;

            case EDMA3_OS_PROTECT_INTERRUPT_TC_ERROR :
                switch (*intState) {
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                        /* Fall through... */
                        TSK_disable();
                        break;

                     default:
                        break;
                }
                break;

            default:
                break;
        }
    }
}


/*
 *  ======== edma3OsProtectExit ========
 *  OS critical section protect (Exit) function
 */
void edma3OsProtectExit(int level, unsigned int intState)
{
    switch (level) {
        /* Enable all (global) interrupts */
        case EDMA3_OS_PROTECT_INTERRUPT :
            HWI_restore(intState);
            break;

        /* Enable scheduler */
        case EDMA3_OS_PROTECT_SCHEDULER :
            break;
 
        case EDMA3_OS_PROTECT_INTERRUPT_XFER_COMPLETION :
            TSK_enable();
            break;

        case EDMA3_OS_PROTECT_INTERRUPT_CC_ERROR :
            TSK_enable();
            break;

        /* Enable EDMA3 TC error interrupt only */
        case EDMA3_OS_PROTECT_INTERRUPT_TC_ERROR :
            switch (intState)
                {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                    /* Fall through... */
                    /* Enable the corresponding interrupt */
                    TSK_enable();
                    break;

                 default:
                    break;
                }

            break;

        default: 
            break;
    }
}
/*
 *  @(#) ti.sdo.fc.dman3.examples.fastcopy; 1, 0, 0,235; 12-1-2010 17:24:29; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

