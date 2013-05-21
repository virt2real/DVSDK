/** ===========================================================================
* @file imp4venc.h
*
* @path $\\(PROJDIR)\\..\\Inc\\
*
* @desc IMP4VENC Interface Header
*
* =============================================================================
*
* Copyright (c) Texas Instruments Inc 2006, 2007
*
* Use of this software is controlled by the terms and conditions found
* in the license agreement under which this software has been supplied
*
* ===========================================================================*/

#ifndef __IMP4HDVICPENC__
#define __IMP4HDVICPENC__

//#include <xdas.h>
//#include "mpeg4venc_ti_includes.h"
//#include "tistdtypes.h"
#include <ti/xdais/xdas.h>
//#include <ialg.h>
#include <ti/xdais/ialg.h>
//#include <ividenc1.h>
#include <ti/xdais/dm/ividenc1.h>
//#include "idma_dm510.h"
//#include "idma_dm510_for_926_fc.h"
/*
 *=============================================================================
 * IMP4HDVICPENC_Handle
 *
 * This handle is used to reference all MPEG-4 encoder instance objects
 * Pointer to MPEG-4 encoder object structure
 *=============================================================================
 */
typedef struct IMP4HDVICPENC_Obj *IMP4HDVICPENC_Handle;

/*
 *=============================================================================
 * IMP4HDVICPENC_Obj
 *
 * This structure must be the first field of all MP4enc instance objects
 * MPEG-4 encoder base structure contains pointer to algorithm API functions
 *=============================================================================
 */
typedef struct IMP4HDVICPENC_Obj
{
    struct IMP4HDVICPENC_Fxns *fxns;
} IMP4HDVICPENC_Obj;


/*
 *=============================================================================
 * IMP4HDVICPENC_Status
 *
 * Extended Status structure defines the parameters that can be changed or read
 * during real-time operation of the algorithm.
 *=============================================================================
 */
typedef struct IMP4HDVICPENC_Status {

  /*!
   * Mandatory fields of the status structure - Base class
   */
  IVIDENC1_Status  videncStatus;


  /*!
   * Additional elements specific to MP4 Encoder - Extensions to base class
   */
} IMP4HDVICPENC_Status;

/*
 *=============================================================================
 * IMP4HDVICPENC_Cmd
 *
 * The Cmd enumeration defines the control commands for the MPEG4 video encoder
 * control method.
 *=============================================================================
 */
typedef IVIDENC1_Cmd IMP4HDVICPENC_Cmd;

/*
 *=============================================================================
 * control method commands
 *=============================================================================
 */

/* Example of extension of command ID, starting with 256 on ward  */
#define IMP4HDVICPENC_PREPROCESS   256 /* internal preprocssing for noise revomal */

/*
 *=============================================================================
 * Enum for  chroma format
 * IMP4HDVICPENC_YUV_420IUV - YUV420 UV interleaved format
 *=============================================================================
 */
#if 0
typedef enum
{
    IMP4HDVICPENC_YUV_420IUV  = 256
} IMP4HDVICPENC_ChromaFormat;
#endif

#define IMP4HDVICPENC_YUV_420IUV XDM_YUV_420SP

/*
 *=============================================================================
 * Enum for  rate control algos
 * IMP4HDVICPENC_RC_NONE - Fixed QP , no Rate control
 * IMP4HDVICPENC_RC_CBR - PLR3/CBR algo
 * IMP4HDVICPENC_RC_VBR - PLR4/VBR rc algo
 *=============================================================================
 */
typedef enum
{
    IMP4HDVICPENC_RC_NONE  = 0,
    IMP4HDVICPENC_RC_CBR   = 4,
    IMP4HDVICPENC_RC_VBR   = 8,
    IMP4HDVICPENC_RC_DEFAULT = IMP4HDVICPENC_RC_VBR

} IMP4HDVICPENC_RCAlgo;


