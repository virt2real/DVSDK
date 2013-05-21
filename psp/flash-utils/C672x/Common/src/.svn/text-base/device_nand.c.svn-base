/* --------------------------------------------------------------------------
    FILE        : device_nand.c 				                             	 	        
    PROJECT     : C672x Flashing Utils
    AUTHOR      : Daniel Allred
    DESC        : This file implements the NAND_ECC interface defined in the
                  common nand_ecc.h file
-------------------------------------------------------------------------- */ 

// General type include
#include "tistdtypes.h"

// Device specific CSL
#include "device.h"

// Device specific NAND details
#include "device_nand.h"

// Generic NAND header file
#include "nand.h"


/************************************************************
* Explicit External Declarations                            *
************************************************************/


/************************************************************
* Local Macro Declarations                                  *
************************************************************/


/************************************************************
* Local Function Declarations                               *
************************************************************/

// Required implementation for NAND_ECC structure
static void DEVICE_NAND_ECC_calculate(NAND_InfoHandle hNandInfo, Uint8 *data, Uint8 *calcECC);
static void DEVICE_NAND_ECC_store(NAND_InfoHandle hNandInfo, Uint8 *spareBytes, Uint8 opNum, Uint8 *calcECC);
static void DEVICE_NAND_ECC_enable(NAND_InfoHandle hNandInfo);
static void DEVICE_NAND_ECC_disable(NAND_InfoHandle hNandInfo);
static void DEVICE_NAND_ECC_read(NAND_InfoHandle hNandInfo, Uint8 *spareBytes, Uint8 opNum, Uint8 *readECC);
static Uint32 DEVICE_NAND_ECC_correct(NAND_InfoHandle hNandInfo, Uint8 *data, Uint8 *readECC);

// Required implementation for NAND_BB_Info struct
static void DEVICE_NAND_BB_markSpareBytes(NAND_InfoHandle hNandInfo, Uint8 *spareBytes);
static Uint32 DEVICE_NAND_BB_checkSpareBytes(NAND_InfoHandle hNandInfo, Uint8 *spareBytes);


/************************************************************
* Local Variable Definitions                                *
************************************************************/


/************************************************************
* Global Variable Definitions                               *
************************************************************/

// Specfic ECC info to support ROM of device
const NAND_ECC_InfoObj DEVICE_NAND_ECC_info = 
{
  TRUE,         // ECCEnable
  4,            // calcECCByteCnt
  4,            // storedECCByteCnt
  &(DEVICE_NAND_ECC_calculate),
  &(DEVICE_NAND_ECC_store),
  &(DEVICE_NAND_ECC_enable),
  &(DEVICE_NAND_ECC_disable),
  &(DEVICE_NAND_ECC_read),
  &(DEVICE_NAND_ECC_correct)
};

const NAND_BB_InfoObj DEVICE_NAND_BB_info = 
{
  TRUE,
  TRUE,
  &(DEVICE_NAND_BB_markSpareBytes),
  &(DEVICE_NAND_BB_checkSpareBytes)
};

// Specific Page layout to support ROM of device
const NAND_PAGE_LayoutObj DEVICE_NAND_PAGE_layout = 
{
  // Data region definition
  {
    NAND_REGION_DATA,           // Region Type
    NAND_OFFSETS_RELTODATA,     // Offsets relative type
    DEVICE_NAND_MAX_BYTES_PER_OP,      // bytesPerOp
    { 0*(512) ,1*(512) ,2*(512) ,3*(512) ,    // dataOffsets
      4*(512) ,5*(512) ,6*(512) ,7*(512) ,
      8*(512) ,9*(512) ,10*(512),11*(512),
      12*(512),13*(512),14*(512),15*(512) }
  },
  
  // Spare region definition
  {
    NAND_REGION_SPARE,          // Region Type
    NAND_OFFSETS_RELTOSPARE,    // Offsets relative type
    DEVICE_NAND_MAX_SPAREBYTES_PER_OP, // bytesPerOp  
    { 0*16  ,1*16  ,2*16  ,3*16  ,      // spareOffsets
      4*16  ,5*16  ,6*16  ,7*16  ,
      8*16  ,9*16  ,10*16 ,11*16 ,
      12*16 ,13*16 ,14*16 ,15*16  }
  }
};

