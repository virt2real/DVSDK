/* --------------------------------------------------------------------------
  FILE        : nandwriter.c 				                             	 	        
  PROJECT     : TI Booting and Flashing Utilities
  AUTHOR      : Daniel Allred
  DESC	      : CCS-based utility to flash the DM644x in preparation for 
                NAND booting
 ----------------------------------------------------------------------------- */

// C standard I/O library
#include "stdio.h"

// General type include
#include "tistdtypes.h"

// Device specific CSL
#include "device.h"

// This module's header file 
#include "nandwriter.h"

// NAND driver include
#include "nand.h"
#include "device_nand.h"

// Misc. utility function include
#include "util.h"


/************************************************************
* Explicit External Declarations                            *
************************************************************/

extern __FAR__ Uint32 EMIFStart;


/************************************************************
* Local Macro Declarations                                  *
************************************************************/


/************************************************************
* Local Typedef Declarations                                *
************************************************************/


/************************************************************
* Local Function Declarations                               *
************************************************************/

static Uint32 nandwriter(void);
static Uint32 LOCAL_writeHeaderAndData(NAND_InfoHandle hNandInfo, NANDWRITER_Boot *nandBoot, Uint8 *srcBuf);


/************************************************************
* Global Variable Definitions
************************************************************/

// Global variables for page buffers 
static Uint8* gNandTx;
static Uint8* gNandRx;

/************************************************************
* Global Function Definitions                               *
************************************************************/

void main( void )
{
  int status;

  // Init memory alloc pointer
  UTIL_setCurrMemPtr(0);

  // System init
  if (DEVICE_init() !=E_PASS)
  {
    exit();
  }

  DEVICE_pinmuxControl( 0, DEVICE_PINMUX_EMIF_MASK, DEVICE_PINMUX_EMIF_EN );

	// Execute the NAND flashing
  status = nandwriter();

  if (status != E_PASS)
  {
    DEBUG_printString("\n\nNAND flashing failed!\r\n");
  }
  else
  {
    DEBUG_printString( "\n\nNAND boot preparation was successful!\r\n" );
  }
}


/************************************************************
* Local Function Definitions                                *
************************************************************/

