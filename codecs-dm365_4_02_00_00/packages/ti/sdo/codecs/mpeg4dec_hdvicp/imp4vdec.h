/** ==========================================================================
 *  @file   imp4vdec.h
 *
 *  @path   $(PROJDIR)\Inc
 *
 *  @desc   This file provides definisions for the interface handles.
 *
 *  ==========================================================================
 *  Copyright (c) Texas Instruments Inc 2006, 2007
 *
 *  Use of this software is controlled by the terms and conditions found
 *  in the license agreement under which this software has been supplied
 * =========================================================================*/

/* -------------------- compilation control switches ---------------------- */

#ifndef Imp4VDEC_
#define Imp4VDEC_


/****************************************************************************
*   INCLUDE FILES
*****************************************************************************/
/* -------------------- system and platform files ------------------------- */
/* ------------------------- program files -------------------------------- */
#include <ti/xdais/xdas.h>
#include <ti/xdais/ialg.h>
#include <ti/xdais/dm/ividdec2.h>
//#include <idma_dm510.h>

/****************************************************************************
*   EXTERNAL REFERENCES NOTE : only use if not found in header file
*****************************************************************************/
/* ------------------------ data declarations ----------------------------- */
/* ----------------------- function prototypes ---------------------------- */

/****************************************************************************
*   PUBLIC DECLARATIONS Defined here, used elsewhere
*****************************************************************************/
/* ----------------------- data declarations ------------------------------ */

/*!
*****************************************************************************
*@typedef status_flags
*
*@brief  This enum has error or bit stream status
*
*@note   None
*
*****************************************************************************/

enum IMPEG4VDEC_status_flags
{
    NO_FAULT,
    FAULT,
    FAULT_RVLC,
    MV_FAULT,
    MBHEADER_FAULT,
    PACKET_FAULT,
    END_PACKET,
    END_VOP,
    END_GOV,
    END_VOL,
    END_VO,
    END_VOS
};
/* Description of extnd_error flags */

enum IMPEG4VDEC_extend_error
{
    /* Errors in handle/arguments to process and control calls */

    IMPEG4VDEC_EX_ERR_INV_IMPL_ID                   = 1,          /* Invalid implementationId seen in handle structure */
    IMPEG4VDEC_EX_ERR_INV_CONTXT                    = 2,          /* Invalid codec context in the handle structure */
    IMPEG4VDEC_EX_ERR_INV_CODEC_ID                  = 3,          /* Invalid codec ID in the handle */
    IMPEG4VDEC_EX_ERR_ALGO_INACTIVE                 = 4,          /* algActivate not called before control */
    IMPEG4VDEC_EX_ERR_ERR_RESOURCE_INIT_NOT_DONE    = 5,          /* process or control called before initResources was successfully completed */
    IMPEG4VDEC_NOTALL_RES_ACTIVE                    = 6,          /* Not all resources were activated before calling process/control */

    /* Errors in arguments to control call */
    IMPEG4VDEC_EX_ERR_INV_STATUS_SIZE        = 10,           /* Size of status structure is not valid */
    IMPEG4VDEC_EX_ERR_INV_HANDLE             = 11,           /* Invalid handle passed */
    IMPEG4VDEC_EX_ERR_INV_DYN_PARAMS         = 12,           /* Invalid dynamic params structure passed */
    IMPEG4VDEC_EX_ERR_VER_ERR_INSUFF_BUFSIZE = 13,          /* Insufficient bufSize passed for GETVERSION call - 128 bytes is the minBufSize */


