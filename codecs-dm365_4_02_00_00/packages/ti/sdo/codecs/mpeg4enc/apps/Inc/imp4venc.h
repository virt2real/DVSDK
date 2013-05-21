/*
//============================================================================
//    FILE NAME : imp4venc.h
//    ALGORITHM : MP4VENC
//    VENDOR    : TI
//    TARGET Proc: DM355
//    PURPOSE   : This is the top level driver file that exercises the MPEG4
//               Encoder code
//============================================================================
*/
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
#ifndef IMP4VENC_
#define IMP4VENC_

//#include <xdc/std.h>
#include <ti/xdais/dm/xdm.h>
#include <ti/xdais/ialg.h>
#include <ti/xdais/dm/ividenc1.h>

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/

//RC algorithm defines

//Extended enumeration for rateControlPreset
#define IMP4VENC_CVBR_LBR1 256
#define IMP4VENC_CVBR_LBR2 257
#define IMP4VENC_CVBR 258


//Extended enumeration for encodingPreset
#define IMP4VENC_HIGH_QUALITY_MODERATE_PERFORMANCE 256
#define IMP4VENC_HIGHEST_QUALITY_LOWEST_PERFORMANCE 257
#define IMP4VENC_LOW_QUALITY_HIGHEST_PERFORMANCE 258

