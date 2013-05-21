/*
****************************************************************************

    FILE NAME : IVC1VDEC.h

    ALGORITHM : VC1VDEC

    VENDOR    : TI

    TARGET DSP: DM510

    PURPOSE   : IVC1VDEC Interface Header

****************************************************************************
*/

#ifndef IVC1VDEC_
#define IVC1VDEC_
#include <ti/xdais/xdas.h>
//#include <ti/xdais/ialg.h>
//#include <ividdec1.h>
#include <ti/xdais/dm/ividdec2.h>

/*
// ***************************************************************************
// IVC1VDEC_Obj
//
// This structure must be the first field of all VC1VDEC instance objects
*/
typedef struct IVC1VDEC_Obj {
    struct IVC1VDEC_Fxns *fxns;
} IVC1VDEC_Obj;

/*
// ***************************************************************************
// IVC1VDEC_Handle
//
// This handle is used to reference all VC1VDEC instance objects
*/
typedef struct IVC1VDEC_Obj *IVC1VDEC_Handle;


/*
// ***************************************************************************
// IVC1VDEC_Status
//
// Status structure defines the parameters that can be changed or read
// during real-time operation of the alogrithm.
*/
typedef struct IVC1VDEC_Status {
    IVIDDEC2_Status  viddecStatus;

    /* Add more  */

} IVC1VDEC_Status;

/*
// ***************************************************************************
// IVC1VDEC_Cmd
//
// The Cmd enumeration defines the control commands for the VC1 Video decoder
// control method.
*/
typedef IVIDDEC2_Cmd IVC1VDEC_Cmd;

/*
// ***************************************************************************
// control method commands
*/
#define IVC1VDEC_GETSTATUS      XDM_GETSTATUS
#define IVC1VDEC_SETPARAMS      XDM_SETPARAMS
#define IVC1VDEC_RESET          XDM_RESET
#define IVC1VDEC_FLUSH          XDM_FLUSH
#define IVC1VDEC_SETDEFAULT     XDM_SETDEFAULT
#define IVC1VDEC_GETBUFINFO     XDM_GETBUFINFO

/* Example of extension of command ID, starting with 256 on ward  */
#define IVC1VDEC_PREPROCESS   257    /* internal preprocssing for noise revomal */
#define IVC1VDEC_YUV_420IUV   256    /* 420 Chroma Format with UV interleaved */
#define IVC1VDEC_YUV_420SP    XDM_YUV_420SP    /* 420 Chroma Format with UV interleaved */



/*
// ***************************************************************************
// IVC1VDEC_Params
//
// This structure defines the creation parameters for all VC1VDEC objects
*/
typedef struct IVC1VDEC_Params {
    IVIDDEC2_Params viddecParams; /* must be followed for all video encoders */
    /* Add more  */
/*
 * display delay will whether to disply in display order or decode order
 */

    XDAS_Int32  display_delay;
    //IDMA_DM510_Params Dma_DynamicParams;
/*
 * HDVICP related handle object
 */
    void *hdvicpHandle;

    XDAS_Int8 rcvParseInLib;
    XDAS_Int8 streamType;   /* 0 - Default(stream type decided in library itself-normal case
    						   1 - RCV
    						   2 - AP */

} IVC1VDEC_Params;
/*
// ***************************************************************************
// IVC1VDEC_PARAMS
//
// Default parameter values for VC1VDEC instance objects
*/
extern IVC1VDEC_Params IVC1VDEC_PARAMS;

/*
 *  ******** IVIDDEC_InArgs ********
 *  This structure defines the run time arguments for all VIDDEC objects.
 *  This structure may be extended by individual codec implementation
 *  allowing customization with vendor specific parameters.
 */
typedef struct IVC1VDEC_InArgs {
    IVIDDEC2_InArgs   viddecInArgs;/* must be followed for all video encoders */
    /* Add more  */

}IVC1VDEC_InArgs;

/*
// ***************************************************************************
// IVC1VDEC_DynamicParams
//
// This structure defines the run time parameters for all VC1VDEC objects
*/
typedef struct IVC1VDEC_DynamicParams {
    IVIDDEC2_DynamicParams viddecDynamicParams; /* must be followed for all video encoders */
/* TODO : add on  algorithm & vendor specific parameters here
 * Recommandations : segregare into two parts , creation time folloed by
 * runtime parameters
 */
/*
 * When Out loop deblock is needed for simple profile this
 * flag must be set. Out loop deblocking can be controlled
 * dynamically at frame level
 */
    XDAS_Int32  outloopDeblocking;
/*
 *  Flag to used for resetting the kaleido
 *  for each frame or resetting at sequence level
 */
    XDAS_Int8 reset_HDVICP_every_frame;

/*
 * Add more
 */


} IVC1VDEC_DynamicParams;


