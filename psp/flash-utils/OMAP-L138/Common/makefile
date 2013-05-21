#############################################################
# Makefile for TI hexAIS project.                           #
#############################################################
# Auth: Daniel Allred
# Vers: v1.01 on 18-Feb-2008
#	    
PROGRAM:=hexAIS

MONOCOMPILE=gmcs
DOTNETCOMPILE=csc
LOCALSOURCES=$(PROGRAM).cs
REMOTESOURCES=DM643x_AISGen.cs Endian.cs EmbeddedFileIO.cs Debug.cs COFF.cs AISGen.cs
DEVSTRING=DM643x

OBJECTS:=$(patsubst %.cs,%.module,$(REMOTESOURCES))
EXECUTABLE:=../$(PROGRAM)_$(DEVSTRING)_.exe

ICONPATH:=$(COMMONPATH)/ti.ico

COMMONPATH:=../../../Common
UTILLIBPATH:=$(COMMONPATH)/UtilLib

DEVCOMMONPATH:=../../Common
DEVAISGENPATH:=$(DEVCOMMONPATH)/AISGen

AISEXTRAPATH:=../AISExtra
AISEXTRAIMAGE:=$(AISEXTRAPATH)/dm643x_AISExtra.out

# Target definitions
all: $(EXECUTABLE) $(OBJECTS)

.PHONY : clean
clean:
		-rm -f -v $(EXECUTABLE) $(OBJECTS)

$(EXECUTABLE): $(LOCALSOURCES) $(OBJECTS) $(AISEXTRAIMAGE)
ifeq ($(shell uname),Linux)
		@$(MONOCOMPILE) -t:exe -resource:$(AISEXTRAIMAGE) -define:$(DEVSTRING) -out:$(EXECUTABLE) $(LOCALSOURCES) $(OBJECTS)
else
		@$(DOTNETCOMPILE) /t:exe /resource:$(AISEXTRAIMAGE) /define:$(DEVSTRING) /out:$(EXECUTABLE) /win32icon:$(ICONPATH) $(LOCALSOURCES) $(OBJECTS)
endif

%.module: %.cs
		@cp $< $@

vpath %.cs $(UTILLIBPATH)/:$(DEVAISGENPATH)/





