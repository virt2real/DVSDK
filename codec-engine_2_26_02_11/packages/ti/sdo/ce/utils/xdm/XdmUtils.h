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
 *  ======== XdmUtils.h ========
 */

/**
 *  @file       ti/sdo/ce/utils/xdm/XdmUtils.h
 *
 *  @brief      Codec Engine XDM-related utilities.
 */

#ifndef ti_sdo_ce_utils_xdm_XdmUtils_
#define ti_sdo_ce_utils_xdm_XdmUtils_

#include <ti/xdais/dm/xdm.h>
#include <ti/xdais/dm/ivideo.h>

#ifdef __cplusplus
extern "C" {
#endif

extern Void XdmUtils_init(Void);
extern Void XdmUtils_exit(Void);

/*
 *  ======== XdmUtils_validateExtendedStruct ========
 */
/**
 *  @brief      Utility fxn to validate a required, extendable structure with a
 *              first field named @c size.
 *
 *  @param[in]  pStruct     Pointer to extendable structure.
 *  @param[in]  minSize     Minimum size of the extendable 'base' structure.
 *  @param[in]  name        Friendly name to associate with the structure.
 *
 *  @pre        @c name <b>must</b> be a valid, zero-terminated string.
 *
 *  @remarks    This is commonly used to validate @c inArgs, @c outArgs,
 *              @c dynamicParams and @c Status structs.  As an example, in
 *              these cases @c name is commonly "inArgs", "outArgs",
 *              "dynamicParams" and "Status".
 */
extern Bool XdmUtils_validateExtendedStruct(void *pStruct, UInt minSize,
    char *name);


/*
 *  ======== XdmUtils_validateSparseBufDesc ========
 */
/**
 *  @brief      Utility fxn to validate a sparse XDM_BufDesc structure.
 *
 *  @param[in]  bufDesc     XDM_BufDesc to validate.
 *  @param[in]  name        Friendly name to associate with the buffer.
 *
 *  @pre        @c name <b>must</b> be a valid, zero-terminated string.
 *
 *  @remarks    This is commonly used to validate inBufs and outBufs of a
 *              process() call.  As an example, in these cases @c name is
 *              "inBufs" or "outBufs".
 */
extern Bool XdmUtils_validateSparseBufDesc(XDM_BufDesc *bufDesc, char *name);


/*
 *  ======== XdmUtils_validateSparseBufDesc ========
 */
/**
 *  @brief      Utility fxn to validate a sparse XDM_BufDesc2 structure.
 *
 *  @param[in]  bufDesc     XDM_BufDesc2 to validate.
 *  @param[in]  name        Friendly name to associate with the buffer.
 *
 *  @pre        @c name <b>must</b> be a valid, zero-terminated string.
 *
 *  @remarks    This is commonly used to validate inBufs and outBufs of a
 *              process() call.  As an example, in these cases @c name is
 *              "inBufs" or "outBufs".
 */
extern Bool XdmUtils_validateSparseBufDesc1(XDM1_BufDesc *bufDesc, char *name);

/*
 *  ======== XdmUtils_validateVideoBufDesc ========
 */
/**
 *  @brief      Utility fxn to validate a IVIDEO_BufDesc structure.
 *
 *  @param[in]  vidBufDesc  IVIDEO_BufDesc to validate.
 *  @param[in]  name        Friendly name to associate with the buffer.
 *
 *  @pre        @c name <b>must</b> be a valid, zero-terminated string.
 */
extern Bool XdmUtils_validateVideoBufDesc(IVIDEO_BufDesc *vidBufDesc,
        char *name);

/*
 *  ======== XdmUtils_validateVideo1BufDesc ========
 */
/**
 *  @brief      Utility fxn to validate a IVIDEO1_BufDesc structure.
 *
 *  @param[in]  vidBufDesc  IVIDEO1_BufDesc to validate.
 *  @param[in]  name        Friendly name to associate with the buffer.
 *
 *  @pre        @c name <b>must</b> be a valid, zero-terminated string.
 */
extern Bool XdmUtils_validateVideo1BufDesc(IVIDEO1_BufDesc *vidBufDesc,
        char *name);


#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.utils.xdm; 1, 0, 2,232; 12-2-2010 21:28:09; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

