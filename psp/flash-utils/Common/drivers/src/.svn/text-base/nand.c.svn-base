/* --------------------------------------------------------------------------
  FILE      : nand.c                                                   
  PROJECT   : TI Booting and Flashing Utilities
  AUTHOR    : Daniel Allred
  DESC      : Generic NAND driver file for EMIFA peripheral
-------------------------------------------------------------------------- */


/************************************************************
* Include Files                                             *
************************************************************/

// General type include
#include "tistdtypes.h"

// Device specific CSL
#include "device.h"

#ifndef USE_IN_ROM
  // Util functions
  #include "util.h"

  // Debug functions for non-ROMed version
  #include "debug.h"
#endif

// This module's header file 
#include "nand.h"

// Device NAND specific stuff
#include "device_nand.h"


/************************************************************
* Explicit External Declarations                            *
************************************************************/

// The device specific table of supported NAND devices
extern NAND_CHIP_InfoObj    DEVICE_NAND_CHIP_infoTable[];

// The device specific ECC info struct
extern NAND_ECC_InfoObj     DEVICE_NAND_ECC_info;

// The device specific BB info struct
extern NAND_BB_InfoObj      DEVICE_NAND_BB_info;

// The device specific PAGE layout structure
extern NAND_PAGE_LayoutObj  DEVICE_NAND_PAGE_layout;


/************************************************************
* Local Macro Declarations                                  *
************************************************************/


/************************************************************
* Local Function Declarations                               *
************************************************************/

// Low-level NAND functions read, write, and command functions
static VUint8 *LOCAL_flashMakeAddr (Uint32 baseAddr, Uint32 offset);
static void LOCAL_flashWriteData(NAND_InfoHandle hNandInfo, Uint32 offset, Uint32 data);
static Uint32 LOCAL_flashReadData(NAND_InfoHandle hNandInfo);

// Address byte write functions
static void LOCAL_flashWriteColAddrBytes(NAND_InfoHandle hNandInfo, Uint32 offset);
static void LOCAL_flashWriteRowAddrBytes(NAND_InfoHandle hNandInfo, Uint32 page);


#ifndef USE_IN_ROM
// Array data writing functions
static void LOCAL_flashWriteBytes (NAND_InfoHandle hNandInfo, void *pSrc, Uint32 numBytes);

// Function to erase a block
static Uint32 LOCAL_eraseBlock(NAND_InfoHandle hNandInfo, Uint32 block, Bool force);
#endif

// Array data reading functions
static void LOCAL_flashReadBytes(NAND_InfoHandle hNandInfo, void *pDest, Uint32 numBytes);

// Wait for ready signal seen at NANDFSCR
static Uint32 LOCAL_flashWaitForRdy(Uint32 timeout);

// Wait for status result from device to read good
static Uint32 LOCAL_flashWaitForStatus(NAND_InfoHandle hNandInfo, Uint32 timeout);

// page Pointer set function
static Uint32 LOCAL_setPagePtr(NAND_InfoHandle hNandInfo,NAND_RegionType regtionType, Uint32 opNum);

// Get Chip details
static Uint32 LOCAL_flashGetDetails(NAND_InfoHandle hNandInfo);

// ONFI CRC check for Read Parameter Page command
static Bool LOCAL_onfiParamPageCRCCheck(Uint8 *paramPageData);


/************************************************************
* Local Variable Definitions                                *
************************************************************/


/************************************************************
* Global Variable Definitions                               *
************************************************************/

#ifdef USE_IN_ROM
#pragma DATA_SECTION(gNandInfo,".NANDInfoStruct")
NAND_InfoObj gNandInfo;
#endif


/************************************************************
* Global Function Definitions                               *
************************************************************/

// Initialze NAND interface and find the details of the NAND used
NAND_InfoHandle NAND_open(Uint32 baseCSAddr,  Uint8 busWidth)
{
  NAND_InfoHandle hNandInfo;

  // Set NandInfo handle
#ifdef USE_IN_ROM
  hNandInfo = (NAND_InfoHandle) &gNandInfo;
#else
  hNandInfo = (NAND_InfoHandle) UTIL_allocMem(sizeof(NAND_InfoObj));
#endif

  // Set NAND flash base address
  hNandInfo->flashBase = baseCSAddr;
  
  // Init the current block number and good flag
  hNandInfo->currBlock = -1;     
  hNandInfo->isBlockGood = FALSE;  
  
  // Use device specific page layout and ECC layout
  hNandInfo->hPageLayout  = &DEVICE_NAND_PAGE_layout;
  hNandInfo->hEccInfo     = &DEVICE_NAND_ECC_info;
  hNandInfo->hBbInfo      = &DEVICE_NAND_BB_info;
  hNandInfo->hChipInfo    = DEVICE_NAND_CHIP_infoTable;
    
  // Get the CSOffset ( can be 0 through (DEVICE_EMIF_NUMBER_CE_REGION -1) )
  hNandInfo->CSOffset = 0;
  while (hNandInfo->CSOffset < DEVICE_EMIF_NUMBER_CE_REGION)
  {
    if ( (hNandInfo->flashBase >= (DEVICE_EMIF_FIRST_CE_START_ADDR + (DEVICE_EMIF_INTER_CE_REGION_SIZE * (hNandInfo->CSOffset+0)))) &&
         (hNandInfo->flashBase <  (DEVICE_EMIF_FIRST_CE_START_ADDR + (DEVICE_EMIF_INTER_CE_REGION_SIZE * (hNandInfo->CSOffset+1)))) 
       )
    {
      break;
    }
    hNandInfo->CSOffset++;
  }

  if (hNandInfo->CSOffset == DEVICE_EMIF_NUMBER_CE_REGION)
    return NULL;
    
  // Set EMIF bus width
  hNandInfo->busWidth = busWidth;

  // Setup AEMIF registers for NAND    
  AEMIF->NANDFCR |= (0x1 << (hNandInfo->CSOffset));        // NAND enable for CSx
  (*hNandInfo->hEccInfo->fxnEnable)(hNandInfo);
                         
  // Send reset command to NAND
  if ( NAND_reset(hNandInfo) != E_PASS )
    return NULL;
  
  // Get and set device details
  if ( LOCAL_flashGetDetails(hNandInfo) != E_PASS )
    return NULL;

  // Send reset command to NAND
  if ( NAND_reset(hNandInfo) != E_PASS )
    return NULL;
  
  return hNandInfo;
}


