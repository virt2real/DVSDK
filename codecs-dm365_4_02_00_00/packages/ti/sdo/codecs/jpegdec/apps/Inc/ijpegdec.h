/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */
/*
 *  ======== ijpegdec.h ========
 *  IJPEGDEC Interface Header
 */
#ifndef IJPEGDEC_
#define IJPEGDEC_
//#include <xdc/std.h>
#include <ti/xdais/ialg.h>  
#include <ti/xdais/dm/xdm.h>  
#include <ti/xdais/idma3.h>                      
#include <ti/xdais/dm/iimgdec1.h>

/* JPEG decoder Error status messages */
typedef enum{
    
	/*Input buffer underflow*/
	JPEGDEC_ERROR_INSUFFICIENT_DATA= 0,

	/*Invalid display width (displaywidth < imagewidth)*/
    	JPEGDEC_ERROR_DISPLAY_WIDTH= 1,

	JPEGDEC_ERROR_INVALID_ROTATION_PARAM = 2,
    
    	JPEGDEC_ERROR_INVALID_RESIZE = 3,
    
    	JPEGDEC_ERROR_INVALID_numAU = 4,
 
 	JPEGDEC_ERROR_INVALID_DecodeHeader = 5,

	JPEGDEC_ERROR_UNSUPPORTED_forceChromaFormat = 6,

	JPEGDEC_ERROR_UNSUPPORTED_dataEndianness = 7,

	/*Successful decoding*/
	JPEGDEC_ERROR_INVALID_SUBWINDOW = 8,	
	/*SOI not found*/

    	JPEGDEC_ERROR_DQT_TYPE= 16,      /* Invalid quant table type or Q-table not supported */
 
}IJPEGDEC_ErrorStatus;

/* JPEG warnings */
#define WARN_JPGD_BAD_PROGRESSION  0x2500   /* Inconsistent progression sequence, AC coeff without DC coeff being decoded */
#define WARN_JPGD_APPx_MARKER_SKIP 0x2501   /* Decoding of APP0 marker not supported. It will be skipped.*/

/*JPEG default values */

#define JPEGDEC_YUV420    XDM_YUV_420P
#define JPEGDEC_YUV422    XDM_YUV_422P
#define JPEGDEC_YUV444    XDM_YUV_444P
#define JPEGDEC_YUV411    XDM_YUV_411P
#define JPEGDEC_YUVGRAY   XDM_GRAY
#define JPEGDEC_YUV422ILE XDM_YUV_422ILE
#define JPEGDEC_YUV_422VP (XDM_RGB + 1)
/*
 *  ======== IJPEGDEC_Cmd ========
 *  The Cmd enumeration defines the control commands for the JPEGDEC
 *  control method.
 */

typedef IIMGDEC1_Cmd IJPEGDEC_Cmd;

/*
// ===========================================================================
// control method commands
*/
#define IJPEGDEC_GETSTATUS      XDM_GETSTATUS
#define IJPEGDEC_SETPARAMS      XDM_SETPARAMS
#define IJPEGDEC_RESET          XDM_RESET
#define IJPEGDEC_FLUSH          XDM_FLUSH
#define IJPEGDEC_SETDEFAULT     XDM_SETDEFAULT
#define IJPEGDEC_GETBUFINFO     XDM_GETBUFINFO
/* Since this is an extended control command we allow a 
 * margin of 10 more commands to come inbetween the last valid
 * XDM control command and this extended command 
 */
#define IJPEGDEC_SETPOSTPROC     (XDM_GETBUFINFO + 10)

typedef enum {
  XDM_SETPOSTPROC= XDM_GETBUFINFO + 1,
  XDM_ABORT
} XDM_ExtCmdId;

typedef enum {
 JPEGDEC_TI_DECODE_SETPOSTPROC= XDM_GETBUFINFO + 1,
 JPEGDEC_TI_DECODE_ABORT
} JPEGDEC_TI_DECODE_ExtCmdId;

typedef enum {
  XDM_POSTPROC= 0,
  XDM_ABORTERR= 1,
} XDM_ExtErrorBit;

/* from 0-7 error codes are reserved for codec implementation in XDM
 * we are using the first error code 0 to signal error in post 
 * processing function.
 */
#define IJPEGDEC_POSTPROC  0

/*
 *  ======== IJPEGDEC_Handle ========
 *  This handle is used to reference all JPEG_DEC instance objects
 */
typedef struct IJPEGDEC_Obj *IJPEGDEC_Handle;

/*
 *  ======== IJPEGDEC_Obj ========
 *  This structure must be the first field of all JPEG_DEC instance objects
 */
typedef struct IJPEGDEC_Obj {
    struct IJPEGDEC_Fxns *fxns;
} IJPEGDEC_Obj;

/*
 *  ======== IJPEGDEC_Params ========
 *  This structure defines the creation parameters for all JPEG_DEC objects
 */
