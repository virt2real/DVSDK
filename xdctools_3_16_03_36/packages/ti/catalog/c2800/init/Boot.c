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
 *  Perform the following critical 28x initializations prior to cinit:
 *
 *  1) Disable the watchdog timer.
 *  2) Initialize the PLL.
 *
 *  The code below contains excerpts from the examples provided with
 *  this development platform.
 *
 */

#include <xdc/std.h>

#include "_SysCtrl.h"        /* System Control/Power Modes */
#include "_Gpio.h"
#include "_Xintf.h"

#define sysCtrlRegs (*(volatile struct SysCtrlRegs *)(0x7010))
#define xintfRegs (*(volatile XINTF_REGS *)(0x0b20))
#define gpioCtrlRegs (*(volatile struct GPIO_CTRL_REGS *)(0x6F80))

#define Boot_disableWatchdog  ti_catalog_c2800_init_Boot_disableWatchdog
#define Boot_configurePll     ti_catalog_c2800_init_Boot_configurePll
#define Boot_50usDelay        ti_catalog_c2800_init_Boot_50usDelay
#define Boot_configEzdspXintf ti_catalog_c2800_init_Boot_configEzdspXintf
#define Boot_configEzdspGpio  ti_catalog_c2800_init_Boot_configEzdspGpio

#define EALLOW asm(" EALLOW")
#define EDIS   asm(" EDIS")
#define ESTOP0 asm(" ESTOP0")

#pragma CODE_SECTION(Boot_disableWatchdog, ".bootCodeSection")
#pragma CODE_SECTION(Boot_configurePll, ".bootCodeSection")
#pragma CODE_SECTION(Boot_configEzdspXintf, ".bootCodeSection")
#pragma CODE_SECTION(Boot_configEzdspGpio, ".bootCodeSection")

extern Void Boot_50usDelay();

/*
 *  ======== Boot_disableWatchdog ========
 */
Void Boot_disableWatchdog(Void)
{
    EALLOW;
    sysCtrlRegs.WDCR |= 0x0068; /* disable it */
    sysCtrlRegs.WDKEY = 0x0055; /* service it once */
    sysCtrlRegs.WDKEY = 0x00AA; /* to be sure */
    EDIS;
}

/*
 *  ======== Boot_configurePll ========
 */
Void Boot_configurePll(UInt16 pllcrDIV, UInt16 pllstsDIVSEL)
{

    /* Make sure the PLL is not running in limp mode */
    if (sysCtrlRegs.PLLSTS.bit.MCLKSTS != 0) {
        /* 
         * Missing external clock has been detected
         * Replace this line with a call to an appropriate
         * SystemShutdown(); function.
         */
        ESTOP0;
    }
    
    /* 
     * DIVSEL MUST be 0 before PLLCR can be changed from
     * 0x0000. It is set to 0 by an external reset XRSn
     *  This puts us in 1/4
     */
    if (sysCtrlRegs.PLLSTS.bit.DIVSEL != 0) {
        EALLOW;
        sysCtrlRegs.PLLSTS.bit.DIVSEL = 0;
        EDIS;
    }
    
    /* Change the PLLCR */
    if (sysCtrlRegs.PLLCR.bit.DIV != pllcrDIV) {
        EALLOW;
        /* Before setting PLLCR turn off missing clock detect logic */
        sysCtrlRegs.PLLSTS.bit.MCLKOFF = 1;
        sysCtrlRegs.PLLCR.bit.DIV = pllcrDIV;
        EDIS;

        /*
         * Optional: Wait for PLL to lock.
         * During this time the CPU will switch to OSCCLK/2 until
         * the PLL is stable.  Once the PLL is stable the CPU will
         * switch to the new PLL value.
         * 
         * This time-to-lock is monitored by a PLL lock counter.
         * 
         * Code is not required to sit and wait for the PLL to lock.
         * However, if the code does anything that is timing critical,
         * and requires the correct clock be locked, then it is best to
         * wait until this switching has completed.
         * 
         * Wait for the PLL lock bit to be set.
         * 
         * The watchdog should be disabled before this loop, or fed within
         * the loop via ServiceDog().
         * 
         * Uncomment to disable the watchdog
         * DisableDog();
         */
        while (sysCtrlRegs.PLLSTS.bit.PLLLOCKS != 1) {
            /* Uncomment to service the watchdog */
            /* ServiceDog(); */
        }

        EALLOW;
        sysCtrlRegs.PLLSTS.bit.MCLKOFF = 0;
        EDIS;
    }
    
    /* If switching to 1/2 */
    if ((pllstsDIVSEL == 1) || (pllstsDIVSEL == 2)) {
        EALLOW;
        sysCtrlRegs.PLLSTS.bit.DIVSEL = pllstsDIVSEL;
        EDIS;
    }
    
    /* 
     * If switching to 1/1
     * First go to 1/2 and let the power settle. The time 
     *  required will depend on the system, this is only an example
     * Then switch to 1/1
     */
    if (pllstsDIVSEL == 3) {
        EALLOW;
        sysCtrlRegs.PLLSTS.bit.DIVSEL = 2;
        Boot_50usDelay();
        sysCtrlRegs.PLLSTS.bit.DIVSEL = 3;
        EDIS;
    }
}

