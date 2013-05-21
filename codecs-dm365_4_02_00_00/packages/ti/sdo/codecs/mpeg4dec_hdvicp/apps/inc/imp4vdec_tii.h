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

#ifndef Imp4VDEC_TII_
#define Imp4VDEC_TII_


/****************************************************************************
*   INCLUDE FILES
*****************************************************************************/
/* -------------------- system and platform files ------------------------- */
#include <ti/xdais/xdas.h>
#include <ti/xdais/ialg.h>
#include <ti/xdais/dm/ividdec2.h>
#include <ti/xdais/ires.h>
/* ------------------------- program files -------------------------------- */
#include "imp4vdec.h"

/****************************************************************************
*   EXTERNAL REFERENCES NOTE : only use if not found in header file
*****************************************************************************/
/* ------------------------ data declarations ----------------------------- */

/* Referene to external symbol MPEG4VDEC_TI_IALG, holding the pointers to the
 * all the basic algorithm creation related functions.
 */
extern IALG_Fxns     MPEG4VDEC_TI_IALG;

/* Referene to external symbol MPEG4VDEC_TI_IMPEG4VDEC,holding the pointers to
 * the all the mpeg4 decoder algorithm interfaces
 */
extern Imp4VDEC_Fxns MPEG4VDEC_TI_IMPEG4VDEC;

extern IRES_Fxns MPEG4VDEC_TI_IRES;

/* ----------------------- function prototypes ---------------------------- */

/****************************************************************************
*   PUBLIC DECLARATIONS Defined here, used elsewhere
*****************************************************************************/
/* ----------------------- data declarations ------------------------------ */
/* ----------------------- function prototypes ---------------------------- */

/****************************************************************************
*   PRIVATE DECLARATIONS Defined here, used only here
*****************************************************************************/
/* ---------------------- data declarations ------------------------------- */
/* --------------------- function prototypes ------------------------------ */

/* ---------------------------- macros ------------------------------------ */

#endif  /* Imp4VDEC_TII */

/* End of file. */




/*!
 *! Revision History
 *! ================
 *! 27-Aug-2007   Kumar    : Incorporated code review comments.
 *! 01-Jul-2006   Prashanth: Created.
 *!
 */
