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

/**
 * @defgroup   ti_sdo_dmai_BufTab   BufTab
 *
 * @brief Describes an array of Buffer objects (of all types, see #Buffer_Type).
 *        All buffers in a BufTab have the same size and are created with the
 *        same attributes. For this reason, one can access the first Buffer in
 *        the BufTab to learn about the characteristics of all Buffers in the
 *        BufTab. Typical usage below to allocate an array of 10 basic Buffers
 *        of size 1KB (no error checking):
 *
 * @code
 *     #include <xdc/std.h>
 *     #include <ti/sdo/dmai/Dmai.h>
 *     #include <ti/sdo/dmai/BufTab.h>
 *     BufTab_Handle hBufTab;
 *     Buffer_Attrs bAttrs = Buffer_Attrs_DEFAULT;
 *
 *     Dmai_init();
 *     hBufTab = BufTab_create(10, 1024, &bAttrs);
 *     // Operate on the Buffers in the BufTab
 *     BufTab_delete(hBufTab);
 * @endcode
 */

/** @ingroup    ti_sdo_dmai_BufTab */
/*@{*/

#ifndef ti_sdo_dmai_BufTab_Defines_
#define ti_sdo_dmai_BufTab_Defines_

/**
 * @brief       Handle through which to reference a BufTab.
 */
typedef struct BufTab_Object *BufTab_Handle;

#endif /* ti_sdo_dmai_BufTab_Defines_ */

#ifndef ti_sdo_dmai_BufTab_h_
#define ti_sdo_dmai_BufTab_h_

#include <xdc/std.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Buffer.h>

#if defined (__cplusplus)
extern "C" {
#endif

/**
 * @brief       Creates a BufTab and the buffers belonging to it.
 *
 * @param[in]   numBufs     Number of buffers to allocate.
 * @param[in]   size        Size in bytes of buffers to create.
 * @param[in]   attrs       #Buffer_Attrs to use for creating the buffers
 *                          in the BufTab.
 *
 * @retval      #BufTab_Handle for use in subsequent operations
 *              (see #BufTab_Handle).
 * @retval      NULL for failure.
 */
extern BufTab_Handle BufTab_create(Int numBufs,
                                   Int32 size, Buffer_Attrs *attrs);

/**
 * @brief       Deletes a BufTab.
 *
 * @param[in]   hBufTab     The #BufTab_Handle to delete.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #BufTab_create must be called before this function.
 */
extern Int BufTab_delete(BufTab_Handle hBufTab);

/**
 * @brief       Chunk a BufTab in to smaller buffer sizes. This will not
 *              change the original allocation during creation, it merely tries
 *              to fit many smaller Buffers inside the already
 *              allocated Buffers. 
 *
 *              Each buffer in a BufTab is chunked separately; i.e., if the 
 *              initial buffer size is not an exact multiple of the new bufSize, 
 *              the remaining space in the initial buffer becomes unused and 
 *              does not count when chunking the next buffer in the BufTab. 
 *              
 * @param[in]   hBufTab     The #BufTab_Handle to chunk.
 * @param[in]   numBufs     The desired # of buffers to chunk the BufTab into
 * @param[in]   bufSize     The size in bytes of the buffers to chunk in to.
 *
 * @retval      The difference between numBufs and the actual number of buffers 
 *              in the newly modified BufTab. 0 if the number of buffers matches 
 *              numBufs.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #BufTab_create must be called before this function.
 *
 * @remarks     If a Buffer inside the BufTab is already in use when this
 *              functions is called, it will not be chunked but left as is.
 *              Note that this means that you may have a BufTab with varying
 *              sizes after this call.
 */
extern Int BufTab_chunk(BufTab_Handle hBufTab, Int numBufs, Int32 bufSize);

/**
 * @brief       Restore the BufTab to the state before #BufTab_chunk was
 *              called on it. Note that this will undo any calls to
 *              #BufTab_expand after the #BufTab_chunk call.
 *
 * @param[in]   hBufTab     The #BufTab_Handle to collapse.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #BufTab_create must be called before this function.
 */
extern Int BufTab_collapse(BufTab_Handle hBufTab);

/**
 * @brief       Expand a BufTab with more buffers.
 *
 * @param[in]   hBufTab     The #BufTab_Handle to expand.
 * @param[in]   numBufs     The number of buffers to expand the BufTab with.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #BufTab_create must be called before this function.
 *
 * @remarks     In case a BufTab contains buffers of different sizes (which
 *              is possible after a #BufTab_chunk), the new buffers will be
 *              cloned from the Buffer with the smallest size.
 */
extern Int BufTab_expand(BufTab_Handle hBufTab, Int numBufs);

/**
 * @brief       Return a buffer with a certain index in the BufTab.
 *
 * @param[in]   hBufTab     The #BufTab_Handle to which the buffer belongs.
 * @param[in]   bufIdx      The index of the buffer in the BufTab.
 *
 * @retval      Handle to the buffer matching the supplied index
 *              (see #BufTab_Handle).
 *
 * @remarks     #BufTab_create must be called before this function.
 */
Buffer_Handle BufTab_getBuf(BufTab_Handle hBufTab, Int bufIdx);

/**
 * @brief       Get the number of Buffers in a BufTab.
 *
 * @param[in]   hBufTab     The BufTab of which to get the number of buffers.
 *
 * @retval      "Number of buffers" in the BufTab.
 *
 * @remarks     #BufTab_create must be called before this function.
 */
Int BufTab_getNumBufs(BufTab_Handle hBufTab);

/**
 * @brief       Print information about the buffers in the BufTab.
 *
 * @param[in]   hBufTab     The #BufTab_Handle to print information about.
 *
 * @remarks     #BufTab_create must be called before this function.
 */
extern Void BufTab_print(BufTab_Handle hBufTab);

/**
 * @brief       Mark all buffers in a BufTab as free.
 *
 * @param[in]   hBufTab     The #BufTab_Handle of the BufTab to free.
 *
 * @remarks     #BufTab_create must be called before this function.
 */
extern Void BufTab_freeAll(BufTab_Handle hBufTab);

/**
 * @brief       Mark a Buffer as free in a BufTab
 *
 * @param[in]   hBuf        The #Buffer_Handle of the Buffer to free.
 *
 * @remarks     #BufTab_create must be called before this function.
 */
extern Void BufTab_freeBuf(Buffer_Handle hBuf);

/**
 * @brief       Return a free buffer from the BufTab and mark it as used.
 *
 * @param[in]   hBufTab     The #BufTab_Handle from which to get a buffer.
 *
 * @retval      Handle to a free buffer (see #BufTab_Handle).
 * @retval      NULL for failure.
 *
 * @remarks     #BufTab_create must be called before this function.
 */
extern Buffer_Handle BufTab_getFreeBuf(BufTab_Handle hBufTab);

#if defined (__cplusplus)
}
#endif

/*@}*/

#endif /* ti_sdo_dmai_BufTab_h_ */
