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
 * @defgroup   ti_sdo_dmai_Loader   Loader
 *
 * @brief Implements an elementary stream file loader. Typical usage
 *        (MPEG2, no error checking):
 *
 * @code
 *   #include <xdc/std.h>
 *   #include <ti/sdo/dmai/Dmai.h>
 *   #include <ti/sdo/dmai/Buffer.h>
 *   #include <ti/sdo/dmai/Loader.h>
 *   Loader_Attrs lAttrs = Loader_Attrs_DEFAULT;
 *   Loader_Handle hLoader;
 *   Buffer_Handle hBuf;
 *
 *   Dmai_init();
 *   hLoader = Loader_create("myfile.m2v", &lAttrs);
 *   Loader_prime(hLoader, &hBuf);
 *   while (1) {
 *       // Call Vdec or Vdec2 to decode the elementary stream.
 *       Loader_getFrame(hLoader, hBuf);
 *
 *       if (Buffer_getUserPtr(hBuf) == NULL) {
 *           // There is no more data to read, terminate.
 *           break;
 *       }
 *   }
 *   Loader_delete(hLoader);
 * @endcode
 */
#ifndef ti_sdo_dmai_Loader_h_
#define ti_sdo_dmai_Loader_h_

#include <xdc/std.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Buffer.h>

/** @ingroup    ti_sdo_dmai_Loader */
/*@{*/

/**
 * @brief Attributes used to create a Loader.
 * @see Loader_Attrs_DEFAULT.
 */
typedef struct Loader_Attrs {
    /** @brief Size of the read buffer in bytes, needs to be 2xreadSize (??) */
    UInt32       readBufSize;

    /**
     * @brief Size of the "window" in bytes. This amount of data will always
     * be made available (if possible). When used with an elementary stream
     * decoder this needs to be the size of the minum sized encoded frame.
     */
    UInt32       readSize;

    /**
      * @brief In the asynchronous case the thread calling #Loader_readData
      * may want to load further in advance of the window, and this parameter
      * lets you specify the amount of bytes in advance to read. This parameter
      * is ignored in the synchronous case.
      */
    UInt32       readAhead;

    /**
      * @brief Some platforms may benefit from tweaking the stdio buffer size
      * using setvbuf. This parameter allows tweaking the size of this
      * buffer. If set to 0, no setvbuf call will be made.
      */
    UInt32       vBufSize;

    /**
      * @brief When set to TRUE, this enables asynchronous mode in the Loader
      * module. This is used to parallellize the I/O with the processing, and
      * is achieved by calling #Loader_readData in a separate thread from
      * #Loader_getFrame.
      */
    Int          async;
    
    /**
      * @brief Memory allocation parameters used to allocate the read buffer 
      * of the Loader.
      */                
    Memory_AllocParams  mParams;
    
} Loader_Attrs;

/**
 * @brief Default attributes for a Loader.
 * @code
 *     readBufSize      = 3 * 1024 * 1024,
 *     readSize         = 720 * 576 * 2
 *     readAhead        = 0
 *     vBufSize         = 0
 *     async            = FALSE
 * @endcode
 */
extern const Loader_Attrs Loader_Attrs_DEFAULT;

/**
 * @brief Handle through which to reference a Loader.
 */
typedef struct Loader_Object *Loader_Handle;

#if defined (__cplusplus)
extern "C" {
#endif

/**
 * @brief       Creates a Loader.
 *
 * @param[in]   fileName    Name of the file to load data from.
 * @param[in]   attrs       #Loader_Attrs to use for creating the Loader.
 *
 * @retval      Handle for use in subsequent operations (see #Loader_Attrs).
 * @retval      NULL for failure.
 */
extern Loader_Handle Loader_create(Char *fileName, Loader_Attrs *attrs);

/**
 * @brief       Prime the loader and obtain the first frame.
 *
 * @param[in]   hLoader     The #Loader_Handle to prime.
 * @param[out]  hBufPtr     The buffer containing an encoded frame
 *                          will be returned in this #Buffer_Handle.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Loader_create must be called before this function.
 */
extern Int Loader_prime(Loader_Handle hLoader, Buffer_Handle *hBufPtr);

/**
 * @brief       Read more data in to the ring buffer. This call should be used
 *              when the Loader module works in asynchronous mode
 *              (@see #Loader_Attrs.async). In synchronous mode this call
 *              should @b not be used, it's called internally by
 *              #Loader_getFrame for this configuration.
 *
 * @param[in]   hLoader     The #Loader_Handle to read data for.
 *
 * @retval      Dmai_EOK for success.
 * @retval      Dmai_EEOF if end of file was encountered.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Loader_create must be called before this function.
 * @remarks     This function should @b not be used in synchronous mode
 *              (see #Loader_Attrs.async).
 */
extern Int Loader_readData(Loader_Handle hLoader);

/**
 * @brief       Load the next frame.
 *
 * @param[in]   hLoader     The #Loader_Handle to load from.
 * @param[in]   hBuf        The #Buffer_Handle of the buffer previously
 *                          returned by #Loader_prime. The bytes used
 *                          set by #Buffer_setNumBytesUsed and obtained using
 *                          #Buffer_getNumBytesUsed should be previously updated
 *                          by the decoder, e.g. using a #Vdec2_process call.
 *                          When no more data is available (end of file) the
 *                          #Buffer_getUserPtr call will return NULL for this
 *                          buffer and the function will return Dmai_EEOF.
 *
 * @retval      Dmai_EOK for success.
 * @retval      Dmai_EEOF if end of file was encountered.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Loader_create must be called before this function.
 * @remarks     #Loader_prime must be called before this function.
 */
extern Int Loader_getFrame(Loader_Handle hLoader, Buffer_Handle hBuf);

/**
 * @brief       Tells the thread calling #Loader_readData that it should quit.
 *              If the Loader is not used in async mode this call has no
 *              effect.
 *
 * @param[in]   hLoader     The #Loader_Handle to force.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Loader_create must be called before this function.
 * @remarks     #Loader_delete should be called after this function, the
 *              Loader instance cannot be used with other API calls after this.
 * @remarks     This function should be called from the thread calling
 *              #Loader_getFrame and not the thread calling #Loader_readData.
 */
extern Int Loader_flush(Loader_Handle hLoader);

/**
 * @brief       Deletes a Loader.
 *
 * @param[in]   hLoader     The #Loader_Handle to delete.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Loader_create must be called before this function.
 */
extern Int Loader_delete(Loader_Handle hLoader);

#if defined (__cplusplus)
}
#endif

/*@}*/

#endif /* ti_sdo_dmai_linux_Loader_h_ */