typedef struct IJPEGDEC_Params {
    /* -------------------------------------------------------------------- */
    /* Global Memory Pool                                                   */
    /* -------------------------------------------------------------------- */
	IIMGDEC1_Params imgdecParams;
	XDAS_Void (*halfBufCB)(Uint32 curBufPtr, XDAS_Void*arg);          /* half buffer Call Back function pointer */
    XDAS_Void* halfBufCBarg;
    } IJPEGDEC_Params;


/*
 *  ======== IJPEGDEC_Params ========
 *  This structure defines the Dynamic parameters for all JPEG_DEC objects
 */
typedef struct IJPEGDEC_DynamicParams {
     	
	IIMGDEC1_DynamicParams imgdecDynamicParams;
	XDAS_Int16      disableEOI;
 	XDAS_Int32      resizeOption;/* Set the resizing option: */
									/* 0: No resizing           */
									/* N < 8: resize the o/p image by N/8  */
	XDAS_Int16	subRegionUpLeftX; /* Area encode upper left window corner X coordinate, set to 0 to disabled this feature */
	
	XDAS_Int16	subRegionUpLeftY; /* Area encode upper left window corner Y coordinate, set to 0 to disabled this feature */
	XDAS_Int16	subRegionDownRightX; /* Area encode lower right window corner X coordinate, set to 0 to disabled this feature */
	
	XDAS_Int16	subRegionDownRightY;/* Area encode lower right window corner Y coordinate, set to 0 to disabled this feature */
	XDAS_Int16	rotation;			/* Can be 0 (XDM_DEFAULT), 90, 180, 270 */
	XDAS_Int16	decodingPreset;
} IJPEGDEC_DynamicParams;


/*
 *  ======== IJPEGDEC_Status ========
 *  This structure defines the status parameters for all JPEG_DEC objects
 *  Presently IJPEGDEC_Status is same as IJPEGDEC_Output structure
 */
typedef struct IJPEGDEC_Status {
  IIMGDEC1_Status imgdecStatus;
  XDAS_Int32        mode;           /* 0: baseline sequential, 1: progressive*/
  XDAS_Int32        imageHeight;    /* Actual height of the image*/
  XDAS_Int32        stride[3];      /* stride values for Y,U and V components */
  XDAS_Int32        decImageSize;   /* size of the decoded image in bytes*/
  XDAS_Int32        lastMCU;        /* 1: last MCU in the frame, 0: not last*/
  XDAS_UInt32		numAU;
  XDAS_UInt16  		*nextFreeCmdPtr;
  XDAS_UInt8  		*nextFreeImBufPtr;
  XDAS_UInt8  		*nextFreeCoefBufPtr;
  XDAS_Int32        inputChromaFormat;
} IJPEGDEC_Status;

/*
 *  ======== IJPEGDEC_InArgs ========
 *  This structure defines the runtime input arguments for IJPEGDEC::process
 */

typedef struct IJPEGDEC_InArgs{
    	
	IIMGDEC1_InArgs imgdecInArgs;  
	XDAS_UInt8 *ringBufStart;
	XDAS_UInt32 ringBufSize; 
} IJPEGDEC_InArgs;

/*
 *  ======== IJPEGDEC_OutArgs ========
 *  This structure defines the run time output arguments for IJPEGDEC::process
 *  function.
 */

typedef struct IJPEGDEC_OutArgs{
    	
	IIMGDEC1_OutArgs imgdecOutArgs;
	XDAS_UInt8 *curInPtr; 
	XDAS_UInt8 *curOutPtr; 
	XDAS_UInt8 *curOutPtrChroma;	
} IJPEGDEC_OutArgs;


/*
 *  ======== IJPEGDEC_PARAMS ========
 *  Default parameter values for JPEG_DEC instance objects
 */
extern IJPEGDEC_Params IJPEGDEC_PARAMS;
extern IJPEGDEC_DynamicParams IJPEGDEC_DYNAMICPARAMS;

/*
 *  ======== IJPEGDEC_Fxns ========
 *  This structure defines all of the operations on JPEG_DEC objects
 */
typedef struct IJPEGDEC_Fxns {
    	IIMGDEC1_Fxns iimgdec; 
} IJPEGDEC_Fxns;

/*
 *  ======== JPEGDEC_TI_IALG ========
 *  TI's implementation of the IALG interface for JPEGDEC
 */
extern IALG_Fxns JPEGDEC_TI_IALG;

extern IDMA3_Fxns JPEGDEC_TI_IDMA3;

/*
 *  ======== JPEGDEC_TI_IJPEGDEC ========
 *  TI's implementation of the IJPEGDEC interface
 */
extern IJPEGDEC_Fxns JPEGDEC_TI_IJPEGDEC;



#endif	/* IJPEGDEC_ */
