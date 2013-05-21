/** ===========================================================================
* @file imp2venc.h
*
* @path $\\(PROJDIR)\\..\\Inc\\
*
* @desc IMP2VENC Interface Header
*
* =============================================================================
*
* Copyright (c) Texas Instruments Inc 2006, 2007
*
* Use of this software is controlled by the terms and conditions found
* in the license agreement under which this software has been supplied
*
* ===========================================================================*/

#ifndef __IMP2VENC__
#define __IMP2VENC__

//#include <xdas.h>
//#include "mpeg2venc_ti_includes.h"
//#include "tistdtypes.h"
#include <ti/xdais/xdas.h>
//#include <ialg.h>
#include <ti/xdais/ialg.h>
#include <ti/xdais/dm/ividenc1.h>
//#include "idma_dm510.h"
//#include "idma_dm510_for_926_fc.h"
/*
 *=============================================================================
 * IMP2VENC_Handle
 *
 * This handle is used to reference all MPEG-4 encoder instance objects
 * Pointer to MPEG-4 encoder object structure
 *=============================================================================
 */
typedef struct IMP2VENC_Obj *IMP2VENC_Handle;

/*
 *=============================================================================
 * IMP2VENC_Obj
 *
 * This structure must be the first field of all MP2enc instance objects
 * MPEG-4 encoder base structure contains pointer to algorithm API functions
 *=============================================================================
 */
typedef struct IMP2VENC_Obj
{
    struct IMP2VENC_Fxns *fxns;
} IMP2VENC_Obj;


/*
 *=============================================================================
 * IMP2VENC_Status
 *
 * Extended Status structure defines the parameters that can be changed or read
 * during real-time operation of the algorithm.
 *=============================================================================
 */
typedef struct IMP2VENC_Status {

  /*!
   * Mandatory fields of the status structure - Base class
   */
  IVIDENC1_Status  videncStatus;


  /*!
   * Additional elements specific to MP2 Encoder - Extensions to base class
   */
} IMP2VENC_Status;

/*
 *=============================================================================
 * IMP2VENC_Cmd
 *
 * The Cmd enumeration defines the control commands for the MPEG2 video encoder
 * control method.
 *=============================================================================
 */
typedef IVIDENC1_Cmd IMP2VENC_Cmd;

/*
 *=============================================================================
 * control method commands
 *=============================================================================
 */

/* Example of extension of command ID, starting with 256 on ward  */
#define IMP2VENC_PREPROCESS   256 /* internal preprocssing for noise revomal */

/*
 *=============================================================================
 * Enum for  chroma format
 * IMP2VENC_YUV_420IUV - YUV420 UV interleaved format
 *=============================================================================
 */
#define IMP2VENC_YUV_420IUV	XDM_YUV_420SP

/*
 *=============================================================================
 * Enum for  rate control algos
 * IMP2VENC_RC_NONE - Fixed QP , no Rate control
 * IMP2VENC_RC_CBR - PLR3/CBR algo
 * IMP2VENC_RC_VBR - PLR4/VBR rc algo
 *=============================================================================
 */
typedef enum
{
    IMP2VENC_RC_NONE  = 0,
    IMP2VENC_RC_CBR   = 4,
    IMP2VENC_RC_VBR   = 8,
    IMP2VENC_RC_DEFAULT = IMP2VENC_RC_VBR

} IMP2VENC_RCAlgo;


/*
 *=============================================================================
 * aspect ratio enum
 *=============================================================================
 */
typedef enum
{
    IMP2VENC_AR_SQUARE  = 1,
    IMP2VENC_AR_3_4	    = 2,
    IMP2VENC_AR_9_16    = 3,
    IMP2VENC_AR_1_2_21  = 4,
    IMP2VENC_AR_DEFAULT = IMP2VENC_AR_SQUARE

} IMP2VENC_AspectRatio;


/*
 *=============================================================================
 * pixel/video range enum
 * IMP2VENC_PR_16_235 - Y varies from 16 to 235 and Cb/Cr varies from 16 to 240
 * IMP2VENC_PR_0_255 - Y/Cb/Cr varies from 0 to 255
 *=============================================================================
 */
typedef enum
{
    IMP2VENC_PR_16_235  = 0,
    IMP2VENC_PR_0_255   = 1,
    IMP2VENC_PR_DEFAULT = IMP2VENC_PR_0_255

} IMP2VENC_PixelRange;



