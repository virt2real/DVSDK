/*
 ******************************************************************************
 *  
 * DM36x Based H.264 Decoder
 *
 * "DM36x Based H.264 Decoder is software module developed on TI's DM36x.
 * This module is capable of decoding H.264 bit-stream" 
 * Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/ 
 * ALL RIGHTS RESERVED 
 ******************************************************************************
 */
/** ===========================================================================
* @file ih264vdec.h
*
* @path $(PROJDIR)\src
*
* @brief This File contains function declarations and macros
* =============================================================================
*/
/* ------compilation control switches -------------------------*/
#ifndef IH264VDEC_
#define IH264VDEC_
/***************************************************************
*  INCLUDE FILES
****************************************************************/
/* ----- system and platform files ----------------------------*/
/*-------program files ----------------------------------------*/
/***************************************************************
*  EXTERNAL REFERENCES NOTE : only use if not found in header file
****************************************************************/
/*--------data declarations -----------------------------------*/
/*--------function prototypes ---------------------------------*/
/****************************************************************
*  PRIVATE DECLARATIONS Defined here, used only here
****************************************************************/
/*--------data declarations -----------------------------------*/
/*--------function prototypes ---------------------------------*/
/*--------macros ----------------------------------------------*/
/*!
*****************************************************************************
*@define Control command macros
*
*@brief Control commands identified by XDM control API. These are directly
*       mapped to the XDM v1.0 defined control commands any extensiosn to
*       control commands should appear here and it should have a value greater
*       than the max enum value defined in XDM_CmdId at xdm.h
*
*@note   None
*
******************************************************************************/
#define IH264VDEC_GETSTATUS      XDM_GETSTATUS
#define IH264VDEC_SETPARAMS      XDM_SETPARAMS
#define IH264VDEC_RESET          XDM_RESET
#define IH264VDEC_FLUSH          XDM_FLUSH
#define IH264VDEC_SETDEFAULT     XDM_SETDEFAULT
#define IH264VDEC_GETBUFINFO     XDM_GETBUFINFO
#define MAXCPBCNT 32

/* Extending Chroma Formates                                                */
#define IH264VDEC_YUV_420IUV        256

/****************************************************************
*  PUBLIC DECLARATIONS Defined here, used elsewhere
****************************************************************/
/*--------data declarations -----------------------------------*/

/** ============================================================
 *  @name   IH264VDEC_TI_MAXNUMBLOCKS
 *
 *  @desc   Max value of dataSyncDescriptor->numBlocks accepted
 *          by decoder when operated in IH264VDEC_TI_SLICEMODE 
 *
 *  ============================================================
 */
#define IH264VDEC_TI_MAXNUMBLOCKS   5


/** ============================================================
 *  @name   IH264VDEC_TI_DataMode
 *
 *  @desc   Describes the granularity of input data provided to 
 *          decoder. This enumeration type is used by APP to 
 *          specify codec if input buffer carries bits sufficient 
 *          to decoded one complere frame or partial frame (slices)    
 *
 *  @field  IH264VDEC_TI_SLICEMODE
 *          provide bits sufficient to decoded slice of frame
 *  @field  IH264VDEC_TI_ENTIREFRAME 
 *          provide bits to decode complete frame
 *  ============================================================
 */

typedef enum
{
    IH264VDEC_TI_SLICEMODE   = 0,       //Processing of one slice
	IH264VDEC_TI_ENTIREFRAME = 1        //Processing of entire frame data
} IH264VDEC_TI_DataMode;


/** ============================================================
 *  @name   IH264VDEC_TI_SliceFormat
 *
 *  @desc   Describes the input slice format provided to decoder.   
 *          This enumeration type is used by App to specify codec
 *          input slice format (NAL/Bytestream) type  
 *
 *  @field  IH264VDEC_TI_NALSTREAM
 *          provide encoded slice in NAL stream format
 *  @field  IH264VDEC_TI_BYTESTREAM 
 *          provide encoded slice in BYTE stream format
 *  ============================================================
 */