// Routine to check a particular block to see if it is good or bad
Uint32 NAND_badBlockCheck(NAND_InfoHandle hNandInfo, Uint32 block)
{
  Uint8 spareBytes[256];

  if (!hNandInfo->hBbInfo->BBCheckEnable)
  {
    return E_PASS;
  }
  else if (hNandInfo->currBlock != block)
  {
    hNandInfo->currBlock = block;

    // Read and check spare bytes of first page of block (ONFI and normal)
    NAND_readSpareBytesOfPage(hNandInfo, block, 0, spareBytes);
    
    if ((*hNandInfo->hBbInfo->fxnBBCheck)(hNandInfo,spareBytes) != E_PASS)
    {
      hNandInfo->isBlockGood = FALSE;
      return E_FAIL;
    }

    // Read and check spare bytes of second page of block (normal)
    NAND_readSpareBytesOfPage(hNandInfo, block, 1, spareBytes);
    if ((*hNandInfo->hBbInfo->fxnBBCheck)(hNandInfo,spareBytes) != E_PASS)
    {
      hNandInfo->isBlockGood = FALSE;
      return E_FAIL;
    }

    if (hNandInfo->isONFI)
    {
      // Read and check spare bytes of last page of block (for ONFI)
      NAND_readSpareBytesOfPage(hNandInfo, block, (hNandInfo->pagesPerBlock - 1), spareBytes);
      if ((*hNandInfo->hBbInfo->fxnBBCheck)(hNandInfo,spareBytes) != E_PASS)
      {
        hNandInfo->isBlockGood = FALSE;
        return E_FAIL;
      }
    }

    hNandInfo->isBlockGood = TRUE;
    return E_PASS;
  }
  else if (hNandInfo->isBlockGood == FALSE)
  {
    return E_FAIL;
  }
  else
  {
    return E_PASS;
  }  
}


// Routine to reset the NAND device
Uint32 NAND_reset(NAND_InfoHandle hNandInfo)
{
  // Send reset command to NAND
  LOCAL_flashWriteData(hNandInfo, DEVICE_NAND_CLE_OFFSET, NAND_RESET );
  return LOCAL_flashWaitForRdy(NAND_TIMEOUT);
}


// Routine to read a page from NAND
Uint32 NAND_readPage(NAND_InfoHandle hNandInfo, Uint32 block, Uint32 page, Uint8 *dest)
{
  Uint32 i, currPagePtr, nextPagePtr;
  //FIXME: the size of this array should be determined by the calcECCByteCnt
  Uint8 readECC[16];

  // This is enough to support 8 Kbyte page devices
  Uint8 spareBytes[256];

  // Get spare bytes of page (includes all stored ECC data)
  NAND_readSpareBytesOfPage(hNandInfo,block,page,spareBytes);
  
  // Write read command
  LOCAL_flashWriteData(hNandInfo,DEVICE_NAND_CLE_OFFSET,NAND_READ_PAGE);

  // Jump to first data region
  currPagePtr = LOCAL_setPagePtr(hNandInfo,NAND_REGION_DATA,0);
  LOCAL_flashWriteColAddrBytes(hNandInfo, currPagePtr);
  LOCAL_flashWriteRowAddrBytes(hNandInfo, (block*hNandInfo->pagesPerBlock) + page);

  // Additional confirm command for large page devices
  if(hNandInfo->isLargePage)
  {
    LOCAL_flashWriteData(hNandInfo, DEVICE_NAND_CLE_OFFSET, NAND_READ_30H);
  }

  // Wait for data to be available
  if(LOCAL_flashWaitForRdy(NAND_TIMEOUT) != E_PASS)
    return E_FAIL;

  // Clear the ECC hardware before starting
  (*hNandInfo->hEccInfo->fxnDisable)(hNandInfo);
 
  // Read data bytes with ECC enabled
  for (i=0; i < hNandInfo->numOpsPerPage; i++)
  {
    (*hNandInfo->hEccInfo->fxnEnable)(hNandInfo);
    LOCAL_flashReadBytes(hNandInfo, &dest[hNandInfo->dataBytesPerOp*i], hNandInfo->dataBytesPerOp);
    (*hNandInfo->hEccInfo->fxnDisable)(hNandInfo);

    // Use ECC bytes to correct any errors
    (*hNandInfo->hEccInfo->fxnRead)(hNandInfo, spareBytes, i, readECC);
    if ((*hNandInfo->hEccInfo->fxnCorrect)(hNandInfo,&dest[hNandInfo->dataBytesPerOp*i],readECC) != E_PASS)
    {
      return E_FAIL;
    }
    
    // Go to next data region of page
    currPagePtr += hNandInfo->dataBytesPerOp;
    
    if (i != (hNandInfo->numOpsPerPage-1))
    {  
      nextPagePtr = LOCAL_setPagePtr(hNandInfo,NAND_REGION_DATA,i+1);
      if ( currPagePtr != nextPagePtr )
      { 
        // Adjust page pointer      
        currPagePtr = nextPagePtr;
        
        // Jump to next data section of page (random read command)
        LOCAL_flashWriteData(hNandInfo,DEVICE_NAND_CLE_OFFSET,NAND_RANDOM_READ_PAGE);
        LOCAL_flashWriteColAddrBytes(hNandInfo, currPagePtr);
        LOCAL_flashWriteData(hNandInfo,DEVICE_NAND_CLE_OFFSET,NAND_RANDOM_READ_E0H);
      }
    }
  }

  // Return status check result
  return LOCAL_flashWaitForStatus(hNandInfo, NAND_TIMEOUT);
}

// Function to just read the sparebytes region of a page
Uint32 NAND_readSpareBytesOfPage(NAND_InfoHandle hNandInfo, Uint32 block, Uint32 page, Uint8 *dest)
{
  Uint32 i, currPagePtr, nextPagePtr;

  // The large page device MUST support Random Read Command (0x05)
  if(hNandInfo->isLargePage)
  {
    // Write read command
    LOCAL_flashWriteData(hNandInfo,DEVICE_NAND_CLE_OFFSET,NAND_READ_PAGE);
    
    // Jump to first spare bytes region
    currPagePtr = LOCAL_setPagePtr(hNandInfo,NAND_REGION_SPARE,0);
    LOCAL_flashWriteColAddrBytes(hNandInfo, currPagePtr);
    LOCAL_flashWriteRowAddrBytes(hNandInfo, (block*hNandInfo->pagesPerBlock) + page);
    
    // Additional confirm command for large page devices
    LOCAL_flashWriteData(hNandInfo, DEVICE_NAND_CLE_OFFSET, NAND_READ_30H);

    // Wait for data to be available
    if(LOCAL_flashWaitForRdy(NAND_TIMEOUT) != E_PASS)
      return E_FAIL;    
    
    // Collect spare bytes regions from the page into end of pageBuffer
    for (i=0; i < hNandInfo->numOpsPerPage; i++)
    {
      // Read spare bytes
      LOCAL_flashReadBytes(hNandInfo, &dest[hNandInfo->spareBytesPerOp*i], hNandInfo->spareBytesPerOp);
      currPagePtr += hNandInfo->spareBytesPerOp;
      nextPagePtr = LOCAL_setPagePtr(hNandInfo,NAND_REGION_SPARE,i+1);
      if ( (i != (hNandInfo->numOpsPerPage-1)) && ( currPagePtr != nextPagePtr) )
      { 
        // Adjust page pointer      
        currPagePtr = nextPagePtr;
        
        // Jump back to start of page (random read command)
        LOCAL_flashWriteData(hNandInfo,DEVICE_NAND_CLE_OFFSET,NAND_RANDOM_READ_PAGE);
        LOCAL_flashWriteColAddrBytes(hNandInfo, currPagePtr);
        LOCAL_flashWriteData(hNandInfo,DEVICE_NAND_CLE_OFFSET,NAND_RANDOM_READ_E0H);
      }
    }
  }
  else
  {
    // Go to start of spare bytes region
    LOCAL_flashWriteData(hNandInfo,DEVICE_NAND_CLE_OFFSET,NAND_EXTRA_PAGE);
    LOCAL_flashWriteColAddrBytes(hNandInfo, 0x0);
    LOCAL_flashWriteRowAddrBytes(hNandInfo, (block*hNandInfo->pagesPerBlock) + page);  
  
    // Wait for data to be available
    if(LOCAL_flashWaitForRdy(NAND_TIMEOUT) != E_PASS)
      return E_FAIL;
      
    // Read spare bytes (includes ECC data) 
    LOCAL_flashReadBytes(hNandInfo, dest, hNandInfo->spareBytesPerOp);
  }

  // Return status check result
  return LOCAL_flashWaitForStatus(hNandInfo, NAND_TIMEOUT);
}



