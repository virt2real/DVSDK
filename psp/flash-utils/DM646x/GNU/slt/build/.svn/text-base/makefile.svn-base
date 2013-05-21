#############################################################
# Makefile for TI Serial Loader Target (SLT) project.       #
#   Generates the binary SLT file that is intended to be    #
#   executed on the device for loading code via UART.       #
#############################################################
# Author:   Daniel Allred
#
PROGRAM:=slt

CROSSCOMPILE=arm-none-linux-gnueabi-
CC=$(CROSSCOMPILE)gcc
OBJCOPY=$(CROSSCOMPILE)objcopy
OBJDUMP=$(CROSSCOMPILE)objdump
LDFLAGS=-Wl,-T$(LINKERSCRIPT) -nostdlib 
OBJCOPYFLAGS = --gap-fill 0xFF -S
SOURCES=$(PROGRAM).c boot.c selfcopy.c uartboot.c device.c debug.c uart.c util.c
DEVSTRING=DM646x
ENTRYPOINT=boot

CFLAGS:=-c -Os -Wall -mlong-calls -ffreestanding -I../../../Common/include -I../../../../Common/include -I../../../../Common/arch/arm926ejs/include -I../../../../Common/$(PROGRAM)/include -I../../../../Common/ubl/include -I../../../../Common/drivers/include -I../../../../Common/gnu/include

ifeq ($(DEVICE),DM6467_594)
  CFLAGS+= -DM6467_594MHz
  DEVSTRING=DM6467_594
endif
ifeq ($(DEVICE),DM6467_675)
  CFLAGS+= -DM6467_675MHz
  DEVSTRING=DM6467_675
endif
ifeq ($(DEVICE),DM6467_729)
  CFLAGS+= -DM6467_729MHz
  DEVSTRING=DM6467_729
endif
ifeq ($(DEVICE),DM6467_900)
  CFLAGS+= -DM6467_900MHz
  DEVSTRING=DM6467_900
endif
ifeq ($(DEVICE),DM6467_1000)
  CFLAGS+= -DM6467_1000MHz
  DEVSTRING=DM6467_1000
endif

OBJECTS:=$(patsubst %.c,%.o,$(SOURCES))
EXECUTABLE:=$(PROGRAM)_$(DEVSTRING)
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
		
%.o : %.c %.h
		$(CC) $(CFLAGS) $< -o $@      
        
# Search paths for code and header files
vpath %.h :../../../Common/include:../../../../Common/include:../../../../Common/arch/arm926ejs/include:../../../../Common/$(PROGRAM)/include:../../../../Common/ubl/include:../../../../Common/gnu/include:../../../../Common/drivers/include
vpath %.c ../../../Common/src:../../../../Common/src:../../../../Common/arch/arm926ejs/src:../../../../Common/$(PROGRAM)/src:../../../../Common/ubl/src:../../../../Common/gnu/src:../../../../Common/drivers/src