// Table of ROM supported NAND devices
const NAND_CHIP_InfoObj DEVICE_NAND_CHIP_infoTable[] = 
{// devID,  numBlocks,  pagesPerBlock,  bytesPerPage
  { 0xE3,   512,        16,             512+16},	// 4 MB
  { 0xE5,   512,        16,             512+16},	// 4 MB
  
  { 0x39,   1024,       16,             512+16},	// 8 MB
  { 0xE6,   1024,       16,             512+16},	// 8 MB
  { 0x49,   1024,       16,             512+16},	// 8 MB x16
  { 0x59,   1024,       16,             512+16},	// 8 MB x16
  
  { 0x6B,   1024,       16,             512+16},	// 8 MB
  
  { 0x33,   1024,       32,             512+16},	// 16 MB
  { 0x73,   1024,       32,             512+16},	// 16 MB
//  { 0x43,   1024,       32,             512+16},	// 16 MB x16
//  { 0x53,   1024,       32,             512+16},	// 16 MB x16
  
  { 0x75,   2048,       32,             512+16},	// 32 MB
  { 0x35,   2048,       32,             512+16},	// 32 MB
  { 0xF5,   2048,       32,             512+16},  // 32 MB  

  { 0x76,   4096,       32,             512+16},	// 64 MB
  { 0x36,   4096,       32,             512+16},	// 64 MB
//  { 0x46,   4096,       32,             512+16},  // 64 MB x16
//  { 0x56,   4096,       32,             512+16},  // 64 MB x16

  { 0x78,   8192,       32,             512+16},  // 128 MB
  { 0x79,   8192,       32,             512+16},	// 128 MB
//  { 0x72,   8192,       32,             512+16},  // 128 MB x16
//  { 0x74,   8192,       32,             512+16},  // 128 MB x16

  { 0x71,   16384,      32,             512+16},	// 256 MB  

  { 0xA1,   1024,       64,             2048+64},	// 128 MB
//  { 0xB1,   1024,       64,             2048+64}, // 128 MB x16
//  { 0xC1,   1024,       64,             2048+64}, // 128 MB x16
  { 0xF1,   1024,       64,             2048+64}, // 128 MB  

  { 0xAA,   2048,       64,             2048+64},	// 256 MB (4th ID byte will be checked)
//  { 0xBA,   2048,       64,             2048+64}, // 256 MB x16 (4th ID byte will be checked) 
//  { 0xCA,   2048,       64,             2048+64}, // 256 MB x16 (4th ID byte will be checked)
  { 0xDA,   2048,       64,             2048+64},	// 256 MB (4th ID byte will be checked)

  { 0xAC,   4096,       64,             2048+64}, // 512 MB (4th ID byte will be checked)
//  { 0xBC,   4096,       64,             2048+64}, // 512 MB x16 (4th ID byte will be checked)
//  { 0xCC,   4096,       64,             2048+64}, // 512 MB x16 (4th ID byte will be checked)
  { 0xDC,   4096,       64,             2048+64},	// 512 MB (4th ID byte will be checked)

  { 0xA3,   8192,       64,             2048+64}, // 1 GB (4th ID byte will be checked)
//  { 0xB3,   8192,       64,             2048+64}, // 1 GB x16 (4th ID byte will be checked) 
//  { 0xC3,   8192,       64,             2048+64}, // 1 GB x16 (4th ID byte will be checked) 
  { 0xD3,   8192,       64,             2048+64}, // 1 GB (4th ID byte will be checked)

  { 0xA5,  16384,       64,             2048+64}, // 2 GB (4th ID byte will be checked)
//  { 0xB5,  16384,       64,             2048+64}, // 2 GB x16 (4th ID byte will be checked)
//  { 0xC5,  16384,       64,             2048+64}, // 2 GB x16 (4th ID byte will be checked)
  { 0xD5,  16384,       64,             2046+64}, // 2 GB (4th ID byte will be checked)
   
  { 0x00,      0,        0,                   0}	// Dummy null entry to indicate end of table
};


/************************************************************
* Global Function Definitions                               *
************************************************************/

static void DEVICE_NAND_ECC_calculate(NAND_InfoHandle hNandInfo, Uint8 *data, Uint8 *calcECC)
{
  Uint32 *eccValue = (Uint32 *) calcECC;
  eccValue[0] = ((Uint32*)(&(AEMIF->NANDF1ECC)))[hNandInfo->CSOffset] & 0x0FFF0FFF;
}

// Do conversion from 8 10-bit ECC values from HW (in 16 byte input) to 10 8-bit continguous values for storage in spare bytes
static void DEVICE_NAND_ECC_store(NAND_InfoHandle hNandInfo, Uint8 *spareBytes, Uint8 opNum, Uint8 *calcECC)
{
  Uint8 i,*eccBytes;
  
  eccBytes = (hNandInfo->isLargePage)?(spareBytes+DEVICE_NAND_ECC_START_OFFSET_LARGEPAGE):(spareBytes+DEVICE_NAND_ECC_START_OFFSET_SMALLPAGE);
  eccBytes += hNandInfo->hPageLayout->spareRegion.bytesPerOp * opNum;
  
  // Swap ECC byte order for storing to NAND
  for (i=0; i<DEVICE_NAND_ECC_info.calcECCByteCnt; i++)
  {
    eccBytes[i] = calcECC[DEVICE_NAND_ECC_info.calcECCByteCnt - 1 - i];
  }
} 

static void DEVICE_NAND_ECC_enable(NAND_InfoHandle hNandInfo)
{
  VUint32 temp;
  
  // Write appropriate bit to start ECC calcualtions
  AEMIF->NANDFCR |= (1<<(8 + (hNandInfo->CSOffset)));
  
  // Flush NANDFCR write (by reading another CFG register)
  temp = AEMIF->ERCSR;
}

