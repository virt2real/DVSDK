#ifndef VC1VDEC_TI_
#define VC1VDEC_TI_
/*!
******************************************************************************
* @file VC1VDEC.h
* @path $(PROJDIR)\Inc
*@brief     This header defines the interface used by clients of the
*           VC1VDEC module.
*
* Copyright (c) Texas Instruments Inc 2005, 2006
* Use of this software is controlled by the terms and conditions found
* in the license agreement under which this software has been supplied
*  @defgroup  CONF_FILE Configuararion file for decoder
******************************************************************************/

///////////////////////////////////////////////////////////////////////////////
///                                INCLUDE FILES
///////////////////////////////////////////////////////////////////////////////
/*!
 * ----------------------- SYSTEM AND PLATFORM FILES --------------------------
 */

#include <ti/sdo/fc/ires/edma3chan/ires_edma3Chan.h>
#include <ti/sdo/fc/ires/vicp/ires_vicp2.h>
#include <ti/sdo/fc/ires/hdvicp/ires_hdvicp.h>
#include <ti/sdo/fc/ires/addrspace/ires_addrspace.h>
/*!
 * ------------------------------ PROGRAM FILES -------------------------------
 */
#include "ivc1vdec.h"

///////////////////////////////////////////////////////////////////////////////
///               PUBLIC DECLARATIONS Defined here, used elsewhere
///////////////////////////////////////////////////////////////////////////////
#define NUM_EDMA_RESOURCES 26
#define NUM_HDVICP_RESOURCES 1


#define NUM_ADDRSPACE_RESOURCE 1



#define NUM_RESOURCES (NUM_EDMA_RESOURCES + \
                     NUM_HDVICP_RESOURCES + NUM_ADDRSPACE_RESOURCE)

#define MAX_MEM_TABS 23

/*!
* ---------------------------- DATA DECLARATIONS -----------------------------
*/
/*!
**********************************************************************************
* VC1VDEC_TI_Obj
**********************************************************************************
*/
typedef struct VC1VDEC_TI_Obj {
    IALG_Obj        alg;   /*!To start with setting the height of frame  */
                          /*!To start with setting the height of frame  */
    //void *vc1_context;
/*
 * Pointer to DMA Handle
 */
    //void *DMAHandle;
    void *ext_context0;
    void *ext_context1;
    void *hdvicpHandle;
    unsigned int    decoderInitialized; /* First time flag for decoder      */
	IRES_EDMA3CHAN_Handle   resourceHandles[NUM_EDMA_RESOURCES];
	IRES_EDMA3CHAN_ProtocolArgs edma3ProtocolArgs[NUM_EDMA_RESOURCES];
	IRES_HDVICP_Handle  hdvicpResourceHandles[NUM_HDVICP_RESOURCES];
	IRES_HDVICP_ProtocolArgs    hdvicpProtocolArgs[NUM_HDVICP_RESOURCES];

    IRES_ADDRSPACE_Handle   	addrspaceHandle[NUM_ADDRSPACE_RESOURCE];
    IRES_ADDRSPACE_ProtocolArgs addrspaceProtocolArgs[NUM_ADDRSPACE_RESOURCE];

    char resourceState[NUM_RESOURCES];
	void *memTab_base_addr[MAX_MEM_TABS]; //--->Only926
    unsigned int   memTab_base_size[MAX_MEM_TABS]; //--->Only926
	unsigned char memTab_base_space[MAX_MEM_TABS]; //--->Only926
    unsigned char memTab_base_attrs[MAX_MEM_TABS]; //--->Only926
    unsigned int alloc_tccs_map_lo;
    unsigned int alloc_tccs_map_hi;
} VC1VDEC_TI_Obj;
/*
*****************************************************************************
* VC1VDEC_TI_IALG
*
* TI's implementation of the IALG interface for VC1VDEC
*/
#ifdef _TMS320C6X
extern far IALG_Fxns VC1VDEC_TI_IALG;
#else
extern IALG_Fxns VC1VDEC_TI_IALG;
#endif

