/*
//============================================================================
//
//    FILE NAME : IENHAACPDEC.h
//
//    ALGORITHM : ENHAACPDEC
//
//    VENDOR    : IS
//
//    TARGET DSP: C64x
//
//    PURPOSE   : IENHAACPDEC Interface Header
//
//    Component Wizard for eXpressDSP Version 1.33.00 Auto-Generated Component
//
//    Number of Inputs : 1
//    Number of Outputs: 1
//
//    Creation Date: Wed - 21 June 2006
//    Creation Time: 06:24 PM
//
//============================================================================
*/

#ifndef IENHAACPDEC_
#define IENHAACPDEC_

/* Requires the following include files
#ifdef WIN32
#include "ia_type_def.h"
#include "xdais.h"
#else
#include <std.h>
#include <xdas.h>
#include <ialg.h>
#endif

#include "xdm.h"
#include "iaudio.h"
#include "iauddec1.h" */

/*
// ===========================================================================
// IENHAACPDEC_Handle
//
// This handle is used to reference all ENHAACPDEC instance objects
*/
typedef struct IENHAACPDEC_Obj *ITTIAM_ENHAACPDEC_Handle;

/*
// ===========================================================================
// IENHAACPDEC_Obj
//
// This structure must be the first field of all ENHAACPDEC instance objects
*/
typedef struct IENHAACPDEC_Obj {
    struct ITTIAM_ENHAACPDEC_Fxns *fxns;
} IENHAACPDEC_Obj;

/*
// ===========================================================================
// ITTIAM_ENHAACPDEC_Status
//
// Status structure defines the parameters that can be changed or read
// during real-time operation of the alogrithm.
*/
typedef struct ITTIAM_ENHAACPDEC_Status {
    IAUDDEC1_Status  s_iauddec_status;
    XDAS_Int32      i_channel_mask;
    XDAS_Int32      i_channel_mode;
    XDAS_Int32      i_sbr_mode;
	XDAS_Int32      i_num_channels; /* Though available in base structure, */
                                    /* replicated for unsupported channelMode enums */
    //XDAS_UInt8      a_ver_info[64]; /* Part of base structure */
} ITTIAM_ENHAACPDEC_Status;

/*
// ===========================================================================
// IENHAACPDEC_Cmd
//
// The Cmd enumeration defines the control commands for the ENHAACPDEC
// control method.
*/

typedef  IAUDDEC1_Cmd ITTIAM_ENHAACPDEC_Cmd;

/*
// ===========================================================================
// ITTIAM_ENHAACPDEC_Params
//
// This structure defines the creation parameters for all ENHAACPDEC objects
*/
typedef struct ITTIAM_ENHAACPDEC_Params {
    IAUDDEC1_Params s_iauddec_params;
    //XDAS_Int32      i_output_pcm_fmt; /* Now part of base structure */
    XDAS_Int32      i_max_channels; /* Moved to extended params as removed from base */
    XDAS_Int32      i_flag_08khz_out;
    XDAS_Int32      i_flag_16khz_out;
    //XDAS_Int32      i_downsample; /* base param in dynParam */
    //XDAS_Int32      i_flag_downmix; /* base param in inargs */
    XDAS_Int32      i_interleave;     /* to enable/disable to_stereo option */
    XDAS_Int32      i_mp4_flag;
    XDAS_Int32      i_disable_sync;
    XDAS_Int32      i_auto_sbr_upsample;
    XDAS_Int32      i_sampfreq;
    XDAS_Int32      i_coupling_channel;
    //XDAS_Int32      i_downmix_mc_to_stereo; /* base param in inargs */
} ITTIAM_ENHAACPDEC_Params;

/*
// ===========================================================================
// ITTIAM_ENHAACPDEC_PARAMS
//
// Default parameter values for ENHAACPDEC instance objects
*/
extern ITTIAM_ENHAACPDEC_Params ENHAACPDECODER_ITTIAM_PARAMS;

/*
 *  ======== ITTIAM_MP3DEC_DynamicParams ========
 *  This structure defines the codec parameters that can be modified after
 *  creation via 'control' calls.
 *
 *  It is not necessary that given implementation support all dynamic
 *  parameters to be configurable at run time. If a particular codec
 *  does not support run-time updates to a parameter that  the application
 *  is attempting to change at runtime, the codec may indicate this as an
 *  error.
 */
/* If no change just typedef it as same */
typedef struct ITTIAM_ENHAACPDEC_DynamicParams {
	IAUDDEC1_DynamicParams s_iauddec_dynparams;
}ITTIAM_ENHAACPDEC_DynamicParams;

/*
 *  ======== ITTIAM_MP3DEC_InArgs ========
 *  This structure defines the runtime input arguments for AUDDEC process
 *  function.
 */
typedef struct ITTIAM_ENHAACPDEC_InArgs {
	IAUDDEC1_InArgs  s_iauddec_in_args;
}ITTIAM_ENHAACPDEC_InArgs;

/*
 *  ======== ITTIAM_MP3DEC_OutArgs ========
 *  This structure defines the run time output arguments for AUDDEC process
 *  function.
 */
typedef struct ITTIAM_ENHAACPDEC_OutArgs
{
	IAUDDEC1_OutArgs s_iauddec_outargs;
	XDAS_Int32      i_init_done;
	XDAS_Int32      i_exec_done;
	XDAS_Int32      i_ittiam_err_code ;
	//XDAS_Int32      i_frame_len; /* Available in base structure */
	XDAS_Int32      i_output_bits_per_sample;
	XDAS_Int32      i_num_channels; /* Though available in base structure, */
                                    /* replicated for unsupported channelMode enums */
    XDAS_Int32      i_channel_mask;
	//XDAS_Int32      i_sample_rate; /* Available in base structure */
}ITTIAM_ENHAACPDEC_OutArgs;

/*
 *  ======== ITTIAM_ENHAACPDEC_Fxns ========
 *  This structure defines all of the operations on AUDDEC objects.
 *
 *  process() - Basic audio decoding call. It takes input and output buffer
 *              descriptors and structures for input and output arguments.
 *              The algorithm may also modify the output buffer pointers.
 *              The return value is IAUDDEC1_EOK for success or IAUDDEC1_EFAIL
 *              in case of failure. The extendedError field of the outArgs
 *              contain further error conditions flagged by the algorithm.
 *
 *  control() - This will control behaviour of algorithm via Cmd ID.
 *              All XDM Control Commands are supported:
 *                  XDM_GETSTATUS =0, XDM_SETPARAMS, XDM_RESET, XDM_SETDEFAULT,
 *                  XDM_FLUSH, XDM_GETBUFINFO
 *              See xdm.h for details.
 *              The return value is IAUDDEC1_EOK for success or IAUDDEC1_EFAIL.
 *              In case of failure extended error code contains details.
 */

typedef struct ITTIAM_ENHAACPDEC_Fxns {
      IAUDDEC1_Fxns s_iauddec_fxns;
}ITTIAM_ENHAACPDEC_Fxns;

#endif	/* IENHAACPDEC_ */
