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
 *  ======== Reg_wince.c ========
 */
#include <xdc/std.h>

#include <stdlib.h>
#include <windows.h>

#include <ti/sdo/utils/trace/gt.h>

#include <ti/sdo/ce/osal/Global.h>
#include <ti/sdo/ce/osal/Memory.h>

#include <ti/sdo/ce/osal/wince/Reg.h>


/* REMINDER: if you add an initialized static var, reinitialize it at cleanup */

static Void    cleanup(Void);

static Int curInit = 0;

static GT_Mask curTrace = {NULL, NULL};

/*
 *  ======== Reg_getValue ========
 *  Retrieve a value from the registry.
 */
Bool Reg_getValue(HKEY *phKey, String subkey, String value,
                        UInt8 *pbData, Int *pDataSize)
{
    HKEY            hKey = NULL;
    LONG            lResult = 0L;
    DWORD           dwType = 0L;
    WCHAR           wszSubkey[Reg_MAXREGPATHLENGTH];
    WCHAR           wszValue[Reg_MAXREGPATHLENGTH];
    UInt8          *pRegData;
    UInt32          bufSize;
    Bool            status = TRUE;
    
    GT_0trace(curTrace, GT_ENTER, "Reg_getValue: entered\n");
    
    /* Convert ANSI strings to UNICODE */
    if (strlen(subkey) > Reg_MAXREGPATHLENGTH) {
        GT_2trace(curTrace, GT_7CLASS,
                "Length of registry key: %d, exceeds maximum (%d)\n",
                strlen(subkey), Reg_MAXREGPATHLENGTH);
        status = FALSE;
    }

    if (strlen(value) > Reg_MAXREGPATHLENGTH) {
        GT_2trace(curTrace, GT_7CLASS,
                "Length of registry value: %d, exceeds maximum (%d)\n",
                strlen(value), Reg_MAXREGPATHLENGTH);
        status = FALSE;
    }

    if (pDataSize == NULL) {
        GT_0trace(curTrace, GT_7CLASS,
                "Must enter a non-NULL pointer to data size!\n");
        status = FALSE;
    }

    if (status) {
        /* Convert ANSI strings to UNICODE */
        MultiByteToWideChar(CP_ACP, 0, subkey, strlen(subkey) + 1, wszSubkey,
                sizeof(wszSubkey) / sizeof(wszSubkey[0]));

        MultiByteToWideChar(CP_ACP, 0, value, strlen(value) + 1, wszValue,
                sizeof(wszValue) / sizeof(wszValue[0]));
    }

    if (status) {
        /* Open the registry subkey */
        lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, wszSubkey, 0, 0, &hKey);

        if (lResult != ERROR_SUCCESS) {
            status = FALSE;
            GT_0trace(curTrace, GT_6CLASS, "Reg_getValue: RegOpenKeyEx() "
                    "failed\n");
        }
        else {
            /* Allocate memory for query buffer. */
            bufSize = sizeof(BYTE) * (*pDataSize);
            pRegData = Memory_alloc(bufSize, NULL);

            if (pRegData == NULL) {
                status = FALSE;
                GT_0trace(curTrace, GT_7CLASS, "Reg_getValue: Memory_alloc() "
                        "failed\n");
            }
            else {
                /* Query registry value. */
                lResult = RegQueryValueEx(hKey, wszValue, NULL, &dwType,
                        pRegData, pDataSize);

                if (lResult == ERROR_SUCCESS) {
                    if ((dwType == REG_SZ) || (dwType == REG_MULTI_SZ) ||
                            (dwType == REG_EXPAND_SZ)) {
                        /* Convert UNICODE strings to ANSI. */
                        wcstombs(pbData, (WCHAR *)pRegData, *pDataSize);
                    }
                    else {
                        memcpy(pbData, pRegData, *pDataSize);
                    }
                }
                else if (lResult == ERROR_MORE_DATA) {
                    /* Data didn't fit */
                    status = FALSE;
                    GT_0trace(curTrace, GT_6CLASS,"Reg_getValue: "
                            "RegQueryValueEx() returned ERROR_MORE_DATA\n");
                }
                else {
                    status = FALSE;
                    GT_0trace(curTrace, GT_6CLASS, 
                            "Reg_getValue: RegQueryValueEx() failed\n");
                }
                    
                /* Free allocated memory. */
                Memory_free(pRegData, bufSize, NULL);
            }
                
            /* close opened key */
            lResult = RegCloseKey (hKey);
        }
    }
    
    return (status);
}