//!< control method commands
#define IMP4VENC_GETSTATUS      XDM_GETSTATUS
#define IMP4VENC_SETPARAMS      XDM_SETPARAMS
#define IMP4VENC_RESET          XDM_RESET
#define IMP4VENC_FLUSH          XDM_FLUSH
#define IMP4VENC_SETDEFAULT     XDM_SETDEFAULT
#define IMP4VENC_GETBUFINFO     XDM_GETBUFINFO

    /*
     *  ======== IMP4VENC_Handle ========
     *  This handle is used to reference all MPEG4VENC instance objects
     */
    typedef struct IMP4VENC_Obj *IMP4VENC_Handle;

    /*
     *  ======== IMP4VENC_Obj ========
     *  This structure must be the first field of all MP4VENC instance objects
     */
    typedef struct IMP4VENC_Obj {

        struct IMP4VENC_Fxns *fxns;

    } IMP4VENC_Obj;


    /*
    // ===========================================================================
    // IMP4VE_Params
    //
    // This structure defines the creation parameters for all MP4VE objects
    */
    typedef struct IMP4VENC_Params {

        IVIDENC1_Params videncParams; /* must be followed for all video encoders */

        // CreateParams specific to MPEG4 Encoder
        XDAS_Int32 subWindowHeight;     /* Height of the Subwindow       */
        XDAS_Int32 subWindowWidth;      /*  Width of the Subwindow     */
        XDAS_Int32 rotation;            /* Rotation (anticlockwise): 0: No Rotation, 90: 90 degree, 180: 180 degree, 270: 270 degree */
        /*Rate control related parameters*/
        XDAS_Int32 vbvSize;		/* VBV size interms of 16 K bits*/

        /*MPEG4/H.263(SVH) mode*/
        XDAS_Int32 svhMode;		    /* 1:Mpeg4 in short video header mode*/
	XDAS_Int32 IFrameBitRateBiasFactor;	/* Q7 number for I frame bit rate biasing: For no effect use 256 */    
	XDAS_Int32 PFrameBitRateBiasFactor;	/* Q7 number for P frame bit rate biasing: For no effect use 256 */    
    	XDAS_Int32 peakBufWindow;    /* Time duration (in sec) during which actual bitrate of encoding stream can reach the max bitrate limit */   
	XDAS_Int32 minBitRate;      /* Minimum bit rate, bits per second. (optional) */

    } IMP4VENC_Params;

    /*
    // ===========================================================================
    // IMP4VE_DynamicParams
    // This structure defines the parameters that can be modified run time
    */

    typedef struct IMP4VENC_DynamicParams
    {
        IVIDENC1_DynamicParams videncDynamicParams;

        XDAS_Int32 intraAlgo;           /* INTRA/INTER Decision Algorithm. 0: Algorithm 1 with IIDC at 16x16,
					                                   1: Algorithm 1 with IIDC at 8x8,*/
        XDAS_Int32 numMBRows;           /* Number of MB rows in a Packet */

        /*Rate control related parameters*/
        XDAS_Int32 initQ;               /* Q init value */
        XDAS_Int32 rcQMax;             /* Q MAX value */
        XDAS_Int32 rcQMin;             /* Q MIN value */
        XDAS_Int32 intraFrameQP;               /* I-Frame QP value */
        XDAS_Int32 interFrameQP;               /* P-Frame QP value */
        XDAS_Int32 rateFix;             /* Reserved */
        XDAS_Int32 rateFixRange;        /* Reserved */

        /*Quality related parameters*/
        XDAS_Int32 meAlgo;              /* ME Algorithm. 0: 8421H ME, 1: 4421H ME, 2: 84221H ME, 3: 21H ME*/
        XDAS_Int32 skipMBAlgo;          /* SkipMB Algorithm. 0: normal skipMB Algo, 1: Bonus skipMB Algo */
        XDAS_Int32 unrestrictedMV;                 /* UMV. 0: disable, 1: enable*/

        /* parameter for Motion vector access*/
        XDAS_Int32 mvDataEnable;        /* for providing Motion vector access, 0: disable, 1: enable*/

    }IMP4VENC_DynamicParams;
    /*
     *  ======== IMP4VENC_PARAMS ========
     *  Default parameter values for MPEG4VENC instance objects
     */
    extern IMP4VENC_Params IMP4VENC_PARAMS;

    /*
    // ===========================================================================
    // IMP4VE_Status
    //
    // Status structure defines the parameters that can be changed or read
    // during real-time operation of the alogrithm.
    */

    typedef struct IMP4VENC_Status
    {

        IVIDENC1_Status  videncStatus;	/* must be followed for video encoder */

        /* TODO : add on  algorithm & vendor specific status here */

    } IMP4VENC_Status;

    /*
     *  ======== IMP4VENC_InArgs ========
     *  This structure defines the runtime input arguments for IMP4VENC::process
     */

    typedef struct IMP4VENC_InArgs
    {

        IVIDENC1_InArgs videncInArgs;
        XDAS_Int32 subWindowHozOfst;               /*  Hor offset                */
        XDAS_Int32 subWindowVerOfst;               /*  Ver offset                */

        /* User Data Parameters */
        XDAS_Bool insertUserData;		       /* 0: disable, 1:enable user data insertion */
        XDAS_UInt32 lengthUserData;	       /* lenght of userData, which needs to be inserted by App */
    } IMP4VENC_InArgs;

    /*
     *  ======== IMP4VENC_OutArgs ========
     *  This structure defines the run time output arguments for IMP4VENC::process
     *  function.
     */

    typedef struct IMP4VENC_OutArgs
    {

        IVIDENC1_OutArgs videncOutArgs;
        XDAS_Int32	  	mvDataSize;

        XDAS_Int32 offsetUserData; /* offset in output buffer, where App needs to insert UserData */
    } IMP4VENC_OutArgs;

    /*
     *  ======== IMP4VENC_Cmd ========
     *  This structure defines the control commands for the IMP4VENC module.
     */
    typedef IVIDENC1_Cmd IMP4VENC_Cmd;

    /*
     *  ======== IMP4VENC_Fxns ========
     *  This structure defines all of the operations on IMP4VENC objects.
     */

    typedef struct IMP4VENC_Fxns
    {

        IVIDENC1_Fxns	ividenc;    // IMP4VE extends IVIDENC object.

    } IMP4VENC_Fxns;



    typedef enum {
        IMP4VENC_ME_MQ_MP = 0,            /* Me algorithm for medium quality and medium performance */
        IMP4VENC_ME_HQ_MP = 1,           /* Me algorithm for High quality and medium performance */
        IMP4VENC_ME_HQ_LP  = 2,          /* Me algorithm for Highest quality and low performance */
        IMP4VENC_ME_LQ_HP = 3            /* Me algorithm for Lowest quality and Highest performance */
    } IMP4VENC_ME;

    typedef enum {
        IMP4VENC_UMV_LQ_HP = 0,            /* UMV for low quality and high performance... UMV is disabled */
        IMP4VENC_UMV_HQ_LP = 1           /* UMV for high quality and low performance... UMV is enabled */
    } IMP4VENC_UMV;

    typedef enum {
        IMP4VENC_INTRA_INTER_BLK_SIZE_LQ_HP  = 0,            /* 16x16 Block size for intra/inter decision for low quality and high performance */
        IMP4VENC_INTRA_INTER_BLK_SIZE_HQ_LP  = 1           /* 8x8 Block size for intra/inter decision for high quality and low performance */
    } IMP4VENC_IIDC;

    typedef enum {
        IMP4VENC_INTRA_INTER_DECISION_LQ_HP  = 0,   /* intra/inter decision for low quality and high performance */
        IMP4VENC_INTRA_INTER_DECISION_HQ_LP  = 1    /* intra/inter decision for high quality and low performance */
    } IMP4VENC_intraAlgo;

    typedef enum {
        IMP4VENC_SKIP_MB_LQ_HP  = 0,            /* Skip MB not biassed*/
        IMP4VENC_SKIP_MB_HQ_LP  = 1           /* Biassed Skip MB*/
    } IMP4VENC_pSkip;



    typedef enum {
        IMP4VENC_INVALID_IMAGEWIDTH  = 1,            /* Invalid Image Width*/
        IMP4VENC_INVALID_IMAGEHEIGHT  = 2,            /* Invalid Image Height*/
        IMP4VENC_INVALID_ENCODINGPRESET  = 3,            /* Invalid encodingPreset*/
        IMP4VENC_INVALID_RATECONTROLPRESET  = 4,            /* Invalid encodingPreset*/
        IMP4VENC_INVALID_MAXINTERFRAMEINTERVAL  = 5,            /* Invalid maxInterFrameInterval*/
        IMP4VENC_INVALID_INPUTCONTENTTYPE  = 6,            /* Invalid inputContentType*/
        IMP4VENC_INVALID_RECONCHROMAFORMAT  = 7,            /* Invalid reconChromaFormat*/
        IMP4VENC_INVALID_ROTATION  = 8,            /* Invalid rotation*/
        IMP4VENC_INVALID_FRAMERATE  = 9,            /* Invalid FrameRate*/
        IMP4VENC_INVALID_BITRATE  = 10,            /* Invalid BitRate*/
        IMP4VENC_INVALID_INTRAFRAMEINTERVAL  = 11,            /* Invalid intraFrameInterval*/
        IMP4VENC_INVALID_INTERFRAMEINTERVAL  = 12,            /* Invalid interFrameInterval*/
        IMP4VENC_INVALID_INTRAALGO  = 13,            /* Invalid intraAlgo*/
        IMP4VENC_INVALID_NUMMBROWS  = 14,            /* Invalid numMBRows*/
        IMP4VENC_INVALID_INITQ  = 15,            /* Invalid initQ*/
        IMP4VENC_INVALID_RCQMAX  = 16,            /* Invalid rcQ_MAX*/
        IMP4VENC_INVALID_RCQMIN  = 17,            /* Invalid rcQ_MIN*/
        IMP4VENC_INVALID_RATEFIX  = 18,            /* Invalid rateFix*/
        IMP4VENC_INVALID_RATEFIXRANGE  = 19,            /* Invalid rateFixRange*/
        IMP4VENC_INVALID_VBVSIZE  = 20,            /* Invalid VBV_size*/
        IMP4VENC_INVALID_MEALGO  = 21,            /* Invalid meAlgo*/
        IMP4VENC_INVALID_SKIPMBALGO  = 22,            /* Invalid SkipMBAlgo*/
        IMP4VENC_INVALID_UMV  = 23,            /* Invalid UMV*/
        IMP4VENC_INVALID_SVH  = 24,            /* Invalid SVH*/
        IMP4VENC_INVALID_FORCEFRAME  = 25,
        IMP4VENC_INVALID_GENERATEHEADER  = 25,            /* Invalid GENERATEHEADER*/
        IMP4VENC_INVALID_MVDATAENABLE  = 27,            /* Invalid GENERATEHEADER*/
        IMP4VENC_INVALID_INTRAFRAMEQP  = 28,            /* Invalid I frame Qp*/
        IMP4VENC_INVALID_INTERFRAMEQP  = 29            /* Invalid P frame Qp*/
    } IMP4VENC_ERROR;


    extern IMP4VENC_Fxns MP4VENC_TI_IMP4VENC;

#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif    /* IMP4VENC_ */

/* ======================================================================== */
/* End of file : imp4venc.h                                               */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

