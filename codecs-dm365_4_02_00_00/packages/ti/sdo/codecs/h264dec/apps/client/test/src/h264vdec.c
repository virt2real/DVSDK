/*
******************************************************************************
*  
* DM36x Based H.264 Decoder Test Application
*
* "DM36x Based H.264 Decoder Test application is software module developed on TI's DM36x.
* This module shows XDM interface for H.264 Video Decoder.
* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/ 
* ALL RIGHTS RESERVED 
******************************************************************************
*/
/** ===========================================================================
* @file H264VDEC.c
*
* @path $(PROJDIR)\src
*
* @brief This File contains function definitions which help an application 
*       developer to use the codec API's in a hassle free manner. Ideally 
*       a codec integrator would extend and modify these APIs which internally
*      use more detailed codec APIs for various scenarios like: process call
*      with and with out activate nd de-activate calls based on application
*      needs. 
*      In short these are the API's provided by the codec integrator to 
*      end application programmer by making various combinations of core codec 
*      API's.
* =============================================================================
*/
/* ------compilation control switches -------------------------*/
/***************************************************************
*  INCLUDE FILES                                                
****************************************************************/
#include <xdc/std.h>
/* ----- system and platform files ----------------------------*/
#include <ti/xdais/dm/ividdec2.h>

#include <ti/sdo/fc/ires/edma3chan/ires_edma3Chan.h>
#include <ti/sdo/fc/ires/vicp/ires_vicp2.h>
#include <ti/sdo/fc/ires/hdvicp/ires_hdvicp.h>
#include <ti/sdo/fc/ires/addrspace/ires_addrspace.h>

#include <ih264vdec.h>
#include <h264vdec_tii.h>
/***************************************************************
*  EXTERNAL REFERENCES NOTE : only use if not found in header file
****************************************************************/
/*--------preprocessor directives -----------------------------------*/
#ifdef __TMS470__
#pragma CODE_SECTION(H264VDEC_create,  ".text:create")
#pragma CODE_SECTION(H264VDEC_control, ".text:control")
#pragma CODE_SECTION(H264VDEC_delete,  ".text:delete")
#endif
/*--------function prototypes ---------------------------------*/
/****************************************************************
*  PUBLIC DECLARATIONS Defined here, used elsewhere
****************************************************************/
/*--------data declarations -----------------------------------*/
/*--------function prototypes ---------------------------------*/
/****************************************************************
*  PRIVATE DECLARATIONS Defined here, used only here
****************************************************************/
/*--------data declarations -----------------------------------*/
extern IRES_Fxns H264VDEC_TI_IRES;

/*--------function prototypes ---------------------------------*/
/*--------macros ----------------------------------------------*/
/*--------function definitions---------------------------------*/
/*****************************************************************************/
/**
*@func H264VDEC_create()
*@brief  To create an instance of the h264 decoder object
*
*        The H264VDEC_create function is called by the test application to
*        create and initialise the h264 decoder instance with the parameters 
         filled by the user.
*
*@param  const IH264VDEC_Fxns *fxns
*        Pointer to set of function pointers implemented by the algorithm as 
*        part of XDIAS compliance
*
*@param  const H264VDEC_Params *prms
*        Pointer to param structure containing user defined values. Refer to 
*        user guide for description of the prms structrue elements.
*
*@return Handle to decoder instance if successful in creating else NULL
*
*/
/*****************************************************************************/
IALG_Handle H264VDEC_create(const IALG_Fxns *fxns,
                                const IALG_Params *prms)
{
    return (IALG_Handle)(ALG_create(fxns, NULL, prms));
}

