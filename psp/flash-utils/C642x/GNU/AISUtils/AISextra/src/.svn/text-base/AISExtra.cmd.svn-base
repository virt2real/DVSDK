
MEMORY
{
	L2RAM		org=0x10800000 len=0x00020000 /* L2 RAM/Cache */
	L1P_CACHE1	org=0x10E08000 len=0x00006000 /* L1P RAM/cache */
	L1P_CACHE2	org=0x10E0E000 len=0x00001C00 /* L1P RAM/cache */
	L1D_CACHE1	org=0x10F10000 len=0x00006000 /* L1D RAM */
	L1D_CACHE2	org=0x10F16000 len=0x00001C00 /* L1D RAM */
	L1_STACK	org=0x10F17C00 len=0x00000400 /* STACK in L1D */
}


SECTIONS
{
	.params		> L1D_CACHE2
	.cinit      > L1D_CACHE2
	.text:uart  : load = L1D_CACHE2, run = L1P_CACHE2
	.text       : load = L1D_CACHE2, run = L1P_CACHE2
	.data:uart  > L1D_CACHE2
	.const      > L1D_CACHE2
	.bss        > L1D_CACHE2
	.far		> L1D_CACHE2
	.switch		> L1D_CACHE2
	.data       > L1D_CACHE2
	.stack      > L1_STACK
}

