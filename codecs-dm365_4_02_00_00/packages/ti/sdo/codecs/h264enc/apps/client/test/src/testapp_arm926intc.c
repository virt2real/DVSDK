/** ==========================================================================
 *  @file   testapp_arm968intc.c
 *
 *  @path   $(PROJDIR)\Src
 *
 *  @desc  This File contains the definition of interrupt handler for ARM968,
 *          
 *  ==========================================================================
 *  Copyright (c) Texas Instruments Inc 2006, 2007
 *
 *  Use of this software is controlled by the terms and conditions found
 *  in the license agreement under which this software has been supplied
 * =========================================================================*/


/* -------------------- compilation control switches -----------------------*/


/****************************************************************************
*   INCLUDE FILES
*****************************************************************************/

/* -------------------- system and platform files ------------------------- */
#ifdef ENABLE_DM510
#include <std.h>
#endif //ENABLE_DM510
#include <stdio.h>

/* ------------------------- program files -------------------------------- */
#include "testapp_arm926intc.h"

/****************************************************************************
*   EXTERNAL REFERENCES NOTE : only use if not found in header file
*****************************************************************************/

/* ------------------------ data declarations ----------------------------- */

/* ----------------------- function prototypes ---------------------------- */
void Icache_Enable(void);
void Icache_Disable(void);
void Cache_Set_RoundRobin(void);
void Cache_Set_Random(void);
void Dcache_Enable(void);
void Dcache_Disable(void);
void Flush_Icache(void);
void Flush_Dcache(void);
void Enable_MMU(void);
void Disable_MMU(void);
void Set_MMU_Base(unsigned int);
void Set_Domains(unsigned int);


/****************************************************************************
*   PUBLIC DECLARATIONS Defined here, used elsewhere
*****************************************************************************/

/* ----------------------- data declarations ------------------------------ */

/* ---------------------- function prototypes ----------------------------- */


/****************************************************************************
*   PRIVATE DECLARATIONS Defined here, used only here
*****************************************************************************/

/* ---------------------- data declarations ------------------------------- */

/* --------------------- function prototypes ------------------------------ */


/* ---------------------------- macros ------------------------------------ */
/* Base address of DTCM where MMU tables are defined */
#define MMU_BASE 0x8AFFC000/*0x00014000*/


/* ===========================================================================
 *  @func     cache_low_data_clean()
 *      
 *  @desc     Function cleans the Data cache. This function has to be called
 *            before any DMA operation on the HOst ARM to take care of cache 
 *            coherancy in ARM926. 
 *
 *  @param    None
 *
 *  @return   None
 *  ==========================================================================
 */
void cache_low_data_clean()
{

    /* This is a CP15 command. It tests the cache line and if dirty bit is set
     * It cleans the cache line. Accordingly it sets the bit 31 of PC. */
    __asm(" MRC     p15, #0, PC, c7, c10, #3 ");      
    
    /* If bit 31 of PC is set, this means that there where some dirtly lines
     * in the cache. So loop back again to clean it. This loop will continue
     * till there are no dirtly lines in the cache */
    __asm(" BNE     _cache_low_data_clean ");

} 


/* ===========================================================================
 *  @func     cache_low_data_clean_flush()
 *      
 *  @desc     Function cleans and invalidates the Data cache. This function has 
 *            to be called  before any DMA operation on the HOst ARM to take
 *            care of cache coherancy in ARM926. 
 *
 *  @param    None
 *
 *  @return   None
 *  ==========================================================================
 */
void cache_low_data_clean_flush()
{
    /* This is a CP15 command. It tests the cache line and if dirty bit is set
     * It cleans the cache line. It also invalidates that cache line 
     * Accordingly it sets the bit 31 of PC. */
    __asm(" MRC   p15, #0, PC, c7, c14, #3   ");      
    
    /* If bit 31 of PC is set, this means that there where some dirtly lines
     * in the cache. So loop back again to clean it. This loop will continue
     * till there are no dirtly lines in the cache */
    __asm(" BNE  _cache_low_data_clean_flush  ");  
}


/* ===========================================================================
 *  @func     enable_FIQ()
 *      
 *  @desc     Function enables the Fast Interrupt Queue in ARM926. Enabaling
 *            FIQ is needed for Kaliedo-Host communication. After posting a
 *            message, Kaliedo informs HOST by raising an FIQ
 *
 *  @param    None
 *
 *  @return   None
 *  ==========================================================================
 */
