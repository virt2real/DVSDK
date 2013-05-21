#############################################################
# Makefile for TI UBL project.                              #
#   Generates the binary UBL file can be used as the        #
#   secondary bootloader for the DM644x in NOR, NAND, and   #
#   UART boot modes.                                        #
#############################################################
# Author:   Daniel Allred
#
PROGRAM:=ubl

CROSSCOMPILE=arm-none-linux-gnueabi-
CC=$(CROSSCOMPILE)gcc
OBJCOPY=$(CROSSCOMPILE)objcopy
OBJDUMP=$(CROSSCOMPILE)objdump
LDFLAGS=-Wl,-T$(LINKERSCRIPT) -nostdlib 
OBJCOPYFLAGS = --gap-fill 0xFF -S
SOURCES=$(PROGRAM).c boot.c selfcopy.c uartboot.c device.c debug.c uart.c util.c
DEVSTRING=DM644x
ENTRYPOINT=boot

CFLAGS:=-c -Os -Wall -ffreestanding -I../../../Common/include -I../../../../Common/include -I../../../../Common/arch/arm926ejs/include -I../../../../Common/$(PROGRAM)/include -I../../../../Common/drivers/include -I../../../../Common/gnu/include 
ifeq ($(TYPE),nand)
	CFLAGS+= -DUBL_NAND
  SOURCES+= nand.c nandboot.c device_nand.c
endif
ifeq ($(TYPE),nor)
  CFLAGS+= -DUBL_NOR
  SOURCES+= nor.c norboot.c 
endif
ifeq ($(TYPE),sdmmc)
	CFLAGS+= -DUBL_SDMMC
  SOURCES+= sdmmc.c sdmmcboot.c
endif

ifeq ($(DEVICE),DM6441)
  CFLAGS+= -DDM6441
  DEVSTRING=DM6441
endif
ifeq ($(DEVICE),DM6441_LV)
  CFLAGS+= -DDM6441_LV
  DEVSTRING=DM6441LV
endif

OBJECTS:=$(patsubst %.c,%_$(TYPE).o,$(SOURCES))
EXECUTABLE:=$(PROGRAM)_$(DEVSTRING)_$(TYPE)
BINARY:=../$(EXECUTABLE).bin
LINKERSCRIPT=../$(PROGRAM).lds

# Target definitions
all: $(BINARY) $(OBJECTS)

.PHONY : clean objclean
clean:
		-rm -f -v $(OBJECTS) $(BINARY) $(EXECUTABLE)
		
objclean:
		-rm -f -v $(OBJECTS)
		
$(BINARY): $(EXECUTABLE)
		$(OBJCOPY) $(OBJCOPYFLAGS) -O binary $< $@
		@echo -n "The entry point of the binary is 0x"
		@$(OBJDUMP) -t $< | grep -E '[0-9a-f]{8}*[0-9a-f]{8} $(ENTRYPOINT)' | sed  's/^\([0-9a-f]\{4\}\)\([0-9a-f]\{4\}\).*/\2/'

$(EXECUTABLE): $(OBJECTS) $(LINKERSCRIPT)
		$(CC) $(LDFLAGS) $(OBJECTS) -o $@
		
%_$(TYPE).o : %.c %.h
		$(CC) $(CFLAGS) $< -o $@      
        
# Search paths for code and header files
vpath %.h :../../../Common/include:../../../../Common/include:../../../../Common/arch/arm926ejs/include:../../../../Common/$(PROGRAM)/include:../../../../Common/gnu/include:../../../../Common/drivers/include
vpath %.c ../../../Common/src:../../../../Common/src:../../../../Common/arch/arm926ejs/src:../../../../Common/$(PROGRAM)/src:../../../../Common/gnu/src:../../../../Common/drivers/src

