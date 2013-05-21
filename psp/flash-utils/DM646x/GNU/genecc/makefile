#############################################################
# Makefile for ECC Generation (genecc) project.             #
#############################################################
# Auth: Daniel Allred
#	    
PROGRAM:=genecc
DEVSTRING:=DM646x

MONOCOMPILE=gmcs
DOTNETCOMPILE=csc
REMOTESOURCES=$(PROGRAM)_hamming.cs device_name.cs Debug.cs ECC.cs FileIO.cs
ICON=ti.ico

OBJECTS:=$(patsubst %.cs,%.module,$(REMOTESOURCES))
EXECUTABLE:=../$(PROGRAM)_$(DEVSTRING).exe
LOCAL_ICON:=ti.icon
COMMONPATH:=../../../Common
UTILLIBPATH:=$(COMMONPATH)/UtilLib
DEVCOMMONPATH:=../../Common
GNUCOMMONPATH:=../Common

# Target definitions
all: $(EXECUTABLE) $(OBJECTS)

.PHONY : clean
clean:
		-rm -f -v $(EXECUTABLE) $(OBJECTS) $(LOCAL_ICON)

$(EXECUTABLE): $(OBJECTS) $(LOCAL_ICON)
ifeq ($(shell uname),Linux)
		@$(MONOCOMPILE) -t:exe -define:$(DEVSTRING) -out:$(EXECUTABLE) $(OBJECTS)
else
		@$(DOTNETCOMPILE) /t:exe /define:$(DEVSTRING) /out:$(EXECUTABLE) /win32icon:$(LOCAL_ICON) $(OBJECTS)
endif

%.module: %.cs
		@cp $< $@

%.icon: %.ico
		@cp $< $@

vpath %.cs ./::$(COMMONPATH)/genecc/:$(UTILLIBPATH)/:$(GNUCOMMONPATH)/:$(DEVCOMMONPATH)/src/
vpath %.ico ./::$(COMMONPATH)


