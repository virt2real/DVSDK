/* --------------------------------------------------------------------------
    FILE        : spi24.h
    PURPOSE     : SPI24 header file
    PROJECT     : DaVinci User Boot-Loader and Flasher
    AUTHOR      : Texas Instruments Incorporated
    DATE	    : May-15-2007

    HISTORY
        v1.00 completion
 	        - May-15-2007
 	        
    Copyright 2007 Texas Instruments Incorporated. 	          
 	        
 ----------------------------------------------------------------------------- */
#ifndef _SPI24_H_
#define _SPI24_H_

#include <tistdtypes.h>
  typedef struct {
       VUint32 fileSize;
  } SPI24_INFO, *PSPI24_INFO;

// ---------------- Prototypes of functions for SPI24 Eeprom Write --------------------
  
Uint32 SPI24_Init(void);
Uint32 SPI24_WriteHeaderAndData(Uint8 *ramPtr);
Uint32 SPI24_ReadByte(Uint32 eeprom_addr);
Uint32 SPI24_WriteByte(Uint32 eeprom_addr, Uint8 *byte);
Uint32 SPI24_bulkErase(void);


#define SPI_READ_COMMAND            0x03000000u // Read data from EEPROM
#define SPI_PROG_COMMAND            0x02000000u // Program data to EEPROM
#define SPI_WREN_COMMAND            0x06000000u // Set EEPROM Write Enable
#define SPI_WSR_COMMAND             0x01000000u // Write to EEPROM status register
#define SPI_RSR_COMMAND             0x05000000u // Read EEPROM status register
#define SPI_BE_COMMAND              0xC7000000u // Bulk Erase Command	  
#endif
