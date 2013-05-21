# Makefile for fbdev applications
# Change the kernel patch to point to personal Linux Tree

CMEMLIB=cmem.a470uC
CC = $(CROSS_COMPILE)gcc -I$(KERNEL_DIR)/include
INSTALL_DIR=$(FINAL_DEST)/vdce

all: saResize saBlending saCCV420_422 saDisplay

saDisplay: saDisplay.o
	$(CC) -o  saDisplay $^

saResize: saResize.o
	$(CC) -o  saResize $^

saBlending: saBlending.o
	$(CC) -o  saBlending $^

saCCV420_422: saCCV420_422.o
	$(CC) -o  saCCV420_422 $^
%.o:%.c
	$(CC) $(CFLAGS) -c $^

install:
	mkdir -p $(INSTALL_DIR)
	cp saResize $(INSTALL_DIR)
	cp saBlending $(INSTALL_DIR)
	cp saCCV420_422 $(INSTALL_DIR)
	cp saDisplay $(INSTALL_DIR)

clean:
	rm -f *.o *~ core saResize saBlending saCCV420_422