/*
 *  ======== Boot_configEzdspGpio ========
 *  Configure the GPIO for XINTF with a 16-bit data bus.
 *  This function was taken from 'InitXintf16Gpio' in DSP2833x_Xintf.c of
 *  the 283xx examples.
 */
void Boot_configEzdspGpio()
{
     EALLOW;
     gpioCtrlRegs.GPCMUX1.bit.GPIO64 = 3;  /* XD15 */
     gpioCtrlRegs.GPCMUX1.bit.GPIO65 = 3;  /* XD14 */
     gpioCtrlRegs.GPCMUX1.bit.GPIO66 = 3;  /* XD13 */
     gpioCtrlRegs.GPCMUX1.bit.GPIO67 = 3;  /* XD12 */
     gpioCtrlRegs.GPCMUX1.bit.GPIO68 = 3;  /* XD11 */
     gpioCtrlRegs.GPCMUX1.bit.GPIO69 = 3;  /* XD10 */
     gpioCtrlRegs.GPCMUX1.bit.GPIO70 = 3;  /* XD19 */
     gpioCtrlRegs.GPCMUX1.bit.GPIO71 = 3;  /* XD8 */
     gpioCtrlRegs.GPCMUX1.bit.GPIO72 = 3;  /* XD7 */
     gpioCtrlRegs.GPCMUX1.bit.GPIO73 = 3;  /* XD6 */
     gpioCtrlRegs.GPCMUX1.bit.GPIO74 = 3;  /* XD5 */
     gpioCtrlRegs.GPCMUX1.bit.GPIO75 = 3;  /* XD4 */
     gpioCtrlRegs.GPCMUX1.bit.GPIO76 = 3;  /* XD3 */
     gpioCtrlRegs.GPCMUX1.bit.GPIO77 = 3;  /* XD2 */
     gpioCtrlRegs.GPCMUX1.bit.GPIO78 = 3;  /* XD1 */
     gpioCtrlRegs.GPCMUX1.bit.GPIO79 = 3;  /* XD0 */

     gpioCtrlRegs.GPBMUX1.bit.GPIO40 = 3;  /* XA0/XWE1n */
     gpioCtrlRegs.GPBMUX1.bit.GPIO41 = 3;  /* XA1 */
     gpioCtrlRegs.GPBMUX1.bit.GPIO42 = 3;  /* XA2 */
     gpioCtrlRegs.GPBMUX1.bit.GPIO43 = 3;  /* XA3 */
     gpioCtrlRegs.GPBMUX1.bit.GPIO44 = 3;  /* XA4 */
     gpioCtrlRegs.GPBMUX1.bit.GPIO45 = 3;  /* XA5 */
     gpioCtrlRegs.GPBMUX1.bit.GPIO46 = 3;  /* XA6 */
     gpioCtrlRegs.GPBMUX1.bit.GPIO47 = 3;  /* XA7 */

     gpioCtrlRegs.GPCMUX2.bit.GPIO80 = 3;  /* XA8 */
     gpioCtrlRegs.GPCMUX2.bit.GPIO81 = 3;  /* XA9 */
     gpioCtrlRegs.GPCMUX2.bit.GPIO82 = 3;  /* XA10 */
     gpioCtrlRegs.GPCMUX2.bit.GPIO83 = 3;  /* XA11 */
     gpioCtrlRegs.GPCMUX2.bit.GPIO84 = 3;  /* XA12 */
     gpioCtrlRegs.GPCMUX2.bit.GPIO85 = 3;  /* XA13 */
     gpioCtrlRegs.GPCMUX2.bit.GPIO86 = 3;  /* XA14 */
     gpioCtrlRegs.GPCMUX2.bit.GPIO87 = 3;  /* XA15 */
     gpioCtrlRegs.GPBMUX1.bit.GPIO39 = 3;  /* XA16 */
     gpioCtrlRegs.GPAMUX2.bit.GPIO31 = 3;  /* XA17 */
     gpioCtrlRegs.GPAMUX2.bit.GPIO30 = 3;  /* XA18 */
     gpioCtrlRegs.GPAMUX2.bit.GPIO29 = 3;  /* XA19 */

     gpioCtrlRegs.GPBMUX1.bit.GPIO34 = 3;  /* XREADY */
         gpioCtrlRegs.GPBMUX1.bit.GPIO35 = 3;  /* XRNW */
     gpioCtrlRegs.GPBMUX1.bit.GPIO38 = 3;  /* XWE0 */

     gpioCtrlRegs.GPBMUX1.bit.GPIO36 = 3;  /* XZCS0 */
     gpioCtrlRegs.GPBMUX1.bit.GPIO37 = 3;  /* XZCS7 */
     gpioCtrlRegs.GPAMUX2.bit.GPIO28 = 3;  /* XZCS6 */
     EDIS;
}

