/* --------------------------------------------------------------------------
  FILE      : sdmmc.c
  PROJECT   : TI Boot and Flash Utilities
  AUTHOR    : Daniel Allred
  DESC      : Generic SDMMC memory driver
-------------------------------------------------------------------------- */

// General type include
#include "tistdtypes.h"

// Device specific CSL
#include "device.h"

// Util functions
#include "util.h"

// The generic SD/MMC module driver 
#include "sdmmc.h"


/************************************************************
* Explicit External Declarations                            *
************************************************************/


/************************************************************
* Local Macro Declarations                                  *
************************************************************/


/************************************************************
* Local Function Declarations                               *
************************************************************/
static Uint8 Local_SDMMCInitCard(SDMMC_InfoHandle hSDMMCInfo);

/************************************************************
* Local Variable Definitions                                *
************************************************************/

#define SD_HIGH_CAPACITY_CARD

/************************************************************
* Global Variable Definitions                               *
************************************************************/

#ifdef USE_IN_ROM
SDMMC_InfoObj gSDMMCInfo;
#endif
// Default SPI Config strcuture
const SDMMC_ConfigObj DEFAULT_SDMMC_CONFIG = 
{
SDMMC_LITTLE_ENDIAN,
SDMMC_LITTLE_ENDIAN,
SDMMC_DAT3_EDGE_DETECT_DISABLE,
(Uint8)FALSE,
(Uint8)FALSE,
(Uint8)FALSE,
(Uint8)0,
SDMMC_MODE_NATIVE, /* No SPI */
(Uint8)FALSE, /* Valid Only in SPI mode */
(Uint8)FALSE, /* Valid Only in SPI mode */
SDMMC_4BIT_DATABUS,
(Uint16)0xFF,
0xFFFF,
SDMMC_FIFO_LEVEL_32BYTES
};

SDMMC_ConfigHandle const hDEFAULT_SDMMC_CONFIG = (SDMMC_ConfigHandle) &DEFAULT_SDMMC_CONFIG;
#define SDMMC_BLOCK_LENGTH     (512)

/************************************************************
* Global Function Definitions                               *
************************************************************/

// Initialze SDMMC interface and find the details of the SD/MMC card used
SDMMC_InfoHandle SDMMC_open(Uint32 sdmmcPeripheralNum, SDMMC_ConfigHandle hSDMMCCfg)
{
  SDMMC_InfoHandle hSDMMCInfo;
  Uint32 localDataBytesPerBlk = 0;

  // Set SDMMCInfo handle
#ifdef USE_IN_ROM
  hSDMMCInfo = (SDMMC_InfoHandle) &gSDMMCInfo;
#else
  hSDMMCInfo = (SDMMC_InfoHandle) UTIL_allocMem(sizeof(SDMMC_InfoObj));
#endif

  if (hSDMMCCfg == NULL)
  {
    hSDMMCInfo->hSDMMCCfg = hDEFAULT_SDMMC_CONFIG;
  }
  else
  {
    hSDMMCInfo->hSDMMCCfg = hSDMMCCfg;
  }
  hSDMMCInfo->dataBytesPerBlk = SDMMC_BLOCK_LENGTH;

  localDataBytesPerBlk = hSDMMCInfo->dataBytesPerBlk;
  hSDMMCInfo->dataBytesPerBlkPower2 = 0;
  while(localDataBytesPerBlk > 1)
  {
    localDataBytesPerBlk >>= 1;
	hSDMMCInfo->dataBytesPerBlkPower2++;
  }
  // Open SDMMC peripheral
  Local_SDMMCInitCard(hSDMMCInfo);  

  return hSDMMCInfo;
}




// Defining this macro for the build will cause write (flash) ability to be removed
// This can be used for using this driver as read-only for ROM code
#ifndef USE_IN_ROM    

// Global Erase NOR Flash
Uint32 SDMMC_globalErase(SDMMC_InfoHandle hSDMMCInfo)
{
  return E_PASS;
}

// NAND Flash erase block function
Uint32 SDMMC_eraseBytes(SDMMC_InfoHandle hSDMMCInfo, Uint32 startAddr, Uint32 byteCnt)
{  
  return E_PASS;
}
#endif

/************************************************************
* Local Function Definitions                                *
************************************************************/

