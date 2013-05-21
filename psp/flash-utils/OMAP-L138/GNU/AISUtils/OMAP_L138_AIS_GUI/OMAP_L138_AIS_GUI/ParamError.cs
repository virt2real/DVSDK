using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

namespace OMAP_L138_AIS_GUI
{
    class ParamError
    {
        // constants
        private const int PINMUX_cnt = 20;

        // error providers
        public ErrorProvider appFiles, aisFile, generalClock, generalEntryPoint,
            periphIdealClock, periphModuleClock, pll0preDiv, pll0postDiv,
            pll0mult, pll0div1, pll0div3, pll0div7,
            pll0cpu, pll0sdram, pll0emac, sdramClock,
            sdramSdbcr, sdramSdtmr, sdramSdrsrpdexit, sdramSdrcr,
            pll1postDiv, pll1mult, pll1div1, pll1div2,
            pll1div3, pll1ddr2, ddr2Clock, ddr2phy,
            ddr2sdcr, ddr2sdtimr, ddr2sdtimr2, ddr2sdrcr,
            lpsc0enable, lpsc0disable, lpsc0syncRst, lpsc1enable,
            lpsc1disable, lpsc1syncRst, flashTiming;
        public ErrorProvider[] pinmux;

        // ref to main form
        private MainForm parent;

