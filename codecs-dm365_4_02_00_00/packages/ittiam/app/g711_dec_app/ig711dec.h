/*****************************************************************************/
/*                                                                           */
/*                            G.711 CODEC                                        */
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
/*  File Name         : ig711dec.h                                           */
/*                                                                           */
/*  Description       : interface data structure defined here                */
/*                                                                           */
/*  List of Functions : None                                                 */
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
 *  ======== isphdec.h ========
 *  This header defines all types, constants, and functions shared by all
 *  implementations of the speech decoder algorithms.
 *  Version 0.3
 *
 */
#ifndef G711DEC_ITTIAM_
#define G711DEC_ITTIAM_

#ifdef __cplusplus
extern "C" {
#endif

#define G711DEC_ITTIAM_CID      "ti.xdais.dm.ITTIAM_G711DEC"

#define G711DEC_ITTIAM_ERUNTIME  XDM_ERUNTIME
#define G711DEC_ITTIAM_EOK       XDM_EOK
#define G711DEC_ITTIAM_EFAIL     XDM_EFAIL


/*
 *  ======== G711DEC_ITTIAM_Handle ========
 *  This handle is used to reference all SPHENC instance objects.
 */

/**
 *  @brief      This must be the first field of all ISPHENC1
 *              instance objects.
 */
typedef struct G711DEC_ITTIAM_Obj {
    struct G711DEC_ITTIAM_Fxns *fxns;
} G711DEC_ITTIAM_Obj;


/**
 *  @brief      Opaque handle to an ISPHENC1 objects.
 */
typedef struct G711DEC_ITTIAM_Obj  *G711DEC_ITTIAM_Handle;


/*****************************************************************************/
/* Structure                                                                 */
/*****************************************************************************/

/*
 *  ======== G711DEC_ITTIAM_Params ========
 *  This structure defines the creation time parameters for all SPHDEC instance
 *  objects.
 */

typedef struct G711DEC_ITTIAM_Params {
    ISPHDEC1_Params base;           /* common set of parameters */
    /* No extentions available here */
} G711DEC_ITTIAM_Params;

/*
 *  ======== G711DEC_ITTIAM_DynamicParams ========
 *  This structure defines the parameters that can be modified at run time 
 *  via 'control' operation.
 *  
 *  It is not necessary that given implementation support all dynamic 
 *  parameters to be configurable at run time. If a particular codec
 *  does not support run-time updates to a parameter that  the application
 *  is attempting to change at runtime, the codec may indicate this as an
 *  error. 
 */
typedef struct G711DEC_ITTIAM_DynamicParams {
    ISPHDEC1_DynamicParams base;    /* common set of parameters */
    /* No extentions available here */
} G711DEC_ITTIAM_DynamicParams;


/*
 *  ======== G711DEC_ITTIAM_InArgs ========
 *  This structure defines the run time input args for ITTIAM_G711DEC decoders.
 */
typedef struct G711DEC_ITTIAM_InArgs {
    ISPHDEC1_InArgs base;           /* common set of parameters */
//    XDAS_Int32 bufDataSize; /* size of data present in the input buffer */
} G711DEC_ITTIAM_InArgs;

/*
 *  ======== G711DEC_ITTIAM_Status ========
 *  This structure defines instance status parameters (read-only).
 */
typedef struct G711DEC_ITTIAM_Status {
    ISPHDEC1_Status base;           /* common set of parameters */
    /* No extentions available here */
} G711DEC_ITTIAM_Status;

/*
 *  ======== G711DEC_ITTIAM_OutArgs ========
 *  This structure defines the run time output arguments for ITTIAM_G711DEC 
 *  process function. 
 */
typedef struct G711DEC_ITTIAM_OutArgs {
    ISPHDEC1_OutArgs base;          /* common set of parameters */
    /* No extentions available here */
} G711DEC_ITTIAM_OutArgs;


/*****************************************************************************/
/* Typedefs                                                                  */
/*****************************************************************************/
/*
 *  ======== G711DEC_ITTIAM_Cmd ========
 *  This structure defines the control commands for the ITTIAM_G711DEC module.
 */
typedef  IALG_Cmd G711DEC_ITTIAM_Cmd;

/*****************************************************************************/
/* Structure                                                                 */
/*****************************************************************************/

/* Ittiam version of functions interface */
//typedef struct ISPHDEC1_Fxns G711DEC_ITTIAM_Fxns;

/*
 *  ======== G711DEC_ITTIAM_Fxns ========
 *  This structure defines all of the operations on ITTIAM_G711DEC objects.
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
typedef struct G711DEC_ITTIAM_Fxns{
    IALG_Fxns  ialg;
    XDAS_Int32 (*process)(G711DEC_ITTIAM_Handle handle, XDM1_SingleBufDesc *inBuf, 
            XDM1_SingleBufDesc *outBuf, G711DEC_ITTIAM_InArgs *inArgs, 
            G711DEC_ITTIAM_OutArgs *outArgs);
    XDAS_Int32 (*control)(G711DEC_ITTIAM_Handle handle, XDM_CmdId id, 
            G711DEC_ITTIAM_DynamicParams *params, G711DEC_ITTIAM_Status *status);
} G711DEC_ITTIAM_Fxns;



/*
 *  ======== IG711DECODE_PARAMS ========
 *  Default parameter values for G711DECODE instance objects
 */

extern
#ifdef G711_DECODER_LIB_EXPORTS
__declspec(dllexport)
#endif

#ifdef G711_DECODER_LIB_IMPORTS
__declspec(dllimport)
#endif

G711DEC_ITTIAM_Params G711DECODER_ITTIAM_PARAMS;


#ifdef __cplusplus
}
#endif

#endif  /* G711DEC_ITTIAM_ */