void SDMMCClearResponse() {
  SDMMC->MMCRSP01 = 0x0;
  SDMMC->MMCRSP23 = 0x0;
  SDMMC->MMCRSP45 = 0x0;
  SDMMC->MMCRSP67 = 0x0;
  SDMMC->MMCCIDX &= 0xFFC0;
}

/**
    Send Command to MMC/ SD

    command  Command to be sent to MMC/ SD
    argument  Arguments to be sent with the command
    checkStatus  0: no status check, 1: status check
	statusBits  status bits to be checked in MMCST0 register, if 'checkStatus' = 1

    E_PASS, on completion
*/
Uint8 SDMMCSendCmd(Uint32 command, Uint32 argument, Bool checkStatus) {
  
	Uint32 statusRegBits=0x0;
	volatile Uint32 dummyread;

	// Dummy read
	dummyread = SDMMC->MMCST0;

   	/* Clear Response Registers*/
   	SDMMCClearResponse();


   	//Setup the Argument Register and send CMD */
   	SDMMC->MMCARGHL = argument;
   	SDMMC->MMCCMD   = command;
  
   	/*Delay loop allowing cards to respond */
	UTIL_waitLoop(1000);
        
   	if (checkStatus == 1) {
	   	/* Wait for RspDne; exit on RspTimeOut or RspCRCErr
		   bit 2 - RSPDNE
		   bit 3 - 7 Error/timeout */
	   	while((statusRegBits & (0x00FC)) == 0 )
	    {
	     statusRegBits = SDMMC->MMCST0;
	    }

	    return( ((statusRegBits & 0x4) == 0x4) ? E_PASS : E_DEVICE );
	}

	return E_PASS;
}


/**
    Get Response from MMC/SD controller and Clear Response

    SDMMCResponse Command Response is received in this parameter

    if success, \c E_PASS, else error code

*/
Uint8 SDMMCGetResponse(SDMMC_ResponseData* sdMmcResponse) {

  sdMmcResponse->response[0] = (SDMMC->MMCRSP01 & 0xFFFF); 
  sdMmcResponse->response[1] = (SDMMC->MMCRSP01 & 0xFFFF0000) >> 16;
  sdMmcResponse->response[2] = (SDMMC->MMCRSP23 & 0xFFFF); 
  sdMmcResponse->response[3] = (SDMMC->MMCRSP23 & 0xFFFF0000) >> 16;
  sdMmcResponse->response[4] = (SDMMC->MMCRSP45 & 0xFFFF); 
  sdMmcResponse->response[5] = (SDMMC->MMCRSP45 & 0xFFFF0000) >> 16;
  sdMmcResponse->response[6] = (SDMMC->MMCRSP67 & 0xFFFF); 
  sdMmcResponse->response[7] = (SDMMC->MMCRSP67 & 0xFFFF0000) >> 16;
  sdMmcResponse->commandIdk  = (SDMMC->MMCCIDX  & 0x003F);
	
  SDMMCClearResponse();

  return E_PASS;
}


Uint8 SDMMC_Send_Op_Cmd(Uint32 Arg)
{
	Uint8 status;

   UTIL_waitLoop(100000);  				
   
   status = SDMMCSendCmd( SDMMC_APP_CMD,0,TRUE);

   UTIL_waitLoop(100000);  				

   status = SDMMCSendCmd( SD_APP_OP_COND, Arg, TRUE);

   return status;
}

Uint8 SDMMC_Identify_Card(Bool *CardType, SDMMC_InfoHandle hSDMMCInfo)
{
	Uint8 status;
	Uint32 temp;
	Bool mmc;
	Uint32 opTimeOut;
	Bool HCS_flag = 0;
		
	/* CMD8 is accepted by both MMC and SD cards */
	status = SDMMCSendCmd( SDMMC_HICAP_CMD,(0x100 | SD_HIGH_CAPACITY_ECHO_PATTERN),TRUE);
	temp = (SDMMC->MMCRSP67 & 0x000000FF);

	if(temp == SD_HIGH_CAPACITY_ECHO_PATTERN)
		HCS_flag = 1;

	/*  MMC card will not respond to this command ACMD41 */
	status = SDMMC_Send_Op_Cmd(HCS_flag << 30 | SDMMC_VDD_27_36);

	if(status != E_PASS)
		mmc = TRUE;
	else 
		mmc = FALSE;

	opTimeOut = SDMMC_OP_TIMEOUT;
	do{ 
		if(mmc == TRUE)
			/* Send command 1 with 30th [High capacity] bit set to 1 */
			status = SDMMCSendCmd( MMC_SEND_OP_COND, (0x40000000 | SDMMC_VDD_27_36), TRUE);
		else
			/* In case of High Capacity cards ,this bit should be set .The  CCS bit in the
			 * response determines if the High cpacity or not
			 */
			SDMMC_Send_Op_Cmd(HCS_flag << 30 | SDMMC_VDD_27_36);
		temp = (SDMMC->MMCRSP67 & 0xC0000000);
		opTimeOut--;
	
	} while ( ((opTimeOut > 0)  && ((temp & 0x80000000) == 0)) );

	if(temp & 0x40000000) {
		hSDMMCInfo->mmcSdCSDRegInfo.sdHighCapacityCard = 1;
	} else {
		hSDMMCInfo->mmcSdCSDRegInfo.sdHighCapacityCard = 0;

	}
    
	*CardType = mmc;

	if(opTimeOut == 0)
		return  E_FAIL;

	return E_PASS;
		
}