/*
 *  ======== Reg_init ========
 */
Void Reg_init(Void)
{
    if (curInit++ == 0) {
        GT_create(&curTrace, Reg_GTNAME);
        GT_0trace(curTrace, GT_4CLASS, "Reg_init> ");

        Global_atexit((Fxn)cleanup);
    }
}


/*
 *  ======== Reg_setValue ========
 *  Set a value in the registry.
 */
Bool Reg_setValue(HKEY *phKey, String subkey, String value, UInt32 type,
        UInt8 *pData, UInt32 dataSize, UInt32 flags)
{
    LONG        lResult = 0L;
    HKEY        hKey = NULL;
    DWORD       dwType = (DWORD)type;
    DWORD       dwDisposition = 0L;
    WCHAR       wszSubkey[Reg_MAXREGPATHLENGTH];
    WCHAR       wszValue[Reg_MAXREGPATHLENGTH];
    TCHAR      *ptszData = NULL;
    BYTE       *pRegData = pData;            /* registry value to set */
    UInt32      bufSize;
    DWORD       options;
    Bool        status = TRUE;
    
    GT_assert(curTrace, subkey && value && pData);
    GT_assert(curTrace, phKey == NULL);
    GT_assert(curTrace, dataSize > 0);
    GT_assert(curTrace, strlen(subkey) < Reg_MAXREGPATHLENGTH);
    GT_assert(curTrace, strlen(value) < Reg_MAXREGPATHLENGTH);
    
    GT_0trace(curTrace, GT_ENTER, "Reg_setValue: entered\n");
    
    options = (flags & Reg_NONVOLATILE) ? REG_OPTION_NON_VOLATILE :
        REG_OPTION_VOLATILE;

    /* convert ANSI strings to UNICODE */
    MultiByteToWideChar(CP_ACP, 0, subkey, strlen(subkey) + 1, wszSubkey,
                sizeof(wszSubkey) / sizeof(wszSubkey[0]));
    MultiByteToWideChar(CP_ACP, 0, value, strlen(value) + 1, wszValue,
                sizeof(wszValue) / sizeof(wszValue[0]));
            
    /* check the type of registry value to be set */
    if ((dwType == REG_SZ) || (dwType == REG_MULTI_SZ) ||
            (dwType == REG_EXPAND_SZ)) {
                
        /* Allocate memory for string value. */
        bufSize = sizeof(WCHAR) * dataSize;
        ptszData = Memory_alloc(bufSize, NULL);
        if (ptszData == NULL) {
            status = FALSE;
            GT_0trace(curTrace, GT_6CLASS, "Reg_setValue: Memory_alloc() "
                    "failed\n");
        }
        else {
            MultiByteToWideChar(CP_ACP, 0, pData, strlen(pData) + 1,
                    ptszData, bufSize);
            /* Set data size according to length of data string. */
            dataSize = sizeof(TCHAR) * dataSize;
            pRegData = (BYTE*)ptszData;
        }
    }

    if (status) {
        /* Create reg key if it does not exist. */
        lResult = RegCreateKeyEx(HKEY_LOCAL_MACHINE, wszSubkey, 0, TEXT(""),
                options, 0, NULL, &hKey, &dwDisposition);

        if (lResult != ERROR_SUCCESS) {
            status = FALSE;
            GT_0trace(curTrace, GT_6CLASS, "REG_SetValue: RegCreateKeyEx() "
                    "failed\n");
        }
    }

    if (status) {
        /* Set reg value. */
        lResult = RegSetValueEx(hKey, wszValue, 0, dwType, pRegData, dataSize);
        if (lResult != ERROR_SUCCESS) {
            status = FALSE;
            GT_0trace(curTrace, GT_6CLASS, "REG_SetValue: RegSetValueEx() "
                    "failed\n");
        }
        /* Close the active key */
        RegCloseKey (hKey);
    }
    
    /* Free allocated memory. */
    if (ptszData) {
        Memory_free(ptszData, bufSize, NULL);
    }
    
    return (status);
}

/*
 *  ======== cleanup ========
 */
static Void cleanup(Void)
{
    GT_assert(curTrace, curInit > 0);

    if (--curInit == 0) {
        /* Nothing to do */
    }
}
/*
 *  @(#) ti.sdo.ce.osal.wince; 1, 0, 0,82; 12-2-2010 21:25:05; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

