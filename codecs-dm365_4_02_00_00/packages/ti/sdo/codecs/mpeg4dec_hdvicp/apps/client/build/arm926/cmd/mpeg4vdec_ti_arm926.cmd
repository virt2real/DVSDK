/*==========================================================================*/
/* LNK.CMD   - v2.50a COMMAND FILE FOR LINKING TMS470 32BIS C/C++ PROGRAMS  */
/*                                                                          */
/*   Usage:  lnk470 <obj files...>    -o <out file> -m <map file> lnk.cmd   */
/*           cl470 <src files...> -z -o <out file> -m <map file> lnk.cmd    */
/*                                                                          */
/*   Description: < Empty >                                                 */
/*																			*/
/*   Notes: (1)   You must specify the directory in which run-time support  */
/*                library is located.  Either add a "-i<directory>" line to */
/*                this file, or use the system environment variable C_DIR   */
/*                to specify a search path for libraries.                   */
/*                                                                          */
/*          (2)   If the run-time support library you are using is not      */
/*                named below, be sure to use the correct name here.        */
/*                                                                          */
/*==========================================================================*/

-c                                      /* LINK USING C CONVENTIONS      	*/
-stack  0xA000                          /* SOFTWARE STACK SIZE           	*/
-heap   0x156FBC0                        /* HEAP AREA SIZE                	*/
/*-l rts32earm9.lib*/ 						/* GET RUN-TIME SUPPORT          	*/

__F_STACK_SIZE = 0x100;          /* FIQ Stack */
__S_STACK_SIZE = 0x100;          /* SUPERVISOR Stack */

/*--------------------------------------------------------------------------*/
/* SPECIFY THE SYSTEM MEMORY MAP 											*/
/*--------------------------------------------------------------------------*/

MEMORY
{
	RESET	         : org = 0x00000000   len = 0x00000004
	VECS             : org = 0x00000004   len = 0x000000FB
	ITCM	         : org = 0x00000100   len = 0x00003F00  /* IRAM 0 */
	DTCM	         : org = 0x00014000   len = 0x00004000  /* IRAM 1 */
    EXT              : org = 0x80000000   len = 0x15ADE740	

}


/*--------------------------------------------------------------------------*/
/* SPECIFY THE SECTIONS ALLOCATION INTO MEMORY 								*/
/*--------------------------------------------------------------------------*/

SECTIONS
{

    .text           >       EXT
    .intDataMem     >       EXT
    .stack          >       EXT
    .far            >       EXT
    .switch         >       EXT
    .tables         >       EXT
    .data           >       EXT
    .bss            >       EXT
    .sysmem         >       EXT
    .cinit			>		EXT
    .cio            >       EXT
	.input_buffer   >       EXT
	.const          >       EXT
	.display_buffer >       EXT
	.ref_buffer     >       EXT
    .CoProcData		>       EXT
	.L1D_mem        >       EXT
	.My_Sect		> 		EXT
	.chroma_buffer  >       EXT
	.sstack         >       EXT
	.fstack         >       EXT
	.cacheapi       >       EXT
	.handler        >       ITCM
	.intvecs        >       VECS
	.mmutable	    >	    DTCM

}