// Defining this macro for the build will cause write (flash) ability to be removed
// This can be used for using this driver as read-only for ROM code
#ifndef USE_IN_ROM

// Check to see if device is write protected
Bool   NAND_isWriteProtected(NAND_InfoHandle hNandInfo)
{
  Uint32 status;
  
  LOCAL_flashWriteData(hNandInfo, DEVICE_NAND_CLE_OFFSET,NAND_STATUS);
  status = LOCAL_flashReadData(hNandInfo);
  
  return (status&NAND_STATUS_PROTECTED)?FALSE:TRUE;
}

// Function to mark a bad block
Uint32 NAND_badBlockMark(NAND_InfoHandle hNandInfo, Uint32 block)
{
  Uint8 spareBytes[256];

  // Check if marking enabled
  if (!hNandInfo->hBbInfo->BBMarkEnable)
  {
    return E_PASS;
  }
  
  // Check to see if this block is already known as bad
  if ((hNandInfo->currBlock == block) && (hNandInfo->isBlockGood == FALSE))
  {
    return E_PASS;
  }

  // Indicate that this block is bad
  hNandInfo->currBlock = block;
  hNandInfo->isBlockGood = FALSE;

  // Mark the spare bytes according to device specific function
  (*hNandInfo->hBbInfo->fxnBBMark)(hNandInfo,spareBytes);

  // Erase the block so that we can mark the pages
  if (LOCAL_eraseBlock(hNandInfo, block, TRUE) != E_PASS)
  {
    return E_FAIL;
  }

  // Write the marked spare bytes to the first page (ONFI and normal)
  if (NAND_writeOnlySpareBytesOfPage(hNandInfo,block,0,spareBytes) != E_PASS)
  {
    // Marking the first page didn't succeed, try a second
    if (hNandInfo->isONFI)
    {
      // Write the marked spare bytes to the last page (ONFI)
      return NAND_writeOnlySpareBytesOfPage(hNandInfo,block,(hNandInfo->pagesPerBlock - 1),spareBytes);
    }
    else
    {
      // Write the marked spare bytes to the second page (normal)
      return NAND_writeOnlySpareBytesOfPage(hNandInfo,block,1,spareBytes);
    }
  }

  return E_PASS;
}


// Function to write only the spare bytes region (page must be
// erased and not written to prior to calling this)
Uint32 NAND_writeOnlySpareBytesOfPage(NAND_InfoHandle hNandInfo, Uint32 block, Uint32 page, Uint8* spareBytes)
{
  Uint32 i,currPagePtr, nextPagePtr;

  // For small page devices, set pointer
  if (!hNandInfo->isLargePage)
    LOCAL_flashWriteData(hNandInfo, DEVICE_NAND_CLE_OFFSET, NAND_EXTRA_PAGE);
  
  // Write program command
  LOCAL_flashWriteData(hNandInfo, DEVICE_NAND_CLE_OFFSET, NAND_PGRM_START);

  // Write address bytes
  currPagePtr = LOCAL_setPagePtr(hNandInfo,NAND_REGION_SPARE,0);
  if (!hNandInfo->isLargePage)
    LOCAL_flashWriteColAddrBytes(hNandInfo, 0);
  else
    LOCAL_flashWriteColAddrBytes(hNandInfo, currPagePtr);
  LOCAL_flashWriteRowAddrBytes(hNandInfo, (block*hNandInfo->pagesPerBlock) + page);

  
  // Write spare bytes sections of page
  for (i=0; i<hNandInfo->numOpsPerPage; i++)
  {

    LOCAL_flashWriteBytes(hNandInfo, &spareBytes[hNandInfo->spareBytesPerOp*i], hNandInfo->spareBytesPerOp);
    
    currPagePtr += hNandInfo->spareBytesPerOp;

    if (i != (hNandInfo->numOpsPerPage-1))
    {  
      nextPagePtr = LOCAL_setPagePtr(hNandInfo,NAND_REGION_SPARE,i+1);
      if ( currPagePtr != nextPagePtr )
      { 
        // Adjust page pointer      
        currPagePtr = nextPagePtr;
      
        // Jump to next data section of page (random program command)
        LOCAL_flashWriteData(hNandInfo,DEVICE_NAND_CLE_OFFSET,NAND_RANDOM_PGRM);
        LOCAL_flashWriteColAddrBytes(hNandInfo, currPagePtr);
      }
    }
  }

  // Write program end command
  LOCAL_flashWriteData(hNandInfo, DEVICE_NAND_CLE_OFFSET, NAND_PGRM_END);

  // Wait for the device to be ready
  if (LOCAL_flashWaitForRdy(NAND_TIMEOUT) != E_PASS)
    return E_FAIL;

  // Return status check result  
  return LOCAL_flashWaitForStatus(hNandInfo, NAND_TIMEOUT);
}