/* 
 * Configure the timing paramaters for Zone 7.
 * Notes:
 *    This function should not be executed from XINTF
 *    Adjust the timing based on the data manual and
 *    external device requirements.
 */
void Boot_configEzdspXintf(void)
{
    /* Make sure the XINTF clock is enabled */
        sysCtrlRegs.PCLKCR3.bit.XINTFENCLK = 1;

        /* Configure the GPIO for XINTF with a 16-bit data bus */
        Boot_configEzdspGpio();

    EALLOW;
    /* All Zones */
    
    /* Timing for all zones based on XTIMCLK = SYSCLKOUT */
    xintfRegs.XINTCNF2.bit.XTIMCLK = 0;
    
    /* Buffer up to 3 writes */
    xintfRegs.XINTCNF2.bit.WRBUFF = 3;
    
    /* XCLKOUT is enabled */
    xintfRegs.XINTCNF2.bit.CLKOFF = 0;
    
    /* XCLKOUT = XTIMCLK */
    xintfRegs.XINTCNF2.bit.CLKMODE = 0;

    /* 
     * Zone 7
     * When using ready, ACTIVE must be 1 or greater
     * Lead must always be 1 or greater
     */
     
    /* Zone write timing */
    xintfRegs.XTIMING7.bit.XWRLEAD = 1;
    xintfRegs.XTIMING7.bit.XWRACTIVE = 2;
    xintfRegs.XTIMING7.bit.XWRTRAIL = 1;
    
    /* Zone read timing */
    xintfRegs.XTIMING7.bit.XRDLEAD = 1;
    xintfRegs.XTIMING7.bit.XRDACTIVE = 3;
    xintfRegs.XTIMING7.bit.XRDTRAIL = 0;

    /* don't double all Zone read/write lead/active/trail timing */
    xintfRegs.XTIMING7.bit.X2TIMING = 0;

    /* Zone will not sample XREADY signal */
    xintfRegs.XTIMING7.bit.USEREADY = 0;
    xintfRegs.XTIMING7.bit.READYMODE = 0;

    /*
     * 1,1 = x16 data bus
     * 0,1 = x32 data bus
     * other values are reserved
     */
    xintfRegs.XTIMING7.bit.XSIZE = 3;
    EDIS;

   /*
    * Force a pipeline flush to ensure that the write to
    * the last register configured occurs before returning.
    */
   asm(" RPT #7 || NOP");
}

/*
 *  @(#) ti.catalog.c2800.init; 1, 0, 0,77; 2-23-2010 16:50:24; /db/ztree/library/trees/platform/platform-k32x/src/
 */

