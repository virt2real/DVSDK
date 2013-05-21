/*
******************************************************************************
*
*    FILE NAME : Imp2VDEC.h
*
*    ALGORITHM : mp2VDEC
*
*    VENDOR    : TII
*
*    TARGET DSP: DM365
*
*    PURPOSE   : Imp2VDEC Interface Header
*
*****************************************************************************
*/

#ifndef Imp2VDEC_
#define Imp2VDEC_

#include <ti/xdais/xdas.h>
#include <ti/xdais/ialg.h>
#include <ti/xdais/dm/ividdec2.h>

/*
// ***************************************************************************
// Imp2VDEC_Obj
//
// This structure must be the first field of all mp2VDEC instance objects
*/
typedef struct Imp2VDEC_Obj {
    struct Imp2VDEC_Fxns *fxns;
} Imp2VDEC_Obj;

/*
// ***************************************************************************
// Imp2VDEC_Handle
//
// This handle is used to reference all mp2VDEC instance objects
*/
typedef struct Imp2VDEC_Obj *Imp2VDEC_Handle;


/** ===========================================================================
*@typedef IMP2VDEC_STATUS
*
*@brief  Enumeration of the different error codes that can be returned by the
*        MPEG2 Decoder implementation
*
*@note   None
*
*@n ===========================================================================
*/
typedef enum IMP2VDEC_ExtendedError
{

	/*				NULL INCORRECT HANDLE PASSED		 */

	IMPEG2VDEC_ERR_INCORRECT_HANDLE = 0x2,

	/*				INCORRECT CODEC ID 					 */

	IMPEG2VDEC_ERR_INCORRECT_CODEC_ID,

	/*				RESOURCES NOT INITIATED 			 */

	IMPEG2VDEC_ERR_RESOURCE_INIT_UNSUCCESSFUL,

	/*				NULL INPUT ARG PASSED				 */

	IMPEG2VDEC_ERR_INPUT_ARGUMENT_NULL,

	/*				INCORRECT INPUT ARG SIZE PASSED		 */

	IMPEG2VDEC_ERR_INPUT_ARGUMENT_SIZE_INCORRECT,

	/*				INCORRECT INBUFS BUFDESC			 */

	IMPEG2VDEC_ERR_IVIDENC1_INBUFS_BUFDESC,

	/*				INCCORECT OUTBUFS BUFDESC			 */

	IMPEG2VDEC_ERR_IVIDENC1_OUTBUFS_BUFDESC,

	/*				INARGS SIZE INCCORECT				 */

	IMPEG2VDEC_ERR_IVIDDEC2_INARGS_SIZE,

	/*				ERRONEOUS SEQUENCE HEADER			 */

	IMPEG2VDEC_ERR_SEQ_HEADER,

	/*				INVALID ARG HANDLE IN CONTROL CALL	 */

	IMPEG2VDEC_ERR_INV_ARG_HANDLE_IN_CONTROL,

	/*	 ALGORITHM NOT ACTIVATED AND PROCESS\CONTROL CALLED		 */

	IMPEG2VDEC_ERR_ALGO_NOT_ACTIVATED,

	/*		RESOURCES NOT INITIATED AND PROCESS/CONTROL CALLED	 */

	IMPEG2VDEC_ERR_RESOURCES_NOT_INITIATED,

	/*				NOT ALL RESOURCES INITIATED					 */

	IMPEG2VDEC_ERR_REQ_RESOURCES_NOTALL_ACTIVATED,

	/*				INVALID INPUT ID PASSED 					 */

	IMPEG2VDEC_ERR_INVALID_INPUT_ID,

	/*				INVALID NUMBYTES PASSED 					 */

	IMPEG2VDEC_ERR_INVALID_NUM_BYTES,

	/*				FORBIDDEN FRAME RATE CODE 					 */

	IMPEG2VDEC_ERR_FORBIDDEN_FRAME_RATE_CODE,

	/*				BIT RATE IN THE STREAM ZERO FORBIDDEN		 */

	IMPEG2VDEC_ERR_FORBIDDEN_BIT_RATE,

	/*				DISPLAY HOR SIZE ZERO   					 */

	IMPEG2VDEC_ERR_DISPLAY_HOR_SIZE_ZERO,

	/*				DISPLAY VERT SIZE ZERO 						 */

	IMPEG2VDEC_ERR_DISPLAY_VERTICAL_SIZE_ZERO,

	/*  SCICE LEVEL VERIFICATION CHECK FAILED 					 */

	IMPEG2VDEC_ERR_SLICE_VERIFICATION_CHECK_FAILED,

	/*  JUNK DATA */

	IMPEG2VDEC_ERR_JUNK_DATA,

	/* INVALID DISPLAY WIDTH		*/

	IMPEG2VDEC_ERR_INVALID_DISPLAY_WIDTH,

	/* DYNAMIC CHANGE OF DISPLAY WIDTH INVALID */

	IMPEG2VDEC_ERR_DISPLAY_WIDTH_DYNAMIC_CHANGE_INVALID,

	IMPEG2VDEC_ERR_SET_DEFAULT_VALUE_ZERO,

	IMPEG2VDEC_ERR_VALUE_OUT_OF_RANGE,

	IMPEG2VDEC_ERR_HEIGTH_OR_WIDTH_EXCEEDING_MAX,

	IMPEG2VDEC_ERR_HEIGTH_OR_WIDTH_LESSTHAN_MIN,

	IMPEG2VDEC_ERR_HEIGTH_OR_WIDTH_ODD_VAL,

	IMPEG2VDEC_ERR_INCORRECT_ASPECT_RATIO,

	IMPEG2VDEC_ERR_MARKER_BIT_NOT_FOUND,

	IMPEG2VDEC_ERR_INCORRECT_QUANT_MATRIX,

	IMPEG2VDEC_ERR_INVALID_PIC_CODING_TYPE,

	IMPEG2VDEC_ERR_FIELD_PIC_PAIR_NOT_FOUND,

	IMPEG2VDEC_ERR_OUTPUT_FORMAT_NOT_SUPPORTED,

	IMPEG2VDEC_ERR_MP_LEVEL_HT_WD_LIMITS_EXCEEDED,

	IMPEG2VDEC_ERR_HP_LEVEL8_HT_WD_LIMITS_EXCEEDED,

	IMPEG2VDEC_ERR_SCALABILITY_NOT_SUPPORTED,

	IMPEG2VDEC_ERR_INVALID_F_CODE,

	IMPEG2VDEC_ERR_ILLEGAL_INTERLACE_CONTENT,

	IMPEG2VDEC_ERR_INVALID_FRAME_PRED_FRAME_DCT,

	IMPEG2VDEC_ERR_INVALID_REPEAT_1ST_FIELD,

	IMPEG2VDEC_ERR_422FORMAT_UNSUPPORTED,

	IMPEG2VDEC_ERR_PROFILE_AND_LEVEL_UNSUPPORTED,

	IMPEG2VDEC_ERR_INCORRECT_INPUTID_FOR_SECOND_FLD,

	IMPEG2VDEC_ERR_FRAME_ORDER_NON_CONF_AFTER_FIRST_FRAME

} IMP2VDEC_ExtendedError;

