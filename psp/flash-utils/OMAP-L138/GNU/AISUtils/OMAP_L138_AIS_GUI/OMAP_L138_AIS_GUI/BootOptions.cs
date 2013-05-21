using System;
using System.IO;
using System.Collections.Generic;
using System.Text;

namespace OMAP_L138_AIS_GUI
{
    class BootOptions
    {
        // selected boot mode
        public BootMode boot;

        // numeric settings
        public int deviceType, clockType, pll0preDiv,
            pll0Mult, pll0postDiv, pll0div1, pll0div3,
            pll0div7, pll1Mult, pll1postDiv, pll1div1,
            pll1div2, pll1div3;
        public double inputClock;
        public uint entrypoint, sdramSdbcr, sdramSdtmr, sdramSdrsrpdexit,
            sdramSdrcr, ddr2Phy, ddr2Sdcr, ddr2Sdtimr,
            ddr2Sdtimr2, ddr2Sdrcr;

        // boolean settings
        public bool configPeriph, configPll0, configSdram, configPll1,
            configDdr2, configLpsc, configPinmux, enableCRC,
            specifyEntrypoint, enableSeqRead, sdramDiv45,
            ddr2directClk, configFlash;

        // lpsc and pinmux lists
        public int[] lpsc0enable, lpsc0disable, lpsc0syncRst, lpsc1enable,
            lpsc1disable, lpsc1syncRst, pinmuxReg;
        public uint[] pinmuxVal;
        public bool[] pinmuxApply;

        // file name settings
        public String[] appFileName;
        public uint[] appFileAddr;
        public String aisFileName;
        public String cfgFileName;

        public BootOptions()
        {
            // Define defaults; most are applied when app starts

            // boot mode
            boot = new BootMode("NOR Flash");

            // numeric
            deviceType = 1;
            clockType = 0;
            inputClock = 24.00;
            entrypoint = 0;
            pll0preDiv = 1;
            pll0Mult = 20;
            pll0postDiv = 2;
            pll0div1 = 1;
            pll0div3 = 3;
            pll0div7 = 6;
            sdramSdbcr = 0;
            sdramSdtmr = 0;
            sdramSdrsrpdexit = 0;
            sdramSdrcr = 0;
            pll1Mult = 20;
            pll1postDiv = 2;
            pll1div1 = 1;
            pll1div2 = 2;
            pll1div3 = 3; 
            ddr2Phy = 0;
            ddr2Sdcr = 0;
            ddr2Sdtimr = 0;
            ddr2Sdtimr2 = 0;
            ddr2Sdrcr = 0;
            lpsc0enable = new int[0];
            lpsc0disable = new int[0];
            lpsc0syncRst = new int[0];
            lpsc1enable = new int[0];
            lpsc1disable = new int[0];
            lpsc1syncRst = new int[0];
            pinmuxReg = new int[20];
            pinmuxVal = new uint[20];            

            // boolean
            configPeriph = false;
            configPll0 = false;
            configSdram = false;
            configPll1 = false;
            configDdr2 = false;
            configLpsc = false;
            configPinmux = false;
            enableCRC = false;
            specifyEntrypoint = false;
            enableSeqRead = false;
            sdramDiv45 = false;
            ddr2directClk = false;
            pinmuxApply = new bool[20];
            for (int i = 0; i < 20; i++)
                pinmuxApply[i] = false;

            // file settings
            appFileName = new String[1];
            appFileName[0] = "";
            appFileAddr = new uint[1];
            appFileAddr[0] = (uint)Consts.BinAddr.invalid;
            aisFileName = "";
            cfgFileName = "";
        }

