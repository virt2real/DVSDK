using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Text;
using System.Windows.Forms;
using UtilLib;
using UtilLib.HexConv;
using AISGenLib;

namespace OMAP_L138_AIS_GUI
{
    public partial class MainForm : Form
    {
        // boot options
        private BootOptions options;

        // arrays to better handle pinmux tab
        public NumericUpDown[] numericUpDownPinmux;
        public TextBox[] textBoxPinmux;

        // instance variables for tab workaround
        private bool[] tabVisible;
        private TabPage[] tab;

        // error manager
        private ParamError error;

        // log stream
        private StreamWriter log;

        // INITIALIZATION ---------------------------------------------------------------------

        public MainForm()
        {
            InitializeComponent();
        }

        private void FormLoad(object sender, EventArgs e)
        {
            // setup log file
            log = new StreamWriter("AIGgen_log.txt");
            Console.SetOut(log);

            // initialize dumb tab workaround and turn off all but first tab
            tab = new TabPage[(int)Consts.Tab.num_tabs];
            tabVisible = new bool[(int)Consts.Tab.num_tabs];
            for (int i = 0; i < (int)Consts.Tab.num_tabs; i++)
            {
                tab[i] = (TabPage)tabControlConfig.GetControl(i);
                tabVisible[i] = true;
            }
            for (int i = 1; i < (int)Consts.Tab.num_tabs; i++)
                UTIL_tabHide(i);

            // setup pinmux control arrays
            UTIL_setupPinmuxArrays();

            // create error icons
            error = new ParamError(this);

            // initialize boot options and apply to forms
            options = new BootOptions();

            UTIL_refreshFields();
        }

        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            // close log file
            log.Close();
        }

        // MENU COMMAND HANDLERS --------------------------------------------------------------

        private void restoreDefaultsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            // reset active tab to General
            tabControlConfig.SelectedIndex = 0;

            // initialize boot options and apply to forms
            options = new BootOptions();

