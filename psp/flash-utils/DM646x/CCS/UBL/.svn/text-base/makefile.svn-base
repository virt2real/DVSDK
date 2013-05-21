#############################################################
# Makefile for UBL CCS project.                             #
#############################################################
# Auth: Daniel Allred
#	    
PROGRAM:=UBL
DEVSTRING:=DM646x

NANDPROJECTFILE=$(PROGRAM)_NAND.pjt
NORPROJECTFILE=$(PROGRAM)_NOR.pjt
NANDBIN:=$(wildcard $(PROGRAM)_$(DEVSTRING)_NAND_*.bin)
NORBIN:=$(wildcard $(PROGRAM)_$(DEVSTRING)_NOR_*.bin)


# Target definitions
.PHONY : all clean
all: 
		timake $(NANDPROJECTFILE) DM6467_594MHz -a
		timake $(NANDPROJECTFILE) DM6467_675MHz -a
		timake $(NANDPROJECTFILE) DM6467_729MHz -a
		timake $(NANDPROJECTFILE) DM6467_900MHz -a
		timake $(NANDPROJECTFILE) DM6467_1000MHz -a
		timake $(NORPROJECTFILE) DM6467_594MHz -a
		timake $(NORPROJECTFILE) DM6467_675MHz -a
		timake $(NORPROJECTFILE) DM6467_729MHz -a
		timake $(NORPROJECTFILE) DM6467_900MHz -a
		timake $(NORPROJECTFILE) DM6467_1000MHz -a  

clean:
		timake $(NANDPROJECTFILE) DM6467_594MHz -clean
		timake $(NANDPROJECTFILE) DM6467_675MHz -clean
		timake $(NANDPROJECTFILE) DM6467_729MHz -clean
		timake $(NANDPROJECTFILE) DM6467_900MHz -clean
		timake $(NANDPROJECTFILE) DM6467_1000MHz -clean
		timake $(NORPROJECTFILE) DM6467_594MHz -clean
		timake $(NORPROJECTFILE) DM6467_675MHz -clean
		timake $(NORPROJECTFILE) DM6467_729MHz -clean
		timake $(NORPROJECTFILE) DM6467_900MHz -clean
		timake $(NORPROJECTFILE) DM6467_1000MHz -clean
		rm -f $(NANDBIN)
		rm -f $(NORBIN)


