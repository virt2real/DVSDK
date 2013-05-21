#ifndef mp4VENC_TII_
#define mp4VENC_TII_
/*!
******************************************************************************
* @file mp4vdec_tii.h

* @path $(PROJDIR)\Inc

*@brief     This header defines the interface used by clients of the
*           mp4VENC module.
*
* Copyright (c) Texas Instruments Inc 2005, 2006

* Use of this software is controlled by the terms and conditions found
* in the license agreement under which this software has been supplied
*  @defgroup  CONF_FILE Configuararion file for decoder
******************************************************************************/
/*!
*! Revision History
*!    05-01-2006 Dinesh Kumar: Created.
*/

///////////////////////////////////////////////////////////////////////////////
///                                INCLUDE FILES
///////////////////////////////////////////////////////////////////////////////

/*!
 * ----------------------- SYSTEM AND PLATFORM FILES --------------------------
 */
#include <ti/sdo/fc/utils/api/alg.h>
#include <ti/xdais/xdas.h>
#include <ti/sdo/fc/ires/edma3chan/ires_edma3Chan.h>
#include <ti/sdo/fc/ires/vicp/ires_vicp2.h>
#include <ti/sdo/fc/ires/hdvicp/ires_hdvicp.h>

/*!
 * ------------------------------ PROGRAM FILES -------------------------------
 */
#include "imp4venc.h"

///////////////////////////////////////////////////////////////////////////////
///               PUBLIC DECLARATIONS Defined here, used elsewhere
///////////////////////////////////////////////////////////////////////////////

#define NUM_EDMA_RESOURCES 36
#define NUM_HDVICP_RESOURCES 1

#ifdef ON_LINUX
#define NUM_ADDRSPACE_RESOURCES 1
#else
#define NUM_ADDRSPACE_RESOURCES 0
#endif

#define NUM_RESOURCES (NUM_EDMA_RESOURCES +   \
                       NUM_HDVICP_RESOURCES + \
                       NUM_ADDRSPACE_RESOURCES)

//#define NUM_RESOURCES (NUM_EDMA_RESOURCES + \
//                     NUM_HDVICP_RESOURCES)

typedef struct mp4VENC_TII_Obj
{
    IALG_Obj        alg;
    void            *mp4_context;  /* Scatch to MPEG4 codec state struture  */
    void            *ext_context0; /*Persitant to MPEG4 handle struture     */
    void            *ext_context1; /*Persitant to MPEG4 codec state struture*/
	void            *hdvicpHandle; /* pointer to the HDVICP handle          */
	unsigned int    encoderInitialized; /* First time flag for decoder      */
    IRES_EDMA3CHAN_Handle   resourceHandles[NUM_EDMA_RESOURCES];
    IRES_EDMA3CHAN_ProtocolArgs edma3ProtocolArgs[NUM_EDMA_RESOURCES];
    IRES_ADDRSPACE_Handle   	addrspaceHandle;
    IRES_ADDRSPACE_ProtocolArgs addrspaceProtocolArgs;
    IRES_HDVICP_Handle  hdvicpResourceHandles[NUM_HDVICP_RESOURCES];
    IRES_HDVICP_ProtocolArgs    hdvicpProtocolArgs[NUM_HDVICP_RESOURCES];
    char resourceState[NUM_RESOURCES];

} mp4VENC_TII_Obj1;







#endif  /* mp4VENC_ */































































































































