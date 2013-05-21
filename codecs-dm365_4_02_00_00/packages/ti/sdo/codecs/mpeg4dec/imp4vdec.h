/*
//============================================================================
//    FILE NAME : imp4vdec.h
//    ALGORITHM : MP4VDEC
//    VENDOR    : TI
//    TARGET PLATFORM: DM355
//    PURPOSE   : This is the top level driver file that exercises the MPEG4
//               Decoder code
//============================================================================
*/
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
#ifndef IMP4VDEC_
#define IMP4VDEC_

//#include <xdc/std.h>
#include <ti/xdais/dm/xdm.h>
#include <ti/xdais/ialg.h>
#include <ti/xdais/idma3.h>
#include <ti/xdais/dm/ividdec2.h>


#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/

//!< control method commands
#define IMP4VDEC_GETSTATUS      XDM_GETSTATUS
#define IMP4VDEC_SETPARAMS      XDM_SETPARAMS
#define IMP4VDEC_RESET          XDM_RESET
#define IMP4VDEC_FLUSH          XDM_FLUSH
#define IMP4VDEC_SETDEFAULT     XDM_SETDEFAULT
#define IMP4VDEC_GETBUFINFO     XDM_GETBUFINFO


    /*
     *  Extended error enumeration for MPEG4 Decoder
     *
     *  Bit 8-31 : Defined by the XDM standard
     *  Bit 7-0 :   Codec & Implementation specific errors described below
     *
     *  Bit FAULT_HEADER_PARSING: 1 => Bit-stream Header Parsing Error
     *                            0 => Ignore
     *  Bit FAULT_BITSTRM_DATA_PARSING: 1 => Bit-stream Parsing Error from Hardware
     *                            0 => Ignore
     *  Notes :
     *  =====
     *  1) Algorithm will set multiple bits to 1 based on conditions.
     *     e.g. it will set bits XDM_FATALERROR (fatal) and XDM_UNSUPPORTEDPARAM
     *     (unsupported params) in case of unsupported run time parameters
     *  2) Some erors are applicable to decoders only.
     */
    typedef enum {
        FAULT_HEADER_PARSING=0, FAULT_BITSTRM_DATA_PARSING=1

    } FAULT_ErrorBit;


    typedef enum {

        MP4VDEC_ERROR_MAXHEIGHT=16,
        MP4VDEC_ERROR_MAXWIDTH=17,
        MP4VDEC_ERROR_DATAENDIANNESS=18,
        MP4VDEC_ERROR_CHROMA=19,
        MP4VDEC_ERROR_ROTATION=20,
        MP4VDEC_ERROR_DISPLAYWIDTH=21,
        MP4VDEC_ERROR_MERANGE=22,
        MP4VDEC_ERROR_DECODEHEADER=23,
        MP4VDEC_ERROR_UMV=24
    }Fault_inputparam_ErrorBit;

#define FAULT_ISHEADER_PARSING(x)         (((x) >> FAULT_HEADER_PARSING) & 0x1)
#define FAULT_ISBITSTRM_DATA_PARSING(x)   (((x) >> FAULT_BITSTRM_DATA_PARSING) & 0x1)

#define FAULT_SETHEADER_PARSING(x)         ((x)|=(0x1 << FAULT_HEADER_PARSING))
#define FAULT_SETBITSTRM_DATA_PARSING(x)   ((x)|=(0x1 << FAULT_BITSTRM_DATA_PARSING) )

    /*
     *  ======== IMP4VDEC_Handle ========
     *  This handle is used to reference all MPEG4VDEC instance objects
     */
    typedef struct IMP4VDEC_Obj *IMP4VDEC_Handle;

    /*
     *  ======== IMP4VDEC_Obj ========
     *  This structure must be the first field of all MP4VDEC instance objects
     */
    typedef struct IMP4VDEC_Obj {

        struct IMP4VDEC_Fxns *fxns;

    } IMP4VDEC_Obj;


    /*
    // ===========================================================================
    // IMP4VE_Params
    //
    // This structure defines the creation parameters for all MP4VE objects
    */
    typedef struct IMP4VD_Params {

        IVIDDEC2_Params viddecParams; /* must be followed for all video decoders */

        // CreateParams specific to MPEG4 Decoder
        XDAS_Int32 meRange;			/* Motion Estimation Range 7: ME7, 31: ME31. Others not supported. Test for b-imx */
        XDAS_Int32 displayWidth;  /*  DEFAULT (0): use imagewidth as pitch
                               *  else use given Display width for pitch
                               *  only if Displaywidth greater than
                               *  imagewidth of input.
                               */
        XDAS_Int32 rotation;   /*  Rotation (anticlockwise):
                               *  0: No Rotation,
                               *  90: 90 degree,
                               *  180: 180 degree,
                               *  270: 270 degree
                               */


        XDAS_Int32 unrestrictedMV;   /*  0: disabled 1:enabled */
    } IMP4VDEC_Params;

    /*
     *  ======== IMP4VDEC_PARAMS ========
     *  Default parameter values for MPEG4VDEC instance objects
     */
    extern IMP4VDEC_Params IMP4VDEC_PARAMS;

    /*
    // ===========================================================================
    // IMP4VE_Status
    //
    // Status structure defines the parameters that can be changed or read
    // during real-time operation of the alogrithm.
    */

    typedef struct IMP4VDEC_Status {

        IVIDDEC2_Status  viddecStatus;	/* must be followed for video decoder */

        /* TODO : add on  algorithm & vendor specific status here */

    } IMP4VDEC_Status;

    /*
     *  ======== IMP4VDEC_InArgs ========
     *  This structure defines the runtime input arguments for IMP4VDEC::process
     */

    typedef struct IMP4VDEC_InArgs {

        IVIDDEC2_InArgs viddecInArgs;

    } IMP4VDEC_InArgs;

    /*
     *  ======== IMP4VDEC_OutArgs ========
     *  This structure defines the run time output arguments for IMP4VDEC::process
     *  function.
     */

    typedef struct IMP4VDEC_OutArgs {

        IVIDDEC2_OutArgs viddecOutArgs;

    } IMP4VDEC_OutArgs;

    /*
     *  ======== IMP4VDEC_Cmd ========
     *  This structure defines the control commands for the IMP4VDEC module.
     */
    typedef IVIDDEC2_Cmd IMP4VDEC_Cmd;

    /*
     *  ======== IMP4VDEC_Fxns ========
     *  This structure defines all of the operations on IMP4VDEC objects.
     */

    typedef struct IMP4VDEC_Fxns {

        IVIDDEC2_Fxns	ividdec;    // IMP4VE extends IVIDDEC object.

    } IMP4VDEC_Fxns;

#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif    /* IMP4VDEC_ */

/* ======================================================================== */
/* End of file : imp4vdec.h                                               */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

