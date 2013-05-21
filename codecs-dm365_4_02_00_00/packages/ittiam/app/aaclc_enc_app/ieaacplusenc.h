/*
//============================================================================
//
//    FILE NAME : IEAACPLUSENC.h
//
//    ALGORITHM : EAACPLUSENC
//
//    VENDOR    : ITTIAM
//
//    TARGET DSP: C64x+
//
//    PURPOSE   : IEAACPLUSENC Interface Header
//
//    Component Wizard for eXpressDSP Version 1.33.00 Auto-Generated Component
//
//    Number of Inputs : 1
//    Number of Outputs: 1
//
//    Creation Date: Tue - 04 July 2006
//    Creation Time: 02:46 PM
//
//============================================================================
*/

#ifndef IEAACPLUSENC_
#define IEAACPLUSENC_

/*
 *  ======== ITTIAM_EAACPLUSENC_Obj ========
 */
typedef struct ITTIAM_EAACPLUSENC_Obj {
    struct ITTIAM_EAACPLUSENC_Fxns *fxns;
} ITTIAM_EAACPLUSENC_Obj;

/*
 *  ======== ITTIAM_EAACPLUSENC_Handle ========
 */
typedef struct ITTIAM_EAACPLUSENC_Obj *ITTIAM_EAACPLUSENC_Handle;

/*
 *  ======== EAACPLUSENCODER_ITTIAM_PARAMS ========
 */
typedef struct ITTIAM_EAACPLUSENC_Params
{
    IAUDENC1_Params s_iaudenc_params;
	/* Extended params */
	XDAS_Int32 noChannels;
	XDAS_Int32 aacClassic;
	XDAS_Int32 psEnable;
	XDAS_Int32 dualMono;
	XDAS_Int32 downmix;
	XDAS_Int32 useSpeechConfig;
	XDAS_Int32 fNoStereoPreprocessing;
	XDAS_Int32 invQuant;
	XDAS_Int32 useTns;
	XDAS_Int32 use_ADTS;
	XDAS_Int32 use_ADIF;
	XDAS_Int32 full_bandwidth;
  XDAS_Int32 i_channels_mask;
  XDAS_Int32 i_num_coupling_chan;
  XDAS_Int32 write_program_config_element;


} ITTIAM_EAACPLUSENC_Params;

/*
 *  ======== ITTIAM_EAACPLUSENC_DynamicParams ========
 */
typedef struct ITTIAM_EAACPLUSENC_DynamicParams {
    IAUDENC1_DynamicParams     s_iaudenc_dynamic_params;
} ITTIAM_EAACPLUSENC_DynamicParams;

/*
 *  ======== ITTIAM_EAACPLUSENC_Status ========
 */
typedef struct ITTIAM_EAACPLUSENC_Status {
    IAUDENC1_Status s_iaudenc_status;
} ITTIAM_EAACPLUSENC_Status;

/*
 *  ======== ITTIAM_EAACPLUSENC_Fxns ========
 */
typedef struct ITTIAM_EAACPLUSENC_Fxns {
    IAUDENC1_Fxns s_iaudenc_fxns;
} ITTIAM_EAACPLUSENC_Fxns;

/*
 *  ======== ITTIAM_EAACPLUSENC_InArgs ========
 */
typedef struct ITTIAM_EAACPLUSENC_InArgs {
    IAUDENC1_InArgs s_iaudenc_in_args;
} ITTIAM_EAACPLUSENC_InArgs;

/*
 *  ======== ITTIAM_EAACPLUSENC_OutArgs ========
 */
typedef struct ITTIAM_EAACPLUSENC_OutArgs {
    IAUDENC1_OutArgs s_iaudenc_out_args;
    XDAS_Int32      i_exec_done;
    XDAS_Int32      i_ittiam_err_code;
} ITTIAM_EAACPLUSENC_OutArgs;

/* Typecasting some old strcutures into new ones */
/* For XDAIS support */
typedef ITTIAM_EAACPLUSENC_Params IEAACPLUSENC_Params;
typedef ITTIAM_EAACPLUSENC_Status IEAACPLUSENC_Status;
typedef ITTIAM_EAACPLUSENC_Handle IEAACPLUSENC_Handle;
typedef ITTIAM_EAACPLUSENC_Fxns IEAACPLUSENC_Fxns;

/*
 *  ======== EAACPLUSENCODER_ITTIAM_PARAMS ========
 *  Default parameter values for EAACPLUSENC instance objects
 */

extern ITTIAM_EAACPLUSENC_Params EAACPLUSENCODER_ITTIAM_PARAMS;

#ifdef __cplusplus
}
#endif

#endif	/* IEAACPLUSENC_ */
