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
#include <ti/sdo/utils/trace/gt.h>
#include <ti/xdais/dm/xdm.h>
#include <ti/xdais/dm/ivideo.h>

#include "XdmUtils.h"

/* REMEMBER: if you add an initialized static var, reinitialize it at cleanup */
static Bool curInit = FALSE;

static GT_Mask curTrace;

/*
 * ======== XdmUtils_init ========
 */
Void XdmUtils_init(Void)
{
    if (curInit != TRUE) {
        curInit = TRUE;

        GT_create(&curTrace, "XU");
    }
}


#if 0
/*
 * ======== TraceUtil_exit ========
 */
Void XdmUtils_exit()
{
    if (curInit == FALSE) {
        return;
    }
    curInit = FALSE;

}
#endif


/*
 *  ======== XdmUtils_validateExtendedStruct ========
 */
Bool XdmUtils_validateExtendedStruct(void *pStruct, UInt minSize, char *name)
{
    Bool fRetVal;
    UInt32 providedSize;

    GT_3trace(curTrace, GT_ENTER, "XdmUtils_validateExtendedStruct> "
        "Enter (pStruct=0x%x, minSize=0x%x, name=%s\n", pStruct, minSize, name);

    if (pStruct == NULL) {
        GT_1trace(curTrace, GT_7CLASS, "ERROR> extended struct (%s) is NULL\n",
            name);
        fRetVal = FALSE;
    }
    else {
        providedSize = (*((UInt32 *)pStruct));

        if (providedSize < minSize) {
            GT_3trace(curTrace, GT_7CLASS, "ERROR> invalid extended struct (%s)"
                " detected - only %d of required %d bytes were provided!\n",
                name, providedSize, minSize);
            fRetVal = FALSE;
        }
        else {
            fRetVal = TRUE;
        }
    }

    GT_1trace(curTrace, GT_ENTER, "XdmUtils_validateExtendedStruct> return "
        "(0x%x)\n", fRetVal);

    return (fRetVal);
}


/*
 *  ======== XdmUtils_validateSparseBufDesc ========
 */
Bool XdmUtils_validateSparseBufDesc(XDM_BufDesc *bufDesc, char *name)
{
    Int i;
    Int numValidBufs;
    Bool fRetVal;

    GT_2trace(curTrace, GT_ENTER, "XdmUtils_validateSparseBufDesc> "
        "Enter (bufDesc=0x%x, name=%s\n", bufDesc, name);

    if (bufDesc == NULL) {
        GT_1trace(curTrace, GT_7CLASS, "ERROR> bufDesc (%s) pointer is NULL\n",
            name);
        return (FALSE);
    }

    for (i = 0, numValidBufs = 0; i < XDM_MAX_IO_BUFFERS; i++) {
        if (bufDesc->bufs[i] != NULL) {
            numValidBufs++;
        }
    }

    /* finding more buffers than declared is okay, but finding fewer is not */
    if (numValidBufs < bufDesc->numBufs) {
        GT_3trace(curTrace, GT_7CLASS, "ERROR> invalid bufDesc (%s) detected - "
            "%d of %d expected bufs were found!\n", name, numValidBufs,
            bufDesc->numBufs);
        fRetVal = FALSE;
    }
    else {
        fRetVal = TRUE;
    }

    GT_1trace(curTrace, GT_ENTER, "XdmUtils_validateSparseBufDesc> return "
        "(0x%x)\n", fRetVal);

    return (fRetVal);
}

/*
 *  ======== XdmUtils_validateSparseBufDesc1 ========
 */
Bool XdmUtils_validateSparseBufDesc1(XDM1_BufDesc *bufDesc, char *name)
{
    Int i;
    Int numValidBufs;
    Bool fRetVal;

    GT_2trace(curTrace, GT_ENTER, "XdmUtils_validateSparseBufDesc1> "
        "Enter (bufDesc=0x%x, name=%s\n", bufDesc, name);

    if (bufDesc == NULL) {
        GT_1trace(curTrace, GT_7CLASS, "ERROR> bufDesc (%s) pointer is NULL\n",
            name);
        return (FALSE);
    }

    for (i = 0, numValidBufs = 0; i < XDM_MAX_IO_BUFFERS; i++) {
        if (bufDesc->descs[i].buf != NULL) {
            numValidBufs++;
        }
    }

    /* finding more buffers than declared is okay, but finding fewer is not */
    if (numValidBufs < bufDesc->numBufs) {
        GT_3trace(curTrace, GT_7CLASS, "ERROR> invalid bufDesc (%s) detected - "
            "%d of %d expected bufs were found!\n", name, numValidBufs,
            bufDesc->numBufs);
        fRetVal = FALSE;
    }
    else {
        fRetVal = TRUE;
    }

    GT_1trace(curTrace, GT_ENTER, "XdmUtils_validateSparseBufDesc1> return "
        "(0x%x)\n", fRetVal);

    return (fRetVal);
}

