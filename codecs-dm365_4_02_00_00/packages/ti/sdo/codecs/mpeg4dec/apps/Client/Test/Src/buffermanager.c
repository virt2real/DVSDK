/** ===========================================================================
* @file buffermanager.c
*
* @path $(PROJDIR)\src
*
* @brief This File contains function definitions which implements a sample
*            buffer management algorithm for integrating with XDM 1.0 compliant
*            video decoder.  
* =============================================================================
* Copyright (c) Texas Instruments Inc 2006, 2007
*
* Use of this software is controlled by the terms and conditions found
* in the license agreement under which this software has been supplied
**============================================================================*/
/* ------compilation control switches -------------------------*/
/***************************************************************
*  INCLUDE FILES                                                
****************************************************************/
/* ----- system and platform files ----------------------------*/
//#include "cmem.h"
#include "buffermanager.h"
#include "TestAppDecoder.h"

#ifdef LINUX
#include <ti/sdo/linuxutils/cmem/include/cmem.h>
#endif

/***************************************************************
*  EXTERNAL REFERENCES NOTE : only use if not found in header file
****************************************************************/
/*--------data declarations -----------------------------------*/
/*--------function prototypes ---------------------------------*/
/****************************************************************
*  PUBLIC DECLARATIONS Defined here, used elsewhere
****************************************************************/
/*--------data declarations -----------------------------------*/

BUFFMGR_buffEle buffArray[MAX_BUFF_ELEMENTS];
XDAS_UInt8 *GlobalBufferHandle = NULL;
XDAS_UInt32 GlobalBufferSize;

#ifndef LINUX
extern XDAS_Int8 outputData[OUTPUT_BUFFER_SIZE];
#endif

#ifdef LINUX
    CMEM_AllocParams memParams_out= {
	                            CMEM_POOL,
				    			CMEM_NONCACHED,
				    			256
                                    };
#endif

/*--------function prototypes ---------------------------------*/
/****************************************************************
*  PRIVATE DECLARATIONS Defined here, used only here
****************************************************************/
/*--------data declarations -----------------------------------*/
/*--------function prototypes ---------------------------------*/
/*--------macros ----------------------------------------------*/
/*--------function definitions---------------------------------*/
/*****************************************************************************/
/**
*@func BUFFMGR_Init()
*@brief  TI's (Texas Instrument) implementation of buffer manager 
*       initialization module
*
*        The BUFFMGR_Init function is called by the test application to
*        initialise the global buffer element array to default and to allocate
*        required number of memory data for reference and output buffers.
*        The maximum required dpb size is defined by the supported profile & 
*        level.
*
*@param  totBufSize
*        Total buffer size to be allocated
*
*@return Success(0)/failure(-1) in allocating and initialising
*
*/
/*****************************************************************************/
XDAS_Int32 BUFFMGR_Init(XDAS_Int32 totBufSize)
{
    XDAS_UInt32 tmpCnt;
    /* total buffer size allocatable is divided into three parts one part goes 
     * to luma buffers and the other two parts go to luma buffers */
    
   GlobalBufferSize = totBufSize;
    
   GlobalBufferHandle = NULL ;

   if(GlobalBufferHandle == NULL)
    {
        /* Allocate the global buffers */

#ifdef LINUX
	GlobalBufferHandle = CMEM_alloc(GlobalBufferSize,&memParams_out);
#else
      
        GlobalBufferHandle = malloc(GlobalBufferSize*sizeof(char));
#endif

        if(GlobalBufferHandle == NULL)
        {
            return -1;
        }
    }    

    /* Initialise the elements in the global buffer array */
    for(tmpCnt = 0; tmpCnt < MAX_BUFF_ELEMENTS; tmpCnt++)
    {
        buffArray[tmpCnt].bufId = tmpCnt+1;
        buffArray[tmpCnt].bufStatus = BUFFMGR_BUFFER_FREE;
        buffArray[tmpCnt].bufSize[0] = 0;
        buffArray[tmpCnt].buf[0] = NULL;
    }
    
    /* Initialise the entire buffer space to first frame and 
     * re-modify buffer sizes as per the picture frame sizes 
     * after first frame decode */

     buffArray[0].buf[0] = GlobalBufferHandle;
     buffArray[0].bufSize[0] = GlobalBufferSize;
     return 0;
}


/*****************************************************************************/
/**
*@func BUFFMGR_ReInit()
*@brief  TI's (Texas Instrument) implementation of buffer manager 
*       re-initialization module
*
*        The BUFFMGR_ReInit function allocates global luma and chroma buffers
*       and allocates entire space to first element. This element will be used 
*       in first frame decode. After the picture's height and width and its luma 
*       and chroma buffer requirements are obtained the global luma and chroma
*       buffers are re-initialised to other elements in teh buffer arary. 
*
*@param  lumaOneFrameBufSize
*        Buffer size for one luma frame in bytes
*
*@param  chromaOneFrameBufSize
*        Buffer size for one chroma frame in bytes
*
*@return Success(0)/failure(-1) in allocating and initialising
*
*/
/*****************************************************************************/
XDAS_Int32 BUFFMGR_ReInit(XDAS_Int32 lumaOneFrameBufSize,
                              XDAS_Int32 chromaOneFrameBufSize)
{
  
    return 0;
}


