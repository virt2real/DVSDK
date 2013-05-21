#############################################################
# Makefile for NANDWriter program for the OMAP-L137.        #
#############################################################
# Auth: Daniel Allred
#	    
PROGRAM:=NORWriter
DEVSTRING:=OMAP-L137

DSPPROJECTFILE=$(PROGRAM)_DSP.pjt
ARMPROJECTFILE=$(PROGRAM)_ARM.pjt
DSPEXECUTABLE=./Debug/$(PROGRAM)_DSP.out
ARMEXECUTABLE=./Debug/$(PROGRAM)_ARM.out

# Target definitions
.PHONY : all clean
all: 
		timake $(DSPPROJECTFILE) Debug -a
		timake $(ARMPROJECTFILE) Debug -a

clean:
		timake $(DSPPROJECTFILE) Debug -clean
		timake $(ARMPROJECTFILE) Debug -clean    


