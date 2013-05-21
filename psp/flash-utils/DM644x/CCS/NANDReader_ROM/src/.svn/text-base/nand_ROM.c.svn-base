/******************************************************************************/
/*            TEXAS INSTRUMENTS INCORPORATED PROPRIETARY INFORMATION          */ 
/*   Created 2005, (C) Copyright 2005 Texas Instruments.  All rights reserved.*/ 
/*																			  */
/* 	FILE	: nand.c 				                                	      */
/*	PURPOSE	: NAND driver file				                                  */
/*  PROJECT	: DaVinci ROM boot-loader 		                                  */
/*  AUTHOR	: Vignesh LA					                                  */
/*  DATE	: April-25-2005                                                   */
/******************************************************************************/
#include "bootloader_ROM.h"
#include "util.h"
#include "nand.h"
#include "device_nand.h"
#include "nand_ROM.h"

NAND_INFO	gNandInfo;
extern NAND_BOOT gNandBoot;				 /* structure for holding details about UBL stored in NAND */
extern Uint32 gDMA;

/* Details of NAND device sizes supported */
const NAND_DEVICE_INFO   gNandDevInfo[] = {
/*  devid,p_cnt,p_byte1,blk_shift, addr_cycles */
  	{0x6E, 16, 	256+8, 	12, 		3},  /* 1 MB */
  	{0x68, 16, 	256+8, 	12, 		3},  /* 1 MB */
  	{0xEC, 16, 	256+8, 	12, 		3},  /* 1 MB */
  	{0xE8, 16, 	256+8, 	12, 		3},  /* 1 MB */
  	{0xEA, 16, 	256+8, 	12, 		3},  /* 2 MB */
    {0xE3, 16, 	512+16, 12, 		3},	 /* 4 MB */
    {0xE5, 16, 	512+16, 12, 		3},	 /* 4 MB */
    {0xE6, 16, 	512+16, 12, 		3},	 /* 8 MB */
    {0x39, 16, 	512+16, 12, 		3},	 /* 8 MB */
    {0x6B, 16, 	512+16, 12, 		3},	 /* 8 MB */    
    {0x73, 32, 	512+16, 13, 		3},	 /* 16 MB */
    {0x33, 32, 	512+16, 13, 		3},	 /* 16 MB */
    {0x75, 32, 	512+16, 13, 		3},	 /* 32 MB */
    {0x35, 32, 	512+16, 13, 		3},	 /* 32 MB */
	{0x43, 32, 	512+16, 12, 		3},  /* 16 MB 0x1243 */
	{0x45, 32, 	512+16, 12, 		3},  /* 32 MB 0x1245 */
	{0x53, 32, 	512+16, 12, 		3},  /* 16 MB 0x1253 */
	{0x55, 32, 	512+16, 12, 		3},  /* 32 MB 0x1255 */
    //{0x76, 32, 	512+16, 13, 		4},	 /* 64 MB */
    {0x36, 32, 	512+16, 13, 		4},	 /* 64 MB */
    {0x79, 32, 	512+16, 13, 		4},	 /* 128 MB */
  	{0x71, 32, 	512+16, 13, 		4},	 /* 256 MB */
	{0x46, 32, 	512+16, 13, 		4},  /* 64 MB 0x1346 */
	{0x56, 32, 	512+16, 13, 		4},  /* 64 MB 0x1356 */
	{0x74, 32, 	512+16, 13, 		4},  /* 128 MB 0x1374 */   
    //{0xF1, 64, 	2048+64,22, 		4},  /* 128 MB - Big Block */
    {0xA1, 64, 	2048+64,22, 		4},	 /* 128 MB - Big Block */
 	{0xAA, 64, 	2048+64,22, 		5},	 /* 256 MB - Big Block */
 	{0xDA, 64, 	2048+64,22, 		5},	 /* 256 MB - Big Block */
 	{0xDC, 64, 	2048+64,22, 		5},	 /* 512 MB - Big Block */
 	{0x76, 32, 	512+16, 13, 		4},	 /* 64 MB */
 	{0xAC, 64, 	2048+64,22, 		5},  /* 512 MB - Big Block */
	{0xB1, 64, 	2048+64,22, 		4},  /* 128 MB - Big Block 0x22B1 */
  	{0xC1, 64, 	2048+64,22, 		4},  /* 128 MB - Big Block 0x22C1 */
	{0xF1, 64, 	2048+64,22, 		4},  /* 128 MB - Big Block */

};    

