# Makefile for fbdev applications
CMEMLIB=cmem.a470uC
CC = $(CROSS_COMPILE)gcc -I$(KERNEL_DIR)/include

all: fbdev_loopback fbdev_loopback_userptr blend

fbdev_loopback: fbdev_loopback.o
	$(CC) -o fbdev_loopback $^
fbdev_loopback_userptr: fbdev_loopback_userptr.o
	$(CC) -o fbdev_loopback_userptr $^ $(CMEMLIB)
blend: blend.o
	$(CC) -o blend $^

%.o:%.c
	$(CC) $(CFLAGS) -c $^

install:
	mkdir -p $(FINAL_DEST)/fbdev
	cp fbdev_loopback $(FINAL_DEST)/fbdev/
	cp fbdev_loopback_userptr $(FINAL_DEST)/fbdev/
	cp blend $(FINAL_DEST)/fbdev/

clean:
	rm -f *.o *~ core fbdev_loopback fbdev_loopback_userptr blend
