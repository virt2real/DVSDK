/** ===========================================================================
* @file ih264venc.h
*
* @path $\\(PROJDIR)\\..\\Inc\\
*
* @desc IH264VENC Interface Header
*
* =============================================================================
*
* Copyright (c) Texas Instruments Inc 2006, 2007
*
* Use of this software is controlled by the terms and conditions found
* in the license agreement under which this software has been supplied 
*
* ===========================================================================*/


#ifndef _IH264VENC_
#define _IH264VENC_
#include <ti/xdais/xdas.h>
#include <ti/xdais/ialg.h>
#include <ti/xdais/dm/ividenc1.h>

/*
 *=============================================================================
 * IH264VENC_Handle
 *
 * This handle is used to reference all H.264 encoder instance objects
 * Pointer to H.264 encoder object structure
 *=============================================================================
 */
typedef struct IH264VENC_Obj *IH264VENC_Handle;

/*
 *=============================================================================
 * IH264VENC_Obj
 *
 * This structure must be the first field of all H.264 encoder instance objects
 * H.264 encoder base structure contains pointer to algorithm API functions
 *=============================================================================
 */
typedef struct IH264VENC_Obj
{
    struct IH264VENC_Fxns *fxns;
} IH264VENC_Obj;

/*
 *=============================================================================
 * IH264VENC_Status
 *
 * Extended Status structure defines the parameters that can be changed or read
 * during real-time operation of the algorithm.
 *=============================================================================
 */
typedef struct IH264VENC_Status {
  
  /*!
   * Mandatory fields of the status structure - Base class
   */
  IVIDENC1_Status  videncStatus; 


  /*!
   * Additional elements specific to H.264 Encoder - Extensions to base class
   */
} IH264VENC_Status;

/*
 *=============================================================================
 * IH264VENC_Cmd
 *
 * The Cmd enumeration defines the control commands for the H.264 video encoder
 * control method.
 *=============================================================================
 */
typedef IVIDENC1_Cmd IH264VENC_Cmd;


/** ============================================================
*  @name   IH264VENC_TI_MAXNUMBLOCKS
*
*  @desc   Max value of dataSyncDescriptor->numBlocks accepted
*          by decoder when operated in IH264VENC_TI_SLICEMODE 
*
*  ============================================================
*/
#define IH264VENC_TI_MAXNUMBLOCKS   5


/** ============================================================
*  @name   H264VENC_TI_DataMode
*
*  @desc  This enumeration type is used by APP to specify codec
*          when to provide encoded data - after entire frame 
*          encoding or after slice encoding  
*
*  @field  H264VENC_TI_SLICEMODE
*          provide encoded data after one slice is encoded
*  @field  H264VENC_TI_ENTIREFRAME 
*          provide encoded data after entire frame is encoded
*  ============================================================
*/

typedef enum
{
    IH264VENC_TI_SLICEMODE   = 0,       //Processing of one slice
    IH264VENC_TI_ENTIREFRAME = 1        //Processing of entire frame data
} IH264VENC_TI_DataMode;


/** ============================================================
*  @name   H264VENC_TI_SliceFormat
*
*  @desc   Describes the output slice format of encoder. This  
*          enumeration type is used by APP to specify codec
*          out slice format (NAL/Bytestream) type  
*
*  @field  H264VENC_TI_NAL_STREAM
*          provide encoded slice in NAL stream format
*  @field  H264VENC_TI_BYTE_STREAM 
*          provide encoded slice in BYTE stream format
*  ============================================================
*/

typedef enum
{
    IH264VENC_TI_NALSTREAM   = 0,       //Output data in NAL stream format
    IH264VENC_TI_BYTESTREAM  = 1        //Output data in BYTE stream format
} IH264VENC_TI_SliceFormat;

/*
*=============================================================================
* IH264VENC_TI_DataSyncHandle
*
* This handle is provided by the application to handle DataSync Fifo. Encoder 
* passes this handle back to application when providing o/p data
* via callback
*=============================================================================
*/
typedef void *IH264VENC_TI_DataSyncHandle;



/** =================================================================
*  @name   IH264VENC_TI_DataSyncDesc
*  
*  @desc   This structure specifies the parameter used by application
*          tp provide bit-stream buffer details to encoder
*  @field  size
*          Size of this structure
*  @field  numBlocks
*          Number of blocks available
*  @field  varBlockSizesFlag
*          Flag indicating whether any of the data blocks vary in size
*  @field  baseAddr
*          Array of address of first byte on valid blocks provided to 
*          decoder
*  @field  varBlockSizesFlag
*          Variable block sizes array containing valid values of 
*          numBlocks size
*  ===================================================================
*/

typedef struct IH264VENC_TI_DataSyncDesc
{
    XDAS_Int32  size;
    XDAS_Int32  numBlocks;
    XDAS_Int32  varBlockSizesFlag;
    XDAS_Int32  *baseAddr[IH264VENC_TI_MAXNUMBLOCKS];
    XDAS_Int32  blockSizes[IH264VENC_TI_MAXNUMBLOCKS];
} IH264VENC_TI_DataSyncDesc;



/** ============================================================
*  @name   IH264VENC_TI_DataSyncPutGetFxn
*
*  @desc  Blocking API used by encoder to signal "data ready" 
*        to consumer and to get the space for next set of data. 
*        Consumer need to define this API. Returns the success
*        or failure status. Valid return value is XDM_EOK or 
*        XDM_EFAIL 
*
*  @field  IH264VENC_TI_DataSyncHandle
*          Handle of dataSync provided by application

*  @field  IH264VENC_TI_DataSyncDesc 
*          dataSyncDescriptor containing encoded slice to be 
*          provided to application
*  ============================================================
*/
typedef XDAS_Int32 (* IH264VENC_TI_DataSyncPutGetFxn)
(IH264VENC_TI_DataSyncHandle dataSyncHandle, 
 IH264VENC_TI_DataSyncDesc *dataSyncDesc);