Uint8 SDMMC_Select_Card(SDMMC_InfoHandle hSDMMCInfo)
{
	SDMMC_cardStatusReg cardStatus;
	Uint8 status;

	if(!hSDMMCInfo)
		return E_FAIL;

	/* Select the Card which responded */
   /*  the rca value is sent as the upper 16 bits of the command argument  */
	status = SDMMCSendCmd( SDMMC_SELECT_CARD, hSDMMCInfo->relCardAddress<<16, TRUE);
   
	if( status == E_PASS ) {
		/* no timeout */
		if ( (hSDMMCInfo->relCardAddress) > 0 ) {
			/*  the rca value is sent as the upper 16 bits of the command argument  */
	  	 	status = SDMMCSendCmd( SDMMC_SEND_STATUS, (hSDMMCInfo->relCardAddress)<<16, TRUE);
   		    if( status == E_PASS ) {
				SDMMCGetResponse(&(hSDMMCInfo->sdMmcResponse));
		    	/* Response expected: R1 in native mode*/
			    cardStatus.currentState = (SDMMC_CardStates) ( (hSDMMCInfo->sdMmcResponse.response[6] >> 9) & 0xf );
                if( (cardStatus.currentState != SDMMC_CARD_STATE_TRAN) && (cardStatus.currentState != SDMMC_CARD_STATE_PRG ) ) 
                	return ( E_FAIL );
           	}
        }
   } 

   return status;
}

Uint8 SDMMC_Read_CSD(SDMMC_InfoHandle hSDMMCInfo)
{

	Uint8 status;
	Uint8 i;
	Uint16 cardReg[8];
	
	if(!hSDMMCInfo)
		return E_FAIL;
		
   /* Send Status may be required at this point */
   
   /* Read the CSD structure for MMC/SD */
   status = SDMMCSendCmd( SDMMC_SEND_CSD, hSDMMCInfo->relCardAddress<<16, TRUE);

   if( status == E_PASS ) {
    	/* Check whether the mode of operation is native MMC/SD or SPI */
   		SDMMCGetResponse(&(hSDMMCInfo->sdMmcResponse));

	    /* Read CSD from response R2 */
	    for( i=0; i<8; i++ ){
	  	  cardReg[i] = hSDMMCInfo->sdMmcResponse.response[i];
		}
	  	
    	// Fill the local structure with information required for other commands used in the driver
		hSDMMCInfo->mmcSdCSDRegInfo.permWriteProtect =  (cardReg[0]>>13) & 0x1;
		hSDMMCInfo->mmcSdCSDRegInfo.tmpWriteProtect =  (cardReg[0]>>12) & 0x1;
		hSDMMCInfo->mmcSdCSDRegInfo.writeBlkPartial =  (cardReg[1]>>5) & 0x1;
		hSDMMCInfo->mmcSdCSDRegInfo.writeBlkLenBytes =  1<<((cardReg[1]>>6) & 0xF);
    	hSDMMCInfo->mmcSdCSDRegInfo.wpGrpEnable = (cardReg[1]>>15) & 0x1;
    	hSDMMCInfo->mmcSdCSDRegInfo.wpGrpSize = (cardReg[2] & 0x7F) + 1;           ///> Extracting 7 bits: For MMC - 5 bits reqd; For SD - 7 bits reqd. (have to be taken care by user)
		hSDMMCInfo->mmcSdCSDRegInfo.dsrImp = (cardReg[4]>>12) &0x1;
		hSDMMCInfo->mmcSdCSDRegInfo.readBlkMisalign = (cardReg[4]>>13) &0x1;
		hSDMMCInfo->mmcSdCSDRegInfo.writeBlkMisalign = (cardReg[4]>>14) &0x1;
		hSDMMCInfo->mmcSdCSDRegInfo.readBlkPartial =  (cardReg[4]>>15) & 0x1;
		hSDMMCInfo->mmcSdCSDRegInfo.readBlkLenBytes =  1<<(cardReg[5] & 0xF);
    	hSDMMCInfo->mmcSdCSDRegInfo.sysSpecVersion = (cardReg[7]>>10) & 0xF;    ///> These bits are reserved in the case of SD card
   } 

   return status;
}
   
