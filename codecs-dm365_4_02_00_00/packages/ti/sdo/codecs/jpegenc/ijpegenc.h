/*
//============================================================================
//    FILE NAME : ijpegenc.h
//    ALGORITHM : JPEGENC
//    VENDOR    : TI
//    TARGET PLATFORM: DM365
//    PURPOSE   : This is the top level driver file that exercises the JPEG
//               Encoder code
//============================================================================
*/
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
#ifndef IJPEGENC_
#define IJPEGENC_

//#include <xdc/std.h>
#include <ti/xdais/dm/xdm.h>
#include <ti/xdais/ialg.h>
#include <ti/xdais/idma3.h>
#include <ti/xdais/dm/iimgenc1.h>

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/

//!< control method commands
#define IJPEGENC_GETSTATUS      XDM_GETSTATUS
#define IJPEGENC_SETPARAMS      XDM_SETPARAMS

#define IJPEGENC_RESET          XDM_RESET
#define IJPEGENC_FLUSH          XDM_FLUSH
#define IJPEGENC_SETDEFAULT     XDM_SETDEFAULT
#define IJPEGENC_GETBUFINFO     XDM_GETBUFINFO

#define IJPEGENC_YUV_420LINE             0x8000

typedef enum {
 JPEGENC_TI_ENCODE_AU_NOHEADER= XDM_GENERATE_HEADER + 1
} JPEGENC_TI_ENCODE_ExtEncMode;

typedef enum {
  JPEGENC_TI_ENCODE_SETPREPROC= XDM_GETBUFINFO + 1,
  JPEGENC_TI_ENCODE_SETOVERLAY,
  JPEGENC_TI_ENCODE_SETCUSTOMQ,
  JPEGENC_TI_ENCODE_ABORT
} JPEGENC_TI_ENCODE_ExtCmdId;

typedef enum {
  JPEGENC_TI_ENCODE_PREPROC= 0
} JPEGENC_TI_ENCODE_ExtErrorBit;

/*
 *  ======== IJPEGENC_Handle ========
 *  This handle is used to reference all JPEGENC instance objects
 */
typedef struct IJPEGENC_Obj *IJPEGENC_Handle;

/*
 *  ======== IJPEGENC_Obj ========
 *  This structure must be the first field of all JPEGENC instance objects
 */
typedef struct IJPEGENC_Obj {

	struct IJPEGENC_Fxns *fxns;

} IJPEGENC_Obj;
  
/*
// ===========================================================================
// IJPEGE_Params
//
// This structure defines the creation parameters for all JPEG ENC objects
*/
typedef struct IJPEGE_Params {

    IIMGENC1_Params imgencParams; /* must be followed for all video encoders */
    XDAS_Void (*halfBufCB)(Uint32 curBufPtr, XDAS_Void*arg);          /* half buffer Call Back function pointer */
    XDAS_Void* halfBufCBarg;
    } IJPEGENC_Params;

/*
 *  ======== IJPEGENC_PARAMS ========
 *  Default parameter values for JPEGENC instance objects
 */
extern IJPEGENC_Params IJPEGENC_PARAMS;
typedef struct IJPEGENCQtab {
	Uint8 luma[64];
	Uint8 chroma[64];
} IJPEGENCQtab;
/*
// ===========================================================================
// IJPEGE_DynamicParams
//
// This structure defines the run time parameters for all JPEGENC objects
*/
typedef struct IJPEGE_DynamicParams {

	IIMGENC1_DynamicParams imgencDynamicParams; /* must be followed for all jpeg encoders */
	Uint16 rstInterval; /* restart interval */
	Uint16 disableEOI;  /* XDM_DEFAULT: EOI enabled, 1: EOI disabled */
	Uint16 rotation;   /*Can be 0 (XDM_DEFAULT),, 90, 180, 270 */
	IJPEGENCQtab *customQ;
} IJPEGENC_DynamicParams;

extern IJPEGENC_DynamicParams IJPEGENC_DYNAMICPARAMS;

/*
// ===========================================================================
// IJPEGENC_Status
//
// Status structure defines the parameters that can be changed or read
// during real-time operation of the alogrithm.
*/