/*****************************************************************************/
/**
*@func H264VDEC_control()
*@brief  To alter or read the h264 decoder object's attributes
*
*        Function to either write to the read/write parameters in the status
*           structure or to read all the parameters in the status structure.
*
*@param  H264VDEC_Handle handle
*        Handle ot decoder instance - as returned by H264VDEC_create function.
*
*@param  H264VDEC_Cmd cmd
*        Intended command to be performed on the decoder instance.Refer to 
*       userguide for detailed description of various commands supported..
*
*@param  H264VDEC_DynamicParams *params
*        Parameter structure which enables passing of attribute values between
*        application and codec instance.
*
*@param  H264VDEC_Status *status
*        Status structure which is filled with the current status of the decoder 
*        instance. Elements are in compliance with XDM v1.0 specifications.
*
*@return IALG_EOK - if commands gets executed successfully
*        IALG_EFAIL - if execution is not-successful
*
*/
/*****************************************************************************/
Int H264VDEC_control(IALG_Handle handle, IALG_Cmd cmd, 
            IVIDDEC2_DynamicParams *params, IVIDDEC2_Status *status)
{
   Int error;
    /* Activate the algorithm - refer to XDM v1.2 and user guide */
    ALG_activate((IALG_Handle)handle);

	/* Activate all the resources */
	H264VDEC_TI_IRES.activateAllResources(handle);

    /* Call control function implemntation - which is in compliance with
     * XDM specifications  */
    error =   ((H264VDEC_Handle)handle)->fxns->ividdec.control (
											(IVIDDEC2_Handle)handle, 
                                             cmd,
                                             params, 
                                             status);

	/* De-activate all the resources */
	H264VDEC_TI_IRES.deactivateAllResources(handle);

    /* De-Activate the algorithm - refer to XDM v1.2 and user guide */
    ALG_deactivate((IALG_Handle)handle);
    return (error);
}


/*****************************************************************************/
/**
*@func H264VDEC_delete()
*@brief  To delete the h264 decoder object instance and free up the resources.
*
*        Function to delete the instance and free up the resources.
*
*@param  H264VDEC_Handle handle
*        Handle ot decoder instance - as returned by H264VDEC_create function.
*
*@return None
*
*/
/*****************************************************************************/
void H264VDEC_delete(IALG_Handle handle)
{
    ALG_delete((IALG_Handle)handle);
}


/*****************************************************************************/
/**
*@func H264VDEC_decode()
*@brief  To call one frame decode function for the given h264 decoder object 
*           instance.
*
*@param  H264VDEC_Handle handle
*        Handle to decoder instance - as returned by H264VDEC_create function.
*
*@param  XDM1_BufDesc  *input
*        Pointer to the Buffer Descriptor having the pointers to the input
*        data buffer.
*
*@param  XDM_BufDesc  *output
*        Pointer to the Buffer Descriptor having the pointers to the output
*        data buffer.
*
*@param  H264VDEC_InArgs *inarg
*        Pointer to the input arguments structure for the current instance.
*
*@param  H264VDEC_OutArgs *outarg
*        Pointer to the output arguments structure for the current instance.
*
*@return IALG_EOK - if commands gets executed successfully
*        IALG_EFAIL - if execution is not-successful
*
*/
/*****************************************************************************/
Int H264VDEC_decode(IALG_Handle handle, XDM1_BufDesc  *input,
     XDM_BufDesc  *output, IVIDDEC2_InArgs *inarg, IVIDDEC2_OutArgs *outarg)
{

    Int error;

	/* Activate the algorithm - refer to XDM v1.2 and user guide */
    ALG_activate((IALG_Handle)handle);

	/* Activate all the resources */
	H264VDEC_TI_IRES.activateAllResources(handle);

    error = ((H264VDEC_Handle)handle)->fxns->ividdec.process (
							(IVIDDEC2_Handle)handle, 
							input,
							output, 
							(IVIDDEC2_InArgs * )inarg, 
							(IVIDDEC2_OutArgs *)outarg);

	/* De-activate all the resources */
	H264VDEC_TI_IRES.deactivateAllResources(handle);

	/* De-Activate the algorithm - refer to XDM v1.2 and user guide */
    ALG_deactivate((IALG_Handle)handle);

    return(error);
}

/*!
*! Revision History
*! ================
*! 03-Sep-2007 Vinay M K: Modified to comply with MMCodecs 
*!                        coding guidelines.
*! 05-Jan-2006 Dinesh Kumar: Created.
*/