Uint8 SDMMC_Set_BusWidth(Uint32 rca)
{
	Uint8 status;
	Uint32 opTimeOut = SDMMC_OP_TIMEOUT;

	do{
			/* Send CMD55 */
			status = SDMMCSendCmd( SDMMC_APP_CMD, rca << 16, TRUE);
		    if ( status != E_PASS )
				return ( E_FAIL );

			status = SDMMCSendCmd( SD_SET_BUS_WIDTH, 2, TRUE);

		} while( (status != E_PASS) && opTimeOut-- );
		 
		return status;
}

/**
	MMC/SD interface selection, Controller and Card Initialization

*/
static Uint8 Local_SDMMCInitCard(SDMMC_InfoHandle hSDMMCInfo) {
	Bool mmc = TRUE;
	Uint8 status;

	hSDMMCInfo->mmcSdCSDRegInfo.sdHighCapacityCard = 0;
	SDMMC->MMCCLK =0x01B;
    SDMMC->MMCFIFOCTL |= ((Uint16)hSDMMCInfo->hSDMMCCfg->fifoThreshold) << 2; //0x0004;
   	
   	SDMMC->MMCCTL = 0x0003;
	UTIL_waitLoop(500000);
	SDMMC->MMCCTL |= ((Uint16)hSDMMCInfo->hSDMMCCfg->busWidth) << 2;
	SDMMC->MMCCTL &= ~0x0003;

    /* Max timeout set*/
	SDMMC->MMCTOR = (Uint16)hSDMMCInfo->hSDMMCCfg->timeoutResponse;// 0xFF;
    SDMMC->MMCTOD = (Uint16)hSDMMCInfo->hSDMMCCfg->timeoutRead; // 0xFFFF
   
   /* Place all cards in idle state */
	status = SDMMCSendCmd( (0x4000 | SDMMC_GO_IDLE_STATE), SDMMC_STUFF_BITS, FALSE);
	if( status != E_PASS )
		return ( status );
    
	UTIL_waitLoop(1000000); 

	/* Identify the card type and also check whether it is mmc or SD */
	status = SDMMC_Identify_Card(&mmc, hSDMMCInfo);
		 				
    if(status == E_FAIL)
		return  status;

   //cardStatus.multiMediaCard = (Bool)mmc;
        
	UTIL_waitLoop(100000); 
         
   /* Ask all cards to send their CIDs */
   status = SDMMCSendCmd( SDMMC_ALL_SEND_CID, SDMMC_STUFF_BITS, TRUE);
   if( status != E_PASS )
   		return ( status );

   SDMMCGetResponse(&(hSDMMCInfo->sdMmcResponse));
   
   if( mmc == TRUE ){
		/* Set Relative Address for the card. As we are using only one card
		currently setting the card rca to  MMC_CARD_ID = 2
		We cannot use 1 because that is the default for all the SanDisk cards
		*/
		hSDMMCInfo->relCardAddress = 2;

		status = SDMMCSendCmd( MMC_SET_RELATIVE_ADDR, hSDMMCInfo->relCardAddress<<16, TRUE);

	  	if( status!= E_PASS )
			return E_FAIL;
	} else {
		
		/* Read Relative Address from the card and store it in variable rca */
		 status = SDMMCSendCmd( SD_SEND_RELATIVE_ADDR, SDMMC_STUFF_BITS, TRUE);

	  	if( status == E_PASS ) {
        	hSDMMCInfo->relCardAddress = (SDMMC->MMCRSP67 & 0xFFFF0000) >> 16;
      	} else {
			return ( E_FAIL );
		}
   }
   
     /* Read the CSD structure for MMC/SD */
   	status = SDMMC_Read_CSD(hSDMMCInfo);
	if(status == E_FAIL)
		return  status;
      
	status = SDMMC_Select_Card(hSDMMCInfo);	
	if(status == E_FAIL)
		return  status;
   
	if(mmc == FALSE) {
		SDMMC_Set_BusWidth(hSDMMCInfo->relCardAddress);
		/* bit no.2 to 1 for 4 bit bus width */
	  	SDMMC->MMCCTL |= 0x4;
	} else {
   		SDMMC->MMCCTL &= 0xFFFFFFFB;
	}
	return status;
}


