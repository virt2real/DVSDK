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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <xdc/std.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Display.h>

#include "priv/_SysFs.h"

#define MODULE_NAME     "Dmai"

/* Strings for sysfs video output variables */
static Char *outputStrings[Display_Output_COUNT] = {
    "SVIDEO",
    "COMPOSITE",
    "COMPONENT",
    "LCD",
    "DVI",
    NULL
};

/* Strings for sysfs video mode variables */
static Char *modeStrings[VideoStd_COUNT] = {
    NULL,
    NULL,
    NULL,
    NULL,
    "VGA",
    "NTSC",
    "PAL",
    "480P-60",
    "576P-50",
    "720P-60",
    "720P-50",
    "720P-30",
    "1080I-30",
    "1080I-25",
    "1080P-30",
    "1080P-25",
    "1080P-24",
    "1080P-60",
    "1080P-50",
};

#define SYSFS_FMT             "/sys/class/davinci_display/ch%d/output"

/******************************************************************************
 * readSysFs
 ******************************************************************************/
static Int readSysFs(Char *fileName, Char *val, int length)
{
    FILE *fp;
    int ret;
    int len;
    char *tok;

    fp = fopen(fileName, "r");

    if (fp == NULL) {
        Dmai_err1("Failed to open %s for reading\n", fileName);
        return Dmai_EIO;
    }

    memset(val, '\0', length);

    ret = fread(val, 1, length, fp);

    if (ret < 1) {
        Dmai_err1("Failed to read sysfs variable from %s\n", fileName);
        return Dmai_EIO;
    }

    tok = strtok(val, "\n");
    len = tok ? strlen(tok) : strlen(val);
    val[len] = '\0';

    fclose(fp);

    return Dmai_EOK;
}

/******************************************************************************
 * writeSysFs
 ******************************************************************************/
static Int writeSysFs(Char *fileName, Char *val)
{
    FILE *fp;
    Char *valString;

    valString = malloc(strlen(val) + 1);

    if (valString == NULL) {
        Dmai_err0("Failed to allocate memory for temporary string\n");
        return Dmai_ENOMEM;
    }

    fp = fopen(fileName, "w");

    if (fp == NULL) {
        Dmai_err1("Failed to open %s for writing\n", fileName);
        free(valString);
        return Dmai_EIO;
    }

    if (fwrite(val, strlen(val) + 1, 1, fp) != 1) {
        Dmai_err2("Failed to write sysfs variable %s to %s\n",
                  fileName, val);
        fclose(fp);
        free(valString);
        return Dmai_EIO;
    }

    fclose(fp);

    if (readSysFs(fileName, valString, strlen(val) + 1) < 0) {
        free(valString);
        return Dmai_EIO;
    }

    if (strcmp(valString, val) != 0) {
        Dmai_err3("Failed to verify sysfs variable %s to %s (is %s)\n",
                  fileName, val, valString);
        free(valString);
        return Dmai_EFAIL;
    }

    free(valString);

    return Dmai_EOK;
}


/******************************************************************************
 * _SysFs_setup (INTERNAL)
 ******************************************************************************/
Int _SysFs_setup(Display_Attrs *attrs)
{
    Char sysfsFileName[MAX_SYSFS_PATH_LEN];
    Char sysfsValue[MAX_SYSFS_VALUE_LEN];
    Int  sysfsVideoStd;
    Int  sysfsDisplayOut;

    sprintf(sysfsFileName, SYSFS_FMT, 0);
    
    /* Select the output by reading from sysfs */
    if (attrs->videoOutput == Display_Output_SYSTEM) {
        if (readSysFs(sysfsFileName, sysfsValue, MAX_SYSFS_VALUE_LEN)) {
            return Dmai_EIO;
        }

        /* Map sysfs string to the display output enum */
        for (sysfsDisplayOut=0; sysfsDisplayOut < Display_Output_COUNT; 
                sysfsDisplayOut++) {
            if (outputStrings[sysfsDisplayOut] == NULL)
                continue;
            if (strcmp(outputStrings[sysfsDisplayOut],sysfsValue) == 0) {
                attrs->videoOutput = sysfsDisplayOut;
                Dmai_dbg1("Setting video output to '%s'\n", 
                            outputStrings[attrs->videoOutput]);
                break;
            }
        }   
    }
    else {
        /* Sanity check the video output passed by user */
        if (attrs->videoOutput < 0 ||
            attrs->videoOutput > Display_Output_COUNT) {

            Dmai_err1("Unsupported video output %d\n", attrs->videoOutput);
            return Dmai_EINVAL; 
        }

        /* Select the output by writing to sysfs */
        if (writeSysFs(sysfsFileName, outputStrings[attrs->videoOutput]) 
            < 0) {
            return Dmai_EIO;
        }
    }

    sysfsFileName[strlen(SYSFS_FMT) - 7] = 0;
    strcat(sysfsFileName, "mode");

    /* Select the video standard by reading from sysfs */
    if (attrs->videoStd == VideoStd_AUTO) {        
        if(readSysFs(sysfsFileName, sysfsValue, MAX_SYSFS_VALUE_LEN)) {
            return Dmai_EIO;
        }
 
        /* Map sysfs string to the video standard enum */
        for(sysfsVideoStd=0; sysfsVideoStd < VideoStd_COUNT; sysfsVideoStd++) {
            if (modeStrings[sysfsVideoStd] == NULL)
                continue;
            if (strcmp(modeStrings[sysfsVideoStd], sysfsValue) == 0) {
                attrs->videoStd = sysfsVideoStd;
                Dmai_dbg1("Setting video standard to '%s'\n", 
                            modeStrings[attrs->videoStd]);
                break;
            }
        }
    }
    else {
        /* Sanity check the display mode passed by user */
        if (attrs->videoStd < 0 ||
            attrs->videoStd > VideoStd_COUNT ||
            modeStrings[attrs->videoStd] == NULL ) { 

            Dmai_err1("Unsupported video standard %d\n", attrs->videoStd);
            return Dmai_EINVAL; 
        }   

        /* Select the video standard by writing to sysfs */
        if (writeSysFs(sysfsFileName, modeStrings[attrs->videoStd]) < 0) {
            return Dmai_EIO;
        }
    }


    return Dmai_EOK;
}