static Uint32 nandwriter()
{
  Uint32 numPagesUBL;
  Uint32 numPagesAPP;

  NANDWRITER_Boot  gNandBoot;
  NAND_InfoHandle  hNandInfo;

  FILE	*fPtr;
  Uint8	*ublPtr, *appPtr;
  Int32	ublFileSize = 0,ublAllocSize = 0, appFileSize = 0,appAllocSize = 0;
  Int8  fileName[256];
  Int8  answer[24];
  Int32 i=0;

  DEBUG_printString("Starting DM644x_NANDWriter.\r\n");

  // Initialize NAND Flash
  hNandInfo = NAND_open((Uint32)&EMIFStart, (Uint8) DEVICE_emifBusWidth() );
  
  if (hNandInfo == NULL)
  {
    DEBUG_printString( "\tERROR: NAND Initialization failed.\r\n" );
    return E_FAIL;
  }

  // Read the file from host
  DEBUG_printString("Enter the binary UBL file Name (enter 'none' to skip) :\r\n");
  DEBUG_readString(fileName);
  fflush(stdin);

  if (strcmp(fileName,"none") != 0)
  {
	// Open an File from the hard drive
	fPtr = fopen(fileName, "rb");
	if(fPtr == NULL)
	{
      DEBUG_printString("\tERROR: File ");
      DEBUG_printString(fileName);
      DEBUG_printString(" open failed.\r\n");
      return E_FAIL;
	}

    // Read file size
    fseek(fPtr,0,SEEK_END);
    ublFileSize = ftell(fPtr);

    if(ublFileSize == 0)
    {
      DEBUG_printString("\tERROR: File read failed.. Closing program.\r\n");
      fclose (fPtr);
      return E_FAIL;
    }

    numPagesUBL = 0;
    while ( (numPagesUBL * hNandInfo->dataBytesPerPage)  < ublFileSize )
    {
      numPagesUBL++;
    }

    //We want to allocate an even number of pages.
    ublAllocSize = numPagesUBL * hNandInfo->dataBytesPerPage;

    // Setup pointer in RAM
    ublPtr = (Uint8 *) UTIL_allocMem(ublAllocSize);


    for (i=0; i<ublAllocSize; i++)
      ublPtr[i]=0x00;

    fseek(fPtr,0,SEEK_SET);

    if (ublFileSize != fread(ublPtr, 1, ublFileSize, fPtr))
    {
      DEBUG_printString("\tWARNING: File Size mismatch.\r\n");
    }

    fclose (fPtr);

    gNandBoot.magicNum    = UBL_MAGIC_SAFE;
    gNandBoot.block       = DEVICE_NAND_RBL_SEARCH_START_BLOCK;
    gNandBoot.page        = 0;
    gNandBoot.numPage     = numPagesUBL;
    gNandBoot.entryPoint  = 0x0100;       // This fixed entry point will work with the UBLs
    gNandBoot.ldAddress   = 0;            // This doesn't matter for the UBL

    if (LOCAL_writeHeaderAndData(hNandInfo,&gNandBoot,ublPtr) != E_PASS)
    {
      printf("\tERROR: Write failed.\r\n");
      return E_FAIL;
    }
  }

  // Read the file from host
  DEBUG_printString("Enter the U-boot or application file name (enter 'none' to skip):\r\n");
  DEBUG_readString(fileName);
  fflush(stdin);

  if (strcmp(fileName,"none") != 0)
  {
    // Open an File from the hard drive
    fPtr = fopen(fileName, "rb");
    if(fPtr == NULL)
    {
      DEBUG_printString("\tERROR: File ");
      DEBUG_printString(fileName);
      DEBUG_printString(" open failed.\r\n");
      return E_FAIL;
    }

    // Read file size
    fseek(fPtr,0,SEEK_END);
    appFileSize = ftell(fPtr);

    if(appFileSize == 0)
    {
      DEBUG_printString("\tERROR: File read failed.. Closing program.\r\n");
      fclose (fPtr);
      return E_FAIL;
    }

    numPagesAPP = 0;
    while ( (numPagesAPP * hNandInfo->dataBytesPerPage)  < (appFileSize) )
    {
      numPagesAPP++;
    }

    // We want to allocate an even number of pages.
    appAllocSize = numPagesAPP * hNandInfo->dataBytesPerPage;
     
    // Setup pointer in RAM
    appPtr = (Uint8 *) UTIL_allocMem(appAllocSize);

    fseek(fPtr,0,SEEK_SET);

    if (appFileSize != fread(appPtr, 1, appFileSize, fPtr))
    {
      DEBUG_printString("\tWARNING: File Size mismatch\n");
    }

    fclose(fPtr);

    // Get the entry point and load addresses
    DEBUG_printString("Enter the U-boot or application entry point (in hex): \n");
    DEBUG_readString(answer);
    gNandBoot.entryPoint = strtoul(answer, NULL, 16);
    fflush(stdin);

    if ( (gNandBoot.entryPoint < DEVICE_DDR2_START_ADDR) || (gNandBoot.entryPoint >= DEVICE_DDR2_END_ADDR) )
    {
      DEBUG_printString("\tWARNING: Entry point not in acceptable range - using default 0x81080000.\r\n");
      gNandBoot.entryPoint = 0x81080000;
    }
    else
    {
      DEBUG_printString("Selected entry point is ");
      DEBUG_printHexInt(gNandBoot.entryPoint);
      DEBUG_printString("\r\n");
    }

    DEBUG_printString("Enter the U-boot or application load address (in hex): \r\n");
    DEBUG_readString(answer);
    gNandBoot.ldAddress = strtoul(answer, NULL, 16);

    if ( (gNandBoot.ldAddress < DEVICE_DDR2_START_ADDR) || (gNandBoot.ldAddress >= DEVICE_DDR2_END_ADDR) )
    {
      DEBUG_printString("\tWARNING: Load address not in acceptable range - using default 0x81080000.\r\n");
      gNandBoot.ldAddress = 0x81080000;
    }

    gNandBoot.magicNum = UBL_MAGIC_BIN_IMG;
    gNandBoot.block = DEVICE_NAND_UBL_SEARCH_START_BLOCK;
    gNandBoot.page = 0;
    gNandBoot.numPage = numPagesAPP;

    if (LOCAL_writeHeaderAndData(hNandInfo, &gNandBoot, appPtr) != E_PASS)
    {
      DEBUG_printString("\tERROR: Write Failed\n");
      return E_FAIL;
    }
  }

  return E_PASS;
}

