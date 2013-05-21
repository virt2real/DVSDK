/** ===========================================================================
* @file  h264venc_arm968.c
*
* @path  $(PROJDIR)\Client\Test\Src
*
* @brief This function polls for the signal from ARM926 for encoding of the 
*        frame and executes the call for encoding of the frame. On completion
*        of encoding, it signals back to ARM926 regarding completion of
*        encoding.
*
* =============================================================================
*
* Copyright (c) Texas Instruments Inc 2005, 2006
*
* Use of this software is controlled by the terms and conditions found
* in the license agreement under which this software has been supplied
*
* =============================================================================
*/
/*---------------------------------------------------------------------------*/
/*                        COMPILATION CONTROL SWITCHES                       */
/*---------------------------------------------------------------------------*/
#if defined(FRAME_PROFILE) || \
    defined(MB_TTL_PROFILE) || defined(MB_LOOP_PROFILE)
#define _PROFILE
#endif

/* ------------------------------------ PRAGMAS ---------------------------- */
#pragma DATA_SECTION(DtcmMem, ".DTCM_MEM");
#ifdef _PROFILE
#pragma DATA_SECTION(Prof_Array, ".PROF_ARR");
#endif //_PROFILE

/*---------------------------------------------------------------------------*/
/*                                  INCLUDE FILES                            */
/*---------------------------------------------------------------------------*/
/* ----------------------- SYSTEM AND PLATFORM FILES ----------------------- */
/* ------------------------------ PROGRAM FILES ---------------------------- */
#include "kld_ti_datatypedefs.h"
#include "hdvicp_ti_coprocessor_globals.h"
#include "hdvicp_ti_coprocessor_typedef.h"
#include "hdvicp_ti_coprocessor_common.h"
#include "h264venc_state.h"

#include "kld_ti_arm968intc.h"
#include "cslr_kldintc.h"
#ifdef ENABLE_DM510
#include "cslr_kaleido.h"
#endif
#ifdef _PROFILE
#include <stdio.h>
#include "timerapi.h"
#endif //_PROFILE

#ifdef H264ENC_EDMA
#include "csl_edma.h"
#include "h264v_ti_edma_dm510.h"
#endif //H264ENC_EDMA

/*---------------------------------------------------------------------------*/
/*      EXTERNAL REFERENCES NOTE : only use if not found in header file      */
/*---------------------------------------------------------------------------*/
/* ---------------------------- DATA DECLARATIONS -------------------------- */
/* --------------------------- FUNCTION PROTOTYPES ------------------------- */
#ifdef _PROFILE
extern void profileInit(int i);
extern void profileStart(int i);
extern Uint64 profileCount(int i);
extern Uint64 profileEnd(int i);
#endif //_PROFILE

extern H264VENC_TI_Enc_ARM968 (tH264EncState_968 *pH264Enc_ARM968);

/*---------------------------------------------------------------------------*/
/*               PUBLIC DECLARATIONS Defined here, used elsewhere            */
/*---------------------------------------------------------------------------*/
/* ---------------------------- DATA DECLARATIONS -------------------------- */
#ifdef LITE_ENCODER
#define DTCM_SZ     (DTCM_SHARE_SZ + DTCM_DATA_SZ_LITE)
#else
#define DTCM_SZ     (DTCM_SHARE_SZ + DTCM_DATA_SZ)
#endif
U8      DtcmMem[DTCM_SZ];

#ifdef _PROFILE
U32     Prof_Array[MAX_PROF_WORD];
pU32    profPtr;
U32     prfCnt = 0;
U32     ttlFrmCycles = 0;
pU32    pProfDDR;
S32     timer = 0;
#endif //_PROFILE
/* --------------------------- FUNCTION PROTOTYPES ------------------------- */

/*---------------------------------------------------------------------------*/
/*               PRIVATE DECLARATIONS Defined here, used here only           */
/*---------------------------------------------------------------------------*/
/* ---------------------------- DATA DECLARATIONS -------------------------- */
volatile pU32 poll_word = (pU32)0x00400000;

volatile pU32 arm968firstTimeflag = (pU32)(0x00400000 + 0xD0);
/* --------------------------- FUNCTION PROTOTYPES ------------------------- */
/* --------------------------- MACROS -------------------------------------- */


/* ============================================================================
 *  @func     main
 *      
 *  @desc     <>
 *
 *  @modif    This function does not modify any variable/structure
 *
 *  @inputs   This function takes no inputs
 *
 *  @outputs  <argument name> 
 *            Description of usage
 *
 *  @return   Return value of this function if any
 *  ===========================================================================
 */

