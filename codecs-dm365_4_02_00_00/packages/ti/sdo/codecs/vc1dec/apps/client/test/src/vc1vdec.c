/** ============================================================================
 *  @file   vc1vdec.c
 *
 * @path $(PROJDIR)\src
 *
 *  @desc   This file implements all methods defined in 'vc1vdec.h'
 *  ============================================================================
 *  Copyright (c) Texas Instruments Inc 2006, 2007
 *
 * Use of this software is controlled by the terms and conditions found
 *  in the license agreement under which this software has been supplied
 * ===========================================================================*/

/* ---------------------compilation control switches -------------------------*/

#ifdef __TMS470__
#pragma CODE_SECTION(VC1VDEC_create,  ".text:create")
#pragma CODE_SECTION(VC1VDEC_control, ".text:control")
#pragma CODE_SECTION(VC1VDEC_delete,  ".text:delete")
#endif
/*******************************************************************************
*                  INCLUDE FILES
*******************************************************************************/
/* -------------------- system and platform files ----------------------------*/

//#include <std.h>
//#include <alg.h>
#include <xdc/std.h>
#include <ti/sdo/fc/utils/api/alg.h>
/*----------------------program files ----------------------------------------*/

#include "ivc1vdec.h"
#include "vc1vdec_ti.h"
/*******************************************************************************
*          EXTERNAL REFERENCES NOTE : only use if not found in header file
*******************************************************************************/
/*-----------------------data declarations -----------------------------------*/

/*-----------------------function prototypes ---------------------------------*/

/*******************************************************************************
*            PUBLIC DECLARATIONS Defined here, used elsewhere
*******************************************************************************/
/*-----------------------data declarations -----------------------------------*/

/*-----------------------function prototypes ---------------------------------*/
/*******************************************************************************
*              PRIVATE DECLARATIONS Defined here, used only here
*******************************************************************************/
/*-----------------------data declarations -----------------------------------*/

/*-----------------------function prototypes ---------------------------------*/

/*-----------------------macros ----------------------------------------------*/
/* =============================================================================
 *  @func     VC1VDEC_create
 *
 *  @brief    This function will creat algorithm instance to the VC1decoder
 *            all the required memory allocation and codec specific DMA
 *            ssettings are updated here.
 *
 *  @param    IVC1VDEC_Fxns * - pointer to VC1 Decode Algorrithm functions.
 *            VC1VDEC_Params *- pointer to VC1 Decode parmeters.
 *
 *  @return   VC1VDEC_Params - Pointer to VC1 Decode Algorithm functions.
 *
 * =============================================================================
*/
VC1VDEC_Handle VC1VDEC_create(const IVC1VDEC_Fxns *fxns,
             const VC1VDEC_Params *prms)
{
    return ((VC1VDEC_Handle)ALG_create((IALG_Fxns *)fxns, NULL,
        (IALG_Params *)prms));
}
/* =============================================================================
 *  @func     VC1VDEC_control
 *
 *  @brief    This function will Controll the decoder library.
 *            can be used to set parameters or read the status of decoder and
 *            input buffers.
 *
 *  @param    VC1VDEC_Handle * - pointer to VC1 Decode Algorrithm functions.
 *            VC1VDEC_Cmd      - Controll command to the decoder
 *            IVIDDEC2_DynamicParams - Pointer to the dynamic parameters
 *                               of the VC1 Decoder
 *            VC1VDEC_Status  -    Pointer to the status parameters of
 *                                 the decoder.
 *
 *  @return   error -  IALG_Ok when no error.
 *                  -  Error Code when error occured
 *
 * =============================================================================
*/
Int VC1VDEC_control(VC1VDEC_Handle handle, VC1VDEC_Cmd cmd,
            VC1VDEC_DynamicParams *params, VC1VDEC_Status *status)
{
   Int error;
/*
 * Activate the VC1 Decoder instace by passing the corresponding algorithm
 * handle
 */
    ALG_activate((IALG_Handle)handle);
/*
 * Call controll library function  returns error code when fails to
 * process the command.
 */
  error =   handle->fxns->ividdec.control ((IVIDDEC2_Handle)handle, cmd,
             (IVIDDEC2_DynamicParams *)params, (IVIDDEC2_Status *)status);
/*
 * De- activate the algorithm instance when finished
 */
    ALG_deactivate((IALG_Handle)handle);
  return (error);
}
/* =============================================================================
 *  @func     VC1VDEC_delete
 *
 *  @brief    This function will deletes the VC1 Decode instance
 *
 *  @param    VC1VDEC_Handle * - pointer to VC1 Decode Algorrithm functions.
 *
 *  @return   None
 *
 * =============================================================================
*/
void VC1VDEC_delete(VC1VDEC_Handle handle)
{
    ALG_delete((IALG_Handle)handle);
}
/* =============================================================================
 *  @func     VC1VDEC_decode
 *
 *  @brief    This is the main function decode the vc1 streams.
 *            This will activate the algorithm and starts decoding the frame
 *            with help of ARM968 and Kaleido.
 *
 *  @param    VC1VDEC_Handle * - pointer to VC1 Decode Algorrithm functions.
 *            XDM1_BufDesc *   - pointer to input buffer discriptor used as
 *                               input to the processs basically stream.
 *            XDM_BufDesc *    - Pointer to the output buffer discripter
 *                               gernarry display buffers.
 *            VC1VDEC_InArgs * - pointer to the input parameters wich controll
 *                               decode process in base class parameters only
 *                               length of the stream and buffer ID is provided.
 *
 *  @return   IALG_Ok when success
 *            Error Code.when fail
 *
 * =============================================================================
*/
Int VC1VDEC_decode(VC1VDEC_Handle handle, XDM1_BufDesc  *input,
     XDM_BufDesc  *output, VC1VDEC_InArgs *inarg, VC1VDEC_OutArgs *outarg)
{
   Int error;
/*
 * Activate VC1 Decode algorithm instance
 */
    ALG_activate((IALG_Handle)handle);



    error = handle->fxns->ividdec.process ((IVIDDEC2_Handle)handle, input,
         output, (IVIDDEC2_InArgs * )inarg, (IVIDDEC2_OutArgs *)outarg);



/*
 * Deactivate the algorithm when finished.
*/
    ALG_deactivate((IALG_Handle)handle);
    return(error);
}
