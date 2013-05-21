/*
******************************************************************************
*  
* DM36x Based H.264 Decoder Test Application
*
* "DM36x Based H.264 Decoder Test application is software module developed on TI's DM36x.
* This module shows XDM interface for H.264 Video Decoder.
* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/ 
* ALL RIGHTS RESERVED 
******************************************************************************
*/
/*
 *  ======== LockMP_noOS.c ========
 *  Mock implementation of an MP Lock. Replace with CE OSAL in real program 
 */

#include <xdc/std.h>


/*
 *  ======== LockMP_Obj ========
 */
typedef struct LockMP_Obj {
    Int count;
    Int key;
} LockMP_Obj;

typedef LockMP_Obj * LockMP_Handle; 

static LockMP_Obj lockArr[100];

static int index = 0;
 
/*
 *  ======== LockMP_acquire ========
 */
Void LockMP_acquire(LockMP_Handle lock)
{
    int i;
    for (i = 0; i < index; i++) {
        if (lockArr[i].key == lock->key) {
            lockArr[i].count++;
            return;
        }
    } 
    while(1);
}

/*
 *  ======== LockMP_create ========
 */
LockMP_Handle LockMP_create(Int key)
{
    lockArr[index].key = key; 
    lockArr[index].count++;
    index++;
    return (&lockArr[index-1]);
}

/*
 *  ======== LockMP_delete ========
 */
Void LockMP_delete(LockMP_Handle lock)
{
}

/*
 *  ======== LockMP_getCount ========
 */
Int LockMP_getCount(LockMP_Handle lock)
{
    int i;
    for (i = 0; i < index; i++) {
        if (lockArr[i].key == lock->key) {
            return lockArr[i].count;
        }
    } 
    while(1);
}

/*
 *  ======== LockMP_getRefCount ========
 */
Int LockMP_getRefCount(LockMP_Handle lock)
{
    return (0);
}

/*
 *  ======== LockMP_init ========
 */
Void LockMP_init(Void)
{
}

/*
 *  ======== LockMP_release ========
 */
Void LockMP_release(LockMP_Handle lock)
{
    int i;
    for (i = 0; i < index; i++) {
        if (lockArr[i].key == lock->key) {
            lockArr[i].count--;
            return;
        }
    } 
    while(1);
}

/*
 *  @(#) ti.sdo.fc.rman.examples; 1, 0, 0,25; 8-28-2008 20:02:31; /db/atree/library/trees/fc-h05x/src/
 */