    IMPEG4VDEC_EX_ERR_INV_DBLK_VAL          = 14,           /* Invalid value passed for outloopDeblocking param */
    IMPEG4VDEC_EX_ERR_INV_DRNG_VAL          = 15,           /* Invalid value passed for outloopDeringing param */
    IMPEG4VDEC_EX_ERR_INV_DEC_HEADR_MODE    = 16,           /* Invalid value passed for decodeHeader param */
    IMPEG4VDEC_EX_ERR_ERR_FRAME_PITCH       = 17,           /* Invalid value passed for displayWidth param, greater than maxWidth, non-multiple of 32 etc */
    IMPEG4VDEC_EX_ERR_ERR_FRAME_ORDER       = 18,           /* Invalid value passed for decodeOrder param */
    IMPEG4VDEC_EX_ERR_INV_FRM_SKIP_MODE     = 19,            /* Invalid value passed for frmaeSkipMode param */
    IMPEG4VDEC_EX_ERR_INV_RESET_HDVICP      = 20,            /* Invalid value passed for resetHDVICPeveryFrame param */
    IMPEG4VDEC_EX_ERR_DEBLK_MORE_THAN_CIF   = 21,            /* Deblocking and Deringing enabled for a stream larger than CIF */
    IMPEG4VDEC_EX_ERR_INV_MBDATAFLAG_PARAM  = 22,            /* MBData Flag is not supported */
    IMPEG4VDEC_EX_ERR_INV_NEWFRAMEFLAG_PARAM= 23,            /* New Frame flag is not supported */


    IMPEG4VDEC_EX_ERR_DEBLK_RUNTIME_CHANGE_NOT_SUPPORTED    = 25,  /* Runtime configuration of Deblocking not supported */
    IMPEG4VDEC_EX_ERR_DERING_RUNTIME_CHANGE_NOT_SUPPORTED   = 26,  /* Runtime configuration of deRinging not supported */
    IMPEG4VDEC_EX_ERR_DISP_WD_RUNTIME_CHANGE_NOT_SUPPORTED  = 27,  /* Runtime configuration of dsiplayWidth not supported */
    IMPEG4VDEC_EX_ERR_FRM_ORDER_RUNTIME_CHANGE_NOT_SUPPORTED= 28,  /* Runtime configuration of frameOrder not supported */


    IMPEG4VDEC_EX_ERR_NULL_ARGS                 = 30,               /* Null arguments to process */
    IMPEG4VDEC_EX_ERR_INVALID_ARG_SIZES         = 31,               /* Invalid size of inargs or outargs */
    IMPEG4VDEC_EX_ERR_INVALID_BITS_BUF          = 32,               /* Invalid size/NULL buf passed as bitstream buffer */
    IMPEG4VDEC_EX_ERR_INVALID_YUV_BUF           = 33,               /* Invalid size/NULL buf passed as YUV buffer */
    IMPEG4VDEC_EX_ERR_INVALID_NUM_BYTES         = 34,               /* Invalid value for inargs->numBytes */

    /* Benign error while decoding sequence/frame headers */
    IMPEG4VDEC_EX_ERR_UNSUPP_PROFILE            = 40,   /* Unsupported profile found while decoding sequence header*/
    IMPEG4VDEC_EX_ERR_VISUAL_OBJ_NOT_SUPP       = 41,   /* Unsupported Visual Object found */
    IMPEG4VDEC_EX_ERR_CHROMA_FORMAT_NOT_SUPP    = 42,   /* Unsupported Chroma Format*/
    IMPEG4VDEC_EX_ERR_VOL_SHAPE_INVALID         = 43,   /* Invalid VOL Shape found*/
    IMPEG4VDEC_EX_ERR_OBMC_NOT_SUPPORTED        = 44,   /* OBMC is not supported. The flag will be ignored and normal motion compensation will be done */
    IMPEG4VDEC_EX_ERR_GUC_ESTIMATION_METHOD     = 45,   /* if video_object_layer_verid > 1, estimation_method is unsupported  */
    IMPEG4VDEC_EX_ERR_GOV_HDR_FOLL_BY_NONI      = 46,   /* GOV starts with non-I frame */
    IMPEG4VDEC_EX_ERR_VOL_VERID_INVALID         = 47,   /* Invalid vol_verifier */
    IMPEG4VDEC_EX_ERR_ASPECT_RATIO_INFO_INV     = 48,   /* Invalid ASPECT Ration Info */
    IMPEG4VDEC_EX_ERR_VOP_TIME_INCRE_ZERO       = 49,   /* VOP Time increment set to Zero */
    IMPEG4VDEC_EX_ERR_FIX_VOP_TIME_INCRE_ZERO   = 50,   /* Fixed VOP increment is set to Zero */
    IMPEG4VDEC_EX_ERR_SPRITE_CODING_UNSUPP      = 51,   /* Sprite enabled stream found */
    IMPEG4VDEC_EX_ERR_UNALIGNED_DISP_BUF        = 52,   /* Display buffer base addresses are not aligned */
    IMPEG4VDEC_EX_ERR_B_PRESENT_IN_LOW_DELAY    = 53,   /* B frame present when display_delay was set to 0, i.e. decode order dump mode */
    IMPEG4VDEC_EX_ERR_SPRITE_ENABLED_FRAME      = 54,       /* Sprite enabled frame. This will be treated as not-coded vop */