/*Maximum ROIs supported*/ 
#define MAX_ROI 5 

/** ===========================================================================
*@typedef ROI_type
*
*@brief  Enumeration of the different ROI types.
*
*@note   None
*
*@n ===========================================================================
*/
typedef enum {
  FACE_OBJECT = 0,
  BACKGROUND_OBJECT = 1,
  FOREGROUND_OBJECT = 2,
  DEFAULT_OBJECT = 3,
  PRIVACY_MASK = 4
}ROI_type;

/*
 *=============================================================================
 * ROI_Interface
 *
 * This structure defines the ROI parameters required by Encoder.
 *=============================================================================
 */
typedef struct ROI_Interface
{   
    XDM_Rect listROI[MAX_ROI];         /* list of ROI passed to codec */    
    ROI_type roiType[MAX_ROI];         /* type of ROI passed to codec */
    XDAS_Int32 numOfROI;               /* Number of Region of interest passed to codec */
    XDAS_Int32 roiPriority[MAX_ROI];   /* Priority of ROI */  
  
}ROI_Interface;
  




/* Max number if frame level parameter to be passed from low resolution to high resolution */
#define MAX_FRAMEINFO_PARAM 8
/*
 *=============================================================================
 *  @brief      MBRow info
 *
 *  @remark     Structure containing buffer description of MB row related Parameters.
*/

typedef struct
{
   XDAS_UInt32 gmvVert;     // GMV information per ROW.
}MBRowinfo;


/*
 *=============================================================================
 *  @brief      MB info
 *
 *  @remark     Structure containing buffer description of MB related Parameters.
 */

typedef struct
{
    XDAS_UInt16 numBitsMB;      // Number of bits to encode MB
    XDAS_UInt8  mbCodingMode;   // MB coding mode Inter or Intra
    XDAS_UInt8  mbQP;           // QP of MB
}MBinfo;

/*
 *=============================================================================
 *  @brief      Frame info
 *
 *  @remark     Structure containing buffer description of frame related 
 *              Parameters.
 *=============================================================================
 */

typedef struct
{
    XDAS_UInt16  width;             // Width of the Frame in pixels.
    XDAS_UInt16  hight;             // Height of the Frame in pixels.
    XDAS_UInt32  sceneChangeFlag;   // Flag to indicate scene change.
    XDAS_UInt32  bitsPerFrame;      // Number of Bits used to encode frame.
    XDAS_UInt32  frameRate;         // Frame rate per second.
    XDAS_UInt32  bitRate;           // Target Bit rate in bps.
    XDAS_Int32   *mvSADpointer;     // Pointer containing MVSAD of all the MBs in a frame.
    XDAS_Int32   *mbComplexity; // Pointer containing MB information of all the MBs  in a frame
    XDAS_Int32   *gmvPointerVert;   // Pointer containing vertical GMV values per row.
}FrameInfo_Interface;


/*         : rrr
 *=============================================================================
 *  @brief      Customized VUI Buffer Descriptor
 *
 *  @remark     Structure containing description of encoded VUI Parameters
 *              buffer, provided by external application user.
 *=============================================================================
 */

typedef struct
{
    XDAS_UInt32  VUIbufsize;             // Width of the Frame in pixels.
    XDAS_UInt8  customizedVUIbuffer[512]; // Pointer containing MVSAD of all the MBs in a frame.
}tCustomizedVUIbuffer_Interface;



/*
 *=============================================================================
 * control method commands
 *=============================================================================
 */
#define IH264VENC_GETSTATUS      XDM_GETSTATUS
#define IH264VENC_SETPARAMS      XDM_SETPARAMS
#define IH264VENC_RESET          XDM_RESET
#define IH264VENC_FLUSH          XDM_FLUSH
#define IH264VENC_SETDEFAULT     XDM_SETDEFAULT
#define IH264VENC_GETBUFINFO     XDM_GETBUFINFO
#define IH264VENC_GETVERSION     XDM_GETVERSION

/*
 *=============================================================================
 * Enum for H.264 Baseline profile levels (supported) - 
 * 1, 1b, 1.1, 1.2, 1.3, 2.0, 2.1, 2.2, 3, 3.1
 *=============================================================================
 */
typedef enum
{
    IH264VENC_LEVEL_10 = 10,  //!< Level 1.0
    IH264VENC_LEVEL_1b =  9,  //!< Level 1.b
    IH264VENC_LEVEL_11 = 11,  //!< Level 1.1
    IH264VENC_LEVEL_12 = 12,  //!< Level 1.2
    IH264VENC_LEVEL_13 = 13,  //!< Level 1.3
    IH264VENC_LEVEL_20 = 20,  //!< Level 2.0
    IH264VENC_LEVEL_21 = 21,  //!< Level 2.1
    IH264VENC_LEVEL_22 = 22,  //!< Level 2.2
    IH264VENC_LEVEL_30 = 30,  //!< Level 3.0
    IH264VENC_LEVEL_31 = 31,  //!< Level 3.1
    IH264VENC_LEVEL_32 = 32,  //!< Level 3.2
    IH264VENC_LEVEL_40 = 40,  //!< Level 4.0
    IH264VENC_LEVEL_41 = 41,  //!< Level 4.1
    IH264VENC_LEVEL_42 = 42,  //!< Level 4.2
    IH264VENC_LEVEL_50 = 50,  //!< Level 5.0
    IH264VENC_LEVEL_51 = 51   //!< Level 5.1 <- This is not supported
} IH264VENC_Level;


