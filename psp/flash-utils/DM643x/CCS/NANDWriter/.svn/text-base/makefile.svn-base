#############################################################
# Makefile for TI CCS NANDWriter project for DM643x.        #
#############################################################
# Auth: Daniel Allred
#
DEVSTRING:=DM643x
PROGRAM:=NANDWriter


PROJECTFILE=$(PROGRAM).pjt
EXECUTABLE=./Debug/$(PROGRAM).out


# Target definitions
.PHONY : all clean
all: 
		timake $(PROJECTFILE) Debug -a

clean:
		timake $(PROJECTFILE) Debug -clean