            UTIL_refreshFields();
        }

        private void saveConfigToolStripMenuItem_Click(object sender, EventArgs e)
        {
            // get new CFG file name
            bool ok;
            String cfgFileName = UTIL_getSaveFileName("Save Configuration to File",
                "Configuration files|*.cfg|All files|*.*",
                true, out ok);

            // save file name if user clicked OK
            if (ok)
                try
                {
                    options.saveToFile(cfgFileName, textBoxAppFiles.Text);
                    LOG_msg("Saved configuration to file " + cfgFileName);
                }
                catch (Exception ex)
                {
                    LOG_msg("Error saving configuration: " + ex.Message);
                }
        }

        private void loadConfigToolStripMenuItem_Click(object sender, EventArgs e)
        {
            // get existing CFG file name
            bool ok;
            String cfgFileName = UTIL_getFileName("Load Configuration from File",
                "Configuration files|*.cfg|All files|*.*",
                false, out ok);

            // save file name if user clicked OK
            if (ok)
                try
                {
                    String loadFileList;
                    options.loadFromFile(cfgFileName, out loadFileList);
                    textBoxAppFiles.Text = loadFileList;
                    LOG_msg("Loaded configuration from file " + cfgFileName);
                }
                catch (Exception ex)
                {
                    LOG_msg("Error loading configuration: " + ex.Message);
                }

            // reset active tab to General
            tabControlConfig.SelectedIndex = 0;

            // refresh form
            UTIL_refreshFields();
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            AboutForm about = new AboutForm(this.DesktopLocation.X + 120, this.DesktopLocation.Y + 100);
            about.ShowDialog();
        }

        // CHECK BOX HANDLERS -----------------------------------------------------------------

        private void checkBoxPLL0_CheckedChanged(object sender, EventArgs e)
        {
            options.configPll0 = checkBoxPLL0.Checked;

            // show or hide the PLL0 tab
            if (options.configPll0)
                UTIL_tabShow((int)Consts.Tab.pll0);
            else
                UTIL_tabHide((int)Consts.Tab.pll0);

            // update clock calculations
            CLOCK_updatePLL0clk();
        }

        private void checkBoxPLL1_CheckedChanged(object sender, EventArgs e)
        {
            options.configPll1 = checkBoxPLL1.Checked;

            // show or hide the PLL1 tab
            if (options.configPll1)
                UTIL_tabShow((int)Consts.Tab.pll1);
            else
                UTIL_tabHide((int)Consts.Tab.pll1);

            // update clock calculations
            CLOCK_updatePLL1clk();
        }

        private void checkBoxSDRAM_CheckedChanged(object sender, EventArgs e)
        {
            options.configSdram = checkBoxSDRAM.Checked;

            // show or hide the SDRAM tab
            if (options.configSdram)
                UTIL_tabShow((int)Consts.Tab.sdram);
            else
                UTIL_tabHide((int)Consts.Tab.sdram);

            // update clock calculations
            CLOCK_updateSDRAMclk();
        }

        private void checkBoxSpecifyEntrypoint_CheckedChanged(object sender, EventArgs e)
        {
            options.specifyEntrypoint = checkBoxSpecifyEntrypoint.Checked;

            // enable or disable entrypoint text box and associated error check
            if (options.specifyEntrypoint)
            {
                textBoxSpecifyEntrypoint.Enabled = true;
                textBoxSpecifyEntrypoint_TextChanged(sender, e);
            }
            else
            {
                textBoxSpecifyEntrypoint.Enabled = false;
                error.generalEntryPoint.Clear();
            }
        }

        private void checkBoxDDR2_CheckedChanged(object sender, EventArgs e)
        {
            options.configDdr2 = checkBoxDDR2.Checked;

            // show or hide the DDR2 tab
            if (options.configDdr2)
            {
                UTIL_tabShow((int)Consts.Tab.ddr2);
                // force check PLL1
                checkBoxPLL1.Checked = true;
                checkBoxPLL1.Enabled = false;
            }
            else
            {
                UTIL_tabHide((int)Consts.Tab.ddr2);
                // force un-check PLL1
                checkBoxPLL1.Checked = false;
                checkBoxPLL1.Enabled = true;
            }

            // update clock calculations
            CLOCK_updateDDR2clk();
        }

        private void checkBoxCRC_CheckedChanged(object sender, EventArgs e)
        {
            options.enableCRC = checkBoxCRC.Checked;
        }

        private void checkBoxSDRAMdiv_CheckedChanged(object sender, EventArgs e)
        {
            options.sdramDiv45 = checkBoxSDRAMdiv.Checked;
            
            // refresh SDRAM clock calculation
            CLOCK_updateSDRAMclk();
        }

        private void checkBoxDDR2directClock_CheckedChanged(object sender, EventArgs e)
        {
            options.ddr2directClk = checkBoxDDR2directClock.Checked;

            // refresh DDR2 clock calculation
            CLOCK_updateDDR2clk();
        }

        private void checkBoxPeriphSeqRead_CheckedChanged(object sender, EventArgs e)
        {
            options.enableSeqRead = checkBoxPeriphSeqRead.Checked;
        }

        private void checkBoxLPSC_CheckedChanged(object sender, EventArgs e)
        {
            options.configLpsc = checkBoxLPSC.Checked;

            // show or hide the SDRAM tab
            if (options.configLpsc)
                UTIL_tabShow((int)Consts.Tab.lpsc);
            else
                UTIL_tabHide((int)Consts.Tab.lpsc);
        }

        private void checkBoxPinmux_CheckedChanged(object sender, EventArgs e)
        {
            options.configPinmux = checkBoxPinmux.Checked;

            // show or hide the SDRAM tab
            if (options.configPinmux)
                UTIL_tabShow((int)Consts.Tab.pinmux);
            else
                UTIL_tabHide((int)Consts.Tab.pinmux);
        }

        // COMBO BOX HANDLERS -----------------------------------------------------------------

        private void comboBoxBootMode_SelectedIndexChanged(object sender, EventArgs e)
        {
            // change selected boot mode
            options.boot.select((String)comboBoxBootMode.SelectedItem);

            // update peripheral tab
            if (options.boot.isConfigurable)
            {
                // show or hide sequential read checkbox
                if (options.boot.allowSeqRead)
                    checkBoxPeriphSeqRead.Show();
                else
                    checkBoxPeriphSeqRead.Hide();

                // allow of disallow speed changes
                if (options.boot.allowSpeedChange)
                    textBoxPeriphClockIdeal.Enabled = true;
                else
                    textBoxPeriphClockIdeal.Enabled = false;

                // update ideal clock speed selection
                textBoxPeriphClockIdeal.Text = Convert.ToString(options.boot.targetSpeed);
                // force clock update (may not be called in transition from I2C0 to I2C1, etc.)
                CLOCK_updatePeriphClk();

                // change labels
                labelPeriphClock.Text = options.boot.peripheralName + " Clock:";
                labelPeriphClockHz.Text = options.boot.speedName;

                options.configPeriph = true;
                UTIL_tabShow((int)Consts.Tab.peripheral);
            }
            else
            {
                options.configPeriph = false;
                UTIL_tabHide((int)Consts.Tab.peripheral);
            }

            // update flash tab
            if (options.boot.isFlash)
            {
                // update timing
                textBoxFlashTiming.Text = FORMAT_32bHexString(options.boot.flashTiming);

                if (options.boot.isNAND)
                {
                    // force 8-bit for NAND and disable selection
                    comboBoxFlashWidth.SelectedIndex = (int)Consts.FlashWidth.eightbit;
                    comboBoxFlashWidth.Enabled = false;
                }
                else
                {
                    // allow 16-bit selection and restore previous setting
                    comboBoxFlashWidth.Enabled = true;
                    if (options.boot.flashTimingIsSixteenBit())
                        comboBoxFlashWidth.SelectedIndex = (int)Consts.FlashWidth.sixteenbit;
                    else
                        comboBoxFlashWidth.SelectedIndex = (int)Consts.FlashWidth.eightbit;
                }

                // change labels
                if (options.boot.isNOR)
                    labelFlashTiming.Text = "CS2 Setup:";
                else if (options.boot.isNAND)
                    labelFlashTiming.Text = "CS3 Setup:";

                options.configFlash = true;
                UTIL_tabShow((int)Consts.Tab.flash);
            }
            else
            {
                options.configFlash = false;
                UTIL_tabHide((int)Consts.Tab.flash);
            }
        }

        private void comboBoxBootType_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (((String)comboBoxBootType.SelectedItem).Contains("DSP"))
            {
                options.deviceType = (int)Consts.BootType.dsp;
                labelAppFile.Text = "DSP Application File:";
            }
            else
            {
                options.deviceType = (int)Consts.BootType.arm;
                labelAppFile.Text = "ARM Application File:";
            }
        }

        private void comboBoxClockSource_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (((String)comboBoxClockSource.SelectedItem).Contains("Crystal"))
                options.clockType = (int)Consts.ClockSrc.crystal;
            else
                options.clockType = (int)Consts.ClockSrc.oscillator;
        }

        private void comboBoxFlashWidth_SelectedIndexChanged(object sender, EventArgs e)
        {
            //  apply setting
            options.boot.flashWidth = comboBoxFlashWidth.SelectedIndex;

            // update timing value and refresh
            options.boot.flashTimingUpdate();
            textBoxFlashTiming.Text = FORMAT_32bHexString(options.boot.flashTiming);
        }

        // NUMERIC UP/DOWN HANDLERS -----------------------------------------------------------

        private void numericUpDownPinmux_ValueChanged(object sender, EventArgs e)
        {
            // identify caller (fall out and do nothing if not recognized)
            for (int i = 0; i < 20; i++)
                if (sender == numericUpDownPinmux[i])
                {
                    // turn on text box if a valid pinmux register is selected
                    if (numericUpDownPinmux[i].Value >= (int)Consts.PinmuxReg.min &&
                        numericUpDownPinmux[i].Value <= (int)Consts.PinmuxReg.max)
                    {
                        options.pinmuxApply[i] = true;
                        options.pinmuxReg[i] = (int)numericUpDownPinmux[i].Value;

                        textBoxPinmux[i].Enabled = true;
                        // validate text box
                        if (!VAL_isHexNum(textBoxPinmux[i].Text) ||
                            !VAL_isPinmuxDigits(textBoxPinmux[i].Text))
                            error.pinmux[i].SetError(textBoxPinmux[i],
                                "Must be a 32-bit hexadecimal number with digits 0, 1, 2, 4, or 8."); 
                    }
                    else
                    {
                        options.pinmuxApply[i] = false;
                        textBoxPinmux[i].Enabled = false;
                        // clear error
                        error.pinmux[i].Clear();
                    }
                    break;
                }
        }

        // BUTTON HANDLERS --------------------------------------------------------------------

        private void buttonBrowseFile_Click(object sender, EventArgs e)
        {
            // get app file name
            bool ok;
            String appFileName = UTIL_getFileName("Open Application File",
                "Application files|*.out|Binary Files|*.bin|All files|*.*",
                false, out ok);

            // proceed if user clicked OK
            if (ok)
            {
                // add on address if this is not a .out file
                appFileName = UTIL_addBinFileAddress(appFileName, (uint)Consts.BinAddr.boilerplate);

                // save file name (overwrite for browse button, but append for add button)
                if (sender == buttonAddFile && textBoxAppFiles.Text.Length > 0)
                    textBoxAppFiles.Text += (";" + appFileName);
                else
                    textBoxAppFiles.Text = appFileName;
            }
        }

        private void buttonAISbrowseFile_Click(object sender, EventArgs e)
        {
            // get new AIS file name
            bool ok;
            String aisFileName = UTIL_getFileName("Output AIS File",
                "AIS binary files|*.bin;*.ais|C header files|*.h;*.c|All files|*.*",
                true, out ok);

            // save file name if user clicked OK
            if (ok)
                textBoxAISfile.Text = aisFileName;
        }

        private void buttonGenerateAIS_Click(object sender, EventArgs e)
        {
            Byte[] ais;

            // clear message log
            LOG_clear();

            // check for other errors
            if (VAL_errorsRaised())
            {
                LOG_msg("One or more parameter error must be corrected.");
                return;
            }

            // check that either 1) at least one .out file is specified, or 2) an entrypoint is specified
            if (!options.specifyEntrypoint && VAL_appFileNamesAllBinary())
            {
                LOG_msg("Must specify an entrypoint or at least one COFF file.");
                return;
            }

            // set busy cursor for main processing
            this.Cursor = Cursors.WaitCursor;

            // create INI array with appropriate sections and hash entries
            INISection[] ini = INI_assemble(options.appFileName, options.appFileAddr);
            
            // generate AIS contents and save to file
            try
            {
                AISGen_OMAP_L138 devAISgen = new AISGen_OMAP_L138();

                // generate AIS
                ais = AISGen.GenAIS(null, devAISgen, ini);
                if (ais == null)
                    throw new Exception("AIS generation failed.");

                // add NOR config word
                if (options.boot.isNOR)
                    ais = FORMAT_insertConfigWord(ais);

                // convert to C array if AIS file ends in .h or .c
                if (options.aisFileName.ToLower().EndsWith(".h") || options.aisFileName.ToLower().EndsWith(".c"))
                    ais = CArray.bin2CArray(ais, 4);

                // save
                File.WriteAllBytes(options.aisFileName, ais);
                LOG_msg(String.Format("Wrote {0} bytes to file " + options.aisFileName, ais.Length));
            }
            catch (Exception ex)
            {
                // report error and abort
                LOG_msg("AIS generation aborted. " + ex.Message);
            }

            // reset cursor
            this.Cursor = Cursors.Default;
        }

        // TEXT BOX HANDLERS ------------------------------------------------------------------

        private void textBoxClockSpeed_TextChanged(object sender, EventArgs e)
        {
            // validate input
            VAL_checkRange(textBoxClockSpeed, (double)Consts.ClockIn.min, (double)Consts.ClockIn.max,
                error.generalClock, out options.inputClock);

            // update all clock calculations
            CLOCK_updatePeriphClk();
            CLOCK_updatePLL0clk();
            CLOCK_updatePLL1clk();
        }

        private void textBoxSpecifyEntrypoint_TextChanged(object sender, EventArgs e)
        {
            uint n;

            // validate input
            if (VAL_isHexNum(textBoxSpecifyEntrypoint.Text, out n))
            {
                // clear error
                error.generalEntryPoint.Clear();

                // save new entrypoint
                options.entrypoint = n;
            }
            else
            {
                // raise error
                error.generalEntryPoint.SetError(textBoxSpecifyEntrypoint,
                    "Must be a 32-bit hexadecimal number.");
            }
        }

        private void textBoxFlashTiming_TextChanged(object sender, EventArgs e)
        {
            uint n;

            // validate input
            if (VAL_isHexNum(textBoxFlashTiming.Text, out n))
            {
                // clear error
                error.flashTiming.Clear();

                // save new value
                options.boot.flashTiming = n;
                options.boot.saveFlash();
            }
            else
            {
                // raise error
                error.flashTiming.SetError(textBoxFlashTiming,
                    "Must be a 32-bit hexadecimal number.");
            }
        }
        
        private void textBoxPeriphClockIdeal_TextChanged(object sender, EventArgs e)
        {
            // validate input
            VAL_checkRange(textBoxPeriphClockIdeal, (double)options.boot.minSpeed, (double)options.boot.maxSpeed,
                error.periphIdealClock, out options.boot.targetSpeed);

            // save new input
            options.boot.saveSpeed();

            // update peripheral clock calculations
            CLOCK_updatePeriphClk();
        }

        private void textBoxPLL0preDiv_TextChanged(object sender, EventArgs e)
        {
            // validate input
            VAL_checkRange(textBoxPLL0preDiv, (int)Consts.ClockDiv.min, (int)Consts.ClockDiv.max,
                error.pll0preDiv, out options.pll0preDiv);

            // update PLL0 calculations
            CLOCK_updatePLL0clk();
        }

        private void textBoxPLL0mult_TextChanged(object sender, EventArgs e)
        {
            // validate input
            VAL_checkRange(textBoxPLL0mult, (int)Consts.ClockMult.min, (int)Consts.ClockMult.max,
                error.pll0mult, out options.pll0Mult);

            // update PLL0 calculations
            CLOCK_updatePLL0clk();
        }

        private void textBoxPLL0postDiv_TextChanged(object sender, EventArgs e)
        {
            // validate input
            VAL_checkRange(textBoxPLL0postDiv, (int)Consts.ClockDiv.min, (int)Consts.ClockDiv.max,
                error.pll0postDiv, out options.pll0postDiv);

            // update PLL0 calculations
            CLOCK_updatePLL0clk();
        }

        private void textBoxPLL0div1_TextChanged(object sender, EventArgs e)
        {
            // validate input
            VAL_checkRange(textBoxPLL0div1, (int)Consts.ClockDiv.min, (int)Consts.ClockDiv.max,
                error.pll0div1, out options.pll0div1);

            // update PLL0 calculations
            CLOCK_updatePLL0clk();
        }

        private void textBoxPLL0div3_TextChanged(object sender, EventArgs e)
        {
            // validate input
            VAL_checkRange(textBoxPLL0div3, (int)Consts.ClockDiv.min, (int)Consts.ClockDiv.max,
                error.pll0div3, out options.pll0div3);

            // update PLL0 calculations
            CLOCK_updatePLL0clk();
        }

        private void textBoxPLL0div7_TextChanged(object sender, EventArgs e)
        {
            // validate input
            VAL_checkRange(textBoxPLL0div7, (int)Consts.ClockDiv.min, (int)Consts.ClockDiv.max,
                error.pll0div7, out options.pll0div7);

            // update PLL0 calculations
            CLOCK_updatePLL0clk();
        }

        private void textBoxSDRAMsdbcr_TextChanged(object sender, EventArgs e)
        {
            uint n;

            // validate input
            if (VAL_isHexNum(textBoxSDRAMsdbcr.Text, out n))
            {
                // clear error
                error.sdramSdbcr.Clear();

                // save new entrypoint
                options.sdramSdbcr = n;
            }
            else
            {
                // raise error
                error.sdramSdbcr.SetError(textBoxSDRAMsdbcr,
                    "Must be a 32-bit hexadecimal number.");
            }
        }

        private void textBoxSDRAMsdtmr_TextChanged(object sender, EventArgs e)
        {
            uint n;

            // validate input
            if (VAL_isHexNum(textBoxSDRAMsdtmr.Text, out n))
            {
                // clear error
                error.sdramSdtmr.Clear();

                // save new entrypoint
                options.sdramSdtmr = n;
            }
            else
            {
                // raise error
                error.sdramSdtmr.SetError(textBoxSDRAMsdtmr,
                    "Must be a 32-bit hexadecimal number.");
            }
        }

        private void textBoxSDRAMsdrsrpdexit_TextChanged(object sender, EventArgs e)
        {
            uint n;

            // validate input
            if (VAL_isHexNum(textBoxSDRAMsdrsrpdexit.Text, out n))
            {
                // clear error
                error.sdramSdrsrpdexit.Clear();

                // save new entrypoint
                options.sdramSdrsrpdexit = n;
            }
            else
            {
                // raise error
                error.sdramSdrsrpdexit.SetError(textBoxSDRAMsdrsrpdexit,
                    "Must be a 32-bit hexadecimal number.");
            }
        }

        private void textBoxSDRAMsdrcr_TextChanged(object sender, EventArgs e)
        {
            uint n;

            // validate input
            if (VAL_isHexNum(textBoxSDRAMsdrcr.Text, out n))
            {
                // clear error
                error.sdramSdrcr.Clear();

                // save new entrypoint
                options.sdramSdrcr = n;
            }
            else
            {
                // raise error
                error.sdramSdrcr.SetError(textBoxSDRAMsdrcr,
                    "Must be a 32-bit hexadecimal number.");
            }
        }

        private void textBoxPLL1mult_TextChanged(object sender, EventArgs e)
        {
            // validate input
            VAL_checkRange(textBoxPLL1mult, (int)Consts.ClockMult.min, (int)Consts.ClockMult.max,
                error.pll1mult, out options.pll1Mult);

            // update PLL1 calculations
            CLOCK_updatePLL1clk();
        }

        private void textBoxPLL1postDiv_TextChanged(object sender, EventArgs e)
        {
            // validate input
            VAL_checkRange(textBoxPLL1postDiv, (int)Consts.ClockDiv.min, (int)Consts.ClockDiv.max,
                error.pll1postDiv, out options.pll1postDiv);

            // update PLL1 calculations
            CLOCK_updatePLL1clk();
        }

        private void textBoxPLL1div1_TextChanged(object sender, EventArgs e)
        {
            // validate input
            VAL_checkRange(textBoxPLL1div1, (int)Consts.ClockDiv.min, (int)Consts.ClockDiv.max,
                error.pll1div1, out options.pll1div1);

            // update PLL1 calculations
            CLOCK_updatePLL1clk();
        }

        private void textBoxPLL1div2_TextChanged(object sender, EventArgs e)
        {
            // validate input
            VAL_checkRange(textBoxPLL1div2, (int)Consts.ClockDiv.min, (int)Consts.ClockDiv.max,
                error.pll1div2, out options.pll1div2);

            // update PLL1 calculations
            CLOCK_updatePLL1clk();
        }

        private void textBoxPLL1div3_TextChanged(object sender, EventArgs e)
        {
            // validate input
            VAL_checkRange(textBoxPLL1div3, (int)Consts.ClockDiv.min, (int)Consts.ClockDiv.max,
                error.pll1div3, out options.pll1div3);

            // update PLL1 calculations
            CLOCK_updatePLL1clk();
        }

        private void textBoxDDR2phy_TextChanged(object sender, EventArgs e)
        {
            uint n;

            // validate input
            if (VAL_isHexNum(textBoxDDR2phy.Text, out n))
            {
                // clear error
                error.ddr2phy.Clear();

                // save new entrypoint
                options.ddr2Phy = n;
            }
            else
            {
                // raise error
                error.ddr2phy.SetError(textBoxDDR2phy,
                    "Must be a 32-bit hexadecimal number.");
            }
        }

        private void textBoxDDR2sdcr_TextChanged(object sender, EventArgs e)
        {
            uint n;

            // validate input
            if (VAL_isHexNum(textBoxDDR2sdcr.Text, out n))
            {
                // clear error
                error.ddr2sdcr.Clear();

                // save new entrypoint
                options.ddr2Sdcr = n;
            }
            else
            {
                // raise error
                error.ddr2sdcr.SetError(textBoxDDR2sdcr,
                    "Must be a 32-bit hexadecimal number.");
            }
        }

        private void textBoxDDR2sdtimr_TextChanged(object sender, EventArgs e)
        {
            uint n;

            // validate input
            if (VAL_isHexNum(textBoxDDR2sdtimr.Text, out n))
            {
                // clear error
                error.ddr2sdtimr.Clear();

                // save new entrypoint
                options.ddr2Sdtimr = n;
            }
            else
            {
                // raise error
                error.ddr2sdtimr.SetError(textBoxDDR2sdtimr,
                    "Must be a 32-bit hexadecimal number.");
            }
        }

        private void textBoxDDR2sdtimr2_TextChanged(object sender, EventArgs e)
        {
            uint n;

            // validate input
            if (VAL_isHexNum(textBoxDDR2sdtimr2.Text, out n))
            {
                // clear error
                error.ddr2sdtimr2.Clear();

                // save new entrypoint
                options.ddr2Sdtimr2 = n;
            }
            else
            {
                // raise error
                error.ddr2sdtimr2.SetError(textBoxDDR2sdtimr2,
                    "Must be a 32-bit hexadecimal number.");
            }
        }

        private void textBoxDDR2sdrcr_TextChanged(object sender, EventArgs e)
        {
            uint n;

            // validate input
            if (VAL_isHexNum(textBoxDDR2sdrcr.Text, out n))
            {
                // clear error
                error.ddr2sdrcr.Clear();

                // save new entrypoint
                options.ddr2Sdrcr = n;
            }
            else
            {
                // raise error
                error.ddr2sdrcr.SetError(textBoxDDR2sdrcr,
                    "Must be a 32-bit hexadecimal number.");
            }
        }

        private void textBoxLps0Enable_TextChanged(object sender, EventArgs e)
        {
            VAL_checkLpscBox(textBoxLps0Enable, error.lpsc0enable, out options.lpsc0enable, 0);
        }

        private void textBoxLps0Disable_TextChanged(object sender, EventArgs e)
        {
            VAL_checkLpscBox(textBoxLps0Disable, error.lpsc0disable, out options.lpsc0disable, 0);
        }

        private void textBoxLps0SyncRst_TextChanged(object sender, EventArgs e)
        {
            VAL_checkLpscBox(textBoxLps0SyncRst, error.lpsc0syncRst, out options.lpsc0syncRst, 0);
        }

        private void textBoxLps1Enable_TextChanged(object sender, EventArgs e)
        {
            VAL_checkLpscBox(textBoxLps1Enable, error.lpsc1enable, out options.lpsc1enable, 1);
        }

        private void textBoxLps1Disable_TextChanged(object sender, EventArgs e)
        {
            VAL_checkLpscBox(textBoxLps1Disable, error.lpsc1disable, out options.lpsc1disable, 1);
        }

        private void textBoxLps1SyncRst_TextChanged(object sender, EventArgs e)
        {
            VAL_checkLpscBox(textBoxLps1SyncRst, error.lpsc1syncRst, out options.lpsc1syncRst, 1);
        }

        private void textBoxPinmuxVal_TextChanged(object sender, EventArgs e)
        {
            uint n;

            // identify caller (fall out and do nothing if not recognized)
            for (int i = 0; i < 20; i++)
                if (sender == textBoxPinmux[i])
                {
                    // validate input
                    if (VAL_isHexNum(textBoxPinmux[i].Text, out n) && VAL_isPinmuxDigits(textBoxPinmux[i].Text))
                    {
                        // save value
                        options.pinmuxVal[i] = Convert.ToUInt32(textBoxPinmux[i].Text, 16);

                        // clear error
                        error.pinmux[i].Clear();
                    }
                    else
                    {
                        // raise error
                        error.pinmux[i].SetError(textBoxPinmux[i],
                            "Must be a 32-bit hexadecimal number with digits 0, 1, 2, 4, or 8.");
                    }

                    break;
                }
        }

        private void textBoxAppFiles_TextChanged(object sender, EventArgs e)
        {
            VAL_checkAppFileNames(textBoxAppFiles.Text);
        }

        private void textBoxAISfile_TextChanged(object sender, EventArgs e)
        {
            options.aisFileName = textBoxAISfile.Text;
            VAL_checkAisFileName(options.aisFileName);
        }

        // CLOCK CALCULATION -------------------------------------------------------------

        private void CLOCK_updatePeriphClk()
        {
            int psc, div;
            double modClk, maxModClk, pscClk, actualClk;

            // check for input errors before beginning (check pll0 errors only if pll0 configured)
            if ( error.anyInputPeriph() || (options.configPll0 && error.anyInputPLL0()) )
            {
                // clear calculated fields
                textBoxPeriphModuleClock.Clear();
                textBoxPeriphClockActual.Clear();

                // clear calculation errors and return (input errors already prevent AIS generation)
                error.periphModuleClock.Clear();
                return;
            }
            else
            {
                // find module clock; use PLL0 configuration or assume bypass
                CLOCK_findModuleClk(out modClk, out maxModClk);
            }

            // display module clock
            textBoxPeriphModuleClock.Text = modClk.ToString("f2");
            // raise error if out of range (and abort divisor calculation)
            VAL_checkRange(textBoxPeriphModuleClock, (double)Consts.ClockI2Cmod.min, maxModClk,
                error.periphModuleClock, out modClk);
            if (error.periphModuleClock.GetError(textBoxPeriphModuleClock) != "")
            {
                textBoxPeriphClockActual.Clear();
                return;
            }

            // find divisor(s) and actual speed
            if (options.boot.isI2c)
            {
                CLOCK_findI2Cdivs(modClk, out psc, out div, out pscClk, out actualClk);

                // raise error and abort if pre-scaled module clock falls outside 7-13 MHz range
                if (pscClk < 7.0 || pscClk > 13.0)
                {
                    error.periphModuleClock.SetError(textBoxPeriphModuleClock,
                        "Must allow division to 7-13 MHz range with integer divisor.");
                    textBoxPeriphClockActual.Clear();
                    return;
                }
            }
            else if (options.boot.isSpi)
                CLOCK_findSPIdivs(modClk, out psc, out div, out actualClk);
            else if (options.boot.isUart)
                CLOCK_findUARTdivs(modClk, out psc, out div, out actualClk);
            else
                return; // invalid mode; should never come here

            // show actual speed
            textBoxPeriphClockActual.Text = actualClk.ToString("f2");

            // save divisors
            options.boot.psc = psc;
            options.boot.div = div;

            // DEBUG: display divisor values we arrived at
            //LOG_msg(String.Format("Using (psc, div) = ({0}, {1})", psc, div));
        }

        public void CLOCK_findModuleClk(out double modClk, out double maxModClk)
        {
            // find sys clocks for bypass clock or configured pll0
            double sysClk2, sysClk4, auxClk;

            try
            {
                sysClk2 = (options.configPll0) ? (Convert.ToDouble(textBoxPLL0cpu.Text) / 2.0) :
                    (Convert.ToDouble(textBoxClockSpeed.Text) / 2.0);
                sysClk4 = (options.configPll0) ? (Convert.ToDouble(textBoxPLL0cpu.Text) / 4.0) :
                    (Convert.ToDouble(textBoxClockSpeed.Text) / 4.0);
                auxClk = (options.configPll0) ? Convert.ToDouble(textBoxClockSpeed.Text) :
                    (Convert.ToDouble(textBoxClockSpeed.Text));
            }
            catch
            {
                // most likely error: pll0 text boxes are not set yet.  Abort and let pll0 update
                // re-call this function
                modClk = 0.0;
                maxModClk = 0.0;
                return;
            }

            // find module clock
            if (options.boot.name.Contains("I2C0"))
            {
                modClk = auxClk;
                maxModClk = (double)Consts.ClockAUX.max;
            }
            else if (options.boot.name.Contains("I2C1"))
            {
                modClk = sysClk4;
                maxModClk = (double)Consts.ClockSYS4.max;
            }
            else if (options.boot.isSpi || options.boot.isUart)
            {
                modClk = sysClk2;
                maxModClk = (double)Consts.ClockSYS2.max;
            }
            else
            {
                modClk = 0.0; // invalid boot mode
                maxModClk = 0.0;
            }
        }

        public void CLOCK_findI2Cdivs(double modClk, out int psc, out int div, out double pscClk, out double actualClk)
        {
            int divAdd;

            // find psc (target 10 MHz psc clk)
            psc = Convert.ToInt32(modClk / 10.0);
            // enforce minimum 1
            if (psc < 1) psc = 1;
            pscClk = modClk / (double)psc;

            // find div
            if (psc > 2)
                divAdd = 5;
            else if (psc == 2)
                divAdd = 6;
            else
                divAdd = 7;

            div = (int)(1000.0 * pscClk / options.boot.targetSpeed / 2.0 - divAdd);
            // enforce minimum 1
            if (div < 1) div = 1;

            // find actual speed
            actualClk = 1000.0 * pscClk / (2.0 * (div + divAdd));
        }

        public void CLOCK_findSPIdivs(double modClk, out int psc, out int div, out double actualClk)
        {
            // find psc
            psc = (int)(modClk / options.boot.targetSpeed);
            // enforce minimum 2
            if (psc < 2) psc = 2;

            // force div to 1 (not used)
            div = 1;

            // find actual speed
            actualClk = modClk / (double)psc;
        }

        public void CLOCK_findUARTdivs(double modClk, out int psc, out int div, out double actualClk)
        {
            // force psc to 1 (not used)
            psc = 1;

            // find div
            div = (int)(modClk * 1000000.0 / (options.boot.targetSpeed * 13.0));
            // enforce minimum 1
            if (div < 1) div = 1;

            // find actual speed
            actualClk = modClk * 1000000.0 / (div * 13.0);
        }

        private void CLOCK_updatePLL0clk()
        {
            // check for input errors before beginning
            if (error.anyInputPLL0())
            {
                // clear calculated fields
                textBoxPLL0cpu.Clear();
                textBoxPLL0emac.Clear();

                // clear calculation errors (input errors already prevent AIS generation)
                error.pll0cpu.Clear();
                error.pll0emac.Clear();
            }
            else
            {
                // compute fields and fill in text boxes
                double pllCore = options.inputClock / (double)options.pll0preDiv
                    * (double)options.pll0Mult / (double)options.pll0postDiv;
                double sysClk1 = pllCore / (double)options.pll0div1;
                double sysClk7 = pllCore / (double)options.pll0div7;

                textBoxPLL0cpu.Text = sysClk1.ToString("f2");
                // raise error if out of range
                VAL_checkRange(textBoxPLL0cpu, (double)Consts.ClockCPU.min,
                    (double)Consts.ClockCPU.max, error.pll0cpu, out sysClk1);

                textBoxPLL0emac.Text = sysClk7.ToString("f2");
                // raise error if out of range
                VAL_checkRange(textBoxPLL0emac, (double)Consts.ClockEMAC.min,
                    (double)Consts.ClockEMAC.max, error.pll0emac, out sysClk7);
            }

            // update SDRAM clock and peripheral clocks
            CLOCK_updateSDRAMclk();
            CLOCK_updatePeriphClk();
        }

        private void CLOCK_updatePLL1clk()
        {
            // note: no PLL1 clocks calculated except DDR2
            
            // update DDR2 clock
            CLOCK_updateDDR2clk();
        }

        private void CLOCK_updateSDRAMclk()
        {
            // check for input errors before beginning
            if (error.anyInputSDRAM())
            {
                // clear calculated fields
                textBoxPLL0sdram.Clear();
                textBoxSDRAMclock.Clear();
                
                // clear calculation errors (input errors already prevent AIS generation)
                error.pll0sdram.Clear();
                error.sdramClock.Clear();
            }
            else
            {
                // compute fields and fill in text boxes
                double pllCore = options.inputClock;
                if (options.configPll0)
                    pllCore = pllCore / (double)options.pll0preDiv
                        * (double)options.pll0Mult / (double)options.pll0postDiv;

                // divide by div3 or 4.5 depending on checkbox
                double sysClk3 = (checkBoxSDRAMdiv.Checked) ? (pllCore / 4.5)
                    : (pllCore / (double)options.pll0div3);

                textBoxPLL0sdram.Text = sysClk3.ToString("f2");
                // raise error if out of range
                VAL_checkRange(textBoxPLL0sdram, (double)Consts.ClockSDRAM.min,
                    (double)Consts.ClockSDRAM.max, error.pll0sdram, out sysClk3);

                textBoxSDRAMclock.Text = sysClk3.ToString("f2");
                // raise error if out of range
                VAL_checkRange(textBoxSDRAMclock, (double)Consts.ClockSDRAM.min,
                    (double)Consts.ClockSDRAM.max, error.sdramClock, out sysClk3);
            }
        }

        private void CLOCK_updateDDR2clk()
        {
            // check for input errors before beginning
            if (error.anyInputDDR2())
            {
                // clear calculated fields
                textBoxPLL1ddr2.Clear();
                textBoxDDR2clock.Clear();

                // clear calculation errors (input errors already prevent AIS generation)
                error.pll1ddr2.Clear();
                error.ddr2Clock.Clear();
            }
            else
            {
                // compute fields and fill in text boxes
                double pllCore = options.inputClock * (double)options.pll1Mult;
                // skip division if checkbox says so
                double sysClk1 = (checkBoxDDR2directClock.Checked) ? pllCore :
                    (pllCore / (double)options.pll1postDiv / (double)options.pll1div1);

                textBoxPLL1ddr2.Text = sysClk1.ToString("f2");
                // raise error if out of range
                VAL_checkRange(textBoxPLL1ddr2, (double)Consts.ClockDDR2.min,
                    (double)Consts.ClockDDR2.max, error.pll1ddr2, out sysClk1);

                textBoxDDR2clock.Text = sysClk1.ToString("f2");
                // raise error if out of range
                VAL_checkRange(textBoxDDR2clock, (double)Consts.ClockDDR2.min,
                    (double)Consts.ClockDDR2.max, error.ddr2Clock, out sysClk1);
            }
        }

        // AIS GENERATION ----------------------------------------------------------------

        private INISection[] INI_assemble(String[] appFileName, uint[] appFileAddr)
        {
            List<INISection> streamSections = new List<INISection>();
            bool entryPointSet = false;

            // 1. General section
            streamSections.Add(INI_generalSection(ref entryPointSet));

            // 2. Binary/Object file sections
            for (int i = 0; i < appFileName.Length; i++)
            {
                if (appFileName[i].ToLower().EndsWith(".out"))
                    streamSections.Add(INI_objectInputFileSection(appFileName[i], ref entryPointSet));
                else
                    streamSections.Add(INI_binaryInputFileSection(appFileName[i], appFileAddr[i]));
            }

            // 3. PLL0 and peripheral config
            if (options.configPeriph && options.configPll0)
                streamSections.Add(INI_pll0andPeriphConfigSection());
            else if (options.configPeriph)
                streamSections.Add(INI_periphConfigSection());
            else if (options.configPll0)
                streamSections.Add(INI_pll0configSection());

            // 4. PLL1 and DDR2 config
            if (options.configDdr2)
                streamSections.Add(INI_ddr2configSection());
            else if (options.configPll1)
                streamSections.Add(INI_pll1configSection());

            // 5. SDRAM config
            if (options.configSdram)
                streamSections.Add(INI_sdramConfigSection());

            // 6. SDRAM chip select config?
            if (options.boot.isFlash)
                streamSections.Add(INI_sdramCsSection());

            // 7. LPSC config
            if (options.configLpsc)
            {
                for (int i = 0; i < options.lpsc0enable.Length; i++)
                    streamSections.Add(INI_lpscConfigSection(0, options.lpsc0enable[i], (int)Consts.LpscDomain.enable));
                for (int i = 0; i < options.lpsc0disable.Length; i++)
                    streamSections.Add(INI_lpscConfigSection(0, options.lpsc0disable[i], (int)Consts.LpscDomain.disable));
                for (int i = 0; i < options.lpsc0syncRst.Length; i++)
                    streamSections.Add(INI_lpscConfigSection(0, options.lpsc0syncRst[i], (int)Consts.LpscDomain.syncRst));
                for (int i = 0; i < options.lpsc1enable.Length; i++)
                    streamSections.Add(INI_lpscConfigSection(1, options.lpsc1enable[i], (int)Consts.LpscDomain.enable));
                for (int i = 0; i < options.lpsc1disable.Length; i++)
                    streamSections.Add(INI_lpscConfigSection(1, options.lpsc1disable[i], (int)Consts.LpscDomain.disable));
                for (int i = 0; i < options.lpsc1syncRst.Length; i++)
                    streamSections.Add(INI_lpscConfigSection(1, options.lpsc1syncRst[i], (int)Consts.LpscDomain.syncRst));
            }

            // 8. Pinmux config
            if (options.configPinmux)
                for (int i = 0; i < 20; i++)
                    if (options.pinmuxApply[i])
                        streamSections.Add(INI_pinmuxConfigSection(options.pinmuxReg[i], options.pinmuxVal[i]));

            // return ini sections in array
            return streamSections.ToArray();
        }

        private INISection INI_generalSection(ref bool entryPointSet)
        {
            INISection section = new INISection();
            section.sectionValues = new Hashtable();

            section.iniSectionName = "GENERAL";
            section.sectionValues["BUSWIDTH"] = (uint)8;  // TODO: make configurable (NOR, NAND)
            section.sectionValues["BOOTMODE"] = "NONE";  // TODO: make configurable (NOR)
            if (options.enableCRC)
                section.sectionValues["CRCCHECKTYPE"] = "SECTION_CRC";
            else
                section.sectionValues["CRCCHECKTYPE"] = "NO_CRC";
            if (options.enableSeqRead)
                section.sectionValues["SEQREADEN"] = "ON";
            if (options.specifyEntrypoint)
            {
                section.sectionValues["ENTRYPOINT"] = options.entrypoint;
                entryPointSet = true;
            }

            return section;
        }

        private INISection INI_binaryInputFileSection(String fileName, uint addr)
        {
            INISection section = new INISection();
            section.sectionValues = new Hashtable();

            section.iniSectionName = "BINARYINPUTFILE";

            section.sectionValues["FILENAME"] = fileName;
            section.sectionValues["LOADADDRESS"] = addr;

            return section;
        }

        private INISection INI_objectInputFileSection(String fileName, ref bool entryPointSet)
        {
            INISection section = new INISection();
            section.sectionValues = new Hashtable();

            section.iniSectionName = "OBJECTINPUTFILE";

            section.sectionValues["FILENAME"] = fileName;
            if (!entryPointSet)
            {
                // only use entrypoint from first obj file
                section.sectionValues["USEENTRYPOINT"] = "TRUE";
                entryPointSet = true;
            }

            return section;
        }

        private INISection INI_pll0configSection()
        {
            INISection section = new INISection();
            section.sectionValues = new Hashtable();
            uint cfg0, cfg1;

            section.iniSectionName = "PLL0CONFIG";

            // assemble config words
            cfg0 = FORMAT_configWordBlob(options.clockType, options.pll0Mult - 1,
                options.pll0preDiv - 1, options.pll0postDiv - 1);
            cfg1 = FORMAT_configWordBlob(0, options.pll0div1 - 1,
                options.pll0div3 - 1, options.pll0div7 - 1);

            section.sectionValues["PLL0CFG0"] = cfg0;
            section.sectionValues["PLL0CFG1"] = cfg1;

            return section;

            //; PLL0CFG0: | CLKMODE| PLLM   | PREDIV | POSTDIV|
            //; PLL0CFG1: | RSVD   | PLLDIV1| PLLDIV3| PLLDIV7|
            //[PLL0CONFIG]
            //PLL0CFG0 = 0x00130001
            //PLL0CFG1 = 0x00000104
        }

        private INISection INI_periphConfigSection()
        {
            INISection section = new INISection();
            section.sectionValues = new Hashtable();
            uint cfg;

            section.iniSectionName = "PERIPHCLKCFG";

            // assemble config word
            if (options.boot.isI2c)
                cfg = FORMAT_configWordBlob(0, options.boot.psc - 1,
                    options.boot.div, options.boot.div);
            else if (options.boot.isSpi)
                cfg = FORMAT_configWordBlob(0, 0, 0, options.boot.psc - 1);
            else if (options.boot.isUart)
                cfg = FORMAT_configWordBlob(0, 1, options.boot.div >> 8, options.boot.div);
            else
                cfg = 0; // should never reach here

            section.sectionValues["PERIPHCLKCFG"] = cfg;

            return section;

            //; SPI:        |------24|------16|-------8|-------0|
            //;             |           RSVD           |PRESCALE|
            //;
            //; I2C:        |------24|------16|-------8|-------0|
            //;             |  RSVD  |PRESCALE|  CLKL  |  CLKH  |
            //;
            //; UART:       |------24|------16|-------8|-------0|
            //;             | RSVD   |  OSR   |  DLH   |  DLL   |
            //[PERIPHCLKCFG]
            //PERIPHCLKCFG = 0x00000000
        }

        private INISection INI_pll0andPeriphConfigSection()
        {
            // combine pll0 and periph config sections
            INISection sectionA = INI_pll0configSection();
            INISection sectionB = INI_periphConfigSection();

            sectionA.iniSectionName = "PLLANDCLOCKCONFIG";
            sectionA.sectionValues["PERIPHCLKCFG"] = sectionB.sectionValues["PERIPHCLKCFG"];

            return sectionA;
        }

        private INISection INI_pll1configSection()
        {
            INISection section = new INISection();
            section.sectionValues = new Hashtable();
            uint cfg0, cfg1;

            section.iniSectionName = "PLL1CONFIG";

            // assemble config words
            cfg0 = FORMAT_configWordBlob(options.pll1Mult - 1, options.pll1postDiv - 1,
                options.pll1div1 - 1, options.pll1div2 - 1);
            cfg1 = FORMAT_configWordBlob(0, 0, 0, options.pll1div3 - 1);

            section.sectionValues["PLL1CFG0"] = cfg0;
            section.sectionValues["PLL1CFG1"] = cfg1;

            return section;

            //;           |------24|------16|-------8|-------0|
            //; PLL1CFG0: |    PLLM| POSTDIV| PLLDIV1| PLLDIV2|
            //; PLL1CFG1: |           RSVD           | PLLDIV3|
            //[PLL1CONFIG]
            //PLL1CFG0 = 0x00000000
            //PLL1CFG1 = 0x00000000
        }

        private INISection INI_ddr2configSection()
        {
            // start with PLL1 config section
            INISection section = INI_pll1configSection();

            section.iniSectionName = "EMIF3DDR";

            section.sectionValues["DDRPHYC1R"] = options.ddr2Phy;
            section.sectionValues["SDCR"] = options.ddr2Sdcr;
            section.sectionValues["SDTIMR"] = options.ddr2Sdtimr;
            section.sectionValues["SDTIMR2"] = options.ddr2Sdtimr2;
            section.sectionValues["SDRCR"] = options.ddr2Sdrcr;
            if (options.ddr2directClk)
                section.sectionValues["CLK2XSRC"] = (uint)1;
            else
                section.sectionValues["CLK2XSRC"] = (uint)0;

            return section;

            //[EMIF3DDR]
            //PLL1CFG0 = 0x13010001
            //PLL1CFG1 = 0x00000002
            //DDRPHYC1R = 0x000000C4
            //SDCR = 0x08134632
            //SDTIMR = 0x26922A09
            //SDTIMR2 = 0x0014C722
            //SDRCR = 0x00000492
            //CLK2XSRC = 0x00000000
        }

        private INISection INI_sdramConfigSection()
        {
            INISection section = new INISection();
            section.sectionValues = new Hashtable();

            section.iniSectionName = "EMIF25SDRAM";

            section.sectionValues["SDBCR"] = options.sdramSdbcr;
            section.sectionValues["SDTIMR"] = options.sdramSdtmr;
            section.sectionValues["SDRSRPDEXIT"] = options.sdramSdrsrpdexit;
            section.sectionValues["SDRCR"] = options.sdramSdrcr;
            if (options.sdramDiv45)
                section.sectionValues["DIV4P5_CLK_ENABLE"] = (uint)1;
            else
                section.sectionValues["DIV4P5_CLK_ENABLE"] = (uint)0;

            return section;

            //[EMIF25SDRAM]
            //SDBCR = 0x00004421
            //SDTIMR = 0x42215810
            //SDRSRPDEXIT = 0x00000009
            //SDRCR = 0x00000410
            //DIV4p5_CLK_ENABLE = 0x00000001
        }

        private INISection INI_sdramCsSection()
        {
            INISection section = new INISection();
            section.sectionValues = new Hashtable();

            section.iniSectionName = "EMIF25ASYNC";

            if (options.boot.isNOR)
            {
                section.sectionValues["A1CR"] = options.boot.flashTiming;
                section.sectionValues["A2CR"] = (uint)0;
            }
            else if (options.boot.isNAND)
            {
                section.sectionValues["A1CR"] = (uint)0;
                section.sectionValues["A2CR"] = options.boot.flashTiming;
            }
            else
            {
                section.sectionValues["A1CR"] = (uint)0;
                section.sectionValues["A2CR"] = (uint)0;
            }

            section.sectionValues["A3CR"] = (uint)0;
            section.sectionValues["A4CR"] = (uint)0;

            if (options.boot.isNAND)
                section.sectionValues["NANDFCR"] = (uint)0x00000002;
            else
                section.sectionValues["NANDFCR"] = (uint)0;

            return section;

            //[EMIF25ASYNC]
            //A1CR = 0x00000000
            //A2CR = 0x00000000
            //A3CR = 0x00000000
            //A4CR = 0x00000000
            //NANDFCR = 0x00000000
        }

        private INISection INI_lpscConfigSection(int psc, int module, int state)
        {
            INISection section = new INISection();
            section.sectionValues = new Hashtable();
            uint cfg;
            int pd;

            // set pd to 1 for special cases: (psc, module) = (0, 15) or (1, 31)
            if ((psc == 0 && module == 15) || (psc == 1 && module == 31))
                pd = 1;
            else
                pd = 0;

            section.iniSectionName = "PSCCONFIG";

            cfg = FORMAT_configWordBlob(psc, module, pd, state);
            section.sectionValues["LPSCCFG"] = cfg;

            return section;

            //;           |------24|------16|-------8|-------0|
            //; LPSCCFG:  | PSCNUM | MODULE |   PD   | STATE  |
            //[PSCCONFIG]
            //LPSCCFG = 0x01030003
        }

        private INISection INI_pinmuxConfigSection(int reg, uint val)
        {
            INISection section = new INISection();
            section.sectionValues = new Hashtable();

            section.iniSectionName = "PINMUX";

            section.sectionValues["REGNUM"] = (uint)reg;
            section.sectionValues["VALUE"] = val;
            section.sectionValues["MASK"] = FORMAT_pinmuxMask(val);

            return section;

            //[PINMUX]
            //REGNUM = 5
            //MASK = 0x00FF0000
            //VALUE = 0x00880000
        }

        // INPUT VALIDATION AND FORMAT ---------------------------------------------------

        private void VAL_checkRange(TextBox box, int min, int max, ErrorProvider err, out int y)
        {
            if (VAL_isRangeNum(box.Text, min, max, out y))
            {
                // clear error
                err.Clear();
            }
            else
            {
                // raise error
                err.SetError(box,
                    String.Format("Must be a number between {0} and {1}.",
                    min, max));
            }
        }

        private void VAL_checkRange(TextBox box, double min, double max, ErrorProvider err, out double y)
        {
            if (VAL_isRangeNum(box.Text, min, max, out y))
            {
                // clear error
                err.Clear();
            }
            else
            {
                // raise error
                err.SetError(box,
                    String.Format("Must be a number between {0:f2} and {1:f2}.",
                    min, max));
            }
        }

        private bool VAL_isRangeNum(String text, int min, int max, out int n)
        {
            // convert text to integer and check if it's in specified range

            try
            {
                n = Convert.ToInt32(text);
                if (n <= max && n >= min)
                    return true;
                else
                    return false;
            }
            catch
            {
                // most likely exception: improperly formatted string
                n = 0;
                return false;
            }
        }

        private bool VAL_isRangeNum(String text, double min, double max, out double n)
        {
            // convert text to integer and check if it's in specified range

            try
            {
                n = Convert.ToDouble(text);
                if (n <= max && n >= min)
                    return true;
                else
                    return false;
            }
            catch
            {
                // most likely exception: improperly formatted string
                n = 0;
                return false;
            }
        }

        private bool VAL_isHexNum(String text, out uint n)
        {
            // convert text to hex integer and check if it fits in 32-bit limit

            try
            {
                n = Convert.ToUInt32(text, 16);
                return true;
            }
            catch
            {
                // most likely exception: improperly formatted string OR out of bounds
                n = 0;
                return false;
            }
        }

        private bool VAL_isHexNum(String text)
        {
            // convert text to hex integer and check if it fits in 32-bit limit
            uint n;

            try
            {
                n = Convert.ToUInt32(text, 16);
                return true;
            }
            catch
            {
                // most likely exception: improperly formatted string OR out of bounds
                n = 0;
                return false;
            }
        }

        private bool VAL_isPinmuxDigits(String text)
        {
            for (int i = 0; i < text.Length; i++)

                if (text[i] != '0' && text[i] != '1' && text[i] != '2' && text[i] != '4'
                    && text[i] != '8' && text[i] != 'x' && text[i] != 'X')
                    return false;

            return true;
        }

        private void VAL_checkLpscBox(TextBox box, ErrorProvider err, out int[] storage, int lpscNum)
        {
            char[] numSeparators = { ';' };
            int min, max;

            if (lpscNum == 0)
            {
                min = (int)Consts.LpscDomain.min0;
                max = (int)Consts.LpscDomain.max0;
            }
            else if (lpscNum == 1)
            {
                min = (int)Consts.LpscDomain.min1;
                max = (int)Consts.LpscDomain.max1;
            }
            else
            {
                // invalid
                min = 2;
                max = 1;
            }

            // clear error
            err.Clear();

            // break up text into ; separated strings
            String[] domain = box.Text.Split(numSeparators, StringSplitOptions.RemoveEmptyEntries);
            int domainCnt = domain.Length;

            // create new array to store power domains
            storage = new int[domainCnt];

            // abort if no numbers
            if (domainCnt < 1) return;

            // validate substrings (numeric)
            for (int i = 0; i < domainCnt; i++)
            {
                if (VAL_isRangeNum(domain[i], min, max, out storage[i]))
                {
                    // VAL_isRangeNum saves domain number to array
                }
                else
                {
                    // raise error
                    err.SetError(box, String.Format(
                        "Must list LPSC numbers between {0} and {1} separated by \';\'",
                        min, max));

                    break;
                }
            }
        }

        private void VAL_checkAppFileNames(String text)
        {
            int i, j, appFileCnt;
            char[] fileNameSeparators = { ';' };
            char fileAddrMarker = '@';

            // clear error to start
            error.appFiles.Clear();

            // check for zero-length input first
            if (text.Length == 0)
            {
                error.appFiles.SetError(textBoxAppFiles, "Must specify at least one application file.");
                return;
            }

            // break up string into array of file names (separated by ";")
            options.appFileName = text.Split(fileNameSeparators, StringSplitOptions.RemoveEmptyEntries);
            appFileCnt = options.appFileName.Length;
            options.appFileAddr = new uint[appFileCnt];

            // fail if no file names found (i.e. textbox all ";;;;")
            if (appFileCnt < 1)
            {
                error.appFiles.SetError(textBoxAppFiles, "Must specify at least one application file.");
                return;
            }

            // check files for specified load addresses ("file.bin@<hex addr>")
            for (i = 0; i < appFileCnt; i++)
            {
                j = options.appFileName[i].IndexOf(fileAddrMarker);

                // save address (and remove from file name) if one is present
                if (j != -1)
                {
                    try
                    {
                        // save address
                        options.appFileAddr[i] = Convert.ToUInt32(options.appFileName[i].Substring(j + 1), 16);
                    }
                    catch
                    {
                        // numeric conversion failed; invalid address specification
                        
                        error.appFiles.SetError(textBoxAppFiles,
                            "Invalid address specified: " + options.appFileName[i].Substring(j + 1));
                        return;
                    }

                    // remove address from file name
                    options.appFileName[i] = options.appFileName[i].Remove(j);
                }
                else
                    options.appFileAddr[i] = (uint)Consts.BinAddr.invalid;

                // check if file exists; fail if it doesn't
                if (!File.Exists(options.appFileName[i]))
                {
                    error.appFiles.SetError(textBoxAppFiles,
                        "Cannot find application file " + options.appFileName[i]);
                    return;
                }
            }
        }

        private bool VAL_appFileNamesAllBinary()
        {
            bool foundAnOutFile = false;

            for (int i = 0; i < options.appFileName.Length; i++)
                if (options.appFileName[i].ToLower().EndsWith(".out"))
                {
                    foundAnOutFile = true;
                    break;
                }

            return !foundAnOutFile;
        }

        private void VAL_checkAisFileName(String text)
        {
            // raise error on blank input
            if (text.Length == 0)
                error.aisFile.SetError(textBoxAISfile, "Must specify an output file.");
            else
                error.aisFile.Clear();
        }

        private bool VAL_errorsRaised()
        {
            // check for parameter errors in all active tabs
            bool err = error.anyGeneral();

            if (options.configPeriph)
                err |= error.anyInputPeriph() | error.anyCalcPeriph();
            if (options.configPll0)
                err |= error.anyInputPLL0() | error.anyCalcPLL0();
            if (options.configPll1)
                err |= error.anyInputPLL1() | error.anyCalcPLL1();
            if (options.configSdram)
                err |= error.anyInputSDRAM() | error.anyCalcSDRAM();
            if (options.configDdr2)
                err |= error.anyInputDDR2() | error.anyCalcDDR2();
            if (options.configLpsc)
                err |= error.anyLpsc();
            if (options.configPinmux)
                err |= error.anyPinmux();

            return err;
        }

        private uint FORMAT_pinmuxMask(uint val)
        {
            uint maskVal = 0;

            // note: input must be 32-bit hex value
            for (int i = 0; i < 8; i++)
                if (((val >> (i * 4)) & 0xF) != 0)
                    maskVal |= ((uint)0xF << (i * 4));

            return maskVal;
        }

        private String FORMAT_32bHexString(uint val)
        {
            String text = String.Format("0x{0:X}", val);
            String zeros = "00000000";
            int n = text.Length;

            // insert leading zeros if necessary
            if (n < 10)
                text = text.Insert(2, zeros.Substring(0, 10 - n));
            //for (int i = 0; i < 10 - n; i++)
            //    text = text.Insert(2, "0");

            return text;
        }

        private uint FORMAT_configWordBlob(uint b3, uint b2, uint b1, uint b0)
        {
            return ((b3 & 0xFF) << 24) |
                ((b2 & 0xFF) << 16) |
                ((b1 & 0xFF) << 8) |
                (b0 & 0xFF);
        }

        private uint FORMAT_configWordBlob(int b3, int b2, int b1, int b0)
        {
            return (((uint)b3 & 0xFF) << 24) |
                (((uint)b2 & 0xFF) << 16) |
                (((uint)b1 & 0xFF) << 8) |
                ((uint)b0 & 0xFF);
        }

        private String FORMAT_lpscListString(int[] list)
        {
            String listString = "";
            for (int i = 0; i < list.Length; i++)
                listString += list[i].ToString() + ";";

            return listString;
        }

        private String FORMAT_appFileListString()
        {
            String text = "";

            for (int i = 0; i < options.appFileName.Length; i++)
                if (options.appFileName[i] != "")
                {
                    text += options.appFileName[i];
                    if (options.appFileAddr[i] != (uint)Consts.BinAddr.invalid)
                        text += "@" + FORMAT_32bHexString(options.appFileAddr[i]);
                    text += ";";
                }

            return text;
        }

        private byte[] FORMAT_insertConfigWord(byte[] ais)
        {
            byte configByte = (byte)(0x20 | options.boot.flashWidth);
            byte[] newAis = new byte[ais.Length + 4];
            
            newAis[0] = configByte;
            newAis[1] = newAis[2] = newAis[3] = 0;
            ais.CopyTo(newAis, 4);

            return newAis;
        }

        // MESSAGE LOGGING ---------------------------------------------------------------

        private void LOG_msg(String text)
        {
            labelMessage.Text = text;
            log.WriteLine("***" + text);
        }

        private void LOG_clear()
        {
            labelMessage.Text = "";
        }

        // MISC UTILITY ------------------------------------------------------------------
        
        private void UTIL_tabShow(int index)
        {
            int insertAt;

            // do nothing if already visible
            if (tabVisible[index]) return;

            // correct index based on which preceding tabs are visible
            insertAt = UTIL_correctTabIndex(index);

            // insert tab to TabPageCollection
            tabControlConfig.TabPages.Insert(insertAt, tab[index]);
            tabVisible[index] = true;
        }

        private void UTIL_tabHide(int index)
        {
            int removeAt;

            // do nothing if already hidden
            if (!tabVisible[index]) return;

            // correct index based on which preceding tabs are visible
            removeAt = UTIL_correctTabIndex(index);

            // remove tab from TabPagesCollection
            tabControlConfig.TabPages.RemoveAt(removeAt);
            tabVisible[index] = false;            
        }

        private int UTIL_correctTabIndex(int index)
        {
            int correctIndex = index;
            for (int i = 0; i < index; i++)
                if (tabVisible[i] == false)
                    correctIndex--;

            return correctIndex;
        }

        private String UTIL_getFileName(String title_text, String filter_text, bool new_file, out bool ok)
        {
            // open file browser
            OpenFileDialog fileOpenSel = new OpenFileDialog();

            fileOpenSel.Filter = filter_text;
            fileOpenSel.Title = title_text;
            fileOpenSel.CheckFileExists = !new_file;
            try
            {
                if (fileOpenSel.ShowDialog() == DialogResult.OK) ok = true;
                else ok = false;
                return fileOpenSel.FileName;
            }
            catch
            {
                LOG_msg("Error: Could not retrieve file name.");
                ok = true;
                return "";
            }
        }

        private String UTIL_getSaveFileName(String title_text, String filter_text, bool new_file, out bool ok)
        {
            // open file browser
            SaveFileDialog fileSaveSel = new SaveFileDialog();

            fileSaveSel.Filter = filter_text;
            fileSaveSel.Title = title_text;
            fileSaveSel.CheckFileExists = !new_file;
            try
            {
                if (fileSaveSel.ShowDialog() == DialogResult.OK) ok = true;
                else ok = false;
                return fileSaveSel.FileName;
            }
            catch
            {
                LOG_msg("Error: Could not retrieve file name.");
                ok = true;
                return "";
            }
        }

        private String UTIL_addBinFileAddress(String fileName, uint addr)
        {
            // don't do anything to app files (.out)
            if (fileName.ToLower().EndsWith(".out"))
                return fileName;

            return fileName.Insert(fileName.Length, "@0x" + Convert.ToString(addr, 16));
        }

        private void UTIL_setupPinmuxArrays()
        {
            numericUpDownPinmux = new NumericUpDown[20];
            textBoxPinmux = new TextBox[20];

            numericUpDownPinmux[0] = numericUpDownPinmux0;
            numericUpDownPinmux[1] = numericUpDownPinmux1;
            numericUpDownPinmux[2] = numericUpDownPinmux2;
            numericUpDownPinmux[3] = numericUpDownPinmux3;
            numericUpDownPinmux[4] = numericUpDownPinmux4;
            numericUpDownPinmux[5] = numericUpDownPinmux5;
            numericUpDownPinmux[6] = numericUpDownPinmux6;
            numericUpDownPinmux[7] = numericUpDownPinmux7;
            numericUpDownPinmux[8] = numericUpDownPinmux8;
            numericUpDownPinmux[9] = numericUpDownPinmux9;
            numericUpDownPinmux[10] = numericUpDownPinmux10;
            numericUpDownPinmux[11] = numericUpDownPinmux11;
            numericUpDownPinmux[12] = numericUpDownPinmux12;
            numericUpDownPinmux[13] = numericUpDownPinmux13;
            numericUpDownPinmux[14] = numericUpDownPinmux14;
            numericUpDownPinmux[15] = numericUpDownPinmux15;
            numericUpDownPinmux[16] = numericUpDownPinmux16;
            numericUpDownPinmux[17] = numericUpDownPinmux17;
            numericUpDownPinmux[18] = numericUpDownPinmux18;
            numericUpDownPinmux[19] = numericUpDownPinmux19;
            textBoxPinmux[0] = textBoxPinmuxVal0;
            textBoxPinmux[1] = textBoxPinmuxVal1;
            textBoxPinmux[2] = textBoxPinmuxVal2;
            textBoxPinmux[3] = textBoxPinmuxVal3;
            textBoxPinmux[4] = textBoxPinmuxVal4;
            textBoxPinmux[5] = textBoxPinmuxVal5;
            textBoxPinmux[6] = textBoxPinmuxVal6;
            textBoxPinmux[7] = textBoxPinmuxVal7;
            textBoxPinmux[8] = textBoxPinmuxVal8;
            textBoxPinmux[9] = textBoxPinmuxVal9;
            textBoxPinmux[10] = textBoxPinmuxVal10;
            textBoxPinmux[11] = textBoxPinmuxVal11;
            textBoxPinmux[12] = textBoxPinmuxVal12;
            textBoxPinmux[13] = textBoxPinmuxVal13;
            textBoxPinmux[14] = textBoxPinmuxVal14;
            textBoxPinmux[15] = textBoxPinmuxVal15;
            textBoxPinmux[16] = textBoxPinmuxVal16;
            textBoxPinmux[17] = textBoxPinmuxVal17;
            textBoxPinmux[18] = textBoxPinmuxVal18;
            textBoxPinmux[19] = textBoxPinmuxVal19;
        }

        private void UTIL_refreshFields()
        {
            // select defaults in combo boxes
            comboBoxBootType.SelectedIndex = options.deviceType;
            comboBoxBootMode.SelectedIndex = options.boot.getIndex();
            comboBoxClockSource.SelectedIndex = options.clockType;
            comboBoxFlashWidth.SelectedIndex = options.boot.flashWidth;

            // numeric
            textBoxClockSpeed.Text = Convert.ToString(options.inputClock);
            textBoxSpecifyEntrypoint.Text = FORMAT_32bHexString(options.entrypoint);
            textBoxPeriphClockIdeal.Text = Convert.ToString(options.boot.targetSpeed);
            textBoxPLL0preDiv.Text = Convert.ToString(options.pll0preDiv);
            textBoxPLL0mult.Text = Convert.ToString(options.pll0Mult);
            textBoxPLL0postDiv.Text = Convert.ToString(options.pll0postDiv);
            textBoxPLL0div1.Text = Convert.ToString(options.pll0div1);
            textBoxPLL0div3.Text = Convert.ToString(options.pll0div3);
            textBoxPLL0div7.Text = Convert.ToString(options.pll0div7);
            textBoxSDRAMsdbcr.Text = FORMAT_32bHexString(options.sdramSdbcr);
            textBoxSDRAMsdtmr.Text = FORMAT_32bHexString(options.sdramSdtmr);
            textBoxSDRAMsdrsrpdexit.Text = FORMAT_32bHexString(options.sdramSdrsrpdexit);
            textBoxSDRAMsdrcr.Text = FORMAT_32bHexString(options.sdramSdrcr);
            textBoxPLL1mult.Text = Convert.ToString(options.pll1Mult);
            textBoxPLL1postDiv.Text = Convert.ToString(options.pll1postDiv);
            textBoxPLL1div1.Text = Convert.ToString(options.pll1div1);
            textBoxPLL1div2.Text = Convert.ToString(options.pll1div2);
            textBoxPLL1div3.Text = Convert.ToString(options.pll1div3);
            textBoxDDR2phy.Text = FORMAT_32bHexString(options.ddr2Phy);
            textBoxDDR2sdcr.Text = FORMAT_32bHexString(options.ddr2Sdcr);
            textBoxDDR2sdtimr.Text = FORMAT_32bHexString(options.ddr2Sdtimr);
            textBoxDDR2sdtimr2.Text = FORMAT_32bHexString(options.ddr2Sdtimr2);
            textBoxDDR2sdrcr.Text = FORMAT_32bHexString(options.ddr2Sdrcr);
            textBoxFlashTiming.Text = FORMAT_32bHexString(options.boot.flashTiming);

            // boolean
            checkBoxPLL0.Checked = options.configPll0;
            checkBoxSDRAM.Checked = options.configSdram;
            checkBoxPLL1.Checked = options.configPll1;
            checkBoxDDR2.Checked = options.configDdr2;
            checkBoxLPSC.Checked = options.configLpsc;
            checkBoxPinmux.Checked = options.configPinmux;
            checkBoxCRC.Checked = options.enableCRC;
            checkBoxSpecifyEntrypoint.Checked = options.specifyEntrypoint;
            checkBoxPeriphSeqRead.Checked = options.enableSeqRead;
            checkBoxSDRAMdiv.Checked = options.sdramDiv45;
            checkBoxDDR2directClock.Checked = options.ddr2directClk;

            // lpsc
            textBoxLps0Enable.Text = FORMAT_lpscListString(options.lpsc0enable);
            textBoxLps0Disable.Text = FORMAT_lpscListString(options.lpsc0disable);
            textBoxLps0SyncRst.Text = FORMAT_lpscListString(options.lpsc0syncRst);
            textBoxLps1Enable.Text = FORMAT_lpscListString(options.lpsc1enable);
            textBoxLps1Disable.Text = FORMAT_lpscListString(options.lpsc1disable);
            textBoxLps1SyncRst.Text = FORMAT_lpscListString(options.lpsc1syncRst);

            // pinmux
            for (int i = 0; i < 20; i++)
                if (options.pinmuxApply[i])
                {
                    numericUpDownPinmux[i].Value = options.pinmuxReg[i];
                    textBoxPinmux[i].Text = FORMAT_32bHexString(options.pinmuxVal[i]);
                }
                else
                {
                    numericUpDownPinmux[i].Value = -1;
                    textBoxPinmux[i].Text = "0x00000000";
                }

            // string
            textBoxAppFiles.Text = FORMAT_appFileListString();
            textBoxAISfile.Text = options.aisFileName;
        }
    }
}