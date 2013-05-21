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
 *  ======== osalsetenv.c ========
 *  Utility program to set "environment" variables for WinCE. The variable
 *  name and its value are stored in the Windows registry.
 */

#include <windows.h>


#define OSAL_REG_KEY TEXT("SOFTWARE\\Texas Instruments\\ti.sdo.ce.osal")

static BOOL setEnv(char *name, char *val);


/*
 *  ======== smain ========
 */
int main(int argc, char **argv)
{
    char *env = NULL;

    if ((argc <= 1) || (argc > 3)) {
        RETAILMSG(TRUE, (TEXT("Usage: osalsetenv_wince.exe <var> [val]\n")));
        return (-1);
    }

    if (argc == 2) {
        if (!setEnv(argv[1], NULL)) {
            RETAILMSG(TRUE, (TEXT("Failed to unset environment variable\n")));
        }
        else {
            RETAILMSG(TRUE, (TEXT("Environment variable unset\n")));
        }
    }
    else {
        if (!setEnv(argv[1], argv[2])) {
            RETAILMSG(TRUE, (TEXT("Failed to set environment variable\n")));
        }
        else {
            RETAILMSG(TRUE, (TEXT("Environment variable set\n")));
        }
    }

    return (0);
}

/*
 *  ======== setEnv ========
 */
static BOOL setEnv(char *name, char *val)
{
    LONG        lStatus = 0;
    HKEY        hKey;
    DWORD       dwcbData;
    WCHAR       wszEnvName[256];
    WCHAR       wszEnvVal[256];

    if (name == NULL) {
        RETAILMSG(TRUE, (TEXT("setEnv> name must be non-NULL\n")));
        return (FALSE);
    }

    /*
     *  Create the reg key. If it already exists, this function opens it.
     */
    lStatus = RegCreateKeyEx(HKEY_LOCAL_MACHINE,
                             OSAL_REG_KEY,
                             0,
                             NULL,
                             REG_OPTION_NON_VOLATILE,
                             0,
                             NULL,
                             &hKey,
                             NULL);

    if (lStatus == ERROR_SUCCESS) {
        MultiByteToWideChar(CP_ACP, 0, name, strlen(name) + 1, wszEnvName,
                sizeof(wszEnvName) / sizeof(wszEnvName[0]));

        if (val != NULL) {
            MultiByteToWideChar(CP_ACP, 0, val, strlen(val) + 1, wszEnvVal,
                    sizeof(wszEnvVal) / sizeof(wszEnvVal[0]));
            dwcbData = (strlen(val) + 1) * sizeof(TCHAR);

            lStatus = RegSetValueEx(hKey,
                    wszEnvName,          /* the name of the registry entry */
                    0,                   /* Reserved - must be set to 0 */
                    REG_SZ,              /* data type - Unicode string */
                    (LPBYTE)wszEnvVal,   /* the data */
                    dwcbData);           /* size of the data */
        }
        else {
            /*
             *  Passing in a NULL val corresponds to unsetting the environment
             *  variable. So we'll delete the value from the registry.
             */
            lStatus = RegDeleteValue(hKey, wszEnvName);

            if (lStatus == ERROR_FILE_NOT_FOUND) {
                /* This is ok. We're unsetting a variable that wasn't set */
                lStatus = ERROR_SUCCESS;
            }
        }

        RegCloseKey(hKey);
    }
    return ((lStatus == ERROR_SUCCESS) ? TRUE : FALSE);
}
/*
 *  @(#) ti.sdo.ce.osal.wince.utils; 1, 0, 0,77; 12-2-2010 21:25:04; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