/*
 *=============================================================================
 * aspect ratio enum
 *=============================================================================
 */
typedef enum
{
    IMP4HDVICPENC_AR_SQUARE  = 1,
    IMP4HDVICPENC_AR_12_11   = 2,
    IMP4HDVICPENC_AR_10_11   = 3,
    IMP4HDVICPENC_AR_16_11   = 4,
    IMP4HDVICPENC_AR_40_33   = 5,
    IMP4HDVICPENC_AR_DEFAULT = IMP4HDVICPENC_AR_SQUARE

} IMP4HDVICPENC_AspectRatio;


/*
 *=============================================================================
 * pixel/video range enum
 * IMP4HDVICPENC_PR_16_235 - Y varies from 16 to 235 and Cb/Cr varies from 16 to 240
 * IMP4HDVICPENC_PR_0_255 - Y/Cb/Cr varies from 0 to 255
 *=============================================================================
 */
typedef enum
{
    IMP4HDVICPENC_PR_16_235  = 0,
    IMP4HDVICPENC_PR_0_255   = 1,
    IMP4HDVICPENC_PR_DEFAULT = IMP4HDVICPENC_PR_0_255

} IMP4HDVICPENC_PixelRange;


/*
 *=============================================================================
 * Enum for MPEG-4 Simple profile levels - 0, 0b, 1, 2, 3, 4a & 5
 *=============================================================================
 */
typedef enum
{
    IMP4HDVICPENC_SP_LEVEL_0   = 0,
    IMP4HDVICPENC_SP_LEVEL_0B  = 9,
    IMP4HDVICPENC_SP_LEVEL_1   = 1,
    IMP4HDVICPENC_SP_LEVEL_2   = 2,
    IMP4HDVICPENC_SP_LEVEL_3   = 3,
    IMP4HDVICPENC_SP_LEVEL_4A  = 4,
    IMP4HDVICPENC_SP_LEVEL_5   = 5

} IMP4HDVICPENC_Level;


/*
 *=============================================================================
 * Enum for H.263 base profile levels - 10,20,30,40 & 45
 *=============================================================================
 */
typedef enum
{
    IMP4HDVICPENC_H263_LEVEL_10 = 10,
    IMP4HDVICPENC_H263_LEVEL_20 = 20,
    IMP4HDVICPENC_H263_LEVEL_30 = 30,
    IMP4HDVICPENC_H263_LEVEL_40 = 40,
    IMP4HDVICPENC_H263_LEVEL_45 = 45

} IMP4HDVICPENC_H263Level;

