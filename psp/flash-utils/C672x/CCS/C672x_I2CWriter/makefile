#############################################################
# Makefile for TI CCS NORWriter project for C672x.          #
#############################################################
# Auth: Daniel Allred
# Vers: v1.00 on 21-Feb-2008
#	    
DEVSTRING:=C672x
PROGRAM:=$(DEVSTRING)_NORWriter


PROJECTFILE=$(PROGRAM).pjt
EXECUTABLE=./Debug/$(PROGRAM).out


# Target definitions
.PHONY : all clean
all: 
		timake $(PROJECTFILE) Debug -a

clean:
		timake $(PROJECTFILE) Debug -clean