        public ParamError(MainForm parentSpec)
        {
            parent = parentSpec;

            // initialize all error objects

            // un-tabbed errors
            appFiles = new ErrorProvider();
            appFiles.SetIconAlignment(parent.textBoxAppFiles, ErrorIconAlignment.MiddleRight);
            appFiles.SetIconPadding(parent.textBoxAppFiles, 2);
            appFiles.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;

            aisFile = new ErrorProvider();
            aisFile.SetIconAlignment(parent.textBoxAISfile, ErrorIconAlignment.MiddleRight);
            aisFile.SetIconPadding(parent.textBoxAISfile, 2);
            aisFile.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;

            // general tab errors
            generalClock = new ErrorProvider();
            generalClock.SetIconAlignment(parent.textBoxClockSpeed, ErrorIconAlignment.MiddleRight);
            generalClock.SetIconPadding(parent.textBoxClockSpeed, 2);
            generalClock.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;

            generalEntryPoint = new ErrorProvider();
            generalEntryPoint.SetIconAlignment(parent.textBoxSpecifyEntrypoint, ErrorIconAlignment.MiddleRight);
            generalEntryPoint.SetIconPadding(parent.textBoxSpecifyEntrypoint, 2);
            generalEntryPoint.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;

            // peripheral tab errors
            periphIdealClock = new ErrorProvider();
            periphIdealClock.SetIconAlignment(parent.textBoxPeriphClockIdeal, ErrorIconAlignment.MiddleRight);
            periphIdealClock.SetIconPadding(parent.textBoxPeriphClockIdeal, 2);
            periphIdealClock.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;

            periphModuleClock = new ErrorProvider();
            periphModuleClock.SetIconAlignment(parent.textBoxPeriphModuleClock, ErrorIconAlignment.MiddleRight);
            periphModuleClock.SetIconPadding(parent.textBoxPeriphModuleClock, 2);
            periphModuleClock.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;
            
            // pll0 tab errors
            pll0preDiv = new ErrorProvider();
            pll0preDiv.SetIconAlignment(parent.textBoxPLL0preDiv, ErrorIconAlignment.MiddleRight);
            pll0preDiv.SetIconPadding(parent.textBoxPLL0preDiv, 2);
            pll0preDiv.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;

            pll0postDiv = new ErrorProvider();
            pll0postDiv.SetIconAlignment(parent.textBoxPLL0postDiv, ErrorIconAlignment.MiddleRight);
            pll0postDiv.SetIconPadding(parent.textBoxPLL0postDiv, 2);
            pll0postDiv.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;

            pll0mult = new ErrorProvider();
            pll0mult.SetIconAlignment(parent.textBoxPLL0mult, ErrorIconAlignment.MiddleRight);
            pll0mult.SetIconPadding(parent.textBoxPLL0mult, 2);
            pll0mult.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;

            pll0div1 = new ErrorProvider();
            pll0div1.SetIconAlignment(parent.textBoxPLL0div1, ErrorIconAlignment.MiddleRight);
            pll0div1.SetIconPadding(parent.textBoxPLL0div1, 2);
            pll0div1.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;

            pll0div3 = new ErrorProvider();
            pll0div3.SetIconAlignment(parent.textBoxPLL0div3, ErrorIconAlignment.MiddleRight);
            pll0div3.SetIconPadding(parent.textBoxPLL0div3, 2);
            pll0div3.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;

            pll0div7 = new ErrorProvider();
            pll0div7.SetIconAlignment(parent.textBoxPLL0div7, ErrorIconAlignment.MiddleRight);
            pll0div7.SetIconPadding(parent.textBoxPLL0div7, 2);
            pll0div7.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;

            pll0cpu = new ErrorProvider();
            pll0cpu.SetIconAlignment(parent.textBoxPLL0cpu, ErrorIconAlignment.MiddleRight);
            pll0cpu.SetIconPadding(parent.textBoxPLL0cpu, 2);
            pll0cpu.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;

            pll0sdram = new ErrorProvider();
            pll0sdram.SetIconAlignment(parent.textBoxPLL0sdram, ErrorIconAlignment.MiddleRight);
            pll0sdram.SetIconPadding(parent.textBoxPLL0sdram, 2);
            pll0sdram.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;

            pll0emac = new ErrorProvider();
            pll0emac.SetIconAlignment(parent.textBoxPLL0emac, ErrorIconAlignment.MiddleRight);
            pll0emac.SetIconPadding(parent.textBoxPLL0emac, 2);
            pll0emac.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;
            
            // sdram tab errors
            sdramClock = new ErrorProvider();
            sdramClock.SetIconAlignment(parent.textBoxSDRAMclock, ErrorIconAlignment.MiddleRight);
            sdramClock.SetIconPadding(parent.textBoxSDRAMclock, 2);
            sdramClock.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;

            sdramSdbcr = new ErrorProvider();
            sdramSdbcr.SetIconAlignment(parent.textBoxSDRAMsdbcr, ErrorIconAlignment.MiddleRight);
            sdramSdbcr.SetIconPadding(parent.textBoxSDRAMsdbcr, 2);
            sdramSdbcr.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;

            sdramSdtmr = new ErrorProvider();
            sdramSdtmr.SetIconAlignment(parent.textBoxSDRAMsdtmr, ErrorIconAlignment.MiddleRight);
            sdramSdtmr.SetIconPadding(parent.textBoxSDRAMsdtmr, 2);
            sdramSdtmr.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;

            sdramSdrsrpdexit = new ErrorProvider();
            sdramSdrsrpdexit.SetIconAlignment(parent.textBoxSDRAMsdrsrpdexit, ErrorIconAlignment.MiddleRight);
            sdramSdrsrpdexit.SetIconPadding(parent.textBoxSDRAMsdrsrpdexit, 2);
            sdramSdrsrpdexit.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;

            sdramSdrcr = new ErrorProvider();
            sdramSdrcr.SetIconAlignment(parent.textBoxSDRAMsdrcr, ErrorIconAlignment.MiddleRight);
            sdramSdrcr.SetIconPadding(parent.textBoxSDRAMsdrcr, 2);
            sdramSdrcr.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;

            // pll1 tab errors
            pll1postDiv = new ErrorProvider();
            pll1postDiv.SetIconAlignment(parent.textBoxPLL1postDiv, ErrorIconAlignment.MiddleRight);
            pll1postDiv.SetIconPadding(parent.textBoxPLL1postDiv, 2);
            pll1postDiv.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;

            pll1mult = new ErrorProvider();
            pll1mult.SetIconAlignment(parent.textBoxPLL1mult, ErrorIconAlignment.MiddleRight);
            pll1mult.SetIconPadding(parent.textBoxPLL1mult, 2);
            pll1mult.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;

            pll1div1 = new ErrorProvider();
            pll1div1.SetIconAlignment(parent.textBoxPLL1div1, ErrorIconAlignment.MiddleRight);
            pll1div1.SetIconPadding(parent.textBoxPLL1div1, 2);
            pll1div1.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;

            pll1div2 = new ErrorProvider();
            pll1div2.SetIconAlignment(parent.textBoxPLL1div2, ErrorIconAlignment.MiddleRight);
            pll1div2.SetIconPadding(parent.textBoxPLL1div2, 2);
            pll1div2.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;

            pll1div3 = new ErrorProvider();
            pll1div3.SetIconAlignment(parent.textBoxPLL1div3, ErrorIconAlignment.MiddleRight);
            pll1div3.SetIconPadding(parent.textBoxPLL1div3, 2);
            pll1div3.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;

            pll1ddr2 = new ErrorProvider();
            pll1ddr2.SetIconAlignment(parent.textBoxPLL1ddr2, ErrorIconAlignment.MiddleRight);
            pll1ddr2.SetIconPadding(parent.textBoxPLL1ddr2, 2);
            pll1ddr2.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;
            
            // ddr2 tab errors
            ddr2Clock = new ErrorProvider();
            ddr2Clock.SetIconAlignment(parent.textBoxDDR2clock, ErrorIconAlignment.MiddleRight);
            ddr2Clock.SetIconPadding(parent.textBoxDDR2clock, 2);
            ddr2Clock.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;

            ddr2phy = new ErrorProvider();
            ddr2phy.SetIconAlignment(parent.textBoxDDR2phy, ErrorIconAlignment.MiddleRight);
            ddr2phy.SetIconPadding(parent.textBoxDDR2phy, 2);
            ddr2phy.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;

            ddr2sdcr = new ErrorProvider();
            ddr2sdcr.SetIconAlignment(parent.textBoxDDR2sdcr, ErrorIconAlignment.MiddleRight);
            ddr2sdcr.SetIconPadding(parent.textBoxDDR2sdcr, 2);
            ddr2sdcr.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;

            ddr2sdtimr = new ErrorProvider();
            ddr2sdtimr.SetIconAlignment(parent.textBoxDDR2sdtimr, ErrorIconAlignment.MiddleRight);
            ddr2sdtimr.SetIconPadding(parent.textBoxDDR2sdtimr, 2);
            ddr2sdtimr.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;

            ddr2sdtimr2 = new ErrorProvider();
            ddr2sdtimr2.SetIconAlignment(parent.textBoxDDR2sdtimr2, ErrorIconAlignment.MiddleRight);
            ddr2sdtimr2.SetIconPadding(parent.textBoxDDR2sdtimr2, 2);
            ddr2sdtimr2.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;

            ddr2sdrcr = new ErrorProvider();
            ddr2sdrcr.SetIconAlignment(parent.textBoxDDR2sdrcr, ErrorIconAlignment.MiddleRight);
            ddr2sdrcr.SetIconPadding(parent.textBoxDDR2sdrcr, 2);
            ddr2sdrcr.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;

            // lpsc tab errors
            lpsc0enable = new ErrorProvider();
            lpsc0enable.SetIconAlignment(parent.textBoxLps0Enable, ErrorIconAlignment.MiddleRight);
            lpsc0enable.SetIconPadding(parent.textBoxLps0Enable, 2);
            lpsc0enable.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;

            lpsc0disable = new ErrorProvider();
            lpsc0disable.SetIconAlignment(parent.textBoxLps0Disable, ErrorIconAlignment.MiddleRight);
            lpsc0disable.SetIconPadding(parent.textBoxLps0Disable, 2);
            lpsc0disable.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;

            lpsc0syncRst = new ErrorProvider();
            lpsc0syncRst.SetIconAlignment(parent.textBoxLps0SyncRst, ErrorIconAlignment.MiddleRight);
            lpsc0syncRst.SetIconPadding(parent.textBoxLps0SyncRst, 2);
            lpsc0syncRst.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;

            lpsc1enable = new ErrorProvider();
            lpsc1enable.SetIconAlignment(parent.textBoxLps1Enable, ErrorIconAlignment.MiddleRight);
            lpsc1enable.SetIconPadding(parent.textBoxLps1Enable, 2);
            lpsc1enable.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;

            lpsc1disable = new ErrorProvider();
            lpsc1disable.SetIconAlignment(parent.textBoxLps1Disable, ErrorIconAlignment.MiddleRight);
            lpsc1disable.SetIconPadding(parent.textBoxLps1Disable, 2);
            lpsc1disable.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;

            lpsc1syncRst = new ErrorProvider();
            lpsc1syncRst.SetIconAlignment(parent.textBoxLps1SyncRst, ErrorIconAlignment.MiddleRight);
            lpsc1syncRst.SetIconPadding(parent.textBoxLps1SyncRst, 2);
            lpsc1syncRst.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;

            // pinmux tab errors
            pinmux = new ErrorProvider[PINMUX_cnt];
            for (int i = 0; i < PINMUX_cnt; i++)
            {
                pinmux[i] = new ErrorProvider();
                pinmux[i].SetIconAlignment(parent.textBoxPinmux[i], ErrorIconAlignment.MiddleRight);
                pinmux[i].SetIconPadding(parent.textBoxPinmux[i], 2);
                pinmux[i].BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;
            }

            // flash tab errors
            flashTiming = new ErrorProvider();
            flashTiming.SetIconAlignment(parent.textBoxFlashTiming, ErrorIconAlignment.MiddleRight);
            flashTiming.SetIconPadding(parent.textBoxFlashTiming, 2);
            flashTiming.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;
        }

