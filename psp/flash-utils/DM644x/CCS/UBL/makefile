#############################################################
# Makefile for UBL CCS project.                             #
#############################################################
# Auth: Daniel Allred
#	    
DEVSTRING:=DM644x
PROGRAM:=UBL

PROJECTFILE=$(PROGRAM).pjt
NANDBIN=./$(PROGRAM)_$(DEVSTRING)_NAND.bin
NORBIN=./$(PROGRAM)_$(DEVSTRING)_NOR.bin
NANDBIN41=./$(PROGRAM)_DM6441_NAND.bin
NORBIN41=./$(PROGRAM)_DM6441_NOR.bin
NANDBIN41LV=./$(PROGRAM)_DM6441LV_NAND.bin
NORBIN41LV=./$(PROGRAM)_DM6441LV_NOR.bin



# Target definitions
.PHONY : all clean
all: 
		timake $(PROJECTFILE) BOOT_NAND
		timake $(PROJECTFILE) BOOT_NAND_DM6441
		timake $(PROJECTFILE) BOOT_NAND_DM6441LV    
		timake $(PROJECTFILE) BOOT_NOR
		timake $(PROJECTFILE) BOOT_NOR_DM6441
		timake $(PROJECTFILE) BOOT_NOR_DM6441LV

clean:
		timake $(PROJECTFILE) BOOT_NAND -clean
		timake $(PROJECTFILE) BOOT_NAND_DM6441 -clean
		timake $(PROJECTFILE) BOOT_NAND_DM6441LV -clean
		timake $(PROJECTFILE) BOOT_NOR -clean
		timake $(PROJECTFILE) BOOT_NOR_DM6441 -clean
		timake $(PROJECTFILE) BOOT_NOR_DM6441LV -clean
		rm -f $(NORBIN)
		rm -f $(NANDBIN)
		rm -f $(NORBIN41)
		rm -f $(NANDBIN41)
		rm -f $(NORBIN41LV)
		rm -f $(NANDBIN41LV)