/*
 *=============================================================================
 * Enum for  chroma format
 * IMP4VENC_YUV_420IUV - YUV420 UV interleaved format
 *=============================================================================
 */
#if 0
typedef enum 
{   
    IH264VENC_YUV_420IUV  = 256
} IH264VENC_ChromaFormat;
#endif
#define IH264VENC_YUV_420IUV    XDM_YUV_420SP
/* Example of extension of command ID, starting with 256 on ward  */
#define IH264VENC_PREPROCESS   256 /* internal preprocssing for noise revomal */

/** ===========================================================================
*@typedef IH264VENC_STATUS
*
*@brief  Enumeration of the different error codes that can be returned by the 
*        H.264 Encoder implementation
*
*@note   None
*
*@n ===========================================================================
*/
typedef enum
{
    /*************************************************************************/
    /* Enumeration of all fatal and unsupported input error codes            */
    /*************************************************************************/

    /*H264VENC_TI_MIN_WIDTH <= maxWidth <= H264VENC_TI_MAX_WIDTH; else fatal */
    IH264VENC_ERR_MAXWIDTH =
        (0x1 << XDM_FATALERROR) + (0x1 << XDM_UNSUPPORTEDINPUT),

    /*H264VENC_TI_MIN_HEIGHT<=maxHeight<=H264VENC_TI_MAX_HEIGHT; else fatal */
    IH264VENC_ERR_MAXHEIGHT,

    /* XDM_DEFAULT <= encodingPreset <= XDM_USER_DEFINED; otherwise fatal  */
    IH264VENC_ERR_ENCODINGPRESET,

    /* 0 <= rateControlPreset <= IVIDEO_USER_DEFINED : otherwise fatal  */
    IH264VENC_ERR_RATECONTROLPRESET,

    /* 0 < maxFrameRate <= 30000 : otherwise fatal */
    IH264VENC_ERR_MAXFRAMERATE,

    /* 0 < maxBitRate <= 50000000 : otherwise fatal */
    IH264VENC_ERR_MAXBITRATE,
    
    /* 0 < maxBitRate <= maxBitRate : otherwise fatal */
    IH264VENC_ERR_MAXBITRATE_CVBR,

    /* 0 <= maxBitRate <= 8 : otherwise fatal */
    IH264VENC_ERR_CVBR_SENSITIVITY,

    /* 0 <= maxBitRate <= 60 : otherwise fatal */
    IH264VENC_ERR_CVBR_MAX_CMPX_INT,

    /* dataEndianness shall be XDM_BYTE :otherwise  fatal  */
    IH264VENC_ERR_DATAENDIANNESS,

    /* inputChromaFormat shall be XDM_YUV_420SP/XDM_CHROMA_NA : else fatal */
    IH264VENC_ERR_INPUTCHROMAFORMAT,

    /* inputContentType to be IVIDEO_PROGRESSIVE/IVIDEO_INTERLACED:else fatal*/
    IH264VENC_ERR_INPUTCONTENTTYPE,

    /* reconChromaFormat shall be XDM_YUV_420SP/XDM_CHROMA_NA : else fatal */
    IH264VENC_ERR_RECONCHROMAFORMAT,

    /* H264VENC_TI_MIN_WIDTH <= inputWidth <= maxWidth; else fatal */
    IH264VENC_ERR_INPUTWIDTH,

    /* H264VENC_TI_MIN_HEIGHT <= inputWidth <= maxHeight; else fatal */
    IH264VENC_ERR_INPUTHEIGHT,

    /* number of MBs in frame exceeded limit : not supported and fatal */
    IH264VENC_ERR_MAX_MBS_IN_FRM_LIMIT_EXCEED,

    /* (0 < targetFrameRate <= maxFrameRate) and targetFrameRate shall be */
    /* multiple of 500; else fatal */
    IH264VENC_ERR_TARGETFRAMERATE,

    /* (0 < targetBitRate <= maxBitRate); else fatal */
    IH264VENC_ERR_TARGETBITRATE,

    /* profileIdc shall be 66(BP), 77(MP) or 100(HP):otherwise fatal */
    IH264VENC_ERR_PROFILEIDC,

    /* levelIdc shall be as in IH264VENC_Level enums: otherwise fatal */
    /* IH264VENC_LEVEL_51 is also not supported and fatal             */
    IH264VENC_ERR_LEVELIDC,

    /* Cabac entropyMode not supported in BP : fatal  */
    IH264VENC_ERR_ENTROPYMODE_IN_BP,

    /* transform8x8FlagIntraFrame supported only in HP, not BP or MP : fatal */
    IH264VENC_ERR_TRANSFORM8X8FLAGINTRA_IN_BP_MP,

    /* transform8x8FlagInterFrame supported only in HP, not BP or MP : fatal */
    IH264VENC_ERR_TRANSFORM8X8FLAGINTER_IN_BP_MP,

    /* seqScalingFlag supported only in HP, not BP or MP : fatal */
    IH264VENC_ERR_SEQSCALINGFLAG_IN_BP_MP,

    /* aspectRatioX < 0 not supported : fatal */
    IH264VENC_ERR_ASPECTRATIOX,

    /* aspectRatioY < 0 not supported : fatal */
    IH264VENC_ERR_ASPECTRATIOY,

    /* pixelRange shall be 0 or 1; Not supported othwerwise */
    IH264VENC_ERR_PIXELRANGE,

    /* timeScale<0 or (timeScale*1000<targetFrameRate) not supported,fatal */
    IH264VENC_ERR_TIMESCALE,

    /* numUnitsInTicks < 0 not supported : fatal */
    IH264VENC_ERR_NUMUNITSINTICKS,

    /* enableVUIparams shall be 0 or 1; Not supported otherwise */
    IH264VENC_ERR_ENABLEVUIPARAMS,
	
	// rrr : CUSTOMSCALINGMATRIX
    /* Sequence Scaling Matrix Value shall be in range 9 to 255 (both inclusive); */
	/* Sequence Scaling Matrix must not be NULL Pointer*/
	/* Not supported otherwise */
    IH264VENC_ERR_SEQSCALEMATRIXVALUENOTINRANGE,	

    /* resetHDVICPeveryFrame shall be 0 or 1; Not supported otherwise */
    IH264VENC_ERR_RESETHDVICPEVERYFRAME,

    /* meAlgo shall be 0 or 1; Not supported otherwise */
    IH264VENC_ERR_MEALGO,

    /* unrestrictedMV shall be 0 or 1; Not supported otherwise */
    IH264VENC_ERR_UNRESTRICTEDMV,

    /* encQuality shall be 0 or 1; Not supported otherwise */
    IH264VENC_ERR_ENCQUALITY,

    /* enableARM926Tcm shall be 0 or 1; Not supported otherwise */
    /* Also not supported if maxWidth > 1280 and enableARM926Tcm = 1 */
    IH264VENC_ERR_ENABLEARM926TCM,

    /* enableDDRbuff shall be 0 or 1; Not supported otherwise */
    IH264VENC_ERR_ENABLEDDRBUFF,

    /* sliceMode shall be 0,1,2 or 3; Not supported otherwise */
    IH264VENC_ERR_SLICEMODE,

    /* Output data mode shall be 0 or 1; Not supported otherwise */
    IH264VENC_ERR_OUTPUTDATAMODE,

    /* Slice format shall be 0 or 1; Not supported otherwise */
    IH264VENC_ERR_SLICEFORMAT,

    /* No matching level coressponding to input width, height, bitrate */
    /* and framerate in H264 standard : not supported and fatal.       */
    IH264VENC_ERR_LEVEL_NOT_FOUND,

    /* (refFrameRate != targetFrameRate) not supported : fatal */
    IH264VENC_ERR_REFFRAMERATE_MISMATCH,

    /* intraFrameInterval < 0 not supported : fatal */
    IH264VENC_ERR_INTRAFRAMEINTERVAL,

    /* (generateHeader < 0) || (generateHeader > 1) not supported : fatal */
    IH264VENC_ERR_GENERATEHEADER,

    /* forceFrame other than IVIDEO_NA_FRAME or IVIDEO_I_FRAME  or */
    /* IVIDEO_IDR_FRAME not supported : fatal */
    IH264VENC_ERR_FORCEFRAME,

    /* if rcPreset is IVIDEO_USER_DEFINED, rcAlgo shall be 0,1 or 2 */
    /* else not supported and fatal */
    IH264VENC_ERR_RCALGO,

    /* 0 <= intraFrameQP  <= 51; else not supported and fatal */
    IH264VENC_ERR_INTRAFRAMEQP,

    /* 0 <= interPFrameQP  <= 51; else not supported and fatal */
    IH264VENC_ERR_INTERPFRAMEQP,

    /* 0 <= rcQMax <= 51; else not supported and fatal */
    IH264VENC_ERR_RCQMAX,

    /* 0 <= rcQMin <= rcQMax; else not supported and fatal */
    IH264VENC_ERR_RCQMIN,

    /* 0 <= rcIQMax <= 51; else not supported and fatal */
    IH264VENC_ERR_RCIQMAX,

    /* 0 <= rcIQMin <= rcIQMax; else not supported and fatal */
    IH264VENC_ERR_RCIQMIN,

    /* 0 <= initQ <= 51; else not supported and fatal */
    IH264VENC_ERR_INITQ,

    /* 100 <= maxDelay < 10000; else not supported and fatal */
    IH264VENC_ERR_MAXDELAY,

    /* lfDisableIdc shall be 0,1 or 2; else not supported and fatal */
    IH264VENC_ERR_LFDISABLEIDC,

    /* enableBufSEI shall be 0 or 1; else not supported and fatal */
    IH264VENC_ERR_ENABLEBUFSEI,

    /* enablePicTimSEI shall be 0 or 1; else not supported and fatal */
    IH264VENC_ERR_ENABLEPICTIMSEI,

    /* sliceSize shall be atleast 1024; else not supported and fatal */
    IH264VENC_ERR_SLICESIZE,

    /* intraSliceNum shall be non-negative; else not supported and fatal */
    IH264VENC_ERR_INTRASLICENUM,

    /* airRate shall be non-negative; else not supported and fatal */
    IH264VENC_ERR_AIRRATE,

    /* meMultiPart shall be 0 or 1; else not supported and fatal */
    IH264VENC_ERR_MEMULTIPART,

    /* 0 <= intraThrQF <= 5; else not supported and fatal */
    IH264VENC_ERR_INTRATHRQF,

    /* perceptualRC shall be 0 or 1; else not supported and fatal */
    IH264VENC_ERR_PERCEPTUALRC,

    /* idrFrameInterval shall be non-negative; else not supported and fatal */
    IH264VENC_ERR_IDRFRAMEINTERVAL,

    /* mvSADoutFlag shall be 0 or 1; else not supported and fatal */
    IH264VENC_ERR_MVSADOUTFLAG,

    /* enableROI shall be 0 or 1; else not supported and fatal */
    IH264VENC_ERR_ENABLEROI,

    /* enableGDR shall be 0,1 or 2; else not supported and fatal */
    IH264VENC_ERR_ENABLEGDR,

    /* GDRinterval shall be non-negative; else not supported and fatal       */
    IH264VENC_ERR_GDRINTERVAL,

    /* GDRduration shall be non-negative and lesser than GDRinterval;        */
    /* else not supported and fatal                                          */
    IH264VENC_ERR_GDRDURATION,

    /* Enable Longterm Frame  shall be 0 or 1                                */
    IH264VENC_ERR_ENABLELONGTERMFRAME,

    /* LongTerm Frame interval shall be non-negative                         */
    IH264VENC_ERR_LONGTERMDURATION,

    /* Flag to use longterm frame shall be 0 or 1                            */
    IH264VENC_ERR_USELONGTERMFRAME,
   
    /* Flag to set longterm frame shall be 0 or 1                            */
    IH264VENC_ERR_SETLONGTERMFRAME,
   
    /* Number of temporal layers shall be 0, 1, 2 or 3                       */
    IH264VENC_ERR_NUMTEMPORALLAYERS,

    /* SVC Syntax enable shall be 0, 1, 2 or 3                               */
    IH264VENC_ERR_SVCSYNTAXENABLE,

    /* Invalid LBRmaxpicsize - Refer user guide                              */
    IH264VENC_ERR_MAXPICSIZE,

    /* Invalid LBRminpicsize - Refer user guide                              */
    IH264VENC_ERR_MINPICSIZE,

    /* Invalid skip interval - Refer user guide                              */
    IH264VENC_ERR_SKIPINTERVAL,

    /* Pointer to putDataGetSpace function should be non zero value if*/
    /* outputDataMode chosen is IH264VENC_TI_SLICEMODE */
    IH264VENC_ERR_PUTDATAGETSPACEFUNC,

	/* Reference mode should be 0, 1 or 2 else not supported and fatal */
	IH264VENC_ERR_INTERLACE_REF_MODE,
    /*************************************************************************/
    /* Enumeration of all fatal and unsupported param error codes            */
    /*************************************************************************/

    /* maxInterFrameInterval param not supported: fatal  */
    IH264VENC_ERR_MAXINTERFRAMEINTERVAL =
        (0x1 << XDM_FATALERROR) + (0x1 << XDM_UNSUPPORTEDPARAM),

    /* captureWidth to be 0 or >= inputWidth; otherwise not supported, fatal */
    IH264VENC_ERR_CAPTUREWIDTH,

    /* interFrameInterval shall be 0 or 1; otherwise not supported, fatal */
    IH264VENC_ERR_INTERFRAMEINTERVAL,

    /* mbDataFlag shall be 0; otherwise not supported, fatal */
    IH264VENC_ERR_MBDATAFLAG,

    /*************************************************************************/
    /* Enumeration of all fatal error codes                                  */
    /*************************************************************************/
    /* IVIDENC1_DynamicParams size not set correctly : fatal  */
    IH264VENC_ERR_IVIDENC1_DYNAMICPARAMS_SIZE_IN_CORRECT =
        (0x1 << XDM_FATALERROR),

    /* one or more of the arguments to process call is NULL : fatal  */
    IH264VENC_ERR_IVIDENC1_PROCESS_ARGS_NULL,

    /* inArgs->size is not equal to either baseparams or extnd params fatal  */
    IH264VENC_ERR_IVIDENC1_INARGS_SIZE,

    /* outArgs->size is not equal to either baseparams or extnd params fatal  */
    IH264VENC_ERR_IVIDENC1_OUTARGS_SIZE,

    /* inArgs->inputID is equal to 0 : fatal  */
    IH264VENC_ERR_IVIDENC1_INARGS_INPUTID,

    /* inArgs->topFieldFirstFlag is not set correctly : fatal  */
    IH264VENC_ERR_IVIDENC1_INARGS_TOPFIELDFIRSTFLAG,

    /* inBufs elements were not set correctly : fatal */
    IH264VENC_ERR_IVIDENC1_INBUFS,

    /* inBufs buffer descriptors were not set correctly : fatal */
    IH264VENC_ERR_IVIDENC1_INBUFS_BUFDESC,

    /* outBufs elements were not set correctly : fatal */
    IH264VENC_ERR_IVIDENC1_OUTBUFS,

    /* outBufs buffers are NULL */
    IH264VENC_ERR_IVIDENC1_OUTBUFS_NULL,

    /* In slice mode interface (low latency) mode, invalid */
    /* value supplied to numOutputDataUnits               */
    IH264VENC_ERR_IVIDENC1_INVALID_NUM_OUTDATA_UNIT,

    /* Interlace enabled for BASELINE_PROFILE */
    IH264VENC_ERR_INTERLACE_IN_BP,

    /* Reserved fatal error  */
    IH264VENC_ERR_RESERVED,

    /* insertUserData value is not set correctly */
    IH264VENC_ERR_INSERTUSERDATA,

    /* lengthUserData value is not set correctly */
    IH264VENC_ERR_LENGTHUSERDATA,

    /* numOfROI value is not set correctly */
    IH264VENC_ERR_ROIPARAM,

    /* fatal error in encode process call : fatal */
    IH264VENC_ERR_PROCESS_CALL,

    /* init/process/control/delete api called with NULL handle : fatal */
    IH264VENC_ERR_HANDLE_NULL,

    /* init/process/control/delete api called with incorrect handle : fatal */
    IH264VENC_ERR_INCORRECT_HANDLE,

    /* memtab null error in algInit/algFree : fatal */
    IH264VENC_ERR_MEMTAB_NULL,

    /* videncParams.size shall be either sizeof(IVIDENC1_Params) or  */
    /* sizeof(IH264VENC_Params) : otherwise it is a fatal error      */
    IH264VENC_ERR_IVIDENC1_INITPARAMS_SIZE,

    /* MemTab base pointers are NULL : fatal */
    IH264VENC_ERR_MEMTABS_BASE_NULL,

    /* MemTab base pointers not aligned to required sizes : fatal */
    IH264VENC_ERR_MEMTABS_BASE_NOT_ALIGNED,

    /* MemTabs size less than request size : fatal */
    IH264VENC_ERR_MEMTABS_SIZE,

    /* MemTabs attrs mismatch request value IALG_PERSIST/IALG_SCRATCH: fatal */
    IH264VENC_ERR_MEMTABS_ATTRS,

    /* MemTabs space mismatch request value IALG_EXTERNAL etc: fatal */
    IH264VENC_ERR_MEMTABS_SPACE,

    /* MemTabs are overlapping : fatal */
    IH264VENC_ERR_MEMTABS_OVERLAP,

    /* Fatal error if process/control api is called without prior activate() */
    IH264VENC_ERR_CODEC_INACTIVE,

    /*************************************************************************/
    /* Enumeration of unsupported input as warnings. Encoder would ignore    */
    /* the unsupported params and can continue process                       */
    /*************************************************************************/
    /* levelIdc not set correctly : not supported but not fatal */
    IH264VENC_WARN_LEVELIDC = (0x1 << XDM_UNSUPPORTEDINPUT),

    /*************************************************************************/
    /* Enumeration of unsupported param as warnings. Encoder would ignore    */
    /* the unsupported params and can continue process                       */
    /*************************************************************************/

    /* rateControlPreset not set correctly : not supported but not fatal */
    IH264VENC_WARN_RATECONTROLPRESET = (0x1 << XDM_UNSUPPORTEDPARAM),

    /* 0->Not in use, 1-> Generate Meta data, 2-> Use Metadata generated by other encoder*/
    IH264VENC_ERR_METADATAFLAG,

	/* For the case sliceMode = 1 and the slice size exceeds the target size */
	IH264VENC_WARN_H241_SLICE_SIZE_EXCEEDED,

    /*************************************************************************/
    /* Enumeration of other benign errors                                    */
    /*************************************************************************/
    /* returned when videncStatus.data.buf is NULL in GETVERSION control call*/
    /* returned when videncStatus.data.bufSize is not sufficient for version */
    IH264VENC_ERR_STATUS_BUF = 0x1

}IH264VENC_STATUS;


