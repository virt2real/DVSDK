#############################################################
# Makefile for TI Serial Flasher Host (SFH) project.        #
#   Generates the Host executable file that is used in      #
#   in conjunction with the SFT to send and boot over UART. #
#   This executable is dependent on the SFT binary having   #
#   been generated first.                                   #
#############################################################
# Auth: Daniel Allred
#	    
PROGRAM:=sfh

MONOCOMPILE=gmcs
DOTNETCOMPILE=csc
REMOTESOURCES=$(PROGRAM).cs device_name.cs Debug.cs CRC32.cs EmbeddedFileIO.cs FileIO.cs SerialIO.cs ConsoleUtility.cs
DEVSTRING=DM35x

OBJECTS:=$(patsubst %.cs,%.module,$(REMOTESOURCES))
EXECUTABLE:=../$(PROGRAM)_$(DEVSTRING).exe
COMMONPATH:=../../../Common
ICONPATH:=$(COMMONPATH)/ti.ico
UTILLIBPATH:=$(COMMONPATH)/UtilLib
SFTPATH:=../sft
NORSFTIMAGE:=$(SFTPATH)/sft_$(DEVSTRING)_nor.bin
NANDSFTIMAGE:=$(SFTPATH)/sft_$(DEVSTRING)_nand.bin

# Target definitions
all: $(EXECUTABLE) $(OBJECTS)

.PHONY : clean
clean:
		-rm -f -v $(EXECUTABLE) $(OBJECTS)

$(EXECUTABLE): $(OBJECTS) $(NORSFTIMAGE) $(NANDSFTIMAGE)
ifeq ($(shell uname),Linux)
		@$(MONOCOMPILE) -t:exe -resource:$(NORSFTIMAGE) -resource:$(NANDSFTIMAGE) -define:$(DEVSTRING) -out:$(EXECUTABLE) $(OBJECTS)
else
		@$(DOTNETCOMPILE) /t:exe /resource:$(NORSFTIMAGE) /resource:$(NANDSFTIMAGE) /define:$(DEVSTRING) /out:$(EXECUTABLE) /win32icon:$(ICONPATH) $(OBJECTS)
endif

%.module: %.cs
		@cp $< $@


vpath %.cs $(UTILLIBPATH)/:$(COMMONPATH)/sfh/:../../Common/src/


