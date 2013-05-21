-lrts64plus.lib

-stack          0x00008000 /* Stack Size */  
-heap           0x00008000 /* Heap Size */



MEMORY
{
	L2RAM		org=0x10800000 len=0x00020000 /* L2 RAM/Cache */
	L1P_CACHE1	org=0x10E08000 len=0x00006000 /* L1P RAM/cache */
	L1P_CACHE2	org=0x10E0E000 len=0x00001C00 /* L1P RAM/cache */
	L1D_CACHE1	org=0x10F10000 len=0x00006000 /* L1D RAM */
	L1D_CACHE2	org=0x10F16000 len=0x00001C00 /* L1D RAM */
	L1_STACK	org=0x10F17C00 len=0x00000400 /* STACK in L1D */
	DRAM		org=0x80000000 len=0x08000000 /* DDR RAM */
	AEMIF		org=0x42000000 len=0x01000000 /* AEMIF CS2 region */
}


SECTIONS
{
	.text       > L2RAM
	.const      > L2RAM
	.bss        > L2RAM
	.far		> L2RAM
	.switch		> L2RAM
	.stack      > L2RAM
	.data       > L2RAM
	.cinit		> L2RAM
	.sysmem		> L2RAM
	.cio		> L2RAM
	.aemif_mem  > AEMIF
	.ddr_mem :
	{
	  .+=0x08000000;
	}
	load = DRAM, type= DSECT, fill = 0xFFFFFFFF, START(_EXTERNAL_RAM_START), END(_EXTERNAL_RAM_END)
}