/* Initialze NAND interface and find the details of the NAND used */
Uint32 NANDInit() { 
	Uint32 error;
	/* Setting the nand_width = 0(8 bit NAND) or 1(16 bit NAND). AEMIF CS2 bus Width 
	   is given by the BOOTCFG(bit no.5)
	   
	 */
	gNandInfo.nand_width = ((*BOOTCFG)&(NAND_TYPE_MASK_0X00000020))>>5;

	/* initialize NAND interface */
	NANDConfig();
	
	/* Send reset command to NAND */
	*NAND_CMD_ADDR = NAND_RST;
	UTIL_waitLoop(10);
	if(NANDWaitRdy() != E_PASS) {
		error = E_FAIL;
	} else {
		/* Find details of the NAND used */
		error = NANDGetDetails();                
	}
	
	return error;
}
                                         
void NANDReadNBytes(Uint32 numBytes, Uint8* destAddr) {
	Uint32 i;

	/* Starting the ECC in the NANDFCR register for CS2(bit no.8) */
	NANDECCRead();
	NANDECCStart();

	if (gNandInfo.nand_width) {
	/* 16-bit NAND */
		for(i=0;i<(numBytes/2);i++) {
	    	/* NANDRead done directly without checking for nand_width */
	    	*(Uint16*)destAddr = *((volatile Uint16*)NAND_DATA_ADDR);
			destAddr += 2;
		}
	} else {
	/* 8-bit NAND */
	    for (i=0; i < numBytes; i++) {
			/* NANDRead done directly without checking for nand_width */
			*destAddr = (*NAND_DATA_ADDR);
	    	destAddr++;
	    }
	}
}     

Uint32 NANDReadNBytesDMA(Uint32 numBytes, Uint8* destAddr) {
	Uint32 status = 0;
	volatile Uint32 count = DMA_TIMEOUT;	
	/* Starting the ECC in the NANDFCR register for CS2(bit no.8) */
	NANDECCRead();
	NANDECCStart();                    

	CSL_EDMACC_0_REGS->PARAMENTRY[0].OPT = 0x00100004;
	CSL_EDMACC_0_REGS->PARAMENTRY[0].SRC = 0x02000000;
	CSL_EDMACC_0_REGS->PARAMENTRY[0].SRC_DST_BIDX = 0x00080000;
	CSL_EDMACC_0_REGS->PARAMENTRY[0].LINK_BCNTRLD = 0x0;
	CSL_EDMACC_0_REGS->PARAMENTRY[0].SRC_DST_CIDX = 0x0;
	CSL_EDMACC_0_REGS->PARAMENTRY[0].CCNT = 1;              

	CSL_EDMACC_0_REGS->PARAMENTRY[0].A_B_CNT = ((numBytes/8)<<16) | (0x8);

	CSL_EDMACC_0_REGS->PARAMENTRY[0].DST = (Uint32)((&destAddr[0]));

	CSL_EDMACC_0_REGS->SHADOW[0].ICR = 0xFFFFFFFF;				
	CSL_EDMACC_0_REGS->SHADOW[0].EESR |= 0x1;
	CSL_EDMACC_0_REGS->SHADOW[0].ESR  |= 0x1;
    
	/* check for the status to be ready */
	do { 
		status = ((CSL_EDMACC_0_REGS->SHADOW[0].IPR) & (0x00000001));
		count --;
	} while (!status && count > 0);
	
	if(count == 0)
		return E_TIMEOUT;
	else
		return E_PASS;

}           
                           
