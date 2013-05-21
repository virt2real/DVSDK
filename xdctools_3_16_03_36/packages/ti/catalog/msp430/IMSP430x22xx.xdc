/* 
 *  Copyright (c) 2008 Texas Instruments and others.
 *  All rights reserved. This program and the accompanying materials
 *  are made available under the terms of the Eclipse Public License v1.0
 *  which accompanies this distribution, and is available at
 *  http://www.eclipse.org/legal/epl-v10.html
 * 
 *  Contributors:
 *      Texas Instruments - initial implementation
 * 
 * */

/*!
 *  ======== IMSP430x22xx.xdc ========
 *  Common definition for MSP430x22xx devices
 */

metaonly interface IMSP430x22xx inherits IMSP430
{
    struct Timer {
        string  name;
        UInt    baseAddr;
        UInt    intNum;
    };

instance:

    /*!
     *  ======== commonMap ========
     *  Memory map elements shared by all MSP430x22xx devices
     */
    config xdc.platform.IPlatform.Memory commonMap[string]  = [
        ["PERIPHERALS_8BIT", {
            comment:    "Memory mapped I/O registers",
            name:       "PERIPHERALS_8BIT",
            base:       0x0010,
            len:        0x00F0,
            space:      "io",
            access:     "RW"
        }],

        ["PERIPHERALS_16BIT", {
            comment:    "Memory mapped I/O registers",
            name:       "PERIPHERALS_16BIT",
            base:       0x0100,
            len:        0x0100,
            space:      "io",
            access:     "RW"
        }],

        ["BSLSKEY", {
            comment:    "Boot loader security key",
            name:       "BSLSKEY",
            base:       0xFFDE,
            len:        0x0002,
            space:      "data",
            access:     "RI"
        }],

        ["INT00", {
            comment:    "Reserved Vector (int00)",
            name:       "INT00",
            base:       0xFFE0,
            len:        0x0002,
            space:      "data",
            access:     "RW"
        }],

        ["INT01", {
            comment:    "Reserved Vector (int01)",
            name:       "INT01",
            base:       0xFFE2,
            len:        0x0002,
            space:      "data",
            access:     "RW"
        }],

        ["IOPORT1", {
            comment:    "I/O Port P1 Vector (int02)",
            name:       "IOPORT1",
            base:       0xFFE4,
            len:        0x0002,
            space:      "data",
            access:     "RW"
        }],

        ["IOPORT2", {
            comment:    "I/O Port P2 Vector (int03)",
            name:       "IOPORT2",
            base:       0xFFE6,
            len:        0x0002,
            space:      "data",
            access:     "RW"
        }],

        ["INT04", {
            comment:    "Reserved Vector (int04)",
            name:       "INT04",
            base:       0xFFE8,
            len:        0x0002,
            space:      "data",
            access:     "RW"
        }],

        ["ADC10", {
            comment:    "ADC10 Vector (int05)",
            name:       "ADC10",
            base:       0xFFEA,
            len:        0x0002,
            space:      "data",
            access:     "RW"
        }],

        ["USCI_TX", {
            comment:    "USCI_A0/B0 Transmit Vector (int06)",
            name:       "USCI_TX",
            base:       0xFFEC,
            len:        0x0002,
            space:      "data",
            access:     "RW"
        }],

        ["USCI_RX", {
            comment:    "USCI_A0/B0 Receive Vector (int07)",
            name:       "USCI_RX",
            base:       0xFFEE,
            len:        0x0002,
            space:      "data",
            access:     "RW"
        }],

        ["TIMER_A1", {
            comment:    "Timer_A3 TBCCR1 Vector (int08)",
            name:       "TIMER_A1",
            base:       0xFFF0,
            len:        0x0002,
            space:      "data",
            access:     "RW"
        }],

        ["TIMER_A0", {
            comment:    "Timer_A3 TBCCR0 Vector (int09)",
            name:       "TIMER_A0",
            base:       0xFFF2,
            len:        0x0002,
            space:      "data",
            access:     "RW"
        }],

        ["INT10", {
            comment:    "Watchdog Vector (int10)",
            name:       "INT10",
            base:       0xFFF4,
            len:        0x0002,
            space:      "data",
            access:     "RW"
        }],

        ["INT11", {
            comment:    "Reserved Vector (int11)",
            name:       "INT11",
            base:       0xFFF6,
            len:        0x0002,
            space:      "data",
            access:     "RW"
        }],

        ["TIMER_B1", {
            comment:    "Timer_B3 TBCCR1 Vector (int12)",
            name:       "TIMER_B1",
            base:       0xFFF8,
            len:        0x0002,
            space:      "data",
            access:     "RW"
        }],

        ["TIMER_B0", {
            comment:    "Timer_B3 TBCCR0 Vector (int13)",
            name:       "TIMER_B0",
            base:       0xFFFA,
            len:        0x0002,
            space:      "data",
            access:     "RW"
        }],

        ["NMI", {
            comment:    "NMI Vector (int14)",
            name:       "NMI",
            base:       0xFFFC,
            len:        0x0002,
            space:      "data",
            access:     "RW"
        }],

        ["RESET", {
            comment:    "Reset Vector (int15)",
            name:       "RESET", 
            base:       0xFFFE,
            len:        0x0002,
            space:      "data",
            access:     "RW"
        }],

        ["INFO", {
            comment:    "Information FLASH",
            name:       "INFO",
            base:       0x1000,
            len:        0x0100,
            space:      "data",
            access:     "RW"
        }],
    ];

    config Timer timers[2] = [
        {
            name: "Timer_A3",
            baseAddr: 0x160,
            intNum: 25
        },

        {
            name: "Timer_B3",
            baseAddr: 0x180,
            intNum: 29
        },
    ];
}
/*
 *  @(#) ti.catalog.msp430; 1, 0, 0,17; 2-23-2010 16:52:59; /db/ztree/library/trees/platform/platform-k32x/src/
 */

