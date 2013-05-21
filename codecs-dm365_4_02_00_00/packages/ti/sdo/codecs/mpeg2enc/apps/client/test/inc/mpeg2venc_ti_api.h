/** ===========================================================================
* @file mpeg2venc_ti_api.h
*
* @path $(PROJDIR)\..\Client\\Test\\Inc\\
*
* @desc This File defines interface used by client of the MPEG2 encoder module
* =============================================================================
* Copyright (c) Texas Instruments Inc 2005, 2006, 2007
*
* Use of this software is controlled by the terms and conditions found
* in the license agreement under which this software has been supplied
* ===========================================================================*/

#ifndef __MPEG2VENC_TI_API__
#define __MPEG2VENC_TI_API__

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
#include "imp2venc.h"

/*****************************************************************************/
/*               PUBLIC DECLARATIONS Defined here, used elsewhere            */
/*****************************************************************************/

/*--------------------------- DATA DECLARATIONS -----------------------------*/

/*=============================================================================
* MP2VENC_Handle
*
* This pointer is used to reference all MP2VENC instance objects
*==============================================================================
*/
typedef struct IMP2VENC_Obj *MP2VENC_Handle;

/*=============================================================================
* MP2VENC_Params
*
* This structure defines the creation parameters for all MPEG-4 VENC objects
*==============================================================================
*/
typedef IMP2VENC_Params MP2VENC_Params;

/*=============================================================================
* MP2VENC_PARAMS
*
* This structure defines default creation parameters for MPEG-4 VENC objects
*==============================================================================
*/
#define MP2VENC_PARAMS   MPEG2VENC_TI_MP2VENC_PARAMS

/*=============================================================================
* MP2VENC_DynamicParams
*
* This structure defines the dynamic parameters for all MP2VENC objects
*==============================================================================
*/
typedef IMP2VENC_DynamicParams MP2VENC_DynamicParams;

/*=============================================================================
* MP2VENC_Status
*
* This structure defines the status parameters for MP2VENC objects
*==============================================================================
*/
typedef struct IMP2VENC_Status   MP2VENC_Status;

/*=============================================================================
* MP2VENC_InArgs
*
* This structure defines the real-time input arguments for MP2VENC objects
*==============================================================================
*/
typedef struct IMP2VENC_InArgs   MP2VENC_InArgs;

/*=============================================================================
* MP2VENC_OutArgs
*
* This structure defines extened output arguments for all MPEG2 VENC objects
*==============================================================================
*/
typedef struct IMP2VENC_OutArgs MP2VENC_OutArgs;

/*=============================================================================
* MP2VENC_Cmd
*
* This typedef defines the control commands MPEG-4 VENC objects
*==============================================================================
*/
typedef IMP2VENC_Cmd   MP2VENC_Cmd;

/*--------------------------- MACROS  ---------------------------------------*/
/*=============================================================================
* control method commands
*==============================================================================
*/
#define MP2VENC_GETSTATUS     IMP2VENC_GETSTATUS
#define MP2VENC_SETPARAMS     IMP2VENC_SETPARAMS
#define MP2VENC_RESET         IMP2VENC_RESET
#define MP2VENC_SETDEFAULT    IMP2VENC_SETDEFAULT
#define MP2VENC_FLUSH         IMP2VENC_FLUSH
#define MP2VENC_GETBUFINFO    IMP2VENC_GETBUFINFO


/*-------------------------- FUNCTION PROTOTYPES ----------------------------*/

/*=============================================================================
*@func  MP2VENC_create()
*
*@brief Create an MPEG2 VENC instance object
*       using parameters specified by prms)
*
*@param  fxns
*        Pointer to the MPEG-4 VENC interface functions
*        prms
*        Pointer to MPEG-4 encoder extended parameter structure
*
*@return MP2VENC_Handle
*        Handle to the MPEG-4 encoder instance object
*
*@see    None
*
*@note   None
*==============================================================================
*/
extern MP2VENC_Handle MP2VENC_create( const IMP2VENC_Fxns *fxns,
                                      const MP2VENC_Params *prms);

/*=============================================================================
*@func  MP2VENC_control()
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
extern Int MP2VENC_control(MP2VENC_Handle         handle,
                           MP2VENC_Cmd            cmd,
                           MP2VENC_DynamicParams *params,
                           MP2VENC_Status        *status);

/*=============================================================================
*@func  MP2VENC_delete()
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
extern Void MP2VENC_delete(MP2VENC_Handle handle);

/*=============================================================================
*@func  MP2VENC_Encode()
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
extern Int MP2VENC_Encode(MP2VENC_Handle     handle,
                          IVIDEO1_BufDescIn *inbufdesc ,
                          XDM_BufDesc       *outbufdesc,
                          MP2VENC_InArgs    *inargs,
                          MP2VENC_OutArgs   *outargs);

#endif /* __MPEG2VENC_TI_API__ */

/*!
*! Revision History
*! ================
*! 27-Aug-2007 Prasad RSV : Added function headers and description
*! 23-Jan-2006 Anirban Basu: Created.
*/



