#############################################################
# Makefile for TI hexAIS project.                           #
#############################################################
# Auth: Daniel Allred
#	    
PROGRAM:=SecureHexAIS
DEVSTRING:=DM643x_Secure

MONOCOMPILE=gmcs
DOTNETCOMPILE=csc
LOCALSOURCES=$(PROGRAM).cs
REMOTESOURCES=device_name.cs AISGen_$(DEVSTRING).cs Ini.cs CRC32.cs Endian.cs FileIO.cs EmbeddedFileIO.cs ASN1.cs CryptoUtility.cs Debug.cs COFF.cs HexConv.cs AISGen.cs SecureAISGen.cs SerialIO.cs

OBJECTS:=$(patsubst %.cs,%.module,$(REMOTESOURCES))
EXECUTABLE:=../$(PROGRAM)_$(DEVSTRING).exe

COMMONPATH:=../../../../Common
ICON:=$(COMMONPATH)/ti.ico
UTILLIBPATH:=$(COMMONPATH)/UtilLib
AISGENLIBPATH:=$(COMMONPATH)/AISGenLib

DEVCOMMONPATH:=../../../Common
GNUCOMMONPATH:=../../Common
DEVAISGENLIBPATH:=$(GNUCOMMONPATH)/AISGenLib

# Target definitions
all: $(EXECUTABLE) $(OBJECTS) $(LOCALSOURCES) $(REMOTESOURCES) 

.PHONY : clean
clean:
		-rm -f -v $(EXECUTABLE) $(OBJECTS)

$(EXECUTABLE): $(LOCALSOURCES) $(OBJECTS) $(REMOTESOURCES)
ifeq ($(shell uname),Linux)
		@$(MONOCOMPILE) -t:exe -out:$(EXECUTABLE) $(LOCALSOURCES) $(OBJECTS)
else
		@$(DOTNETCOMPILE) /t:exe /out:$(EXECUTABLE) /win32icon:$(ICON) $(LOCALSOURCES) $(OBJECTS)
endif 

%.module: %.cs
		@cp $< $@

vpath %.cs $(UTILLIBPATH)/:$(DEVAISGENLIBPATH)/:$(AISGENLIBPATH)/:$(DEVCOMMONPATH)/src/