        public void saveToFile(String fileName, String appFileString)
        {
            String tokens;
            int i;

            // save file name
            cfgFileName = fileName;

            StreamWriter s = new StreamWriter(fileName);

            // save boot mode (name, target speed, and flash params will suffice)
            s.WriteLine("Boot Mode=" + boot.name);
            s.WriteLine(String.Format("Boot Speed={0}", boot.targetSpeed));
            s.WriteLine("Flash Width=" + boot.flashWidth.ToString());
            s.WriteLine("Flash Timing=" + Convert.ToString(boot.flashTiming, 16));
            
            // save boolean values
            s.WriteLine("Configure Peripheral=" + configPeriph.ToString());
            s.WriteLine("Configure PLL0=" + configPll0.ToString());
            s.WriteLine("Configure SDRAM=" + configSdram.ToString());
            s.WriteLine("Configure PLL1=" + configPll1.ToString());
            s.WriteLine("Configure DDR2=" + configDdr2.ToString());
            s.WriteLine("Configure LPSC=" + configLpsc.ToString());
            s.WriteLine("Configure Pinmux=" + configPinmux.ToString());
            s.WriteLine("Enable CRC=" + enableCRC.ToString());
            s.WriteLine("Specify Entrypoint=" + specifyEntrypoint.ToString());
            s.WriteLine("Enable Sequential Read=" + enableSeqRead.ToString());
            s.WriteLine("Use 4.5 Clock Divider=" + sdramDiv45.ToString());
            s.WriteLine("Use DDR2 Direct Clock=" + ddr2directClk.ToString());

            // save numeric values
            s.WriteLine("Device Type=" + deviceType.ToString());
            s.WriteLine(String.Format("Input Clock Speed={0}", inputClock));
            s.WriteLine("Clock Type=" + clockType.ToString());
            s.WriteLine("PLL0 Pre Divider=" + pll0preDiv.ToString());
            s.WriteLine("PLL0 Multiplier=" + pll0Mult.ToString());
            s.WriteLine("PLL0 Post Divider=" + pll0postDiv.ToString());
            s.WriteLine("PLL0 Div1=" + pll0div1.ToString());
            s.WriteLine("PLL0 Div3=" + pll0div3.ToString());
            s.WriteLine("PLL0 Div7=" + pll0div7.ToString());
            s.WriteLine("PLL1 Multiplier=" + pll1Mult.ToString());
            s.WriteLine("PLL1 Post Divider=" + pll1postDiv.ToString());
            s.WriteLine("PLL1 Div1=" + pll1div1.ToString());
            s.WriteLine("PLL1 Div2=" + pll1div2.ToString());
            s.WriteLine("PLL1 Div3=" + pll1div3.ToString());
            s.WriteLine("Entrypoint=" + Convert.ToString(entrypoint, 16));
            s.WriteLine("SDRAM SDBCR=" + Convert.ToString(sdramSdbcr, 16));
            s.WriteLine("SDRAM SDTMR=" + Convert.ToString(sdramSdtmr, 16));
            s.WriteLine("SDRAM SDRSRPDEXIT=" + Convert.ToString(sdramSdrsrpdexit, 16));
            s.WriteLine("SDRAM SDRCR=" + Convert.ToString(sdramSdrcr, 16));
            s.WriteLine("DDR2 PHY=" + Convert.ToString(ddr2Phy, 16));
            s.WriteLine("DDR2 SDCR=" + Convert.ToString(ddr2Sdcr, 16));
            s.WriteLine("DDR2 SDTIMR=" + Convert.ToString(ddr2Sdtimr, 16));
            s.WriteLine("DDR2 SDTIMR2=" + Convert.ToString(ddr2Sdtimr2, 16));
            s.WriteLine("DDR2 SDRCR=" + Convert.ToString(ddr2Sdrcr, 16));

            // save lpsc and pinmux list
            tokens = "";
            for (i = 0; i < lpsc0enable.Length; i++)
                tokens += lpsc0enable[i].ToString() + "+";
            s.WriteLine("LPSC0 Enable=" + tokens);

            tokens = "";
            for (i = 0; i < lpsc0disable.Length; i++)
                tokens += lpsc0disable[i].ToString() + "+";
            s.WriteLine("LPSC0 Disable=" + tokens);

            tokens = "";
            for (i = 0; i < lpsc0syncRst.Length; i++)
                tokens += lpsc0syncRst[i].ToString() + "+";
            s.WriteLine("LPSC0 SyncRst=" + tokens);

            tokens = "";
            for (i = 0; i < lpsc1enable.Length; i++)
                tokens += lpsc1enable[i].ToString() + "+";
            s.WriteLine("LPSC1 Enable=" + tokens);

            tokens = "";
            for (i = 0; i < lpsc1disable.Length; i++)
                tokens += lpsc1disable[i].ToString() + "+";
            s.WriteLine("LPSC1 Disable=" + tokens);

            tokens = "";
            for (i = 0; i < lpsc1syncRst.Length; i++)
                tokens += lpsc1syncRst[i].ToString() + "+";
            s.WriteLine("LPSC1 SyncRst=" + tokens);

            tokens = "";
            for (i = 0; i < 20; i++)
                if (pinmuxApply[i])
                    tokens += pinmuxReg[i].ToString() + ":" + Convert.ToString(pinmuxVal[i], 16) + "+";
            s.WriteLine("Pinmux=" + tokens);

            // save strings (exclude cfgFileName)
            s.WriteLine("App File String=" + appFileString);
            s.WriteLine("AIS File Name=" + aisFileName);

            // close file
            s.Close();
        }