/**
    Read N words from the MMC Controller Register

    data     -  Buffer for storing read data from the MMC
    numWords -  Number of words to be read from the MMC

*/
Uint8 SDMMCReadNWords(Uint32 *data, Uint32 numofBytes) 
{
  Uint16 i=0,j=0;
  Uint32 status;
  Uint32 fifoReadItrCount=0;          /* Word counter */
  fifoReadItrCount= numofBytes >> 5;

  for(i=0; i < fifoReadItrCount/2;i++)
  {			 	      
  	if(i != (fifoReadItrCount -1))
	{
	    
		// wait for DRRDY timeout
		do {
               status=SDMMC->MMCST0;
               if (status & 0xf8)
                   return (E_FAIL);
         } while(! (status & 0x0400) );	
	}
     
	for(j=0;j < 16; j++)
		*data++ = SDMMC->MMCDRR;
  }
  return ( E_PASS );
}

/**
    Send command to read a single block of data from the MMC/SD card

    cardAddr  Address of the location on the card to be read (should be a multiple of )
    dest  Buffer to read data into, from MMC/SD card
	blkLength  Size of the block in bytes, to be read from MMC/SD card

*/
Uint8 SDMMCSingleBlkRead( SDMMC_InfoHandle hSDMMCInfo, Uint32 cardMemAddr, Uint32 *dest, Uint32 blkLength ) 
{
  Uint8 status;
  Uint32 timeOut;

  /*Set the FIFO level 32 bytes (256 bit) always */
  SDMMC->MMCFIFOCTL |= 0x0004;
 
  status = SDMMCSendCmd(SDMMC_SET_BLOCKLEN, blkLength, FALSE);
  if(status != E_PASS)
  	return	E_FAIL;
      
  SDMMCClearResponse();

  UTIL_waitLoop(100000);
    /* Set the blocklength and size of the block in bytes */
  if(blkLength == 0)
    return E_FAIL;

  SDMMC->MMCBLEN |= (Uint16)(blkLength&0xFFF);
  SDMMC->MMCNBLK =  1;

    /* reset the FIFO  */
  SDMMC->MMCFIFOCTL |= 0x1;

  /* Set the Transfer direction from the FIFO as receive*/
  SDMMC->MMCFIFOCTL &= 0xFFFD;

  /*Send read single Block Command */       
  if(hSDMMCInfo->mmcSdCSDRegInfo.sdHighCapacityCard)
    status = SDMMCSendCmd(0x2000 | SDMMC_READ_SINGLE_BLOCK, cardMemAddr >> hSDMMCInfo->dataBytesPerBlkPower2, FALSE);
  else
    status = SDMMCSendCmd(0x2000 | SDMMC_READ_SINGLE_BLOCK, cardMemAddr, FALSE);

  if(status != E_PASS)
	return E_FAIL;
		   		
  status=SDMMCReadNWords((Uint32*)dest, blkLength);
  if(status !=E_PASS)
	 return E_FAIL; 

  UTIL_waitLoop(100); 

  /*Delay needed for safety */
  timeOut = 3000;
  do {
	if(SDMMC->MMCST0 & SDMMC_STAT0_DATDNE) {
		return E_PASS;	
	}
	timeOut--;
	if( timeOut == 0 ) 
		return E_TIMEOUT;
  } while(1);

}
/**
    Send command to read multiple blocks of data from the MMC/SD card

    cardAddr  - Address of the location on the card to be read (should be a multiple of )
    dest      - Buffer to read data into, from MMC/SD card
	dataLength - Number of bytes to be read
*/
Uint8 SDMMCMultipleBlkRead( SDMMC_InfoHandle hSDMMCInfo, Uint32 cardMemAddr, Uint32 *dest, Uint32 dataLength) 
{
  Uint8 status, retVal;
  Uint32 numBlks;
  volatile Uint32 timeOut;

  retVal = E_PASS;

  /*Set the FIFO level 32 bytes (256 bit) always */
  SDMMC->MMCFIFOCTL |= 0x0004;
  status = SDMMCSendCmd(SDMMC_SET_BLOCKLEN, 512, FALSE);
  if(status != E_PASS)
  	return	E_FAIL;
     
  /* Clear all the response registers */
  SDMMCClearResponse();

  /* To find the Number of blocks to be read in terms of 512 Bytes */
  numBlks = dataLength >> hSDMMCInfo->dataBytesPerBlkPower2;

  SDMMC->MMCBLEN |= hSDMMCInfo->dataBytesPerBlk;
  SDMMC->MMCNBLK =  numBlks;

    /* reset the FIFO  */
  SDMMC->MMCFIFOCTL |= 0x1;
  UTIL_waitLoop(100000);
  /* Set the Transfer direction from the FIFO as receive*/
  SDMMC->MMCFIFOCTL &= 0xFFFD;

  /* Set the access width that will be used (MMCFIFOCTL register ACCWD bits) */

  /*Set the FIFO level(Threshold) 32 bytes (256 bit) always. After reset*/
  SDMMC->MMCFIFOCTL |= 0x0004;

  /* Send the Multi Blk Read Command with a no response check */
  if(hSDMMCInfo->mmcSdCSDRegInfo.sdHighCapacityCard)
    status = SDMMCSendCmd(0xA080 | SDMMC_READ_MULTIPLE_BLOCK, cardMemAddr >> hSDMMCInfo->dataBytesPerBlkPower2, FALSE);
  else
    status = SDMMCSendCmd(0xA080 | SDMMC_READ_MULTIPLE_BLOCK, cardMemAddr, FALSE);

  if(status != E_PASS)
   	return E_FAIL;
	   		
  status=SDMMCReadNWords((Uint32*)dest, dataLength);
  if(status !=E_PASS)
	 return E_FAIL; 

  /*Delay needed for safety */
  UTIL_waitLoop(10000); 
  timeOut = 50000;
  do {
	if(SDMMC->MMCST0 & SDMMC_STAT0_DATDNE) {
	    retVal = E_PASS;
		break;
	}
	timeOut--;
	if( timeOut == 0 ) {
	    retVal = E_TIMEOUT;
		break;
	}
  } while(1);

  /* Send the Stop Tx Command */
  if(retVal == E_PASS) {
	  status = SDMMCSendCmd(SDMMC_STOP_TRANSMISSION, cardMemAddr, FALSE);
	  if(status != E_PASS)
	   	retVal = E_FAIL;
  }

  return retVal;
}

