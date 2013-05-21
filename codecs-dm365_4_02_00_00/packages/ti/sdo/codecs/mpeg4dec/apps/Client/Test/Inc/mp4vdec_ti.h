/*
//============================================================================
//    FILE NAME : mp4vdec_ti.h
//    ALGORITHM : MP4VDEC
//    VENDOR    : TI
//    TARGET PROC: DM350
//    PURPOSE   : This is the top level driver file that exercises the MPEG4
//               Decoder code
//============================================================================
*/
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2006 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

#ifndef MP4VDEC_TI_
#define MP4VDEC_TI_

#include <imp4vdec.h>
/*
 *  ======== MP4VDEC_TI_IALG ========
 *  TI's implementation of the IALG interface for MP4VDEC
 */
extern IALG_Fxns MP4VDEC_TI_IALG;
extern IDMA3_Fxns MP4VDEC_TI_IDMA3;
/*
 *  ======== MP4VDEC_TI_IMP4VDEC ========
 *  TI's implementation of the IMP4VDEC interface
 */
extern IMP4VDEC_Fxns MP4VDEC_TI_IMP4VDEC;
//extern IVIDDEC1_Fxns MP4VDEC_TI_IMP4VDEC;
extern void MPEG4DEC_TI_init(void);

extern void MPEG4DEC_TI_exit(void);

extern void MP4VDEC_TI_activate(IALG_Handle);

extern XDAS_Int32 MP4VDEC_TI_alloc(const IALG_Params *,
                              struct IALG_Fxns **,
                              IALG_MemRec *);

extern XDAS_Int32 MP4VDEC_TI_control(IMP4VDEC_Handle handle, IVIDDEC2_Cmd cmd,
                    IVIDDEC2_DynamicParams *params, IMP4VDEC_Status *status);

extern void MP4VDEC_TI_deactivate(IALG_Handle);

extern XDAS_Int32 MP4VDEC_TI_free(IALG_Handle, IALG_MemRec *);

extern XDAS_Int32 MP4VDEC_TI_initObj(IALG_Handle,
                                const IALG_MemRec *,
                                IALG_Handle,
                                const IALG_Params *);

extern void MP4VDEC_TI_moved(IALG_Handle,
                               const IALG_MemRec *,
                               IALG_Handle,
                               const IALG_Params *);

extern XDAS_UInt32 MP4VDEC_TI_numAlloc(Void);

extern XDAS_Int32 MP4VDEC_TI_decode(IMP4VDEC_Handle handle, XDM1_BufDesc *InBufs,
            XDM_BufDesc *OutBufs, IMP4VDEC_InArgs *Inargs,
            IMP4VDEC_OutArgs *Outargs);

#endif	/* MP4VDEC_TI_ */

/* ======================================================================== */
/* End of file : mp4vdec_ti.h                                             */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2006 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