/** ===========================================================================
*@typedef IMP4VENC_STATUS
*
*@brief  Enumeration of the different error codes that can be returned by the
*        MPEG4 Encoder implementation
*
*@note   None
*
*@n ===========================================================================
*/
typedef enum
{
    /*************************************************************************/
    /* Enumeration of all fatal error codes                                  */
    /*************************************************************************/

    /* init/process/control/delete api called with NULL handle : fatal */
    MPEG4VENC_ERR_HANDLE_NULL =
    (0x1 << XDM_FATALERROR),

    /* init/process/control/delete api called with incorrect handle : fatal */
    MPEG4VENC_ERR_INCORRECT_HANDLE,

    /* memtab null error in algInit/algFree : fatal */
    MPEG4VENC_ERR_MEMTAB_NULL,

    /* videncParams.size shall be either sizeof(IVIDENC1_Params) or  */
    /* sizeof(IMPEG4VENC_Params) : otherwise it is a fatal error      */
    MPEG4VENC_ERR_IVIDENC1_INITPARAMS_SIZE,

    /* MemTabs size less than request size : fatal */
    MPEG4VENC_ERR_MEMTABS_SIZE,

    /* MemTabs attrs mismatch request value IALG_PERSIST/IALG_SCRATCH: fatal */
    MPEG4VENC_ERR_MEMTABS_ATTRS,

    /* MemTabs space mismatch request value IALG_EXTERNAL or IALG_DARAM0: fatal */
    MPEG4VENC_ERR_MEMTABS_SPACE,

    /* MemTab base pointers are NULL : fatal */
    MPEG4VENC_ERR_MEMTABS_BASE_NULL,

    /* MemTab base pointers not aligned to required sizes : fatal */
    MPEG4VENC_ERR_MEMTABS_BASE_NOT_ALIGNED,

    /* MemTabs are overlapping : fatal */
    MPEG4VENC_ERR_MEMTABS_OVERLAP,

    /* Invlaid Codec Id passed to the codec */
    MPEG4VENC_ERR_INV_CODEC_ID,
    /*************************************************************************/
    /* Enumeration of all fatal and unsupported input error codes            */
    /*************************************************************************/

    /* XDM_DEFAULT <= encodingPreset <= XDM_USER_DEFINED; otherwise fatal
    and unsupported */
    MPEG4VENC_ERR_ENCODINGPRESET =
        (0x1 << XDM_FATALERROR) + (0x1 << XDM_UNSUPPORTEDINPUT),

    /* inputChromaFormat shall be IMP4HDVICPENC_YUV_420IUV/XDM_CHROMA_NA : else fatal
    and unsupported*/
    MPEG4VENC_ERR_INPUTCHROMAFORMAT,

    /* 0 < maxFrameRate <= 30000 : otherwise fatal and unsupported*/
    MPEG4VENC_ERR_MAXFRAMERATE,

    /* 0 < maxBitRate <= 20000000 : otherwise fatal and unsupported*/
    MPEG4VENC_ERR_MAXBITRATE,

    /*MPEG4VENC_TI_MIN_WIDTH <= maxWidth <= MPEG4VENC_TI_MAX_WIDTH; else fatal
    and unsupported*/
    MPEG4VENC_ERR_MAXWIDTH,

    /*MPEG4VENC_TI_MIN_HEIGHT<=maxHeight<=MPEG4VENC_TI_MAX_HEIGHT; else fatal
    and unsupported*/
    MPEG4VENC_ERR_MAXHEIGHT,

    /* number of MBs in frame exceeded limit : not supported and fatal
    and unsupported*/
    MPEG4VENC_ERR_MAX_TOTAL_MBS,

    /* dataEndianness shall be XDM_BYTE :otherwise  fatal and unsupported*/
    MPEG4VENC_ERR_DATAENDIANNESS,

    /* maxInterFrameInterval param not supported: fatal and unsupported*/
    MPEG4VENC_ERR_MAXINTERFRAMEINTERVAL,

    /* reconChromaFormat shall be IMP4HDVICPENC_YUV_420IUV/XDM_CHROMA_NA : else fatal
    and unsupported*/
    MPEG4VENC_ERR_RECONCHROMAFORMAT,

    /* inputContentType to be IVIDEO_PROGRESSIVE:else fatal
    and unsupported*/
    MPEG4VENC_ERR_INPUTCONTENTTYPE,

    /* 0 <= rateControlPreset <= IVIDEO_USER_DEFINED : otherwise fatal
    and unsupported*/
    MPEG4VENC_ERR_RATECONTROLPRESET,

    /* Mpeg4 (1) or H.263 (0) otherwise not supported */
    MPEG4VENC_ERR_MPEG4MODE,

    /* levelIdc shall be as in IMPEG4VENC_Level enums: otherwise fatal
    and unsupported*/
    MPEG4VENC_ERR_LEVELIDC,

    /*VOS header is coded(1) or not(0) otherwise unsupported and fatal
    and unsupported*/
    MPEG4VENC_ERR_ENCPARM_USE_VOS,

    /*GOV header is coded(1) or not(0) otherwise unsupported and fatal
    and unsupported*/
    MPEG4VENC_ERR_USE_GOV,

    /*Data partioning, 0 = off , 1 = on.otherwise unsupported and fatal
    and unsupported*/
    MPEG4VENC_ERR_DATA_PART,

    /*RVLC 0 = off , 1 = on.otherwise unsupported and fatal */
    MPEG4VENC_ERR_RVLC,

    /*reversible_vlc not supported when Data Partition is off*/
    MPEG4VENC_ERR_DATA_PART_RVLC,

    /*No of Ticks per second (1 to 65535):fatal
    and unsupported*/
    MPEG4VENC_ERR_TIMER_RESOLUTION,

    /* aspectRatio < 1 or aspectRatio > 5 not supported : fatal */
    MPEG4VENC_ERR_ASPECTRATIO,

    /* pixelRange shall be 0 or 1; fatal and Not supported otherwise */
    MPEG4VENC_ERR_PIXELRANGE,

    /* resetHDVICPeveryFrame shall be 0 or 1; fatal Not supported otherwise */
    MPEG4VENC_ERR_RESETHDVICPEVERYFRAME,

    /* meType shall be 0 or 1; fatal Not supported otherwise */
    MPEG4VENC_ERR_METYPE,

    /* unrestrictedMV shall be 0 or 1; fatal Not supported otherwise */
    MPEG4VENC_ERR_UNRESTRICTEDMV,

    /* one or more of the arguments to process call is NULL : fatal
    and unsupported*/
    MPEG4VENC_ERR_IVIDENC1_PROCESS_ARGS_NULL,

    /* inArgs->size is not equal to either baseparams or extnd params : fatal
    and unsupported*/
    MPEG4VENC_ERR_IVIDENC1_INARGS_SIZE,

    /* outArgs->size is not equal to either baseparams or extnd params : fatal
    and unsupported*/
    MPEG4VENC_ERR_IVIDENC1_OUTARGS_SIZE,

    /* inArgs->inputID is equal to 0 : fatal
    and unsupported*/
    MPEG4VENC_ERR_IVIDENC1_INARGS_INPUTID,

    /* inArgs->topFieldFirstFlag is not set correctly : fatal
    and unsupported*/
    MPEG4VENC_ERR_IVIDENC1_INARGS_TOPFIELDFIRSTFLAG,

    /* inBufs elements were not set correctly : fatal
    and unsupported.error code=30*/
    MPEG4VENC_ERR_IVIDENC1_INBUFS,

    /* inBufs buffer descriptors were not set correctly : fatal
    and unsupported*/
    MPEG4VENC_ERR_IVIDENC1_INBUFS_BUFDESC,

    /* outBufs elements were not set correctly : fatal
    and unsupported*/
    MPEG4VENC_ERR_IVIDENC1_OUTBUFS,

    /* outBufs buffers are NULL.fatal and unsupported*/
    MPEG4VENC_ERR_IVIDENC1_OUTBUFS_NULL,

    /* Fatal error if process/control api is called without prior activate() */
    MPEG4VENC_ERR_CODEC_INACTIVE,

    /* Fatal error if process/control api is called without prior initializations() */
    MPEG4VENC_ERR_CODEC_NOT_INITIALIZED,

    /* If input width is not a multiple of 16 : Not supported and fatal*/
    MPEG4VENC_ERR_INPUTWIDTH_NON_MULT_OF_2,

    /* If input height is not a multiple of 16 : Not supported and fatal*/
    MPEG4VENC_ERR_INPUTHEIGHT_NON_MULT_OF_2,

    /* MPEG4VENC_TI_MIN_WIDTH <= inputWidth <= maxWidth; and */
    /* MPEG4VENC_TI_MIN_HEIGHT <= inputWidth <= maxHeight; else
    Not supported and fatal */
    MPEG4VENC_ERR_INPUTWIDTHHEIGHT,

    /* captureWidth to be 0 or >= inputWidth; otherwise not supported, fatal */
    MPEG4VENC_ERR_CAPTUREWIDTH,

    /* (generateHeader < 0) || (generateHeader > 1) not supported : fatal */
    MPEG4VENC_ERR_GENERATEHEADER,

    /* interFrameInterval shall be 0 or 1; otherwise not supported, fatal */
    MPEG4VENC_ERR_INTERFRAMEINTERVAL,

    /* (0 < BitRate <= maxBitRate); else Not supported fatal */
    MPEG4VENC_ERR_BITRATE,

    /* (refFrameRate != targetFrameRate) not supported : fatal */
    MPEG4VENC_ERR_REFFRAMERATE_MISMATCH,

    /* (0 < targetFrameRate <= maxFrameRate) and targetFrameRate shall be */
    /* multiple of 500; else Not supported fatal */
    MPEG4VENC_ERR_TARGETFRAMERATE,

    /* intraFrameInterval < 0 not supported : fatal */
    MPEG4VENC_ERR_INTRAFRAMEINTERVAL,

    /* forceFrame other than IVIDEO_NA_FRAME or IVIDEO_I_FRAME */
    /* or IVIDEO_P_FRAME.IVIDEO_IDR_FRAME not supported : fatal */
    MPEG4VENC_ERR_FORCEFRAME,

    /* No. of gob headers cannot be more than no.of MB rows in frame
    Not supported and fatal*/
    MPEG4VENC_ERR_GOBHEADER,

    /* timeScale<0 or (timeScale*1000<targetFrameRate) not supported,fatal */
    MPEG4VENC_ERR_TIMESCALE,

    /* QP value limitation from MPEG-4 standard - QP range 0 to 31
    else Not supported Not supported and fatal*/
    MPEG4VENC_ERR_INTERFRAMEQP,

    /* QP value limitation from MPEG-4 standard - QP range 0 to 31
    else Not supported Not supported and fatal.error code=50*/
    MPEG4VENC_ERR_INTRAFRAMEQP,

    /* QP value limitation from MPEG-4 standard - QP range 0 to 31
    else Not supported Not supported and fatal*/
    MPEG4VENC_ERR_INITQ,

    /* QPMAX = 31
    else Not supported Not supported and fatal*/
    MPEG4VENC_ERR_QPMAX,

    /*QPMIN = 2
    else Not supported Not supported and fatal*/
    MPEG4VENC_ERR_QPMIN,

    /* Packet size should be either 0 or more than1024 bits for */
    /* this implementation else Not supported Not supported and fatal*/
    MPEG4VENC_ERR_PACKETSIZE,

    /* Invalid AIR rate else Not supported Not supported and fatal*/
    MPEG4VENC_ERR_AIRRATE,

    /* Either 0 or 1 otherwise fatal and unsupported*/
    MPEG4VENC_ERR_4MVMODE,

    /* either 0 or 1.else Not supported Not supported and fatal*/
    MPEG4VENC_ERR_HECMODE,

    /*supported only 0 = IMP4VENC_RC_NONE , 4 - IMP4VENC_RC_CBR,*/
    /*8- IMP4VENC_RC_VBR else Not supported and fatal*/
    MPEG4VENC_ERR_RCMETHOD,

    /* max delay should be more than 100
    else Not supported and fatal*/
    MPEG4VENC_ERR_MAXDELAY,

    /* This is a reserved error code */
    MPEG4VENC_ERR_PERCEPTUALRC,

    /* invalid error code*/
    MPEG4VENC_ERR_INVALID_H263_LEVEL,

    /* mvSADoutFlag shall be 0 or 1; else not supported and fatal */
    MPEG4VENC_ERR_MV_SAD_OUT_FLAG,

    /*error code to indicate if a resolution is
    not supported for a level.*/
    MPEG4VENC_ERR_SP_LEVEL_RESOLUTION,

    /*error code to indicate if maximum target frame rate exceeded
    the frame rate associated with a particular level.*/
    MPEG4VENC_ERR_SP_LEVEL_TARGETFRAMERATE,

    /*error code to indicate if the bit rate is not
    supported for a level.*/
    MPEG4VENC_ERR_SP_LEVEL_TARGETBITRATE,

    /*error code if target bit rate exceeds that associated
    with a level or if maximum MB’s per frame is greater than 99*/
    MPEG4VENC_ERR_SP_LEVEL_MAX_MBS_MAX_BITRATE,

    /*error code if maximum encoded MB’s per second
    exceeds that associated with a level.*/
    MPEG4VENC_ERR_SP_LEVEL_MAX_ENCODED_MBS,

    /*************************************************************************/
    /* Enumeration of unsupported input warning codes                        */
    /*************************************************************************/

    /* warning code if some parameters are not conformant with the level*/
    MPEG4VENC_WARN_SP_LEVEL_DP =
        (0x1 << XDM_UNSUPPORTEDINPUT)

}IMP4VENC_STATUS;