typedef struct IJPEGENC_Status {

   IIMGENC1_Status  imgencStatus;	/* must be followed for jpeg encoder */

   XDAS_Int32 bytesGenerated; /*  The bytes generated. */
   XDAS_Int32 numAU;
   XDAS_UInt16  *nextFreeCmdPtr;
   XDAS_UInt8  *nextFreeImBufPtr;
   XDAS_UInt8  *nextFreeCoefBufPtr;
} IJPEGENC_Status;

/*
 *  ======== IJPEGENC_InArgs ========
 *  This structure defines the runtime input arguments for IJPEGENC::process
 */

typedef struct IJPEGENC_InArgs {

	IIMGENC1_InArgs imgencInArgs;
	XDAS_UInt8 *ringBufStart;
	XDAS_UInt32 ringBufSize; 
	XDAS_Int16 sliceNum;   /* slice number. -1 if last slice */
	unsigned short 	appDataType;  
	unsigned short	appDataLength[16]; 
	unsigned short	insertCommentMarker; 
	unsigned short	commentSegLen; 
} IJPEGENC_InArgs;

/*
 *  ======== IJPEGENC_OutArgs ========
 *  This structure defines the run time output arguments for IJPEGENC::process
 *  function.
 */

typedef struct IJPEGENC_OutArgs {

	IIMGENC1_OutArgs imgencOutArgs;
	XDAS_UInt8 *curInPtrY;
	XDAS_UInt8 *curInPtrU;
	XDAS_UInt8 *curInPtrV;
	XDAS_UInt8 *curOutPtr;
	unsigned int offsetAppData; 
    unsigned int offsetCommentData; 
} IJPEGENC_OutArgs;

/*
 *  ======== IJPEGENC_Cmd ========
 *  This structure defines the control commands for the IJPEGENC module.
 */
typedef IIMGENC1_Cmd IJPEGENC_Cmd;

/*
 *  ======== IJPEGENC_Fxns ========
 *  This structure defines all of the operations on IJPEGENC objects.
 */

typedef struct IJPEGENC_Fxns {

	  IIMGENC1_Fxns	iimgenc;    // 

} IJPEGENC_Fxns;

typedef enum 
{

	DM365_JPEGENC_INVALID_MAXWIDTH  = 1,      /* Invalid max Width*/
	DM365_JPEGENC_INVALID_MAXHEIGHT = 2,      /* Invalid max height*/
	DM365_JPEGENC_INVALID_MAXSCANS = 3,       /* Invalid max scans*/
	DM365_JPEGENC_INVALID_DATAENDIANNESS =4,    /*Invalid Endianness of output data*/
	DM365_JPEGENC_INVALID_FORCECHROMAFORMAT = 5, /*Invalid force chromaformat*/
    
	DM365_JPEGENC_INVALID_NUMAU = 6,              /*Invalid numau*/
	DM365_JPEGENC_INVALID_INPUTCHROMAFORMAT = 7,  /*Invalid inputchromaformat*/
	DM365_JPEGENC_INVALID_INPUTHEIGHT = 8,       /*Invalid input height*/
	DM365_JPEGENC_INVALID_INPUTWIDTH = 9,        /*Invalid inputwidth*/
	DM365_JPEGENC_INVALID_CAPTUREWIDTH = 10,     /*invalid capturewidth*/
	DM365_JPEGENC_INVALID_GENERATEHEADER = 11,    /*Invalid capturewidth*/
	DM365_JPEGENC_INVALID_QVALUE = 12,            /* Invalid qvalue*/
	
	DM365_JPEGENC_INVALID_RSTINTERVAL = 13,        /* Invalid rstinterval*/
	DM365_JPEGENC_INVALID_ROTATION = 14,           /* Invalid rotation*/
	DM365_JPEGENC_INVALID_DISABLEEOI = 15        /*Invalid disable EOI*/

} DM365_JPEGENC_ERROR;

extern IJPEGENC_Fxns JPEGENC_TI_IJPEGENC;
extern IDMA3_Fxns JPEGENC_TI_IDMA3;
#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif    /* IJPEGENC_ */

/* ======================================================================== */
/* End of file : IJPEGENC.h                                               */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

