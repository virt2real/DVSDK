/** ===========================================================================
* @file bufffermanager.h
*
* @path $(PROJDIR)\src
*
* @brief This File contains function definitions which implements a sample
*             buffer management  algorithm for XDm 1.0 compliance on the test-app
*            side.
* =============================================================================
* Copyright (c) Texas Instruments Inc 2006, 2007
*
* Use of this software is controlled by the terms and conditions found
* in the license agreement under which this software has been supplied
**============================================================================*/
/* ------compilation control switches -------------------------*/
#ifndef BUFFMANAGER_H_
#define BUFFMANAGER_H_
/***************************************************************
*  INCLUDE FILES
****************************************************************/
/* ----- system and platform files ----------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <xdc/std.h>
//#include <xdas.h>
//#include <tistdtypes.h>
#include <ti/xdais/xdas.h>
/*-------program files ----------------------------------------*/
/***************************************************************
*  EXTERNAL REFERENCES NOTE : only use if not found in header file
****************************************************************/
/*--------data declarations -----------------------------------*/
/*--------function prototypes ---------------------------------*/
/****************************************************************
*  PUBLIC DECLARATIONS Defined here, used elsewhere
****************************************************************/
/*--------macros ----------------------------------------------*/
/* Maximum number of buffer elements this module can support
 * This macro is should be greater than or equal to total buffer
 * size [given for buffer init] / buffer size per frame [given in
 * reinit function]
 */
#define MAX_BUFF_ELEMENTS 4
/*--------data declarations -----------------------------------*/
/**
 *  @brief      Status of the buffer elements.
 */
typedef enum {
    BUFFMGR_BUFFER_FREE = 0,
    BUFFMGR_BUFFER_USED = 1
} BUFFMGR_BufferStatus;

/**
 *  @brief      Definition of buffer element in the buffer array.
 *            every time a new buffer is requested buffer manager
 *            module returns a pointer to one of the elements
 *            defined below from the buffer array
 */
typedef struct BuffEle
{
    /*! Unique Id which identifies the buffer element */
    XDAS_UInt32 bufId;
    /*! Status of the buffer element: can be either free for allocation or
     * held by the codec and cannot be allocated */
    BUFFMGR_BufferStatus bufStatus;
    /*! Size of buffer members held by this buffer element in bytes */
    XDAS_UInt32 bufSize[2];
    /*! buffer members which contain the address of the actual buffers
     * represented by this buffer element */
    XDAS_UInt8 *buf[2];
} BUFFMGR_buffEle;

typedef BUFFMGR_buffEle* BUFFMGR_buffEleHandle;

extern BUFFMGR_buffEle buffArray[MAX_BUFF_ELEMENTS];
/*--------function prototypes ---------------------------------*/
/**
*@func BUFFMGR_Init()
*        The BUFFMGR_Init function is called by the test application to
*        initialise the global buffer element array to default and to allocate
*        required number of memory data for reference and output buffers.
*        The maximum required dpb size is defined by the supported profile &
*        level.
*/
extern XDAS_Int32 BUFFMGR_Init(XDAS_Int32 totBufSize);

/**
*@func BUFFMGR_ReInit()
*        The BUFFMGR_ReInit function allocates global luma and chroma buffers
*       and allocates entire space to first element. This element will be used
*       in first frame decode. After the picture's height and width and its luma
*       and chroma buffer requirements are obtained the global luma and chroma
*       buffers are re-initialised to other elements in teh buffer arary.
*/
extern XDAS_Int32 BUFFMGR_ReInit(XDAS_Int32 lumaOneFrameBufSize,
                              XDAS_Int32 chromaOneFrameBufSize);
/**
*@func BUFFMGR_GetFreeBuffer()
*        The BUFFMGR_GetFreeBuffer function searches for a free buffer in the
*        global buffer array and returns the address of that element. Incase
*        if none of the elements are free then it returns NULL
*/
extern BUFFMGR_buffEleHandle BUFFMGR_GetFreeBuffer();

/**
*@func BUFFMGR_ReleaseBuffer(buffId)
*        The BUFFMGR_ReleaseBuffer function takes an array of buffer-ids
*        which are released by the test-app. "0" is not a valid buffer Id
*        hence this function keeps moving until it encounters a buffer Id
*        as zero or it hits the MAX_BUFF_ELEMENTS
*/
extern void BUFFMGR_ReleaseBuffer(XDAS_UInt32 bufffId[]);

/**
*@func BUFFMGR_DeInit()
*        The BUFFMGR_DeInit function releases all memory allocated by buffer
*           manager.
*/
extern void BUFFMGR_DeInit();

#endif /* BUFFMANAGER_H_ */
/*!
*! Revision History
*! ================
*!
*! 31-May-2007 Vinay M K: Modified to comply with MMCodecs
*!                        coding guidelines.
*! 15-May-2007 Vinay M K: Initial version created.
*/