/*
 *=============================================================================
 * IMP2VENC_Params
 *
 * This structure defines the creation parameters for all MPEG2 enc objects
 *=============================================================================
 */
typedef struct IMP2VENC_Params
{
  /*!
   * Mandatory fields of the Params structure - Base class
   */
  IVIDENC1_Params videncParams;

  /*!
   * Additional elements specific to MP2 Encoder - Extensions to base class
   */
  XDAS_Int32  aspectRatio;        /* Aspect ration info                    */
  XDAS_Int32  pixelRange;	      /* video_range=0 : Y from 16 to 235,
                                     Cb and Cr from 16 to 240;
                                     video_range=1 : Y from 0 to 255,
                                     Cb and Cr from 0 to 255.              */
  XDAS_Int32  timerResolution;    /* Timer resolution - clock ticks per sec*/
  XDAS_Int32  ME_Type;			  /* Switch for ME type option             */
  XDAS_Int32  QscaleType;   	  /* Q scale type*/
  XDAS_Int32  IntraDCPrec;   	  /* Q scale type*/

  void        *hdvicpHandle;      /* HDVICP related handle onject          */

} IMP2VENC_Params;

/*
 *=============================================================================
 * MPEG2VENC_TI_MP2VENC_PARAMS
 *
 * Default parameter values for MP2enc instance objects
 *=============================================================================
 */
extern IMP2VENC_Params MPEG2VENC_TI_MP2VENC_PARAMS;

/*
 *=============================================================================
 *  IVIDENC_InArgs:
 *  This structure defines the run time arguments for all VIDENC objects.
 *  This structure may be extended by individual codec implementation
 *  allowing customization with vendor specific parameters.
 *=============================================================================
 */
typedef struct IMP2VENC_InArgs
{
  /*!
   * Mandatory fields of the InArgs structure - Base class
   */
  IVIDENC1_InArgs   videncInArgs;

  /*!
   * Additional elements specific to MP2 Encoder - Extensions to base class
   */
  XDAS_UInt32        TimeStamp;   /*   Time stamp value of the frame to be
                                       put in bitstream  */

}IMP2VENC_InArgs;

/*
 *=============================================================================
 * IMP2VENC_DynamicParams
 *
 * This structure defines the run time parameters for all MP2enc objects
 *=============================================================================
 */
typedef struct IMP2VENC_DynamicParams
{
  /*!
   * Mandatory fields of the DynamicParams structure - Base class
   */
  IVIDENC1_DynamicParams videncDynamicParams;

  XDAS_Int32  qpIntra;      			/* default QP for I frame : QPI,  range 2 to 31 */
  XDAS_Int32  qpInter;      			/* default QP for P frame, range 2 to 31        */
  XDAS_Int32  RcAlgo;      				/* Rate Control Method,
                            			   0: disable rate control, 4-CBR,  8-VBR       */
  XDAS_Int32  QPMax;	    			/* Maximum QP to be used  Range[2,31]           */
  XDAS_Int32  QPMin;					/* Minimum QP to be used  Range[2,31]           */
  XDAS_Int32  maxDelay;					/* max delay for rate control interms of ms,
                            			    set it to 1000 for 1 second delay           */
  XDAS_Int32  qpInit;					/* max delay for rate control interms of ms,
                            			    set it to 1000 for 1 second delay           */
  XDAS_Int32  PerceptualRC; 			/* Flag to switch on/off perceptual rate control*/
  XDAS_Int32  reset_vIMCOP_every_frame;	/* Reset HDVICP flag: 1 - reset: 0 - Dont reset */
  XDAS_Int32  mvSADoutFlag;				/* Flag for enable/disable MVSAD out to the app */
} IMP2VENC_DynamicParams;

/**===========================================================================
*@struct IMP2VENC_exportMEdata
*
*@desc   This structure defines structure for exporting ME info: Motion vectors and ME Sad
*
*
*@note   None
*
*=============================================================================
*/
typedef struct _IMP2VENC_exportMEdata
{
	XDAS_Int32 meSad;
	XDAS_Int16 mvX;
	XDAS_Int16 mvY;
}IMP2VENC_exportMEdata;


/*
 *=============================================================================
 *  IMP2VENC_OutArgs:
 *  This structure defines the run time output arguments for IMP2VENC
 *  instance objects.
 *  This structure may be extended by individual codec implementation
 *  allowing customization with vendor specific parameters.
 *=============================================================================
 */