typedef enum 
{
    IH264VDEC_TI_NALSTREAM   = 0,       //Output data in NAL stream format
	IH264VDEC_TI_BYTESTREAM  = 1        //Output data in BYTE stream format
} IH264VDEC_TI_SliceFormat;

/*
 *=============================================================================
 * IH264VDEC_dataSyncHandle
 *
 * This handle is provided by the application to handle DataSync Fifo. Decoder 
 * passes this handle back to application when making request for more i/p data
 * via callback
 *=============================================================================
 */
typedef void * IH264VDEC_TI_DataSyncHandle;
/** ===========================EXAMPLE=================================
 *  @name   IH264VDEC_TI_DataSyncDesc
 *  
 *  @desc   This structure specifies the parameter used by application
 *          provide input bit-stream buffer details to decoder
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

typedef struct IH264VDEC_TI_DataSyncDesc
{
	XDAS_Int32 	size;
	XDAS_Int32 	numBlocks;
	XDAS_Int32 	varBlockSizesFlag;
	XDAS_Int32  *baseAddr[IH264VDEC_TI_MAXNUMBLOCKS];
	XDAS_Int32  blockSizes[IH264VDEC_TI_MAXNUMBLOCKS];
} IH264VDEC_TI_DataSyncDesc;
/** ============================================================
 *  @name   IH264VDEC_TI_DataSyncGetFxn
 *
 *  @desc  Blocking API used by decoder to signal "data request" 
 *        to producer . 
 *        Producer need to define this API. Returns the success
 *        or failure status. Valid return value is XDM_EOK or 
 *        XDM_EFAIL 
 *
 *  @field  IH264VDEC_TI_DataSyncHandle
 *          Handle of dataSync provided by application

 *  @field  IH264VDEC_TI_DataSyncDesc 
 *          dataSyncDescriptor containing encoded bistream buffer 
 *          details
 *  ============================================================
 */
typedef XDAS_Int32 (* IH264VDEC_TI_DataSyncGetFxn)
        (IH264VDEC_TI_DataSyncHandle dataSyncHandle, 
        IH264VDEC_TI_DataSyncDesc *dataSyncDesc);


/*
***************************************************************************
* eH264VDEC_TI_Profile
*
* This enum tells the profile of the encoded H.264 stream
*/

typedef enum profile{
    PROFILE_INVALID=-1,       //!<-1: Used to indicate unsupported profile
    BASELINE=66,              //!< 66: BASELINE PROFILE
    MAIN    =77,              //!< 77: MAIN PROFILE
    EXTENDED=88,              //!< 88: EXTENDED PROFILE
    MAX_PROFILES_TYPES=3     //!< Maximum Number of Profile == 3
}eH264VDEC_TI_Profile;


/*!
 *****************************************************************************
 * \enum  eLevelIdc
 * \brief Level Enumerators as per Annex A.
 *
 * This enumerator describes possible values of syntax element level_idc
 * which is equal to 10 times the value of level number
 *****************************************************************************/
typedef enum levelIdc{
    LEVEL_1 = 10, //!<Level 1.0
    LEVEL_1_1,    //!<Level 1.1
    LEVEL_1_2,    //!<Level 1.2
    LEVEL_1_3,    //!<Level 1.3
    LEVEL_2 = 20, //!<Level 2.0
    LEVEL_2_1,    //!<Level 2.1
    LEVEL_2_2,    //!<Level 2.2
    LEVEL_3 = 30, //!<Level 3.0
    LEVEL_3_1,    //!<Level 3.1
    LEVEL_3_2,    //!<Level 3.2
    LEVEL_4 = 40, //!<Level 4.0
    LEVEL_4_1,    //!<Level 4.1
    LEVEL_4_2,    //!<Level 4.2
    LEVEL_5 = 50, //!<Level 5.0
    LEVEL_5_1,    //!<Level 5.1
    LEVEL_INVALID = 0xFF, //!< Indicates Invalid level
    MAX_NUM_LEVELS = 15  //!< Size of Level Array
}eH264VDEC_TI_LevelIdc;