        //public bool any()
        //{
        //    // return true if any error currently unresolved (unused)
        //    if (appFiles.GetError(parent.textBoxAppFiles) == "" &&
        //        aisFile.GetError(parent.textBoxAISfile) == "" &&
        //        generalClock.GetError(parent.textBoxClockSpeed) == "" &&
        //        generalEntryPoint.GetError(parent.textBoxSpecifyEntrypoint) == "" &&
        //        periphIdealClock.GetError(parent.textBoxPeriphClockIdeal) == "" &&
        //        periphModuleClock.GetError(parent.textBoxPeriphModuleClock) == "" &&
        //        pll0preDiv.GetError(parent.textBoxPLL0preDiv) == "" &&
        //        pll0postDiv.GetError(parent.textBoxPLL0postDiv) == "" &&
        //        pll0mult.GetError(parent.textBoxPLL0mult) == "" &&
        //        pll0div1.GetError(parent.textBoxPLL0div1) == "" &&
        //        pll0div3.GetError(parent.textBoxPLL0div3) == "" &&
        //        pll0div7.GetError(parent.textBoxPLL0div7) == "" &&
        //        pll0cpu.GetError(parent.textBoxPLL0cpu) == "" &&
        //        pll0sdram.GetError(parent.textBoxPLL0sdram) == "" &&
        //        pll0emac.GetError(parent.textBoxPLL0emac) == "" &&
        //        sdramClock.GetError(parent.textBoxSDRAMclock) == "" &&
        //        sdramSdbcr.GetError(parent.textBoxSDRAMsdbcr) == "" &&
        //        sdramSdtmr.GetError(parent.textBoxSDRAMsdtmr) == "" &&
        //        sdramSdrsrpdexit.GetError(parent.textBoxSDRAMsdrsrpdexit) == "" &&
        //        sdramSdrcr.GetError(parent.textBoxSDRAMsdrcr) == "" &&
        //        pll1postDiv.GetError(parent.textBoxPLL1postDiv) == "" &&
        //        pll1mult.GetError(parent.textBoxPLL1mult) == "" &&
        //        pll1div1.GetError(parent.textBoxPLL1div1) == "" &&
        //        pll1div2.GetError(parent.textBoxPLL1div2) == "" &&
        //        pll1div3.GetError(parent.textBoxPLL1div3) == "" &&
        //        pll1ddr2.GetError(parent.textBoxPLL1ddr2) == "" &&
        //        ddr2Clock.GetError(parent.textBoxDDR2clock) == "" &&
        //        ddr2phy.GetError(parent.textBoxDDR2phy) == "" &&
        //        ddr2sdcr.GetError(parent.textBoxDDR2sdcr) == "" &&
        //        ddr2sdtimr.GetError(parent.textBoxDDR2sdtimr) == "" &&
        //        ddr2sdtimr2.GetError(parent.textBoxDDR2sdtimr2) == "" &&
        //        ddr2sdrcr.GetError(parent.textBoxDDR2sdrcr) == "")
        //        return false;
        //    else
        //        return true;
        //}

