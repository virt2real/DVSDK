/*
 * gpio_test kernel module
 *
 * Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the
 * distribution.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of
 * its contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/
/*******************************************************************************
 *	HEADER FILES
 */
#include <linux/module.h>
#include <linux/version.h>
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/device.h>
#include <linux/errno.h>
#include <linux/init.h>
#include <linux/gpio.h>
#include <mach/io.h>
#include <mach/cputype.h>
#include <mach/hardware.h>

/*******************************************************************************
 *	LOCAL DEFINES
 */
#define IRQ_RISING_EDGE 0
#define IRQ_FALLING_EDGE 1
#define IRQ_BOTH_EDGE 2

#define GPIO_DIR_OUT 0
#define GPIO_DIR_IN 1

#define __REG(addr)   (*(volatile unsigned int *)IO_ADDRESS(addr))

#define REG_PINMUX0     __REG(0x01c40000)
#define REG_PINMUX1     __REG(0x01c40004)
#define REG_PINMUX2     __REG(0x01c40008)
#define REG_PINMUX3     __REG(0x01c4000c)
#define REG_PINMUX4     __REG(0x01c40010)

/*******************************************************************************
 *	FILE GLOBALS
 */
/*
1) if is_test_irq = 0, all params related to irq is no effect.
2) if dir = 0 (output), gpio_src is no effect.
3) if gpio_num > 9, irq_num is no effect.
*/
/* Populated the variables with Default values */
static int gpio_num = 7;
static int dir = 0;		/* 0: out; 1: in */
static int irq_num = 51;	/* for dm355 */
static int irq_trig_edge = 0;
static int test_loop = 2;
static int gpio_src = 6;	/* output pin for testing input gpio */
static int is_test_irq = 0;
static int is_disable_irq = 0;	/*irq is not disable by default */

module_param(gpio_num, int, S_IRUSR);
module_param(dir, int, S_IRUSR);
module_param(irq_num, int, S_IRUSR);
module_param(irq_trig_edge, int, S_IRUSR);
module_param(test_loop, int, S_IRUSR);
module_param(gpio_src, int, S_IRUSR);
module_param(is_test_irq, int, S_IRUSR);
module_param(is_disable_irq, int, S_IRUSR);

static irqreturn_t gpio_irq_handler(int irq, void *dev_id);

/*******************************************************************************
 *	FUNCTION DEFINITIONS
 */
/***************************************************************************
 * Function             - gpio_irq_handler
 * Functionality        - Interrupt Handler for TX GPIO's
 * Input Params - ST_GPIOAttrs *
 * Return Value - None
 * Note                 - None
 ****************************************************************************/
static irqreturn_t gpio_irq_handler(int irq, void *dev_id)
{
	printk("<1> gpio_irq_handler : IRQ=%d \n", irq);
	return IRQ_HANDLED;
}

/***************************************************************************
 * Function             - gpio_request_irq
 * Functionality        - Registers Handlers to the IRQ's of GPIO's by request_irq
 * Input Params - 
 * Return Value - None
 * Note                 - None
 ****************************************************************************/
void gpio_request_irq(int irq_num)
{
	int status = 0;
	int edge_type = 0;
	
	if (irq_trig_edge == IRQ_RISING_EDGE) {
		edge_type = IORESOURCE_IRQ_HIGHEDGE;
	} else if (irq_trig_edge == IRQ_FALLING_EDGE) {
		edge_type = IORESOURCE_IRQ_LOWEDGE;
	} else {
		edge_type = IORESOURCE_IRQ_LOWEDGE | IORESOURCE_IRQ_HIGHEDGE;
	}
	status = request_irq(irq_num, &gpio_irq_handler,
		IRQF_DISABLED | edge_type, "gpio_test", NULL);
	if (status < 0) {
		printk("<1> gpio_request_irq : Failed to Register IRQ %d  \n",
		       irq_num);
		printk("<1> gpio_request_irq : return status is %d  \n",
		       status);
	}

}