void enable_FIQ()
{
    /* Load SPSR in RO. Since this function is called in User mode, the User
     * mode CPSR will be saved in SPSR. Hence SPSR needs to be changed for
     * for enabling interrupts */
    __asm(" MRS     R0, SPSR");
    
    /* Set the bitfield to enable FIQ */ 
    __asm(" BIC     R0, R0, #0x40"); 
    
    /* Store back the SPSR after enabling FIQ */
    __asm(" MSR     SPSR, r0"); 
} 


/* ===========================================================================
 *  @func     Icache_Enable()
 *      
 *  @desc     Function enables the I-Cache of ARM926. Enabaling
 *            I-Cache is needed for better performance for frame level codec 
 *            operation. Nevertheless, system may also operate with I-cache ON
 *            for better efficiency.
 *
 *  @param    None
 *
 *  @return   None
 *  ==========================================================================
 */
void Icache_Enable()
{
    /* Read the CP15 cache control register in R0. For details of the intruction
     * format refer to ARM926 TRM which can be downlaoded from www.arm.com  */
    __asm(" MRC p15, #0, R0, c1, c0, #0 "); 
    
    /* Set the corresponding bit in R0 to enable I-Cache */
    __asm(" ORR R0,R0,#0x00001000 ");     
   
   /* Store back Ro to CP15 register after setting the I-Cache enable bit */
    __asm(" MCR p15, #0, R0, c1, c0, #0 "); 
}


/* ===========================================================================
 *  @func     Icache_Disable()
 *      
 *  @desc     Function disables the I-Cache of ARM926. This function is just
 *            added for debug purpose
 *
 *  @param    None
 *
 *  @return   None
 *  ==========================================================================
 */
void Icache_Disable(void)
{
     /* Read the CP15 cache control register in R0. For details of the intruction
     * format refer to ARM926 TRM which can be downlaoded from www.arm.com  */
    __asm(" MRC p15, #0, R0, c1, c0, #0 ");

    /* Set the corresponding bit in R0 to disbale I-Cache */
    __asm(" BIC R0, R0, #0x1000 ");

   /* Store back Ro to CP15 register after setting the I-Cache disable bit */
    __asm(" MCR p15, #0, R0, c1, c0, #0 ");

}


/* ===========================================================================
 *  @func     Cache_Set_RoundRobin()
 *      
 *  @desc     Function sets the cache operation mode. In a n-way set
 *            associateive cache, Cache line replacement follows one of the ,
 *            algorithm 
 *           round robin : First come, first replaced
 *           LRU: Least recently used
 *           Random: The name signifies the replacement strategy
 *
 *  @param    None
 *
 *  @return   None
 *  ==========================================================================
 */
void Cache_Set_RoundRobin(void)
{
    /* Read the CP15 cache control register in R0. For details of the intruction
     * format refer to ARM926 TRM which can be downlaoded from www.arm.com  */
    __asm(" MRC p15, #0, R0, c1, c0, #0 ");
    
    /* Set the corresponding bit in R0 to enable round robin replacement */
    __asm(" ORR R0, R0, #0x4000 ");
    
    /* Store back R0 to CP15 register after setting the Round robin mode */
    __asm(" MCR p15, #0, R0, c1, c0, #0 ");

}


/* ===========================================================================
 *  @func     Cache_Set_Random()
 *      
 *  @desc     Function sets the cache operation mode. In a n-way set
 *            associateive cache, Cache line replacement follows one of the ,
 *            algorithm 
 *           round robin : First come, first replaced
 *           LRU: Least recently used
 *           Random: The name signifies the replacement strategy
 *
 *  @param    None
 *
 *  @return   None
 *  ==========================================================================
 */
void Cache_Set_Random(void)
{
    /* Read the CP15 cache control register in R0. For details of the intruction
     * format refer to ARM926 TRM which can be downlaoded from www.arm.com  */
    __asm(" MRC p15, #0, R0, c1, c0, #0 ");
    
    /* Set the corresponding bit in R0 to enable random replacement mode */
    __asm(" BIC R0, R0, #0x4000 ");
    
    /* Store back Ro to CP15 register after setting the Cache random 
     * replacement mode */
    __asm(" MCR p15, #0, R0, c1, c0, #0 ");

}


/* ===========================================================================
 *  @func     Dcache_Enable()
 *      
 *  @desc     Function enables the D-Cache of ARM926. Enabaling
 *            D-Cache is needed for better performance for frame level codec 
 *            operation. Nevertheless, system may also operate with I-cache ON
 *            for better efficiency.
 *
 *  @param    None
 *
 *  @return   None
 *  ==========================================================================
 */