// Generic routine to write a page of data to NAND
Uint32 NAND_writePage(NAND_InfoHandle hNandInfo, Uint32 block, Uint32 page, Uint8 *src)
{
  Uint32 i,currPagePtr, nextPagePtr;
  //FIXME: the size of this array should be determined by the calcECCByteCnt  
  Uint8 calcECC[16];

  // This is enough to support 8 Kbyte page devices
  Uint8 spareBytes[256];

  // Fill in the spare bytes region with 0xFF
  for (i=0; i<hNandInfo->spareBytesPerPage; i++)
  {
    spareBytes[i] = 0xFF;
  }

  // For small page devices, set pointer
  if (!hNandInfo->isLargePage)
    LOCAL_flashWriteData(hNandInfo, DEVICE_NAND_CLE_OFFSET, NAND_LO_PAGE);
  
  // Write program command
  LOCAL_flashWriteData(hNandInfo, DEVICE_NAND_CLE_OFFSET, NAND_PGRM_START);

  // Write address bytes
  currPagePtr = LOCAL_setPagePtr(hNandInfo,NAND_REGION_DATA,0);
  LOCAL_flashWriteColAddrBytes(hNandInfo, currPagePtr);
  LOCAL_flashWriteRowAddrBytes(hNandInfo, (block*hNandInfo->pagesPerBlock) + page);

  // Clear the ECC hardware before starting
  (*hNandInfo->hEccInfo->fxnDisable)(hNandInfo);

  // Write data sections of page, getting ECC data
  for (i=0; i<hNandInfo->numOpsPerPage; i++)
  {
    (*hNandInfo->hEccInfo->fxnEnable)(hNandInfo);
    LOCAL_flashWriteBytes(hNandInfo, &src[hNandInfo->dataBytesPerOp*i], hNandInfo->dataBytesPerOp);
    (*hNandInfo->hEccInfo->fxnDisable)(hNandInfo);

    (*hNandInfo->hEccInfo->fxnCalculate)(hNandInfo, &src[hNandInfo->dataBytesPerOp*i], calcECC);
    
    (*hNandInfo->hEccInfo->fxnStore)(hNandInfo, spareBytes, i, calcECC);
    
    currPagePtr += hNandInfo->dataBytesPerOp;

    if (i != (hNandInfo->numOpsPerPage-1))
    {  
      nextPagePtr = LOCAL_setPagePtr(hNandInfo,NAND_REGION_DATA,i+1);
      if ( currPagePtr != nextPagePtr )
      { 
        // Adjust page pointer      
        currPagePtr = nextPagePtr;
      
        // Jump to next data section of page (random program command)
        LOCAL_flashWriteData(hNandInfo,DEVICE_NAND_CLE_OFFSET,NAND_RANDOM_PGRM);
        LOCAL_flashWriteColAddrBytes(hNandInfo, currPagePtr);
      }
    }
    else
    {
      nextPagePtr = LOCAL_setPagePtr(hNandInfo,NAND_REGION_SPARE,0);
      if ( currPagePtr != nextPagePtr )
      { 
        // Adjust page pointer      
        currPagePtr = nextPagePtr;
      
        // Jump to first spare section of page (random program command)
        LOCAL_flashWriteData(hNandInfo,DEVICE_NAND_CLE_OFFSET,NAND_RANDOM_PGRM);
        LOCAL_flashWriteColAddrBytes(hNandInfo, currPagePtr);
      }
    }
  }

  // Write spare bytes sections of page
  for (i=0; i<hNandInfo->numOpsPerPage; i++)
  {

    LOCAL_flashWriteBytes(hNandInfo, &spareBytes[hNandInfo->spareBytesPerOp*i], hNandInfo->spareBytesPerOp);
    
    currPagePtr += hNandInfo->spareBytesPerOp;

    if (i != (hNandInfo->numOpsPerPage-1))
    {  
      nextPagePtr = LOCAL_setPagePtr(hNandInfo,NAND_REGION_SPARE,i+1);
      if ( currPagePtr != nextPagePtr )
      { 
        // Adjust page pointer      
        currPagePtr = nextPagePtr;
      
        // Jump to next spare section of page (random program command)
        LOCAL_flashWriteData(hNandInfo,DEVICE_NAND_CLE_OFFSET,NAND_RANDOM_PGRM);
        LOCAL_flashWriteColAddrBytes(hNandInfo, currPagePtr);
      }
    }
  }

  // Write program end command
  LOCAL_flashWriteData(hNandInfo, DEVICE_NAND_CLE_OFFSET, NAND_PGRM_END);

  // Wait for the device to be ready
  if (LOCAL_flashWaitForRdy(NAND_TIMEOUT) != E_PASS)
    return E_FAIL;

  // Return status check result  
  return LOCAL_flashWaitForStatus(hNandInfo, NAND_TIMEOUT);
}

#ifdef DM35X_STANDARD
// Generic routine to write a page of data to NAND
//Note:  This is identical to the NAND_writePage routine except for some special
//       handling required for the UBL header.  For the UBL header, the spare bytes
//       region for the first 512 sector of the page has to be duplicated in two places.
//       a)  In the normal spare bytes region
//       b)  At an offset of 512 bytes from the start of the page.  This is necessary to be
//           compatible with revision 1.1. silicon compatibility mode.

Uint32 NAND_writePage_ubl_header(NAND_InfoHandle hNandInfo, Uint32 block, Uint32 page, Uint8 *src)
{
  Uint32 i,j,currPagePtr, nextPagePtr;
  //FIXME: the size of this array should be determined by the calcECCByteCnt  
  Uint8 calcECC[16];

  // This is enough to support 8 Kbyte page devices
  Uint8 spareBytes[256];

  // Fill in the spare bytes region with 0xFF
  for (i=0; i<hNandInfo->spareBytesPerPage; i++)
  {
    spareBytes[i] = 0xFF;
  }

  // For small page devices, set pointer
  if (!hNandInfo->isLargePage)
    LOCAL_flashWriteData(hNandInfo, DEVICE_NAND_CLE_OFFSET, NAND_LO_PAGE);
  
  // Write program command
  LOCAL_flashWriteData(hNandInfo, DEVICE_NAND_CLE_OFFSET, NAND_PGRM_START);

  // Write address bytes
  currPagePtr = LOCAL_setPagePtr(hNandInfo,NAND_REGION_DATA,0);
  LOCAL_flashWriteColAddrBytes(hNandInfo, currPagePtr);
  LOCAL_flashWriteRowAddrBytes(hNandInfo, (block*hNandInfo->pagesPerBlock) + page);

  // Clear the ECC hardware before starting
  (*hNandInfo->hEccInfo->fxnDisable)(hNandInfo);

  // Write data sections of page, getting ECC data
  for (i=0; i<hNandInfo->numOpsPerPage; i++)
  {
    (*hNandInfo->hEccInfo->fxnEnable)(hNandInfo);
    LOCAL_flashWriteBytes(hNandInfo, &src[hNandInfo->dataBytesPerOp*i], hNandInfo->dataBytesPerOp);
    (*hNandInfo->hEccInfo->fxnDisable)(hNandInfo);

    (*hNandInfo->hEccInfo->fxnCalculate)(hNandInfo, &src[hNandInfo->dataBytesPerOp*i], calcECC);
    
    (*hNandInfo->hEccInfo->fxnStore)(hNandInfo, spareBytes, i, calcECC);
    
    currPagePtr += hNandInfo->dataBytesPerOp;

	//If we are doing the 1st 512 byte section, then copy the spare bytes information
	//into the first part of the 2nd 512 byte section.  This is legal because we KNOW that
	//this is a blank area for a header page.
	if (i == 0)
	{
	  for (j=0; j<16; j++) 
	  {
	     src[(hNandInfo->dataBytesPerOp)+j] = spareBytes[j];
	  }
	}

    if (i != (hNandInfo->numOpsPerPage-1))
    {  
      nextPagePtr = LOCAL_setPagePtr(hNandInfo,NAND_REGION_DATA,i+1);
      if ( currPagePtr != nextPagePtr )
      { 
        // Adjust page pointer      
        currPagePtr = nextPagePtr;
      
        // Jump to next data section of page (random program command)
        LOCAL_flashWriteData(hNandInfo,DEVICE_NAND_CLE_OFFSET,NAND_RANDOM_PGRM);
        LOCAL_flashWriteColAddrBytes(hNandInfo, currPagePtr);
      }
    }
    else
    {
      nextPagePtr = LOCAL_setPagePtr(hNandInfo,NAND_REGION_SPARE,0);
      if ( currPagePtr != nextPagePtr )
      { 
        // Adjust page pointer      
        currPagePtr = nextPagePtr;
      
        // Jump to first spare section of page (random program command)
        LOCAL_flashWriteData(hNandInfo,DEVICE_NAND_CLE_OFFSET,NAND_RANDOM_PGRM);
        LOCAL_flashWriteColAddrBytes(hNandInfo, currPagePtr);
      }
    }
  }

  // Write spare bytes sections of page
  for (i=0; i<hNandInfo->numOpsPerPage; i++)
  {

    LOCAL_flashWriteBytes(hNandInfo, &spareBytes[hNandInfo->spareBytesPerOp*i], hNandInfo->spareBytesPerOp);
    
    currPagePtr += hNandInfo->spareBytesPerOp;

    if (i != (hNandInfo->numOpsPerPage-1))
    {  
      nextPagePtr = LOCAL_setPagePtr(hNandInfo,NAND_REGION_SPARE,i+1);
      if ( currPagePtr != nextPagePtr )
      { 
        // Adjust page pointer      
        currPagePtr = nextPagePtr;
      
        // Jump to next spare section of page (random program command)
        LOCAL_flashWriteData(hNandInfo,DEVICE_NAND_CLE_OFFSET,NAND_RANDOM_PGRM);
        LOCAL_flashWriteColAddrBytes(hNandInfo, currPagePtr);
      }
    }
  }

  // Write program end command
  LOCAL_flashWriteData(hNandInfo, DEVICE_NAND_CLE_OFFSET, NAND_PGRM_END);

  // Wait for the device to be ready
  if (LOCAL_flashWaitForRdy(NAND_TIMEOUT) != E_PASS)
    return E_FAIL;

  // Return status check result  
  return LOCAL_flashWaitForStatus(hNandInfo, NAND_TIMEOUT);
}
#endif

