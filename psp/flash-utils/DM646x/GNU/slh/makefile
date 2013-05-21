#############################################################
# Makefile for TI Serial Loader Host (SLH) project.         #
#   Generates the Host executable file that is used in      #
#   in conjunction with the SLT to send and boot over UART. #
#   This executable is dependent on the SLT binary having   #
#   been generated first.                                   #
#############################################################
# Auth: Daniel Allred
#	    
PROGRAM:=slh

MONOCOMPILE=gmcs
DOTNETCOMPILE=csc
REMOTESOURCES=$(PROGRAM).cs device_name.cs Debug.cs CRC32.cs EmbeddedFileIO.cs FileIO.cs SerialIO.cs ConsoleUtility.cs
DEVSTRING=DM646x

ifeq ($(DEVICE),DM6441)
    DEVSTRING=DM6441
endif
ifeq ($(DEVICE),DM6441_LV)
    DEVSTRING=DM6441LV
endif

OBJECTS:=$(patsubst %.cs,%.module,$(REMOTESOURCES))
EXECUTABLE:=../$(PROGRAM)_$(DEVSTRING).exe
COMMONPATH:=../../../Common
ICONPATH:=$(COMMONPATH)/ti.ico
UTILLIBPATH:=$(COMMONPATH)/UtilLib
SLTPATH:=../slt
SLTIMAGE:=$(SLTPATH)/slt_$(DEVSTRING).bin

# Target definitions
all: $(EXECUTABLE) $(OBJECTS)

.PHONY : clean
clean:
		-rm -f -v $(EXECUTABLE) $(OBJECTS)

$(EXECUTABLE): $(OBJECTS) $(SLTIMAGE)
ifeq ($(shell uname),Linux)
		@$(MONOCOMPILE) -t:exe -resource:$(SLTIMAGE) -define:$(DEVSTRING) -out:$(EXECUTABLE) $(OBJECTS)
else
		@$(DOTNETCOMPILE) /t:exe /resource:$(SLTIMAGE) /define:$(DEVSTRING) /out:$(EXECUTABLE) /win32icon:$(ICONPATH) $(OBJECTS)
endif

%.module: %.cs
		@cp $< $@


vpath %.cs $(UTILLIBPATH)/:$(COMMONPATH)/slh/:../../Common/src/


