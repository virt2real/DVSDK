# Makefile for fbdev applications
# Appropriately change the below path

CMEMLIB=cmem.a470uC
CC = $(CROSS_COMPILE)gcc -I$(KERNEL_DIR)/include

all: ipipe

ipipe: ipipe.o ipipe_config.o config_table.o
	$(CC) -o ipipe $^ $(CMEMLIB)

%.o:%.c
	$(CC) $(CFLAGS) -c $^

clean:
	rm -f *.o *~ core ipipe