void Dcache_Enable(void)
{
    /* Read the CP15 cache control register in R0. For details of the intruction
     * format refer to ARM926 TRM which can be downlaoded from www.arm.com  */
    __asm(" MRC p15, #0, R0, c1, c0, #0 ");
    
    /* Set the corresponding bit in R0 to enable D-Cache */
    __asm(" ORR R0, R0, #0x4 ");
    
    /* Store back Ro to CP15 register after setting the D-Cache enable bit */
    __asm(" MCR p15, #0, R0, c1, c0, #0 ");

}


/* ===========================================================================
 *  @func     Dcache_Disable()
 *      
 *  @desc     Function disables the D-Cache of ARM926. This function is just
 *            added for debug purpose
 *
 *  @param    None
 *
 *  @return   None
 *  ==========================================================================
 */
void Dcache_Disable(void)
{
    /* Read the CP15 cache control register in R0. For details of the intruction
     * format refer to ARM926 TRM which can be downlaoded from www.arm.com  */
    __asm(" MRC p15, #0, R0, c1, c0, #0 ");
    
    /* Set the corresponding bit in R0 to disbale D-Cache */
    __asm(" BIC R0, R0, #0x4 ");
    
    /* Store back Ro to CP15 register after setting the D-Cache disable bit */
    __asm(" MCR p15, #0, R0, c1, c0, #0 ");

}


/* ===========================================================================
 *  @func     Flush_Icache()
 *      
 *  @desc     Function inavlidates the whole I-cache. This is helpful when we 
 *            want to re-set the I-cache state. Generally used after coming 
 *            out of application crash or just after enabling I-cache
 *
 *  @param    None
 *
 *  @return   None
 *  ==========================================================================
 */
void Flush_Icache(void)
{
    __asm(" MOV R0,#0 ");
    
    /* Store back Ro to CP15 register after setting the I-Cache invalidate bit */
    __asm(" MCR p15, #0, R0, c7, c5, #0 ");

}

/* ===========================================================================
 *  @func     Flush_Dcache()
 *      
 *  @desc     Function inavlidates the whole D-cache. This is helpful when we 
 *            want to re-set the D-cache state. Generally used after coming 
 *            out of application crash or just after enabling D-cache
 *
 *  @param    None
 *
 *  @return   None
 *  ==========================================================================
 */
void Flush_Dcache(void)
{
    __asm(" MOV R0,#0 ");
    
    /* Store back Ro to CP15 register after setting the D-Cache invalidate bit */
    __asm(" MCR p15, #0, R0, c7, c6, #0 ");
}


/* ===========================================================================
 *  @func     Enable_MMU()
 *      
 *  @desc     Function enables the MMU of ARM926. This is used to set the
 *            virtual and physical address mapping. Enabling MMU is mandatory
 *            when D-cache is enabled. Otherwise, D-cache enable has no effect
 *
 *  @param    None
 *
 *  @return   None
 *  ==========================================================================
 */
void Enable_MMU(void)
{
    /* Read the CP15 MMU control register in R0. For details of the intruction
     * format refer to ARM926 TRM which can be downlaoded from www.arm.com  */
    __asm(" MRC p15, #0, R0, c1, c0 ");
    
    /* Set the corresponding bit in R0 to enable MMU */
    __asm(" ORR R0, R0, #0x1 ");
    
    /* Store back Ro to CP15 register after setting the MMU enable bit */
    __asm(" MCR p15, #0, R0, c1, c0 ");
}


/* ===========================================================================
 *  @func     Disable_MMU()
 *      
 *  @desc     Function disables the MMU ARM926. This function is just
 *            added for debug purpose
 *
 *  @param    None
 *
 *  @return   None
 *  ==========================================================================
 */
void Disable_MMU(void)
{
    /* Read the CP15 MMU control register in R0. For details of the intruction
     * format refer to ARM926 TRM which can be downlaoded from www.arm.com  */
    __asm(" MRC p15, #0, R0, c1, c0 ");
    
    /* Set the corresponding bit in R0 to disbale MMU */
    __asm(" BIC R0, R0, #0x1 ");
    
    /* Store back Ro to CP15 register after setting the MMU disable bit */
    __asm(" MCR p15, #0, R0, c1, c0 ");
}


/* ===========================================================================
 *  @func     Set_MMU_Base()
 *      
 *  @desc     Function sets the MMU base address in TCM. In case there is no
 *            entry of a virtual address in TLB, MMU will look at the traslation
 *           table kept at the adress location(set here) for Virtual address to
 *           physical address mapping
 *
 *  @param    None
 *
 *  @return   None
 *  ==========================================================================
 */
