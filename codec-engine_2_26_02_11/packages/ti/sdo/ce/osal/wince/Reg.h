/* 
 * Copyright (c) 2010, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
/*
 *  ======== Reg.h ========
 */
/**
 *  @file       ti/sdo/ce/osal/wince/Reg.h
 *
 *  @brief      The Codec Engine OSAL wince Reg interface.  Provides the user
 *              a Reg abstraction.
 */
/**
 *  @defgroup   ti_sdo_ce_osal_wince_Reg     Codec Engine OSAL wince - Reg
 */

#ifndef ti_sdo_ce_osal_wince_Reg_
#define ti_sdo_ce_osal_wince_Reg_

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup    ti_sdo_ce_osal_wince_Reg */
/*@{*/

/**
 *  @brief      Trace name for the Reg module
 */
#define Reg_GTNAME "ti.sdo.ce.osal.Reg"

#define Reg_NONVOLATILE 0x0
#define Reg_VOLATILE 0x1

#define Reg_MAXREGPATHLENGTH 255

/*
 *  ======== Reg_getValue ========
 *  Retrieve a value from the registry.
 *
 *  Parameters:
 *      phKey       Currently not used. Must be set to NULL.
 *      subkey      Name of the subkey under HKEY_LOCAL_MACHINE.
 *                  (eg, "SOFTWARE\\Texas Instruments\\ti.sdo.ce.osal")
 *      value       The name of the value to get (eg, "CE_DEBUG").
 *      pbData      Pointer to buffer where the data for the specified
 *                  value name will be copied.
 *      pDataSize   Pointer to the size of the pbData buffer. Will be set
 *                  to the number of bytes actually copied into the pbData.
 */
extern Bool Reg_getValue(HKEY *phKey, String subkey, String value,
        UInt8 *pbData, Int *pDataSize);

/*
 *  ======== Reg_init ========
 */
extern Void Reg_init(Void);

/*
 *  ======== Reg_setValue ========
 *  Set the data for a specified value in the registry. Create the subkey
 *  for the value name, if it does not yet exist.
 *
 *  Parameters:
 *      phKey       Currently not used. Must be set to NULL.
 *      subkey      Name of the subkey under HKEY_LOCAL_MACHINE.
 *                  (eg, "SOFTWARE\\Texas Instruments\\ti.sdo.ce.osal")
 *      value       The name of the value to set (eg, "CE_DEBUG").
 *      type        Type of data pointed to by pData. These are the same as
 *                  the values passed to RegSetValueEx, eg, REG_DWORD,
 *                  REG_SZ.
 *      pData       Pointer to buffer containing the data to be stored with
 *                  the specified value name.
 *      dataSize    Number of bytes to be stored.
 *      flags       Set to Reg_VOLATILE or Reg_NONVOLATILE.
 *                  If the subkey has not been created, this is used to
 *                  create the subkey as either volatile or non-volatile.
 *                  If flags = Reg_NONVOLATILE, the information will be
 *                  preserved when the system is restarted.
 */
extern Bool Reg_setValue(HKEY *phKey, String subkey, String value, UInt32 type,
        UInt8 *pData, UInt32 dataSize, UInt32 flags);

/*@}*/  /* ingroup */

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.osal.wince; 1, 0, 0,82; 12-2-2010 21:25:05; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

