#ifndef Imp2VDEC_TII_
#define Imp2VDEC_TII_
/*!
******************************************************************************
* @file imp2vdec_tii.h

* @path $(PROJDIR)\Inc

*@brief     Imp2VDEC Interface Header.
*
* Copyright (c) Texas Instruments Inc 2005, 2006

* Use of this software is controlled by the terms and conditions found
* in the license agreement under which this software has been supplied
*  @defgroup  CONF_FILE Configuararion file for decoder
*****************************************************************************/
/*!
*! Revision History
*!    05-01-2006 Dinesh Kumar: Created.
*/

//////////////////////////////////////////////////////////////////////////////
///                                INCLUDE FILES
//////////////////////////////////////////////////////////////////////////////

/*!
 * ----------------------- SYSTEM AND PLATFORM FILES -------------------------
 */
#include <ti/xdais/xdas.h>
#include <ti/xdais/ialg.h>
#include <ti/xdais/dm/ividdec2.h>
#include <ti/xdais/ires.h>

/*!
 * ------------------------------ PROGRAM FILES ------------------------------
 */
#include "imp2vdec.h"

//////////////////////////////////////////////////////////////////////////////
///               PUBLIC DECLARATIONS Defined here, used elsewhere
//////////////////////////////////////////////////////////////////////////////
/*!
* ---------------------------- DATA DECLARATIONS -----------------------------
*/

/*
 *  ======== mp2VDEC_TII_IALG ========
 *  TI's implementation of the IALG interface for mp2VDEC
 */
extern IALG_Fxns MPEG2VDEC_TI_IALG;


/*
 *  ======== mp2VDEC_TII_IDMA3 ========
 *  TI's implementation of mp2VDec's IDMA3 interface
 */
//extern IDMA3_Fxns mp2VDEC_TII_IDMA3;

/*
 *  ======== mp2VDEC_TII_IRES ========
 *  TI's implementation of mp2VDec's IRES interface
 */

extern IRES_Fxns MPEG2VDEC_TI_IRES;

/*!
 * ---------------------------- FUNCTION DECLARATIONS ------------------------
 */

/*
 *  ======== mp2VDEC_TII_Imp2VDEC ========
 *  TI's implementation of mp2VDec's IDMA3 interface
 */
extern Imp2VDEC_Fxns MPEG2VDEC_TI_IMPEG2VDEC;

extern Int MPEG2VDEC_TI_init(IALG_Handle        handle,
                            const IALG_MemRec *memTab,
                            IALG_Handle        parent,
                            const IALG_Params *params);

extern XDAS_Int32  MPEG2VDEC_TI_decode (IVIDDEC2_Handle handle,
                                       XDM1_BufDesc *inptr,
                                       XDM_BufDesc *outptr,
                                       IVIDDEC2_InArgs *inargs,
                                       IVIDDEC2_OutArgs *outargs);


extern Void MPEG2VDEC_TI_exit(Void);



#endif  /* Imp2VDEC_TII */
