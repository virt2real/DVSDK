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
 * @defgroup   ti_sdo_dmai_Buffer   Buffer
 *
 * @brief Describes a buffer. The other DMAI modules perform
 *        operations on instances of this module. There are submodules of
 *        this module such as BufferGfx which can also use the Buffer
 *        functions. Typical Buffer module usage for a 1KB buffer
 *        (no error checks):
 *
 * @code
 *     #include <xdc/std.h>
 *     #include <ti/sdo/dmai/Dmai.h>
 *     #include <ti/sdo/dmai/Buffer.h>
 *     Buffer_Handle hBuf;
 *     Buffer_Attrs bAttrs = Buffer_Attrs_DEFAULT;
 *     Dmai_init();
 *     hBuf = Buffer_create(1024, &bAttrs);
 *     // Operate on Buffer
 *     Buffer_delete(hBuf);
 * @endcode
 */

#include <xdc/std.h>

#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/dmai/Dmai.h>

/** @ingroup    ti_sdo_dmai_Buffer */
/*@{*/

#ifndef ti_sdo_dmai_Buffer_Defines_
#define ti_sdo_dmai_Buffer_Defines_

/**
 * @brief Types of Buffers.
 */
typedef enum {
    /** @brief The basic Buffer used for e.g. I/O or Sound */
    Buffer_Type_BASIC       = 0,

    /** @brief  The extended graphics Buffer described in BufferGfx */
    Buffer_Type_GRAPHICS    = 1,

    Buffer_Type_COUNT
} Buffer_Type;

/**
 * @brief Attributes used when creating a Buffer instance.
 * @see Buffer_Attrs_DEFAULT
 */
typedef struct Buffer_Attrs {
    /**
      * @brief Parameters used to allocate the buffer using the Codec Engine
      * OSAL Memory module.
      * @see Buffer_Memory_Params_DEFAULT
      */
    Memory_AllocParams      memParams;

    /**
      * @brief The type of buffer to allocate.
      * @see Buffer_Type
      * @see Buffer_getType
      */
    Buffer_Type             type;

    /**
      * @brief The mask to indicate that a buffer is busy in a BufTab (a
      * useMask value of 0 indicates a free buffer). Using a flexible mask
      * allows multiple "owners" of a buffer (e.g. codec and display device
      * driver).
      * @see Buffer_setUseMask
      * @see Buffer_getUseMask
      * @see Buffer_freeUseMask
      * @see Buffer_resetUseMask
      */
    UInt16                  useMask;

    /**
     * @brief If this is set to true no buffer will be allocated, instead
     * the resulting #Buffer_Handle will be a reference to an already existing
     * memory area (@see #Buffer_setUserPtr and #Buffer_setSize).
     */
    Bool                    reference;
} Buffer_Attrs;

/**
 * @brief Handle through which to reference a Buffer instance.
 */
typedef struct _Buffer_Object *Buffer_Handle;

/**
 * @brief The default parameters for the Memory module while creating a Buffer.
 * @code
 * type         = Memory_CONTIGPOOL,
 * flags        = Memory_NONCACHED,
 * align        = Memory_DEFAULTALIGNMENT,
 * seg          = 0
 * @endcode
 */
extern const Memory_AllocParams Buffer_Memory_Params_DEFAULT;

/**
 * @brief The default parameters when creating a Buffer.
 * @code
 * memParams    = Buffer_Memory_Params_DEFAULT,
 * type         = Buffer_Type_BASIC,
 * useMask      = 1
 * reference    = FALSE
 * @endcode
 */
extern const Buffer_Attrs Buffer_Attrs_DEFAULT;

#endif /* ti_sdo_dmai_Buffer_Defines_*/

#ifndef ti_sdo_dmai_Buffer_h_
#define ti_sdo_dmai_Buffer_h_

#include <ti/sdo/dmai/BufTab.h>