/*!
*****************************************************************************
*@typedef VC1VDEC_Handle
*
*@brief  This pointer is used to reference all VC1VDEC instance objects
*
*@note   None
*
******************************************************************************/
typedef struct IVC1VDEC_Obj *VC1VDEC_Handle;
/*!
*****************************************************************************
*@typedef VC1VDEC_Params
*
*@brief  This structure defines the creation parameters for all VC1VDEC objects
*
*@note   None
*
******************************************************************************/
typedef IVC1VDEC_Params VC1VDEC_Params;
/*!
*****************************************************************************
*@typedef VC1VDEC_DynamicParams
*
*@brief  This structure defines the creation parameters for all VC1VDEC objects
*
*@note   None
*
******************************************************************************/
typedef IVC1VDEC_DynamicParams VC1VDEC_DynamicParams;
/*!
*****************************************************************************
*@typedef VC1VDEC_Status
*
*@brief  This structure store the status of the the real-time parameters for
*        VC1VDEC objects
*
*@note   None
*
******************************************************************************/
typedef struct IVC1VDEC_Status   VC1VDEC_Status;
/*!
*****************************************************************************
*@typedef VC1VDEC_OutArgs
*
*@brief  This structure defines input arguments for all VC1VDEC objects
*
*@note   None
*
******************************************************************************/
typedef IVC1VDEC_OutArgs VC1VDEC_OutArgs;
/*!
*****************************************************************************
*@typedef VC1VDEC_InArgs
*
*@brief  This structure defines the real-time input arguments for VC1VDEC
*        objects
*
*@note   None
*
*****************************************************************************/
typedef struct IVC1VDEC_InArgs   VC1VDEC_InArgs;
/*!
*****************************************************************************
*@typedef VC1VDEC_Cmd
*
*@brief  This typedef defines the control commands VC1VDEC objects
*
*@note   None
*
*****************************************************************************/
typedef IVC1VDEC_Cmd   VC1VDEC_Cmd;
/*!
 * ---------------------------- FUNCTION DECLARATIONS -----------------------------
 */
/*!
*****************************************************************************
*@typedef VC1VDEC_create
*
*@brief  Create an VC1VDEC instance object (using parameters specify by prms)
*
*@note   None
*
*****************************************************************************/
extern VC1VDEC_Handle VC1VDEC_create(const IVC1VDEC_Fxns *fxns,
                                            const VC1VDEC_Params *prms);
/*!
*****************************************************************************
*@typedef VC1VDEC_control
*
*@brief  Get, set, and change the parameters of the VC1VDEC function
*        (using parameters specified by status).
*
*@note   None
*
*****************************************************************************/
extern Int VC1VDEC_control(VC1VDEC_Handle handle, VC1VDEC_Cmd cmd,
                     VC1VDEC_DynamicParams *params, VC1VDEC_Status *status);
/*!
*****************************************************************************
*@typedef VC1VDEC_delete
*
*@brief  Delete the VC1VDEC instance object specified by handle
*
*@note   None
*
*****************************************************************************/
extern Void VC1VDEC_delete(VC1VDEC_Handle handle);
/*!
*****************************************************************************
*@typedef VC1VDEC_decode
*
*@brief  Decodes the frame/slice or one data unit as specified
*
*@note   None
*
*****************************************************************************/
extern Int VC1VDEC_decode(VC1VDEC_Handle handle, XDM1_BufDesc *inptr,
         XDM_BufDesc *outptr, VC1VDEC_InArgs *inarg, VC1VDEC_OutArgs *outarg);
/*!
* ---------------------------- MACRO DEFINATIONS -----------------------------
*/
/*!
*****************************************************************************
*@typedef IVC1VDEC_PARAMS
*
*@brief  This structure defines the default creation parameters for VC1VDEC objects
*
*@note   None
*
******************************************************************************/

#define VC1VDEC_PARAMS   IVC1VDEC_PARAMS

#define VC1VDEC_GETSTATUS    IVC1VDEC_GETSTATUS
#define VC1VDEC_SETPARAMS    IVC1VDEC_SETPARAMS
#define VC1VDEC_PREPROCESS   IVC1VDEC_PREPROCESS
#define VC1VDEC_RESET        IVC1VDEC_RESET
#define VC1VDEC_FLUSH        IVC1VDEC_FLUSH
#define VC1VDEC_SETDEFAULT   IVC1VDEC_SETDEFAULT
#define VC1VDEC_GETBUFINFO   IVC1VDEC_GETBUFINFO

#endif  /* VC1VDEC_ */