    /* Header is marked as corrupt and decoder resumes to look for another header for the following*/
    IMPEG4VDEC_EX_ERR_NOT_8_BIT_UNSUPP          = 60,       /* not_8_bit flat set */
    IMPEG4VDEC_EX_ERR_REDUCED_RESLN_VOP_ENBL    = 61,       /* Reduced resolution mode not supported */
    IMPEG4VDEC_EX_ERR_SCALABLE_CODING_UNSUPP    = 62,       /* Scalability not supported */
    IMPEG4VDEC_EX_ERR_FAULT_VOP_HDR             = 64,       /* Error in decoding VOP header */
    IMPEG4VDEC_EX_ERR_PTYPE_UNSUPP_BASE_PROF    = 65,       /* Extended PTYPE not supported in short video header stream */
    IMPEG4VDEC_EX_ERR_H263_UNSUPP_DIMENSIONS    = 66,       /* Unsupported dimensions seen in short_video header */
    IMPEG4VDEC_EX_ERR_H263_UNSUPP_SRCFRMT_DIM   = 67,       /* Invalid value for source format in short_video_header */
    IMPEG4VDEC_EX_ERR_INV_H263_OR_MPEG4_STR     = 68,       /* Not a valid H263 or MPEG4 stream */
    IMPEG4VDEC_EX_ERR_B_S_VOP_UNSUPP_SMPL_PRO   = 69,       /* SVOP seen in simple profile complexity estimatation header decode */
    IMPEG4VDEC_EX_ERR_HEADER_NOT_FOUND          = 72,       /* Header not found in the given buffer */
    IMPEG4VDEC_EX_ERR_NEWPRED_NOT_SUPP          = 73,   /* NEW Pred not supported */


    IMPEG4VDEC_EX_ERR_PACK_HDR              = 80,           /* Error while decoding video packet header */
    IMPEG4VDEC_EX_ERR_MB_HDR                = 81,           /* Error while decoding MB header */
    IMPEG4VDEC_EX_ERR_HEIGHT_SMALLER        = 82,           /* Height smaller than 48 */
    IMPEG4VDEC_EX_ERR_WIDTH_SMALLER         = 83,           /* Width smaller than 48 */
    IMPEG4VDEC_EX_ERR_VOL_WIDTH_INVALID     = 84,           /* Width decoded from the stream is invalid- either greater than max width or equal to zero */
    IMPEG4VDEC_EX_ERR_VOL_HEIGHT_INVALID    = 85,           /* Height decoded from the stream is invalid- either greater than max width or equal to zero */
    IMPEG4VDEC_EX_ERR_VOP_NOTCODED_DEC_START= 86,           /* Stream starts with a not-coded VOP */
    IMPEG4VDEC_EX_ERR_BLKDATA               = 87,           /* Error while decoding block data by ECD */
    IMPEG4VDEC_EX_ERR_WIDTH_NON_MULT2       = 88,           /* Width non-multiple of 2 - Benign error */
    IMPEG4VDEC_EX_ERR_HEIGHT_NON_MULT2      = 89            /* Height non-multiple of 2 - Benign error */

};

