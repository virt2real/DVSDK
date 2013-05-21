/* ========================================================================== */
/*                                                                            */
/*  TEXAS INSTRUMENTS, INC.                                                   */
/*                                                                            */
/*  NAME                                                                      */
/*     alg_control.c                                                          */
/*                                                                            */
/*  DESCRIPTION                                                               */
/*   ALG_control implementation.  This is common to all implementations       */
/*   of the ALG module.                                                       */
/*                                                                            */
/*  COPYRIGHT NOTICES                                                         */
/*   Copyright (C) 1996, MPEG Software Simulation Group. All Rights           */
/*   Reserved.                                                                */
/*                                                                            */
/*   Copyright (c) 2001-2003 Texas Instruments Inc.  All rights reserved.     */
/*   Exclusive property of the Video & Imaging Products, Emerging End         */
/*   Equipment group of Texas Instruments India Limited. Any handling,        */
/*   use, disclosure, reproduction, duplication, transmission, or storage     */
/*   of any part of this work by any means is subject to restrictions and     */
/*   prior written permission set forth in TI's program license agreements    */
/*   and associated software documentation.                                   */
/*                                                                            */
/*   This copyright notice, restricted rights legend, or other proprietary    */
/*   markings must be reproduced without modification in any authorized       */
/*   copies of any part of this work.  Removal or modification of any part    */
/*   of this notice is prohibited.                                            */
/*                                                                            */
/*   U.S. Patent Nos. 5,283,900  5,392,448                                    */
/* -------------------------------------------------------------------------- */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.             */
/*                           All Rights Reserved.                             */
/* ========================================================================== */
/* "@(#) XDAS 2.12 05-21-01 (__imports)" */

#include <alg.h>

/*
 *  ======== ALG_control ========
 */
Int ALG_control(ALG_Handle alg, IALG_Cmd cmd, IALG_Status * statusPtr)
{
    if (alg && alg->fxns->algControl) {
        return (alg->fxns->algControl(alg, cmd, statusPtr));
    }

    return (IALG_EFAIL);
}

/* ========================================================================== */
/* End of file : alg_control.c                                                */
/* -------------------------------------------------------------------------- */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.             */
/*                           All Rights Reserved.                             */
/* ========================================================================== */