/***************************************************************************
 * Function             - gpio_unrequest_irq
 * Functionality        - Free Handlers o the IRQ's of GPIO's
 * Input Params - 
 * Return Value - None
 * Note                 - None
 ****************************************************************************/
void gpio_unrequest_irq(int irq_num)
{
	free_irq(irq_num, NULL);
	printk("<1> gpio_unrequest_irq :  Freeing IRQ %d  \n", irq_num);

}

/***************************************************************************
 * Function             - gpio_write
 * Functionality        - toggel gpio output
 * Input Params - 
 * Return Value - None
 * Note                 - None
 ****************************************************************************/
void gpio_write(void)
{
	int i, j;
	int toggle = 0;
	int gpio;

	gpio = (dir == GPIO_DIR_IN) ? gpio_src : gpio_num;

	printk("<1> \n");
	printk("<1> Toggle gpio %d \n", gpio);

	/* toggle output values to trigger irq */
	for (i = 0; i < test_loop; i++) {
		toggle = !(toggle);	/* toggle the data */
		printk("<1>   set %d to gpio \n", toggle);
		__gpio_set_value(gpio, toggle);

		/* wait for sometime: 1x10+9 <=> 4.6 seconds for 216MHz */
		for (j = 0; j < 1000000; j++)
			asm("NOP");

	}
}

int gpio_get_settings(int gpio, unsigned long reg_val, char *reg_type)
{
	/* Verify if the bit is set right or not */
	int mask = 0, set_value = 0;
	mask = 1 << (gpio % 32);
	set_value = (reg_val & mask) >> (gpio % 32);
	printk("<1> The value was set to %d for gpio %d in %s register.\n\n",
	       set_value, gpio, reg_type);

	return set_value;
}

/***************************************************************************
 * Function		- gpio_get_dir_reg_info
 * Functionality	- Consoles the Direction Regs of the GPIO's
 * Input Params	- None
 * Return Value	- None
 * Note			- None
 ****************************************************************************/
void gpio_get_dir_reg_info(int gio)
{
	volatile unsigned long *reg;
	int blank = (gio >> 5) & 0x3;
	int offset = 0;

	offset = 0x10 + blank * 0x28;

	reg = (unsigned long *)IO_ADDRESS(DAVINCI_GPIO_BASE + offset);

	if (cpu_is_davinci_dm355()) {
		switch (offset) {
		default:
		case (0x10):
			printk("<1> GPIO DIR bank 0 and 1:\t 0x%lx\n", *reg);
			break;
		case (0x38):
			printk("<1> GPIO DIR bank 2 and 3:\t 0x%lx\n", *reg);
			break;
		case (0x60):
			printk("<1> GPIO DIR bank 4 and 5:\t 0x%lx\n", *reg);
			break;
		case (0x88):
			printk("<1> GPIO DIR bank 6:\t 0x%lx\n", *reg);
			break;
		}
	} else if (cpu_is_davinci_dm644x()) {
		switch (offset) {
		default:
		case (0x10):
			printk("<1> GPIO DIR bank 0 and 1:\t 0x%lx\n", *reg);
			break;
		case (0x38):
			printk("<1> GPIO DIR bank 2 and 3:\t 0x%lx\n", *reg);
			break;
		case (0x60):
			printk("<1> GPIO DIR bank 4 and 5:\t 0x%lx\n", *reg);
			break;
		}
	}

	/* Verify if the bit is set right or not */
	if (dir == 0) {
		if (gpio_get_settings(gio, *reg, "DIR") != 0)
			printk
			    ("<1> Failure: DIR register is not set to 0 for gpio %d\n",
			     gio);
	} else {
		if (gpio_get_settings(gio, *reg, "DIR") != 1)
			printk
			    ("<1> Failure: DIR register is not set to 1 for gpio %d\n",
			     gio);

	}
}

/***************************************************************************
 * Function		- gpio_get_out_data_reg_info
 * Functionality	- Consoles the Output state Regs of GPIO's
 * Input Params	- None
 * Return Value	- None
 * Note			- None
 ****************************************************************************/
