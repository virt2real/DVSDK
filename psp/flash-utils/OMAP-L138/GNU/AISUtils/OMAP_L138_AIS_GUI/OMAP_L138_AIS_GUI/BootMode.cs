using System;
using System.Collections.Generic;
using System.Text;

namespace OMAP_L138_AIS_GUI
{
    class BootMode
    {
        // constants
        private const double SPEED_i2c = 100.0;
        private const double SPEED_spi = 1.0;
        private const double SPEED_uart = 115200.0;
        private const uint TIMING_default = 0x3FFFFFFC;
        private const uint TIMING_mask = 0xFFFFFFFC;
        private const uint TIMING_8bit = 0x0;
        private const uint TIMING_16bit = 0x1;

        // public members
        public String name, peripheralName, speedName;
        public int psc, div, flashWidth;
        public uint flashTiming, savedNORtiming, savedNANDtiming;
        public double minSpeed, maxSpeed, targetSpeed, savedI2cSpeed,
            savedSpiSpeed, savedUartSpeed;
        public bool isConfigurable, allowSeqRead, allowSpeedChange, isI2c,
            isSpi, isUart, isFlash, isNOR, isNAND;

        public BootMode(String givenName)
        {
            isConfigurable = false;
            isFlash = false;
            allowSeqRead = false;
            allowSpeedChange = false;

            psc = 1;
            div = 1;

            // save default peripheral speeds
            savedI2cSpeed = SPEED_i2c;
            savedSpiSpeed = SPEED_spi;
            savedUartSpeed = SPEED_uart;

            // default flash settings
            flashTiming = TIMING_default;
            savedNORtiming = TIMING_default;
            savedNANDtiming = TIMING_default;
            flashWidth = (int)Consts.FlashWidth.eightbit;

            select(givenName);
        }

        public void select(String newName)
        {
            name = newName;

            isI2c = false;
            isSpi = false;
            isUart = false;
            isNAND = false;
            isNOR = false;
            isFlash = false;

            // determine peripheral type
            if (name.Contains("I2C"))
            {
                peripheralName = "I2C";
                speedName = "kHz";
                minSpeed = 1.0;
                maxSpeed = 400.0;
                targetSpeed = savedI2cSpeed;
                isI2c = true;
            }
            else if (name.Contains("SPI"))
            {
                peripheralName = "SPI";
                speedName = "MHz";
                minSpeed = 1.0;
                maxSpeed = 50.0;
                targetSpeed = savedSpiSpeed;
                isSpi = true;
            }
            else if (name.Contains("UART"))
            {
                peripheralName = "UART";
                speedName = "baud";
                minSpeed = SPEED_uart;
                maxSpeed = SPEED_uart;
                targetSpeed = savedUartSpeed;
                isUart = true;
            }
            else
            {
                // other peripherals shouldn't be configurable
                peripheralName = "Invalid";
                speedName = "mph";
                minSpeed = 15.0;
                maxSpeed = 70.0;
            }

            // display tab for EEPROM cases and UART (above)
            if (name.Contains("EEPROM") || (isSpi && name.Contains("Flash")))
            {
                isConfigurable = true;
                allowSpeedChange = true;
                allowSeqRead = true;
            }
            else if (isUart)
            {
                isConfigurable = true;
                allowSpeedChange = false;
                allowSeqRead = false;
            }
            else
            {
                isConfigurable = false;
                allowSeqRead = false;
                allowSpeedChange = false;
            }

            // display flash tab for NOR, NAND
            if (name.Contains("NOR"))
            {
                isFlash = true;
                isNOR = true;
                flashTiming = savedNORtiming;
            }
            else if (name.Contains("NAND"))
            {
                isFlash = true;
                isNAND = true;
                flashTiming = savedNANDtiming;
            }
        }

        public void saveSpeed()
        {
            if (isI2c)
                savedI2cSpeed = targetSpeed;
            else if (isSpi)
                savedSpiSpeed = targetSpeed;
            else if (isUart)
                savedUartSpeed = targetSpeed;
        }

        public int getIndex()
        {
            // Returns index of combo box entry in main form.  Must be updated
            // if combo box collection is modified or re-ordered.

            switch (name)
            {
                case "NOR Flash":   return 0;
                case "NAND Flash":  return 1;
                case "SPI0 Flash":  return 2;
                case "SPI1 Flash":  return 3;
                case "I2C0 EEPROM": return 4;
                case "I2C1 EEPROM": return 5;
                case "SPI0 EEPROM": return 6;
                case "SPI1 EEPROM": return 7;
                case "I2C0 Slave":  return 8;
                case "I2C1 Slave":  return 9;
                case "SPI0 Slave":  return 10;
                case "SPI1 Slave":  return 11;
                case "UART0":       return 12;
                case "UART1":       return 13;
                case "UART2":       return 14;
                default:            return 0;   // should never come here
            }
        }

        public void saveFlash()
        {
            if (isNAND)
                savedNANDtiming = flashTiming;
            else if (isNOR)
                savedNORtiming = flashTiming;
        }

        public void flashTimingUpdate()
        {
            // apply data width to timing value
            flashTiming &= TIMING_mask;
            if (flashWidth == (int)Consts.FlashWidth.eightbit)
                flashTiming |= TIMING_8bit;
            else
                flashTiming |= TIMING_16bit;
        }

        public bool flashTimingIsSixteenBit()
        {
            if ((flashTiming & TIMING_16bit) == 1)
                return true;
            else
                return false;
        }
    }
}