// Generic function to write a UBL or Application header and the associated data
static Uint32 LOCAL_writeHeaderAndData(NAND_InfoHandle hNandInfo, NANDWRITER_Boot *nandBoot, Uint8 *srcBuf)
{
  Uint32    endBlockNum;
  Uint32    *headerPtr;
  Uint32    blockNum;
  Uint32    count;
  Uint32    countMask;
  Uint32    numBlks;
  Uint32    pageNum;
  Uint32    i;
  Uint8     *dataPtr;


  gNandTx = (Uint8 *) UTIL_allocMem(NAND_MAX_PAGE_SIZE);
  gNandRx = (Uint8 *) UTIL_allocMem(NAND_MAX_PAGE_SIZE);

  for (i=0; i<NAND_MAX_PAGE_SIZE; i++)  
  {
    gNandTx[i]=0xff;
    gNandRx[i]=0xff;
  }  
  
  // Get total number of blocks needed
  numBlks = 0;
  while ( (numBlks * hNandInfo->pagesPerBlock)  < (nandBoot->numPage + 1) )
  {
    numBlks++;
  }
  DEBUG_printString("Number of blocks needed for header and data: ");
  DEBUG_printHexInt(numBlks);
  DEBUG_printString("\r\n");

  // Check whether writing UBL or APP (based on destination block)
  blockNum = nandBoot->block;
  if (blockNum == DEVICE_NAND_RBL_SEARCH_START_BLOCK)
  {
    endBlockNum = DEVICE_NAND_RBL_SEARCH_END_BLOCK;
  }
  else if (blockNum == DEVICE_NAND_UBL_SEARCH_START_BLOCK)
  {
    endBlockNum = DEVICE_NAND_UBL_SEARCH_END_BLOCK;
  }
  else
  {
    // Block number is out of range
    return E_FAIL; 
  }

NAND_WRITE_RETRY:
  if (blockNum > endBlockNum)
  {
    return E_FAIL;
  }
  DEBUG_printString("Attempting to start write in block number ");
  DEBUG_printHexInt(blockNum);
  DEBUG_printString(".\r\n");

  // Unprotect all needed blocks of the Flash 
  if (NAND_unProtectBlocks(hNandInfo,blockNum,numBlks) != E_PASS)
  {
    blockNum++;
    DEBUG_printString("Unprotect failed.\r\n");
    goto NAND_WRITE_RETRY;
  }
  
  // Setup header to be written
  headerPtr = (Uint32 *) gNandTx;
  headerPtr[0] = nandBoot->magicNum;          //Magic Number
  headerPtr[1] = nandBoot->entryPoint;        //Entry Point
  headerPtr[2] = nandBoot->numPage;           //Number of Pages
  headerPtr[3] = blockNum;                    //Starting Block Number 
  headerPtr[4] = 1;                           //Starting Page Number - always start data in page 1 (this header goes in page 0)

  if ( (blockNum>=DEVICE_NAND_RBL_SEARCH_START_BLOCK) &&  (blockNum <= DEVICE_NAND_RBL_SEARCH_END_BLOCK) )
  {
    headerPtr[5] = 0;                           //nandBoot->ldAddress;  
  }
  else if ( (blockNum>=DEVICE_NAND_UBL_SEARCH_START_BLOCK) &&  (blockNum<=DEVICE_NAND_UBL_SEARCH_END_BLOCK) )
  {
    headerPtr[5] = nandBoot->ldAddress;         //nandBoot->ldAddress;
  }
  else
  {
    // Block number is out of range
    return E_FAIL; 
  }
  pageNum = 0;
    
  // Erase the block where the header goes and the data starts
  if (NAND_eraseBlocks(hNandInfo,blockNum,numBlks) != E_PASS)
  {
    blockNum++;
    DEBUG_printString("Erase failed\n");
    goto NAND_WRITE_RETRY;
  }

  DEBUG_printString("Writing header data to Block ");
  DEBUG_printHexInt(blockNum);
  DEBUG_printString(", Page ");
  DEBUG_printHexInt(pageNum);
  DEBUG_printString("\r\n");

  if (NAND_writePage(hNandInfo, blockNum, pageNum, gNandTx) != E_PASS)
  {
    blockNum++;
    DEBUG_printString("Write failed\n");
    NAND_reset(hNandInfo);
    goto NAND_WRITE_RETRY;
  }
    
  UTIL_waitLoop(200);

  // Verify the page just written
  if (NAND_verifyPage(hNandInfo, blockNum, pageNum, gNandTx, gNandRx) != E_PASS)
  {
    DEBUG_printString("Verify failed. Attempting to clear page\n");
    NAND_reset(hNandInfo);
    NAND_eraseBlocks(hNandInfo,blockNum,numBlks);
    
    blockNum++;
    NAND_reset(hNandInfo);

    goto NAND_WRITE_RETRY;
  }

  // Start writing in page 1 of current block (header was in page 0)
  count = 1;

  // The following assumes power of 2 pagesPerBlock -  *should* always be valid 
  countMask = (Uint32) hNandInfo->pagesPerBlock - 1;
  dataPtr = srcBuf;

  do
  {
    DEBUG_printString((Uint8 *)"Writing image data to Block ");
    DEBUG_printHexInt(blockNum);
    DEBUG_printString((Uint8 *)", Page ");
    DEBUG_printHexInt(count & countMask);
    DEBUG_printString((Uint8 *)"\r\n");

    // Write the UBL or APP data on a per page basis
    if (NAND_writePage(hNandInfo, blockNum,  (count & countMask), dataPtr) != E_PASS)
    {
      blockNum++;
      DEBUG_printString("Write failed\n");
      goto NAND_WRITE_RETRY;
    }
    
    UTIL_waitLoop(200);
    
    // Verify the page just written
    if (NAND_verifyPage(hNandInfo, blockNum, (count & countMask), dataPtr, gNandRx) != E_PASS)
    {
      DEBUG_printString("Verify failed. Attempting to clear page\n");
      NAND_reset(hNandInfo);
      NAND_eraseBlocks(hNandInfo,blockNum,numBlks);
      blockNum++;
      goto NAND_WRITE_RETRY;
    }
    
    count++;
    dataPtr +=  hNandInfo->dataBytesPerPage;
    if (!(count & countMask))
    {
      do
      {
        blockNum++;
      }
      while (NAND_badBlockCheck(hNandInfo,blockNum) != E_PASS);
    }
  } while (count <= nandBoot->numPage);

  NAND_protectBlocks(hNandInfo);

  return E_PASS;
}


/***********************************************************
* End file                                                 *
***********************************************************/

/* --------------------------------------------------------------------------
  HISTORY
    v1.00 - DJA - 02-Nov-2007
      Initial release
-------------------------------------------------------------------------- */