/*
 *=============================================================================
 * IH264VENC_Params
 *
 * This structure defines the creation parameters for all H.264 enc objects
 *=============================================================================
 */
typedef struct IH264VENC_Params
{
  
  /*!
   * Mandatory fields of the Params structure - Base class
   */
  IVIDENC1_Params videncParams; 

  /*!
   * Additional elements specific to H.264 Encoder - Extensions to base class
   */
  XDAS_Int32  profileIdc;     /*!< ofile IDC (66=baseline, 77=main, 88=extended, 100=HighProfile) */
  XDAS_Int32  levelIdc;       /*!< level idc */
  XDAS_Int32  Log2MaxFrameNumMinus4; /*!< Set the maximum frame number value  */
  XDAS_Int32  ConstraintSetFlag; /*!< ConstraintSetFlags */
  XDAS_Int32  entropyMode;    /*!< entropy mode flag 0-CAVLC, 1-CABAC */
  XDAS_Int32  transform8x8FlagIntraFrame; /*!< Flag for 8x8 Transform in Inter frames*/
  XDAS_Int32  transform8x8FlagInterFrame; /*!< Flag for 8x8 Transform in Intra Frames*/
  XDAS_Int32  enableVUIparams;/*!< Enable VUI Parameters */
  XDAS_Int32  meAlgo;            /*!< Reserved */
  XDAS_Int32  seqScalingFlag; /*!< Sequence Scaling Matrix Present Flag */
                              /*!< = Disable, 1 = Auto, 2 = Low, 3 = Moderate, 4 = Reserved */
  XDAS_Int32  encQuality;     /*!< 0 => version 1.1 backward compatible mode, 2 => Platinum mode,  
                                   1 => Full feature, high Quality (It is depreciated due to performance reasons) */
  XDAS_Int32  enableARM926Tcm;  /*!< 0 -> do not use ARM926 TCM, 1 -> use ARM926 TCM */
  XDAS_Int32  enableDDRbuff;    /*!< 0 -> do not use DDR, 1 -> use DDR instead of IMCOP */
  XDAS_Int32  sliceMode;        /*!< 0 -> no multiple slices, 1 -> multiple slices - bits/slice  */
                                /*!< 2 -> multiple slices-MBs/slice,3 -> multiple slices - Rows/slice*/
  XDAS_Int32  numTemporalLayers; /* Number of temporal layers 
                                      0 -> one layer (Base layer)
                                      1 -> two layers
                                      2 -> three layers
                                      3 -> four layers 
                                      255 -> Chain free P frames */
  XDAS_Int32  svcSyntaxEnable;   /* SVC and MMCO enable/disable 
                                    0 -> SVC disabled short term ref frames used
                                    1 -> SVC enabled short term ref frames used
                                    2 -> SVC disabled long term ref frames used 
                                    3 -> SVC enabled long term ref frames used*/
  XDAS_Int32  EnableLongTermFrame;/* Flag to enable/disable long term reference frame */
  XDAS_Int32  outputDataMode;    /* 0 -> low latency, encoded streams produced after N (configurable) slices encode,*/
                                 /* 1 -> encoded stream produce at the end of frame */
  XDAS_Int32  sliceFormat;      /* 0 -> encoded stream in NAL unit format, */
                                /* 1 -> encoded stream in bytes stream format */
} IH264VENC_Params;     