/*
// ***************************************************************************
// Imp2VDEC_Status
//
// Status structure defines the parameters that can be changed or read
// during real-time operation of the alogrithm.
*/
typedef struct Imp2VDEC_Status {
    IVIDDEC2_Status  viddecStatus;

    /*-----------------------------------------------------------------------*/
    /*  When the mb_error_reporting flag in extended outargs structure is    */
    /*  turned on, this element gives the no of erroneous mbs in the current */
    /*  frame                                                                */
    /*-----------------------------------------------------------------------*/
    XDAS_Int32 error_mbs;

} Imp2VDEC_Status;

/*
// ***************************************************************************
// Imp2VDEC_Cmd
//
// The Cmd enumeration defines the control commands for the MPEG2 video encoder
// control method.
*/
typedef IVIDDEC2_Cmd Imp2VDEC_Cmd;

/*
// ***************************************************************************
// control method commands
*/
#define Imp2VDEC_GETSTATUS      XDM_GETSTATUS
#define Imp2VDEC_SETPARAMS      XDM_SETPARAMS
#define Imp2VDEC_RESET          XDM_RESET
#define Imp2VDEC_FLUSH          XDM_FLUSH
#define Imp2VDEC_SETDEFAULT     XDM_SETDEFAULT
#define Imp2VDEC_GETBUFINFO     XDM_GETBUFINFO