/*
// ***************************************************************************
// sHrdParm_t
//
// This structure contains the HRD parameters decoded by the decoder
*/
typedef struct  hrd_parm {
    unsigned int  cpb_cnt;                                          //!< ue(v)
    unsigned int  bit_rate_scale;                                   //!< u(4)
    unsigned int  cpb_size_scale;                                   //!< u(4)
    unsigned int  bit_rate_value [MAXCPBCNT];                       //!< ue(v)
    unsigned int  cpb_size_value[MAXCPBCNT];                        //!< ue(v)
    unsigned int  vbr_cbr_flag[MAXCPBCNT];                          //!< u(1)
    unsigned int  initial_cpb_removal_delay_length_minus1;          //!< u(5)
    unsigned int  cpb_removal_delay_length_minus1;                  //!< u(5)
    unsigned int  dpb_output_delay_length_minus1;                   //!< u(5)
    unsigned int  time_offset_length;                               //!< u(5)
} sHrdParm_t;


/*
// ***************************************************************************
// sVSP_t
//
// This structure contains the VUI sequence parameters decoded by the decoder
*/
typedef struct  vui_seq_parm {
    unsigned int  parsed_flag;
    unsigned int  aspect_ratio_info_present_flag;                    //!< u(1)
    unsigned int  aspect_ratio_idc;                                  //!< u(8)
    unsigned int  sar_width;                                         //!< u(16)
    unsigned int  sar_height;                                        //!< u(16)
    unsigned int  overscan_info_present_flag;                        //!< u(1)
    unsigned int  overscan_appropriate_flag;                         //!< u(1)
    unsigned int  video_signal_type_present_flag;                    //!< u(1)
    unsigned int  video_format;                                      //!< u(3)
    unsigned int  video_full_range_flag;                             //!< u(1)
    unsigned int  colour_description_present_flag;                   //!< u(1)
    unsigned int  colour_primaries;                                  //!< u(8)
    unsigned int  transfer_characteristics;                          //!< u(8)
    unsigned int  matrix_coefficients;                               //!< u(8)
    unsigned int  chroma_location_info_present_flag;                 //!< u(1)
    unsigned int  chroma_sample_loc_type_top_field;                  //!< ue(v)
    unsigned int  chroma_sample_loc_type_bottom_field;               //!< ue(v)
    unsigned int  timing_info_present_flag;                          //!< u(1)
    unsigned int  num_units_in_tick;                                 //!< u(32)
    unsigned int  time_scale;                                        //!< u(32)
    unsigned int  fixed_frame_rate_flag;                             //!< u(1)
    unsigned int  nal_hrd_parameters_present_flag;                   //!< u(1)
    sHrdParm_t nal_hrd_parameters;                        //!< hrd_paramters_t
    unsigned int  vcl_hrd_parameters_present_flag;                   //!< u(1)
    sHrdParm_t vcl_hrd_parameters;                        //!< hrd_paramters_t
    unsigned int  low_delay_hrd_flag;                                //!< u(1)
    unsigned int  pic_struct_present_flag;                           //!< u(1)
    unsigned int  bitstream_restriction_flag;                        //!< u(1)
    unsigned int  motion_vectors_over_pic_boundaries_flag;           //!< u(1)
    unsigned int  max_bytes_per_pic_denom;                           //!< ue(v)
    unsigned int  max_bits_per_mb_denom;                             //!< ue(v)
    unsigned int  log2_max_mv_length_vertical;                       //!< ue(v)
    unsigned int  log2_max_mv_length_horizontal;                     //!< ue(v)
    unsigned int  num_reorder_frames;                                //!< ue(v)
    unsigned int  max_dec_frame_buffering;                           //!< ue(v)
} sVSP_t;


