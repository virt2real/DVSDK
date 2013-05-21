/** =========================================================================
* @file mp2VDEC.c
*
* @path $(PROJDIR)\src
*
* @brief This file implements all methods defined in 'mp2VDEC.h'
* ===========================================================================
* Copyright (c) Texas Instruments Inc 2006, 2007
*
* Use of this software is controlled by the terms and conditions found
* in the license agreement under which this software has been supplied
* ===========================================================================
*/

/******************************************************************************
*                                 INCLUDE FILES
******************************************************************************/

/* ----------------------- SYSTEM AND PLATFORM FILES ------------------------*/


#include <xdc/std.h>
#include <ti/sdo/fc/utils/api/alg.h>
#include "imp2vdec.h"

/* ------------------------------ PROGRAM FILES -----------------------------*/
#include "datatypedefs.h"
#include "mp2vdec_tii.h"

/******************************************************************************
*                PUBLIC DECLARATIONS Defined here, used elsewhere
******************************************************************************/

/* ---------------------------- DATA DECLARATIONS ---------------------------*/
/* HACK for ires_common.h issue */

#include <ti/xdais/ires.h>


extern int MPEG2VDEC_TI_scratchId;

/* ---------------------------- FUNCTION PROTOTYPES -------------------------*/


/* -------------------------------- DIRECTIVES ------------------------------*/


/*---------------------------------------------------------------------------*/
/*  Global timer stamps used for profiling across every picture.             */
/*---------------------------------------------------------------------------*/

#ifdef _PROFILE
extern XDAS_UInt32 time0, time1, time2, time3, time4, time5, time6;
#endif

/* ==========================================================================
* MPEG2VDEC_create
*
*  Create an MPEG2VDEC instance object (using parameters specified by prms)
* ===========================================================================
*/
MPEG2VDEC_Handle MPEG2VDEC_create(const Imp2VDEC_Fxns  *fxns,
                              const mp2VDEC_Params *prms)
{
    return ((MPEG2VDEC_Handle)ALG_create((IALG_Fxns *)fxns, NULL,
        (IALG_Params *)prms));
}


/* ==========================================================================
* MPEG2VDEC_control
*
* Function to either write to the read/write parameters in the status
* structure or to read all the parameters in the status structure.
* ===========================================================================
*/
S32 MPEG2VDEC_control(MPEG2VDEC_Handle handle, MPEG2VDEC_Cmd cmd,
            MPEG2VDEC_DynamicParams *params, MPEG2VDEC_Status *status)
{

  S32 error;


  ALG_activate((IALG_Handle)handle);

  /*
   * Activate All RMAN Resources
   */
  RMAN_activateAllResources((IALG_Handle)handle,
                                &MPEG2VDEC_TI_IRES, MPEG2VDEC_TI_scratchId);


  error =   handle->fxns->ividdec.control ((IVIDDEC2_Handle)handle, cmd,
             (IVIDDEC2_DynamicParams *)params, (IVIDDEC2_Status *)status);

  /*
   * Deactivate All Resources
   */
  RMAN_deactivateAllResources((IALG_Handle)handle,
                                &MPEG2VDEC_TI_IRES, MPEG2VDEC_TI_scratchId);


  ALG_deactivate((IALG_Handle)handle);

  return (error);
}



/* ===========================================================================
* MPEG2VDEC_delete
*
* Delete the MPEG2VDEC instance object specified by handle
* ============================================================================
*/
void MPEG2VDEC_delete(MPEG2VDEC_Handle handle)
{
    ALG_delete((IALG_Handle)handle);
}

/* ===========================================================================
* MPEG2VDEC_init
*
* MPEG2VDEC module initialization
* ===========================================================================
*/
void  MPEG2VDEC_init(void)
{
}

/** =========================================================================
* MPEG2VDEC_exit
*
* MPEG2VDEC module finalization
* ===========================================================================
*/
void  MPEG2VDEC_exit(void)
{
}

/* ==========================================================================
*  MPEG2VDEC_decode
*  Main Decode process call.
* ===========================================================================
*/
S32 MPEG2VDEC_decode(MPEG2VDEC_Handle handle, XDM1_BufDesc  *input,
     XDM_BufDesc  *output, MPEG2VDEC_InArgs *inarg, MPEG2VDEC_OutArgs *outarg)
{

    S32 error;

#ifdef _PROFILE
time0 = TSC_read();
#endif

    ALG_activate((IALG_Handle)handle);

    error = handle->fxns->ividdec.process ((IVIDDEC2_Handle)handle, input,
         output, (IVIDDEC2_InArgs * )inarg, (IVIDDEC2_OutArgs *)outarg);

    ALG_deactivate((IALG_Handle)handle);

#ifdef _PROFILE
time5 = TSC_read();
#endif

    return(error);
}


/*!
*! Revision History
*!    05-01-2006 Dinesh Kumar: Created.
*!    12-07-2007 Raman       : Removed redundant function
*/

