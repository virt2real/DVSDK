-lrts64plus.lib

-stack          0x00008000 /* Stack Size */  
-heap           0x00008000 /* Heap Size */



MEMORY
{
	L2RAM		org=0x00A00000 len=0x00040000 /* L2 RAM/Cache */
	L1P_CACHE1	org=0x00E00000 len=0x00006000 /* L1P RAM/cache */
	L1P_CACHE2	org=0x00E06000 len=0x00001C00 /* L1P RAM/cache */
	L1D_CACHE1	org=0x00F00000 len=0x00006000 /* L1D RAM */
	L1D_CACHE2	org=0x00F06000 len=0x00001C00 /* L1D RAM */
	L1_STACK	org=0x00F07C00 len=0x00000400 /* STACK in L1D */
	DRAM		org=0xE0000000 len=0x10000000 /* DDR RAM */
	AEMIF		org=0xA0000000 len=0x02000000 /* AEMIF CS2 region */
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
	.ddr_mem    > DRAM 
	.aemif_mem  > AEMIF
}