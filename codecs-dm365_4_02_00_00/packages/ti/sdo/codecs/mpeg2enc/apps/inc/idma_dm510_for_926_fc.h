/** ===========================================================================
* @file idma_dm510.h
*
* @path $(PROJDIR)\src
*
* @brief This File contains macros and structure declarations required for DMA
*		initializations. This is a interface file providing user control
*		of DMa operations
* =============================================================================
* Copyright (c) Texas Instruments Inc 2006, 2007
*
* Use of this software is controlled by the terms and conditions found
* in the license agreement under which this software has been supplied
**============================================================================*/
/* ------compilation control switches -------------------------*/
#ifndef IDMA_DM510_H
#define IDMA_DM510_H
/***************************************************************
*  INCLUDE FILES
****************************************************************/
/* ----- system and platform files ----------------------------*/
#include <ti/xdais/xdas.h>
/*-------program files ----------------------------------------*/
/****************************************************************
*  PUBLIC DECLARATIONS Defined here, used elsewhere
****************************************************************/
/*--------data declarations -----------------------------------*/
/*--------function prototypes ---------------------------------*/
/****************************************************************
*  PRIVATE DECLARATIONS Defined here, used only here
****************************************************************/
/*--------data declarations -----------------------------------*/
/*--------function prototypes ---------------------------------*/
/*--------macros ----------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*  The below #defines are set by the client. Note the Number of logical      */
/* channels should not be set more than Max number of Channels set inside the */
/* decoder library.figures for Max numchannels that are set in decoder lib    */
/* is given below                                                             */
/*    MAX_EDMA_LGL_CHANNELS       18                                          */
/*    MAX_QDMA_LGL_CHANNELS       8                                           */
/*    MAX_TOTAL_EDMA_CHANNELS     64                                          */
/*    MAX_TOTAL_QDMA_CHANNELS     8                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*  Number of EDMA Logical channels                                           */
/*----------------------------------------------------------------------------*/
#define NUM_EDMA_LGL_CHANNELS    26

/*----------------------------------------------------------------------------*/
/*  Number of QDMA Logical channels                                           */
/* If no QDMA channels are used this can be set to Zero.                      */
/*----------------------------------------------------------------------------*/
#define NUM_QDMA_LGL_CHANNELS    8

/*----------------------------------------------------------------------------*/
/*  Total number of param sets allowed                                        */
/*----------------------------------------------------------------------------*/
#define MAX_PRM_SETS_ALLOWED     74

/*----------------------------------------------------------------------------*/
/*  Total Number Logical channels used.                                       */
/*----------------------------------------------------------------------------*/
#define NUM_CHANNELS            (NUM_EDMA_LGL_CHANNELS+NUM_QDMA_LGL_CHANNELS)

/*----------------------------------------------------------------------------*/
/*  Total Number EDMA channels available                                      */
/*----------------------------------------------------------------------------*/
#define TOTAL_EDMA_CHANNELS    64

/*----------------------------------------------------------------------------*/
/*  Total Number of QDMA channels available.                                  */
/*----------------------------------------------------------------------------*/
#define TOTAL_QDMA_CHANNELS     8


/*----------------------------------------------------------------------------*/
/* Number of channels required for the algorithm                              */
/*----------------------------------------------------------------------------*/
#define NUM_LOGICAL_CH 4

/*----------------------------------------------------------------------------*/
/*  Client needs to set this to zero if he needs to program QUE TC MAP,QUE Pri*/
/*----------------------------------------------------------------------------*/
#define SETQUE_ATTR 1


/*----------------------------------------------------------------------------*/
/* Here the Client can set the approriate value of QUETCMAP                   */
/* Currently it is set to defualt value that is being used by the software    */
/*----------------------------------------------------------------------------*/

#define CCCFG_NUM_TC_1        (0x00000000u)
#define CCCFG_NUM_TC_2        (0x00000001u)
#define QUETCMAP_TCNUMQ0_SHIFT (0x00000000u)
#define QUETCMAP_TCNUMQ1_SHIFT (0x00000004u)