        public bool anyGeneral()
        {
            // return true if any general tab param error currently unresolved
            if (appFiles.GetError(parent.textBoxAppFiles) == "" &&
                aisFile.GetError(parent.textBoxAISfile) == "" &&
                generalClock.GetError(parent.textBoxClockSpeed) == "" &&
                generalEntryPoint.GetError(parent.textBoxSpecifyEntrypoint) == "")
                return false;
            else
                return true;
        }

        public bool anyInputPLL0()
        {
            // return true if any PLL0 input param error currently unresolved
            if (generalClock.GetError(parent.textBoxClockSpeed) == "" &&
                pll0preDiv.GetError(parent.textBoxPLL0preDiv) == "" &&
                pll0postDiv.GetError(parent.textBoxPLL0postDiv) == "" &&
                pll0mult.GetError(parent.textBoxPLL0mult) == "" &&
                pll0div1.GetError(parent.textBoxPLL0div1) == "" &&
                pll0div3.GetError(parent.textBoxPLL0div3) == "" &&
                pll0div7.GetError(parent.textBoxPLL0div7) == "")
                return false;
            else
                return true;
        }

        public bool anyCalcPLL0()
        {
            // return true if any PLL0 calculated param error currently unresolved
            if (pll0cpu.GetError(parent.textBoxPLL0cpu) == "" &&
                pll0sdram.GetError(parent.textBoxPLL0sdram) == "" &&
                pll0emac.GetError(parent.textBoxPLL0emac) == "")
                return false;
            else
                return true;
        }

