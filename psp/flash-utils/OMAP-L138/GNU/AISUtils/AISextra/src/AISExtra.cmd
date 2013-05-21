
MEMORY
{
	L2RAM		    org=0x0081E000 len=0x00002000 /* L2 RAM/Cache */
}


SECTIONS
{
	.params		  > L2RAM
	.cinit      > L2RAM
	.text       > L2RAM
	.const      > L2RAM
	.bss        > L2RAM
	.far		    > L2RAM
	.switch		  > L2RAM
	.data       > L2RAM
	.stack      > L2RAM
}

