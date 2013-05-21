/****************************************************************************/
/* mpeg2venc_ti_arm926.cmd COMMAND FILE FOR LINKING PROGRAMS                */
/****************************************************************************/

-c                                         /* LINK USING C CONVENTIONS      */
-stack  0x8000                             /* SOFTWARE STACK SIZE           */
-heap   0x2000000                           /* HEAP AREA SIZE                */
__F_STACK_SIZE = 0x100;                    /* IRQ Stack                     */
__S_STACK_SIZE = 0x100;                    /* SUPERVISOR Stack              */
-l D:\CCStudio_v3.3\tms470\cgtools\lib\rts32earm9.lib

/* SPECIFY THE SYSTEM MEMORY MAP */

MEMORY
{
	RESET	    : org = 0x00000000   len = 0x00000004
	VECS        : org = 0x00000004   len = 0x000000FB
    ITCM	    : org = 0x00000100   len = 0x00003F00  /* IRAM 0 */
    DTCM        : org = 0x00014000   len = 0x00004000  /* IRAM 1 */
    EXT         : org = 0x80000000   len = 0x40000000
}

/* SPECIFY THE SECTIONS ALLOCATION INTO MEMORY */

SECTIONS
{
	.intvecs        >       VECS
    .text           >       EXT
    .stack          >       EXT
    .bss            >       EXT
    .far            >       EXT
    .switch         >       EXT 
    .data           >       EXT
    .cinit			>		EXT
    .cio            >       EXT 
	.const          >       EXT
    .sysmem         >       EXT
	.handler        >       ITCM
	.sstack         >       EXT
	.fstack         >       EXT
    .mmutable       >       DTCM
}


