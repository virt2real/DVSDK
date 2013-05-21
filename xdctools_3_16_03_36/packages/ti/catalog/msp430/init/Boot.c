/*
 *  Copyright (c) 2010 by Texas Instruments and others.
 *  All rights reserved. This program and the accompanying materials
 *  are made available under the terms of the Eclipse Public License v1.0
 *  which accompanies this distribution, and is available at
 *  http://www.eclipse.org/legal/epl-v10.html
 *
 *  Contributors:
 *      Texas Instruments - initial implementation
 *
 * */

/*
 *  ======== Boot.c ========
 *
 *  Perform the following critical 430 initializations prior to cinit:
 *
 *  1) Optionally disable the watchdog timer.
 *  2) Optionally configure the DCO and clocks.
 *
 */
#include <xdc/std.h>

#define REG(x)  (*(volatile Uns *)(x))

#define Boot_disableWatchdog  ti_catalog_msp430_init_Boot_disableWatchdog
#define Boot_configureDCO     ti_catalog_msp430_init_Boot_configureDCO

#define UCSCTL0         0x160   /* UCS control reg 0 */
#define UCSCTL1         0x162   /* UCS control reg 1 */
#define UCSCTL2         0x164   /* UCS control reg 2 */
#define UCSCTL3         0x166   /* UCS control reg 3 */
#define UCSCTL4         0x168   /* UCS control reg 4 */
#define UCSCTL7         0x16E   /* UCS control reg 7 */
#define SFRIFG1         0x102   /* interrupt flag register */

#define WDTPW           0x5a00  /* WDT password */
#define WDTHOLD         0x0080  /* WDT hold bit */

#define SELREF_2        0x20    /* FLL ref clock select */
#define SELA_2          0x200   /* ACLK source select */
#define DCORSEL_5       0x50    /* freq range select */
#define FLLD_1          0x1000  /* multiply select */
#define XT2OFFG         0x8     /* XT2 fault flag */
#define XT1LFOFFG       0x2     /* XT1 low freq fault flag */
#define XT1HFOFFG       0x4     /* XT1 high freq fault flag */
#define DCOFFG          0x1     /* DCO fault flag */
#define OFIFG           0x2     /* Osc fault flag */
#define SCG0            0x40    /* system clock generator 0 control bit  */

#pragma CODE_SECTION(Boot_disableWatchdog, ".bootCodeSection")
#pragma CODE_SECTION(Boot_configureDCO, ".bootCodeSection")

/*
 *  ======== Boot_disableWatchdog ========
 */
Void Boot_disableWatchdog(UInt address)
{
    REG(address) = WDTPW + WDTHOLD;     /* disable watchdog */
}

/*
 *  ======== Boot_configureDCO ========
 *  Initializes MSP430F54xx clocks and DCO for:
 *      ACLK = REFO = 32768Hz 
 *      MCLK = SMCLK = 12MHz
 *  Derived from the msp430x54x_UCS_3.c example. 
 */
Void Boot_configureDCO(Void)
{
    REG(UCSCTL3) |= SELREF_2;           /* set FLL ref to REF0 */
    REG(UCSCTL4) |= SELA_2;             /* set ACLK to REF0 */

    __bis_SR_register(SCG0);            /* disable FLL */
    REG(UCSCTL0) = 0x0000;              /* set lowest DCOx and MODx bits */
    REG(UCSCTL1) = DCORSEL_5;           /* select 24 MHz range */
    
    REG(UCSCTL2)  = FLLD_1 + 374;       /* 
                                           set multiplier for 12MHz:
                                               (N + 1) * FLLRef = Fdco 
                                             (374 + 1) * 32768  = 12 MHz
                                                FLL Div = fDCOCLK/2  
                                        */

    __bic_SR_register(SCG0);            /* enable FLL */

    /* 
     worst-case settling time (MCLK cylces) =  N x 32 x 32 x f_MCLK / f_FLL_ref 
                                     375000 =  32 x 32 x 12 MHz / 32768 Hz
    */
    __delay_cycles(375000);

    /* wait until XT1, XT2, and DCO fault flags are cleared... */
    do
    {
       REG(UCSCTL7) &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG);
       REG(SFRIFG1) &= ~OFIFG;
    } while (REG(SFRIFG1) &OFIFG); 

}
/*
 *  @(#) ti.catalog.msp430.init; 1, 0, 0,17; 2-23-2010 16:50:25; /db/ztree/library/trees/platform/platform-k32x/src/
 */