void Set_MMU_Base(unsigned int x)
{
    /* Set the MMU base reigister. For more description. refer to section 3
     * of ARM926 Technical reference Manual */
    __asm(" MCR p15, #0, R0, c2, c0 ");
}


/* ===========================================================================
 *  @func     Set_Domains()
 *      
 *  @desc     Function sets the MMU domain register. Refer to section 3 of ARM
 *            TRM for more details of Domains
 *
 *  @param    
 *       U32 x : permission of domain
 *
 *  @return   None
 *  ==========================================================================
 */
void Set_Domains(unsigned int x)
{
    /* Set the MMU domain access reigister. Here the domain protections are 
     * removed. So there will be no permission fault generated. For more
     * description. refer to section 3 of ARM926 Technical reference Manual */
    __asm(" MCR p15, #0, R0, c3, c0 ");
}



/* ===========================================================================
 *  @func   ARM926_user_swi_handler()
 *
 *  @desc   This function is a C level SWI handler.
 *          .
 *  @param  int swi_numberNone.
 *
 *  @param  int *args - For future expansion
 *
 *  @return None
 *
 *  @note   None
 * ===========================================================================
 */
void ARM926_user_swi_handler (int swi_number, int *args)
{
    /* The SWI number is used to switch to different functions to perform
     * the desired action  */
    switch (swi_number)
    {
        case 0:
            /* Enable the MMU */
            Enable_MMU();
            break;
        case 1:
            /* Disable the MMU */
            Disable_MMU();
            break;
        case 2:
            /* Set the MMU base address */
            Set_MMU_Base(MMU_BASE);
            break;
        case 3:
            /* Set the MMU domain register to Full permission */
            Set_Domains(0xFFFFFFFF);
            break;
        case 4: 
            /* Enable the FIQ */
            enable_FIQ();
            break;
        case 5:
            /* Enable I-cache */
            Icache_Enable();
            break;
        case 6:
            /* Disable I-cache */
            Icache_Disable();
            break;
        case 7:
            /* set round robin cache replacement strategy */
            Cache_Set_RoundRobin();
            break;
        case 8:
            /* set random cache replacement strategy */
            Cache_Set_Random();
            break;
        case 9:
            /* Enable D-cache */
            Dcache_Enable();
            break;
        case 10:
            /* Disable D-cache */
            Dcache_Disable();
            break;
        case 11:
            /* Flush I-cache */
            Flush_Icache();
            break;
        case 12:
            /* Invalidate D-cache */
            Flush_Dcache();
            break;
        case 13:
            /* Clean  D-cache */
            cache_low_data_clean();
            break;
        case 14:
            /* clean and Invalidate D-cache */
            cache_low_data_clean_flush();
            break;
        default:
            break;
    } /* end switch */ 
} /* ARM926_user_swi_handler() */ 



/* ===========================================================================
 *  @func   ARM926_INTC_init()
 *
 *  @desc   This function initializes ARM926 Interrupt controller.For more
 *          details, refer to chanpter 8 of DM510 TRM
 *          .
 *  @param  None
 *
 *  @return None
 *
 *  @note   None
 * ===========================================================================
 */
void ARM926_INTC_init ()
{
    
    /*----------------------------------------------------------------------*/
    /* For details about the register and its meaning, refer to Chapter 8   */
    /* of DM510 TRM                                                         */
    /*----------------------------------------------------------------------*/
    
    /* Init INTCL : Default values is OK                                    */
    *(int *)ARM926_INTCTL = 0x0;  /* IDMODE=0, IERAW=0, FERAW=0             */
   
    /* Enable Interrupt No 28 KAL-HOST interrupt in EINT0                   */
    *(int *)ARM926_EINT0 |= BIT_28_MASK;
   
#ifdef ENABLE_DM510
    /* Set up INTPRI : default value is 7: reset it to 7                    */
    *(int *)ARM926_INTPRI3 &= KAL2HOST_INT_PRI_1;
#else //ENABLE_DM510
    /* Set up INTPRI : default value is 7: reset it to 7                    */
    *(int *)ARM926_INTPRI1 &= KAL2HOST_INT_PRI_1;
#endif //ENABLE_DM510
    
    /* EAbase is not reqd as standalone will only have 1 interrupt
     * Maybe set it to zero: Default value of 0 is OK 
     */
     *(int *)ARM926_EABASE = INT_BASE;
} /* ARM926_INTC_init() */



/*!
 *! Revision History
 *! ================
 *! 16-Sep-2007   Yashwant    : Added more comments to code.
 *! 16-Aug-2007   Kumar    : Incorporated code review comments.
 *! 11-Apr-2007   Yashwant :  Created.
 *!
 */