/*
// ***************************************************************************
// sUserDataRegisteredITUT_t
//
// This structure contains the user data SEI msg elements
*/
typedef struct user_data_registered_itu_t_t35{
    unsigned int  parsed_flag;
	unsigned int  buffer_size;
	unsigned int  user_data_size;
	unsigned int  buffer_size_insufficient;
    unsigned int  itu_t_t35_country_code;
    unsigned int  itu_t_t35_country_code_extension_byte;
    unsigned char *itu_t_t35_payload_byte;
} sUserDataRegisteredITUT_t;


/*
// ***************************************************************************
// sUserDataUnregistered_t
//
// This structure contains the user data SEI msg elements
*/
typedef struct user_data_unregistered{
    unsigned int  parsed_flag;
	unsigned int  buffer_size;
	unsigned int  user_data_size;
	unsigned int  buffer_size_insufficient;
    unsigned char *user_data_payload_byte;
} sUserDataUnregistered_t;


/*
// ***************************************************************************
// sBufferingPeriod_t
//
// This structure contains the buffering period SEI msg elements
*/
typedef struct buffering_period{
    unsigned int parsed_flag;
    unsigned int seq_parameter_set_id;
    unsigned int initial_cpb_removal_delay[ MAXCPBCNT ];
    unsigned int initial_cpb_removal_delay_offset[MAXCPBCNT];
} sBufferingPeriod_t;



/*
// ***************************************************************************
// sProgRefineStart_t
//
// This structure contains the progressive refinement start SEI msg elements
*/
typedef struct prog_refinement_start{
    unsigned int parsed_flag;
    unsigned int progressive_refinement_id;
    unsigned int num_refinement_steps_minus1;
} sProgRefineStart_t;


/*
// ***************************************************************************
// sProgRefineEnd_t
//
// This structure contains the progressive refinement end SEI msg elements
*/
typedef struct prog_refinement_end{
    unsigned int parsed_flag;
    unsigned int progressive_refinement_id;
} sProgRefineEnd_t;


/*
// ***************************************************************************
// sRecoveryPointInfo_t
//
// This structure contains the sRecovery Point Info SEI msg elements
*/
typedef struct recovery_point_info {
    unsigned int  parsed_flag;
    unsigned int  recovery_frame_cnt;
    unsigned char   exact_match_flag;
    unsigned char   broken_link_flag;
    unsigned char   changing_slice_group_idc;
} sRecoveryPointInfo_t;


/*
// ***************************************************************************
// sPictureTiming_t
//
// This structure contains the picture timing SEI msg elements
*/
typedef struct picture_timing_SEI{
   unsigned int parsed_flag;
   unsigned int cpb_removal_delay;
   unsigned int dpb_output_delay;
   unsigned int pic_struct;
   unsigned int clock_timestamp_flag[3];
   unsigned int ct_type[3];
   unsigned int nuit_field_based_flag[3];
   unsigned int counting_type[3];
   unsigned int full_timestamp_flag[3];
   unsigned int discontinuity_flag[3];
   unsigned int cnt_dropped_flag[3];
   unsigned int n_frames[3];
   unsigned int seconds_value[3];
   unsigned int minutes_value[3];
   unsigned int hours_value[3];
   unsigned int time_offset[3];
} sPictureTiming_t;


/*
// ***************************************************************************
// sFullFrameFreezeRepetition_t
//
// This structure contains the full frmae freeze repetition SEI msg elements
*/
typedef struct frame_freeze_repetetion{
   unsigned int parsed_flag;
   unsigned int full_frame_freeze_repetition_period;
} sFullFrameFreezeRepetition_t;


/*
// ***************************************************************************
// sFullFrameFreezeRelease_t
//
// This structure contains frame freeze release SEI msg elements
*/
typedef struct frame_freeze_release{
   unsigned int parsed_flag;
   unsigned char  full_frame_freeze_release_flag;
} sFullFrameFreezeRelease_t;