/** ==========================================================================
 *  @name   Imp4VDEC_Obj
 *
 *  @desc   This structure must be the first field of all mp4VDEC instance
 *           objects
 *
 *  @field  fxns
 *          Handle to extented mpeg4 video decoder library interface functions
 *
 *  @see    None
 *  ==========================================================================
 */
typedef struct Imp4VDEC_Obj
{
    struct Imp4VDEC_Fxns *fxns;
} Imp4VDEC_Obj;

/** ==========================================================================
 *  @name   Imp4VDEC_Handle
 *
 *  @desc   This handle is used to reference all mp4VDEC instance objects
 *
 *  @see    None
 *  ==========================================================================
 */
typedef struct Imp4VDEC_Obj *Imp4VDEC_Handle;

/** ==========================================================================
 *  @name   Imp4VDEC_Status
 *
 *  @desc   Status structure defines the parameters that can be changed or
 *          read during real-time operation of the alogrithm.
 *
 *  @field  viddecStatus
 *          Handle to base class status struture which defines the all
 *          run time parameters.
 *
 *  @see    None
 *  ==========================================================================
 */
typedef struct Imp4VDEC_Status
{
    IVIDDEC2_Status  viddecStatus;
    /* Add more  */
} Imp4VDEC_Status;

/** ==========================================================================
 *  @name   Imp4VDEC_Cmd
 *
 *  @desc   The Cmd enumeration defines the control commands for the MPEG4
 *          video decoder control method.
 *
 *  @see    None
 *  ==========================================================================
 */
typedef IVIDDEC2_Cmd Imp4VDEC_Cmd;

/** ==========================================================================
 *  @name   Imp4VDEC_Params
 *
 *  @desc   This structure defines the creation parameters for all
 *          mp4VDEC objects
 *
 *  @field  viddecParams
 *          Defines the creation time parameters for
 *          all IVIDDEC2 instance objects.
 *
 *  @field  hdvicpHandle
 *          Handle to HDVICP Framework related data declarations
 *
 *  @field  dmaParams
 *          Handle for structure to store all the attributes required for
 *          client to init DMA
 *
 *  @see    None
 *  ==========================================================================
 */
typedef struct Imp4VDEC_Params
{
    IVIDDEC2_Params    viddecParams; /* must be followed for                */
                                     /* all video decoders                  */
    /* Add more  */
    /* Display delay will decide the initial delay before which decode call */
    /* starts  */
    XDAS_Int32         displayDelay;
    void               *hdvicpHandle;
    //IDMA_DM510_Params  dmaParams;
    XDAS_Int8 disableHDVICPeveryFrame;


} Imp4VDEC_Params;

/** ==========================================================================
 *  @name   IMPEG4VDEC_PARAMS
 *
 *  @desc   Default parameter values for mp4VDEC instance objects
 *
 *  @see    None
 *  ==========================================================================
 */
extern Imp4VDEC_Params IMPEG4VDEC_PARAMS;

/** ==========================================================================
 *  @name   Imp4VDEC_DynamicParams
 *
 *  @desc   This structure defines the run time parameters for all
 *          mp4VDEC objects
 *
 *  @field  viddecDynamicParams
 *          Defines the ru time parameters for
 *          all IVIDDEC2 instance objects.
 *
 *  @field  outloopDeblocking
 *          This variable will be updated by client for each process call
 *          for enabling or disabling Outloop de-blocking.
 *
 *  @field  outloopDeRinging
 *          This variable will be updated by client for each process call
 *          for enabling or disabling Outloop de-ringing.
 *
 *  @see    None
 *  ==========================================================================
 */
