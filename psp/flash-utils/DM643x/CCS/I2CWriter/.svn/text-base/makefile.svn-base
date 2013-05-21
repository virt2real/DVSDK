#############################################################
# Makefile for TI CCS I2CWriter project for DM643x.         #
#############################################################
# Auth: Daniel Allred
#	    
DEVSTRING:=DM643x
PROGRAM:=I2CWriter

PROJECTFILE=$(PROGRAM).pjt
EXECUTABLE=./Debug/$(PROGRAM).out


# Target definitions
.PHONY : all clean
all: 
		timake $(PROJECTFILE) Debug -a

clean:
		timake $(PROJECTFILE) Debug -clean



