/* --------------------------------------------------------------------------
  FILE      : i2c_ecp.h
  PURPOSE   : I2C_ECP header file
  PROJECT   : DM648 flashing utilities
  AUTHOR    : Daniel Allred
  DESC      : This header file provides device and EVM specifc defines and
                  driver functionality to use the I2C peripheral, specifically for
                  communicating with the DM648EVM MSP430 controller.
 ----------------------------------------------------------------------------- */

#ifndef _I2C_ECP_H_
#define _I2C_ECP_H_

#include "tistdtypes.h"

// Prevent C++ name mangling
#ifdef __cplusplus
extern far "c" {
#endif

/***********************************************************
* Global Macro Declarations                                *
***********************************************************/

#define I2C_ECP_ADDRESS (0x70)              // MSP430(ECP) I2C address
#define I2C_ECP_CMD_REG (0x00)              // ECP Command register
#define I2C_ECP_STT_REG (0x01)              // ECP Status register
#define I2C_ECP_RIN_REG (0x02)              // ECP Reset in register
#define I2C_ECP_ROU_REG (0x03)              // ECP Reset out register
#define I2C_ECP_PCI_REG (0x04)              // ECP PCI config register
#define I2C_ECP_REV_REG (0x05)              // ECP Revision register
#define I2C_ECP_VMX_REG (0x06)              // ECP Video Mux regsiter
#define I2C_ECP_LED_REG (0x07)              // ECP LED register (writing)
#define I2C_ECP_SWI_REG (0x07)              // ECP Switch register (reading)
#define I2C_ECP_DCGPIO_CNTRL_REG    (0x08)  // ECP DC GPIO control
#define I2C_ECP_DCGPIO_STATE_REG    (0x09)  // ECP DC GPIO state
#define I2C_ECP_TMR_REG             (0x0A)  // ECP DSP Timer interface
#define I2C_ECP_PS_CNTRL_REG        (0x0B)  // ECP Power Supply contrl
#define I2C_ECP_BTMD_LOW_REG        (0x0C)  // ECP Bootmode low
#define I2C_ECP_BTMD_HIGH_REG       (0x0D)  // ECP Bootmode high
#define I2C_ECP_BTMD_OVR_LOW_REG    (0x0E)  // ECP Bootmode low
#define I2C_ECP_UART_SPI_CTRL_REG   (0x10)  // ECP UART SPI control
#define I2C_ECP_VID_STT_REG         (0x11)  // ECP Video status
#define I2C_ECP_CLK_CTRL_REG        (0x12)  // ECP Clock control
#define I2C_ECP_SPIDF_CTRL_REG      (0x13)  // ECP SPDIF control
#define I2C_ECP_McASP_MUX_CTRL_REG  (0x13)  // ECP McASP mux control

#define I2C_ECP_RETRY_CNT_MAX       (256)


/***********************************************************
* Global Typedef declarations                              *
***********************************************************/


/***********************************************************
* Global Function Declarations                             *
***********************************************************/

Uint32  I2C_ECP_write( Uint8 offset, Uint8 data );
Uint32  I2C_ECP_read( Uint8 offset, Uint8 *data );
void    I2C_ECP_reset();


/***********************************************************
* End file                                                 *
***********************************************************/

#ifdef __cplusplus
}
#endif

#endif //_I2C_ECP_H_

/* --------------------------------------------------------------------------
	HISTORY
 		v1.00 - DJA - 07-Nov-2007
 	    	Initial Release
 ----------------------------------------------------------------------------- */
