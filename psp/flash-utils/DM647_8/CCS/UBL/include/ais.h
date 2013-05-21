/* --------------------------------------------------------------------------
    FILE        : ais.h
    PURPOSE     : AIS routine header file
    PROJECT     : DM648 User Boot Loader
    AUTHOR      : Daniel Allred
    DESC	    : Header file for the AIS routines used to parse the AIS 
    			  application image on the DM648 EVM from Lyrtech.  
 ----------------------------------------------------------------------------- */

#ifndef _AIS_H_
#define _AIS_H_

#include "tistdtypes.h"

// Prevent C++ name mangling
#ifdef __cplusplus
extern far "c" {
#endif

/***********************************************************
* Global Macro Declarations                                *
***********************************************************/

#define AIS_MAGIC_NUMBER	                      (0x41504954)

#define AIS_PROTOCOL_COMMAND_PREFIX_MASK        (0xFFFFFF00u)
#define AIS_PROTOCOL_COMMAND_PREFIX             (0x58535900u)

#define AIS_PROTOCOL_XMT_START                  (0)
#define AIS_PROTOCOL_SECTION_LOAD               (1)
#define AIS_PROTOCOL_REQUEST_CRC                (2)
#define AIS_PROTOCOL_ENABLE_CRC                 (3)
#define AIS_PROTOCOL_DISABLE_CRC                (4)
#define AIS_PROTOCOL_JUMP                       (5)
#define AIS_PROTOCOL_JUMP_CLOSE                 (6)
#define AIS_PROTOCOL_SET                        (7)
#define AIS_PROTOCOL_STARTOVER                  (8)
#define AIS_PROTOCOL_COMPSECTION_LOAD           (9) 
#define AIS_PROTOCOL_SECTION_FILL               (10)
#define AIS_PROTOCOL_PING_DEVICE                (11)
#define AIS_PROTOCOL_GET                        (12)
#define AIS_PROTOCOL_FUNCTION_EXECUTE           (13)
#define AIS_PROTOCOL_ENABLE_ICACHE              (14)
#define AIS_PROTOCOL_DISABLE_ICACHE             (15)
#define AIS_PROTOCOL_ENABLE_DMA                 (16)
#define AIS_PROTOCOL_DISABLE_DMA                (17)
#define AIS_PROTOCOL_REENTER_BOOT               (18)
#define AIS_PROTOCOL_FASTOOT                    (19)

#define AIS_DATA_LOAD                           (1)


#define BOOT_TABLE_TYPE_Byte                    (1)
#define BOOT_TABLE_TYPE_Short                   (2)
#define BOOT_TABLE_TYPE_Int                     (3)
#define BOOT_TABLE_TYPE_Field                   (4)
#define BOOT_TABLE_TYPE_Bits                    (5)

#define AIS_PROTOCOL_MAX_OPCODES                (0xFE)
#define AIS_MAX_CYCLES_TO_WAIT_FOR_HOST         (0x10000u)
#define AIS_BOOT_COMPLETE                       (0xFF)
#define AIS_PROTOCOL_MAX_NUM_CRC_ERRORS         (2)

#define TARGET_LITTLE_ENDIAN                    (1u)
#define TARGET_BIG_ENDIAN                       (0u)


/***********************************************************
* Global Typedef declarations                              *
***********************************************************/

typedef void (*AIS_fxnPtr)(void);


/***********************************************************
* Global Function Declarations                             *
***********************************************************/

void *AIS_parseImage(void *baseAddr);


/***********************************************************
* End file                                                 *
***********************************************************/

#ifdef __cplusplus
}
#endif

#endif //_AIS_H

/* -------------------------------------------------------------------------- 
  HISTORY
 		v1.00  -  DJA  -  15-Nov-2007
			Initial Release 	   
 ----------------------------------------------------------------------------- */