// Test routine to write a page of data to NAND without writing sparebytes or ECC data
#if defined(NAND_ECC_TEST)
Uint32 NAND_writePageWithSpareBytes(NAND_InfoHandle hNandInfo, Uint32 block, Uint32 page, Uint8 *src, Uint8* spareBytes)
{
  Uint32 i,currPagePtr, nextPagePtr;
  //FIXME: the size of this array should be determined by the calcECCByteCnt  
  Uint8 calcECC[16];

  // For small page devices, set pointer
  if (!hNandInfo->isLargePage)
    LOCAL_flashWriteData(hNandInfo, DEVICE_NAND_CLE_OFFSET, NAND_LO_PAGE);
  
  // Write program command
  LOCAL_flashWriteData(hNandInfo, DEVICE_NAND_CLE_OFFSET, NAND_PGRM_START);

  // Write address bytes
  currPagePtr = LOCAL_setPagePtr(hNandInfo,NAND_REGION_DATA,0);
  LOCAL_flashWriteColAddrBytes(hNandInfo, currPagePtr);
  LOCAL_flashWriteRowAddrBytes(hNandInfo, (block*hNandInfo->pagesPerBlock) + page);

  (*hNandInfo->hEccInfo->fxnDisable)(hNandInfo);

  // Write data sections of page, getting ECC data
  for (i=0; i<hNandInfo->numOpsPerPage; i++)
  {
    (*hNandInfo->hEccInfo->fxnEnable)(hNandInfo);
    LOCAL_flashWriteBytes(hNandInfo, &src[hNandInfo->dataBytesPerOp*i], hNandInfo->dataBytesPerOp);
    (*hNandInfo->hEccInfo->fxnDisable)(hNandInfo);

    (*hNandInfo->hEccInfo->fxnCalculate)(hNandInfo, &src[hNandInfo->dataBytesPerOp*i], calcECC);
    
    currPagePtr += hNandInfo->dataBytesPerOp;

    if (i != (hNandInfo->numOpsPerPage-1))
    {  
      nextPagePtr = LOCAL_setPagePtr(hNandInfo,NAND_REGION_DATA,i+1);
      if ( currPagePtr != nextPagePtr )
      { 
        // Adjust page pointer      
        currPagePtr = nextPagePtr;
      
        // Jump to next data section of page (random program command)
        LOCAL_flashWriteData(hNandInfo,DEVICE_NAND_CLE_OFFSET,NAND_RANDOM_PGRM);
        LOCAL_flashWriteColAddrBytes(hNandInfo, currPagePtr);
      }
    }
    else
    {
      nextPagePtr = LOCAL_setPagePtr(hNandInfo,NAND_REGION_SPARE,0);
      if ( currPagePtr != nextPagePtr )
      { 
        // Adjust page pointer      
        currPagePtr = nextPagePtr;
      
        // Jump to first spare section of page (random program command)
        LOCAL_flashWriteData(hNandInfo,DEVICE_NAND_CLE_OFFSET,NAND_RANDOM_PGRM);
        LOCAL_flashWriteColAddrBytes(hNandInfo, currPagePtr);
      }
    }
  }

  // Write spare bytes sections of page
  for (i=0; i<hNandInfo->numOpsPerPage; i++)
  {
    LOCAL_flashWriteBytes(hNandInfo, &spareBytes[hNandInfo->spareBytesPerOp*i], hNandInfo->spareBytesPerOp);
    
    currPagePtr += hNandInfo->spareBytesPerOp;

    if (i != (hNandInfo->numOpsPerPage-1))
    {  
      nextPagePtr = LOCAL_setPagePtr(hNandInfo,NAND_REGION_SPARE,i+1);
      if ( currPagePtr != nextPagePtr )
      { 
        // Adjust page pointer      
        currPagePtr = nextPagePtr;
      
        // Jump to next spare section of page (random program command)
        LOCAL_flashWriteData(hNandInfo,DEVICE_NAND_CLE_OFFSET,NAND_RANDOM_PGRM);
        LOCAL_flashWriteColAddrBytes(hNandInfo, currPagePtr);
      }
    }
  }

  // Write program end command
  LOCAL_flashWriteData(hNandInfo, DEVICE_NAND_CLE_OFFSET, NAND_PGRM_END);

  // Wait for the device to be ready
  if (LOCAL_flashWaitForRdy(NAND_TIMEOUT) != E_PASS)
    return E_FAIL;

  // Return status check result  
  return LOCAL_flashWaitForStatus(hNandInfo, NAND_TIMEOUT);
}
#endif

// Verify data written by reading and comparing byte for byte
Uint32 NAND_verifyPage(NAND_InfoHandle hNandInfo, Uint32 block, Uint32 page, Uint8* src, Uint8* dest)
{
  Uint32 i;

  if (NAND_readPage(hNandInfo, block, page, dest) != E_PASS)
    return E_FAIL;
    
  for (i=0; i <(hNandInfo->dataBytesPerPage>>2); i++)
  {
    // Check for data read errors
    if ( ((Uint32 *)src)[i] != ((Uint32 *)dest)[i] )
    {
      DEBUG_printString("Data verification failed! Block: ");
      DEBUG_printHexInt(block);
      DEBUG_printString(" page: ");
      DEBUG_printHexInt(page);
      DEBUG_printString(". First Failing Byte: ");
      DEBUG_printHexInt(i<<2);
      DEBUG_printString("\r\n");
      return E_FAIL;
    }
  }

  return E_PASS;
}

