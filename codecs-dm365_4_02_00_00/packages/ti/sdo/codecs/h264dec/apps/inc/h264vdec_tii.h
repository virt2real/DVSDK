/*
 ******************************************************************************
 *  
 * DM36x Based H.264 Decoder
 *
 * "DM36x Based H.264 Decoder is software module developed on TI's DM36x.
 * This module is capable of decoding H.264 bit-stream" 
 * Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/ 
 * ALL RIGHTS RESERVED 
 ******************************************************************************
 */
/** ===========================================================================
* @file h264vdec_tii.h
*
* @path $(PROJDIR)\src
*
* @brief This File contains extended ialg object specific to h.264 decoder 
*            instance This header defines the interface used by clients of the
*           H264VDEC module
* =============================================================================
*/
/* ------compilation control switches -------------------------*/
#ifndef H264VDEC_TII_H
#define H264VDEC_TII_H
/***************************************************************
*  INCLUDE FILES                                                
****************************************************************/
#ifdef ON_LINUX
#include <ti/sdo/fc/ires/memtcm/ires_memtcm.h>
#endif
/* ----- system and platform files ----------------------------*/
/*-------program files ----------------------------------------*/
/***************************************************************
*  EXTERNAL REFERENCES NOTE : only use if not found in header file
****************************************************************/
/*--------data declarations -----------------------------------*/
/*--------function prototypes ---------------------------------*/
/****************************************************************
*  PUBLIC DECLARATIONS Defined here, used elsewhere
****************************************************************/
#define NUM_EDMA_RESOURCES 40
#define NUM_VICP_RESOURCES 1
#define NUM_HDVICP_RESOURCES 1
#ifdef ON_LINUX
#define NUM_MEMTCM_RESOURCES 1
#else
#define NUM_MEMTCM_RESOURCES 0
#endif
#ifdef ON_LINUX
#define NUM_ADDRSPACE_RESOURCE 1
#else
#define NUM_ADDRSPACE_RESOURCE 0
#endif
#define NUM_RESOURCES (NUM_EDMA_RESOURCES +\
                       NUM_VICP_RESOURCES +\
                       NUM_HDVICP_RESOURCES +\
                       NUM_MEMTCM_RESOURCES +\
                       NUM_ADDRSPACE_RESOURCE\
			)
/*--------data declarations -----------------------------------*/
/*!
*****************************************************************************
*@typedef H264VDEC_TI_Obj
*
*@brief  This structure defines the basic H264 decoder object instance.
* 
*@note   None
*
******************************************************************************/
typedef struct H264VDEC_TI_Obj {
    /* Base IALG_obj  */
    IALG_Obj        alg;   
    /* pointer to the H.264 context */
    void *h264_context;
    /* pointer to the H.264 context in persitant memory */
    void *ext_context0;
    /* Handle to HDVICP object - initialised by the application - this 
     * handle needs to be passed on for HDVICP function calls made from the 
     * codec */
    void *hdvicpHandle;

    IRES_EDMA3CHAN_Handle   resourceHandles[NUM_EDMA_RESOURCES]; 
    IRES_EDMA3CHAN_ProtocolArgs edma3ProtocolArgs[NUM_EDMA_RESOURCES];
    IRES_VICP2_Handle   vicpResourceHandles[NUM_VICP_RESOURCES]; 
    IRES_VICP2_ProtocolArgs vicpProtocolArgs[NUM_VICP_RESOURCES];
    IRES_HDVICP_Handle  hdvicpResourceHandles[NUM_HDVICP_RESOURCES]; 
    IRES_HDVICP_ProtocolArgs    hdvicpProtocolArgs[NUM_HDVICP_RESOURCES];
#ifdef ON_LINUX
    IRES_MEMTCM_Handle          memTcmHandle;
    IRES_MEMTCM_ProtocolArgs    memTcmProtocolArgs;
    IRES_ADDRSPACE_Handle   	addrspaceHandle[NUM_ADDRSPACE_RESOURCE];
    IRES_ADDRSPACE_ProtocolArgs addrspaceProtocolArgs[NUM_ADDRSPACE_RESOURCE];
#endif
    char resourceState[NUM_RESOURCES]; 
    unsigned int alloc_tccs_map_lo;
    unsigned int alloc_tccs_map_hi;
} H264VDEC_TI_Obj;
/*
*****************************************************************************
* H264VDEC_TI_IALG
*
* TI's implementation of the IALG interface for H264VDEC
*/
#ifdef _TMS320C6X
extern far IALG_Fxns H264VDEC_TI_IALG;
#else
extern IALG_Fxns H264VDEC_TI_IALG;
#endif

/*
****************************************************************************
* H264VDEC_TI_IH264VDEC
*
* TI's implementation of the IH264VDEC interface
*/
#ifdef _TMS320C6X
extern far IH264VDEC_Fxns H264VDEC_TI_IH264VDEC;
#else
extern IH264VDEC_Fxns H264VDEC_TI_IH264VDEC;
#endif

