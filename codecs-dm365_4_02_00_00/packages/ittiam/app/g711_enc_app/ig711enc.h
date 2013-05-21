/*****************************************************************************/
/*                                                                           */
/*                            G.711 CODEC                                    */
/*                  ITTIAM SYSTEMS PVT LTD, BANGALORE                        */
/*                           COPYRIGHT(C) 2006                               */
/*                                                                           */
/*  This program  is  proprietary to  Ittiam  Systems  Private  Limited  and */
/*  is protected under Indian  Copyright Law as an unpublished work. Its use */
/*  and  disclosure  is  limited by  the terms  and  conditions of a license */
/*  agreement. It may not be copied or otherwise  reproduced or disclosed to */
/*  persons outside the licensee's organization except in accordance with the*/
/*  terms  and  conditions   of  such  an  agreement.  All  copies  and      */
/*  reproductions shall be the property of Ittiam Systems Private Limited and*/
/*  must bear this notice in its entirety.                                   */
/*                                                                           */
/*****************************************************************************/

/*****************************************************************************/
/*                                                                           */
/*  File Name         : ig711enc.h                                           */
/*                                                                           */
/*  Description       : Interface strcutures for xDAIS are declared here     */
/*                      Cross mapping to xDMI structures also provided.      */
/*                                                                           */
/*  List of Functions : No function defined, just data taype.                */
/*                                                                           */
/*  Issues / Problems : None                                                 */
/*                                                                           */
/*  Revision History  :                                                      */
/*                                                                           */
/*         DD MM YYYY   Author(s)       Changes (Describe the changes made)  */
/*         22 06 2006   Kumar          Initial                               */
/*                                                                           */
/*****************************************************************************/


/*
 *  ======== iSPHENC.h ========
 *  This header defines all types, constants, and functions shared by all
 *  implementations of the speech encoder algorithms.
 *  Version 0.3
 */
#ifndef G711_G711ENC_ITTIAM_
#define G711_G711ENC_ITTIAM_


#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************/
/* Constant Macros                                                           */
/*****************************************************************************/
#define G711ENC_ITTIAM_ERUNTIME  XMI_ERUNTIME
#define G711ENC_ITTIAM_EOK       XMI_EOK
#define G711ENC_ITTIAM_EFAIL     XMI_EFAIL

/*
 *  ======== G711ENC_ITTIAM_Handle ========
 *  This handle is used to reference all SPHENC instance objects.
 */

/**
 *  @brief      This must be the first field of all ISPHENC1
 *              instance objects.
 */
typedef struct G711ENC_ITTIAM_Obj {
    struct G711ENC_ITTIAM_Fxns *fxns;
} G711ENC_ITTIAM_Obj;


/**
 *  @brief      Opaque handle to an ISPHENC1 objects.
 */
typedef struct G711ENC_ITTIAM_Obj  *G711ENC_ITTIAM_Handle;

/*****************************************************************************/
/* Structure                                                                 */
/*****************************************************************************/

/*
 *  ======== G711ENC_ITTIAM_Params ========
 *  This structure defines the creation time parameters for all SPHENC instance
 *  objects.
 */

typedef struct G711ENC_ITTIAM_Params {
    ISPHENC1_Params base;           /* common set of parameters */
    /* No extentions available here */
} G711ENC_ITTIAM_Params;


/*
 *  ======== G711ENC_ITTIAM_DynamicParams ========
 *  This structure defines the dynamic parameters that can be changed at 
 *  run time via ITTIAM_G711ENC 'control' API.
 * 
 *  It is not necessary that given implementation may support run time change 
 *  of these parameters. In that case, after first call, whenever application 
 *  changes these parameters, the algorithm will return error message.
 */
typedef struct G711ENC_ITTIAM_DynamicParams {
    ISPHENC1_DynamicParams base;    /* common set of parameters */
    /* No extentions available here */
} G711ENC_ITTIAM_DynamicParams;

/*
 *  ======== G711ENC_ITTIAM_InArgs ========
 *  This structure defines the run time arguments for all SPHENC objects.
 */
typedef struct G711ENC_ITTIAM_InArgs {
    ISPHENC1_InArgs base;           /* common set of parameters */
    /* No extensions available here */
} G711ENC_ITTIAM_InArgs;



/*
 *  ======== G711ENC_ITTIAM_Status ========
 *  This structure defines instance status parameters (read-only).
 */
typedef struct G711ENC_ITTIAM_Status {
    ISPHENC1_Status base;           /* common set of parameters */
    /* No extentions available here */
} G711ENC_ITTIAM_Status;

/*
 *  ======== G711ENC_ITTIAM_OutArgs ========
 *  This structure defines the run time output arguments for all SPHENC
 *  instance objects.
 */
typedef struct G711ENC_ITTIAM_OutArgs {
    ISPHENC1_OutArgs base;          /* common set of parameters */
    /* No extentions available here */
} G711ENC_ITTIAM_OutArgs;

/*****************************************************************************/
/* Typedefs                                                                  */
/*****************************************************************************/

/*
 *  ======== G711ENC_ITTIAM_Cmd ========
 *  This structure defines the control commands for the SPHENC module.
 */
typedef  XDM_CmdId G711ENC_ITTIAM_Cmd;

/*
 *  ======== G711ENC_ITTIAM_Fxns ========
 *  This structure defines all of the operations on ITTIAM_G711ENC objects.
 *
 *  process() - Basic speech encoding call. It takes input and output buffer
 *              descriptors and structures for input and output arguments. 
 *              The algorithm may also modify the output buffer pointers.
 *              The return value is IALG_EOK for success or IALG_EFAIL
 *              in case of failure. The extendedError field of the outArgs
 *              contain further error conditions flagged by the algorithm.
 *
 *  control() - This will control behaviour of algorithm via Cmd ID. 
 *              All XDM Control Commands are supported:
 *                  XDM_GETSTATUS =0, XDM_SETPARAMS, XDM_RESET, XDM_SETDEFAULT,
 *                  XDM_FLUSH, XDM_GETBUFINFO
 *              See xdm.h for details. 
 *              The return value is IALG_EOK for success or IALG_EFAIL.
 *              In case of failure extended error code contains details. 
 */
typedef struct G711ENC_ITTIAM_Fxns{
    IALG_Fxns  ialg;
    XDAS_Int32 (*process)(G711ENC_ITTIAM_Handle handle, XDM1_SingleBufDesc *inBuf, 
            XDM1_SingleBufDesc *outBuf, G711ENC_ITTIAM_InArgs *inArgs, 
            G711ENC_ITTIAM_OutArgs *outArgs);
    XDAS_Int32 (*control)(G711ENC_ITTIAM_Handle handle, XDM_CmdId id, 
            G711ENC_ITTIAM_DynamicParams *params, G711ENC_ITTIAM_Status *status);
} G711ENC_ITTIAM_Fxns;

/*
 *  ======== G711ENCODER_ITTIAM_PARAMS ========
 *  Default parameter values for G711ENCODE instance objects
 */
extern
#ifdef G711_ENCODER_LIB_EXPORTS
__declspec(dllexport)
#endif

#ifdef G711_ENCODER_LIB_IMPORTS
__declspec(dllimport)
#endif
 G711ENC_ITTIAM_Params G711ENCODER_ITTIAM_PARAMS;

#ifdef __cplusplus
}
#endif

#endif  /* G711_G711ENC_ITTIAM_ */