/*
// ***************************************************************************
// sSeiMessages_t
//
// This structure contains all the supported SEI msg objects
*/
typedef struct sei_messages {
    unsigned int parsed_flag;
    sFullFrameFreezeRepetition_t frame_freeze_repetition;
    sFullFrameFreezeRelease_t frame_freeze_release;
    sProgRefineStart_t prog_refine_start;
    sProgRefineEnd_t   prog_refine_end;
    sRecoveryPointInfo_t recovery_pt_info;
    sPictureTiming_t   pic_timing;
    sUserDataRegisteredITUT_t user_data_registered;
    sUserDataUnregistered_t  user_data_unregistered;
    sBufferingPeriod_t  buffering_period_info;
}sSeiMessages_t;

/*
// ***************************************************************************
// sSeiVuiParams_t
//
// This structure contains SEI and VUI msg instance objects
*/
typedef struct  sei_vui_parm {
    unsigned int parsed_flag;
    sVSP_t vui_params;
    sSeiMessages_t sei_messages;
} sSeiVuiParams_t;


/*
// ***************************************************************************
// IH264VDEC_Obj
//
// This structure must be the first field of all H264VDEC instance objects
*/
typedef struct IH264VDEC_Obj {
    struct IH264VDEC_Fxns *fxns;
} IH264VDEC_Obj;

/*
// ***************************************************************************
// IH264VDEC_Handle
//
// This handle is used to reference all H264VDEC instance objects
*/
typedef struct IH264VDEC_Obj *IH264VDEC_Handle;


/*
// ***************************************************************************
// IH264VDEC_Status
//
// Status structure defines the parameters that can be changed or read
// during real-time operation of the alogrithm.
*/
typedef struct IH264VDEC_Status {
    IVIDDEC2_Status  viddecStatus;

    /* Add more if reqd */
    /* Header decode mode members*/
    XDAS_Int32 frameType;
    XDAS_Int32 firstMBinSlc;
    XDAS_Int32 frmNuminSlcHdr;

} IH264VDEC_Status;

/*
// ***************************************************************************
// IH264VDEC_Cmd
//
// The Cmd enumeration defines the control commands for the MPEG4 video decoder
// control method.
*/
typedef IVIDDEC2_Cmd IH264VDEC_Cmd;


/*
// ***************************************************************************
// IH264VDEC_Params
//
// This structure defines the creation parameters for all H264VDEC objects
*/
typedef struct IH264VDEC_Params {
    IVIDDEC2_Params viddecParams; /* must be followed for all video encoders */
    /* TODO : add on  algorithm & vendor specific parameters here
       Recommandations : segregare into two parts , creation time folloed by
       runtime parameters */
    /* Display delay will decide the initial delay before which decode call */
    /* starts  */
    XDAS_Int32  displayDelay;
    /* HDVICP related handle onject */
    void    *hdvicpHandle;
    /* resetHDVICPeveryFrame - flag to indicate if the co-processor needs
     * to be reset and initialised at end of every frame */
    //XDAS_Int8 resetHDVICPeveryFrame;
    XDAS_Int8 disableHDVICPeveryFrame;
    /* levelLimit sets the maximum limit for the level idc */
	XDAS_Int32 levelLimit;
	XDAS_Int32 frame_closedloop_flag;
    /* DMA params to be initialised for DMA state structure */
    XDAS_Int32      inputDataMode;    /* ENTIREFRAME or SLICEMODE */
    XDAS_Int32      sliceFormat;      /* NAL or Byte stream format */

} IH264VDEC_Params;


/*
// ***************************************************************************
// IH264VDEC_PARAMS
//
// Default parameter values for H264VDEC instance objects
*/
extern IH264VDEC_Params IH264VDEC_PARAMS;


/*
 *  ******** IVIDDEC2_InArgs ********
 *  This structure defines the run time arguments for all VIDDEC objects.
 *  This structure may be extended by individual codec implementation
 *  allowing customization with vendor specific parameters.
 */
typedef struct IH264VDEC_InArgs {
    IVIDDEC2_InArgs   viddecInArgs; /*must be followed for all video decoders*/

    /* Add more if required */
    XDAS_Int32       seiVuiParseFlag;
    sSeiVuiParams_t *seiVuiBufferPtr;
    XDAS_Int32 	   numBytesNextFrame;

    XDAS_Int32      pNumBytesInDesc[IH264VDEC_TI_MAXNUMBLOCKS];

}IH264VDEC_InArgs;

