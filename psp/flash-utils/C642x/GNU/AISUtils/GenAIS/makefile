#############################################################
# Makefile for TI hexAIS project.                           #
#############################################################
# Auth: Daniel Allred
#	    
PROGRAM:=GenAIS
DEVSTRING:=C642x

MONOCOMPILE=gmcs
DOTNETCOMPILE=csc
LOCALSOURCES=$(PROGRAM).cs
REMOTESOURCES=device_name.cs AISGen_$(DEVSTRING).cs CRC32.cs Endian.cs EmbeddedFileIO.cs Debug.cs COFF.cs AISGen.cs


OBJECTS:=$(patsubst %.cs,%.module,$(REMOTESOURCES))
EXECUTABLE:=../$(PROGRAM)_$(DEVSTRING).exe

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
all: $(EXECUTABLE) $(OBJECTS) $(LOCALSOURCES) $(AISEXTRAIMAGE) $(REMOTESOURCES) 

.PHONY : clean
clean:
		-rm -f -v $(EXECUTABLE) $(OBJECTS)

$(EXECUTABLE): $(LOCALSOURCES) $(OBJECTS) $(AISEXTRAIMAGE) $(REMOTESOURCES) 
ifeq ($(shell uname),Linux)
		@$(MONOCOMPILE) -t:exe -resource:$(AISEXTRAIMAGE) -define:$(DEVSTRING) -out:$(EXECUTABLE) $(LOCALSOURCES) $(OBJECTS)
else
		@$(DOTNETCOMPILE) /t:exe /resource:$(AISEXTRAIMAGE) /define:$(DEVSTRING) /out:$(EXECUTABLE) /win32icon:$(ICON) $(LOCALSOURCES) $(OBJECTS)
endif

%.module: %.cs
		@cp $< $@

vpath %.cs $(UTILLIBPATH)/:$(DEVAISGENLIBPATH)/:$(AISGENLIBPATH)/:$(DEVCOMMONPATH)/src/
