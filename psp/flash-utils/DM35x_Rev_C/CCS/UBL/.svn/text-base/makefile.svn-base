#############################################################
# Makefile for UBL CCS project.                             #
#############################################################
# Auth: Daniel Allred
# Vers: v1.00 on 29-Jan-2008
#	    
PROGRAM:=UBL
DEVSTRING:=DM35x

NANDPROJECTFILE=$(PROGRAM)_NAND.pjt
NORPROJECTFILE=$(PROGRAM)_NOR.pjt
NANDBIN:=$(wildcard $(PROGRAM)_$(DEVSTRING)_NAND_*.bin)
NORBIN:=$(wildcard $(PROGRAM)_$(DEVSTRING)_NOR_*.bin)



# Target definitions
.PHONY : all clean
all:
		timake $(NANDPROJECTFILE) DM355_270MHz -a
		timake $(NANDPROJECTFILE) DM355_216MHz -a
		timake $(NANDPROJECTFILE) DM355_270MHz_LEGACY -a
		timake $(NANDPROJECTFILE) DM355_216MHz_LEGACY -a
		timake $(NORPROJECTFILE) DM355_270MHz -a
		timake $(NORPROJECTFILE) DM355_216MHz -a

clean:
		timake $(NANDPROJECTFILE) DM355_270MHz -clean
		timake $(NANDPROJECTFILE) DM355_216MHz -clean
		timake $(NANDPROJECTFILE) DM355_270MHz_LEGACY -clean
		timake $(NANDPROJECTFILE) DM355_216MHz_LEGACY -clean
		timake $(NORPROJECTFILE) DM355_270MHz -clean
		timake $(NORPROJECTFILE) DM355_216MHz -clean
		rm -f $(NANDBIN)
		rm -f $(NORBIN)