/*
 *  ******** IVC1VDEC_OutArgs ********
 *  This structure defines the run time output arguments for IVC1VDEC
 *  instance objects.
 *  This structure may be extended by individual codec implementation
 *  allowing customization with vendor specific parameters.
 */
typedef struct IVC1VDEC_OutArgs {
    IVIDDEC2_OutArgs  viddecOutArgs;  /* must be followed for all video encoders */
/*
 * NOTE : VC1 decoder on DM510 supporst only simple and main profiles.
 * Pixel aspect ratio is specified only in advanced profile.
 * Pixel aspect ratio will always be 1:1
 * Pixel range is always 0 - 255.
 */
    XDAS_UInt8        pixelRange;  /* pixelRange=0 gives a range of Y from  */
                                   /* 16 to 235, Cb and Cr from 16 to 240    */
                                   /* pixelRange=1 gives a range of Y from  */
                                   /* 0 to 255, Cb and Cr from 0 to 255.      */
    XDAS_UInt16       parWidth;
    XDAS_UInt16       parHeight;
    XDAS_Int8         rangeYScale; /* Luma Scale for expanding the pixel
 	                                * range. If it is 1 or 2. If 1 dont
                                    * do range expansion, if 2 multiply
                                    * all pixels by 2.
                                    */
    XDAS_Int8         rangeUVScale;/* Chroma Scale for expanding the pixel
                                    * range. If it is 1 or 2. If 1 dont
                                    * do range expansion, if 2 multiply
                                    * all pixels by 2.
                                    */
/*
 * Number of Macroblocks decoded with error is update in below field
 */
    XDAS_UInt16             numErrMbs;

    /* Add more  */


} IVC1VDEC_OutArgs;
/*
// ***************************************************************************
// IVC1VDEC_Fxns
//
// This structure defines all of the operations on VC1VDEC objects
*/
typedef struct IVC1VDEC_Fxns {
    IVIDDEC2_Fxns    ividdec;    /* IVC1VDEC extends IVIDDEC object.
                                    Should be second set of functions */
    /* Add more  */
} IVC1VDEC_Fxns;


/*!
 * ---------------------------- FUNCTION DECLARATIONS -----------------------------
 */

/*
 *  ======== VC1VDEC_TI_IVC1VDEC ========
 *  TI's implementation of the IVC1VDEC interface
 */
extern IVC1VDEC_Fxns VC1VDEC_TI_IVC1VDEC;

/*
 * Base class IALG functions
 */
extern IVIDDEC2_Fxns VC1VDEC_TI_IVIDDECFUNCTIONS;

extern Int VC1VDEC_TI_init(IALG_Handle handle, const IALG_MemRec *memTab,
                         IALG_Handle par_handle, const IALG_Params *params);

extern XDAS_Int32  VC1VDEC_TI_decode (IVIDDEC2_Handle handle,
        XDM1_BufDesc *inptr, XDM_BufDesc *outptr,
        IVIDDEC2_InArgs *inargs, IVIDDEC2_OutArgs *outargs);


extern Void VC1VDEC_TI_exit(Void);