/* Get details of the NAND flash used from the id and the table of NAND */
Uint32 NANDGetDetails()
{
	Uint32 deviceID,i;
	Uint32 foundNAND = NAND_NOT_FOUND;
	
	/* read device ID */
	*NAND_CMD_ADDR =  NAND_RDID;/* Read ID Command */
	*NAND_ALE_ADDR =  NAND_RDIDADD;/* Send ID address */
	UTIL_waitLoop(10);
	
	/* Always reading the ID alone in 8 bit mode */
	i			= (*NAND_DATA_ADDR);
	deviceID 	= (*NAND_DATA_ADDR);
	i	 		= (*NAND_DATA_ADDR);
	i 			= (*NAND_DATA_ADDR);

	/* Search for the NAND details in the table */
	for(i=0;(i<MAX_NAND_SUPPORTED) && (foundNAND == NAND_NOT_FOUND);i++) {
		if(deviceID == gNandDevInfo[i].dev_id) {
			foundNAND = NAND_FOUND;
			gNandInfo.dev_code = deviceID;
			gNandInfo.page_cnt = gNandDevInfo[i].p_cnt;
			gNandInfo.page_size = gNandDevInfo[i].p_byte1;
			gNandInfo.blk_shift = gNandDevInfo[i].blk_shift;
			gNandInfo.addr_cycles = gNandDevInfo[i].addr_cycles;
			if(gNandInfo.page_size > 528) {
				gNandInfo.page_shift = 16;
				gNandInfo.big_block = 1;
			}
			else {
				gNandInfo.page_shift = 8;
				gNandInfo.big_block = 0;
			}
		}
	}
	if(foundNAND == NAND_NOT_FOUND) {
		/* Default configuration */
		/* For SAMSUNG/RENESAS and other. We dont support Toshiba */
		gNandInfo.dev_code 		= UNKNOWN_NAND;
		gNandInfo.page_cnt 		= 64;
		gNandInfo.page_size 	= 2112;
		gNandInfo.blk_shift 	= 22;
		gNandInfo.big_block 	= 1;
		gNandInfo.addr_cycles 	= 5;
		gNandInfo.page_shift 	= 16;
	}    
	
	return E_PASS;
}

