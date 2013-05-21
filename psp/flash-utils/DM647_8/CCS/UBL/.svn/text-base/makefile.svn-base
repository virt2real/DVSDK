#############################################################
# Makefile for TI CCS NORWriter project for DM648.          #
#############################################################
# Auth: Daniel Allred
# Vers: v1.00 on 03-Mar-2008
#	    
PROGRAM:=UBL
DEVSTRING:=DM648

PROJECTFILE=$(PROGRAM).pjt
EXECUTABLE=./Debug/$(PROGRAM).out


# Target definitions
.PHONY : all clean
all: 
		timake $(PROJECTFILE) Debug -a
		timake $(PROJECTFILE) DDR_512MB -a

clean:
		timake $(PROJECTFILE) Debug -clean
		timake $(PROJECTFILE) DDR_512MB -clean



