/** ===========================================================================
* @file H264VENC.c
*
* @path $\\(PROJDIR)\\..\\Client\\Test\\Src\\
*
* @desc This file contains implementation for wrapper API functions 
*       for XDAS/XDM APIs
* =============================================================================
* Copyright (c) Texas Instruments Inc 2005, 2006, 2007
*
* Use of this software is controlled by the terms and conditions found
* in the license agreement under which this software has been supplied 
* ===========================================================================*/
/* --------------------- COMPILATION CONTROL SWITCHES -----------------------*/
#pragma CODE_SECTION(H264VENC_create,  ".text:create")
#pragma CODE_SECTION(H264VENC_control, ".text:control")
#pragma CODE_SECTION(H264VENC_delete,  ".text:delete")
#pragma CODE_SECTION(H264VENC_encode,  ".text:encode")

/*****************************************************************************/
/*                              INCLUDE FILES                                */
/*****************************************************************************/
/* ---------------------- SYSTEM AND PLATFORM FILES -------------------------*/
//#define _55_
//#define _67_
#include <xdc/std.h>
#include <ti/xdais/xdas.h>


/*----------------------------- PROGRAM FILES -------------------------------*/
#include <ti/xdais/dm/xdm.h>
//#include "ih264venc.h"
#include "h264venc_tii.h"
#include "h264venc.h"

/*****************************************************************************/
/*     EXTERNAL REFERENCES NOTE : only use if not found in header file       */
/*****************************************************************************/
/*--------------------------- DATA DECLARATIONS -----------------------------*/

/*-------------------------- FUNCTION PROTOTYPES ----------------------------*/

/*****************************************************************************/
/*               PUBLIC DECLARATIONS Defined here, used elsewhere            */
/*****************************************************************************/
/*--------------------------- DATA DECLARATIONS -----------------------------*/

/*-------------------------- FUNCTION PROTOTYPES ----------------------------*/

/*****************************************************************************/
/*              PRIVATE DECLARATIONS Defined here, used only here            */
/*****************************************************************************/

/*--------------------------- DATA DECLARATIONS -----------------------------*/

/*-------------------------- FUNCTION PROTOTYPES ----------------------------*/

/*****************************************************************************/
/*       GLOBAL FUNCTION DEFINITIONS (DEFINED HERE / CALLED ELSEWHERE)       */
/*****************************************************************************/

/*=============================================================================
*@func  H264VENC_create()
*
*@brief Create an H264VENC instance object 
*       using parameters specified by prms)
* 
*@param  fxns  
*        Pointer to the H264VENC interface functions 
*        prms
*        Pointer to H264 encoder extended parameter structure 
*
*@return H264VENC_Handle
*        Handle to the H264 encoder instance object 
*
*@see    None
*
*@note   None
*==============================================================================
*/
H264VENC_Handle H264VENC_create(
    const IH264VENC_Fxns *fxns,
    const H264VENC_Params *prms
)
{
    return (
        (H264VENC_Handle)ALG_create(
            (IALG_Fxns *)fxns,
            NULL, 
            (IALG_Params *)prms
        )
    );

}/* H264VENC_create */



/*=============================================================================
*@func  H264VENC_control()
*
*@brief Get, set, and change the parameters of the H264 encoder
*       (using parameters specified by status).
* 
*@param  handle  
*        Handle to the H264 encoder instance object 
*        cmd
*        Get/Set Command to the H264 encoder.
*        params
*        Pointer to H264 encoder extended dynamic parameter structure 
*        status        
*        Pointer to H264 encoder extended status parameter structure 
*
*@return Error code
*        Handle to the H264 encoder instance object 
*
*@see    None
*
*@note   None
*==============================================================================
*/
Int H264VENC_control(
    H264VENC_Handle handle, 
    H264VENC_Cmd cmd,
    H264VENC_DynamicParams *params, 
    H264VENC_Status *status
)
{
    Int error;
	if(handle == NULL)
	{
		return IVIDENC1_EFAIL;
	}
    ALG_activate((IALG_Handle)handle);
    error = handle->fxns->ividenc1.control(
        (IVIDENC1_Handle)handle,
        (IVIDENC1_Cmd)cmd,
        (IVIDENC1_DynamicParams *)params,
        (IVIDENC1_Status *)status
    );
    ALG_deactivate((IALG_Handle)handle);

    return(error);

}/* H264VENC_control */



/*=============================================================================
*@func  H264VENC_delete()
*
*@brief Deletes the H264 VENC instance object specified by handle
*       (using parameters specified by status).
* 
*@param  handle  
*        Handle to the H.264 encoder instance object 
*
*@return None
*
*@see    None
*
*@note   None
*==============================================================================
*/
Void H264VENC_delete(H264VENC_Handle handle)
{
    ALG_delete((IALG_Handle)handle);
}/* H264VENC_delete */



/*=============================================================================
*@func  H264VENC_encode()
*
*@brief This API is for encoding one video frame.
* 
*@param  handle  
*        Handle to the H.264 encoder instance object 
*        inbufdesc
*        Pointer to the input buffer descriptor structure.
*        outbufdesc
*        Pointer to the output buffer descriptor structure. 
*        inargs        
*        Pointer to the input arguments structure. 
*        outargs
*        Pointer to the output arguments structure.
*
*@return Error code
*
*@see    XDM doc for details of different structures
*
*@note   None
*==============================================================================
*/
Int H264VENC_encode( 
    H264VENC_Handle handle, 
    IVIDEO1_BufDescIn *Input, 
    XDM_BufDesc *Output,
    H264VENC_InArgs *inargs,
    H264VENC_OutArgs *outarg
)
{
    XDAS_Int32 result;
	if(handle == NULL)
	{
		return IVIDENC1_EFAIL;
	}
    ALG_activate((IALG_Handle)handle);
    result = handle->fxns->ividenc1.process(
        (IVIDENC1_Handle)handle,
        Input,
        Output,
        (IVIDENC1_InArgs *)inargs,
        (IVIDENC1_OutArgs *)outarg
    );
    ALG_deactivate((IALG_Handle)handle);

    return(result);
}/* H264VENC_encode */

/*---------------------------------------------------------------------------*/
/*       LOCAL STATIC FUNCTION DEFINATIONS (DEFINED HERE / USED HERE)        */
/*---------------------------------------------------------------------------*/


/*!
*! Revision History
*! ****************
*! 02-10-2007 Sunil Koteyar: Cleaned up file header and function headers
*/