/*
 *=============================================================================
 * IMP4HDVICPENC_Params
 *
 * This structure defines the creation parameters for all MPEG4 enc objects
 *=============================================================================
 */
typedef struct IMP4HDVICPENC_Params
{
  /*!
   * Mandatory fields of the Params structure - Base class
   */
  IVIDENC1_Params videncParams;

  /*!
   * Additional elements specific to MP4 Encoder - Extensions to base class
   */
  XDAS_Int32  MPEG4_mode ;        /* MPEG4 = 1, H.263 = 0                  */
  XDAS_Int32  levelIdc;           /* level idc                             */
  XDAS_Int32  useVOS;             /* VOS header insertion, 0 = off, 1 = on */
  XDAS_Int32  useGOV;             /* GOV header insertion, 0 = off, 1 = on */
  XDAS_Int32  useDataPartition;   /* Data partioning, 0 = off , 1 = on     */
  XDAS_Int32  useRVLC;            /* RVLC, 0 = off , 1 = on                */
  XDAS_Int32  aspectRatio;        /* Aspect ration info                    */
  XDAS_Int32  pixelRange;         /* video_range=0 : Y from 16 to 235,
                                     Cb and Cr from 16 to 240;
                                     video_range=1 : Y from 0 to 255,
                                     Cb and Cr from 0 to 255.              */
  XDAS_Int32  timerResolution;    /* Timer resolution - clock ticks per sec*/
  //XDAS_Int32  reset_vIMCOP_every_frame;
  XDAS_Int32  ME_Type;            /* Switch for ME type option             */
  XDAS_Int32  UMV;                /* Switch for un-restricted MV option    */
  XDAS_Int32  EncQuality_mode;
  void        *hdvicpHandle;      /* HDVICP related handle onject          */

  //IDMA_DM510_Params DmaParams;    /* Structure DMA params from app         */

} IMP4HDVICPENC_Params;

