#ifndef _AEMIF_H_
#define _AEMIF_H_

#define AEMIF_ADDR  			0x01E10000

#define RCSR  		         (unsigned int*)(AEMIF_ADDR + 0x00)	//Revision Code and Status Register
#define WAITCFG              (unsigned int*)(AEMIF_ADDR + 0x04) 	//Async Wait Cycle Config Register
#define ACFG2  				 (unsigned int*)(AEMIF_ADDR + 0x10)	//Async Bank1 Config Register
#define ACFG3	 			 (unsigned int*)(AEMIF_ADDR + 0x14)	//Async Bank2 Config Register
#define ACFG4	 			 (unsigned int*)(AEMIF_ADDR + 0x18)	//Async Bank3 Config Register
#define ACFG5	 			 (unsigned int*)(AEMIF_ADDR + 0x1C)	//Async Bank4 Config Register
#define AINTRAW				 (unsigned int*)(AEMIF_ADDR + 0x40)	//Interrpt Raw Register
#define AINTMASK			 (unsigned int*)(AEMIF_ADDR + 0x44)	//Interrupt Masked Register
#define AINTMASKSET			 (unsigned int*)(AEMIF_ADDR + 0x48)	//Interrupt Mask Set Register
#define INTMASKCLEAR         (unsigned int*)(AEMIF_ADDR + 0x4C)	//Interrupt Mask Clear Register
#define NANDCTL				 (unsigned int*)(AEMIF_ADDR + 0x60)	//NAND Flash Control Register
#define NANDSTAT			 (unsigned int*)(AEMIF_ADDR + 0x64)	//NAND Flash Status Register
#define NANDECC2			 (unsigned int*)(AEMIF_ADDR + 0x70)	//NAND Flash 1 ECC Register
#define NANDECC3			 (unsigned int*)(AEMIF_ADDR + 0x74)	//NAND Flash 2 ECC Register
#define NANDECC4			 (unsigned int*)(AEMIF_ADDR + 0x78)	//NAND Flash 3 ECC Register
#define NANDECC5			 (unsigned int*)(AEMIF_ADDR + 0x7C)	//NAND Flash 4 ECC Register

#endif
/* Rev.No.   Date/Time               ECN No.          Modifier      */
/* -------   ---------               -------          --------      */

/* 1         25 Jun 2004 10:31:02    1881             xkeshavm      */
/*                                                                  */
/* Command header files added to develop test cases                 */
/********************************************************************/ 
