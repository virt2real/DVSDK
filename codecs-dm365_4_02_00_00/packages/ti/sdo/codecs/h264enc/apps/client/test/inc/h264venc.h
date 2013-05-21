/** ===========================================================================
* @file H264VENC.h
*
* @path $(PROJDIR)\..\Client\\Test\\Inc\\
*
* @desc This File definesinterface used by clients of the H264VENC module
* =============================================================================
* Copyright (c) Texas Instruments Inc 2005, 2006, 2007
*
* Use of this software is controlled by the terms and conditions found
* in the license agreement under which this software has been supplied 
* ===========================================================================*/

#ifndef __H264VENC__
#define __H264VENC__

/*****************************************************************************/
/*                              INCLUDE FILES                                */
/*****************************************************************************/
/* ---------------------- SYSTEM AND PLATFORM FILES -------------------------*/
/*----------------------------- PROGRAM FILES -------------------------------*/
#include <ti/sdo/fc/utils/api/alg.h>
#include <ti/xdais/xdas.h>
#include "ih264venc.h"

/*****************************************************************************/
/*               PUBLIC DECLARATIONS Defined here, used elsewhere            */
/*****************************************************************************/
/*--------------------------- DATA DECLARATIONS -----------------------------*/

/*===========================================================================
* H264VENC_Handle
*
* This pointer is used to reference all H264VENC instance objects
*==============================================================================
*/
typedef struct IH264VENC_Obj *H264VENC_Handle;

/*=============================================================================
* H264VENC_Params
*
* This structure defines the creation parameters for all H264VENC objects
*==============================================================================
*/
typedef IH264VENC_Params H264VENC_Params;

/*=============================================================================
* IH264VENC_PARAMS
*
* This structure defines default creation parameters for H264VENC objects
*==============================================================================
*/
#define H264VENC_PARAMS   IH264VENC_PARAMS

/*=============================================================================
* H264VENC_DynamicParams
*
* This structure defines the dynamic parameters for all H264VENC objects
*==============================================================================
*/
typedef IH264VENC_DynamicParams H264VENC_DynamicParams;

#define VUIPARAMSBUFFER   VUIPARAMBUFFER

// rrr : CUSTOMSCALINGMATRIX
#define CUSTOMSEQSCALEMATRICES CUSTOMSCALINGMATRIX

/*=============================================================================
* H264VENC_Status
*
* This structure defines the status parameters for H264VENC objects
*==============================================================================
*/
typedef struct IH264VENC_Status   H264VENC_Status;

/*=============================================================================
* H264VENC_InArgs
*
* This structure defines the real-time input arguments for H264VENC objects
*==============================================================================
*/
typedef struct IH264VENC_InArgs   H264VENC_InArgs;

/*=============================================================================
* H264VENC_OutArgs
*
* This structure defines extened output arguments for all H264VENC objects
*==============================================================================
*/
typedef struct IH264VENC_OutArgs H264VENC_OutArgs;

/*=============================================================================
* H264VENC_Cmd
*
* This typedef defines the control commands H264VENC objects
*==============================================================================
*/
typedef IH264VENC_Cmd   H264VENC_Cmd;

/*--------------------------- MACROS  ---------------------------------------*/
/*=============================================================================
* control method commands
*==============================================================================
*/
#define H264VENC_GETSTATUS     IH264VENC_GETSTATUS
#define H264VENC_SETPARAMS     IH264VENC_SETPARAMS
#define H264VENC_RESET         IH264VENC_RESET
#define H264VENC_SETDEFAULT    IH264VENC_SETDEFAULT
#define H264VENC_FLUSH         IH264VENC_FLUSH
#define H264VENC_GETBUFINFO    IH264VENC_GETBUFINFO


/*-------------------------- FUNCTION PROTOTYPES ----------------------------*/
/*=============================================================================
*@func  H264VENC_create()
*
*@brief Create an H.264 VENC instance object 
*       using parameters specified by prms)
* 
*@param  fxns  
*        Pointer to the H.264 VENC interface functions 
*        prms
*        Pointer to H.264 encoder extended parameter structure 
*
*@return MP4VENC_Handle
*        Handle to the H.264 encoder instance object 
*
*@see    None
*
*@note   None
*==============================================================================
*/
extern H264VENC_Handle H264VENC_create(
	const IH264VENC_Fxns *fxns,
	const H264VENC_Params *prms
);

/*=============================================================================
*@func  H264VENC_control()
*
*@brief Get, set, and change the parameters of the H.264 encoder
*       (using parameters specified by status).
* 
*@param  handle  
*        Handle to the H.264 encoder instance object 
*        cmd
*        Get/Set Command to the H.264 encoder.
*        params
*        Pointer to H.264 encoder extended dynamic parameter structure 
*        status        
*        Pointer to H.264 encoder extended status parameter structure 
*
*@return Error code
*        Handle to the H.264 encoder instance object 
*
*@see    None
*
*@note   None
*==============================================================================
*/
extern Int H264VENC_control(
	H264VENC_Handle handle,
	H264VENC_Cmd cmd,
	H264VENC_DynamicParams *, 
	H264VENC_Status *status
);

/*=============================================================================
*@func  H264VENC_delete()
*
*@brief Deletes the H.264 VENC instance object specified by handle
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
extern Void H264VENC_delete(H264VENC_Handle handle);

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
extern Int H264VENC_encode(
	H264VENC_Handle handle,
	IVIDEO1_BufDescIn *,
	XDM_BufDesc *,
	H264VENC_InArgs *,
	H264VENC_OutArgs *
);


#endif /* __H264VENC__ */

/*!
*! Revision History
*! ================
*! 02-10-2007 Sunil Koteyar: Cleaned up headers
*! 23-01-2006 Anirban Basu: Created.
*/