// Verify erase succeeded by reading and comparing byte for byte
Uint32 NAND_verifyBlockErased(NAND_InfoHandle hNandInfo, Uint32 block, Uint8* dest)
{
  Uint32 i,j;
  
  for (j=0; j<hNandInfo->pagesPerBlock; j++)
  {
    if (NAND_readPage(hNandInfo, block, j, dest) != E_PASS)
      return E_FAIL;
    
    for (i=0; i<(hNandInfo->dataBytesPerPage>>2); i++)
    {
      // Check for data read errors
      if (((Uint32 *)dest)[i] += 0xFFFFFFFF)
      {
        DEBUG_printString("Erase verification failed! Block: ");
        DEBUG_printHexInt(block);
        DEBUG_printString(" page: ");
        DEBUG_printHexInt(j);
        DEBUG_printString(". First Failing Byte: ");
        DEBUG_printHexInt(i);
        DEBUG_printString("\r\n");
        return E_FAIL;
      }
    }
  }
  return E_PASS;
}

// Global Erase NAND Flash
Uint32 NAND_globalErase(NAND_InfoHandle hNandInfo)
{
  // We don't erase block 0, and possibly some ending blocks reserved for BBT
  return NAND_eraseBlocks( hNandInfo, 1, (hNandInfo->numBlocks - 1 - NAND_NUM_BLOCKS_RESERVED_FOR_BBT) );
}

// GLobal Erase NAND flash with Bad Block checking and marking
Uint32 NAND_globalErase_with_bb_check(NAND_InfoHandle hNandInfo)
{
  // We don't erase block 0, and possibly some ending blocks reserved for BBT
  return NAND_eraseBlocks_with_bb_check( hNandInfo, 1, (hNandInfo->numBlocks - 1) );
}

// NAND Flash erase block function
Uint32 NAND_eraseBlocks(NAND_InfoHandle hNandInfo, Uint32 startBlkNum, Uint32 blkCnt)
{  
  Uint32 i;
  Uint32 endBlkNum = startBlkNum + blkCnt - 1;

  // Do bounds checking
  if ( endBlkNum >= hNandInfo->numBlocks )
    return E_FAIL;
  
  // Output info about what we are doing
  DEBUG_printString("Erasing block ");
  DEBUG_printHexInt(startBlkNum);
  DEBUG_printString(" through ");
  DEBUG_printHexInt(endBlkNum);
  DEBUG_printString(".\r\n");

  for (i = startBlkNum; i <= endBlkNum; i++)
  {
    if (LOCAL_eraseBlock(hNandInfo,i,FALSE) != E_PASS)
      return E_FAIL;
  }
  
  return E_PASS;
}

Uint32 NAND_eraseBlocks_with_bb_check(NAND_InfoHandle hNandInfo, Uint32 startBlkNum, Uint32 blkCnt)
{  
  Uint32 i;
  Uint32 endBlkNum = startBlkNum + blkCnt - 1;

  // Do bounds checking
  if ( endBlkNum >= hNandInfo->numBlocks )
    return E_FAIL;
  
  // Output info about what we are doing
  DEBUG_printString("Erasing block ");
  DEBUG_printHexInt(startBlkNum);
  DEBUG_printString(" through ");
  DEBUG_printHexInt(endBlkNum);
  DEBUG_printString(".\r\n");

  for (i = startBlkNum; i <= endBlkNum; i++)
  {
    if (LOCAL_eraseBlock(hNandInfo,i,FALSE) != E_PASS)
    {
      DEBUG_printString(" Bad Block NO  \n");
      DEBUG_printHexInt(i);
      DEBUG_printString(" Erasing is skipped \n");
      NAND_badBlockMark(hNandInfo, i);
    }	
  }
 
  return E_PASS;
}

// NAND Flash unprotect command
Uint32 NAND_unProtectBlocks(NAND_InfoHandle hNandInfo, Uint32 startBlkNum, Uint32 blkCnt)
{
  Uint32 endBlkNum = startBlkNum + blkCnt - 1;

  // Do bounds checking
  if (endBlkNum >= hNandInfo->numBlocks)
    return E_FAIL;

  // Output info about what we are doing
  DEBUG_printString("Unprotecting blocks ");
  DEBUG_printHexInt(startBlkNum);
  DEBUG_printString(" through ");
  DEBUG_printHexInt(endBlkNum);
  DEBUG_printString(".\r\n");

  LOCAL_flashWriteData(hNandInfo, DEVICE_NAND_CLE_OFFSET, NAND_UNLOCK_START);
  LOCAL_flashWriteRowAddrBytes(hNandInfo, hNandInfo->pagesPerBlock * startBlkNum);
  
  LOCAL_flashWriteData(hNandInfo, DEVICE_NAND_CLE_OFFSET, NAND_UNLOCK_END);
  LOCAL_flashWriteRowAddrBytes(hNandInfo, hNandInfo->pagesPerBlock * endBlkNum);
    
  return E_PASS;
}

// NAND Flash protect command
void NAND_protectBlocks(NAND_InfoHandle hNandInfo)
{
  DEBUG_printString("Protecting the entire NAND flash.\n");
  LOCAL_flashWriteData(hNandInfo, DEVICE_NAND_CLE_OFFSET, NAND_LOCK);
}

#endif // END of !defined(USE_IN_ROM) section


/************************************************************
* Local Function Definitions                                *
************************************************************/

// Generic Low-level NAND access functions
static VUint8 *LOCAL_flashMakeAddr (Uint32 baseAddr, Uint32 offset)
{
  return ((VUint8 *) ( baseAddr + offset ));
}

static void LOCAL_flashWriteData(NAND_InfoHandle hNandInfo, Uint32 offset, Uint32 data)
{
  volatile NAND_Ptr addr;
  NAND_Data dataword;
  dataword.l = data;

  addr.cp = LOCAL_flashMakeAddr (hNandInfo->flashBase, offset);
  switch (hNandInfo->busWidth)
  {
    case BUS_8BIT:
      *addr.cp = dataword.c;
      break;
    case BUS_16BIT:
      *addr.wp = dataword.w;
      break;
  }
}

static Uint32 LOCAL_flashReadData (NAND_InfoHandle hNandInfo)
{
  volatile NAND_Ptr addr;
  NAND_Data cmdword;
  cmdword.l = 0x0;

  addr.cp = LOCAL_flashMakeAddr (hNandInfo->flashBase, NAND_DATA_OFFSET );
  switch (hNandInfo->busWidth)
  {
    case BUS_8BIT:
     cmdword.c = *addr.cp;
     break;
    case BUS_16BIT:
     cmdword.w = *addr.wp;
     break;
  }
  return cmdword.l;
}

static void LOCAL_flashWriteRowAddrBytes(NAND_InfoHandle hNandInfo, Uint32 page)
{
  Uint32 i;
  for (i=0; i<hNandInfo->numRowAddrBytes; i++)
  {
    LOCAL_flashWriteData(hNandInfo, DEVICE_NAND_ALE_OFFSET, ( (page >> (8*i) ) & 0xff) );
  }
}

static void LOCAL_flashWriteColAddrBytes(NAND_InfoHandle hNandInfo, Uint32 offset)
{
  Uint32 i;

  // Adjust column address for 16-bit buswidth since we address words instead of bytes
  if (hNandInfo->busWidth == (Uint8) DEVICE_BUSWIDTH_16BIT)
    offset >>= 1;

  for (i=0; i<hNandInfo->numColAddrBytes; i++)
  {
    LOCAL_flashWriteData(hNandInfo, DEVICE_NAND_ALE_OFFSET, ( (offset >> (8*i) ) & 0xff) );
  }
}