/*
// ***************************************************************************
// IH264VDEC_DynamicParams
//
// This structure defines the run time parameters for all H264VDEC objects
*/
typedef struct IH264VDEC_DynamicParams {
    IVIDDEC2_DynamicParams viddecDynamicParams;


    IH264VDEC_TI_DataSyncGetFxn   getDataFxn; /* Pointer to callback module */
    IH264VDEC_TI_DataSyncHandle   dataSyncHandle;

    /* Add more if required */
	/* resetHDVICPeveryFrame - flag to indicate if the co-processor needs
     * to be reset and initialised at end of every frame */
    XDAS_Int8 resetHDVICPeveryFrame;

} IH264VDEC_DynamicParams;


/*
 *  ******** IH264VDEC_OutArgs ********
 *  This structure defines the run time output arguments for IH264VDEC
 *  instance objects.
 *  This structure may be extended by individual codec implementation
 *  allowing customization with vendor specific parameters.
 */
typedef struct IH264VDEC_OutArgs {
    /* must be followed for all video encoders */
    IVIDDEC2_OutArgs  viddecOutArgs;
    /* Range of the pixel values - 8bit or 16 bit */
    XDAS_UInt8  pixelRange;
    XDAS_UInt16 parWidth;
    XDAS_UInt16 parHeight;
    XDAS_UInt16 numErrMbs;
    sSeiVuiParams_t *seiVuiBufferPtr;
    XDAS_Int32 bytesConsumedNextFrame;

    XDAS_UInt8 numBlocksConsumed;

} IH264VDEC_OutArgs;
/*
// ***************************************************************************
// IH264VDEC_Fxns
//
// This structure defines all of the operations on H264VDEC objects
*/
typedef struct IH264VDEC_Fxns {
    IVIDDEC2_Fxns    ividdec;    /* IH264VDEC extends IVIDDEC object.
                                    Should be second set of functions */
    /* TODO : add given algorithm, vendor specific functions here
    The following function is example of how VIDDEC object can be
    expanded to make IMOD. You can also write various interface functions
    of CIL here and map using extra layer above codec */
    Int   (*metaprocess)     (IH264VDEC_Handle handle,
                              IH264VDEC_DynamicParams *params);
    /* Add more  */
} IH264VDEC_Fxns;
/*
 *  ======== H264VDECEC_TII_IH264VDECEC ========
 *  TI's implementation of the IH264VDECEC interface
 */

