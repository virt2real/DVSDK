#############################################################
# Makefile for UBL CCS project.                             #
#############################################################
# Auth: Daniel Allred
#	    
DEVSTRING:=DM357
PROGRAM:=UBL

PROJECTFILE=$(PROGRAM).pjt
NANDBIN=./$(PROGRAM)_$(DEVSTRING)_NAND.bin
NORBIN=./$(PROGRAM)_$(DEVSTRING)_NOR.bin


# Target definitions
.PHONY : all clean
all: 
		timake $(PROJECTFILE) BOOT_NAND
		timake $(PROJECTFILE) BOOT_NOR

clean:
		timake $(PROJECTFILE) BOOT_NAND -clean
		timake $(PROJECTFILE) BOOT_NOR -clean
		rm -f $(NORBIN)
		rm -f $(NANDBIN)

