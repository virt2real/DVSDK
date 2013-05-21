#############################################################
# Makefile for TI hexAIS project.                           #
#############################################################
# Auth: Daniel Allred
#	    
PROGRAM:=SecureHexAIS
DEVSTRING:=OMAP-L138

MONOCOMPILE=gmcs
DOTNETCOMPILE=csc
LOCALSOURCES=$(PROGRAM).cs
REMOTESOURCES=device_name.cs AISGen_$(DEVSTRING).cs Ini.cs CRC32.cs Endian.cs FileIO.cs EmbeddedFileIO.cs ASN1.cs CryptoUtility.cs Debug.cs COFF.cs HexConv.cs AISGen.cs SecureAISGen.cs SerialIO.cs

OBJECTS:=$(patsubst %.cs,%.module,$(REMOTESOURCES))
EXECUTABLE_ROM1:=../$(PROGRAM)_$(DEVSTRING)_ROM1.exe
EXECUTABLE_ROM2:=../$(PROGRAM)_$(DEVSTRING)_ROM2.exe

COMMONPATH:=../../../../Common
ICON:=$(COMMONPATH)/ti.ico
UTILLIBPATH:=$(COMMONPATH)/UtilLib
AISGENLIBPATH:=$(COMMONPATH)/AISGenLib

DEVCOMMONPATH:=../../../Common
GNUCOMMONPATH:=../../Common
DEVAISGENLIBPATH:=$(GNUCOMMONPATH)/AISGenLib

AISEXTRAPATH:=../AISExtra
AISEXTRAIMAGE:=$(AISEXTRAPATH)/AISExtra_$(DEVSTRING).out

# Target definitions
all: $(EXECUTABLE_ROM1) $(EXECUTABLE_ROM2) $(AISEXTRAIMAGE) $(OBJECTS) $(LOCALSOURCES) $(REMOTESOURCES) 

.PHONY : clean
clean:
		-rm -f -v $(EXECUTABLE_ROM1) $(EXECUTABLE_ROM2) $(OBJECTS)

$(EXECUTABLE_ROM1): $(LOCALSOURCES) $(OBJECTS) $(AISEXTRAIMAGE) $(REMOTESOURCES) 
ifeq ($(shell uname),Linux)
		@$(MONOCOMPILE) -t:exe -resource:$(AISEXTRAIMAGE) -out:$@ -D:OLD_MPK_METHOD $(LOCALSOURCES) $(OBJECTS)
else
		@$(DOTNETCOMPILE) /t:exe /resource:$(AISEXTRAIMAGE) /out:$@ /win32icon:$(ICON) /D:OLD_MPK_METHOD $(LOCALSOURCES) $(OBJECTS)
endif

$(EXECUTABLE_ROM2): $(LOCALSOURCES) $(OBJECTS) $(AISEXTRAIMAGE) $(REMOTESOURCES) 
ifeq ($(shell uname),Linux)
		@$(MONOCOMPILE) -t:exe -resource:$(AISEXTRAIMAGE) -out:$@ $(LOCALSOURCES) $(OBJECTS)
else
		@$(DOTNETCOMPILE) /t:exe /resource:$(AISEXTRAIMAGE) /out:$@ /win32icon:$(ICON) $(LOCALSOURCES) $(OBJECTS)
endif

%.module: %.cs
		@cp $< $@

vpath %.cs $(UTILLIBPATH)/:$(DEVAISGENLIBPATH)/:$(AISGENLIBPATH)/:$(DEVCOMMONPATH)/src/