#define _QUETCMAP \
        ((CCCFG_NUM_TC_1 << QUETCMAP_TCNUMQ0_SHIFT) | \
        (CCCFG_NUM_TC_2 << QUETCMAP_TCNUMQ1_SHIFT))

/*----------------------------------------------------------------------------*/
/* Here the Client can set the approriate value of QUETCMAP                   */
/* Currently it is set to defualt value that is being used by the software    */
/*----------------------------------------------------------------------------*/
#define _QUE_PRI0                 0
#define _QUE_PRI1                 1

#define QUEPRI_PRIQ0_SHIFT    (0x00000000u)
#define QUEPRI_PRIQ1_SHIFT    (0x00000004u)

#define _QUEPRI \
        ((_QUE_PRI0 << QUEPRI_PRIQ0_SHIFT) | \
        (_QUE_PRI1 << QUEPRI_PRIQ1_SHIFT))


/***************************************************************
*  EXTERNAL REFERENCES NOTE : only use if not found in header file
****************************************************************/
/*--------data declarations -----------------------------------*/
/*----------------------------------------------------------------------------*/
/* This array is used to map logical channels to physical dma channels        */
/* In actual case this will be proviced by DMAN3                              */
/*----------------------------------------------------------------------------*/

extern XDAS_UInt32 edma_phy_to_lgl_map[64];
extern XDAS_UInt32 qdma_phy_to_lgl_map[8];
extern XDAS_UInt32 mpeg2venc_edma_tcc_array[NUM_EDMA_LGL_CHANNELS];
extern XDAS_UInt32 qdma_tcc_array[NUM_QDMA_LGL_CHANNELS];
extern XDAS_UInt16         transfer_pending_edma[64];
extern XDAS_UInt16         transfer_pending_qdma[8];

/*----------------------------------------------------------------------------*/
/*  Structure to store all the attributes required for client to init DMA     */
/*----------------------------------------------------------------------------*/
typedef struct IDMA_DM510_Params
{
    XDAS_UInt32             Num_Edma_Channels;
    XDAS_UInt32             Num_Qdma_Channels;
    XDAS_UInt32             Total_Edma_Channels;
    XDAS_UInt32             Total_Qdma_Channels;
    volatile XDAS_UInt16    *Transfer_Pending_Edma;
    volatile XDAS_UInt16   	*Transfer_Pending_Qdma;
    volatile XDAS_UInt32    *Edma_Params_Array[NUM_EDMA_LGL_CHANNELS];
    volatile XDAS_UInt32    *Qdma_Params_Array[NUM_QDMA_LGL_CHANNELS];
    volatile XDAS_UInt32    *Edma_Tcc_Array;
    volatile XDAS_UInt32    *Qdma_Tcc_Array;
    volatile XDAS_UInt32    *Edma_Phy_to_Lgl_Map;
    volatile XDAS_UInt32    *Qdma_Phy_to_Lgl_Map;
    volatile XDAS_UInt32     Setque_Attr;
    volatile XDAS_UInt32     Quetcmap;
    volatile XDAS_UInt32     Quepri;

} IDMA_DM510_Params;

/*--------function prototypes ---------------------------------*/

/* =============================================================================
 *  @func     TestApp_SetDMAInitParams
 *
 *  @desc     DMA Open routine
 *
 *  @param    IDMA_DM510_Params *DMAparams
 *            Pointer to DMA parameters structure.
 *
 *  @return   S32
 *            -ve value indicates error
 *  ============================================================================
 */
extern XDAS_Int32 TestApp_SetDMAInitParams (IDMA_DM510_Params *DMAparams);

#endif /* IDMA_DM510_H */
/*!
*! Revision History
*! ================
*! 15-May-2007 Vinay M K: Created initial version.
*/