void gpio_get_out_data_reg_info(int gio)
{
	volatile unsigned long *reg;
	int blank = (gio >> 5) & 0x3;
	int offset = 0;

	offset = 0x14 + blank * 0x28;

	reg = (unsigned long *)IO_ADDRESS(DAVINCI_GPIO_BASE + offset);

	if (cpu_is_davinci_dm355()) {
		switch (offset) {
		default:
		case (0x14):
			printk("<1> GPIO OUT_DATA bank 0 and 1:\t 0x%lx\n",
			       *reg);
			break;
		case (0x3C):
			printk("<1> GPIO OUT_DATA bank 2 and 3:\t 0x%lx\n",
			       *reg);
			break;
		case (0x64):
			printk("<1> GPIO OUT_DATA bank 4 and 5:\t 0x%lx\n",
			       *reg);
			break;
		case (0x8C):
			printk("<1> GPIO OUT_DATA bank 6:\t 0x%lx\n", *reg);
			break;
		}
	} else if (cpu_is_davinci_dm644x()) {
		switch (offset) {
		default:
		case (0x14):
			printk("<1> GPIO OUT_DATA bank 0 and 1:\t 0x%lx\n",
			       *reg);
			break;
		case (0x3C):
			printk("<1> GPIO OUT_DATA bank 2 and 3:\t 0x%lx\n",
			       *reg);
			break;
		case (0x64):
			printk("<1> GPIO OUT_DATA bank 4 and 5:\t 0x%lx\n",
			       *reg);
			break;
		}
	}

	/* Verify if the bit is set right or not only check when dir is output */
	if (dir == 0) {
		if (test_loop % 2 == 0) {	/* if test_loop is even, the value is set to 0. */
			if (gpio_get_settings(gio, *reg, "OUT_DATA") != 0)
				printk
				    ("<1> Failure: OUT_DATA register is not set to 0 for gpio %d\n",
				     gio);
		} else {
			if (gpio_get_settings(gio, *reg, "OUT_DATA") != 1)
				printk
				    ("<1> Failure: OUT_DATA register is not set to 1 for gpio %d\n",
				     gio);

		}
	}
}

/***************************************************************************
 * Function		- gpio_get_in_data_reg_info
 * Functionality	- Consoles the Input state Regs of GPIO's
 * Input Params	- None
 * Return Value	- None
 * Note			- None
 ****************************************************************************/
void gpio_get_in_data_reg_info(int gio)
{
	volatile unsigned long *reg;
	int blank = (gio >> 5) & 0x3;
	int offset = 0;

	offset = 0x20 + blank * 0x28;

	reg = (unsigned long *)IO_ADDRESS(DAVINCI_GPIO_BASE + offset);

	if (cpu_is_davinci_dm355()) {
		switch (offset) {
		default:
		case (0x20):
			printk("<1> GPIO IN_DATA bank 0 and 1:\t 0x%lx\n",
			       *reg);
			break;
		case (0x48):
			printk("<1> GPIO IN_DATA bank 2 and 3:\t 0x%lx\n",
			       *reg);
			break;
		case (0x70):
			printk("<1> GPIO IN_DATA bank 4 and 5:\t 0x%lx\n",
			       *reg);
			break;
		case (0x98):
			printk("<1> GPIO IN_DATA bank 6:\t 0x%lx\n", *reg);
			break;
		}
	} else if (cpu_is_davinci_dm644x()) {
		switch (offset) {
		default:
		case (0x20):
			printk("<1> GPIO IN_DATA bank 0 and 1:\t 0x%lx\n",
			       *reg);
			break;
		case (0x48):
			printk("<1> GPIO IN_DATA bank 2 and 3:\t 0x%lx\n",
			       *reg);
			break;
		case (0x70):
			printk("<1> GPIO IN_DATA bank 4 and 5:\t 0x%lx\n",
			       *reg);
			break;
		}
	}

	gpio_get_settings(gio, *reg, "IN_DATA");
}

