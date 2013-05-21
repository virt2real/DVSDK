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
 *  ======== File.h ========
 */

/**
 *  @file       ti/sdo/ce/osal/File.h
 *
 *  @brief      The Codec Engine OSAL File module.
 */


#ifndef ti_sdo_ce_osal_File_
#define ti_sdo_ce_osal_File_

#ifdef __cplusplus
extern "C" {
#endif

#define File_EOK          0                 /* no error */
#define File_EFAIL        -1                /* unspecified failure */

/*
 *  ======== File_GTNAME ========
 */
#define File_GTNAME       "ti.sdo.ce.osal.File"

/*
 *  ======== File_Stat ========
 */
typedef struct File_Stat {
    Uint32 resvd_0;
    UInt32 resvd_1;
    UInt32 resvd_2;
    UInt32 resvd_3;
} File_Stat;

/*
 *  ======== File_init ========
 */
/**
 *  @brief      Initialize the File module.
 *
 *  @remarks    This function must be called prior to using any of the File
 *              APIs.
 */
extern Void File_init(Void);

/*
 *  ======== File_stat ========
 */
/**
 *  @brief      Return information about a file.
 *
 *  @param[in]  name    The full path name of the file.
 *
 *  @param[in]  statBuf Location to store file stats.
 *
 *  @retval     File_EOK    Success
 *  @retval     File_EFAIL: Failure.
 */
extern Int File_stat(String name, File_Stat *statBuf);

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.osal; 2, 0, 2,427; 12-2-2010 21:24:37; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