/*!
*****************************************************************************
*@typedef H264VDEC_Handle
*
*@brief  This pointer is used to reference all H264VDEC instance objects
* 
*@note   None
*
******************************************************************************/
typedef struct IH264VDEC_Obj *H264VDEC_Handle;

/*!
*****************************************************************************
*@typedef H264VDEC_Params
*
*@brief  This structure defines the creation parameters for all H264VDEC objects
* 
*@note   None
*
******************************************************************************/
typedef IH264VDEC_Params H264VDEC_Params;

/*!
*****************************************************************************
*@typedef H264VDEC_DynamicParams
*
*@brief  This structure defines the creation parameters for all H264VDEC objects
* 
*@note   None
*
******************************************************************************/
typedef IH264VDEC_DynamicParams H264VDEC_DynamicParams;

/*!
*****************************************************************************
*@typedef H264VDEC_Status
*
*@brief  This structure store the status of the the real-time parameters for
*        H264VDEC objects
* 
*@note   None
*
******************************************************************************/
typedef struct IH264VDEC_Status   H264VDEC_Status;

/*!
*****************************************************************************
*@typedef H264VDEC_OutArgs
*
*@brief  This structure defines input arguments for all H264VDEC objects
* 
*@note   None
*
******************************************************************************/
typedef IH264VDEC_OutArgs H264VDEC_OutArgs;

/*!
*****************************************************************************
*@typedef H264VDEC_InArgs
*
*@brief  This structure defines the real-time input arguments for H264VDEC
*        objects
* 
*@note   None
*
*****************************************************************************/
typedef struct IH264VDEC_InArgs   H264VDEC_InArgs;

/*!
*****************************************************************************
*@typedef H264VDEC_Cmd
*
*@brief  This typedef defines the control commands H264VDEC objects
* 
*@note   None
*
*****************************************************************************/
typedef IH264VDEC_Cmd   H264VDEC_Cmd;

/*--------function prototypes ---------------------------------*/
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
extern IALG_Handle H264VDEC_create(const IALG_Fxns *fxns, 
                                       const IALG_Params *prms);
/*****************************************************************************/
/**
*@func H264VDEC_control()
*@brief  To alter or read the h264 decoder object's attributes
*
*        Function to either write to the read/write parameters in the status
*           structure or to read all the parameters in the status structure.
*
*@param  IALG_Handle handle
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
extern Int H264VDEC_control(IALG_Handle handle, 
                            IALG_Cmd cmd,
                            IVIDDEC2_DynamicParams *params, 
                            IVIDDEC2_Status *status);
/*****************************************************************************/
/**
*@func H264VDEC_delete()
*@brief  To delete the h264 decoder object instance and free up the resources.
*
*        Function to delete the instance and free up the resources.
*
*@param  IALG_Handle handle
*        Handle ot decoder instance - as returned by H264VDEC_create function.
*
*@return None
*
*/
/*****************************************************************************/
extern Void H264VDEC_delete(IALG_Handle handle);

/*****************************************************************************/
/**
*@func H264VDEC_decode()
*@brief  To call one frame decode function for the given h264 decoder object 
*           instance.
*
*@param  IALG_Handle handle
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
extern Int H264VDEC_decode(IALG_Handle handle, XDM1_BufDesc *inptr,
         XDM_BufDesc *outptr, IVIDDEC2_InArgs *inarg, IVIDDEC2_OutArgs *outarg);

/*--------macros ----------------------------------------------*/
/*!
*****************************************************************************
*@typedef IH264VDEC_PARAMS
*
*@brief  This structure defines the default creation parameters for H264VDEC 
*           object
* 
*@note   None
*
******************************************************************************/
#define H264VDEC_PARAMS       IH264VDEC_PARAMS
/*!
*****************************************************************************
*Control commands
*@brief  Set of macros map control commands defined in ih264vdec.h to 
*           non-virtual implementation. The original Control command macros are 
*           mapped to XDMv1.0 defined control commands as given by ih264vdec.h
******************************************************************************/
#define H264VDEC_GETSTATUS    IH264VDEC_GETSTATUS
#define H264VDEC_SETPARAMS    IH264VDEC_SETPARAMS
#define H264VDEC_RESET        IH264VDEC_RESET
#define H264VDEC_FLUSH        IH264VDEC_FLUSH
#define H264VDEC_SETDEFAULT   IH264VDEC_SETDEFAULT
#define H264VDEC_GETBUFINFO   IH264VDEC_GETBUFINFO
/*--------function definitions---------------------------------*/
#endif  /* H264VDEC_TII_H */
/*!
*! Revision History
*! ================
*! 22-Aug-2007 Vinay M K: Modified to comply with coding guidelines.
*!                           related review comments.
*! 05-Jan-2006 Dinesh Kumar: Created.
*/