/***************************************************************************
 * Function             - gpio_get_set_ris_reg_info
 * Functionality        - Consoles the SET_RIS_TRIG Regs of the GPIO's
 * Input Params - None
 * Return Value - None
 * Note                 - None
 ****************************************************************************/
void gpio_get_set_ris_reg_info(int gio)
{
	volatile unsigned long *reg;
	int blank = (gio >> 5) & 0x3;
	int offset = 0;

	offset = 0x24 + blank * 0x28;

	reg = (unsigned long *)IO_ADDRESS(DAVINCI_GPIO_BASE + offset);

	if (cpu_is_davinci_dm355()) {
		switch (offset) {
		default:
		case (0x24):
			printk("<1> GPIO SET_RIS_TRIG bank 0 and 1:\t 0x%lx\n",
			       *reg);
			break;
		case (0x4C):
			printk("<1> GPIO SET_RIS_TRIG bank 2 and 3:\t 0x%lx\n",
			       *reg);
			break;
		case (0x74):
			printk("<1> GPIO SET_RIS_TRIG bank 4 and 5:\t 0x%lx\n",
			       *reg);
			break;
		case (0x9C):
			printk("<1> GPIO SET_RIS_TRIG bank 6:\t 0x%lx\n", *reg);
			break;
		}
	} else if (cpu_is_davinci_dm644x()) {
		switch (offset) {
		default:
		case (0x24):
			printk("<1> GPIO SET_RIS_TRIG bank 0 and 1:\t 0x%lx\n",
			       *reg);
			break;
		case (0x4C):
			printk("<1> GPIO SET_RIS_TRIG bank 2 and 3:\t 0x%lx\n",
			       *reg);
			break;
		case (0x74):
			printk("<1> GPIO SET_RIS_TRIG bank 4 and 5:\t 0x%lx\n",
			       *reg);
			break;

		}
	}

	/* Verify if the bit is set right or not */
	if (irq_trig_edge == 0) {
		if (gpio_get_settings(gio, *reg, "SET_RIS_TRIG") != 1)
			printk
			    ("<1> Failure: SET_RIS_TRIG register is not set to 1 for gpio %d\n",
			     gio);
	} else			/* not check the setting if falling-edge */
		gpio_get_settings(gio, *reg, "SET_RIS_TRIG");
}

/***************************************************************************
 * Function             - gpio_get_set_fal_reg_info
 * Functionality        - Consoles the SET_FAL_TRIG Regs of the GPIO's
 * Input Params - None
 * Return Value - None
 * Note                 - None
 ****************************************************************************/
void gpio_get_set_fal_reg_info(int gio)
{
	volatile unsigned long *reg;
	int blank = (gio >> 5) & 0x3;
	int offset = 0;

	offset = 0x2C + blank * 0x28;

	reg = (unsigned long *)IO_ADDRESS(DAVINCI_GPIO_BASE + offset);

	if (cpu_is_davinci_dm355()) {
		switch (offset) {
		default:
		case (0x2C):
			printk("<1> GPIO SET_FAL_TRIG bank 0 and 1:\t 0x%lx\n",
			       *reg);
			break;
		case (0x54):
			printk("<1> GPIO SET_FAL_TRIG bank 2 and 3:\t 0x%lx\n",
			       *reg);
			break;
		case (0x7C):
			printk("<1> GPIO SET_FAL_TRIG bank 4 and 5:\t 0x%lx\n",
			       *reg);
			break;
		case (0xA4):
			printk("<1> GPIO SET_FAL_TRIG bank 6:\t 0x%lx\n", *reg);
			break;
		}
	} else if (cpu_is_davinci_dm644x()) {
		switch (offset) {
		default:
		case (0x2C):
			printk("<1> GPIO SET_FAL_TRIG 0 and 1:\t 0x%lx\n",
			       *reg);
			break;
		case (0x54):
			printk("<1> GPIO SET_FAL_TRIG 2 and 3:\t 0x%lx\n",
			       *reg);
			break;
		case (0x7C):
			printk("<1> GPIO SET_FAL_TRIG 4 and 5:\t 0x%lx\n",
			       *reg);
			break;

		}
	}

	/* Verify if the bit is set right or not */
	if (irq_trig_edge == 1) {
		if (gpio_get_settings(gio, *reg, "SET_FAL_TRIG") != 1)
			printk
			    ("<1> Failure: SET_FAL_TRIG register is not set to 1 for gpio %d\n",
			     gio);
	} else
		gpio_get_settings(gio, *reg, "SET_FAL_TRIG");
}