/*
 *  ======== XdmUtils_validateVideoBufDesc ========
 */
Bool XdmUtils_validateVideoBufDesc(IVIDEO_BufDesc *vidBufDesc, char *name)
{
    Int i;
    Int numValidBufs;
    Bool fRetVal = TRUE;   /* optimistic */

    GT_2trace(curTrace, GT_ENTER, "XdmUtils_validateVideoBufDesc> "
            "Enter (vidBufDesc=0x%x, name=%s\n", vidBufDesc, name);

    if (vidBufDesc == NULL) {
        GT_1trace(curTrace, GT_7CLASS,
                "ERROR> IVIDEO_BufDesc \"%s\" pointer is NULL\n", name);
        return (FALSE);
    }

    numValidBufs = vidBufDesc->numBufs;

    if ((numValidBufs < 0) || (numValidBufs > XDM_MAX_IO_BUFFERS)) {
        GT_2trace(curTrace, GT_7CLASS,
                "ERROR> %s->numBufs (%d) is invalid\n", name,
                vidBufDesc->numBufs);
        return (FALSE);
    }

    for (i = 0; i < numValidBufs; i++) {
        if (vidBufDesc->bufs[i] == NULL) {
            GT_4trace(curTrace, GT_7CLASS,
                    "ERROR> %s->numBufs is %d, but %s->bufs[%d] is NULL!\n",
                    name, vidBufDesc->numBufs, name, i);
            return (FALSE);
        }
        if (vidBufDesc->bufSizes[i] <= 0) {
            GT_4trace(curTrace, GT_7CLASS,
                    "ERROR> %s->bufSizes[%d] is invalid - %d (0x%x)!\n",
                    name, i, vidBufDesc->bufSizes[i], vidBufDesc->bufSizes[i]);
            return (FALSE);
        }
    }

    GT_1trace(curTrace, GT_ENTER, "XdmUtils_validateVideoBufDesc> return "
            "(0x%x)\n", fRetVal);

    return (fRetVal);
}


/*
 *  ======== XdmUtils_validateVideo1BufDesc ========
 */
Bool XdmUtils_validateVideo1BufDesc(IVIDEO1_BufDesc *vidBufDesc, char *name)
{
    Int i;
    Int numValidBufs;
    Bool fRetVal = TRUE;   /* optimistic */

    GT_2trace(curTrace, GT_ENTER, "XdmUtils_validateVideo1BufDesc> "
            "Enter (vidBufDesc=0x%x, name=%s\n", vidBufDesc, name);

    if (vidBufDesc == NULL) {
        GT_1trace(curTrace, GT_7CLASS,
                "ERROR> IVIDEO_BufDesc \"%s\" pointer is NULL\n", name);
        return (FALSE);
    }

    numValidBufs = vidBufDesc->numBufs;

    if ((numValidBufs < 0) || (numValidBufs > IVIDEO_MAX_YUV_BUFFERS)) {
        GT_2trace(curTrace, GT_7CLASS,
                "ERROR> %s->numBufs (%d) is invalid\n", name,
                vidBufDesc->numBufs);
        return (FALSE);
    }

    for (i = 0; i < numValidBufs; i++) {
        if (vidBufDesc->bufDesc[i].buf == NULL) {
            GT_4trace(curTrace, GT_7CLASS,
                    "ERROR> %s->numBufs is %d, but %s->bufDesc[%d].buf is "
                    "NULL!\n", name, vidBufDesc->numBufs, name, i);
            return (FALSE);
        }
        if (vidBufDesc->bufDesc[i].bufSize <= 0) {
            GT_4trace(curTrace, GT_7CLASS,
                    "ERROR> %s->bufDesc[%d].bufSize is invalid - %d (0x%x)!\n",
                    name, i, vidBufDesc->bufDesc[i].bufSize,
                    vidBufDesc->bufDesc[i].bufSize);
            return (FALSE);
        }
    }

    GT_1trace(curTrace, GT_ENTER, "XdmUtils_validateVideo1BufDesc> return "
            "(0x%x)\n", fRetVal);

    return (fRetVal);
}
/*
 *  @(#) ti.sdo.ce.utils.xdm; 1, 0, 2,232; 12-2-2010 21:28:08; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

