/** ==========================================================================
 *  @file   mpeg4vedc_ti_api.h
 *
 *  @path   $(PROJDIR)\Inc
 *
 *  @desc   A header file describing funtion protypes for moeg4d decoder
 *          interface functions with rapers.
 *
 *  ==========================================================================
 *  Copyright (c) Texas Instruments Inc 2006, 2007
 *
 *  Use of this software is controlled by the terms and conditions found
 *  in the license agreement under which this software has been supplied
 * =========================================================================*/

/* -------------------- compilation control switches ---------------------- */

#ifndef MP4VDEC_API_
#define MP4VDEC_API_

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
extern Imp4VDEC_Handle mp4VDEC_create(
                                      const Imp4VDEC_Fxns   *fxns,
                                      const Imp4VDEC_Params *prms
                                     );

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
extern Int  mp4VDEC_control(
                            Imp4VDEC_Handle        handle,
                            Imp4VDEC_Cmd           cmd,
                            Imp4VDEC_DynamicParams *params,
                            Imp4VDEC_Status        *status
                           );

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
extern void  mp4VDEC_delete(Imp4VDEC_Handle handle);

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
extern void  mp4VDEC_init(void);

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
extern void  mp4VDEC_exit(void);

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
extern Int mp4VDEC_decode(
						  Imp4VDEC_Handle    handle,
                          XDM1_BufDesc     * input,
                          XDM_BufDesc      * output,
                          Imp4VDEC_InArgs  * inarg,
                          Imp4VDEC_OutArgs * outarg
                         );


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

#endif /*MP4VDEC_API_*/



/*!
 *! Revision History
 *! ================
 *! 27-Aug-2007   Kumar    : Incorporated code review comments.
 *! 01-Jul-2006   Prashanth: Created.
 *!
 */