typedef struct IMP2VENC_OutArgs
{
  /*!
   * Mandatory fields of the OutArgs structure - Base class
   */
  IVIDENC1_OutArgs  videncOutArgs;

} IMP2VENC_OutArgs;

/*
 *=============================================================================
 * IMP2VENC_Fxns
 *
 * This structure defines all of the operations on MP2enc objects
 *=============================================================================
 */
typedef struct IMP2VENC_Fxns
{
  /*!
   * Mandatory functions of the function table - Base class
   */
    IVIDENC1_Fxns  ividenc;

} IMP2VENC_Fxns;

/** ===========================================================================
*@typedef IMP2VENC_STATUS
*
*@brief  Enumeration of the different error codes that can be returned by the
*        MP2 Encoder implementation
*
*@note   None
*
*@n ===========================================================================
*/
typedef enum
{
	/*************************************************************************/
	/* Enumeration of all fatal error codes						             */
	/*************************************************************************/

	/* init/process/control/delete api called with NULL handle : fatal */
	IMPEG2VENC_ERR_HANDLE_NULL =
	(0x1 << XDM_FATALERROR),

	/* init/process/control/delete api called with incorrect handle : fatal */
	IMPEG2VENC_ERR_INCORRECT_HANDLE,

	/* memtab null error in algInit/algFree : fatal */
	IMPEG2VENC_ERR_MEMTAB_NULL,

	/* videncParams.size shall be either sizeof(IVIDENC1_Params) or  */
	/* sizeof(IMPEG2VENC_Params) : otherwise it is a fatal error      */
	IMPEG2VENC_ERR_IVIDENC1_INITPARAMS_SIZE,

	/* MemTabs size less than request size : fatal */
	IMPEG2VENC_ERR_MEMTABS_SIZE,

	/* MemTabs attrs mismatch request value IALG_PERSIST/IALG_SCRATCH: fatal */
	IMPEG2VENC_ERR_MEMTABS_ATTRS,

	/* MemTabs space mismatch request value IALG_EXTERNAL etc: fatal */
	IMPEG2VENC_ERR_MEMTABS_SPACE,

	/* MemTab base pointers are NULL : fatal */
	IMPEG2VENC_ERR_MEMTABS_BASE_NULL,

	/* MemTab base pointers not aligned to required sizes : fatal */
	IMPEG2VENC_ERR_MEMTABS_BASE_NOT_ALIGNED,

	/* MemTabs are overlapping : fatal */
	IMPEG2VENC_ERR_MEMTABS_OVERLAP,

	/* Invlaid Codec Id passed to the codec */
	IMPEG2VENC_ERR_INV_CODEC_ID,

	/*************************************************************************/
	/* Enumeration of all fatal and unsupported input error codes            */
	/*************************************************************************/

	/* XDM_DEFAULT <= encodingPreset <= XDM_USER_DEFINED; otherwise fatal  */
	/* 0xa000 */
	IMPEG2VENC_ERR_ENCODINGPRESET =
		(0x1 << XDM_FATALERROR) + (0x1 << XDM_UNSUPPORTEDINPUT),

	/* inputChromaFormat shall be IMP4VENC_YUV_420IUV/XDM_CHROMA_NA : else fatal */
	/* 0xa001 */
	IMPEG2VENC_ERR_INPUTCHROMAFORMAT,

	/* 0 < maxFrameRate <= 30000 : otherwise fatal */
	/* 0xa002 */
	IMPEG2VENC_ERR_MAXFRAMERATE,

	/* 0 < maxBitRate <= 20000000 : otherwise fatal */
	/* 0xa003 */
	IMPEG2VENC_ERR_MAXBITRATE,

	/*MPEG2VENC_TI_MIN_WIDTH <= maxWidth <= MPEG2VENC_TI_MAX_WIDTH; else fatal */
	/* 0xa004 */
	IMPEG2VENC_ERR_MAXWIDTH,

	/*MPEG2VENC_TI_MIN_HEIGHT<=maxHeight<=MPEG2VENC_TI_MAX_HEIGHT; else fatal */
	/* 0xa005 */
	IMPEG2VENC_ERR_MAXHEIGHT,

	/* number of MBs in frame exceeded limit : not supported and fatal */
	/* 0xa006 */
	IMPEG2VENC_ERR_MAX_TOTAL_MBS,

	/* dataEndianness shall be XDM_BYTE :otherwise  fatal  */
	/* 0xa007 */
	IMPEG2VENC_ERR_DATAENDIANNESS,

	/* maxInterFrameInterval param not supported: fatal  */
	/* 0xa008 */
	IMPEG2VENC_ERR_MAXINTERFRAMEINTERVAL,

	/* reconChromaFormat shall be IMP4VENC_YUV_420IUV/XDM_CHROMA_NA : else fatal */
	/* 0xa009 */
	IMPEG2VENC_ERR_RECONCHROMAFORMAT,

	/* inputContentType to be IVIDEO_PROGRESSIVE:else fatal*/
	/* 0xa00a */
	IMPEG2VENC_ERR_INPUTCONTENTTYPE,

	/* 0 <= rateControlPreset <= IVIDEO_USER_DEFINED : otherwise fatal  */
	/* 0xa00b */
	IMPEG2VENC_ERR_RATECONTROLPRESET,


	/*No of Ticks per second (1 to 65535):fatal*/
	/* 0xa00c */
	IMPEG2VENC_ERR_TIMER_RESOLUTION,

	/* aspectRatio < 1 or aspectRatio > 4 not supported : fatal */
	/* 0xa00d */
	IMPEG2VENC_ERR_ASPECTRATIO,

	/* pixelRange shall be 0 or 1; Not supported othwerwise */
	/* 0xa00e */
	IMPEG2VENC_ERR_PIXELRANGE,

	/* resetHDVICPeveryFrame shall be 0 or 1; Not supported otherwise */
	/* 0xa00f */
	IMPEG2VENC_ERR_RESETHDVICPEVERYFRAME,

	/* meType shall be 0 or 1; Not supported otherwise */
	/* 0xa010 */
	IMPEG2VENC_ERR_METYPE,

	/* one or more of the arguments to process call is NULL : fatal  */
	/* 0xa011 */
	IMPEG2VENC_ERR_IVIDENC1_PROCESS_ARGS_NULL,

	/* inArgs->size is not equal to either baseparams or extnd params : fatal  */
	/* 0xa012 */
	IMPEG2VENC_ERR_IVIDENC1_INARGS_SIZE,

	/* outArgs->size is not equal to either baseparams or extnd params : fatal  */
	/* 0xa013 */
	IMPEG2VENC_ERR_IVIDENC1_OUTARGS_SIZE,

	/* inArgs->inputID is equal to 0 : fatal  */
	/* 0xa014 */
	IMPEG2VENC_ERR_IVIDENC1_INARGS_INPUTID,

	/* inArgs->topFieldFirstFlag is not set correctly : fatal  */
	/* 0xa015 */
	IMPEG2VENC_ERR_IVIDENC1_INARGS_TOPFIELDFIRSTFLAG,

	/* inBufs elements were not set correctly : fatal */
	/* 0xa016 */
	IMPEG2VENC_ERR_IVIDENC1_INBUFS,

	/* inBufs buffer descriptors were not set correctly : fatal */
	/* 0xa017 */
	IMPEG2VENC_ERR_IVIDENC1_INBUFS_BUFDESC,

	/* outBufs elements were not set correctly : fatal */
	/* 0xa018 */
	IMPEG2VENC_ERR_IVIDENC1_OUTBUFS,

	/* outBufs buffers are NULL */
	/* 0xa019 */
	IMPEG2VENC_ERR_IVIDENC1_OUTBUFS_NULL,

	/* Fatal error if process/control api is called without prior activate() */
	/* 0xa01a */
	IMPEG2VENC_ERR_CODEC_INACTIVE,

	/* Fatal error if process/control api is called without prior initializations() */
	/* 0xa01b */
	IMPEG2VENC_ERR_CODEC_NOT_INITIALIZED,

	/* If input width is not a multiple of 16 : Not supported and fatal*/
	/* 0xa01c */
	IMPEG2VENC_ERR_INPUTWIDTH_NON_MULT_OF_16,

	/* If input height is not a multiple of 16 : Not supported and fatal*/
	/* 0xa01d */
	IMPEG2VENC_ERR_INPUTHEIGHT_NON_MULT_OF_16,

	/* MPEG2VENC_TI_MIN_WIDTH <= inputWidth <= maxWidth; and */
	/* MPEG2VENC_TI_MIN_HEIGHT <= inputWidth <= maxHeight; else fatal */
	/* 0xa01e */
	IMPEG2VENC_ERR_INPUTWIDTHHEIGHT,

	/* captureWidth to be 0 or >= inputWidth; otherwise not supported, fatal */
	/* 0xa01f */
	IMPEG2VENC_ERR_CAPTUREWIDTH,

	/* (generateHeader < 0) || (generateHeader > 1) not supported : fatal */
	/* 0xa020 */
	IMPEG2VENC_ERR_GENERATEHEADER,

	/* interFrameInterval shall be 0 or 1; otherwise not supported, fatal */
	/* 0xa021 */
	IMPEG2VENC_ERR_INTERFRAMEINTERVAL,

	/* (0 < BitRate <= maxBitRate); else fatal */
	/* 0xa022 */
	IMPEG2VENC_ERR_BITRATE,

	/* (refFrameRate != targetFrameRate) not supported : fatal */
	/* 0xa023 */
	IMPEG2VENC_ERR_REFFRAMERATE_MISMATCH,

	/* (0 < targetFrameRate <= maxFrameRate) and targetFrameRate shall be */
	/* multiple of 500; else fatal */
	/* 0xa024 */
	IMPEG2VENC_ERR_TARGETFRAMERATE,

	/* intraFrameInterval < 0 not supported : fatal */
	/* 0xa025 */
	IMPEG2VENC_ERR_INTRAFRAMEINTERVAL,

	/* forceFrame other than IVIDEO_NA_FRAME or IVIDEO_I_FRAME */
	/* or IVIDEO_P_FRAME.IVIDEO_IDR_FRAME not supported : fatal */
	/* 0xa026 */
	IMPEG2VENC_ERR_FORCEFRAME,

	/* timeScale<0 or (timeScale*1000<targetFrameRate) not supported,fatal */
	/* 0xa027 */
	IMPEG2VENC_ERR_TIMESCALE,

	/* QP value limitation from MPEG-4 standard - QP range 0 to 31*/
	/* 0xa028 */
	IMPEG2VENC_ERR_INTERFRAMEQP,

	/* QP value limitation from MPEG-4 standard - QP range 0 to 31*/
	/* 0xa029 */
	IMPEG2VENC_ERR_INTRAFRAMEQP,

	/* QP value limitation from MPEG-4 standard - QP range 0 to 31*/
	/* 0xa02a */
	IMPEG2VENC_ERR_INITQ,

	/* QPMAX = 31 */
	/* 0xa02b */
	IMPEG2VENC_ERR_QPMAX,

	/*QPMIN = 1 */
	/* 0xa02c */
	IMPEG2VENC_ERR_QPMIN,

	/*QPMIN > QPMAX */
	/* 0xa02d */
	IMPEG2VENC_ERR_QPMIN_EXCEEDS_QPMAX,

	/* Incorrect Rc Algo type */
	/* 0xa02e */
	IMPEG2VENC_ERR_RCALGO,

	/*8- IMP4VENC_RC_VBR*/
	/* 0xa02f */
	IMPEG2VENC_ERR_RCMETHOD,

	/* max delay should be more than 100 */
	/* 0xa030 */
	IMPEG2VENC_ERR_MAXDELAY,

	/*1 => Enable Perceptual QP modulation, 0 => Disable */
	/* 0xa031 */
	IMPEG2VENC_ERR_PERCEPTUALRC,

	/* error in VBV buffer size used in H.263 mode*/
	/* 0xa032 */
	IMPEG2VENC_ERR_VBV_BUF_SIZE,

	/* error in Q scale type */
	/* 0xa033 */
	IMPEG2VENC_ERR_QSCALETYPE,

	/* error in Intra Dc Prec */
	/* 0xa034 */
	IMPEG2VENC_ERR_INTRA_DC_PREC,

	/* mvSADoutFlag shall be 0 or 1; else not supported and fatal */
	/* 0xa035 */
	IMPEG2VENC_ERR_MV_SAD_OUT_FLAG,

	/* One of the hardware IPs have encountered an error */
	/* 0xa036 */
	IMPEG2VENC_ERR_IP_EXECUTION,

	/* targetBitRate configured by the application is not supported by the level of the encoding */
	/* 0xa037 */
	IMPEG2VENC_ERR_TARGET_BITRATE_NOT_SUPPORTED_BY_LEVEL


	/* Warning codes for checking parameters for any level and*/
	/* returning a warning in case of discrepancy */
}IMP2VENC_STATUS;


#endif  /* __IMP2VENC__ */

