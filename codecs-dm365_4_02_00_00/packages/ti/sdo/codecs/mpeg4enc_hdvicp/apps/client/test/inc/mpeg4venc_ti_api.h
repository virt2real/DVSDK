/** ===========================================================================
* @file mpeg4venc_ti_api.h
*
* @path $(PROJDIR)\..\Client\\Test\\Inc\\
*
* @desc This File defines interface used by client of the MPEG4 encoder module
* =============================================================================
* Copyright (c) Texas Instruments Inc 2005, 2006, 2007
*
* Use of this software is controlled by the terms and conditions found
* in the license agreement under which this software has been supplied
* ===========================================================================*/

#ifndef __MPEG4VENC_TI_API__
#define __MPEG4VENC_TI_API__

/*****************************************************************************/
/*                              INCLUDE FILES                                */
/*****************************************************************************/

/* ---------------------- SYSTEM AND PLATFORM FILES -------------------------*/

/*----------------------------- PROGRAM FILES -------------------------------*/
//#include "alg.h"
//#include "xdas.h"
#include "ti/xdais/xdas.h"
//#include <std.h>
#include <xdc/std.h>
#include <ti/sdo/fc/utils/api/alg.h>
#include "imp4venc.h"

/*****************************************************************************/
/*               PUBLIC DECLARATIONS Defined here, used elsewhere            */
/*****************************************************************************/

/*--------------------------- DATA DECLARATIONS -----------------------------*/

/*=============================================================================
* MP4VENC_Handle
*
* This pointer is used to reference all MP4VENC instance objects
*==============================================================================
*/
typedef struct IMP4HDVICPENC_Obj *MP4VENC_Handle;

/*=============================================================================
* MP4VENC_Params
*
* This structure defines the creation parameters for all MPEG-4 VENC objects
*==============================================================================
*/
typedef IMP4HDVICPENC_Params MP4VENC_Params;

/*=============================================================================
* MP4VENC_PARAMS
*
* This structure defines default creation parameters for MPEG-4 VENC objects
*==============================================================================
*/
#define MP4VENC_PARAMS   IMPEG4VENC_PARAMS

/*=============================================================================
* MP4VENC_DynamicParams
*
* This structure defines the dynamic parameters for all MP4VENC objects
*==============================================================================
*/
typedef IMP4HDVICPENC_DynamicParams MP4VENC_DynamicParams;

/*=============================================================================
* MP4VENC_Status
*
* This structure defines the status parameters for MP4VENC objects
*==============================================================================
*/
typedef struct IMP4HDVICPENC_Status   MP4VENC_Status;

/*=============================================================================
* MP4VENC_InArgs
*
* This structure defines the real-time input arguments for MP4VENC objects
*==============================================================================
*/
typedef struct IMP4HDVICPENC_InArgs   MP4VENC_InArgs;

/*=============================================================================
* MP4VENC_OutArgs
*
* This structure defines extened output arguments for all MPEG4 VENC objects
*==============================================================================
*/
typedef struct IMP4HDVICPENC_OutArgs MP4VENC_OutArgs;

/*=============================================================================
* MP4VENC_Cmd
*
* This typedef defines the control commands MPEG-4 VENC objects
*==============================================================================
*/
typedef IMP4HDVICPENC_Cmd   MP4VENC_Cmd;

/*--------------------------- MACROS  ---------------------------------------*/
/*=============================================================================
* control method commands
*==============================================================================
*/
#define MP4VENC_GETSTATUS     IMP4HDVICPENC_GETSTATUS
#define MP4VENC_SETPARAMS     IMP4HDVICPENC_SETPARAMS
#define MP4VENC_RESET         IMP4HDVICPENC_RESET
#define MP4VENC_SETDEFAULT    IMP4HDVICPENC_SETDEFAULT
#define MP4VENC_FLUSH         IMP4HDVICPENC_FLUSH
#define MP4VENC_GETBUFINFO    IMP4HDVICPENC_GETBUFINFO


/*-------------------------- FUNCTION PROTOTYPES ----------------------------*/

/*=============================================================================
*@func  MP4VENC_create()
*
*@brief Create an MPEG4 VENC instance object
*       using parameters specified by prms)
*
*@param  fxns
*        Pointer to the MPEG-4 VENC interface functions
*        prms
*        Pointer to MPEG-4 encoder extended parameter structure
*
*@return MP4VENC_Handle
*        Handle to the MPEG-4 encoder instance object
*
*@see    None
*
*@note   None
*==============================================================================
*/
extern MP4VENC_Handle MP4VENC_create( const IMP4HDVICPENC_Fxns *fxns,
                                      const MP4VENC_Params *prms);

/*=============================================================================
*@func  MP4VENC_control()
*
*@brief Get, set, and change the parameters of the MPEG-4 encoder
*       (using parameters specified by status).
*
*@param  handle
*        Handle to the MPEG-4 encoder instance object
*        cmd
*        Get/Set Command to the MPEG-4 encoder.
*        params
*        Pointer to MPEG-4 encoder extended dynamic parameter structure
*        status
*        Pointer to MPEG-4 encoder extended status parameter structure
*
*@return Error code
*        Handle to the MPEG-4 encoder instance object
*
*@see    None
*
*@note   None
*==============================================================================
*/
extern Int MP4VENC_control(MP4VENC_Handle         handle,
                           MP4VENC_Cmd            cmd,
                           MP4VENC_DynamicParams *params,
                           MP4VENC_Status        *status);

/*=============================================================================
*@func  MP4VENC_delete()
*
*@brief Deletes the MPEG-4 VENC instance object specified by handle
*       (using parameters specified by status).
*
*@param  handle
*        Handle to the MPEG-4 encoder instance object
*
*@return None
*
*@see    None
*
*@note   None
*==============================================================================
*/
extern Void MP4VENC_delete(MP4VENC_Handle handle);

/*=============================================================================
*@func  MP4VENC_Encode()
*
*@brief This API is for encoding one video frame.
*
*@param  handle
*        Handle to the MPEG-4 encoder instance object
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
extern Int MP4VENC_Encode(MP4VENC_Handle     handle,
                          IVIDEO1_BufDescIn *inbufdesc ,
                          XDM_BufDesc       *outbufdesc,
                          MP4VENC_InArgs    *inargs,
                          MP4VENC_OutArgs   *outargs);

#endif /* __MPEG4VENC_TI_API__ */

/*!
*! Revision History
*! ================
*! 27-Aug-2007 Prasad RSV : Added function headers and description
*! 23-Jan-2006 Anirban Basu: Created.
*/



