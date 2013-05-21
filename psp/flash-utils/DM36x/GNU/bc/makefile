#############################################################
# Makefile for TI Boot Loader Bin Creator (BC) project.     #
#   Generates the binary image with the appropriate header  #
#   in place for flashing boot loader images (UBL, U-boot)  #
#   within the U-boot  environment.                         #
#############################################################
# Auth: Daniel Allred
#

#Include the device specific make
include ../device.mak

PROGRAM:=bc

MONOCOMPILE=gmcs
DOTNETCOMPILE=csc
REMOTESOURCES=$(PROGRAM).cs device_name.cs Debug.cs CRC32.cs EmbeddedFileIO.cs FileIO.cs SerialIO.cs

OBJECTS:=$(patsubst %.cs,%.module,$(REMOTESOURCES))
EXECUTABLE:=../$(PROGRAM)_$(DEVSTRING).exe
COMMONPATH:=../../../Common
ICONPATH:=$(COMMONPATH)/ti.ico
UTILLIBPATH:=$(COMMONPATH)/UtilLib

# Target definitions
all: $(EXECUTABLE) $(OBJECTS)

.PHONY : clean
clean:
		-rm -f -v $(EXECUTABLE) $(OBJECTS)

$(EXECUTABLE): $(OBJECTS)
ifeq ($(shell uname),Linux)
		@$(MONOCOMPILE) -t:exe -define:$(DEVSTRING) -out:$(EXECUTABLE) $(OBJECTS)
else
		@$(DOTNETCOMPILE) /t:exe /define:$(DEVSTRING) /out:$(EXECUTABLE) /win32icon:$(ICONPATH) $(OBJECTS)
endif

%.module: %.cs
		@cp $< $@


vpath %.cs $(UTILLIBPATH)/:$(COMMONPATH)/bc/:../../Common/src/

