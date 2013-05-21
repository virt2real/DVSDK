#############################################################
# Makefile for UBL CCS project.                             #
#############################################################
# Auth: Daniel Allred
# Vers: v1.00 on 29-Jan-2008
#	    
PROGRAM:=UBL
DEVSTRING:=DM35x

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
		rm -f $(NANDBIN)
		rm -f $(NORBIN)


