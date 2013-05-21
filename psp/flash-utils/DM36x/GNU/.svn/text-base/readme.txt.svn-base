/****************************************************************
 *  TI DM36x Serial Loading and Flashing Utilities              *
 *  (C) 2009, Texas Instruments, Inc.                           *
 *                                                              *
 ****************************************************************/
 
This readme describes the usage of the Serial Flasher and Serial
Loader utilities.  Each utility consists of two separate projects, 
a host and a target.  The target portions of the utilities are embedded
into the host executable during the build process. The two executable 
files are
  sfh_DM36x.exe  -  Serial Flashing Host
  slh_DM36x.exe  -  Serial Loading Host
Running
=======

- Under Windows - 
This utilites can be run from the commandline under Windows with 
the .Net Framework 2.0 or later installed.  

  sfh_DM36x.exe [options]
  slh_DM36x.exe [options]
	
- Under Linux -
They can also be run on a Linux machine with the latest open-source Mono
Framework installed.

  mono sfh_DM36x.exe [options]
  mono slh_DM36x.exe [options]

 
Compiling
=========

A makefile is included for compiling the host and target parts of each utility.
The target portions are built first since they are embedded into the the host
executables.  These target portions are loaded to the DM36x device via the UART
boot mode.


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
  
The above instructions assume the that GNU ARM cross-compiler tools (arm_v5t_le-gcc, 
etc.) are somewhere in the current PATH.
	

Serial Loader Usage
===================
More info can be found by running the utility with the '-h' option.
	slh_DM36x.exe -h
	
1) Load a UBL or small UBL-like application to the DM36x IRAM
	
	slh_DM36x.exe -load2IRAM <UBL binary file>
	
2) Load a larger image compiled to run at start of DDR space 
	
	slh_DM36x.exe -load2DDR <binary application file>
	
For the load to IRAM option, the file size is limited to 14KB, and the 
application assumes an entry point address of 0x0100 (the smallest 
allowed).  The entry point address canbe modified by using the -startAddr
command line option, with the address specified in hex.

For the load to DDR option, the file size is limited to 32MB, and the 
application assumes a load address and entry point address of 0x80000000.
The entry point address can be altered by using the -startAddr command line option, 
as with the -load2IRAM case.  The load address can be altered from the default by 
using the -loadAddr command line option


Serial Flasher Usage
====================
More info can be found by running the utility with the '-h' option.
	sfh_DM36x.exe -h
	
1) Erase the NAND flash
	
	sfh_DM36x.exe -nanderase
	
2) Flash the NAND with a UBL and u-boot image
	
	sfh_DM36x.exe -nandflash  <UBL binary file> <binary application file>
	
The entry point of the UBL is assumed to be 0x0100, but this can be changed by using 
the -UBLStartAddr option.  The entry point and load address of the application default
to 0x81080000 (u-boot defaults).  To change these values, use the -APPStartAddr and 
-APPLoadAddr option.

NOTE: Currently, YOU MUST USE THE UBL BINARY CREATED BY THE UBL PROJECT IN THIS PACKAGE.
      If you use any other UBL binary, the boot procedure will most likely fail.



Other Options for Both Utilities
================================

-p <COM PORT NAME>  : Allows specifying com port other than default 'COM1' 
                      or '/dev/ttyS0'.

-h                  : Show help text.
-v                  : See verbose output from the DM36x.