/*
 *=============================================================================
 * IMPEG4VENC_PARAMS
 *
 * Default parameter values for MP4enc instance objects
 *=============================================================================
 */
extern IMP4HDVICPENC_Params IMPEG4VENC_PARAMS;

/*
 *=============================================================================
 *  IVIDENC_InArgs:
 *  This structure defines the run time arguments for all VIDENC objects.
 *  This structure may be extended by individual codec implementation
 *  allowing customization with vendor specific parameters.
 *=============================================================================
 */
typedef struct IMP4HDVICPENC_InArgs
{
  /*!
   * Mandatory fields of the InArgs structure - Base class
   */
  IVIDENC1_InArgs   videncInArgs;

  /*!
   * Additional elements specific to MP4 Encoder - Extensions to base class
   */
  XDAS_UInt32        TimeStamp;   /*   Time stamp value of the frame to be
                                       put in bitstream  */

}IMP4HDVICPENC_InArgs;

/*
 *=============================================================================
 * IMP4HDVICPENC_DynamicParams
 *
 * This structure defines the run time parameters for all MP4enc objects
 *=============================================================================
 */
typedef struct IMP4HDVICPENC_DynamicParams
{
  /*!
   * Mandatory fields of the DynamicParams structure - Base class
   */
  IVIDENC1_DynamicParams videncDynamicParams;

  /*!
   * Additional elements specific to MP4 Encoder - Extensions to base class
   */
  XDAS_Int32  Four_MV_mode;
  XDAS_Int32  PacketSize;   /*Packet size in bits, 0 means No packets
                              i.e. whole frame in one packet                */
  XDAS_Int32  qpIntra;      /* default QP for I frame : QPI,  range 2 to 31 */
  XDAS_Int32  qpInter;      /* default QP for P frame, range 2 to 31        */
  XDAS_Int32  airRate;      /* Adaptive Intra refresh of n MBs per frame    */
  XDAS_Int32  useHEC;       /* HEC, 0 = off , 1 = on                        */
  XDAS_Int32  useGOBSync;   /* chanes frequency of GOB headers i.e.
                               0: GOB header for none, x : for every xth row*/
  XDAS_Int32  RcAlgo;       /* Rate Control Method,
                               0: disable rate control, 4-CBR,  8-VBR       */
  XDAS_Int32  QPMax;        /* Maximum QP to be used  Range[2,31]           */
  XDAS_Int32  QPMin;        /* Minimum QP to be used  Range[2,31]           */
  XDAS_Int32  maxDelay;     /* max delay for rate control interms of ms,
                                set it to 1000 for 1 second delay           */
  XDAS_Int32  qpInit;       /* max delay for rate control interms of ms,
                                set it to 1000 for 1 second delay           */
  XDAS_Int32  PerceptualRC; /* This is a reserved parameter */
  XDAS_Int32  reset_vIMCOP_every_frame;/*reset_vIMCOP_every_frame flag to reset on/off */
  XDAS_Int32  mvSADoutFlag;             /* Flag for enable/disable MVSAD out to the app */
} IMP4HDVICPENC_DynamicParams;   /* initial QP for first frame                   */