/* Routine to read a page from NAND */	
Uint32 NANDReadPage(Uint32 blkAddr, Uint32 page, Uint8 *dest) {
	Uint32 i,j;
	Uint32 addr;
	Uint32 eccValue[4];
	Uint32 spareValue;
	
	*NAND_CMD_ADDR = NAND_LO_PAGE;
	
	/* Send address of the block + page to be read */
	if(gNandInfo.addr_cycles == 5) {
		addr = (blkAddr << (gNandInfo.blk_shift-16)) | page;
		*NAND_ALE_ADDR = 0x00;
		*NAND_ALE_ADDR = 0x00;
		*NAND_ALE_ADDR = (addr & 0xff);
		*NAND_ALE_ADDR = ((addr & 0xff00)>>8);
		*NAND_ALE_ADDR = ((addr & 0xff0000)>>16);
	}
	else if(gNandInfo.addr_cycles == 4) {
		addr = (blkAddr << gNandInfo.blk_shift) | (page << gNandInfo.page_shift);
		*NAND_ALE_ADDR = (addr & 0xff);
		*NAND_ALE_ADDR = ((addr & 0xff00)>>8);
		*NAND_ALE_ADDR = ((addr & 0xff0000)>>16);
		*NAND_ALE_ADDR = ((addr & 0xff000000)>>24);				
	}
	else {
		addr = (blkAddr << gNandInfo.blk_shift) | (page << gNandInfo.page_shift);
		*NAND_ALE_ADDR = (addr & 0xff);
		*NAND_ALE_ADDR = ((addr & 0xff00)>>8);
		*NAND_ALE_ADDR = ((addr & 0xff0000)>>16);
	}
	
	if(gNandInfo.big_block == 1)	/* Big block NAND */
		*NAND_CMD_ADDR = NAND_READ_30H;

	/* Wait for data to be available */
	if(NANDWaitRdy())
		return E_FAIL;

	if(gDMA == 0) {
		/* Read the data to the destination buffer and detect error*/
		if(gNandInfo.page_size == 264) {
			NANDReadNBytes(256,dest);
			/* Ignoring the p2048 bits for the 256 byte read */
			eccValue[0] = ((NANDECCRead())&(0x07FF07FF));
			
			NANDReadNBytes(8,&dest[256]);			
			/* Spare date stored immediately afer the data of 256 */
			spareValue = (NANDSpareECCRead(&dest[256])&(0x07FF07FF));
			if(eccValue[0] != spareValue)
				return E_FAIL; /* E_FAIL */
		} 
		else if (gNandInfo.page_size == 528) {
			NANDReadNBytes(512,dest);
			eccValue[0] = ((NANDECCRead())&(0x0FFF0FFF));
			
			NANDReadNBytes(16,&dest[512]);			
			spareValue = (NANDSpareECCRead(&dest[512])&(0x0FFF0FFF));
			if(eccValue[0] != spareValue)
				return E_FAIL; /* E_FAIL */
		} 
		else if (gNandInfo.page_size == 2112) {
			for(i = 0;i<4;i++) {
				NANDReadNBytes(512,&dest[512*i]);
				eccValue[i] = ((NANDECCRead())&(0x0FFF0FFF));
			}                                       
			NANDReadNBytes(64,&dest[2048]);

			for(j=0;j<4;j++) {
				/* ECC values read from (2056+j*16+8)*/
				spareValue = (NANDSpareECCRead(&dest[2056+(j*16)])&(0xFFF0FFF));
				if(eccValue[j] != spareValue)
					return E_FAIL; /* E_FAIL */
			}
		}	
	}
	else {
		/* EDMACC is used when dma = 1 */
		/* Register settings for TPCC. Using DMA region 0, Channel 11*/ 
		CSL_EDMACC_0_REGS->DRA[0].DRAE  |= 0xFFFFFFFF;
		CSL_EDMACC_0_REGS->DRA[0].DRAEH |= 0xFFFFFFFF;

		if(gNandInfo.page_size == 264) {
			// Reading 256 bytes                                        
			if(NANDReadNBytesDMA(256,&dest[0]) != E_PASS)
				return E_FAIL;			

			/* ECC detection */
			/* Ignoring the p2048 bits for the 256 byte read */
			eccValue[0] = ((NANDECCRead())&(0x07FF07FF));

			if(NANDReadNBytesDMA(8,&dest[256]) != E_PASS)
				return E_FAIL;			

			/* Spare date stored immediately afer the data of 256 */
			spareValue = (NANDSpareECCRead(&dest[256])&(0x07FF07FF));
			if(eccValue[0] != spareValue)
				return E_FAIL; /* E_FAIL */
				
		} else if(gNandInfo.page_size == 528) {
			// Reading 512 bytes
			if(NANDReadNBytesDMA(512,&dest[0]) != E_PASS)
				return E_FAIL;			
			
			eccValue[0] = ((NANDECCRead())&(0x0FFF0FFF));

			if(NANDReadNBytesDMA(16,&dest[512]) != E_PASS)
				return E_FAIL;			

			/* Spare date stored immediately afer the data of 512 */
			spareValue = (NANDSpareECCRead(&dest[512])&(0xFFF0FFF));
			if(eccValue[0] != spareValue)
				return E_FAIL; /* E_FAIL */

		} else if(gNandInfo.page_size == 2112) {
			for(i = 0;i<4;i++) {
				if(NANDReadNBytesDMA(512,&dest[512*i]) != E_PASS)
					return E_FAIL;       
					
				eccValue[i] = ((NANDECCRead())&(0x0FFF0FFF));
			}                                       
			NANDReadNBytesDMA(64,&dest[2048]);

			for(j=0;j<4;j++) {
				/* ECC values read from (2056+j*16)*/
				spareValue = (NANDSpareECCRead(&dest[2056+(j*16)])&(0xFFF0FFF));
				if(eccValue[j] != spareValue)
					return E_FAIL; /* E_FAIL */
			}
		} 
	}	
	/* Wait NAND to be set to ready */
	if(NANDWaitRdyReg() != E_PASS)
		return E_FAIL;	
		
	return E_PASS;
}