/***************************************************************************
 * Function		- gpio_get_intstat_reg_info
 * Functionality	- Consoles the Interrupt state Regs of GPIO's
 * Input Params	- None
 * Return Value	- None
 * Note			- None
 ****************************************************************************/
void gpio_get_intstat_reg_info(int gio)
{
	volatile unsigned long *reg;
	int blank = (gio >> 5) & 0x3;
	int offset = 0;

	offset = 0x34 + blank * 0x28;

	reg = (unsigned long *)IO_ADDRESS(DAVINCI_GPIO_BASE + offset);

	if (cpu_is_davinci_dm355()) {
		switch (offset) {
		default:
		case (0x34):
			printk("<1> GPIO INSTAT bank 0 and 1:\t 0x%lx\n", *reg);
			break;
		case (0x5C):
			printk("<1> GPIO INSTAT bank 2 and 3:\t 0x%lx\n", *reg);
			break;
		case (0x84):
			printk("<1> GPIO INSTAT bank 4 and 5:\t 0x%lx\n", *reg);
			break;
		case (0xAC):
			printk("<1> GPIO INSTAT bank 6:\t 0x%lx\n", *reg);
			break;
		}
	} else if (cpu_is_davinci_dm644x()) {
		switch (offset) {
		default:
		case (0x34):
			printk("<1> GPIO INSTAT bank 0 and 1:\t 0x%lx\n", *reg);
			break;
		case (0x5C):
			printk("<1> GPIO INSTAT bank 2 and 3:\t 0x%lx\n", *reg);
			break;
		case (0x84):
			printk("<1> GPIO INSTAT bank 4 and 5:\t 0x%lx\n", *reg);
			break;
		}
	}

	gpio_get_settings(gio, *reg, "INSTAT");
}

/***************************************************************************
 * Function		- gpio_get_binten_reg_info
 * Functionality	- Consoles the BINTEN of GPIO's
 * Input Params	- None
 * Return Value	- None
 * Note			- None
 ****************************************************************************/
void gpio_get_binten_reg_info(void)
{
	volatile unsigned long *reg;
	int offset = 0;

	offset = 0x08;

	reg = (unsigned long *)IO_ADDRESS(DAVINCI_GPIO_BASE + offset);
	printk("<1> GPIO BINTEN:\t 0x%lx\n", *reg);
}

