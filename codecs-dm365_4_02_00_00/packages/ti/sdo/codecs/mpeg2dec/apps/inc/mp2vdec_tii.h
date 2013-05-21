#ifndef mp2VDEC_TII_
#define mp2VDEC_TII_
/*!
******************************************************************************
* @file mp2vdec_tii.h

* @path $(PROJDIR)\Inc

*@brief     This header defines the interface used by clients of the
*           mp2VDEC module.
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
//#include <xdc/std.h>
#include <ti/sdo/fc/utils/api/alg.h>
//#include <xdas.h>
//#include <ires.h>
#include <ti/sdo/fc/ires/hdvicp/ires_hdvicp.h>
#include <ti/sdo/fc/ires/edma3chan/ires_edma3Chan.h>

#ifdef DEVICE_ID_CHECK
#include <ti/sdo/fc/ires/addrspace/ires_addrspace.h>
#include "datatypedefs.h"
#endif


/*!
 * ------------------------------ PROGRAM FILES ------------------------------
 */
#include "imp2vdec.h"
//#include "hdvicp_framework.h"

//////////////////////////////////////////////////////////////////////////////
///               PUBLIC DECLARATIONS Defined here, used elsewhere
//////////////////////////////////////////////////////////////////////////////
/*!
* ---------------------------- DATA DECLARATIONS -----------------------------
*/


#define NUM_HDVICP_RESOURCES 1
#define NUM_EDMA_RESOURCES  15
#define NUM_QDMA_RESOURCES   4
#define MAX_PARAM_PER_CHANNEL 20



#ifdef DEVICE_ID_CHECK
#define NUM_ADDRSPACE_RESOURCES 1
#define NUM_RESOURCES (NUM_HDVICP_RESOURCES + NUM_EDMA_RESOURCES \
                    						+ NUM_ADDRSPACE_RESOURCES)

#else
#define NUM_RESOURCES (NUM_HDVICP_RESOURCES + NUM_EDMA_RESOURCES)
#endif

/*!
******************************************************************************
* MPEG2VDEC_TI_Obj
******************************************************************************
*/
typedef struct MPEG2VDEC_TI_Obj {
    IALG_Obj        alg;   /*!To start with setting the height of frame  */
                          /*!To start with setting the height of frame  */
    void *mp2_context;
//    IDMA3_Handle handle[4];
    void *ext_context0;
    void *ext_context1;
//CHANGED
    IRES_EDMA3CHAN_Handle       edma3ResourceHandles[NUM_EDMA_RESOURCES];
    IRES_EDMA3CHAN_Handle       qdma3ResourceHandles[NUM_QDMA_RESOURCES];
    IRES_EDMA3CHAN_ProtocolArgs edma3ProtocolArgs[NUM_EDMA_RESOURCES +
                                                  NUM_QDMA_RESOURCES];

    IRES_YieldFxn     yieldFxn;      /* acquired from RMAN during init */
    IRES_YieldArgs    yieldArgs;     /* acquired from RMAN during init */
    IRES_YieldContext yieldContext;  /* to pass to the 'yield' fxn     */

    XDAS_UInt16 transfer_pending_edma[64];
    XDAS_UInt16 transfer_pending_qdma[8];

    volatile XDAS_UInt32 *edma_params_array[NUM_EDMA_RESOURCES];
    volatile XDAS_UInt32 *qdma_params_array[NUM_QDMA_RESOURCES];
    XDAS_UInt32           edma_tcc_array[NUM_EDMA_RESOURCES];
    XDAS_UInt32           qdma_tcc_array[NUM_QDMA_RESOURCES];
    XDAS_UInt32           edma_phy_to_lgl_map[NUM_EDMA_RESOURCES];
    XDAS_UInt32           qdma_phy_to_lgl_map [NUM_QDMA_RESOURCES];
    XDAS_UInt32           num_edma_channels;

//CHANGED
    char resourceState[NUM_RESOURCES];
    IRES_HDVICP_Handle  hdvicpResourceHandles[NUM_HDVICP_RESOURCES];
    IRES_HDVICP_ProtocolArgs    hdvicpProtocolArgs[NUM_HDVICP_RESOURCES];

#ifdef DEVICE_ID_CHECK
    IRES_ADDRSPACE_Handle   	addrspaceHandle;
    IRES_ADDRSPACE_ProtocolArgs addrspaceProtocolArgs;
    U8 *addrSpacePointer;
#endif

    short edmaChanPaRamArray[NUM_EDMA_RESOURCES][MAX_PARAM_PER_CHANNEL];
    short qdmaChanPaRamArray[NUM_QDMA_RESOURCES][MAX_PARAM_PER_CHANNEL];

#ifdef SLICE_LEVEL_CONCEAL
    /* One Extra memTab for Error Concealment of I Frames.               */
	IALG_MemRec memTab[15];
#else
	IALG_MemRec memTab[14];
#endif
	unsigned int resource_init_success;
    unsigned int alloc_tccs_map_lo;
    unsigned int alloc_tccs_map_hi;


} MPEG2VDEC_TI_Obj;

/*
*****************************************************************************
* MPEG2VDEC_TI_IALG
*
* TII's implementation of the IALG interface for mp2VDEC
*/
#ifdef _TMS320C6X
extern far IALG_Fxns MPEG2VDEC_TI_IALG;
#else
extern IALG_Fxns MPEG2VDEC_TI_IALG;
#endif