/* Wait for the status to be ready 
Polling for the pad_wait_i(bit 0) of NANDFSR */
Uint32 NANDWaitRdy() {
	volatile Uint32 cnt;
	Uint32 status;
  	cnt = NAND_TIMEOUT;
  	
  	do {
    	status = (CSL_EMIF_0_REGS->NANDFSR & 1);
    	cnt--;
  	} while((cnt>0) && !status);

  	if(cnt == 0)
  		return E_FAIL;

 	return E_PASS;
}


/* Wait for the status to be ready in register 
 There were some problems reported in DM320 with Ready/Busy pin
 not working with all NANDs. So this check has also been added */
Uint32 NANDWaitRdyReg() {
	volatile Uint32 cnt;
	Uint32 status;
    *NAND_CMD_ADDR = NAND_STATUS;
    status = *NAND_DATA_ADDR;
    cnt = NAND_TIMEOUT;

  	do {
	    *NAND_CMD_ADDR = NAND_STATUS;
	    status = *NAND_DATA_ADDR;
    	cnt--;
  	} while((cnt>0) && !status);
    
	if(cnt == 0)
		return E_FAIL;  		

	return E_PASS;
}


//Confirm the timings and replace with #defines
void NANDConfig (void) {

	/* We are leaving the CSL_EMIF_0_REGS->AWCCR = 0x80 
	   This is the default setting. Hibari sets it to 0x0F
	 */
    /*Aysnchronous bank 1 is used for NAND CS2 */
    if (gNandInfo.nand_width ) {
	  CSL_EMIF_0_REGS->AB1CR = 0x3FFFFFFD;//16 bit->01
    } 
    /* For 8 bit NAND the default value is 0x3FFFFFFC */
     
    /* configuring the CS2(bit no.0) for NAND) */
    CSL_EMIF_0_REGS->NANDFCR =  0x1; 
}

Uint32 NANDSpareECCRead(Uint8* readPtr) {
	
	Uint32 spareECCValue;
	if(gNandInfo.nand_width)
    	// 16 bit NAND
    	spareECCValue = (*((Uint16*)(&readPtr[0]))<<16)|(*((Uint16*)(&readPtr[2]))); 
    else
    	// 8 bit NAND
    	spareECCValue = (readPtr[0]<<24)|(readPtr[1]<<16)|(readPtr[2]<<8)|(readPtr[3]); 
    	
	return spareECCValue;
}

void EMIFEnableFastMode() {
	// if 8_16 = 1 then CSL_EMIF_0_REGS->AB1CR = 0x1
	// else CSL_EMIF_0_REGS->AB1CR = 0x0
 	CSL_EMIF_0_REGS->AB1CR &= 0x1;
}

void EMIFDisableFastMode() {
	// if 8_16 = 1 then CSL_EMIF_0_REGS->AB1CR = 0x3FFFFFFD
	// else CSL_EMIF_0_REGS->AB1CR = 0x3FFFFFFC
	CSL_EMIF_0_REGS->AB1CR |= 0x3FFFFFFC;
}