void gpio_demux_pins(void)
{
	/* PINMUX address is same between dm355 and dm6446? */
	if (cpu_is_davinci_dm355()) {
		/* Besides the dedicated GPIO pins */
		/* Demux pins to GPIO pins which can be accessed from DC5 */
		REG_PINMUX1 |= (1 << 17);	/* gio71 */
		REG_PINMUX1 &= ~((1 << 19) | (1 << 18));	/* gio70 */
		REG_PINMUX1 &= ~((1 << 0) | (1 << 1));	/* gio81 */
		REG_PINMUX1 &= ~((1 << 2) | (1 << 3));	/* gio80 */
		REG_PINMUX1 &= ~((1 << 4) | (1 << 5));	/* gio79 */
		REG_PINMUX1 &= ~((1 << 6) | (1 << 7));	/* gio78 */

		REG_PINMUX3 &= ~(1 << 28);	/* gio07 */

#if 0
		/* Demux the following pins for DC7 in new dm355 board */
		/* gpio 58 to 65, no pin mux is available */
		REG_PINMUX2 |= (1 << 10);	/* gio32 Enable EM_AVD */
		REG_PINMUX4 |= (1 << 1);	/* gio32 Enable SPIO_SDI */
		REG_PINMUX2 &= ~(1 << 2);	/* gio54 */
		REG_PINMUX2 |= (1 << 3);	/* gio54 */
		/* comment out the following because it causes 'etho transmit timeout' */
		/* REG_PINMUX2 |= (1<<1); *//* gio55:56 */
		REG_PINMUX2 |= (1 << 0);	/* gio57:67 */

		/* Demux pins to GPIO pins which can be accessed from DC3 */
		REG_PINMUX3 &= ~(1 << 0);	/* gio30 */
		REG_PINMUX3 &= ~(1 << 1);	/* gio29 */
		REG_PINMUX3 &= ~(1 << 2);	/* gio28 */
		REG_PINMUX3 &= ~(1 << 3);	/* gio27 */
		REG_PINMUX3 &= ~(1 << 4);	/* gio26 */
		REG_PINMUX3 &= ~(1 << 5);	/* gio25 */
#endif
	} else if (cpu_is_davinci_dm644x()) {
		/* after do the de-pinmux EMAC, network will go down. UUT need
		 * reboot in order to test gpio54 and up, uncomment the following.
		 */
		/*REG_PINMUX0 &= ~(1<<31); */
	}

}

/* gpio 0-9 has direct interrupt number corresponding to them for dm355. */
int get_gpio_num_direct_irq(void)
{
	int rtn = 0;

	if (cpu_is_davinci_dm355())
		rtn = 10;
	else if (cpu_is_davinci_dm644x())
		rtn = 8;
	return rtn;
}

int gpio_test_init(void)
{

	printk("<1> GPIO Test Begins\n");

	/* Demux pins to test GPIOs */
	if (is_test_irq == 1) {
		gpio_demux_pins();
	}

	/* Request GPIO */
	gpio_request(gpio_num, "gpio_test");

	/* set direction */
	if (dir == GPIO_DIR_IN) {
		gpio_direction_input(gpio_num);

		/* If direction is input, setup another tx gpio so that
		 * loopback data back to input gpio.
		 */
		gpio_direction_output(gpio_src, 0);
	} else {
		gpio_direction_output(gpio_num, 0);
	}

	if (is_test_irq == 1) {
		printk("<1> IRQ number after gpio_to_irq() is: %d \n", __gpio_to_irq(gpio_num));
		gpio_request_irq(__gpio_to_irq(gpio_num));
	}

	/* toggle gpio output */
	gpio_write();

	/* get register values */
	printk("<1> \n");
	gpio_get_dir_reg_info(gpio_num);
	gpio_get_out_data_reg_info(gpio_num);
	gpio_get_in_data_reg_info(gpio_num);
	gpio_get_set_ris_reg_info(gpio_num);
	gpio_get_set_fal_reg_info(gpio_num);
	gpio_get_intstat_reg_info(gpio_num);
	gpio_get_binten_reg_info();

	if (is_disable_irq) {
		/* test disable irq */
		printk("<1> Disable IRQ - %d\n", __gpio_to_irq(gpio_num));
		disable_irq(__gpio_to_irq(gpio_num));
		gpio_write();

		/* get register values */
		gpio_get_dir_reg_info(gpio_num);
		gpio_get_out_data_reg_info(gpio_num);
		gpio_get_in_data_reg_info(gpio_num);
		gpio_get_set_ris_reg_info(gpio_num);
		gpio_get_set_fal_reg_info(gpio_num);
		gpio_get_intstat_reg_info(gpio_num);
		gpio_get_binten_reg_info();
	}
	return 0;
}

void gpio_test_exit(void)
{

	printk("<1> Exiting GPIO Test\n");

	if (is_test_irq) {
		gpio_unrequest_irq(__gpio_to_irq(gpio_num));
	}
}

module_init(gpio_test_init);
module_exit(gpio_test_exit);

MODULE_LICENSE("GPL");
