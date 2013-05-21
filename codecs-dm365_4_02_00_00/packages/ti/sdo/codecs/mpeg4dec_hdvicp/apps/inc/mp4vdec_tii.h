#ifndef mp4VDEC_TII_
#define mp4VDEC_TII_
/*!
******************************************************************************
* @file mp4vdec_tii.h

* @path $(PROJDIR)\Inc

*@brief     This header defines the interface used by clients of the
*           mp4VDEC module.
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
#ifdef DEVICE_ID_CHECK
#include <ti/sdo/fc/ires/addrspace/ires_addrspace.h>
#include "mpeg4vdec_ti_datatypedefs.h"
#endif

#include <ti/sdo/fc/utils/api/alg.h>
#include <ti/xdais/xdas.h>
#include <ti/sdo/fc/ires/edma3chan/ires_edma3Chan.h>
#include <ti/sdo/fc/ires/vicp/ires_vicp2.h>
#include <ti/sdo/fc/ires/hdvicp/ires_hdvicp.h>

/*!
 * ------------------------------ PROGRAM FILES -------------------------------
 */
#include "imp4vdec.h"

///////////////////////////////////////////////////////////////////////////////
///               PUBLIC DECLARATIONS Defined here, used elsewhere
///////////////////////////////////////////////////////////////////////////////

#define NUM_EDMA_RESOURCES 26
#define NUM_HDVICP_RESOURCES 1
#define NUM_MEMTABS 18

#ifdef DEVICE_ID_CHECK
#define NUM_ADDRSPACE_RESOURCES 1
#define NUM_RESOURCES (NUM_EDMA_RESOURCES + \
                     NUM_HDVICP_RESOURCES + \
                     NUM_ADDRSPACE_RESOURCES)

#else
#define NUM_RESOURCES (NUM_EDMA_RESOURCES + \
                     NUM_HDVICP_RESOURCES)
#endif

typedef struct mp4VDEC_TII_Obj
{
    IALG_Obj        alg;
    void            *mp4_context;  /* Scatch to MPEG4 codec state struture  */
    void            *ext_context0; /*Persitant to MPEG4 handle struture     */
    void            *ext_context1; /*Persitant to MPEG4 codec state struture*/
    void            *hdvicpHandle; /* pointer to the HDVICP handle          */
    unsigned int    decoderInitialized; /* First time flag for decoder      */
    IRES_EDMA3CHAN_Handle   resourceHandles[NUM_EDMA_RESOURCES];
    IRES_EDMA3CHAN_ProtocolArgs edma3ProtocolArgs[NUM_EDMA_RESOURCES];
#ifdef DEVICE_ID_CHECK
    IRES_ADDRSPACE_Handle       addrspaceHandle;
    IRES_ADDRSPACE_ProtocolArgs addrspaceProtocolArgs;
    unsigned char *addrSpacePointer;
#endif
    IRES_HDVICP_Handle  hdvicpResourceHandles[NUM_HDVICP_RESOURCES];
    IRES_HDVICP_ProtocolArgs    hdvicpProtocolArgs[NUM_HDVICP_RESOURCES];
    char resourceState[NUM_RESOURCES];

    unsigned int alloc_tccs_map_lo;
    unsigned int alloc_tccs_map_hi;
    IALG_MemRec memTab[18];
    unsigned int algo_activated;
    unsigned int resource_init_success;
    unsigned int vol_decoded;
    unsigned int frame_not_present;
    unsigned int num_active_resources;
    unsigned int frame_order;
} mp4VDEC_TII_Obj;

/*
*****************************************************************************
* H264VDEC_TI_IALG
*
* TI's implementation of the IALG interface for H264VDEC
*/
#ifdef _TMS320C6X
extern far IALG_Fxns MPEG4VDEC_TI_IALG;
#else
extern IALG_Fxns MPEG4VDEC_TI_IALG;
#endif







#endif  /* mp4VDEC_ */












































