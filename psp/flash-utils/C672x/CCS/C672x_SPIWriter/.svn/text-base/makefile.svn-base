#############################################################
# Makefile for TI CCS SPIWriter project for C672x.          #
#############################################################
#	    
DEVSTRING:=C672x
PROGRAM:=$(DEVSTRING)_SPIWriter


PROJECTFILE=$(PROGRAM).pjt
EXECUTABLE=./Debug/$(PROGRAM).out

# Target definitions
.PHONY : all clean
all: 
		timake $(PROJECTFILE) Debug -a

clean:
		timake $(PROJECTFILE) Debug -clean