/*
 *=============================================================================
 * IH264VENC_PARAMS
 *
 * Default parameter values for H.264 instance objects
 *=============================================================================
 */
extern IH264VENC_Params IH264VENC_PARAMS;

/*
 *=============================================================================
 *  IH264VENC_InArgs:
 *  This structure defines the run time arguments for all VIDENC objects.
 *  This structure may be extended by individual codec implementation
 *  allowing customization with vendor specific parameters.
 *=============================================================================
 */
typedef struct IH264VENC_InArgs
{
  /*!
   * Mandatory fields of the InArgs structure - Base class
   */
  IVIDENC1_InArgs   videncInArgs;

  /*!
   * Additional elements specific to H.264 Encoder - Extensions to base class
   */
  XDAS_Int32 timeStamp; /* Time Stamp for the current Frame */
  XDAS_Int32 insertUserData; /* Reserved */
  XDAS_Int32 lengthUserData; /* Reserved */
  ROI_Interface roiParameters;
  XDAS_Int32 numOutputDataUnits; 
}IH264VENC_InArgs;

/*
 *=============================================================================
 * VUIParamBuffer
 *
 * This structure defines the VUI parameters for the encoder
 *=============================================================================
 */
typedef struct VUIParamBuffer
{
    XDAS_Int32 aspectRatioInfoPresentFlag;     
    XDAS_Int32 overscanInfoPresentFlag;         
    XDAS_Int32 overscanAppropriateFlag;          
    XDAS_Int32 videoSignalTypePresentFlag;     
    XDAS_Int32 videoFormat;                       
    XDAS_Int32 pixelRange;                         
    XDAS_Int32 colourDescriptionPresentFlag;    
    XDAS_Int32 colourPrimaries;                   
    XDAS_Int32 transferCharacteristics;           
    XDAS_Int32 matrixCoefficients;                
    XDAS_Int32 timingInfoPresentFlag;           
    XDAS_Int32 numUnitsInTicks;                  
    XDAS_Int32 timeScale;                         
    XDAS_Int32 fixedFrameRateFlag;              
    XDAS_Int32 nalHrdParameterspresentFlag;    
    XDAS_Int32 picStructPresentFlag;            
    XDAS_Int32 bitstreamRestrictionFlag;         
} VUIParamBuffer;