#if defined (__cplusplus)
extern "C" {
#endif

/**
 * @brief       Creates and allocates a contiguous Buffer.
 *
 * @param[in]   size        Size in bytes of buffer to create.
 * @param[in]   attrs       #Buffer_Attrs to use for creating the Buffer.
 *
 * @retval      Handle for use in subsequent operations (see #Buffer_Handle).
 * @retval      NULL for failure.
 */
extern Buffer_Handle Buffer_create(Int32 size, Buffer_Attrs *attrs);

/**
 * @brief       Creates and clone of an existing Buffer. Only the attributes
 *              used while creating the cloned Buffer will be used.
 *
 * @param[in]   hBuf        The #Buffer_Handle of the Buffer to clone.
 *
 * @retval      Handle for use in subsequent operations (see #Buffer_Handle).
 * @retval      NULL for failure.
 *
 * @remarks     #Buffer_create or #BufTab_create must be called
 *              before this function.
 */
extern Buffer_Handle Buffer_clone(Buffer_Handle hBuf);

/**
 * @brief       Prints information about a buffer.
 *
 * @param[in]   hBuf        The #Buffer_Handle of the Buffer to print
 *                          information for.
 *
 * @remarks     #Buffer_create or #BufTab_create must be called
 *              before this function.
 */
extern Void Buffer_print(Buffer_Handle hBuf);

/**
 * @brief       Deletes and frees a contiguous Buffer.
 *
 * @param[in]   hBuf        The #Buffer_Handle of the Buffer to delete.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Buffer_create or #BufTab_create must be called
 *              before this function.
 */
extern Int Buffer_delete(Buffer_Handle hBuf);

/**
 * @brief       Get the #Buffer_Attrs corresponding to existing buffer.
 *
 * @param[in]   hBuf        The #Buffer_Handle to match #Buffer_Attrs for.
 * @param[out]  attrs       The #Buffer_Attrs structure to fill in.
 *
 * @remarks     #Buffer_create or #BufTab_create must be called
 *              before this function.
 */
extern Void Buffer_getAttrs(Buffer_Handle hBuf, Buffer_Attrs *attrs);

/**
 * @brief       Set the current use mask.
 *
 * @param[in]   hBuf        The #Buffer_Handle to set the use mask for.
 * @param[in]   useMask     The useMask to set.
 *
 * @remarks     #Buffer_create or #BufTab_create must be called
 *              before this function.
 */
extern Void Buffer_setUseMask(Buffer_Handle hBuf, UInt16 useMask);

/**
 * @brief       Free bits in the current use mask. When the resulting use mask
 *              is 0, the Buffer is considered free.
 *
 * @param[in]   hBuf        The #Buffer_Handle to free the use mask of.
 * @param[in]   useMask     The use mask to strip using
 *                          "BufferUseMask &= ~useMask";
 *
 * @remarks     #Buffer_create or #BufTab_create must be called
 *              before this function.
 */
extern Void Buffer_freeUseMask(Buffer_Handle hBuf, UInt16 useMask);

/**
 * @brief       Set the current use mask to the original use mask, essentially
 *              marking the Buffer as busy.
 *
 * @param[in]   hBuf        The #Buffer_Handle to reset.
 *
 * @remarks     #Buffer_create or #BufTab_create must be called
 *              before this function.
 */
extern Void Buffer_resetUseMask(Buffer_Handle hBuf);

/**
 * @brief       Get the current use mask of a Buffer.
 *
 * @param[in]   hBuf        The #Buffer_Handle to get the current use mask of.
 *
 * @retval      useMask of the Buffer.
 *
 * @remarks     #Buffer_create or #BufTab_create must be called
 *              before this function.
 */
extern UInt16 Buffer_getUseMask(Buffer_Handle hBuf);

/**
 * @brief       Get the id of a Buffer. The id identifies a Buffer in a BufTab.
 *
 * @param[in]   hBuf        The #Buffer_Handle to get the id of.
 *
 * @retval      id of the Buffer.
 *
 * @remarks     #Buffer_create or #BufTab_create must be called
 *              before this function.
 */
extern Int Buffer_getId(Buffer_Handle hBuf);

/**
 * @brief       Get the user pointer of the Buffer. This pointer can be used
 *              to access the Buffer using the CPU.
 *
 * @param[in]   hBuf        The #Buffer_Handle to get the user pointer of.
 *
 * @retval      "User pointer" of the Buffer.
 *
 * @remarks     #Buffer_create or #BufTab_create must be called
 *              before this function.
 */
extern Int8 *Buffer_getUserPtr(Buffer_Handle hBuf);

/**
 * @brief       Get the physical pointer of the Buffer. This pointer can be used
 *              by device drivers and DMA to access the Buffer.
 *
 * @param[in]   hBuf        The #Buffer_Handle to get the user pointer of.
 *
 * @retval      "Physical pointer" of the Buffer.
 *
 * @remarks     You should not use this pointer in your application directly.
 *
 * @remarks     #Buffer_create or #BufTab_create must be called
 *              before this function.
 */
extern Int32 Buffer_getPhysicalPtr(Buffer_Handle hBuf);

/**
 * @brief       Get the size of a Buffer.
 *
 * @param[in]   hBuf        The #Buffer_Handle to get the size of.
 *
 * @retval      Size of the Buffer.
 *
 * @remarks     #Buffer_create or #BufTab_create must be called
 *              before this function.
 */
extern Int32 Buffer_getSize(Buffer_Handle hBuf);

/**
 * @brief       Get the type of a Buffer.
 *
 * @param[in]   hBuf        The #Buffer_Handle to get the type of.
 *
 * @retval      Type of the Buffer (see #Buffer_Type).
 *
 * @remarks     #Buffer_create or #BufTab_create must be called
 *              before this function.
 */
extern Buffer_Type Buffer_getType(Buffer_Handle hBuf);

/**
 * @brief       When a DMAI module has processed data and written it to a
 *              Buffer, it records the actual number of bytes used (which may
 *              or may not be the same as the size).
 *
 * @param[in]   hBuf        The #Buffer_Handle to get the number of bytes
 *                          used of.
 *
 * @retval      "Number of bytes used" in the Buffer.
 *
 * @remarks     A DMAI processing function or #Buffer_setNumBytesUsed() should
 *              be used on this module before calling this function.
 * @remarks     #Buffer_create or #BufTab_create must be called
 *              before this function.
 */
extern Int32 Buffer_getNumBytesUsed(Buffer_Handle hBuf);

/**
 * @brief       Set the number of bytes used in a Buffer. If you process data
 *              outside of DMAI, call this function to tell the DMAI modules
 *              how many bytes it should process in the Buffer.
 *
 * @param[in]   hBuf        The #Buffer_Handle to set the number of bytes
 *                          used for.
 * @param[in]   numBytes    The number of bytes used in the Buffer.
 *
 * @remarks     #Buffer_create or #BufTab_create must be called
 *              before this function.
 */
extern Void Buffer_setNumBytesUsed(Buffer_Handle hBuf, Int32 numBytes);

/**
 * @brief       Set the User pointer for a Buffer reference.
 *
 * @param[in]   hBuf        The #Buffer_Handle to set the pointer for. Needs
 *                          to have been created as a reference (see
 *                          #Buffer_Attrs.reference.
 * @param[in]   ptr         Pointer to set.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     The Buffer instance passed need to having been created as a
 *              reference, see #Buffer_Attrs.reference.
 * @remarks     #Buffer_create or #BufTab_create must be called
 *              before this function.
 */
extern Int Buffer_setUserPtr(Buffer_Handle hBuf, Int8 *ptr);

/**
 * @brief       Set the size of a Buffer reference.
 *
 * @param[in]   hBuf        The #Buffer_Handle to set the pointer for. Needs
 *                          to have been created as a reference (see
 *                          #Buffer_Attrs.reference.
 * @param[in]   size        Size to set.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     The Buffer instance passed need to having been created as a
 *              reference, see #Buffer_Attrs.reference.
 * @remarks     #Buffer_create or #BufTab_create must be called
 *              before this function.
 */
extern Int Buffer_setSize(Buffer_Handle hBuf, Int32 size);

/**
 * @brief       Set the virtual size of a Buffer.
 *
 * @param[in]   hBuf        The #Buffer_Handle to set the pointer for. Needs
 *                          to have been created as a reference (see
 *                          #Buffer_Attrs.reference.
 * @param[in]   size        Size to set.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     The Buffer instance passed need to having been created as a
 *              reference, see #Buffer_Attrs.reference.
 * @remarks     #Buffer_create or #BufTab_create must be called
 *              before this function.
 * @remarks     This API as temporary workaround to handle disjoined buffers.
 *              It will become obsolete, once PSP supports multiple buffer planes,
 *              and DMAI makes corresponding changes.
 */
extern Int Buffer_setVirtualSize(Buffer_Handle hBuf, Int32 size);

/**
 * @brief       Investigate whether a Buffer instance is a reference or not.
 *
 * param[in]    hBuf        The #Buffer_Handle to investigate.
 *
 * @retval      TRUE if the Buffer instance is a reference.
 * @retval      FALSE if not.
 */
extern Bool Buffer_isReference(Buffer_Handle hBuf);

/**
 * @brief       Get the BufTab instance which a Buffer belongs to, if any.
 *
 * @param[in]   hBuf        Get the #BufTab_Handle of the BufTab this
 *                          Buffer belong to, if any.
 *
 * @retval      BufTab_Handle of the BufTab instance a Buffer belongs to.
 * @retval      NULL if the Buffer does not belong to a BufTab.
 */
extern BufTab_Handle Buffer_getBufTab(Buffer_Handle hBuf);

/**
 * @brief       Copies Buffer object from source to destination.
 *
 * @param[in]   hSrcBuf        The #Buffer_Handle of the Buffer to copy.
 * @param[out]  hDstBuf        The #Buffer_Handle of the destination Buffer.
 *
 * @remarks     The destination Buffer will become a reference buffer and
 *              can be safely freed using #Buffer_delete.
 * @remarks     The buffer pointed to by the destination Buffer object will
 *              be freed before the copy occurs.
 */
extern Int Buffer_copy(Buffer_Handle hSrcBuf, Buffer_Handle hDstBuf);


#if defined (__cplusplus)
}
#endif

/*@}*/

#endif /* ti_sdo_dmai_Buffer_h_ */
