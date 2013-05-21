-lrts67plus.lib

-stack          0x00008000 /* Stack Size */  
-heap           0x00008000 /* Heap Size */


MEMORY
{
	IRAM        : o = 0x10000000, l = 0x00030000 /* L2 RAM/Cache */
  IRAM2       : o = 0x10030000, l = 0x00010000
	DRAM		    : o = 0x80000000, l = 0x08000000 /* DDR RAM */
	AEMIF		    : o = 0x90000000, l = 0x10000000 /* AEMIF CS2 region */
}


SECTIONS
{
	.text       > IRAM
	.const      > IRAM
	.bss        > IRAM
	.far		    > IRAM
	.switch		  > IRAM
	.stack      > IRAM
	.data       > IRAM
	.cinit		  > IRAM
	.sysmem		  > IRAM
	.cio		    > IRAM
	.ddr_mem    > IRAM2 
	.aemif_mem  > AEMIF
}