/*
 * ===========================================================================
 * VUIParamBuffer
 *
 * Default dynamic parameter values for h264enc instance object
 */
extern VUIParamBuffer VUIPARAMBUFFER;


// rrr : CUSTOMSCALINGMATRIX
/*
 *=============================================================================
 * CustomScalingMatrix
 *
 * This structure defines the Scaling Matrix values for the encoder
 *=============================================================================
 */
typedef struct CustomScalingMatrix
{
	XDAS_UInt32 dummy;

	/* High Sequence scaling matrix */
	XDAS_UInt8 scalingListinput4x4_Intra_Luma[16]; 

	XDAS_UInt8 scalingListinput4x4_Intra_Cb[16]; 
	
	XDAS_UInt8 scalingListinput4x4_Intra_Cr[16]; 	

	XDAS_UInt8 scalingListinput4x4_Inter_Luma[16];
	
	XDAS_UInt8 scalingListinput4x4_Inter_Cb[16]; 

	XDAS_UInt8 scalingListinput4x4_Inter_Cr[16]; 

	XDAS_UInt8 scalingListinput8x8_Intra[64];

	XDAS_UInt8 scalingListinput8x8_Inter[64];

} CustomScalingMatrix;

// rrr : CUSTOMSCALINGMATRIX
/*
 * ===========================================================================
 * CustomScalingMatrix
 *
 * Default dynamic parameter values for h264enc instance object
 */
