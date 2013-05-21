/** ===========================================================================
* @file mpeg2venc_ti_api.c
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

/*****************************************************************************/
/*                              INCLUDE FILES                                */
/*****************************************************************************/
/* ---------------------- SYSTEM AND PLATFORM FILES -------------------------*/
#include <xdc/std.h>
//#include <tistdtypes.h>
//#include <alg.h>
#include <ti/sdo/fc/utils/api/alg.h>
//#include <xdas.h>
#include <ti/xdais/xdas.h>
/*----------------------------- PROGRAM FILES -------------------------------*/
#include <ti/xdais/dm/xdm.h>
#include "imp2venc.h"
#include "mpeg2venc_ti.h"
#include "mpeg2venc_ti_api.h"
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
MP2VENC_Handle MP2VENC_create(const IMP2VENC_Fxns *fxns,
                              const MP2VENC_Params *prms)
{
    /* Call the ALG create XDAIS API - ALG_create()
     */
    return ((MP2VENC_Handle)ALG_create((IALG_Fxns *)fxns,
                                        NULL,
                                       (IALG_Params *)prms));

}/* MP2VENC_create */

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
Int MP2VENC_control(MP2VENC_Handle         handle,
                    MP2VENC_Cmd            cmd,
                    MP2VENC_DynamicParams *params,
                    MP2VENC_Status        *status)
{

    Int error;

    ALG_activate((IALG_Handle)handle);

    /* Call the ALG create XDM API control()
     */
    error =  handle->fxns->ividenc.control((IVIDENC1_Handle)handle,cmd,
                                  (IVIDENC1_DynamicParams *)params,
                                  (IVIDENC1_Status *)status);

    ALG_deactivate((IALG_Handle)handle);

    return(error);
}/*MP2VENC_control*/

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
Void MP2VENC_delete(MP2VENC_Handle handle)
{
    /* Call the ALG delete XDAIS API
     */
    ALG_delete((IALG_Handle)handle);

	return;
}/*MP2VENC_delete*/


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
Int MP2VENC_Encode( MP2VENC_Handle     handle,
                    IVIDEO1_BufDescIn *Input,
                    XDM_BufDesc       *Output,
                    MP2VENC_InArgs    *inargs,
                    MP2VENC_OutArgs   *outarg)
{
    XDAS_Int32 result;

    ALG_activate((IALG_Handle)handle);

    /* Call the ALG create XDM API process()
     */
    result = handle->fxns->ividenc.process((IVIDENC1_Handle)handle,
                                            Input,
                                            Output,
                                            (IVIDENC1_InArgs *)inargs,
                                            (IVIDENC1_OutArgs *)outarg);

    ALG_deactivate((IALG_Handle)handle);

    return(result);
}/*MP2VENC_Encode*/

/*---------------------------------------------------------------------------*/
/*       LOCAL STATIC FUNCTION DEFINITIONS (DEFINED HERE / USED HERE)        */
/*---------------------------------------------------------------------------*/
