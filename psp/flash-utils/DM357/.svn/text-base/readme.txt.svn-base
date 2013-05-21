/****************************************************************
 *  TI DM644x Serial Application Flasher (DVFLasher)            *
 *  (C) 2007, Texas Instruments, Inc.                           *
 *                                                              *
 * History: 22-Jan-2007 - v1.00 release                         *
 *			01-Feb-2007 - v1.10 release                         *
 *			07-Mar-2007 - v1.11 release                         *
 *                                                              *
 ****************************************************************/
 
Running
=======

- Under Windows - 
This application can be run from the commandline under Windows with 
the .Net Framework 2.0 or later installed.  

	DVFlasher.exe [options]
	
- Under Linux -
It can also be run on a Linux machine with the latest open-source Mono
Framework installed.

	mono DVFlasher.exe [options]

 
Compiling
=========

A makefile is included for compiling the host application and the associated
UBL files (a NAND UBL and a NOR UBL).  The make command should be run from
the top-level directory (the one containing the 'DVFlasher' and the 'ubl'
directories). The UBL binaries are generated first.  These binary files are
then embedded into the DVFlasher executable when it is compiled. When 
DVFlasher is run, one of these is downloaded to the DM644x via the ROM 
boot loader(RBL). If the download is successful, the RBL passes execution 
control to the UBL. The host application continues running and interfacing 
to the UBL to perform the function specified by the command-line options.


- Under Windows - 
The currently supported method is to use the Cygwin enviroment (such as
the one provided with the Montavista Linux tools for Windows) and put the 
C sharp compiler's (the csc.exe executable) install location in the user's
path.  This compiler comes with the .NET Framework installation and can
usually be found in C:\WINDOWS\Microsoft.NET\Framework\<version number>.
Then go to the top level directory of the package and run:
	
	make


- Under Linux -
The Mono Framework must be installed and in the path.  RPMs are available 
at 'http://www.mono-project.com/Downloads'.  Then go to the top level
directory of the package and run:

	make
	

Custom Board Usage
==================

Note that to use aplication for flashing on a cutom PCB (not the DVEVM),
you will almost certainly need to modify some initialization code in the
UBL, specifically for the DDR2 RAM.  All of these customizations can be 
found in the 'dm644x.c' source file.  Use values calculated using the
formulas in the DDR2 Memory Controller User's Guide (SPRUE22).


DM6441 and DM6441 Low Voltage Support
=====================================
The UBLs and host application compile by default to support the DM6446 
and DM6443 devices (DSP @ 594 MHz, ARM @ 297 MHz, DDR @ 162 MHz).  The
makefiles support building the UBLs and the host application for the 
DM6441 (DSP @ 513 MHz, ARM @ 256 MHz, DDR @ 162 MHz) and the DM6441 
Low Voltage (DSP @ 405 MHz, ARM @ 202 MHz, DDR @ 135 MHz) devices. To do
this use the following commands from the top level directory
	
	make DM6441
	make DM6441_LV 


Switch and Jumper Settings for DVEVM
====================================

On the DVEVM you need to make sure the S3-3 switch and J4 jumper are 
correctly set for the flash type you will be using and to boot in UART
boot mode

  NOR - J4=FLASH, S3[1..4] = 1110 (UART boot, 16-bit AEMIF, ARM boots DSP)
  NAND - J4=NAND, S3[1..4] = 1100 (UART boot, 8-bit AEMIF, ARM boots DSP)

To run the DVEVM demos with the ARM set to boot the DSP, also make sure you
are using the latest U-boot sources from TI.


Usage
=====
Use of the application is simple, but if you need more info type 
	DVFlasher.exe -h
	
1) Global Erase of NOR Flash (this is recommended to start if you are 
   using this application to restore your flash to a bootable state)
	
	DVFlasher.exe -enor 		
	
2) Global Erase of NAND Flash (this is recommended to start if you are 
   using this application to restore your flash to a bootable state)
	
	DVFlasher.exe -enand
	
3) Restore the NOR Flash to a bootable state:
	
	DVFlasher.exe -r u-boot-xxx-nor.bin 
	
   where xxx=567 or 594.
   
4) Boot/Run an application over UART.
	
	DVFlasher.exe -b <application file>
	
   where <application file> is a binary or S-record file that you want 
   the board to execute out of RAM.  This application will be downloaded 
   over the UART and execution will pass from the UBL to the application.

   
Advanced Usage
==============
1) Flash an s-record application image (like u-boot) to NAND along with
   the necessary UBL image and headers needed to boot out of NAND.

	DVFlasher.exe -fnandsrec u-boot-nand.bin 
	
2) Flash a binary application image (like u-boot) to NAND along with
   the necessary UBL image and headers needed to boot out of NAND.
		
	DVFlasher.exe -fnandbin u-boot-nand.bin 

Note: There are no 594 and 567 versions of the NAND u-boot since in the 
NAND boot mode the UBL turns on the PLL and memory.  If you need 567
frequency settings you will need to edit the provided UBL code in
'dm644x.c' to acheive this.
	   
3) Flash an s-record application image (like u-boot) to NOR along with
   the necessary UBL image and headers needed to boot out of NOR.  In 
   this case the UBL image is placed at the beginning of NOR and will 
   run out of reset.  The UBL will find the application image in NOR and
   load it to RAM to run.
   
	DVFlasher.exe -fnorsrec <special u-boot>.bin 
	
4) Flash an binary application image (like u-boot) to NOR along with
   the necessary UBL image and headers needed to boot out of NOR.  In 
   this case the UBL image is placed at the beginning of NOR and will 
   run out of reset.  The UBL will find the application image in NOR and
   load it to RAM to run.
   
	DVFlasher.exe -fnorbin <special u-boot>.bin 
	
NOTE: The provided NOR U-boot images do not work in this fashion, since
      they include automatic relocation code.  You must compile a special
      u-boot (or your own application) that can run directly out of RAM.
      The included u-boot-uart.bin works in this fashion but is very 
      limited since it can't access flash memory.

NOTE: The S-record image is more secure since checksums are performed on 
      the data as it is copied from flash to RAM, but the S-record image
      is approximately three times bigger than the binary image.
	  

Other Options
=============

-p <COM PORT NAME> 	: Allows specifying com port other than default 'COM1' 
                      or '/dev/ttyS0'.
-s <APP Start Addr>	: Allows specifying the memory address location that
                      downloaded application code will run from.
-h					: Show help text.
-v					: See verbose output from the DM644x.
-noRBL				: If the board is booting the supplied UART UBL (you
                      see BOOTPSP, instead of BOOTME), use this to skip 
                      sending the UART UBL, and start by sending a command
-useMyUBL <UBLFILE> : Use this provide your own UBL that will be put in 
                      flash and will be used for booting (either NAND or
                      NOR depending on how your own UBL is written).  Note 
                      that this option does not affect the UBL that is 
                      used to communicate over the UART (the one that is
                      sent via the RBL - referred to as the UART UBL).  
                      Also note that this option must be used with one of
                      the flashing commands (fnorsrec,fnorbin,fnandsrec,
                      or fnandbin)