        public void loadFromFile(String fileName, out String appFileString)
        {
            String[] keyVal, subVal, subSubVal;

            // set app file string initially in case it's not found in file
            appFileString = "";

            // save file name
            cfgFileName = fileName;
            char[] sep = { '=' };
            char[] subSep = { '+' };
            char[] subSubSep = { ':' };

            // slurp file and separate by newlines,
            // then look for strings containing "<name>="
            String[] fileLines = File.ReadAllLines(fileName);

            // check each line for "<key>=<value>" and apply settings
            for (int i = 0; i < fileLines.Length; i++)
            {
                keyVal = fileLines[i].Split(sep, StringSplitOptions.None);
                // skip to next line if there isn't exactly one '='
                if (keyVal.Length != 2) continue;

                switch (keyVal[0])
                {
                    case "Boot Mode":
                        boot.select(keyVal[1]);
                        break;

                    case "Boot Speed":
                        // note: may break if "Boot Speed" comes before "Boot Mode"
                        boot.targetSpeed = Convert.ToDouble(keyVal[1]);
                        boot.saveSpeed();
                        break;

                    case "Flash Width":
                        // note: may break if "Flash Width" comes before "Boot Mode"
                        boot.flashWidth = Convert.ToInt32(keyVal[1], 10);
                        break;

                    case "Flash Timing":
                        // note: may break if "Flash Timing" comes before "Boot Mode"
                        boot.flashTiming = Convert.ToUInt32(keyVal[1], 16);
                        boot.saveFlash();
                        break;

                    // boolean
                    case "Configure Peripheral":
                        configPeriph = Convert.ToBoolean(keyVal[1]);
                        break;

                    case "Configure PLL0":
                        configPll0 = Convert.ToBoolean(keyVal[1]);
                        break;

                    case "Configure SDRAM":
                        configSdram = Convert.ToBoolean(keyVal[1]);
                        break;

                    case "Configure PLL1":
                        configPll1 = Convert.ToBoolean(keyVal[1]);
                        break;

                    case "Configure DDR2":
                        configDdr2 = Convert.ToBoolean(keyVal[1]);
                        break;

                    case "Configure LPSC":
                        configLpsc = Convert.ToBoolean(keyVal[1]);
                        break;

                    case "Configure Pinmux":
                        configPinmux = Convert.ToBoolean(keyVal[1]);
                        break;

                    case "Enable CRC":
                        enableCRC = Convert.ToBoolean(keyVal[1]);
                        break;

                    case "Specify Entrypoint":
                        specifyEntrypoint = Convert.ToBoolean(keyVal[1]);
                        break;

                    case "Enable Sequential Read":
                        enableSeqRead = Convert.ToBoolean(keyVal[1]);
                        break;

                    case "Use 4.5 Clock Divider":
                        sdramDiv45 = Convert.ToBoolean(keyVal[1]);
                        break;

                    case "Use DDR2 Direct Clock":
                        ddr2directClk = Convert.ToBoolean(keyVal[1]);
                        break;

                    // numeric
                    case "Device Type":
                        deviceType = Convert.ToInt32(keyVal[1], 10);
                        break;

                    case "Input Clock Speed":
                        inputClock = Convert.ToDouble(keyVal[1]);
                        break;

                    case "Clock Type":
                        clockType = Convert.ToInt32(keyVal[1], 10);
                        break;

                    case "PLL0 Pre Divider":
                        pll0preDiv = Convert.ToInt32(keyVal[1], 10);
                        break;

                    case "PLL0 Multiplier":
                        pll0Mult = Convert.ToInt32(keyVal[1], 10);
                        break;

                    case "PLL0 Post Divider":
                        pll0postDiv = Convert.ToInt32(keyVal[1], 10);
                        break;

                    case "PLL0 Div1":
                        pll0div1 = Convert.ToInt32(keyVal[1], 10);
                        break;

                    case "PLL0 Div3":
                        pll0div3 = Convert.ToInt32(keyVal[1], 10);
                        break;

                    case "PLL0 Div7":
                        pll0div7 = Convert.ToInt32(keyVal[1], 10);
                        break;

                    case "PLL1 Multiplier":
                        pll1Mult = Convert.ToInt32(keyVal[1], 10);
                        break;

                    case "PLL1 Post Divider=":
                        pll1Mult = Convert.ToInt32(keyVal[1], 10);
                        break;

                    case "PLL1 Div1":
                        pll1div1 = Convert.ToInt32(keyVal[1], 10);
                        break;

                    case "PLL1 Div2":
                        pll1div2 = Convert.ToInt32(keyVal[1], 10);
                        break;

                    case "PLL1 Div3":
                        pll1div3 = Convert.ToInt32(keyVal[1], 10);
                        break;

                    case "Entrypoint":
                        entrypoint = Convert.ToUInt32(keyVal[1], 16);
                        break;

                    case "SDRAM SDBCR":
                        sdramSdbcr = Convert.ToUInt32(keyVal[1], 16);
                        break;

                    case "SDRAM SDTMR":
                        sdramSdtmr = Convert.ToUInt32(keyVal[1], 16);
                        break;

                    case "SDRAM SDRSRPDEXIT":
                        sdramSdrsrpdexit = Convert.ToUInt32(keyVal[1], 16);
                        break;

                    case "SDRAM SDRCR":
                        sdramSdrcr = Convert.ToUInt32(keyVal[1], 16);
                        break;

                    case "DDR2 PHY":
                        ddr2Phy = Convert.ToUInt32(keyVal[1], 16);
                        break;

                    case "DDR2 SDCR":
                        ddr2Sdcr = Convert.ToUInt32(keyVal[1], 16);
                        break;

                    case "DDR2 SDTIMR":
                        ddr2Sdtimr = Convert.ToUInt32(keyVal[1], 16);
                        break;

                    case "DDR2 SDTIMR2":
                        ddr2Sdtimr2 = Convert.ToUInt32(keyVal[1], 16);
                        break;

                    case "DDR2 SDRCR":
                        ddr2Sdrcr = Convert.ToUInt32(keyVal[1], 16);
                        break;

                    // LPSC
                    case "LPSC0 Enable":
                        // break up into '+' separated numbers
                        subVal = keyVal[1].Split(subSep, StringSplitOptions.RemoveEmptyEntries);
                        lpsc0enable = new int[subVal.Length];
                        for (int j = 0; j < subVal.Length; j++)
                            lpsc0enable[j] = Convert.ToInt32(subVal[j], 10);
                        break;

                    case "LPSC0 Disable":
                        // break up into '+' separated numbers
                        subVal = keyVal[1].Split(subSep, StringSplitOptions.RemoveEmptyEntries);
                        lpsc0disable = new int[subVal.Length];
                        for (int j = 0; j < subVal.Length; j++)
                            lpsc0disable[j] = Convert.ToInt32(subVal[j], 10);
                        break;

                    case "LPSC0 SyncRst":
                        // break up into '+' separated numbers
                        subVal = keyVal[1].Split(subSep, StringSplitOptions.RemoveEmptyEntries);
                        lpsc0syncRst = new int[subVal.Length];
                        for (int j = 0; j < subVal.Length; j++)
                            lpsc0syncRst[j] = Convert.ToInt32(subVal[j], 10);
                        break;

                    case "LPSC1 Enable":
                        // break up into '+' separated numbers
                        subVal = keyVal[1].Split(subSep, StringSplitOptions.RemoveEmptyEntries);
                        lpsc1enable = new int[subVal.Length];
                        for (int j = 0; j < subVal.Length; j++)
                            lpsc1enable[j] = Convert.ToInt32(subVal[j], 10);
                        break;

                    case "LPSC1 Disable":
                        // break up into '+' separated numbers
                        subVal = keyVal[1].Split(subSep, StringSplitOptions.RemoveEmptyEntries);
                        lpsc1disable = new int[subVal.Length];
                        for (int j = 0; j < subVal.Length; j++)
                            lpsc1disable[j] = Convert.ToInt32(subVal[j], 10);
                        break;

                    case "LPSC1 SyncRst":
                        // break up into '+' separated numbers
                        subVal = keyVal[1].Split(subSep, StringSplitOptions.RemoveEmptyEntries);
                        lpsc1syncRst = new int[subVal.Length];
                        for (int j = 0; j < subVal.Length; j++)
                            lpsc1syncRst[j] = Convert.ToInt32(subVal[j], 10);
                        break;

                    // Pinmux
                    case "Pinmux":
                        // break up into '+' separated register/value pairs
                        subVal = keyVal[1].Split(subSep, StringSplitOptions.RemoveEmptyEntries);
                        pinmuxApply = new bool[20];
                        pinmuxReg = new int[20];
                        pinmuxVal = new uint[20];
                        for (int j = 0; j < subVal.Length; j++)
                        {
                            // break up into ':' separated values (register, then value)
                            subSubVal = subVal[j].Split(subSubSep, StringSplitOptions.RemoveEmptyEntries);
                            // proceed if we find a valid pair
                            if (subSubVal.Length == 2)
                            {
                                pinmuxApply[j] = true;
                                pinmuxReg[j] = Convert.ToInt32(subSubVal[0], 10);
                                pinmuxVal[j] = Convert.ToUInt32(subSubVal[1], 16);
                            }
                            else
                                pinmuxApply[j] = false;
                        }
                        for (int j = subVal.Length; j < 20; j++)
                            pinmuxApply[j] = false;
                        break;

                    case "App File String":
                        appFileString = keyVal[1];
                        break;

                    case "AIS File Name":
                        aisFileName = keyVal[1];
                        break;

                    default:
                        // unrecognized param; do nothing
                        break;
                }
            }
        }
    }
}