/**
    \brief  Write N words to the MMC Controller Register

    \param  data  Buffer containing data to be written to the MMC
    \param  numWords  Number of words to be written to the MMC

    \return if success, \c E_PASS, else error code

*/
Uint8 SDMMCWriteNWords( SDMMC_InfoHandle hSDMMCInfo, Uint32 *data, Uint32 numofBytes,Uint32 cardMemAddr ) 
{
  register volatile Uint16 stat;
  Uint32 ii=0,jj=0,fifoDxrWrCnt=0;
  Uint32 fifoWriteItrCount=0;          /* Word counter */
  Uint8 status;
 
     /* reset the FIFO  */
  SDMMC->MMCFIFOCTL |= 0x1;

  /* Set the Transfer direction from the FIFO as receive*/
  SDMMC->MMCFIFOCTL |= 0x0002;

  /*Set the FIFO level 32 bytes (256 bit) always - Already done in Init TODO (remove?)*/
  SDMMC->MMCFIFOCTL |= 0x0004;

  fifoWriteItrCount=numofBytes >> 5;
  fifoDxrWrCnt=8;
     
  for(ii=0; ii < fifoWriteItrCount;ii++)
  {	
  	if(ii==0)
	{
		if(numofBytes == hSDMMCInfo->dataBytesPerBlk)
	        status = SDMMCSendCmd(0x2800 | SDMMC_WRITE_BLOCK, cardMemAddr,FALSE);
	    else
	        status = SDMMCSendCmd(0x2880 | SDMMC_WRITE_MULTIPLE_BLOCK, cardMemAddr, FALSE);
	}
  
  	for(jj=0;jj < fifoDxrWrCnt; jj++)
  		SDMMC->MMCDXR= (Uint32)*data++;

	   
  	if(ii != (fifoWriteItrCount -1))
  		while(!((SDMMC->MMCST0 & DEVICE_SDMMC_MMCST0_DXRDY_MASK) >> DEVICE_SDMMC_MMCST0_DXRDY_SHIFT));
  }	      		         		          		         		         
	     		        
  return status;
}


