/** ==========================================================================
 *  @file   mpeg4vedc_ti_api.c
 *
 *  @path   $(PROJDIR)\Src
 *
 *  @desc  This File contains the definition of interrupt handler for ARM968,
 *
 *  ==========================================================================
 *  Copyright (c) Texas Instruments Inc 2006, 2007
 *
 *  Use of this software is controlled by the terms and conditions found
 *  in the license agreement under which this software has been supplied
 * =========================================================================*/


/* -------------------- compilation control switches -----------------------*/


/****************************************************************************
*   INCLUDE FILES
*****************************************************************************/

/* -------------------- system and platform files ------------------------- */
#include <xdc/std.h>
#include <ti/sdo/fc/utils/api/alg.h>
/* ------------------------- program files -------------------------------- */
#include "imp4vdec.h"

/****************************************************************************
*   EXTERNAL REFERENCES NOTE : only use if not found in header file
*****************************************************************************/

/* ------------------------ data declarations ----------------------------- */

/* ----------------------- function prototypes ---------------------------- */


/****************************************************************************
*   PUBLIC DECLARATIONS Defined here, used elsewhere
*****************************************************************************/

/* ----------------------- data declarations ------------------------------ */

/* ---------------------- function prototypes ----------------------------- */


/****************************************************************************
*   PRIVATE DECLARATIONS Defined here, used only here
*****************************************************************************/

/* ---------------------- data declarations ------------------------------- */

/* --------------------- function prototypes ------------------------------ */


/* ---------------------------- macros ------------------------------------ */


/* ===========================================================================
 *  @func   mp4VDEC_create()
 *
 *  @desc   Create an mp4VDEC instance object using specified parameters
 *          .
 *  @param  Imp4VDEC_Fxns  *fxns.:Handle to ALG functions
 *
 *  @param  mp4VDEC_Params *prms :Parametre specific to current instance
 *
 *  @return mp4VDEC_Handle       :Algorithm instance handle.
 * ===========================================================================
 */
Imp4VDEC_Handle mp4VDEC_create(
                               const Imp4VDEC_Fxns   *fxns,
                               const Imp4VDEC_Params *prms
                              )
{
    Imp4VDEC_Handle handle;
    handle =  ((Imp4VDEC_Handle)ALG_create((IALG_Fxns   *)fxns, NULL,
                                           (IALG_Params *)prms));
    return handle;
} /* mp4VDEC_create() */



/* ===========================================================================
 *  @func   mp4VDEC_control()
 *
 *  @desc    Function to either write to the read/write parameters in the
 *           status structure or to read all the parameters in the status
 *           structure
 *.
 *  @param  (mp4VDEC_Handle handle.: Algorithm instance handle
 *
 *  @param   mp4VDEC_Cmd cmd
 *
 *  @param   mp4VDEC_DynamicParams *params
 *
 *  @param   mp4VDEC_Status *status
 *
 *  @return  Decode call status (Pass/Error)
 *.
 * ===========================================================================
 */
Int mp4VDEC_control(Imp4VDEC_Handle        handle,
                    Imp4VDEC_Cmd           cmd,
                    Imp4VDEC_DynamicParams *params,
                    Imp4VDEC_Status        *status
                   )
{
    Int error;
    /* ALG_activate function to be called before each control call to copy
     * image of handle structure data in the external persistant memory to
     * scarcth memory
     */
    ALG_activate((IALG_Handle)handle);
    error =   handle->fxns->ividdec.control ((IVIDDEC2_Handle)handle,
                                              cmd,
                                             (IVIDDEC2_DynamicParams *)params,
                                             (IVIDDEC2_Status *)status
                                            );
    /* ALG_deactivate function to be called before each control call to store
     * image of handle structure data in the scarcth  memory to
     * external persistant memory
     */
    ALG_deactivate((IALG_Handle)handle);
    return (error);
}/* mp4VDEC_control() */


/* ===========================================================================
 *  @func   mp4VDEC_delete()
 *
 *  @desc   Delete the mp4VDEC instance object specified by handle
 *.
 *  @param  (mp4VDEC_Handle handle.: Algorithm instance handle
 *
 *  @return  None
 *.
 * ===========================================================================
 */
void mp4VDEC_delete(Imp4VDEC_Handle handle)
{
    ALG_delete((IALG_Handle)handle);
}/* mp4VDEC_delete() */



/* ===========================================================================
 *  @func    mp4VDEC_init()
 *
 *  @desc    mp4VDEC module initialization
 *.
 *  @param   None
 *
 *  @return  None
 *.
 * ===========================================================================
 */
void  mp4VDEC_init(void)
{
 /* Need to be Implimented */
}/* mp4VDEC_init() */

/* ===========================================================================
 *  @func    mp4VDEC_exit()
 *
 *  @desc    mp4VDEC module finalization
 *.
 *  @param   None
 *
 *  @return  None
 *.
 * ===========================================================================
 */
void  mp4VDEC_exit(void)
{
 /* Need to be Implimented */
} /* mp4VDEC_exit() */



/* ===========================================================================
 *  @func   mp4VDEC_control()
 *
 *  @desc    Function to process one decode call
 *.
 *  @param  (mp4VDEC_Handle handle.: Algorithm instance handle
 *
 *  @param   XDM1_BufDesc    *input : Input buffer descriptors
 *
 *  @param   XDM_BufDesc     *output: Output buffer descriptors
 *
 *  @param   mp4VDEC_InArgs  *inarg : Input arguments handle
 *
 *  @param   mp4VDEC_OutArgs *outarg: Output arguments handle
 *
 *  @return  Decode call status (Pass/Error)
 *.
 * ===========================================================================
 */
Int mp4VDEC_decode(Imp4VDEC_Handle  handle,
                   XDM1_BufDesc     *input,
                   XDM_BufDesc      *output,
                   Imp4VDEC_InArgs  *inarg,
                   Imp4VDEC_OutArgs *outarg)
{
    Int error;
    /* ALG_activate function to be called before each process call to copy
     * image of handle structure data in the external persistant memory to
     * scarcth memory
     */
    ALG_activate((IALG_Handle)handle);
    error = handle->fxns->ividdec.process ((IVIDDEC2_Handle)handle,
                                           input,
                                           output,
                                           (IVIDDEC2_InArgs * )inarg,
                                           (IVIDDEC2_OutArgs *)outarg
                                          );
    /* ALG_deactivate function to be called before each process call to store
     * image of handle structure data in the scarcth  memory to
     * external persistant memory
     */
    ALG_deactivate((IALG_Handle)handle);
    return(error);
} /* mp4VDEC_decode() */



/*!
 *! Revision History
 *! ================
 *! 16-Aug-2007   Kumar    : Incorporated code review comments.
 *! 01-Jul-2006   Prashanth:  Created.
 *!
 */