extern CustomScalingMatrix CUSTOMSCALINGMATRIX;

/*
 *=============================================================================
 * IH264VENC_DynamicParams
 *
 * This structure defines the run time parameters for all H264VENC objects
 *=============================================================================
 */
typedef struct IH264VENC_DynamicParams
{
  /*!
   * Mandatory fields of the DynamicParams structure - Base class
   */
  IVIDENC1_DynamicParams videncDynamicParams;
  
  /*!
   * Additional elements specific to H.264 Encoder - Extensions to base class
   */
  XDAS_Int32 sliceSize;        /*!< No. of MB rows per Slice */
  XDAS_Int32 airRate;          /*!< Adaptive Intra Refresh MB Period */
  XDAS_Int32 intraFrameQP;     /*!< Quant. param for I Slices (0-51) */
  XDAS_Int32 interPFrameQP;    /*!< Quant. Param for non - I Slices  */
  XDAS_Int32 initQ;           /*!< Initial QP for RC */
  XDAS_Int32 rcQMax;          /*!< Maximum QP to be used  Range[0,51] */
  XDAS_Int32 rcQMin;          /*!< Minimum QP to be used  Range[0,51] */
  XDAS_Int32 rcQMaxI;          /*!< Maximum QP to be used  Range[0,51] */
  XDAS_Int32 rcQMinI;          /*!< Minimum QP to be used  Range[0,51] */
  XDAS_Int32 rcAlgo;           /*!< Algorithm to be used by Rate Ctrl Scheme*/
                               /*!< => CBR, 1 => VBR, 2 => Fixed QP, 3=> CVBR,*/ 
                               /*!< 4=> FIXED_RC 5=> CBR custom1 6=> VBR custom1*/
  XDAS_Int32 maxDelay;         /*!< max delay for rate control interms of ms,*/
                               /*!< set it to 1000 for 1 second delay  */
  XDAS_Int32 aspectRatioX;      /*!< X scale for Aspect Ratio */
  XDAS_Int32 aspectRatioY;      /*!< Y scale for Aspect Ratio */
  XDAS_Int32 lfDisableIdc;     /*!< Loop Filter enable/disable control */
  XDAS_Int32 enableBufSEI;     /*!< Enable Buffering period SEI */
  XDAS_Int32 enablePicTimSEI;  /*!< Enable Picture Timing SEI */
  XDAS_Int32 perceptualRC;     /*!< Flag for enabling/disabling PRC */
  XDAS_Int32 idrFrameInterval;  /* IDR Frame Interval */
  XDAS_Int32 mvSADoutFlag;      /* Flag for enable/disable MVSAD out to the app*/
  XDAS_Int32 resetHDVICPeveryFrame; /* Flag for resetting hdvicp */
                                    /* after every frame encode */
  XDAS_Int32 enableROI;      /*!< 0 -> do not enable ROI, 1 -> enable ROI */
  XDAS_Int32 metaDataGenerateConsume; /* Flag to indicate Generate or Consume metaData*/
  XDAS_Int32 maxBitrateCVBR;  /* Specifies the max Bitrate for CVBR RC algortihm*/
  XDAS_UInt8 interlaceRefMode;      /*!<Mode to choose between ARF/SPF/MRCF*/
                                    /*!< 0 = ARF (default mode), 1 = SPF, 2 = MRCF */
  XDAS_Int32 enableGDR;             /* Flag to enable Gradual Decoder Refresh */
  XDAS_Int32 GDRduration;           /* GDR refresh duration                   */
  XDAS_Int32 GDRinterval;           /* Interval between GDR refresh           */
  XDAS_Int32 LongTermRefreshInterval;/* Refresh period for long term reference frame */
  XDAS_Int32 UseLongTermFrame;    /* Use longterm frame as reference*/
  XDAS_Int32 SetLongTermFrame;    /* Set a frame as longterm frame for reference */
  VUIParamBuffer *VUI_Buffer;     /* Pointer to VUI buffer*/
  CustomScalingMatrix *CustomScaleMatrix_Buffer; /* CUSTOMSCALINGMATRIX*/
  XDAS_Int32  CVBRsensitivity;   /* Specifies the target bitrate used by rate control*/
                                 /* in high complexity state */  
  XDAS_Int32  CVBRminbitrate ;   /* Reserved */  
  XDAS_Int32  LBRmaxpicsize;     /* parameter controls the maximum number of bits consumed per frame*/
  XDAS_Int32  LBRminpicsize;     /* parameter controls the minimum number of bits consumed per frame */
  XDAS_Int32  LBRskipcontrol;    /* parameter configures the minimum number of frames */
                                 /*  to be encoded in a set of N frames */
  XDAS_Int32 maxHighCmpxIntCVBR;    /* Specifies the maximum duration of increased complexity */
  XDAS_Int32 disableMVDCostFactor;  /* Reserved */
  IH264VENC_TI_DataSyncPutGetFxn putDataGetSpaceFxn;   /* Pointer to callback module */
  IH264VENC_TI_DataSyncHandle    dataSyncHandle;  /* Handle to datSyncDesc */
} IH264VENC_DynamicParams;

