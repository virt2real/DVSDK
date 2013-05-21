#############################################################
# Makefile for TI UBL project.                              #
#   Generates the binary UBL file can be used as the        #
#   secondary bootloader for the DM35x in NOR, NAND, and   #
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
DEVSTRING=DM35x
ENTRYPOINT=boot

CFLAGS:=-c -Os -Wall -ffreestanding -I../../../Common/include -I../../../../Common/include -I../../../../Common/arch/arm926ejs/include -I../../../../Common/$(PROGRAM)/include -I../../../../Common/drivers/include -I../../../../Common/gnu/include 
ifeq ($(TYPE),NAND)
	CFLAGS+= -DUBL_NAND
  SOURCES+= nand.c nandboot.c device_nand.c
endif
ifeq ($(TYPE),NOR)
  CFLAGS+= -DUBL_NOR
  SOURCES+= nor.c norboot.c 
endif
ifeq ($(TYPE),SDMMC)
	CFLAGS+= -DUBL_SDMMC
  SOURCES+= sdmmc.c sdmmcboot.c
endif

ifeq ($(DEVICE),DM355_216)
  CFLAGS+= -DM355_216MHz -DDM35X_STANDARD
  DEVSTRING=DM355_216
endif
ifeq ($(DEVICE),DM355_270)
  CFLAGS+= -DM355_270MHz -DDM35X_STANDARD
  DEVSTRING=DM355_270
endif
ifeq ($(DEVICE),DM355_216_LEGACY)
  CFLAGS+= -DM355_216MHz
  DEVSTRING=DM355_216_LEGACY
endif
ifeq ($(DEVICE),DM355_270_LEGACY)
  CFLAGS+= -DM355_270MHz
  DEVSTRING=DM355_270_LEGACY
endif

OBJECTS:=$(patsubst %.c,%_$(TYPE)_$(DEVSTRING).o,$(SOURCES))
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
		
%_$(TYPE)_$(DEVSTRING).o : %.c %.h
		$(CC) $(CFLAGS) $< -o $@      
        
# Search paths for code and header files
vpath %.h :../../../Common/include:../../../../Common/include:../../../../Common/arch/arm926ejs/include:../../../../Common/$(PROGRAM)/include:../../../../Common/gnu/include:../../../../Common/drivers/include
vpath %.c ../../../Common/src:../../../../Common/src:../../../../Common/arch/arm926ejs/src:../../../../Common/$(PROGRAM)/src:../../../../Common/gnu/src:../../../../Common/drivers/src

