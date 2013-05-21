#############################################################
# Makefile for TI AISExtra project.                         #
#   Generates the COFF AISExtra file which is used to       #
#   supplement the AIS ROM bootloader to add the ability    #
#   to boot successfully over UART and to change the power  #
#   domain states of the DM643x's Local Power Domains.      #
#############################################################
# Auth: Daniel Allred
#
PROGRAM:=AISExtra

CROSSCOMPILE=
CC=$(CROSSCOMPILE)cl6x
SOURCES=dm643x.c
DEVSTRING=DM643x

CFLAGS=-O=2 -c -I=../../../../../Common/include -I=../../../../Common/include -I=../../../Common/include -I=../include -ms3 -mv6400+ --symdebug:none
LNKFLAGS=-z -a -u_UARTSendDONE -e_LPSCTransition -w -x

OBJECTS:=$(patsubst %.c,%.obj,$(SOURCES))
EXECUTABLE:=../$(PROGRAM)_$(DEVSTRING).out
LINKERSCRIPT:=AISExtra.cmd

all: $(EXECUTABLE) $(OBJECTS) $(LINKERSCRIPT)

.PHONY : clean objclean
clean:
		-rm -f -v $(OBJECTS) $(EXECUTABLE)
		
objclean:
		-rm -f -v $(OBJECTS)

$(EXECUTABLE): $(OBJECTS)
		$(CC) $(LNKFLAGS) -o=$@ $(LINKERSCRIPT) $(OBJECTS)
		
%.obj : %.c %.h
		$(CC) $(CFLAGS) $< 

vpath %.h ../../../../Common/include:../../../Common/include:../../Common/include:../include        