static void DEVICE_NAND_ECC_disable(NAND_InfoHandle hNandInfo)
{
  VUint32 temp;

  // Flush data accesses (by reading CS3 data region)
  temp = *((VUint32*)(((VUint8*)hNandInfo->flashBase) + DEVICE_EMIF_INTER_CE_REGION_SIZE));
  
  // Read the ECC register to end the calculation and clear the ECC start bit
  temp = AEMIF->NANDF1ECC;
}

// Read 10 8-bit values from pagebuffer and convert to 8 10-bit values
static void DEVICE_NAND_ECC_read(NAND_InfoHandle hNandInfo, Uint8 *spareBytes, Uint8 opNum, Uint8 *readECC)
{
  Uint8 i,*eccBytes;
  
  eccBytes = (hNandInfo->isLargePage)?(spareBytes+DEVICE_NAND_ECC_START_OFFSET_LARGEPAGE):(spareBytes+DEVICE_NAND_ECC_START_OFFSET_SMALLPAGE);
  eccBytes += hNandInfo->hPageLayout->spareRegion.bytesPerOp * opNum;
  
  for (i=0; i<DEVICE_NAND_ECC_info.storedECCByteCnt; i++)
  {
    readECC[i] = eccBytes[DEVICE_NAND_ECC_info.calcECCByteCnt - 1 - i];
  }
}

static Uint32 DEVICE_NAND_ECC_correct(NAND_InfoHandle hNandInfo, Uint8 *data, Uint8 *readECC)
{
  Uint16 ECCxorVal, byteAddr, bitAddr;
  Uint32 *ECCold, *ECCnew, calcECC = 0;
  
  ECCold = (Uint32 *) readECC;
  ECCnew = (Uint32 *) &calcECC;
  DEVICE_NAND_ECC_calculate(hNandInfo, data, (Uint8 *)ECCnew);

  if (!DEVICE_NAND_ECC_info.ECCEnable)
    return E_PASS;

  if ((*ECCold) == (*ECCnew))
    return E_PASS;

  ECCxorVal = (Uint16)  ((ECCold[0] & 0xFFFF0000) >> 16) ^  // write ECCo
                        ((ECCold[0] & 0x0000FFFF) >> 0 ) ^  // write ECCe
                        ((ECCnew[0] & 0xFFFF0000) >> 16) ^  // read ECCo 
                        ((ECCnew[0] & 0x0000FFFF) >> 0 );   // read ECCe

  if ( ECCxorVal == 0x000003FF )
  {
    // Single Bit error - can be corrected
    ECCxorVal = (Uint16) ((ECCold[0] & 0xFFFF0000) >> 16) ^ ((ECCnew[0] & 0xFFFF0000) >> 16);
    byteAddr = (ECCxorVal >> 3);
    bitAddr = (ECCxorVal & 0x7);
    data[byteAddr] ^= (0x1 << bitAddr);
    return E_PASS;
  }
  else
  {
    // Multiple Bit error - nothing we can do
    return E_FAIL;
  }
}

// Function to manipulate the spare bytes to mark as a bad block
static void DEVICE_NAND_BB_markSpareBytes(NAND_InfoHandle hNandInfo, Uint8 *spareBytes)
{
  Uint32 i,j,offset;

  offset = (hNandInfo->isLargePage)?DEVICE_NAND_ECC_START_OFFSET_LARGEPAGE:DEVICE_NAND_ECC_START_OFFSET_SMALLPAGE;

  // Mark all the free bytes (non-ECC bytes) as 0x00
  for (j = 0; j< hNandInfo->numOpsPerPage; j++)
  {
    for (i=0; i<offset; i++)
    {
      spareBytes[i+hNandInfo->spareBytesPerOp*j] = 0x00;
    }
    for (i=(offset+DEVICE_NAND_ECC_info.storedECCByteCnt); i<hNandInfo->spareBytesPerOp; i++)
    {
      spareBytes[i+hNandInfo->spareBytesPerOp*j] = 0x00;
    }
  }
}

// Function to determine if the spare bytes indicate a bad block
static Uint32 DEVICE_NAND_BB_checkSpareBytes(NAND_InfoHandle hNandInfo, Uint8 *spareBytes)
{
  Uint32 i,j,offset;

  offset = (hNandInfo->isLargePage)?DEVICE_NAND_ECC_START_OFFSET_LARGEPAGE:DEVICE_NAND_ECC_START_OFFSET_SMALLPAGE;

  // Check all the free bytes (non-ECC bytes) for 0xFF
  for (j = 0; j< hNandInfo->numOpsPerPage; j++)
  {
    for (i=0; i<offset; i++)
    {
      if (spareBytes[i+hNandInfo->spareBytesPerOp*j] != 0xFF)
        return E_FAIL;
    }
    for (i=(offset+DEVICE_NAND_ECC_info.storedECCByteCnt); i<hNandInfo->spareBytesPerOp; i++)
    {
      if (spareBytes[i+hNandInfo->spareBytesPerOp*j] != 0xFF)
        return E_FAIL;
    }
  }

  return E_PASS;
}

/***********************************************************
* End file                                                 *
***********************************************************/

/* --------------------------------------------------------------------------
  HISTORY
    v1.00 - DJA - 04-Apr-2008
      Initial release
-------------------------------------------------------------------------- */