Uint8 SDMMCSingleBlkWrite( SDMMC_InfoHandle hSDMMCInfo, Uint32 cardMemAddr, Uint32 *src, Uint32 blkLength)
{
  Uint8 status = E_PASS;

  SDMMC->MMCBLEN |= (Uint16)(hSDMMCInfo->dataBytesPerBlk&0xFFF);
  SDMMC->MMCNBLK =  1;
    
  status = SDMMCSendCmd(SDMMC_SET_BLOCKLEN, hSDMMCInfo->dataBytesPerBlk, FALSE);
  if(status != E_PASS)
  	return	E_FAIL;             
 
  if(status == E_PASS) 
  {
    if(hSDMMCInfo->mmcSdCSDRegInfo.sdHighCapacityCard)
	{
  	  /* Write Data, every time MMCDXR Reg full */
	  status = SDMMCWriteNWords(hSDMMCInfo,(Uint32*)src, hSDMMCInfo->dataBytesPerBlk,cardMemAddr >> hSDMMCInfo->dataBytesPerBlkPower2);
	}
	else
	{
  	  /* Write Data, every time MMCDXR Reg full */
	  status = SDMMCWriteNWords(hSDMMCInfo, (Uint32*)src, hSDMMCInfo->dataBytesPerBlk,cardMemAddr);
	}
		   
	/*Delay Required*/
	//UTIL_waitLoop(100);
		 
    if(status == E_PASS)
    {
	do {
	  	if(SDMMC->MMCST0 & SDMMC_STAT0_DATDNE)
			return E_PASS;
	} while(1);       
		   	     
    }else
		 return E_FAIL;
  }	
  return E_PASS;
}

Uint8 SDMMCMultipleBlkWrite( SDMMC_InfoHandle hSDMMCInfo, Uint32 cardMemAddr, Uint32 *src, Uint32 datalength) 
{
	Uint8 status;
	Uint32 numBlks;
      
   /*Clear all Response Registers */  
   SDMMCClearResponse();
     
   /* To find out number of BLOCKS to be written in terms of 512 bytes */
   numBlks = datalength >> hSDMMCInfo->dataBytesPerBlkPower2;

   if(numBlks* hSDMMCInfo->dataBytesPerBlk < datalength)
     numBlks++;
    
   SDMMC->MMCBLEN |= hSDMMCInfo->dataBytesPerBlk;
   SDMMC->MMCNBLK =  numBlks;

   /* Send the BLOCK LEN command to the card , it is an optional one*/
   status = SDMMCSendCmd(SDMMC_SET_BLOCKLEN, hSDMMCInfo->dataBytesPerBlk, FALSE);
   if(status!=E_PASS)
	   return E_FAIL;  
    if(hSDMMCInfo->mmcSdCSDRegInfo.sdHighCapacityCard)
	{             		
      /* Read Data, every time Data Rd Reg full, till all words read */
      status = SDMMCWriteNWords(hSDMMCInfo, (Uint32*)src,datalength,cardMemAddr >> hSDMMCInfo->dataBytesPerBlkPower2);
	}
    else
	{             		
      /* Read Data, every time Data Rd Reg full, till all words read */
      status = SDMMCWriteNWords(hSDMMCInfo, (Uint32*)src,datalength,cardMemAddr);
	}

   /*Delay required */
   UTIL_waitLoop(100);
			  
   if(status != E_PASS)
	return E_FAIL;

   /* Check for SDMMC_DATDNE signal */ 
   /* No timeout in QT mode */
   do {
   	if(SDMMC->MMCST0 & SDMMC_STAT0_DATDNE) {
 		SDMMCSendCmd(0xA180 | SDMMC_STOP_TRANSMISSION, SDMMC_STUFF_BITS, FALSE);
		    return E_PASS;
	}
   } while(1);       
}


/***********************************************************
* End file                                                 *
***********************************************************/