#ifndef USE_IN_ROM
static void LOCAL_flashWriteBytes(NAND_InfoHandle hNandInfo, void* pSrc, Uint32 numBytes)
{
  volatile NAND_Ptr destAddr, srcAddr;
  Uint32 i;
  
  srcAddr.cp = (VUint8*) pSrc;
  destAddr.cp = LOCAL_flashMakeAddr (hNandInfo->flashBase, NAND_DATA_OFFSET );
  switch (hNandInfo->busWidth)
  {
    case BUS_8BIT:
      for(i=0;i<( numBytes );i++)
        *destAddr.cp = *srcAddr.cp++;
      break;
    case BUS_16BIT:
      for(i=0;i<( numBytes >> 1);i++)
        *destAddr.wp = *srcAddr.wp++;
      break;
    }
}

static Uint32 LOCAL_eraseBlock(NAND_InfoHandle hNandInfo, Uint32 block, Bool force)
{
  
  // Start erase command
  LOCAL_flashWriteData(hNandInfo, DEVICE_NAND_CLE_OFFSET, NAND_BERASEC1);

  // Write the row addr bytes only
  LOCAL_flashWriteRowAddrBytes(hNandInfo, hNandInfo->pagesPerBlock * block );
  
  // Confirm erase command
  LOCAL_flashWriteData(hNandInfo, DEVICE_NAND_CLE_OFFSET, NAND_BERASEC2);

  // Wait for the device to be ready
  if (LOCAL_flashWaitForRdy(NAND_TIMEOUT) != E_PASS)
    return E_FAIL;

  // Verify the op succeeded by reading status from flash
  return LOCAL_flashWaitForStatus(hNandInfo, NAND_TIMEOUT);
} 
#endif

static void LOCAL_flashReadBytes(NAND_InfoHandle hNandInfo, void* pDest, Uint32 numBytes)
{
  volatile NAND_Ptr destAddr, srcAddr;
  Uint32 i;
  
  destAddr.cp = (VUint8*) pDest;
  srcAddr.cp = LOCAL_flashMakeAddr (hNandInfo->flashBase, NAND_DATA_OFFSET );
  switch (hNandInfo->busWidth)
  {
    case BUS_8BIT:
        for(i=0;i<( numBytes );i++)
          *destAddr.cp++ = *srcAddr.cp;
        break;
    case BUS_16BIT:
        for(i=0;i<( numBytes >> 1);i++)
          *destAddr.wp++ = *srcAddr.wp;
        break;
    }
}

// Poll bit of NANDFSR to indicate ready
static Uint32 LOCAL_flashWaitForRdy(Uint32 timeout)
{
  VUint32 cnt;
  Uint32 status;
  Bool status_reached_zero = FALSE;

  cnt = timeout;

  // Wait for the status to show busy, and then after that
  // point we start checking for it to be high.  If we
  // don't do this we might see the status as ready before
  // it has even transitioned to show itself as busy.
  do 
  {  
    status = (AEMIF->NANDFSR & NAND_NANDFSR_READY);
    if (status == 0)
      status_reached_zero = TRUE;
  }
  while(((cnt--)>0) && (!status || (status_reached_zero == FALSE)));

  return E_PASS;
}


// Wait for the status to be ready in NAND register
//      There were some problems reported in DM320 with Ready/Busy pin
//      not working with all NANDs. So this check has also been added.
static Uint32 LOCAL_flashWaitForStatus(NAND_InfoHandle hNandInfo, Uint32 timeout)
{
  VUint32 cnt;
  Uint32 status;
  cnt = timeout;

  do
  {
    LOCAL_flashWriteData(hNandInfo, DEVICE_NAND_CLE_OFFSET,NAND_STATUS);
    status = LOCAL_flashReadData(hNandInfo);
    cnt--;
  }
  while((cnt>0) && !(status & NAND_STATUS_READY));

  if( (cnt == 0) || (status & NAND_STATUS_ERROR) )
  {
    return E_FAIL;
  }

  return E_PASS;
}


// Function to set page pointer to appropriate location
static Uint32 LOCAL_setPagePtr(NAND_InfoHandle hNandInfo, NAND_RegionType regionType, Uint32 opNum)
{
  Uint32 currPtr = 0;
  NAND_RegionHandle hRegion;
  hRegion = (regionType == NAND_REGION_DATA)? &(hNandInfo->hPageLayout->dataRegion): &(hNandInfo->hPageLayout->spareRegion);
  
  currPtr = (hRegion->offsetType == NAND_OFFSETS_RELTODATA)? 0 : hNandInfo->dataBytesPerPage;
  currPtr += hRegion->offsets[opNum];
  
  return currPtr;
}