/* error codes for VC1 decoder */
typedef enum IVC1VDEC_ExtendedError{
IVC1VDEC_EX_ERR_RESOLUTION_NOT_SUPPORTED =  0x1,
IVC1VDEC_EX_ERR_BITSTREAM_ERROR = 0x2,
IVC1VDEC_EX_ERR_UNSUPPORTED_PICTURE = 0x3,
IVC1VDEC_EX_ERR_INVALID_ARG_IN_PROCESSCALL = 0x4,
IVC1VDEC_EX_ERR_INVALID_IMPLEMENTATION_ID = 0x5,
IVC1VDEC_EX_ERR_INVALID_CODEC_ID = 0x6,
IVC1VDEC_EX_ERR_ALGO_NOT_ACTIVATED = 0x7,
IVC1VDEC_EX_ERR_RESOURCE_NOT_INITIALIZED = 0x8,
IVC1VDEC_EX_ERR_INVALID_INPUT_BUFFER_ID = 0x9,
IVC1VDEC_EX_ERR_OUTBUF_SIZE_INSUFFICIENT = 0xA,
IVC1VDEC_EX_ERR_NO_SYNC_MARKER = 0xB,
IVC1VDEC_EX_ERR_INSUFFICIENT_DATA = 0xC,
IVC1VDEC_EX_ERR_NUMBFRAMES_NONZERO_BUT_DISPLAYDELAY_IS_0 = 0xD,
IVC1VDEC_EX_ERR_INVALID_ALTPQUANT_VALUE = 0xE,
IVC1VDEC_EX_ERR_INVALID_BUFFER_FULLNESS = 0xF,
IVC1VDEC_EX_ERR_RESPIC_NOT_ZERO = 0x10,
IVC1VDEC_EX_ERR_INVALID_BITPLANE_DATA = 0x11,
IVC1VDEC_EX_ERR_SEQ_PROFILE_INVALID = 0x12,
IVC1VDEC_EX_ERR_SEQ_LEVEL_INVALID = 0x13,
IVC1VDEC_EX_ERR_SEQ_INVALID_CHROMA_FORMAT = 0x14,
IVC1VDEC_EX_ERR_SEQ_LOOP_FILTER_IN_SP = 0x15,
IVC1VDEC_EX_ERR_SEQ_EXTENDED_MV_IN_SP = 0x16,
IVC1VDEC_EX_ERR_SEQ_INVALID_DQUANT = 0x17,
IVC1VDEC_EX_ERR_SEQ_RANGERED_SET_IN_SP = 0x18,
IVC1VDEC_EX_ERR_INTENSITY_COMP_ENABLED_IN_SP = 0x19,
IVC1VDEC_EX_ERR_INVALID_QUANT_PARAMS = 0x1A,
IVC1VDEC_EX_ERR_SEQ_DQUANT_NONZERO_IN_SP  = 0x1B,
IVC1VDEC_EX_ERR_SEQ_SYNC_MARKER_NONZERO_IN_SP = 0x1C,

/*this value should not be changed*/
IVC1VDEC_EX_ERR_INVALID_FRAMEHEADER_IN_SLICE = 0x1D,
IVC1VDEC_EX_ERR_INVALID_ARG_IN_CONTROL_CALL = 0x1E,
IVC1VDEC_EX_ERR_NO_REF_AVAILABLE = 0x1F,
IVC1VDEC_EX_ERR_INVALID_SEQHDR = 0x20,
IVC1VDEC_EX_ERR_IN_START_OF_FRAME = 0x21,
IVC1VDEC_EX_ERR_IN_MB_DATA = 0x22,
IVC1VDEC_EX_ERR_INVALID_DISPLAY_WIDTH = 0x23,
IVC1VDEC_EX_ERR_DISPLAY_WIDTH_NOT_MULTIPLE_OF_32 = 0x24,
IVC1VDEC_EX_ERR_DISPLAY_WIDTH_DYNAMIC_CHANGE_INVALID = 0x25,
IVC1VDEC_EX_ERR_RESOURCE_INIT_NOT_DONE = 0x26,
IVC1VDEC_EX_ERR_ALL_RESOURCES_NOT_ACTIVATED = 0x27,
IVC1VDEC_EX_ERR_INVALID_FRAME_SIZE = 0x28,
IVC1VDEC_EX_ERR_INTERLACE_NOT_SUPPORTED = 0x29,
IVC1VDEC_EX_ERR_CHANGE_IN_RESOLUTION_NOTSUPPORTED = 0x2A,
IVC1VDEC_EX_ERR_HEADER_NOT_FOUND = 0x2B,
IVC1VDEC_EX_ERR_INVALID_DECODEHEADER_PARAM = 0x2C,
IVC1VDEC_EX_ERR_INVALID_FRAMESKIP_PARAM = 0x2D,
IVC1VDEC_EX_ERR_INVALID_FRAMEORDER_PARAM = 0x2E,
IVC1VDEC_EX_ERR_INVALID_MBDATAFLAG_PARAM = 0x2F,
IVC1VDEC_EX_ERR_INVALID_NEWFRAMEFLAG_PARAM = 0x30,
IVC1VDEC_EX_ERR_INVALID_RESETHDVICP_PARAM = 0x31,
IVC1VDEC_EX_ERR_INAVLID_DISPLAYWIDTH_WHEN_OUTLOOP_DEBLK_ENABLED = 0x32,
IVC1VDEC_EX_ERR_FRAMEORDER_DYNAMIC_CHANGE_INVALID = 0x33,
IVC1VDEC_EX_ERR_OUTLOOP_DBLK_DYNAMIC_CHANGE_INVALID = 0x34,
IVC1VDEC_EX_ERR_INCOMPLETE_FRAME = 0x35,
IVC1VDEC_EX_ERR_DISPLAYBUF_NOT_ALIGNED = 0x36,
IVC1VDEC_EX_ERR_INVALID_OUTLOOP_DBLK_PARAM = 0x37,
IVC1VDEC_EX_ERR_VALID_FRAMESTARTCODE_INVALID_SEQ_HDR = 0x38,
IVC1VDEC_EX_ERR_NO_START_CODE_FOUND = 0x39,
IVC1VDEC_EX_ERR_BFRAME_PRESENT_BUT_DISPLAYDELAY_IS_0 = 0x3A
/*max error code value is 0x7f,as the 8th bit is used indicate the status of reference frame*/
}IVC1VDEC_ExtendedError;

#define ERR_INREF_FRAME 7
#endif  /* IVC1VDEC_ */