/**===========================================================================
*@struct IMP4HDVICPENC_exportMEdata
*
*@desc   This structure defines structure for exporting ME info: Motion vectors and ME Sad
*
*
*@note   None
*
*=============================================================================
*/
typedef struct _IMP4HDVICPENC_exportMEdata
{
    XDAS_Int32 meSad;
    XDAS_Int16 mvX;
    XDAS_Int16 mvY;
}IMP4HDVICPENC_exportMEdata;


/*
 *=============================================================================
 *  IMP4HDVICPENC_OutArgs:
 *  This structure defines the run time output arguments for IMP4VENC
 *  instance objects.
 *  This structure may be extended by individual codec implementation
 *  allowing customization with vendor specific parameters.
 *=============================================================================
 */
typedef struct IMP4HDVICPENC_OutArgs
{
  /*!
   * Mandatory fields of the OutArgs structure - Base class
   */
  IVIDENC1_OutArgs  videncOutArgs;

  /*!
   * Additional elements specific to MP4 Encoder - Extensions to base class
   */
  /* Pointer to communicate the Packet sizes in a Frame between
   * the Encoder and the Application
   */
   XDAS_Int32  *packetSize;

  /* Variable to communicate the total number of packets in a Frame
   * between the Encoder and the Application
   */
   XDAS_Int32  numPackets;

} IMP4HDVICPENC_OutArgs;

/*
 *=============================================================================
 * IMP4HDVICPENC_Fxns
 *
 * This structure defines all of the operations on MP4enc objects
 *=============================================================================
 */
typedef struct IMP4HDVICPENC_Fxns
{
  /*!
   * Mandatory functions of the function table - Base class
   */
    IVIDENC1_Fxns  ividenc;

} IMP4HDVICPENC_Fxns;

#endif  /* __IMP4HDVICPENC__ */
