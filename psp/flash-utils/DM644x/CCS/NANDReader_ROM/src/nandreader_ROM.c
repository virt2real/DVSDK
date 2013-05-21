/* --------------------------------------------------------------------------
  FILE        : nandreader_ROM.c
  PROJECT     : TI Booting and Flashing Utilities
  AUTHOR      : Daniel Allred
  DESC	      : CCS-based utility to read the NAND as the ROM does
 ----------------------------------------------------------------------------- */

// C standard I/O library
#include "stdio.h"

// General type include
#include "tistdtypes.h"

// Device specific CSL
#include "device.h"

// This module's header file 
#include "nandreader_ROM.h"

// NAND driver include
#include "nand.h"
#include "device_nand.h"
#include "nand_ROM.h"

// Misc. utility function include
#include "util.h"


/************************************************************
* Explicit External Declarations                            *
************************************************************/

extern __FAR__ Uint32 EMIFStart;
extern __FAR__ Uint32 DDRStart;

extern __FAR__ NAND_INFO gNandInfo;

/************************************************************
* Local Macro Declarations                                  *
************************************************************/


/************************************************************
* Local Typedef Declarations                                *
************************************************************/


/************************************************************
* Local Function Declarations                               *
************************************************************/

static Uint32 nandreader_ROM(void);
#if (0)
static Uint32 LOCAL_readHeaderAndData(NAND_InfoHandle hNandInfo, NANDWRITER_Boot *nandBoot, Uint8 *srcBuf);
static Uint32 LOCAL_NAND_verifyPage(Uint8 *writeBuf, Uint8 *readBuf, Uint32 numBytes);
#endif


/************************************************************
* Global Variable Definitions
************************************************************/

// Global variables for page buffers 
#pragma DATA_SECTION(gNandTx,".nandbuff");
static Uint8 gNandTx[4096];
#pragma DATA_SECTION(gNandRx,".nandbuff");
static Uint8 gNandRx[4096];

static NAND_InfoObj gMyNandInfo;

Uint32 gDMA = 0;


/************************************************************
* Global Function Definitions                               *
************************************************************/

void main( void )
{
  int status;

  // System init
  if (DEVICE_init() != E_PASS)
  {
    return;
  }

  // Set PLL to 27 MHz
//  DEVICE_PLL1Init(1);

  DEVICE_pinmuxControl( 0, DEVICE_PINMUX_EMIF_MASK, DEVICE_PINMUX_EMIF_EN );

	// Execute the NAND flashing
  status = nandreader_ROM();

  if (status != E_PASS)
  {
    DEBUG_printString("\n\nNAND reading failed!\r\n");
  }
  else
  {
    DEBUG_printString( "\n\nNAND reading was successful!\r\n" );
  }
}


/************************************************************
* Local Function Definitions                                *
************************************************************/

static Uint32 nandreader_ROM()
{

#if (1)
  Uint32 i,j, status;
  NAND_InfoHandle  hNandInfo = &gMyNandInfo;
#else
  Uint32 numPagesUBL;
  Uint32 numPagesAPP;

  Uint32 status;

  NANDWRITER_Boot  gNandBoot;
  NAND_InfoHandle  hNandInfo = &gMyNandInfo;

  FILE	*fPtr;
  Uint8	*ublPtr, *appPtr;
  Int32	ublFileSize = 0,ublAllocSize = 0, appFileSize = 0,appAllocSize = 0;
  Int8  fileName[256];
  Int8  answer[24];
#endif

  DEBUG_printString("Starting NANDReader_ROM.\r\n");

  // Initialize NAND Flash (ROM init routine)
  status = NANDInit();
  
  if (status != E_PASS)
  {
    DEBUG_printString( "\tERROR: NAND Initialization failed.\r\n" );
    return E_FAIL;
  }

  hNandInfo->dataBytesPerPage = NANDFLASH_PAGESIZE(gNandInfo.page_size);
  hNandInfo->CSOffset = 0;
  hNandInfo->busWidth = (gNandInfo.nand_width==0)?BUS_8BIT:BUS_16BIT;
  hNandInfo->dataBytesPerOp = 512;
  hNandInfo->devID = gNandInfo.dev_code;
  hNandInfo->flashBase = 0x02000000;
  hNandInfo->spareBytesPerOp = 16;
  hNandInfo->pagesPerBlock = 0x1 << (gNandInfo.blk_shift - gNandInfo.page_shift);
  hNandInfo->isLargePage = gNandInfo.big_block;
  hNandInfo->numColAddrBytes = gNandInfo.page_shift >> 3;
  hNandInfo->numRowAddrBytes = gNandInfo.addr_cycles - hNandInfo->numColAddrBytes;

#if (0)
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
    while ( (numPagesUBL *  hNandInfo->dataBytesPerPage)  < ublFileSize )
    {
      numPagesUBL++;
    }

    //We want to allocate an even number of pages.
    ublAllocSize = numPagesUBL *  hNandInfo->dataBytesPerPage;

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

    if (LOCAL_readHeaderAndData(hNandInfo,&gNandBoot,ublPtr) != E_PASS)
    {
      printf("\tERROR: Read failed.\r\n");
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

    if (LOCAL_readHeaderAndData(hNandInfo, &gNandBoot, appPtr) != E_PASS)
    {
      DEBUG_printString("\tERROR: Write Failed\n");
      return E_FAIL;
    }
  }
#else
  for (i = 1; i <= 5; i++)
  { 
    for (j=0; j < hNandInfo->pagesPerBlock; j++)
    {

      DEBUG_printString("Block ");
      DEBUG_printHexInt(i);
      DEBUG_printString(", Page ");
      DEBUG_printHexInt(j);

      if (NANDReadPage(i,j,gNandRx) != E_PASS)
      {
        DEBUG_printString("\r\n\tRead failed\r\n");
        break;
      }

      DEBUG_printString("\r\n\t1st Word = ");
      DEBUG_printHexInt(((Uint32 *)gNandRx)[0]);
      DEBUG_printString("\r\n\t2nd Word = ");
      DEBUG_printHexInt(((Uint32 *)gNandRx)[1]);
      DEBUG_printString("\r\n\t3rd Word = ");
      DEBUG_printHexInt(((Uint32 *)gNandRx)[2]);
      DEBUG_printString("\r\n\t4th Word = ");
      DEBUG_printHexInt(((Uint32 *)gNandRx)[3]);
      DEBUG_printString("\r\n");
    }
  }
#endif

  return E_PASS;
}