/* IH264VDEC_ExtendedError describes Bits 6-0 are codec and implementation */
/* specific. Bits 7 IH264VDEC_EOSTR indicates end of the stream condition  */
/* Bit 7 and value corresponding to Bits 6-0 are independent of each other */
typedef enum IH264VDEC_ExtendedError {

	IH264VDEC_EX_ERR_DANGLING_FLD                          = 0x1,
	IH264VDEC_EX_ERR_INVALID_SPS_CNT                       = 0x2,
	IH264VDEC_EX_ERR_INVALID_LEVEL                         = 0x3,
	IH264VDEC_EX_ERR_INVALID_CONSTRAINT_SET3_FLAG          = 0x4,
	IH264VDEC_EX_ERR_UNSUPP_PROFILE_IDC                    = 0x5,
	IH264VDEC_EX_ERR_UNSUPP_CHROMA_FORMAT_IDC              = 0x6,
	IH264VDEC_EX_ERR_SCAL_LIST_NOT_SUPPORTED               = 0x7,
	IH264VDEC_EX_ERR_INV_MAX_FRM_NUM                       = 0x8,
	IH264VDEC_EX_ERR_WRONG_POC                             = 0x9,
	IH264VDEC_EX_ERR_MAX_POC_CYCLE_EXCEEDED                = 0xA,
	IH264VDEC_EX_ERR_INV_POC_TYPE                          = 0xB,
	IH264VDEC_EX_ERR_NO_OF_REF_FRMS_EXCEEDED               = 0xC,
	IH264VDEC_EX_ERR_UNSUPP_RESOLUTION                     = 0xD,
	IH264VDEC_EX_ERR_MAXCPBCNT_EXCEEDED                    = 0xE,
	IH264VDEC_EX_ERR_LEVEL_SEQ_PAR_SETID_EXCEEDED          = 0xF,
	IH264VDEC_EX_ERR_CABAC_NOT_SUPPORTED                   = 0x10,
	IH264VDEC_EX_ERR_WEIGHTED_PRED_NOT_SUPPORTED           = 0x11,
	IH264VDEC_EX_ERR_INV_SLICE_QP                          = 0x12,
	IH264VDEC_EX_ERR_INV_CHROMA_QP_OFFSET                  = 0x13,
	IH264VDEC_EX_ERR_INV_INFERENCE_FLAG                    = 0x14,
	IH264VDEC_EX_ERR_CHANGE_IN_RESO                        = 0x15,
	IH264VDEC_EX_ERR_FIRST_MB_IN_SLICE                     = 0x16,
	IH264VDEC_EX_ERR_FMO_NOT_SUPPORTED                     = 0x17,
	IH264VDEC_EX_ERR_MAX_PPS_CNT_EXCEEDED                  = 0x18,
	IH264VDEC_EX_ERR_INV_SLICE_TYPE                        = 0x19,
	IH264VDEC_EX_ERR_INV_PPS_ID                            = 0x1A,
	IH264VDEC_EX_ERR_INV_DPB_LIMIT                         = 0x1B,
	IH264VDEC_EX_ERR_NALU_TYPE_NOT_SUPPORTED               = 0x1C,
	IH264VDEC_EX_ERR_INV_ASPECT_RATIO_IDC                  = 0x1D,
	IH264VDEC_EX_ERR_LEVEL_LIMIT_VIOLATED                  = 0x1E,
	IH264VDEC_EX_ERR_INV_MAX_REFIDX                        = 0x1F,
	IH264VDEC_EX_ERR_FRAME_NUM_ERROR                       = 0x20,
	IH264VDEC_EX_ERR_UNSUPPORTED_SLICE_TYPE                = 0x21,
	IH264VDEC_EX_ERR_GARBAGE_DATA_IN_BITSTREAM             = 0x22,
	IH264VDEC_EX_ERR_MAX_NO_DATA_IN_NALU                   = 0x23,
	IH264VDEC_EX_ERR_BITSTREAM_CORRUPTION                  = 0x24,
	IH264VDEC_EX_ERR_NO_NAL_SYNC_MARKER                    = 0x25,
	IH264VDEC_EX_ERR_MISSING_MBS                           = 0x26,
	IH264VDEC_EX_ERR_CORRU_IN_MB_DATA                      = 0x27,
	IH264VDEC_EX_ERR_RS_NOT_SUPP                           = 0x28,
	IH264VDEC_EX_ERR_INV_CROPPING                          = 0x29,
	IH264VDEC_EX_ERR_SLICE_ALFA_C0_OFFSET                  = 0x2A,
	IH264VDEC_EX_ERR_SLICE_BETA_OFFSET                     = 0x2B,
	IH264VDEC_EX_ERR_INV_MAX_WEIGHT_BIPRED_IDC             = 0x2C,
	IH264VDEC_EX_ERR_INV_IDR_PIC_ID                        = 0x2D,
	IH264VDEC_EX_ERR_INV_PIC_ORDER_CNT_LSB                 = 0x2E,
	IH264VDEC_EX_ERR_INV_DEBLOCKING_FILT_IDC               = 0x2F,
	IH264VDEC_EX_ERR_INV_REFIDX                            = 0x30,
	IH264VDEC_EX_ERR_INV_FIRST_MB_IN_SLICE                 = 0x31,
	IH264VDEC_EX_ERR_INV_CABAC_IDC                         = 0x32,
	IH264VDEC_EX_ERR_INSUFF_BUFSIZE                        = 0x33,
	IH264VDEC_EX_ERR_INV_ARG_IN_PROCESS_CALL               = 0x34,
	IH264VDEC_EX_ERR_INV_IMPLEMENTATION_ID                 = 0x35,
	IH264VDEC_EX_ERR_INV_CODEC_ID                          = 0x36,
	IH264VDEC_EX_ERR_INV_ARG_IN_CONTROL_CALL               = 0x37,
	IH264VDEC_EX_ERR_ALGO_NOT_ACTIVATED                    = 0x38,
	IH264VDEC_EX_ERR_RESOURCE_NOT_INITIALIZED              = 0x39,
	IH264VDEC_EX_ERR_INVALID_LEVEL_SETTING_TO_4_2          = 0x3A,
	IH264VDEC_EX_ERR_INAPPROPRIATE_LEVEL_FOR_GIVEN_RESOLN  = 0x3B,
	IH264VDEC_EX_ERR_INVALID_DYNAMIC_PARAMS_SIZE           = 0x3C,
	IH264VDEC_EX_ERR_DISPLAY_WIDTH_DYNAMIC_CHANGE_INVALID  = 0x3D,
	IH264VDEC_EX_ERR_INVALID_DISPLAY_WIDTH                 = 0x3E,
	IH264VDEC_EX_ERR_DISPLAY_WIDTH_NOT_MULTIPLE_OF_32      = 0x3F,
	IH264VDEC_EX_ERR_RESET_HDVICP_VALUE_NOT_SUPPORTED      = 0x40,
	IH264VDEC_EX_ERR_FRAME_ORDER_DYNAMIC_CHANGE_INVALID    = 0x41,
	IH264VDEC_EX_ERR_FRAME_ORDER_INVALID                   = 0x42,
	IH264VDEC_EX_ERR_DECODE_HEADER_VALUE_INVALID           = 0x43,
	IH264VDEC_EX_ERR_UNALIGNED_PIC_BUFFER                  = 0x44,
	IH264VDEC_EX_ERR_HEADER_NOT_FOUND                      = 0x45,
	IH264VDEC_EX_ERR_INVALID_HEADER_FOUND                  = 0x46,
	IH264VDEC_EX_ERR_VERSION_BUFFER_INVALID                = 0x47,
	IH264VDEC_EX_ERR_SEI_VUI_BUFFER_INVALID                = 0x48,
	IH264VDEC_EX_ERR_FRAME_SKIP_NOT_IMPLEMENTED            = 0x49,
	IH264VDEC_EX_ERR_NEW_FRAME_LOGIC_NOT_IMPLEMENTED       = 0x4A,
	IH264VDEC_EX_ERR_MB_DATA_NOT_SUPPORTED                 = 0x4B,
	IH264VDEC_EX_ERR_WRONG_INPUT_ID                        = 0x4C,
	IH264VDEC_EX_ERR_SEI_NAL                               = 0x4D,
	IH264VDEC_EX_ERR_INVALID_RESERVED_BITS                 = 0x4E,
	IH264VDEC_EX_ERR_REF_FRAME_IN_ERROR                    = 0x4F,
    IH264VDEC_EX_ERR_GET_DATA_FXN_NULL                     = 0x50,
    IH264VDEC_EX_ERR_CALLBK                                = 0x51,
    IH264VDEC_EX_ERR_UNSUPPORTED_SLICEMODE_IN_MBAFF        = 0x52,
    IH264VDEC_EX_ERR_UNINTENSIONAL_FRAME_LOST              = 0x53,

	IH264VDEC_EOSTR                                        = 0x80

} IH264VDEC_ExtendedError;


#endif  /* IH264VDEC_ */


 /*!
*! Revision History
*! ================
*! 17-Oct-2007 Vinay : fixed a variable naming non-consistency bug viddecInArg
*                       in InArgs structure. CDMR00005144.
*! 31-July-2007 Yashwant Dutt: Added SEI and VUI support.
*! 10-June-2007 Vinay MK: Modified for coding guidelines
*! 05-Jan-2006 Dinesh Kumar: Created.
*/
