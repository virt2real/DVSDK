/* --COPYRIGHT--,BSD
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
 * --/COPYRIGHT--*/

/**
 * @defgroup   ti_sdo_dmai_Ir       Ir
 *
 * @brief Allows reception of Ir commands. Typical example (no error checking):
 *
 * @code
 *   #include <xdc/std.h>
 *   #include <ti/sdo/dmai/Dmai.h>
 *   #include <ti/sdo/dmai/Ir.h>
 *   Ir_Handle hIr;
 *   Ir_Attrs irAttrs = Ir_Attrs_DEFAULT;
 *   Ir_Key key;
 * 
 *   Dmai_init();
 *   hIr = Ir_create(&irAttrs);
 *   Ir_getKey(hIr, &key);
 *   // The received key is now available in the key variable.
 * @endcode
 */

#ifndef ti_sdo_dmai_Ir_h_
#define ti_sdo_dmai_Ir_h_

#include <xdc/std.h>

#include <ti/sdo/dmai/Dmai.h>

/** @ingroup    ti_sdo_dmai_Ir */
/*@{*/

/**
 * @brief The different keys supported on the Ir remote.
 */
typedef enum {
    Ir_Key_POWER           = 0x300c,
    Ir_Key_CHANINC         = 0x3020,
    Ir_Key_CHANDEC         = 0x3021,
    Ir_Key_VOLINC          = 0x3010,
    Ir_Key_VOLDEC          = 0x3011,
    Ir_Key_UP              = 0x301c,
    Ir_Key_DOWN            = 0x301d,
    Ir_Key_LEFT            = 0x302c,
    Ir_Key_RIGHT           = 0x302b,
    Ir_Key_OK              = 0x302e,
    Ir_Key_MUTE            = 0x300d,
    Ir_Key_MENUDONE        = 0x300f,
    Ir_Key_INFOSELECT      = 0x300f,
    Ir_Key_SLEEP           = 0x3026,
    Ir_Key_SUBTITLE        = 0x30cb,
    Ir_Key_REPEAT          = 0x3022,
    Ir_Key_1               = 0x3001,
    Ir_Key_2               = 0x3002,
    Ir_Key_3               = 0x3003,
    Ir_Key_4               = 0x3004,
    Ir_Key_5               = 0x3005,
    Ir_Key_6               = 0x3006,
    Ir_Key_7               = 0x3007,
    Ir_Key_8               = 0x3008,
    Ir_Key_9               = 0x3009,
    Ir_Key_0               = 0x3000,
    Ir_Key_ENTER           = 0x2039,
    Ir_Key_INPUT           = 0x20ff,
    Ir_Key_REWIND          = 0x3172,
    Ir_Key_PLAY            = 0x3175,
    Ir_Key_FASTFORWARD     = 0x3174,
    Ir_Key_RECORD          = 0x3177,
    Ir_Key_STOP            = 0x3176,
    Ir_Key_PAUSE           = 0x3169,
} Ir_Key;

/**
 * @brief Handle through which to reference an Ir Object.
 */
typedef struct Ir_Object *Ir_Handle;

/**
 * @brief       Attributes used to create an Ir object.
 * @see         Ir_Attrs_DEFAULT.
 */
typedef struct Ir_Attrs {
    /** @brief Currently no attributes for this module, but this may change. */
    Int dummy;
} Ir_Attrs;

/**
 * @brief       Default attributes for an Ir object.
 */
extern const Ir_Attrs Ir_Attrs_DEFAULT;

#if defined (__cplusplus)
extern "C" {
#endif

/**
 * @brief       Creates an Ir object.
 *
 * @retval      Handle for use in subsequent operations (see #Ir_Handle).
 * @retval      NULL for failure.
 */
extern Ir_Handle Ir_create(Ir_Attrs *attrs);

/**
 * @brief       Get a key from the Ir.
 *
 * @param[in]   hIr         The #Ir_Handle from which to receive a keycode.
 * @param[out]  key         Pointer to a received #Ir_Key.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Ir_create must be called before this function.
 */
extern Int Ir_getKey(Ir_Handle hIr, Ir_Key *key);

/**
 * @brief       Deletes an Ir Object.
 *
 * @param[in]   hIr         The #Ir_Handle to delete.
 *
 * @retval      Dmai_EOK for success.
 * @retval      "Negative value" for failure, see Dmai.h.
 *
 * @remarks     #Ir_create must be called before this function.
 */
extern Int Ir_delete(Ir_Handle hIr);

#if defined (__cplusplus)
}
#endif

/*@}*/

#endif /* ti_sdo_dmai_Ir_h_ */