/* Example of extension of command ID, starting with 256 on ward  */
#define Imp2VDEC_PREPROCESS   256 /* internal preprocssing for noise revomal */
#define Imp2VDEC_OUTPUT_ORDER 257 /* Display/Decode order of the output YUV */



/*
// ***************************************************************************
// Imp2VDEC_Params
//
// This structure defines the creation parameters for all mp2VDEC objects
*/
typedef struct Imp2VDEC_Params {
    IVIDDEC2_Params viddecParams; /* must be followed for all video decoders */
    /* TODO : add on  algorithm & vendor specific parameters here
       Recommandations : segregare into two parts , creation time folloed by
       runtime parameters */

    /* Add more  */
	/* Display delay will decide the initial delay before which decode call */
    /* starts  */
    XDAS_Int32         display_delay;

} Imp2VDEC_Params;
/*
// ***************************************************************************
// Imp2VDEC_PARAMS
//
// Default parameter values for mp2VDEC instance objects
*/
extern Imp2VDEC_Params MPEG2VDEC_TI_PARAMS;

/*
 *  ******** IVIDDEC_InArgs ********
 *  This structure defines the run time arguments for all VIDDEC objects.
 *  This structure may be extended by individual codec implementation
 *  allowing customization with vendor specific parameters.
 */
typedef struct Imp2VDEC_InArgs {
    IVIDDEC2_InArgs   viddecInArgs;/* must be followed for all video encoders*/
    /* Add more  */

}Imp2VDEC_InArgs;

/*
// ***************************************************************************
// Imp2VDEC_DynamicParams
//
// This structure defines the run time parameters for all mp2VDEC objects
*/
typedef struct Imp2VDEC_DynamicParams {
    IVIDDEC2_DynamicParams viddecDynamicParams;
     /* must be followed for all video decoders */
    /* TODO : add on  algorithm & vendor specific parameters here
       Recommandations : segregare into two parts , creation time folloed by
       runtime parameters */

    /*-----------------------------------------------------------------------*/
    /*  Flag to turn on/off the DMA transfer for bottom fields of B frame    */
    /*  picture or to bypass decoding a B bottom Field picture. This is an   */
    /*  option to save on DDR bandwidth.                                     */
    /*-----------------------------------------------------------------------*/
    XDAS_Int8 bottom_fld_DDR_Opt;

    /*-----------------------------------------------------------------------*/
    /*  Flag to turn on slice level sync up and continue decoding with the   */
    /*  next slice in the same frame. Also setting this flag gives the no    */
    /*  of error mbs in the frame through the status extended structure      */
    /*-----------------------------------------------------------------------*/
    XDAS_Int8 mb_error_reporting;

    /*-----------------------------------------------------------------------*/
    /* Concealment flag to invoke the concealment for the current frame      */
    /*-----------------------------------------------------------------------*/
    XDAS_Int32 errorConceal;

    XDAS_Int8          reset_HDVICP_every_frame;

} Imp2VDEC_DynamicParams;


/*
 *  ******** Imp2VDEC_OutArgs ********
 *  This structure defines the run time output arguments for Imp2VDEC
 *  instance objects.
 *  This structure may be extended by individual codec implementation
 *  allowing customization with vendor specific parameters.
 */
typedef struct Imp2VDEC_OutArgs {
    IVIDDEC2_OutArgs  viddecOutArgs;/* must be followed for all video decoder*/
    /* Add more  */

} Imp2VDEC_OutArgs;
/*
// ***************************************************************************
// Imp2VDEC_Fxns
//
// This structure defines all of the operations on mp2VDEC objects
*/
typedef struct Imp2VDEC_Fxns {
    IVIDDEC2_Fxns    ividdec;    /* Imp2VDEC extends IVIDDEC object.
                                    Should be second set of functions */
    /* Add more  */
} Imp2VDEC_Fxns;
/*
 *  ======== mp2VDECEC_TII_Imp2VDECEC ========
 *  TI's implementation of the Imp2VDECEC interface
 */

#endif  /* Imp2VDEC_ */