/*****************************************************************************/
/**
*@func BUFFMGR_GetFreeBuffer()
*@brief  TI's (Texas Instrument) implementation of buffer manager 
*       re-initialization module
*
*        The BUFFMGR_GetFreeBuffer function searches for a free buffer in the 
*        global buffer array and returns the address of that element. Incase
*        if none of the elements are free then it returns NULL
*
*
*@return Valid buffer element address or NULL incase if no buffers are empty
*
*/
/*****************************************************************************/
BUFFMGR_buffEleHandle BUFFMGR_GetFreeBuffer()
{
    XDAS_UInt32 tmpCnt;
    /* Since buffers are re-initialised later on its perfectly possible to 
     * have buffer elements with NULL as the buffer pointers - as soon as 
     * such buffer elements are encountered we need to stop search for 
     * free buffers 
     */
    for(tmpCnt = 0; 
        (tmpCnt < MAX_BUFF_ELEMENTS) && (buffArray[tmpCnt].buf[0] != NULL); 
        tmpCnt++)
    {
        /* Check for first empty buffer in the array and return its address */
        if(buffArray[tmpCnt].bufStatus == BUFFMGR_BUFFER_FREE)
        {
            buffArray[tmpCnt].bufStatus = BUFFMGR_BUFFER_USED;
            return (&buffArray[tmpCnt]);
        }
    }    
    printf("Run short of frames !!\n");
    /* Incase if no elements in the array are free then return NULL */
    return NULL;
}


/*****************************************************************************/
/**
*@func BUFFMGR_ReleaseBuffer(buffId)
*@brief  TI's (Texas Instrument) implementation of buffer manager 
*       re-initialization module
*
*        The BUFFMGR_ReleaseBuffer function takes an array of buffer-ids
*        which are released by the test-app. "0" is not a valid buffer Id
*        hence this function keeps moving until it encounters a buffer Id 
*        as zero or it hits the MAX_BUFF_ELEMENTS
*
*
*@return None
*
*/
/*****************************************************************************/
void BUFFMGR_ReleaseBuffer(XDAS_UInt32 bufffId[])
{
    XDAS_UInt32 tmpCnt, tmpId;
    for(tmpCnt = 0; 
        (tmpCnt < MAX_BUFF_ELEMENTS); 
        tmpCnt++)
    {
        tmpId = bufffId[tmpCnt];
        /*
         * Check if the buffer Id = 0 condition has reached. zero is not a 
         * valid buffer Id hence that value is used to identify the end of 
         * buffer array
         */
        if(tmpId == 0)
        {
           break;
        }
        /* 
         * convert the buffer-Id to its corresponding index in the global 
         * array 
         */
        tmpId--;

        if(tmpId >= MAX_BUFF_ELEMENTS) {
        /* Inidcates an invalid buffer Id passed - this buffer Id can be 
         * ignored!! alternatively we can break here.
         */
         printf("Trying to release a buffer using an invalid bufferId %d \
                  ignoring..\n", tmpId+1);
         continue;
        }
        if(buffArray[tmpId].bufStatus == BUFFMGR_BUFFER_FREE) {
        /* Trying to release an already free bufffer this idicates some mismanagement 
         * in buffer usage following printf will help application developer to identify 
         * any such problem in her algorithm
         */
         printf("Trying to release an already free buffer Id %d \n", tmpId+1);
        }
        /* Set the status of the buffer to FREE */
        buffArray[tmpId].bufStatus = BUFFMGR_BUFFER_FREE;
    }    
#ifdef _DBG_VERBOSE
    printf("Currrently locked buffers after release are: ");
    for(tmpCnt = 0; 
        (tmpCnt < MAX_BUFF_ELEMENTS); 
        tmpCnt++)
    {
        if(buffArray[tmpCnt].bufStatus != BUFFMGR_BUFFER_FREE &&
            buffArray[tmpCnt].buf[1] != NULL) {
            printf("%d, ", tmpCnt+1);
        }
    }
    printf("- \n");
#endif
    return;
}

/*****************************************************************************/
/**
*@func BUFFMGR_DeInit()
*@brief  TI's (Texas Instrument) implementation of buffer manager 
*       re-initialization module
*
*        The BUFFMGR_DeInit function releases all memory allocated by buffer 
*           manager.
*
*@return None
*
*/
/*****************************************************************************/
void BUFFMGR_DeInit()
{
    if(GlobalBufferHandle)
#ifdef LINUX      
        CMEM_free(GlobalBufferHandle,&memParams_out);
#else
        free(GlobalBufferHandle);
#endif   
    return;
}
/*!
*! Revision History
*! ================
*! 31-May-2007   Vinay: Modified to comply with coding guidelines.
*! 15-May-2007 Vinay M K  : Created.
*/