        public bool anyInputPLL1()
        {
            // return true if any PLL1 input param error currently unresolved
            if (generalClock.GetError(parent.textBoxClockSpeed) == "" &&
                pll1postDiv.GetError(parent.textBoxPLL1postDiv) == "" &&
                pll1mult.GetError(parent.textBoxPLL1mult) == "" &&
                pll1div1.GetError(parent.textBoxPLL1div1) == "" &&
                pll1div2.GetError(parent.textBoxPLL1div2) == "" &&
                pll1div3.GetError(parent.textBoxPLL1div3) == "")
                return false;
            else
                return true;
        }

        public bool anyCalcPLL1()
        {
            // return true if any PLL1 calculated param error currently unresolved
            if (pll1ddr2.GetError(parent.textBoxPLL1ddr2) == "")
                return false;
            else
                return true;
        }

        public bool anyInputPeriph()
        {
            // return true if any periph clock or flash input param error currently unresolved
            if (generalClock.GetError(parent.textBoxClockSpeed) == "" &&
                periphIdealClock.GetError(parent.textBoxPeriphClockIdeal) == "" &&
                flashTiming.GetError(parent.textBoxFlashTiming) == "")
                return false;
            else
                return true;
        }

        public bool anyCalcPeriph()
        {
            // return true if any periph clock calculated param error currently unresolved
            if (periphModuleClock.GetError(parent.textBoxPeriphModuleClock) == "")
                return false;
            else
                return true;
        }

        public bool anyInputSDRAM()
        {
            // return true if any SDRAM clock input param error currently unresolved
            if (generalClock.GetError(parent.textBoxClockSpeed) == "" &&
                pll0preDiv.GetError(parent.textBoxPLL0preDiv) == "" &&
                pll0postDiv.GetError(parent.textBoxPLL0postDiv) == "" &&
                pll0mult.GetError(parent.textBoxPLL0mult) == "" &&
                pll0div1.GetError(parent.textBoxPLL0div1) == "" &&
                pll0div1.GetError(parent.textBoxPLL0div3) == "")
                return false;
            else
                return true;
        }

        public bool anyCalcSDRAM()
        {
            // return true if any SDRAM clock calculated param error currently unresolved
            if (sdramClock.GetError(parent.textBoxSDRAMclock) == "")
                return false;
            else
                return true;
        }

        public bool anyInputDDR2()
        {
            // return true if any DDR2 input param error currently unresolved
            if (generalClock.GetError(parent.textBoxClockSpeed) == "" &&
                pll1postDiv.GetError(parent.textBoxPLL1postDiv) == "" &&
                pll1mult.GetError(parent.textBoxPLL1mult) == "" &&
                pll1div1.GetError(parent.textBoxPLL1div1) == "")
                return false;
            else
                return true;
        }

        public bool anyCalcDDR2()
        {
            // return true if any DDR2 calculated param error currently unresolved
            if (ddr2Clock.GetError(parent.textBoxDDR2clock) == "")
                return false;
            else
                return true;
        }

        public bool anyLpsc()
        {
            // return true if any lpsc list error currently unresolved
            if (lpsc0enable.GetError(parent.textBoxLps0Enable) == "" &&
                lpsc0disable.GetError(parent.textBoxLps0Disable) == "" &&
                lpsc0syncRst.GetError(parent.textBoxLps0SyncRst) == "" &&
                lpsc1enable.GetError(parent.textBoxLps1Enable) == "" &&
                lpsc1disable.GetError(parent.textBoxLps1Disable) == "" &&
                lpsc1syncRst.GetError(parent.textBoxLps1SyncRst) == "")
                return false;
            else
                return true;
        }

        public bool anyPinmux()
        {
            // return true if any pinmux error currently unresolved
            for (int i = 0; i < PINMUX_cnt; i++)
                if (pinmux[i].GetError(parent.textBoxPinmux[i]) != "")
                    return true;
            
            return false;
        }
    }
}