/*
****************************************************************************
* MPEG2VDEC_TI_Imp2VDEC
*
* TII's implementation of the Imp2VDEC interface
*/
#ifdef _TMS320C6X
extern far Imp2VDEC_Fxns MPEG2VDEC_TI_IMPEG2VDEC;
#else
extern Imp2VDEC_Fxns MPEG2VDEC_TI_IMPEG2VDEC;
#endif

#ifdef _TMS320C6X
extern far IRES_Fxns MPEG2VDEC_TI_IRES;
#else
extern IRES_Fxns MPEG2VDEC_TI_IRES;
#endif

/*!
*****************************************************************************
*@typedef MPEG2VDEC_Handle
*
*@brief  This pointer is used to reference all mp2VDEC instance objects
*
*@note   None
*
*****************************************************************************/
typedef struct Imp2VDEC_Obj *MPEG2VDEC_Handle;

/*!
*****************************************************************************
*@typedef mp2VDEC_Params
*
*@brief  This structure defines the creation parameters for all mp2VDEC
*        objects
*
*@note   None
*
*****************************************************************************/

typedef Imp2VDEC_Params mp2VDEC_Params;

/*!
*****************************************************************************
*@typedef mp2VDEC_DynamicParams
*
*@brief  This structure defines the creation parameters for all mp2VDEC
*        objects
*
*@note   None
*
*****************************************************************************/
typedef Imp2VDEC_DynamicParams MPEG2VDEC_DynamicParams;

/*!
*****************************************************************************
*@typedef mp2VDEC_Status
*
*@brief  This structure store the status of the the real-time parameters for
*        mp2VDEC objects
*
*@note   None
*
*****************************************************************************/

typedef struct Imp2VDEC_Status   MPEG2VDEC_Status;
/*!
*****************************************************************************
*@typedef mp2VDEC_OutArgs
*
*@brief  This structure defines input arguments for all mp2VDEC objects
*
*@note   None
*
*****************************************************************************/

typedef Imp2VDEC_OutArgs MPEG2VDEC_OutArgs;

/*!
*****************************************************************************
*@typedef mp2VDEC_InArgs
*
*@brief  This structure defines the real-time input arguments for mp2VDEC
*        objects
*
*@note   None
*
*****************************************************************************/
typedef struct Imp2VDEC_InArgs   MPEG2VDEC_InArgs;

/*!
*****************************************************************************
*@typedef mp2VDEC_Cmd
*
*@brief  This typedef defines the control commands mp2VDEC objects
*
*@note   None
*
*****************************************************************************/

typedef Imp2VDEC_Cmd   MPEG2VDEC_Cmd;

/*!
 * ---------------------------- FUNCTION DECLARATIONS ------------------------
 */

/*!
*****************************************************************************
*@typedef mp2VDEC_create
*
*@brief  Create an mp2VDEC instance object (using parameters specify by prms)
*
*@note   None
*
*****************************************************************************/
extern MPEG2VDEC_Handle MPEG2VDEC_create(const Imp2VDEC_Fxns *fxns,
                                            const mp2VDEC_Params *prms);
/*!
*****************************************************************************
*@typedef mp2VDEC_control
*
*@brief  Get, set, and change the parameters of the mp2VDEC function
*        (using parameters specified by status).
*
*@note   None
*
*****************************************************************************/

extern Int MPEG2VDEC_control(MPEG2VDEC_Handle handle, MPEG2VDEC_Cmd cmd,
                     MPEG2VDEC_DynamicParams *params, MPEG2VDEC_Status *status);
/*!
*****************************************************************************
*@typedef MPEG2VDEC_delete
*
*@brief  Delete the mp2VDEC instance object specified by handle
*
*@note   None
*
*****************************************************************************/
extern Void MPEG2VDEC_delete(MPEG2VDEC_Handle handle);

/*!
*****************************************************************************
*@typedef mp2VDEC_decode
*
*@brief  Decodes the frame/slice or one data unit as specified
*
*@note   None
*
*****************************************************************************/

extern Int MPEG2VDEC_decode(MPEG2VDEC_Handle handle, XDM1_BufDesc *inptr,
         XDM_BufDesc *outptr, MPEG2VDEC_InArgs *inarg, MPEG2VDEC_OutArgs *outarg);

/*!
* ---------------------------- MACRO DEFINATIONS -----------------------------
*/
/*!
*****************************************************************************
*@typedef IMPEG2VDEC_PARAMS
*
*@brief  This structure defines the default creation parameters for mp2VDEC
*        objects
*
*@note   None
*
*****************************************************************************/

#define MPEG2VDEC_PARAMS       Imp2VDEC_PARAMS

#define MPEG2VDEC_GETSTATUS    Imp2VDEC_GETSTATUS
#define MPEG2VDEC_SETPARAMS    Imp2VDEC_SETPARAMS
#define MPEG2VDEC_PREPROCESS   Imp2VDEC_PREPROCESS
#define MPEG2VDEC_RESET        Imp2VDEC_RESET
#define MPEG2VDEC_FLUSH        Imp2VDEC_FLUSH
#define MPEG2VDEC_SETDEFAULT   Imp2VDEC_SETDEFAULT
#define MPEG2VDEC_GETBUFINFO   Imp2VDEC_GETBUFINFO
#define mp2VDEC_OUTPUTORDER  Imp2VDEC_OUTPUTORDER




#endif  /* mp2VDEC_ */





























































































