// Get details of the NAND flash used from the id and the table of NAND devices
static Uint32 LOCAL_flashGetDetails(NAND_InfoHandle hNandInfo)
{
  Uint8 devID[4];
  Uint32 i,j;
  
  // Check if ONFI compatible device
  LOCAL_flashWriteData(hNandInfo, DEVICE_NAND_CLE_OFFSET, NAND_RDID);
  LOCAL_flashWriteData(hNandInfo, DEVICE_NAND_ALE_OFFSET, NAND_ONFIRDIDADD);
  
  // Wait for data to be available
  if(LOCAL_flashWaitForRdy(NAND_TIMEOUT) != E_PASS)
    return E_FAIL;
    
  // Read ID bytes (to check for ONFI signature)
  for (i=0; i<4; i++)
    devID[i] = LOCAL_flashReadData(hNandInfo) & 0xFF;

  // Set ONFI flag as appropriate  
  if ( *((Uint32 *)devID) == NANDONFI_STRING)
    hNandInfo->isONFI = TRUE;
  else
    hNandInfo->isONFI = FALSE;
    
  // Send reset command to NAND
  if ( NAND_reset(hNandInfo) != E_PASS )
    return E_FAIL;
    
  // Issue device read ID command
  LOCAL_flashWriteData(hNandInfo, DEVICE_NAND_CLE_OFFSET, NAND_RDID);
  LOCAL_flashWriteData(hNandInfo, DEVICE_NAND_ALE_OFFSET, NAND_RDIDADD);
  
  // Wait for data to be available
  if(LOCAL_flashWaitForRdy(NAND_TIMEOUT) != E_PASS)
    return E_FAIL;

  // Read ID bytes (to get true device ID data)
  for (i=0; i<4; i++)
    devID[i] = LOCAL_flashReadData(hNandInfo) & 0xFF;

  if (hNandInfo->isONFI)
  {
    Uint8 paramPageData[256];
    
    // Issue read param page command
    LOCAL_flashWriteData(hNandInfo, DEVICE_NAND_CLE_OFFSET, NANDONFI_RDPARAMPAGE);
    
    // Issue lo-page address
    LOCAL_flashWriteData(hNandInfo, DEVICE_NAND_ALE_OFFSET, NAND_READ_PAGE);
    
    // Wait for data to be available
    if(LOCAL_flashWaitForRdy(NAND_TIMEOUT) != E_PASS)
      return E_FAIL;
      
    // Read 256 bytes of param page data
    j = 0;
    do 
    {
      for (i=0; i<256; i++)
        paramPageData[i] = LOCAL_flashReadData(hNandInfo) & 0xFF;
      j++;
    }
    while ((!LOCAL_onfiParamPageCRCCheck(paramPageData)) && (j<3));

    // We never got a good param page, so look in the NAND table
    if (j == 3) goto SEARCH_TABLE;

    // Use JEDEC manufacturer ID from Parameter Page
    hNandInfo->manfID = paramPageData[64];
    
    // Use Device ID from the standard READID command
    hNandInfo->devID = (Uint8) devID[1];
    
    // Use Parameter Page data to fill in NAND device info structure
    hNandInfo->dataBytesPerPage     = (Uint16) (*((Uint32 *) (paramPageData+80))) & 0xFFFF;
    hNandInfo->spareBytesPerPage    = (Uint16) (*((Uint16 *) (paramPageData+84)));
    hNandInfo->pagesPerBlock        = (Uint16) (*((Uint32 *) (paramPageData+92))) & 0xFFFF;
    hNandInfo->numBlocks            = (Uint32) (*((Uint32 *) (paramPageData+96))) * paramPageData[100];
    hNandInfo->numColAddrBytes      = (Uint8)  ((paramPageData[101] >> 4) & 0xF);
    hNandInfo->numRowAddrBytes      = (Uint8)  (paramPageData[101] & 0xF);
  }
  else
  {
SEARCH_TABLE:
    i=0;

    hNandInfo->manfID = (Uint8) devID[0];
    hNandInfo->devID = (Uint8) devID[1]; 

    // Search for Device ID in table
    while (hNandInfo->hChipInfo[i].devID != 0x00)
    {
      if(devID[1] == hNandInfo->hChipInfo[i].devID)
      {
        hNandInfo->pagesPerBlock      = (Uint16) hNandInfo->hChipInfo[i].pagesPerBlock;
        hNandInfo->numBlocks          = (Uint32) hNandInfo->hChipInfo[i].numBlocks;
        hNandInfo->dataBytesPerPage   = (Uint16) NANDFLASH_PAGESIZE(hNandInfo->hChipInfo[i].bytesPerPage);
        hNandInfo->spareBytesPerPage  = (Uint16) (hNandInfo->hChipInfo[i].bytesPerPage - hNandInfo->dataBytesPerPage);
        break;
      }
      i++;
    }
    
    // If we didn't find the device in the device table OR
    // If we did find the device and it is reportedly greater than 1Gb in size, let's check and use the 4th ID byte
    // This will possibly allow support for 4K-page devices with same device ID as those in table, and bigger than 1 Gb (128 MB) in size    
    if ( 
         (hNandInfo->hChipInfo[i].devID == 0x00) ||
         ( 
           (hNandInfo->dataBytesPerPage > 512) && 
           (((hNandInfo->pagesPerBlock>>4) * hNandInfo->numBlocks * (hNandInfo->dataBytesPerPage>>8)) > (128*1024*1024 >> 12))
         ) 
       )
    {
      // Either 1K, 2K, 4K, or 8K
      hNandInfo->dataBytesPerPage = 0x1 << (10 +(devID[3] & 0x03));   
      
      // Calculates BlockSize/PageSize = pagesPerBlock
      hNandInfo->pagesPerBlock = 0x1 << ( 6 + ((devID[3]>>4) & 0x3) - (devID[3] & 0x3) ); 
      
      // Number of 512 byte blocks per page * spare bytes per 512 block
      j  = 0x1 << ( 3 + ((devID[3]>>2) & 0x1)); // Spare bytes per 512 bytes
      hNandInfo->spareBytesPerPage = (hNandInfo->dataBytesPerPage >> 9) * j;

      // If the device ID is not in the table then assume a value for the
      // total number of blocks. Make sure this matches with the actual NAND device
      hNandInfo->numBlocks = 8192;

      // Check busWidth to make sure it is valid and matches the device's set bus width
      if ((devID[3]>>6) & 0x1)  // Device says it is 16-bit
      {
        if (hNandInfo->busWidth != (Uint8) DEVICE_BUSWIDTH_16BIT)
        {
          return E_FAIL;
        }
      }
      else    // Device says it is 8-bit
      {
        if (hNandInfo->busWidth != (Uint8) DEVICE_BUSWIDTH_8BIT)
        {
          return E_FAIL;
        }
      }
    }

    // Setup row and column address byte-lengths
    hNandInfo->numColAddrBytes = (hNandInfo->dataBytesPerPage > 512)?2:1;
    
    j = 0;
    while( ((hNandInfo->numBlocks * hNandInfo->pagesPerBlock) >> j) > 1) j++;
    hNandInfo->numRowAddrBytes = j >> 3;
    if (j > (hNandInfo->numRowAddrBytes << 3) )
      hNandInfo->numRowAddrBytes++;
  }

  // Assign the number of operations per page value
  hNandInfo->numOpsPerPage = 0;
  while ( (hNandInfo->numOpsPerPage * DEVICE_NAND_MAX_BYTES_PER_OP) < hNandInfo->dataBytesPerPage )
    hNandInfo->numOpsPerPage++;
  
  // Assign the bytes per operation value
  if (hNandInfo->dataBytesPerPage < hNandInfo->hPageLayout->dataRegion.bytesPerOp)
  {
    hNandInfo->dataBytesPerOp = hNandInfo->dataBytesPerPage;
  }
  else
  {
    hNandInfo->dataBytesPerOp = hNandInfo->hPageLayout->dataRegion.bytesPerOp;
  }
  
  // Assign the spare bytes per operation value
  if (hNandInfo->spareBytesPerPage < hNandInfo->hPageLayout->spareRegion.bytesPerOp)
  {
    hNandInfo->spareBytesPerOp = hNandInfo->spareBytesPerPage;
  }
  else
  {
    hNandInfo->spareBytesPerOp = hNandInfo->hPageLayout->spareRegion.bytesPerOp;
  }

  // Check to make sure there are enough spare bytes to satisfy our needs
  if ((hNandInfo->numOpsPerPage * hNandInfo->spareBytesPerOp) > hNandInfo->spareBytesPerPage)
    return E_FAIL;

  // Check and make sure we have enough spare bytes per op
  if (hNandInfo->spareBytesPerOp < DEVICE_NAND_MIN_SPAREBYTES_PER_OP)
    return E_FAIL;
   
  // Assign the large page flag
  hNandInfo->isLargePage = (hNandInfo->dataBytesPerPage > 512)?TRUE:FALSE;

  return E_PASS;
}

static Bool LOCAL_onfiParamPageCRCCheck(Uint8 *paramPageData)
{
  // Bit by bit algorithm without augmented zero bytes 
  const Uint16 polynom = 0x8005;  // Polynomial
  const Uint16 crcmask=0xFFFF, crchighbit=0x8000;
  Uint16 crc = 0x4F4E;    // Initialize the crc shift register with 0x4F4E
  Uint16 i, j, bit;

  for (i =0; i<254; i++) 
  {   
   for (j=0x80; j; j>>=1)
   {
     bit = crc & crchighbit;
     crc <<= 1;
     if (paramPageData[i] & j) 
       bit ^= crchighbit;
     if (bit) crc^= polynom;
   }   
   crc &= crcmask;
  }
  return  (crc == *((Uint16 *)&paramPageData[254]));
}

/***********************************************************
* End file                                                 *
***********************************************************/


