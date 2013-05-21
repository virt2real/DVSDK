/**+--------------------------------------------------------------------------+**
**|                            ****                                          |**
**|                            ****                                          |**
**|                            ******o***                                    |**
**|                      ********_///_****                                   |**
**|                      ***** /_//_/ ****                                   |**
**|                       ** ** (__/ ****                                    |**
**|                           *********                                      |**
**|                            ****                                          |**
**|                            ***                                           |**
**|                                                                          |**
**|         Copyright (c) 1998-2008 Texas Instruments Incorporated           |**
**|                        ALL RIGHTS RESERVED                               |**
**|                                                                          |**
**| Permission is hereby granted to licensees of Texas Instruments           |**
**| Incorporated (TI) products to use this computer program for the sole     |**
**| purpose of implementing a licensee product based on TI products.         |**
**| No other rights to reproduce, use, or disseminate this computer          |**
**| program, whether in part or in whole, are granted.                       |**
**|                                                                          |**
**| TI makes no representation or warranties with respect to the             |**
**| performance of this computer program, and specifically disclaims         |**
**| any responsibility for any damages, special or consequential,            |**
**| connected with the use of this program.                                  |**
**|                                                                          |**
**+--------------------------------------------------------------------------+**
*******************************************************************************/

This README file describes how to invoke the loopback commands for doing
capture through vpfe capture driver from a video source such as tvp5146 or a
camera source such as mt9t031 and display the video using fbdev.

NAME

	fbdev_loopback/fbdev_loopback_userptr -  fbdev based video loopback
	blend		- Providing blending between video and osd windows

SYNOPSIS

	fbdev_loopback [ARGUMENTS]

	ARGUMENTS
		-i <input> input values:- 0 - composite, 1 - S-Video, 2 - Camera
		-m <standard>, standard values:- 0 - NTSC, 1 - PAL
		-f <field>, field values:- 0 - INTERLACED, 1 - TOP BOTTOM (TB)
		-s <stress>, stress values:-  0 - disable, 1 - enable
		-d <display>, display :- 0 - disable, 1 - enable
		-w <save frame>, save frame values:- 0 - disable, 1 - disable
		-p <print frame number>, values:- 0 - disable, 1 - enable
		-l <crop width>
		-h <crop_height>
		-b <crop_left>
		-t <crop_top>
		-c <crop_enable>

	blend [ARGUMENT]

	ARGUMENT
		<value> blend vlaue range [0-7]

DESCRIPTION:

This is a video loopback program that allows capture from a TVP5146 composite or 
S-Video input source through vpfe capture driver and display through vpfe composite
output using frame buffer device.  It has two versions. fbdev_loopback uses MMAP
user buffer exchange mechanism at vpfe capture driver. fbdev_loopback_userptr
allocates frame buffer using CMEM utility and then configure vpfe capture to use
USERPTR buffer exchange mechanism. 

When doing camera capture, disable display since the captured data is Bayer RGB
format which requires format conversion before display. Use -d 0 to do this.

Before building, set KERNEL_DIR in Makefile to your kernel tree top level directory.

AUTHOR
       Written by Murali Karicheri

REPORTING BUGS
       Fix it yourself or Report bugs to <m-karicheri2@ti.com>.