#if (0)
// Generic function to write a UBL or Application header and the associated data
static Uint32 LOCAL_readHeaderAndData(NAND_InfoHandle hNandInfo, NANDWRITER_Boot *nandBoot, Uint8 *srcBuf)
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

  // Clear buffers
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

NAND_READ_RETRY:
  if (blockNum > endBlockNum)
  {
    return E_FAIL;
  }
  DEBUG_printString("Attempting to start read in block number ");
  DEBUG_printHexInt(blockNum);
  DEBUG_printString(".\r\n");
 
  // Setup header to be read
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
    
  DEBUG_printString("Reading header data from Block ");
  DEBUG_printHexInt(blockNum);
  DEBUG_printString(", Page ");
  DEBUG_printHexInt(pageNum);
  DEBUG_printString("\r\n");

  if (NANDReadPage(blockNum,pageNum,gNandRx) != E_PASS)
  {
    blockNum++;
    DEBUG_printString("Read failed\n");
    goto NAND_READ_RETRY;
  }
    
  UTIL_waitLoop(200);

  // Verify the page just written
  if (LOCAL_NAND_verifyPage(gNandTx, gNandRx, sizeof(NANDWRITER_Boot)) != E_PASS)
  {
    blockNum++;
    DEBUG_printString("Verify failed. Attempting to clear page\n");
    goto NAND_READ_RETRY;
  }

  // Start writing in page 1 of current block (header was in page 0)
  count = 1;

  // The following assumes power of 2 pagesPerBlock -  *should* always be valid 
  countMask = (Uint32) hNandInfo->pagesPerBlock - 1;
  dataPtr = srcBuf;

  do
  {
    DEBUG_printString((Uint8 *)"Reading image data from Block ");
    DEBUG_printHexInt(blockNum);
    DEBUG_printString((Uint8 *)", Page ");
    DEBUG_printHexInt(count & countMask);
    DEBUG_printString((Uint8 *)"\r\n");

    // Write the UBL or APP data on a per page basis
    if (NANDReadPage(blockNum,pageNum,gNandRx) != E_PASS)
    {
      blockNum++;
      DEBUG_printString("Read failed\n");
      goto NAND_READ_RETRY;
    }

    UTIL_waitLoop(200);
    
    // Verify the page just written
    if (LOCAL_NAND_verifyPage(gNandTx, gNandRx, hNandInfo->dataBytesPerPage) != E_PASS)
    {
      blockNum++;
      DEBUG_printString("Verify failed. Attempting to clear page\n");
      goto NAND_READ_RETRY;
    }
    
    count++;
    dataPtr +=  hNandInfo->dataBytesPerPage;
    if (!(count & countMask))
    {
      blockNum++;
    }
  } while (count <= nandBoot->numPage);

  return E_PASS;
}

static Uint32 LOCAL_NAND_verifyPage(Uint8 *writeBuf, Uint8 *readBuf, Uint32 numBytes)
{
  Uint32 i = 0;
  for (i=0; i<numBytes; i++)
  {  
    if (writeBuf[i] != readBuf[i])
    {
      DEBUG_printString("Data Verify failed!");
      return E_FAIL;
    }
  }
  return E_PASS;
}

#endif

/***********************************************************
* End file                                                 *
***********************************************************/

/* --------------------------------------------------------------------------
  HISTORY
    v1.00 - DJA - 02-Nov-2007
      Initial release
-------------------------------------------------------------------------- */