void main()
{
    pU8     pDataMemDTCM;
    tH264EncState_968   *pH264Enc_ARM968;
#ifdef LOW_LATENCY_FEATURE
    volatile pU8 hdvicp_sync_wait = (pU8)SHARED_MSG_ARM968_HDVICPSYNC_WAIT;
#endif //LOW_LATENCY_FEATURE

#ifdef _PROFILE
    profPtr = (pU32)(Prof_Array);
#endif //_PROFILE

#ifdef DM510_POWER_OPT
    /* Disable(Enable CG) all CoProc Buffers */
    HDVICP_TI_BUF_CG_EBL();
    /* Disable(Enable CG) all CoProc IPs */
    HDVICP_TI_ALL_COPROC_CG_EBL();
#endif //DM510_POWER_OPT

    //Continous Encoding Loop - Needs a way to get out of loop
    while(1)
    {
        pDataMemDTCM = (pU8)(DtcmMem + DTCM_DATA);

#ifdef DM365_IPC_WFI_ENABLE
        asm(" SWI #1 ");// Going into Supervisor mode to enter WFI mode
#else //DM365_IPC_WFI_ENABLE
        /*-------------------------------------------------------------------*/
        /* Polling to ARM 926                                                */
        /*-------------------------------------------------------------------*/
        while(((*poll_word) & 0x01) == 0);  //bit 0 for ARM968 to start
        *poll_word = 0;
#endif //DM365_IPC_WFI_ENABLE

#ifdef DM510_POWER_OPT
        /* Enable(Disable CG) all CoProc Buffers */
        HDVICP_TI_BUF_CG_DBL();
#endif //DM510_POWER_OPT

        /*-------------------------------------------------------------------*/
        /* Check if HOST ARM926 has asked to terminate operation             */
        /*-------------------------------------------------------------------*/
        if((*poll_word) == 0xFFFFFFFF)
            break;  //ARM926 signals - No more frames to decode

        (*poll_word) &= 0xFFFFFFFE ;   // Set the wait bit to 0 again

#ifdef _PROFILE
        profileInit(timer); 
        profileStart(timer);
        pProfDDR = (pU32)profPtr[0] + 1;
#endif //_PROFILE

#ifdef DEBUG_H264
        {
            volatile pU32 ptr_watch_var = (pU32)(DTCM_WATCH_VARIABLE);
            *ptr_watch_var = 0xABCD0000;
            //while(*ptr_watch_var != 0x10);
        }
#endif

#ifdef LITE_ENCODER
        //Set Encoder Structure Pointer
        pH264Enc_ARM968 = (tH264EncState_968 *)(pDataMemDTCM + ENCSTATE_OFST_LITE);

        //Set Pointers of member structures
        //Internal Scratch Memory
        pH264Enc_ARM968->pubIntMemScratch =
            (pU8)(pDataMemDTCM + INTMEM_SCR_OFST);
        pH264Enc_ARM968->uiIntMemScratchSize = INTMEM_SCR_SZ_LITE;
        //Internal Persistent Memory
        //pH264Enc_ARM968->pubIntMemPersist =
        //  (pU8)(pDataMemDTCM + INTMEM_PST_OFST);
        //pH264Enc_ARM968->uiIntMemPersistSize = INTMEM_PST_SZ;
        //Bitstream Offset
        pH264Enc_ARM968->bitstream =
            (tBitStream *)(pDataMemDTCM + BITSTREAM_OFST_LITE);
        //SPS Strcuture
        pH264Enc_ARM968->psSeqParamSet = ((sSPS_t *)(pDataMemDTCM + SPS_OFST_LITE));
        //PPS Strcuture
        pH264Enc_ARM968->psPicParamSet = ((sPPS_t *)(pDataMemDTCM + PPS_OFST_LITE));
        //Slice Param Structure
        pH264Enc_ARM968->psSlcParam =
            (sSlcParm_t *)(pDataMemDTCM + SLCPARAM_OFST_LITE);
        /* Slice Size Array */
        pH264Enc_ARM968->SlcSizInBytes = (pS32)(pDataMemDTCM + SLCSIZARR_OFST_LITE);

        pH264Enc_ARM968->puPaddingBuffer = 
               (pU8)(pDataMemDTCM + PADDING_BUF_OFST_LITE);
#else
        //Set Encoder Structure Pointer
        pH264Enc_ARM968 = (tH264EncState_968 *)(pDataMemDTCM + ENCSTATE_OFST);

        //Set Pointers of member structures
        //Internal Scratch Memory
        pH264Enc_ARM968->pubIntMemScratch =
            (pU8)(pDataMemDTCM + INTMEM_SCR_OFST);
        pH264Enc_ARM968->uiIntMemScratchSize = INTMEM_SCR_SZ;
        //Internal Persistent Memory
        //pH264Enc_ARM968->pubIntMemPersist =
        //  (pU8)(pDataMemDTCM + INTMEM_PST_OFST);
        //pH264Enc_ARM968->uiIntMemPersistSize = INTMEM_PST_SZ;
        //Bitstream Offset
        pH264Enc_ARM968->bitstream =
            (tBitStream *)(pDataMemDTCM + BITSTREAM_OFST);
        //SPS Strcuture
        pH264Enc_ARM968->psSeqParamSet = ((sSPS_t *)(pDataMemDTCM + SPS_OFST));
        //PPS Strcuture
        pH264Enc_ARM968->psPicParamSet = ((sPPS_t *)(pDataMemDTCM + PPS_OFST));
        //Slice Param Structure
        pH264Enc_ARM968->psSlcParam =
            (sSlcParm_t *)(pDataMemDTCM + SLCPARAM_OFST);
        /* Slice Size Array */
        pH264Enc_ARM968->SlcSizInBytes = (pS32)(pDataMemDTCM + SLCSIZARR_OFST);

//        pH264Enc_ARM968->puPaddingBuffer = 
//               (pU8)(pDataMemDTCM + PADDING_BUF_OFST);
#endif
/*Removed from state for memory optimization */
/*
        pH264Enc_ARM968->dma_state_struct.trf_pend_edma =
            pH264Enc_ARM968->transfer_pending_edma;
        pH264Enc_ARM968->dma_state_struct.trf_pend_qdma =
            pH264Enc_ARM968->transfer_pending_qdma;
*/
#ifdef LOW_LATENCY_FEATURE
        /* Initialize hdvicp_sync_wait message to 0 */
        *hdvicp_sync_wait = 0;
#endif //LOW_LATENCY_FEATURE

        //Encoding of Slice
        H264VENC_TI_Enc_ARM968 (pH264Enc_ARM968);

        *arm968firstTimeflag = pH264Enc_ARM968->EncQuality<<8 |
                               pH264Enc_ARM968->tCurrFrameType;
#ifdef DM510_POWER_OPT
        /* Disable(Enable CG) all CoProc Buffers */
        HDVICP_TI_BUF_CG_EBL();
#endif //DM510_POWER_OPT

#ifdef _PROFILE
        ttlFrmCycles = profileEnd(timer);
#endif //_PROFILE

#ifdef FRAME_PROFILE
        profPtr[0] = ttlFrmCycles;
#endif //FRAME_PROFILE

#ifdef MB_LOOP_PROFILE
        profPtr[0] = prfCnt;
#endif //MB_LOOP_PROFILE

#ifdef MB_TTL_PROFILE
        //profPtr[0] = 1;
#endif //prfCnt

#ifdef LOW_LATENCY_FEATURE
        /* Wait for last slice callback to return before sending end of */
        /* intterupt frame                                              */
        H264VENC_TI_Enc_getBitstreamSpace(pH264Enc_ARM968);
        pH264Enc_ARM968->dataSyncDesc.numBlocks = pH264Enc_ARM968->numBlocks;
        *hdvicp_sync_wait = END_OF_FRAME;
#endif //LOW_LATENCY_FEATURE
        /* -------------------------------------------------------*/
        /* Send interrupt to ARM926: Set the poll bit             */
        /* -------------------------------------------------------*/
#ifdef DM365_IPC_INTC_ENABLE
        /* Send interrupt to arm926 FIQ by writing sw_int_out1 bit KLD INTC*/
        SW_INT_OUT1();
#else //DM365_IPC_INTC_ENABLE
        (*poll_word) |= 0x02;   //bit 1 for ARM926 to start
#endif //DM365_IPC_INTC_ENABLE
    }
}

/*!
*! Revision History
*! ****************
*! 25-11-2009 Manisha Agrawal: Added support for low latency interface
*! 16-05-2007 Sunil Koteyar : Changes related to Coding Guidelines
*! 22-01-2007 Sunil Koteyar : Created.
*/
