/*
 *  Linker-command file for the fastcopytest application
 */
-l fastcopytestcfg.cmd


/* these libraries are autoincluded since they belong to dependent projects */
/* -l ../../../acpy3/acpy3.l64P   */
/* -l ../../../dman3/dman3.l64P   */

_FCPY_IFCPY = _FCPY_TI_IFCPY;
_FCPY_IDMA3 = _FCPY_TI_IDMA3;
_DMAN3_EDMA3BASE = 0x02A00000;

SECTIONS
{    

    .image       >      DDR 
    .internal    >      L1DSRAM
   
}