/*
 * ===========================================================================
 * IH264VENC_DYNAMICPARAMS
 *
 * Default dynamic parameter values for h264enc instance object
 */
extern IH264VENC_DynamicParams H264VENC_TI_IH264VENC_DYNAMICPARAMS;
/*
 *=============================================================================
 *  IH264VENC_OutArgs
 *  This structure defines the run time output arguments for IH264VENC
 *  instance objects.
 *  This structure may be extended by individual codec implementation
 *  allowing customization with vendor specific parameters.
 *=============================================================================
 */
typedef struct IH264VENC_OutArgs
{
  /*!
   * Mandatory fields of the OutArgs structure - Base class
   */
  IVIDENC1_OutArgs  videncOutArgs;

  /*!
   * Additional elements specific to H.264 Encoder - Extensions to base class
   */
  XDAS_Int32 numPackets;
 // XDAS_Int32 *packetSize;
  XDAS_Int32 offsetUserData; /* Reserved */
//  XDAS_Int32 *puiSadMVinfo;
} IH264VENC_OutArgs;

/*
 * ===========================================================================
 * IH264VENC_Fxns
 *
 * This structure defines all of the operations on h264enc objects
 */
typedef struct IH264VENC_Fxns
{
  /*!
   * Mandatory functions of the function table - Base class
   */
  IVIDENC1_Fxns  ividenc1;    
   
  /*!
   * Additional functions specific to H.264 Encoder - Extensions to base class
   */

} IH264VENC_Fxns;

#endif  /* _IH264VENC_ */

/*!
*! Revision History
*! ****************
*! 25-11-2009 Manisha Agrawal: Added support for low latency interface
*! 02-10-2007 Sunil Koteyar: Updated File and datatype headers
*/