typedef struct Imp4VDEC_DynamicParams
{
    IVIDDEC2_DynamicParams viddecDynamicParams; /* must be followed for     */
                                                /* all video encoders       */
    /* Add more  */
    XDAS_Int32             outloopDeblocking;
    XDAS_Int32             outloopDeRinging;

    XDAS_Int8              resetHDVICPeveryFrame;
} Imp4VDEC_DynamicParams;

/** ==========================================================================
 *  @name   Imp4VDEC_InArgs
 *
 *  @desc   This structure defines the run time input arguments for all VIDDEC
 *          objects.This structure may be extended by individual codec
 *          implementation allowing customization with vendor specific
 *          parameters.
 *
 *  @field  viddecInArgs
 *          Defines the input arguments for all IVIDDEC2 instance
 *          process function.
 *
 *  @see    None
 *  ==========================================================================
 */
typedef struct Imp4VDEC_InArgs
{
    IVIDDEC2_InArgs   viddecInArgs; /* must be followed for                 */
                                    /* all video decoders                   */
    /* Add more  */

}Imp4VDEC_InArgs;

/** ==========================================================================
 *  @name   Imp4VDEC_OutArgs
 *
 *  @desc   This structure defines the run time output arguments for VIDDEC
 *          objects.This structure may be extended by individual codec
 *          implementation allowing customization with vendor specific
 *          parameters.
 *
 *  @field  viddecOutArgs
 *          Defines the output arguments for all IVIDDEC2 instance
 *          process function.
 *
 *  @see    None
 *  ==========================================================================
 */
typedef struct Imp4VDEC_OutArgs
{
    IVIDDEC2_OutArgs  viddecOutArgs;  /* must be followed for               */
                                      /* all video decoders                 */
    /* Add more  */
    XDAS_UInt8        pixelRange;  /* pixelRange=0 gives a range of Y from  */
                                   /* 16 to 235, Cb and Cr from 16 to 240   */
                                   /* pixelRange=1 gives a range of Y from  */
                                   /* 0 to 255, Cb and Cr from 0 to 255.    */
    XDAS_UInt16        parWidth;
    XDAS_UInt16        parHeight;
    XDAS_UInt16        numErrMbs;
    XDAS_UInt16        mode;       /* 1: MPEG4; 0 : H.263                   */
}Imp4VDEC_OutArgs;

/** ==========================================================================
 *  @name   Imp4VDEC_Fxns
 *
 *  @desc   This structure defines all of the operations on mp4VDEC objects.
 *
 *  @field  ividdec
 *          handle to the all function of the operations on IVIDDEC2 objects
 *
 *  @see    None
 *  ==========================================================================
 */
typedef struct Imp4VDEC_Fxns
{
    IVIDDEC2_Fxns    ividdec;    /* Imp4VDEC extends IVIDDEC object.
                                    Should be second set of functions */
    /* Add more  */
} Imp4VDEC_Fxns;
/* ---------------------- function prototypes ----------------------------- */
/****************************************************************************
*   PRIVATE DECLARATIONS Defined here, used only here
*****************************************************************************/
/* ---------------------- data declarations ------------------------------- */
/* --------------------- function prototypes ------------------------------ */

/* ---------------------------- macros ------------------------------------ */
/* Extending control method commands                                        */
#define Imp4VDEC_GETSTATUS      XDM_GETSTATUS
#define Imp4VDEC_SETPARAMS      XDM_SETPARAMS
#define Imp4VDEC_RESET          XDM_RESET
#define Imp4VDEC_FLUSH          XDM_FLUSH
#define Imp4VDEC_SETDEFAULT     XDM_SETDEFAULT
#define Imp4VDEC_GETBUFINFO     XDM_GETBUFINFO

/* Extending Chroma Formates                                                */
#define Imp4VDEC_YUV_420SP        XDM_YUV_420SP


#endif  /* Imp4VDEC_ */



/*!
 *! Revision History
 *! ================
 *! 27-Aug-2007   Kumar    : Incorporated code review comments.
 *! 01-Jul-2006   Prashanth: Created.
 *!
 */
